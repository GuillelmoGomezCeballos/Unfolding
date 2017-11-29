#include <TFile.h>
#include <TSystem.h>
#include <TString.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TMath.h>
#include <TLegend.h>
#include <TLatex.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>
#include <fstream>

void readGenevaInputs(bool isDebug = false){

  double theLumi = 35800.0;

  TFile *_file0 = TFile::Open("inputs/Geneva_Histograms_mm.root");
  TFile *_file1 = TFile::Open("inputs/Geneva_Histograms_ee.root");

  const int nBinRap = 12; Float_t xbinsRap[nBinRap+1] = {0.0,0.2,0.4,0.6,0.8,1.0,1.2,1.4,1.6,1.8,2.0,2.2,2.4};

  const int nBinPt = 36; Float_t xbinsPt[nBinPt+1] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,16,18,20,22,25,28,32,37,43,52,65,85,120,160,190,220,250,300,400,500,800,1500};
  TH1D *hDDilPtMM  = new TH1D(Form("hDDilPtMM"),  Form("hDDilPtMM"),  nBinPt, xbinsPt);
  TH1D *hDDilPtEE  = new TH1D(Form("hDDilPtEE"),  Form("hDDilPtEE"),  nBinPt, xbinsPt);
  TGraphAsymmErrors *ZPt_stat_mm = (TGraphAsymmErrors*)_file0->Get(Form("ZPt_stat"));
  TGraphAsymmErrors *ZPt_syst_mm = (TGraphAsymmErrors*)_file0->Get(Form("ZPt_syst"));
  TGraphAsymmErrors *ZPt_stat_ee = (TGraphAsymmErrors*)_file1->Get(Form("ZPt_stat"));
  TGraphAsymmErrors *ZPt_syst_ee = (TGraphAsymmErrors*)_file1->Get(Form("ZPt_syst"));
  if(nBinPt != ZPt_stat_mm->GetN()) return;
  for(int i=0; i <nBinPt; i++) {
   double x1,y1,x2,y2;
   ZPt_stat_mm->GetPoint(i, x1, y1);
   ZPt_syst_mm->GetPoint(i, x2, y2);
   hDDilPtMM->SetBinContent(i+1,y1*theLumi);
   hDDilPtMM->SetBinError(i+1,sqrt(ZPt_stat_mm->GetErrorY(i)*ZPt_stat_mm->GetErrorY(i)+ZPt_syst_mm->GetErrorY(i)*ZPt_syst_mm->GetErrorY(i))*theLumi);
   if(isDebug == true) printf("hDDilPtMM(%2d): %.3f +/- %.3f\n",i+1,hDDilPtMM->GetBinContent(i+1),hDDilPtMM->GetBinError(i+1)/hDDilPtMM->GetBinContent(i+1));  
  }
  if(isDebug == true) printf("TotalSum hDDilPtMM: %f\n",hDDilPtMM->Integral("Width")/theLumi);

  if(nBinPt != ZPt_stat_ee->GetN()) return;
  for(int i=0; i <nBinPt; i++) {
    double x1,y1,x2,y2;
    ZPt_stat_ee->GetPoint(i, x1, y1);
    ZPt_syst_ee->GetPoint(i, x2, y2);
    hDDilPtEE->SetBinContent(i+1,y1*theLumi);
    hDDilPtEE->SetBinError(i+1,sqrt(ZPt_stat_ee->GetErrorY(i)*ZPt_stat_ee->GetErrorY(i)+ZPt_syst_ee->GetErrorY(i)*ZPt_syst_ee->GetErrorY(i))*theLumi);
    if(isDebug == true) printf("hDDilPtEE(%2d): %.3f +/- %.3f\n",i+1,hDDilPtEE->GetBinContent(i+1),hDDilPtEE->GetBinError(i+1)/hDDilPtEE->GetBinContent(i+1));  
  }
  if(isDebug == true) printf("TotalSum hDDilPhiStarEE: %f\n",hDDilPtEE->Integral("Width")/theLumi);

  const int nBinPhiStar = 34; Float_t xbinsPhiStar[nBinPhiStar+1] = {
                                         1e-3, 2e-3, 3e-3, 4e-3, 5e-3, 6e-3, 7e-3, 8e-3, 9e-3,
                                         1e-2, 2e-2, 3e-2, 4e-2, 5e-2, 6e-2, 7e-2, 8e-2, 9e-2,
                                         1e-1, 2e-1, 3e-1, 4e-1, 5e-1, 6e-1, 7e-1, 8e-1, 9e-1,
                                            1,    3,    5,    7,   10,   20,   30,   50};
  TH1D *hDDilPhiStarMM  = new TH1D(Form("hDDilPhiStarMM"),  Form("hDDilPhiStarMM"),  nBinPhiStar, xbinsPhiStar);
  TH1D *hDDilPhiStarEE  = new TH1D(Form("hDDilPhiStarEE"),  Form("hDDilPhiStarEE"),  nBinPhiStar, xbinsPhiStar);
  TGraphAsymmErrors *ZPhiStar_stat_mm = (TGraphAsymmErrors*)_file0->Get(Form("PhiStar_stat"));
  TGraphAsymmErrors *ZPhiStar_syst_mm = (TGraphAsymmErrors*)_file0->Get(Form("PhiStar_syst"));
  TGraphAsymmErrors *ZPhiStar_stat_ee = (TGraphAsymmErrors*)_file1->Get(Form("PhiStar_stat"));
  TGraphAsymmErrors *ZPhiStar_syst_ee = (TGraphAsymmErrors*)_file1->Get(Form("PhiStar_syst"));
  if(nBinPhiStar != ZPhiStar_stat_mm->GetN()) return;
  for(int i=0; i <nBinPhiStar; i++) {
    double x1,y1,x2,y2;
    ZPhiStar_stat_mm->GetPoint(i, x1, y1);
    ZPhiStar_syst_mm->GetPoint(i, x2, y2);
    hDDilPhiStarMM->SetBinContent(i+1,y1*theLumi);
    hDDilPhiStarMM->SetBinError(i+1,sqrt(ZPhiStar_stat_mm->GetErrorY(i)*ZPhiStar_stat_mm->GetErrorY(i)+ZPhiStar_syst_mm->GetErrorY(i)*ZPhiStar_syst_mm->GetErrorY(i))*theLumi);
    if(isDebug == true) printf("hDDilPhiStarMM(%2d): %.3f +/- %.3f\n",i+1,hDDilPhiStarMM->GetBinContent(i+1),hDDilPhiStarMM->GetBinError(i+1)/hDDilPhiStarMM->GetBinContent(i+1));  
  }
  if(isDebug == true) printf("TotalSum hDDilPtEE: %f\n",hDDilPhiStarMM->Integral("Width")/theLumi);

  if(nBinPhiStar != ZPhiStar_stat_ee->GetN()) return;
  for(int i=0; i <nBinPhiStar; i++) {
    double x1,y1,x2,y2;
    ZPhiStar_stat_ee->GetPoint(i, x1, y1);
    ZPhiStar_syst_ee->GetPoint(i, x2, y2);
    hDDilPhiStarEE->SetBinContent(i+1,y1*theLumi);
    hDDilPhiStarEE->SetBinError(i+1,sqrt(ZPhiStar_stat_ee->GetErrorY(i)*ZPhiStar_stat_ee->GetErrorY(i)+ZPhiStar_syst_ee->GetErrorY(i)*ZPhiStar_syst_ee->GetErrorY(i))*theLumi);
    if(isDebug == true) printf("hDDilPhiStarEE(%2d): %.3f +/- %.3f\n",i+1,hDDilPhiStarEE->GetBinContent(i+1),hDDilPhiStarEE->GetBinError(i+1)/hDDilPhiStarEE->GetBinContent(i+1));  
  }
  if(isDebug == true) printf("TotalSum hDDilPhiStarMM: %f\n",hDDilPhiStarEE->Integral("Width")/theLumi);

 char output[200];
 char CommandToExec[300];

 {
 sprintf(output,"histoUnfoldingSystPt_nsel0_dy4_rebin1_default.root"); 
 TFile* outFilePlots = new TFile(output,"recreate");
 outFilePlots->cd();
 hDDilPtMM->Write();
 outFilePlots->Close();
 sprintf(CommandToExec,"cp histoUnfoldingSystPt_nsel0_dy4_rebin1_default.root histoUnfolding_XSRatioSystPt_nsel0_dy4_rebin1_default.root");
 gSystem->Exec(CommandToExec);  
 }

 {
 sprintf(output,"histoUnfoldingSystPt_nsel1_dy4_rebin1_default.root"); 
 TFile* outFilePlots = new TFile(output,"recreate");
 outFilePlots->cd();
 hDDilPtEE->Write();
 outFilePlots->Close();
 sprintf(CommandToExec,"cp histoUnfoldingSystPt_nsel1_dy4_rebin1_default.root histoUnfolding_XSRatioSystPt_nsel1_dy4_rebin1_default.root");
 gSystem->Exec(CommandToExec);  
 }

 {
 sprintf(output,"histoUnfoldingSystPhiStar_nsel0_dy4_rebin1_default.root"); 
 TFile* outFilePlots = new TFile(output,"recreate");
 outFilePlots->cd();
 hDDilPhiStarMM->Write();
 outFilePlots->Close();
 sprintf(CommandToExec,"cp histoUnfoldingSystPhiStar_nsel0_dy4_rebin1_default.root histoUnfolding_XSRatioSystPhiStar_nsel0_dy4_rebin1_default.root");
 gSystem->Exec(CommandToExec);  
 }

 {
 sprintf(output,"histoUnfoldingSystPhiStar_nsel1_dy4_rebin1_default.root"); 
 TFile* outFilePlots = new TFile(output,"recreate");
 outFilePlots->cd();
 hDDilPhiStarEE->Write();
 outFilePlots->Close();
 sprintf(CommandToExec,"cp histoUnfoldingSystPhiStar_nsel1_dy4_rebin1_default.root histoUnfolding_XSRatioSystPhiStar_nsel1_dy4_rebin1_default.root");
 gSystem->Exec(CommandToExec);  
 }

}
