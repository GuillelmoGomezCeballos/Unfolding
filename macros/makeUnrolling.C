#include <TFile.h>
#include <TSystem.h>
#include <TString.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TMath.h>
#include <iostream>
#include <fstream>
#include "zPtBinning.h"

void makeUnrolling(int whichDY=3, TString theHistName = "Rap"){
  TString theInputFolder = "inputs";
  TFile *_file0 = TFile::Open(Form("%s/histoDY%dzll%sRecGen_period3.root",theInputFolder.Data(),whichDY,theHistName.Data()));

  // Chosing binning
  int nBinGenX, nBinRecX;
  if     (theHistName == "Tot"){
    nBinGenX = nBinTot;
    nBinRecX = nBinRecoTot;
  }
  else if(theHistName == "Pt"){
    nBinGenX = nBinPt;
    nBinRecX = nBinRecoPt;
  }
  else if(theHistName == "Rap"){
    nBinGenX = nBinRap;
    nBinRecX = nBinRecoRap;
  }
  else if(theHistName == "PhiStar"){
    nBinGenX = nBinPhiStar;
    nBinRecX = nBinRecoPhiStar;
  }
  else if(theHistName == "PtRap0"){
    nBinGenX = nBinPtRap0;
    nBinRecX = nBinRecoPtRap0;
  }
  else if(theHistName == "PtRap1"){
    nBinGenX = nBinPtRap1;
    nBinRecX = nBinRecoPtRap1;
  }
  else if(theHistName == "PtRap2"){
    nBinGenX = nBinPtRap2;
    nBinRecX = nBinRecoPtRap2;
  }
  else if(theHistName == "PtRap3"){
    nBinGenX = nBinPtRap3;
    nBinRecX = nBinRecoPtRap3;
  }
  else if(theHistName == "PtRap4"){
    nBinGenX = nBinPtRap4;
    nBinRecX = nBinRecoPtRap4;
  }
  else {
    printf("PROBLEM %s\n",theHistName.Data());
    return;
  }
  const int nBinGenY = nBinGenX;
  const int nBinRecY = nBinRecX*2;
  Float_t xbinsGenY[nBinGenY+1];
  Float_t xbinsRecY[nBinRecY+1];
  if     (theHistName == "Tot"){
    for(int i=0; i<=nBinGenX; i++) xbinsGenY[i] = xbinsTot[i];
    for(int i=0; i<=nBinRecX; i++) xbinsRecY[i] = xbinsRecoTot[i];
  }
  else if(theHistName == "Pt"){
    for(int i=0; i<=nBinGenX; i++) xbinsGenY[i] = xbinsPt[i];
    for(int i=0; i<=nBinRecX; i++) xbinsRecY[i] = xbinsRecoPt[i];
  }
  else if(theHistName == "Rap"){
    for(int i=0; i<=nBinGenX; i++) xbinsGenY[i] = xbinsRap[i];
    for(int i=0; i<=nBinRecX; i++) xbinsRecY[i] = xbinsRecoRap[i];
  }
  else if(theHistName == "PhiStar"){
    for(int i=0; i<=nBinGenX; i++) xbinsGenY[i] = xbinsPhiStar[i];
    for(int i=0; i<=nBinRecX; i++) xbinsRecY[i] = xbinsRecoPhiStar[i];
  }
  else if(theHistName == "PtRap0"){
    for(int i=0; i<=nBinGenX; i++) xbinsGenY[i] = xbinsPtRap0[i];
    for(int i=0; i<=nBinRecX; i++) xbinsRecY[i] = xbinsRecoPtRap0[i];
  }
  else if(theHistName == "PtRap1"){
    for(int i=0; i<=nBinGenX; i++) xbinsGenY[i] = xbinsPtRap1[i];
    for(int i=0; i<=nBinRecX; i++) xbinsRecY[i] = xbinsRecoPtRap1[i];
  }
  else if(theHistName == "PtRap2"){
    for(int i=0; i<=nBinGenX; i++) xbinsGenY[i] = xbinsPtRap2[i];
    for(int i=0; i<=nBinRecX; i++) xbinsRecY[i] = xbinsRecoPtRap2[i];
  }
  else if(theHistName == "PtRap3"){
    for(int i=0; i<=nBinGenX; i++) xbinsGenY[i] = xbinsPtRap3[i];
    for(int i=0; i<=nBinRecX; i++) xbinsRecY[i] = xbinsRecoPtRap3[i];
  }
  else if(theHistName == "PtRap4"){
    for(int i=0; i<=nBinGenX; i++) xbinsGenY[i] = xbinsPtRap4[i];
    for(int i=0; i<=nBinRecX; i++) xbinsRecY[i] = xbinsRecoPtRap4[i];
  }
  for(int i=1; i<=nBinRecX; i++) xbinsRecY[i+nBinRecX] = xbinsRecY[nBinRecX] + xbinsRecY[i];

  printf("Gen: "); for(int i=0; i<=nBinGenY; i++) printf("(%d,%.1f) ",i,xbinsGenY[i]); printf("\n");
  printf("Rec: "); for(int i=0; i<=nBinRecY; i++) printf("(%d,%.1f) ",i,xbinsRecY[i]); printf("\n");

  const int nRecNuisances = 4;
  const int nEffNuisances = 8+480;
  const int nMomNuisances = 5;

  // Initialization of input histograms
  TH2D* histoXRecGen[2]; // 2
  TH2D* histoXRecGen_RecEff[2][nRecNuisances]; // 8
  TH2D* histoXRecGen_LepEff[2][nEffNuisances]; // 976
  TH2D* histoXRecGen_MomRes[2][nMomNuisances]; // 10
  TH1D* histoXRecDA[2]; // 2
  TH1D* histoXRecDY[2]; // 2
  TH1D* histoXRecEM[2]; // 2
  TH1D* histoXRecVV[2]; // 2
  TH1D* histoXRecDY_RecEff[2][nRecNuisances]; // 8
  TH1D* histoXRecVV_RecEff[2][nRecNuisances]; // 8
  TH1D* histoXRecDY_LepEff[2][nEffNuisances]; // 976
  TH1D* histoXRecVV_LepEff[2][nEffNuisances]; // 976
  TH1D* histoXRecDA_MomRes[2][nMomNuisances]; // 10
  TH1D* histoXRecDY_MomRes[2][nMomNuisances]; // 10
  TH1D* histoXRecEM_MomRes[2][nMomNuisances]; // 10
  TH1D* histoXRecVV_MomRes[2][nMomNuisances]; // 10
  TH1D* histoXRecVV_PDF[2]; // 2
  TH1D* histoXRecDY_PDF[2]; // 2
  TH1D* histoXRecVV_QCD[2]; // 2
  TH1D* histoXRecDY_QCD[2]; // 2
  for(int i=0; i<2; i++){
    histoXRecGen[i] = (TH2D*)_file0->Get(Form("histo%sRecGen_%d",theHistName.Data(),i));
    for(int j=0; j<nRecNuisances; j++){
      histoXRecGen_RecEff[i][j] = (TH2D*)_file0->Get(Form("histo%sRecGen_RecEff_%d_%d",theHistName.Data(),i,j));
    }
    for(int j=0; j<nEffNuisances; j++){
      histoXRecGen_LepEff[i][j] = (TH2D*)_file0->Get(Form("histo%sRecGen_LepEff_%d_%d",theHistName.Data(),i,j));
    }
    for(int j=0; j<nMomNuisances; j++){
      histoXRecGen_MomRes[i][j] = (TH2D*)_file0->Get(Form("histo%sRecGen_MomRes_%d_%d",theHistName.Data(),i,j));
    }
    histoXRecDA[i] = (TH1D*)_file0->Get(Form("histo%sRecDA_%d",theHistName.Data(),i));
    histoXRecDY[i] = (TH1D*)_file0->Get(Form("histo%sRecDY_%d",theHistName.Data(),i));
    histoXRecEM[i] = (TH1D*)_file0->Get(Form("histo%sRecEM_%d",theHistName.Data(),i));
    histoXRecVV[i] = (TH1D*)_file0->Get(Form("histo%sRecVV_%d",theHistName.Data(),i));

    for(int j=0; j<nRecNuisances; j++){
      histoXRecDY_RecEff[i][j] = (TH1D*)_file0->Get(Form("histo%sRecDY_RecEff_%d_%d",theHistName.Data(),i,j));
      histoXRecVV_RecEff[i][j] = (TH1D*)_file0->Get(Form("histo%sRecVV_RecEff_%d_%d",theHistName.Data(),i,j));
    }
    for(int j=0; j<nEffNuisances; j++){
      histoXRecDY_LepEff[i][j] = (TH1D*)_file0->Get(Form("histo%sRecDY_LepEff_%d_%d",theHistName.Data(),i,j));
      histoXRecVV_LepEff[i][j] = (TH1D*)_file0->Get(Form("histo%sRecVV_LepEff_%d_%d",theHistName.Data(),i,j));
    }
    for(int j=0; j<nMomNuisances; j++){
      histoXRecDA_MomRes[i][j] = (TH1D*)_file0->Get(Form("histo%sRecDA_MomRes_%d_%d",theHistName.Data(),i,j));
      histoXRecDY_MomRes[i][j] = (TH1D*)_file0->Get(Form("histo%sRecDY_MomRes_%d_%d",theHistName.Data(),i,j));
      histoXRecEM_MomRes[i][j] = (TH1D*)_file0->Get(Form("histo%sRecEM_MomRes_%d_%d",theHistName.Data(),i,j));
      histoXRecVV_MomRes[i][j] = (TH1D*)_file0->Get(Form("histo%sRecVV_MomRes_%d_%d",theHistName.Data(),i,j));
    }
    histoXRecVV_PDF[i] = (TH1D*)_file0->Get(Form("histo%sRecVV_PDF_%d",theHistName.Data(),i));
    histoXRecDY_PDF[i] = (TH1D*)_file0->Get(Form("histo%sRecDY_PDF_%d",theHistName.Data(),i));

    histoXRecVV_QCD[i] = (TH1D*)_file0->Get(Form("histo%sRecVV_QCD_%d",theHistName.Data(),i));
    histoXRecDY_QCD[i] = (TH1D*)_file0->Get(Form("histo%sRecDY_QCD_%d",theHistName.Data(),i));
  }

  // Initialization of output histograms
  TH2D* histoYRecGen[2]; // 2
  TH2D* histoYRecGen_RecEff[2][nRecNuisances]; // 8
  TH2D* histoYRecGen_LepEff[2][nEffNuisances]; // 976
  TH2D* histoYRecGen_MomRes[2][nMomNuisances]; // 10
  TH1D* histoYRecDA[2]; // 2
  TH1D* histoYRecDY[2]; // 2
  TH1D* histoYRecEM[2]; // 2
  TH1D* histoYRecVV[2]; // 2
  TH1D* histoYRecDY_RecEff[2][nRecNuisances]; // 8
  TH1D* histoYRecVV_RecEff[2][nRecNuisances]; // 8
  TH1D* histoYRecDY_LepEff[2][nEffNuisances]; // 976
  TH1D* histoYRecVV_LepEff[2][nEffNuisances]; // 976
  TH1D* histoYRecDA_MomRes[2][nMomNuisances]; // 10
  TH1D* histoYRecDY_MomRes[2][nMomNuisances]; // 10
  TH1D* histoYRecEM_MomRes[2][nMomNuisances]; // 10
  TH1D* histoYRecVV_MomRes[2][nMomNuisances]; // 10
  TH1D* histoYRecVV_PDF[2]; // 2
  TH1D* histoYRecDY_PDF[2]; // 2
  TH1D* histoYRecVV_QCD[2]; // 2
  TH1D* histoYRecDY_QCD[2]; // 2
  for(int i=0; i<2; i++){
    histoYRecGen[i] = new TH2D(Form("histoLL%sRecGen_%d",theHistName.Data(),i), Form("histoLL%sRecGen_%d",theHistName.Data(),i), nBinRecY, xbinsRecY, nBinGenY, xbinsGenY);
    for(int j=0; j<nRecNuisances; j++){
      histoYRecGen_RecEff[i][j] = new TH2D(Form("histoLL%sRecGen_RecEff_%d_%d",theHistName.Data(),i,j), Form("histoLL%sRecGen_RecEff_%d_%d",theHistName.Data(),i,j), nBinRecY, xbinsRecY, nBinGenY, xbinsGenY);
    }
    for(int j=0; j<nEffNuisances; j++){
      histoYRecGen_LepEff[i][j] = new TH2D(Form("histoLL%sRecGen_LepEff_%d_%d",theHistName.Data(),i,j), Form("histoLL%sRecGen_LepEff_%d_%d",theHistName.Data(),i,j), nBinRecY, xbinsRecY, nBinGenY, xbinsGenY);
    }
    for(int j=0; j<nMomNuisances; j++){
      histoYRecGen_MomRes[i][j] = new TH2D(Form("histoLL%sRecGen_MomRes_%d_%d",theHistName.Data(),i,j), Form("histoLL%sRecGen_MomRes_%d_%d",theHistName.Data(),i,j), nBinRecY, xbinsRecY, nBinGenY, xbinsGenY);
    }
    histoYRecDA[i]  = new TH1D(Form("histoLL%sRecDA_%d",theHistName.Data(),i),  Form("histoLL%sRecDA_%d",theHistName.Data(),i),  nBinRecY, xbinsRecY);
    histoYRecDY[i]  = new TH1D(Form("histoLL%sRecDY_%d",theHistName.Data(),i),  Form("histoLL%sRecDY_%d",theHistName.Data(),i),  nBinRecY, xbinsRecY);
    histoYRecEM[i]  = new TH1D(Form("histoLL%sRecEM_%d",theHistName.Data(),i),  Form("histoLL%sRecEM_%d",theHistName.Data(),i),  nBinRecY, xbinsRecY);
    histoYRecVV[i]  = new TH1D(Form("histoLL%sRecVV_%d",theHistName.Data(),i),  Form("histoLL%sRecVV_%d",theHistName.Data(),i),  nBinRecY, xbinsRecY);

    for(int j=0; j<nRecNuisances; j++){
      histoYRecDY_RecEff[i][j] = new TH1D(Form("histoLL%sRecDY_RecEff_%d_%d",theHistName.Data(),i,j), Form("histoLL%sRecDY_RecEff_%d_%d",theHistName.Data(),i,j), nBinRecY, xbinsRecY);
      histoYRecVV_RecEff[i][j] = new TH1D(Form("histoLL%sRecVV_RecEff_%d_%d",theHistName.Data(),i,j), Form("histoLL%sRecVV_RecEff_%d_%d",theHistName.Data(),i,j), nBinRecY, xbinsRecY);
    }
    for(int j=0; j<nEffNuisances; j++){
      histoYRecDY_LepEff[i][j] = new TH1D(Form("histoLL%sRecDY_LepEff_%d_%d",theHistName.Data(),i,j), Form("histoLL%sRecDY_LepEff_%d_%d",theHistName.Data(),i,j), nBinRecY, xbinsRecY);
      histoYRecVV_LepEff[i][j] = new TH1D(Form("histoLL%sRecVV_LepEff_%d_%d",theHistName.Data(),i,j), Form("histoLL%sRecVV_LepEff_%d_%d",theHistName.Data(),i,j), nBinRecY, xbinsRecY);
    }
    for(int j=0; j<nMomNuisances; j++){
      histoYRecDA_MomRes[i][j] = new TH1D(Form("histoLL%sRecDA_MomRes_%d_%d",theHistName.Data(),i,j), Form("histoLL%sRecDA_MomRes_%d_%d",theHistName.Data(),i,j), nBinRecY, xbinsRecY);
      histoYRecDY_MomRes[i][j] = new TH1D(Form("histoLL%sRecDY_MomRes_%d_%d",theHistName.Data(),i,j), Form("histoLL%sRecDY_MomRes_%d_%d",theHistName.Data(),i,j), nBinRecY, xbinsRecY);
      histoYRecEM_MomRes[i][j] = new TH1D(Form("histoLL%sRecEM_MomRes_%d_%d",theHistName.Data(),i,j), Form("histoLL%sRecEM_MomRes_%d_%d",theHistName.Data(),i,j), nBinRecY, xbinsRecY);
      histoYRecVV_MomRes[i][j] = new TH1D(Form("histoLL%sRecVV_MomRes_%d_%d",theHistName.Data(),i,j), Form("histoLL%sRecVV_MomRes_%d_%d",theHistName.Data(),i,j), nBinRecY, xbinsRecY);
    }
    histoYRecVV_PDF[i] = new TH1D(Form("histoLL%sRecVV_PDF_%d",theHistName.Data(),i), Form("histoLL%sRecVV_PDF_%d",theHistName.Data(),i), nBinRecY, xbinsRecY);
    histoYRecDY_PDF[i] = new TH1D(Form("histoLL%sRecDY_PDF_%d",theHistName.Data(),i), Form("histoLL%sRecDY_PDF_%d",theHistName.Data(),i), nBinRecY, xbinsRecY);

    histoYRecVV_QCD[i] = new TH1D(Form("histoLL%sRecVV_QCD_%d",theHistName.Data(),i), Form("histoLL%sRecVV_QCD_%d",theHistName.Data(),i), nBinRecY, xbinsRecY);
    histoYRecDY_QCD[i] = new TH1D(Form("histoLL%sRecDY_QCD_%d",theHistName.Data(),i), Form("histoLL%sRecDY_QCD_%d",theHistName.Data(),i), nBinRecY, xbinsRecY);
  }

  // Assignment of output histograms
  for(int iOutput=0; iOutput<2; iOutput++){
  for(int iInput=0; iInput<2; iInput++){
    int addBinOutputHist = 0;
    if(iInput==1) addBinOutputHist = histoXRecGen[iOutput]->GetNbinsX();
    for(int nr=1; nr<=histoXRecGen[iOutput]->GetNbinsX(); nr++) {
      for(int ng=1; ng<=histoXRecGen[iOutput]->GetNbinsY(); ng++) {
        histoYRecGen[iOutput]->SetBinContent(nr+addBinOutputHist,ng,histoXRecGen[iInput]->GetBinContent(nr,ng));
        if(iOutput == iInput){
          for(int j=0; j<nRecNuisances; j++){
            histoYRecGen_RecEff[iOutput][j]->SetBinContent(nr+addBinOutputHist,ng,histoXRecGen_RecEff[iInput][j]->GetBinContent(nr,ng));
          }
          for(int j=0; j<nEffNuisances; j++){
            histoYRecGen_LepEff[iOutput][j]->SetBinContent(nr+addBinOutputHist,ng,histoXRecGen_LepEff[iInput][j]->GetBinContent(nr,ng));
          }
          for(int j=0; j<nMomNuisances; j++){
            histoYRecGen_MomRes[iOutput][j]->SetBinContent(nr+addBinOutputHist,ng,histoXRecGen_MomRes[iInput][j]->GetBinContent(nr,ng));
          }
        }
        else {
          for(int j=0; j<nRecNuisances; j++){
            histoYRecGen_RecEff[iOutput][j]->SetBinContent(nr+addBinOutputHist,ng,histoXRecGen[iInput]->GetBinContent(nr,ng));
          }
          for(int j=0; j<nEffNuisances; j++){
            histoYRecGen_LepEff[iOutput][j]->SetBinContent(nr+addBinOutputHist,ng,histoXRecGen[iInput]->GetBinContent(nr,ng));
          }
          for(int j=0; j<nMomNuisances; j++){
            histoYRecGen_MomRes[iOutput][j]->SetBinContent(nr+addBinOutputHist,ng,histoXRecGen[iInput]->GetBinContent(nr,ng));
          }
        }
      }
      histoYRecDA[iOutput]->SetBinContent(nr+addBinOutputHist,histoXRecDA[iInput]->GetBinContent(nr));
      histoYRecDY[iOutput]->SetBinContent(nr+addBinOutputHist,histoXRecDY[iInput]->GetBinContent(nr));
      histoYRecEM[iOutput]->SetBinContent(nr+addBinOutputHist,histoXRecEM[iInput]->GetBinContent(nr));
      histoYRecVV[iOutput]->SetBinContent(nr+addBinOutputHist,histoXRecVV[iInput]->GetBinContent(nr));

      if(iOutput == iInput){
	for(int j=0; j<nRecNuisances; j++){
          histoYRecDY_RecEff[iOutput][j]->SetBinContent(nr+addBinOutputHist,histoXRecDY_RecEff[iInput][j]->GetBinContent(nr));
          histoYRecVV_RecEff[iOutput][j]->SetBinContent(nr+addBinOutputHist,histoXRecVV_RecEff[iInput][j]->GetBinContent(nr));
	}
	for(int j=0; j<nEffNuisances; j++){
          histoYRecDY_LepEff[iOutput][j]->SetBinContent(nr+addBinOutputHist,histoXRecDY_LepEff[iInput][j]->GetBinContent(nr));
          histoYRecVV_LepEff[iOutput][j]->SetBinContent(nr+addBinOutputHist,histoXRecVV_LepEff[iInput][j]->GetBinContent(nr));
	}
	for(int j=0; j<nMomNuisances; j++){
          histoYRecDA_MomRes[iOutput][j]->SetBinContent(nr+addBinOutputHist,histoXRecDA_MomRes[iInput][j]->GetBinContent(nr));
          histoYRecDY_MomRes[iOutput][j]->SetBinContent(nr+addBinOutputHist,histoXRecDY_MomRes[iInput][j]->GetBinContent(nr));
          histoYRecEM_MomRes[iOutput][j]->SetBinContent(nr+addBinOutputHist,histoXRecEM_MomRes[iInput][j]->GetBinContent(nr));
          histoYRecVV_MomRes[iOutput][j]->SetBinContent(nr+addBinOutputHist,histoXRecVV_MomRes[iInput][j]->GetBinContent(nr));
	}
      }
      else {
	for(int j=0; j<nRecNuisances; j++){
          histoYRecDY_RecEff[iOutput][j]->SetBinContent(nr+addBinOutputHist,histoXRecDY[iInput]->GetBinContent(nr));
          histoYRecVV_RecEff[iOutput][j]->SetBinContent(nr+addBinOutputHist,histoXRecVV[iInput]->GetBinContent(nr));
	}
	for(int j=0; j<nEffNuisances; j++){
          histoYRecDY_LepEff[iOutput][j]->SetBinContent(nr+addBinOutputHist,histoXRecDY[iInput]->GetBinContent(nr));
          histoYRecVV_LepEff[iOutput][j]->SetBinContent(nr+addBinOutputHist,histoXRecVV[iInput]->GetBinContent(nr));
	}
	for(int j=0; j<nMomNuisances; j++){
          histoYRecDA_MomRes[iOutput][j]->SetBinContent(nr+addBinOutputHist,histoXRecDA[iInput]->GetBinContent(nr));
          histoYRecDY_MomRes[iOutput][j]->SetBinContent(nr+addBinOutputHist,histoXRecDY[iInput]->GetBinContent(nr));
          histoYRecEM_MomRes[iOutput][j]->SetBinContent(nr+addBinOutputHist,histoXRecEM[iInput]->GetBinContent(nr));
          histoYRecVV_MomRes[iOutput][j]->SetBinContent(nr+addBinOutputHist,histoXRecVV[iInput]->GetBinContent(nr));
	}
      }
      histoYRecVV_PDF[iOutput]->SetBinContent(nr+addBinOutputHist,histoXRecVV_PDF[iInput]->GetBinContent(nr));
      histoYRecDY_PDF[iOutput]->SetBinContent(nr+addBinOutputHist,histoXRecDY_PDF[iInput]->GetBinContent(nr));

      histoYRecVV_QCD[iOutput]->SetBinContent(nr+addBinOutputHist,histoXRecVV_QCD[iInput]->GetBinContent(nr));
      histoYRecDY_QCD[iOutput]->SetBinContent(nr+addBinOutputHist,histoXRecDY_QCD[iInput]->GetBinContent(nr));
    }
  }
  }

  // Writing output to a file
  TString output = Form("histoDY%dzll%sRecGen_period3.root",whichDY,theHistName.Data()); 
  TFile* outFilePlots = new TFile(output.Data(),"recreate");
  outFilePlots->cd();
  for(int i=0; i<2; i++){
    histoYRecGen[i]->Write();
    for(int nj=0; nj<nRecNuisances; nj++) histoYRecGen_RecEff[i][nj]->Write();
    for(int nj=0; nj<nEffNuisances; nj++) histoYRecGen_LepEff[i][nj]->Write();
    for(int nj=0; nj<nMomNuisances; nj++) histoYRecGen_MomRes[i][nj]->Write();
    histoYRecDA[i]->Write();
    histoYRecDY[i]->Write();
    histoYRecEM[i]->Write();
    histoYRecVV[i]->Write();
    for(int nj=0; nj<nRecNuisances; nj++) histoYRecDY_RecEff[i][nj]->Write();
    for(int nj=0; nj<nRecNuisances; nj++) histoYRecVV_RecEff[i][nj]->Write();
    for(int nj=0; nj<nEffNuisances; nj++) histoYRecDY_LepEff[i][nj]->Write();
    for(int nj=0; nj<nEffNuisances; nj++) histoYRecVV_LepEff[i][nj]->Write();
    for(int nj=0; nj<nMomNuisances; nj++) histoYRecDA_MomRes[i][nj]->Write();
    for(int nj=0; nj<nMomNuisances; nj++) histoYRecDY_MomRes[i][nj]->Write();
    for(int nj=0; nj<nMomNuisances; nj++) histoYRecEM_MomRes[i][nj]->Write();
    for(int nj=0; nj<nMomNuisances; nj++) histoYRecVV_MomRes[i][nj]->Write();
    histoYRecVV_PDF[i]->Write();
    histoYRecDY_PDF[i]->Write();
    histoYRecVV_QCD[i]->Write();
    histoYRecDY_QCD[i]->Write();
  }
  outFilePlots->Close();
}
