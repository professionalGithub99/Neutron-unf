#include "UNCERT.h"
namespace UNFOLD{
  //constructor for uncertainty quant. generating fakedata
  //unfold_pnt is the pointer to an unfolding object
  //sampleCount sample count is  how many sets of bins do you expect to be created on gaussian smear and or how many reconstrcuted on unfoldin
  UNCERT::UNCERT(UNFOLD *unfold_pnt,int sampleCount,vector<double> en,vector<double> w){

    UNCERT::unfold_pnt=unfold_pnt;

  //sets number of times you want to generate simulated data
    UNCERT::sampleCount=sampleCount;

    //setting fake data params
    UNCERT::en=en;
    UNCERT::w=w;

    //reconstructed bins are mean to house post gaussian smearing.generated lightout ouptuts but pre unfolding.
    //row count is samplecount and light bin size is the column count
    reconstructedBinMatrix.resize(sampleCount,unfold_pnt->nBins);
    reconstructedBinUncertainties.resize(unfold_pnt->nBins);

//simulated bins are for neutron energies which are after the unfolding to reconstructed bins
//the column count is the number of energyBins
    simulatedBinMatrix.resize(0,unfold_pnt->eBins);
    simulatedBinMatrix.setZero();

    simulatedBinMeans.resize(unfold_pnt->eBins);
    simulatedBinMeans.setZero();

    simulatedBinUncertainties.resize(unfold_pnt->eBins);

    generateFakeData();
  }

//generates fakeData and then sets the private variable light output bins to the light output response generated
Eigen::VectorXf UNCERT::generateFakeData(){

    UNCERT::unfold_pnt->generateFakeData(en,w);
    unfold_pnt->calcNormMatrix();
    UNCERT::lightOutputs=UNCERT::unfold_pnt->getLightOutputResponse();
    UNCERT::lightOutputUncertainties=UNCERT::unfold_pnt->getLightOutputUncertainties();
    return lightOutputs;
}

//constructor for real data
  UNCERT::UNCERT(UNFOLD *unfold_pnt,int sampleCount,Eigen::VectorXf lightOutputs){

    UNCERT::unfold_pnt=unfold_pnt;

  //sets number of times you want to generate simulated data
    UNCERT::sampleCount=sampleCount;

    UNCERT::lightOutputs=lightOutputs;
    UNCERT::unfold_pnt->setLightOutput(lightOutputs);

    UNCERT::lightOutputUncertainties=unfold_pnt->getLightOutputUncertainties();

    //reconstructed bins are mean to house post gaussian smearing.generated lightout ouptuts but pre unfolding.
    //row count is samplecount and light bin size is the column count
    reconstructedBinMatrix.resize(sampleCount,UNCERT::lightOutputs.size());
    reconstructedBinUncertainties.resize(UNCERT::lightOutputs.size());

//simulated bins are for neutron energies which are after the unfolding to reconstructed bins
//the column count is the number of energyBins
    simulatedBinMatrix.resize(0,unfold_pnt->eBins);
    simulatedBinMatrix.setZero();

    simulatedBinMeans.resize(unfold_pnt->eBins);
    simulatedBinMeans.setZero();
    simulatedBinUncertainties.resize(unfold_pnt->eBins);
    binGeneration();
  }




/*Eigen::VectorXf UNCERT::setRealData(Eigen::VectorXf lightOutputs, Eigen::VectorXf lightOutputUncertainties){
  //not yet completeds`
}*/

//this method generates the smeared bins from the initial light outputs-> It puts each generated
//Lightoutput vctor into a row in reconstructed bin matrix
  Eigen::MatrixXf UNCERT::binGeneration(){
    // one for fake data and one for expiremental can take in vect or hist.

    TRandom random_tracker= TRandom();
    for(int i=0;i<lightOutputs.size();i++){
      Eigen::VectorXf tempVect(sampleCount);
      double standardDev=0;
      for (int j=0;j<sampleCount;j++){
        float temp_tracker=random_tracker.Gaus(lightOutputs(i),lightOutputUncertainties(i));
        tempVect(j)=temp_tracker;
      }
      /*if(tempVect.isZero()!=1){
      cout<<"bin"<<i<<endl;
      cout<<tempVect.transpose()<<endl;
      cout<<tempVect.maxCoeff()<<" max ";
      cout<<tempVect.minCoeff()<<" min ";
      cout<<tempVect.mean()<<" mean ";
      cout<<h1->GetMean()<<" meanCheck ";
      cout<<h1->GetStdDev()<<" std ";
      cout<<tempVect.isZero()<<" is Zero ";
      cout<<endl<<endl;
    }*/

    //this matrix each row will be unfolded
    reconstructedBinMatrix.col(i)=tempVect;
  }

/*unfold_pnt->setLightOutput(reconstructedBinMatrix.row(10));
unfold_pnt->plotInputSpectrum();
Eigen::VectorXf vect=mean(reconstructedBinMatrix);
unfold_pnt->setLightOutput(vect);
unfold_pnt->plotInputSpectrum();*/
  return reconstructedBinMatrix;
}


void UNCERT::plotReconstructedLightOutputByTrial(int trialNumber,char *name){
  unfold_pnt->setLightOutput(reconstructedBinMatrix.row(trialNumber));
  unfold_pnt->plotInputSpectrum(name);
}

//this method loops through reconstructed bin matrix
  Eigen::MatrixXf UNCERT::unfoldReconstructed(){

  for(int i=0;i<reconstructedBinMatrix.rows();i++){
  unfold_pnt->setLightOutput(reconstructedBinMatrix.row(i));
  unfold_pnt->setInitialGuess(1.);
  for(int j=0; j<390; j++)
  {
    unfold_pnt->updateMLEM();
  }
simulatedBinMatrix.resize(simulatedBinMatrix.rows()+1,simulatedBinMatrix.cols());
simulatedBinMatrix.row(simulatedBinMatrix.rows()-1)=unfold_pnt->getInputEnergies();
  }

setSimulatedMeans();
setSimulatedUncertainties();
return simulatedBinMatrix;
}

Eigen::VectorXf UNCERT::standardDeviation(Eigen::MatrixXf matrix){
  Eigen::VectorXf stdVectors;
  stdVectors.resize(matrix.cols());
  for (int i=0;i<matrix.cols();i++) {
    float sd=0;
    float mean=matrix.col(i).mean();
    for (int j=0;j<matrix.rows();j++){
      sd+=TMath::Power((matrix(j,i)-mean),2);
  }
  sd=sqrt(sd/matrix.rows());
  stdVectors(i)=sd;
}
return stdVectors;
}

Eigen::VectorXf UNCERT::mean(Eigen::MatrixXf matrix){
  Eigen::VectorXf meanVector;
  meanVector.resize(matrix.cols());
  for (int i=0;i<matrix.cols();i++) {
    float mean=matrix.col(i).mean();
    meanVector(i)=mean;
  }
return meanVector;
}


void UNCERT::setSimulatedMeans(){
  Eigen::VectorXf simVect(simulatedBinMatrix.cols());
  for(int i=0;i<simulatedBinMatrix.cols();i++){
    simulatedBinMeans(i)=simulatedBinMatrix.col(i).mean();
  }
}


void UNCERT::setSimulatedUncertainties(){
Eigen::VectorXf stdVect=standardDeviation(simulatedBinMatrix);
  simulatedBinUncertainties=stdVect;
}


void UNCERT::plotSimulatedMeans(char *name){
  unfold_pnt->setInputEnergy(simulatedBinMeans);
  //unfold_pnt->plotAnswer(name);
 unfold_pnt->plotAnswer(simulatedBinUncertainties,name);
  //unfold_pnt->setAnswerUncertainties(simulatedBinUncertainties);
}

void UNCERT::plotSimulatedMeanByTrial(int trialNumber,char* name){
  Eigen::VectorXf trial=simulatedBinMatrix.row(trialNumber);
  cout<<simulatedBinMatrix.row(trialNumber)<<"Tet";
  unfold_pnt->setInputEnergy(trial);
  unfold_pnt->plotAnswer(name);
  //unfold_pnt->setAnswerUncertainties(simulatedBinUncertainties);
}



//this is for our own testing purposes to see that we get a guassian for each reconstructed bin

//this is for our own testing purposes to see that we get a guassian for each reconstructed bin
void UNCERT::plotBinNumber(int binNumber,Eigen::MatrixXf matrix, char *name,const char *title){
  new TCanvas;
  Eigen::VectorXf plottedBin= matrix.col(binNumber);
  TH1F * binX= new TH1F(name,"specificLOBin;counts;countsgen",unfold_pnt->nBins+1,-10,10);
  double total=0;
  for (int i =0;i<matrix.col(binNumber).size();i++){
    binX->Fill(matrix(i,binNumber),1);
    cout<<i<<" "<<binX->GetBinContent(i)<<" "<<binX->GetBinLowEdge(i)<<" "<<matrix(i,binNumber)<<endl;
    total+=binX->GetBinContent(i);
  }
  total=total/matrix.col(binNumber).size();
  binX->Draw();

}

}
