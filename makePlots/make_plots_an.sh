root -l -b -q finalPlotUnfolding.C+'(0,1,"p_{T}","GeV","../macros/outputs/histoUnfoldingSystPt","ratio_unf_zmm_dy_pt", 1,1,"Pt","MM")'
root -l -b -q finalPlotUnfolding.C+'(0,1,"p_{T}","GeV","../macros/outputs/histoUnfoldingSystPt","ratio_unf_zee_dy_pt", 1,1,"Pt","EE")'
root -l -b -q finalPlotUnfolding.C+'(0,1,"p_{T}","GeV","../macros/outputs/histoUnfoldingSystPt","ratio_unf_zll_dy_pt", 1,1,"Pt","LL")'
root -l -b -q finalPlotUnfolding.C+'(0,1,"|y_{ll}|","","../macros/outputs/histoUnfoldingSystRap","ratio_unf_zmm_dy_rap", 0,0,"Rap","MM")'
root -l -b -q finalPlotUnfolding.C+'(0,1,"|y_{ll}|","","../macros/outputs/histoUnfoldingSystRap","ratio_unf_zee_dy_rap", 0,0,"Rap","EE")'
root -l -b -q finalPlotUnfolding.C+'(0,1,"|y_{ll}|","","../macros/outputs/histoUnfoldingSystRap","ratio_unf_zll_dy_rap", 0,0,"Rap","LL")'
root -l -b -q finalPlotUnfolding.C+'(0,1,"#phi_{#eta}*","","../macros/outputs/histoUnfoldingSystPhiStar","ratio_unf_zmm_dy_phistar", 1,1,"PhiStar","MM")'
root -l -b -q finalPlotUnfolding.C+'(0,1,"#phi_{#eta}*","","../macros/outputs/histoUnfoldingSystPhiStar","ratio_unf_zee_dy_phistar", 1,1,"PhiStar","EE")'
root -l -b -q finalPlotUnfolding.C+'(0,1,"#phi_{#eta}*","","../macros/outputs/histoUnfoldingSystPhiStar","ratio_unf_zll_dy_phistar", 1,1,"PhiStar","LL")'
root -l -b -q finalPlotUnfolding.C+'(0,1,"p_{T}","GeV","../macros/outputs/histoUnfoldingSystPtRap0","ratio_unf_zmm_dy_ptrap0", 1,1,"PtRap0","MM")'
root -l -b -q finalPlotUnfolding.C+'(0,1,"p_{T}","GeV","../macros/outputs/histoUnfoldingSystPtRap0","ratio_unf_zee_dy_ptrap0", 1,1,"PtRap0","EE")'
root -l -b -q finalPlotUnfolding.C+'(0,1,"p_{T}","GeV","../macros/outputs/histoUnfoldingSystPtRap0","ratio_unf_zll_dy_ptrap0", 1,1,"PtRap0","LL")'
root -l -b -q finalPlotUnfolding.C+'(0,1,"p_{T}","GeV","../macros/outputs/histoUnfoldingSystPtRap1","ratio_unf_zmm_dy_ptrap1", 1,1,"PtRap1","MM")'
root -l -b -q finalPlotUnfolding.C+'(0,1,"p_{T}","GeV","../macros/outputs/histoUnfoldingSystPtRap1","ratio_unf_zee_dy_ptrap1", 1,1,"PtRap1","EE")'
root -l -b -q finalPlotUnfolding.C+'(0,1,"p_{T}","GeV","../macros/outputs/histoUnfoldingSystPtRap1","ratio_unf_zll_dy_ptrap1", 1,1,"PtRap1","LL")'
root -l -b -q finalPlotUnfolding.C+'(0,1,"p_{T}","GeV","../macros/outputs/histoUnfoldingSystPtRap2","ratio_unf_zmm_dy_ptrap2", 1,1,"PtRap2","MM")'
root -l -b -q finalPlotUnfolding.C+'(0,1,"p_{T}","GeV","../macros/outputs/histoUnfoldingSystPtRap2","ratio_unf_zee_dy_ptrap2", 1,1,"PtRap2","EE")'
root -l -b -q finalPlotUnfolding.C+'(0,1,"p_{T}","GeV","../macros/outputs/histoUnfoldingSystPtRap2","ratio_unf_zll_dy_ptrap2", 1,1,"PtRap2","LL")'
root -l -b -q finalPlotUnfolding.C+'(0,1,"p_{T}","GeV","../macros/outputs/histoUnfoldingSystPtRap3","ratio_unf_zmm_dy_ptrap3", 1,1,"PtRap3","MM")'
root -l -b -q finalPlotUnfolding.C+'(0,1,"p_{T}","GeV","../macros/outputs/histoUnfoldingSystPtRap3","ratio_unf_zee_dy_ptrap3", 1,1,"PtRap3","EE")'
root -l -b -q finalPlotUnfolding.C+'(0,1,"p_{T}","GeV","../macros/outputs/histoUnfoldingSystPtRap3","ratio_unf_zll_dy_ptrap3", 1,1,"PtRap3","LL")'
root -l -b -q finalPlotUnfolding.C+'(0,1,"p_{T}","GeV","../macros/outputs/histoUnfoldingSystPtRap4","ratio_unf_zmm_dy_ptrap4", 1,1,"PtRap4","MM")'
root -l -b -q finalPlotUnfolding.C+'(0,1,"p_{T}","GeV","../macros/outputs/histoUnfoldingSystPtRap4","ratio_unf_zee_dy_ptrap4", 1,1,"PtRap4","EE")'
root -l -b -q finalPlotUnfolding.C+'(0,1,"p_{T}","GeV","../macros/outputs/histoUnfoldingSystPtRap4","ratio_unf_zll_dy_ptrap4", 1,1,"PtRap4","LL")'

