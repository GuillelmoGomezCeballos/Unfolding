#include <TFile.h>
#include <TSystem.h>
#include <TString.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TMath.h>
#include <iostream>
#include <fstream>
#include "TUnfold.h"

void findUniformYields(int nsel = 0,int whichDY = 1, TString theHistName = "Pt"){
  TString theInputFolder = "inputs";

  TFile *_file0;
  TFile *_file1;
  TFile *_file2;
  double theXS = 2008.4*3;
  double theLumi = 35800.0;
  if     (whichDY == 0){
    _file0 = TFile::Open(Form("%s/histoDY%dzll%sRecGen.root",theInputFolder.Data(),whichDY,theHistName.Data()));
    _file1 = TFile::Open("/afs/cern.ch/work/c/ceballos/public/samples/panda/v_005_0/DYJetsToLL_M-50_LO.root");
    _file2 = TFile::Open(Form("%s/histoDY%dzll%sRecGen.root",theInputFolder.Data(),1,theHistName.Data()));
  }
  else if(whichDY == 1){
    _file0 = TFile::Open(Form("%s/histoDY%dzll%sRecGen.root",theInputFolder.Data(),whichDY,theHistName.Data()));
    _file1 = TFile::Open("/afs/cern.ch/work/c/ceballos/public/samples/panda/v_005_0/DYJetsToLL_M-50_NLO.root");
    _file2 = TFile::Open(Form("%s/histoDY%dzll%sRecGen.root",theInputFolder.Data(),2,theHistName.Data()));
  }
  else if(whichDY == 2 && nsel == 0){
    _file0 = TFile::Open(Form("%s/histoDY%dzll%sRecGen.root",theInputFolder.Data(),whichDY,theHistName.Data()));
    _file1 = TFile::Open("/afs/cern.ch/work/c/ceballos/public/samples/panda/v_005_0/DYJetsToMM_POWHEG.root");
    _file2 = TFile::Open(Form("%s/histoDY%dzll%sRecGen.root",theInputFolder.Data(),1,theHistName.Data()));
    theXS = 1975.0;
  }
  else if(whichDY == 2 && nsel == 1){
    _file0 = TFile::Open(Form("%s/histoDY%dzll%sRecGen.root",theInputFolder.Data(),whichDY,theHistName.Data()));
    _file1 = TFile::Open("/afs/cern.ch/work/c/ceballos/public/samples/panda/v_005_0/DYJetsToEE_POWHEG.root");
    _file2 = TFile::Open(Form("%s/histoDY%dzll%sRecGen.root",theInputFolder.Data(),1,theHistName.Data()));
    theXS = 1975.0;
  }

TString systName0 = "";
TString systName1 = "";

TH1D* bdat = (TH1D*)_file0->Get(Form("histo%sRecDA%s_%d",theHistName.Data(),systName0.Data(),nsel));
TH1D* bini = (TH1D*)_file0->Get(Form("histo%sRecDY%s_%d",theHistName.Data(),systName1.Data(),nsel));

TString inputFileHist = Form("hDDil%sMM",theHistName.Data());
if(nsel == 1) inputFileHist = Form("hDDil%sEE",theHistName.Data());
TH1D* xini  = (TH1D*)_file1->Get(inputFileHist.Data());

TH1D* hDNEvt  = (TH1D*)_file1->Get("hDTotalMCWeight");

xini->Scale(theXS*theLumi/hDNEvt->GetSumOfWeights());

bini->Scale(1.0/bini->GetSumOfWeights());
for(int i=1; i<=bini->GetNbinsX(); i++) {
printf("%2d %6.3f\n",i,100*bini->GetBinContent(i));
}

}
