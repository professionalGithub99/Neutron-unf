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

/**
 * \details This class is used to aggregate various classes that are part of a neutron unfolding such as response matrix, light output spectrum, neutron guess spectrum and more
 * 
 */
class UNFOLD
{
  private:
    Eigen::MatrixXf a, b, x, x_1, catr, ax, ansIndex,z,x_uncert;
    Eigen::ArrayXf a_norm;
    Eigen::VectorXf ground_truth;
    FILEIO *m_fio;
    // a - response matrix
    // b - LO spectrum to unfold
    // x - guess
    // x_1 - updated guess
    // catr - normalization matrix
    // ax - forward projection
    // ansInex - corresponding energy for a position in x or x_1
    std::vector<double> rmse2Vals; // rss values as a function of iteration
    std::vector<double> rmseDeltaVals; // rss values as a function of iteration
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
    void calcRMSE(); //calculates rmse 
    Eigen::ArrayXf updateMLEM(); // update equation for MLEM
    void backProject();
    void updateSIRT(); // update equation for SIRT
    std::vector<double>getRSS(); // calculate rss value
    std::vector<double>getRMSEDelta(); // calculate rss value
    // *******
    // SETTERS
    // *******
    void setInSpectrum(Eigen::VectorXf vect);
    void setInputEnergy(Eigen::VectorXf vect);
Eigen::VectorXf scaleVectorWithKey(Eigen::VectorXf scaleTo, Eigen::VectorXf key,Eigen::VectorXf scale);
    // *******
    // Getters
    // *******
    std::vector<float> getProjection();
    std::vector<float> getProjectionUncertainties();
    Eigen::VectorXf getFwdProjection();
    double getStopIndice();
    double getRss();
    double getRMSE();
    double getMeanInSpectrumBinCount();
    double getMD(Eigen::VectorXf fwdProj);
    Eigen::VectorXf getInSpectrum();
    Eigen::VectorXf getInSpectrumUncertainties();
    Eigen::VectorXf getBestGuess();
    Eigen::VectorXf expirementalGetBestGuess(char *name);
    Eigen::MatrixXf getResponseMatrix();
    Eigen::VectorXf getGroundTruth();
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
    void plotRSS();
    void plotTheoreticalMD(char *name);
  public:
    TH1F *hFinal;
    TH1F *hInput;
    TH1F *hAnswer;
    TH1F *hAnswerTest;
    TH1F *hSig;

};
}

#endif
