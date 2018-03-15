#!/bin/sh

combineTool.py -M Impacts -d workspace_Pt_mm.root -m 125 --robustFit 1 --doInitialFit --allPars --rMin 0.5 --rMax 1.5;
combineTool.py -M Impacts -d workspace_Pt_mm.root -m 125 --robustFit 1 --doFits --allPars --rMin 0.5 --rMax 1.5;
combineTool.py -M Impacts -d workspace_Pt_mm.root -m 125 -o impacts_mc.json --allPars --rMin 0.5 --rMax 1.5;
mv impacts_mc.json impacts_mc_mm.json;
plotImpacts.py -i impacts_mc_mm.json -o impacts_mc_mm;

combineTool.py -M Impacts -d workspace_Pt_ee.root -m 125 --robustFit 1 --doInitialFit --allPars --rMin 0.5 --rMax 1.5;
combineTool.py -M Impacts -d workspace_Pt_ee.root -m 125 --robustFit 1 --doFits --allPars --rMin 0.5 --rMax 1.5;
combineTool.py -M Impacts -d workspace_Pt_ee.root -m 125 -o impacts_mc.json --allPars --rMin 0.5 --rMax 1.5;
mv impacts_mc.json impacts_mc_ee.json;
plotImpacts.py -i impacts_mc_ee.json -o impacts_mc_ee;

combineTool.py -M Impacts -d workspace_Pt_ll.root -m 125 --robustFit 1 --doInitialFit --allPars --rMin 0.5 --rMax 1.5;
combineTool.py -M Impacts -d workspace_Pt_ll.root -m 125 --robustFit 1 --doFits --allPars --rMin 0.5 --rMax 1.5;
combineTool.py -M Impacts -d workspace_Pt_ll.root -m 125 -o impacts_mc.json --allPars --rMin 0.5 --rMax 1.5;
mv impacts_mc.json impacts_mc_ll.json;
plotImpacts.py -i impacts_mc_ll.json -o impacts_mc_ll;

combineTool.py -M Impacts -d workspace_Tot_mm.root -m 125 --robustFit 1 --doInitialFit --allPars --rMin 0.5 --rMax 1.5;
combineTool.py -M Impacts -d workspace_Tot_mm.root -m 125 --robustFit 1 --doFits --allPars --rMin 0.5 --rMax 1.5;
combineTool.py -M Impacts -d workspace_Tot_mm.root -m 125 -o impacts_mc.json --allPars --rMin 0.5 --rMax 1.5;
mv impacts_mc.json impacts_mc_Tot_mm.json;
plotImpacts.py -i impacts_mc_Tot_mm.json -o impacts_mc_Tot_mm;

combineTool.py -M Impacts -d workspace_Tot_ee.root -m 125 --robustFit 1 --doInitialFit --allPars --rMin 0.5 --rMax 1.5;
combineTool.py -M Impacts -d workspace_Tot_ee.root -m 125 --robustFit 1 --doFits --allPars --rMin 0.5 --rMax 1.5;
combineTool.py -M Impacts -d workspace_Tot_ee.root -m 125 -o impacts_mc.json --allPars --rMin 0.5 --rMax 1.5;
mv impacts_mc.json impacts_mc_Tot_ee.json;
plotImpacts.py -i impacts_mc_Tot_ee.json -o impacts_mc_Tot_ee;

combineTool.py -M Impacts -d workspace_Tot_ll.root -m 125 --robustFit 1 --doInitialFit --allPars --rMin 0.5 --rMax 1.5;
combineTool.py -M Impacts -d workspace_Tot_ll.root -m 125 --robustFit 1 --doFits --allPars --rMin 0.5 --rMax 1.5;
combineTool.py -M Impacts -d workspace_Tot_ll.root -m 125 -o impacts_mc.json --allPars --rMin 0.5 --rMax 1.5;
mv impacts_mc.json impacts_mc_Tot_ll.json;
plotImpacts.py -i impacts_mc_Tot_ll.json -o impacts_mc_Tot_ll;

rm -f combine_logger.out;
rm -f higgsCombine*.root;
