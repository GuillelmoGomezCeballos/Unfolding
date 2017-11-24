#include "TROOT.h"
#include "TInterpreter.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TH1F.h"
#include "TStyle.h"
#include "TPad.h"
#include "Math/QuantFuncMathCore.h"
#include "TMath.h"
#include "TGraphAsymmErrors.h"
#include "TSystem.h"
#include "TLegend.h"
#include <iostream>
#include "CMS_lumi.C"

bool isDebug = true;

void eraselabel(TPad *p,Double_t h){
  p->cd();
  TPad *pe = new TPad("pe","pe",0.02,0,p->GetLeftMargin(),h);	   
  pe->Draw();
  pe->SetFillColor(p->GetFillColor()); 
  pe->SetBorderMode(0);
}

void atributes(TH1D *histo, TString xtitle = "", TString ytitle = "Fraction", TString units = ""){

  histo->SetTitle("");
  //histo->SetMarkerStyle(20);
  //histo->SetMarkerSize(0.8);
  //histo->SetLineWidth(4);
  if(strcmp(units.Data(),"")==0){
    histo->GetXaxis()->SetTitle(xtitle.Data());
    histo->GetXaxis()->SetLabelOffset(0.01);
    histo->GetXaxis()->SetTitleOffset(  0.8);
    histo->GetXaxis()->SetLabelSize  (0.10);
    histo->GetXaxis()->SetTitleSize  (0.11);
  } else {
    histo->GetXaxis()->SetTitle(Form("%s [%s]",xtitle.Data(),units.Data()));
    histo->GetXaxis()->SetLabelOffset(0.00);
    histo->GetXaxis()->SetTitleOffset(  1);
    histo->GetXaxis()->SetLabelSize  (0.04);
    histo->GetXaxis()->SetTitleSize  (0.095);
  }
  histo->GetXaxis()->SetLabelFont  (   42);
  histo->GetXaxis()->SetNdivisions (  505);
  histo->GetXaxis()->SetTitleFont  (   42);
  histo->GetXaxis()->SetTickLength (0.07 );

  histo->GetYaxis()->SetTitle(ytitle.Data());
  histo->GetYaxis()->SetLabelFont  (   42);
  histo->GetYaxis()->SetLabelOffset(0.015);
  histo->GetYaxis()->SetLabelSize  (0.120);
  histo->GetYaxis()->SetNdivisions (  505);
  histo->GetYaxis()->SetTitleFont  (   42);
  histo->GetYaxis()->SetTitleOffset( 0.65);
  histo->GetYaxis()->SetTitleSize  (0.110);
  histo->GetYaxis()->SetTickLength (0.03 );

  histo->SetLineColor  (kBlack);
  histo->SetMarkerStyle(kFullCircle);
}

