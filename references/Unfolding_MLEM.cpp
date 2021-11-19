/************************************************************************
 *
 *  Filename: Unfolding.cpp
 *
 *  Description:
 *    Maximum-Likelihood Expectation Maximization (MLEM)
 *
 *  Compile:
 *	  To compile use "g++ Unfolding.cpp -I. -o Program.exe"
 *
 *  Inputs:
 *    spectrum:   spectrum to be unfolded
 *    iterations: number of interations*
 *    binWidth: width of bins in spectrum in MeVee
 *    options:
 *          -c  terminate on convergence (default)
 *          -i  terminate when iterations complete
 *          -p  print result to output file
 *
 *
 *  Author(s):
 *     Haonan Zhu
 *     Michael T. Febbraro
 *
 *
 *  Creation Date: 2/8/2014
 *  Last modified: 2/8/2014
 *
 * -----------------------------------------------------
 *  Nuclear Reaction Group
 *  University of Michigan, Ann Arbor, MI, USA
 *  (c) All Rights Reserved.
 *
 */

#include <iostream>
#include <sstream>
#include <string>
#include "../Eigen/Eigen"
#include <fstream>
#include <queue>

using namespace Eigen;
using namespace std;

/** ----------------------------------------------------
* Variable declairation
*   ----------------------------------------------------
*/

  bool run = 1;
  double val;
  char filename[250], prompt;
  int I, J, k, iterations, eBins, lBins,sLength, NPS, N;
  int Nconstrains, Nmatrix[100], matrixIndex;
  double norm_factor, threshold, criteria, max_diff;
              //I: Number of inputs, J:Number of Outputs
  float lwidth, binWidth;
  MatrixXd R;  //Response Matrix
  MatrixXd y;  //Input
  MatrixXd Z; //Inverse of Response Matrix
  VectorXd Rs; //Vector of sums
  VectorXd x; //Output
  VectorXd diff; //difference between S(k+1) - S(k)
  VectorXd r; //Residuals
  VectorXd residual; //Residuals
  VectorXd dx; // Uncertainty
  VectorXd ax; // Average of x
  VectorXd t;  // temporary vector
  VectorXd s;  // Scaling vector
  MatrixXd sum;
  string line;
  clock_t Stop, Start;
  stringstream ss (stringstream::in | stringstream::out);
  ofstream out;

namespace Eigen

// Define a new fstream input method for matrix
{
    fstream& operator>>(fstream &fin, MatrixXd &mat) {
            int h=0, w,size=0;
            queue<double> In;
            getline(fin,line);
            ss.clear();
            ss<<line;
            for(size=0;ss>>val;size++);
            ss.clear();
            ss<<line;
            if(size == 3){
                 ss>>sLength;     cout << " - Number of bins: " << sLength << endl;
                 ss>>binWidth;    cout << " - Bin width: " << binWidth << " MeVee" << endl;
                 ss>>iterations;  cout << " - Iterations: " << iterations << endl;
            }
            else if(size == 4){
                  ss>> lBins; cout <<" - Light bins:" << lBins << endl;
                  ss >> eBins; cout <<" - Energy bins: " << eBins << endl;
                  ss>> NPS; cout << " - NPS: " << NPS << endl;
                  ss>> lwidth; cout << " - Bin width: " << lwidth << " MeVee" << endl;
            }
            else{
              cout<<"Wrong File Formatting ";
              exit(1);
            }
            while(getline(fin, line)){
                if(line.empty()) break;
                ss.clear();
                ss << line;
                while(ss >> val)
                {
			        //if(val<=threshold) val=0;
                    In.push(val);
                }
                if(h==0) w = In.size();
                h++;
            }
            mat = MatrixXd(h, w);
            int i=0,j=0;
            while(!In.empty()) {
                mat(i,j) = In.front();
                j++;
                if(j==w) {
                    j=0, i++;
                }
                In.pop();
            }
            return fin;

        }
}

MatrixXd Update(MatrixXd x,MatrixXd zero,int I)
//Replace all zeros terms in the matrix with 1
{
     MatrixXd check(I,1);
     stringstream ss (stringstream::in | stringstream::out);
     ss.clear();
     ss<<(x.array()==zero.array());
     queue<double> In;
     double val;
     while(ss >> val)
     {
       	In.push(val);
     }

     int i=0;
     while(i<I) {
         check(i,0) = In.front();
         i++;
         In.pop();
     }
     return x+check;
}

