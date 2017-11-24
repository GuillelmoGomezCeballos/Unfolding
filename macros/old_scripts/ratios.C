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
#include "StandardPlotUnfolding.C"
#include "CMS_lumi.C"

double scaling[8] = {1,1,1,1,1,1,1,1};
//double scaling[8] = {73.496/69.913,1.2,168.114/157.695,404.402/361.347,2.583/2.537,1,1,1}; // EM/Zjets/WZ/ZZ/VVV
//double scaling[8] = {0.94,1.04,1.04,1.01,1.00,1.02,1.01,1.05}; // EWK/QCD/VV/VVV/WS/WG/DPS/Wjets

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
  histo->GetXaxis()->SetLabelSize  (0.140);
  histo->GetXaxis()->SetNdivisions (  505);
  histo->GetXaxis()->SetTitleFont  (   42);
  histo->GetXaxis()->SetTitleOffset( 1.1);
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

  histo->SetLineColor  (kBlack);
  histo->SetMarkerStyle(kFullCircle);
}

void ratios(int nsel = 0, int ReBin = 1, TString XTitle = "N_{jets}", TString units = "", TString plotName = "histo_nice.root", TString outputName = "njets",
                bool isLogY = false, bool isLogX = false, TString keyLabel0 = "Pt", TString keyLabel1 = "MM") {
  
  int me=0;
  if (strncmp(keyLabel1.Data(),"EE",2)==0){me=1;}

  TString extraLabel = "";
  TString plotExtraName = "";
  gInterpreter->ExecuteMacro("GoodStyle.C");
  //gROOT->LoadMacro("StandardPlotUnfolding.C");
  gStyle->SetOptStat(0);
  char filename1[300];
  sprintf(filename1,"_nsel%d_dy3_rebin%d_default.root",me,ReBin);//default, AMCNLO                                                                            
  plotName.Append(filename1); 
  TFile* file = new TFile(plotName, "read");  if(!file) {printf("File %s does not exist\n",plotName.Data()); return;}
  TFile* fileExtra = new TFile(plotExtraName, "read"); bool hasFileExtra = true; if(!fileExtra->IsOpen()) hasFileExtra = false;
  char sys_name[200];
  sprintf(sys_name,"../macros/histoUnfoldingSyst%s_nsel%d_dy3_rebin1_default.root",keyLabel0.Data(),me);
  TFile* uncertainty=new TFile(sys_name,"read");if(!uncertainty) {printf("File %s does not exist\n",sys_name); return;}
  TH1D* sys=(TH1D*)uncertainty->Get("histoSyst_0");

  TH1F* hPred ;
  TH1F* hData ;

  if     (nsel == 0){
    printf("Unfolding style plots\n");
    hData  = (TH1F*)file->Get(Form("unfold"));
    hPred   = (TH1F*)file->Get(Form("hDDil%s%s",keyLabel0.Data(),keyLabel1.Data()));
    hData->Sumw2();
    hPred->Sumw2();
  }
  else {
    return;
  }
  TCanvas* c1 = new TCanvas("c1", "c1",5,5,500,500);
  //CMS_lumi( c1, 4, 12 );
  c1->SetBottomMargin(0.1);
  c1->cd();
 
  TPad *pad1 = new TPad("pad1", "pad1",0.00,0.30,1.00,1.00);
  TPad *pad2 = new TPad("pad2", "pad2",0.00,0.00,1.00,0.30);
  pad1->SetBottomMargin(0);
  pad2->SetTopMargin(0);
  pad2->SetBottomMargin(0.3);
  pad1->Draw();
  pad2->Draw();

  pad1->cd();
  gStyle->SetOptStat(0);
  if(isLogY == true){ c1->SetLogy();pad1->SetLogy();}
  if(isLogX == true) {pad1->SetLogx(); c1->SetLogx();pad2->SetLogx();}




  //myPlot.Draw(ReBin);
  //draw pad1
  hPred->GetYaxis()->SetTitle("Events");
  hPred->GetYaxis()->SetLabelFont  (   42);
  hPred->GetYaxis()->SetLabelOffset(0.015);
  hPred->GetYaxis()->SetLabelSize  (0.050);
  hPred->GetYaxis()->SetNdivisions (  505);
  hPred->GetYaxis()->SetTitleFont  (   42);
  hPred->GetYaxis()->SetTitleOffset(  1.2);
  hPred->GetYaxis()->SetTitleSize  (0.060);
  hPred->GetYaxis()->SetTickLength (0.03 );
  
  hData->SetLineColor  (kBlack);
  hData->SetMarkerSize(0.7);
  hData->SetMarkerStyle(kFullCircle);
  hPred->SetLineColor(901);
  hPred->SetFillColor(901);
  // hPred->SetFillStyle(1001);
  //hPred->SetMarkerStyle(3);
  //hPred->SetMarkerColor(kWhite);
  hPred->SetLineWidth(0);
  hPred->SetMarkerColor(901);
  hPred->SetTitle("");
  hData->SetTitle("");
  hPred->GetYaxis()->SetRangeUser(hPred->GetMinimum()/10,hPred->GetMaximum()*25);
  hPred->Draw("hist");
  hData->Draw("ep same");
  gStyle->SetOptStat(0);
  CMS_lumi( pad1, 4, 12 );
  TLegend* legend = new TLegend(0.22,0.77,0.37,0.87);

  legend->SetBorderSize(     0);
  legend->SetFillColor (     0);
  legend->SetTextAlign (    12);
  legend->SetTextFont  (    42);
  legend->SetTextSize  (0.04);
  legend->AddEntry(hData,"Unfolded data");
  legend->AddEntry(hPred, "Prediction");

  legend->Draw();

  double pull;
  double pullerr;


  pad2->cd();

  TH1D* hNum = (TH1D*) hData->Clone();
  hNum->Reset();
  TH1D* hDen = (TH1D*) hData->Clone();
  hDen->Reset();
  hNum->Add(hPred);
  hDen->Add(hData);
  TH1D* hRatio = (TH1D*) hData->Clone();
  hRatio->Reset();
  TH1D* hBand = (TH1D*) hData->Clone();
  hBand->Reset();
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
    hBand->SetBinError  (i,sys->GetBinContent(i)/100.);
  }
  units = units.ReplaceAll("BIN","");
  atributes(hRatio,XTitle.Data(),"aMC@NLO/Data",units.Data());

  hRatio->Draw("e");
  hBand->SetFillColor(12);
  hBand->SetFillStyle(3002);
  hBand->SetMarkerSize(0);
  hBand->SetLineWidth(0);
  hBand->Draw("E2same");



  // Draw a line throgh y=0
  double theLines[2] = {1.0, 0.5};
  //  if(showPulls) {theLines[0] = 0.0; theLines[1] = 1.5;}
  TLine* baseline = new TLine(hRatio->GetXaxis()->GetXmin(), theLines[0],
                              hRatio->GetXaxis()->GetXmax(), theLines[0]);
  baseline->SetLineStyle(kDashed);
  baseline->Draw();
  // Set the y-axis range symmetric around y=0
  Double_t dy = TMath::Max(TMath::Abs(hRatio->GetMaximum()),
                           TMath::Abs(hRatio->GetMinimum())) + theLines[1];
  hRatio->GetYaxis()->SetRangeUser(0.5, +1.5);
  hRatio->GetYaxis()->CenterTitle();
  eraselabel(pad1,hData->GetXaxis()->GetLabelSize());
  
  char CommandToExec[300];
  sprintf(CommandToExec,"mkdir -p plots");
  gSystem->Exec(CommandToExec);  

  if(strcmp(outputName.Data(),"") != 0){
    TString myOutputFile;
    myOutputFile = Form("plots/%s.eps",outputName.Data());
    //c1->SaveAs(myOutputFile.Data());
    myOutputFile = Form("plots/%s.png",outputName.Data());
    //c1->SaveAs(myOutputFile.Data());
    myOutputFile = Form("plots/%s.pdf",outputName.Data());
    c1->SaveAs(myOutputFile.Data());
  }

}
