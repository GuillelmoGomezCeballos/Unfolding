void makeZXXNtuple(){

  const int nValues = 5;
  Float_t xbinsHighPt[nValues+1] = {200,300,400,500,800,1500};
  TH1D *hDDilHighPtLL     = new TH1D("hDDilHighPtLL", "hDDilHighPtLL", nValues, xbinsHighPt);
  TH1D *hDDilHighPtNN     = new TH1D("hDDilHighPtNN", "hDDilHighPtNN", nValues, xbinsHighPt);
  TH1D *hDDilHighPtXX     = new TH1D("hDDilHighPtXX", "hDDilHighPtXX", nValues, xbinsHighPt);
  TH1D *hDTheoHighPt      = new TH1D("hDTheoHighPt" , "hDTheoHighPt" , nValues, xbinsHighPt);

  TH1D *hDDilHighPtLL_inc = new TH1D("hDDilHighPtLL_inc", "hDDilHighPtLL_inc", 1, xbinsHighPt[0], xbinsHighPt[nValues]);
  TH1D *hDDilHighPtNN_inc = new TH1D("hDDilHighPtNN_inc", "hDDilHighPtNN_inc", 1, xbinsHighPt[0], xbinsHighPt[nValues]);
  TH1D *hDDilHighPtXX_inc = new TH1D("hDDilHighPtXX_inc", "hDDilHighPtXX_inc", 1, xbinsHighPt[0], xbinsHighPt[nValues]);
  TH1D *hDTheoHighPt_inc  = new TH1D("hDTheoHighPt_inc" , "hDTheoHighPt_inc" , 1, xbinsHighPt[0], xbinsHighPt[nValues]);

  double rsZLL[nValues+1]	 = {1.107,1.033,1.111,1.090,1.186,1.076};
  double rsZLLUp[nValues+1]	 = {0.041,0.040,0.048,0.055,0.142,0.040};
  double rsZLLDown[nValues+1]	 = {0.041,0.040,0.048,0.055,0.142,0.040};
  double rsZNN[nValues+1]	 = {1.128,1.084,1.067,1.043,0.964,1.040};
  double rsZNNUp[nValues+1]	 = {0.066,0.059,0.061,0.060,0.080,0.054};
  double rsZNNDown[nValues+1]	 = {0.066,0.059,0.061,0.060,0.080,0.054};
  double rsZXX[nValues+1]	 = {1.104,1.038,1.064,1.028,1.027,1.076};
  double rsZXXUp[nValues+1]	 = {0.038,0.037,0.039,0.040,0.065,0.038};
  double rsZXXDown[nValues+1]	 = {0.038,0.037,0.039,0.040,0.065,0.038};

  double xs[nValues+1]        = {2108.39,373.45,87.00,40.12,3.20,2612.16};
  double xsUp[nValues+1]      = {0.156,0.176,0.195,0.215,0.280,0.160};
  double xsDown[nValues+1]    = {0.156,0.176,0.195,0.215,0.280,0.160};

  for(int i=0; i<=nValues; i++){
    xs[i] = xs[i] / 1000.;
    if(i<nValues){
      hDDilHighPtLL->SetBinContent(i+1, rsZLL  [i]*xs[i]);
      hDDilHighPtLL->SetBinError  (i+1, rsZLLUp[i]*xs[i]);
      hDDilHighPtNN->SetBinContent(i+1, rsZNN  [i]*xs[i]);
      hDDilHighPtNN->SetBinError  (i+1, rsZNNUp[i]*xs[i]);
      hDDilHighPtXX->SetBinContent(i+1, rsZXX  [i]*xs[i]);
      hDDilHighPtXX->SetBinError  (i+1, rsZXXUp[i]*xs[i]);
      hDTheoHighPt ->SetBinContent(i+1,            xs[i]);
      hDTheoHighPt ->SetBinError  (i+1,    xsUp[i]*xs[i]);
    } else {
      hDDilHighPtLL_inc->SetBinContent(1, rsZLL  [i]*xs[i]);
      hDDilHighPtLL_inc->SetBinError  (1, rsZLLUp[i]*xs[i]);
      hDDilHighPtNN_inc->SetBinContent(1, rsZNN  [i]*xs[i]);
      hDDilHighPtNN_inc->SetBinError  (1, rsZNNUp[i]*xs[i]);
      hDDilHighPtXX_inc->SetBinContent(1, rsZXX  [i]*xs[i]);
      hDDilHighPtXX_inc->SetBinError  (1, rsZXXUp[i]*xs[i]);
      hDTheoHighPt_inc ->SetBinContent(1,	     xs[i]);
      hDTheoHighPt_inc ->SetBinError  (1,    xsUp[i]*xs[i]);
    }
  }

  TFile myOutputFile("zPtMeasurements.root","RECREATE");
    hDDilHighPtLL     ->Write();
    hDDilHighPtNN     ->Write();
    hDDilHighPtXX     ->Write();
    hDTheoHighPt      ->Write();

    hDDilHighPtLL_inc ->Write();
    hDDilHighPtNN_inc ->Write();
    hDDilHighPtXX_inc ->Write();
    hDTheoHighPt_inc  ->Write();
  myOutputFile.Close();
}
