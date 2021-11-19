// test SIRT for light-output spectrum unfolding
void EJ315_SIRT(TString iFN = "in.root")
{
  UNFOLD::SIRT s(50,0.05);
  s.setRebinVal(50);
  TString ts = "/media/7jn/gogo/neutronResponseEJ315_05/";
  s.setThreshold(1.1);
  // add these to FileIO class
  //s.setHistoName("XXX");
  //s.setFileExtension("");
  s.setResponse(ts, 380);
  //s.setExpSpectrum(ts);
  //int nBins = 400;        p/ # of bins in exp spectrum to unfold.
                            // this is also the number of bins in one segment
                            // of the response matrix
  //s.setEbins(380);
  //s.setNbins(nBins);
  cout << "setting response matrix\n";
  s.setResponseMatrix();
  vector<double> en = {2.4,14.1};
  vector<double>  w = {100,100};
  //cout << "generating fake data\n";
  //s.generateFakeData(en, w);
  //s.readInExpSpectrum("/home/7jn/code/Compass/scripts/out_AmBe.root","hNeutronE_cal1");
  s.readInExpSpectrum(iFN,"hNeutronE_cal1");
  s.setData();
  cout << "calculating normal matrix\n";
  s.calcNormMatrix();
  cout << "setting initial guess\n";
  s.setInitialGuess(1.);

  // loop over number of iterations for unfolding
  cout << "updating\n" << endl;\
  for(int i=0; i<2000; i++)
  {
    s.update();
  }

  //s.fwdProject();
  // do some visualization
  //auto c1 = new TCanvas;
  //c1->Divide(2,1);
  //c1->cd(1);
  //s.plotInputSpectrum();
  s.plotProjection();
  s.plotAnswer();

  return;
}
