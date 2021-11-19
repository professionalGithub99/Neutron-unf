// test SIRT for light-output spectrum unfolding
void Odessa_SIRT_FakeDataTest()
{
  UNFOLD::FILEIO *fio;
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
  vector<double> en = {.2,1.2,3.1,8};
  vector<double>  w = {3,0.5,8,22};

  s.generateFakeData(en, w);
  //s.readInExpSpectrum(iFN,"hPIC");
  //s.setData();
  cout << "calculating normal matrix\n";
  s.calcNormMatrix();
  cout << "setting initial guess\n";
  s.setInitialGuess(1.);

  // loop over number of iterations for unfolding
  cout << "updating\n" << endl;\
  for(int i=0; i<2000; i++)
  {
    s.updateMLEM();
  }
  s.plotProjection();
  s.plotAnswer();
  auto tf_out = new TFile("mlem_out.root","recreate");
  s.hAnswer->Write();
  s.hInput->Write();
  s.hFinal->Write();
  
  return;
}