void double_ratio_test(int nsel = 0, int ReBin = 1, TString XTitle = "N_{jets}", TString units = "", TString plotName = "histo_nice.root", TString outputName = "njets",
                bool isLogY = false, bool isLogX = false, TString keyLabel0 = "Pt") {

  gInterpreter->ExecuteMacro("GoodStyle.C");
  //gROOT->LoadMacro("StandardPlotUnfolding.C");
  gStyle->SetOptStat(0);

  char filename10[300];
  char filename20[300];
  char filename30[300];
  char filename11[300];
  char filename21[300];
  char filename31[300];
  sprintf(filename10,"_nsel%d_dy3_rebin%d_default.root",0,ReBin);
  sprintf(filename20,"_nsel%d_dy0_rebin%d_default.root",0,ReBin);
  sprintf(filename30,"_nsel%d_dy2_rebin%d_default.root",0,ReBin);
  sprintf(filename11,"_nsel%d_dy3_rebin%d_default.root",1,ReBin);
  sprintf(filename21,"_nsel%d_dy0_rebin%d_default.root",1,ReBin);
  sprintf(filename31,"_nsel%d_dy2_rebin%d_default.root",1,ReBin);
  TString plotName10=plotName;
  TString plotName20=plotName;
  TString plotName30=plotName;
  TString plotName11=plotName;
  TString plotName21=plotName;
  TString plotName31=plotName;
  plotName10=plotName10.Append(filename10);
  plotName20=plotName20.Append(filename20);
  plotName30=plotName30.Append(filename30);;
  plotName11=plotName11.Append(filename11);
  plotName21=plotName21.Append(filename21);
  plotName31=plotName31.Append(filename31);;

  printf("%s\n",plotName10.Data());
  TFile* file10 = new TFile(plotName10, "read");  if(!file10) {printf("File %s does not exist\n",plotName10.Data()); return;}
  TFile* file20 = new TFile(plotName20, "read");  if(!file20) {printf("File %s does not exist\n",plotName20.Data()); return;}
  TFile* file30 = new TFile(plotName30, "read");  if(!file30) {printf("File %s does not exist\n",plotName30.Data()); return;}
  TFile* file11 = new TFile(plotName11, "read");  if(!file11) {printf("File %s does not exist\n",plotName11.Data()); return;}
  TFile* file21 = new TFile(plotName21, "read");  if(!file21) {printf("File %s does not exist\n",plotName21.Data()); return;}
  TFile* file31 = new TFile(plotName31, "read");  if(!file31) {printf("File %s does not exist\n",plotName31.Data()); return;}

  TH1D* hData0  = (TH1D*)file10->Get(Form("unfoldNoLumi"));
  TH1D* hPred10 = (TH1D*)file10->Get(Form("hDDil%s%s_Stat",keyLabel0.Data(),"MM"));
  TH1D* hPred20 = (TH1D*)file20->Get(Form("hDDil%s%s_Stat",keyLabel0.Data(),"MM"));
  TH1D* hPred30 = (TH1D*)file30->Get(Form("hDDil%s%s_Stat",keyLabel0.Data(),"MM"));
  TH1D* hData1  = (TH1D*)file11->Get(Form("unfoldNoLumi"))		   ;
  TH1D* hPred11 = (TH1D*)file11->Get(Form("hDDil%s%s_Stat",keyLabel0.Data(),"EE"));
  TH1D* hPred21 = (TH1D*)file21->Get(Form("hDDil%s%s_Stat",keyLabel0.Data(),"EE"));
  TH1D* hPred31 = (TH1D*)file31->Get(Form("hDDil%s%s_Stat",keyLabel0.Data(),"EE"));

  printf("Total yields mm: %f - %f %f %f\n", hData0->GetSumOfWeights(),hPred10->GetSumOfWeights(),hPred20->GetSumOfWeights(),hPred30->GetSumOfWeights());
  printf("Total yields ee: %f - %f %f %f\n", hData1->GetSumOfWeights(),hPred11->GetSumOfWeights(),hPred21->GetSumOfWeights(),hPred31->GetSumOfWeights());

  hPred10->Divide(hPred11);
  hPred20->Divide(hPred21);
  hPred30->Divide(hPred31);
  hData0 ->Divide(hData1);

  double pull; 
  double pullerr;

  TCanvas* c1 = new TCanvas("c1", "c1",5,5,600,600);

  c1->SetBottomMargin(0.1);
  c1->cd();
  TPad* pad1 = new TPad("pad1", "pad1",0.00,0.655,1.00,1.000);
  TPad* pad2 = new TPad("pad2", "pad2",0.00,0.355,1.00,0.645);
  TPad* pad3 = new TPad("pad3", "pad3",0.00,0.000,1.00,0.345);
  CMS_lumi( c1, 4, 11 );

  pad1->SetBottomMargin(0);
  pad2->SetTopMargin(0);
  pad2->SetBottomMargin(0);
  pad3->SetTopMargin(0);
  pad1->Draw();
  pad2->Draw();
  pad3->Draw();

  /////////////////////////////////////////////PAD1///////////////////////////////////////////////////////////////
  {
  pad1->cd();
  gStyle->SetOptStat(0);

  if(isLogX == true) pad1->SetLogx();

  TH1D* hNum = (TH1D*) hData0->Clone(); hNum->Reset();
  TH1D* hDen = (TH1D*) hData0->Clone(); hDen->Reset();

  TH1D* hRatio = (TH1D*) hData0->Clone(); hRatio->Reset();
  TH1D* hBand  = (TH1D*) hData0->Clone(); hBand->Reset();

  hNum->Add(hPred10);
  hDen->Add(hData0);

  for(int i=1; i<=hNum->GetNbinsX(); i++){
      pull = 1.0; pullerr = 0.0;
      if(hNum->GetBinContent(i) > 0 && hDen->GetBinContent(i) > 0){
        pull = (hNum->GetBinContent(i)/hDen->GetBinContent(i));
	pullerr = pull*hDen->GetBinError(i)/hDen->GetBinContent(i);
      }
      else {
        printf("0 events in %d\n",i);
      }
      if(isDebug) printf("ratio(%2d): data/pred = %.3f +/- %.3f predUnc: %.3f\n",i,pull,pullerr,hNum->GetBinError(i)/hNum->GetBinContent(i));
      hRatio->SetBinContent(i,pull);
      hRatio->SetBinError(i,pullerr);
      hBand->SetBinContent(i,1);
      hBand->SetBinError  (i,hNum->GetBinError(i)/hNum->GetBinContent(i)); 
  }
  units = units.ReplaceAll("BIN","");
  atributes(hRatio,XTitle.Data(),"#frac{(#mu#mu/ee)^{aMC@NLO}}{(#mu#mu/ee)^{Data}}",units.Data());

  hRatio->Draw("e");
  hBand->SetFillColor(12);
  hBand->SetFillStyle(3003);
  hBand->SetMarkerSize(0);
  hBand->SetLineWidth(0);
  hBand->Draw("E2same");
 
  // Draw a line throgh y=0
  double theLines[2] = {1.0, 0.5};
  TLine* baseline = new TLine(hRatio->GetXaxis()->GetXmin(), theLines[0],
                              hRatio->GetXaxis()->GetXmax(), theLines[0]);
  baseline->SetLineStyle(kDashed);
  baseline->Draw();
  // Set the y-axis range symmetric around y=0
  Double_t dy = TMath::Max(TMath::Abs(hRatio->GetMaximum()),
                           TMath::Abs(hRatio->GetMinimum())) + theLines[1];
  // Double_t dy = TMath::Max(TMath::Abs(TMath::Abs(hRatio->GetMaximum())-1),TMath::Abs(TMath::Abs(hRatio->GetMinimum()))-1);
  hRatio->GetYaxis()->SetRangeUser(0.601,1.399);
  hRatio->GetYaxis()->CenterTitle();
  eraselabel(pad1,hData0->GetXaxis()->GetLabelSize());
 
  TLegend* leg = new TLegend(0.20,0.60,0.40,0.90);                                                    
  leg ->SetFillStyle(0);
  leg ->SetFillColor(kWhite);
  leg ->SetBorderSize(0);
  leg->SetTextSize(0.0);                                                                         
  leg->AddEntry(hBand,"Theory prediction","f");
  leg->AddEntry(hRatio,"Experimental data","lpe");
  leg->Draw();
  }

  /////////////////////////////////////////////PAD2///////////////////////////////////////////////////////////////
  {
  pad2->cd();
  gStyle->SetOptStat(0);

  if(isLogX == true) pad2->SetLogx();

  TH1D* hNum = (TH1D*) hData0->Clone(); hNum->Reset();
  TH1D* hDen = (TH1D*) hData0->Clone(); hDen->Reset();

  TH1D* hRatio = (TH1D*) hData0->Clone(); hRatio->Reset();
  TH1D* hBand  = (TH1D*) hData0->Clone(); hBand->Reset();

  hNum->Add(hPred20);
  hDen->Add(hData0);

  for(int i=1; i<=hNum->GetNbinsX(); i++){
      pull = 1.0; pullerr = 0.0;
      if(hNum->GetBinContent(i) > 0 && hDen->GetBinContent(i) > 0){
        pull = (hNum->GetBinContent(i)/hDen->GetBinContent(i));
	pullerr = pull*hDen->GetBinError(i)/hDen->GetBinContent(i);
      }
      else {
        printf("0 events in %d\n",i);
      }
      if(isDebug) printf("ratio(%2d): data/pred = %.3f +/- %.3f predUnc: %.3f\n",i,pull,pullerr,hNum->GetBinError(i)/hNum->GetBinContent(i));
      hRatio->SetBinContent(i,pull);
      hRatio->SetBinError(i,pullerr);
      hBand->SetBinContent(i,1);
      hBand->SetBinError  (i,hNum->GetBinError(i)/hNum->GetBinContent(i)); 
  }
  units = units.ReplaceAll("BIN","");
  atributes(hRatio,XTitle.Data(),"#frac{(#mu#mu/ee)^{MADGRAPH}}{(#mu#mu/ee)^{Data}}",units.Data());

  hRatio->Draw("e");
  hBand->SetFillColor(12);
  hBand->SetFillStyle(3003);
  hBand->SetMarkerSize(0);
  hBand->SetLineWidth(0);
  hBand->Draw("E2same");
 
  // Draw a line throgh y=0
  double theLines[2] = {1.0, 0.5};
  TLine* baseline = new TLine(hRatio->GetXaxis()->GetXmin(), theLines[0],
                              hRatio->GetXaxis()->GetXmax(), theLines[0]);
  baseline->SetLineStyle(kDashed);
  baseline->Draw();
  // Set the y-axis range symmetric around y=0
  Double_t dy = TMath::Max(TMath::Abs(hRatio->GetMaximum()),
                           TMath::Abs(hRatio->GetMinimum())) + theLines[1];
  // Double_t dy = TMath::Max(TMath::Abs(TMath::Abs(hRatio->GetMaximum())-1),TMath::Abs(TMath::Abs(hRatio->GetMinimum()))-1);
  hRatio->GetYaxis()->SetRangeUser(0.601,1.399);
  hRatio->GetYaxis()->CenterTitle();
  eraselabel(pad2,hData0->GetXaxis()->GetLabelSize());
  }
 
  /////////////////////////////////////////////PAD3///////////////////////////////////////////////////////////////
  {
  pad3->cd();
  gStyle->SetOptStat(0);

  if(isLogX == true) pad3->SetLogx();

  TH1D* hNum = (TH1D*) hData0->Clone(); hNum->Reset();
  TH1D* hDen = (TH1D*) hData0->Clone(); hDen->Reset();

  TH1D* hRatio = (TH1D*) hData0->Clone(); hRatio->Reset();
  TH1D* hBand  = (TH1D*) hData0->Clone(); hBand->Reset();

  hNum->Add(hPred30);
  hDen->Add(hData0);

  for(int i=1; i<=hNum->GetNbinsX(); i++){
      pull = 1.0; pullerr = 0.0;
      if(hNum->GetBinContent(i) > 0 && hDen->GetBinContent(i) > 0){
        pull = (hNum->GetBinContent(i)/hDen->GetBinContent(i));
	pullerr = pull*hDen->GetBinError(i)/hDen->GetBinContent(i);
      }
      else {
        printf("0 events in %d\n",i);
      }
      if(isDebug) printf("ratio(%2d): data/pred = %.3f +/- %.3f predUnc: %.3f\n",i,pull,pullerr,hNum->GetBinError(i)/hNum->GetBinContent(i));
      hRatio->SetBinContent(i,pull);
      hRatio->SetBinError(i,pullerr);
      hBand->SetBinContent(i,1);
      hBand->SetBinError  (i,hNum->GetBinError(i)/hNum->GetBinContent(i)); 
  }
  units = units.ReplaceAll("BIN","");
  atributes(hRatio,XTitle.Data(),"#frac{(#mu#mu/ee)^{POWHEG}}{(#mu#mu/ee)^{Data}}",units.Data());

  hRatio->Draw("e");
  hBand->SetFillColor(12);
  hBand->SetFillStyle(3003);
  hBand->SetMarkerSize(0);
  hBand->SetLineWidth(0);
  hBand->Draw("E2same");
 
  // Draw a line throgh y=0
  double theLines[2] = {1.0, 0.5};
  TLine* baseline = new TLine(hRatio->GetXaxis()->GetXmin(), theLines[0],
                              hRatio->GetXaxis()->GetXmax(), theLines[0]);
  baseline->SetLineStyle(kDashed);
  baseline->Draw();
  // Set the y-axis range symmetric around y=0
  Double_t dy = TMath::Max(TMath::Abs(hRatio->GetMaximum()),
                           TMath::Abs(hRatio->GetMinimum())) + theLines[1];
  // Double_t dy = TMath::Max(TMath::Abs(TMath::Abs(hRatio->GetMaximum())-1),TMath::Abs(TMath::Abs(hRatio->GetMinimum()))-1);
  hRatio->GetYaxis()->SetRangeUser(0.601,1.399);
  hRatio->GetYaxis()->CenterTitle();
  eraselabel(pad3,hData0->GetXaxis()->GetLabelSize());
  } 

  char CommandToExec[300];
  sprintf(CommandToExec,"mkdir -p plots");
  gSystem->Exec(CommandToExec);  

  if(strcmp(outputName.Data(),"") != 0){
    TString myOutputFile;
    myOutputFile = Form("plots/%s.eps",outputName.Data());
    //c1->SaveAs(myOutputFile.Data());
    myOutputFile = Form("plots/%s.png",outputName.Data());
    c1->SaveAs(myOutputFile.Data());
    myOutputFile = Form("plots/%s.pdf",outputName.Data());
    c1->SaveAs(myOutputFile.Data());
  }

}
