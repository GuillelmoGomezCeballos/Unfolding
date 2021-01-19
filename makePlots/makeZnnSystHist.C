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

void atributes(TH1D *histo, TString xtitle="", Int_t COLOR = 1, TString ytitle="Fraction", Int_t style = 1){

  histo->ResetAttLine();
  histo->ResetAttFill();
  histo->ResetAttMarker();
  histo->SetTitle("");
  histo->SetMarkerStyle(kFullCircle);
  histo->SetMarkerSize(0.8);
  histo->SetLineWidth(4);
  histo->GetXaxis()->SetTitle(xtitle);
  histo->GetXaxis()->SetLabelFont  (   42);
  histo->GetXaxis()->SetLabelOffset(0.015);
  histo->GetXaxis()->SetLabelSize  (0.039);
  histo->GetXaxis()->SetNdivisions (  505);
  histo->GetXaxis()->SetTitleFont  (   42);
  histo->GetXaxis()->SetTitleOffset( 1.20);
  histo->GetXaxis()->SetTitleSize  (0.035);

  histo->GetYaxis()->SetTitle(ytitle);
  histo->GetYaxis()->SetLabelFont  (   42);
  histo->GetYaxis()->SetLabelOffset(0.015);
  histo->GetYaxis()->SetLabelSize  (0.039);
  histo->GetYaxis()->SetNdivisions (  505);
  histo->GetYaxis()->SetTitleFont  (   42);
  histo->GetYaxis()->SetTitleOffset( 1.20);
  histo->GetYaxis()->SetTitleSize  (0.055);
  histo->SetLineColor(COLOR);
  histo->SetMarkerStyle(kFullDotLarge);
  histo->SetLineStyle(style);
  histo->SetLineWidth(5);
}

