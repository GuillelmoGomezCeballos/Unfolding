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
void helper_function(int nsel=0,int whichDY=0, int rebin=1, TString theHistName = "Pt", TString suffix = "", int suffixStat = -1){
  printf("TORUN: nsel = %d whichDY = %d rebin = %d theHistName = %s  suffix = %s, suffixStat = %d\n",nsel,whichDY,rebin,theHistName.Data(),suffix.Data(),suffixStat);
  TString theInputFolder = "inputsLL";
  TString theTheorySubFolder = "v_001_0";

  TFile *_file0;
  TFile *_file1;
  TFile *_file2;
  double theXS = 1.0;
  double theLumi = 35800.0;
  if     (whichDY == 0){
    _file0 = TFile::Open(Form("%s/histoDY%dzll%sRecGen_period3.root",theInputFolder.Data(),whichDY,theHistName.Data()));
    _file1 = TFile::Open(Form("/afs/cern.ch/work/c/ceballos/public/samples/panda/%s/genZpt_LO.root",theTheorySubFolder.Data()));
    _file2 = TFile::Open(Form("%s/histoDY%dzll%sRecGen_period3.root",theInputFolder.Data(),1,theHistName.Data()));
  }
  else if(whichDY == 1){
    _file0 = TFile::Open(Form("%s/histoDY%dzll%sRecGen_period3.root",theInputFolder.Data(),whichDY,theHistName.Data()));
    _file1 = TFile::Open(Form("/afs/cern.ch/work/c/ceballos/public/samples/panda/%s/DYJetsToLL_M-50_NLO.root",theTheorySubFolder.Data()));
    _file2 = TFile::Open(Form("%s/histoDY%dzll%sRecGen_period3.root",theInputFolder.Data(),2,theHistName.Data()));
    theXS = 2075.14*3;
  }
  else if(whichDY == 2 && nsel == 0){
    _file0 = TFile::Open(Form("%s/histoDY%dzll%sRecGen_period3.root",theInputFolder.Data(),whichDY,theHistName.Data()));
    _file1 = TFile::Open(Form("/afs/cern.ch/work/c/ceballos/public/samples/panda/%s/DYJetsToMM_POWHEG.root",theTheorySubFolder.Data()));
    _file2 = TFile::Open(Form("%s/histoDY%dzll%sRecGen_period3.root",theInputFolder.Data(),1,theHistName.Data()));
    theXS = 1975.0*2075.14/2008.4;
  }
  else if(whichDY == 2 && nsel == 1){
    _file0 = TFile::Open(Form("%s/histoDY%dzll%sRecGen_period3.root",theInputFolder.Data(),whichDY,theHistName.Data()));
    _file1 = TFile::Open(Form("/afs/cern.ch/work/c/ceballos/public/samples/panda/%s/DYJetsToEE_POWHEG.root",theTheorySubFolder.Data()));
    _file2 = TFile::Open(Form("%s/histoDY%dzll%sRecGen_period3.root",theInputFolder.Data(),1,theHistName.Data()));
    theXS = 1975.0*2075.14/2008.4;
  }
  else if(whichDY == 3){
    _file0 = TFile::Open(Form("%s/histoDY%dzll%sRecGen_period3.root",theInputFolder.Data(),whichDY,theHistName.Data()));
    _file1 = TFile::Open(Form("/afs/cern.ch/work/c/ceballos/public/samples/panda/%s/genZpt_NLO.root",theTheorySubFolder.Data()));
    _file2 = TFile::Open(Form("%s/histoDY%dzll%sRecGen_period3.root",theInputFolder.Data(),3,theHistName.Data()));
  }

if((suffix == "_lepeff" || suffix == "_sigstat") && suffixStat < 0) {printf("Wrong suffixStat: %d\n",suffixStat); return;}

TString systName0 = "";
TString systName1 = "";
TString systName2 = "";
TString systName3 = "";
if(suffix == "_momres0"){systName2 = "_MomRes";systName3 = "_0";if(nsel == 1) {systName0 = "_MomRes";systName1 = "_0";}}
if(suffix == "_momres1"){systName2 = "_MomRes";systName3 = "_1";if(nsel == 1) {systName0 = "_MomRes";systName1 = "_1";}}
if(suffix == "_momres2"){systName2 = "_MomRes";systName3 = "_2";if(nsel == 1) {systName0 = "_MomRes";systName1 = "_2";}}
if(suffix == "_momres3"){systName2 = "_MomRes";systName3 = "_3";if(nsel == 1) {systName0 = "_MomRes";systName1 = "_3";}}
if(suffix == "_momres4"){systName2 = "_MomRes";systName3 = "_4";if(nsel == 1) {systName0 = "_MomRes";systName1 = "_4";}}
if(suffix == "_lepeff") {systName2 = "_LepEff";systName3 = Form("_%d",suffixStat); suffix = Form("_lepeff%d",suffixStat);}
if(suffix == "_receff0") {systName2 = "_RecEff";systName3 = "_0";}
if(suffix == "_receff1") {systName2 = "_RecEff";systName3 = "_1";}
if(suffix == "_receff2") {systName2 = "_RecEff";systName3 = "_2";}
if(suffix == "_receff3") {systName2 = "_RecEff";systName3 = "_3";}
if(suffix == "_momreslepeff") {systName2 = "_MomRes";systName3 = "_3";if(nsel == 1) {systName2 = "_MomRes";systName3 = "_2";systName0 = "_MomRes";systName1 = "_2";}}
cout << Form("histoLL%sRecDA%s_%d%s",theHistName.Data(),systName0.Data(),nsel,systName1.Data()) << endl;
TH1D* hDA = (TH1D*)_file0->Get(Form("histoLL%sRecDA%s_%d%s",theHistName.Data(),systName0.Data(),nsel,systName1.Data()));
TH1D* hEM = (TH1D*)_file0->Get(Form("histoLL%sRecEM%s_%d%s",theHistName.Data(),systName0.Data(),nsel,systName1.Data()));

if     (suffix == "_qcd") systName0 = "_QCD";
else if(suffix == "_pdf") systName0 = "_PDF";
TH1D* hVV = (TH1D*)_file0->Get(Form("histoLL%sRecVV%s_%d%s",theHistName.Data(),systName0.Data(),nsel,systName1.Data()));

hDA->Add(hEM,-1.0);
hDA->Add(hVV,-1.0);
for(int i=0; i<=hDA->GetNbinsX()+1; i++) {
  if(hDA->GetBinContent(i) < 0) hDA->SetBinContent(i,0.0);
}

TH1D* hDY  = (TH1D*)_file0->Get(Form("histoLL%sRecDY%s_%d%s",theHistName.Data(),systName2.Data(),nsel,systName3.Data()));
TH2D* Adet = (TH2D*)_file0->Get(Form("histoLL%sRecGen%s_%d%s",theHistName.Data(),systName2.Data(),nsel,systName3.Data()));

if     (suffix == "_sigstat") {
  suffix = Form("_sigstat%d",suffixStat);
  // add +1sigma to evaluate the statitical uncertainty
  for(int i=0; i<=hDY->GetNbinsX()+1; i++) {
    //printf("(%2d) %f ",i,hDY->GetBinContent(i));
    if(i == suffixStat) hDY->SetBinContent(i,hDY->GetBinContent(i)+hDY->GetBinError(i));
    //printf("%f\n",hDY->GetBinContent(i));
  }
  for(int i=0; i<=Adet->GetNbinsX()+1; i++) {
    for(int j=0; j<=Adet->GetNbinsY()+1; j++) {
      if(i == suffixStat) Adet->SetBinContent(i,j,Adet->GetBinContent(i,j)+Adet->GetBinError(i,j));
    }
  }
}

if(suffix == "_momreslepeff") {
  systName2 = "_LepEff";systName3 = Form("_%d",3);
  TH1D* hDYSyst  = (TH1D*)_file0->Get(Form("histoLL%sRecDY%s_%d%s",theHistName.Data(),systName2.Data(),nsel,systName3.Data()));
  TH2D* AdetSyst = (TH2D*)_file0->Get(Form("histoLL%sRecGen%s_%d%s",theHistName.Data(),systName2.Data(),nsel,systName3.Data()));

  systName2 = "";systName3 = "";
  TH1D* hDYDef  = (TH1D*)_file0->Get(Form("histoLL%sRecDY%s_%d%s",theHistName.Data(),systName2.Data(),nsel,systName3.Data()));
  TH2D* AdetDef = (TH2D*)_file0->Get(Form("histoLL%sRecGen%s_%d%s",theHistName.Data(),systName2.Data(),nsel,systName3.Data()));

  double diff;
  for(int i=0; i<=hDY->GetNbinsX()+1; i++) {
    diff = hDYSyst->GetBinContent(i) - hDYDef->GetBinContent(i);
    hDY->SetBinContent(i,hDY->GetBinContent(i)+diff);
  }
  for(int i=0; i<=Adet->GetNbinsX()+1; i++) {
    for(int j=0; j<=Adet->GetNbinsY()+1; j++) {
      diff = AdetSyst->GetBinContent(i,j) - AdetDef->GetBinContent(i,j);
      Adet->SetBinContent(i,j,Adet->GetBinContent(i,j)+diff);
    }
  }
}

TString inputFileHist = Form("hDDil%sMM",theHistName.Data());
if(nsel == 1) inputFileHist = Form("hDDil%sEE",theHistName.Data());
TH1D* xini  = (TH1D*)_file1->Get(inputFileHist.Data());

TString inputFilePDFHist = Form("hDDil%sMM_PDF",theHistName.Data());
if(nsel == 1) inputFilePDFHist = Form("hDDil%sEE_PDF",theHistName.Data());
TH1D* hDDilPDF = (TH1D*)_file1->Get(inputFilePDFHist.Data());

TString inputFileQCDHist = Form("hDDil%sMM_QCD",theHistName.Data());
if(nsel == 1) inputFileQCDHist = Form("hDDil%sEE_QCD",theHistName.Data());
TH1D* hDDilQCD = (TH1D*)_file1->Get(inputFileQCDHist.Data());

if(whichDY == 1 || whichDY == 2){
  TH1D* hDNEvt  = (TH1D*)_file1->Get("hDTotalMCWeight");
  xini    ->Scale(theXS*theLumi/hDNEvt->GetSumOfWeights());
  hDDilPDF->Scale(theXS*theLumi/hDNEvt->GetSumOfWeights());
  hDDilQCD->Scale(theXS*theLumi/hDNEvt->GetSumOfWeights());
} else {
  xini    ->Scale(theLumi);
  hDDilPDF->Scale(theLumi);
  hDDilQCD->Scale(theLumi);
}
xini    ->Scale(2.0);
hDDilPDF->Scale(2.0);
hDDilQCD->Scale(2.0);

// add non-reconstructed fiducial events in gen bin 0
for(int i=1; i<=Adet->GetNbinsY(); i++) { // GEN
  double genBin = xini->GetBinContent(i);
  double recBin = 0;
  for(int j=1; j<=Adet->GetNbinsX(); j++) { // RECO
    recBin = recBin + Adet->GetBinContent(j,i);
    //if(i==1) printf("%d (%f/%f)\n",j,Adet->GetBinContent(j,i),recBin);
  }
  if(genBin-recBin <= 0) printf("Bin %d totally efficient (%f/%f/%f)\n",i,genBin,recBin,genBin-recBin);
  //if(i==1) printf("Bin %d totally efficient (%f/%f/%f)\n",i,genBin,recBin,genBin-recBin);
  Adet->SetBinContent(0,i,TMath::Max(genBin-recBin,0.0));
}
for(int i=1; i<=Adet->GetNbinsY(); i++) {
 //Adet->SetBinContent(i                  ,Adet->GetNbinsY()+1,TMath::Max(Adet->GetBinContent(i                  ,Adet->GetNbinsY()+1),0.0));
 //Adet->SetBinContent(Adet->GetNbinsX()+1,i                  ,TMath::Max(Adet->GetBinContent(Adet->GetNbinsX()+1,i                  ),0.0));
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
  if(gendiff <= 0 || hDA->GetBinContent(i)-gendiff <= 0) printf("Non-fiducial: Bin %d totally efficient %f %f\n",i,gendiff,hDA->GetBinContent(i)-gendiff);
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
hDDilPDF->Rebin(rebin);
hDDilQCD->Rebin(rebin);

printf("data: %f\n",hDA->GetSumOfWeights());
printf("  DY: %f\n",hDY->GetSumOfWeights());
printf("  2D: %f\n",Adet->GetSumOfWeights());
printf(" gen: %f\n",xini->GetSumOfWeights());

//Do Unfolding
TUnfold::ERegMode regMode =TUnfold::kRegModeCurvature;
//TUnfold::ERegMode regMode =TUnfold::kRegModeNone;
// preserve the area (constrain)
//TUnfold::EConstraint constraintMode=TUnfold::kEConstraintArea;
TUnfold::EConstraint constraintMode=TUnfold::kEConstraintNone;
TUnfoldDensity::EDensityMode densityFlags=TUnfoldDensity::kDensityModeBinWidth;

TUnfoldDensity unfold(Adet,TUnfold::kHistMapOutputVert, regMode, constraintMode ,densityFlags);
unfold.SetInput(hDA);
//Double_t tau=1.E-4;
//Double_t biasScale=0.0;
//unfold.DoUnfold(tau,hDA,biasScale);

int regParam_=-3;
int iBest=regParam_;
if (regParam_ <0)
{
  Int_t nScan=20;
  if(suffix == "_testscan") nScan=50;
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

{
  unfoldedDistribution->Scale(0.5);
  xini    ->Scale(0.5);
  hDDilPDF->Scale(0.5);
  hDDilQCD->Scale(0.5);
}

unfoldedDistribution->Scale(1,"width");
xini->Scale(1,"width");
hDDilPDF->Scale(1,"width");
hDDilQCD->Scale(1,"width");

for(int i=0; i<=unfoldedDistribution->GetNbinsX()+1; i++) {
  if(unfoldedDistribution->GetBinContent(i) < 0) unfoldedDistribution->SetBinContent(i,0.00001);
}

unfoldedDistribution->Draw();
xini->Draw("same");
xini->SetLineColor(kRed);
printf("RESULTS: %f %f\n",unfoldedDistribution->Integral("width"),xini->Integral("width"));

TString theOutputFolder = Form("outputsLL%s_nsel%d/dy%d",theHistName.Data(),nsel,whichDY);

char CommandToExec[300];
sprintf(CommandToExec,"mkdir -p %s",theOutputFolder.Data());
gSystem->Exec(CommandToExec);  
char output[100];
sprintf(output,"%s/histoUnfolding%s_nsel%d_dy%d_rebin%d%s.root",theOutputFolder.Data(),theHistName.Data(),nsel,whichDY,rebin,suffix.Data());

TFile* outFilePlots = new TFile(output,"recreate");
outFilePlots->cd();
unfoldedDistribution->Write();
if(suffix == "_default"){
  xini->Write();
  hDDilPDF->Write();
  hDDilQCD->Write();
}
outFilePlots->Close();

}

void testUnfoldLL(TString theHistName = "Pt", TString suffix = "", int suffixLepStat = -1, int rebin=1){
  for (int i=0;i<=1;i++){
    for (int j=2;j<=3;j++){
  //for (int i=0;i<=0;i++){
  //  for (int j=0;j<=0;j++){
      helper_function(i,j,rebin,theHistName.Data(),suffix.Data(),suffixLepStat);

    }
  }
}
