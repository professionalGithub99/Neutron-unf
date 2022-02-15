#include "UNFOLD.h"
//ROOT classes
#include <TFile.h>
#include <TF1.h>
#include <TH1.h>
#include <TGraph.h>
#include <TString.h>
#include <TRandom.h>
#include <TRandom1.h>
#include <TCanvas.h>
#include <TMath.h>
//c++ classes
#include <vector>
#include <fstream>
#include <string>
#include <iostream>
// reference: https://tomroelandts.com/articles/the-sirt-algorithm
using namespace std;

namespace UNFOLD
{

  // this default constructor
  UNFOLD::UNFOLD(FILEIO *fio)
  {
    m_fio = fio;
    eBins=fio->eBins;
    nBins=fio->nBins;
    // These values are set manually in FILEIO. I could probably make it
    // automatic in the future.
    // check to see if your number makes sense
    /*if(m_fio->nBins != m_fio->inSpectrum->size())
    {
    cout << "WARNING: the number of light output bins does not equal your\n"
    "the number of L.O. bins in your input spectrum. Something is "
    "amiss.\n";
  }
  if(m_fio->eBins != nFiles)
  {
  cout << "WARNING: the number of en bins does not equal your\n"
  "the number of energy files. Something is "
  "amiss.\n";
}*/
//cout << "make sure you are calling the right constructor.\n";
}


void UNFOLD::printParameters()
{
  cout << "*** UNFOLD Parameters ***\n";
  cout << "\nm_fio->nBins = " << m_fio->nBins << endl;
  cout << "\nm_fio->eBins = " << m_fio->eBins << endl;
  cout << "\neIncrement = " << m_fio->energyIncrement << endl;
}
void UNFOLD::setResponseMatrix()
{
  //cout << m_fio->response->size() << endl;
  //printParameters();
  a.resize(m_fio->nBins,m_fio->eBins);
  for(int en=0; en<m_fio->eBins; en++)   // en = energy
  {
    for(int bN=0; bN<m_fio->nBins; bN++) // bN = bin number
    {
      int pos = en*m_fio->nBins + bN;
      //
      //cout << en << " " << m_fio->eBins << " " << bN << " " <<  pos << " "
      //   << m_fio->response->at(pos) << endl;
      a(bN,en) = m_fio->response->at(pos);
    }
  }
  
  //delete m_fio->response; // delete pointer
  // set answer index; maps "best" guess values to response matrix values
  ansIndex.resize(m_fio->eBins,1);
  for(int en=0; en<m_fio->eBins; en++)
  {
    //ansIndex(en,0) = 1 + (en+1)*m_fio->energyIncrement;
    ansIndex(en,0) = m_fio->startR + (en)*m_fio->energyIncrement;
    //cout << "ansIndex = " << ansIndex(en,0) << endl;
  }
  return;
}

// todo: add arguements for SIRT and MLEM
void UNFOLD::calcNormMatrix()
{
  // for SIRT
  Eigen::VectorXf r = a.rowwise().sum(); // diagonal matrix of row sums of a //nBinsSize
  Eigen::VectorXf c = a.colwise().sum(); // diagonal matrix of col sums of a //eBinSize
  cout << "r: " << r.rows() << "x" << r.cols() << endl;
  cout << "c: " << c.rows() << "x" << c.cols() << endl;
  
  for(int i=0; i<r.size(); i++)
  {
    if(r(i) == 0) r(i) = 0;
    else{r(i) = 1/ r(i);}
  }

  for(int i=0; i<c.size(); i++)
  {
    if(c(i) == 0) c(i) = 0;
    else{c(i) = 1/ c(i);}
  }
  catr = c.asDiagonal() * a.transpose() * r.asDiagonal();

  // for MLEM
  a_norm.resize(a.cols());

  for(int j=0; j<a.cols(); j++)
  {
    double sum = 0;
    for(int i=0; i<a.rows(); i++)
    {
      sum += a(i,j);
    }
    //print out the sum
    // you will divide by this vector, so make sure there is not a zero.
    if(sum == 0) sum = 1E-6;
    a_norm(j) = (sum);
  }
  return;
}
// fills matrix b
void UNFOLD::setData()
{
  b.resize(m_fio->nBins,1);
  for(int bN=0; bN<m_fio->nBins; bN++) // bN = bin number
  {
    b(bN,0) = m_fio->inSpectrum->at(bN);
    //if(bN*m_fio->energyIncrement < m_fio->threshold) b(bN,0) = 0;
  }
  delete m_fio->inSpectrum;  // delete pointer

  return;
}
// uses response to set matrix b
void UNFOLD::generateFakeData(vector<double> en, vector<double> weight)
{
  cout << "creating fake data...\n";
  Eigen::MatrixXf testData = Eigen::MatrixXf::Zero(m_fio->eBins,1);
  // find the corresponding positions for the energies added
  vector<int> en_pos;
  for(int i=0; i<en.size(); i++)
  {en_pos.push_back(en[i]/m_fio->energyIncrement);}
  for(int i=0; i<en.size(); i++)
  {
    testData(en_pos[i],0) = weight[i];}
  //cout << en_pos[0] << endl;
  //testData(30,0) = 10;
  //cout << 30 * m_fio->energyIncrement << endl;
  b.resize(m_fio->nBins,1);
  cout  << a.rows() << "x" << a.cols() << endl;
  cout  << testData.rows() << "x" << testData.cols() << endl;
  ground_truth.resize(m_fio->eBins);
  ground_truth = testData.col(0);
  b = a * testData;
  for(int i=0; i<b.size(); i++)
  {
    auto val = gRandom->PoissonD(b(i)*100);
    /*cout<<b(i)<<endl;
    cout<<val<<endl;
    cout<< val/100<< " "<<endl<<endl;*/
    //cout << b(i) << " " << val/100 << endl;
    b(i,0) = val/100;
    //cout<<i<<" "<<val;
  }
  return;
}

double UNFOLD::getRss()
{
	Eigen::VectorXf residual = b - getFwdProjection();
	double rss = residual.transpose() * residual;
	return rss;
}
void UNFOLD::setInitialGuess(float guess)
{
  x_1.resize(m_fio->eBins,1);
  x.resize(m_fio->eBins,1);
  x_uncert.resize(m_fio->eBins,1);
  x.setOnes();
  x_1.setOnes();
  //cout << x << endl;
  //print answer index
  for(int i=0; i<m_fio->eBins; i++)
  {
    if(ansIndex(i,0) < m_fio->threshold)
    {
//if a bin's energy is less than  the threshold, set the initial bin to zero
//ohterwise, leave the bin as 1
      x_1(i,0) = 0;
      x(i,0) = 0;
    }
  }
  z.resize(m_fio->eBins,1);
  z=x;
  x_uncert=x;
  return;
}

void UNFOLD::calcRMSE()
{
  double rms = getRMSE();
  rmse2Vals.push_back(rms); // this is now the RMSE
  rss2Vals.push_back(getStopIndice());
  if(rmse2Vals.size() > 1)
  {
	  rmseDeltaVals.push_back(rmse2Vals[rmse2Vals.size()-1] - rmse2Vals[rmse2Vals.size()-2]);
  }
}

double UNFOLD::getRMSE(){
  Eigen::VectorXf val= x-ground_truth;
  Eigen::VectorXf val_sq = val.cwiseProduct(val);
  double rms = sqrt(val_sq.sum()/m_fio->eBins);
  return rms;
}

double UNFOLD::getMeanInSpectrumBinCount(){
	double mean = 0;
	//sum all elements of b
	for(int i=0; i<b.size(); i++){
		mean += b(i,0);
	}
	mean = mean/b.size();
}
std::vector<double> UNFOLD::getRSS()
{
  return rss2Vals;
}
std::vector<double> UNFOLD::getRMSEDelta()
{
  return rmseDeltaVals;
}
Eigen::VectorXf UNFOLD::getFwdProjection()
{
	  return a * x;
}
double UNFOLD::getMD(Eigen::VectorXf fwdProj)
{	//take the absolute value of the difference between the forward projection and the b vector
	//sum all elements of the difference vector
	//divide by the number of elements in the difference vector
	//return the result
	Eigen::VectorXf val= fwdProj-b;
	Eigen::VectorXf val_sq = val.cwiseProduct(val);
	double meanDeviation= sqrt(val_sq.sum())/m_fio->nBins;
	return meanDeviation;
}
void UNFOLD::updateSIRT()
{
  //Eigen::MatrixXf test = catr * ( b - a*x);
  //cout << catr << endl;
  x_1 = x + catr * ( b - a*x);
  //x_1 = catr * ( b - a*x);
  for(int i=0; i<m_fio->eBins; i++)
  {
    if(x_1(i,0) < 0) x_1(i,0) = 0;
    if(ansIndex(i,0) < m_fio->threshold) x_1(i,0) = 0;
  }
  //cout << x_1 << endl;
  x = x_1;
}

//change return type to boolean calculate indicatior function and rms error after line 257, return true at intersection when = each other.
Eigen::ArrayXf UNFOLD::updateMLEM()
{
  Eigen::ArrayXf a_x = x.col(0);
  Eigen::ArrayXf a_dem(m_fio->nBins);
  for(int i=0; i<m_fio->nBins;i++)
  {
    Eigen::ArrayXf a_temp = a.row(i);
    a_temp = a_temp*a_x;
    if(a_temp.sum() == 0) a_dem(i) = 1E-6;
    else{
	    a_dem(i) = a_temp.sum();
    }
  }
  // for every enery bin sum the light bins
  Eigen::ArrayXf a_sum(m_fio->eBins);
  Eigen::ArrayXf a_b = b.col(0);
  for(int i=0; i<m_fio->eBins; i++)
  {
    Eigen::ArrayXf a_temp = a.col(i);
    a_temp = a_temp* a_b / a_dem;
    a_sum(i) = a_temp.sum();
  }
  // multiple element-by-element
  Eigen::ArrayXf a_x1 = a_x / a_norm * a_sum;
  x_1.col(0) = a_x1;
  // set energies below m_fio->threshold to zero
  //for(int i=0; i<m_fio->eBins; i++)
  //if(ansIndex(i,0) < m_fio->threshold) x_1(i,0) = 0;
  // set previous guess to current
  x = x_1;
  return (x_1);
}

double UNFOLD::getStopIndice()
{
	double rss=getRss();
	double forwardProjectionSum=getFwdProjection().sum();
	double stopIndice=rss/getFwdProjection().sum();
;
	return  stopIndice;

}

Eigen::VectorXf UNFOLD::getGroundTruth()
{
  return ground_truth;
}


void UNFOLD::backProject()
{
  ax = a * x_1;
}

void UNFOLD::setInSpectrum(Eigen::VectorXf vect){
  b.col(0)=vect;
}
void UNFOLD::setInputEnergy(Eigen::VectorXf vect){
  x.col(0)=vect;
}
vector<float> UNFOLD::getProjection()
{
  vector<float> v;
  for(int i=0; i<m_fio->nBins; i++)
  {
    v.push_back(ax(i,0));
  }
  return v;
}
Eigen::VectorXf UNFOLD::getInSpectrum(){
  return b;
}
Eigen::VectorXf UNFOLD::getInSpectrumUncertainties(){
  Eigen::MatrixXf loUncertainties (m_fio->nBins,1);
  for(int i=0;i<m_fio->nBins;i++){
    loUncertainties(i,0)=TMath::Sqrt(b(i,0));
  }
  return loUncertainties;
}
Eigen::VectorXf UNFOLD::getBestGuess(){
  return x.col(0);
}
Eigen::MatrixXf UNFOLD::getResponseMatrix(){
  return a;}

