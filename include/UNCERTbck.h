
#ifndef _UNCERT_H_
#define _UNCERT_H_
//Eigen
#include <Eigen/Core>
#include <Eigen/Dense>
#include <TH1.h>
// including Root stuff

#include <fstream>
#include <string>
#include <iostream>
#include <TRandom.h>
#include<UNFOLD.h>
using namespace std;
namespace UNFOLD{
	class UNCERT{
	private:
	public:
		typedef Eigen::VectorXf ( *simulation_fn) (Eigen::VectorXf inputVectors);
		UNCERT(UNFOLD *unfold_pnt,Eigen::VectorXf sampledVector, Eigen::VectorXf sampledVectorUncertainties,int sampleCount);
		void binGeneration(int sampleCount);
		//Eigen::MatrixXf unfoldReconstructed();
		UNFOLD *unfold_pnt;
		Eigen::VectorXf sampledVector;
		Eigen::VectorXf sampledVectorUncertainties;
		Eigen::MatrixXf reconstructedBinMatrix;
		Eigen::VectorXf reconstructedBinMeans;
		Eigen::VectorXf reconstructedBinUncertainties;
		Eigen::MatrixXf simulatedBinMatrix;
		Eigen::VectorXf simulatedBinMeans;
		Eigen::VectorXf simulatedBinUncertainties;
		int sampleCount;
		int binCount;
	};
}
#endif
