// test SIRT for light-output spectrum unfolding
void plotResponseMatrix()
{
  /*UNFOLD::SIRT s;
  TString ts = "/media/7jn/gogo/neutronResponseEJ315_05/";
  s.setResponse(ts,380);
  //s.setExpSpectrum(ts);
  int nBins = 200;   // # of bins in exp spectrum to unfold.
                     // this is also the number of bins in one segment
                     // of the response matrix
                     // 200 bins is a bin width of 100 keV
  s.setEbins(380);   // number of response files
  s.setNbins(nBins); // number of bins in your response histogram for 1 energy
  cout << "setting response matrix\n";
  s.setResponseMatrix();
  //s.plotResponseMatrix();*/
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

  s.plotResponseForAnEnergy(5);
  return;
}
