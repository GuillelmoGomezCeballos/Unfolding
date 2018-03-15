// compares inclusive ZpT spectra between di-electron and di-muon channels using BLUE method 
// https://www.sciencedirect.com/science/article/pii/S0168900203003292
//
// in case of 0 correlation between channels, the Chi2 is calculated by
//
// (VecEE - blue)^T * CovEE^{-1} * (VecEE - blue) + 
// (VecMM - blue)^T * CovMM^{-1} * (VecMM - blue) 
//
// and this is minimized by solving d(Chi2)/d(blue) = 0, such that
//
// blue = (CovEE^{-1} + CovMM^{-1})^{-1} * (CovEE^{-1} * VecEE + CovMM^{-1} * VecMM)
//
// then the minimum Chi2 is calculated by plugging in this vector into the above formula
//
// general case: Chi2 = (VecObs - A * VecBlue)^T * CovObs^{-1} * (VecObs - A * VecBlue)
// and VecBlue = (A^T * CovObs^{-1} * A)^{-1} * A^T * CovObvs^{-1} * VecObs

#include "TROOT.h"
#include "TInterpreter.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TH1.h"
#include "TH2.h"
#include "TStyle.h"
#include "TPad.h"
#include "Math/SVector.h"
#include "Math/SMatrix.h"
#include "TMath.h"
#include "TGraphAsymmErrors.h"
#include "TSystem.h"
#include "TLegend.h"
#include <iostream>


void chiSqTest_EE_vs_MM(bool doNorms=false) {

  TFile *fMM_nom = new TFile("/afs/cern.ch/user/c/ceballos/public/zpt/outputs/histoUnfolding_XSRatioSystPt_nsel0_dy3_rebin1_default.root","read");
  TH1D *hMM_nom = (TH1D*) fMM_nom->Get("unfoldNoLumi");

  TFile *fEE_nom = new TFile("/afs/cern.ch/user/c/ceballos/public/zpt/outputs/histoUnfolding_XSRatioSystPt_nsel1_dy3_rebin1_default.root","read");
  TH1D *hEE_nom = (TH1D*) fEE_nom->Get("unfoldNoLumi");

  TFile *fMM_cov = new TFile("/afs/cern.ch/user/c/ceballos/public/zpt/output_root/matrix03.root", "read");
  TH2D *hMM_cov = (TH2D*) fMM_cov->Get("covariance_totsum_0");
  
  TFile *fEE_cov = new TFile("/afs/cern.ch/user/c/ceballos/public/zpt/output_root/matrix13.root", "read");
  TH2D *hEE_cov = (TH2D*) fEE_cov->Get("covariance_totsum_1");

  assert(hEE_cov->GetNbinsX() == hEE_cov->GetNbinsY());
  assert(hMM_cov->GetNbinsX() == hMM_cov->GetNbinsY());
  assert(hEE_cov->GetNbinsX() == hMM_cov->GetNbinsX());
  assert(hEE_nom->GetNbinsX() == hMM_nom->GetNbinsX());
  assert(hEE_nom->GetNbinsX() == hEE_cov->GetNbinsX());

  //hard coded because ROOT
  static const uint nBins=36;//hEE_cov->GetNbinsX();

  ROOT::Math::SVector<double, nBins>VecEE;
  ROOT::Math::SVector<double, nBins>VecMM;
  ROOT::Math::SMatrix<double, nBins, nBins>CovEE;
  ROOT::Math::SMatrix<double, nBins, nBins>CovMM;

  double totEE=0, totMM=0;

  for (uint i=1; i<=nBins; i++) {
    VecEE(i-1) = hEE_nom->GetBinContent(i);
    totEE+=hEE_nom->GetBinContent(i);
    VecMM(i-1) = hMM_nom->GetBinContent(i);
    totMM+=hMM_nom->GetBinContent(i);
    for (uint j=1; j<=nBins; j++) {
      CovEE(i-1,j-1) = hEE_cov->GetBinContent(i,j)*hEE_nom->GetBinContent(i)*hEE_nom->GetBinContent(j);
      CovMM(i-1,j-1) = hMM_cov->GetBinContent(i,j)*hMM_nom->GetBinContent(i)*hMM_nom->GetBinContent(j);
      //cout << "( " << i << ", " << j << " ) = " << CovMM(i-1, j-1) << ", " << hMM_cov->GetBinContent(i,j) << endl;
    }
  }

  if (doNorms==true) {
    VecEE/=totEE;
    VecMM/=totMM;
  }

  bool ret = CovEE.Invert();assert(ret);
  ret = CovMM.Invert();assert(ret);

  ROOT::Math::SMatrix<double, nBins, nBins>CovTot = CovEE+CovMM;
  ret = CovTot.Invert();assert(ret);

  ROOT::Math::SVector<double, nBins> temp = CovEE * VecEE + CovMM * VecMM;

  ROOT::Math::SVector<double, nBins> blue = CovTot * temp;

  ROOT::Math::SVector<double, nBins> resid1 = CovEE * ( VecEE - blue );
  ROOT::Math::SVector<double, nBins> resid2 = CovMM * ( VecMM - blue );

  double chi2 = ROOT::Math::Dot( (VecEE - blue), resid1 ) + ROOT::Math::Dot( (VecMM - blue), resid2 );

  std::cout << chi2 << ", " << TMath::Prob(chi2, 36) << endl;

}
