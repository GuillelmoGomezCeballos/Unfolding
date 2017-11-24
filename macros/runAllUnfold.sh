#!/bin/sh

if [ $# == 1 ] && [ $1 == 1 ]; then

  for i in `seq 390 1057`;
    do
      export OPTION=$i;
      root -l -q -b testUnfold.C'("Pt","_lepeff",'${OPTION}')';
      root -l -q -b testUnfold.C'("Rap","_lepeff",'${OPTION}')';
      root -l -q -b testUnfold.C'("PhiStar","_lepeff",'${OPTION}')';
      root -l -q -b testUnfold.C'("PtRap0","_lepeff",'${OPTION}')';
      root -l -q -b testUnfold.C'("PtRap1","_lepeff",'${OPTION}')';
      root -l -q -b testUnfold.C'("PtRap2","_lepeff",'${OPTION}')';
      root -l -q -b testUnfold.C'("PtRap3","_lepeff",'${OPTION}')';
    done    

elif [ $# == 1 ] && [ $1 == 2 ]; then

  for i in `seq 0 73`;
    do
      export OPTION=$i;
      root -l -q -b testUnfold.C'("Pt","_sigstat",'${OPTION}')';
      root -l -q -b testUnfold.C'("Rap","_sigstat",'${OPTION}')';
      root -l -q -b testUnfold.C'("PhiStar","_sigstat",'${OPTION}')';
      root -l -q -b testUnfold.C'("PtRap0","_sigstat",'${OPTION}')';
      root -l -q -b testUnfold.C'("PtRap1","_sigstat",'${OPTION}')';
      root -l -q -b testUnfold.C'("PtRap2","_sigstat",'${OPTION}')';
      root -l -q -b testUnfold.C'("PtRap3","_sigstat",'${OPTION}')';
    done    

else

root -l -q -b testUnfold.C'("Pt","_default")';
root -l -q -b testUnfold.C'("Rap","_default")';
root -l -q -b testUnfold.C'("PhiStar","_default")';
root -l -q -b testUnfold.C'("PtRap0","_default")';
root -l -q -b testUnfold.C'("PtRap1","_default")';
root -l -q -b testUnfold.C'("PtRap2","_default")';
root -l -q -b testUnfold.C'("PtRap3","_default")';

root -l -q -b testUnfold.C'("Pt","_momres0")';
root -l -q -b testUnfold.C'("Rap","_momres0")';
root -l -q -b testUnfold.C'("PhiStar","_momres0")';
root -l -q -b testUnfold.C'("PtRap0","_momres0")';
root -l -q -b testUnfold.C'("PtRap1","_momres0")';
root -l -q -b testUnfold.C'("PtRap2","_momres0")';
root -l -q -b testUnfold.C'("PtRap3","_momres0")';

root -l -q -b testUnfold.C'("Pt","_momres1")';
root -l -q -b testUnfold.C'("Rap","_momres1")';
root -l -q -b testUnfold.C'("PhiStar","_momres1")';
root -l -q -b testUnfold.C'("PtRap0","_momres1")';
root -l -q -b testUnfold.C'("PtRap1","_momres1")';
root -l -q -b testUnfold.C'("PtRap2","_momres1")';
root -l -q -b testUnfold.C'("PtRap3","_momres1")';

root -l -q -b testUnfold.C'("Pt","_momres2")';
root -l -q -b testUnfold.C'("Rap","_momres2")';
root -l -q -b testUnfold.C'("PhiStar","_momres2")';
root -l -q -b testUnfold.C'("PtRap0","_momres2")';
root -l -q -b testUnfold.C'("PtRap1","_momres2")';
root -l -q -b testUnfold.C'("PtRap2","_momres2")';
root -l -q -b testUnfold.C'("PtRap3","_momres2")';

root -l -q -b testUnfold.C'("Pt","_momres3")';
root -l -q -b testUnfold.C'("Rap","_momres3")';
root -l -q -b testUnfold.C'("PhiStar","_momres3")';
root -l -q -b testUnfold.C'("PtRap0","_momres3")';
root -l -q -b testUnfold.C'("PtRap1","_momres3")';
root -l -q -b testUnfold.C'("PtRap2","_momres3")';
root -l -q -b testUnfold.C'("PtRap3","_momres3")';

root -l -q -b testUnfold.C'("Pt","_momres4")';
root -l -q -b testUnfold.C'("Rap","_momres4")';
root -l -q -b testUnfold.C'("PhiStar","_momres4")';
root -l -q -b testUnfold.C'("PtRap0","_momres4")';
root -l -q -b testUnfold.C'("PtRap1","_momres4")';
root -l -q -b testUnfold.C'("PtRap2","_momres4")';
root -l -q -b testUnfold.C'("PtRap3","_momres4")';

root -l -q -b testUnfold.C'("Pt","_pdf")';
root -l -q -b testUnfold.C'("Rap","_pdf")';
root -l -q -b testUnfold.C'("PhiStar","_pdf")';
root -l -q -b testUnfold.C'("PtRap0","_pdf")';
root -l -q -b testUnfold.C'("PtRap1","_pdf")';
root -l -q -b testUnfold.C'("PtRap2","_pdf")';
root -l -q -b testUnfold.C'("PtRap3","_pdf")';

root -l -q -b testUnfold.C'("Pt","_qcd")';
root -l -q -b testUnfold.C'("Rap","_qcd")';
root -l -q -b testUnfold.C'("PhiStar","_qcd")';
root -l -q -b testUnfold.C'("PtRap0","_qcd")';
root -l -q -b testUnfold.C'("PtRap1","_qcd")';
root -l -q -b testUnfold.C'("PtRap2","_qcd")';
root -l -q -b testUnfold.C'("PtRap3","_qcd")';

root -l -q -b testUnfold.C'("Pt","_receff")';
root -l -q -b testUnfold.C'("Rap","_receff")';
root -l -q -b testUnfold.C'("PhiStar","_receff")';
root -l -q -b testUnfold.C'("PtRap0","_receff")';
root -l -q -b testUnfold.C'("PtRap1","_receff")';
root -l -q -b testUnfold.C'("PtRap2","_receff")';
root -l -q -b testUnfold.C'("PtRap3","_receff")';

root -l -q -b testUnfold.C'("Pt","_momreslepeff")';
root -l -q -b testUnfold.C'("Rap","_momreslepeff")';
root -l -q -b testUnfold.C'("PhiStar","_momreslepeff")';
root -l -q -b testUnfold.C'("PtRap0","_momreslepeff")';
root -l -q -b testUnfold.C'("PtRap1","_momreslepeff")';
root -l -q -b testUnfold.C'("PtRap2","_momreslepeff")';
root -l -q -b testUnfold.C'("PtRap3","_momreslepeff")';

root -l -q -b testUnfold.C'("Pt","_testscan")';
root -l -q -b testUnfold.C'("Rap","_testscan")';
root -l -q -b testUnfold.C'("PhiStar","_testscan")';
root -l -q -b testUnfold.C'("PtRap0","_testscan")';
root -l -q -b testUnfold.C'("PtRap1","_testscan")';
root -l -q -b testUnfold.C'("PtRap2","_testscan")';
root -l -q -b testUnfold.C'("PtRap3","_testscan")';

fi
