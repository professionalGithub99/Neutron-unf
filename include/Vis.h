//Programmer: Jason Nattress
//Purpose:
#ifndef _Vis_H_
#define _Vis_H_
//ROOT classes
#include <TH1.h>
#include <TH2.h>
#include <TString.h>
//c++ classes
#include <vector>
#include <fstream>
#include <string>

namespace UNFOLD{

class Vis
{
  private:

  public:
    Vis();
    ~Vis();
    TH1F *histEDep;   // simulated deposited energy spectrum from Geant
    TH1F *histSmear;  // smeared simulated histogram from Geant
    TH1F *histExpCal; // calibrated exp LO spectrum (spectrum to unfold)
    TH1F *histToPlot[10]; // this should be dynamically allocated but I am
                          // leaving that for now...

  public:
    void loadSimHistoFile(TString iFN);
    void loadExpHistoFile(TString iFN);
    void histoVector(TString name, int nH, std::vector<float> v, int bR, int eR);
};
}

#endif
