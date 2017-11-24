#include <TFile.h>
#include <TSystem.h>
#include <TString.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TMath.h>
#include <iostream>
#include <fstream>
#include "TUnfold.h"

// nsel = 0 (mm) 1 (ee)
// whichDY = 0 (MG), 1 (aMCNLO), 2 (POWHEG), 3 (aMCNLO Pt)
void helper_function(int nsel=0,int whichDY=3, int rebin=1, TString theHistName = "Pt", TString suffix = "",TString systName3=""){
  TString theInputFolder = "inputs";

  TFile *_file0;
  TFile *_file1;
  TFile *_file2;
  double theXS = 1;
  double theLumi = 35800.0;
  if     (whichDY == 0){
    _file0 = TFile::Open(Form("%s/histoDY%dzll%sRecGen.root",theInputFolder.Data(),whichDY,theHistName.Data()));
    _file1 = TFile::Open("/afs/cern.ch/work/c/ceballos/public/samples/panda/v_004_0/genZpt_LO.root");
    _file2 = TFile::Open(Form("%s/histoDY%dzll%sRecGen.root",theInputFolder.Data(),1,theHistName.Data()));
  }  else if(whichDY == 1){
    _file0 = TFile::Open(Form("%s/histoDY%dzll%sRecGen.root",theInputFolder.Data(),whichDY,theHistName.Data()));
    _file1 = TFile::Open("/afs/cern.ch/work/c/ceballos/public/samples/panda/v_004_0/DYJetsToLL_M-50_NLO.root");
    _file2 = TFile::Open(Form("%s/histoDY%dzll%sRecGen.root",theInputFolder.Data(),2,theHistName.Data()));
    theXS = 2008.4*3;
  }
  else if(whichDY == 2 && nsel == 0){
    _file0 = TFile::Open(Form("%s/histoDY%dzll%sRecGen.root",theInputFolder.Data(),whichDY,theHistName.Data()));
    _file1 = TFile::Open("/afs/cern.ch/work/c/ceballos/public/samples/panda/v_004_0/DYJetsToMM_POWHEG.root");
    _file2 = TFile::Open(Form("%s/histoDY%dzll%sRecGen.root",theInputFolder.Data(),1,theHistName.Data()));
    theXS = 1975.0;
  }
  else if(whichDY == 2 && nsel == 1){
    _file0 = TFile::Open(Form("%s/histoDY%dzll%sRecGen.root",theInputFolder.Data(),whichDY,theHistName.Data()));
    _file1 = TFile::Open("/afs/cern.ch/work/c/ceballos/public/samples/panda/v_004_0/DYJetsToEE_POWHEG.root");
    _file2 = TFile::Open(Form("%s/histoDY%dzll%sRecGen.root",theInputFolder.Data(),1,theHistName.Data()));
    theXS = 1975.0;
  }
  else if(whichDY == 3){
    _file0 = TFile::Open(Form("%s/histoDY%dzll%sRecGen.root",theInputFolder.Data(),whichDY,theHistName.Data()));
    _file1 = TFile::Open("/afs/cern.ch/work/c/ceballos/public/samples/panda/v_004_0/genZpt_NLO.root");
    _file2 = TFile::Open(Form("%s/histoDY%dzll%sRecGen.root",theInputFolder.Data(),2,theHistName.Data()));
  }
  if(!_file0||!_file1||!_file2){printf("file not found");}
TString systName0 = "";
TString systName1 = "";
TString systName2 = "";

if(suffix == "_momres") {systName2 = "_MomRes";}
if(suffix == "_lepeff") {systName2 = "_LepEff";}

TH1D* hDA = (TH1D*)_file0->Get(Form("histo%sRecDA%s_%d%s",theHistName.Data(),systName0.Data(),nsel,systName1.Data()));
TH1D* hEM = (TH1D*)_file0->Get(Form("histo%sRecEM%s_%d%s",theHistName.Data(),systName0.Data(),nsel,systName1.Data()));

if     (suffix == "_qcd") systName0 = "_QCD";
else if(suffix == "_pdf") systName0 = "_PDF";
TH1D* hVV = (TH1D*)_file0->Get(Form("histo%sRecVV%s_%d",theHistName.Data(),systName0.Data(),nsel));

hDA->Add(hEM,-1.0);
hDA->Add(hVV,-1.0);
 TH1D* hDY = (TH1D*)_file0->Get(Form("histo%sRecDY%s_%d%s",theHistName.Data(),systName2.Data(),nsel,systName3.Data()));

  TH2D* Adet = (TH2D*)_file0->Get(Form("histo%sRecGen%s_%d%s",theHistName.Data(),systName2.Data(),nsel,systName3.Data()));
  if(!hDY){printf("%s",Form("histo%sRecDY%s_%d%s",theHistName.Data(),systName2.Data(),nsel,systName3.Data()));}
  if(!Adet){printf("%s",Form("histo%sRecGen%s_%d%s",theHistName.Data(),systName2.Data(),nsel,systName3.Data()));}
  if(!hDA){printf("%s",Form("histo%sRecDA%s_%d%s",theHistName.Data(),systName0.Data(),nsel,systName1.Data()));}
  if(!hEM){printf("%s",Form("histo%sRecEM%s_%d%s",theHistName.Data(),systName0.Data(),nsel,systName1.Data()));}
    if(!hVV){printf("%s",Form("histo%sRecVV%s_%d",theHistName.Data(),systName0.Data(),nsel));}
  if     (suffix == "_sigstat") {
  // add +1sigma to evaluate the statitical uncertainty
     for(int i=0; i<=hDY->GetNbinsX()+1; i++) {
       printf("(%2d) %f ",i,hDY->GetBinContent(i));
       hDY->SetBinContent(i,hDY->GetBinContent(i)+hDY->GetBinError(i));
       printf("%f\n",hDY->GetBinContent(i));
     }
     for(int i=0; i<=Adet->GetNbinsX()+1; i++) {
       for(int j=0; j<=Adet->GetNbinsY()+1; j++) {
	 Adet->SetBinContent(i,j,Adet->GetBinContent(i,j)+Adet->GetBinError(i,j));
       }
     }
   }
 
TString inputFileHist = Form("hDDil%sMM",theHistName.Data());
if(nsel == 1) inputFileHist = Form("hDDil%sEE",theHistName.Data());
TH1D* xini  = (TH1D*)_file1->Get(inputFileHist.Data());

/*if(whichDY != 3){
  TH1D* hDNEvt  = (TH1D*)_file1->Get("hDTotalMCWeight");
  xini->Scale(theXS*theLumi/hDNEvt->GetSumOfWeights());
} else {
  xini->Scale(theLumi);
  }*/
 if(whichDY == 1 || whichDY == 2){
   TH1D* hDNEvt  = (TH1D*)_file1->Get("hDTotalMCWeight");
   xini->Scale(theXS*theLumi/hDNEvt->GetSumOfWeights());
 } else {
   xini->Scale(theLumi);
 }

// add non-reconstructed fiducial events in gen bin 0
for(int i=1; i<=Adet->GetNbinsY(); i++) { // GEN
  double genBin = xini->GetBinContent(i);
  double recBin = 0;
  for(int j=1; j<=Adet->GetNbinsX(); j++) { // RECO
    recBin = recBin + Adet->GetBinContent(j,i);
  }
  if(genBin-recBin <= 0) printf("Bin %d totally efficient (%f)\n",i,genBin-recBin);
  Adet->SetBinContent(0,i,TMath::Max(genBin-recBin,0.0));
}
for(int i=1; i<=Adet->GetNbinsY(); i++) {
 Adet->SetBinContent(i                  ,Adet->GetNbinsY()+1,0.0);
 Adet->SetBinContent(Adet->GetNbinsX()+1,i                  ,0.0);
}

// subtract reconstructed non-fiducial events in data
for(int i=1; i<=Adet->GetNbinsX(); i++) { // RECO
  double allRecBin = hDY->GetBinContent(i);
  double fidRecBin = 0;
  for(int j=1; j<=Adet->GetNbinsY(); j++) { // GEN
    fidRecBin = fidRecBin + Adet->GetBinContent(i,j);
  }
  double gendiff = allRecBin - fidRecBin;
  if(gendiff <= 0 || hDA->GetBinContent(i)-gendiff <= 0) printf("Bin %d totally efficient\n",i);
  //printf("dat(%2d) = %f -> ",i,hDA->GetBinContent(i));
  hDA->SetBinContent(i,TMath::Max(hDA->GetBinContent(i)-gendiff,0.0));
  //printf("%f\n",hDA->GetBinContent(i));
}

//hDA->Sumw2();
//hDY->Sumw2();
//Adet->Sumw2();
//xini->Sumw2();
hDA->Rebin(rebin);
hDY->Rebin(rebin);
Adet->Rebin2D(rebin,rebin);
xini->Rebin(rebin);

printf("data: %f\n",hDA->GetSumOfWeights());
printf("  DY: %f\n",hDY->GetSumOfWeights());
printf("  2D: %f\n",Adet->GetSumOfWeights());
printf(" gen: %f\n",xini->GetSumOfWeights());

//Do Unfolding
TUnfold::ERegMode regMode =TUnfold::kRegModeCurvature;
TUnfold::EConstraint constraintMode=TUnfold::kEConstraintNone;
TUnfoldDensity::EDensityMode densityFlags=TUnfoldDensity::kDensityModeBinWidth;

TUnfoldDensity unfold(Adet,TUnfold::kHistMapOutputVert, regMode, constraintMode ,densityFlags);
unfold.SetInput(hDA);
  

int regParam_=-3;
int iBest=regParam_;
if (regParam_ <0)
{
  Int_t nScan=30;
  TSpline *logTauX,*logTauY;
  TGraph *lCurve;
  // this method scans the parameter tau and finds the kink in the L curve
  //   // finally, the unfolding is done for the best choice of tau
  iBest=unfold.ScanLcurve(nScan,0.,0.,&lCurve,&logTauX,&logTauY);
}

//TH1D *unfoldedDistribution = (TH1D*)hDA->Clone();
//unfoldedDistribution->Reset();
//unfold.GetOutput(unfoldedDistribution);
 TH1D *unfoldedDistribution = (TH1D*)unfold.GetOutput("unfold");

// TH1D *x = (TH1D*)(unfold.GetOutput("x","myVariable",0,0));
// TH2D *rhoij=unfold.GetRhoIJ("correlation","myVariable");
 unfoldedDistribution->Scale(1,"width");
 xini->Scale(1,"width");

/*unfoldedDistribution->Draw();
 xini->Draw("same");
 xini->SetLineColor(kRed);*/
//printf("%f %f\n",unfoldedDistribution->GetSumOfWeights(),xini->GetSumOfWeights());



 char output[100];
 sprintf(output,"outputC/histoUnfolding%s_nsel%d_dy%d_rebin%d%s%s.root",theHistName.Data(),nsel,whichDY,rebin,suffix.Data(),systName3.Data());

 TFile* outFilePlots = new TFile(output,"recreate");
 outFilePlots->cd();
 unfoldedDistribution->Write();
 xini->Write();

outFilePlots->Close();
 _file0->Close();
 _file1->Close();
 _file2->Close();
}
//histname="Pt","Rap","PtRap0"...4
void testUnfoldC(TString theHistName = "Pt", TString suffix = "",int rebin=1){
  int num;
  for (int i=0;i<=1;i++){
    for (int j=0;j<=3;j++){
      
      if(suffix=="_lepeff"||suffix=="_momres"){
	num=144;
	if (suffix=="_momres"){num=4;}
	for(int k=1;k<=num;k++){
	  TString sys=Form("_%d",k);
	  helper_function(i,j,rebin,theHistName.Data(),suffix.Data(),sys.Data());
	}
      }
      else{
	helper_function(i,j,rebin,theHistName.Data(),suffix.Data());
      }
    }
  }
}
