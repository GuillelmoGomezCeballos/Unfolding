void makeWWNtuple(){

  for(int nsel=0; nsel<4; nsel++) {
    TString outNtuplename = "test.root";
    if     (nsel == 0){
      outNtuplename = "higgsCombinetest_ww_mll.MultiDimFit.mH120_normalized.root";
    }
    else if(nsel == 1){
      outNtuplename = "higgsCombinetest_ww_ptl1.MultiDimFit.mH120_normalized.root";
    }
    else if(nsel == 2){
      outNtuplename = "higgsCombinetest_ww_ptl2.MultiDimFit.mH120_normalized.root";
    }
    else if(nsel == 3){
      outNtuplename = "higgsCombinetest_ww_phill.MultiDimFit.mH120_normalized.root";
    }

    TFile *outtuple = TFile::Open(outNtuplename.Data(),"recreate");
    TNtuple *nt = new TNtuple("limit","limit","r_s0:r_s1:r_s2:r_s3:r_s4:r_s5:r_s6:r_s7:r_s8");

    double rs[9],rsUp[9],rsDown[9];

    double rsMLL[9]        = {0.873,0.913,1.152,0.917,1.010,1.002,1.012,0.958,0.871};
    double rsMLLUp[9]      = {0.077,0.062,0.047,0.059,0.061,0.057,0.052,0.059,0.059};
    double rsMLLDown[9]    = {0.077,0.062,0.047,0.059,0.061,0.057,0.052,0.059,0.059};
    double rsPTL1[9]       = {0.873,0.913,1.152,0.917,1.010,1.002,1.012,0.958,0.871};//fake
    double rsPTL1Up[9]     = {0.077,0.062,0.047,0.059,0.061,0.057,0.052,0.059,0.059};//fake
    double rsPTL1Down[9]   = {0.077,0.062,0.047,0.059,0.061,0.057,0.052,0.059,0.059};//fake
    double rsPTL2[9]       = {0.984,0.938,0.998,1.094,0.900,1.135,0.996,0.996,0.688};
    double rsPTL2Up[9]     = {0.079,0.044,0.040,0.046,0.067,0.064,0.045,0.045,0.143};
    double rsPTL2Down[9]   = {0.079,0.044,0.040,0.046,0.067,0.064,0.045,0.045,0.143};
    double rsDPHILL[9]     = {0.873,0.913,1.152,0.917,1.010,1.002,1.012,0.958,0.871};//fake
    double rsDPHILLUp[9]   = {0.077,0.062,0.047,0.059,0.061,0.057,0.052,0.059,0.059};//fake
    double rsDPHILLDown[9] = {0.077,0.062,0.047,0.059,0.061,0.057,0.052,0.059,0.059};//fake

    for(int i=0; i<9; i++){
      if     (nsel == 0){
	rs[i] = rsMLL[i];  rsUp[i] = rsMLLUp[i]; rsDown[i] = rsMLLDown[i]; 
      }
      else if(nsel == 1){
	rs[i] = rsPTL1[i];  rsUp[i] = rsPTL1Up[i]; rsDown[i] = rsPTL1Down[i]; 
      }
      else if(nsel == 2){
	rs[i] = rsPTL2[i];  rsUp[i] = rsPTL2Up[i]; rsDown[i] = rsPTL2Down[i]; 
      }
      else if(nsel == 3){
	rs[i] = rsDPHILL[i];  rsUp[i] = rsDPHILLUp[i]; rsDown[i] = rsDPHILLDown[i]; 
      }

      rsUp[i]   = rs[i] + rsUp[i];
      rsDown[i] = rs[i] - rsDown[i];
    }

    nt->Fill(rs[0],rs[1],rs[2],rs[3],rs[4],rs[5],rs[6],rs[7],rs[8]);
    nt->Fill(rsUp[0],rsUp[1],rsUp[2],rsUp[3],rsUp[4],rsUp[5],rsUp[6],rsUp[7],rsUp[8]);
    nt->Fill(rsDown[0],rsDown[1],rsDown[2],rsDown[3],rsDown[4],rsDown[5],rsDown[6],rsDown[7],rsDown[8]);
    nt->Write();
    outtuple->Close();
  }
}
