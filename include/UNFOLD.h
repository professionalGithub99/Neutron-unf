//
#ifndef _UNFOLD_H_
#define _UNFOLD_H_
//ROOT classes
// Eigen
#include <Eigen/Core>
#include <Eigen/Dense>
//c++ classes
#include <vector>
#include <fstream>
#include <string>
#include <TGraph.h>
//my classes
#include <FILEIO.h>

namespace UNFOLD{

class UNFOLD
{
  private:
    Eigen::MatrixXf a, b, x, x_1, catr, ax, ansIndex;
    Eigen::ArrayXf a_norm;
    FILEIO *m_fio;
    // a - response matrix
    // b - LO spectrum to unfold
    // x - guess
    // x_1 - updated guess
    // catr - normalization matrix
    // ax - forward projection
    // ansInex - corresponding energy for a position in x or x_1
    std::vector<double> rss2Vals; // rss values as a function of iteration
  public:
    int nBins;
    int eBins;
    UNFOLD(FILEIO *fio);
    void printParameters();
    //~UNFOLD();
    void setResponseMatrix();
    void calcNormMatrix();
    void setData(); // fills matrix b
    void generateFakeData(std::vector<double> en, std::vector<double> weight);
    void setInitialGuess(float guess);
    void fwdProject(); // also calcs rss value for a projection`
    void updateMLEM(); // update equation for MLEM
    void backProject();
    void updateSIRT(); // update equation for SIRT
    // *******
    // SETTERS
    // *******
    void setLightOutput(Eigen::VectorXf vect);
    void setInputEnergy(Eigen::VectorXf vect);
Eigen::VectorXf scaleVectorWithKey(Eigen::VectorXf scaleTo, Eigen::VectorXf key,Eigen::VectorXf scale);
    // *******
    // Getters
    // *******
    std::vector<float> getProjection();
    std::vector<float> getBestGuess();
    std::vector<float> getInSpectrum();
    std::vector<float> getProjectionUncertainties();
    std::vector<float> getProjectionUncertaintiesWSqrt();
    Eigen::VectorXf getLightOutputResponse();
    Eigen::VectorXf getLightOutputUncertainties();
    Eigen::VectorXf getInputEnergies();
    // *************
    // histogram visualization
    // *************
    void plotResponseForAnEnergy(double energy);
    void plotInputSpectrum(char*name);
    void plotProjection(char*name);
    TGraph* plotAnswer(char* name);
    TGraph* plotAnswer(Eigen::VectorXf uncertainties,char *name);
    void plotResponseMatrix();
    void plotRMSE();
  public:
    TH1F *hFinal;
    TH1F *hInput;
    TH1F *hAnswer;
    TH1F *hAnswerTest;
    TH1F *hSig;

};
}

#endif
