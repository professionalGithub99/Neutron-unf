#include "UNCERT.h"

namespace UNFOLD{
UNCERT::UNCERT(UNFOLD *unfold_pnt,int fakeDataCount,int sampleCount,vector<double> en,vector<double> w){
UNCERT::unfold_pnt=unfold_pnt;
UNCERT::sampleCount=sampleCount;
UNCERT::sampledVector=unfold_pnt->getLightOutputResponse();
UNCERT::sampledVectorUncertainties=unfold_pnt->getLightOutputUncertainties();
UNCERT::en=en;
UNCERT::w=w;
reconstructedBinMatrix.resize(sampleCount,UNCERT::sampledVector.size());
reconstructedBinMeans.resize(UNCERT::sampledVector.size());
reconstructedBinUncertainties.resize(UNCERT::sampledVector.size());
simulatedBinMatrix.resize(0,unfold_pnt->eBins);
simulatedBinMatrix.setZero();
simulatedBinMeans.resize(unfold_pnt->eBins);
simulatedBinMeans.setZero();
simulatedBinUncertainties.resize(unfold_pnt->eBins);
binGeneration();
}

void UNCERT::loopSampleCreate(){

}
Eigen::MatrixXf UNCERT::binGeneration(){
  unfold_pnt->generateFakeData(en,w);
  Eigen::VectorXf lightOutputs=unfold_pnt->getLightOutputResponse();
  Eigen::VectorXf lightOuptutUncertainties=unfold_pnt->getLightOutputUncertainties();
  TRandom random_tracker= TRandom();
  for(int i=0;i<lightOutputs.size();i++){
  Eigen::VectorXf tempVect(sampleCount);
  TH1F *h1 = new TH1F("test", "test", sampleCount,-100,100);
  double standardDev=0;
  for (int j=0;j<sampleCount;j++){
      float temp_tracker=random_tracker.Gaus(lightOutputs(i),lightOuptutUncertainties(i));
      h1->Fill(temp_tracker);
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
  reconstructedBinMatrix.col(i)=tempVect;
  reconstructedBinMeans(i)=h1->GetMean();
  reconstructedBinUncertainties(i)=h1->GetMean();
  delete h1;
    }
    return reconstructedBinMatrix;
  }


void UNCERT::plotReconstructedBinNumb(int binNumber){
  new TCanvas;
  Eigen::VectorXf plottedBin= reconstructedBinMatrix.col(binNumber);
  std::string var= "binNumber "+std::to_string(binNumber)+";Light Output (MeVee);Counts";
  TH1F * reconstructedBinX= new TH1F("binNumber","binNumber;Light Output (MeVee);Counts",reconstructedBinMatrix.rows(),reconstructedBinMatrix.col(binNumber).minCoeff(),reconstructedBinMatrix.col(binNumber).maxCoeff());
  for (int i =0;i<reconstructedBinMatrix.col(binNumber).size();i++){
  reconstructedBinX->Fill(reconstructedBinMatrix.col(binNumber)(i));
  }
  reconstructedBinX->Draw();
}

void UNCERT::plotReconstructedLightOutputs(){
  unfold_pnt->setLightOutput(reconstructedBinMeans);
  unfold_pnt->plotProjection();
}

Eigen::VectorXf UNCERT::unfoldReconstructedMean(){
    unfold_pnt->setLightOutput(reconstructedBinMeans);
  unfold_pnt->calcNormMatrix();
  unfold_pnt->setInitialGuess(1.);
  for(int j=0; j<2000; j++)
  {
    unfold_pnt->updateMLEM();
  }
  /*int z=0;
  while(!simulatedBinMatrix.row(z).isZero()){
  z++;
}*/
cout<<simulatedBinMatrix.rows()<<" "<<simulatedBinMatrix.cols()<<endl<<endl;
simulatedBinMatrix.resize(simulatedBinMatrix.rows()+1,simulatedBinMatrix.cols());
  simulatedBinMatrix.row(simulatedBinMatrix.rows()-1)=unfold_pnt->getInputEnergies();
getSimulatedMeans();  
  Eigen::VectorXf vectors=unfold_pnt->getInputEnergies();
  cout<<vectors<<"test"<<endl<<endl;
//  cout<<simulatedBinMeans<<"test 2"<<endl<<endl;
  return simulatedBinMeans;
}

void UNCERT::getSimulatedMeans(){
for (int i=0;i<simulatedBinMatrix.cols();i++){
  simulatedBinMeans(i)=simulatedBinMatrix.col(i).mean();
}
}

void UNCERT::getSimulatedUncertainties(){
for (int i=0;i<simulatedBinMatrix.cols();i++){
  TH1F * temp= new TH1F("binNumber","binNumber;Light Output (MeVee);Counts",reconstructedBinMatrix.rows(),reconstructedBinMatrix.col(i).minCoeff(),reconstructedBinMatrix.col(i).maxCoeff());
  for (int j=0;j<simulatedBinMatrix.rows();j++){
  temp->Fill(simulatedBinMatrix.col(i)(j));
  }
simulatedBinUncertainties(i)=temp->GetStdDev();
delete temp;
}
}

  void UNCERT::plotReconstructedMeans(){
  unfold_pnt->setInputEnergy(simulatedBinMeans);
  unfold_pnt->plotAnswer();

  }

/*Eigen::MatrixXf UNCERT::unfoldReconstructed(){
  for (int i=0;i<simulatedBinMatrix.rows();i++){
    unfold_pnt->setLightOutput(reconstructedBinMatrix.row(i));
  for(int j=0; j<2000; j++)
  {
    unfold_pnt->updateMLEM();
  }
  simulatedBinMatrix.row(i)=unfold_pnt->getInputEnergies();
  }
  for (int i=0;i<simulatedBinMatrix.cols();i++){
    TH1F *h1= new TH1F("test","test",sampleCount,-100,100);
  for(int j=0; j<simulatedBinMatrix.rows(); j++)
  {
    h1->Fill(simulatedBinMatrix(j,i));
  }
  simulatedBinMeans(i)=h1->GetMean();
  simulatedBinUncertainties(i)=h1->GetStdDev();
  delete h1;
  }
  return simulatedBinMatrix;
}*/


  }
