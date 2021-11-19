#include "Vis.h"
//ROOT classes
#include <TFile.h>
#include <TH1.h>
#include <TH2.h>
#include <TString.h>
#include <TRandom1.h>
#include <TMath.h>
//c++ classes
#include <vector>
#include <fstream>
#include <string>
#include <iostream>

using namespace std;

namespace UNFOLD{

Vis::Vis()
{
  //
}

void Vis::loadSimHistoFile(TString iFN)
{
  TFile *f1 = new TFile( iFN,"read" );
  histEDep =(TH1F*)f1->Get("Det0_eDep");
  histEDep->Rebin(10);
}

void Vis::loadExpHistoFile(TString iFN)
{
  TFile *f1 = new TFile( iFN,"read" );
  histExpCal =(TH1F*)f1->Get("h1_calPI");
  histExpCal->Rebin(10);

  const int numOfBins = histEDep->GetNbinsX();
  const int xmax = histEDep->GetXaxis()->GetXmax();

  histSmear = new TH1F("histSmear",";Light Output;Counts" ,numOfBins, 0., xmax);
}

void Vis::histoVector(TString name, int nH, vector<float> v,
                                  int bR, int eR)
{
  int nBins = v.size();
  histToPlot[nH] = new TH1F(name,";;" ,nBins, bR, eR);

  for(int i=0; i<nBins; i++)
  {
    histToPlot[nH]->SetBinContent(i+1,v.at(i));
  }

}

} // end namespace UNFOLD
