// test SIRT for light-output spectrum unfolding
void Odessa_SIRT_FakeData()
{
  UNFOLD::FILEIO *fio;
  UNFOLD::UNCERT *uncert;
  fio = new UNFOLD::FILEIO();
  fio->setResponse("odessa_matrix.txt");
  fio->setThreshold(0.2);
  fio->setNbins(350);
  fio->setEbins(160);
  fio->setRange(0,10);
  fio->setEnergyIncrement(0.05); // in units of MeV
  UNFOLD::UNFOLD s(fio);
  s.printParameters();
  // add these to FILEIO class
  cout << "setting response matrix\n";
  s.setResponseMatrix();
/*  vector<double> en = {.5,1.2,3.2,5};
  vector<double>  w = {3,10.5,10,20};*/

/*  vector<double> en = {0.5,3.2,6.2};
  vector<double>  w = {11,16,10};*/
  vector<double> en = {1.2,6.5,4.5};
  vector<double>  w = {9,11,29};
  s.generateFakeData(en, w);
  Eigen::VectorXf test=s.getLightOutputResponse();
  //s.readInExpSpectrum(iFN,"hPIC");
  //s.setData();
  cout << "calculating normal matrix\n";
  s.calcNormMatrix();
  cout << "setting initial guess\n";
  s.setInitialGuess(1.);

  // loop over number of iterations for unfolding
  cout << "updating\n" << endl;\
  for(int i=0; i<500; i++)
  {
    s.updateMLEM();
  }

  // loop over number of iterations for unfolding
s.plotInputSpectrum("jj");
s.plotAnswer("tt");


uncert=new UNFOLD::UNCERT(&s,200,en,w);
Eigen::MatrixXf reconstMtx= uncert->binGeneration();
//Eigen::MatrixXf simMtx= uncert->unfoldReconstructed();
//uncert->plotSimulatedMeans("testing");

uncert->plotBinNumber(18,reconstMtx,"Testing","testing2");
uncert->plotReconstructedLightOutputByTrial(18,"aaa");
//uncert->plotReconstructedLightOutputByTrial(5,"zaa");
//uncert->plotBinNumber(22,simMtx,"Testing","testing2");
//uncert->plotSimulatedMeans();
//Eigen::MatrixXf simulMtx= uncert->unfoldReconstructed();
//cout<<simulMtx.rows()<<"jksljdlf"<<simulMtx.cols()<<endl<<endl;
//uncert->plotBinNumber(33,simulMtx,"test","test2");
//uncert->plotBinNumber(99,simulMtx,"test","test2");

//Eigen::MatrixXf test=uncert->unfoldReconstructed();
//uncert->plotReconstructedMeans();
//Eigen::MatrixXf matrix=uncert->reconstructedBinMatrix;

//Eigen::VectorXf lightOutputs=s.getLightOutputResponse();
//Eigen::VectorXf lightOutputUncertainties= s.getLightOutputUncertainties();
//makesure newLight output and new energybins match counts
//std::vector<Eigen::VectorXf> histogramVectors;
//Eigen::MatrixXf newLightOutputs(5,lightOutputs.col(0).size());
//Eigen::MatrixXf newEnergyBins(5,160);
//TRandom random_tracker= TRandom();
/*int genGauss=2000;
for(int i=0;i<lightOutputs.col(0).size();i++){
      Eigen::VectorXf tempVect(genGauss);
      double standardDev=0;
    TH1F *h1 = new TH1F("test", "test", genGauss, -100,100 );
    for (int j=0;j<genGauss;j++){
  float temp_tracker=random_tracker.Gaus(lightOutputs.col(0)[i],lightOutputUncertainties.col(0)[i]);
  h1->Fill(temp_tracker);
  tempVect(j)=temp_tracker;
  }
  if(tempVect.isZero()!=1){
    cout<<"bin"<<i<<endl;
    cout<<tempVect.transpose()<<endl;
    cout<<tempVect.maxCoeff()<<" max ";
    cout<<tempVect.minCoeff()<<" min ";
    cout<<tempVect.mean()<<" mean ";
    cout<<h1->GetMean()<<" meanCheck ";
    cout<<h1->GetStdDev()<<" std ";
    cout<<tempVect.isZero()<<" is Zero ";
    cout<<endl<<endl;
  }
  histogramVectors.push_back(tempVect);
  delete h1;
}

int drawVector=11;
TH1F *h1 = new TH1F("test", "test", genGauss,histogramVectors.at(drawVector).minCoeff(),histogramVectors.at(drawVector).maxCoeff() );
for(int i=0;i<histogramVectors.at(drawVector).size();i++){
  h1->Fill(histogramVectors.at(drawVector)(i));
}
h1->Draw();*/


/*for (int j=0;j<newLightOutputs.rows();j++){
  s.setLightOutputMatrix(newLightOutputs.row(j));
  for(int z=0; z<2000; z++)
  {
    s.updateMLEM();
  }
  Eigen::VectorXf bb=s.getInputEnergies();
  newEnergyBins.row(0)=s.getInputEnergies();
//  s.plotAnswer();
}
Eigen::VectorXf meanVect(newEnergyBins.cols());
Eigen::VectorXf stdVectors(newEnergyBins.cols());
for(int i=0;i<newEnergyBins.cols();i++){
meanVect(i)=newEnergyBins.col(i).mean();
}
s.setInputEnergy(meanVect);
s.plotAnswer();
  for (int i=0;i<newEnergyBins.cols();i++) {
    float sd=0;
    float mean=newEnergyBins.col(i).mean();
    for (int j=0;j<newEnergyBins.rows();j++){
      sd+=pow((newEnergyBins(j,i)-mean),2);
  }
  sd=sqrt(sd/newEnergyBins.rows());
  stdVectors(i)=sd;
}*/
  auto tf_out = new TFile("mlem_out.root","recreate");
//s.hAnswer->Write();
// s.hInput->Write();
 // s.hFinal->Write();
  return;
}