 Eigen::VectorXf UNFOLD::expirementalGetBestGuess(char*name)
{
  TH1F *hAnswer = new TH1F(name,"Best Estimate;E_{n} (MeV);Counts",200,0,10);
  // ***fix your vis ***
  for(int bN=0; bN<m_fio->eBins; bN++)
  {
    hAnswer->Fill(ansIndex(bN,0), x(bN,0));
    /*cout <<"binNumber"<<hAnswer->GetBin(bN) <<"Energy " <<ansIndex(bN,0) << " counts? " << x(bN,0) <<" counts "<<hAnswer->GetBinContent(bN)
     <<  " center " << hAnswer->GetBinCenter(bN)<<" low edge "<<hAnswer->GetBinLowEdge(bN)<<endl<< endl;*/
  }
  Eigen::VectorXf testVector(200);
  for(int i=0;i<200;i++){
    testVector(i)=hAnswer->GetBinContent(i);
  }
  return testVector;
}
vector<float> UNFOLD::getProjectionUncertainties(){
  vector<float> float_vect;
  for(int bN=0; bN<m_fio->nBins; bN++) // bN = bin number
  {
    float_vect.push_back(hFinal->GetBinError(bN));
  }
  return float_vect;
}


void UNFOLD::plotResponseForAnEnergy(double en)
{
  new TCanvas;
  int respPos = en / (ansIndex(1,0)-ansIndex(0,0)); // this needs to be changed
  auto h1 = new TH1F("h1",";;",m_fio->nBins,0,m_fio->endR);
  for(int bN=0; bN<m_fio->nBins; bN++) // bN = bin number
  {
    h1->SetBinContent(bN, a(bN,respPos));
    //cout << bN << " " << a(bN,respPos) << endl;
  }
  cout << h1->Integral() << " Integral"<<endl;
  h1->Draw();
}

void UNFOLD::plotInputSpectrum(char *name)
{
  new TCanvas;
  TH1F *hInput = new TH1F(name,";;",m_fio->nBins+1,0,m_fio->endR);
  for(int bN=0; bN<m_fio->nBins; bN++) // bN = bin number
  {
    hInput->SetBinContent(bN, b(bN,0));
  }
  cout << b.rows() << "x" << b.cols() << endl;
  hInput->Draw();
}


TGraph* UNFOLD::plotAnswer(Eigen::VectorXf vectStd,char *name)
{
  cout << "plotting uncertainty\n";
  new TCanvas;
  double binW = ansIndex(1,0) - ansIndex(0,0);
  cout << "m_fio->endR: " << m_fio->endR << endl;
  //double hStart  = m_fio->energyIncrement/2.;
  double hStart=0;
  //double hEnd    = m_fio->endR + m_fio->energyIncrement/2.;
  double hEnd=10;
  int nBins = (hEnd - hStart) / binW;
  cout << hStart << " " << hEnd << " " << m_fio->nBins << endl<<endl;
  // todo: need to check if this is right for the bins and range
cout<<ansIndex(1,0)-ansIndex(0,0)<<"kjsldjfs"<<endl;
  TH1F *hAnswer = new TH1F(name,"Best Estimate;E_{n} (MeV);Counts",200,0,10);
  //TH1F *hAnswer = new TH1F(name,"Best Estimate;E_{n} (MeV);Counts",m_fio->nBins+1,hStart,hEnd);
  // ***fix your vis ***

  for(int bN=0; bN<m_fio->eBins; bN++)
  {
    hAnswer->Fill(ansIndex(bN,0), x(bN,0));
    /*cout <<"binNumber"<<hAnswer->GetBin(bN) <<"Energy " <<ansIndex(bN,0) << " counts? " << x(bN,0) <<" counts "<<hAnswer->GetBinContent(bN)
     <<  " center " << hAnswer->GetBinCenter(bN)<<" low edge "<<hAnswer->GetBinLowEdge(bN)<<endl<< endl;*/
  }
  Eigen::VectorXf temp(m_fio->nBins+1);
  for(int i=0;i<nBins+1;i++){
     temp(i)=hAnswer->GetBinLowEdge(i);
  }
 Eigen::VectorXf scaledVect=scaleVectorWithKey(temp,ansIndex,vectStd);
  for(int bN=0; bN<m_fio->nBins+1; bN++)
  {
    hAnswer->SetBinError(bN,scaledVect(bN));
    /*cout <<"binNumber"<<hAnswer->GetBin(bN) <<"Energy " <<ansIndex(bN,0) << " counts? " << x(bN,0) <<" counts "<<hAnswer->GetBinContent(bN)<<
    " scaled test "<<scaledVect(bN)<<" center " << hAnswer->GetBinCenter(bN)<<" low edge "<<hAnswer->GetBinLowEdge(bN)<<endl<< endl;*/
  }

  //cout << x << endl;
  /*cout << "counts: answer -> " << hAnswer->Integral() << endl;
  const Int_t n = 300;//ansIndex.rows();
  Double_t gx[n], gy[n];*/

  for(int bN=0; bN<m_fio->eBins; bN++)
  {
    //cout << bN << endl;
    //gx[bN] = ansIndex(bN,0);
    //gy[bN] = x(bN,0);
    //cout << ansIndex(bN,0) << " " << x(bN,0) << endl;
    //   <<  " " << hAnswer->GetBinCenter(bN) << endl;
    //hAnswer->Fill(ansIndex(bN,0), x(bN,0));
  }
  TGraph *gr  = new TGraph;//(n,gx,gy);
  //gr->Draw("AC");
  auto hr = gr->GetHistogram();
  hAnswer->SetLineColor(kViolet);
  hAnswer->SetMarkerStyle(kFullSquare);
  hAnswer->SetMarkerSize(1);
  hAnswer->SetMarkerColor(kRed);
  hAnswer->Draw("E1 hist");
  //auto tf = new TFile("ans.root","recreate");
  //gr->Write();
  //tf->Close();
  return gr;
}
TGraph* UNFOLD::plotAnswer(char*name)
{
  cout << "plotting answer____\n";
  new TCanvas;
  double binW = ansIndex(1,0) - ansIndex(0,0);
  cout << "m_fio->endR: " << m_fio->endR << endl;
  double hStart  = m_fio->energyIncrement/2.;
  double hEnd    = m_fio->endR + m_fio->energyIncrement/2.;
  int nBins = (hEnd - hStart) / binW;
  cout << hStart << " " << hEnd << " " << m_fio->nBins << endl<<endl;
  // todo: need to check if this is right for the bins and range
  //hAnswer = new TH1F("hAnswer","Best Estimate;E_{n} (MeV);Counts",300,0.025,15.025);
  // TH1F* hAnswer = new TH1F(name,"Best Estimate;E_{n} (MeV);Counts",m_fio->nBins+1,hStart,hEnd);
  TH1F *hAnswer = new TH1F(name,"Best Estimate;E_{n} (MeV);Counts",200,0,10);
  // ***fix your vis ***
  for(int bN=0; bN<m_fio->eBins; bN++)
  {
    hAnswer->Fill(ansIndex(bN,0), x(bN,0));
    /*cout <<"binNumber"<<hAnswer->GetBin(bN) <<"Energy " <<ansIndex(bN,0) << " counts? " << x(bN,0) <<" counts "<<hAnswer->GetBinContent(bN)
     <<  " center " << hAnswer->GetBinCenter(bN)<<" low edge "<<hAnswer->GetBinLowEdge(bN)<<endl<< endl;*/
  }
  //cout << x << endl;
  /*cout << "counts: answer -> " << hAnswer->Integral() << endl;
  const Int_t n = 300;//ansIndex.rows();
  Double_t gx[n], gy[n];*/

  for(int bN=0; bN<m_fio->eBins; bN++)
  {
    //cout << bN << endl;
    //gx[bN] = ansIndex(bN,0);
    //gy[bN] = x(bN,0);
    //cout << ansIndex(bN,0) << " " << x(bN,0) << endl;
    //   <<  " " << hAnswer->GetBinCenter(bN) << endl;
    //hAnswer->Fill(ansIndex(bN,0), x(bN,0));
  }
  TGraph *gr  = new TGraph;//(n,gx,gy);
  //gr->Draw("AC");
  auto hr = gr->GetHistogram();
  hAnswer->SetLineColor(2);
  //hAnswer->Draw("hist same");
  hAnswer->Draw("hist");
  //auto tf = new TFile("ans.root","recreate");
  //gr->Write();
  //tf->Close();
  return gr;
}

Eigen::VectorXf UNFOLD::scaleVectorWithKey(Eigen::VectorXf scaleTo, Eigen::VectorXf key,Eigen::VectorXf scale){
  Eigen::VectorXf scaledVector;
  scaledVector.resize(scaleTo.size());
  int i=0;
  int j=0;
  while(i<key.size() && j<scaleTo.size()-1){
  if(key(i)>=scaleTo(j)&&key(i)<scaleTo(j+1)){
    scaledVector(j)=scale(i);
    i++;
    j++;
  }
  else{scaledVector(j)=0;j++;}
  }
  return(scaledVector);
}

void UNFOLD::plotProjection(char *name)
{
  new TCanvas;
  backProject();
  TH1F* hFinal = new TH1F("hProj","Projection;Light Output (MeVee);Counts",m_fio->nBins,0,m_fio->endR);
  for(int bN=0; bN<m_fio->nBins; bN++)
  hFinal->SetBinContent(bN, ax(bN,0));
  hFinal->SetLineColor(2);
  hFinal->Draw();
  cout << "reconstructed is red\n";
  hInput = new TH1F(name,"Input;Light Output (MeVee);Counts",m_fio->nBins,0,m_fio->endR);
  for(int bN=0; bN<m_fio->nBins; bN++) // bN = bin number
  {
    hInput->SetBinContent(bN, b(bN,0));
  }
  cout << "Light output:\n";
  cout << "counts: input -> " << hInput->Integral() << " proj -> " << hFinal->Integral() << endl;
  hInput->Draw("same");

  hSig = new TH1F("hSig",";Light Output (MeVee);#Delta/#sigma",m_fio->nBins,0,m_fio->endR);
  for(int i=0; i<hFinal->GetNbinsX(); i++)
  {
    auto diff = hInput->GetBinContent(i) - hFinal->GetBinContent(i);
    //cout << diff << endl;
    if( hInput->GetBinContent(i)!=0) diff = diff / TMath::Sqrt( hInput->GetBinContent(i) );
    else{diff = 0;}
    hSig->SetBinContent(i,diff);
  }
// new TCanvas;
  //hSig->Draw();
}
void UNFOLD::plotResponseMatrix()
{
  cout << "Drawing response matrix...\n";
  auto hRes = new TH2F("hRes",";E_{n};Light Output (MeVee)",m_fio->eBins+1,0,m_fio->endR,m_fio->nBins,0,m_fio->endR);
  for(int en=0; en<m_fio->eBins; en++)   // en = energy
  {
    for(int bN=0; bN<m_fio->nBins; bN++) // bN = bin number
    {
      double pos;
      pos = bN * (ansIndex(1,0)-ansIndex(0,0));
      hRes->Fill(ansIndex(en,0),pos,a(bN,en));
    }
  }
  new TCanvas;
  hRes->Draw("surf1");
}

void UNFOLD::plotRSS(){
  new TCanvas;
  auto hRSS = new TH1F("hRSS",";;",rss2Vals.size(),0,rss2Vals.size());
  for(int bN=0; bN<rss2Vals.size(); bN++) // bN = bin number
  {
    hRSS->SetBinContent(bN+1, rss2Vals.at(bN));
  }
  //hRMSE->SetDirectory(0);
  hRSS->Draw();
}
void UNFOLD::plotRMSE()
{
  new TCanvas;
  auto hRMSE = new TH1F("hRMSE",";;",rmse2Vals.size(),0,rmse2Vals.size());
  for(int bN=0; bN<rmse2Vals.size(); bN++) // bN = bin number
  {
    hRMSE->SetBinContent(bN+1, rmse2Vals.at(bN));
  }
  //hRMSE->SetDirectory(0);
  hRMSE->Draw();
}

void UNFOLD::plotTheoreticalMD(char *name)
{
  auto cv= new TCanvas;
  //create a histogram that ranges from 0 to 10^6 on the x-axis and 0 to 10^6 on the y-axis
  //fill the histogram with the theoretical values
  
  TF1 *fb2 = new TF1("fa3","(pow(x,x+1)*2*exp(-x))/TMath::Factorial(x)",0,30);
  //set fb2 to log scale
fb2->Draw();
  cv->SetLogx();
  cv->SetLogy();
}
/////////////////////////
} // end namespace UNFOLD
