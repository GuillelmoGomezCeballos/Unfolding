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
void helper_function(int me, int DY, TString theHistName, int count, int isNorm=0, TString path = "/afs/cern.ch/user/c/ceballos/public/zpt/outputs/", int reBin = 1){

  char filename[300];

  if (isNorm==0) sprintf(filename,"%s/histoUnfoldingSyst%s_nsel%d_dy%d_rebin%d_default.root",path.Data(),theHistName.Data(),me,DY,reBin);
  else sprintf(filename,"%s/histoUnfolding_XSRatioSyst%s_nsel%d_dy%d_rebin%d_default.root",path.Data(),theHistName.Data(),me,DY,reBin);

  TFile* _file0 = new TFile(Form("%s",filename),  "read"); if(!_file0) {printf("File does not exist\n"); return;}
  printf("Filename: %s\n",filename);

  //const int nGenSyst = 8;
  //const int nEffSyst = 7+480;
  //const int nStaSyst = 72;
  //const int nOthSyst = 2;
  //
  //const int nSyst = nGenSyst+nEffSyst+nStaSyst+nOthSyst;
  //TH1D* histoSyst[nSyst];
  //for(int i=0; i<nSyst; i++) {histoSyst[i] = (TH1D*)_file0->Get(Form("histoSystCov_%d",i));assert(histoSyst[i]);}
  //
  //const int nBinGen = histoSyst[0]->GetNbinsX();
  //Float_t xbinsGen[nBinGen+1];
  //for(int i=0; i<=nBinGen; i++){
  // xbinsGen[i] = histoSyst[0]->GetXaxis()->GetBinLowEdge(i+1);
  //}
  //
  //TH2D* covariance_momres     = new TH2D(Form("covariance_momres_%d",me),     Form("covariance_momres_%d",me),     nBinGen, xbinsGen, nBinGen, xbinsGen);
  //TH2D* covariance_lepeff     = new TH2D(Form("covariance_lepeff_%d",me),     Form("covariance_lepeff_%d",me),     nBinGen, xbinsGen, nBinGen, xbinsGen);
  //TH2D* covariance_lepeffSyst = new TH2D(Form("covariance_lepeffSyst_%d",me), Form("covariance_lepeffSyst_%d",me), nBinGen, xbinsGen, nBinGen, xbinsGen);
  //TH2D* covariance_lepeffStat = new TH2D(Form("covariance_lepeffStat_%d",me), Form("covariance_lepeffStat_%d",me), nBinGen, xbinsGen, nBinGen, xbinsGen);
  //TH2D* covariance_totsum;
  //
  //if (isNorm==0) covariance_totsum     = new TH2D(Form("d%02d-x01-y01",count),     Form("covariance_%s_nsel%d_dy%d",theHistName.Data(),me,DY),nBinGen, xbinsGen, nBinGen, xbinsGen);
  //else covariance_totsum     = new TH2D(Form("d%02d-x01-y01",count),     Form("covariance_XSRatio_%s_nsel%d_dy%d",theHistName.Data(),me,DY),nBinGen, xbinsGen, nBinGen, xbinsGen);

  TH1D* unfold = (TH1D*)_file0->Get("unfold");
  unfold->SetName(Form("d%02d-x01-y01",count+1));
  if (isNorm==0) unfold->SetTitle(Form("unfold_%s_nsel%d_dy%d", theHistName.Data(),me,DY));
  else unfold->SetTitle(Form("unfold_XSRatio_%s_nsel%d_dy%d", theHistName.Data(),me,DY));

  for (int i=1;i<=unfold->GetNbinsX(); i++) {
    double tmpErr=unfold->GetBinError(i);
    unfold->SetBinContent(i, unfold->GetBinContent(i)*unfold->GetBinWidth(i) );
    unfold->SetBinError(i, tmpErr*unfold->GetBinWidth(i));
  }


  //for (int i=1;i<=nBinGen;i++){
  //  for (int j=1;j<=nBinGen;j++){
  //
  //    double sum_momres = histoSyst[1]->GetBinContent(i)*histoSyst[1]->GetBinContent(j)+
  //                        histoSyst[2]->GetBinContent(i)*histoSyst[2]->GetBinContent(j)+
  //                        histoSyst[3]->GetBinContent(i)*histoSyst[3]->GetBinContent(j)+
  //                        histoSyst[4]->GetBinContent(i)*histoSyst[4]->GetBinContent(j);
  //
  //    double sum_lepeff = 0;
  //    for(int k=nGenSyst; k<nGenSyst+nEffSyst; k++) sum_lepeff = sum_lepeff + histoSyst[k] ->GetBinContent(i)*histoSyst[k] ->GetBinContent(j);
  //
  //    double sum_lepeffSyst = 0;
  //    for(int k=nGenSyst; k<nGenSyst+7; k++) sum_lepeffSyst = sum_lepeffSyst + histoSyst[k] ->GetBinContent(i)*histoSyst[k] ->GetBinContent(j);
  //
  //    double sum_lepeffStat = 0;
  //    for(int k=nGenSyst+7; k<nGenSyst+nEffSyst; k++) sum_lepeffStat = sum_lepeffStat + histoSyst[k] ->GetBinContent(i)*histoSyst[k] ->GetBinContent(j);
  //
  //    double sum_totsum = 0.;
  //    for(int k=0; k<nSyst-2; k++) sum_totsum = sum_totsum + histoSyst[k]->GetBinContent(i)*histoSyst[k]->GetBinContent(j);
  //    if(i==j) sum_totsum = sum_totsum + histoSyst[nSyst-2]->GetBinContent(i)*histoSyst[nSyst-2]->GetBinContent(j); // data stat. uncertainty is diagonal only
  //    sum_totsum = sum_totsum + histoSyst[nSyst-1]->GetBinContent(i)*histoSyst[nSyst-1]->GetBinContent(j); // adding lumi
  //                        
  //    covariance_momres    ->SetBinContent(i,j,sum_momres    );
  //    covariance_lepeff    ->SetBinContent(i,j,sum_lepeff    );
  //    covariance_lepeffSyst->SetBinContent(i,j,sum_lepeffSyst);
  //    covariance_lepeffStat->SetBinContent(i,j,sum_lepeffStat);
  //    covariance_totsum    ->SetBinContent(i,j,sum_totsum    );
  //  }
  //}

  //char CommandToExec[300];
  //sprintf(CommandToExec,"mkdir -p output_root");
  //gSystem->Exec(CommandToExec);  

  TString XName = "p_{TZ}";
  if     (theHistName == "Rap") XName = "|y^{Z}|";
  else if(theHistName == "PhiStar") XName = "\\phi^{*}";

  //covariance_totsum->GetXaxis()->SetTitle(Form("$%s$",XName.Data()));
  //covariance_totsum->GetYaxis()->SetTitle(Form("$%s$",XName.Data()));
  //covariance_totsum->GetZaxis()->SetTitle(Form("$\\sigma(%s,%s)$",XName.Data(), XName.Data()));
  unfold->GetXaxis()->SetTitle(Form("$%s$",XName.Data()));
  unfold->GetYaxis()->SetTitle(Form("$d\\sigma/d%s$", XName.Data()));

  if (isNorm==0) unfold->Scale(1.0/35900.0);
  else unfold->Scale(1.0/unfold->Integral());

  char outputLimits[200];
  sprintf(outputLimits,"forRIVET4/matrix%02d.root",count);
  TFile* outFileLimits = new TFile(outputLimits,"recreate");
  outFileLimits->cd();
  //covariance_totsum->Write();  
  unfold->Write();

  outFileLimits->Close();
  
  
}
void matrixForRIVET(){


  TString histNames[8] = {"Pt","PhiStar", "Rap", "PtRap0", "PtRap1", "PtRap2", "PtRap3", "PtRap4"};

  int gc2=33;
  int gc=1;

  for (int x=0; x<8; x++) {
    for(int i=0;i<=1;i++){
      for(int j=3;j<=3;j++){
	helper_function(i,j,histNames[x].Data(), gc, 0);
	helper_function(i,j,histNames[x].Data(), gc2, 1);
	gc+=2; gc2+=2;
      }
    }
  }

}
