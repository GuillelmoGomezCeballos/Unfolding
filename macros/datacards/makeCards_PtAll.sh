#!/bin/sh

root -q -b -l testAnalysis_test.C+'(0,3,0,"PtAll",1)';
root -q -b -l testAnalysis_test.C+'(1,3,0,"PtAll",1)';


grep -v lumi_13TeV datacard_Pt_mm.txt > lll; mv lll datacard_Pt_mm.txt;
grep -v lumi_13TeV datacard_Pt_ee.txt > lll; mv lll datacard_Pt_ee.txt;

combineCards.py -S datacard_Pt_mm.txt > datacard_Pt_mm.text;
combineCards.py -S datacard_Pt_ee.txt > datacard_Pt_ee.text;
combineCards.py -S datacard_Pt_mm.txt datacard_Pt_ee.txt > datacard_Pt_ll.text;

text2workspace.py -P HiggsAnalysis.CombinedLimit.PhysicsModel:multiSignalModel --PO verbose  \
--PO 'map=.*/DY_0:r_s0[1,0,10]'  \
--PO 'map=.*/DY_1:r_s1[1,0,10]'  \
--PO 'map=.*/DY_2:r_s2[1,0,10]'  \
--PO 'map=.*/DY_3:r_s3[1,0,10]'  \
--PO 'map=.*/DY_4:r_s4[1,0,10]'  \
--PO 'map=.*/DY_5:r_s5[1,0,10]'  \
--PO 'map=.*/DY_6:r_s6[1,0,10]'  \
--PO 'map=.*/DY_7:r_s7[1,0,10]'  \
--PO 'map=.*/DY_8:r_s8[1,0,10]'  \
--PO 'map=.*/DY_9:r_s9[1,0,10]'  \
--PO 'map=.*/DY_10:r_s10[1,0,10]'  \
--PO 'map=.*/DY_11:r_s11[1,0,10]'  \
--PO 'map=.*/DY_12:r_s12[1,0,10]'  \
--PO 'map=.*/DY_13:r_s13[1,0,10]'  \
--PO 'map=.*/DY_14:r_s14[1,0,10]'  \
--PO 'map=.*/DY_15:r_s15[1,0,10]'  \
--PO 'map=.*/DY_16:r_s16[1,0,10]'  \
--PO 'map=.*/DY_17:r_s17[1,0,10]'  \
--PO 'map=.*/DY_18:r_s18[1,0,10]'  \
--PO 'map=.*/DY_19:r_s19[1,0,10]'  \
--PO 'map=.*/DY_20:r_s20[1,0,10]'  \
--PO 'map=.*/DY_21:r_s21[1,0,10]'  \
--PO 'map=.*/DY_22:r_s22[1,0,10]'  \
--PO 'map=.*/DY_23:r_s23[1,0,10]'  \
--PO 'map=.*/DY_24:r_s24[1,0,10]'  \
--PO 'map=.*/DY_25:r_s25[1,0,10]'  \
--PO 'map=.*/DY_26:r_s26[1,0,10]'  \
--PO 'map=.*/DY_27:r_s27[1,0,10]'  \
--PO 'map=.*/DY_28:r_s28[1,0,10]'  \
--PO 'map=.*/DY_29:r_s29[1,0,10]'  \
--PO 'map=.*/DY_30:r_s30[1,0,10]'  \
--PO 'map=.*/DY_31:r_s31[1,0,10]'  \
--PO 'map=.*/DY_32:r_s32[1,0,10]'  \
--PO 'map=.*/DY_33:r_s33[1,0,10]'  \
--PO 'map=.*/DY_34:r_s34[1,0,10]'  \
--PO 'map=.*/DY_35:r_s35[1,0,10]'  \
datacard_Pt_mm.text -o workspace_Pt_mm.root;

