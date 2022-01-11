#include "UNCERT.h"
#include <cstdlib>   // for rand()
#include <cctype>    // for isalnum()
#include <algorithm> // for back_inserter
#include <string>
namespace UNCERT{


  //Change light output bin width to to 10Kev (ee)
  //constructor for uncertainty quant. generating fakedata
  //unfold_pnt is the pointer to an unfolding object
  //sampleCount sample count is  how many sets of bins do you expect to be created on gaussian smear and or how many reconstrcuted on unfoldin
  UNCERT::UNCERT(UNFOLD::UNFOLD *unfold_pnt,int sampleCount,vector<double> en,vector<double> w){

    UNCERT::unfold_pnt=unfold_pnt;

    //sets number of times you want to generate simulated data
    UNCERT::sampleCount=sampleCount;

    //setting fake data params
    UNCERT::en=en;
    UNCERT::w=w;

    //reconstructed bins are mean to house post gaussian smearing.generated lightout ouptuts but pre unfolding.
    //row count is samplecount and light bin size is the column count
    reconstructedBinMatrix.resize(sampleCount,unfold_pnt->nBins);
    reconstructedBinUncertainties.resize(unfold_pnt->nBins);

    //simulated bins are for neutron energies which are after the unfolding to reconstructed bins
    //the column count is the number of energyBins
    simulatedBinMatrix.resize(sampleCount,200);
    simulatedBinMatrix.setZero();

    simulatedBinMeans.resize(200);
    simulatedBinMeans.setZero();

    simulatedBinSums.resize(200);
    simulatedBinSums.setZero();

    simulatedBinUncertainties.resize(200);
    generateFakeData();
  }

  //generates fakeData and then sets the private variable light output bins to the light output response generated
  Eigen::VectorXf UNCERT::generateFakeData(){
    //UNCERT::unfold_pnt->generateFakeData(en,w);
    unfold_pnt->calcNormMatrix();
    //Eigen::VectorXf temp=UNCERT::scaleVectorOverOne(UNCERT::unfold_pnt->getInSpectrum());
    //unfold_pnt->setInSpectrum(temp);
    //UNCERT::unfold_pnt->plotProjection("tekjk");
    UNCERT::inSpectrum= unfold_pnt->getInSpectrum();
    UNCERT::inSpectrumUncertainties=UNCERT::unfold_pnt->getInSpectrumUncertainties();
    return inSpectrum;
  }

