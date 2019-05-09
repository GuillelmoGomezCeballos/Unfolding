#!/bin/sh

root -q -b -l testAnalysis_test.C+'(0,3,0,"Total")';
root -q -b -l testAnalysis_test.C+'(1,3,0,"Total")';
combineCards.py -S datacard_Tot_mm.txt > datacard_Tot_mm.text;
combineCards.py -S datacard_Tot_ee.txt > datacard_Tot_ee.text;
combineCards.py -S datacard_Tot_mm.txt datacard_Tot_ee.txt > datacard_Tot_ll.text;

text2workspace.py -P HiggsAnalysis.CombinedLimit.PhysicsModel:multiSignalModel --PO verbose  \
--PO 'map=.*/DY_0:r_s0[1,0,10]'  \
datacard_Tot_mm.text -o workspace_Tot_mm.root;

text2workspace.py -P HiggsAnalysis.CombinedLimit.PhysicsModel:multiSignalModel --PO verbose  \
--PO 'map=.*/DY_0:r_s0[1,0,10]'  \
datacard_Tot_ee.text -o workspace_Tot_ee.root;

text2workspace.py -P HiggsAnalysis.CombinedLimit.PhysicsModel:multiSignalModel --PO verbose  \
--PO 'map=.*/DY_0:r_s0[1,0,10]'  \
datacard_Tot_ll.text -o workspace_Tot_ll.root;

#combine -M MaxLikelihoodFit datacard_Tot_mm.text -m 1 --expectSignal=1 -t -1 --saveNorm --saveWithUncertainties --rMin=-1 --rMax=2 --robustFit=1 --X-rtd FITTER_DYN_STEP 

#combineTool.py -M Impacts -d workspace_Tot_mm.root -m 125 --expectSignal=1 -t -1 --robustFit 1 --doInitialFit --allPars;
#combineTool.py -M Impacts -d workspace_Tot_mm.root -m 125 --expectSignal=1 -t -1 --robustFit 1 --doFits --allPars;
#combineTool.py -M Impacts -d workspace_Tot_mm.root -m 125 -o impacts_mc.json --allPars;
#plotImpacts.py -i impacts_mc.json -o impacts_mc;

#combine -M MultiDimFit workspace_Tot_mm.root -P r_s0 --floatOtherPOIs=1 --setPhysicsModelParameterRange r_s0=0.9,1.1 --algo=grid --points=100 -m 1250 --minimizerTolerance 0.001 --robustFit=1

#combine -M MultiDimFit workspace_Tot_mm.root --algo=singles --robustFit=1 --rMin 0.5 --rMax 1.5

#combine -M MultiDimFit workspace_Tot_mm.text --algo=grid --robustFit=1 --rMin 0.9 --rMax 1.1 --points=4000
