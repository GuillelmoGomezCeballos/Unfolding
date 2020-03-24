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

Float_t GetMaximumIncludingErrors(TH1D* h, bool doApplyBinWidth)
{
    Float_t maxWithErrors = 0;

    for (Int_t i=1; i<=h->GetNbinsX(); i++) {

        Float_t binHeight = h->GetBinContent(i) + h->GetBinError(i);

        if(doApplyBinWidth) binHeight = binHeight/h->GetBinWidth(i);

        if (binHeight > maxWithErrors) maxWithErrors = binHeight;
    }

    return maxWithErrors;
}

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
  histo->GetXaxis()->SetLabelSize  (0.110);
  histo->GetXaxis()->SetNdivisions (  505);
  histo->GetXaxis()->SetTitleFont  (   42);
  histo->GetXaxis()->SetTitleOffset(  0.9);
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
  histo->SetFillColor(12);
  histo->SetFillStyle(3345);
  histo->SetLineColor  (kBlack);
  histo->SetMarkerSize(0.8);
  histo->SetMarkerStyle(kFullCircle);
}

void finalPlotVBSUnfolding(TString keyLabel0 = "MLL", bool isNormalized = false) {

  TString XTitle = "X";
  TString units = "GeV";
  bool isLogY = false;
  bool isLogX = false;

  if     (keyLabel0 == "WWMLL") {XTitle = "m_{ll}";}
  else if(keyLabel0 == "WWMJJ" || keyLabel0 == "WZMJJ") {XTitle = "m_{jj}";}
  else if(keyLabel0 == "WWPTL1") {XTitle = "p_{T}^{max}";}

  gInterpreter->ExecuteMacro("PaperStyle.C");
  gStyle->SetOptStat(0);

  bool isDebug = true;

  double diff[2];
  double scaleXS = 1000.0;

  TFile *_fileGenVBS = TFile::Open("/afs/cern.ch/work/c/ceballos/public/samples/panda/v_001_0/genVBS.root");
  TH1D* hPred1     = (TH1D*)_fileGenVBS->Get(Form("hDNoEWKCorrEWK%s",keyLabel0.Data()));     hPred1    ->Scale(scaleXS); hPred1    ->SetDirectory(0);
  TH1D* hPred1_PDF = (TH1D*)_fileGenVBS->Get(Form("hDNoEWKCorrEWK%s_PDF",keyLabel0.Data())); hPred1_PDF->Scale(scaleXS); hPred1_PDF->SetDirectory(0);
  TH1D* hPred1_QCD = (TH1D*)_fileGenVBS->Get(Form("hDNoEWKCorrEWK%s_QCD",keyLabel0.Data())); hPred1_QCD->Scale(scaleXS); hPred1_QCD->SetDirectory(0);

  TH1D* hQCDPred1     = (TH1D*)_fileGenVBS->Get(Form("hDNoEWKCorrQCD%s",keyLabel0.Data()));     hQCDPred1    ->Scale(scaleXS); hQCDPred1    ->SetDirectory(0);
  TH1D* hQCDPred1_PDF = (TH1D*)_fileGenVBS->Get(Form("hDNoEWKCorrQCD%s_PDF",keyLabel0.Data())); hQCDPred1_PDF->Scale(scaleXS); hQCDPred1_PDF->SetDirectory(0);
  TH1D* hQCDPred1_QCD = (TH1D*)_fileGenVBS->Get(Form("hDNoEWKCorrQCD%s_QCD",keyLabel0.Data())); hQCDPred1_QCD->Scale(scaleXS); hQCDPred1_QCD->SetDirectory(0);

  TH1D* hINTPred1     = (TH1D*)_fileGenVBS->Get(Form("hDNoEWKCorrINT%s",keyLabel0.Data()));     hINTPred1    ->Scale(scaleXS); hINTPred1    ->SetDirectory(0);
  TH1D* hINTPred1_PDF = (TH1D*)_fileGenVBS->Get(Form("hDNoEWKCorrINT%s_PDF",keyLabel0.Data())); hINTPred1_PDF->Scale(scaleXS); hINTPred1_PDF->SetDirectory(0);
  TH1D* hINTPred1_QCD = (TH1D*)_fileGenVBS->Get(Form("hDNoEWKCorrINT%s_QCD",keyLabel0.Data())); hINTPred1_QCD->Scale(scaleXS); hINTPred1_QCD->SetDirectory(0);

  TH1D* hPred2     = (TH1D*)_fileGenVBS->Get(Form("hDEWK%s",keyLabel0.Data()));     hPred2    ->Scale(scaleXS); hPred2    ->SetDirectory(0);
  TH1D* hPred2_PDF = (TH1D*)_fileGenVBS->Get(Form("hDEWK%s_PDF",keyLabel0.Data())); hPred2_PDF->Scale(scaleXS); hPred2_PDF->SetDirectory(0);
  TH1D* hPred2_QCD = (TH1D*)_fileGenVBS->Get(Form("hDEWK%s_QCD",keyLabel0.Data())); hPred2_QCD->Scale(scaleXS); hPred2_QCD->SetDirectory(0);

  TH1D* hQCDPred2     = (TH1D*)_fileGenVBS->Get(Form("hDNoEWKCorrQCD%s",keyLabel0.Data()));     hQCDPred2    ->Scale(scaleXS); hQCDPred2    ->SetDirectory(0);
  TH1D* hQCDPred2_PDF = (TH1D*)_fileGenVBS->Get(Form("hDNoEWKCorrQCD%s_PDF",keyLabel0.Data())); hQCDPred2_PDF->Scale(scaleXS); hQCDPred2_PDF->SetDirectory(0);
  TH1D* hQCDPred2_QCD = (TH1D*)_fileGenVBS->Get(Form("hDNoEWKCorrQCD%s_QCD",keyLabel0.Data())); hQCDPred2_QCD->Scale(scaleXS); hQCDPred2_QCD->SetDirectory(0);

  TH1D* hINTPred2     = (TH1D*)_fileGenVBS->Get(Form("hDNoEWKCorrINT%s",keyLabel0.Data()));     hINTPred2    ->Scale(scaleXS); hINTPred2    ->SetDirectory(0);
  TH1D* hINTPred2_PDF = (TH1D*)_fileGenVBS->Get(Form("hDNoEWKCorrINT%s_PDF",keyLabel0.Data())); hINTPred2_PDF->Scale(scaleXS); hINTPred2_PDF->SetDirectory(0);
  TH1D* hINTPred2_QCD = (TH1D*)_fileGenVBS->Get(Form("hDNoEWKCorrINT%s_QCD",keyLabel0.Data())); hINTPred2_QCD->Scale(scaleXS); hINTPred2_QCD->SetDirectory(0);

  TH1D* hEWKOnly = (TH1D*)_fileGenVBS->Get(Form("hDNoEWKCorrEWK%s",keyLabel0.Data())); hEWKOnly->Scale(scaleXS); hEWKOnly->SetDirectory(0);

  hPred1    ->Add(hINTPred1    );
  hPred1_PDF->Add(hINTPred1_PDF);
  hPred1_QCD->Add(hINTPred1_QCD);

  hPred2    ->Add(hINTPred2    );
  hPred2_PDF->Add(hINTPred2_PDF);
  hPred2_QCD->Add(hINTPred2_QCD);

  diff[0] = (hPred1_PDF->GetSumOfWeights()-hPred1->GetSumOfWeights());
  diff[1] = (hPred1_QCD->GetSumOfWeights()-hPred1->GetSumOfWeights());
  printf("PredNoEWKCorrEWK: %.2f %.2f %.2f (%.2f)\n",hPred1->GetSumOfWeights(),diff[0],diff[1],TMath::Sqrt(TMath::Power(diff[0],2)+TMath::Power(diff[1],2)));

  diff[0] = (hPred2_PDF->GetSumOfWeights()-hPred2->GetSumOfWeights());
  diff[1] = (hPred2_QCD->GetSumOfWeights()-hPred2->GetSumOfWeights());
  printf("PredEWK: %.2f %.2f %.2f (%.2f)\n",hPred2->GetSumOfWeights(),diff[0],diff[1],TMath::Sqrt(TMath::Power(diff[0],2)+TMath::Power(diff[1],2)));

  diff[0] = (hQCDPred1_PDF->GetSumOfWeights()-hQCDPred1->GetSumOfWeights());
  diff[1] = (hQCDPred1_QCD->GetSumOfWeights()-hQCDPred1->GetSumOfWeights());
  printf("PredQCD: %.2f %.2f %.2f (%.2f)\n",hQCDPred1->GetSumOfWeights(),diff[0],diff[1],TMath::Sqrt(TMath::Power(diff[0],2)+TMath::Power(diff[1],2)));

  hPred1    ->Add(hQCDPred1    );
  hPred1_PDF->Add(hQCDPred1_PDF);
  hPred1_QCD->Add(hQCDPred1_QCD);

  hPred2    ->Add(hQCDPred2    );
  hPred2_PDF->Add(hQCDPred2_PDF);
  hPred2_QCD->Add(hQCDPred2_QCD);

  diff[0] = (hPred1_PDF->GetSumOfWeights()-hPred1->GetSumOfWeights());
  diff[1] = (hPred1_QCD->GetSumOfWeights()-hPred1->GetSumOfWeights());
  printf("PredNoEWKCorr: %.2f %.2f %.2f (%.2f)\n",hPred1->GetSumOfWeights(),diff[0],diff[1],TMath::Sqrt(TMath::Power(diff[0],2)+TMath::Power(diff[1],2)));

  diff[0] = (hPred2_PDF->GetSumOfWeights()-hPred2->GetSumOfWeights());
  diff[1] = (hPred2_QCD->GetSumOfWeights()-hPred2->GetSumOfWeights());
  printf("Pred: %.2f %.2f %.2f (%.2f)\n",hPred2->GetSumOfWeights(),diff[0],diff[1],TMath::Sqrt(TMath::Power(diff[0],2)+TMath::Power(diff[1],2)));

  TString plotName = Form("input_files_vbs/xs_%s_normalized%d.root", keyLabel0.Data(), isNormalized);
  TFile *_file0 = TFile::Open(plotName.Data());
  TH1D* hData = (TH1D*)_file0->Get(Form("hDAll%s",keyLabel0.Data())); hData->SetDirectory(0);

  double totalUnc1[2] = {TMath::Abs(1-hPred1_PDF->GetSumOfWeights() /hPred1->GetSumOfWeights()),
                         TMath::Abs(1-hPred1_QCD->GetSumOfWeights() /hPred1->GetSumOfWeights())};
  double totalUnc2[2] = {TMath::Abs(1-hPred2_PDF->GetSumOfWeights() /hPred2->GetSumOfWeights()),
                         TMath::Abs(1-hPred2_QCD->GetSumOfWeights() /hPred2->GetSumOfWeights())};

  for(Int_t i=1;i<=hPred1->GetNbinsX();++i){
    double diff1[3] = {hPred1->GetBinError(i)/hPred1->GetBinContent(i),
                      TMath::Abs(1-hPred1_PDF->GetBinContent(i) /hPred1->GetBinContent(i)),
                      TMath::Abs(1-hPred1_QCD->GetBinContent(i) /hPred1->GetBinContent(i))};
    double diff2[3] = {hPred2->GetBinError(i)/hPred2->GetBinContent(i),
                      TMath::Abs(1-hPred2_PDF->GetBinContent(i) /hPred2->GetBinContent(i)),
                      TMath::Abs(1-hPred2_QCD->GetBinContent(i) /hPred2->GetBinContent(i))};

    if(isNormalized) {
      diff1[1] = TMath::Abs(1-(hPred1_PDF->GetBinContent(i) /hPred1_PDF->GetSumOfWeights() )/(hPred1->GetBinContent(i)/hPred1->GetSumOfWeights()));
      diff1[2] = TMath::Abs(1-(hPred1_QCD->GetBinContent(i) /hPred1_QCD->GetSumOfWeights() )/(hPred1->GetBinContent(i)/hPred1->GetSumOfWeights()));
      diff2[1] = TMath::Abs(1-(hPred2_PDF->GetBinContent(i) /hPred2_PDF->GetSumOfWeights() )/(hPred2->GetBinContent(i)/hPred2->GetSumOfWeights()));
      diff2[2] = TMath::Abs(1-(hPred2_QCD->GetBinContent(i) /hPred2_QCD->GetSumOfWeights() )/(hPred2->GetBinContent(i)/hPred2->GetSumOfWeights()));
    }

    hData->SetBinContent(i,hData->GetBinContent(i)*hPred1->GetBinContent(i));
    hData->SetBinError  (i,hData->GetBinError  (i)*hPred1->GetBinContent(i));

    hPred1->SetBinError(i,sqrt(diff1[0]*diff1[0]+diff1[1]*diff1[1]+diff1[2]*diff1[2])*hPred1->GetBinContent(i));
    hPred2->SetBinError(i,sqrt(diff2[0]*diff2[0]+diff2[2]*diff2[2]+diff2[2]*diff2[2])*hPred2->GetBinContent(i));
    if(isDebug) printf("hPredSyst1 (%2d) %5.2f %5.2f %5.2f -> %5.2f\n",i,100*diff1[0],100*diff1[1],100*diff1[2],100*hPred1->GetBinError(i)/hPred1->GetBinContent(i));
    if(isDebug) printf("hPredSyst2 (%2d) %5.2f %5.2f %5.2f -> %5.2f\n",i,100*diff2[0],100*diff2[1],100*diff2[2],100*hPred2->GetBinError(i)/hPred2->GetBinContent(i));
  }

  if(!isNormalized) {
    hData ->Scale(1,"width");
    hPred1->Scale(1,"width");
    hPred2->Scale(1,"width");
    hEWKOnly->Scale(1,"width");
  }

  Int_t ww = 800;
  Int_t wh = 800;

  TCanvas *c1 = new TCanvas("c1", "c1", ww, wh);

  TPad* pad1 = new TPad("pad1", "pad1", 0, 0.350, 1, 0.975);
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
  if(isLogX == true) {pad1->SetLogx(); pad2->SetLogx();}

  // draw pad1
  if(strcmp(units.Data(),"")==0){
    hPred1->GetXaxis()->SetTitle(XTitle.Data());
    hPred1->GetXaxis()->SetLabelOffset(0.005);
    hPred1->GetXaxis()->SetTitleOffset(  0.9);
    hPred2->GetXaxis()->SetTitle(XTitle.Data());
    hPred2->GetXaxis()->SetLabelOffset(0.005);
    hPred2->GetXaxis()->SetTitleOffset(  0.9);
  } else {
    hPred1->GetXaxis()->SetTitle(Form("%s [%s]",XTitle.Data(),units.Data()));
    hPred1->GetXaxis()->SetLabelOffset(0.00);
    hPred1->GetXaxis()->SetTitleOffset(  1.1);
    hPred2->GetXaxis()->SetTitle(Form("%s [%s]",XTitle.Data(),units.Data()));
    hPred2->GetXaxis()->SetLabelOffset(0.00);
    hPred2->GetXaxis()->SetTitleOffset(  1.1);
  }

  TString theYTitle = "#sigma / GeV [fb]";
  if     ( isNormalized && keyLabel0.Contains("MLL"))    theYTitle = "1/#sigma d#sigma/dm_{ll} [1/bin]";
  else if( isNormalized && keyLabel0.Contains("MJJ"))    theYTitle = "1/#sigma d#sigma/dm_{jj} [1/bin]";
  else if( isNormalized && keyLabel0.Contains("PTL1"))   theYTitle = "1/#sigma d#sigma/dp_{T}^{max} [1/bin]";
  else if(!isNormalized && keyLabel0.Contains("MLL"))    theYTitle = "d#sigma/dm_{ll} [fb/GeV]";
  else if(!isNormalized && keyLabel0.Contains("MJJ"))    theYTitle = "d#sigma/dm_{jj} [fb/GeV]";
  else if(!isNormalized && keyLabel0.Contains("PTL1"))   theYTitle = "d#sigma/dp_{T}^{max} [fb/GeV]";
  else {printf("PROBLEM!\n"); return;}

  hPred1->GetYaxis()->SetTitle(theYTitle.Data());
  hPred1->GetYaxis()->SetLabelFont  (   42);
  hPred1->GetYaxis()->SetLabelOffset(0.015);
  hPred1->GetYaxis()->SetLabelSize  (0.050);
  hPred1->GetYaxis()->SetNdivisions (  505);
  hPred1->GetYaxis()->SetTitleFont  (   42);
  hPred1->GetYaxis()->SetTitleOffset(  1.0);
  hPred1->GetYaxis()->SetTitleSize  (0.080);
  hPred1->GetYaxis()->SetTickLength (0.03 );
  hPred1->GetXaxis()->SetLabelFont  (   42);
  hPred1->GetXaxis()->SetLabelSize  (0.040);
  hPred1->GetXaxis()->SetNdivisions (  505);
  hPred1->GetXaxis()->SetTitleFont  (   42);
  hPred1->GetXaxis()->SetTitleSize  (0.060);
  hPred1->GetXaxis()->SetTickLength (0.07 );
 
  hPred2->GetYaxis()->SetTitle(theYTitle.Data());
  hPred2->GetYaxis()->SetLabelFont  (   42);
  hPred2->GetYaxis()->SetLabelOffset(0.015);
  hPred2->GetYaxis()->SetLabelSize  (0.050);
  hPred2->GetYaxis()->SetNdivisions (  505);
  hPred2->GetYaxis()->SetTitleFont  (   42);
  hPred2->GetYaxis()->SetTitleOffset(  1.2);
  hPred2->GetYaxis()->SetTitleSize  (0.060);
  hPred2->GetYaxis()->SetTickLength (0.03 );
  hPred2->GetXaxis()->SetLabelFont  (   42);
  hPred2->GetXaxis()->SetLabelSize  (0.040);
  hPred2->GetXaxis()->SetNdivisions (  505);
  hPred2->GetXaxis()->SetTitleFont  (   42);
  hPred2->GetXaxis()->SetTitleSize  (0.060);
  hPred2->GetXaxis()->SetTickLength (0.07 );
 
  hData->SetFillStyle(3004);
  hData->SetFillColor(TColor::GetColor("#828282"));
  hData->GetYaxis()->SetTitleFont(42);
  hData->GetYaxis()->SetLabelFont(42);
  hData->GetXaxis()->SetTitleFont(42);
  hData->GetXaxis()->SetLabelFont(42);
  hData->GetYaxis()->SetTitleSize(0.055);
  hData->GetXaxis()->SetTitleSize(0.055);
  hData->GetYaxis()->SetLabelSize(0.039);
  hData->GetXaxis()->SetLabelSize(0.039);
  hData->GetYaxis()->SetTitleOffset(1.30);
  hData->GetXaxis()->SetTitleOffset(1.20);
  hData->GetYaxis()->SetLabelOffset(0.015);
  hData->GetXaxis()->SetLabelOffset(0.015);

  hPred1->SetLineColor(kBlack);
  hPred1->SetMarkerStyle(3);
  hPred1->SetMarkerColor(kBlack);
  hPred1->SetLineWidth(3);

  hPred2->SetLineColor(kBlue);
  hPred2->SetLineStyle(2);
  hPred2->SetMarkerStyle(5);
  hPred2->SetMarkerColor(kBlue);
  hPred2->SetLineWidth(3);

  hEWKOnly->SetFillColor(kCyan+3);
  hEWKOnly->SetFillStyle(1001);


  TAxis *xa = hData->GetXaxis();
  hPred1->SetTitle("");
  hPred2->SetTitle("");
  hData ->SetTitle("");
  double normalization[4] = {1.0, 1.0, 1.0,1.0};
  if(isNormalized) {normalization[0] = hPred1->GetSumOfWeights(); normalization[1] = hPred2->GetSumOfWeights(); normalization[2] = hData->GetSumOfWeights(); normalization[3] = hEWKOnly->GetSumOfWeights();};
  hPred1  ->Scale(1./normalization[0]);
  hPred2  ->Scale(1./normalization[1]);
  hData   ->Scale(1./normalization[2]);
  hEWKOnly->Scale(1./normalization[3]);

  TH1D* unfold = (TH1D*) hData->Clone("unfold");

  Float_t dataMax = GetMaximumIncludingErrors(hPred1,false);
  hPred1->SetMaximum(1.15 * dataMax);

  double theEdges[2] = {TMath::Min(hPred1->GetMinimum(),hPred2->GetMinimum()),
                        TMath::Max(hPred1->GetMaximum(),hPred2->GetMaximum())};
  if(isLogY == true) hPred1->GetYaxis()->SetRangeUser(theEdges[0]/10,theEdges[1]*100);
  else               hPred1->GetYaxis()->SetRangeUser(0.0,theEdges[1]*1.5);
  hPred1->Draw("hist");
  hPred2->Draw("hist,same");
  hData->Draw("ep,same");
  if(!isNormalized && keyLabel0.Contains("WZ")) hEWKOnly->Draw("hist,same");

  gStyle->SetOptStat(0);
  TLegend* legend = new TLegend(0.42,0.60,0.82,0.85);
  legend->SetBorderSize(     0);
  legend->SetFillColor (     0);
  legend->SetTextAlign (    12);
  legend->SetTextFont  (    42);
  legend->SetTextSize  (0.035);
  legend->AddEntry(hData,  "Data", "ep");
  legend->AddEntry(hPred1, "MG5_aMC@NLO+Pythia8 without NLO corr.", "l");
  legend->AddEntry(hPred2, "MG5_aMC@NLO+Pythia8 with NLO corr.", "l");
  if(!isNormalized && keyLabel0.Contains("WZ")) legend->AddEntry(hEWKOnly, "EW WZ", "f");

  bool plotSystErrorBars = true;
  if(plotSystErrorBars == true) {
    TGraphAsymmErrors * gsyst1 = new TGraphAsymmErrors(hPred1);
    for (int i = 0; i < gsyst1->GetN(); ++i) {
      gsyst1->SetPointEYlow (i,hPred1->GetBinError(i+1));
      gsyst1->SetPointEYhigh(i,hPred1->GetBinError(i+1));
    }
    gsyst1->SetFillColor(12);
    gsyst1->SetFillStyle(3001);
    gsyst1->SetMarkerSize(0);
    gsyst1->SetLineWidth(0);
    gsyst1->SetLineColor(kWhite);
    gsyst1->Draw("E2same");

    TGraphAsymmErrors * gsyst2 = new TGraphAsymmErrors(hPred2);
    for (int i = 0; i < gsyst2->GetN(); ++i) {
      gsyst2->SetPointEYlow (i,hPred1->GetBinError(i+1));
      gsyst2->SetPointEYhigh(i,hPred1->GetBinError(i+1));
    }
    gsyst2->SetFillColor(12);
    gsyst2->SetFillStyle(3002);
    gsyst2->SetMarkerSize(0);
    gsyst2->SetLineWidth(0);
    gsyst2->SetLineColor(kWhite);
    //gsyst2->Draw("E2same");
    legend->AddEntry(gsyst1, "Theory uncertainty", "f");
  }
  legend->Draw();

  CMS_lumi( pad1, 2019, 1 );

  pad2->cd();
  gStyle->SetOptStat(0);

  TH1D* hNum1 = (TH1D*) hData->Clone(); hNum1->Reset();
  TH1D* hNum2 = (TH1D*) hData->Clone(); hNum2->Reset();
  TH1D* hDen  = (TH1D*) hData->Clone(); hDen->Reset();

  hNum1->Add(hPred1);
  hNum2->Add(hPred2);
  hDen ->Add(hData);

  double pull; 
  double pullerr;
  double pullinv; 
  double pullinverr;

  // Ratio w.r.t. Pred1
  TH1D* hRatio1 = (TH1D*) hData->Clone(); hRatio1->Reset();
  TH1D* hBand1  = (TH1D*) hData->Clone(); hBand1->Reset();
  for(int i=1; i<=hNum1->GetNbinsX(); i++){
      pull = 1.0; pullerr = 0.0;
      pullinv = 1.0; pullinverr = 0.0;
      if(hNum1->GetBinContent(i) > 0 && hDen->GetBinContent(i) > 0){
        pull = (hNum1->GetBinContent(i)/hDen->GetBinContent(i));
	pullerr = pull*hDen->GetBinError(i)/hDen->GetBinContent(i);
        pullinv = (hDen->GetBinContent(i)/hNum1->GetBinContent(i));
	pullinverr = pullinv*hDen->GetBinError(i)/hDen->GetBinContent(i);
      }
      else {
        printf("0 events in %d\n",i);
      }
      if(isDebug) printf("ratio(%2d): pred/data = %.3f +/- %.3f predUnc: %.3f\n",i,pull,pullerr,hNum1->GetBinError(i)/hNum1->GetBinContent(i));
      if(isDebug) printf("ratio(%2d): data/pred = %.3f +/- %.3f, sigma = %.3f fb\n",i,pullinv,pullinverr,hNum1->GetBinContent(i));
      hRatio1->SetBinContent(i,pull);
      hRatio1->SetBinError(i,pullerr);
      hBand1->SetBinContent(i,1);
      hBand1->SetBinError  (i,hNum1->GetBinError(i)/hNum1->GetBinContent(i)); 
  }
  units = units.ReplaceAll("BIN","");
  atributes(hRatio1,XTitle.Data(),"#frac{Theory}{Data}",units.Data());

  hRatio1->Draw("e");
  hBand1->SetFillColor(12);
  hBand1->SetFillStyle(3001);
  hBand1->SetMarkerSize(0);
  hBand1->SetLineWidth(0);
  hBand1->Draw("E2same");
  
  // Band w.r.t. Pred2
  TH1D* hBand2  = (TH1D*) hPred2->Clone(); hBand2->Reset();
  for(int i=1; i<=hNum1->GetNbinsX(); i++){
      pull = 1.0; pullerr = 0.0;
      pullinv = 1.0; pullinverr = 0.0;
      if(hNum1->GetBinContent(i) > 0 && hNum2->GetBinContent(i) > 0){
        pull = (hNum2->GetBinContent(i)/hNum1->GetBinContent(i));
	pullerr = pull*hNum2->GetBinError(i)/hNum2->GetBinContent(i);
      }
      else {
        printf("0 events in %d\n",i);
      }
      if(isDebug) printf("ratio(%2d): pred/pred2 = %.3f +/- %.3f predUnc: %.3f\n",i,pull,pullerr,hNum1->GetBinError(i)/hNum1->GetBinContent(i));
      hBand2->SetBinContent(i,pull);
      hBand2->SetBinError(i,pullerr);
  }

  hBand2->GetYaxis()->SetLabelFont  (   42);
  hBand2->GetYaxis()->SetLabelOffset(0.015);
  hBand2->GetYaxis()->SetLabelSize  (0.050);
  hBand2->GetYaxis()->SetNdivisions (  505);
  hBand2->GetYaxis()->SetTitleFont  (   42);
  hBand2->GetYaxis()->SetTitleOffset(  1.2);
  hBand2->GetYaxis()->SetTitleSize  (0.060);
  hBand2->GetYaxis()->SetTickLength (0.03 );
  hBand2->GetXaxis()->SetLabelFont  (   42);
  hBand2->GetXaxis()->SetLabelSize  (0.040);
  hBand2->GetXaxis()->SetNdivisions (  505);
  hBand2->GetXaxis()->SetTitleFont  (   42);
  hBand2->GetXaxis()->SetTitleSize  (0.060);
  hBand2->GetXaxis()->SetTickLength (0.07 );
 
  hBand2->SetLineWidth(3);
  hBand2->SetLineStyle(2);
  hBand2->SetLineColor(kBlue);
  hBand2->Draw("same,hist");
  
  TLegend* leg = new TLegend(0.20,0.70,0.30,0.85);                                                    
  leg ->SetFillStyle(0);
  leg ->SetFillColor(kWhite);
  leg ->SetBorderSize(0);
  leg->SetTextSize(0.05);                                                                         
  leg->AddEntry(hBand1,"Theory prediction without NLO corr.","f");
  leg->AddEntry(hBand2,"Theory prediction with NLO corr.","l");
  leg->AddEntry(hRatio1,"Experimental data","pe");
  //leg->Draw();

  // Draw a line throgh y=0
  double theLines[2] = {1.0, 0.5};
  TLine* baseline = new TLine(hRatio1->GetXaxis()->GetXmin(), theLines[0],
                              hRatio1->GetXaxis()->GetXmax(), theLines[0]);
  baseline->SetLineStyle(kDashed);
  baseline->Draw();
  // Set the y-axis range symmetric around y=0
  Double_t dy = TMath::Max(TMath::Abs(hRatio1->GetMaximum()),
                           TMath::Abs(hRatio1->GetMinimum())) + theLines[1];
  // Double_t dy = TMath::Max(TMath::Abs(TMath::Abs(hRatio1->GetMaximum())-1),TMath::Abs(TMath::Abs(hRatio1->GetMinimum()))-1);
  hRatio1->GetYaxis()->SetRangeUser(0.201,1.999);
  hRatio1->GetYaxis()->CenterTitle();
  eraselabel(pad1,hData->GetXaxis()->GetLabelSize());

  printf("Total yields: %f - %f -  %f\n", hData->GetSumOfWeights(),hPred1->GetSumOfWeights(),hPred2->GetSumOfWeights());

  char CommandToExec[300];
  sprintf(CommandToExec,"mkdir -p plotsvbs");
  gSystem->Exec(CommandToExec);  

  TString outputName = Form("unf_%s_normalized%d",keyLabel0.Data(),isNormalized);
  if(strcmp(outputName.Data(),"") != 0){
    TString myOutputFile;
    myOutputFile = Form("plotsvbs/%s.png",outputName.Data());
    c1->SaveAs(myOutputFile.Data());
    myOutputFile = Form("plotsvbs/%s.pdf",outputName.Data());
    c1->SaveAs(myOutputFile.Data());
    myOutputFile = Form("plotsvbs/%s.root",outputName.Data());
    TFile *outRoot = TFile::Open(myOutputFile.Data(),"recreate");
    outRoot->cd();
    unfold->Write();
    outRoot->Close();
  }
}
