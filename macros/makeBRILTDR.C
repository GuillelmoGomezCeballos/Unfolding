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
void helper_function(TString theSuffix, int nsel = 0, int whichDY = 3, TString theHistName = "Pt", bool doXSRatio = false){

  TFile *_file[3];
  TH1D* histoSystPlot[11];

  _file[0] = TFile::Open(Form("histoUnfoldingSyst%s_nsel%d_dy%d_lumunc0p025.root",theHistName.Data(),nsel,whichDY));
  _file[1] = TFile::Open(Form("histoUnfoldingSyst%s_nsel%d_dy%d_lumunc0p020.root",theHistName.Data(),nsel,whichDY));
  _file[2] = TFile::Open(Form("histoUnfoldingSyst%s_nsel%d_dy%d_lumunc0p010.root",theHistName.Data(),nsel,whichDY));

  histoSystPlot[0] = (TH1D*)_file[0]->Get(Form("histoSystPlot_0")); assert(histoSystPlot[0]); histoSystPlot[0]->SetDirectory(0); // total
  histoSystPlot[1] = (TH1D*)_file[0]->Get(Form("histoSystPlot_1")); assert(histoSystPlot[1]); histoSystPlot[1]->SetDirectory(0); // unfolding + mc stat
  histoSystPlot[2] = (TH1D*)_file[0]->Get(Form("histoSystPlot_2")); assert(histoSystPlot[2]); histoSystPlot[2]->SetDirectory(0); // momres
  histoSystPlot[3] = (TH1D*)_file[0]->Get(Form("histoSystPlot_3")); assert(histoSystPlot[3]); histoSystPlot[3]->SetDirectory(0); // Bkg.
  histoSystPlot[4] = (TH1D*)_file[0]->Get(Form("histoSystPlot_4")); assert(histoSystPlot[4]); histoSystPlot[4]->SetDirectory(0); // LepEff
  histoSystPlot[5] = (TH1D*)_file[0]->Get(Form("histoSystPlot_5")); assert(histoSystPlot[5]); histoSystPlot[5]->SetDirectory(0); // RecEff
  histoSystPlot[6] = (TH1D*)_file[0]->Get(Form("histoSystPlot_6")); assert(histoSystPlot[6]); histoSystPlot[6]->SetDirectory(0); // data stat
  histoSystPlot[7] = (TH1D*)_file[0]->Get(Form("histoSystPlot_7")); assert(histoSystPlot[7]); histoSystPlot[7]->SetDirectory(0); // lumi
  histoSystPlot[8] = (TH1D*)_file[0]->Get(Form("histoSystPlot_8")); assert(histoSystPlot[8]); histoSystPlot[8]->SetDirectory(0); // total, except for lumi

  histoSystPlot[9]  = (TH1D*)_file[1]->Get(Form("histoSystPlot_0")); assert(histoSystPlot[0]); histoSystPlot[ 9]->SetDirectory(0); // total 2p0 lumi
  histoSystPlot[10] = (TH1D*)_file[2]->Get(Form("histoSystPlot_0")); assert(histoSystPlot[0]); histoSystPlot[10]->SetDirectory(0); // total 1p0 lumi

  TString theXSRatioName = "";
  if(doXSRatio) theXSRatioName = "_XSRatio";

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
  //atributes(histoSystPlot[7],XName.Data(),11,Form("Uncertainty in %s (%%)",theUncLabel.Data()), 8, increaseSize);
  atributes(histoSystPlot[8],XName.Data(),46,Form("Uncertainty in %s (%%)",theUncLabel.Data()), 9, increaseSize);
  atributes(histoSystPlot[ 9],XName.Data(), 1,Form("Uncertainty in %s (%%)",theUncLabel.Data()), 7, increaseSize);
  atributes(histoSystPlot[10],XName.Data(), 1,Form("Uncertainty in %s (%%)",theUncLabel.Data()), 8, increaseSize);

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
  //if(!doXSRatio) histoSystPlot[7]->Draw("same,hist");
  histoSystPlot[8]->Draw("same,hist");
  histoSystPlot[ 9]->Draw("same,hist");
  histoSystPlot[10]->Draw("same,hist");

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
  //TLegend* leg = new TLegend(0.20,0.73,0.50,0.90);                                                    
  leg->SetBorderSize  (    0);
  leg->SetFillColor   (    0);
  leg->SetTextAlign   (   12);
  leg->SetTextFont    (   42);
  leg->SetTextSize    (0.035);
  leg->SetShadowColor(     0);
  leg->AddEntry(histoSystPlot[0],"Total uncertainty (with 2.5% lumi. unc.)","l");
  leg->AddEntry(histoSystPlot[9],"Total uncertainty (with 2% lumi. unc.)","l");
  leg->AddEntry(histoSystPlot[10],"Total uncertainty (with 1% lumi. unc.)","l");
  leg->AddEntry(histoSystPlot[8],"Total uncertainty (excluding lumi. unc.)","l");
  leg->AddEntry(histoSystPlot[4],"Identification & trigger","l");
  leg->AddEntry(histoSystPlot[5],"Reconstruction","l");
  leg->AddEntry(histoSystPlot[2],"Momentum resolution","l");
  leg->AddEntry(histoSystPlot[1],"Unfolding","l");
  leg->AddEntry(histoSystPlot[3],"Background","l");
  //leg->AddEntry(histoSystPlot[6],"Statistical","l");
  //if(!doXSRatio) leg->AddEntry(histoSystPlot[7],"Integrated luminosity","l");
  leg->Draw();
  if(1){
    TString theLabel = ""; double addY= 0;
    TString leptonLegend = "#mu^{+}#mu^{-} sample";
    if(nsel == 1) {leptonLegend = "e^{+}e^{-} sample"; addY = 0.05;}
    if     (theHistName == "PtRap0") theLabel = Form("#splitline{0 < |y^{l^{+}l^{-}}| < 0.4}{%s}",leptonLegend.Data());
    else if(theHistName == "PtRap1") theLabel = Form("#splitline{0.4 < |y^{l^{+}l^{-}}| < 0.8}{%s}",leptonLegend.Data());
    else if(theHistName == "PtRap2") theLabel = Form("#splitline{0.8 < |y^{l^{+}l^{-}}| < 1.2}{%s}",leptonLegend.Data());
    else if(theHistName == "PtRap3") theLabel = Form("#splitline{1.2 < |y^{l^{+}l^{-}}| < 1.6}{%s}",leptonLegend.Data());
    else if(theHistName == "PtRap4") theLabel = Form("#splitline{1.6 < |y^{l^{+}l^{-}}| < 2.4}{%s}",leptonLegend.Data());
    else if(nsel == 0              ) theLabel = leptonLegend.Data();
    else if(nsel == 1              ) theLabel = leptonLegend.Data();
    TLatex *_extraLabel = new TLatex(0.45, 0.35+addY, theLabel.Data());
    _extraLabel->SetNDC();
    _extraLabel->SetTextAlign(32);
    _extraLabel->SetTextFont(42);
    _extraLabel->SetTextSize(0.05);
    _extraLabel->Draw("same");
  }

  //printf("       unf     monres  bkg     receff  lepeff  totnol  totl1p0 totl2p0 totl2p5\n");
  //for(int i=1; i<=histoSystPlot[0]->GetNbinsX(); i++){
  //  printf("(%2d) %7.1f %7.1f %7.1f %7.1f %7.1f %7.1f %7.1f %7.1f %7.1f\n",i,
  //          histoSystPlot[3]->GetBinContent(i),histoSystPlot[1]->GetBinContent(i),histoSystPlot[2]->GetBinContent(i),
  //          histoSystPlot[5]->GetBinContent(i),histoSystPlot[4]->GetBinContent(i),histoSystPlot[8]->GetBinContent(i),
  //          histoSystPlot[10]->GetBinContent(i),histoSystPlot[9]->GetBinContent(i),histoSystPlot[0]->GetBinContent(i));
  //}

  TString myOutputFile = Form("histoUnfolding%sSyst%s%s_nsel%d_dy%d.pdf",theXSRatioName.Data(),theSuffix.Data(),theHistName.Data(),nsel,whichDY);
  c1->SaveAs(myOutputFile.Data());

}
void makeBRILTDR(TString theSuffix = "", TString theHistName = "Rap"){
  if(theSuffix != "LL") theSuffix = "";
  char output[200];
  for (int j=3;j<=3;j++){ // dy versions
    for (int nr=0; nr<=0; nr++) {
      for (int i=0; i<=1; i++){ // 0 / 1 == mm / ee
        printf("Parameters: %s %d %d %s %d\n",theSuffix.Data(),i,j,theHistName.Data(),nr);
        helper_function(theSuffix.Data(), i, j, theHistName, nr);
      }
    }
  }
}
