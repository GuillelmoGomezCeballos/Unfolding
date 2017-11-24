#include <TROOT.h>
#include <TFile.h>
#include <TTree.h>
#include <TSystem.h>
#include <TString.h>
#include <TLegend.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TMath.h>
#include <iostream>
#include <fstream>
#include "TLorentzVector.h"
TLegend *legend=new TLegend(0.65,0.55,0.9,0.75);
//int me, muon==0, electron==1
//#include "Unfolding/macros/pandaFlat.C"
void helper_function(int rebinX=1,int rebinY=1,int me=0){
  int count;
  double mean;
  double current;
  double expect;
 
  TFile* f;
  /*  if (finner==true){
    f= TFile::Open("inputs_finerbinning/histozllPtRecGen_LO.root");
  }
  else{
    f= TFile::Open("inputs/histozllPtRecGen_LO.root");
    }*/

  f= TFile::Open("inputs/histoDY0zllPtRecGen.root");

  TH2D* h1=(TH2D*)f->Get(Form("histoPtRecGen_%d",me));
  h1->Rebin2D(rebinX,rebinY);
  int nBinY=h1->GetNbinsY();
  int nBinX=h1->GetNbinsX();
  double bin_width;
  TH1D* final=h1->ProjectionX("px",1,1);
  
  for(int i=1;i<=nBinY;i++){

    TH1D* px=h1->ProjectionX("px",i,i);
    expect= px->Integral();
    final->SetBinContent(i,100*px->GetBinContent(i)/expect);
    //printf("%f\n",sigma);
    px->Reset();px->Clear();

  }

  /*  if (rebin==1){final->SetLineColor(1);
    if(finner==false){final->SetLineColor(6);}


  }
  else if(rebin==2){final->SetLineColor(2);}
  else if(rebin==5){final->SetLineColor(3);}
  else{final->SetLineColor(4);}*/
  final->SetLineColor(me+1);
  final->Draw("SAME");
  /*  if (rebin==10){legend->AddEntry(final,"Bin width = 1 GeV");}
  else if(finner==false){legend->AddEntry(final,"default variable binning");}
  else{legend->AddEntry(final,Form("Bin width = 0.%d GeV",rebin));}*/
  if (me==0){legend->AddEntry(final,"Muon");}
  else{legend->AddEntry(final,"Electron");}
  final->GetYaxis()->SetTitle("Purity (%)");
  final->GetXaxis()->SetTitle("Generated P_{T} (GeV)");
}
void purity(){
  helper_function(2,1,1);
  helper_function(2,1,0);
  /*  helper_function(true,10);
  helper_function(true,1);
  helper_function(true,5);
  helper_function(true,2);*/
  legend->Draw();
  gStyle->SetOptStat(0);
}
