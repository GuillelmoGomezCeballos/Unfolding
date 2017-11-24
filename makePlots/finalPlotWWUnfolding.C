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
#include "TTree.h"

// This can be done via a root file late on
const double totalXSUnc = 0.07165385;

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
  } else {
    histo->GetXaxis()->SetTitle(Form("%s [%s]",xtitle.Data(),units.Data()));
  }
  histo->GetXaxis()->SetLabelFont  (   42);
  histo->GetXaxis()->SetLabelOffset(0.015);
  histo->GetXaxis()->SetLabelSize  (0.140);
  histo->GetXaxis()->SetNdivisions (  505);
  histo->GetXaxis()->SetTitleFont  (   42);
  histo->GetXaxis()->SetTitleOffset( 0.95);
  histo->GetXaxis()->SetTitleSize  (0.140);
  histo->GetXaxis()->SetTickLength (0.07 );

  histo->GetYaxis()->SetTitle(ytitle.Data());
  histo->GetYaxis()->SetLabelFont  (   42);
  histo->GetYaxis()->SetLabelOffset(0.015);
  histo->GetYaxis()->SetLabelSize  (0.120);
  histo->GetYaxis()->SetNdivisions (  505);
  histo->GetYaxis()->SetTitleFont  (   42);
  histo->GetYaxis()->SetTitleOffset(  0.5);
  histo->GetYaxis()->SetTitleSize  (0.120);
  histo->GetYaxis()->SetTickLength (0.03 );

  histo->SetLineColor  (kBlack);
  histo->SetMarkerStyle(kFullCircle);
}

