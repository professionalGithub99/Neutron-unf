// test SIRT for light-output spectrum unfolding
/*
 *\brief a test program for UNFOLDING 
 */
void Odessa_SIRT_FakeData()
{
  UNFOLD::FILEIO *fio;
  UNCERT::UNCERT *uncert;
  fio = new UNFOLD::FILEIO();
  fio->setThreshold(0.2);
  fio->setNbins(350);
  fio->setEbins(160);
  fio->setRange(0,10);
  fio->setEnergyIncrement(0.05); // in units of MeV
  fio->setResponse("odessa_matrix.txt");
  UNFOLD::UNFOLD s(fio);
  s.printParameters();
  // add these to FILEIO class
  cout << "setting response matrix\n";
  s.setResponseMatrix();
 vector<double> en = {1.1,1.2,1.3,1.6,1.7,1.8,1.9,2.2,2.3,2.4,3.6,3.7,3.8};
  vector<double>  w = {1800,2100,1000,8800,9000,8400,13000,1000,1200,1300,1850,1950,1850};
  
  //30 m_bar
  /*vector<double> en = {1.5,3.2,6.2};
  vector<double>  w = {11,16,10};
  //700 iters
  vector<double> en = {1.5,3.2,6.2};
  vector<double>  w = {10,10,17};*/
  //800 iters
  //vector<double> en = {3.1,6.6};
  //vector<double>  w = {20,10};
  //2000 iters
  /*vector<double> en = {4.1,5.2};
  vector<double>  w = {8,22};*/


  s.generateFakeData(en, w);
  //s.readInExpSpectrum(iFN,"hPIC");
  //s.setData();
  cout << "calculating normal matrix\n";
  s.calcNormMatrix();
  cout << "setting initial guess\n";
  s.setInitialGuess(1.);
  //s.plotProjection("lightOutput");


  double lowestRMSE=s.getRMSE();
  double lowestIteration=0;
  Eigen::VectorXf lowestForwardProjection=s.getFwdProjection();
  //prints the forward projection, light output spectrum, neutron guess, and ground truth neutron specrum does the mlem unfolding for i counts
  for(int i=0; i<2014; i++)
  {
	  //this prints out the various arrays-> forward projection, light output spectrum, neutron guess, and ground truth neutron spectrum
  /*cout<<"|Fwd Proj|lOutSpect|NeutronGuess|Ground_Truth|"<<endl;
	std::cout << std::setprecision(5);
	  for(int j=0; j<s.getFwdProjection().size(); j++)
	  {
		  cout<<fixed<<std::setprecision(5)<<s.getFwdProjection()[j]<<"     "<<s.getInSpectrum()[j]<<"     ";
		  int bestGuessSize=s.getBestGuess().size();
		  if(j<bestGuessSize)
		  {
			  cout<<setprecision(5)<<s.getBestGuess()[j]<<"      "<<s.getGroundTruth()[j]<<endl;
		  }
		  else{cout<<endl;}
	  }*/
	  //cout<<std::setprecision(14)<<"Iteration:"<<i<<"|Stop Indice:"<<s.getStopIndice()<<"|RSS:"<<s.getRss()<<"|RMSE:"<<s.getRMSE()<<"|lowest RMSE:"<<lowestRMSE<<"|lowest iteration:"<<lowestIteration<<endl;

	  if(s.getRMSE()<lowestRMSE)
	  {
		  lowestRMSE=s.getRMSE();
		  lowestIteration=i;
		  lowestForwardProjection=s.getFwdProjection();
	  }
	  //append s.getBestGuess() to the end of the matrix
	  s.updateMLEM();
	  //cout<<endl<<endl;
	  s.calcRMSE();
  }
cout<<setprecision(12)<<"|Stop Indice:"<<s.getStopIndice()<<"|RSS:"<<s.getRss()<<"|RMSE:"<<s.getRMSE()<<"|lowest RMSE:"<<lowestRMSE<<"|lowest iteration:"<<lowestIteration<<"|mean input spectrum bin count:" <<s.getMeanInSpectrumBinCount()<<"|MeanDeviation:"<<s.getMD(lowestForwardProjection)<<"|InputSpectrum sum"<<s.getInSpectrum().sum()<<"|Forward Projection Size:"<<s.getFwdProjection().size()<<endl<<endl;
s.plotTheoreticalMD("TheoreticalMD");
s.plotRSS();
s.plotRMSE();
s.plotProjection("lightOutput");
s.plotAnswer("NeutronSpectrum");



//uncertainty calculations
/*uncert=new UNCERT::UNCERT(&s,205,en,w);
Eigen::MatrixXf reconstMtx= uncert->binGeneration();
Eigen::MatrixXf simMtx= uncert->unfoldReconstructed();
//uncert->plotSimulatedMeanByTrial(0,"11");
//uncert->plotSimulatedMeanByTrial(8,"22");
uncert->plotBinNumber(65,simMtx,"neutronEnergyBin65;counts;countsgen","testing2");
uncert->plotBinNumber(130,simMtx,"neutronEnergyBin130;counts;countsgen","testing2");
uncert->plotBinNumber(131,simMtx,"neutronEnergyBin131;counts;countsgen","testing2");
uncert->plotBinNumber(142,simMtx,"neutronEnergyBin142;counts;countsgen","testing2");
uncert->plotBinNumber(30,reconstMtx,"LOBin30;counts;countsgen","stuff");
uncert->plotInSpectrumByTrial(2,"example light output spectrum");
uncert->plotSimulatedMeans("abcdef");*/
//s.hAnswer->Write();
// s.hInput->Write();
 // s.hFinal->Write();
 
  auto tf_out = new TFile("mlem_out.root","recreate");
  return;
}


//notes
// uncertainty of response is square root
//chapter 3 in radiation detector book read
// nulls
