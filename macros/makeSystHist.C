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
  histo->GetXaxis()->SetLabelSize  (0.050);
  histo->GetXaxis()->SetNdivisions (  505);
  histo->GetXaxis()->SetTitleFont  (   42);
  histo->GetXaxis()->SetTitleOffset(  1.5);
  histo->GetXaxis()->SetTitleSize  (0.035);

  histo->GetYaxis()->SetTitle(ytitle);
  histo->GetYaxis()->SetLabelFont  (   42);
  histo->GetYaxis()->SetLabelOffset(0.015);
  histo->GetYaxis()->SetLabelSize  (0.050);
  histo->GetYaxis()->SetNdivisions (  505);
  histo->GetYaxis()->SetTitleFont  (   42);
  histo->GetYaxis()->SetTitleOffset(  1.7);
  histo->GetYaxis()->SetTitleSize  (0.035);
  histo->SetLineColor(COLOR);
  histo->SetMarkerStyle(kFullDotLarge);
  histo->SetLineStyle(style);
}
void makeSystHist(int nsel = 0, int whichDY = 3, TString theHistName = "Pt", bool doXSRatio = false){

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

  int version = 1; int alternative = 0;
  if     (whichDY == 0) { version = 0; alternative = 1;}
  else if(whichDY == 2) { version = 2; alternative = 1;}
  else if(whichDY == 3) { version = 3; alternative = 0;}
  TString theOutputName = Form("outputs%s_nsel%d",theHistName.Data(),nsel);

  const int nGenSyst = 8;
  const int nEffSyst = 1058;
  const int nStaSyst = 72;
  const int nOthSyst = 2;

  const int allNuisancesCov  = nGenSyst+nEffSyst+nStaSyst+nOthSyst;
  const int allNuisancesPlot = 10;

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
  _file[7] = TFile::Open(Form("%s/dy%d/histoUnfolding%s_nsel%d_dy%d_rebin1_receff.root",theOutputName.Data(),version,theHistName.Data(),nsel,version)); // RecEff
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

                       // receff/lepeff2/lepeff3/lepeff4/leff5/lepeff6/lepeff7/lumi
  double systXSVal[8] = {0.091, 0.196, 0.167, 0.275, 0.546, 0.439, 0.028, 2.500};
  if(nsel == 1) {systXSVal[0] = 1.140;
                 systXSVal[1] = 0.671; systXSVal[2] = 1.350; systXSVal[3] = 0.661; systXSVal[4] = 1.103; systXSVal[5] = 0.823; systXSVal[6] = 0.095;
             systXSVal[7] = 2.500;}

  double systUnfVal[16] = {0.355, 0.567, 0.214, 0.522, 0.285, 0.466, 0.572, 1.164, 0.778, 0.395, 0.193, 0.593, 0.258, 0.527, 0.111, 0.107};
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

    if(doMakeUseFixedSystUnf == true) systVal[0] = theSystUnfVal;

    if(nsel == 1) {systVal[3] =0; systVal[4] =0;}

    //if      (histDef->GetBinCenter(i)+histDef->GetBinWidth(i)/2<=45  && systVal[0] > 1.0) systVal[0] = 1.0;
    //else if (histDef->GetBinCenter(i)+histDef->GetBinWidth(i)/2<=105 && systVal[0] > 1.0) systVal[0] = 0.5;
    //if(theHistName == "PtRap3" && systVal[0] > 7.0) systVal[0] = 2.0 + gRandom->Rndm()*0.5;
    //if(systVal[0] > 0.5) systVal[0] = 0.5 + gRandom->Rndm()*0.5;
    if(systVal[1] > 3.0 && i < 20) systVal[1] = 3.0 + gRandom->Rndm()*0.5;
    if(systVal[2] > 3.0 && i < 20) systVal[2] = 3.0 + gRandom->Rndm()*0.5;
    if(systVal[3] > 3.0 && i < 20) systVal[3] = 3.0 + gRandom->Rndm()*0.5;
    systVal[allNuisancesCov-2] = 100.*histDef->GetBinError(i)/histDef->GetBinContent(i); // data stat
    systVal[allNuisancesCov-1] = 100.*0.025;

    if(doCorrelateMomResLepEff == true) systVal[nGenSyst+3] = 0;

    if(doXSRatio){
      systVal[0 ] = 0;
      systVal[7 ] = systVal[7 ] - systXSVal[0];
      systVal[10] = systVal[10] - systXSVal[1];
      if(doCorrelateMomResLepEff == false) systVal[11] = systVal[11] - systXSVal[2];
      else                                 systVal[2 ] = systVal[2 ] - systXSVal[2];
      systVal[12] = systVal[12] - systXSVal[3];
      systVal[13] = systVal[13] - systXSVal[4];
      systVal[14] = systVal[14] - systXSVal[5];
      systVal[15] = systVal[15] - systXSVal[6];
      systVal[allNuisancesCov-1] = systVal[allNuisancesCov-1] - systXSVal[7];
    }

    for(int j=0; j<allNuisancesCov; j++) {histoSystCov[j]->SetBinContent(i,systVal[j]/100.);}

    double systEffValStaAtOnce = systVal[9];
    double systEffValNoStat = sqrt(systVal[nGenSyst+2]*systVal[nGenSyst+2]+systVal[nGenSyst+3]*systVal[nGenSyst+3]+systVal[nGenSyst+4]*systVal[nGenSyst+4]+
                                   systVal[nGenSyst+5]*systVal[nGenSyst+5]+systVal[nGenSyst+6]*systVal[nGenSyst+6]+systVal[nGenSyst+7]*systVal[nGenSyst+7]);

    systVal[8] = 0; systVal[9] = 0; // make sure not used anymore
    double systEffValSta = 0;
    for(int k=nGenSyst+7; k<nGenSyst+nEffSyst; k++) systEffValSta = systEffValSta + systVal[k]*systVal[k];
    systEffValSta = sqrt(systEffValSta);

    double systMCValSta = 0;
    for(int k=nGenSyst+nEffSyst; k<nGenSyst+nEffSyst+nStaSyst; k++) systMCValSta = systMCValSta + systVal[k]*systVal[k];
    systMCValSta = sqrt(systMCValSta);

    histoSystPlot[1]->SetBinContent(i,systVal[0]); // unfolding
    histoSystPlot[2]->SetBinContent(i,sqrt(systVal[1]*systVal[1]+systVal[2]*systVal[2]+systVal[3]*systVal[3]+systVal[4]*systVal[4])); // momres
    histoSystPlot[3]->SetBinContent(i,sqrt(systVal[5]*systVal[5]+systVal[6]*systVal[6])); // Bkg.
    histoSystPlot[5]->SetBinContent(i,systVal[7]); // RecEff
    histoSystPlot[4]->SetBinContent(i,sqrt(systEffValNoStat*systEffValNoStat+systEffValSta*systEffValSta)); // LepEff
    histoSystPlot[6]->SetBinContent(i,systMCValSta); // mc stat
    histoSystPlot[7]->SetBinContent(i,systVal[allNuisancesCov-2]); // data stat
    histoSystPlot[8]->SetBinContent(i,systVal[allNuisancesCov-1]); // lumi

    histoSystPlot[0]->SetBinContent(i,sqrt(histoSystPlot[1]->GetBinContent(i)*histoSystPlot[1]->GetBinContent(i)+
                                           histoSystPlot[2]->GetBinContent(i)*histoSystPlot[2]->GetBinContent(i)+
                                           histoSystPlot[3]->GetBinContent(i)*histoSystPlot[3]->GetBinContent(i)+
                                           histoSystPlot[5]->GetBinContent(i)*histoSystPlot[5]->GetBinContent(i)+
                                           histoSystPlot[4]->GetBinContent(i)*histoSystPlot[4]->GetBinContent(i)+
                                           histoSystPlot[6]->GetBinContent(i)*histoSystPlot[6]->GetBinContent(i)+
                                           histoSystPlot[7]->GetBinContent(i)*histoSystPlot[7]->GetBinContent(i)+
                                           histoSystPlot[8]->GetBinContent(i)*histoSystPlot[8]->GetBinContent(i)
                                           ));

    histoSystPlot[9]->SetBinContent(i,sqrt(histoSystPlot[1]->GetBinContent(i)*histoSystPlot[1]->GetBinContent(i)+
                                           histoSystPlot[2]->GetBinContent(i)*histoSystPlot[2]->GetBinContent(i)+
                                           histoSystPlot[3]->GetBinContent(i)*histoSystPlot[3]->GetBinContent(i)+
                                           histoSystPlot[5]->GetBinContent(i)*histoSystPlot[5]->GetBinContent(i)+
                                           histoSystPlot[4]->GetBinContent(i)*histoSystPlot[4]->GetBinContent(i)+
                                           histoSystPlot[6]->GetBinContent(i)*histoSystPlot[6]->GetBinContent(i)+
                                           histoSystPlot[7]->GetBinContent(i)*histoSystPlot[7]->GetBinContent(i)
                                           ));//except for lumi
    printf("(%2d) %7.3f %7.3f %7.3f %7.3f %7.3f %7.3f %7.3f %7.3f %7.3f(%7.3f) %7.3f %7.3f %7.3f %7.3f -> %7.3f\n",i,
            systVal[0],systVal[1],systVal[2],systVal[3],systVal[4],systVal[5],systVal[6],systVal[7],
            systEffValSta,systEffValStaAtOnce,systEffValNoStat,systMCValSta,systVal[allNuisancesCov-2],systVal[allNuisancesCov-1],
            histoSystPlot[0]->GetBinContent(i));
  }

  histoSystPlot[0]->Smooth();
  histoSystPlot[1]->Smooth();
  histoSystPlot[2]->Smooth();
  histoSystPlot[3]->Smooth();
  histoSystPlot[5]->Smooth();
  histoSystPlot[4]->Smooth();
  histoSystPlot[6]->Smooth();
  histoSystPlot[7]->Smooth();
  histoSystPlot[8]->Smooth();
  histoSystPlot[9]->Smooth();

  TString XName = "Z p_{T} [GeV]";
  if     (theHistName == "Rap") XName = "|y^{Z}|";
  else if(theHistName == "PhiStar") XName = "#phi*";
  atributes(histoSystPlot[0],XName.Data(), 1,"Uncertainty (%)", 1);
  atributes(histoSystPlot[1],XName.Data(), 2,"Uncertainty (%)", 1);
  atributes(histoSystPlot[2],XName.Data(), 4,"Uncertainty (%)", 1);
  atributes(histoSystPlot[3],XName.Data(), 5,"Uncertainty (%)", 1);
  atributes(histoSystPlot[4],XName.Data(), 6,"Uncertainty (%)", 1);
  atributes(histoSystPlot[5],XName.Data(), 7,"Uncertainty (%)", 1);
  atributes(histoSystPlot[6],XName.Data(), 8,"Uncertainty (%)", 1);
  atributes(histoSystPlot[7],XName.Data(),11,"Uncertainty (%)", 1);
  atributes(histoSystPlot[8],XName.Data(),46,"Uncertainty (%)", 1);

  TCanvas* c1 = new TCanvas("c1", "c1",5,5,500,500);
  c1->cd();
  if(theHistName != "Rap") c1->SetLogx();

  histoSystPlot[0]->SetMinimum(0.0);
  histoSystPlot[0]->Draw();
  if(!doXSRatio) histoSystPlot[1]->Draw("same,hist");
  histoSystPlot[2]->Draw("same,hist");
  histoSystPlot[3]->Draw("same,hist");
  histoSystPlot[4]->Draw("same,hist");
  histoSystPlot[5]->Draw("same,hist");
  histoSystPlot[6]->Draw("same,hist");
  histoSystPlot[7]->Draw("same,hist");
  if(!doXSRatio) histoSystPlot[8]->Draw("same,hist");

 TLatex * CMSLabel = new TLatex (0.15, 0.93, "#bf{CMS} Preliminary");
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
 TLegend* leg = new TLegend(0.20,0.60,0.50,0.85);                                                    
 leg ->SetFillStyle(0);
 leg ->SetFillColor(kWhite);
 leg ->SetBorderSize(0);
 leg->SetTextSize(0.035);                                                                         
 leg->AddEntry(histoSystPlot[0],"Total Unc.","l");
 if(!doXSRatio) leg->AddEntry(histoSystPlot[1],"Unfolding","l");
 leg->AddEntry(histoSystPlot[2],"Mom. Res.","l");
 leg->AddEntry(histoSystPlot[3],"Bkg.","l");
 leg->AddEntry(histoSystPlot[4],"Identification","l");
 leg->AddEntry(histoSystPlot[5],"Reconstruction","l");
 leg->AddEntry(histoSystPlot[6],"MC Stat.","l");
 leg->AddEntry(histoSystPlot[7],"Statistical","l");
 if(!doXSRatio) leg->AddEntry(histoSystPlot[8],"Luminosity","l");
 leg->Draw();

 TString theXSRatioName = "";
 if(doXSRatio) theXSRatioName = "_XSRatio";

 TString myOutputFile = Form("histoUnfolding%sSyst%s_nsel%d_dy%d.pdf",theXSRatioName.Data(),theHistName.Data(),nsel,whichDY);
 c1->SaveAs(myOutputFile.Data());

 for(int i=1; i<=histDef->GetNbinsX(); i++){
   histDef      ->SetBinError(i,histDef->GetBinContent(i)*histoSystPlot[0]->GetBinContent(i)/100.);
   histDefNoLumi->SetBinError(i,histDef->GetBinContent(i)*histoSystPlot[9]->GetBinContent(i)/100.);
 }
 for(Int_t i=1;i<=histPred->GetNbinsX();++i){
   double diff[3] = {histPred->GetBinError(i), histPred_PDF->GetBinContent(i)-histPred->GetBinContent(i), histPred_QCD->GetBinContent(i)-histPred->GetBinContent(i)};
   histPred    ->SetBinError(i,sqrt(diff[0]*diff[0]+diff[1]*diff[1]+diff[2]*diff[2]));
   histPredStat->SetBinError(i,diff[0]);
   if(isDebug) printf("histPredSyst (%2d) %5.2f %5.2f %5.2f -> %5.2f\n",i,100*diff[0]/histPred->GetBinContent(i),100*diff[1]/histPred->GetBinContent(i),100*diff[2]/histPred->GetBinContent(i),100*histPred->GetBinError(i)/histPred->GetBinContent(i));
 }

 char output[200];
 sprintf(output,"histoUnfolding%sSyst%s_nsel%d_dy%d_rebin1_default.root",theXSRatioName.Data(),theHistName.Data(),nsel,whichDY); 
 TFile* outFilePlots = new TFile(output,"recreate");
 outFilePlots->cd();

 histDef      ->Write();
 histDefNoLumi->Write();
 histPred     ->Write();
 histPredStat ->Write();
 
 for(int i=0; i<allNuisancesCov; i++) histoSystCov[i]->Write();
 for(int i=0; i<allNuisancesPlot; i++) histoSystPlot[i]->Write();

 outFilePlots->Close();

}
