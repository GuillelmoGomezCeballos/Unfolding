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
  histo->SetFillColor(12);
  histo->SetFillStyle(3345);
  histo->SetLineColor  (kBlack);
  histo->SetMarkerStyle(kFullCircle);
}

void finalPlotWWUnfolding(TString keyLabel0 = "MLL", bool isNormalized = false) {

  TString XTitle = "X";
  TString units = "GeV";
  bool isLogY = false;
  bool isLogX = false;

  if     (keyLabel0 == "MLL"    || keyLabel0 == "MLL0JET")    {XTitle = "m_{ll}"; isLogX = true;}
  else if(keyLabel0 == "DPHILL" || keyLabel0 == "DPHILL0JET") {XTitle = "#Delta#phi_{ll}"; units = "rad";}
  else if(keyLabel0 == "PTL1"   || keyLabel0 == "PTL10JET")   {XTitle = "p_{T}^{max}"; isLogX = true;}
  else if(keyLabel0 == "PTL2"   || keyLabel0 == "PTL20JET")   {XTitle = "p_{T}^{min}"; isLogX = true;}
  else if(keyLabel0 == "PTLL"   || keyLabel0 == "PTLL0JET")   {XTitle = "p_{T}^{ll}"; isLogX = true;}
  else if(keyLabel0 == "NJET")  {XTitle = "N_{jets}"; units = "";}
  else if(keyLabel0 == "N0JET") {XTitle = ""; units = "";}

  gInterpreter->ExecuteMacro("PaperStyle.C");
  gStyle->SetOptStat(0);

  bool isDebug = true;

  double scaleDFSF = 1.0; if(keyLabel0.Contains("N0JET")) scaleDFSF = 2.0;

  TFile *_fileGenWW = TFile::Open("/afs/cern.ch/work/c/ceballos/public/samples/panda/v_001_0/genWW.root");
  TH1D* hPred1     = (TH1D*)_fileGenWW->Get(Form("hDWW%s",keyLabel0.Data()));
  TH1D* hPred1_PDF = (TH1D*)_fileGenWW->Get(Form("hDWW%s_PDF",keyLabel0.Data()));
  TH1D* hPred1_QCD = (TH1D*)_fileGenWW->Get(Form("hDWW%s_QCD",keyLabel0.Data()));
  TH1D* hPred1_NNLO= (TH1D*)_fileGenWW->Get(Form("hDWW%s_NNLO",keyLabel0.Data()));

  TString plotName = Form("input_files/xs_WW%s_normalized%d.root", keyLabel0.Data(), isNormalized);
  TFile *_file0 = TFile::Open(plotName.Data());
  TH1D* hData = (TH1D*)_file0->Get(Form("hDWW%s",keyLabel0.Data()));
  
  double totalUnc[3] = {TMath::Abs(1-hPred1_PDF->GetSumOfWeights() /hPred1->GetSumOfWeights()),
                        TMath::Abs(1-hPred1_QCD->GetSumOfWeights() /hPred1->GetSumOfWeights()),
                        TMath::Abs(1-hPred1_NNLO->GetSumOfWeights()/hPred1->GetSumOfWeights())};

  for(Int_t i=1;i<=hPred1->GetNbinsX();++i){
    double diff[4] = {hPred1->GetBinError(i)/hPred1->GetBinContent(i),
                      TMath::Abs(1-hPred1_PDF->GetBinContent(i) /hPred1->GetBinContent(i)),
                      TMath::Abs(1-hPred1_QCD->GetBinContent(i) /hPred1->GetBinContent(i)),
                      TMath::Abs(1-hPred1_NNLO->GetBinContent(i)/hPred1->GetBinContent(i))};

    if(isNormalized) {
      diff[1] = TMath::Abs(1-(hPred1_PDF->GetBinContent(i) /hPred1_PDF->GetSumOfWeights() )/(hPred1->GetBinContent(i)/hPred1->GetSumOfWeights()));
      diff[2] = TMath::Abs(1-(hPred1_QCD->GetBinContent(i) /hPred1_QCD->GetSumOfWeights() )/(hPred1->GetBinContent(i)/hPred1->GetSumOfWeights()));
      diff[3] = TMath::Abs(1-(hPred1_NNLO->GetBinContent(i)/hPred1_NNLO->GetSumOfWeights())/(hPred1->GetBinContent(i)/hPred1->GetSumOfWeights()));
    }

    hData->SetBinContent(i,hData->GetBinContent(i)*hPred1->GetBinContent(i));
    hData->SetBinError  (i,hData->GetBinError  (i)*hPred1->GetBinContent(i));

    hPred1->SetBinError(i,sqrt(diff[0]*diff[0]+diff[1]*diff[1]+diff[2]*diff[2]+diff[3]*diff[3])*hPred1->GetBinContent(i));
    if(isDebug) printf("hPredSyst (%2d) %5.2f %5.2f %5.2f %5.2f -> %5.2f\n",i,100*diff[0],100*diff[1],100*diff[2],100*diff[3],100*hPred1->GetBinError(i)/hPred1->GetBinContent(i));
  }

  hData ->Scale(scaleDFSF);
  hPred1->Scale(scaleDFSF);
  
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
  if(isLogX == true) {pad1->SetLogx(); pad2->SetLogx();}

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
  if     (!isNormalized && keyLabel0.Contains("MLL"))    theYTitle = "d#sigma/dm_{ll} [pb/GeV]";
  else if(!isNormalized && keyLabel0.Contains("DPHILL")) theYTitle = "d#sigma/d#Delta#phi_{ll} [pb/rad]";
  else if(!isNormalized && keyLabel0.Contains("PTL1"))   theYTitle = "d#sigma/dp_{T}^{max} [pb/GeV]";
  else if(!isNormalized && keyLabel0.Contains("PTL2"))   theYTitle = "d#sigma/dp_{T}^{mix} [pb/GeV]";
  else if(!isNormalized && keyLabel0.Contains("PTLL"))   theYTitle = "d#sigma/dp_{T}^{ll} [pb/GeV]";
  else if(!isNormalized && keyLabel0.Contains("NJET"))   theYTitle = "d#sigma/dn_{jets}";
  else if( isNormalized && keyLabel0.Contains("MLL"))    theYTitle = "1/#sigma d#sigma/dm_{ll} [1/GeV]";
  else if( isNormalized && keyLabel0.Contains("DPHILL")) theYTitle = "1/#sigma d#sigma/d#Delta#phi_{ll} [1/rad]";
  else if( isNormalized && keyLabel0.Contains("PTL1"))   theYTitle = "1/#sigma d#sigma/dp_{T}^{max} [1/GeV]";
  else if( isNormalized && keyLabel0.Contains("PTL2"))   theYTitle = "1/#sigma d#sigma/dp_{T}^{mix} [1/GeV]";
  else if( isNormalized && keyLabel0.Contains("PTLL"))   theYTitle = "1/#sigma d#sigma/dp_{T}^{ll} [1/GeV]";
  else if( isNormalized && keyLabel0.Contains("NJET"))   theYTitle = "1/#sigma d#sigma/dn_{jets}";
  else if(                 keyLabel0.Contains("N0JET"))  theYTitle = "#sigma [pb]";
  else {printf("PROBLEM!\n"); return;}

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

  TAxis *xa = hData->GetXaxis();
  if(keyLabel0.Contains("N0JET")){
   xa->SetBinLabel(1 ,"p_{T}^{j} < 25 GeV");
   xa->SetBinLabel(2 ,"p_{T}^{j} < 30 GeV");
   xa->SetBinLabel(3 ,"p_{T}^{j} < 35 GeV");
   xa->SetBinLabel(4 ,"p_{T}^{j} < 45 GeV");
   xa->SetBinLabel(5 ,"p_{T}^{j} < 60 GeV");
  }
  hPred1->SetTitle("");
  hData ->SetTitle("");
  double normalization[2] = {1.0, 1.0};
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
  legend->AddEntry(hData,  "Data");
  legend->AddEntry(hPred1, "POWHEG");
  legend->Draw();

  CMS_lumi( pad1, 4, 11 );

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
  double pullinv; 
  double pullinverr;

  for(int i=1; i<=hNum->GetNbinsX(); i++){
      pull = 1.0; pullerr = 0.0;
      pullinv = 1.0; pullinverr = 0.0;
      if(hNum->GetBinContent(i) > 0 && hDen->GetBinContent(i) > 0){
        pull = (hNum->GetBinContent(i)/hDen->GetBinContent(i));
	pullerr = pull*hDen->GetBinError(i)/hDen->GetBinContent(i);
        pullinv = (hDen->GetBinContent(i)/hNum->GetBinContent(i));
	pullinverr = pullinv*hDen->GetBinError(i)/hDen->GetBinContent(i);
      }
      else {
        printf("0 events in %d\n",i);
      }
      if(isDebug) printf("ratio(%2d): pred/data = %.3f +/- %.3f predUnc: %.3f\n",i,pull,pullerr,hNum->GetBinError(i)/hNum->GetBinContent(i));
      if(isDebug) printf("ratio(%2d): data/pred = %.3f +/- %.3f, sigma = %.3f pb\n",i,pullinv,pullinverr,hNum->GetBinContent(i));
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
  hRatio->GetYaxis()->SetRangeUser(0.201,1.999);
  hRatio->GetYaxis()->CenterTitle();
  eraselabel(pad1,hData->GetXaxis()->GetLabelSize());

  printf("Total yields: %f - %f\n", hData->GetSumOfWeights(),hPred1->GetSumOfWeights());

  char CommandToExec[300];
  sprintf(CommandToExec,"mkdir -p plotsww");
  gSystem->Exec(CommandToExec);  

  TString outputName = Form("unf_WW%s_normalized%d",keyLabel0.Data(),isNormalized);
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