void makeZnnSystHist(){
  const int nBinZpt = 5;
  Float_t xbinsZpt[nBinZpt+1] = {200,300,400,500,800,1500};

  // znn
  Float_t xbins0Syst0[nBinZpt]     = {0.036464,0.023084,0.017473,0.011698,0.013891}; // MC Statistical
  Float_t xbins0Syst1[nBinZpt]     = {0.027888,0.027326,0.027248,0.026905,0.025570}; // lumi
  Float_t xbins0Syst2[nBinZpt]     = {0.038429,0.039722,0.036675,0.040048,0.043068}; // jes
  Float_t xbins0Syst3[nBinZpt]     = {0.005226,0.004740,0.003892,0.002969,0.002026}; // leptoneff
  Float_t xbins0Syst4[nBinZpt]     = {0.005936,0.007077,0.004506,0.003561,0.003919}; // theory
  Float_t xbins0Syst5[nBinZpt]     = {0.000000,0.000000,0.000000,0.000000,0.000000}; // leptonres
  Float_t xbins0Syst6[nBinZpt]     = {0.002219,0.006383,0.006477,0.009024,0.008019}; // pu
  Float_t xbins0Syst7[nBinZpt]     = {0.005608,0.006055,0.005963,0.005692,0.005037}; // btag
  Float_t xbins0Syst8[nBinZpt]     = {0.003898,0.011112,0.006347,0.006249,0.009423}; // bcknorm
  Float_t xbins0Syst9[nBinZpt]     = {0.028983,0.019175,0.018394,0.015244,0.014351}; // trigger
  Float_t xbins0Mu[nBinZpt]        = {1.135153,1.090550,1.072811,1.048761,0.967758}; // mu
  Float_t xbins0totalSyst[nBinZpt] = {0.067434,0.061526,0.060690,0.063027,0.085371}; // totalSyst
  Float_t xbins0daSyst[nBinZpt]    = {0.002987,0.016941,0.028264,0.033182,0.064674}; // dataStat
  Float_t xbins0Syst[nBinZpt]      = {0.067367,0.059148,0.053707,0.053585,0.055727}; // syst

  // znn normalized
  Float_t xbins1Syst0[nBinZpt]     = {0.006467,0.008362,0.013764,0.019561,0.024732}; // MC Statistical
  Float_t xbins1Syst1[nBinZpt]     = {0.000232,0.000217,0.000531,0.000737,0.001366}; // lumi
  Float_t xbins1Syst2[nBinZpt]     = {0.002345,0.002502,0.005662,0.009991,0.020077}; // jes
  Float_t xbins1Syst3[nBinZpt]     = {0.001573,0.001510,0.003077,0.004895,0.006114}; // leptoneff
  Float_t xbins1Syst4[nBinZpt]     = {0.003813,0.006009,0.004956,0.005326,0.006170}; // theory
  Float_t xbins1Syst5[nBinZpt]     = {0.000000,0.000000,0.000000,0.000000,0.000000}; // leptonres
  Float_t xbins1Syst6[nBinZpt]     = {0.001774,0.002325,0.002433,0.004627,0.003430}; // pu
  Float_t xbins1Syst7[nBinZpt]     = {0.000143,0.000223,0.000398,0.000578,0.000809}; // btag
  Float_t xbins1Syst8[nBinZpt]     = {0.003155,0.005606,0.003085,0.003671,0.007427}; // bcknorm
  Float_t xbins1Syst9[nBinZpt]     = {0.003643,0.004904,0.005263,0.007816,0.007183}; // trigger
  Float_t xbins1Mu[nBinZpt]        = {1.019188,0.979137,0.963219,0.941628,0.868908}; // mu
  Float_t xbins1totalSyst[nBinZpt] = {0.009673,0.015047,0.018564,0.026496,0.058086}; // totalSyst
  Float_t xbins1daSyst[nBinZpt]    = {0.001668,0.007131,0.006746,0.008388,0.046505}; // dataStat
  Float_t xbins1Syst[nBinZpt]      = {0.009528,0.013250,0.017295,0.025133,0.034803}; // syst

  // zxx
  Float_t xbins2Syst0[nBinZpt]     = {0.014189,0.011317,0.013912,0.016852,0.022654}; // MC Statistical
  Float_t xbins2Syst1[nBinZpt]     = {0.027896,0.027246,0.027944,0.027972,0.027806}; // lumi
  Float_t xbins2Syst2[nBinZpt]     = {0.007411,0.008768,0.009001,0.012332,0.020924}; // jes
  Float_t xbins2Syst3[nBinZpt]     = {0.011661,0.011875,0.011220,0.011032,0.010482}; // leptoneff
  Float_t xbins2Syst4[nBinZpt]     = {0.018108,0.014737,0.010607,0.010110,0.011306}; // theory
  Float_t xbins2Syst5[nBinZpt]     = {0.006773,0.008574,0.008858,0.013069,0.021712}; // leptonres
  Float_t xbins2Syst6[nBinZpt]     = {0.001098,0.001445,0.001682,0.002776,0.002026}; // pu
  Float_t xbins2Syst7[nBinZpt]     = {0.000993,0.001403,0.001294,0.000760,0.000377}; // btag
  Float_t xbins2Syst8[nBinZpt]     = {0.005341,0.008145,0.005777,0.006016,0.008365}; // bcknorm
  Float_t xbins2Syst9[nBinZpt]     = {0.008897,0.002993,0.003123,0.001365,0.001029}; // trigger
  Float_t xbins2Mu[nBinZpt]        = {1.124315,1.070993,1.079723,1.055649,1.016355}; // mu
  Float_t xbins2totalSyst[nBinZpt] = {0.042262,0.039632,0.040437,0.042869,0.067452}; // totalSyst
  Float_t xbins2daSyst[nBinZpt]    = {0.011491,0.010602,0.014672,0.013351,0.045180}; // dataStat
  Float_t xbins2Syst[nBinZpt]      = {0.040670,0.038188,0.037682,0.040737,0.050085}; // syst

  // zxx normalized
  Float_t xbins3Syst0[nBinZpt]     = {0.002170,0.006545,0.010727,0.014916,0.019910}; // MC Statistical
  Float_t xbins3Syst1[nBinZpt]     = {0.000145,0.000277,0.000587,0.000854,0.001558}; // lumi
  Float_t xbins3Syst2[nBinZpt]     = {0.001016,0.002746,0.004824,0.008293,0.016503}; // jes
  Float_t xbins3Syst3[nBinZpt]     = {0.000459,0.001068,0.002424,0.003733,0.005412}; // leptoneff
  Float_t xbins3Syst4[nBinZpt]     = {0.003108,0.011452,0.010012,0.009886,0.010778}; // theory
  Float_t xbins3Syst5[nBinZpt]     = {0.000548,0.001348,0.001882,0.005618,0.013576}; // leptonres
  Float_t xbins3Syst6[nBinZpt]     = {0.000530,0.001629,0.001898,0.002681,0.002019}; // pu
  Float_t xbins3Syst7[nBinZpt]     = {0.000106,0.000285,0.000584,0.000613,0.000552}; // btag
  Float_t xbins3Syst8[nBinZpt]     = {0.001188,0.005048,0.002772,0.002645,0.005137}; // bcknorm
  Float_t xbins3Syst9[nBinZpt]     = {0.001229,0.003863,0.004107,0.005821,0.005735}; // trigger
  Float_t xbins3Mu[nBinZpt]        = {1.011000,0.963582,0.971577,0.949704,0.913886}; // mu
  Float_t xbins3totalSyst[nBinZpt] = {0.004472,0.015315,0.016792,0.022572,0.050646}; // totalSyst
  Float_t xbins3daSyst[nBinZpt]    = {0.000922,0.002616,0.002269,0.005079,0.038735}; // dataStat
  Float_t xbins3Syst[nBinZpt]      = {0.004376,0.015090,0.016638,0.021993,0.032629}; // syst

  TH1D* histoResult[13][4];
  for(int i=0; i<13; i++){
    for(int j=0; j<4; j++){
      histoResult[i][j] = new TH1D(Form("histoResult_%d_%d",i,j), Form("histoResult_%d_%d",i,j), nBinZpt, xbinsZpt);
    }
  }

  for(int i=0; i<nBinZpt; i++) histoResult[ 0][ 0]->SetBinContent(i+1,xbins0Syst0[i]/xbins0Mu[i]);
  for(int i=0; i<nBinZpt; i++) histoResult[ 1][ 0]->SetBinContent(i+1,xbins0Syst1[i]/xbins0Mu[i]);
  for(int i=0; i<nBinZpt; i++) histoResult[ 2][ 0]->SetBinContent(i+1,xbins0Syst2[i]/xbins0Mu[i]);
  for(int i=0; i<nBinZpt; i++) histoResult[ 3][ 0]->SetBinContent(i+1,xbins0Syst3[i]/xbins0Mu[i]);
  for(int i=0; i<nBinZpt; i++) histoResult[ 4][ 0]->SetBinContent(i+1,xbins0Syst4[i]/xbins0Mu[i]);
  for(int i=0; i<nBinZpt; i++) histoResult[ 5][ 0]->SetBinContent(i+1,xbins0Syst5[i]/xbins0Mu[i]);
  for(int i=0; i<nBinZpt; i++) histoResult[ 6][ 0]->SetBinContent(i+1,xbins0Syst6[i]/xbins0Mu[i]);
  for(int i=0; i<nBinZpt; i++) histoResult[ 7][ 0]->SetBinContent(i+1,xbins0Syst7[i]/xbins0Mu[i]);
  for(int i=0; i<nBinZpt; i++) histoResult[ 8][ 0]->SetBinContent(i+1,xbins0Syst8[i]/xbins0Mu[i]);
  for(int i=0; i<nBinZpt; i++) histoResult[ 9][ 0]->SetBinContent(i+1,xbins0Syst9[i]/xbins0Mu[i]);
  for(int i=0; i<nBinZpt; i++) histoResult[10][ 0]->SetBinContent(i+1,xbins0totalSyst[i]/xbins0Mu[i]);
  for(int i=0; i<nBinZpt; i++) histoResult[11][ 0]->SetBinContent(i+1,xbins0daSyst[i]   /xbins0Mu[i]);
  for(int i=0; i<nBinZpt; i++) histoResult[12][ 0]->SetBinContent(i+1,xbins0Syst[i]     /xbins0Mu[i]);

  for(int i=0; i<nBinZpt; i++) histoResult[ 0][ 1]->SetBinContent(i+1,xbins1Syst0[i]/xbins1Mu[i]);
  for(int i=0; i<nBinZpt; i++) histoResult[ 1][ 1]->SetBinContent(i+1,xbins1Syst1[i]/xbins1Mu[i]);
  for(int i=0; i<nBinZpt; i++) histoResult[ 2][ 1]->SetBinContent(i+1,xbins1Syst2[i]/xbins1Mu[i]);
  for(int i=0; i<nBinZpt; i++) histoResult[ 3][ 1]->SetBinContent(i+1,xbins1Syst3[i]/xbins1Mu[i]);
  for(int i=0; i<nBinZpt; i++) histoResult[ 4][ 1]->SetBinContent(i+1,xbins1Syst4[i]/xbins1Mu[i]);
  for(int i=0; i<nBinZpt; i++) histoResult[ 5][ 1]->SetBinContent(i+1,xbins1Syst5[i]/xbins1Mu[i]);
  for(int i=0; i<nBinZpt; i++) histoResult[ 6][ 1]->SetBinContent(i+1,xbins1Syst6[i]/xbins1Mu[i]);
  for(int i=0; i<nBinZpt; i++) histoResult[ 7][ 1]->SetBinContent(i+1,xbins1Syst7[i]/xbins1Mu[i]);
  for(int i=0; i<nBinZpt; i++) histoResult[ 8][ 1]->SetBinContent(i+1,xbins1Syst8[i]/xbins1Mu[i]);
  for(int i=0; i<nBinZpt; i++) histoResult[ 9][ 1]->SetBinContent(i+1,xbins1Syst9[i]/xbins1Mu[i]);
  for(int i=0; i<nBinZpt; i++) histoResult[10][ 1]->SetBinContent(i+1,xbins1totalSyst[i]/xbins1Mu[i]);
  for(int i=0; i<nBinZpt; i++) histoResult[11][ 1]->SetBinContent(i+1,xbins1daSyst[i]   /xbins1Mu[i]);
  for(int i=0; i<nBinZpt; i++) histoResult[12][ 1]->SetBinContent(i+1,xbins1Syst[i]     /xbins1Mu[i]);

  for(int i=0; i<nBinZpt; i++) histoResult[ 0][ 2]->SetBinContent(i+1,xbins2Syst0[i]/xbins2Mu[i]);
  for(int i=0; i<nBinZpt; i++) histoResult[ 1][ 2]->SetBinContent(i+1,xbins2Syst1[i]/xbins2Mu[i]);
  for(int i=0; i<nBinZpt; i++) histoResult[ 2][ 2]->SetBinContent(i+1,xbins2Syst2[i]/xbins2Mu[i]);
  for(int i=0; i<nBinZpt; i++) histoResult[ 3][ 2]->SetBinContent(i+1,xbins2Syst3[i]/xbins2Mu[i]);
  for(int i=0; i<nBinZpt; i++) histoResult[ 4][ 2]->SetBinContent(i+1,xbins2Syst4[i]/xbins2Mu[i]);
  for(int i=0; i<nBinZpt; i++) histoResult[ 5][ 2]->SetBinContent(i+1,xbins2Syst5[i]/xbins2Mu[i]);
  for(int i=0; i<nBinZpt; i++) histoResult[ 6][ 2]->SetBinContent(i+1,xbins2Syst6[i]/xbins2Mu[i]);
  for(int i=0; i<nBinZpt; i++) histoResult[ 7][ 2]->SetBinContent(i+1,xbins2Syst7[i]/xbins2Mu[i]);
  for(int i=0; i<nBinZpt; i++) histoResult[ 8][ 2]->SetBinContent(i+1,xbins2Syst8[i]/xbins2Mu[i]);
  for(int i=0; i<nBinZpt; i++) histoResult[ 9][ 2]->SetBinContent(i+1,xbins2Syst9[i]/xbins2Mu[i]);
  for(int i=0; i<nBinZpt; i++) histoResult[10][ 2]->SetBinContent(i+1,xbins2totalSyst[i]/xbins2Mu[i]);
  for(int i=0; i<nBinZpt; i++) histoResult[11][ 2]->SetBinContent(i+1,xbins2daSyst[i]   /xbins2Mu[i]);
  for(int i=0; i<nBinZpt; i++) histoResult[12][ 2]->SetBinContent(i+1,xbins2Syst[i]     /xbins2Mu[i]);

  for(int i=0; i<nBinZpt; i++) histoResult[ 0][ 3]->SetBinContent(i+1,xbins3Syst0[i]/xbins3Mu[i]);
  for(int i=0; i<nBinZpt; i++) histoResult[ 1][ 3]->SetBinContent(i+1,xbins3Syst1[i]/xbins3Mu[i]);
  for(int i=0; i<nBinZpt; i++) histoResult[ 2][ 3]->SetBinContent(i+1,xbins3Syst2[i]/xbins3Mu[i]);
  for(int i=0; i<nBinZpt; i++) histoResult[ 3][ 3]->SetBinContent(i+1,xbins3Syst3[i]/xbins3Mu[i]);
  for(int i=0; i<nBinZpt; i++) histoResult[ 4][ 3]->SetBinContent(i+1,xbins3Syst4[i]/xbins3Mu[i]);
  for(int i=0; i<nBinZpt; i++) histoResult[ 5][ 3]->SetBinContent(i+1,xbins3Syst5[i]/xbins3Mu[i]);
  for(int i=0; i<nBinZpt; i++) histoResult[ 6][ 3]->SetBinContent(i+1,xbins3Syst6[i]/xbins3Mu[i]);
  for(int i=0; i<nBinZpt; i++) histoResult[ 7][ 3]->SetBinContent(i+1,xbins3Syst7[i]/xbins3Mu[i]);
  for(int i=0; i<nBinZpt; i++) histoResult[ 8][ 3]->SetBinContent(i+1,xbins3Syst8[i]/xbins3Mu[i]);
  for(int i=0; i<nBinZpt; i++) histoResult[ 9][ 3]->SetBinContent(i+1,xbins3Syst9[i]/xbins3Mu[i]);
  for(int i=0; i<nBinZpt; i++) histoResult[10][ 3]->SetBinContent(i+1,xbins3totalSyst[i]/xbins3Mu[i]);
  for(int i=0; i<nBinZpt; i++) histoResult[11][ 3]->SetBinContent(i+1,xbins3daSyst[i]   /xbins3Mu[i]);
  for(int i=0; i<nBinZpt; i++) histoResult[12][ 3]->SetBinContent(i+1,xbins3Syst[i]     /xbins3Mu[i]);

  TString outNtuplename = Form("ZnnSystHist.root");
  TFile *outtuple = TFile::Open(outNtuplename.Data(),"recreate");
  outtuple->cd();
  for(int i=0; i<13; i++){
    for(int j=0; j<4; j++){
      histoResult[i][j]->Write();
    }
  }
  outtuple->Close();

  TLatex * CMSLabel = new TLatex (0.15, 0.93, "#bf{CMS} #scale[0.75]{#it{Supplementary}}");
  CMSLabel->SetNDC ();
  CMSLabel->SetTextAlign (10);
  CMSLabel->SetTextFont (42);
  CMSLabel->SetTextSize (0.04);

  TLatex * _lumiLabel = new TLatex (0.95, 0.93, "35.9 fb^{-1} (13 TeV)");
  _lumiLabel->SetNDC ();
  _lumiLabel->SetTextAlign (30);
  _lumiLabel->SetTextFont (42);
  _lumiLabel->SetTextSize (0.04);

  TString XName = "p^{Z}_{T} [GeV]";
  TString theUncLabel = "d#sigma/dp^{Z}_{T}";

  TCanvas* c0 = new TCanvas("c0", "c0",5,5,500,500);
  c0->cd();
  atributes(histoResult[ 0][ 0],XName.Data(), 1,Form("Uncertainty in %s",theUncLabel.Data()), 1);
  atributes(histoResult[ 1][ 0],XName.Data(), 2,Form("Uncertainty in %s",theUncLabel.Data()), 1);
  atributes(histoResult[ 2][ 0],XName.Data(), 3,Form("Uncertainty in %s",theUncLabel.Data()), 1);
  atributes(histoResult[ 3][ 0],XName.Data(), 4,Form("Uncertainty in %s",theUncLabel.Data()), 1);
  atributes(histoResult[ 4][ 0],XName.Data(), 5,Form("Uncertainty in %s",theUncLabel.Data()), 1);
  atributes(histoResult[ 5][ 0],XName.Data(), 6,Form("Uncertainty in %s",theUncLabel.Data()), 1);
  atributes(histoResult[ 6][ 0],XName.Data(), 7,Form("Uncertainty in %s",theUncLabel.Data()), 1);
  atributes(histoResult[ 7][ 0],XName.Data(), 8,Form("Uncertainty in %s",theUncLabel.Data()), 1);
  atributes(histoResult[ 8][ 0],XName.Data(), 9,Form("Uncertainty in %s",theUncLabel.Data()), 1);
  atributes(histoResult[ 9][ 0],XName.Data(),46,Form("Uncertainty in %s",theUncLabel.Data()), 1);
  atributes(histoResult[10][ 0],XName.Data(),11,Form("Uncertainty in %s",theUncLabel.Data()), 1);
  atributes(histoResult[11][ 0],XName.Data(),12,Form("Uncertainty in %s",theUncLabel.Data()), 2);
  atributes(histoResult[12][ 0],XName.Data(),13,Form("Uncertainty in %s",theUncLabel.Data()), 3);
  histoResult[10][ 0]->SetMinimum(0.00);
  histoResult[10][ 0]->SetMaximum(0.13);
  histoResult[10][ 0]->Draw();
  histoResult[ 1][ 0]->Draw("same,hist");
  histoResult[ 2][ 0]->Draw("same,hist");
  histoResult[ 3][ 0]->Draw("same,hist");
  histoResult[ 4][ 0]->Draw("same,hist");
  histoResult[ 5][ 0]->Draw("same,hist");
  histoResult[ 6][ 0]->Draw("same,hist");
  histoResult[ 7][ 0]->Draw("same,hist");
  histoResult[ 8][ 0]->Draw("same,hist");
  histoResult[ 9][ 0]->Draw("same,hist");
  histoResult[12][ 0]->Draw("same,hist");
  histoResult[11][ 0]->Draw("same,hist");

  CMSLabel->Draw("same");
  _lumiLabel->Draw ("same") ;

  TLegend* leg0 = new TLegend(0.20,0.60,0.50,0.90);						      
  leg0 ->SetFillStyle(0);
  leg0 ->SetFillColor(kWhite);
  leg0 ->SetBorderSize(0);
  leg0->SetTextSize(0.025);									   
  leg0->AddEntry(histoResult[10][ 0],"Total uncertainty","l");
  leg0->AddEntry(histoResult[ 0][ 0],"MC statistical","l");
  leg0->AddEntry(histoResult[ 1][ 0],"Luminosity","l");
  leg0->AddEntry(histoResult[ 2][ 0],"Jet energy scale","l");
  leg0->AddEntry(histoResult[ 3][ 0],"Lepton efficiency","l");
  leg0->AddEntry(histoResult[ 4][ 0],"Theory","l");
  leg0->AddEntry(histoResult[ 5][ 0],"Lepton momentum resolution","l");
  leg0->AddEntry(histoResult[ 6][ 0],"Pileup","l");
  leg0->AddEntry(histoResult[ 7][ 0],"B tagging","l");
  leg0->AddEntry(histoResult[ 8][ 0],"Background normalization","l");
  leg0->AddEntry(histoResult[ 9][ 0],"Trigger efficiency","l");
  leg0->AddEntry(histoResult[11][ 0],"Data statistical","l");
  leg0->AddEntry(histoResult[12][ 0],"Total systematic","l");
  leg0->Draw();

  TString myOutputFile0 = Form("histoXS_Znn.pdf");
  c0->SaveAs(myOutputFile0.Data());

  TCanvas* c1 = new TCanvas("c1", "c1",5,5,500,500);
  c1->cd();
  atributes(histoResult[ 0][ 1],XName.Data(), 1,Form("Uncertainty in %s",theUncLabel.Data()), 1);
  atributes(histoResult[ 1][ 1],XName.Data(), 2,Form("Uncertainty in %s",theUncLabel.Data()), 1);
  atributes(histoResult[ 2][ 1],XName.Data(), 3,Form("Uncertainty in %s",theUncLabel.Data()), 1);
  atributes(histoResult[ 3][ 1],XName.Data(), 4,Form("Uncertainty in %s",theUncLabel.Data()), 1);
  atributes(histoResult[ 4][ 1],XName.Data(), 5,Form("Uncertainty in %s",theUncLabel.Data()), 1);
  atributes(histoResult[ 5][ 1],XName.Data(), 6,Form("Uncertainty in %s",theUncLabel.Data()), 1);
  atributes(histoResult[ 6][ 1],XName.Data(), 7,Form("Uncertainty in %s",theUncLabel.Data()), 1);
  atributes(histoResult[ 7][ 1],XName.Data(), 8,Form("Uncertainty in %s",theUncLabel.Data()), 1);
  atributes(histoResult[ 8][ 1],XName.Data(), 9,Form("Uncertainty in %s",theUncLabel.Data()), 1);
  atributes(histoResult[ 9][ 1],XName.Data(),46,Form("Uncertainty in %s",theUncLabel.Data()), 1);
  atributes(histoResult[10][ 1],XName.Data(),11,Form("Uncertainty in %s",theUncLabel.Data()), 1);
  atributes(histoResult[11][ 1],XName.Data(),12,Form("Uncertainty in %s",theUncLabel.Data()), 2);
  atributes(histoResult[12][ 1],XName.Data(),13,Form("Uncertainty in %s",theUncLabel.Data()), 3);
  histoResult[10][ 1]->SetMinimum(0.00);
  histoResult[10][ 1]->SetMaximum(0.13);
  histoResult[10][ 1]->Draw();
  histoResult[ 1][ 1]->Draw("same,hist");
  histoResult[ 2][ 1]->Draw("same,hist");
  histoResult[ 3][ 1]->Draw("same,hist");
  histoResult[ 4][ 1]->Draw("same,hist");
  histoResult[ 5][ 1]->Draw("same,hist");
  histoResult[ 6][ 1]->Draw("same,hist");
  histoResult[ 7][ 1]->Draw("same,hist");
  histoResult[ 8][ 1]->Draw("same,hist");
  histoResult[ 9][ 1]->Draw("same,hist");
  histoResult[12][ 1]->Draw("same,hist");
  histoResult[11][ 1]->Draw("same,hist");

  CMSLabel->Draw("same");
  _lumiLabel->Draw ("same") ;

  TLegend* leg1 = new TLegend(0.20,0.60,0.50,0.90);						      
  leg1 ->SetFillStyle(0);
  leg1 ->SetFillColor(kWhite);
  leg1 ->SetBorderSize(0);
  leg1->SetTextSize(0.025);									   
  leg1->AddEntry(histoResult[10][ 1],"Total uncertainty","l");
  leg1->AddEntry(histoResult[ 0][ 1],"MC statistical","l");
  leg1->AddEntry(histoResult[ 1][ 1],"Luminosity","l");
  leg1->AddEntry(histoResult[ 2][ 1],"Jet energy scale","l");
  leg1->AddEntry(histoResult[ 3][ 1],"Lepton efficiency","l");
  leg1->AddEntry(histoResult[ 4][ 1],"Theory","l");
  leg1->AddEntry(histoResult[ 5][ 1],"Lepton momentum resolution","l");
  leg1->AddEntry(histoResult[ 6][ 1],"Pileup","l");
  leg1->AddEntry(histoResult[ 7][ 1],"B tagging","l");
  leg1->AddEntry(histoResult[ 8][ 1],"Background normalization","l");
  leg1->AddEntry(histoResult[ 9][ 1],"Trigger efficiency","l");
  leg1->AddEntry(histoResult[11][ 1],"Data statistical","l");
  leg1->AddEntry(histoResult[12][ 1],"Total systematic","l");
  leg1->Draw();

  TString myOutputFile1 = Form("histoXS_Zll.pdf");
  c1->SaveAs(myOutputFile1.Data());

  TCanvas* c2 = new TCanvas("c2", "c2",5,5,500,500);
  c2->cd();
  atributes(histoResult[ 0][ 2],XName.Data(), 1,Form("Uncertainty in %s",theUncLabel.Data()), 1);
  atributes(histoResult[ 1][ 2],XName.Data(), 2,Form("Uncertainty in %s",theUncLabel.Data()), 1);
  atributes(histoResult[ 2][ 2],XName.Data(), 3,Form("Uncertainty in %s",theUncLabel.Data()), 1);
  atributes(histoResult[ 3][ 2],XName.Data(), 4,Form("Uncertainty in %s",theUncLabel.Data()), 1);
  atributes(histoResult[ 4][ 2],XName.Data(), 5,Form("Uncertainty in %s",theUncLabel.Data()), 1);
  atributes(histoResult[ 5][ 2],XName.Data(), 6,Form("Uncertainty in %s",theUncLabel.Data()), 1);
  atributes(histoResult[ 6][ 2],XName.Data(), 7,Form("Uncertainty in %s",theUncLabel.Data()), 1);
  atributes(histoResult[ 7][ 2],XName.Data(), 8,Form("Uncertainty in %s",theUncLabel.Data()), 1);
  atributes(histoResult[ 8][ 2],XName.Data(), 9,Form("Uncertainty in %s",theUncLabel.Data()), 1);
  atributes(histoResult[ 9][ 2],XName.Data(),46,Form("Uncertainty in %s",theUncLabel.Data()), 1);
  atributes(histoResult[10][ 2],XName.Data(),11,Form("Uncertainty in %s",theUncLabel.Data()), 1);
  atributes(histoResult[11][ 2],XName.Data(),12,Form("Uncertainty in %s",theUncLabel.Data()), 2);
  atributes(histoResult[12][ 2],XName.Data(),13,Form("Uncertainty in %s",theUncLabel.Data()), 3);
  histoResult[10][ 2]->SetMinimum(0.00);
  histoResult[10][ 2]->SetMaximum(0.13);
  histoResult[10][ 2]->Draw();
  histoResult[ 1][ 2]->Draw("same,hist");
  histoResult[ 2][ 2]->Draw("same,hist");
  histoResult[ 3][ 2]->Draw("same,hist");
  histoResult[ 4][ 2]->Draw("same,hist");
  histoResult[ 5][ 2]->Draw("same,hist");
  histoResult[ 6][ 2]->Draw("same,hist");
  histoResult[ 7][ 2]->Draw("same,hist");
  histoResult[ 8][ 2]->Draw("same,hist");
  histoResult[ 9][ 2]->Draw("same,hist");
  histoResult[12][ 2]->Draw("same,hist");
  histoResult[11][ 2]->Draw("same,hist");

  CMSLabel->Draw("same");
  _lumiLabel->Draw ("same") ;

  TLegend* leg2 = new TLegend(0.20,0.60,0.50,0.90);						      
  leg2 ->SetFillStyle(0);
  leg2 ->SetFillColor(kWhite);
  leg2 ->SetBorderSize(0);
  leg2->SetTextSize(0.025);									   
  leg2->AddEntry(histoResult[10][ 2],"Total uncertainty","l");
  leg2->AddEntry(histoResult[ 0][ 2],"MC statistical","l");
  leg2->AddEntry(histoResult[ 1][ 2],"Luminosity","l");
  leg2->AddEntry(histoResult[ 2][ 2],"Jet energy scale","l");
  leg2->AddEntry(histoResult[ 3][ 2],"Lepton efficiency","l");
  leg2->AddEntry(histoResult[ 4][ 2],"Theory","l");
  leg2->AddEntry(histoResult[ 5][ 2],"Lepton momentum resolution","l");
  leg2->AddEntry(histoResult[ 6][ 2],"Pileup","l");
  leg2->AddEntry(histoResult[ 7][ 2],"B tagging","l");
  leg2->AddEntry(histoResult[ 8][ 2],"Background normalization","l");
  leg2->AddEntry(histoResult[ 9][ 2],"Trigger efficiency","l");
  leg2->AddEntry(histoResult[11][ 2],"Data statistical","l");
  leg2->AddEntry(histoResult[12][ 2],"Total systematic","l");
  leg2->Draw();

  TString myOutputFile2 = Form("histoXSnorm_Znn.pdf");
  c2->SaveAs(myOutputFile2.Data());

  TCanvas* c3 = new TCanvas("c3", "c3",5,5,500,500);
  c3->cd();
  atributes(histoResult[ 0][ 3],XName.Data(), 1,Form("Uncertainty in %s",theUncLabel.Data()), 1);
  atributes(histoResult[ 1][ 3],XName.Data(), 2,Form("Uncertainty in %s",theUncLabel.Data()), 1);
  atributes(histoResult[ 2][ 3],XName.Data(), 3,Form("Uncertainty in %s",theUncLabel.Data()), 1);
  atributes(histoResult[ 3][ 3],XName.Data(), 4,Form("Uncertainty in %s",theUncLabel.Data()), 1);
  atributes(histoResult[ 4][ 3],XName.Data(), 5,Form("Uncertainty in %s",theUncLabel.Data()), 1);
  atributes(histoResult[ 5][ 3],XName.Data(), 6,Form("Uncertainty in %s",theUncLabel.Data()), 1);
  atributes(histoResult[ 6][ 3],XName.Data(), 7,Form("Uncertainty in %s",theUncLabel.Data()), 1);
  atributes(histoResult[ 7][ 3],XName.Data(), 8,Form("Uncertainty in %s",theUncLabel.Data()), 1);
  atributes(histoResult[ 8][ 3],XName.Data(), 9,Form("Uncertainty in %s",theUncLabel.Data()), 1);
  atributes(histoResult[ 9][ 3],XName.Data(),46,Form("Uncertainty in %s",theUncLabel.Data()), 1);
  atributes(histoResult[10][ 3],XName.Data(),11,Form("Uncertainty in %s",theUncLabel.Data()), 1);
  atributes(histoResult[11][ 3],XName.Data(),12,Form("Uncertainty in %s",theUncLabel.Data()), 2);
  atributes(histoResult[12][ 3],XName.Data(),13,Form("Uncertainty in %s",theUncLabel.Data()), 3);
  histoResult[10][ 3]->SetMinimum(0.00);
  histoResult[10][ 3]->SetMaximum(0.13);
  histoResult[10][ 3]->Draw();
  histoResult[ 1][ 3]->Draw("same,hist");
  histoResult[ 2][ 3]->Draw("same,hist");
  histoResult[ 3][ 3]->Draw("same,hist");
  histoResult[ 4][ 3]->Draw("same,hist");
  histoResult[ 5][ 3]->Draw("same,hist");
  histoResult[ 6][ 3]->Draw("same,hist");
  histoResult[ 7][ 3]->Draw("same,hist");
  histoResult[ 8][ 3]->Draw("same,hist");
  histoResult[ 9][ 3]->Draw("same,hist");
  histoResult[12][ 3]->Draw("same,hist");
  histoResult[11][ 3]->Draw("same,hist");

  CMSLabel->Draw("same");
  _lumiLabel->Draw ("same") ;

  TLegend* leg3 = new TLegend(0.20,0.60,0.50,0.90);						      
  leg3 ->SetFillStyle(0);
  leg3 ->SetFillColor(kWhite);
  leg3 ->SetBorderSize(0);
  leg3->SetTextSize(0.025);									   
  leg3->AddEntry(histoResult[10][ 3],"Total uncertainty","l");
  leg3->AddEntry(histoResult[ 0][ 3],"MC statistical","l");
  leg3->AddEntry(histoResult[ 1][ 3],"Luminosity","l");
  leg3->AddEntry(histoResult[ 2][ 3],"Jet energy scale","l");
  leg3->AddEntry(histoResult[ 3][ 3],"Lepton efficiency","l");
  leg3->AddEntry(histoResult[ 4][ 3],"Theory","l");
  leg3->AddEntry(histoResult[ 5][ 3],"Lepton momentum resolution","l");
  leg3->AddEntry(histoResult[ 6][ 3],"Pileup","l");
  leg3->AddEntry(histoResult[ 7][ 3],"B tagging","l");
  leg3->AddEntry(histoResult[ 8][ 3],"Background normalization","l");
  leg3->AddEntry(histoResult[ 9][ 3],"Trigger efficiency","l");
  leg3->AddEntry(histoResult[11][ 3],"Data statistical","l");
  leg3->AddEntry(histoResult[12][ 3],"Total systematic","l");
  leg3->Draw();

  TString myOutputFile3 = Form("histoXSnorm_Zll.pdf");
  c3->SaveAs(myOutputFile3.Data());
}
