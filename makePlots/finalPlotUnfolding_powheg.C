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
#include <TGaxis.h>
#include "../macros/CPlot.hh"	          // helper class for plots
#include "../macros/MitStyleRemix.hh"      // style settings for drawing

bool isDebug = true;

void eraselabel(TPad *p,Double_t h){
  p->cd();
  TPad *pe = new TPad("pe","pe",0.02,0,p->GetLeftMargin(),h);	   
  pe->Draw();
  pe->SetFillColor(p->GetFillColor()); 
  pe->SetBorderMode(0);
}


TH1D *makeDiffHist(TH1D* hData, TH1D* hFit, const TString name)
{
  //double xbin[37]={0.3,1,2,3,4,5,6,7,8,9,10,11,12,13,14,16,18,20,22,25,28,32,37,43,52,65,85,120,160,190,220,250,300,400,500,800,1500};
  //TH1D* hDiff = new TH1D("h0","h0",36,xbin);
  double xbin[35]={0.3,1,2,3,4,5,6,7,8,9,10,11,12,13,14,16,18,20,22,25,28,32,37,43,52,65,85,120,160,190,220,250,300,400,1500};
  TH1D* hDiff = new TH1D("h0","h0",34,xbin);
  //TH1D *hDiff = (TH1D*)hData->Clone("hDiff");
  hDiff->SetName(name);
  for(Int_t ibin=1; ibin<=hData->GetNbinsX(); ibin++) {
    
    Double_t diff=0;
    Double_t err=0;
    if(hData->GetBinContent(ibin)!=0)
      {
	diff = hFit->GetBinContent(ibin)/hData->GetBinContent(ibin);
	err = hFit->GetBinError(ibin)/hData->GetBinContent(ibin);
      }
    hDiff->SetBinContent(ibin,diff);
    hDiff->SetBinError(ibin,err);   
  }
  
  hDiff->GetYaxis()->SetTitleOffset(0.55);
  hDiff->GetYaxis()->SetTitleSize(0.13);
  hDiff->GetYaxis()->SetLabelSize(0.10);
  hDiff->GetYaxis()->SetNdivisions(104);
  hDiff->GetYaxis()->CenterTitle();
  hDiff->GetXaxis()->SetTitleOffset(1.2);
  hDiff->GetXaxis()->SetTitleSize(0.13);
  hDiff->GetXaxis()->SetLabelSize(0.12);
  hDiff->GetXaxis()->CenterTitle();
  
  return hDiff;
}

TH1D* myratio(TH1D* g1,TH1D* g2) {
  std::cout << "New" << std::endl;
  
  TH1D* g3= (TH1D*)g1->Clone("httt");;

  Double_t   x1=0.,   y1=0., x2=0., y2=0.;
  Double_t pull=1.0, pullerr=0.0;

  for (Int_t i=1; i<=g1->GetNbinsX(); i++) {
    pull = 1.0; pullerr = 0.0;
    if(g1->GetBinContent(i)>0 && g2->GetBinContent(i)>0)
      {
	pull = (g1->GetBinContent(i)/g2->GetBinContent(i));
	pullerr = pull*g1->GetBinError(i)/g1->GetBinContent(i);
	g3->SetBinContent(i,pull);
	g3->SetBinError(i,pullerr);
      }
    else {
      printf("0 events in %d\n",i);
    }
  }
  return g3;
}

