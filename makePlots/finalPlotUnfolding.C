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

void finalPlotUnfolding(int nsel = 0, int ReBin = 1, TString XTitle = "N_{jets}", TString units = "", TString plotName = "histo_nice.root", TString outputName = "njets",
                bool isLogY = false, bool isLogX = false, TString keyLabel0 = "Pt", TString keyLabel1 = "MM", bool isNormalized = false) {

  gInterpreter->ExecuteMacro("PaperStyle.C");
  gStyle->SetOptStat(0);

  double TotalLumi = 35900.0;
  double normalization[2];

  int me=0;
  if (strncmp(keyLabel1.Data(),"EE",2)==0){me=1;}

  char filename1[300];
  char filename2[300];
  char filename3[300];
  sprintf(filename1,"_nsel%d_dy3_rebin%d_default.root",me,ReBin);//default, AMCNLO
  sprintf(filename2,"_nsel%d_dy0_rebin%d_default.root",me,ReBin);
  if(keyLabel0 == "Pt" || keyLabel0 == "PhiStar") sprintf(filename3,"_nsel%d_dy4_rebin%d_default.root",me,ReBin);
  else                                            sprintf(filename3,"_nsel%d_dy2_rebin%d_default.root",me,ReBin);
  TString plotName2=plotName;
  TString plotName3=plotName;
  plotName.Append(filename1);
  plotName2=plotName2.Append(filename2);
  plotName3=plotName3.Append(filename3);;
  
  TH1D* hData;
  TH1D* hPred1;
  TH1D* hPred2;
  TH1D* hPred3;

  TFile* file1 = new TFile(plotName, "read");  if(!file1) {printf("File %s does not exist\n",plotName.Data()); return;}
  hData      = (TH1D*)file1->Get(Form("unfold"));
  hPred1     = (TH1D*)file1->Get(Form("hDDil%s%s"    ,keyLabel0.Data(),keyLabel1.Data()));
  TFile *file2 = new TFile(plotName2, "read");  if(!file2) {printf("File %s does not exist\n",plotName.Data()); return;}
  hPred2 = (TH1D*)file2->Get(Form("hDDil%s%s"	 ,keyLabel0.Data(),keyLabel1.Data()));
  TFile *file3 = new TFile(plotName3, "read");  if(!file3) {printf("File %s does not exist\n",plotName.Data()); return;}
  hPred3     = (TH1D*)file3->Get(Form("hDDil%s%s"    ,keyLabel0.Data(),keyLabel1.Data()));

  double pull; 
  double pullerr;

  TCanvas* c1 = new TCanvas("c1", "c1",5,5,600,600);

  c1->SetBottomMargin(0.1);
  c1->cd();
  TPad* pad0 = new TPad("pad0", "pad0",0.00,0.575,1.00,1.000);
  TPad* pad1 = new TPad("pad1", "pad1",0.00,0.385,1.00,0.565);
  TPad* pad2 = new TPad("pad2", "pad2",0.00,0.195,1.00,0.375);
  TPad* pad3 = new TPad("pad3", "pad3",0.00,0.000,1.00,0.185);

  pad0->SetTopMargin(0.19);
  pad0->SetBottomMargin(0);
  pad1->SetTopMargin(0);
  pad1->SetBottomMargin(0);
  pad2->SetTopMargin(0);
  pad2->SetBottomMargin(0);
  pad3->SetTopMargin(0);
  pad3->SetBottomMargin(0.3);
  pad0->Draw();
  pad1->Draw();
  pad2->Draw();
  pad3->Draw();
 
  pad0->cd();

  if(isLogX == true) pad0->SetLogx();
  if(isLogY == true) pad0->SetLogy();

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
  if     (isNormalized && keyLabel0 == "Rap")     theYTitle = "1/#sigma d#sigma/dY";
  else if(isNormalized && keyLabel0 == "PhiStar") theYTitle = "1/#sigma d#sigma/d#phi*";
  else if(isNormalized)                           theYTitle = "1/#sigma d#sigma/dp_{T} [ GeV^{-1}]";

  hPred1->GetYaxis()->SetTitle(theYTitle.Data());
  hPred1->GetYaxis()->SetLabelFont  (   42);
  hPred1->GetYaxis()->SetLabelOffset(0.015);
  hPred1->GetYaxis()->SetLabelSize  (0.060);
  hPred1->GetYaxis()->SetNdivisions (  505);
  hPred1->GetYaxis()->SetTitleFont  (   42);
  hPred1->GetYaxis()->SetTitleOffset(  1.0);
  hPred1->GetYaxis()->SetTitleSize  (0.050);
  hPred1->GetYaxis()->SetTickLength (0.03 );

  hPred1->GetXaxis()->SetLabelFont  (   42);
  hPred1->GetXaxis()->SetLabelSize  (0.040);
  hPred1->GetXaxis()->SetNdivisions (  505);
  hPred1->GetXaxis()->SetTitleFont  (   42);
  hPred1->GetXaxis()->SetTitleSize  (0.040);
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
  if(isNormalized) {normalization[0] = hPred2->GetSumOfWeights();};
  if(isNormalized) {normalization[0] = hPred3->GetSumOfWeights();};
  hPred1->Scale(1./normalization[0]);
  hPred2->Scale(1./normalization[0]);
  hPred3->Scale(1./normalization[0]);
  hData ->Scale(1./normalization[1]);

  if(isLogY == true) hPred1->GetYaxis()->SetRangeUser(hPred1->GetMinimum()/10,hPred1->GetMaximum()*500);
  else               hPred1->GetYaxis()->SetRangeUser(0.0,hPred1->GetMaximum()*1.5);
  hPred1->Draw();
  hData->Draw("ep,same");

  gStyle->SetOptStat(0);
  TLegend* legend = new TLegend(0.70,0.80,0.80,0.90);
  legend->SetBorderSize(     0);
  legend->SetFillColor (     0);
  legend->SetTextAlign (    12);
  legend->SetTextFont  (    42);
  legend->SetTextSize  (0.03);
  legend->AddEntry(hData,"Unfolded data");
  legend->AddEntry(hPred1, "aMC@NLO");

  /********** MADGRAPH **************/
  hPred2->SetMarkerStyle(kFullCircle);
  hPred2->Draw("same");
  legend->AddEntry(hPred2, "MADGRAPH");

  /************ POWHEG *************/
  hPred3->SetMarkerStyle(23);
  hPred3->Draw("same");
  if(keyLabel0 == "Pt" || keyLabel0 == "PhiStar") legend->AddEntry(hPred3, "GENEVA");
  else                                            legend->AddEntry(hPred3, "POWHEG");

  CMS_lumi( c1, 4, 1);
  legend->Draw();

  /////////////////////////////////////////////PAD1///////////////////////////////////////////////////////////////
  pad1->cd();
  gStyle->SetOptStat(0);

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

  /////////////////////////////////////////////PAD2///////////////////////////////////////////////////////////////
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

  /////////////////////////////////////////////PAD3///////////////////////////////////////////////////////////////
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
  if(keyLabel0 == "Pt" || keyLabel0 == "PhiStar") atributes(hRatio,XTitle.Data(),"GENEVA/Data",units.Data());
  else						  atributes(hRatio,XTitle.Data(),"POWHEG/Data",units.Data());
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

  printf("Total yields: %f - %f %f %f\n", hData->Integral("Width"),hPred1->Integral("Width"),hPred2->Integral("Width"),hPred3->Integral("Width"));

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
