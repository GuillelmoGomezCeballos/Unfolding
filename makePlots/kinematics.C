#include <TROOT.h>
#include <TFile.h>
#include <TTree.h>
#include <TSystem.h>
#include <TString.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TMath.h>
#include <iostream>
#include <fstream>
#include "TRandom.h"
#include "TLorentzVector.h"

#include "MitAnalysisRunII/panda/macros/80x/pandaFlat.C"
#include "MitAnalysisRunII/data/80x/RoccoR.cc"

enum TriggerBits {
    kMETTrig	   =(1<<0),
    kSinglePhoTrig =(1<<1),
    kMuEGTrig	   =(1<<2),
    kMuMuTrig	   =(1<<3),
    kMuTrig	   =(1<<4),
    kEGEGTrig	   =(1<<5),
    kEGTrig	   =(1<<6)
};

enum SelectionBit {
 kLoose   =(1<<0),
 kFake    =(1<<1),
 kMedium  =(1<<2),
 kTight   =(1<<3)
};

const double mass_el = 0.000510998928;
const double mass_mu = 0.10566;
void kinematics(int whichDY = 1, bool isMIT=false)
{

  gInterpreter->ExecuteMacro("GoodStyle.C");

  TString dirPathRM = TString(gSystem->Getenv("CMSSW_BASE")) + "/src/MitAnalysisRunII/data/80x/rcdata.2016.v3";
  RoccoR rmcor(dirPathRM.Data());
  double lumi = 35.8;
  double k_eff = 0.5 * sqrt(20285930./12446486.);
  //*******************************************************
  //Input Files
  //*******************************************************
  TString filesPath = "/data/t3home000/ceballos/panda/v_004_0/";
  if(isMIT == false) filesPath = "/afs/cern.ch/work/c/ceballos/public/samples/panda/v_004_0/";
  vector<TString> infileName_;
  vector<Int_t> infileCat_;

  TCanvas *c = new TCanvas("c","c",600, 600);

  c->SetRightMargin(0.15);

  const int nBinPt = 38; Float_t xbinsPt[nBinPt+1] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,16,18,20,22,25,28,32,37,43,52,65,85,
						      120,160,190,220,250,300,400,500,750,1000,1250,1500};
  const int nBinRap = 24; Float_t xbinsRap[nBinRap+1] = {0.0,0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1.0,1.1,1.2,1.3,1.4,1.5,1.6,1.7,1.8,1.9,2.0,2.1,2.2,2.3,2.4};
  const int nBinPhiStar = 37; Float_t xbinsPhiStar[nBinPhiStar+1] = {0.0001,0.001,0.002,0.003,0.004,0.005,0.006,0.007,0.008,0.009,
								     0.010,0.020,0.030,0.040,0.050,0.060,0.070,0.080,0.090,
								     0.100,0.200,0.300,0.400,0.500,0.600,0.700,0.800,0.900,1.000,2.000,3.000,4.000,5.000,10, 20, 30, 50, 100};
  const int nBinDPhi = 32; Float_t xbinsDPhi[nBinDPhi+1];
  for (int i=0; i<nBinDPhi+1; i++) xbinsDPhi[i]=0.1*i;

  const int nBinDY = 25; Float_t xbinsDY[nBinDY+1];
  for (int i=0; i<nBinDY+1; i++) xbinsDY[i]=0.2*i;

  const int nBinDR = 25; Float_t xbinsDR[nBinDR+1];
  for (int i=0; i<nBinDR+1; i++) xbinsDR[i]=0.2*i;

  TFile *outf = new TFile("testout.root","recreate");

  TH2D *phiVpt = new TH2D("phiVpt", "", nBinPhiStar, xbinsPhiStar, nBinPt, xbinsPt);
  TH2D *phiVrap = new TH2D("phiVrap", "", nBinPhiStar, xbinsPhiStar, nBinRap, xbinsRap);
  TH2D *ptVrap = new TH2D("ptVrap", "", nBinPt, xbinsPt, nBinRap, xbinsRap);

  TH2D *phiVdphi = new TH2D("phiVdphi", "", nBinPhiStar, xbinsPhiStar, nBinDPhi, xbinsDPhi);
  TH2D *ptVdphi = new TH2D("ptVdphi", "", nBinPt, xbinsPt, nBinDPhi, xbinsDPhi);
  TH2D *rapVdphi = new TH2D("rapVdphi", "", nBinRap, xbinsRap, nBinDPhi, xbinsDPhi);

  TH2D *phiVdy = new TH2D("phiVdy", "", nBinPhiStar, xbinsPhiStar, nBinDY, xbinsDY);
  TH2D *ptVdy = new TH2D("ptVdy", "", nBinPt, xbinsPt, nBinDY, xbinsDY);
  TH2D *rapVdy = new TH2D("rapVdy", "", nBinRap, xbinsRap, nBinDY, xbinsDY);

  TH2D *phiVdr = new TH2D("phiVdr", "", nBinPhiStar, xbinsPhiStar, nBinDR, xbinsDR);
  TH2D *ptVdr = new TH2D("ptVdr", "", nBinPt, xbinsPt, nBinDR, xbinsDR);
  TH2D *rapVdr = new TH2D("rapVdr", "", nBinRap, xbinsRap, nBinDR, xbinsDR);

  infileName_.push_back(Form("%sDYJetsToLL_Pt0To50.root" ,filesPath.Data()));  infileCat_.push_back(2);
  infileName_.push_back(Form("%sDYJetsToLL_Pt50To100.root" ,filesPath.Data()));  infileCat_.push_back(2);
  infileName_.push_back(Form("%sDYJetsToLL_Pt100To250.root" ,filesPath.Data()));  infileCat_.push_back(2);
  infileName_.push_back(Form("%sDYJetsToLL_Pt250To400.root" ,filesPath.Data()));  infileCat_.push_back(2);
  infileName_.push_back(Form("%sDYJetsToLL_Pt400To650.root" ,filesPath.Data()));  infileCat_.push_back(2);
  infileName_.push_back(Form("%sDYJetsToLL_Pt650ToInf.root" ,filesPath.Data()));  infileCat_.push_back(2);
  
  for(UInt_t ifile=0; ifile<infileName_.size(); ifile++) {
    printf("sampleNames(%d): %s\n",ifile,infileName_[ifile].Data());
    TFile *the_input_file = TFile::Open(infileName_[ifile].Data());
    TTree *the_input_tree = (TTree*)the_input_file->FindObjectAny("events");
    
    pandaFlat thePandaFlat(the_input_tree);
    Long64_t nentries = thePandaFlat.fChain->GetEntriesFast();
    Long64_t nbytes = 0, nb = 0;
    for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = thePandaFlat.LoadTree(jentry);
      if (ientry < 0) break;
      nb = thePandaFlat.fChain->GetEntry(jentry);   nbytes += nb;
      if (jentry%1000000 == 0) printf("--- reading event %8lld (%8lld) of %8lld\n",jentry,ientry,nentries);

      bool passTrigger = (thePandaFlat.trigger & kMuEGTrig) == kMuEGTrig || (thePandaFlat.trigger & kMuMuTrig) == kMuMuTrig ||
                         (thePandaFlat.trigger & kMuTrig)   == kMuTrig   || (thePandaFlat.trigger & kEGEGTrig) == kEGEGTrig ||
			 (thePandaFlat.trigger & kEGTrig)   == kEGTrig;
      if(passTrigger == false) continue;
      if(thePandaFlat.metFilter == 0) continue;
      
      if(thePandaFlat.nLooseLep != 2) continue;

      int theCategory = infileCat_[ifile];

      bool passLepId = ((thePandaFlat.looseLep1SelBit & kMedium) == kMedium) && ((thePandaFlat.looseLep2SelBit & kMedium) == kMedium);
      if(passLepId == false) continue;

      int lepType = -1;
      if     (abs(thePandaFlat.looseLep1PdgId)==13 && abs(thePandaFlat.looseLep2PdgId)==13 && thePandaFlat.looseLep1PdgId*thePandaFlat.looseLep2PdgId<0) lepType = 0;
      else if(abs(thePandaFlat.looseLep1PdgId)==11 && abs(thePandaFlat.looseLep2PdgId)==11 && thePandaFlat.looseLep1PdgId*thePandaFlat.looseLep2PdgId<0) lepType = 1;
      else if(abs(thePandaFlat.looseLep1PdgId)==13 && abs(thePandaFlat.looseLep2PdgId)==11 && thePandaFlat.looseLep1PdgId*thePandaFlat.looseLep2PdgId<0) lepType = 2;
      else if(abs(thePandaFlat.looseLep1PdgId)==11 && abs(thePandaFlat.looseLep2PdgId)==13 && thePandaFlat.looseLep1PdgId*thePandaFlat.looseLep2PdgId<0) lepType = 2;
      else if(abs(thePandaFlat.looseLep1PdgId)==13 && abs(thePandaFlat.looseLep2PdgId)==13 && thePandaFlat.looseLep1PdgId*thePandaFlat.looseLep2PdgId>0) lepType = 3;
      else if(abs(thePandaFlat.looseLep1PdgId)==11 && abs(thePandaFlat.looseLep2PdgId)==11 && thePandaFlat.looseLep1PdgId*thePandaFlat.looseLep2PdgId>0) lepType = 4;
      else if(abs(thePandaFlat.looseLep1PdgId)==13 && abs(thePandaFlat.looseLep2PdgId)==11 && thePandaFlat.looseLep1PdgId*thePandaFlat.looseLep2PdgId>0) lepType = 5;
      else if(abs(thePandaFlat.looseLep1PdgId)==11 && abs(thePandaFlat.looseLep2PdgId)==13 && thePandaFlat.looseLep1PdgId*thePandaFlat.looseLep2PdgId>0) lepType = 5;
      else printf("Impossible dilepton combination: %d %d\n",thePandaFlat.looseLep1PdgId,thePandaFlat.looseLep2PdgId);

      if(lepType >= 3 || (lepType == 2 && theCategory != 0)) continue;
      
      double thePDGMass[2] = {mass_mu, mass_mu};
      if     (abs(lepType) == 1) {thePDGMass[0] = mass_el; thePDGMass[1] = mass_el;}
      else if(abs(lepType) == 2 && abs(thePandaFlat.looseLep1PdgId)==11) {thePDGMass[0] = mass_el;}
      else if(abs(lepType) == 2 && abs(thePandaFlat.looseLep2PdgId)==11) {thePDGMass[1] = mass_el;}
      TLorentzVector v1,v2;
      v1.SetPtEtaPhiM(thePandaFlat.looseLep1Pt,thePandaFlat.looseLep1Eta,thePandaFlat.looseLep1Phi,thePDGMass[0]);
      v2.SetPtEtaPhiM(thePandaFlat.looseLep2Pt,thePandaFlat.looseLep2Eta,thePandaFlat.looseLep2Phi,thePDGMass[1]);

      bool passSel = TMath::Abs((v1+v2).M()-91.1876) < 15 && v1.Pt() > 25 && v2.Pt() > 25;

      double ZRecPt  = (v1+v2).Pt();
      double ZRecRap = TMath::Abs((v1+v2).Rapidity());

      double ZRecPhiACop=0; double ZRecCosThetaStar=0; double ZRecPhiStar=0;
      ZRecPhiACop = TMath::Pi() - fabs(v1.DeltaPhi(v2));
      if (thePandaFlat.looseLep1PdgId < 0) ZRecCosThetaStar = tanh( float( (v1.Rapidity() - v2.Rapidity())/2) );
      else                                 ZRecCosThetaStar = tanh( float( (v2.Rapidity() - v1.Rapidity())/2) );
      ZRecPhiStar = tan(ZRecPhiACop/2)*sqrt(1-pow(ZRecCosThetaStar,2));

      double ZGenPt = 0; double ZGenRap = 0; bool passPtFid = false; bool passRapFid = false; bool passPtRapFid[5] = {false, false, false, false, false}; 
      double ZGenPhiACop=0; double ZGenCosThetaStar=0; double ZGenPhiStar=0; bool passPhiStarFid = false;
      if(thePandaFlat.looseGenLep1PdgId != 0 && thePandaFlat.looseGenLep2PdgId != 0 &&
         thePandaFlat.genLep1Pt > 25 && TMath::Abs(thePandaFlat.genLep1Eta) < 2.5 &&
	 thePandaFlat.genLep2Pt > 25 && TMath::Abs(thePandaFlat.genLep2Eta) < 2.5){
        TLorentzVector vGen1,vGen2;
        vGen1.SetPtEtaPhiM(thePandaFlat.genLep1Pt,thePandaFlat.genLep1Eta,thePandaFlat.genLep1Phi,thePDGMass[0]);
        vGen2.SetPtEtaPhiM(thePandaFlat.genLep2Pt,thePandaFlat.genLep2Eta,thePandaFlat.genLep2Phi,thePDGMass[1]);
	if(TMath::Abs((vGen1+vGen2).M()-91.1876) < 15.0) {

	  ZGenPt = ((vGen1+vGen2).Pt());
	  ZGenRap = TMath::Abs((vGen1+vGen2).Rapidity());

	  ZGenPhiACop = TMath::Pi() - fabs(vGen1.DeltaPhi(vGen2));
	  if (thePandaFlat.looseGenLep1PdgId < 0) ZGenCosThetaStar = tanh( float( (vGen1.Rapidity() - vGen2.Rapidity())/2) );
	  else                                 ZGenCosThetaStar = tanh( float( (vGen2.Rapidity() - vGen1.Rapidity())/2) );
	  ZGenPhiStar = tan(ZGenPhiACop/2)*sqrt(1-pow(ZGenCosThetaStar,2));

	  if (ZGenPhiStar<4.0 && ZGenPhiStar>1e-4) { passPhiStarFid = true; }
	}

	double totalWeight = thePandaFlat.normalizedWeight * thePandaFlat.sf_pu;

	phiVpt->Fill(ZGenPhiStar, ZGenPt, totalWeight);
	phiVrap->Fill(ZGenPhiStar, ZGenRap, totalWeight);
	ptVrap->Fill(ZGenPt, ZGenRap, totalWeight);
	
	phiVdphi->Fill(ZGenPhiStar, fabs(vGen1.DeltaPhi(vGen2)), totalWeight);
	ptVdphi->Fill(ZGenPt, fabs(vGen1.DeltaPhi(vGen2)), totalWeight);
	rapVdphi->Fill(ZGenRap, fabs(vGen1.DeltaPhi(vGen2)), totalWeight);
				     
	phiVdy->Fill(ZGenPhiStar, abs(vGen1.Rapidity() - vGen2.Rapidity()), totalWeight);
	ptVdy->Fill(ZGenPt, abs(vGen1.Rapidity() - vGen2.Rapidity()), totalWeight);
	rapVdy->Fill(ZGenRap, abs(vGen1.Rapidity() - vGen2.Rapidity()), totalWeight);
	
	phiVdr->Fill(ZGenPhiStar, sqrt( (vGen1.Eta() - vGen2.Eta())*(vGen1.Eta() - vGen2.Eta()) + (vGen1.DeltaPhi(vGen2)*vGen1.DeltaPhi(vGen2)) ), totalWeight);
	ptVdr->Fill(ZGenPt, sqrt( (vGen1.Eta() - vGen2.Eta())*(vGen1.Eta() - vGen2.Eta()) + (vGen1.DeltaPhi(vGen2)*vGen1.DeltaPhi(vGen2)) ), totalWeight);
	rapVdr->Fill(ZGenRap, sqrt( (vGen1.Eta() - vGen2.Eta())*(vGen1.Eta() - vGen2.Eta()) + (vGen1.DeltaPhi(vGen2)*vGen1.DeltaPhi(vGen2)) ), totalWeight);
      }

      

    } // end event loop
  } // end samples loop

  phiVpt->Scale(1,"width");
  phiVrap->Scale(1,"width");
  ptVrap->Scale(1,"width");

  phiVdphi->Scale(1,"width");
  ptVdphi->Scale(1,"width");
  rapVdphi->Scale(1,"width");

  phiVdy->Scale(1,"width");
  ptVdy->Scale(1,"width");
  rapVdy->Scale(1,"width");

  phiVdr->Scale(1,"width");
  ptVdr->Scale(1,"width");
  rapVdr->Scale(1,"width");

  gStyle->SetOptStat(0);
  c->SetLogz();

  c->SetLogx(1);
  c->SetLogy(1);
  phiVpt->GetXaxis()->SetTitle("Gen #phi *");
  phiVpt->GetYaxis()->SetTitle("Gen p_{T} ");
  phiVpt->Draw("colz");
  c->SaveAs("phiVpt.pdf");

  c->SetLogx(1);
  c->SetLogy(0);
  phiVrap->GetXaxis()->SetTitle("Gen #phi *");
  phiVrap->GetYaxis()->SetTitle("Gen y");
  phiVrap->Draw("colz");
  c->SaveAs("phiVrap.pdf");

  c->SetLogx(1);
  c->SetLogy(0);
  ptVrap->GetXaxis()->SetTitle("Gen p_{T}");
  ptVrap->GetYaxis()->SetTitle("Gen y");
  ptVrap->Draw("colz");
  c->SaveAs("phiVy.pdf");

  c->SetLogx(1);
  c->SetLogy(0);
  phiVdphi->GetXaxis()->SetTitle("Gen #phi *");
  phiVdphi->GetYaxis()->SetTitle("Gen #Delta#phi");
  phiVdphi->Draw("colz");
  c->SaveAs("phiVdphi.pdf");

  c->SetLogx(1);
  c->SetLogy(0);
  ptVdphi->GetXaxis()->SetTitle("Gen p_{T}");
  ptVdphi->GetYaxis()->SetTitle("Gen #Delta#phi");
  ptVdphi->Draw("colz");
  c->SaveAs("ptVdphi.pdf");

  c->SetLogx(0);
  c->SetLogy(0);
  rapVdphi->GetXaxis()->SetTitle("Gen y");
  rapVdphi->GetYaxis()->SetTitle("Gen #Delta#phi");
  rapVdphi->Draw("colz");
  c->SaveAs("rapVdphi.pdf");

  c->SetLogx(1);
  c->SetLogy(0);
  phiVdy->GetXaxis()->SetTitle("Gen #phi *");
  phiVdy->GetYaxis()->SetTitle("Gen #Delta y");
  phiVdy->Draw("colz");
  c->SaveAs("phiVdy.pdf");

  c->SetLogx(1);
  c->SetLogy(0);
  ptVdy->GetXaxis()->SetTitle("Gen p_{T}");
  ptVdy->GetYaxis()->SetTitle("Gen #Delta y");
  ptVdy->Draw("colz");
  c->SaveAs("ptVdy.pdf");

  c->SetLogx(0);
  c->SetLogy(0);
  rapVdy->GetXaxis()->SetTitle("Gen y");
  rapVdy->GetYaxis()->SetTitle("Gen #Delta y");
  rapVdy->Draw("colz");
  c->SaveAs("rapVdy.pdf");

  c->SetLogx(1);
  c->SetLogy(0);
  phiVdr->GetXaxis()->SetTitle("Gen #phi *");
  phiVdr->GetYaxis()->SetTitle("Gen #Delta R");
  phiVdr->Draw("colz");
  c->SaveAs("phiVdr.pdf");

  c->SetLogx(1);
  c->SetLogy(0);
  ptVdr->GetXaxis()->SetTitle("Gen p_{T}");
  ptVdr->GetYaxis()->SetTitle("Gen #Delta R");
  ptVdr->Draw("colz");
  c->SaveAs("ptVdr.pdf");

  c->SetLogx(0);
  c->SetLogy(0);
  rapVdr->GetXaxis()->SetTitle("Gen y");
  rapVdr->GetYaxis()->SetTitle("Gen #Delta R");
  rapVdr->Draw("colz");
  c->SaveAs("rapVdr.pdf");

  outf->Write();
  outf->Close();


}