void finalPlotUnfolding_powheg(int nsel = 0, int ReBin = 1, TString XTitle = "N_{jets}", TString units = "", TString plotName = "histo_nice.root", TString outputName = "njets",
                bool isLogY = false, bool isLogX = false, TString keyLabel0 = "Pt", TString keyLabel1 = "MM", bool isNormalized = false) {
  std::cout << "Are we here? " << std::endl;
  //gInterpreter->ExecuteMacro("PaperStyle.C");
  gStyle->SetOptStat(0);

  double TotalLumi = 35900.0;
  double normalization[2];

  double xbin[35]={0.3,1,2,3,4,5,6,7,8,9,10,11,12,13,14,16,18,20,22,25,28,32,37,43,52,65,85,120,160,190,220,250,300,400,1500};
  TH1D* hZmmPtDiffDummySplit2 = new TH1D("h0","h0",34,xbin);
   
  int me=0;
  if (strncmp(keyLabel1.Data(),"EE",2)==0){me=1;}
  if (strncmp(keyLabel1.Data(),"LL",2)==0){me=2;}

  char filename1[300];
  char filename2[300];
  char filename3[300];
  sprintf(filename1,"_nsel%d_dy3_rebin%d_default.root",me,ReBin);//default, AMCNLO
  sprintf(filename2,"_nsel%d_dy2_rebin%d_default.root",me,ReBin);
  sprintf(filename3,"DYJetsToEE_POWHEG_MINLO.root");

  TString plotName2=plotName;
  TString plotName3="/afs/cern.ch/work/c/ceballos/public/samples/panda/v_001_0/";
  plotName.Append(filename1);
  plotName2=plotName2.Append(filename2);
  plotName3=plotName3.Append(filename3);
  //plotName3=filename3;
  std::cout <<  plotName << std::endl;
  std::cout <<  plotName2 << std::endl;
  std::cout <<  plotName3 << std::endl;
  
  TH1D* hData;
  TH1D* hPred1;
  TH1D* hPred2;
  TH1D* hPred3_pdf;
  TH1D* hPred3_qcd;
  TH1D* hPred3;
  TString keyLabel2;
  if(keyLabel0 == "Pttest")
    {
      keyLabel2="Pt";
    }
  else
    {
      keyLabel2=keyLabel0;
    }
  TFile* file1 = new TFile(plotName, "read");  if(!file1) {printf("File %s does not exist\n",plotName.Data()); return;}
  hData      = (TH1D*)file1->Get(Form("unfold"));
  hPred1     = (TH1D*)file1->Get(Form("hDDil%s%s"    ,keyLabel2.Data(),keyLabel1.Data()));
  TFile *file2 = new TFile(plotName2, "read");  if(!file2) {printf("File %s does not exist\n",plotName.Data()); return;}
  hPred2 = (TH1D*)file2->Get(Form("hDDil%s%s"	 ,keyLabel2.Data(),keyLabel1.Data()));
  TFile *file3 = new TFile(plotName3, "read");  if(!file3) {printf("File %s does not exist\n",plotName.Data()); return;}
  hPred3 = (TH1D*)file3->Get(Form("hDDil%s%s"	 ,keyLabel2.Data(),"EE"));
  hPred3_qcd = (TH1D*)file3->Get(Form("hDDil%s%s_QCD"	 ,keyLabel2.Data(),"EE"));
  hPred3_pdf = (TH1D*)file3->Get(Form("hDDil%s%s_PDF"	 ,keyLabel2.Data(),"EE"));
  
  double pull; 
  double pullerr;

  Int_t linecolorPowheg = kGreen+3;
  Int_t fillcolorPowheg = kGreen-10;
  Int_t markerstylePowheg = 22;
  Int_t linecolorAMCAtNlo = kRed+2;
  Int_t fillcolorAMCAtNlo = kRed-10;
  Int_t markerstyleAMCAtNLO = 21;
  Int_t linecolorFEWZ = kBlue;
  Int_t fillcolorFEWZ = kBlue-10;
  Int_t markerstyleFEWZ = 24;
  
  char xlabel[100];     // string buffer for x-axis label
  char ylabel[100];     // string buffer for y-axis label
  
  // label for lumi
  char lumitext[100];
  sprintf(lumitext,"%.1f fb^{-1}  (13 TeV)",35.9);  
 
  TCanvas *c1 = MakeCanvas("c1","c1",800,800);
  c1->cd()->SetTopMargin(0.10);
  c1->cd()->SetBottomMargin(0.15);
  c1->cd()->SetLeftMargin(0.15);  
  c1->cd()->SetRightMargin(0.07);  
  c1->cd()->SetTickx(1);
  c1->cd()->SetTicky(1);  
  TGaxis::SetMaxDigits(3);

   // canvas for ratio, will be modified
  vector<TCanvas*> cR; // SPLIT
  cR.push_back(  MakeCanvas("c_0_ratio","c",800,800) );
  cR.push_back(  MakeCanvas("c_1_ratio","c",800,400) );
  cR.push_back(  MakeCanvas("c_2_ratio","c",800,600) );
  cR.push_back(  MakeCanvas("c_3_ratio","c",800,800) );
  cR.push_back(  MakeCanvas("c_4_ratio","c",800,1000) );
  double topmargin=0.10;
  double bottommargin=0.149;
  double firstextra=0.05; // for CMS Preliminary, etc..
  
  for(int n=2;n<=4 ;++n)
    {
      double base = (1.0 - 0.)*(1.-topmargin-bottommargin-firstextra)/n;
      
      cR[n]->Divide(1,n,0,0);
      cR[n]->Draw();
      for( int subpad=1; subpad<=n; ++subpad)
  	{
	  double ymin = bottommargin + (subpad-1)* base;
	  double ymax = bottommargin + (subpad)* base;
	  
	  cR[n]->cd(subpad)->SetTopMargin(0);
	  cR[n]->cd(subpad)->SetBottomMargin(0);
	  cR[n]->cd(subpad)->SetLeftMargin(0.15);  
	  cR[n]->cd(subpad)->SetRightMargin(0.07);  
	  cR[n]->cd(subpad)->SetTickx(1);
	  cR[n]->cd(subpad)->SetTicky(1);  
	  if (subpad==1){
	    ymin=0;
	    cR[n]->cd(subpad)->SetBottomMargin(bottommargin/(bottommargin+base));
	  }
	  if (subpad==n){
	    ymax=1;
	    cR[n]->cd(subpad)->SetTopMargin(topmargin/(topmargin+base+firstextra));
	  }
	  
	  cout <<" subpad "<<subpad <<" : "<<ymin << " -- "<<ymax<<endl;
	  cR[n]->cd(subpad)->SetPad(0,ymin,1,ymax);
	  
  	}
      
    }
  cR[0]->cd();

  int n=4;
  double base = (1.0 - 0.)*(1.-topmargin-bottommargin-firstextra)/n;
  double eps=0.01;


  normalization[0] = TotalLumi; normalization[1] = TotalLumi;
  if(isNormalized) {normalization[0] = hPred1->GetSumOfWeights(); normalization[1] = hData->GetSumOfWeights();};
  hPred1->Scale(1./normalization[0]);
  if(!isNormalized)
    hPred1->Scale(2008./2075); // Guillelmo normalizes amc@nlo inclusively to FEWZ NNLO cross section (with NNPDF3.1). Revert back to the amc@nlo inclusive cross section prediction
  if(isNormalized) {normalization[0] = hPred2->GetSumOfWeights();};
  hPred2->Scale(1./normalization[0]);
  if(!isNormalized)
    hPred2->Scale(2008./2075); // Guillelmo normalizes amc@nlo inclusively to FEWZ NNLO cross section (with NNPDF3.1). Revert back to the amc@nlo inclusive cross section prediction
  hPred3->Scale(1.0,"width");
  hPred3->Scale(1952./1.86939e+10);
  hPred3_qcd->Scale(1.0,"width");
  hPred3_qcd->Scale(1952./1.86939e+10);
  hPred3_pdf->Scale(1.0,"width");
  hPred3_pdf->Scale(1952./1.86939e+10);
  for(int i=1; i<=hPred3->GetNbinsX(); i++) {
    double err = sqrt((hPred3_pdf->GetBinContent(i)-hPred3->GetBinContent(i))*(hPred3_pdf->GetBinContent(i)-hPred3->GetBinContent(i))+hPred3->GetBinError(i)*hPred3->GetBinError(i)+(hPred3_qcd->GetBinContent(i)-hPred3->GetBinContent(i))*(hPred3_qcd->GetBinContent(i)-hPred3->GetBinContent(i)));
    hPred3->SetBinError(i,err);
  }
  if(isNormalized) {normalization[0] = hPred3->GetSumOfWeights(); hPred3->Scale(1./normalization[0]);};
  hData ->Scale(1./normalization[1]);
  
  hData->GetYaxis()->SetTitleFont(43);
  hData->GetYaxis()->SetTitleSize(35);
  hData->GetYaxis()->SetLabelFont(43);
  hData->GetYaxis()->SetLabelSize(30);
  hData->GetXaxis()->SetTitleFont(43);
  hData->GetXaxis()->SetTitleSize(35);
  hData->GetXaxis()->SetLabelFont(43);
  hData->GetXaxis()->SetLabelSize(30);
  hData->GetYaxis()->SetTitleOffset(1.4);
  //hData->GetXaxis()->SetLimits(0.8, 1500);

  
  hZmmPtDiffDummySplit2->GetYaxis()->SetTitleFont(43);
  hZmmPtDiffDummySplit2->GetYaxis()->SetTitleSize(35);
  hZmmPtDiffDummySplit2->GetYaxis()->SetLabelFont(43);
  hZmmPtDiffDummySplit2->GetYaxis()->SetLabelSize(30);
  hZmmPtDiffDummySplit2->GetXaxis()->SetTitleFont(43);
  hZmmPtDiffDummySplit2->GetXaxis()->SetTitleSize(35);
  hZmmPtDiffDummySplit2->GetXaxis()->SetLabelFont(43);
  hZmmPtDiffDummySplit2->GetXaxis()->SetLabelSize(30);
  hZmmPtDiffDummySplit2->GetYaxis()->SetTitleOffset(1.4);
 
  hData->SetFillStyle(3554);
  hData->SetFillColor(TColor::GetColor("#828282"));
  hPred1->SetFillColor(fillcolorAMCAtNlo);
  hPred2->SetFillColor(fillcolorPowheg);
  hPred3->SetFillColor(fillcolorFEWZ);
  hPred1->SetFillStyle(3001);
  hPred2->SetFillStyle(3001);
  hPred3->SetFillStyle(3001);
 
  CPlot::sOutDir = "plots";  
  const TString format("all");

  TString plot_name;
  TString ratio_name;
 
  if(nsel==0)
    {
      plot_name="zmm_shower";
      ratio_name="zmm_shower_ratio";
      sprintf(xlabel,"p_{T}^{#mu^{+}#mu^{-}} [GeV]");
      sprintf(ylabel,"d#sigma/dp_{T}^{#mu^{+}#mu^{-}} [pb/GeV]");
    }
  else if (nsel==1)
    {
      plot_name="zee_shower";
      ratio_name="zee_shower_ratio";
      sprintf(xlabel,"p_{T}^{e^{+}e^{-}} [GeV]");
      sprintf(ylabel,"d#sigma/dp_{T}^{e^{+}e^{-}} [pb/GeV]");
    }
  else
    {
      if(!isNormalized)
	{
	  if(keyLabel0 == "Pt")
	    {
	      plot_name="zll_shower";
	      ratio_name="zll_shower_ratio";
	    }
	  else if(keyLabel0 == "PtRap0")
	    {
	      plot_name="zll_double_rap0";
	      ratio_name="zll_double_ratio_rap0";
	    }
	  else if(keyLabel0 == "PtRap1")
	    {
	      plot_name="zll_double_rap1";
	      ratio_name="zll_double_ratio_rap1";
	    }
	  else if(keyLabel0 == "PtRap2")
	    {
	      plot_name="zll_double_rap2";
	      ratio_name="zll_double_ratio_rap2";
	    }
	  else if(keyLabel0 == "PtRap3")
	    {
	      plot_name="zll_double_rap3";
	      ratio_name="zll_double_ratio_rap3";
	    }
	  else if(keyLabel0 == "PtRap4")
	    {
	      plot_name="zll_double_rap4";
	      ratio_name="zll_double_ratio_rap4";
	    }
	}
      else
	{
	  if(keyLabel0 == "Pt")
	    {
	      plot_name="zll_norm";
	      ratio_name="zll_ratio_norm";
	    } 
	   else if(keyLabel0 == "PtRap0")
	    {
	      plot_name="zll_double_normrap0";
	      ratio_name="zll_double_ratio_normrap0";
	    }
	  else if(keyLabel0 == "PtRap1")
	    {
	      plot_name="zll_double_normrap1";
	      ratio_name="zll_double_ratio_normrap1";
	    }
	  else if(keyLabel0 == "PtRap2")
	    {
	      plot_name="zll_double_normrap2";
	      ratio_name="zll_double_ratio_normrap2";
	    }
	  else if(keyLabel0 == "PtRap3")
	    {
	      plot_name="zll_double_normrap3";
	      ratio_name="zll_double_ratio_normrap3";
	    }
	  else if(keyLabel0 == "PtRap4")
	    {
	      plot_name="zll_double_normrap4";
	      ratio_name="zll_double_ratio_normrap4";
	    }
	}
      sprintf(xlabel,"p_{T}^{l^{+}l^{-}} [GeV]");
      sprintf(ylabel,"d#sigma/dp_{T}^{l^{+}l^{-}} [pb/GeV]");
    }
  
  
  CPlot plotZmmPt(plot_name,"",xlabel,ylabel);
  plotZmmPt.SetXRange(0.3,1500);
  plotZmmPt.AddHist1D(hZmmPtDiffDummySplit2);
  plotZmmPt.AddHist1D(hData,"Data","PE2",1,1,20);
  plotZmmPt.AddHist1D(hPred1,"aMC@NLO","PE",linecolorAMCAtNlo,1,markerstyleAMCAtNLO);
  plotZmmPt.AddHist1D(hPred2,"POWHEG","PE",linecolorPowheg,1,markerstylePowheg);
  plotZmmPt.AddHist1D(hPred3,"MINLO","PE",linecolorFEWZ,1,markerstyleFEWZ);
  plotZmmPt.AddHist1D(hData,"PE2",1,1,20);
  plotZmmPt.AddHist1D(hData,"P",1,1,20);
 
  plotZmmPt.AddTextBox("#bf{CMS}",0.08,0.90,0.34,0.96,0);
  plotZmmPt.AddTextBox("|#eta|<2.4, p_{T}>25 GeV",0.18,0.15,0.4,0.25,0);
  plotZmmPt.AddTextBox(lumitext,0.69,0.90,0.93,0.96,0);
  plotZmmPt.SetYRange(0,1.12*(hData->GetMaximum() + sqrt(hData->GetMaximum())));
  plotZmmPt.SetLogx(1);
  plotZmmPt.SetLogy(0);
  plotZmmPt.SetLegend(0.6,0.64,0.95,0.87);
  plotZmmPt.Draw(c1,kTRUE,format);

  // draw split
  TH1D *hZmmPtDiffDummySplit =  makeDiffHist(hData,hData,"hZmmPtDiffDummySplit");
  hZmmPtDiffDummySplit->SetFillStyle(3554);
  hZmmPtDiffDummySplit->SetFillColor(TColor::GetColor("#828282"));
  hZmmPtDiffDummySplit->GetYaxis()->SetTitleFont(43);
  hZmmPtDiffDummySplit->GetYaxis()->SetTitleSize(27);
  hZmmPtDiffDummySplit->GetYaxis()->SetTitleOffset(2);
  hZmmPtDiffDummySplit->GetYaxis()->SetLabelFont(43);
  hZmmPtDiffDummySplit->GetYaxis()->SetLabelSize(25);
  hZmmPtDiffDummySplit->GetYaxis()->SetNdivisions(408);
  hZmmPtDiffDummySplit->GetXaxis()->SetTitleFont(43);
  hZmmPtDiffDummySplit->GetXaxis()->SetTitleSize(35);
  hZmmPtDiffDummySplit->GetXaxis()->SetTitleOffset(3.2);
  hZmmPtDiffDummySplit->GetXaxis()->SetLabelFont(43);
  hZmmPtDiffDummySplit->GetXaxis()->SetLabelSize(30);
  hZmmPtDiffDummySplit->GetXaxis()->SetTickSize(.1);
  hZmmPtDiffDummySplit->GetXaxis()->SetRangeUser(0.3,800);
  
  TH1D *ZPT_RATIO_STAT_SYS_UNCERT_BAND_DATA_AMCATNLO_COMP =  myratio(hPred1,hData);

  CPlot plotZmmPtDiffSplit_AMCATNLO(ratio_name,"","","aMC@NLO/Data");
  plotZmmPtDiffSplit_AMCATNLO.AddHist1D( hZmmPtDiffDummySplit);
  plotZmmPtDiffSplit_AMCATNLO.AddHist1D(ZPT_RATIO_STAT_SYS_UNCERT_BAND_DATA_AMCATNLO_COMP,"E0",linecolorAMCAtNlo,1,markerstyleAMCAtNLO);
  plotZmmPtDiffSplit_AMCATNLO.AddHist1D(hZmmPtDiffDummySplit,"E2",TColor::GetColor("#828282"),20,1);
  plotZmmPtDiffSplit_AMCATNLO.AddTextBox("#bf{CMS}",0.205,0.51,0.465,0.66,0);
  if(isNormalized)
    plotZmmPtDiffSplit_AMCATNLO.AddTextBox("#frac{1}{#sigma} #frac{d#sigma}{dp_{T}^{l^{+}l^{-}}}",0.155,0.801,0.415,0.917,0);
  plotZmmPtDiffSplit_AMCATNLO.AddTextBox("|#eta|<2.4, p_{T}>25 GeV",0.56,0.55,0.765,0.7,0);
  plotZmmPtDiffSplit_AMCATNLO.AddTextBox(lumitext,0.69,0.721,0.93,0.867,0);
  
  plotZmmPtDiffSplit_AMCATNLO.SetLogx(1);
  plotZmmPtDiffSplit_AMCATNLO.SetYRange(0.7+eps,1.2 + (1.2-0.7) *(firstextra)/ base );
  plotZmmPtDiffSplit_AMCATNLO.AddLine(0, 1,1500, 1,kBlack,1);
  plotZmmPtDiffSplit_AMCATNLO.AddLine(0, 1.1,1500, 1.1,kBlack,3);
  plotZmmPtDiffSplit_AMCATNLO.AddLine(0,0.9,1500,0.9,kBlack,3);
  
  hZmmPtDiffDummySplit->GetYaxis()->SetNdivisions(405);

  TH1D *ZPT_RATIO_STAT_SYS_UNCERT_BAND_DATA_POWHEG_COMP =  myratio(hPred2,hData);
    
  CPlot plotZmmPtDiffSplit_POWHEG("zmmPtSplit","","","POWHEG/Data");
  plotZmmPtDiffSplit_POWHEG.AddHist1D( hZmmPtDiffDummySplit);
  plotZmmPtDiffSplit_POWHEG.AddHist1D(ZPT_RATIO_STAT_SYS_UNCERT_BAND_DATA_POWHEG_COMP,"E0",linecolorPowheg,1,markerstylePowheg);
  plotZmmPtDiffSplit_POWHEG.AddHist1D(hZmmPtDiffDummySplit,"E2",TColor::GetColor("#828282"),20,1);
  plotZmmPtDiffSplit_POWHEG.SetLogx(1);
  plotZmmPtDiffSplit_POWHEG.SetYRange(0.7+eps,1.3-eps);
  plotZmmPtDiffSplit_POWHEG.AddLine(0, 1,1500, 1,kBlack,1);
  plotZmmPtDiffSplit_POWHEG.AddLine(0, 1.1,1500, 1.1,kBlack,3);
  plotZmmPtDiffSplit_POWHEG.AddLine(0,0.9,1500,0.9,kBlack,3);

  TH1D *ZPT_RATIO_STAT_SYS_UNCERT_BAND_DATA_FEWZ_COMP =  myratio(hPred3,hData);
  hZmmPtDiffDummySplit->GetXaxis()->SetLabelSize(30);
  
  CPlot plotZmmPtDiffSplit_FEWZ("zmmPtSplit","",xlabel,"MINLO/Data");
  plotZmmPtDiffSplit_FEWZ.AddHist1D(hZmmPtDiffDummySplit);
  plotZmmPtDiffSplit_FEWZ.AddHist1D(ZPT_RATIO_STAT_SYS_UNCERT_BAND_DATA_FEWZ_COMP,"E0",linecolorFEWZ,1,markerstyleFEWZ);
  plotZmmPtDiffSplit_FEWZ.AddHist1D(hZmmPtDiffDummySplit,"E2",TColor::GetColor("#828282"),20,1);
  plotZmmPtDiffSplit_FEWZ.SetLogx(1);
  plotZmmPtDiffSplit_FEWZ.SetYRange(0.7+eps,1.3-eps);
  plotZmmPtDiffSplit_FEWZ.AddLine(0, 1,1500, 1,kBlack,1);
  plotZmmPtDiffSplit_FEWZ.AddLine(0, 1.1,1500, 1.1,kBlack,3);
  plotZmmPtDiffSplit_FEWZ.AddLine(0,0.9,1500,0.9,kBlack,3);
  
  plotZmmPtDiffSplit_FEWZ.Draw(cR[3],kFALSE,format,1);
  hZmmPtDiffDummySplit->GetXaxis()->SetLabelSize(0);
  plotZmmPtDiffSplit_POWHEG.Draw(cR[3],kFALSE,format,2);
  plotZmmPtDiffSplit_AMCATNLO.Draw(cR[3],kTRUE,format,3);


  printf("Total yields: %f - %f %f %f\n", hData->Integral("Width"),hPred1->Integral("Width"),hPred2->Integral("Width"),hPred3->Integral("Width"));

  char CommandToExec[300];
  sprintf(CommandToExec,"mkdir -p plots");
  gSystem->Exec(CommandToExec);  

  /*if(strcmp(outputName.Data(),"") != 0){
    TString myOutputFile;
    myOutputFile = Form("plots/%s.eps",outputName.Data());
    //c1->SaveAs(myOutputFile.Data());
    myOutputFile = Form("plots/%s.png",outputName.Data());
    c1->SaveAs(myOutputFile.Data());
    myOutputFile = Form("plots/%s.pdf",outputName.Data());
    c1->SaveAs(myOutputFile.Data());
    }*/

}
