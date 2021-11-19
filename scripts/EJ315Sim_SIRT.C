// test SIRT for light-output spectrum unfolding
void EJ315Sim_SIRT(TString iFN = "in.root",TString oFN = "rout.root")
{
  UNFOLD::UNFOLD s;
  //UNFOLD::HVis hp;
  TString ts = "/media/7jn/gogo/neutronResponseEJ315_05/";
  s.setThreshold(.1);
  s.setRebinVal(50);
  s.setRange(1.05,20);
  s.setEbins(380); // number of response files
  s.setNbins(400); // number of bins in your response histogram for 1 energy

  s.setEnergyIncrement(0.05);
  s.setResponse(ts,380, "_en_");
  cout << "calculating normal matrix\n";
  //************************************************************************** 
  s.setResponseMatrix();
  s.calcNormMatrix();
  cout << "read in data to unfold\n";
  s.readInExpSpectrum(iFN,"Det0_smear");
  s.setData();
  cout << "setting initial guess\n";
  s.setInitialGuess(1.);
  // loop over number of iterations for unfolding
  cout << "updating\n" << endl;
  int its = 500;
  for(int i=0; i<its; i++)
  {
    if(i%100 == 0)
      cout << i << "\t-----> complete\n";
    s.updateMLEM();
  }


  // do some visualization
  //auto c1 = new TCanvas;
  //c1->Divide(2,1);
  //c1->cd(1);
  //s.plotInputSpectrum();
  s.plotProjection();
  s.plotAnswer();
  auto tf_out = new TFile(oFN,"recreate");
  s.hAnswer->Write();
  s.hInput->Write();
  s.hFinal->Write();
  //s.plotRMSE();
  return;
}
