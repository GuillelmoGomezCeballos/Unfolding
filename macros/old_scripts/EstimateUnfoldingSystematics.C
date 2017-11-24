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
// whichDY = 0 (MG), 1 (aMCNLO), 2 (POWHEG)
void helper_function(int nsel=0,int whichDY=0, int rebin=1, TString theHistName = "Pt", TString suffix = ""){
  TString theInputFolder = "inputs_finerrecobinning";
  //TString theInputFolder = "inputs";

  TRandom3 *rnd = new TRandom3(5002);

  TFile *_file0;
  TFile *_file1;
  double theXS = 2008.4*3;
  TFile *_file0AlternativeMC;
  TFile *_file1AlternativeMC;
  double alternativeMCXS = 2008.4*3;
  double theLumi = 35800.0;
  _file0 = TFile::Open(Form("%s/histoDY%dzll%sRecGen.root",theInputFolder.Data(),1,theHistName.Data()));
  _file1 = TFile::Open("/afs/cern.ch/work/c/ceballos/public/samples/panda/v_004_0/DYJetsToLL_M-50_NLO.root");
  // _file0 = TFile::Open(Form("%s/histoDY%dzll%sRecGen.root",theInputFolder.Data(),0,theHistName.Data()));
  // _file1 = TFile::Open("/afs/cern.ch/work/c/ceballos/public/samples/panda/v_004_0/DYJetsToLL_M-50_LO.root");


  if     (whichDY == 0){
    _file0AlternativeMC = TFile::Open(Form("%s/histoDY%dzll%sRecGen.root",theInputFolder.Data(),whichDY,theHistName.Data()));
    _file1AlternativeMC = TFile::Open("/afs/cern.ch/work/c/ceballos/public/samples/panda/v_004_0/DYJetsToLL_M-50_LO.root");
  }
  else if(whichDY == 1){
    _file0AlternativeMC = TFile::Open(Form("%s/histoDY%dzll%sRecGen.root",theInputFolder.Data(),whichDY,theHistName.Data()));
    _file1AlternativeMC = TFile::Open("/afs/cern.ch/work/c/ceballos/public/samples/panda/v_004_0/DYJetsToLL_M-50_NLO.root");
  }
  else if(whichDY == 2 && nsel == 0){
    _file0AlternativeMC = TFile::Open(Form("%s/histoDY%dzll%sRecGen.root",theInputFolder.Data(),whichDY,theHistName.Data()));
    _file1AlternativeMC = TFile::Open("/afs/cern.ch/work/c/ceballos/public/samples/panda/v_004_0/DYJetsToMM_POWHEG.root");
    alternativeMCXS = 1975.0;
  }
  else if(whichDY == 2 && nsel == 1){
    _file0AlternativeMC = TFile::Open(Form("%s/histoDY%dzll%sRecGen.root",theInputFolder.Data(),whichDY,theHistName.Data()));
    _file1AlternativeMC = TFile::Open("/afs/cern.ch/work/c/ceballos/public/samples/panda/v_004_0/DYJetsToEE_POWHEG.root");
    alternativeMCXS = 1975.0;
  }
  
  //*****************************
  //Load Alternative MC inputs
  //*****************************

  //Get the alternative MC generated spectrum 
  TString alternativeMCGenHistName = Form("hDDil%sMM",theHistName.Data());
  if(nsel == 1) alternativeMCGenHistName = Form("hDDil%sEE",theHistName.Data());
  TH1D* alternativeMCGenSpectrum  = (TH1D*)(_file1AlternativeMC->Get(alternativeMCGenHistName.Data()))->Clone("alternativeMCGenSpectrum");
  TH1D* alternativeMCNEvt  = (TH1D*)(_file1AlternativeMC->Get("hDTotalMCWeight"))->Clone("alternativeMCNEvt");
  alternativeMCGenSpectrum->Scale(alternativeMCXS*theLumi/alternativeMCNEvt->GetSumOfWeights());
  
  //Get the alternative MC reco spectrum 
  TH1D* alternativeMCRecoSpectrum = (TH1D*)(_file0AlternativeMC->Get(Form("histo%sRecDY%s_%d",theHistName.Data(),"",nsel)))->Clone("alternativeMCRecoSpectrum");
  
  cout << "Alternative MC Reco Spectrum: " << _file0AlternativeMC->GetName() << " : " << Form("histo%sRecDY%s_%d",theHistName.Data(),"",nsel) << "\n";
  cout << "Alternative MC Gen Spectrum: " << _file1AlternativeMC->GetName() << " : " << alternativeMCGenHistName.Data() << "\n";

  //Get the alternative MC A matrix
  TH2D* alternativeMCAdet = (TH2D*)(_file0AlternativeMC->Get(Form("histo%sRecGen%s_%d",theHistName.Data(),"",nsel)))->Clone("alternativeMCAdet");

  cout << "test00: " << alternativeMCRecoSpectrum->GetBinContent(10) << "\n";

  // subtract reconstructed non-fiducial events in data
  for(int i=1; i<=alternativeMCAdet->GetNbinsX(); i++) { // RECO
    double allRecBin = alternativeMCRecoSpectrum->GetBinContent(i);
    double fidRecBin = 0;
    for(int j=1; j<=alternativeMCAdet->GetNbinsY(); j++) { // GEN
      fidRecBin = fidRecBin + alternativeMCAdet->GetBinContent(i,j);
    }
    double gendiff = allRecBin - fidRecBin;
    if(gendiff <= 0 || alternativeMCRecoSpectrum->GetBinContent(i)-gendiff <= 0) printf("Bin %d totally efficient\n",i);
    //printf("dat(%2d) = %f -> ",i,bdat->GetBinContent(i));
    alternativeMCRecoSpectrum->SetBinContent(i,TMath::Max(alternativeMCRecoSpectrum->GetBinContent(i)-gendiff,0.0));
    //printf("%f\n",bdat->GetBinContent(i));
  }

  cout << "test01: " << alternativeMCRecoSpectrum->GetBinContent(10) << "\n";

  //*****************************
  //Load Nominal MC inputs
  //*****************************

  //Get the A matrix from default MC sample - aMC@NLO
  TH2D* Adet = (TH2D*)(_file0->Get(Form("histo%sRecGen%s_%d",theHistName.Data(),"",nsel)))->Clone("Adet");

  //Get the generated spectrum from default MC sample - aMC@NLO
  TString inputFileHist = Form("hDDil%sMM",theHistName.Data());
  if(nsel == 1) inputFileHist = Form("hDDil%sEE",theHistName.Data());
  TH1D* xini  = (TH1D*)(_file1->Get(inputFileHist.Data()))->Clone("xini");
  TH1D* hDNEvt  = (TH1D*)(_file1->Get("hDTotalMCWeight"))->Clone("hDNEvt");
  xini->Scale(theXS*theLumi/hDNEvt->GetSumOfWeights());

  //Get the reco spectrum from default MC sample - aMC@NLO 
  TH1D* bdat = (TH1D*)(_file0->Get(Form("histo%sRecDY%s_%d",theHistName.Data(),"",nsel)))->Clone("bdat");
  TH1D* bini = (TH1D*)(_file0->Get(Form("histo%sRecDY%s_%d",theHistName.Data(),"",nsel)))->Clone("bini");

  cout << "bdat: " << _file0->GetName() << " : " << Form("histo%sRecDY%s_%d",theHistName.Data(),"",nsel) << "\n";
  cout << "xini: " << _file1->GetName() << " : " << inputFileHist.Data() << "\n";

  cout << "test0: " << bdat->GetBinContent(10) << " : " << alternativeMCRecoSpectrum->GetBinContent(10) << "\n";


  // add non-reconstructed fiducial events in gen bin 0
  for(int i=1; i<=Adet->GetNbinsY(); i++) { // GEN
    double genBin = xini->GetBinContent(i);
    double recBin = 0;
    for(int j=1; j<=Adet->GetNbinsX(); j++) { // RECO
      recBin = recBin + Adet->GetBinContent(j,i);
    }
    if(genBin-recBin <= 0) printf("Bin %d totally efficient\n",i);
    Adet->SetBinContent(0,i,TMath::Max(genBin-recBin,0.0));
  }

  cout << "test1: " << bdat->GetBinContent(10) << " : " << alternativeMCRecoSpectrum->GetBinContent(10) << "\n";
  //set overflow bin content
  //warning, this part assumes that the A matrix is square
  for(int i=1; i<=Adet->GetNbinsY(); i++) {
    Adet->SetBinContent(i                  ,Adet->GetNbinsY()+1,0.0);
  }
  for(int i=1; i<=Adet->GetNbinsX(); i++) {
    Adet->SetBinContent(Adet->GetNbinsX()+1,i                  ,0.0);
  }

  cout << "test2: " << bdat->GetBinContent(10) << " : " << alternativeMCRecoSpectrum->GetBinContent(10) << "\n";
  // subtract reconstructed non-fiducial events in data
  for(int i=1; i<=Adet->GetNbinsX(); i++) { // RECO
    double allRecBin = bini->GetBinContent(i);
    double fidRecBin = 0;
    for(int j=1; j<=Adet->GetNbinsY(); j++) { // GEN
      fidRecBin = fidRecBin + Adet->GetBinContent(i,j);
    }
    double gendiff = allRecBin - fidRecBin;
    if(gendiff <= 0 || bdat->GetBinContent(i)-gendiff <= 0) printf("Bin %d totally efficient\n",i);
    //printf("dat(%2d) = %f -> ",i,bdat->GetBinContent(i));
    bdat->SetBinContent(i,TMath::Max(bdat->GetBinContent(i)-gendiff,0.0));
    //printf("%f\n",bdat->GetBinContent(i));
  }
  
  //cout << "test3: " << bdat->GetBinContent(10) << " : " << alternativeMCRecoSpectrum->GetBinContent(10) << "\n";
 
  printf("data: %f\n",bdat->GetSumOfWeights());
  printf("  DY: %f\n",bini->GetSumOfWeights());
  printf("  2D: %f\n",Adet->GetSumOfWeights());
  printf(" gen: %f\n",xini->GetSumOfWeights());


  //***************************************************
  //Induce Poisson Fluctuations on the histogram
  //***************************************************
  // for(int i=1; i<=alternativeMCRecoSpectrum->GetXaxis()->GetNbins(); i++) { 
  //   double PoissonMean = 1 / pow(alternativeMCRecoSpectrum->GetBinError(i) / alternativeMCRecoSpectrum->GetBinContent(i),2);
  //   double PoissonRandomNumber = rnd->Poisson(PoissonMean);
  //   double RandomizedBinContent = PoissonRandomNumber * ( alternativeMCRecoSpectrum->GetBinContent(i) / PoissonMean );

  //   cout << "bin : " << i << " : " << alternativeMCRecoSpectrum->GetBinContent(i) << " +/- " << alternativeMCRecoSpectrum->GetBinError(i) 
  // 	 << " : " << PoissonMean << " : " << PoissonRandomNumber << " --> " << RandomizedBinContent 
  // 	 << "\n";
     
  //   alternativeMCRecoSpectrum->SetBinContent(i,RandomizedBinContent);

  // }


  //*****************************
  //Do Unfolding
  //*****************************
  TUnfold::ERegMode regMode =TUnfold::kRegModeCurvature;
  //TUnfold::ERegMode regMode =TUnfold::kRegModeNone;
  // preserve the area (constrain)
  //TUnfold::EConstraint constraintMode=TUnfold::kEConstraintArea;
  TUnfold::EConstraint constraintMode=TUnfold::kEConstraintNone;
  TUnfoldDensity::EDensityMode densityFlags=TUnfoldDensity::kDensityModeBinWidth;

  TUnfoldDensity unfold(Adet,TUnfold::kHistMapOutputVert, regMode, constraintMode ,densityFlags);
  unfold.SetInput(alternativeMCRecoSpectrum);

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

  //TH1D *unfoldedDistribution = (TH1D*)bdat->Clone();
  //unfoldedDistribution->Reset();
  //unfold.GetOutput(unfoldedDistribution);
  TH1D *unfoldedDistribution = (TH1D*)unfold.GetOutput("unfold");

  // TH1D *x = (TH1D*)(unfold.GetOutput("x","myVariable",0,0));
  // TH2D *rhoij=unfold.GetRhoIJ("correlation","myVariable");

  //*****************************
  //divide by the bin width
  //*****************************
  unfoldedDistribution->Scale(1,"width");
  alternativeMCGenSpectrum->Scale(1,"width");
  xini->Scale(1,"width");
  alternativeMCRecoSpectrum->Scale(1,"width");
  bini->Scale(1,"width");
  bdat->Scale(1,"width");

  //*****************************
  //Make Nice Plots
  //*****************************
  TCanvas *cv = new TCanvas("Cv","cv", 800,800);
  cv->SetHighLightColor(2);
  cv->SetFillColor(0);
  cv->SetBorderMode(0);
  cv->SetBorderSize(2);
  cv->SetLeftMargin(0.16);
  cv->SetRightMargin(0.3);
  cv->SetTopMargin(0.07);
  cv->SetBottomMargin(0.12);
  cv->SetFrameBorderMode(0);  

  TPad *pad1 = new TPad("pad1","pad1", 0,0.25,1,1);
  pad1->SetBottomMargin(0.02);
  pad1->SetRightMargin(0.04);
  pad1->Draw();
  pad1->cd();
  pad1->SetLogx();

  TLegend *legend = new TLegend(0.60,0.70,0.90,0.84);
  legend->SetTextSize(0.04);
  legend->SetBorderSize(0);
  legend->SetFillStyle(0);
  legend->AddEntry(unfoldedDistribution, "Unfolded Spectrum");
  legend->AddEntry(alternativeMCGenSpectrum, "Generated Spectrum");

  unfoldedDistribution->SetStats(0);
  unfoldedDistribution->SetTitle("");
  unfoldedDistribution->GetXaxis()->SetLabelSize(0);
  unfoldedDistribution->SetLineWidth(2);
  unfoldedDistribution->Draw();
  alternativeMCGenSpectrum->Draw("same");
  alternativeMCGenSpectrum->SetLineColor(kRed);
  alternativeMCGenSpectrum->SetLineWidth(2);
  legend->Draw();
  printf("%f %f\n",unfoldedDistribution->GetSumOfWeights(),alternativeMCGenSpectrum->GetSumOfWeights());
  
  cv->cd();
  cv->Update();

  TPad *pad2 = new TPad("pad2","pad2", 0,0,1,0.25);
  pad2->SetTopMargin(0.01);
  pad2->SetBottomMargin(0.37);
  pad2->SetRightMargin(0.04);
  pad2->SetGridy();
  pad2->Draw();
  pad2->cd();
  pad2->SetLogx();

  TH1D *ratioPlot = (TH1D*)(alternativeMCGenSpectrum->Clone("ratioPlot"));
  for (int b=0; b<ratioPlot->GetXaxis()->GetNbins()+2; ++b) {
    double num = alternativeMCGenSpectrum->GetBinContent(b);
    double numErr = alternativeMCGenSpectrum->GetBinError(b);
    double den = unfoldedDistribution->GetBinContent(b);
    double denErr = unfoldedDistribution->GetBinError(b);
    ratioPlot->SetBinContent( b, num/den);
    ratioPlot->SetBinError( b, num/den * sqrt( pow(numErr/num,2) + pow(denErr/den,2)));   
  }
  ratioPlot->SetTitle("");
  ratioPlot->GetYaxis()->SetTitle("Ratio");
  ratioPlot->GetYaxis()->SetNdivisions(306);
  ratioPlot->GetYaxis()->SetTitleSize(0.10);
  ratioPlot->GetYaxis()->SetTitleOffset(0.3);
  ratioPlot->GetYaxis()->SetRangeUser(0.75,1.25);
  ratioPlot->GetYaxis()->SetLabelSize(0.10);
  ratioPlot->GetXaxis()->SetTitle("Z p_{T} [GeV/c]");
  ratioPlot->GetXaxis()->SetLabelSize(0.125);
  ratioPlot->GetXaxis()->SetTitleSize(0.15);
  ratioPlot->GetXaxis()->SetTitleOffset(1.1);
  ratioPlot->SetLineColor(kBlack);
  ratioPlot->SetMarkerStyle(20);      
  ratioPlot->SetMarkerSize(1);
  ratioPlot->SetStats(false);
  ratioPlot->Draw("pe");
  
  cv->SaveAs( Form("UnfoldingSystematicError%s_nsel%d_dy%d_rebin%d%s.gif",theHistName.Data(),nsel,whichDY,rebin,suffix.Data()));
  cout << "test: " << bdat->GetBinContent(10) << " : " << alternativeMCRecoSpectrum->GetBinContent(10) << "\n";

  //*****************************
  //Save Output
  //*****************************

  char output[100];
  sprintf(output,"UnfoldingSystematicError%s_nsel%d_dy%d_rebin%d%s.root",theHistName.Data(),nsel,whichDY,rebin,suffix.Data());

  TFile* outFilePlots = new TFile(output,"recreate");
  outFilePlots->cd();
  unfoldedDistribution->Write("unfoldedDistribution");
  alternativeMCGenSpectrum->Write("alternativeMCGenSpectrum");
  xini->Write("xini");
  alternativeMCRecoSpectrum->Write("alternativeMCRecoSpectrum");
  bini->Write("bini");
  bdat->Write("bdat");

  outFilePlots->Close();

}

void EstimateUnfoldingSystematics(TString theHistName = "Pt", TString suffix = "", int rebin=1){

  // Sanity Check
  //helper_function(0,1,rebin,theHistName.Data(),suffix.Data());

  // Madgraph LO
  helper_function(0,0,rebin,theHistName.Data(),suffix.Data());
  helper_function(1,0,rebin,theHistName.Data(),suffix.Data());
  
  // // // POWHEG NLO
  //helper_function(0,2,rebin,theHistName.Data(),suffix.Data());
  //helper_function(1,2,rebin,theHistName.Data(),suffix.Data());

}
