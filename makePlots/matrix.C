#include <TROOT.h>
#include <TFile.h>
#include <TTree.h>
#include <TSystem.h>
#include <TString.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TMath.h>
#include <iostream>
#include <fstream>
void helper_function(int me=0, int DY=3, TString theHistName = "Pt", TString path = "../macros/outputs/", int reBin = 1){

  //gInterpreter->ExecuteMacro("GoodStyle.C");
  gStyle->SetOptStat(0);

  char filename[300];
  sprintf(filename,"%s/histoUnfoldingSyst%s_nsel%d_dy%d_rebin%d_default.root",path.Data(),theHistName.Data(),me,DY,reBin);

  TFile* _file0 = new TFile(Form("%s",filename),  "read"); if(!_file0) {printf("File does not exist\n"); return;}
  printf("Filename: %s\n",filename);

  const int nGenSyst = 8;
  const int nEffSyst = 1057;
  const int nStaSyst = 72;
  const int nOthSyst = 2;

  const int nSyst = nGenSyst+nEffSyst+nStaSyst+nOthSyst;
  TH1D* histoSyst[nSyst];
  for(int i=0; i<nSyst; i++) {histoSyst[i] = (TH1D*)_file0->Get(Form("histoSystCov_%d",i));assert(histoSyst[i]);}

  const int nBinGen = histoSyst[0]->GetNbinsX();
  Float_t xbinsGen[nBinGen+1];
  for(int i=0; i<=nBinGen; i++){
   xbinsGen[i] = histoSyst[0]->GetXaxis()->GetBinLowEdge(i+1);
  }

  TH2D* covariance_momres     = new TH2D(Form("covariance_momres_%d",me),     Form("covariance_momres_%d",me),     nBinGen, xbinsGen, nBinGen, xbinsGen);
  TH2D* covariance_lepeff     = new TH2D(Form("covariance_lepeff_%d",me),     Form("covariance_lepeff_%d",me),     nBinGen, xbinsGen, nBinGen, xbinsGen);
  TH2D* covariance_lepeffSyst = new TH2D(Form("covariance_lepeffSyst_%d",me), Form("covariance_lepeffSyst_%d",me), nBinGen, xbinsGen, nBinGen, xbinsGen);
  TH2D* covariance_lepeffStat = new TH2D(Form("covariance_lepeffStat_%d",me), Form("covariance_lepeffStat_%d",me), nBinGen, xbinsGen, nBinGen, xbinsGen);
  TH2D* covariance_totsum     = new TH2D(Form("covariance_totsum_%d",me),     Form("covariance_totsum_%d",me),     nBinGen, xbinsGen, nBinGen, xbinsGen);

  for (int i=1;i<=nBinGen;i++){
    for (int j=1;j<=nBinGen;j++){

      double sum_momres = histoSyst[1]->GetBinContent(i)*histoSyst[1]->GetBinContent(j)+
                          histoSyst[2]->GetBinContent(i)*histoSyst[2]->GetBinContent(j)+
                          histoSyst[3]->GetBinContent(i)*histoSyst[3]->GetBinContent(j)+
                          histoSyst[4]->GetBinContent(i)*histoSyst[4]->GetBinContent(j);

      double sum_lepeff = 0;
      for(int k=nGenSyst; k<nGenSyst+nEffSyst; k++) sum_lepeff = sum_lepeff + histoSyst[k] ->GetBinContent(i)*histoSyst[k] ->GetBinContent(j);

      double sum_lepeffSyst = 0;
      for(int k=nGenSyst; k<nGenSyst+7; k++) sum_lepeffSyst = sum_lepeffSyst + histoSyst[k] ->GetBinContent(i)*histoSyst[k] ->GetBinContent(j);

      double sum_lepeffStat = 0;
      for(int k=nGenSyst+7; k<nGenSyst+nEffSyst; k++) sum_lepeffStat = sum_lepeffStat + histoSyst[k] ->GetBinContent(i)*histoSyst[k] ->GetBinContent(j);

      double sum_totsum = 0.;
      for(int k=0; k<nSyst-2; k++) sum_totsum = sum_totsum + histoSyst[k]->GetBinContent(i)*histoSyst[k]->GetBinContent(j);
      if(i==j) sum_totsum = sum_totsum + histoSyst[nSyst-2]->GetBinContent(i)*histoSyst[nSyst-2]->GetBinContent(j); // data stat. uncertainty is diagonal only
      sum_totsum = sum_totsum + histoSyst[nSyst-1]->GetBinContent(i)*histoSyst[nSyst-1]->GetBinContent(j); // adding lumi
                          
      covariance_momres    ->SetBinContent(i,j,sum_momres    );
      covariance_lepeff    ->SetBinContent(i,j,sum_lepeff    );
      covariance_lepeffSyst->SetBinContent(i,j,sum_lepeffSyst);
      covariance_lepeffStat->SetBinContent(i,j,sum_lepeffStat);
      covariance_totsum    ->SetBinContent(i,j,sum_totsum    );
    }
  }

  char CommandToExec[300];
  sprintf(CommandToExec,"mkdir -p output_root");
  gSystem->Exec(CommandToExec);  

  char outputLimits[200];
  sprintf(outputLimits,"output_root/matrix%d%d.root",me,DY);
  TFile* outFileLimits = new TFile(outputLimits,"recreate");
  outFileLimits->cd();
  covariance_momres    ->Write();  
  covariance_lepeff    ->Write();  
  covariance_lepeffSyst->Write();  
  covariance_lepeffStat->Write();  
  covariance_totsum    ->Write();  
  outFileLimits->Close();

  TString XName = "Z p_{T} [GeV]";
  if     (theHistName == "Rap") XName = "|y^{Z}|";
  else if(theHistName == "PhiStar") XName = "#phi*";

  /********** draw+save pdf*********/
  TCanvas* c1 = new TCanvas("c1", "c1",5,5,650,500);
  covariance_totsum->Draw("colz");
  c1->SetLogx();
  c1->SetLogy();
  c1->SetLogz();
  gStyle->SetOptStat(0);
  covariance_totsum->SetTitle("");
  covariance_totsum->GetXaxis()->SetTitle(XName.Data());
  covariance_totsum->GetXaxis()->SetLabelFont  (   42);
  covariance_totsum->GetXaxis()->SetLabelOffset(0.015);
  covariance_totsum->GetXaxis()->SetLabelSize  (0.030);
  covariance_totsum->GetXaxis()->SetNdivisions (  505);
  covariance_totsum->GetXaxis()->SetTitleFont  (   42);
  covariance_totsum->GetXaxis()->SetTitleOffset( 1.0);
  covariance_totsum->GetXaxis()->SetTitleSize  (0.040);
  covariance_totsum->GetXaxis()->SetTickLength (0.07 );

  covariance_totsum->GetYaxis()->SetTitle(XName.Data());
  covariance_totsum->GetYaxis()->SetLabelFont  (   42);
  covariance_totsum->GetYaxis()->SetLabelOffset(0.015);
  covariance_totsum->GetYaxis()->SetLabelSize  (0.030);
  covariance_totsum->GetYaxis()->SetNdivisions (  505);
  covariance_totsum->GetYaxis()->SetTitleFont  (   42);
  covariance_totsum->GetYaxis()->SetTitleOffset(  1.2);
  covariance_totsum->GetYaxis()->SetTitleSize  (0.040);
  covariance_totsum->GetYaxis()->SetTickLength (0.03 );
  // covariance_totsum->GetZaxis()->SetTitle("(Relative Uncertainty)^{2}");
  //covariance_totsum->GetZaxis()->SetTitleOffset(0.50);

  sprintf(CommandToExec,"mkdir -p plots");
  gSystem->Exec(CommandToExec);  

  TString myOutputFile;
  myOutputFile = Form("plots/covariance_nsel%d_DY%d.pdf",me,DY);
  c1->SaveAs(myOutputFile.Data());
  
  
}
void matrix(TString theHistName = "Pt"){
  for(int i=0;i<=1;i++){
    for(int j=3;j<=3;j++){
      helper_function(i,j,theHistName.Data());
    }
  }
}