int main(int argc, char** argv)
{
    Start = clock();


	cout << "--------------------------------------" << endl;
	cout << "   MLEM spectrum unfolding            " << endl;
	cout << "--------------------------------------" << endl;
	cout << endl;

	cout << "Spectrum File: ";
	cin >> filename;

	cout << "Threshold: ";
	cin >> threshold;

  criteria = 1.0E-6;
  cout << "Stopping criteria : " << criteria << endl;

//threshold = 10;

	while (run)
	{

    /** ----------------------------------------------------
    * Load response matrix
    *   ----------------------------------------------------
    */
    cout << "\n" << "Loading response matrix..." << endl;

    fstream fin("matrix.txt",fstream::in);
    fin>>Z;
    cout << "Response Matrix loaded!\n" << endl;


    /** ----------------------------------------------------
    * Load spectrum
    *   ----------------------------------------------------
    */
    cout << "\n" << "Loading input spectrum..." << endl;
    fstream fan("spectrum.spe",fstream::in);
    fan>>y;
    cout << "Spectrum loaded!\n" << endl;

    I=(sLength>=lBins)*lBins+(sLength<lBins)*sLength;
    J=eBins;

    // Override number of Iterations
    //iterations = atoi(argv[1]);
    cout << "interations : " << iterations << endl;

	/** ----------------------------------------------------
    * Select operation mode
    *   ----------------------------------------------------
    */
	//cout << "Constrain matrix? (y/n):";
	//cin >> prompt;
  prompt = 'n';
	s=VectorXd::Zero(J);
	if (prompt == 'y' || prompt == 'Y')
	{
		cout << "Number of contrains: ";
		cin >> Nconstrains;

		for (int i = 0; i < Nconstrains; i++)
		{
			cout << "Value: ";
			cin >> matrixIndex;
			s(matrixIndex) = 1;
		}

	}



    /** ----------------------------------------------------
    * normalize, & rebin response matrix & input Spectrum
    * initilize important operational matrices/vectors
    *   ----------------------------------------------------
    */

	for (int i = 0; i < y.size(); i++)
	{
		if(i < threshold) {y(i) = 0;}
	}

  x=VectorXd::Ones(J);
	dx=VectorXd::Zero(J);
	residual=VectorXd::Zero(iterations);
	r=VectorXd::Zero(I);
	t=VectorXd::Zero(J);
	ax=VectorXd::Zero(J);
    VectorXd one=VectorXd::Ones(I);
    VectorXd zero1=VectorXd::Zero(I);
    VectorXd zero2=VectorXd::Zero(J);
    Z.conservativeResize(J,I);

	if (prompt == 'y' || prompt == 'Y')
	{
		for (int i = 0; i < Z.rows(); i++)
		{
			for (int j = 0; j < Z.cols(); j++)
			{
				Z(i,j) = s(i)*Z(i,j);
			}
		}
	}


	for (int i = 0; i < Z.rows(); i++)
	{
		norm_factor = 0;
		for (int j = 0; j < Z.cols(); j++)
		{
			if (j < threshold) {Z(i,j) = 0;}

			norm_factor += Z(i,j);
		}

		for (int j = 0; j < Z.cols(); j++)
		{
			if (norm_factor != 0) {
			Z(i,j) = Z(i,j)/norm_factor;
			}
			else Z(i,j) = 0;
		}
	}

    diff=VectorXd::Zero(I);
    R=Z.transpose();
    y.conservativeResize(I,1);
    sum=Update(Z*one,zero2,J);

	cout << "Starting MLEM..." << endl;

    /** ----------------------------------------------------
    * Maximum-Likelihood Expectation Maximization (MLEM)
    *   ----------------------------------------------------
    */

    for(k=0;k<iterations;k++){

	  x=x.cwiseProduct((Z*(y.cwiseQuotient(Update(R*x,zero1,I)))).cwiseQuotient(sum));

	  for(int i = threshold; i < J; i++) { t(i) = pow(x(i) - (x.sum()/(J-threshold)),2); }
	  dx =  dx + t;

	  r = (y - R*x);
	  residual(k) = sqrt(r.transpose()*r);

	  if (k%10==0) {cout << "Iteration(s): " << k << "\r" << flush;}

    if (iterations > 0 && y.sum() > 0)
      {
        diff = (R*x - diff);
        max_diff = diff.maxCoeff()/y.sum();
        //cout << k << " " << max_diff << endl;
        if (max_diff < criteria) {break;}
        diff = R*x;
      }
    }

	dx = dx/(k+1);

    /** ----------------------------------------------------
    * Output the Unfolded Spectrum and errors
    *   ----------------------------------------------------
    */


    out.open("Unfolded.out");
    out<<x;
    out.close();

	  out.open("error.out");
    out<<dx;
    out.close();

	/** ----------------------------------------------------
    * Output the Estimate Spectrum
    *   ----------------------------------------------------
    */

	out.open("estimate.out");
	out<<R*x;
	out.close();

	/** ----------------------------------------------------
    * Output the Initial Spectrum
    *   ----------------------------------------------------
    */

	out.open("spectrum.in");
	out<<y;
	out.close();

	/** ----------------------------------------------------
    * Output the residuals
    *   ----------------------------------------------------
    */

	out.open("residual.out");
	out<<residual;
	out.close();


    Stop = clock();
    cout << "Iterations run : " << k << endl;
    cout << "Elapsed time(s): " << (float)(Stop - Start)/CLOCKS_PER_SEC << endl;

	//cout << "Run again? (y/n)";
	//cin >> prompt;
  run = 0;
  //if(prompt == 'n') {run = 0;}

	}

  return 0;
}
