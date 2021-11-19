
#ifndef _UNCERT_H_
#define _UNCERT_H_
//Eigen
#include <Eigen/Core>
#include <Eigen/Dense>
#include <TH1.h>
#include <TCanvas.h>
// including Root stuff

#include <fstream>
#include <string>
#include <iostream>
#include <TRandom.h>
#include<UNFOLD.h>
#include<TProfile.h>
#include<TMath.h>
using namespace std;
namespace UNFOLD{
	class UNCERT{
	private:
	public:
		UNCERT(UNFOLD *unfold_pnt,int sampleCount,vector<double> en,vector<double> w);
		UNCERT(UNFOLD *unfold_pnt,int sampleCount,Eigen::VectorXf lightOutputs);

		vector<double>en;
		vector<double>w;
		Eigen::MatrixXf binGeneration();
		Eigen::MatrixXf unfoldReconstructed();
		Eigen::VectorXf generateFakeData();
		Eigen::VectorXf standardDeviation(Eigen::MatrixXf matrix);
		Eigen::VectorXf mean(Eigen::MatrixXf matrix);
		void plotBinNumber(int binNumber, Eigen::MatrixXf matrix,char *name,const char *title);
		void setSimulatedUncertainties();
		void setSimulatedMeans();
		void setSimulatedSums();
		void plotSimulatedMeans(char *name);
		void plotReconstructedLightOutputByTrial(int trialNumber,char* name);
		void plotSimulatedMeanByTrial(int trialNumber,char *name);

		//*******************
		//HELPER FUNCTIONS
		//********************
		Eigen::VectorXf scaleVectorOverOne(Eigen::VectorXf vector);
		//*****************
		//INITIAL VARS
		//****************
		Eigen::VectorXf lightOutputs;
		Eigen::VectorXf lightOutputUncertainties;
		UNFOLD *unfold_pnt;
		//*****************
		//RECONSTRUCTED DATA STRUCTS
		//****************
		Eigen::MatrixXf reconstructedBinMatrix;
		Eigen::VectorXf reconstructedBinUncertainties;
		//*****************
		//NEWLY SIM DATA
		//****************
		Eigen::MatrixXf simulatedBinMatrix;
		Eigen::VectorXf simulatedBinMeans;
		Eigen::VectorXf simulatedBinSums;
		Eigen::VectorXf simulatedBinUncertainties;

		int sampleCount;
	};
}
#endif