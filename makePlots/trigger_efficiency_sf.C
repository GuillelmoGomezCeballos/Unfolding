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

bool isDebug = false;

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
    //histo->GetXaxis()->SetLabelOffset(0.01);
    histo->GetXaxis()->SetTitleOffset(  1.2);
    //histo->GetXaxis()->SetLabelSize  (0.10);
    //histo->GetXaxis()->SetTitleSize  (0.09);
  } else {
    histo->GetXaxis()->SetTitle(Form("%s [%s]",xtitle.Data(),units.Data()));
    //histo->GetXaxis()->SetLabelOffset(0.00);
    histo->GetXaxis()->SetTitleOffset(  1.2);
    //histo->GetXaxis()->SetLabelSize  (0.08);
    //histo->GetXaxis()->SetTitleSize  (0.075);
  }
  //histo->GetXaxis()->SetLabelFont  (   42);
  //histo->GetXaxis()->SetNdivisions (  505);
  //histo->GetXaxis()->SetTitleFont  (   42);
  //histo->GetXaxis()->SetTickLength (0.07 );

  histo->GetYaxis()->SetTitle(ytitle.Data());
  //histo->GetYaxis()->SetLabelFont  (   42);
  //histo->GetYaxis()->SetLabelOffset(0.015);
  //histo->GetYaxis()->SetLabelSize  (0.120);
  //histo->GetYaxis()->SetNdivisions (  505);
  //histo->GetYaxis()->SetTitleFont  (   42);
  histo->GetYaxis()->SetTitleOffset(  1.5);
  //histo->GetYaxis()->SetTitleSize  (0.080);
  //histo->GetYaxis()->SetTickLength (0.03 );

  histo->SetLineColor  (kBlack);
  histo->SetMarkerStyle(kFullCircle);
}

void trigger_efficiency_sf(int ReBin = 1, TString XTitle = "N_{jets}", TString units = "", 
                TString plotName1 = "inputs_trigger/histoDY3zll_16.root", 
                TString plotName2 = "inputs_trigger/histoDY2zll_16.root", 
                TString outputName = "",
                bool isLogY = false, bool isLogX = false) {

  gInterpreter->ExecuteMacro("GoodStyle.C");
  //gROOT->LoadMacro("StandardPlotUnfolding.C");
  gStyle->SetOptStat(0);

  TFile* file1 = new TFile(plotName1.Data(), "read");  if(!file1) {printf("File %s does not exist\n",plotName1.Data()); return;}
  TFile* file2 = new TFile(plotName2.Data(), "read");  if(!file2) {printf("File %s does not exist\n",plotName2.Data()); return;}

  TH1D* hNum  = (TH1D*)file1->Get(Form("histo2"));
  TH1D* hDen  = (TH1D*)file2->Get(Form("histo2"));

  double pull; 
  double pullerr;

  TCanvas* c1 = new TCanvas("c1", "c1",5,5,600,600);

  c1->SetBottomMargin(0.1);
  c1->cd();
  TPad* pad1 = new TPad("pad1", "pad1",0.00,0.000,1.00,1.000);
  CMS_lumi( c1, 4, 11 );

  pad1->SetTopMargin(0.05);
  pad1->SetBottomMargin(0.1);
  pad1->Draw();

  /////////////////////////////////////////////PAD1///////////////////////////////////////////////////////////////
  pad1->cd();
  gStyle->SetOptStat(0);

  //CMS_lumi( pad1, 4, 11 );

  if(isLogX == true) pad1->SetLogx();

  TH1D* hRatio = (TH1D*)hNum->Clone();  hRatio->Reset();

  for(int i=1; i<=hNum->GetNbinsX(); i++){
      pull = 1.0; pullerr = 0.0;
      if(hNum->GetBinContent(i) > 0 && hDen->GetBinContent(i) > 0){
        pull = (hNum->GetBinContent(i)/hDen->GetBinContent(i));
	pullerr = TMath::Abs(pull-1.0)*0.2;
      }
      else {
        printf("0 events in %d\n",i);
      }
      if(isDebug) printf("ratio(%2d): %.3f +/- %.3f\n",i,pull,pullerr);
      hRatio->SetBinContent(i,pull);
      hRatio->SetBinError(i,pullerr);
  }
  units = units.ReplaceAll("BIN","");
  atributes(hRatio,XTitle.Data(),"Efficiency",units.Data());

  hRatio->Draw("e");
 
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
  hRatio->GetYaxis()->SetRangeUser(0.501,1.009);
  hRatio->GetYaxis()->CenterTitle();
  eraselabel(pad1,hNum->GetXaxis()->GetLabelSize());
 
  TLegend* leg = new TLegend(0.20,0.60,0.40,0.70);                                                    
  leg ->SetFillStyle(0);
  leg ->SetFillColor(kWhite);
  leg ->SetBorderSize(0);
  leg->SetTextSize(0.0);                                                                         
  leg->AddEntry(hRatio,"Scale Factor","lpe");
  leg->Draw();

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
