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
  TH1D *hDiff = (TH1D*)hData->Clone("hDiff");
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



TGraphAsymmErrors* myratio_graph(TGraph* g1, TGraph *gpdf, TH1D* g2) {
  std::cout << "New" << std::endl;
  
  TGraphAsymmErrors* g3= (TGraphAsymmErrors*)g1->Clone("httt");;

  Double_t   x1=0.,   y1=0., x2=0., y2=0.;
  Double_t pull=1.0, pullerr=0.0;
  Double_t eyhigh=0, eylow=0;

  for (Int_t i=0; i<=g1->GetN(); i++) {
    pull = 1.0; pullerr = 0.0;
    g1->GetPoint(i,x1,y1);
    eyhigh=sqrt(g1->GetErrorYhigh(i)*g1->GetErrorYhigh(i)+gpdf->GetErrorYhigh(i)*gpdf->GetErrorYhigh(i));
    eylow=sqrt(g1->GetErrorYlow(i)*g1->GetErrorYlow(i)+gpdf->GetErrorYlow(i)*gpdf->GetErrorYlow(i));
    std::cout << "let's test " << y1 << " " << g1->GetErrorYhigh(i) << " " << gpdf->GetErrorYhigh(i) << " " << g1->GetErrorYlow(i) << " " << gpdf->GetErrorYlow(i) << std::endl;
    if(y1>0 && g2->GetBinContent(i+1)>0)
      {
	std::cout << i << " " << y1 << " " << g2->GetBinContent(i+1) << std::endl;
	//pull = (y1/g2->GetBinContent(i));
	g3->SetPoint(i,x1,y1/g2->GetBinContent(i+1));
	g3->SetPointEYhigh(i,eyhigh/g2->GetBinContent(i+1));
	g3->SetPointEYlow(i,eylow/g2->GetBinContent(i+1));
      }
    else {
      printf("0 events in %d\n",i);
    }
  }
  return g3;
}

