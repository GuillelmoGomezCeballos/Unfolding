//takes covariance matrix and convert to correlation matrix
void helper_function(int me=0,int DY=3,TString theHistName = "Pt", TString theUnc = "totsum"){
  TFile *file = new TFile(Form("output_root/matrix%d%d_%s.root",me,DY,theHistName.Data()),"READ");
  TH2D* covar = (TH2D*)file->Get(Form("covariance_%s_%d",theUnc.Data(),me));
  printf("which matrix: %s\n",Form("covariance_%s_%d",theUnc.Data(),me));                                                                                                                          
  TH2D* corr = (TH2D*)covar->Clone("test");
  int nbins=covar->GetNbinsX();
  for (int b=1;b<=nbins;b++){
    for (int j=1;j<=nbins;j++){
      double sigb = TMath::Sqrt(covar->GetBinContent(b,b));
      double sigj = TMath::Sqrt(covar->GetBinContent(j,j));
      corr->SetBinContent(b,j,covar->GetBinContent(b,j)/(sigb*sigj));
    }
  }

  TString XName = "Z p_{T} [GeV]";
  if     (theHistName == "Rap") XName = "|y^{Z}|";
  else if(theHistName == "PhiStar") XName = "#phi*";

  char CommandToExec[300];
  sprintf(CommandToExec,"mkdir -p output_root");
  gSystem->Exec(CommandToExec);  

  char outputLimits[200];
  sprintf(outputLimits,"output_root/correlation%d%d_%s.root",me,DY,theUnc.Data());
  TFile* outFileLimits = new TFile(outputLimits,"recreate");
  outFileLimits->cd();
  corr->Write();
  outFileLimits->Close();
  /********** draw+save pdf*********/
  TCanvas* c1 = new TCanvas("c1", "c1",5,5,650,500);
  corr->SetContour(100);
  gStyle->SetPalette(55);
  corr->Draw("colz");
  c1->SetLogx();
  c1->SetLogy();
  //c1->SetLogz();
  gStyle->SetOptStat(0);
  corr->SetTitle("");
  corr->GetXaxis()->SetTitle(XName.Data());
  corr->GetXaxis()->SetLabelFont  (   42);
  corr->GetXaxis()->SetLabelOffset(0.015);
  corr->GetXaxis()->SetLabelSize  (0.030);
  corr->GetXaxis()->SetNdivisions (  505);
  corr->GetXaxis()->SetTitleFont  (   42);
  corr->GetXaxis()->SetTitleOffset( 1.0);
  corr->GetXaxis()->SetTitleSize  (0.040);
  corr->GetXaxis()->SetTickLength (0.07 );
  corr->GetYaxis()->SetTitle(XName.Data());
  corr->GetYaxis()->SetLabelFont  (   42);
  corr->GetYaxis()->SetLabelOffset(0.015);
  corr->GetYaxis()->SetLabelSize  (0.030);
  corr->GetYaxis()->SetNdivisions (  505);
  corr->GetYaxis()->SetTitleFont  (   42);
  corr->GetYaxis()->SetTitleOffset(  1.2);
  corr->GetYaxis()->SetTitleSize  (0.040);
  corr->GetYaxis()->SetTickLength (0.03 );

  sprintf(CommandToExec,"mkdir -p plots");
  gSystem->Exec(CommandToExec);  

  TString myOutputFile;
  myOutputFile = Form("plots/correlation_nsel%d_DY%d_%s.pdf",me,DY,theUnc.Data());
  c1->SaveAs(myOutputFile.Data());
}

void convert(TString theHistName = "Pt", TString theUnc = "totsum"){
  for(int i=0;i<=2;i++){
    for(int j=3;j<=3;j++){
      helper_function(i,j,theHistName.Data(),theUnc.Data());
    }
  }

}
