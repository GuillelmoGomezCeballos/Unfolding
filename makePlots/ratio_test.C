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
    histo->GetXaxis()->SetLabelSize  (0.08);
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
  histo->GetYaxis()->SetTitleOffset(  0.5);
  histo->GetYaxis()->SetTitleSize  (0.110);
  histo->GetYaxis()->SetTickLength (0.03 );

  histo->SetLineColor  (kBlack);
  histo->SetMarkerStyle(kFullCircle);
}

void ratio_test(int nsel = 0, int ReBin = 1, TString XTitle = "N_{jets}", TString units = "", TString plotName = "histo_nice.root", TString outputName = "njets",
                bool isLogY = false, bool isLogX = false, TString keyLabel0 = "Pt", TString keyLabel1 = "MM") {

  gInterpreter->ExecuteMacro("GoodStyle.C");
  //gROOT->LoadMacro("StandardPlotUnfolding.C");
  gStyle->SetOptStat(0);

  int me=0;
  if (strncmp(keyLabel1.Data(),"EE",2)==0){me=1;}

  char filename1[300];
  char filename2[300];
  char filename3[300];
  sprintf(filename1,"_nsel%d_dy3_rebin%d_default.root",me,ReBin);
  sprintf(filename2,"_nsel%d_dy0_rebin%d_default.root",me,ReBin);
  sprintf(filename3,"_nsel%d_dy2_rebin%d_default.root",me,ReBin);
  TString plotName2=plotName;
  TString plotName3=plotName;
  plotName.Append(filename1);
  TFile* file1 = new TFile(plotName, "read");  if(!file1) {printf("File %s does not exist\n",plotName.Data()); return;}
  plotName2=plotName2.Append(filename2);
  plotName3=plotName3.Append(filename3);;

  printf("%s\n",plotName.Data());

  TH1D* hData;
  TH1D* hPred1;
  TH1D* hPred2;
  TH1D* hPred3;

  if     (nsel == 0){
    printf("Unfolding style plots\n");
    hData  = (TH1D*)file1->Get(Form("unfold"));
    hPred1 = (TH1D*)file1->Get(Form("hDDil%s%s",keyLabel0.Data(),keyLabel1.Data()));
  }
  else {
    return;
  }

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
  pad1->cd();
  gStyle->SetOptStat(0);

  //CMS_lumi( pad1, 4, 11 );

  if(isLogX == true) pad1->SetLogx();

  TH1D* hNum = (TH1D*) hData->Clone(); hNum->Reset();
  TH1D* hDen = (TH1D*) hData->Clone(); hDen->Reset();

  TH1D* hRatio = (TH1D*) hData->Clone(); hRatio->Reset();
  TH1D* hBand = (TH1D*) hData->Clone(); hBand->Reset();

  hNum->Add(hPred1);
  hDen->Add(hData);

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
  atributes(hRatio,XTitle.Data(),"aMC@NLO/Data",units.Data());

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
  eraselabel(pad1,hData->GetXaxis()->GetLabelSize());
 
  TLegend* leg = new TLegend(0.20,0.60,0.40,0.90);                                                    
  leg ->SetFillStyle(0);
  leg ->SetFillColor(kWhite);
  leg ->SetBorderSize(0);
  leg->SetTextSize(0.0);                                                                         
  leg->AddEntry(hBand,"Theory prediction","f");
  leg->AddEntry(hRatio,"Experimental data","lpe");
  leg->Draw();

 ///////////////////////////////////////////////////  ///////////////////////////////////////////////////
    

  TFile *file2 = new TFile(plotName2, "read");  if(!file2) {printf("File %s does not exist\n",plotName.Data()); return;}
  hPred2 = (TH1D*)file2->Get(Form("hDDil%s%s"    ,keyLabel0.Data(),keyLabel1.Data()));

  pad2->cd(); 
  if(isLogX == true) pad2->SetLogx();
  hNum = (TH1D*) hData->Clone(); hNum->Reset();
  hDen = (TH1D*) hData->Clone(); hDen->Reset();

  hRatio = (TH1D*) hData->Clone(); hRatio->Reset();
  hBand = (TH1D*) hData->Clone(); hBand->Reset();

  hNum->Add(hPred2);
  hDen->Add(hData);

  for(int i=1; i<=hNum->GetNbinsX(); i++){
      pull = 1.0; pullerr = 0.0;
      if(hNum->GetBinContent(i) > 0 && hDen->GetBinContent(i) > 0){
        pull = (hNum->GetBinContent(i)/hDen->GetBinContent(i));
	pullerr = pull*hDen->GetBinError(i)/hDen->GetBinContent(i);
      }
      else {
        printf("0 events in %d\n",i);
      }
      hRatio->SetBinContent(i,pull);
      hRatio->SetBinError(i,pullerr);
      hBand->SetBinContent(i,1);
      hBand->SetBinError  (i,hNum->GetBinError(i)/hNum->GetBinContent(i)); 
  }
  units = units.ReplaceAll("BIN","");
  atributes(hRatio,XTitle.Data(),"MADGRAPH/Data",units.Data());
  hRatio->Draw("e");
  hBand->SetFillColor(12);
  hBand->SetFillStyle(3003);
  hBand->SetMarkerSize(0);
  hBand->SetLineWidth(0);
  hBand->Draw("E2same");
 
  // Draw a line throgh y=0
  theLines[0]=1.0;theLines[1]=0.5;
  baseline = new TLine(hRatio->GetXaxis()->GetXmin(), theLines[0],
                              hRatio->GetXaxis()->GetXmax(), theLines[0]);
  baseline->SetLineStyle(kDashed);
  baseline->Draw();
  // Set the y-axis range symmetric around y=0
  dy = TMath::Max(TMath::Abs(hRatio->GetMaximum()),
                           TMath::Abs(hRatio->GetMinimum())) + theLines[1];
  hRatio->GetYaxis()->SetRangeUser(0.601,1.399);
  hRatio->GetYaxis()->CenterTitle();
  eraselabel(pad1,hData->GetXaxis()->GetLabelSize());

  /*  hTotalDivision->Clear();
  hTotalDivision->Reset();
  hDataDivision->Clear();
  hDataDivision->Reset();
  hRatio->Clear();
  hRatio->Reset();
  hBand->Clear();
  hBand->Reset();*/
  ///////////////////////////////////////////////////  ///////////////////////////////////////////////////                      

  TFile *file3 = new TFile(plotName3, "read");  if(!file3) {printf("File %s does not exist\n",plotName.Data()); return;}
  hPred3     = (TH1D*)file3->Get(Form("hDDil%s%s"    ,keyLabel0.Data(),keyLabel1.Data()));

  pad3->cd();
  if(isLogX == true) pad3->SetLogx();
  hNum = (TH1D*) hData->Clone(); hNum->Reset();
  hDen = (TH1D*) hData->Clone(); hDen->Reset();

  hRatio = (TH1D*) hData->Clone(); hRatio->Reset();
  hBand = (TH1D*) hData->Clone(); hBand->Reset();

  hNum->Add(hPred3);
  hDen->Add(hData);

  for(int i=1; i<=hNum->GetNbinsX(); i++){
      pull = 1.0; pullerr = 0.0;
      if(hNum->GetBinContent(i) > 0 && hDen->GetBinContent(i) > 0){
        pull = (hNum->GetBinContent(i)/hDen->GetBinContent(i));
	pullerr = pull*hDen->GetBinError(i)/hDen->GetBinContent(i);
      }
      else {
        printf("0 events in %d\n",i);
      }
      hRatio->SetBinContent(i,pull);
      hRatio->SetBinError(i,pullerr);
      hBand->SetBinContent(i,1);
      hBand->SetBinError  (i,hNum->GetBinError(i)/hNum->GetBinContent(i)); 
  }
  units = units.ReplaceAll("BIN","");
  atributes(hRatio,XTitle.Data(),"POWHEG/Data",units.Data());
  hRatio->Draw("e");
  hBand->SetFillColor(12);
  hBand->SetFillStyle(3003);
  hBand->SetMarkerSize(0);
  hBand->SetLineWidth(0);
  hBand->Draw("E2same");
 
  // Draw a line throgh y=0
  theLines[0]=1.0;theLines[1]=0.5;
  baseline = new TLine(hRatio->GetXaxis()->GetXmin(), theLines[0],
                              hRatio->GetXaxis()->GetXmax(), theLines[0]);
  baseline->SetLineStyle(kDashed);
  baseline->Draw();
  // Set the y-axis range symmetric around y=0
  dy = TMath::Max(TMath::Abs(hRatio->GetMaximum()),
                           TMath::Abs(hRatio->GetMinimum())) + theLines[1];
  hRatio->GetYaxis()->SetRangeUser(0.601,1.399);
  hRatio->GetYaxis()->CenterTitle();
  eraselabel(pad1,hData->GetXaxis()->GetLabelSize());
  

  ///////////////////////////////////////////////////  ///////////////////////////////////////////////////

  printf("Total yields: %f - %f %f %f\n", hData->GetSumOfWeights(),hPred1->GetSumOfWeights(),hPred2->GetSumOfWeights(),hPred3->GetSumOfWeights());

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
