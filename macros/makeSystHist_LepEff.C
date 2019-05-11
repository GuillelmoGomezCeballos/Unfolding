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
  histo->GetXaxis()->SetLabelSize  (0.050);
  histo->GetXaxis()->SetNdivisions (  505);
  histo->GetXaxis()->SetTitleFont  (   42);
  histo->GetXaxis()->SetTitleOffset(  1.5);
  if(!increaseSize)
  histo->GetXaxis()->SetTitleSize  (0.035);
  else
  histo->GetXaxis()->SetTitleSize  (0.040);

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

void helper_function(int nsel = 0, int whichDY = 3, TString theHistName = "Pt", bool doXSRatio = false){
  TString theOutputName = Form("outputs%s_nsel%d",theHistName.Data(),nsel);

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

  const int allNuisancesCov  = 11+480;
  const int allNuisancesPlot = 8;

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
  TH1D* histDef = (TH1D*)_fileDef->Get(Form("unfold"));

  TFile *_file[allNuisancesCov];
  TH1D* histAlt[allNuisancesCov];
  for(int i=0; i<allNuisancesCov; i++){
    _file[i]  = TFile::Open(Form("%s/dy%d/histoUnfolding%s_nsel%d_dy%d_rebin1_lepeff%d.root",theOutputName.Data(),version,theHistName.Data(),nsel,version,i));
    histAlt[i] = (TH1D*)_file[i] ->Get(Form("unfold")); assert(histAlt[i]); histAlt[i]->SetDirectory(0);
    _file[i]->Close();
  }

  double systVal[allNuisancesCov],systTotalVal;

                       // receff/lepeff2/lepeff3/lepeff4/leff5/lepeff6/lepeff7/lepeff8/lepeff8/lepeff10/lumi
  double systXSValMM[11] = {0.378, 0.062, 0.192, 0.548, 0.246, 0.183, 0.059, 0.001, 0.035, 0.115, 2.500};
  double systXSValEE[11] = {0.932, 0.104, 0.058, 0.578, 0.509, 0.385, 0.192, 0.004, 0.111, 0.419, 2.500};
  double systXSVal[11];
  for(int ns=0; ns<11; ns++){
    if     (nsel == 0) systXSVal[ns] = systXSValMM[ns];
    else if(nsel == 1) systXSVal[ns] = systXSValEE[ns];
  }

  for(int i=1; i<=histDef->GetNbinsX(); i++){
    for(int j=0; j<allNuisancesCov; j++){
      systVal[j] = 100.0*TMath::Abs(histDef->GetBinContent(i)-histAlt[j]->GetBinContent(i))/histDef->GetBinContent(i);
      //if(systVal[j]>0.001&&j>6)printf("%f\n",systVal[j]);
    }

    if(doXSRatio){
      systVal[2]  = TMath::Abs(systVal[2]  - systXSVal[1]);
      systVal[3]  = TMath::Abs(systVal[3]  - systXSVal[2]);
      systVal[4]  = TMath::Abs(systVal[4]  - systXSVal[3]);
      systVal[5]  = TMath::Abs(systVal[5]  - systXSVal[4]);
      systVal[6]  = TMath::Abs(systVal[6]  - systXSVal[5]);
      systVal[7]  = TMath::Abs(systVal[7]  - systXSVal[6]);
      systVal[8]  = TMath::Abs(systVal[8]  - systXSVal[7]);
      systVal[9]  = TMath::Abs(systVal[9]  - systXSVal[8]);
      systVal[10] = TMath::Abs(systVal[10] - systXSVal[9]);
    }

    double systValTotAtOnce = systVal[0];
    double systValStaAtOnce = systVal[1];
    double systValNoStat = sqrt(systVal[2]*systVal[2]+systVal[3]*systVal[3]+systVal[ 4]*systVal[ 4]+
                                systVal[5]*systVal[5]+systVal[6]*systVal[6]+systVal[ 7]*systVal[ 7]+
                                systVal[8]*systVal[8]+systVal[9]*systVal[9]+systVal[10]*systVal[10]);

    double systValSta = 0;
    for(int k=7; k<allNuisancesCov; k++) systValSta = systValSta + systVal[k]*systVal[k];
    systValSta = systVal[1]/10.; //sqrt(systValSta);

    printf("(%2d) %7.3f %7.3f %7.3f %7.3f %7.3f %7.3f %7.3f %7.3f %7.3f (%7.3f/%7.3f) -> (%7.3f/%7.3f/%7.3f)\n",i,
           systVal[2],systVal[3],systVal[4],systVal[5],systVal[6],systVal[7],systVal[8],systVal[9],systVal[10],
           systValStaAtOnce,systValSta,
           systValTotAtOnce,sqrt(systValStaAtOnce*systValStaAtOnce+systValNoStat*systValNoStat),sqrt(systValSta*systValSta+systValNoStat*systValNoStat));
    histoSystPlot[0]->SetBinContent(i,sqrt(systValSta*systValSta+systValNoStat*systValNoStat)); // total
    histoSystPlot[1]->SetBinContent(i,systValSta); // statistical
    histoSystPlot[2]->SetBinContent(i,systVal[2]); // lepeff2
    histoSystPlot[3]->SetBinContent(i,systVal[3]); // lepeff3
    histoSystPlot[4]->SetBinContent(i,systVal[4]); // lepeff4 
    histoSystPlot[5]->SetBinContent(i,systVal[5]); // lepeff5 
    histoSystPlot[6]->SetBinContent(i,systVal[6]); // lepeff6
    histoSystPlot[7]->SetBinContent(i,sqrt(systVal[7]*systVal[7]+systVal[ 8]*systVal[ 8]+
                                           systVal[9]*systVal[9]+systVal[10]*systVal[10])); // lepeff7+lepeff8+lepeff9+lepeff10
  }

  TString theUncLabel = "d#sigma/dp_{T}";
  if	 (doXSRatio && theHistName == "Rap")	  theUncLabel = "1/#sigma d#sigma/dY";
  else if(doXSRatio && theHistName == "PhiStar")  theUncLabel = "1/#sigma d#sigma/d#phi*";
  else if(doXSRatio)				  theUncLabel = "1/#sigma d#sigma/dp_{T}";
  else if(!doXSRatio && theHistName == "Rap")	  theUncLabel = "d#sigma/dY";
  else if(!doXSRatio && theHistName == "PhiStar") theUncLabel = "d#sigma/d#phi*";

  Bool_t increaseSize = kFALSE;
  TString XName = "Z p_{T} [GeV]";
  if     (theHistName == "Rap") XName = "|y^{Z}|";
  else if(theHistName == "PhiStar") {XName = "#phi*"; increaseSize = kTRUE;}
  atributes(histoSystPlot[0],XName.Data(), 1,Form("Uncertainty in %s (%%)",theUncLabel.Data()), 1, increaseSize);
  atributes(histoSystPlot[1],XName.Data(), 2,Form("Uncertainty in %s (%%)",theUncLabel.Data()), 1, increaseSize);
  atributes(histoSystPlot[2],XName.Data(), 4,Form("Uncertainty in %s (%%)",theUncLabel.Data()), 1, increaseSize);
  atributes(histoSystPlot[3],XName.Data(), 5,Form("Uncertainty in %s (%%)",theUncLabel.Data()), 1, increaseSize);
  atributes(histoSystPlot[4],XName.Data(), 6,Form("Uncertainty in %s (%%)",theUncLabel.Data()), 1, increaseSize);
  atributes(histoSystPlot[5],XName.Data(), 7,Form("Uncertainty in %s (%%)",theUncLabel.Data()), 1, increaseSize);
  atributes(histoSystPlot[6],XName.Data(), 8,Form("Uncertainty in %s (%%)",theUncLabel.Data()), 1, increaseSize);
  atributes(histoSystPlot[7],XName.Data(),11,Form("Uncertainty in %s (%%)",theUncLabel.Data()), 1, increaseSize);

  TCanvas* c1 = new TCanvas("c1", "c1",5,5,500,500);
  c1->cd();
  if(theHistName != "Rap") c1->SetLogx();

  histoSystPlot[0]->SetMinimum(0.0);
  histoSystPlot[0]->Draw();
  histoSystPlot[1]->Draw("same,hist");
  histoSystPlot[2]->Draw("same,hist");
  histoSystPlot[3]->Draw("same,hist");
  histoSystPlot[4]->Draw("same,hist");
  histoSystPlot[5]->Draw("same,hist");
  histoSystPlot[6]->Draw("same,hist");
  histoSystPlot[7]->Draw("same,hist");

 TLatex * CMSLabel = new TLatex (0.15, 0.93, "#bf{CMS} #scale[0.75]{#it{Preliminary}}");
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
 leg->SetTextSize(0.030);                                                                         
 leg->AddEntry(histoSystPlot[0],"Total efficiency uncertainty","l");
 leg->AddEntry(histoSystPlot[1],"Statistical","l");
 leg->AddEntry(histoSystPlot[2],"FSR modeling","l");
 leg->AddEntry(histoSystPlot[3],"Resolution modeling","l");
 leg->AddEntry(histoSystPlot[4],"Background modeling","l");
 leg->AddEntry(histoSystPlot[5],"Tag selecion","l");
 leg->AddEntry(histoSystPlot[6],"MC generator","l");
 leg->AddEntry(histoSystPlot[7],"Trigger efficiency","l");
 leg->Draw();

 TString theXSRatioName = "";
 if(doXSRatio) theXSRatioName = "_XSRatio";

 TString myOutputFile = Form("histoUnfolding%sSystEff%s_nsel%d_dy%d.pdf",theXSRatioName.Data(),theHistName.Data(),nsel,whichDY);
 c1->SaveAs(myOutputFile.Data());
}

void makeSystHist_LepEff(TString theHistName = "Pt"){
  for (int i=0;i<=1;i++){
    for (int j=0;j<=3;j++){
      helper_function(i, j, theHistName, false);
      helper_function(i, j, theHistName, true);
    }
  }
}
