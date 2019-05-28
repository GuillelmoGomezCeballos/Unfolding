#!/bin/sh

#grep RES log_runAllUnfold0|head -64|awk '{printf("%.5f ",100*$2/$3);if(NR%8==0)printf("\n");}'|awk '{printf("%6.3f %6.3f\n",$1-$4,$5-$8)}'

export OPTION="noLL";
if [ $# == 1 ] && [ $1 == 1 ]; then
   export OPTION="LL";
fi

echo "running OPTION: "${OPTION};

root -l -q -b MITStyle.C makeSystHist.C'("'${OPTION}'","Pt")';
root -l -q -b MITStyle.C makeSystHist.C'("'${OPTION}'","Rap")';
root -l -q -b MITStyle.C makeSystHist.C'("'${OPTION}'","PhiStar")';
root -l -q -b MITStyle.C makeSystHist.C'("'${OPTION}'","PtRap0")';
root -l -q -b MITStyle.C makeSystHist.C'("'${OPTION}'","PtRap1")';
root -l -q -b MITStyle.C makeSystHist.C'("'${OPTION}'","PtRap2")';
root -l -q -b MITStyle.C makeSystHist.C'("'${OPTION}'","PtRap3")';
root -l -q -b MITStyle.C makeSystHist.C'("'${OPTION}'","PtRap4")';

if [ ${OPTION} == "noLL" ]; then
  root -l -q -b MITStyle.C makeSystHist_LepEff.C'("Pt")';
  root -l -q -b MITStyle.C makeSystHist_LepEff.C'("Rap")';
  root -l -q -b MITStyle.C makeSystHist_LepEff.C'("PhiStar")';
fi
