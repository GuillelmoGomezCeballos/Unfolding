#!/bin/sh

#grep RES log_runAllUnfold0|head -64|awk '{printf("%.5f ",100*$2/$3);if(NR%8==0)printf("\n");}'|awk '{printf("%6.3f %6.3f\n",$1-$4,$5-$8)}'

export OPTION="noLL";
if [ $# == 1 ] && [ $1 == 1 ]; then
   export OPTION="LL";
fi

echo "running OPTION: "${OPTION};

root -l -q -b ../MITStyle.C ../makeSystHist_UPSG.C'("'${OPTION}'","Rap", 0.025)';
mv histoUnfoldingSystRap_nsel0_dy3.pdf histoUnfoldingSystRap_nsel0_dy3_lumunc0p025.pdf
mv histoUnfoldingSystRap_nsel1_dy3.pdf histoUnfoldingSystRap_nsel1_dy3_lumunc0p025.pdf
mv histoUnfoldingSystRap_nsel0_dy3_rebin1_default.root histoUnfoldingSystRap_nsel0_dy3_lumunc0p025.root
mv histoUnfoldingSystRap_nsel1_dy3_rebin1_default.root histoUnfoldingSystRap_nsel1_dy3_lumunc0p025.root

root -l -q -b ../MITStyle.C ../makeSystHist_UPSG.C'("'${OPTION}'","Rap", 0.020)';
mv histoUnfoldingSystRap_nsel0_dy3.pdf histoUnfoldingSystRap_nsel0_dy3_lumunc0p020.pdf
mv histoUnfoldingSystRap_nsel1_dy3.pdf histoUnfoldingSystRap_nsel1_dy3_lumunc0p020.pdf
mv histoUnfoldingSystRap_nsel0_dy3_rebin1_default.root histoUnfoldingSystRap_nsel0_dy3_lumunc0p020.root
mv histoUnfoldingSystRap_nsel1_dy3_rebin1_default.root histoUnfoldingSystRap_nsel1_dy3_lumunc0p020.root

root -l -q -b ../MITStyle.C ../makeSystHist_UPSG.C'("'${OPTION}'","Rap", 0.010)';
mv histoUnfoldingSystRap_nsel0_dy3.pdf histoUnfoldingSystRap_nsel0_dy3_lumunc0p010.pdf
mv histoUnfoldingSystRap_nsel1_dy3.pdf histoUnfoldingSystRap_nsel1_dy3_lumunc0p010.pdf
mv histoUnfoldingSystRap_nsel0_dy3_rebin1_default.root histoUnfoldingSystRap_nsel0_dy3_lumunc0p010.root
mv histoUnfoldingSystRap_nsel1_dy3_rebin1_default.root histoUnfoldingSystRap_nsel1_dy3_lumunc0p010.root

