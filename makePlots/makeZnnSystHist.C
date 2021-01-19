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
  Float_t xbins0Syst0[nBinZpt]     = {0.036432,0.024671,0.020166,0.014283,0.012594}; // MC Statistical
  Float_t xbins0Syst1[nBinZpt]     = {0.024306,0.025195,0.026930,0.026731,0.025446}; // lumi
  Float_t xbins0Syst2[nBinZpt]     = {0.038252,0.041168,0.040992,0.044752,0.047547}; // jes
  Float_t xbins0Syst3[nBinZpt]     = {0.011814,0.008865,0.007602,0.005508,0.003350}; // leptoneff
  Float_t xbins0Syst4[nBinZpt]     = {0.007455,0.008349,0.005716,0.003320,0.002052}; // theory
  Float_t xbins0Syst5[nBinZpt]     = {0.000000,0.000000,0.000000,0.000000,0.000000}; // leptonres
  Float_t xbins0Syst6[nBinZpt]     = {0.001571,0.002594,0.002893,0.005336,0.004016}; // pu
  Float_t xbins0Syst7[nBinZpt]     = {0.009560,0.009903,0.010644,0.010518,0.010026}; // btag
  Float_t xbins0Syst8[nBinZpt]     = {0.007324,0.011525,0.007824,0.007856,0.010939}; // bcknorm
  Float_t xbins0Syst9[nBinZpt]     = {0.028655,0.020982,0.021896,0.019008,0.017938}; // trigger
  Float_t xbins0Mu[nBinZpt]        = {1.135028,1.090424,1.072696,1.048651,0.967665}; // mu
  Float_t xbins0totalSyst[nBinZpt] = {0.067551,0.061721,0.061209,0.063204,0.085618}; // totalSyst
  Float_t xbins0daSyst[nBinZpt]    = {0.004214,0.006699,0.013475,0.021679,0.060747}; // dataStat
  Float_t xbins0Syst[nBinZpt]      = {0.067419,0.061356,0.059708,0.059369,0.060335}; // syst

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
  Float_t xbins2Syst0[nBinZpt]     = {0.007661,0.004572,0.009216,0.013531,0.019169}; // MC Statistical
  Float_t xbins2Syst1[nBinZpt]     = {0.028035,0.027370,0.027920,0.027712,0.027504}; // lumi
  Float_t xbins2Syst2[nBinZpt]     = {0.007140,0.009559,0.009239,0.012309,0.019605}; // jes
  Float_t xbins2Syst3[nBinZpt]     = {0.015602,0.014332,0.013843,0.013536,0.012956}; // leptoneff
  Float_t xbins2Syst4[nBinZpt]     = {0.018005,0.014050,0.010123,0.009180,0.010914}; // theory
  Float_t xbins2Syst5[nBinZpt]     = {0.007574,0.008458,0.008585,0.012413,0.020786}; // leptonres
  Float_t xbins2Syst6[nBinZpt]     = {0.001401,0.001038,0.001330,0.002204,0.001503}; // pu
  Float_t xbins2Syst7[nBinZpt]     = {0.002035,0.002445,0.002770,0.002760,0.002665}; // btag
  Float_t xbins2Syst8[nBinZpt]     = {0.003328,0.005239,0.002575,0.003001,0.006058}; // bcknorm
  Float_t xbins2Syst9[nBinZpt]     = {0.009349,0.003602,0.003545,0.001874,0.001758}; // trigger
  Float_t xbins2Mu[nBinZpt]        = {1.119393,1.066964,1.075830,1.051601,1.011912}; // mu
  Float_t xbins2totalSyst[nBinZpt] = {0.041394,0.038688,0.039714,0.041939,0.066891}; // totalSyst
  Float_t xbins2daSyst[nBinZpt]    = {0.009397,0.010655,0.015197,0.014485,0.046883}; // dataStat
  Float_t xbins2Syst[nBinZpt]      = {0.040314,0.037192,0.036691,0.039359,0.047712}; // syst

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

  // zll
  Float_t xbins4Syst0[nBinZpt]     = {0.000909,0.000906,0.004098,0.005098,0.007523}; // MC Statistical
  Float_t xbins4Syst1[nBinZpt]     = {0.028007,0.026754,0.028602,0.028724,0.030873}; // lumi
  Float_t xbins4Syst2[nBinZpt]     = {0.000000,0.000000,0.000000,0.000000,0.000000}; // jes
  Float_t xbins4Syst3[nBinZpt]     = {0.021229,0.019817,0.021047,0.020172,0.019713}; // leptoneff
  Float_t xbins4Syst4[nBinZpt]     = {0.024865,0.020122,0.016765,0.011154,0.016586}; // theory
  Float_t xbins4Syst5[nBinZpt]     = {0.011605,0.012331,0.013952,0.025200,0.054084}; // leptonres
  Float_t xbins4Syst6[nBinZpt]     = {0.000000,0.000000,0.000000,0.000000,0.000000}; // pu
  Float_t xbins4Syst7[nBinZpt]     = {0.000000,0.000000,0.000000,0.000000,0.000000}; // btag
  Float_t xbins4Syst8[nBinZpt]     = {0.000553,0.001550,0.002638,0.003904,0.006578}; // bcknorm
  Float_t xbins4Syst9[nBinZpt]     = {0.000000,0.000000,0.000000,0.000000,0.000000}; // trigger
  Float_t xbins4Mu[nBinZpt]        = {1.116339,1.039740,1.109444,1.094439,1.140863}; // mu
  Float_t xbins4totalSyst[nBinZpt] = {0.046628,0.042980,0.048243,0.054398,0.116250}; // totalSyst
  Float_t xbins4daSyst[nBinZpt]    = {0.013605,0.013367,0.023809,0.030438,0.094192}; // dataStat
  Float_t xbins4Syst[nBinZpt]      = {0.044599,0.040849,0.041958,0.045085,0.068131}; // syst

  // zll normalized
  Float_t xbins5Syst0[nBinZpt]     = {0.000204,0.000809,0.003339,0.004442,0.006689}; // MC Statistical
  Float_t xbins5Syst1[nBinZpt]     = {0.000103,0.000428,0.000468,0.000966,0.001818}; // lumi
  Float_t xbins5Syst2[nBinZpt]     = {0.000000,0.000000,0.000000,0.000000,0.000000}; // jes
  Float_t xbins5Syst3[nBinZpt]     = {0.000546,0.001101,0.002820,0.004678,0.009359}; // leptoneff
  Float_t xbins5Syst4[nBinZpt]     = {0.005902,0.022521,0.023138,0.020115,0.023433}; // theory
  Float_t xbins5Syst5[nBinZpt]     = {0.001352,0.002874,0.006131,0.016129,0.042113}; // leptonres
  Float_t xbins5Syst6[nBinZpt]     = {0.000000,0.000000,0.000000,0.000000,0.000000}; // pu
  Float_t xbins5Syst7[nBinZpt]     = {0.000000,0.000000,0.000000,0.000000,0.000000}; // btag
  Float_t xbins5Syst8[nBinZpt]     = {0.000263,0.000664,0.001608,0.002770,0.005159}; // bcknorm
  Float_t xbins5Syst9[nBinZpt]     = {0.000000,0.000000,0.000000,0.000000,0.000000}; // trigger
  Float_t xbins5Mu[nBinZpt]        = {1.012002,0.942669,1.005884,0.992231,1.034308}; // mu
  Float_t xbins5totalSyst[nBinZpt] = {0.006491,0.024561,0.030350,0.036134,0.096934}; // totalSyst
  Float_t xbins5daSyst[nBinZpt]    = {0.002249,0.009236,0.018063,0.024304,0.083135}; // dataStat
  Float_t xbins5Syst[nBinZpt]      = {0.006089,0.022759,0.024389,0.026739,0.049849}; // syst

  TH1D* histoResult[13][6];
  for(int i=0; i<13; i++){
    for(int j=0; j<6; j++){
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

  for(int i=0; i<nBinZpt; i++) histoResult[ 0][ 4]->SetBinContent(i+1,xbins4Syst0[i]/xbins4Mu[i]);
  for(int i=0; i<nBinZpt; i++) histoResult[ 1][ 4]->SetBinContent(i+1,xbins4Syst1[i]/xbins4Mu[i]);
  for(int i=0; i<nBinZpt; i++) histoResult[ 2][ 4]->SetBinContent(i+1,xbins4Syst2[i]/xbins4Mu[i]);
  for(int i=0; i<nBinZpt; i++) histoResult[ 3][ 4]->SetBinContent(i+1,xbins4Syst3[i]/xbins4Mu[i]);
  for(int i=0; i<nBinZpt; i++) histoResult[ 4][ 4]->SetBinContent(i+1,xbins4Syst4[i]/xbins4Mu[i]);
  for(int i=0; i<nBinZpt; i++) histoResult[ 5][ 4]->SetBinContent(i+1,xbins4Syst5[i]/xbins4Mu[i]);
  for(int i=0; i<nBinZpt; i++) histoResult[ 6][ 4]->SetBinContent(i+1,xbins4Syst6[i]/xbins4Mu[i]);
  for(int i=0; i<nBinZpt; i++) histoResult[ 7][ 4]->SetBinContent(i+1,xbins4Syst7[i]/xbins4Mu[i]);
  for(int i=0; i<nBinZpt; i++) histoResult[ 8][ 4]->SetBinContent(i+1,xbins4Syst8[i]/xbins4Mu[i]);
  for(int i=0; i<nBinZpt; i++) histoResult[ 9][ 4]->SetBinContent(i+1,xbins4Syst9[i]/xbins4Mu[i]);
  for(int i=0; i<nBinZpt; i++) histoResult[10][ 4]->SetBinContent(i+1,xbins4totalSyst[i]/xbins4Mu[i]);
  for(int i=0; i<nBinZpt; i++) histoResult[11][ 4]->SetBinContent(i+1,xbins4daSyst[i]   /xbins4Mu[i]);
  for(int i=0; i<nBinZpt; i++) histoResult[12][ 4]->SetBinContent(i+1,xbins4Syst[i]     /xbins4Mu[i]);

  for(int i=0; i<nBinZpt; i++) histoResult[ 0][ 5]->SetBinContent(i+1,xbins5Syst0[i]/xbins5Mu[i]);
  for(int i=0; i<nBinZpt; i++) histoResult[ 1][ 5]->SetBinContent(i+1,xbins5Syst1[i]/xbins5Mu[i]);
  for(int i=0; i<nBinZpt; i++) histoResult[ 2][ 5]->SetBinContent(i+1,xbins5Syst2[i]/xbins5Mu[i]);
  for(int i=0; i<nBinZpt; i++) histoResult[ 3][ 5]->SetBinContent(i+1,xbins5Syst3[i]/xbins5Mu[i]);
  for(int i=0; i<nBinZpt; i++) histoResult[ 4][ 5]->SetBinContent(i+1,xbins5Syst4[i]/xbins5Mu[i]);
  for(int i=0; i<nBinZpt; i++) histoResult[ 5][ 5]->SetBinContent(i+1,xbins5Syst5[i]/xbins5Mu[i]);
  for(int i=0; i<nBinZpt; i++) histoResult[ 6][ 5]->SetBinContent(i+1,xbins5Syst6[i]/xbins5Mu[i]);
  for(int i=0; i<nBinZpt; i++) histoResult[ 7][ 5]->SetBinContent(i+1,xbins5Syst7[i]/xbins5Mu[i]);
  for(int i=0; i<nBinZpt; i++) histoResult[ 8][ 5]->SetBinContent(i+1,xbins5Syst8[i]/xbins5Mu[i]);
  for(int i=0; i<nBinZpt; i++) histoResult[ 9][ 5]->SetBinContent(i+1,xbins5Syst9[i]/xbins5Mu[i]);
  for(int i=0; i<nBinZpt; i++) histoResult[10][ 5]->SetBinContent(i+1,xbins5totalSyst[i]/xbins5Mu[i]);
  for(int i=0; i<nBinZpt; i++) histoResult[11][ 5]->SetBinContent(i+1,xbins5daSyst[i]   /xbins5Mu[i]);
  for(int i=0; i<nBinZpt; i++) histoResult[12][ 5]->SetBinContent(i+1,xbins5Syst[i]     /xbins5Mu[i]);

  TString outNtuplename = Form("ZnnSystHist.root");
  TFile *outtuple = TFile::Open(outNtuplename.Data(),"recreate");
  outtuple->cd();
  for(int i=0; i<13; i++){
    for(int j=0; j<6; j++){
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
  histoResult[10][ 0]->SetMinimum(0.000);
  histoResult[10][ 0]->SetMaximum(0.149);
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

  TLegend* leg0 = new TLegend(0.20,0.63,0.50,0.91);						      
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
  TLatex *_extraLabel0 = new TLatex(0.9, 0.8, "#nu#nu channel");
  _extraLabel0->SetNDC();
  _extraLabel0->SetTextAlign(32);
  _extraLabel0->SetTextFont(42);
  _extraLabel0->SetTextSize(0.05);
  _extraLabel0->Draw("same");

  TString myOutputFile0 = Form("histoXS_Znn.pdf");
  c0->SaveAs(myOutputFile0.Data());

  theUncLabel = "1/#sigma d#sigma/dp^{Z}_{T}";
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
  histoResult[10][ 1]->SetMinimum(0.000);
  histoResult[10][ 1]->SetMaximum(0.149);
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

  TLegend* leg1 = new TLegend(0.20,0.63,0.50,0.91);						      
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
  TLatex *_extraLabel1 = new TLatex(0.9, 0.8, "#nu#nu channel");
  _extraLabel1->SetNDC();
  _extraLabel1->SetTextAlign(32);
  _extraLabel1->SetTextFont(42);
  _extraLabel1->SetTextSize(0.05);
  _extraLabel1->Draw("same");

  TString myOutputFile1 = Form("histoXSnorm_Znn.pdf");
  c1->SaveAs(myOutputFile1.Data());

  theUncLabel = "d#sigma/dp^{Z}_{T}";
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
  histoResult[10][ 2]->SetMinimum(0.000);
  histoResult[10][ 2]->SetMaximum(0.149);
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

  TLegend* leg2 = new TLegend(0.20,0.63,0.50,0.91);						      
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
  TLatex *_extraLabel2 = new TLatex(0.9, 0.8, "#nu#nu+ll channel");
  _extraLabel2->SetNDC();
  _extraLabel2->SetTextAlign(32);
  _extraLabel2->SetTextFont(42);
  _extraLabel2->SetTextSize(0.05);
  _extraLabel2->Draw("same");

  TString myOutputFile2 = Form("histoXS_Zxx.pdf");
  c2->SaveAs(myOutputFile2.Data());

  theUncLabel = "1/#sigma d#sigma/dp^{Z}_{T}";
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
  histoResult[10][ 3]->SetMinimum(0.000);
  histoResult[10][ 3]->SetMaximum(0.149);
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

  TLegend* leg3 = new TLegend(0.20,0.63,0.50,0.91);						      
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
  TLatex *_extraLabel3 = new TLatex(0.9, 0.8, "#nu#nu+ll channel");
  _extraLabel3->SetNDC();
  _extraLabel3->SetTextAlign(32);
  _extraLabel3->SetTextFont(42);
  _extraLabel3->SetTextSize(0.05);
  _extraLabel3->Draw("same");

  TString myOutputFile3 = Form("histoXSnorm_Zxx.pdf");
  c3->SaveAs(myOutputFile3.Data());

  theUncLabel = "d#sigma/dp^{Z}_{T}";
  TCanvas* c4 = new TCanvas("c4", "c4",5,5,500,500);
  c4->cd();
  atributes(histoResult[ 0][ 4],XName.Data(), 1,Form("Uncertainty in %s",theUncLabel.Data()), 1);
  atributes(histoResult[ 1][ 4],XName.Data(), 2,Form("Uncertainty in %s",theUncLabel.Data()), 1);
  atributes(histoResult[ 2][ 4],XName.Data(), 3,Form("Uncertainty in %s",theUncLabel.Data()), 1);
  atributes(histoResult[ 3][ 4],XName.Data(), 4,Form("Uncertainty in %s",theUncLabel.Data()), 1);
  atributes(histoResult[ 4][ 4],XName.Data(), 5,Form("Uncertainty in %s",theUncLabel.Data()), 1);
  atributes(histoResult[ 5][ 4],XName.Data(), 6,Form("Uncertainty in %s",theUncLabel.Data()), 1);
  atributes(histoResult[ 6][ 4],XName.Data(), 7,Form("Uncertainty in %s",theUncLabel.Data()), 1);
  atributes(histoResult[ 7][ 4],XName.Data(), 8,Form("Uncertainty in %s",theUncLabel.Data()), 1);
  atributes(histoResult[ 8][ 4],XName.Data(), 9,Form("Uncertainty in %s",theUncLabel.Data()), 1);
  atributes(histoResult[ 9][ 4],XName.Data(),46,Form("Uncertainty in %s",theUncLabel.Data()), 1);
  atributes(histoResult[10][ 4],XName.Data(),11,Form("Uncertainty in %s",theUncLabel.Data()), 1);
  atributes(histoResult[11][ 4],XName.Data(),12,Form("Uncertainty in %s",theUncLabel.Data()), 2);
  atributes(histoResult[12][ 4],XName.Data(),13,Form("Uncertainty in %s",theUncLabel.Data()), 3);
  histoResult[10][ 4]->SetMinimum(0.000);
  histoResult[10][ 4]->SetMaximum(0.149);
  histoResult[10][ 4]->Draw();
  histoResult[ 1][ 4]->Draw("same,hist");
  histoResult[ 2][ 4]->Draw("same,hist");
  histoResult[ 3][ 4]->Draw("same,hist");
  histoResult[ 4][ 4]->Draw("same,hist");
  histoResult[ 5][ 4]->Draw("same,hist");
  histoResult[ 6][ 4]->Draw("same,hist");
  histoResult[ 7][ 4]->Draw("same,hist");
  histoResult[ 8][ 4]->Draw("same,hist");
  histoResult[ 9][ 4]->Draw("same,hist");
  histoResult[12][ 4]->Draw("same,hist");
  histoResult[11][ 4]->Draw("same,hist");

  CMSLabel->Draw("same");
  _lumiLabel->Draw ("same") ;

  TLegend* leg4 = new TLegend(0.20,0.63,0.50,0.91);						      
  leg4 ->SetFillStyle(0);
  leg4 ->SetFillColor(kWhite);
  leg4 ->SetBorderSize(0);
  leg4->SetTextSize(0.025);									   
  leg4->AddEntry(histoResult[10][ 4],"Total uncertainty","l");
  leg4->AddEntry(histoResult[ 0][ 4],"MC statistical","l");
  leg4->AddEntry(histoResult[ 1][ 4],"Luminosity","l");
  leg4->AddEntry(histoResult[ 2][ 4],"Jet energy scale","l");
  leg4->AddEntry(histoResult[ 3][ 4],"Lepton efficiency","l");
  leg4->AddEntry(histoResult[ 4][ 4],"Theory","l");
  leg4->AddEntry(histoResult[ 5][ 4],"Lepton momentum resolution","l");
  leg4->AddEntry(histoResult[ 6][ 4],"Pileup","l");
  leg4->AddEntry(histoResult[ 7][ 4],"B tagging","l");
  leg4->AddEntry(histoResult[ 8][ 4],"Background normalization","l");
  leg4->AddEntry(histoResult[ 9][ 4],"Trigger efficiency","l");
  leg4->AddEntry(histoResult[11][ 4],"Data statistical","l");
  leg4->AddEntry(histoResult[12][ 4],"Total systematic","l");
  leg4->Draw();
  TLatex *_extralabel4 = new TLatex(0.9, 0.8, "ll channel");
  _extralabel4->SetNDC();
  _extralabel4->SetTextAlign(32);
  _extralabel4->SetTextFont(42);
  _extralabel4->SetTextSize(0.05);
  _extralabel4->Draw("same");

  TString myOutputFile4 = Form("histoXS_Zll.pdf");
  c4->SaveAs(myOutputFile4.Data());

  theUncLabel = "1/#sigma d#sigma/dp^{Z}_{T}";
  TCanvas* c5 = new TCanvas("c5", "c5",5,5,500,500);
  c5->cd();
  atributes(histoResult[ 0][ 5],XName.Data(), 1,Form("Uncertainty in %s",theUncLabel.Data()), 1);
  atributes(histoResult[ 1][ 5],XName.Data(), 2,Form("Uncertainty in %s",theUncLabel.Data()), 1);
  atributes(histoResult[ 2][ 5],XName.Data(), 3,Form("Uncertainty in %s",theUncLabel.Data()), 1);
  atributes(histoResult[ 3][ 5],XName.Data(), 4,Form("Uncertainty in %s",theUncLabel.Data()), 1);
  atributes(histoResult[ 4][ 5],XName.Data(), 5,Form("Uncertainty in %s",theUncLabel.Data()), 1);
  atributes(histoResult[ 5][ 5],XName.Data(), 6,Form("Uncertainty in %s",theUncLabel.Data()), 1);
  atributes(histoResult[ 6][ 5],XName.Data(), 7,Form("Uncertainty in %s",theUncLabel.Data()), 1);
  atributes(histoResult[ 7][ 5],XName.Data(), 8,Form("Uncertainty in %s",theUncLabel.Data()), 1);
  atributes(histoResult[ 8][ 5],XName.Data(), 9,Form("Uncertainty in %s",theUncLabel.Data()), 1);
  atributes(histoResult[ 9][ 5],XName.Data(),46,Form("Uncertainty in %s",theUncLabel.Data()), 1);
  atributes(histoResult[10][ 5],XName.Data(),11,Form("Uncertainty in %s",theUncLabel.Data()), 1);
  atributes(histoResult[11][ 5],XName.Data(),12,Form("Uncertainty in %s",theUncLabel.Data()), 2);
  atributes(histoResult[12][ 5],XName.Data(),13,Form("Uncertainty in %s",theUncLabel.Data()), 3);
  histoResult[10][ 5]->SetMinimum(0.000);
  histoResult[10][ 5]->SetMaximum(0.149);
  histoResult[10][ 5]->Draw();
  histoResult[ 1][ 5]->Draw("same,hist");
  histoResult[ 2][ 5]->Draw("same,hist");
  histoResult[ 3][ 5]->Draw("same,hist");
  histoResult[ 4][ 5]->Draw("same,hist");
  histoResult[ 5][ 5]->Draw("same,hist");
  histoResult[ 6][ 5]->Draw("same,hist");
  histoResult[ 7][ 5]->Draw("same,hist");
  histoResult[ 8][ 5]->Draw("same,hist");
  histoResult[ 9][ 5]->Draw("same,hist");
  histoResult[12][ 5]->Draw("same,hist");
  histoResult[11][ 5]->Draw("same,hist");

  CMSLabel->Draw("same");
  _lumiLabel->Draw ("same") ;

  TLegend* leg5 = new TLegend(0.20,0.63,0.50,0.91);						      
  leg5 ->SetFillStyle(0);
  leg5 ->SetFillColor(kWhite);
  leg5 ->SetBorderSize(0);
  leg5->SetTextSize(0.025);									   
  leg5->AddEntry(histoResult[10][ 5],"Total uncertainty","l");
  leg5->AddEntry(histoResult[ 0][ 5],"MC statistical","l");
  leg5->AddEntry(histoResult[ 1][ 5],"Luminosity","l");
  leg5->AddEntry(histoResult[ 2][ 5],"Jet energy scale","l");
  leg5->AddEntry(histoResult[ 3][ 5],"Lepton efficiency","l");
  leg5->AddEntry(histoResult[ 4][ 5],"Theory","l");
  leg5->AddEntry(histoResult[ 5][ 5],"Lepton momentum resolution","l");
  leg5->AddEntry(histoResult[ 6][ 5],"Pileup","l");
  leg5->AddEntry(histoResult[ 7][ 5],"B tagging","l");
  leg5->AddEntry(histoResult[ 8][ 5],"Background normalization","l");
  leg5->AddEntry(histoResult[ 9][ 5],"Trigger efficiency","l");
  leg5->AddEntry(histoResult[11][ 5],"Data statistical","l");
  leg5->AddEntry(histoResult[12][ 5],"Total systematic","l");
  leg5->Draw();
  TLatex *_extralabel5 = new TLatex(0.9, 0.8, "ll channel");
  _extralabel5->SetNDC();
  _extralabel5->SetTextAlign(32);
  _extralabel5->SetTextFont(42);
  _extralabel5->SetTextSize(0.05);
  _extralabel5->Draw("same");

  TString myOutputFile5 = Form("histoXSnorm_Zll.pdf");
  c5->SaveAs(myOutputFile5.Data());
}