void finalPlotUnfolding_phi_tmd(int nsel = 0, int ReBin = 1, TString XTitle = "N_{jets}", TString units = "", TString plotName = "histo_nice.root", TString outputName = "njets",
                bool isLogY = false, bool isLogX = false, TString keyLabel0 = "Pt", TString keyLabel1 = "MM", bool isNormalized = false) {
  std::cout << "Are we here? " << std::endl;
  //gInterpreter->ExecuteMacro("PaperStyle.C");
  gStyle->SetOptStat(0);

  double TotalLumi = 35900.0;
  double normalization[2];
  
  gStyle->SetEndErrorSize(0); 
 
  int me=0;
  if (strncmp(keyLabel1.Data(),"EE",2)==0){me=1;}
  if (strncmp(keyLabel1.Data(),"LL",2)==0){me=2;}

  char filename1[300];
  char filename2[300];
  char filename3[300];
  char filenameTMD[300];
  char filenameTMD_pdf[300];

  sprintf(filename1,"_nsel%d_dy3_rebin%d_default.root",me,ReBin);//default, AMCNLO
  sprintf(filename2,"_nsel%d_dy2_rebin%d_default.root",me,ReBin);
  sprintf(filename3,"DYJetsToEE_POWHEG_MINLO_3points.root");
  sprintf(filenameTMD_pdf,"cascade3-13TeV-aMCatNLO-DY-H6-iscale1-lhescale3-m10toinf-TMDset2-102200-PDF_error.root");
  sprintf(filenameTMD,"cascade3-13TeV-aMCatNLO-DY-H6-iscale1-lhescale3-m10toinf-TMDset2-102200-iwgt-scales_combine.root");


  TString plotName2=plotName;
  TString plotName3="/afs/cern.ch/work/c/ceballos/public/samples/panda/v_001_0/";
  TString plotNameTMD="/afs/cern.ch/work/a/arapyan/Run2/test/CMSSW_8_0_26_patch1/src/Unfolding/makePlots/tmd_predictions/";
  TString plotNameTMD_pdf="/afs/cern.ch/work/a/arapyan/Run2/test/CMSSW_8_0_26_patch1/src/Unfolding/makePlots/tmd_predictions/";
  plotName.Append(filename1);
  plotName2=plotName2.Append(filename2);
  plotName3=plotName3.Append(filename3);
  plotNameTMD=plotNameTMD.Append(filenameTMD);
  plotNameTMD_pdf=plotNameTMD_pdf.Append(filenameTMD_pdf);
  //plotName3=filename3;
  std::cout <<  plotName << std::endl;
  std::cout <<  plotName2 << std::endl;
  std::cout <<  plotName3 << std::endl;
  
  TH1D* hData;
  TH1D* hPred1;
  TH1D* hPred2;
  TH1D* hPred3_pdf;
  TH1D* hPred3_qcd;
  TGraphAsymmErrors* hPredTMD;
  TGraphAsymmErrors* hPredTMD_pdf;
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
  hPred3 = (TH1D*)file3->Get("hDDilPhiStarEE");
  hPred3_qcd = (TH1D*)file3->Get("hDDilPhiStarEE_QCD");
  hPred3_pdf = (TH1D*)file3->Get("hDDilPhiStarEE_PDF");
  TH1D* mcweight = (TH1D*)file3->Get("hDTotalMCWeight");
  double weight_minlo = mcweight->GetSumOfWeights();

  TFile *fileTMD = new TFile(plotNameTMD, "read");  if(!fileTMD) {printf("File %s does not exist\n",plotNameTMD.Data()); return;}
  TFile *fileTMD_pdf = new TFile(plotNameTMD_pdf, "read");  if(!fileTMD) {printf("File %s does not exist\n",plotNameTMD.Data()); return;}
  if(nsel==0||nsel==2)
    {
      hPredTMD = (TGraphAsymmErrors*)fileTMD->Get("CMS_2018_PAS_SMP_17_010/d06-x01-y01");
      hPredTMD_pdf = (TGraphAsymmErrors*)fileTMD_pdf->Get("CMS_2018_PAS_SMP_17_010/d06-x01-y01");
    }
  else
    {
      hPredTMD = (TGraphAsymmErrors*)fileTMD->Get("CMS_2018_PAS_SMP_17_010/d08-x01-y01");
      hPredTMD_pdf = (TGraphAsymmErrors*)fileTMD_pdf->Get("CMS_2018_PAS_SMP_17_010/d08-x01-y01");
    }
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
  double firstextra=0.065; // for CMS Preliminary, etc..
  
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
  hPred3->Scale(1952./weight_minlo);
  hPred3_qcd->Scale(1.0,"width");
  hPred3_qcd->Scale(1952./weight_minlo);
  hPred3_pdf->Scale(1.0,"width");
  hPred3_pdf->Scale(1952./weight_minlo);
  for(int i=1; i<=hPred3->GetNbinsX(); i++) {
    double err = sqrt((hPred3_pdf->GetBinContent(i)-hPred3->GetBinContent(i))*(hPred3_pdf->GetBinContent(i)-hPred3->GetBinContent(i))+hPred3->GetBinError(i)*hPred3->GetBinError(i)+(hPred3_qcd->GetBinContent(i)-hPred3->GetBinContent(i))*(hPred3_qcd->GetBinContent(i)-hPred3->GetBinContent(i)));
   hPred3->SetBinError(i,err);
  }
  if(isNormalized) {normalization[0] = hPred3->GetSumOfWeights();  hPred3->Scale(1./normalization[0]);};
  hData ->Scale(1./normalization[1]);

  hData->GetYaxis()->SetTitleFont(42);
  hData->GetYaxis()->SetLabelFont(42);
  hData->GetXaxis()->SetTitleFont(42);
  hData->GetXaxis()->SetLabelFont(42);
  hData->GetYaxis()->SetTitleSize(0.055);
  hData->GetXaxis()->SetTitleSize(0.055);
  hData->GetYaxis()->SetLabelSize(0.039);
  hData->GetXaxis()->SetLabelSize(0.039);
  hData->GetYaxis()->SetTitleOffset(1.30);
  hData->GetXaxis()->SetTitleOffset(1.20);
  hData->GetYaxis()->SetLabelOffset(0.015);
  hData->GetXaxis()->SetLabelOffset(0.015);
  
  hData->SetFillStyle(3004);
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
      plot_name="zmm_phi";
      ratio_name="zmm_phi_ratio";
      sprintf(xlabel,"#phi_{#eta}*");
      sprintf(ylabel,"d#sigma/d#phi_{#eta}* [pb]");
    }
  else if (nsel==1)
    {
      plot_name="zee_phi";
      ratio_name="zee_phi_ratio";
      sprintf(xlabel,"#phi_{#eta}*");
      sprintf(ylabel,"d#sigma/d#phi_{#eta}* [pb]");
    }
  else
    {
      if(!isNormalized)
	{
	  plot_name="zll_phi";
	  ratio_name="zll_phi_ratio";
	}
      else
	{
	  plot_name="zll_phi_norm";
	  ratio_name="zll_phi_ratio_norm";
	}
      sprintf(xlabel,"#phi_{#eta}*");
      if(isNormalized)
	sprintf(ylabel,"1/#sigma d#sigma/d#phi_{#eta}*");
      else
	sprintf(ylabel,"d#sigma/d#phi_{#eta}* [pb]");
    }
  TGaxis::SetExponentOffset(-0.07, -0.04, "y");
  CPlot plotZmmPt(plot_name,"",xlabel,ylabel);
  plotZmmPt.AddHist1D(hData,"Data","PE2",1,1,20);
  plotZmmPt.AddHist1D(hPred3,"MINLO","PE",linecolorFEWZ,1,markerstyleFEWZ);
  plotZmmPt.AddHist1D(hPred1,"aMC@NLO","PE",linecolorAMCAtNlo,1,markerstyleAMCAtNLO);
  plotZmmPt.AddGraph(hPredTMD,"PB TMD","PE",linecolorPowheg,markerstylePowheg,1);
  //plotZmmPt.AddHist1D(hPred2,"POWHEG","PE",linecolorPowheg,1,markerstylePowheg);
  plotZmmPt.AddHist1D(hData,"PE2",1,1,20);
  plotZmmPt.AddHist1D(hData,"P",1,1,20);
 
  plotZmmPt.AddTextBox("#bf{CMS}",0.08,0.90,0.34,0.96,0);
  if(nsel==0)
    plotZmmPt.AddTextBox("Z/#gamma^{*} #rightarrow #mu^{+}#mu^{-}",0.55,0.55,0.90,0.61,0);
  else if (nsel==1)
    plotZmmPt.AddTextBox("Z/#gamma^{*} #rightarrow e^{+}e^{-}",0.55,0.55,0.90,0.61,0);
  else
    plotZmmPt.AddTextBox("Z/#gamma^{*} #rightarrow #mu^{+}#mu^{-}, e^{+}e^{-}",0.55,0.55,0.90,0.61,0);
  plotZmmPt.AddTextBox("|#eta| < 2.4, p_{T} > 25 GeV",0.55,0.40,0.90,0.55,0);
  plotZmmPt.AddTextBox(lumitext,0.69,0.90,0.93,0.96,0);
  plotZmmPt.SetYRange(0,6900);
  if(isNormalized)
    plotZmmPt.SetYRange(0,0.15);
  plotZmmPt.SetLogx(1);
  plotZmmPt.SetLogy(0);
  plotZmmPt.SetLegend(0.62,0.66,0.95,0.87);
  plotZmmPt.Draw(c1,kTRUE,format);

  // draw split
  TH1D *hZmmPtDiffDummySplit =  makeDiffHist(hData,hData,"hZmmPtDiffDummySplit");
  hZmmPtDiffDummySplit->SetFillStyle(3004);
  hZmmPtDiffDummySplit->SetFillColor(TColor::GetColor("#828282"));
  hZmmPtDiffDummySplit->GetXaxis()->SetTitleFont(42);
  hZmmPtDiffDummySplit->GetXaxis()->SetLabelFont(42);
  hZmmPtDiffDummySplit->GetXaxis()->SetTitleSize(0.140);
  hZmmPtDiffDummySplit->GetXaxis()->SetLabelSize(0.100);
  hZmmPtDiffDummySplit->GetXaxis()->SetTitleOffset(1.20);
  hZmmPtDiffDummySplit->GetXaxis()->SetLabelOffset(0.040);

  hZmmPtDiffDummySplit->GetYaxis()->SetTitleFont(43);
  hZmmPtDiffDummySplit->GetYaxis()->SetTitleSize(27);
  hZmmPtDiffDummySplit->GetYaxis()->SetTitleOffset(2);
  hZmmPtDiffDummySplit->GetYaxis()->SetLabelFont(43);
  hZmmPtDiffDummySplit->GetYaxis()->SetLabelSize(25);
  hZmmPtDiffDummySplit->GetYaxis()->SetNdivisions(408);
  hZmmPtDiffDummySplit->GetXaxis()->SetTickSize(.1);
  
  TH1D *ZPT_RATIO_STAT_SYS_UNCERT_BAND_DATA_AMCATNLO_COMP =  myratio(hPred1,hData);

  CPlot plotZmmPtDiffSplit_AMCATNLO(ratio_name,"","","aMC@NLO/Data");
  plotZmmPtDiffSplit_AMCATNLO.AddHist1D( hZmmPtDiffDummySplit);
  plotZmmPtDiffSplit_AMCATNLO.AddHist1D(ZPT_RATIO_STAT_SYS_UNCERT_BAND_DATA_AMCATNLO_COMP,"E0",linecolorAMCAtNlo,1,markerstyleAMCAtNLO);
  plotZmmPtDiffSplit_AMCATNLO.AddHist1D(hZmmPtDiffDummySplit,"E2",TColor::GetColor("#828282"),20,1);
  plotZmmPtDiffSplit_AMCATNLO.AddTextBox("#bf{CMS}",0.08,0.731,0.34,0.877,0);
  if(isNormalized)
    plotZmmPtDiffSplit_AMCATNLO.AddTextBox("#frac{1}{#sigma} #frac{d#sigma}{d#phi_{#eta}*}",0.16,0.48,0.36,0.62,0);
  else
    plotZmmPtDiffSplit_AMCATNLO.AddTextBox("#frac{d#sigma}{d#phi_{#eta}*}",0.16,0.48,0.36,0.62,0);
  plotZmmPtDiffSplit_AMCATNLO.AddTextBox("|#eta| < 2.4, p_{T} > 25 GeV",0.33,0.49,0.63,0.74,0);
  if(nsel==0)
    plotZmmPtDiffSplit_AMCATNLO.AddTextBox("Z/#gamma^{*} #rightarrow #mu^{+}#mu^{-}",0.64,0.55,0.81,0.70,0);
  else if(nsel==1)
    plotZmmPtDiffSplit_AMCATNLO.AddTextBox("Z/#gamma^{*} #rightarrow e^{+}e^{-}",0.64,0.55,0.81,0.70,0);
  else
    plotZmmPtDiffSplit_AMCATNLO.AddTextBox("Z/#gamma^{*} #rightarrow #mu^{+}#mu^{-}, e^{+}e^{-}",0.64,0.5,0.89,0.75,0);
  //plotZmmPtDiffSplit_AMCATNLO.AddTextBox("#bf{|#eta| < 2.4, p_{T} > 25 GeV}",0.35,0.5,0.65,0.75,0);
  plotZmmPtDiffSplit_AMCATNLO.AddTextBox(lumitext,0.69,0.721,0.93,0.867,0);
  
  plotZmmPtDiffSplit_AMCATNLO.SetLogx(1);
  plotZmmPtDiffSplit_AMCATNLO.SetYRange(0.7+eps,1.2 + (1.2-0.7) *(firstextra)/ base );
  plotZmmPtDiffSplit_AMCATNLO.AddLine(0, 1,50, 1,kBlack,1);
  plotZmmPtDiffSplit_AMCATNLO.AddLine(0, 1.1,50, 1.1,kBlack,3);
  plotZmmPtDiffSplit_AMCATNLO.AddLine(0,0.9,50,0.9,kBlack,3);
  
  hZmmPtDiffDummySplit->GetYaxis()->SetNdivisions(405);

  //TH1D *ZPT_RATIO_STAT_SYS_UNCERT_BAND_DATA_POWHEG_COMP =  myratio(hPred2,hData);
  TGraphAsymmErrors *ZPT_RATIO_STAT_SYS_UNCERT_BAND_DATA_POWHEG_COMP =  myratio_graph(hPredTMD,hPredTMD_pdf,hData);
    
  CPlot plotZmmPtDiffSplit_POWHEG("zmmPtSplit","","","PB TMD/Data");
  plotZmmPtDiffSplit_POWHEG.AddHist1D( hZmmPtDiffDummySplit);
  plotZmmPtDiffSplit_POWHEG.AddGraph(ZPT_RATIO_STAT_SYS_UNCERT_BAND_DATA_POWHEG_COMP,"E0",linecolorPowheg,markerstylePowheg,1);
  plotZmmPtDiffSplit_POWHEG.AddHist1D(hZmmPtDiffDummySplit,"E2",TColor::GetColor("#828282"),20,1);
  plotZmmPtDiffSplit_POWHEG.SetLogx(1);
  plotZmmPtDiffSplit_POWHEG.SetYRange(0.7+eps,1.3-eps);
  plotZmmPtDiffSplit_POWHEG.AddLine(0, 1,50, 1,kBlack,1);
  plotZmmPtDiffSplit_POWHEG.AddLine(0, 1.1,50, 1.1,kBlack,3);
  plotZmmPtDiffSplit_POWHEG.AddLine(0,0.9,50,0.9,kBlack,3);

  TH1D *ZPT_RATIO_STAT_SYS_UNCERT_BAND_DATA_FEWZ_COMP =  myratio(hPred3,hData);
  //hZmmPtDiffDummySplit->GetXaxis()->SetLabelSize(30);
  
  CPlot plotZmmPtDiffSplit_FEWZ("zmmPtSplit","",xlabel,"MINLO/Data");
  plotZmmPtDiffSplit_FEWZ.AddHist1D(hZmmPtDiffDummySplit);
  plotZmmPtDiffSplit_FEWZ.AddHist1D(ZPT_RATIO_STAT_SYS_UNCERT_BAND_DATA_FEWZ_COMP,"E0",linecolorFEWZ,1,markerstyleFEWZ);
  plotZmmPtDiffSplit_FEWZ.AddHist1D(hZmmPtDiffDummySplit,"E2",TColor::GetColor("#828282"),20,1);
  plotZmmPtDiffSplit_FEWZ.SetLogx(1);
  plotZmmPtDiffSplit_FEWZ.SetYRange(0.7+eps,1.3-eps);
  plotZmmPtDiffSplit_FEWZ.AddLine(0, 1,50, 1,kBlack,1);
  plotZmmPtDiffSplit_FEWZ.AddLine(0, 1.1,50, 1.1,kBlack,3);
  plotZmmPtDiffSplit_FEWZ.AddLine(0,0.9,50,0.9,kBlack,3);
  
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
