//
#ifndef _HVis_H_
#define _HVis_H_
//ROOT classes
//ROOT classes
#include <TH1.h>
#include <TH2.h>
#include <TString.h>
// Eigen
#include <Eigen/Core>
#include <Eigen/Dense>
//c++ classes
#include <vector>
#include <fstream>
#include <string>
//my classes
#include <FILEIO.h>


using namespace std;

namespace UNFOLD{

class HVis
{
  private:

  public:
    HVis();
    //~HVis();
    TH1F *histEDep;   // simulated deposited energy spectrum from Geant
    TH1F *histSmear;  // smeared simulated histogram from Geant
    TH1F *histExpCal; // calibrated exp LO spectrum (spectrum to unfold)
    TH1F *histToPlot[10]; // this should be dynamically allocated but I am
                          // leaving that for now...

    void loadSimHistoFile(TString iFN);
    void loadExpHistoFile(TString iFN);
    void histoVector(TString name, int nH, std::vector<float> v, int bR, int eR);

};
}

#endif