text2workspace.py -P HiggsAnalysis.CombinedLimit.PhysicsModel:multiSignalModel --PO verbose  \
--PO 'map=.*/DY_0:r_s0[1,0,10]'  \
--PO 'map=.*/DY_1:r_s1[1,0,10]'  \
--PO 'map=.*/DY_2:r_s2[1,0,10]'  \
--PO 'map=.*/DY_3:r_s3[1,0,10]'  \
--PO 'map=.*/DY_4:r_s4[1,0,10]'  \
--PO 'map=.*/DY_5:r_s5[1,0,10]'  \
--PO 'map=.*/DY_6:r_s6[1,0,10]'  \
--PO 'map=.*/DY_7:r_s7[1,0,10]'  \
--PO 'map=.*/DY_8:r_s8[1,0,10]'  \
--PO 'map=.*/DY_9:r_s9[1,0,10]'  \
--PO 'map=.*/DY_10:r_s10[1,0,10]'  \
--PO 'map=.*/DY_11:r_s11[1,0,10]'  \
--PO 'map=.*/DY_12:r_s12[1,0,10]'  \
--PO 'map=.*/DY_13:r_s13[1,0,10]'  \
--PO 'map=.*/DY_14:r_s14[1,0,10]'  \
--PO 'map=.*/DY_15:r_s15[1,0,10]'  \
--PO 'map=.*/DY_16:r_s16[1,0,10]'  \
--PO 'map=.*/DY_17:r_s17[1,0,10]'  \
--PO 'map=.*/DY_18:r_s18[1,0,10]'  \
--PO 'map=.*/DY_19:r_s19[1,0,10]'  \
--PO 'map=.*/DY_20:r_s20[1,0,10]'  \
--PO 'map=.*/DY_21:r_s21[1,0,10]'  \
--PO 'map=.*/DY_22:r_s22[1,0,10]'  \
--PO 'map=.*/DY_23:r_s23[1,0,10]'  \
--PO 'map=.*/DY_24:r_s24[1,0,10]'  \
--PO 'map=.*/DY_25:r_s25[1,0,10]'  \
--PO 'map=.*/DY_26:r_s26[1,0,10]'  \
--PO 'map=.*/DY_27:r_s27[1,0,10]'  \
--PO 'map=.*/DY_28:r_s28[1,0,10]'  \
--PO 'map=.*/DY_29:r_s29[1,0,10]'  \
--PO 'map=.*/DY_30:r_s30[1,0,10]'  \
--PO 'map=.*/DY_31:r_s31[1,0,10]'  \
--PO 'map=.*/DY_32:r_s32[1,0,10]'  \
--PO 'map=.*/DY_33:r_s33[1,0,10]'  \
--PO 'map=.*/DY_34:r_s34[1,0,10]'  \
--PO 'map=.*/DY_35:r_s35[1,0,10]'  \
datacard_Pt_ee.text -o workspace_Pt_ee.root;

text2workspace.py -P HiggsAnalysis.CombinedLimit.PhysicsModel:multiSignalModel --PO verbose  \
--PO 'map=.*/DY_0:r_s0[1,0,10]'  \
--PO 'map=.*/DY_1:r_s1[1,0,10]'  \
--PO 'map=.*/DY_2:r_s2[1,0,10]'  \
--PO 'map=.*/DY_3:r_s3[1,0,10]'  \
--PO 'map=.*/DY_4:r_s4[1,0,10]'  \
--PO 'map=.*/DY_5:r_s5[1,0,10]'  \
--PO 'map=.*/DY_6:r_s6[1,0,10]'  \
--PO 'map=.*/DY_7:r_s7[1,0,10]'  \
--PO 'map=.*/DY_8:r_s8[1,0,10]'  \
--PO 'map=.*/DY_9:r_s9[1,0,10]'  \
--PO 'map=.*/DY_10:r_s10[1,0,10]'  \
--PO 'map=.*/DY_11:r_s11[1,0,10]'  \
--PO 'map=.*/DY_12:r_s12[1,0,10]'  \
--PO 'map=.*/DY_13:r_s13[1,0,10]'  \
--PO 'map=.*/DY_14:r_s14[1,0,10]'  \
--PO 'map=.*/DY_15:r_s15[1,0,10]'  \
--PO 'map=.*/DY_16:r_s16[1,0,10]'  \
--PO 'map=.*/DY_17:r_s17[1,0,10]'  \
--PO 'map=.*/DY_18:r_s18[1,0,10]'  \
--PO 'map=.*/DY_19:r_s19[1,0,10]'  \
--PO 'map=.*/DY_20:r_s20[1,0,10]'  \
--PO 'map=.*/DY_21:r_s21[1,0,10]'  \
--PO 'map=.*/DY_22:r_s22[1,0,10]'  \
--PO 'map=.*/DY_23:r_s23[1,0,10]'  \
--PO 'map=.*/DY_24:r_s24[1,0,10]'  \
--PO 'map=.*/DY_25:r_s25[1,0,10]'  \
--PO 'map=.*/DY_26:r_s26[1,0,10]'  \
--PO 'map=.*/DY_27:r_s27[1,0,10]'  \
--PO 'map=.*/DY_28:r_s28[1,0,10]'  \
--PO 'map=.*/DY_29:r_s29[1,0,10]'  \
--PO 'map=.*/DY_30:r_s30[1,0,10]'  \
--PO 'map=.*/DY_31:r_s31[1,0,10]'  \
--PO 'map=.*/DY_32:r_s32[1,0,10]'  \
--PO 'map=.*/DY_33:r_s33[1,0,10]'  \
--PO 'map=.*/DY_34:r_s34[1,0,10]'  \
--PO 'map=.*/DY_35:r_s35[1,0,10]'  \
datacard_Pt_ll.text -o workspace_Pt_ll.root;
