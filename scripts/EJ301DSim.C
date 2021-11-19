// test SIRT for light-output spectrum unfolding
void EJ301DSim(TString iFN = "in.root",TString oFN = "rout.root")
{
  UNFOLD::UNFOLD s;
  //UNFOLD::HVis hp;
  //TString ts = "/media/7jn/gogo/neutronResponseEJ315_05/";
  TString ts = "/Users/igu/work/unfolding/neutron_unfolding_sims/outputFiles/";
  s.setThreshold(0.2);
  s.setRebinVal(2);
  //s.setRange(1.05,15);
  s.setRange(0.50,15);
  s.setEnergyIncrement(0.05);
  s.setResponse(ts,290,"anaSingleSetup_En");
  //s.setResponse(ts,290,"anaFullSetup_En");
  // ****************
  //s.setThreshold(0);
  //s.setNbins(350);
  //s.setEbins(160);

  //s.setExpSpectrum(ts);
  //int nBins = 200;   // # of bins in exp spectrum to unfold.
                     // this is also the number of bins in one segment
                     // of the response matrix
                     // 200 bins is a bin width of 100 keV
  //************************************************************************** 
  s.setEbins(290);   // number of response files
  s.setNbins(600); // number of bins in your response histogram for 1 energy
  cout << "setting response matrix\n";
  s.setResponseMatrix();
  cout << "read in data to unfold\n";
  s.readInExpSpectrum(iFN,"hLightOutput_det1");
  s.setData();
  cout << "calculating normal matrix\n";
  s.calcNormMatrix();
  cout << "setting initial guess\n";
  s.setInitialGuess(0.);
  // loop over number of iterations for unfolding
  cout << "updating\n" << endl;
  int its = 1000;
  for(int i=0; i<its; i++)
  {
    if(i%100 == 0)
      cout << i << "\t-----> complete\n";
    //s.updateSIRT();
    s.updateMLEM();
    //s.fwdProject();
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


  TCanvas *c2 = new TCanvas();
  s.plotResponseMatrix();
  
  return;
}
