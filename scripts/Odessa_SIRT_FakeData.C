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
  vector<double> en = {3.1,6.5};
  vector<double>  w = {25,15};
  s.generateFakeData(en, w);
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
uncert=new UNFOLD::UNCERT(&s,250,en,w);
Eigen::MatrixXf reconstMtx= uncert->binGeneration();
Eigen::MatrixXf simMtx= uncert->unfoldReconstructed();
//uncert->plotSimulatedMeanByTrial(0,"11");
//uncert->plotSimulatedMeanByTrial(8,"22");
uncert->plotBinNumber(65,simMtx,"jsjesting","testing2");
uncert->plotBinNumber(130,simMtx,"jsidjijdsdjsting","testing2");
uncert->plotBinNumber(142,simMtx,"rrjrkjk","testing2");
uncert->plotSimulatedMeans("abcdef");
/*uncert->plotInSpectrumByTrial(0,"am");
uncert->plotInSpectrumByTrial(1,"tm");
uncert->plotInSpectrumByTrial(2,"lm");
uncert->plotInSpectrumByTrial(3,"lim");
/*uncert->plotSimulatedMeans("Neutron En");
uncert->plotSimulatedMeanByTrial(0,"11");
uncert->plotSimulatedMeanByTrial(1,"22");
uncert->plotSimulatedMeanByTrial(2,"33");
uncert->plotSimulatedMeanByTrial(3,"44");/*
//uncert->plotSimulatedMeanByTrial(4,"55");
//uncert->plotSimulatedMeanByTrial(5,"66");
/*uncert->plotBinNumber(27,reconstMtx,"jsjesting","testing2");
uncert->plotBinNumber(29,simMtx,"jsidjg","testing2");*/
  auto tf_out = new TFile("mlem_out.root","recreate");
//s.hAnswer->Write();
// s.hInput->Write();
 // s.hFinal->Write();
  return;
}


//notes
// uncertainty of response is square root
//chapter 3 in radiation detector book read
// nulls
