// Programmer: Jason Nattress
// Purpose: setup input file and response matrix as well as the limits for the
// unfolding.
#ifndef _DUP_H_
#define _DUP_H_
//ROOT classes
#include <TH1.h>
#include <TH2.h>
#include <TString.h>
//c++ classes
#include <vector>
#include <fstream>
#include <string>
#include <iostream>

//using namespace std;

namespace UNFOLD{

class DUP
{
  private:

  public:
    DUP();
    //FILEIO(int i_rebinVal, int i_enIncrement);
    //~FILEIO();

  public:
    int rebinVal;
    int numOfSimBins; // I think these are the same things
    int nBins; // numner of L.O. bins for a single energy
    int eBins; // number of energies in response matrix
    double startR; // first neutron energy in response
    double endR;   // last neutron energy in response
    double startL;
    double endL;

    std::vector<float> *inSpectrum; // spectrum that you will unfold
    std::vector<float> *response;   // your response
    float          energyIncrement; // energy increment of the response
    double         threshold; // L.O. threshold
    int            nFiles; // this is from input txt response file or as an
                           // input in the constructor. This file should
                           // equal the eBins

};
}

#endif
