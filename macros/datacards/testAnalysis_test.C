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

void testAnalysis_test(int nsel=0, int DY=3, int alt=0, TString theHistName = "Pt"){

  TString chanName = "mm";
  if(nsel == 1) chanName = "ee";

  const int nChan = 7;
  const int nReco = 14;

  Double_t lumiE = 1.025;

  TString path="../inputsCards200/";
  TFile* _file0    = new TFile(Form("%shistoDY%dzll%sRecGen.root",path.Data(),DY,theHistName.Data()),  "read"); if(!_file0   ) {printf("File does not exist\n"); return;}
  TFile* _file_alt = new TFile(Form("%shistoDY%dzll%sRecGen.root",path.Data(),alt,theHistName.Data()), "read"); if(!_file_alt) {printf("File does not exist\n"); return;}

  TH1D* hDA  = (TH1D*)_file0->Get(Form("histo%sRecDA_%d",theHistName.Data(),nsel));
  TH1D* hRes = (TH1D*)_file0->Get(Form("histo%sRecEM_%d",theHistName.Data(),nsel));
  TH1D* hVV  = (TH1D*)_file0->Get(Form("histo%sRecVV_%d",theHistName.Data(),nsel));

  TH1D* hDY  = (TH1D*)_file0->Get(Form("histo%sRecDY_%d",theHistName.Data(),nsel));
  TH2D* Adet = (TH2D*)_file0->Get(Form("histo%sRecGen_%d",theHistName.Data(),nsel));

  TH1D* hVV_PDF =(TH1D*) _file0->Get(Form("histo%sRecVV_PDF_%d",theHistName.Data(),nsel));
  TH1D* hVV_QCD =(TH1D*) _file0->Get(Form("histo%sRecVV_QCD_%d",theHistName.Data(),nsel));

  TH1D* hDY_alt  = (TH1D*)_file_alt->Get(Form("histo%sRecDY_%d",theHistName.Data(),nsel));
  TH2D* Adet_alt = (TH2D*)_file_alt->Get(Form("histo%sRecGen_%d",theHistName.Data(),nsel));

  TH1D* hVV_MomRes1  = (TH1D*)_file0->Get(Form("histo%sRecVV_MomRes_%d_1",theHistName.Data(),nsel));
  TH1D* hDY_MomRes1  = (TH1D*)_file0->Get(Form("histo%sRecDY_MomRes_%d_1",theHistName.Data(),nsel));
  TH2D* Adet_MomRes1 = (TH2D*)_file0->Get(Form("histo%sRecGen_MomRes_%d_1",theHistName.Data(),nsel));
  TH1D* hVV_MomRes2  = (TH1D*)_file0->Get(Form("histo%sRecVV_MomRes_%d_2",theHistName.Data(),nsel));
  TH1D* hDY_MomRes2  = (TH1D*)_file0->Get(Form("histo%sRecDY_MomRes_%d_2",theHistName.Data(),nsel));
  TH2D* Adet_MomRes2 = (TH2D*)_file0->Get(Form("histo%sRecGen_MomRes_%d_2",theHistName.Data(),nsel));
  TH1D* hVV_MomRes3  = (TH1D*)_file0->Get(Form("histo%sRecVV_MomRes_%d_3",theHistName.Data(),nsel));
  TH1D* hDY_MomRes3  = (TH1D*)_file0->Get(Form("histo%sRecDY_MomRes_%d_3",theHistName.Data(),nsel));
  TH2D* Adet_MomRes3 = (TH2D*)_file0->Get(Form("histo%sRecGen_MomRes_%d_3",theHistName.Data(),nsel));
  TH1D* hVV_MomRes4  = (TH1D*)_file0->Get(Form("histo%sRecVV_MomRes_%d_4",theHistName.Data(),nsel));
  TH1D* hDY_MomRes4  = (TH1D*)_file0->Get(Form("histo%sRecDY_MomRes_%d_4",theHistName.Data(),nsel));
  TH2D* Adet_MomRes4 = (TH2D*)_file0->Get(Form("histo%sRecGen_MomRes_%d_4",theHistName.Data(),nsel));

  TH1D* hVV_LepEff1  = (TH1D*)_file0->Get(Form("histo%sRecVV_LepEff_%d_1",theHistName.Data(),nsel));
  TH1D* hDY_LepEff1  = (TH1D*)_file0->Get(Form("histo%sRecDY_LepEff_%d_1",theHistName.Data(),nsel));
  TH2D* Adet_LepEff1 = (TH2D*)_file0->Get(Form("histo%sRecGen_LepEff_%d_1",theHistName.Data(),nsel));
  TH1D* hVV_LepEff2  = (TH1D*)_file0->Get(Form("histo%sRecVV_LepEff_%d_2",theHistName.Data(),nsel));
  TH1D* hDY_LepEff2  = (TH1D*)_file0->Get(Form("histo%sRecDY_LepEff_%d_2",theHistName.Data(),nsel));
  TH2D* Adet_LepEff2 = (TH2D*)_file0->Get(Form("histo%sRecGen_LepEff_%d_2",theHistName.Data(),nsel));
  TH1D* hVV_LepEff3  = (TH1D*)_file0->Get(Form("histo%sRecVV_LepEff_%d_3",theHistName.Data(),nsel));
  TH1D* hDY_LepEff3  = (TH1D*)_file0->Get(Form("histo%sRecDY_LepEff_%d_3",theHistName.Data(),nsel));
  TH2D* Adet_LepEff3 = (TH2D*)_file0->Get(Form("histo%sRecGen_LepEff_%d_3",theHistName.Data(),nsel));
  TH1D* hVV_LepEff4  = (TH1D*)_file0->Get(Form("histo%sRecVV_LepEff_%d_4",theHistName.Data(),nsel));
  TH1D* hDY_LepEff4  = (TH1D*)_file0->Get(Form("histo%sRecDY_LepEff_%d_4",theHistName.Data(),nsel));
  TH2D* Adet_LepEff4 = (TH2D*)_file0->Get(Form("histo%sRecGen_LepEff_%d_4",theHistName.Data(),nsel));
  TH1D* hVV_LepEff5  = (TH1D*)_file0->Get(Form("histo%sRecVV_LepEff_%d_5",theHistName.Data(),nsel));
  TH1D* hDY_LepEff5  = (TH1D*)_file0->Get(Form("histo%sRecDY_LepEff_%d_5",theHistName.Data(),nsel));
  TH2D* Adet_LepEff5 = (TH2D*)_file0->Get(Form("histo%sRecGen_LepEff_%d_5",theHistName.Data(),nsel));
  TH1D* hVV_LepEff6  = (TH1D*)_file0->Get(Form("histo%sRecVV_LepEff_%d_6",theHistName.Data(),nsel));
  TH1D* hDY_LepEff6  = (TH1D*)_file0->Get(Form("histo%sRecDY_LepEff_%d_6",theHistName.Data(),nsel));
  TH2D* Adet_LepEff6 = (TH2D*)_file0->Get(Form("histo%sRecGen_LepEff_%d_6",theHistName.Data(),nsel));
  TH1D* hVV_LepEff7  = (TH1D*)_file0->Get(Form("histo%sRecVV_LepEff_%d_7",theHistName.Data(),nsel));
  TH1D* hDY_LepEff7  = (TH1D*)_file0->Get(Form("histo%sRecDY_LepEff_%d_7",theHistName.Data(),nsel));
  TH2D* Adet_LepEff7 = (TH2D*)_file0->Get(Form("histo%sRecGen_LepEff_%d_7",theHistName.Data(),nsel));

  TH1D* hVV_RecEff  = (TH1D*)_file0->Get(Form("histo%sRecVV_RecEff_%d_0",theHistName.Data(),nsel));
  TH1D* hDY_RecEff  = (TH1D*)_file0->Get(Form("histo%sRecDY_RecEff_%d_0",theHistName.Data(),nsel));
  TH2D* Adet_RecEff = (TH2D*)_file0->Get(Form("histo%sRecGen_RecEff_%d_0",theHistName.Data(),nsel));

  TH1D* histo_Data   = (TH1D*)hDA->Clone("histo_Data");
  TH1D* histo_Res    = (TH1D*)hRes->Clone("histo_Res");
  TH1D* histo_VV     = (TH1D*)hVV->Clone("histo_VV");

  TH1D* histo_VV_vvNormPDFUp   = (TH1D*)hVV->Clone(Form("histo_VV_vvNormPDFUp"));                    histo_VV_vvNormPDFUp  ->Reset();
  TH1D* histo_VV_vvNormPDFDown = (TH1D*)hVV->Clone(Form("histo_VV_vvNormPDFDown"));                  histo_VV_vvNormPDFDown->Reset();
  TH1D* histo_VV_vvNormQCDUp   = (TH1D*)hVV->Clone(Form("histo_VV_vvNormQCDUp"));                    histo_VV_vvNormQCDUp  ->Reset();
  TH1D* histo_VV_vvNormQCDDown = (TH1D*)hVV->Clone(Form("histo_VV_vvNormQCDDown"));                  histo_VV_vvNormQCDDown->Reset();
  TH1D* histo_VV_MomRes1Up     = (TH1D*)hVV->Clone(Form("histo_VV_MomRes1%sUp",chanName.Data()));    histo_VV_MomRes1Up    ->Reset();
  TH1D* histo_VV_MomRes1Down   = (TH1D*)hVV->Clone(Form("histo_VV_MomRes1%sDown",chanName.Data()));  histo_VV_MomRes1Down  ->Reset();
  TH1D* histo_VV_MomRes2Up     = (TH1D*)hVV->Clone(Form("histo_VV_MomRes2%sUp",chanName.Data()));    histo_VV_MomRes2Up    ->Reset();
  TH1D* histo_VV_MomRes2Down   = (TH1D*)hVV->Clone(Form("histo_VV_MomRes2%sDown",chanName.Data()));  histo_VV_MomRes2Down  ->Reset();
  TH1D* histo_VV_MomRes3Up     = (TH1D*)hVV->Clone(Form("histo_VV_MomRes3%sUp",chanName.Data()));    histo_VV_MomRes3Up    ->Reset();
  TH1D* histo_VV_MomRes3Down   = (TH1D*)hVV->Clone(Form("histo_VV_MomRes3%sDown",chanName.Data()));  histo_VV_MomRes3Down  ->Reset();
  TH1D* histo_VV_MomRes4Up     = (TH1D*)hVV->Clone(Form("histo_VV_MomRes4%sUp",chanName.Data()));    histo_VV_MomRes4Up    ->Reset();
  TH1D* histo_VV_MomRes4Down   = (TH1D*)hVV->Clone(Form("histo_VV_MomRes4%sDown",chanName.Data()));  histo_VV_MomRes4Down  ->Reset();
  TH1D* histo_VV_LepEff1Up     = (TH1D*)hVV->Clone(Form("histo_VV_LepEff1%sUp",chanName.Data()));    histo_VV_LepEff1Up    ->Reset();
  TH1D* histo_VV_LepEff1Down   = (TH1D*)hVV->Clone(Form("histo_VV_LepEff1%sDown",chanName.Data()));  histo_VV_LepEff1Down  ->Reset();
  TH1D* histo_VV_LepEff2Up     = (TH1D*)hVV->Clone(Form("histo_VV_LepEff2%sUp",chanName.Data()));    histo_VV_LepEff2Up    ->Reset();
  TH1D* histo_VV_LepEff2Down   = (TH1D*)hVV->Clone(Form("histo_VV_LepEff2%sDown",chanName.Data()));  histo_VV_LepEff2Down  ->Reset();
  TH1D* histo_VV_LepEff3Up     = (TH1D*)hVV->Clone(Form("histo_VV_LepEff3%sUp",chanName.Data()));    histo_VV_LepEff3Up    ->Reset();
  TH1D* histo_VV_LepEff3Down   = (TH1D*)hVV->Clone(Form("histo_VV_LepEff3%sDown",chanName.Data()));  histo_VV_LepEff3Down  ->Reset();
  TH1D* histo_VV_LepEff4Up     = (TH1D*)hVV->Clone(Form("histo_VV_LepEff4%sUp",chanName.Data()));    histo_VV_LepEff4Up    ->Reset();
  TH1D* histo_VV_LepEff4Down   = (TH1D*)hVV->Clone(Form("histo_VV_LepEff4%sDown",chanName.Data()));  histo_VV_LepEff4Down  ->Reset();
  TH1D* histo_VV_LepEff5Up     = (TH1D*)hVV->Clone(Form("histo_VV_LepEff5%sUp",chanName.Data()));    histo_VV_LepEff5Up    ->Reset();
  TH1D* histo_VV_LepEff5Down   = (TH1D*)hVV->Clone(Form("histo_VV_LepEff5%sDown",chanName.Data()));  histo_VV_LepEff5Down  ->Reset();
  TH1D* histo_VV_LepEff6Up     = (TH1D*)hVV->Clone(Form("histo_VV_LepEff6%sUp",chanName.Data()));    histo_VV_LepEff6Up    ->Reset();
  TH1D* histo_VV_LepEff6Down   = (TH1D*)hVV->Clone(Form("histo_VV_LepEff6%sDown",chanName.Data()));  histo_VV_LepEff6Down  ->Reset();
  TH1D* histo_VV_LepEff7Up     = (TH1D*)hVV->Clone(Form("histo_VV_LepEff7%sUp",chanName.Data()));    histo_VV_LepEff7Up    ->Reset();
  TH1D* histo_VV_LepEff7Down   = (TH1D*)hVV->Clone(Form("histo_VV_LepEff7%sDown",chanName.Data()));  histo_VV_LepEff7Down  ->Reset();
  TH1D* histo_VV_RecEffUp      = (TH1D*)hVV->Clone(Form("histo_VV_RecEff%sUp",chanName.Data()));     histo_VV_RecEffUp     ->Reset();
  TH1D* histo_VV_RecEffDown    = (TH1D*)hVV->Clone(Form("histo_VV_RecEff%sDown",chanName.Data()));   histo_VV_RecEffDown   ->Reset();

  TH1D* histo_NonFid = (TH1D*)hDA->Clone("histo_NonFid"); histo_NonFid->Reset();
  TH1D* histo_DY[nChan];
  for(int i=0; i<nChan; i++) {  
    histo_DY[i] = (TH1D*)hDA->Clone(Form("histo_DY_%d",i)); histo_DY[i]->Reset();
  }

  TH1D* histo_VV_VVStatUp  [nReco];
  TH1D* histo_VV_VVStatDown[nReco];
  TH1D* histo_Res_ResStatUp  [nReco];
  TH1D* histo_Res_ResStatDown[nReco];
  TH1D* histo_NonFid_NonFidStatUp  [nReco];
  TH1D* histo_NonFid_NonFidStatDown[nReco];
  TH1D* histo_DY_DYStatUp  [nChan][nReco];
  TH1D* histo_DY_DYStatDown[nChan][nReco];
  for(int i=0; i<nReco; i++) {  
    histo_VV_VVStatUp  [i] = (TH1D*)hVV->Clone(Form("histo_VV_VVStat_%d%sUp",i,chanName.Data()));   histo_VV_VVStatUp  [i]->Reset();
    histo_VV_VVStatDown[i] = (TH1D*)hVV->Clone(Form("histo_VV_VVStat_%d%sDown",i,chanName.Data())); histo_VV_VVStatDown[i]->Reset();
    histo_Res_ResStatUp  [i] = (TH1D*)hVV->Clone(Form("histo_Res_ResStat_%d%sUp",i,chanName.Data()));   histo_Res_ResStatUp  [i]->Reset();
    histo_Res_ResStatDown[i] = (TH1D*)hVV->Clone(Form("histo_Res_ResStat_%d%sDown",i,chanName.Data())); histo_Res_ResStatDown[i]->Reset();
    histo_NonFid_NonFidStatUp  [i] = (TH1D*)hVV->Clone(Form("histo_NonFid_NonFidStat_%d%sUp",i,chanName.Data()));	histo_NonFid_NonFidStatUp    [i]->Reset();
    histo_NonFid_NonFidStatDown[i] = (TH1D*)hVV->Clone(Form("histo_NonFid_NonFidStat_%d%sDown",i,chanName.Data()));     histo_NonFid_NonFidStatDown[i]->Reset();
    for(int j=0; j<nChan; j++) {  
      histo_DY_DYStatUp  [j][i] = (TH1D*)hVV->Clone(Form("histo_DY_%d_DYStat_%d_%d%sUp",j,j,i,chanName.Data()));   histo_DY_DYStatUp  [j][i]->Reset();
      histo_DY_DYStatDown[j][i] = (TH1D*)hVV->Clone(Form("histo_DY_%d_DYStat_%d_%d%sDown",j,j,i,chanName.Data())); histo_DY_DYStatDown[j][i]->Reset();
    }
  }

  TH1D* histo_NonFid_altUp   = (TH1D*)hDA->Clone("histo_NonFid_altUp");   histo_NonFid_altUp  ->Reset();
  TH1D* histo_NonFid_altDown = (TH1D*)hDA->Clone("histo_NonFid_altDown"); histo_NonFid_altDown->Reset();
  TH1D* histo_DY_altUp  [nChan];
  TH1D* histo_DY_altDown[nChan];
  TH1D* histo_NonFid_MomRes1Up   = (TH1D*)hDA->Clone(Form("histo_NonFid_MomRes1%sUp",chanName.Data()));   histo_NonFid_MomRes1Up  ->Reset();
  TH1D* histo_NonFid_MomRes1Down = (TH1D*)hDA->Clone(Form("histo_NonFid_MomRes1%sDown",chanName.Data())); histo_NonFid_MomRes1Down->Reset();
  TH1D* histo_NonFid_MomRes2Up   = (TH1D*)hDA->Clone(Form("histo_NonFid_MomRes2%sUp",chanName.Data()));   histo_NonFid_MomRes2Up  ->Reset();
  TH1D* histo_NonFid_MomRes2Down = (TH1D*)hDA->Clone(Form("histo_NonFid_MomRes2%sDown",chanName.Data())); histo_NonFid_MomRes2Down->Reset();
  TH1D* histo_NonFid_MomRes3Up   = (TH1D*)hDA->Clone(Form("histo_NonFid_MomRes3%sUp",chanName.Data()));   histo_NonFid_MomRes3Up  ->Reset();
  TH1D* histo_NonFid_MomRes3Down = (TH1D*)hDA->Clone(Form("histo_NonFid_MomRes3%sDown",chanName.Data())); histo_NonFid_MomRes3Down->Reset();
  TH1D* histo_NonFid_MomRes4Up   = (TH1D*)hDA->Clone(Form("histo_NonFid_MomRes4%sUp",chanName.Data()));   histo_NonFid_MomRes4Up  ->Reset();
  TH1D* histo_NonFid_MomRes4Down = (TH1D*)hDA->Clone(Form("histo_NonFid_MomRes4%sDown",chanName.Data())); histo_NonFid_MomRes4Down->Reset();
  TH1D* histo_DY_MomRes1Up  [nChan];
  TH1D* histo_DY_MomRes1Down[nChan];
  TH1D* histo_DY_MomRes2Up  [nChan];
  TH1D* histo_DY_MomRes2Down[nChan];
  TH1D* histo_DY_MomRes3Up  [nChan];
  TH1D* histo_DY_MomRes3Down[nChan];
  TH1D* histo_DY_MomRes4Up  [nChan];
  TH1D* histo_DY_MomRes4Down[nChan];
  TH1D* histo_NonFid_LepEff1Up   = (TH1D*)hDA->Clone(Form("histo_NonFid_LepEff1%sUp",chanName.Data()));   histo_NonFid_LepEff1Up  ->Reset();
  TH1D* histo_NonFid_LepEff1Down = (TH1D*)hDA->Clone(Form("histo_NonFid_LepEff1%sDown",chanName.Data())); histo_NonFid_LepEff1Down->Reset();
  TH1D* histo_NonFid_LepEff2Up   = (TH1D*)hDA->Clone(Form("histo_NonFid_LepEff2%sUp",chanName.Data()));   histo_NonFid_LepEff2Up  ->Reset();
  TH1D* histo_NonFid_LepEff2Down = (TH1D*)hDA->Clone(Form("histo_NonFid_LepEff2%sDown",chanName.Data())); histo_NonFid_LepEff2Down->Reset();
  TH1D* histo_NonFid_LepEff3Up   = (TH1D*)hDA->Clone(Form("histo_NonFid_LepEff3%sUp",chanName.Data()));   histo_NonFid_LepEff3Up  ->Reset();
  TH1D* histo_NonFid_LepEff3Down = (TH1D*)hDA->Clone(Form("histo_NonFid_LepEff3%sDown",chanName.Data())); histo_NonFid_LepEff3Down->Reset();
  TH1D* histo_NonFid_LepEff4Up   = (TH1D*)hDA->Clone(Form("histo_NonFid_LepEff4%sUp",chanName.Data()));   histo_NonFid_LepEff4Up  ->Reset();
  TH1D* histo_NonFid_LepEff4Down = (TH1D*)hDA->Clone(Form("histo_NonFid_LepEff4%sDown",chanName.Data())); histo_NonFid_LepEff4Down->Reset();
  TH1D* histo_NonFid_LepEff5Up   = (TH1D*)hDA->Clone(Form("histo_NonFid_LepEff5%sUp",chanName.Data()));   histo_NonFid_LepEff5Up  ->Reset();
  TH1D* histo_NonFid_LepEff5Down = (TH1D*)hDA->Clone(Form("histo_NonFid_LepEff5%sDown",chanName.Data())); histo_NonFid_LepEff5Down->Reset();
  TH1D* histo_NonFid_LepEff6Up   = (TH1D*)hDA->Clone(Form("histo_NonFid_LepEff6%sUp",chanName.Data()));   histo_NonFid_LepEff6Up  ->Reset();
  TH1D* histo_NonFid_LepEff6Down = (TH1D*)hDA->Clone(Form("histo_NonFid_LepEff6%sDown",chanName.Data())); histo_NonFid_LepEff6Down->Reset();
  TH1D* histo_NonFid_LepEff7Up   = (TH1D*)hDA->Clone(Form("histo_NonFid_LepEff7%sUp",chanName.Data()));   histo_NonFid_LepEff7Up  ->Reset();
  TH1D* histo_NonFid_LepEff7Down = (TH1D*)hDA->Clone(Form("histo_NonFid_LepEff7%sDown",chanName.Data())); histo_NonFid_LepEff7Down->Reset();
  TH1D* histo_DY_LepEff1Up  [nChan];
  TH1D* histo_DY_LepEff1Down[nChan];
  TH1D* histo_DY_LepEff2Up  [nChan];
  TH1D* histo_DY_LepEff2Down[nChan];
  TH1D* histo_DY_LepEff3Up  [nChan];
  TH1D* histo_DY_LepEff3Down[nChan];
  TH1D* histo_DY_LepEff4Up  [nChan];
  TH1D* histo_DY_LepEff4Down[nChan];
  TH1D* histo_DY_LepEff5Up  [nChan];
  TH1D* histo_DY_LepEff5Down[nChan];
  TH1D* histo_DY_LepEff6Up  [nChan];
  TH1D* histo_DY_LepEff6Down[nChan];
  TH1D* histo_DY_LepEff7Up  [nChan];
  TH1D* histo_DY_LepEff7Down[nChan];
  TH1D* histo_NonFid_RecEffUp   = (TH1D*)hDA->Clone(Form("histo_NonFid_RecEff%sUp",chanName.Data()));	histo_NonFid_RecEffUp  ->Reset();
  TH1D* histo_NonFid_RecEffDown = (TH1D*)hDA->Clone(Form("histo_NonFid_RecEff%sDown",chanName.Data())); histo_NonFid_RecEffDown->Reset();
  TH1D* histo_DY_RecEffUp  [nChan];
  TH1D* histo_DY_RecEffDown[nChan];
  for(int i=0; i<nChan; i++) {
    histo_DY_altUp  [i] = (TH1D*)hDA->Clone(Form("histo_DY_%d_altUp",i));   histo_DY_altUp  [i]->Reset();
    histo_DY_altDown[i] = (TH1D*)hDA->Clone(Form("histo_DY_%d_altDown",i)); histo_DY_altDown[i]->Reset();
    histo_DY_MomRes1Up  [i] = (TH1D*)hDA->Clone(Form("histo_DY_%d_MomRes1%sUp",i,chanName.Data()));   histo_DY_MomRes1Up  [i]->Reset();
    histo_DY_MomRes1Down[i] = (TH1D*)hDA->Clone(Form("histo_DY_%d_MomRes1%sDown",i,chanName.Data())); histo_DY_MomRes1Down[i]->Reset();
    histo_DY_MomRes2Up  [i] = (TH1D*)hDA->Clone(Form("histo_DY_%d_MomRes2%sUp",i,chanName.Data()));   histo_DY_MomRes2Up  [i]->Reset();
    histo_DY_MomRes2Down[i] = (TH1D*)hDA->Clone(Form("histo_DY_%d_MomRes2%sDown",i,chanName.Data())); histo_DY_MomRes2Down[i]->Reset();
    histo_DY_MomRes3Up  [i] = (TH1D*)hDA->Clone(Form("histo_DY_%d_MomRes3%sUp",i,chanName.Data()));   histo_DY_MomRes3Up  [i]->Reset();
    histo_DY_MomRes3Down[i] = (TH1D*)hDA->Clone(Form("histo_DY_%d_MomRes3%sDown",i,chanName.Data())); histo_DY_MomRes3Down[i]->Reset();
    histo_DY_MomRes4Up  [i] = (TH1D*)hDA->Clone(Form("histo_DY_%d_MomRes4%sUp",i,chanName.Data()));   histo_DY_MomRes4Up  [i]->Reset();
    histo_DY_MomRes4Down[i] = (TH1D*)hDA->Clone(Form("histo_DY_%d_MomRes4%sDown",i,chanName.Data())); histo_DY_MomRes4Down[i]->Reset();
    histo_DY_LepEff1Up  [i] = (TH1D*)hDA->Clone(Form("histo_DY_%d_LepEff1%sUp",i,chanName.Data()));   histo_DY_LepEff1Up  [i]->Reset();
    histo_DY_LepEff1Down[i] = (TH1D*)hDA->Clone(Form("histo_DY_%d_LepEff1%sDown",i,chanName.Data())); histo_DY_LepEff1Down[i]->Reset();
    histo_DY_LepEff2Up  [i] = (TH1D*)hDA->Clone(Form("histo_DY_%d_LepEff2%sUp",i,chanName.Data()));   histo_DY_LepEff2Up  [i]->Reset();
    histo_DY_LepEff2Down[i] = (TH1D*)hDA->Clone(Form("histo_DY_%d_LepEff2%sDown",i,chanName.Data())); histo_DY_LepEff2Down[i]->Reset();
    histo_DY_LepEff3Up  [i] = (TH1D*)hDA->Clone(Form("histo_DY_%d_LepEff3%sUp",i,chanName.Data()));   histo_DY_LepEff3Up  [i]->Reset();
    histo_DY_LepEff3Down[i] = (TH1D*)hDA->Clone(Form("histo_DY_%d_LepEff3%sDown",i,chanName.Data())); histo_DY_LepEff3Down[i]->Reset();
    histo_DY_LepEff4Up  [i] = (TH1D*)hDA->Clone(Form("histo_DY_%d_LepEff4%sUp",i,chanName.Data()));   histo_DY_LepEff4Up  [i]->Reset();
    histo_DY_LepEff4Down[i] = (TH1D*)hDA->Clone(Form("histo_DY_%d_LepEff4%sDown",i,chanName.Data())); histo_DY_LepEff4Down[i]->Reset();
    histo_DY_LepEff5Up  [i] = (TH1D*)hDA->Clone(Form("histo_DY_%d_LepEff5%sUp",i,chanName.Data()));   histo_DY_LepEff5Up  [i]->Reset();
    histo_DY_LepEff5Down[i] = (TH1D*)hDA->Clone(Form("histo_DY_%d_LepEff5%sDown",i,chanName.Data())); histo_DY_LepEff5Down[i]->Reset();
    histo_DY_LepEff6Up  [i] = (TH1D*)hDA->Clone(Form("histo_DY_%d_LepEff6%sUp",i,chanName.Data()));   histo_DY_LepEff6Up  [i]->Reset();
    histo_DY_LepEff6Down[i] = (TH1D*)hDA->Clone(Form("histo_DY_%d_LepEff6%sDown",i,chanName.Data())); histo_DY_LepEff6Down[i]->Reset();
    histo_DY_LepEff7Up  [i] = (TH1D*)hDA->Clone(Form("histo_DY_%d_LepEff7%sUp",i,chanName.Data()));   histo_DY_LepEff7Up  [i]->Reset();
    histo_DY_LepEff7Down[i] = (TH1D*)hDA->Clone(Form("histo_DY_%d_LepEff7%sDown",i,chanName.Data())); histo_DY_LepEff7Down[i]->Reset();
    histo_DY_RecEffUp  [i]  = (TH1D*)hDA->Clone(Form("histo_DY_%d_RecEff%sUp",i,chanName.Data()));    histo_DY_RecEffUp   [i]->Reset();
    histo_DY_RecEffDown[i]  = (TH1D*)hDA->Clone(Form("histo_DY_%d_RecEff%sDown",i,chanName.Data()));  histo_DY_RecEffDown [i]->Reset();
  }

  if(nChan != Adet->GetNbinsY()) {printf("number of nChan and GEN bins different: %d vs. %d\n",nChan,Adet->GetNbinsY()); return;}
  if(nReco != Adet->GetNbinsX()) {printf("number of nReco and RECO bins different: %d vs. %d\n",nReco,Adet->GetNbinsX()); return;}

  double diff;
  for(int i=1; i<=Adet->GetNbinsX(); i++) { // RECO
    // VV uncertainties
    if(hVV->GetBinContent(i) > 0){
      diff = hVV_PDF->GetBinContent(i)-hVV->GetBinContent(i);
      histo_VV_vvNormPDFUp  ->SetBinContent(i,TMath::Max(hVV->GetBinContent(i)+diff,0.0));
      histo_VV_vvNormPDFDown->SetBinContent(i,TMath::Max(hVV->GetBinContent(i)-diff,0.0));

      diff = hVV_QCD->GetBinContent(i)-hVV->GetBinContent(i);
      histo_VV_vvNormQCDUp  ->SetBinContent(i,TMath::Max(hVV->GetBinContent(i)+diff,0.0));
      histo_VV_vvNormQCDDown->SetBinContent(i,TMath::Max(hVV->GetBinContent(i)-diff,0.0));     

      diff = hVV_MomRes1->GetBinContent(i)-hVV->GetBinContent(i);
      histo_VV_MomRes1Up  ->SetBinContent(i,TMath::Max(hVV->GetBinContent(i)+diff,0.0));
      histo_VV_MomRes1Down->SetBinContent(i,TMath::Max(hVV->GetBinContent(i)-diff,0.0));     

      diff = hVV_MomRes2->GetBinContent(i)-hVV->GetBinContent(i);
      histo_VV_MomRes2Up  ->SetBinContent(i,TMath::Max(hVV->GetBinContent(i)+diff,0.0));
      histo_VV_MomRes2Down->SetBinContent(i,TMath::Max(hVV->GetBinContent(i)-diff,0.0));     

      diff = hVV_MomRes3->GetBinContent(i)-hVV->GetBinContent(i);
      if(nsel == 1) diff = 0.0;
      histo_VV_MomRes3Up  ->SetBinContent(i,TMath::Max(hVV->GetBinContent(i)+diff,0.0));
      histo_VV_MomRes3Down->SetBinContent(i,TMath::Max(hVV->GetBinContent(i)-diff,0.0));     

      diff = hVV_MomRes4->GetBinContent(i)-hVV->GetBinContent(i);
      if(nsel == 1) diff = 0.0;
      histo_VV_MomRes4Up  ->SetBinContent(i,TMath::Max(hVV->GetBinContent(i)+diff,0.0));
      histo_VV_MomRes4Down->SetBinContent(i,TMath::Max(hVV->GetBinContent(i)-diff,0.0));     

      diff = hVV_LepEff1->GetBinContent(i)-hVV->GetBinContent(i);
      histo_VV_LepEff1Up  ->SetBinContent(i,TMath::Max(hVV->GetBinContent(i)+diff,0.0));
      histo_VV_LepEff1Down->SetBinContent(i,TMath::Max(hVV->GetBinContent(i)-diff,0.0));     

      diff = hVV_LepEff2->GetBinContent(i)-hVV->GetBinContent(i);
      histo_VV_LepEff2Up  ->SetBinContent(i,TMath::Max(hVV->GetBinContent(i)+diff,0.0));
      histo_VV_LepEff2Down->SetBinContent(i,TMath::Max(hVV->GetBinContent(i)-diff,0.0));     

      diff = hVV_LepEff3->GetBinContent(i)-hVV->GetBinContent(i);
      histo_VV_LepEff3Up  ->SetBinContent(i,TMath::Max(hVV->GetBinContent(i)+diff,0.0));
      histo_VV_LepEff3Down->SetBinContent(i,TMath::Max(hVV->GetBinContent(i)-diff,0.0));     

      diff = hVV_LepEff4->GetBinContent(i)-hVV->GetBinContent(i);
      histo_VV_LepEff4Up  ->SetBinContent(i,TMath::Max(hVV->GetBinContent(i)+diff,0.0));
      histo_VV_LepEff4Down->SetBinContent(i,TMath::Max(hVV->GetBinContent(i)-diff,0.0));     

      diff = hVV_LepEff5->GetBinContent(i)-hVV->GetBinContent(i);
      histo_VV_LepEff5Up  ->SetBinContent(i,TMath::Max(hVV->GetBinContent(i)+diff,0.0));
      histo_VV_LepEff5Down->SetBinContent(i,TMath::Max(hVV->GetBinContent(i)-diff,0.0));     

      diff = hVV_LepEff6->GetBinContent(i)-hVV->GetBinContent(i);
      histo_VV_LepEff6Up  ->SetBinContent(i,TMath::Max(hVV->GetBinContent(i)+diff,0.0));
      histo_VV_LepEff6Down->SetBinContent(i,TMath::Max(hVV->GetBinContent(i)-diff,0.0));     

      diff = hVV_LepEff7->GetBinContent(i)-hVV->GetBinContent(i);
      histo_VV_LepEff7Up  ->SetBinContent(i,TMath::Max(hVV->GetBinContent(i)+diff,0.0));
      histo_VV_LepEff7Down->SetBinContent(i,TMath::Max(hVV->GetBinContent(i)-diff,0.0));     

      diff = hVV_RecEff->GetBinContent(i)-hVV->GetBinContent(i);
      histo_VV_RecEffUp  ->SetBinContent(i,TMath::Max(hVV->GetBinContent(i)+diff,0.0));
      histo_VV_RecEffDown->SetBinContent(i,TMath::Max(hVV->GetBinContent(i)-diff,0.0));     
    }

    // renormalizing the alternative model to the default one, we care about shape differences only
    Adet_alt->Scale(Adet->GetSumOfWeights()/Adet_alt->GetSumOfWeights());
    hDY_alt ->Scale(hDY ->GetSumOfWeights()/hDY_alt ->GetSumOfWeights());

    // DY uncertainties
    double allRecBin_def     = hDY       ->GetBinContent(i);
    double allRecBin_alt     = hDY_alt   ->GetBinContent(i);
    double allRecBin_MomRes1 = hDY_MomRes1->GetBinContent(i);
    double allRecBin_MomRes2 = hDY_MomRes2->GetBinContent(i);
    double allRecBin_MomRes3 = hDY_MomRes3->GetBinContent(i);
    double allRecBin_MomRes4 = hDY_MomRes4->GetBinContent(i);
    double allRecBin_LepEff1 = hDY_LepEff1->GetBinContent(i);
    double allRecBin_LepEff2 = hDY_LepEff2->GetBinContent(i);
    double allRecBin_LepEff3 = hDY_LepEff3->GetBinContent(i);
    double allRecBin_LepEff4 = hDY_LepEff4->GetBinContent(i);
    double allRecBin_LepEff5 = hDY_LepEff5->GetBinContent(i);
    double allRecBin_LepEff6 = hDY_LepEff6->GetBinContent(i);
    double allRecBin_LepEff7 = hDY_LepEff7->GetBinContent(i);
    double allRecBin_RecEff  = hDY_RecEff->GetBinContent(i);
    double fidRecBin_def     = 0;
    double fidRecBin_alt     = 0;
    double fidRecBin_MomRes1 = 0;
    double fidRecBin_MomRes2 = 0;
    double fidRecBin_MomRes3 = 0;
    double fidRecBin_MomRes4 = 0;
    double fidRecBin_LepEff1 = 0;
    double fidRecBin_LepEff2 = 0;
    double fidRecBin_LepEff3 = 0;
    double fidRecBin_LepEff4 = 0;
    double fidRecBin_LepEff5 = 0;
    double fidRecBin_LepEff6 = 0;
    double fidRecBin_LepEff7 = 0;
    double fidRecBin_RecEff  = 0;
    for(int j=1; j<=Adet->GetNbinsY(); j++) { // GEN
      fidRecBin_def     = fidRecBin_def     + Adet        ->GetBinContent(i,j);
      fidRecBin_alt     = fidRecBin_alt     + Adet_alt    ->GetBinContent(i,j);
      fidRecBin_MomRes1 = fidRecBin_MomRes1 + Adet_MomRes1->GetBinContent(i,j);
      fidRecBin_MomRes2 = fidRecBin_MomRes2 + Adet_MomRes2->GetBinContent(i,j);
      fidRecBin_MomRes3 = fidRecBin_MomRes3 + Adet_MomRes3->GetBinContent(i,j);
      fidRecBin_MomRes4 = fidRecBin_MomRes4 + Adet_MomRes4->GetBinContent(i,j);
      fidRecBin_LepEff1 = fidRecBin_LepEff1 + Adet_LepEff1->GetBinContent(i,j);
      fidRecBin_LepEff2 = fidRecBin_LepEff2 + Adet_LepEff2->GetBinContent(i,j);
      fidRecBin_LepEff3 = fidRecBin_LepEff3 + Adet_LepEff3->GetBinContent(i,j);
      fidRecBin_LepEff4 = fidRecBin_LepEff4 + Adet_LepEff4->GetBinContent(i,j);
      fidRecBin_LepEff5 = fidRecBin_LepEff5 + Adet_LepEff5->GetBinContent(i,j);
      fidRecBin_LepEff6 = fidRecBin_LepEff6 + Adet_LepEff6->GetBinContent(i,j);
      fidRecBin_LepEff7 = fidRecBin_LepEff7 + Adet_LepEff7->GetBinContent(i,j);
      fidRecBin_RecEff  = fidRecBin_RecEff  + Adet_RecEff ->GetBinContent(i,j);
      if(Adet->GetBinContent(i,j) > 0) {
        diff = Adet_alt->GetBinContent(i,j)-Adet->GetBinContent(i,j);
        histo_DY        [j-1]->SetBinError  (i,Adet->GetBinError(i,j));
        histo_DY        [j-1]->SetBinContent(i,Adet->GetBinContent(i,j));
        histo_DY_altUp  [j-1]->SetBinContent(i,TMath::Min(TMath::Max(Adet->GetBinContent(i,j)+diff,0.0),2.0*Adet->GetBinContent(i,j)));
        histo_DY_altDown[j-1]->SetBinContent(i,TMath::Max(Adet->GetBinContent(i,j)-diff,0.0));

        diff = Adet_MomRes1->GetBinContent(i,j)-Adet->GetBinContent(i,j);
        histo_DY_MomRes1Up  [j-1]->SetBinContent(i,TMath::Min(TMath::Max(Adet->GetBinContent(i,j)+diff,0.0),2.0*Adet->GetBinContent(i,j)));
        histo_DY_MomRes1Down[j-1]->SetBinContent(i,TMath::Max(Adet->GetBinContent(i,j)-diff,0.0));

        diff = Adet_MomRes2->GetBinContent(i,j)-Adet->GetBinContent(i,j);
        histo_DY_MomRes2Up  [j-1]->SetBinContent(i,TMath::Min(TMath::Max(Adet->GetBinContent(i,j)+diff,0.0),2.0*Adet->GetBinContent(i,j)));
        histo_DY_MomRes2Down[j-1]->SetBinContent(i,TMath::Max(Adet->GetBinContent(i,j)-diff,0.0));

        diff = Adet_MomRes3->GetBinContent(i,j)-Adet->GetBinContent(i,j);
        if(nsel == 1) diff = 0.0;
        histo_DY_MomRes3Up  [j-1]->SetBinContent(i,TMath::Min(TMath::Max(Adet->GetBinContent(i,j)+diff,0.0),2.0*Adet->GetBinContent(i,j)));
        histo_DY_MomRes3Down[j-1]->SetBinContent(i,TMath::Max(Adet->GetBinContent(i,j)-diff,0.0));

        diff = Adet_MomRes4->GetBinContent(i,j)-Adet->GetBinContent(i,j);
        if(nsel == 1) diff = 0.0;
        histo_DY_MomRes4Up  [j-1]->SetBinContent(i,TMath::Min(TMath::Max(Adet->GetBinContent(i,j)+diff,0.0),2.0*Adet->GetBinContent(i,j)));
        histo_DY_MomRes4Down[j-1]->SetBinContent(i,TMath::Max(Adet->GetBinContent(i,j)-diff,0.0));

        diff = Adet_LepEff1->GetBinContent(i,j)-Adet->GetBinContent(i,j);
        histo_DY_LepEff1Up  [j-1]->SetBinContent(i,TMath::Min(TMath::Max(Adet->GetBinContent(i,j)+diff,0.0),2.0*Adet->GetBinContent(i,j)));
        histo_DY_LepEff1Down[j-1]->SetBinContent(i,TMath::Max(Adet->GetBinContent(i,j)-diff,0.0));

        diff = Adet_LepEff2->GetBinContent(i,j)-Adet->GetBinContent(i,j);
        histo_DY_LepEff2Up  [j-1]->SetBinContent(i,TMath::Min(TMath::Max(Adet->GetBinContent(i,j)+diff,0.0),2.0*Adet->GetBinContent(i,j)));
        histo_DY_LepEff2Down[j-1]->SetBinContent(i,TMath::Max(Adet->GetBinContent(i,j)-diff,0.0));

        diff = Adet_LepEff3->GetBinContent(i,j)-Adet->GetBinContent(i,j);
        histo_DY_LepEff3Up  [j-1]->SetBinContent(i,TMath::Min(TMath::Max(Adet->GetBinContent(i,j)+diff,0.0),2.0*Adet->GetBinContent(i,j)));
        histo_DY_LepEff3Down[j-1]->SetBinContent(i,TMath::Max(Adet->GetBinContent(i,j)-diff,0.0));

        diff = Adet_LepEff4->GetBinContent(i,j)-Adet->GetBinContent(i,j);
        histo_DY_LepEff4Up  [j-1]->SetBinContent(i,TMath::Min(TMath::Max(Adet->GetBinContent(i,j)+diff,0.0),2.0*Adet->GetBinContent(i,j)));
        histo_DY_LepEff4Down[j-1]->SetBinContent(i,TMath::Max(Adet->GetBinContent(i,j)-diff,0.0));

        diff = Adet_LepEff5->GetBinContent(i,j)-Adet->GetBinContent(i,j);
        histo_DY_LepEff5Up  [j-1]->SetBinContent(i,TMath::Min(TMath::Max(Adet->GetBinContent(i,j)+diff,0.0),2.0*Adet->GetBinContent(i,j)));
        histo_DY_LepEff5Down[j-1]->SetBinContent(i,TMath::Max(Adet->GetBinContent(i,j)-diff,0.0));

        diff = Adet_LepEff6->GetBinContent(i,j)-Adet->GetBinContent(i,j);
        histo_DY_LepEff6Up  [j-1]->SetBinContent(i,TMath::Min(TMath::Max(Adet->GetBinContent(i,j)+diff,0.0),2.0*Adet->GetBinContent(i,j)));
        histo_DY_LepEff6Down[j-1]->SetBinContent(i,TMath::Max(Adet->GetBinContent(i,j)-diff,0.0));

        diff = Adet_LepEff7->GetBinContent(i,j)-Adet->GetBinContent(i,j);
        histo_DY_LepEff7Up  [j-1]->SetBinContent(i,TMath::Min(TMath::Max(Adet->GetBinContent(i,j)+diff,0.0),2.0*Adet->GetBinContent(i,j)));
        histo_DY_LepEff7Down[j-1]->SetBinContent(i,TMath::Max(Adet->GetBinContent(i,j)-diff,0.0));

        diff = Adet_RecEff->GetBinContent(i,j)-Adet->GetBinContent(i,j);
        histo_DY_RecEffUp  [j-1]->SetBinContent(i,TMath::Min(TMath::Max(Adet->GetBinContent(i,j)+diff,0.0),2.0*Adet->GetBinContent(i,j)));
        histo_DY_RecEffDown[j-1]->SetBinContent(i,TMath::Max(Adet->GetBinContent(i,j)-diff,0.0));

      }
    }
    double gendiff_def     = allRecBin_def     - fidRecBin_def;
    double gendiff_alt     = allRecBin_alt     - fidRecBin_alt;
    double gendiff_MomRes1 = allRecBin_MomRes1 - fidRecBin_MomRes1;
    double gendiff_MomRes2 = allRecBin_MomRes2 - fidRecBin_MomRes2;
    double gendiff_MomRes3 = allRecBin_MomRes3 - fidRecBin_MomRes3;
    double gendiff_MomRes4 = allRecBin_MomRes4 - fidRecBin_MomRes4;
    double gendiff_LepEff1 = allRecBin_LepEff1 - fidRecBin_LepEff1;
    double gendiff_LepEff2 = allRecBin_LepEff2 - fidRecBin_LepEff2;
    double gendiff_LepEff3 = allRecBin_LepEff3 - fidRecBin_LepEff3;
    double gendiff_LepEff4 = allRecBin_LepEff4 - fidRecBin_LepEff4;
    double gendiff_LepEff5 = allRecBin_LepEff5 - fidRecBin_LepEff5;
    double gendiff_LepEff6 = allRecBin_LepEff6 - fidRecBin_LepEff6;
    double gendiff_LepEff7 = allRecBin_LepEff7 - fidRecBin_LepEff7;
    double gendiff_RecEff  = allRecBin_RecEff  - fidRecBin_RecEff;
    if(gendiff_def     <= 0) {printf("Non-fiducial     def: Bin %d totally efficient %f\n",i,gendiff_def);     gendiff_def     = 0.0;}
    if(gendiff_alt     <= 0) {printf("Non-fiducial     alt: Bin %d totally efficient %f\n",i,gendiff_alt);     gendiff_alt     = 0.0;}
    if(gendiff_MomRes1 <= 0) {printf("Non-fiducial MomRes1: Bin %d totally efficient %f\n",i,gendiff_MomRes1); gendiff_MomRes1 = 0.0;}
    if(gendiff_MomRes2 <= 0) {printf("Non-fiducial MomRes2: Bin %d totally efficient %f\n",i,gendiff_MomRes2); gendiff_MomRes2 = 0.0;}
    if(gendiff_MomRes3 <= 0) {printf("Non-fiducial MomRes3: Bin %d totally efficient %f\n",i,gendiff_MomRes3); gendiff_MomRes3 = 0.0;}
    if(gendiff_MomRes4 <= 0) {printf("Non-fiducial MomRes4: Bin %d totally efficient %f\n",i,gendiff_MomRes4); gendiff_MomRes4 = 0.0;}
    if(gendiff_LepEff1 <= 0) {printf("Non-fiducial LepEff1: Bin %d totally efficient %f\n",i,gendiff_LepEff1); gendiff_LepEff1 = 0.0;}
    if(gendiff_LepEff2 <= 0) {printf("Non-fiducial LepEff2: Bin %d totally efficient %f\n",i,gendiff_LepEff2); gendiff_LepEff2 = 0.0;}
    if(gendiff_LepEff3 <= 0) {printf("Non-fiducial LepEff3: Bin %d totally efficient %f\n",i,gendiff_LepEff3); gendiff_LepEff3 = 0.0;}
    if(gendiff_LepEff4 <= 0) {printf("Non-fiducial LepEff4: Bin %d totally efficient %f\n",i,gendiff_LepEff4); gendiff_LepEff4 = 0.0;}
    if(gendiff_LepEff5 <= 0) {printf("Non-fiducial LepEff5: Bin %d totally efficient %f\n",i,gendiff_LepEff5); gendiff_LepEff5 = 0.0;}
    if(gendiff_LepEff6 <= 0) {printf("Non-fiducial LepEff6: Bin %d totally efficient %f\n",i,gendiff_LepEff6); gendiff_LepEff6 = 0.0;}
    if(gendiff_LepEff7 <= 0) {printf("Non-fiducial LepEff7: Bin %d totally efficient %f\n",i,gendiff_LepEff7); gendiff_LepEff7 = 0.0;}
    if(gendiff_RecEff  <= 0) {printf("Non-fiducial  RecEff: Bin %d totally efficient %f\n",i,gendiff_RecEff);  gendiff_RecEff  = 0.0;}
    histo_NonFid->SetBinContent(i,gendiff_def);
    histo_NonFid->SetBinError(i,gendiff_def*0.01);
    if(gendiff_def > 0){
      diff = gendiff_alt-gendiff_def;
      histo_NonFid_altUp  ->SetBinContent(i,TMath::Max(gendiff_def+diff,0.0));
      histo_NonFid_altDown->SetBinContent(i,TMath::Max(gendiff_def-diff,0.0));      

      diff = gendiff_MomRes1-gendiff_def;
      histo_NonFid_MomRes1Up  ->SetBinContent(i,TMath::Max(gendiff_def+diff,0.0));
      histo_NonFid_MomRes1Down->SetBinContent(i,TMath::Max(gendiff_def-diff,0.0));      

      diff = gendiff_MomRes2-gendiff_def;
      histo_NonFid_MomRes2Up  ->SetBinContent(i,TMath::Max(gendiff_def+diff,0.0));
      histo_NonFid_MomRes2Down->SetBinContent(i,TMath::Max(gendiff_def-diff,0.0));      

      diff = gendiff_MomRes3-gendiff_def;
      if(nsel == 1) diff = 0.0;
      histo_NonFid_MomRes3Up  ->SetBinContent(i,TMath::Max(gendiff_def+diff,0.0));
      histo_NonFid_MomRes3Down->SetBinContent(i,TMath::Max(gendiff_def-diff,0.0));      

      diff = gendiff_MomRes4-gendiff_def;
      if(nsel == 1) diff = 0.0;
      histo_NonFid_MomRes4Up  ->SetBinContent(i,TMath::Max(gendiff_def+diff,0.0));
      histo_NonFid_MomRes4Down->SetBinContent(i,TMath::Max(gendiff_def-diff,0.0));      

      diff = gendiff_LepEff1-gendiff_def;
      histo_NonFid_LepEff1Up  ->SetBinContent(i,TMath::Max(gendiff_def+diff,0.0));
      histo_NonFid_LepEff1Down->SetBinContent(i,TMath::Max(gendiff_def-diff,0.0));      

      diff = gendiff_LepEff2-gendiff_def;
      histo_NonFid_LepEff2Up  ->SetBinContent(i,TMath::Max(gendiff_def+diff,0.0));
      histo_NonFid_LepEff2Down->SetBinContent(i,TMath::Max(gendiff_def-diff,0.0));      

      diff = gendiff_LepEff3-gendiff_def;
      histo_NonFid_LepEff3Up  ->SetBinContent(i,TMath::Max(gendiff_def+diff,0.0));
      histo_NonFid_LepEff3Down->SetBinContent(i,TMath::Max(gendiff_def-diff,0.0));      

      diff = gendiff_LepEff4-gendiff_def;
      histo_NonFid_LepEff4Up  ->SetBinContent(i,TMath::Max(gendiff_def+diff,0.0));
      histo_NonFid_LepEff4Down->SetBinContent(i,TMath::Max(gendiff_def-diff,0.0));      

      diff = gendiff_LepEff5-gendiff_def;
      histo_NonFid_LepEff5Up  ->SetBinContent(i,TMath::Max(gendiff_def+diff,0.0));
      histo_NonFid_LepEff5Down->SetBinContent(i,TMath::Max(gendiff_def-diff,0.0));      

      diff = gendiff_LepEff6-gendiff_def;
      histo_NonFid_LepEff6Up  ->SetBinContent(i,TMath::Max(gendiff_def+diff,0.0));
      histo_NonFid_LepEff6Down->SetBinContent(i,TMath::Max(gendiff_def-diff,0.0));      

      diff = gendiff_LepEff7-gendiff_def;
      histo_NonFid_LepEff7Up  ->SetBinContent(i,TMath::Max(gendiff_def+diff,0.0));
      histo_NonFid_LepEff7Down->SetBinContent(i,TMath::Max(gendiff_def-diff,0.0));      

      diff = gendiff_RecEff-gendiff_def;
      histo_NonFid_RecEffUp  ->SetBinContent(i,TMath::Max(gendiff_def+diff,0.0));
      histo_NonFid_RecEffDown->SetBinContent(i,TMath::Max(gendiff_def-diff,0.0));      
    }
  }

  for(int i=1; i<=nReco; i++) {  
    histo_VV_VVStatUp  [i-1]->Add(histo_VV);
    histo_VV_VVStatDown[i-1]->Add(histo_VV);
    histo_VV_VVStatUp  [i-1]->SetBinContent(i,TMath::Min(TMath::Max(histo_VV->GetBinContent(i)+histo_VV->GetBinError(i),0.0),2*histo_VV->GetBinContent(i)));
    histo_VV_VVStatDown[i-1]->SetBinContent(i,TMath::Max(histo_VV->GetBinContent(i)-histo_VV->GetBinError(i),0.0));
    histo_Res_ResStatUp  [i-1]->Add(histo_Res);
    histo_Res_ResStatDown[i-1]->Add(histo_Res);
    histo_Res_ResStatUp  [i-1]->SetBinContent(i,TMath::Min(TMath::Max(histo_Res->GetBinContent(i)+histo_Res->GetBinError(i),0.0),2*histo_Res->GetBinContent(i)));
    histo_Res_ResStatDown[i-1]->SetBinContent(i,TMath::Max(histo_Res->GetBinContent(i)-histo_Res->GetBinError(i),0.0));
    histo_NonFid_NonFidStatUp  [i-1]->Add(histo_NonFid);
    histo_NonFid_NonFidStatDown[i-1]->Add(histo_NonFid);
    histo_NonFid_NonFidStatUp  [i-1]->SetBinContent(i,TMath::Min(TMath::Max(histo_NonFid->GetBinContent(i)+histo_NonFid->GetBinError(i),0.0),2*histo_NonFid->GetBinContent(i)));
    histo_NonFid_NonFidStatDown[i-1]->SetBinContent(i,TMath::Max(histo_NonFid->GetBinContent(i)-histo_NonFid->GetBinError(i),0.0));
    for(int j=1; j<=nChan; j++) {  
      histo_DY_DYStatUp  [j-1][i-1]->Add(histo_DY[j-1]);
      histo_DY_DYStatDown[j-1][i-1]->Add(histo_DY[j-1]);
      histo_DY_DYStatUp  [j-1][i-1]->SetBinContent(i,TMath::Min(TMath::Max(histo_DY[j-1]->GetBinContent(i)+histo_DY[j-1]->GetBinError(i),0.0),2*histo_DY[j-1]->GetBinContent(i)));
      histo_DY_DYStatDown[j-1][i-1]->SetBinContent(i,TMath::Max(histo_DY[j-1]->GetBinContent(i)-histo_DY[j-1]->GetBinError(i),0.0));
    }
  }

  printf("uncertainties VV: ");
  for(int i=1; i<=histo_Data->GetNbinsX(); i++) printf("%.1f ",histo_VV->GetBinContent(i)); printf("\n");
  for(int i=1; i<=histo_Data->GetNbinsX(); i++) {if(histo_VV->GetBinContent(i)>0)printf("%5.1f ",histo_VV_vvNormPDFUp    ->GetBinContent(i)/histo_VV->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
  for(int i=1; i<=histo_Data->GetNbinsX(); i++) {if(histo_VV->GetBinContent(i)>0)printf("%5.1f ",histo_VV_vvNormPDFDown  ->GetBinContent(i)/histo_VV->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
  for(int i=1; i<=histo_Data->GetNbinsX(); i++) {if(histo_VV->GetBinContent(i)>0)printf("%5.1f ",histo_VV_vvNormQCDUp    ->GetBinContent(i)/histo_VV->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
  for(int i=1; i<=histo_Data->GetNbinsX(); i++) {if(histo_VV->GetBinContent(i)>0)printf("%5.1f ",histo_VV_vvNormQCDDown  ->GetBinContent(i)/histo_VV->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
  for(int i=1; i<=histo_Data->GetNbinsX(); i++) {if(histo_VV->GetBinContent(i)>0)printf("%5.1f ",histo_VV_MomRes1Up      ->GetBinContent(i)/histo_VV->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
  for(int i=1; i<=histo_Data->GetNbinsX(); i++) {if(histo_VV->GetBinContent(i)>0)printf("%5.1f ",histo_VV_MomRes1Down    ->GetBinContent(i)/histo_VV->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
  for(int i=1; i<=histo_Data->GetNbinsX(); i++) {if(histo_VV->GetBinContent(i)>0)printf("%5.1f ",histo_VV_MomRes2Up      ->GetBinContent(i)/histo_VV->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
  for(int i=1; i<=histo_Data->GetNbinsX(); i++) {if(histo_VV->GetBinContent(i)>0)printf("%5.1f ",histo_VV_MomRes2Down    ->GetBinContent(i)/histo_VV->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
  for(int i=1; i<=histo_Data->GetNbinsX(); i++) {if(histo_VV->GetBinContent(i)>0)printf("%5.1f ",histo_VV_MomRes3Up      ->GetBinContent(i)/histo_VV->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
  for(int i=1; i<=histo_Data->GetNbinsX(); i++) {if(histo_VV->GetBinContent(i)>0)printf("%5.1f ",histo_VV_MomRes3Down    ->GetBinContent(i)/histo_VV->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
  for(int i=1; i<=histo_Data->GetNbinsX(); i++) {if(histo_VV->GetBinContent(i)>0)printf("%5.1f ",histo_VV_MomRes4Up      ->GetBinContent(i)/histo_VV->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
  for(int i=1; i<=histo_Data->GetNbinsX(); i++) {if(histo_VV->GetBinContent(i)>0)printf("%5.1f ",histo_VV_MomRes4Down    ->GetBinContent(i)/histo_VV->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
  for(int i=1; i<=histo_Data->GetNbinsX(); i++) {if(histo_VV->GetBinContent(i)>0)printf("%5.1f ",histo_VV_LepEff1Up      ->GetBinContent(i)/histo_VV->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
  for(int i=1; i<=histo_Data->GetNbinsX(); i++) {if(histo_VV->GetBinContent(i)>0)printf("%5.1f ",histo_VV_LepEff1Down    ->GetBinContent(i)/histo_VV->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
  for(int i=1; i<=histo_Data->GetNbinsX(); i++) {if(histo_VV->GetBinContent(i)>0)printf("%5.1f ",histo_VV_LepEff2Up      ->GetBinContent(i)/histo_VV->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
  for(int i=1; i<=histo_Data->GetNbinsX(); i++) {if(histo_VV->GetBinContent(i)>0)printf("%5.1f ",histo_VV_LepEff2Down    ->GetBinContent(i)/histo_VV->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
  for(int i=1; i<=histo_Data->GetNbinsX(); i++) {if(histo_VV->GetBinContent(i)>0)printf("%5.1f ",histo_VV_LepEff3Up      ->GetBinContent(i)/histo_VV->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
  for(int i=1; i<=histo_Data->GetNbinsX(); i++) {if(histo_VV->GetBinContent(i)>0)printf("%5.1f ",histo_VV_LepEff3Down    ->GetBinContent(i)/histo_VV->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
  for(int i=1; i<=histo_Data->GetNbinsX(); i++) {if(histo_VV->GetBinContent(i)>0)printf("%5.1f ",histo_VV_LepEff4Up      ->GetBinContent(i)/histo_VV->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
  for(int i=1; i<=histo_Data->GetNbinsX(); i++) {if(histo_VV->GetBinContent(i)>0)printf("%5.1f ",histo_VV_LepEff4Down    ->GetBinContent(i)/histo_VV->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
  for(int i=1; i<=histo_Data->GetNbinsX(); i++) {if(histo_VV->GetBinContent(i)>0)printf("%5.1f ",histo_VV_LepEff5Up      ->GetBinContent(i)/histo_VV->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
  for(int i=1; i<=histo_Data->GetNbinsX(); i++) {if(histo_VV->GetBinContent(i)>0)printf("%5.1f ",histo_VV_LepEff5Down    ->GetBinContent(i)/histo_VV->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
  for(int i=1; i<=histo_Data->GetNbinsX(); i++) {if(histo_VV->GetBinContent(i)>0)printf("%5.1f ",histo_VV_LepEff6Up      ->GetBinContent(i)/histo_VV->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
  for(int i=1; i<=histo_Data->GetNbinsX(); i++) {if(histo_VV->GetBinContent(i)>0)printf("%5.1f ",histo_VV_LepEff6Down    ->GetBinContent(i)/histo_VV->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
  for(int i=1; i<=histo_Data->GetNbinsX(); i++) {if(histo_VV->GetBinContent(i)>0)printf("%5.1f ",histo_VV_LepEff7Up      ->GetBinContent(i)/histo_VV->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
  for(int i=1; i<=histo_Data->GetNbinsX(); i++) {if(histo_VV->GetBinContent(i)>0)printf("%5.1f ",histo_VV_LepEff7Down    ->GetBinContent(i)/histo_VV->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
  for(int i=1; i<=histo_Data->GetNbinsX(); i++) {if(histo_VV->GetBinContent(i)>0)printf("%5.1f ",histo_VV_RecEffUp       ->GetBinContent(i)/histo_VV->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
  for(int i=1; i<=histo_Data->GetNbinsX(); i++) {if(histo_VV->GetBinContent(i)>0)printf("%5.1f ",histo_VV_RecEffDown     ->GetBinContent(i)/histo_VV->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
  for(int i=1; i<=histo_Data->GetNbinsX(); i++) {if(histo_VV->GetBinContent(i)>0)printf("%5.1f ",histo_VV_VVStatUp  [i-1]->GetBinContent(i)/histo_VV->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
  for(int i=1; i<=histo_Data->GetNbinsX(); i++) {if(histo_VV->GetBinContent(i)>0)printf("%5.1f ",histo_VV_VVStatDown[i-1]->GetBinContent(i)/histo_VV->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");

  printf("uncertainties NonFid: ");
  for(int i=1; i<=histo_Data->GetNbinsX(); i++) printf("%.1f ",histo_NonFid->GetBinContent(i)); printf("\n");
  for(int i=1; i<=histo_Data->GetNbinsX(); i++) {if(histo_NonFid->GetBinContent(i)>0)printf("%5.1f ",histo_NonFid_altUp              ->GetBinContent(i)/histo_NonFid->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
  for(int i=1; i<=histo_Data->GetNbinsX(); i++) {if(histo_NonFid->GetBinContent(i)>0)printf("%5.1f ",histo_NonFid_altDown            ->GetBinContent(i)/histo_NonFid->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
  for(int i=1; i<=histo_Data->GetNbinsX(); i++) {if(histo_NonFid->GetBinContent(i)>0)printf("%5.1f ",histo_NonFid_MomRes1Up	     ->GetBinContent(i)/histo_NonFid->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
  for(int i=1; i<=histo_Data->GetNbinsX(); i++) {if(histo_NonFid->GetBinContent(i)>0)printf("%5.1f ",histo_NonFid_MomRes1Down	     ->GetBinContent(i)/histo_NonFid->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
  for(int i=1; i<=histo_Data->GetNbinsX(); i++) {if(histo_NonFid->GetBinContent(i)>0)printf("%5.1f ",histo_NonFid_MomRes2Up	     ->GetBinContent(i)/histo_NonFid->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
  for(int i=1; i<=histo_Data->GetNbinsX(); i++) {if(histo_NonFid->GetBinContent(i)>0)printf("%5.1f ",histo_NonFid_MomRes2Down	     ->GetBinContent(i)/histo_NonFid->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
  for(int i=1; i<=histo_Data->GetNbinsX(); i++) {if(histo_NonFid->GetBinContent(i)>0)printf("%5.1f ",histo_NonFid_MomRes3Up	     ->GetBinContent(i)/histo_NonFid->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
  for(int i=1; i<=histo_Data->GetNbinsX(); i++) {if(histo_NonFid->GetBinContent(i)>0)printf("%5.1f ",histo_NonFid_MomRes3Down	     ->GetBinContent(i)/histo_NonFid->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
  for(int i=1; i<=histo_Data->GetNbinsX(); i++) {if(histo_NonFid->GetBinContent(i)>0)printf("%5.1f ",histo_NonFid_MomRes4Up	     ->GetBinContent(i)/histo_NonFid->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
  for(int i=1; i<=histo_Data->GetNbinsX(); i++) {if(histo_NonFid->GetBinContent(i)>0)printf("%5.1f ",histo_NonFid_MomRes4Down	     ->GetBinContent(i)/histo_NonFid->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
  for(int i=1; i<=histo_Data->GetNbinsX(); i++) {if(histo_NonFid->GetBinContent(i)>0)printf("%5.1f ",histo_NonFid_LepEff1Up	     ->GetBinContent(i)/histo_NonFid->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
  for(int i=1; i<=histo_Data->GetNbinsX(); i++) {if(histo_NonFid->GetBinContent(i)>0)printf("%5.1f ",histo_NonFid_LepEff1Down	     ->GetBinContent(i)/histo_NonFid->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
  for(int i=1; i<=histo_Data->GetNbinsX(); i++) {if(histo_NonFid->GetBinContent(i)>0)printf("%5.1f ",histo_NonFid_LepEff2Up	     ->GetBinContent(i)/histo_NonFid->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
  for(int i=1; i<=histo_Data->GetNbinsX(); i++) {if(histo_NonFid->GetBinContent(i)>0)printf("%5.1f ",histo_NonFid_LepEff2Down	     ->GetBinContent(i)/histo_NonFid->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
  for(int i=1; i<=histo_Data->GetNbinsX(); i++) {if(histo_NonFid->GetBinContent(i)>0)printf("%5.1f ",histo_NonFid_LepEff3Up	     ->GetBinContent(i)/histo_NonFid->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
  for(int i=1; i<=histo_Data->GetNbinsX(); i++) {if(histo_NonFid->GetBinContent(i)>0)printf("%5.1f ",histo_NonFid_LepEff3Down	     ->GetBinContent(i)/histo_NonFid->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
  for(int i=1; i<=histo_Data->GetNbinsX(); i++) {if(histo_NonFid->GetBinContent(i)>0)printf("%5.1f ",histo_NonFid_LepEff4Up	     ->GetBinContent(i)/histo_NonFid->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
  for(int i=1; i<=histo_Data->GetNbinsX(); i++) {if(histo_NonFid->GetBinContent(i)>0)printf("%5.1f ",histo_NonFid_LepEff4Down	     ->GetBinContent(i)/histo_NonFid->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
  for(int i=1; i<=histo_Data->GetNbinsX(); i++) {if(histo_NonFid->GetBinContent(i)>0)printf("%5.1f ",histo_NonFid_LepEff5Up	     ->GetBinContent(i)/histo_NonFid->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
  for(int i=1; i<=histo_Data->GetNbinsX(); i++) {if(histo_NonFid->GetBinContent(i)>0)printf("%5.1f ",histo_NonFid_LepEff5Down	     ->GetBinContent(i)/histo_NonFid->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
  for(int i=1; i<=histo_Data->GetNbinsX(); i++) {if(histo_NonFid->GetBinContent(i)>0)printf("%5.1f ",histo_NonFid_LepEff6Up	     ->GetBinContent(i)/histo_NonFid->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
  for(int i=1; i<=histo_Data->GetNbinsX(); i++) {if(histo_NonFid->GetBinContent(i)>0)printf("%5.1f ",histo_NonFid_LepEff6Down	     ->GetBinContent(i)/histo_NonFid->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
  for(int i=1; i<=histo_Data->GetNbinsX(); i++) {if(histo_NonFid->GetBinContent(i)>0)printf("%5.1f ",histo_NonFid_LepEff7Up	     ->GetBinContent(i)/histo_NonFid->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
  for(int i=1; i<=histo_Data->GetNbinsX(); i++) {if(histo_NonFid->GetBinContent(i)>0)printf("%5.1f ",histo_NonFid_LepEff7Down	     ->GetBinContent(i)/histo_NonFid->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
  for(int i=1; i<=histo_Data->GetNbinsX(); i++) {if(histo_NonFid->GetBinContent(i)>0)printf("%5.1f ",histo_NonFid_RecEffUp           ->GetBinContent(i)/histo_NonFid->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
  for(int i=1; i<=histo_Data->GetNbinsX(); i++) {if(histo_NonFid->GetBinContent(i)>0)printf("%5.1f ",histo_NonFid_RecEffDown         ->GetBinContent(i)/histo_NonFid->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
  for(int i=1; i<=histo_Data->GetNbinsX(); i++) {if(histo_NonFid->GetBinContent(i)>0)printf("%5.1f ",histo_NonFid_NonFidStatUp  [i-1]->GetBinContent(i)/histo_NonFid->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
  for(int i=1; i<=histo_Data->GetNbinsX(); i++) {if(histo_NonFid->GetBinContent(i)>0)printf("%5.1f ",histo_NonFid_NonFidStatDown[i-1]->GetBinContent(i)/histo_NonFid->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");

  printf("uncertainties Res: ");
  for(int i=1; i<=histo_Data->GetNbinsX(); i++) printf("%.1f ",histo_Res->GetBinContent(i)); printf("\n");
  for(int i=1; i<=histo_Data->GetNbinsX(); i++) {if(histo_Res->GetBinContent(i)>0)printf("%5.1f ",histo_Res_ResStatUp  [i-1]->GetBinContent(i)/histo_Res->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
  for(int i=1; i<=histo_Data->GetNbinsX(); i++) {if(histo_Res->GetBinContent(i)>0)printf("%5.1f ",histo_Res_ResStatDown[i-1]->GetBinContent(i)/histo_Res->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");

  for(int nc=0; nc<nChan; nc++){
    printf("uncertainties DY(%d): ",nc);
    for(int i=1; i<=histo_Data->GetNbinsX(); i++) printf("%.1f ",histo_DY[nc]->GetBinContent(i)); printf("\n");
    for(int i=1; i<=histo_Data->GetNbinsX(); i++) {if(histo_DY[nc]->GetBinContent(i)>0)printf("%5.1f ",histo_DY_altUp[nc]          ->GetBinContent(i)/histo_DY[nc]->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    for(int i=1; i<=histo_Data->GetNbinsX(); i++) {if(histo_DY[nc]->GetBinContent(i)>0)printf("%5.1f ",histo_DY_altDown[nc]        ->GetBinContent(i)/histo_DY[nc]->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    for(int i=1; i<=histo_Data->GetNbinsX(); i++) {if(histo_DY[nc]->GetBinContent(i)>0)printf("%5.1f ",histo_DY_MomRes1Up[nc]	   ->GetBinContent(i)/histo_DY[nc]->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    for(int i=1; i<=histo_Data->GetNbinsX(); i++) {if(histo_DY[nc]->GetBinContent(i)>0)printf("%5.1f ",histo_DY_MomRes1Down[nc]    ->GetBinContent(i)/histo_DY[nc]->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    for(int i=1; i<=histo_Data->GetNbinsX(); i++) {if(histo_DY[nc]->GetBinContent(i)>0)printf("%5.1f ",histo_DY_MomRes2Up[nc]	   ->GetBinContent(i)/histo_DY[nc]->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    for(int i=1; i<=histo_Data->GetNbinsX(); i++) {if(histo_DY[nc]->GetBinContent(i)>0)printf("%5.1f ",histo_DY_MomRes2Down[nc]    ->GetBinContent(i)/histo_DY[nc]->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    for(int i=1; i<=histo_Data->GetNbinsX(); i++) {if(histo_DY[nc]->GetBinContent(i)>0)printf("%5.1f ",histo_DY_MomRes3Up[nc]	   ->GetBinContent(i)/histo_DY[nc]->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    for(int i=1; i<=histo_Data->GetNbinsX(); i++) {if(histo_DY[nc]->GetBinContent(i)>0)printf("%5.1f ",histo_DY_MomRes3Down[nc]    ->GetBinContent(i)/histo_DY[nc]->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    for(int i=1; i<=histo_Data->GetNbinsX(); i++) {if(histo_DY[nc]->GetBinContent(i)>0)printf("%5.1f ",histo_DY_MomRes4Up[nc]	   ->GetBinContent(i)/histo_DY[nc]->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    for(int i=1; i<=histo_Data->GetNbinsX(); i++) {if(histo_DY[nc]->GetBinContent(i)>0)printf("%5.1f ",histo_DY_MomRes4Down[nc]    ->GetBinContent(i)/histo_DY[nc]->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    for(int i=1; i<=histo_Data->GetNbinsX(); i++) {if(histo_DY[nc]->GetBinContent(i)>0)printf("%5.1f ",histo_DY_LepEff1Up[nc]	   ->GetBinContent(i)/histo_DY[nc]->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    for(int i=1; i<=histo_Data->GetNbinsX(); i++) {if(histo_DY[nc]->GetBinContent(i)>0)printf("%5.1f ",histo_DY_LepEff1Down[nc]    ->GetBinContent(i)/histo_DY[nc]->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    for(int i=1; i<=histo_Data->GetNbinsX(); i++) {if(histo_DY[nc]->GetBinContent(i)>0)printf("%5.1f ",histo_DY_LepEff2Up[nc]	   ->GetBinContent(i)/histo_DY[nc]->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    for(int i=1; i<=histo_Data->GetNbinsX(); i++) {if(histo_DY[nc]->GetBinContent(i)>0)printf("%5.1f ",histo_DY_LepEff2Down[nc]    ->GetBinContent(i)/histo_DY[nc]->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    for(int i=1; i<=histo_Data->GetNbinsX(); i++) {if(histo_DY[nc]->GetBinContent(i)>0)printf("%5.1f ",histo_DY_LepEff3Up[nc]	   ->GetBinContent(i)/histo_DY[nc]->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    for(int i=1; i<=histo_Data->GetNbinsX(); i++) {if(histo_DY[nc]->GetBinContent(i)>0)printf("%5.1f ",histo_DY_LepEff3Down[nc]    ->GetBinContent(i)/histo_DY[nc]->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    for(int i=1; i<=histo_Data->GetNbinsX(); i++) {if(histo_DY[nc]->GetBinContent(i)>0)printf("%5.1f ",histo_DY_LepEff4Up[nc]	   ->GetBinContent(i)/histo_DY[nc]->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    for(int i=1; i<=histo_Data->GetNbinsX(); i++) {if(histo_DY[nc]->GetBinContent(i)>0)printf("%5.1f ",histo_DY_LepEff4Down[nc]    ->GetBinContent(i)/histo_DY[nc]->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    for(int i=1; i<=histo_Data->GetNbinsX(); i++) {if(histo_DY[nc]->GetBinContent(i)>0)printf("%5.1f ",histo_DY_LepEff5Up[nc]	   ->GetBinContent(i)/histo_DY[nc]->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    for(int i=1; i<=histo_Data->GetNbinsX(); i++) {if(histo_DY[nc]->GetBinContent(i)>0)printf("%5.1f ",histo_DY_LepEff5Down[nc]    ->GetBinContent(i)/histo_DY[nc]->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    for(int i=1; i<=histo_Data->GetNbinsX(); i++) {if(histo_DY[nc]->GetBinContent(i)>0)printf("%5.1f ",histo_DY_LepEff6Up[nc]	   ->GetBinContent(i)/histo_DY[nc]->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    for(int i=1; i<=histo_Data->GetNbinsX(); i++) {if(histo_DY[nc]->GetBinContent(i)>0)printf("%5.1f ",histo_DY_LepEff6Down[nc]    ->GetBinContent(i)/histo_DY[nc]->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    for(int i=1; i<=histo_Data->GetNbinsX(); i++) {if(histo_DY[nc]->GetBinContent(i)>0)printf("%5.1f ",histo_DY_LepEff7Up[nc]	   ->GetBinContent(i)/histo_DY[nc]->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    for(int i=1; i<=histo_Data->GetNbinsX(); i++) {if(histo_DY[nc]->GetBinContent(i)>0)printf("%5.1f ",histo_DY_LepEff7Down[nc]    ->GetBinContent(i)/histo_DY[nc]->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    for(int i=1; i<=histo_Data->GetNbinsX(); i++) {if(histo_DY[nc]->GetBinContent(i)>0)printf("%5.1f ",histo_DY_RecEffUp[nc]       ->GetBinContent(i)/histo_DY[nc]->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    for(int i=1; i<=histo_Data->GetNbinsX(); i++) {if(histo_DY[nc]->GetBinContent(i)>0)printf("%5.1f ",histo_DY_RecEffDown[nc]     ->GetBinContent(i)/histo_DY[nc]->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    for(int i=1; i<=histo_Data->GetNbinsX(); i++) {if(histo_DY[nc]->GetBinContent(i)>0)printf("%5.1f ",histo_DY_DYStatUp  [nc][i-1]->GetBinContent(i)/histo_DY[nc]->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    for(int i=1; i<=histo_Data->GetNbinsX(); i++) {if(histo_DY[nc]->GetBinContent(i)>0)printf("%5.1f ",histo_DY_DYStatDown[nc][i-1]->GetBinContent(i)/histo_DY[nc]->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
  }

  if(theHistName == "Tot"){
    double momResUnc = sqrt(abs(histo_DY_MomRes1Up[0]->GetBinContent(1)-histo_DY[0]->GetBinContent(1))*abs(histo_DY_MomRes1Up[0]->GetBinContent(1)-histo_DY[0]->GetBinContent(1))+
                            abs(histo_DY_MomRes2Up[0]->GetBinContent(1)-histo_DY[0]->GetBinContent(1))*abs(histo_DY_MomRes2Up[0]->GetBinContent(1)-histo_DY[0]->GetBinContent(1))+
                            abs(histo_DY_MomRes3Up[0]->GetBinContent(1)-histo_DY[0]->GetBinContent(1))*abs(histo_DY_MomRes3Up[0]->GetBinContent(1)-histo_DY[0]->GetBinContent(1))+
                            abs(histo_DY_MomRes4Up[0]->GetBinContent(1)-histo_DY[0]->GetBinContent(1))*abs(histo_DY_MomRes4Up[0]->GetBinContent(1)-histo_DY[0]->GetBinContent(1)))*100/histo_DY[0]->GetSumOfWeights();
    double lepEffUnc = sqrt(abs(histo_DY_LepEff2Up[0]->GetBinContent(1)-histo_DY[0]->GetBinContent(1))*abs(histo_DY_LepEff2Up[0]->GetBinContent(1)-histo_DY[0]->GetBinContent(1))+
                            abs(histo_DY_LepEff3Up[0]->GetBinContent(1)-histo_DY[0]->GetBinContent(1))*abs(histo_DY_LepEff3Up[0]->GetBinContent(1)-histo_DY[0]->GetBinContent(1))+
                            abs(histo_DY_LepEff4Up[0]->GetBinContent(1)-histo_DY[0]->GetBinContent(1))*abs(histo_DY_LepEff4Up[0]->GetBinContent(1)-histo_DY[0]->GetBinContent(1))+
                            abs(histo_DY_LepEff5Up[0]->GetBinContent(1)-histo_DY[0]->GetBinContent(1))*abs(histo_DY_LepEff5Up[0]->GetBinContent(1)-histo_DY[0]->GetBinContent(1))+
                            abs(histo_DY_LepEff6Up[0]->GetBinContent(1)-histo_DY[0]->GetBinContent(1))*abs(histo_DY_LepEff6Up[0]->GetBinContent(1)-histo_DY[0]->GetBinContent(1))+
                            abs(histo_DY_LepEff7Up[0]->GetBinContent(1)-histo_DY[0]->GetBinContent(1))*abs(histo_DY_LepEff7Up[0]->GetBinContent(1)-histo_DY[0]->GetBinContent(1)))*100/histo_DY[0]->GetSumOfWeights();
    double recEffUnc =      abs(histo_DY_RecEffUp[0] ->GetBinContent(1)-histo_DY[0]->GetBinContent(1))*100/histo_DY[0]->GetSumOfWeights();                      
    double totalUnc = sqrt(momResUnc*momResUnc+lepEffUnc*lepEffUnc+recEffUnc*recEffUnc);
    double bkg = histo_Res->GetSumOfWeights()+histo_VV->GetSumOfWeights()+histo_NonFid->GetSumOfWeights();
    double theXS = (histo_Data->GetSumOfWeights()-bkg)/histo_DY[0]->GetSumOfWeights();
    printf("Unc: %.3f, %.3f, %.3f, %.3f, %.3f, %.3f, %.3f\n",
                abs(histo_DY_RecEffUp [0]->GetBinContent(1)-histo_DY[0]->GetBinContent(1))*100/histo_DY[0]->GetSumOfWeights(),
                abs(histo_DY_LepEff2Up[0]->GetBinContent(1)-histo_DY[0]->GetBinContent(1))*100/histo_DY[0]->GetSumOfWeights(),
                abs(histo_DY_LepEff3Up[0]->GetBinContent(1)-histo_DY[0]->GetBinContent(1))*100/histo_DY[0]->GetSumOfWeights(),
                abs(histo_DY_LepEff4Up[0]->GetBinContent(1)-histo_DY[0]->GetBinContent(1))*100/histo_DY[0]->GetSumOfWeights(),
                abs(histo_DY_LepEff5Up[0]->GetBinContent(1)-histo_DY[0]->GetBinContent(1))*100/histo_DY[0]->GetSumOfWeights(),
                abs(histo_DY_LepEff6Up[0]->GetBinContent(1)-histo_DY[0]->GetBinContent(1))*100/histo_DY[0]->GetSumOfWeights(),
                abs(histo_DY_LepEff7Up[0]->GetBinContent(1)-histo_DY[0]->GetBinContent(1))*100/histo_DY[0]->GetSumOfWeights()
                );
    printf("XS: %f (%.2f/%.2f/%.2f->%.2f)\n",theXS,momResUnc,lepEffUnc,recEffUnc,totalUnc);
  }


  char outputPlotName[200];
  sprintf(outputPlotName,"datacard_%s_%s.root",theHistName.Data(),chanName.Data());
  TFile* outFilePlots = new TFile(outputPlotName,"recreate");
  outFilePlots->cd();
  histo_Data  ->Write();
  histo_Res   ->Write();
  histo_VV    ->Write();
  histo_VV_vvNormPDFUp  ->Write();
  histo_VV_vvNormPDFDown->Write();
  histo_VV_vvNormQCDUp  ->Write();
  histo_VV_vvNormQCDDown->Write();
  histo_VV_MomRes1Up	->Write();
  histo_VV_MomRes1Down  ->Write();
  histo_VV_MomRes2Up	->Write();
  histo_VV_MomRes2Down  ->Write();
  histo_VV_MomRes3Up	->Write();
  histo_VV_MomRes3Down  ->Write();
  histo_VV_MomRes4Up	->Write();
  histo_VV_MomRes4Down  ->Write();
  histo_VV_LepEff1Up	->Write();
  histo_VV_LepEff1Down  ->Write();
  histo_VV_LepEff2Up	->Write();
  histo_VV_LepEff2Down  ->Write();
  histo_VV_LepEff3Up	->Write();
  histo_VV_LepEff3Down  ->Write();
  histo_VV_LepEff4Up	->Write();
  histo_VV_LepEff4Down  ->Write();
  histo_VV_LepEff5Up	->Write();
  histo_VV_LepEff5Down  ->Write();
  histo_VV_LepEff6Up	->Write();
  histo_VV_LepEff6Down  ->Write();
  histo_VV_LepEff7Up	->Write();
  histo_VV_LepEff7Down  ->Write();
  histo_VV_RecEffUp     ->Write();
  histo_VV_RecEffDown   ->Write();
  histo_NonFid->Write();
  for(int i=0; i<nChan; i++) {
    histo_DY[i]->Write();
  }
  histo_NonFid_altUp      ->Write();
  histo_NonFid_MomRes1Up  ->Write();
  histo_NonFid_MomRes2Up  ->Write();
  histo_NonFid_MomRes3Up  ->Write();
  histo_NonFid_MomRes4Up  ->Write();
  histo_NonFid_LepEff1Up  ->Write();
  histo_NonFid_LepEff2Up  ->Write();
  histo_NonFid_LepEff3Up  ->Write();
  histo_NonFid_LepEff4Up  ->Write();
  histo_NonFid_LepEff5Up  ->Write();
  histo_NonFid_LepEff6Up  ->Write();
  histo_NonFid_LepEff7Up  ->Write();
  histo_NonFid_RecEffUp   ->Write();
  histo_NonFid_altDown    ->Write();
  histo_NonFid_MomRes1Down->Write();
  histo_NonFid_MomRes2Down->Write();
  histo_NonFid_MomRes3Down->Write();
  histo_NonFid_MomRes4Down->Write();
  histo_NonFid_LepEff1Down->Write();
  histo_NonFid_LepEff2Down->Write();
  histo_NonFid_LepEff3Down->Write();
  histo_NonFid_LepEff4Down->Write();
  histo_NonFid_LepEff5Down->Write();
  histo_NonFid_LepEff6Down->Write();
  histo_NonFid_LepEff7Down->Write();
  histo_NonFid_RecEffDown ->Write();
  for(int i=0; i<nChan; i++) {
    histo_DY_altUp      [i]->Write();
    histo_DY_MomRes1Up  [i]->Write();
    histo_DY_MomRes2Up  [i]->Write();
    histo_DY_MomRes3Up  [i]->Write();
    histo_DY_MomRes4Up  [i]->Write();
    histo_DY_LepEff1Up  [i]->Write();
    histo_DY_LepEff2Up  [i]->Write();
    histo_DY_LepEff3Up  [i]->Write();
    histo_DY_LepEff4Up  [i]->Write();
    histo_DY_LepEff5Up  [i]->Write();
    histo_DY_LepEff6Up  [i]->Write();
    histo_DY_LepEff7Up  [i]->Write();
    histo_DY_RecEffUp   [i]->Write();
    histo_DY_altDown    [i]->Write();
    histo_DY_MomRes1Down[i]->Write();
    histo_DY_MomRes2Down[i]->Write();
    histo_DY_MomRes3Down[i]->Write();
    histo_DY_MomRes4Down[i]->Write();
    histo_DY_LepEff1Down[i]->Write();
    histo_DY_LepEff2Down[i]->Write();
    histo_DY_LepEff3Down[i]->Write();
    histo_DY_LepEff4Down[i]->Write();
    histo_DY_LepEff5Down[i]->Write();
    histo_DY_LepEff6Down[i]->Write();
    histo_DY_LepEff7Down[i]->Write();
    histo_DY_RecEffDown [i]->Write();
  }
  for(int i=0; i<nReco; i++) {  
    histo_VV_VVStatUp  [i]->Write();
    histo_VV_VVStatDown[i]->Write();
    histo_Res_ResStatUp  [i]->Write();
    histo_Res_ResStatDown[i]->Write();
    histo_NonFid_NonFidStatUp  [i]->Write();
    histo_NonFid_NonFidStatDown[i]->Write();
    for(int j=0; j<nChan; j++) {  
      histo_DY_DYStatUp  [j][i]->Write();
      histo_DY_DYStatDown[j][i]->Write();
    }
  }
  outFilePlots->Close();

  char outputLimitsCard[200];  					  
  sprintf(outputLimitsCard,"datacard_%s_%s.txt",theHistName.Data(),chanName.Data());
  ofstream newcardShape;
  newcardShape.open(outputLimitsCard);
  newcardShape << Form("imax * number of channels\n");
  newcardShape << Form("jmax * number of background minus 1\n");
  newcardShape << Form("kmax * number of nuisance parameters\n");

  newcardShape << Form("shapes    *   *   %s  histo_$PROCESS histo_$PROCESS_$SYSTEMATIC\n",outputPlotName);
  newcardShape << Form("shapes data_obs * %s  histo_Data \n",outputPlotName);

  newcardShape << Form("Observation %f\n",histo_Data->GetSumOfWeights());

  newcardShape << Form("bin   ");
  for (int i=0; i<nChan+3; i++){
    newcardShape << Form("ch1  ");
  }
  newcardShape << Form("\n");
 
  newcardShape << Form("process  ");
  for (int i=0; i<nChan; i++){
    newcardShape << Form("DY_%d  ",i);
  }
  newcardShape << Form("Res VV NonFid\n");

  newcardShape << Form("process  ");
  for (int i=0; i<nChan; i++){
    newcardShape << Form("%d  ",-1*i);
  }
  newcardShape << Form("1  2  3\n");

  newcardShape << Form("rate  ");
  for (int i=0; i<nChan; i++){
    newcardShape << Form("%f  ",histo_DY[i]->GetSumOfWeights());
  }
  newcardShape << Form("%f %f %f\n",histo_Res->GetSumOfWeights(),histo_VV->GetSumOfWeights(),histo_NonFid->GetSumOfWeights());

  newcardShape << Form("lumi    lnN     ");
  for (int i=0;i<nChan;i++){
    newcardShape << Form("%6.3f ",lumiE);
  }
  newcardShape << Form("-   %6.3f %6.3f\n",lumiE,lumiE);

  newcardShape << Form("resNorm    lnN     ");
  for (int i=0;i<nChan;i++){
    newcardShape << Form("- ");
  }
  newcardShape << Form("%f - - \n",1.05);

  newcardShape << Form("alt    shape     ");
  for (int i=0;i<nChan;i++){
    newcardShape << Form("1.0 ");
  }
  newcardShape << Form("- - 1.0\n");

  newcardShape << Form("MomRes1%s    shape     ",chanName.Data());
  for (int i=0;i<nChan;i++){
    newcardShape << Form("1.0 ");
  }
  newcardShape << Form("- 1.0 1.0\n");

  if(nsel == 0){ // only for muons
    newcardShape << Form("MomRes2%s    shape     ",chanName.Data());
    for (int i=0;i<nChan;i++){
      newcardShape << Form("1.0 ");
    }
    newcardShape << Form("- 1.0 1.0\n");

    newcardShape << Form("MomRes3%s    shape     ",chanName.Data());
    for (int i=0;i<nChan;i++){
      newcardShape << Form("1.0 ");
    }
    newcardShape << Form("- 1.0 1.0\n");

    newcardShape << Form("MomRes4%s    shape     ",chanName.Data());
    for (int i=0;i<nChan;i++){
      newcardShape << Form("1.0 ");
    }
    newcardShape << Form("- 1.0 1.0\n");
  }

  //newcardShape << Form("LepEff1%s    shape     ",chanName.Data());
  //for (int i=0;i<nChan;i++){
  //  newcardShape << Form("1.0 ");
  //}
  //newcardShape << Form("- 1.0 1.0\n");

  newcardShape << Form("LepEff2%s    shape     ",chanName.Data());
  for (int i=0;i<nChan;i++){
    newcardShape << Form("1.0 ");
  }
  newcardShape << Form("- 1.0 1.0\n");

  newcardShape << Form("LepEff3%s    shape     ",chanName.Data());
  for (int i=0;i<nChan;i++){
    newcardShape << Form("1.0 ");
  }
  newcardShape << Form("- 1.0 1.0\n");

  newcardShape << Form("LepEff4%s    shape     ",chanName.Data());
  for (int i=0;i<nChan;i++){
    newcardShape << Form("1.0 ");
  }
  newcardShape << Form("- 1.0 1.0\n");

  newcardShape << Form("LepEff5%s    shape     ",chanName.Data());
  for (int i=0;i<nChan;i++){
    newcardShape << Form("1.0 ");
  }
  newcardShape << Form("- 1.0 1.0\n");

  newcardShape << Form("LepEff6%s    shape     ",chanName.Data());
  for (int i=0;i<nChan;i++){
    newcardShape << Form("1.0 ");
  }
  newcardShape << Form("- 1.0 1.0\n");

  newcardShape << Form("LepEff7%s    shape     ",chanName.Data());
  for (int i=0;i<nChan;i++){
    newcardShape << Form("1.0 ");
  }
  newcardShape << Form("- 1.0 1.0\n");

  newcardShape << Form("RecEff%s    shape     ",chanName.Data());
  for (int i=0;i<nChan;i++){
    newcardShape << Form("1.0 ");
  }
  newcardShape << Form("- 1.0 1.0\n");

  newcardShape << Form("vvNormPDF    shape     ");
  for (int i=0;i<nChan;i++){
    newcardShape << Form("- ");
  }
  newcardShape << Form("- 1.0 -\n");

  newcardShape << Form("vvNormQCD    shape     ");
  for (int i=0;i<nChan;i++){
    newcardShape << Form("- ");
  }
  newcardShape << Form("- 1.0 -\n");

  for (int i=0; i<nReco; i++) {
    if(histo_Res->GetBinContent(i+1) > 0 && histo_Res->GetBinError(i+1)/histo_Res->GetBinContent(i+1) > 0.005){
      newcardShape << Form("ResStat_%d%s    shape     ",i,chanName.Data());
      for (int i=0;i<nChan;i++){
        newcardShape << Form("- ");
      }
      newcardShape << Form("1.0 - -\n");
    }
  }

  for (int i=0; i<nReco; i++) {  
    if(histo_VV->GetBinContent(i+1) > 0 && histo_VV->GetBinError(i+1)/histo_VV->GetBinContent(i+1) > 0.005){
      newcardShape << Form("VVStat_%d%s    shape     ",i,chanName.Data());
      for (int i=0;i<nChan;i++){
        newcardShape << Form("- ");
      }
      newcardShape << Form("- 1.0 -\n");
    }
  }

  for (int i=0; i<nReco; i++) {  
    if(histo_NonFid->GetBinContent(i+1) > 0 && histo_NonFid->GetBinError(i+1)/histo_NonFid->GetBinContent(i+1) > 0.005){
      newcardShape << Form("NonFidStat_%d%s    shape     ",i,chanName.Data());
      for (int i=0;i<nChan;i++){
        newcardShape << Form("- ");
      }
      newcardShape << Form("- - 1.0\n");
    }
  }

  for (int j=0; j<nChan; j++) {  
    for (int i=0; i<nReco; i++) {  
      if(histo_DY[j]->GetBinContent(i+1) > 0 && histo_DY[j]->GetBinError(i+1)/histo_DY[j]->GetBinContent(i+1) > 0.005){
        newcardShape << Form("DYStat_%d_%d%s    shape     ",j,i,chanName.Data());
        for (int k=0; k<nChan; k++) {
          if(j==k) newcardShape << Form("1.0 ");
          else     newcardShape << Form("- ");
        }
        newcardShape << Form("- - -\n");
      }
    }
  }

  newcardShape.close();

}
