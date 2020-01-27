#if !defined(__CINT__) || defined(__MAKECINT__)
#include <TROOT.h>                  // access to gROOT, entry point to ROOT system
#include <TSystem.h>                // interface to OS
#include <TMath.h>                  // Math
#include <vector>                   // STL vector class
#include <iostream>                 // standard I/O
#include <iomanip>                  // functions to format standard I/O
#include <fstream>                  // functions for file I/O
#include <string>                   // C++ string class
#include <sstream>                  // class for parsing strings
#include <TFile.h>                  // File handle
#include <TH1D.h>                   // 1D histogram class
#endif

void makeVBSResult(TString type, TString state = "WW", bool isNormalized = true){

  const int nBinVBSMJJ = 4;
  Float_t xbinsVBSMJJ[nBinVBSMJJ+1];
    xbinsVBSMJJ[ 0] = 500;     xbinsVBSMJJ[ 1] = 800;     xbinsVBSMJJ[ 2] = 1200;     xbinsVBSMJJ[ 3] = 1800;     xbinsVBSMJJ[ 4] = 3000;

  const int nBinVBSMLL = 4;
  Float_t xbinsVBSMLL[nBinVBSMLL+1];
    xbinsVBSMLL[ 0] = 20;      xbinsVBSMLL[ 1] = 80;      xbinsVBSMLL[ 2] = 140;      xbinsVBSMLL[ 3] = 240;      xbinsVBSMLL[ 4] = 500;

  TString xsfname("input_files_vbs/");
  TH1D* histoResult;
  if     (type == "MJJ")    {histoResult = new TH1D(Form("hDAll%s%s",state.Data(),type.Data()), Form("hDAll%s%s",state.Data(),type.Data()),    nBinVBSMJJ,   xbinsVBSMJJ); xsfname = xsfname + Form("%s%s",state.Data(),type.Data());}
  else if(type == "MLL")    {histoResult = new TH1D(Form("hDAll%s%s",state.Data(),type.Data()), Form("hDAll%s%s",state.Data(),type.Data()),    nBinVBSMLL,   xbinsVBSMLL); xsfname = xsfname + Form("%s%s",state.Data(),type.Data());}
  else {printf("WRONG TYPE\n"); return;}

  if(isNormalized) xsfname = xsfname + "_normalized.txt";
  else             xsfname = xsfname + ".txt";

  int count = 0;
  ifstream ifs;
  ifs.open(xsfname.Data());
  assert(ifs.is_open());
  string line;
  while(getline(ifs,line)) {
    Double_t r,rup,rdown;
    stringstream ss(line);
    ss >> r >> rdown >> rup;
    count++;
    histoResult->SetBinContent(count, r);
    histoResult->SetBinError  (count, (rup+rdown)/2.0);
  }
  ifs.close();

  if(histoResult->GetNbinsX() != count) {printf("DIFFERENT NUMBER OF BINS IN HISTOGRAM AND INPUT FILE: %d %d\n",histoResult->GetNbinsX(),count); return;}

  TString outNtuplename = Form("input_files_vbs/xs_%s%s_normalized%d.root",state.Data(),type.Data(),isNormalized);
  TFile *outtuple = TFile::Open(outNtuplename.Data(),"recreate");
  outtuple->cd();
  histoResult->Write();
  outtuple->Close();
  delete histoResult;
}

void makeVBSNtuple(){
 makeVBSResult("MJJ", "WW" , true);
 makeVBSResult("MLL", "WW" , true);
 makeVBSResult("MJJ", "WZ" , true);
 makeVBSResult("MJJ", "WW" , false);
 makeVBSResult("MLL", "WW" , false);
 makeVBSResult("MJJ", "WZ" , false);

}
