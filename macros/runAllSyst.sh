#!/bin/sh

#grep RES log_runAllUnfold0|head -64|awk '{printf("%.5f ",100*$2/$3);if(NR%8==0)printf("\n");}'|awk '{printf("%6.3f %6.3f\n",$1-$4,$5-$8)}'

export OPTION=0;
if [ $# == 1 ] && [ $1 == 1 ]; then
   export OPTION=1;
fi

echo "running OPTION: "${OPTION};

for lep in {0..2}
do
for gen in {0..3}
do

root -l -q -b MITStyle.C makeSystHist.C'('${lep}','${gen}',"Pt",'${OPTION}')';
root -l -q -b MITStyle.C makeSystHist.C'('${lep}','${gen}',"Rap",'${OPTION}')';
root -l -q -b MITStyle.C makeSystHist.C'('${lep}','${gen}',"PhiStar",'${OPTION}')';
root -l -q -b MITStyle.C makeSystHist.C'('${lep}','${gen}',"PtRap0",'${OPTION}')';
root -l -q -b MITStyle.C makeSystHist.C'('${lep}','${gen}',"PtRap1",'${OPTION}')';
root -l -q -b MITStyle.C makeSystHist.C'('${lep}','${gen}',"PtRap2",'${OPTION}')';
root -l -q -b MITStyle.C makeSystHist.C'('${lep}','${gen}',"PtRap3",'${OPTION}')';
root -l -q -b MITStyle.C makeSystHist.C'('${lep}','${gen}',"PtRap4",'${OPTION}')';

root -l -q -b MITStyle.C makeSystHist_LepEff.C'('${lep}','${gen}',"Pt",'${OPTION}')';
root -l -q -b MITStyle.C makeSystHist_LepEff.C'('${lep}','${gen}',"Rap",'${OPTION}')';
root -l -q -b MITStyle.C makeSystHist_LepEff.C'('${lep}','${gen}',"PhiStar",'${OPTION}')';

done
done
