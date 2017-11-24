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

void eraselabel(TPad *p,Double_t h){
  p->cd();
  TPad *pe = new TPad("pe","pe",0.02,0,p->GetLeftMargin(),h);	   
  pe->Draw();
  pe->SetFillColor(p->GetFillColor()); 
  pe->SetBorderMode(0);
}

void finalPlotUnfolding_yields(int nsel = 0, int ReBin = 1, TString XTitle = "N_{jets}", TString units = "", TString plotName = "histo_nice.root", TString outputName = "njets",
                bool isLogY = false, bool isLogX = false, TString keyLabel0 = "Pt", TString keyLabel1 = "MM", bool isNormalized = false) {

  gInterpreter->ExecuteMacro("GoodStyle.C");
  //gROOT->LoadMacro("StandardPlotUnfolding.C");
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
  sprintf(filename3,"_nsel%d_dy2_rebin%d_default.root",me,ReBin);
  TString plotName2=plotName;
  TString plotName3=plotName;
  plotName.Append(filename1);
  TFile* file1 = new TFile(plotName, "read");  if(!file1) {printf("File %s does not exist\n",plotName.Data()); return;}
  plotName2=plotName2.Append(filename2);
  plotName3=plotName3.Append(filename3);;
  
  TH1D* hData;
  TH1D* hPred1; TH1D* hPred1_PDF; TH1D* hPred1_QCD;
  TH1D* hPred2; TH1D* hPred2_PDF; TH1D* hPred2_QCD;
  TH1D* hPred3; TH1D* hPred3_PDF; TH1D* hPred3_QCD;

  if     (nsel == 0){
    printf("Unfolding style plots\n");
    hData      = (TH1D*)file1->Get(Form("unfold"));
    hPred1     = (TH1D*)file1->Get(Form("hDDil%s%s"    ,keyLabel0.Data(),keyLabel1.Data()));
  }
  else {
    return;
  }

  TCanvas* c1 = new TCanvas("c1", "c1",5,5,500,500);

  c1->SetBottomMargin(0.1);
  c1->cd();
 
  if(isLogY == true) c1->SetLogy();
  if(isLogX == true) c1->SetLogx();
  //draw pad1

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
  hPred1->GetYaxis()->SetLabelSize  (0.050);
  hPred1->GetYaxis()->SetNdivisions (  505);
  hPred1->GetYaxis()->SetTitleFont  (   42);
  hPred1->GetYaxis()->SetTitleOffset(  1.7);
  hPred1->GetYaxis()->SetTitleSize  (0.040);
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
  legend->AddEntry(hPred1, "aMC@NLO");

  /********** MADGRAPH **************/
  TFile *file2 = new TFile(plotName2, "read");  if(!file2) {printf("File %s does not exist\n",plotName.Data()); return;}
  hPred2     = (TH1D*)file2->Get(Form("hDDil%s%s"    ,keyLabel0.Data(),keyLabel1.Data()));
  normalization[0] = TotalLumi;
  if(isNormalized) {normalization[0] = hPred2->GetSumOfWeights();};
  hPred2->Scale(1./normalization[0]);
  hPred2->SetMarkerStyle(kFullCircle);
  hPred2->Draw("same");
  legend->AddEntry(hPred2, "MADGRAPH");


  /************ POWHEG *************/
  TFile *file3 = new TFile(plotName3, "read");  if(!file3) {printf("File %s does not exist\n",plotName.Data()); return;}
  hPred3     = (TH1D*)file3->Get(Form("hDDil%s%s"    ,keyLabel0.Data(),keyLabel1.Data()));
  if(isNormalized) {normalization[0] = hPred3->GetSumOfWeights();};
  hPred3->Scale(1./normalization[0]);
  hPred3->SetMarkerStyle(23);
  hPred3->Draw("same");
  legend->AddEntry(hPred3, "POWHEG");

  CMS_lumi( c1, 4, 11 );
  legend->Draw();

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
