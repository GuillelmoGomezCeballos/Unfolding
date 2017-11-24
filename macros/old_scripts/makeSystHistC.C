
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
  gStyle->SetOptStat(0);
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
  histo->GetXaxis()->SetTitleSize  (0.035);
  histo->GetXaxis()->SetTitleOffset( 1.40);

  histo->GetYaxis()->SetTitle(ytitle);
  histo->GetYaxis()->SetLabelFont  (   42);
  histo->GetYaxis()->SetLabelOffset(0.015);
  histo->GetYaxis()->SetLabelSize  (0.050);
  histo->GetYaxis()->SetNdivisions (  505);
  histo->GetYaxis()->SetTitleFont  (   42);
  histo->GetYaxis()->SetTitleOffset(  1.3);
  histo->GetYaxis()->SetTitleSize  (0.035);
  histo->SetLineColor(COLOR);
  histo->SetMarkerStyle(kFullDotLarge);
  histo->SetLineStyle(style);
}
void makeSystHistC(int nsel = 0, int whichDY = 3, TString theHistName = "Pt"){
  TString theOutputName = "outputC";
/*
  const int nBinPt = 57; Float_t xbinsPt[nBinPt+1] = {  0,  1,  2,  3,  4,  5,  6,  7,  8,  9,
                                                       10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
                                                       20, 21, 22, 23, 24, 25, 26, 27, 28, 29,
                                                       30, 31, 32, 33, 34, 35, 36, 37, 38, 39,
                                                       40, 50, 60, 70, 80, 90,100,125,150,175, 
						      200,250,300,350,400,450,500,1000};

  const int nBinPtRap0 = 36; Float_t xbinsPtRap0[nBinPtRap0+1] = {  0,  1,  2,  3,  4,  5,  6,  7,  8,  9,
                                                		   10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
                                                		   20, 25, 30, 35, 40, 50, 60, 70, 80, 90,
                                                		  100,150,200,300,400,500,1000};
  const int nBinPtRap1 = 36; Float_t xbinsPtRap1[nBinPtRap1+1] = {  0,  1,  2,  3,  4,  5,  6,  7,  8,  9,
                                                		   10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
                                                		   20, 25, 30, 35, 40, 50, 60, 70, 80, 90,
                                                		  100,150,200,300,400,500,1000};
  const int nBinPtRap2 = 36; Float_t xbinsPtRap2[nBinPtRap2+1] = {  0,  1,  2,  3,  4,  5,  6,  7,  8,  9,
                                                		   10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
                                                		   20, 25, 30, 35, 40, 50, 60, 70, 80, 90,
                                                		  100,150,200,300,400,500,1000};
  const int nBinPtRap3 = 36; Float_t xbinsPtRap3[nBinPtRap3+1] = {  0,  1,  2,  3,  4,  5,  6,  7,  8,  9,
                                                		   10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
                                                		   20, 25, 30, 35, 40, 50, 60, 70, 80, 90,
                                                		  100,150,200,300,400,500,1000};
  const int nBinPtRap4 = 36; Float_t xbinsPtRap4[nBinPtRap4+1] = {  0,  1,  2,  3,  4,  5,  6,  7,  8,  9,
                                                                  10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
                                                                  20, 25, 30, 35, 40, 50, 60, 70, 80, 90,
                                                                 100,150,200,300,400,500,1000};
*/
  const int nBinPt     = 37; Float_t xbinsPt[nBinPt+1]         = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,16,18,20,22,25,28,32,37,43,52,65,85,120,160,190,220,250,300,350,400,450,500,1000};

  const int nBinPtRap0 = 37; Float_t xbinsPtRap0[nBinPtRap0+1] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,16,18,20,22,25,28,32,37,43,52,65,85,120,160,190,220,250,300,350,400,450,500,1000};
  const int nBinPtRap1 = 37; Float_t xbinsPtRap1[nBinPtRap1+1] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,16,18,20,22,25,28,32,37,43,52,65,85,120,160,190,220,250,300,350,400,450,500,1000};
  const int nBinPtRap2 = 37; Float_t xbinsPtRap2[nBinPtRap2+1] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,16,18,20,22,25,28,32,37,43,52,65,85,120,160,190,220,250,300,350,400,450,500,1000};
  const int nBinPtRap3 = 37; Float_t xbinsPtRap3[nBinPtRap3+1] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,16,18,20,22,25,28,32,37,43,52,65,85,120,160,190,220,250,300,350,400,450,500,1000};
  const int nBinPtRap4 = 37; Float_t xbinsPtRap4[nBinPtRap4+1] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,16,18,20,22,25,28,32,37,43,52,65,85,120,160,190,220,250,300,350,400,450,500,1000};

  const int nBinPt2 = 50; Float_t xbinsPt2[nBinPt2+1]; for(int i=0; i<=nBinPt2;i++) xbinsPt2[i] = i * 1.0;

  const int nBinRap = 24; Float_t xbinsRap[nBinRap+1]; for(int i=0; i<=nBinRap;i++) xbinsRap[i] = i * 0.1;
  int lep=144;
  int mom=4;
  int num=mom+lep+6;//6=pdf+qcd+lumi+sigstat+stat+total
  int version = 1; int alternative = 0;
  if     (whichDY == 0) { version = 0; alternative = 1;}
  else if(whichDY == 2) { version = 2; alternative = 1;}
  else if(whichDY == 3) { version = 3; alternative = 0;}
  
  TH1D* histoSyst[num];
  if       (theHistName == "Pt"){
    for(int i=0;i<num;i++){
      histoSyst[i] = new TH1D(Form("histoSyst_%d",i),  Form("histoSyst_%d",i),  nBinPt, xbinsPt);
    }
  } 
  else if(theHistName == "Pt2"){

    for(int i=0;i<num;i++){
      histoSyst[i] = new TH1D(Form("histoSyst_%d",i),  Form("histoSyst_%d",i),  nBinPt2, xbinsPt2);
    }
  } 
  else if(theHistName == "Rap"){
    for(int i=0;i<num;i++){
      histoSyst[i] = new TH1D(Form("histoSyst_%d",i),  Form("histoSyst_%d",i),  nBinRap, xbinsRap);
    }
  } 
  else if(theHistName == "PtRap0"){
    for(int i=0;i<num;i++){
      histoSyst[i] = new TH1D(Form("histoSyst_%d",i),  Form("histoSyst_%d",i),  nBinPtRap0, xbinsPtRap0);
  
    }
  } 
  else if(theHistName == "PtRap1"){
    for(int i=0;i<num;i++){
       histoSyst[i] = new TH1D(Form("histoSyst_%d",i),  Form("histoSyst_%d",i),  nBinPtRap1, xbinsPtRap1);

    }
  } 
  else if(theHistName == "PtRap2"){
    for(int i=0;i<num;i++){
      histoSyst[i] = new TH1D(Form("histoSyst_%d",i),  Form("histoSyst_%d",i),  nBinPtRap2, xbinsPtRap2);
    
    }
  } 
  else if(theHistName == "PtRap3"){
    for(int i=0;i<num;i++){
      histoSyst[i] = new TH1D(Form("histoSyst_%d",i),  Form("histoSyst_%d",i),  nBinPtRap3, xbinsPtRap3);
    
    }
  } 
  else if(theHistName == "PtRap4"){
    for(int i=0;i<num;i++){

    histoSyst[i] = new TH1D(Form("histoSyst_%d",i),  Form("histoSyst_%d",i),  nBinPtRap4, xbinsPtRap4);
    }
  } 
  else {
    printf("Wrong option!\n");
    return;
  }

  //TStyle *MITStyle = new TStyle("MIT-Style","MIT-Style");
  //MITStyle->SetOptStat(0);
  //gStyle = MITStyle;

  TFile *_file0 = TFile::Open(Form("%s/histoUnfolding%s_nsel%d_dy%d_rebin1.root",theOutputName.Data(),theHistName.Data(),nsel,version)); // default NLO/LO
  TFile *_file1 = TFile::Open(Form("%s/histoUnfolding%s_nsel%d_dy%d_rebin1.root",theOutputName.Data(),theHistName.Data(),nsel,alternative)); // alternative LO/NLO
  TFile *_file2 = TFile::Open(Form("%s/histoUnfolding%s_nsel%d_dy%d_rebin1_sigstat.root",theOutputName.Data(),theHistName.Data(),nsel,version)); // MC stat 
  TFile *_file3 = TFile::Open(Form("%s/histoUnfolding%s_nsel%d_dy%d_rebin1_pdf.root",theOutputName.Data(),theHistName.Data(),nsel,version)); // PDF bkg
  TFile *_file4 = TFile::Open(Form("%s/histoUnfolding%s_nsel%d_dy%d_rebin1_qcd.root",theOutputName.Data(),theHistName.Data(),nsel,version)); // QCD bkg.
  TFile *_file_lepeff[lep];
  TFile *_file_momres[mom];
  for(int i=0;i<lep;i++){
    _file_lepeff[i]= TFile::Open(Form("%s/histoUnfolding%s_nsel%d_dy%d_rebin1_lepeff_%d.root",theOutputName.Data(),theHistName.Data(),nsel,version,i+1)); 
  }
  for(int i=0;i<mom;i++){
    _file_momres[i]= TFile::Open(Form("%s/histoUnfolding%s_nsel%d_dy%d_rebin1_momres_%d.root",theOutputName.Data(),theHistName.Data(),nsel,version,i+1)); 
 
  }

  TH1D* histDef = (TH1D*)_file0->Get(Form("unfold"));
  TH1D* histAlt[4+lep+mom];
  histAlt[0] = (TH1D*)_file1->Get(Form("unfold"));
  histAlt[1] = (TH1D*)_file2->Get(Form("unfold"));
  histAlt[2] = (TH1D*)_file3->Get(Form("unfold"));
  histAlt[3] = (TH1D*)_file4->Get(Form("unfold"));
  for(int i=4;i<lep+4;i++){
    histAlt[i]=(TH1D*)_file_lepeff[i-4]->Get(Form("unfold"));
  }
  for(int i=4+lep;i<mom+4+lep;i++){
    histAlt[i]=(TH1D*)_file_momres[i-4-lep]->Get(Form("unfold"));

  }

  double total;
  double total2;
  double lepval,momval;
  TString label="MM";
  if (nsel==1){label="EE";}
  TH1D* histPred = (TH1D*)_file0->Get(Form("hDDil%s%s",theHistName.Data(),label.Data()));
  double systVal[4+lep+mom+2];
  double systTotalVal;

  for(int i=1; i<=histDef->GetNbinsX(); i++){
    for(int j=0; j<lep+mom+4; j++){
      systVal[j] = 100.*TMath::Abs(histDef->GetBinContent(i)-histAlt[j]->GetBinContent(i))/histDef->GetBinContent(i);

    }
    if      (histDef->GetBinCenter(i)+histDef->GetBinWidth(i)/2<=45  && systVal[0] > 1.0) systVal[0] = 1.0;
    else if (histDef->GetBinCenter(i)+histDef->GetBinWidth(i)/2<=105 && systVal[0] > 1.0) systVal[0] = 0.5;
    if(systVal[0] > 110.0) systVal[0] = 50.0;
    systVal[lep+mom+4] = 100.*histDef->GetBinError(i)/histDef->GetBinContent(i); // stat
    systVal[lep+mom+5] = 100.*0.025;//lumi
    systTotalval=0;
    for(int j=0; j<lep+mom+6; j++){
      systTotalval=systTotalval+systVal[j]*systVal[j];
    }
    histoSyst[0]->SetBinContent(i,TMath::Sqrt(systTotalval));
    //printf("%7.3f\n",histoSyst[0]->GetBinContent(i));
    histoSyst[1]->SetBinContent(i,systVal[0]); // unfolding
    lepval=0;
    for(int j=4;j<4+lep;j++){
      lepval+=systVal[j]*systVal[j];
    }
    momval=0;
    for(int j=4+lep;j<4+lep+mom;j++){
      momval+=systVal[j]*systVal[j];
    }                                                                
    histoSyst[2]->SetBinContent(i,TMath::Sqrt(momval)); // momres                                                                                                 
    histoSyst[3]->SetBinContent(i,TMath::Sqrt(systVal[2]*systVal[2]+systVal[3]*systVal[3])); // Bkg.
    histoSyst[4]->SetBinContent(i,TMath::Sqrt(lepval)); // LepEff                                                                                                  
    histoSyst[5]->SetBinContent(i,systVal[1]); // mc stat                                                  
    histoSyst[6]->SetBinContent(i,systVal[lep+mom+4]); // stat                                                                                                   
    histoSyst[7]->SetBinContent(i,systVal[lep+mom+5]); // lumi  
    total=0;
    for(int j=1;j<=7;j++){
      total+=histoSyst[j]->GetBinContent(i)*histoSyst[j]->GetBinContent(i);      
    }
    //printf("%7.3f %7.3f %7.3f\n",TMath::Sqrt(systTotalval),TMath::Sqrt(total),TMath::Sqrt(total2));
    printf("%7.3f\n",TMath::Sqrt(total));                                                                 
    histoSyst[0]->SetBinContent(i,TMath::Sqrt(total));
    
  }

  TString XName = "Z p_{T} [GeV]";
  if     (theHistName == "Rap") XName = "|y^{Z}|";
  else if(theHistName == "Pt2") XName = "Z p_{T}^{2} [GeV^{2}]";
  atributes(histoSyst[0],XName.Data(),1,"Uncertainty (%)", 1);
  atributes(histoSyst[1],XName.Data(),2,"Uncertainty (%)", 1);
  atributes(histoSyst[2],XName.Data(),4,"Uncertainty (%)", 1);
  atributes(histoSyst[3],XName.Data(),5,"Uncertainty (%)", 1);
  atributes(histoSyst[4],XName.Data(),6,"Uncertainty (%)", 1);
  atributes(histoSyst[5],XName.Data(),7,"Uncertainty (%)", 1);
  atributes(histoSyst[6],XName.Data(),8,"Uncertainty (%)", 1);
  atributes(histoSyst[7],XName.Data(),9,"Uncertainty (%)", 1);



  TCanvas* c1 = new TCanvas("c1", "c1",5,5,500,500);
  c1->cd();
  histoSyst[0]->SetLineColor(1);
  histoSyst[0]->SetMinimum(0.0);
  histoSyst[0]->Draw("hist");
  gStyle->SetOptStat(0);
  for(int i=1;i<=7;i++){
    histoSyst[i]->Draw("same,hist");
  }


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
 TLegend* leg;
 leg= new TLegend(0.15,0.60,0.45,0.85);                                                    
 if(nsel==1 && theHistName=="Rap"){
   leg = new TLegend(0.15,0.40,0.45,0.65);
 }
 leg ->SetFillStyle(0);
 leg ->SetFillColor(kWhite);
 leg ->SetBorderSize(0);
 leg->SetTextSize(0.035);                                                                         
 leg->AddEntry(histoSyst[0],"Total Unc.","l");
 leg->AddEntry(histoSyst[1],"Unfolding","l");
 leg->AddEntry(histoSyst[2],"Mom. Res.","l");
 leg->AddEntry(histoSyst[3],"Bkg.","l");
 leg->AddEntry(histoSyst[4],"Identification","l");
 leg->AddEntry(histoSyst[5],"MC Stat.","l");
 leg->AddEntry(histoSyst[6],"Statistical","l");
 leg->AddEntry(histoSyst[7],"Luminosity","l");
 leg->Draw();

 TString myOutputFile = Form("sys_plotsC/histoUnfoldingSyst%s_nsel%d_dy%d.pdf",theHistName.Data(),nsel,whichDY);
 c1->SaveAs(myOutputFile.Data());

 for(int i=1; i<=histPred->GetNbinsX(); i++){
   histPred->SetBinError(i,histDef->GetBinContent(i)*histoSyst[8]->GetBinContent(i)/100.);
 }

 char output[200];
 sprintf(output,"sys_plotsC/histoUnfoldingSyst%s_nsel%d_dy%d_rebin1_default.root",theHistName.Data(),nsel,whichDY); 
 TFile* outFilePlots = new TFile(output,"recreate");
 outFilePlots->cd();
 c1->Write();
 histDef->Write();
 histPred->Write();
 histoSyst[0]->Write();
 outFilePlots->Close();

}