  /*Eigen::VectorXf UNCERT::setRealData(Eigen::VectorXf inSpectrum, Eigen::VectorXf lightOutputUncertainties){
  //not yet completeds`
}*/

//this method generates the smeared bins from the initial light outputs-> It puts each generated
//Lightoutput vctor into a row in reconstructed bin matrix
Eigen::MatrixXf UNCERT::binGeneration(){
	//print a number and its square root
	cout<<"sqrt(2)="<<sqrt(2)<<endl;
	 // one for fake data and one for expiremental can take in vect or hist.
  TRandom random_tracker= TRandom();
  for(int i=0;i<inSpectrum.size();i++){
    Eigen::VectorXf tempVect(sampleCount);
    double standardDev=0;
    for (int j=0;j<sampleCount;j++){
      //float temp_tracker=random_tracker.Gaus(inSpectrum(i)*100.0,sqrt(inSpectrum(i)*100.00));
      //float temp_tracker=random_tracker.Gaus(inSpectrum(i)*100.0,inSpectrumUncertainties(i)*100.0);
      float temp_tracker= gRandom->PoissonD(inSpectrum(i)*100.0);
      if(temp_tracker<0){
      //  temp_tracker=0;
      cout<<"under 0 "<<temp_tracker<<" mean * 100 "<<inSpectrum(i)*100.00<<" sqrt(insepctrum *100) "<<sqrt(inSpectrum(i)*100.00)<<endl;
      }
      tempVect(j)=temp_tracker/100.00;
    }
    /*if(tempVect.isZero()!=1){
    cout<<"bin"<<i<<endl;
    cout<<tempVect.transpose()<<endl;
    cout<<tempVect.maxCoeff()<<" max ";
    cout<<tempVect.minCoeff()<<" min ";
    cout<<tempVect.mean()<<" mean ";
    cout<<h1->GetMean()<<" meanCheck ";
    cout<<h1->GetStdDev()<<" std ";
    cout<<tempVect.isZero()<<" is Zero ";
    cout<<endl<<endl;
  }*/
  //this matrix each row will be unfolded
  reconstructedBinMatrix.col(i)=tempVect;
}
return reconstructedBinMatrix;
}


//this method loops through reconstructed bin matrix
Eigen::MatrixXf UNCERT::unfoldReconstructed(){
  for(int z=0;z<reconstructedBinMatrix.rows();z++){
    unfold_pnt->setInSpectrum(reconstructedBinMatrix.row(z));
    unfold_pnt->setInitialGuess(1.);
    char *arr= new char[8];
    gen_random(arr,7);

    for(int j=0; j<500; j++)
    {
      unfold_pnt->updateMLEM();
    }
    simulatedBinMatrix.row(z)=unfold_pnt->expirementalGetBestGuess(arr);
    delete []arr;
  }
  setSimulatedMeans();
  setSimulatedSums();
  setSimulatedUncertainties();
  return simulatedBinMatrix;
}

void UNCERT::printTwoVectors(Eigen::VectorXf v1, Eigen::VectorXf v2){
cout<<" size 1 "<<v1.size()<<" size 2 "<<v2.size()<<endl;
for(int i=0;i<v1.size();i++){
cout<<i<<" v1 "<<v1(i)<<" v2 "<< v2(i)<<endl;
}
}
void UNCERT::plotInSpectrumByTrial(int trialNumber,char *name){
  unfold_pnt->setInSpectrum(reconstructedBinMatrix.row(trialNumber));
  unfold_pnt->plotInputSpectrum(name);
}
 void UNCERT::gen_random(char *s, size_t len) {
     for (size_t i = 0; i < len; ++i) {
         int randomChar = rand()%(26+26+10);
         if (randomChar < 26)
             s[i] = 'a' + randomChar;
         else if (randomChar < 26+26)
             s[i] = 'A' + randomChar - 26;
         else
             s[i] = '0' + randomChar - 26 - 26;
     }
     s[len] = 0;
 }

Eigen::VectorXf UNCERT::standardDeviation(Eigen::MatrixXf matrix){
  Eigen::VectorXf stdVectors;
  stdVectors.resize(matrix.cols());
  for (int i=0;i<matrix.cols();i++) {
    float sd=0;
    float mean=matrix.col(i).mean();
    for (int j=0;j<matrix.rows();j++){
      sd+=TMath::Power((matrix(j,i)-mean),2);
    }
    sd=sqrt(sd/matrix.rows());
    stdVectors(i)=sd;
  }
  return stdVectors;
}


Eigen::VectorXf UNCERT::mean(Eigen::MatrixXf matrix){
  Eigen::VectorXf meanVector;
  meanVector.resize(matrix.cols());
  for (int i=0;i<matrix.cols();i++) {
    float mean=matrix.col(i).mean();
    meanVector(i)=mean;
  }
  return meanVector;
}


void UNCERT::setSimulatedSums(){
  Eigen::VectorXf simVect(simulatedBinMatrix.cols());
  for(int i=0;i<simulatedBinMatrix.cols();i++){
    simulatedBinSums(i)=simulatedBinMatrix.col(i).sum();
  }
}
void UNCERT::setSimulatedMeans(){
  Eigen::VectorXf simVect(simulatedBinMatrix.cols());
  for(int i=0;i<simulatedBinMatrix.cols();i++){
    simulatedBinMeans(i)=simulatedBinMatrix.col(i).mean();
  }
}

void UNCERT::setSimulatedUncertainties(){
  Eigen::VectorXf stdVect=standardDeviation(simulatedBinMatrix);
  simulatedBinUncertainties=stdVect;
}


void UNCERT::plotSimulatedMeans(char *name){
  new TCanvas;
  TH1F *testing= new TH1F(name,"Best Estimate;E_{n} (MeV);Counts",200,0,10);
  for (int i =0;i<simulatedBinMeans.size();i++){
  testing->SetBinContent(i,simulatedBinMeans(i));
  testing->SetBinError(i,simulatedBinUncertainties(i)*3);
  }
  printTwoVectors(simulatedBinMeans,simulatedBinUncertainties);
  testing->SetLineColor(kViolet);
  testing->SetMarkerStyle(kFullSquare);
  testing->SetMarkerSize(0.8);
  testing->SetMarkerColor(kRed);
  testing->Draw("E1 hist");
}

void UNCERT::plotSimulatedMeanByTrial(int trialNumber,char* name){
  new TCanvas;
  TH1F *testing= new TH1F(name,"Best Estimate;E_{n} (MeV);Counts",200,0,10);
  for (int i =0;i<simulatedBinMatrix.row(trialNumber).size();i++){
  testing->SetBinContent(i,simulatedBinMatrix.row(trialNumber)(i));
  }
  testing->SetLineColor(2);
  testing->Draw("hist same");
}

//this is for our own testing purposes to see that we get a guassian for each reconstructed bin
//this is for our own testing purposes to see that we get a guassian for each reconstructed bin
void UNCERT::plotBinNumber(int binNumber,Eigen::MatrixXf matrix, char *name,const char *title){
  new TCanvas;
  Eigen::VectorXf plottedBin= matrix.col(binNumber);
  TH1F * binX= new TH1F(title,name,unfold_pnt->nBins+1,plottedBin.minCoeff(),plottedBin.maxCoeff());
  double total=0;
  for (int i =0;i<matrix.col(binNumber).size();i++){
    binX->Fill(matrix(i,binNumber),1);
    //cout<<i<<" "<<binX->GetBinContent(i)<<" "<<binX->GetBinLowEdge(i)<<" "<<matrix(i,binNumber)<<endl;
    total+=binX->GetBinContent(i);
  }
  total=total/matrix.col(binNumber).size();
  binX->Draw();
}
/*Eigen::VectorXf UNCERT::scaleVectorOverOne(Eigen::VectorXf vect){
Eigen::VectorXf temp(vect.size());
double smallest=1;
temp.setOnes();
for (int i=0;i<vect.size();i++){
if(vect(i)>0){
temp(i)=vect(i);
}
else{temp(i)=1;}
}
smallest=temp.minCoeff();
if(smallest<=1){
return vect/smallest;
}
else{
return vect;
}
}*/

}