#root -l -b -q ratio_test.C+'(0,1,"p_{T}","GeV","../macros/outputs/histoUnfoldingSystPt","ratio_unf_zmm_dy_pt", 1,1,"Pt","MM")'

root -l -b -q double_ratio_test.C+'(0,1,"p_{T}","GeV","../macros/outputs/histoUnfoldingSystPt","double_ratio_unf_zll_dy_pt", 1,1,"Pt")'
root -l -b -q double_ratio_test.C+'(0,1,"|y_{ll}|","","../macros/outputs/histoUnfoldingSystRap","double_ratio_unf_zll_dy_rap", 0,0,"Rap")'
root -l -b -q double_ratio_test.C+'(0,1,"#phi_{#eta}*","","../macros/outputs/histoUnfoldingSystPhiStar","double_ratio_unf_zll_dy_phistar", 1,1,"PhiStar")'
root -l -b -q double_ratio_test.C+'(0,1,"p_{T}","GeV","../macros/outputs/histoUnfoldingSystPtRap0","double_ratio_unf_zll_dy_ptrap0", 1,1,"PtRap0")'
root -l -b -q double_ratio_test.C+'(0,1,"p_{T}","GeV","../macros/outputs/histoUnfoldingSystPtRap1","double_ratio_unf_zll_dy_ptrap1", 1,1,"PtRap1")'
root -l -b -q double_ratio_test.C+'(0,1,"p_{T}","GeV","../macros/outputs/histoUnfoldingSystPtRap2","double_ratio_unf_zll_dy_ptrap2", 1,1,"PtRap2")'
root -l -b -q double_ratio_test.C+'(0,1,"p_{T}","GeV","../macros/outputs/histoUnfoldingSystPtRap3","double_ratio_unf_zll_dy_ptrap3", 1,1,"PtRap3")'
root -l -b -q double_ratio_test.C+'(0,1,"p_{T}","GeV","../macros/outputs/histoUnfoldingSystPtRap4","double_ratio_unf_zll_dy_ptrap4", 1,1,"PtRap4")'

