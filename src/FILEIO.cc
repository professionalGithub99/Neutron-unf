#include "FILEIO.h"
//ROOT classes
#include <TFile.h>
#include <TH1.h>
#include <TH2.h>
#include <TString.h>
//c++ classes
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>

using namespace std;

namespace UNFOLD
{

FILEIO::FILEIO()
{
  rebinVal = 1;   // I typically set the number of bins in my sim to 2E4 with an
                  // endpoint of 20 MeV. A rebin value of 40 will set it to 500
                  // which is what I set my experimental spectrum to. This needs
                  // to be changed or none of this will work if these specific
                  // criteria are not met.
  threshold = 0;
  //energyIncrement = 0.1; // in MeV
  inSpectrum = new vector<float>;
  startL = 0;
  endL   = 20;
}

/*FILEIO::FILEIO(int i_rebinVal, int i_enIncrement)
{
  rebinVal = i_rebinVal;
  energyIncrement = i_enIncrement;
}*/

void FILEIO::setThreshold(float t)
{
  threshold = t;
}

void FILEIO::setLORange(double iR, double eR)
{
  startL = iR;
  endL   = eR;
}

void FILEIO::setNbins(int num)
{
  nBins = num;
  cout << "#bins: " << nBins << endl;

  return;
}

void FILEIO::setEbins(int num)
{
  eBins = num;
  cout << "#Ebins: " << eBins << endl;
  return;
}

// this should be in FILEIO
void FILEIO::setRange(double start, double end)
{
  startR = start;
  endR = end;
}
// Sets response from txt file and creates a file containing histograms of
// the individual energy responses
void FILEIO::setResponse(std::string iFN)
{
  cout << "opening: " << iFN << endl;
  ifstream in;
  in.open(iFN);
  if (in.is_open()) {
    cout << "matrix file path is good.\n";
  }
  else {
    // show message:
    std::cout << "Error opening file\n";
  }

  int nEntries;
  in >> nEntries;
  //int i_nFiles;
  in >> nFiles;
  eBins = nFiles;
  //nFiles = i_nFiles;
  int mcnp; //used if reponse is simulated
  in >> mcnp;
  double loBinWidth;
  in >> loBinWidth;
  cout << "Using the following parameters for response:\n"
       << "\tentries:      " << nEntries   << "\n"
       << "\tnFiles:       " << nFiles   << "\n"
       << "\tLO bin width: " << loBinWidth << endl;

  response = new vector<float>;
  //energyIncrement = 0.05;
  TFile *f1= new TFile( "response.root","recreate" );;
  TH1F *hist;
  // loop over file
  for(int i=0;  i<nFiles; i++)
  {
    stringstream ss;
    double en = i * energyIncrement;
    ss  << "_en_" << en; // hard coded file name
    TString fN = ss.str();
    //cout << fN << endl;
    auto hist = new TH1F(fN,"",nEntries,0,nEntries*loBinWidth);
    if(i == 0)
    {
      cout << "Histo parameters: \n"
           << "\tRange: 0 -- " << nEntries*loBinWidth << "\n"
           << "\tBins:  " << hist->GetNbinsX() << endl;
      numOfSimBins = hist->GetNbinsX();
    }

    for(int i_bN=0; i_bN<nEntries; i_bN++)
    {
      double val;
      in >> val;
      hist->SetBinContent(i_bN,val);
    }

    for(int i_bN=nEntries; i_bN<hist->GetNbinsX(); i_bN++)
    {
      hist->SetBinContent(i_bN,0);
    }
    // normalize histo to 1
    float sV = hist->Integral();
    if(sV > 0) hist->Scale(1./sV);
    hist->Write();
    //f1->Close();
    //delete f1;
    // fill the response from input files
    for(int bN=0; bN<hist->GetNbinsX(); bN++)
      response->push_back(hist->GetBinContent(bN));
    //
    delete hist;
  }
  // check you read the whole file and your indices are not jacked
  double check; // you need one more "<<" to flip the boolean
  in >> check;
  if(in.eof())                      // check for EOF
    std::cout << "[EoF reached]\n";
  else
    std::cout << "[error reading]\n";
  return;
}

void FILEIO::setResponse(TString pathToSimFiles, int i_nFiles,
                         TString fExt )
{
  cout << i_nFiles << " files for the response." << endl;
  nFiles = i_nFiles; // set this to propagate to UNFOLD
  cout << "Loading response\n";
  cout << "response path: " << pathToSimFiles << endl;
  int numOfFiles = i_nFiles;
  double startingPoint = startR;// This is your first response file
  response = new vector<float>;
  eBins = i_nFiles;

  // loop over response files
  for(int i=0;  i<numOfFiles; i++)
  {
    stringstream ss;
    double en = startingPoint + (i) * energyIncrement;
    //ss << pathToSimFiles << fExt << en << ".root";
    //TString fN = ss.str();
    TString fN;
    fN.Form("%s%s%.3fMeV.root", pathToSimFiles.Data(), fExt.Data(), en);
    if(i==0 || i==(numOfFiles-1)) cout << fN << endl;

    //cout << fN << endl;
    TFile *f1 = new TFile( fN,"read" );
    // check if file exists
    if(!f1->IsOpen())
    {
      cout << "ERROR: Your file path is incorrect. Check FILEIO.\n"
           << "Exiting program not elegantly...\n";
      return;
    }
    // need to change this hard-coded histo name
    //TH1F  *hist = (TH1F*)f1->Get("Det0_smear");
    TH1F  *hist = (TH1F*)f1->Get("hLightOutput_det1");

    hist->Rebin(rebinVal);
    // check total number of bins
    // todo: need to add  check

    if(i == 0) numOfSimBins = hist->GetNbinsX();

    // normalize histo to 1
    //float sV = hist->Integral();
    //if(sV > 0) hist->Scale(1./sV);
    // set bins below threshold to zero in the response
    for(int bN=0; bN<hist->GetNbinsX(); bN++)
    {
      // if you are below your LO threshold, set value to 0
      if(hist->GetBinCenter(bN) <= threshold)
        hist->SetBinContent(bN,0);
      //else{ break; }
    }
    // You must normalize an individual response to one. I left out a term in
    // the MLEM method that makes this assumption. If you would like to change
    // this, than the MLEM method must be altered as well.
    float sV = hist->Integral();
    if(sV > 0) hist->Scale(1./sV);

    // fill the response from input files
    for(int bN=0; bN<hist->GetNbinsX(); bN++)
    {
      auto bV = hist->GetBinContent(bN);
      response->push_back(hist->GetBinContent(bN));
    }
  }
  cout << "response is set\n";
  return;
}

void FILEIO::readInExpSpectrum(TString fN, TString hName)
{
  inSpectrum->clear();

  //inSpectrum = new vector<float>;
  cout << "exp. spectrum: " << fN << ": " << hName << endl;
  TFile *f1 = new TFile(fN,"read" );
  if(!f1->IsOpen())
  {
    cout << "ERROR: Your experimental file path is incorrect. Check FILEIO.\n"
         << "Exiting program not elegantly...\n";
    return;
  }
  TH1F  *hist = (TH1F*)f1->Get(hName);
  hist->Rebin(rebinVal); // ****fix maybe later****
  //hist->Scale(0.0025);
  if(hist->GetNbinsX() != numOfSimBins)
  {
    cout << "Exp bins: " << hist->GetNbinsX() << " sim bins: "
         << numOfSimBins << endl;
    cout << "ERROR: The number of bins in the exp and response are not equal\n"
         << "after rebinning. Check response and experimental input spectrum.\n"
         << "This program expects an energy range of 0-20 MeVee with 2E4 bins."
         << "\n";
    return;
  }
  // normalize histo to 1
  float sV = hist->Integral((int)threshold/energyIncrement,hist->GetNbinsX());
  //cout << sV << endl;
  //if(sV > 0) hist->Scale(1./sV);
  for(int bN=0; bN<hist->GetNbinsX(); bN++)
  {
    //inSpectrum->push_back(hist->GetBinContent(bN+1));
    if(hist->GetBinCenter(bN) > threshold)
      inSpectrum->push_back(hist->GetBinContent(bN));
    else{
      //cout << "setting to zero\n" ;
      inSpectrum->push_back(0);
    }
  }
}

} // end namespace UNFOLD