void finalPlotWWUnfolding(
                TString XTitle = "m_{ll}", TString units = "GeV", 
                TString plotName = "../../cards/cards_ww/0/output_fits/higgsCombineww_mll.MultiDimFit.mH120.root", 
                TString outputName = "unf_ww_mll", bool isLogY = false, 
                TString keyLabel0 = "MLL", bool isNormalized = false) {

  gInterpreter->ExecuteMacro("PaperStyle.C");
  gStyle->SetOptStat(0);

  bool isDebug = true;

  double TotalLumi = 1.0;
  double normalization[2];
  
  double theR[9];
  double theRDown[9];
  double theRUp[9];

  TFile *_fileGenWW = TFile::Open("/afs/cern.ch/work/c/ceballos/public/samples/panda/v_005_0/genWW.root");

  TFile *_file0 = TFile::Open(plotName.Data());
  TTree* theTree = nullptr;
  _file0->GetObject("limit",theTree);

  float r_s0 = -999.; theTree->SetBranchAddress( "r_s0", &r_s0);     
  float r_s1 = -999.; theTree->SetBranchAddress( "r_s1", &r_s1);     
  float r_s2 = -999.; theTree->SetBranchAddress( "r_s2", &r_s2);     
  float r_s3 = -999.; theTree->SetBranchAddress( "r_s3", &r_s3);     
  float r_s4 = -999.; theTree->SetBranchAddress( "r_s4", &r_s4);     
  float r_s5 = -999.; theTree->SetBranchAddress( "r_s5", &r_s5);     
  float r_s6 = -999.; theTree->SetBranchAddress( "r_s6", &r_s6);     
  float r_s7 = -999.; theTree->SetBranchAddress( "r_s7", &r_s7);     
  float r_s8 = -999.; theTree->SetBranchAddress( "r_s8", &r_s8);     

  auto nevent = theTree->GetEntries();
  for (Int_t i=0;i<nevent;i++) {
     theTree->GetEntry(i);
     if      (i==0){
       theR[0] = r_s0;
       theR[1] = r_s1;
       theR[2] = r_s2;
       theR[3] = r_s3;
       theR[4] = r_s4;
       theR[5] = r_s5;
       theR[6] = r_s6;
       theR[7] = r_s7;
       theR[8] = r_s8;
     }
     else {
       if     (theR[0] < r_s0) theRUp  [0] = r_s0;
       else if(theR[0] > r_s0) theRDown[0] = r_s0;
       if     (theR[1] < r_s1) theRUp  [1] = r_s1;
       else if(theR[1] > r_s1) theRDown[1] = r_s1;
       if     (theR[2] < r_s2) theRUp  [2] = r_s2;
       else if(theR[2] > r_s2) theRDown[2] = r_s2;
       if     (theR[3] < r_s3) theRUp  [3] = r_s3;
       else if(theR[3] > r_s3) theRDown[3] = r_s3;
       if     (theR[4] < r_s4) theRUp  [4] = r_s4;
       else if(theR[4] > r_s4) theRDown[4] = r_s4;
       if     (theR[5] < r_s5) theRUp  [5] = r_s5;
       else if(theR[5] > r_s5) theRDown[5] = r_s5;
       if     (theR[6] < r_s6) theRUp  [6] = r_s6;
       else if(theR[6] > r_s6) theRDown[6] = r_s6;
       if     (theR[7] < r_s7) theRUp  [7] = r_s7;
       else if(theR[7] > r_s7) theRDown[7] = r_s7;
       if     (theR[8] < r_s8) theRUp  [8] = r_s8;
       else if(theR[8] > r_s8) theRDown[8] = r_s8;
     }
  }
  if(isDebug) for(int i=0; i<9; i++){printf("inputs: %f %f %f\n",1/theR[i],theRUp[i]-theR[i],theR[i]-theRDown[i]);}

  TH1D* hPred1; TH1D* hPred1_PDF; TH1D* hPred1_QCD;
  hPred1     = (TH1D*)_fileGenWW->Get(Form("hDWW%s",keyLabel0.Data()));
  hPred1_PDF = (TH1D*)_fileGenWW->Get(Form("hDWW%s_PDF",keyLabel0.Data()));
  hPred1_QCD = (TH1D*)_fileGenWW->Get(Form("hDWW%s_QCD",keyLabel0.Data()));
  TH1D* hData = (TH1D*)hPred1->Clone("hData"); hData->Reset();
  for(Int_t i=1;i<=hPred1->GetNbinsX();++i){
    double avgErr = (TMath::Abs(theRUp[i-1]-theR[i-1])+TMath::Abs(theRDown[i-1]-theR[i-1]))/2./theR[i-1];
    double diff[3] = {hPred1->GetBinError(i), hPred1_PDF->GetBinContent(i)-hPred1->GetBinContent(i),hPred1_QCD->GetBinContent(i)-hPred1->GetBinContent(i)};

    if(isNormalized) {
      diff[1] = 0; diff[2] = 0;
      avgErr = sqrt(TMath::Max(avgErr*avgErr-totalXSUnc*totalXSUnc,0.0));
    }

    hData->SetBinContent(i,theR[i-1]*hPred1->GetBinContent(i));
    hData->SetBinError  (i,avgErr*hPred1->GetBinContent(i));

    hPred1->SetBinError(i,sqrt(diff[0]*diff[0]+diff[1]*diff[1]+diff[2]*diff[2]));
    if(isDebug) printf("hPredSyst (%2d) %5.2f %5.2f %5.2f -> %5.2f\n",i,100*diff[0]/hPred1->GetBinContent(i),100*diff[1]/hPred1->GetBinContent(i),100*diff[2]/hPred1->GetBinContent(i),100*hPred1->GetBinError(i)/hPred1->GetBinContent(i));
  }

  hData ->Scale(1,"width");
  hPred1->Scale(1,"width");

  Int_t ww = 800;
  Int_t wh = 800;

  TCanvas *c1 = new TCanvas("c1", "c1", ww, wh);

  TPad* pad1 = new TPad("pad1", "pad1", 0, 0.355, 1, 0.975);
  TPad* pad2 = new TPad("pad2", "pad2", 0, 0.000, 1, 0.345);

  pad1->SetTopMargin   (0.08);
  pad1->SetBottomMargin(0.00);  // 0.02

  pad2->SetTopMargin   (0.05);  // 0.08
  pad2->SetBottomMargin(0.30);  // 0.35

  pad1->Draw();
  pad2->Draw();

  pad1->cd();
  gStyle->SetOptStat(0);
  if(isLogY == true) pad1->SetLogy();

  // draw pad1
  if(strcmp(units.Data(),"")==0){
    hPred1->GetXaxis()->SetTitle(XTitle.Data());
    hPred1->GetXaxis()->SetLabelOffset(0.005);
    hPred1->GetXaxis()->SetTitleOffset(  0.9);
  } else {
    hPred1->GetXaxis()->SetTitle(Form("%s [%s]",XTitle.Data(),units.Data()));
    hPred1->GetXaxis()->SetLabelOffset(0.00);
    hPred1->GetXaxis()->SetTitleOffset(  1.1);
  }

  TString theYTitle = "#sigma / GeV [pb]";
  if     (isNormalized && keyLabel0 == "MLL")    theYTitle = "1/#sigma d#sigma/dm_{ll}";
  else if(isNormalized && keyLabel0 == "PTL1")   theYTitle = "1/#sigma d#sigma/dp_{T}^{max}";
  else if(isNormalized && keyLabel0 == "PTL2")   theYTitle = "1/#sigma d#sigma/dp_{T}^{mix}";
  else if(isNormalized && keyLabel0 == "DPHILL") theYTitle = "1/#sigma d#sigma/d#Delta#phi_{ll}";
  else if(                keyLabel0 == "DPHILL") theYTitle = "#sigma / dg. [pb]";

  hPred1->GetYaxis()->SetTitle(theYTitle.Data());
  hPred1->GetYaxis()->SetLabelFont  (   42);
  hPred1->GetYaxis()->SetLabelOffset(0.015);
  hPred1->GetYaxis()->SetLabelSize  (0.050);
  hPred1->GetYaxis()->SetNdivisions (  505);
  hPred1->GetYaxis()->SetTitleFont  (   42);
  hPred1->GetYaxis()->SetTitleOffset(  1.2);
  hPred1->GetYaxis()->SetTitleSize  (0.060);
  hPred1->GetYaxis()->SetTickLength (0.03 );

  hPred1->GetXaxis()->SetLabelFont  (   42);
  hPred1->GetXaxis()->SetLabelSize  (0.040);
  hPred1->GetXaxis()->SetNdivisions (  505);
  hPred1->GetXaxis()->SetTitleFont  (   42);
  hPred1->GetXaxis()->SetTitleSize  (0.060);
  hPred1->GetXaxis()->SetTickLength (0.07 );
 
  hData->SetLineColor  (kBlack);
  hData->SetMarkerSize(1.5);
  hData->SetMarkerStyle(4);

  hPred1->SetLineColor(kBlack);
  hPred1->SetMarkerStyle(3);
  hPred1->SetMarkerColor(kBlack);

  hPred1->SetTitle("");
  hData ->SetTitle("");
  normalization[0] = TotalLumi; normalization[1] = TotalLumi;
  if(isNormalized) {normalization[0] = hPred1->GetSumOfWeights(); normalization[1] = hData->GetSumOfWeights();};
  hPred1->Scale(1./normalization[0]);
  hData ->Scale(1./normalization[1]);

  if(isLogY == true) hPred1->GetYaxis()->SetRangeUser(hPred1->GetMinimum()/10,hPred1->GetMaximum()*100);
  else               hPred1->GetYaxis()->SetRangeUser(0.0,hPred1->GetMaximum()*1.5);
  hPred1->Draw();
  hData->Draw("ep,same");

  gStyle->SetOptStat(0);
  TLegend* legend = new TLegend(0.62,0.65,0.82,0.85);
  legend->SetBorderSize(     0);
  legend->SetFillColor (     0);
  legend->SetTextAlign (    12);
  legend->SetTextFont  (    42);
  legend->SetTextSize  (0.04);
  legend->AddEntry(hData,"Unfolded data");
  legend->AddEntry(hPred1, "POWHEG");

  CMS_lumi( c1, 4, 11 );
  legend->Draw();

  pad2->cd();
  gStyle->SetOptStat(0);

  TH1D* hNum = (TH1D*) hData->Clone(); hNum->Reset();
  TH1D* hDen = (TH1D*) hData->Clone(); hDen->Reset();

  TH1D* hRatio = (TH1D*) hData->Clone(); hRatio->Reset();
  TH1D* hBand = (TH1D*) hData->Clone(); hBand->Reset();

  hNum->Add(hPred1);
  hDen->Add(hData);

  double pull; 
  double pullerr;

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
  atributes(hRatio,XTitle.Data(),"#frac{POWHEG}{Data}",units.Data());

  hRatio->Draw("e");
  hBand->SetFillColor(12);
  hBand->SetFillStyle(3003);
  hBand->SetMarkerSize(0);
  hBand->SetLineWidth(0);
  hBand->Draw("E2same");
  
  TLegend* leg = new TLegend(0.20,0.75,0.30,0.90);                                                    
  leg ->SetFillStyle(0);
  leg ->SetFillColor(kWhite);
  leg ->SetBorderSize(0);
  leg->SetTextSize(0.04);                                                                         
  leg->AddEntry(hBand,"Theory prediction","f");
  leg->AddEntry(hRatio,"Experimental data","lpe");
  leg->Draw();

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
  hRatio->GetYaxis()->SetRangeUser(0.201,1.799);
  hRatio->GetYaxis()->CenterTitle();
  eraselabel(pad1,hData->GetXaxis()->GetLabelSize());

  printf("Total yields: %f - %f\n", hData->GetSumOfWeights(),hPred1->GetSumOfWeights());

  char CommandToExec[300];
  sprintf(CommandToExec,"mkdir -p plotsww");
  gSystem->Exec(CommandToExec);  

  if(strcmp(outputName.Data(),"") != 0){
    TString myOutputFile;
    myOutputFile = Form("plotsww/%s.eps",outputName.Data());
    //c1->SaveAs(myOutputFile.Data());
    myOutputFile = Form("plotsww/%s.png",outputName.Data());
    c1->SaveAs(myOutputFile.Data());
    myOutputFile = Form("plotsww/%s.pdf",outputName.Data());
    c1->SaveAs(myOutputFile.Data());
  }
}