root -l -b -q finalPlotUnfolding.C+'(0,1,"p_{T}","GeV","../macros/outputs/histoUnfolding_XSRatioSystPt","ratio_unf_normalized_zmm_dy_pt", 1,1,"Pt","MM",1)'
root -l -b -q finalPlotUnfolding.C+'(0,1,"p_{T}","GeV","../macros/outputs/histoUnfolding_XSRatioSystPt","ratio_unf_normalized_zee_dy_pt", 1,1,"Pt","EE",1)'
root -l -b -q finalPlotUnfolding.C+'(0,1,"p_{T}","GeV","../macros/outputs/histoUnfolding_XSRatioSystPt","ratio_unf_normalized_zll_dy_pt", 1,1,"Pt","LL",1)'
root -l -b -q finalPlotUnfolding.C+'(0,1,"|y_{ll}|","","../macros/outputs/histoUnfolding_XSRatioSystRap","ratio_unf_normalized_zmm_dy_rap", 0,0,"Rap","MM",1)'
root -l -b -q finalPlotUnfolding.C+'(0,1,"|y_{ll}|","","../macros/outputs/histoUnfolding_XSRatioSystRap","ratio_unf_normalized_zee_dy_rap", 0,0,"Rap","EE",1)'
root -l -b -q finalPlotUnfolding.C+'(0,1,"|y_{ll}|","","../macros/outputs/histoUnfolding_XSRatioSystRap","ratio_unf_normalized_zll_dy_rap", 0,0,"Rap","LL",1)'
root -l -b -q finalPlotUnfolding.C+'(0,1,"#phi_{#eta}*","","../macros/outputs/histoUnfolding_XSRatioSystPhiStar","ratio_unf_normalized_zmm_dy_phistar", 1,1,"PhiStar","MM",1)'
root -l -b -q finalPlotUnfolding.C+'(0,1,"#phi_{#eta}*","","../macros/outputs/histoUnfolding_XSRatioSystPhiStar","ratio_unf_normalized_zee_dy_phistar", 1,1,"PhiStar","EE",1)'
root -l -b -q finalPlotUnfolding.C+'(0,1,"#phi_{#eta}*","","../macros/outputs/histoUnfolding_XSRatioSystPhiStar","ratio_unf_normalized_zll_dy_phistar", 1,1,"PhiStar","LL",1)'
root -l -b -q finalPlotUnfolding.C+'(0,1,"p_{T}","GeV","../macros/outputs/histoUnfolding_XSRatioSystPtRap0","ratio_unf_normalized_zmm_dy_ptrap0", 1,1,"PtRap0","MM",1)'
root -l -b -q finalPlotUnfolding.C+'(0,1,"p_{T}","GeV","../macros/outputs/histoUnfolding_XSRatioSystPtRap0","ratio_unf_normalized_zee_dy_ptrap0", 1,1,"PtRap0","EE",1)'
root -l -b -q finalPlotUnfolding.C+'(0,1,"p_{T}","GeV","../macros/outputs/histoUnfolding_XSRatioSystPtRap0","ratio_unf_normalized_zll_dy_ptrap0", 1,1,"PtRap0","LL",1)'
root -l -b -q finalPlotUnfolding.C+'(0,1,"p_{T}","GeV","../macros/outputs/histoUnfolding_XSRatioSystPtRap1","ratio_unf_normalized_zmm_dy_ptrap1", 1,1,"PtRap1","MM",1)'
root -l -b -q finalPlotUnfolding.C+'(0,1,"p_{T}","GeV","../macros/outputs/histoUnfolding_XSRatioSystPtRap1","ratio_unf_normalized_zee_dy_ptrap1", 1,1,"PtRap1","EE",1)'
root -l -b -q finalPlotUnfolding.C+'(0,1,"p_{T}","GeV","../macros/outputs/histoUnfolding_XSRatioSystPtRap1","ratio_unf_normalized_zll_dy_ptrap1", 1,1,"PtRap1","LL",1)'
root -l -b -q finalPlotUnfolding.C+'(0,1,"p_{T}","GeV","../macros/outputs/histoUnfolding_XSRatioSystPtRap2","ratio_unf_normalized_zmm_dy_ptrap2", 1,1,"PtRap2","MM",1)'
root -l -b -q finalPlotUnfolding.C+'(0,1,"p_{T}","GeV","../macros/outputs/histoUnfolding_XSRatioSystPtRap2","ratio_unf_normalized_zee_dy_ptrap2", 1,1,"PtRap2","EE",1)'
root -l -b -q finalPlotUnfolding.C+'(0,1,"p_{T}","GeV","../macros/outputs/histoUnfolding_XSRatioSystPtRap2","ratio_unf_normalized_zll_dy_ptrap2", 1,1,"PtRap2","LL",1)'
root -l -b -q finalPlotUnfolding.C+'(0,1,"p_{T}","GeV","../macros/outputs/histoUnfolding_XSRatioSystPtRap3","ratio_unf_normalized_zmm_dy_ptrap3", 1,1,"PtRap3","MM",1)'
root -l -b -q finalPlotUnfolding.C+'(0,1,"p_{T}","GeV","../macros/outputs/histoUnfolding_XSRatioSystPtRap3","ratio_unf_normalized_zee_dy_ptrap3", 1,1,"PtRap3","EE",1)'
root -l -b -q finalPlotUnfolding.C+'(0,1,"p_{T}","GeV","../macros/outputs/histoUnfolding_XSRatioSystPtRap3","ratio_unf_normalized_zll_dy_ptrap3", 1,1,"PtRap3","LL",1)'
root -l -b -q finalPlotUnfolding.C+'(0,1,"p_{T}","GeV","../macros/outputs/histoUnfolding_XSRatioSystPtRap4","ratio_unf_normalized_zmm_dy_ptrap4", 1,1,"PtRap4","MM",1)'
root -l -b -q finalPlotUnfolding.C+'(0,1,"p_{T}","GeV","../macros/outputs/histoUnfolding_XSRatioSystPtRap4","ratio_unf_normalized_zee_dy_ptrap4", 1,1,"PtRap4","EE",1)'
root -l -b -q finalPlotUnfolding.C+'(0,1,"p_{T}","GeV","../macros/outputs/histoUnfolding_XSRatioSystPtRap4","ratio_unf_normalized_zll_dy_ptrap4", 1,1,"PtRap4","LL",1)'

