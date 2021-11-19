// Programmer: Jason Nattress
// Purpose: setup input file and response matrix as well as the limits for the 
// unfolding. 
#ifndef _FILEIO_H_
#define _FILEIO_H_
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

class FILEIO
{
  private:

  public:
    FILEIO();
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

  public:
    void setNbins(int num); // This is equal to the number of bins in a single 
                            // response meaning a single energy
    void setEbins(int num); // This is the number of energies you simulated or
                            // measured.

    void setThreshold(float t); // units in MeVee;
                                // sets bin # for threshold and range for
                                // unfolding
    void setRange(double start, double end);
    // energy increment of response matrix
    void setEnergyIncrement(float en) {energyIncrement = en;}
    // give path to file, number of files and the file extentsion. 
    // You need to go and look at the method itself and maybe change it to 
    // whatever you want. Feel free to make this more slick if you want. 
    void setResponse(TString pathToSimFiles, int i_nFiles, TString fExt);
    // Creates response files from a txt file. This method orginally written to
    // take in the measured response from an Odessa detector
    void setResponse(std::string iFN); 
    // give path with name and histogram name
    void readInExpSpectrum(TString fN, TString hName);

    void setRebinVal(int val) {rebinVal = val;}
    void setLORange(double iR, double eR);
};
}

#endif
