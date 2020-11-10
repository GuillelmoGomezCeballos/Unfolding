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

const int nGenSyst = 11;
const int nEffSyst = 11+480;
const int nStaSyst = 72;
const int nOthSyst = 2;

const int allNuisancesCov  = nGenSyst+nEffSyst+nStaSyst+nOthSyst;
const int allNuisancesPlot = 9;

void atributes(TH1D *histo, TString xtitle="", Int_t COLOR = 1, TString ytitle="Fraction", Int_t style = 1, Bool_t increaseSize = kFALSE){

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
  if(xtitle == "p^{Z}_{T} [GeV]")
  histo->GetXaxis()->SetTitleOffset( 1.02);
  else
  histo->GetXaxis()->SetTitleOffset( 1.02);
  if(!increaseSize)
  histo->GetXaxis()->SetTitleSize  (0.055);
  else
  histo->GetXaxis()->SetTitleSize  (0.055);

  histo->GetYaxis()->SetTitle(ytitle);
  histo->GetYaxis()->SetLabelFont  (   42);
  histo->GetYaxis()->SetLabelOffset(0.015);
  histo->GetYaxis()->SetLabelSize  (0.039);
  histo->GetYaxis()->SetNdivisions (  505);
  histo->GetYaxis()->SetTitleFont  (   42);
  histo->GetYaxis()->SetTitleOffset(  1.02);
  histo->GetYaxis()->SetTitleSize  (0.055);
  histo->SetLineColor(COLOR);
  histo->SetMarkerStyle(kFullDotLarge);
  histo->SetLineStyle(style);
  histo->SetLineWidth(5);
}
void helper_function(TString theSuffix, int nsel = 0, int whichDY = 3, TString theHistName = "Pt", bool doXSRatio = false, double lumiUnc = 0.025){

  bool isDebug = false;
  bool doCorrelateMomResLepEff = true;
  bool doMakeUseFixedSystUnf = true;

  const int nBinPt = 36; Float_t xbinsPt[nBinPt+1] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,16,18,20,22,25,28,32,37,43,52,65,85,120,160,190,220,250,300,400,500,800,1500};
  const int nBinRap = 12; Float_t xbinsRap[nBinRap+1] = {0.0,0.2,0.4,0.6,0.8,1.0,1.2,1.4,1.6,1.8,2.0,2.2,2.4};
  const int nBinPhiStar = 34; Float_t xbinsPhiStar[nBinPhiStar+1] = {
                                         1e-3, 2e-3, 3e-3, 4e-3, 5e-3, 6e-3, 7e-3, 8e-3, 9e-3,
                                         1e-2, 2e-2, 3e-2, 4e-2, 5e-2, 6e-2, 7e-2, 8e-2, 9e-2,
                                         1e-1, 2e-1, 3e-1, 4e-1, 5e-1, 6e-1, 7e-1, 8e-1, 9e-1,
                                            1,    3,    5,    7,   10,   20,   30,   50};
  const int nBinPtRap0 = 34; Float_t xbinsPtRap0[nBinPtRap0+1] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,16,18,20,22,25,28,32,37,43,52,65,85,120,160,190,220,250,300,400,1500};
  const int nBinPtRap1 = 34; Float_t xbinsPtRap1[nBinPtRap1+1] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,16,18,20,22,25,28,32,37,43,52,65,85,120,160,190,220,250,300,400,1500};
  const int nBinPtRap2 = 34; Float_t xbinsPtRap2[nBinPtRap2+1] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,16,18,20,22,25,28,32,37,43,52,65,85,120,160,190,220,250,300,400,1500};
  const int nBinPtRap3 = 34; Float_t xbinsPtRap3[nBinPtRap3+1] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,16,18,20,22,25,28,32,37,43,52,65,85,120,160,190,220,250,300,400,1500};
  const int nBinPtRap4 = 34; Float_t xbinsPtRap4[nBinPtRap4+1] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,16,18,20,22,25,28,32,37,43,52,65,85,120,160,190,220,250,300,400,1500};

  int version = 1; int alternative = 1;/*0*/
  if     (whichDY == 0) { version = 0; alternative = 0;/*1*/}
  else if(whichDY == 2) { version = 2; alternative = 2;/*1*/}
  else if(whichDY == 3) { version = 3; alternative = 3;/*0*/}
  TString theOutputName = Form("outputs%s%s_nsel%d",theSuffix.Data(),theHistName.Data(),nsel);

  TH1D *histoSystCov[allNuisancesCov], *histoSystPlot[allNuisancesPlot];
  if       (theHistName == "Pt"){
    for(int i=0; i<allNuisancesCov; i++)  histoSystCov[i]  = new TH1D(Form("histoSystCov_%d",i),  Form("histoSystCov_%d",i),  nBinPt, xbinsPt);
    for(int i=0; i<allNuisancesPlot; i++) histoSystPlot[i] = new TH1D(Form("histoSystPlot_%d",i), Form("histoSystPlot_%d",i), nBinPt, xbinsPt);

  } else if(theHistName == "Rap"){
    for(int i=0; i<allNuisancesCov; i++)  histoSystCov[i]  = new TH1D(Form("histoSystCov_%d",i),  Form("histoSystCov_%d",i),  nBinRap, xbinsRap);
    for(int i=0; i<allNuisancesPlot; i++) histoSystPlot[i] = new TH1D(Form("histoSystPlot_%d",i), Form("histoSystPlot_%d",i), nBinRap, xbinsRap);

  } else if(theHistName == "PhiStar"){
    for(int i=0; i<allNuisancesCov; i++)  histoSystCov[i]  = new TH1D(Form("histoSystCov_%d",i),  Form("histoSystCov_%d",i),  nBinPhiStar, xbinsPhiStar);
    for(int i=0; i<allNuisancesPlot; i++) histoSystPlot[i] = new TH1D(Form("histoSystPlot_%d",i), Form("histoSystPlot_%d",i), nBinPhiStar, xbinsPhiStar);

 } else if(theHistName == "PtRap0"){
    for(int i=0; i<allNuisancesCov; i++)  histoSystCov[i]  = new TH1D(Form("histoSystCov_%d",i),  Form("histoSystCov_%d",i),  nBinPtRap0, xbinsPtRap0);
    for(int i=0; i<allNuisancesPlot; i++) histoSystPlot[i] = new TH1D(Form("histoSystPlot_%d",i), Form("histoSystPlot_%d",i), nBinPtRap0, xbinsPtRap0);

  } else if(theHistName == "PtRap1"){
    for(int i=0; i<allNuisancesCov; i++)  histoSystCov[i]  = new TH1D(Form("histoSystCov_%d",i),  Form("histoSystCov_%d",i),  nBinPtRap1, xbinsPtRap1);
    for(int i=0; i<allNuisancesPlot; i++) histoSystPlot[i] = new TH1D(Form("histoSystPlot_%d",i), Form("histoSystPlot_%d",i), nBinPtRap1, xbinsPtRap1);

  } else if(theHistName == "PtRap2"){
    for(int i=0; i<allNuisancesCov; i++)  histoSystCov[i]  = new TH1D(Form("histoSystCov_%d",i),  Form("histoSystCov_%d",i),  nBinPtRap2, xbinsPtRap2);
    for(int i=0; i<allNuisancesPlot; i++) histoSystPlot[i] = new TH1D(Form("histoSystPlot_%d",i), Form("histoSystPlot_%d",i), nBinPtRap2, xbinsPtRap2);

  } else if(theHistName == "PtRap3"){
    for(int i=0; i<allNuisancesCov; i++)  histoSystCov[i]  = new TH1D(Form("histoSystCov_%d",i),  Form("histoSystCov_%d",i),  nBinPtRap3, xbinsPtRap3);
    for(int i=0; i<allNuisancesPlot; i++) histoSystPlot[i] = new TH1D(Form("histoSystPlot_%d",i), Form("histoSystPlot_%d",i), nBinPtRap3, xbinsPtRap3);

  } else if(theHistName == "PtRap4"){
    for(int i=0; i<allNuisancesCov; i++)  histoSystCov[i]  = new TH1D(Form("histoSystCov_%d",i),  Form("histoSystCov_%d",i),  nBinPtRap4, xbinsPtRap4);
    for(int i=0; i<allNuisancesPlot; i++) histoSystPlot[i] = new TH1D(Form("histoSystPlot_%d",i), Form("histoSystPlot_%d",i), nBinPtRap4, xbinsPtRap4);

 } else {
    printf("Wrong option!\n");
    return;
  }

  //TStyle *MITStyle = new TStyle("MIT-Style","MIT-Style");
  //MITStyle->SetOptStat(0);
  //gStyle = MITStyle;

  TFile *_fileDef= TFile::Open(Form("%s/dy%d/histoUnfolding%s_nsel%d_dy%d_rebin1_default.root",theOutputName.Data(),version,theHistName.Data(),nsel,version)); // default NLO/LO
  TH1D* histDef       = (TH1D*)_fileDef->Get(Form("unfold"));
  TH1D* histDefNoLumi = (TH1D*)histDef->Clone("unfoldNoLumi");

  TFile *_file[allNuisancesCov];
  TH1D* histAlt[allNuisancesCov-2];

  _file[0] = TFile::Open(Form("%s/dy%d/histoUnfolding%s_nsel%d_dy%d_rebin1_default.root",theOutputName.Data(),alternative,theHistName.Data(),nsel,alternative)); // alternative LO/NLO
  _file[1] = TFile::Open(Form("%s/dy%d/histoUnfolding%s_nsel%d_dy%d_rebin1_momres1.root",theOutputName.Data(),version,theHistName.Data(),nsel,version)); // MonRes1
  if(doCorrelateMomResLepEff == false){
  _file[2] = TFile::Open(Form("%s/dy%d/histoUnfolding%s_nsel%d_dy%d_rebin1_momres2.root",theOutputName.Data(),version,theHistName.Data(),nsel,version)); // MonRes2
  _file[3] = TFile::Open(Form("%s/dy%d/histoUnfolding%s_nsel%d_dy%d_rebin1_momres3.root",theOutputName.Data(),version,theHistName.Data(),nsel,version)); // MonRes3
  }
  else if(doCorrelateMomResLepEff == true && nsel == 0){ // swap not a mistake, it is to make momreslepeff in the same position for muons and electrons
  _file[2] = TFile::Open(Form("%s/dy%d/histoUnfolding%s_nsel%d_dy%d_rebin1_momreslepeff.root",theOutputName.Data(),version,theHistName.Data(),nsel,version)); // MonRes3
  _file[3] = TFile::Open(Form("%s/dy%d/histoUnfolding%s_nsel%d_dy%d_rebin1_momres2.root",theOutputName.Data(),version,theHistName.Data(),nsel,version)); // MonRes2
  }
  else if(doCorrelateMomResLepEff == true && nsel == 1){
  _file[2] = TFile::Open(Form("%s/dy%d/histoUnfolding%s_nsel%d_dy%d_rebin1_momreslepeff.root",theOutputName.Data(),version,theHistName.Data(),nsel,version)); // MonRes2
  _file[3] = TFile::Open(Form("%s/dy%d/histoUnfolding%s_nsel%d_dy%d_rebin1_momres3.root",theOutputName.Data(),version,theHistName.Data(),nsel,version)); // MonRes3
  }
  _file[4] = TFile::Open(Form("%s/dy%d/histoUnfolding%s_nsel%d_dy%d_rebin1_momres4.root",theOutputName.Data(),version,theHistName.Data(),nsel,version)); // MonRes4
  _file[5] = TFile::Open(Form("%s/dy%d/histoUnfolding%s_nsel%d_dy%d_rebin1_pdf.root",theOutputName.Data(),version,theHistName.Data(),nsel,version)); // PDF bkg
  _file[6] = TFile::Open(Form("%s/dy%d/histoUnfolding%s_nsel%d_dy%d_rebin1_qcd.root",theOutputName.Data(),version,theHistName.Data(),nsel,version)); // QCD bkg.
  _file[7] = TFile::Open(Form("%s/dy%d/histoUnfolding%s_nsel%d_dy%d_rebin1_receff0.root",theOutputName.Data(),version,theHistName.Data(),nsel,version)); // RecEff0
  _file[8] = TFile::Open(Form("%s/dy%d/histoUnfolding%s_nsel%d_dy%d_rebin1_receff1.root",theOutputName.Data(),version,theHistName.Data(),nsel,version)); // RecEff1
  _file[9] = TFile::Open(Form("%s/dy%d/histoUnfolding%s_nsel%d_dy%d_rebin1_receff2.root",theOutputName.Data(),version,theHistName.Data(),nsel,version)); // RecEff2
  _file[10]= TFile::Open(Form("%s/dy%d/histoUnfolding%s_nsel%d_dy%d_rebin1_receff3.root",theOutputName.Data(),version,theHistName.Data(),nsel,version)); // RecEff3
  for(int i=0; i<nGenSyst; i++){
    histAlt[i] = (TH1D*)_file[i] ->Get(Form("unfold")); assert(histAlt[i]); histAlt[i]->SetDirectory(0);
    _file[i]->Close();
  }

  for(int i=0; i<nEffSyst; i++){
    _file[i+nGenSyst]  = TFile::Open(Form("%s/dy%d/histoUnfolding%s_nsel%d_dy%d_rebin1_lepeff%d.root",theOutputName.Data(),version,theHistName.Data(),nsel,version,i));
    histAlt[i+nGenSyst] = (TH1D*)_file[i+nGenSyst] ->Get(Form("unfold")); assert(histAlt[i+nGenSyst]); histAlt[i+nGenSyst]->SetDirectory(0);
    _file[i+nGenSyst]->Close();
  }

  for(int i=0; i<nStaSyst; i++){
    _file[i+nGenSyst+nEffSyst]  = TFile::Open(Form("%s/dy%d/histoUnfolding%s_nsel%d_dy%d_rebin1_sigstat%d.root",theOutputName.Data(),version,theHistName.Data(),nsel,version,i));
    histAlt[i+nGenSyst+nEffSyst] = (TH1D*)_file[i+nGenSyst+nEffSyst] ->Get(Form("unfold")); assert(histAlt[i+nGenSyst+nEffSyst]); histAlt[i+nGenSyst+nEffSyst]->SetDirectory(0);
    _file[i+nGenSyst+nEffSyst]->Close();
  }

  TString label="MM";
  if (nsel==1){label="EE";}
  TH1D* histPred     = (TH1D*)_fileDef->Get(Form("hDDil%s%s",theHistName.Data(),label.Data()));
  TH1D* histPredStat = (TH1D*)histPred->Clone(Form("hDDil%s%s_Stat",theHistName.Data(),label.Data()));
  TH1D* histPred_PDF = (TH1D*)_fileDef->Get(Form("hDDil%s%s_PDF",theHistName.Data(),label.Data()));
  TH1D* histPred_QCD = (TH1D*)_fileDef->Get(Form("hDDil%s%s_QCD",theHistName.Data(),label.Data()));

  double systVal[allNuisancesCov],systTotalVal;

                       // receff/lepeff2/lepeff3/lepeff4/leff5/lepeff6/lepeff7/lepeff8/lepeff8/lepeff10/lumi
  double systXSValMM[11] = {0.378, 0.062, 0.192, 0.548, 0.246, 0.183, 0.059, 0.001, 0.035, 0.115, 2.500};
  double systXSValEE[11] = {0.932, 0.104, 0.058, 0.578, 0.509, 0.385, 0.192, 0.004, 0.111, 0.419, 2.500};
  double systXSVal[11];
  for(int ns=0; ns<11; ns++){
    if     (nsel == 0) systXSVal[ns] = systXSValMM[ns];
    else if(nsel == 1) systXSVal[ns] = systXSValEE[ns];
  }

  double systUnfVal[16] = {
0.140,
0.140,
0.150,
0.150,
0.130,
0.130,
0.160,
0.160,
0.110,
0.110,
0.130,
0.130,
0.140,
0.140,
0.130,
0.130
};
  double theSystUnfVal = 0.0;
  if     (theHistName == "Pt"      && nsel == 0) theSystUnfVal = systUnfVal[ 0];
  else if(theHistName == "Pt"      && nsel == 1) theSystUnfVal = systUnfVal[ 1];
  else if(theHistName == "Rap"     && nsel == 0) theSystUnfVal = systUnfVal[ 2];
  else if(theHistName == "Rap"     && nsel == 1) theSystUnfVal = systUnfVal[ 3];
  else if(theHistName == "PhiStar" && nsel == 0) theSystUnfVal = systUnfVal[ 4];
  else if(theHistName == "PhiStar" && nsel == 1) theSystUnfVal = systUnfVal[ 5];
  else if(theHistName == "PtRap0"  && nsel == 0) theSystUnfVal = systUnfVal[ 6];
  else if(theHistName == "PtRap0"  && nsel == 1) theSystUnfVal = systUnfVal[ 7];
  else if(theHistName == "PtRap1"  && nsel == 0) theSystUnfVal = systUnfVal[ 8];
  else if(theHistName == "PtRap1"  && nsel == 1) theSystUnfVal = systUnfVal[ 9];
  else if(theHistName == "PtRap2"  && nsel == 0) theSystUnfVal = systUnfVal[10];
  else if(theHistName == "PtRap2"  && nsel == 1) theSystUnfVal = systUnfVal[11];
  else if(theHistName == "PtRap3"  && nsel == 0) theSystUnfVal = systUnfVal[12];
  else if(theHistName == "PtRap3"  && nsel == 1) theSystUnfVal = systUnfVal[13];
  else if(theHistName == "PtRap4"  && nsel == 0) theSystUnfVal = systUnfVal[14];
  else if(theHistName == "PtRap4"  && nsel == 1) theSystUnfVal = systUnfVal[15];
  else {printf("WRONG OPTION\n"); return;}

  printf("       unf     monres1 monres2 monres3 momres4 PDF     QCD     receff  lepeffstat    lepeffsyst mcstat  dastat  lumi       total\n");
  for(int i=1; i<=histDef->GetNbinsX(); i++){
    for(int j=0; j<allNuisancesCov-2; j++){
      systVal[j] = 100.*TMath::Abs(histDef->GetBinContent(i)-histAlt[j]->GetBinContent(i))/histDef->GetBinContent(i);
    }

    // Function smoothing
    bool useFunctionSmoothing = true;
    if(useFunctionSmoothing == true) {
      if     (theHistName == "Pt" && nsel == 1 && histDef->GetBinCenter(i) < 40){
	systVal[1] = 1.09213e+03*TMath::Landau(histDef->GetBinCenter(i),-8.41567e+01,3.36612e+00)/2;
	systVal[2] = 1.09213e+03*TMath::Landau(histDef->GetBinCenter(i),-8.41567e+01,3.36612e+00)/2;
      }
      else if(theHistName == "PtRap0" && nsel == 1 && histDef->GetBinCenter(i) < 40){
	systVal[1] = 1.87297e+03*TMath::Landau(histDef->GetBinCenter(i),-4.11103e+01,8.53311e-01)/2;
	systVal[2] = 1.87297e+03*TMath::Landau(histDef->GetBinCenter(i),-4.11103e+01,8.53311e-01)/2;
      }
      else if(theHistName == "PtRap1" && nsel == 1 && histDef->GetBinCenter(i) < 20){
	systVal[1] = 2.21103e+03*TMath::Landau(histDef->GetBinCenter(i),-1.12350e+01,4.42520e-01)/2;
	systVal[2] = 2.21103e+03*TMath::Landau(histDef->GetBinCenter(i),-1.12350e+01,4.42520e-01)/2;
      }
      else if(theHistName == "PtRap2" && nsel == 1 && histDef->GetBinCenter(i) < 30){
	systVal[1] = 4.94505e+03*TMath::Landau(histDef->GetBinCenter(i),-2.64711e+01,6.50964e-01)/2;
	systVal[2] = 4.94505e+03*TMath::Landau(histDef->GetBinCenter(i),-2.64711e+01,6.50964e-01)/2;
      }
      else if(theHistName == "PtRap2" && nsel == 1 && i>=histDef->GetNbinsX()-1){
	systVal[1] = 100.*TMath::Abs(histDef->GetBinContent(i-1)-histAlt[1]->GetBinContent(i-1))/histDef->GetBinContent(i-1);
	systVal[2] = 100.*TMath::Abs(histDef->GetBinContent(i-1)-histAlt[2]->GetBinContent(i-1))/histDef->GetBinContent(i-1);
      }
      else if(theHistName == "PtRap3" && nsel == 1 && histDef->GetBinCenter(i) < 30){
	systVal[1] = 6.26987e+02*TMath::Landau(histDef->GetBinCenter(i),-3.89846e+01,2.89295e+00)/2;
	systVal[2] = 6.26987e+02*TMath::Landau(histDef->GetBinCenter(i),-3.89846e+01,2.89295e+00)/2;
      }
      else if(theHistName == "PtRap4" && nsel == 1 && histDef->GetBinCenter(i) < 30){
	systVal[1] = 9.71435e+03*TMath::Landau(histDef->GetBinCenter(i),-3.34539e+01,7.61375e-01)/2;
	systVal[2] = 9.71435e+03*TMath::Landau(histDef->GetBinCenter(i),-3.34539e+01,7.61375e-01)/2;
      }
    }

    if(doMakeUseFixedSystUnf == true) systVal[0] = theSystUnfVal;

    if(nsel == 1) {systVal[3] =0; systVal[4] =0;}

    //if(systVal[1] > 3.0 && i < 20) systVal[1] = 3.0 + gRandom->Rndm()*0.5;
    //if(systVal[2] > 3.0 && i < 20) systVal[2] = 3.0 + gRandom->Rndm()*0.5;
    //if(systVal[3] > 3.0 && i < 20) systVal[3] = 3.0 + gRandom->Rndm()*0.5;
    systVal[allNuisancesCov-2] = 100.*histDef->GetBinError(i)/histDef->GetBinContent(i); // data stat
    systVal[allNuisancesCov-1] = 100.*lumiUnc;

    if(doCorrelateMomResLepEff == true) systVal[nGenSyst+3] = 0;

    // reco efficiencies all together
    systVal[7 ] = sqrt(systVal[7 ]*systVal[7 ]+systVal[8 ]*systVal[8 ]+systVal[9 ]*systVal[9 ]+systVal[10]*systVal[10]);
    systVal[8 ] = 0.0;
    systVal[9 ] = 0.0;
    systVal[10] = 0.0;

    if(doXSRatio){
      systVal[0 ] = 0;
      systVal[7 ] = TMath::Abs(systVal[7 ] - systXSVal[0]);
      systVal[13] = TMath::Abs(systVal[13] - systXSVal[1]);
      if(doCorrelateMomResLepEff == false) systVal[14] = TMath::Abs(systVal[14] - systXSVal[2]);
      else                                 systVal[2 ] = TMath::Abs(systVal[2 ] - systXSVal[2]);
      systVal[15] = TMath::Abs(systVal[15] - systXSVal[3]);
      systVal[16] = TMath::Abs(systVal[16] - systXSVal[4]);
      systVal[17] = TMath::Abs(systVal[17] - systXSVal[5]);
      systVal[18] = TMath::Abs(systVal[18] - systXSVal[6]);
      systVal[19] = TMath::Abs(systVal[19] - systXSVal[7]);
      systVal[20] = TMath::Abs(systVal[20] - systXSVal[8]);
      systVal[21] = TMath::Abs(systVal[21] - systXSVal[9]);
      systVal[allNuisancesCov-1] = TMath::Abs(systVal[allNuisancesCov-1] - systXSVal[10]);
    }

    double systEffValStaAtOnce = systVal[12];
    double systEffValNoStat = sqrt(systVal[nGenSyst+2]*systVal[nGenSyst+2]+systVal[nGenSyst+3]*systVal[nGenSyst+3]+systVal[nGenSyst+ 4]*systVal[nGenSyst+ 4]+
                                   systVal[nGenSyst+5]*systVal[nGenSyst+5]+systVal[nGenSyst+6]*systVal[nGenSyst+6]+systVal[nGenSyst+ 7]*systVal[nGenSyst+ 7]+
                                   systVal[nGenSyst+8]*systVal[nGenSyst+8]+systVal[nGenSyst+9]*systVal[nGenSyst+9]+systVal[nGenSyst+10]*systVal[nGenSyst+10]);

    systVal[11] = 0; systVal[12] = 0; // make sure not used anymore
    double systEffValSta = 0;
    for(int k=nGenSyst+7; k<nGenSyst+nEffSyst; k++) systEffValSta = systEffValSta + systVal[k]*systVal[k];
    systEffValSta = sqrt(systEffValSta);

    double systMCValSta = 0;
    for(int k=nGenSyst+nEffSyst; k<nGenSyst+nEffSyst+nStaSyst; k++) systMCValSta = systMCValSta + systVal[k]*systVal[k];
    systMCValSta = sqrt(systMCValSta);

    // Remove double counting uncertainties
    if(nsel == 1 && theSuffix == "LL"){
      systVal[0] = 0;
      systMCValSta = 0;
      systVal[5] = 0;
      systVal[6] = 0;
      systVal[allNuisancesCov-2] = 0;
      systVal[allNuisancesCov-1] = 0;
    }
    systVal[allNuisancesCov-2] = 0;

    for(int j=0; j<allNuisancesCov; j++) {histoSystCov[j]->SetBinContent(i,systVal[j]/100.);}

    histoSystPlot[1]->SetBinContent(i,sqrt(systVal[0]*systVal[0]+systMCValSta*systMCValSta)); // unfolding + mc stat
    histoSystPlot[2]->SetBinContent(i,sqrt(systVal[1]*systVal[1]+systVal[2]*systVal[2]+systVal[3]*systVal[3]+systVal[4]*systVal[4])); // momres
    histoSystPlot[3]->SetBinContent(i,sqrt(systVal[5]*systVal[5]+systVal[6]*systVal[6])); // Bkg.
    histoSystPlot[4]->SetBinContent(i,sqrt(systEffValNoStat*systEffValNoStat+systEffValSta*systEffValSta)); // LepEff
    histoSystPlot[5]->SetBinContent(i,systVal[7]); // RecEff
    histoSystPlot[6]->SetBinContent(i,systVal[allNuisancesCov-2]); // data stat
    histoSystPlot[7]->SetBinContent(i,systVal[allNuisancesCov-1]); // lumi

    histoSystPlot[0]->SetBinContent(i,sqrt(histoSystPlot[1]->GetBinContent(i)*histoSystPlot[1]->GetBinContent(i)+
                                           histoSystPlot[2]->GetBinContent(i)*histoSystPlot[2]->GetBinContent(i)+
                                           histoSystPlot[3]->GetBinContent(i)*histoSystPlot[3]->GetBinContent(i)+
                                           histoSystPlot[5]->GetBinContent(i)*histoSystPlot[5]->GetBinContent(i)+
                                           histoSystPlot[4]->GetBinContent(i)*histoSystPlot[4]->GetBinContent(i)+
                                           histoSystPlot[6]->GetBinContent(i)*histoSystPlot[6]->GetBinContent(i)+
                                           histoSystPlot[7]->GetBinContent(i)*histoSystPlot[7]->GetBinContent(i)
                                           ));

    histoSystPlot[8]->SetBinContent(i,sqrt(histoSystPlot[1]->GetBinContent(i)*histoSystPlot[1]->GetBinContent(i)+
                                           histoSystPlot[2]->GetBinContent(i)*histoSystPlot[2]->GetBinContent(i)+
                                           histoSystPlot[3]->GetBinContent(i)*histoSystPlot[3]->GetBinContent(i)+
                                           histoSystPlot[5]->GetBinContent(i)*histoSystPlot[5]->GetBinContent(i)+
                                           histoSystPlot[4]->GetBinContent(i)*histoSystPlot[4]->GetBinContent(i)+
                                           histoSystPlot[6]->GetBinContent(i)*histoSystPlot[6]->GetBinContent(i)
                                           ));//except for lumi
    printf("(%2d) %7.3f %7.3f %7.3f %7.3f %7.3f %7.3f %7.3f %7.3f %7.3f(%7.3f) %7.3f %7.3f %7.3f %7.3f -> %7.3f\n",i,
            systVal[0],systVal[1],systVal[2],systVal[3],systVal[4],systVal[5],systVal[6],systVal[7],
            systEffValSta,systEffValStaAtOnce,systEffValNoStat,systMCValSta,systVal[allNuisancesCov-2],systVal[allNuisancesCov-1],
            histoSystPlot[0]->GetBinContent(i));
  }

  // This is a beast
  if(!doXSRatio || (theHistName.Contains("Pt") && theHistName != "dPt")){
    histoSystPlot[0]->Smooth();
    histoSystPlot[1]->Smooth();
    histoSystPlot[2]->Smooth();
    histoSystPlot[3]->Smooth();
    histoSystPlot[5]->Smooth();
    histoSystPlot[4]->Smooth();
    histoSystPlot[6]->Smooth();
    histoSystPlot[7]->Smooth();
    histoSystPlot[8]->Smooth();
  }

  TString theXSRatioName = "";
  if(doXSRatio) theXSRatioName = "_XSRatio";
  // All information to a file
  for(int i=1; i<=histDef->GetNbinsX(); i++){
    histDef      ->SetBinError(i,histDef->GetBinContent(i)*histoSystPlot[0]->GetBinContent(i)/100.);
    histDefNoLumi->SetBinError(i,histDef->GetBinContent(i)*histoSystPlot[8]->GetBinContent(i)/100.);
  }
  for(Int_t i=1;i<=histPred->GetNbinsX();++i){
    double diff[3] = {histPred->GetBinError(i), histPred_PDF->GetBinContent(i)-histPred->GetBinContent(i), histPred_QCD->GetBinContent(i)-histPred->GetBinContent(i)};
    histPred    ->SetBinError(i,sqrt(diff[0]*diff[0]+diff[1]*diff[1]+diff[2]*diff[2]));
    histPredStat->SetBinError(i,diff[0]);
    if(isDebug) printf("histPredSyst (%2d) %5.2f %5.2f %5.2f -> %5.2f\n",i,100*diff[0]/histPred->GetBinContent(i),100*diff[1]/histPred->GetBinContent(i),100*diff[2]/histPred->GetBinContent(i),100*histPred->GetBinError(i)/histPred->GetBinContent(i));
  }

  char output[200];
  sprintf(output,"histoUnfolding%sSyst%s%s_nsel%d_dy%d_rebin1_default.root",theXSRatioName.Data(),theSuffix.Data(),theHistName.Data(),nsel,whichDY); 
  TFile* outFilePlots = new TFile(output,"recreate");
  outFilePlots->cd();

  histDef      ->Write();
  histDefNoLumi->Write();
  histPred     ->Write();
  histPredStat ->Write();

  for(int i=0; i<allNuisancesCov; i++) histoSystCov[i]->Write();
  for(int i=0; i<allNuisancesPlot; i++) histoSystPlot[i]->Write();

  outFilePlots->Close();

  TString theUncLabel = "d#sigma/dp^{Z}_{T}";
  if	 (doXSRatio  && theHistName == "Rap")	  theUncLabel = "1/#sigma d#sigma/dy^{Z}";
  else if(doXSRatio  && theHistName == "PhiStar") theUncLabel = "1/#sigma d#sigma/d#phi_{#eta}*";
  else if(doXSRatio)				  theUncLabel = "1/#sigma d#sigma/dp^{Z}_{T}";
  else if(!doXSRatio && theHistName == "Rap")	  theUncLabel = "d#sigma/dy^{Z}";
  else if(!doXSRatio && theHistName == "PhiStar") theUncLabel = "d#sigma/d#phi_{#eta}*";

  // Printing information
  Bool_t increaseSize = kFALSE;
  TString XName = "p^{Z}_{T} [GeV]";
  if     (theHistName == "Rap") XName = "|y^{Z}|";
  else if(theHistName == "PhiStar") {XName = "#phi_{#eta}*"; increaseSize = kTRUE;}
  atributes(histoSystPlot[0],XName.Data(), 1,Form("Uncertainty in %s (%%)",theUncLabel.Data()), 1, increaseSize);
  atributes(histoSystPlot[1],XName.Data(), 2,Form("Uncertainty in %s (%%)",theUncLabel.Data()), 2, increaseSize);
  atributes(histoSystPlot[2],XName.Data(), 4,Form("Uncertainty in %s (%%)",theUncLabel.Data()), 3, increaseSize);
  atributes(histoSystPlot[3],XName.Data(),40,Form("Uncertainty in %s (%%)",theUncLabel.Data()), 4, increaseSize);
  atributes(histoSystPlot[4],XName.Data(),46,Form("Uncertainty in %s (%%)",theUncLabel.Data()), 5, increaseSize);
  atributes(histoSystPlot[5],XName.Data(),49,Form("Uncertainty in %s (%%)",theUncLabel.Data()), 6, increaseSize);
  //atributes(histoSystPlot[6],XName.Data(), 8,Form("Uncertainty in %s (%%)",theUncLabel.Data()), 7, increaseSize);
  atributes(histoSystPlot[7],XName.Data(),11,Form("Uncertainty in %s (%%)",theUncLabel.Data()), 8, increaseSize);
  atributes(histoSystPlot[8],XName.Data(),46,Form("Uncertainty in %s (%%)",theUncLabel.Data()), 9, increaseSize);

  TCanvas* c1 = new TCanvas("c1", "c1",5,5,500,500);
  c1->cd();
  if(theHistName != "Rap") c1->SetLogx();

  histoSystPlot[0]->SetMinimum(0.0);
  if     (theHistName == "Rap" && doXSRatio == false)     histoSystPlot[0]->SetMaximum( 6.0);
  else if(theHistName == "PhiStar" && doXSRatio == false) histoSystPlot[0]->SetMaximum( 6.0);
  else if(theHistName == "Rap" && doXSRatio == true)      histoSystPlot[0]->SetMaximum( 4.0);
  else if(theHistName == "PhiStar" && doXSRatio == true)  histoSystPlot[0]->SetMaximum( 3.0);
  else                                                    histoSystPlot[0]->SetMaximum(16.0);
  histoSystPlot[0]->Draw();
  histoSystPlot[1]->Draw("same,hist");
  histoSystPlot[2]->Draw("same,hist");
  histoSystPlot[3]->Draw("same,hist");
  histoSystPlot[4]->Draw("same,hist");
  histoSystPlot[5]->Draw("same,hist");
  histoSystPlot[6]->Draw("same,hist");
  if(!doXSRatio) histoSystPlot[7]->Draw("same,hist");

  TLatex * CMSLabel = new TLatex (0.15, 0.93, "#bf{CMS} #scale[0.75]{#it{Projection}}");
  //TLatex * CMSLabel = new TLatex (0.15, 0.93, "#bf{CMS}");
  CMSLabel->SetNDC ();
  CMSLabel->SetTextAlign (10);
  CMSLabel->SetTextFont (42);
  CMSLabel->SetTextSize (0.04);
  CMSLabel->Draw ("same") ;
  TLatex * _lumiLabel = new TLatex (0.95, 0.93, "13 TeV");
  //TLatex * _lumiLabel = new TLatex (0.95, 0.93, "35.9 fb^{-1} (13 TeV)");
  _lumiLabel->SetNDC ();
  _lumiLabel->SetTextAlign (30);
  _lumiLabel->SetTextFont (42);
  _lumiLabel->SetTextSize (0.04);
  _lumiLabel->Draw ("same") ;
  TLegend* leg = new TLegend(0.20,0.60,0.50,0.90);                                                    
  leg ->SetFillStyle(0);
  leg ->SetFillColor(kWhite);
  leg ->SetBorderSize(0);
  leg->SetTextSize(0.035);                                                                         
  leg->AddEntry(histoSystPlot[0],"Total uncertainty","l");
  leg->AddEntry(histoSystPlot[1],"Unfolding","l");
  leg->AddEntry(histoSystPlot[2],"Momentum resolution","l");
  leg->AddEntry(histoSystPlot[3],"Background","l");
  leg->AddEntry(histoSystPlot[4],"Identification & trigger","l");
  leg->AddEntry(histoSystPlot[5],"Reconstruction","l");
  //leg->AddEntry(histoSystPlot[6],"Statistical","l");
  if(!doXSRatio) leg->AddEntry(histoSystPlot[7],"Integrated luminosity","l");
  leg->Draw();
  if(1){
    TString theLabel = "";
    TString leptonLegend = "#mu^{+}#mu^{-} sample";
    if(nsel == 1) leptonLegend = "e^{+}e^{-} sample";
    if     (theHistName == "PtRap0") theLabel = Form("#splitline{0 < |y^{l^{+}l^{-}}| < 0.4}{%s}",leptonLegend.Data());
    else if(theHistName == "PtRap1") theLabel = Form("#splitline{0.4 < |y^{l^{+}l^{-}}| < 0.8}{%s}",leptonLegend.Data());
    else if(theHistName == "PtRap2") theLabel = Form("#splitline{0.8 < |y^{l^{+}l^{-}}| < 1.2}{%s}",leptonLegend.Data());
    else if(theHistName == "PtRap3") theLabel = Form("#splitline{1.2 < |y^{l^{+}l^{-}}| < 1.6}{%s}",leptonLegend.Data());
    else if(theHistName == "PtRap4") theLabel = Form("#splitline{1.6 < |y^{l^{+}l^{-}}| < 2.4}{%s}",leptonLegend.Data());
    else if(nsel == 0              ) theLabel = leptonLegend.Data();
    else if(nsel == 1              ) theLabel = leptonLegend.Data();
    TLatex *_extraLabel = new TLatex(0.85, 0.8, theLabel.Data());
    _extraLabel->SetNDC();
    _extraLabel->SetTextAlign(32);
    _extraLabel->SetTextFont(42);
    _extraLabel->SetTextSize(0.05);
    _extraLabel->Draw("same");
  }

  TString myOutputFile = Form("histoUnfolding%sSyst%s%s_nsel%d_dy%d.pdf",theXSRatioName.Data(),theSuffix.Data(),theHistName.Data(),nsel,whichDY);
  c1->SaveAs(myOutputFile.Data());


}
void makeSystHist_UPSG(TString theSuffix, TString theHistName = "Pt", double lumiUnc = 0.025){
  if(theSuffix != "LL") theSuffix = "";
  char output[200];
  for (int j=3;j<=3;j++){ // dy versions
    for (int nr=0; nr<=0; nr++) {
      TString theXSRatioName = "";
      if(nr == 1) theXSRatioName = "_XSRatio";
      for (int i=0; i<=1; i++){
        printf("Parameters: %s %d %d %s %d\n",theSuffix.Data(),i,j,theHistName.Data(),nr);
        helper_function(theSuffix.Data(), i, j, theHistName, nr, lumiUnc);
      }
      if(theSuffix == "LL"){
	sprintf(output,"histoUnfolding%sSyst%s%s_nsel%d_dy%d_rebin1_default.root",theXSRatioName.Data(),theSuffix.Data(),theHistName.Data(),0,j); 
	TFile* inpFilePlots0 = TFile::Open(output);
	sprintf(output,"histoUnfolding%sSyst%s%s_nsel%d_dy%d_rebin1_default.root",theXSRatioName.Data(),theSuffix.Data(),theHistName.Data(),1,j); 
	TFile* inpFilePlots1 = TFile::Open(output);

	TH1D* histDef0       = (TH1D*)inpFilePlots0->Get("unfold"                                 );
	TH1D* histDefNoLumi0 = (TH1D*)inpFilePlots0->Get("unfoldNoLumi"                           );
	TH1D* histPred0      = (TH1D*)inpFilePlots0->Get(Form("hDDil%sMM",theHistName.Data())     );
	TH1D* histPredStat0  = (TH1D*)inpFilePlots0->Get(Form("hDDil%sMM_Stat",theHistName.Data()));
	TH1D* histoSystCov0[allNuisancesCov];
	TH1D* histoSystPlot0[allNuisancesPlot];
	for(int i=0; i<allNuisancesCov; i++)  histoSystCov0[i]  = (TH1D*)inpFilePlots0->Get(Form("histoSystCov_%d",i));
	for(int i=0; i<allNuisancesPlot; i++) histoSystPlot0[i] = (TH1D*)inpFilePlots0->Get(Form("histoSystPlot_%d",i));

	TH1D* histDef1       = (TH1D*)inpFilePlots1->Get("unfold"				  );
	TH1D* histDefNoLumi1 = (TH1D*)inpFilePlots1->Get("unfoldNoLumi" 			  );
	TH1D* histPred1      = (TH1D*)inpFilePlots1->Get(Form("hDDil%sEE",theHistName.Data())	  );
	TH1D* histPredStat1  = (TH1D*)inpFilePlots1->Get(Form("hDDil%sEE_Stat",theHistName.Data()));
	TH1D* histoSystCov1[allNuisancesCov];
	TH1D* histoSystPlot1[allNuisancesPlot];
	for(int i=0; i<allNuisancesCov; i++)  histoSystCov1[i]  = (TH1D*)inpFilePlots1->Get(Form("histoSystCov_%d",i));
	for(int i=0; i<allNuisancesPlot; i++) histoSystPlot1[i] = (TH1D*)inpFilePlots1->Get(Form("histoSystPlot_%d",i));

        for(Int_t nb=1;nb<=histDef0->GetNbinsX();++nb){
          histDef0	->SetBinContent(nb,(histDef0	  ->GetBinContent(nb)+histDef1      ->GetBinContent(nb))/2.0);
          histDefNoLumi0->SetBinContent(nb,(histDefNoLumi0->GetBinContent(nb)+histDefNoLumi1->GetBinContent(nb))/2.0);
          histPred0	->SetBinContent(nb,(histPred0	  ->GetBinContent(nb)+histPred1     ->GetBinContent(nb))/2.0);
          histPredStat0 ->SetBinContent(nb,(histPredStat0 ->GetBinContent(nb)+histPredStat1 ->GetBinContent(nb))/2.0);

          histDef0	->SetBinError(nb,(histDef0      ->GetBinError(nb)+histDef1      ->GetBinError(nb))/2.0);
          histDefNoLumi0->SetBinError(nb,(histDefNoLumi0->GetBinError(nb)+histDefNoLumi1->GetBinError(nb))/2.0);
          histPred0	->SetBinError(nb,(histPred0     ->GetBinError(nb)+histPred1     ->GetBinError(nb))/2.0);
          histPredStat0 ->SetBinError(nb,(histPredStat0 ->GetBinError(nb)+histPredStat1 ->GetBinError(nb))/2.0);
        }
	histDef0      ->SetNameTitle("unfold"	                              , "unfold"                                 );
	histDefNoLumi0->SetNameTitle("unfoldNoLumi"                           , "unfoldNoLumi"                           );
	histPred0     ->SetNameTitle(Form("hDDil%sLL",theHistName.Data()     ), Form("hDDil%sLL",theHistName.Data())     );
	histPredStat0 ->SetNameTitle(Form("hDDil%sLL_Stat",theHistName.Data()), Form("hDDil%sLL_Stat",theHistName.Data()));

        printf("       unf     monres  Bck     id      reco    dastat  lumi       total\n");
        for(Int_t nb=1;nb<=histDef0->GetNbinsX();++nb){
          printf("(%2d) %7.3f %7.3f %7.3f %7.3f %7.3f %7.3f %7.3f -> %7.3f\n",nb,
            histoSystPlot0[1]->GetBinContent(nb),histoSystPlot0[2]->GetBinContent(nb),histoSystPlot0[3]->GetBinContent(nb),
            histoSystPlot0[4]->GetBinContent(nb),histoSystPlot0[5]->GetBinContent(nb),histoSystPlot0[6]->GetBinContent(nb),histoSystPlot0[7]->GetBinContent(nb),
            histoSystPlot0[0]->GetBinContent(nb));
          printf("(%2d) %7.3f %7.3f %7.3f %7.3f %7.3f %7.3f %7.3f -> %7.3f\n",nb,
            histoSystPlot1[1]->GetBinContent(nb),histoSystPlot1[2]->GetBinContent(nb),histoSystPlot1[3]->GetBinContent(nb),
            histoSystPlot1[4]->GetBinContent(nb),histoSystPlot1[5]->GetBinContent(nb),histoSystPlot1[6]->GetBinContent(nb),histoSystPlot1[7]->GetBinContent(nb),
            histoSystPlot1[0]->GetBinContent(nb));
            for(int i=0; i<allNuisancesCov; i++)  histoSystCov0[i] ->SetBinContent(nb, TMath::Sqrt(TMath::Power(histoSystCov0[i] ->GetBinContent(nb),2)+TMath::Power(histoSystCov1[i] ->GetBinContent(nb),2)));
            for(int i=0; i<allNuisancesPlot; i++) histoSystPlot0[i]->SetBinContent(nb, TMath::Sqrt(TMath::Power(histoSystPlot0[i]->GetBinContent(nb),2)+TMath::Power(histoSystPlot1[i]->GetBinContent(nb),2)));
          printf("(%2d) %7.3f %7.3f %7.3f %7.3f %7.3f %7.3f %7.3f -> %7.3f\n",nb,
            histoSystPlot0[1]->GetBinContent(nb),histoSystPlot0[2]->GetBinContent(nb),histoSystPlot0[3]->GetBinContent(nb),
            histoSystPlot0[4]->GetBinContent(nb),histoSystPlot0[5]->GetBinContent(nb),histoSystPlot0[6]->GetBinContent(nb),histoSystPlot0[7]->GetBinContent(nb),
            histoSystPlot0[0]->GetBinContent(nb));
        }

        for(int i=1; i<=histDef0->GetNbinsX(); i++){
          histDef0      ->SetBinError(i,histDef0->GetBinContent(i)*histoSystPlot0[0]->GetBinContent(i)/100.);
          histDefNoLumi0->SetBinError(i,histDef0->GetBinContent(i)*histoSystPlot0[8]->GetBinContent(i)/100.);
        }

	sprintf(output,"histoUnfolding%sSyst%s_nsel%d_dy%d_rebin1_default.root",theXSRatioName.Data(),theHistName.Data(),2,j); 
	TFile* outFilePlots = new TFile(output,"recreate");
	outFilePlots->cd();
	histDef0      ->Write();
	histDefNoLumi0->Write();
	histPred0     ->Write();
	histPredStat0 ->Write();
	for(int i=0; i<allNuisancesCov; i++) histoSystCov0[i]->Write();
	for(int i=0; i<allNuisancesPlot; i++) histoSystPlot0[i]->Write();
	outFilePlots->Close();

        TString theUncLabel = "d#sigma/dp_{T}";
        if     (theXSRatioName == "_XSRatio" && theHistName == "Rap")     theUncLabel = "1/#sigma d#sigma/dY";
        else if(theXSRatioName == "_XSRatio" && theHistName == "PhiStar") theUncLabel = "1/#sigma d#sigma/d#phi_{#eta}*";
        else if(theXSRatioName == "_XSRatio")                             theUncLabel = "1/#sigma d#sigma/dp_{T}";
        else if(theXSRatioName != "_XSRatio" && theHistName == "Rap")     theUncLabel = "d#sigma/dY";
        else if(theXSRatioName != "_XSRatio" && theHistName == "PhiStar") theUncLabel = "d#sigma/d#phi_{#eta}*";

        // Begin printing information
	Bool_t increaseSize = kFALSE;
	TString XName = "Z p_{T} [GeV]";
	if     (theHistName == "Rap") XName = "|y^{Z}|";
	else if(theHistName == "PhiStar") {XName = "#phi_{#eta}*"; increaseSize = kTRUE;}
	atributes(histoSystPlot0[0],XName.Data(), 1,Form("Uncertainty in %s (%%)",theUncLabel.Data()), 1, increaseSize);
	atributes(histoSystPlot0[1],XName.Data(), 2,Form("Uncertainty in %s (%%)",theUncLabel.Data()), 1, increaseSize);
	atributes(histoSystPlot0[2],XName.Data(), 4,Form("Uncertainty in %s (%%)",theUncLabel.Data()), 1, increaseSize);
	atributes(histoSystPlot0[3],XName.Data(), 5,Form("Uncertainty in %s (%%)",theUncLabel.Data()), 1, increaseSize);
	atributes(histoSystPlot0[4],XName.Data(), 6,Form("Uncertainty in %s (%%)",theUncLabel.Data()), 1, increaseSize);
	atributes(histoSystPlot0[5],XName.Data(), 7,Form("Uncertainty in %s (%%)",theUncLabel.Data()), 1, increaseSize);
	atributes(histoSystPlot0[6],XName.Data(), 8,Form("Uncertainty in %s (%%)",theUncLabel.Data()), 1, increaseSize);
	atributes(histoSystPlot0[7],XName.Data(),11,Form("Uncertainty in %s (%%)",theUncLabel.Data()), 1, increaseSize);
	atributes(histoSystPlot0[8],XName.Data(),46,Form("Uncertainty in %s (%%)",theUncLabel.Data()), 1, increaseSize);

	TCanvas* c1 = new TCanvas("c1", "c1",5,5,500,500);
	c1->cd();
	if(theHistName != "Rap") c1->SetLogx();

	histoSystPlot0[0]->SetMinimum(0.0);
	if     (theHistName == "Rap"     && nr == 0) histoSystPlot0[0]->SetMaximum( 6.0);
	else if(theHistName == "PhiStar" && nr == 0) histoSystPlot0[0]->SetMaximum( 6.0);
	else if(theHistName == "Rap"     && nr == 1) histoSystPlot0[0]->SetMaximum( 3.0);
	else if(theHistName == "PhiStar" && nr == 1) histoSystPlot0[0]->SetMaximum( 3.0);
	else                                         histoSystPlot0[0]->SetMaximum(16.0);
	histoSystPlot0[0]->Draw();
	histoSystPlot0[1]->Draw("same,hist");
	histoSystPlot0[2]->Draw("same,hist");
	histoSystPlot0[3]->Draw("same,hist");
	histoSystPlot0[4]->Draw("same,hist");
	histoSystPlot0[5]->Draw("same,hist");
	histoSystPlot0[6]->Draw("same,hist");
	if(nr == 0) histoSystPlot0[7]->Draw("same,hist");

	//TLatex * CMSLabel = new TLatex (0.15, 0.93, "#bf{CMS} #scale[0.75]{#it{Preliminary}}");
	TLatex * CMSLabel = new TLatex (0.15, 0.93, "#bf{CMS}");
	CMSLabel->SetNDC ();
	CMSLabel->SetTextAlign (10);
	CMSLabel->SetTextFont (42);
	CMSLabel->SetTextSize (0.04);
	CMSLabel->Draw ("same") ;
	TLatex * _lumiLabel = new TLatex (0.95, 0.93, "35.9 fb^{-1} (13 TeV)");
	_lumiLabel->SetNDC ();
	_lumiLabel->SetTextAlign (30);
	_lumiLabel->SetTextFont (42);
	_lumiLabel->SetTextSize (0.04);
	_lumiLabel->Draw ("same") ;
	TLegend* leg = new TLegend(0.20,0.60,0.50,0.90);                                                    
	leg ->SetFillStyle(0);
	leg ->SetFillColor(kWhite);
	leg ->SetBorderSize(0);
	leg->SetTextSize(0.035);                                                                         
	leg->AddEntry(histoSystPlot0[0],"Total uncertainty","l");
	leg->AddEntry(histoSystPlot0[1],"Unfolding","l");
	leg->AddEntry(histoSystPlot0[2],"Momentum resolution","l");
	leg->AddEntry(histoSystPlot0[3],"Background","l");
	leg->AddEntry(histoSystPlot0[4],"Identification & trigger","l");
	leg->AddEntry(histoSystPlot0[5],"Reconstruction","l");
	leg->AddEntry(histoSystPlot0[6],"Statistical","l");
	if(nr == 0) leg->AddEntry(histoSystPlot0[7],"Luminosity","l");
	leg->Draw();
     	if(theHistName.Contains("PtRap")){
     	  TString theLabel = "";
     	  if	 (theHistName == "PtRap0") theLabel = "0 < |y^{Z}| < 0.4";
     	  else if(theHistName == "PtRap1") theLabel = "0.4 < |y^{Z}| < 0.8";
     	  else if(theHistName == "PtRap2") theLabel = "0.8 < |y^{Z}| < 1.2";
     	  else if(theHistName == "PtRap3") theLabel = "1.2 < |y^{Z}| < 1.6";
     	  else if(theHistName == "PtRap4") theLabel = "1.6 < |y^{Z}| < 2.4";
     	  TLatex *_extraLabel = new TLatex(0.9, 0.8, theLabel.Data());
     	  _extraLabel->SetNDC();
     	  _extraLabel->SetTextAlign(32);
     	  _extraLabel->SetTextFont(42);
     	  _extraLabel->SetTextSize(0.04);
     	  _extraLabel->Draw("same");
     	}

	TString myOutputFile = Form("histoUnfolding%sSyst%s%s_nsel%d_dy%d.pdf",theXSRatioName.Data(),theSuffix.Data(),theHistName.Data(),2,j);
	c1->SaveAs(myOutputFile.Data());

        // End printing information


      }
    }
  }
}