#root -l -b -q ratio_test.C+'(0,1,"p_{T}","GeV","../macros/outputs/histoUnfolding_XSRatioSystPt","ratio_unf_normalized_zmm_dy_pt", 1,1,"Pt","MM",1)'

root -l -b -q matrix.C'("SystPt")';
root -l -b -q convert.C'("SystPt","totsum")';
root -l -b -q convert.C'("SystPt","lepeff")';
root -l -b -q convert.C'("SystPt","lepeffSyst")';
root -l -b -q convert.C'("SystPt","lepeffStat")';
root -l -b -q convert.C'("SystPt","momres")';

root -l -b -q matrix.C'("SystPt","../macros/folders_dressedleptons/outputs/")';
root -l -b -q matrix.C'("SystPhiStar","../macros/folders_dressedleptons/outputs/")';
root -l -b -q matrix.C'("SystRap","../macros/folders_dressedleptons/outputs/")';
root -l -b -q matrix.C'("SystPtRap0","../macros/folders_dressedleptons/outputs/")';
root -l -b -q matrix.C'("SystPtRap1","../macros/folders_dressedleptons/outputs/")';
root -l -b -q matrix.C'("SystPtRap2","../macros/folders_dressedleptons/outputs/")';
root -l -b -q matrix.C'("SystPtRap3","../macros/folders_dressedleptons/outputs/")';
root -l -b -q matrix.C'("SystPtRap4","../macros/folders_dressedleptons/outputs/")';

root -l -b -q matrix.C'("_XSRatioSystPt","../macros/folders_dressedleptons/outputs/")';
root -l -b -q matrix.C'("_XSRatioSystPhiStar","../macros/folders_dressedleptons/outputs/")';
root -l -b -q matrix.C'("_XSRatioSystRap","../macros/folders_dressedleptons/outputs/")';
root -l -b -q matrix.C'("_XSRatioSystPtRap0","../macros/folders_dressedleptons/outputs/")';
root -l -b -q matrix.C'("_XSRatioSystPtRap1","../macros/folders_dressedleptons/outputs/")';
root -l -b -q matrix.C'("_XSRatioSystPtRap2","../macros/folders_dressedleptons/outputs/")';
root -l -b -q matrix.C'("_XSRatioSystPtRap3","../macros/folders_dressedleptons/outputs/")';
root -l -b -q matrix.C'("_XSRatioSystPtRap4","../macros/folders_dressedleptons/outputs/")';

root -l -b -q matrix.C'("SystPt","../macros/folders_bornleptons/outputs/")';
root -l -b -q matrix.C'("SystPhiStar","../macros/folders_bornleptons/outputs/")';
root -l -b -q matrix.C'("SystRap","../macros/folders_bornleptons/outputs/")';
root -l -b -q matrix.C'("SystPtRap0","../macros/folders_bornleptons/outputs/")';
root -l -b -q matrix.C'("SystPtRap1","../macros/folders_bornleptons/outputs/")';
root -l -b -q matrix.C'("SystPtRap2","../macros/folders_bornleptons/outputs/")';
root -l -b -q matrix.C'("SystPtRap3","../macros/folders_bornleptons/outputs/")';
root -l -b -q matrix.C'("SystPtRap4","../macros/folders_bornleptons/outputs/")';

root -l -b -q matrix.C'("_XSRatioSystPt","../macros/folders_bornleptons/outputs/")';
root -l -b -q matrix.C'("_XSRatioSystPhiStar","../macros/folders_bornleptons/outputs/")';
root -l -b -q matrix.C'("_XSRatioSystRap","../macros/folders_bornleptons/outputs/")';
root -l -b -q matrix.C'("_XSRatioSystPtRap0","../macros/folders_bornleptons/outputs/")';
root -l -b -q matrix.C'("_XSRatioSystPtRap1","../macros/folders_bornleptons/outputs/")';
root -l -b -q matrix.C'("_XSRatioSystPtRap2","../macros/folders_bornleptons/outputs/")';
root -l -b -q matrix.C'("_XSRatioSystPtRap3","../macros/folders_bornleptons/outputs/")';
root -l -b -q matrix.C'("_XSRatioSystPtRap4","../macros/folders_bornleptons/outputs/")';
