root -l -b -q finalPlotUnfolding.C+'(0,1,"p_{T}","GeV","../macros/outputs/histoUnfoldingSystPt","ratio_unf_zmm_dy_pt", 1,1,"Pt","MM")'
root -l -b -q finalPlotUnfolding.C+'(0,1,"p_{T}","GeV","../macros/outputs/histoUnfoldingSystPt","ratio_unf_zee_dy_pt", 1,1,"Pt","EE")'
root -l -b -q finalPlotUnfolding.C+'(0,1,"|y_{ll}|","","../macros/outputs/histoUnfoldingSystRap","ratio_unf_zmm_dy_rap", 0,0,"Rap","MM")'
root -l -b -q finalPlotUnfolding.C+'(0,1,"|y_{ll}|","","../macros/outputs/histoUnfoldingSystRap","ratio_unf_zee_dy_rap", 0,0,"Rap","EE")'
root -l -b -q finalPlotUnfolding.C+'(0,1,"#phi_{#eta}*","","../macros/outputs/histoUnfoldingSystPhiStar","ratio_unf_zmm_dy_phistar", 1,1,"PhiStar","MM")'
root -l -b -q finalPlotUnfolding.C+'(0,1,"#phi_{#eta}*","","../macros/outputs/histoUnfoldingSystPhiStar","ratio_unf_zee_dy_phistar", 1,1,"PhiStar","EE")'
root -l -b -q finalPlotUnfolding.C+'(0,1,"p_{T}","GeV","../macros/outputs/histoUnfoldingSystPtRap0","ratio_unf_zmm_dy_ptrap0", 1,1,"PtRap0","MM")'
root -l -b -q finalPlotUnfolding.C+'(0,1,"p_{T}","GeV","../macros/outputs/histoUnfoldingSystPtRap0","ratio_unf_zee_dy_ptrap0", 1,1,"PtRap0","EE")'
root -l -b -q finalPlotUnfolding.C+'(0,1,"p_{T}","GeV","../macros/outputs/histoUnfoldingSystPtRap1","ratio_unf_zmm_dy_ptrap1", 1,1,"PtRap1","MM")'
root -l -b -q finalPlotUnfolding.C+'(0,1,"p_{T}","GeV","../macros/outputs/histoUnfoldingSystPtRap1","ratio_unf_zee_dy_ptrap1", 1,1,"PtRap1","EE")'
root -l -b -q finalPlotUnfolding.C+'(0,1,"p_{T}","GeV","../macros/outputs/histoUnfoldingSystPtRap2","ratio_unf_zmm_dy_ptrap2", 1,1,"PtRap2","MM")'
root -l -b -q finalPlotUnfolding.C+'(0,1,"p_{T}","GeV","../macros/outputs/histoUnfoldingSystPtRap2","ratio_unf_zee_dy_ptrap2", 1,1,"PtRap2","EE")'
root -l -b -q finalPlotUnfolding.C+'(0,1,"p_{T}","GeV","../macros/outputs/histoUnfoldingSystPtRap3","ratio_unf_zmm_dy_ptrap3", 1,1,"PtRap3","MM")'
root -l -b -q finalPlotUnfolding.C+'(0,1,"p_{T}","GeV","../macros/outputs/histoUnfoldingSystPtRap3","ratio_unf_zee_dy_ptrap3", 1,1,"PtRap3","EE")'
root -l -b -q finalPlotUnfolding.C+'(0,1,"p_{T}","GeV","../macros/outputs/histoUnfoldingSystPtRap4","ratio_unf_zmm_dy_ptrap4", 1,1,"PtRap4","MM")'
root -l -b -q finalPlotUnfolding.C+'(0,1,"p_{T}","GeV","../macros/outputs/histoUnfoldingSystPtRap4","ratio_unf_zee_dy_ptrap4", 1,1,"PtRap4","EE")'

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
root -l -b -q finalPlotUnfolding.C+'(0,1,"|y_{ll}|","","../macros/outputs/histoUnfolding_XSRatioSystRap","ratio_unf_normalized_zmm_dy_rap", 0,0,"Rap","MM",1)'
root -l -b -q finalPlotUnfolding.C+'(0,1,"|y_{ll}|","","../macros/outputs/histoUnfolding_XSRatioSystRap","ratio_unf_normalized_zee_dy_rap", 0,0,"Rap","EE",1)'
root -l -b -q finalPlotUnfolding.C+'(0,1,"#phi_{#eta}*","","../macros/outputs/histoUnfolding_XSRatioSystPhiStar","ratio_unf_normalized_zmm_dy_phistar", 1,1,"PhiStar","MM",1)'
root -l -b -q finalPlotUnfolding.C+'(0,1,"#phi_{#eta}*","","../macros/outputs/histoUnfolding_XSRatioSystPhiStar","ratio_unf_normalized_zee_dy_phistar", 1,1,"PhiStar","EE",1)'
root -l -b -q finalPlotUnfolding.C+'(0,1,"p_{T}","GeV","../macros/outputs/histoUnfolding_XSRatioSystPtRap0","ratio_unf_normalized_zmm_dy_ptrap0", 1,1,"PtRap0","MM",1)'
root -l -b -q finalPlotUnfolding.C+'(0,1,"p_{T}","GeV","../macros/outputs/histoUnfolding_XSRatioSystPtRap0","ratio_unf_normalized_zee_dy_ptrap0", 1,1,"PtRap0","EE",1)'
root -l -b -q finalPlotUnfolding.C+'(0,1,"p_{T}","GeV","../macros/outputs/histoUnfolding_XSRatioSystPtRap1","ratio_unf_normalized_zmm_dy_ptrap1", 1,1,"PtRap1","MM",1)'
root -l -b -q finalPlotUnfolding.C+'(0,1,"p_{T}","GeV","../macros/outputs/histoUnfolding_XSRatioSystPtRap1","ratio_unf_normalized_zee_dy_ptrap1", 1,1,"PtRap1","EE",1)'
root -l -b -q finalPlotUnfolding.C+'(0,1,"p_{T}","GeV","../macros/outputs/histoUnfolding_XSRatioSystPtRap2","ratio_unf_normalized_zmm_dy_ptrap2", 1,1,"PtRap2","MM",1)'
root -l -b -q finalPlotUnfolding.C+'(0,1,"p_{T}","GeV","../macros/outputs/histoUnfolding_XSRatioSystPtRap2","ratio_unf_normalized_zee_dy_ptrap2", 1,1,"PtRap2","EE",1)'
root -l -b -q finalPlotUnfolding.C+'(0,1,"p_{T}","GeV","../macros/outputs/histoUnfolding_XSRatioSystPtRap3","ratio_unf_normalized_zmm_dy_ptrap3", 1,1,"PtRap3","MM",1)'
root -l -b -q finalPlotUnfolding.C+'(0,1,"p_{T}","GeV","../macros/outputs/histoUnfolding_XSRatioSystPtRap3","ratio_unf_normalized_zee_dy_ptrap3", 1,1,"PtRap3","EE",1)'
root -l -b -q finalPlotUnfolding.C+'(0,1,"p_{T}","GeV","../macros/outputs/histoUnfolding_XSRatioSystPtRap4","ratio_unf_normalized_zmm_dy_ptrap4", 1,1,"PtRap4","MM",1)'
root -l -b -q finalPlotUnfolding.C+'(0,1,"p_{T}","GeV","../macros/outputs/histoUnfolding_XSRatioSystPtRap4","ratio_unf_normalized_zee_dy_ptrap4", 1,1,"PtRap4","EE",1)'

#root -l -b -q ratio_test.C+'(0,1,"p_{T}","GeV","../macros/outputs/histoUnfolding_XSRatioSystPt","ratio_unf_normalized_zmm_dy_pt", 1,1,"Pt","MM",1)'

root -l -b -q matrix.C'("Pt")';
root -l -b -q convert.C'("Pt","totsum")';
root -l -b -q convert.C'("Pt","lepeff")';
root -l -b -q convert.C'("Pt","lepeffSyst")';
root -l -b -q convert.C'("Pt","lepeffStat")';
root -l -b -q convert.C'("Pt","momres")';
