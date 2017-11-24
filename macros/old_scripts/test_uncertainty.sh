
#combine -M MultiDimFit zlepton_multidim_lumi.root -P r_s1 --floatOtherPOIs=1 --setPhysicsModelParameterRange r_s1=0.9,1.1 --algo=grid --points=100 -m 11
for i in {1..11}
do
    echo "$i"
   # combine -M MultiDimFit zlepton_multidim_lepeff.root -P r_s${i} --floatOtherPOIs=1 --setPhysicsModelParameterRange r_s${i}=0.9,1.1 --algo=grid --points=100 -m 121${i} --minimizerTolerance 0.001 --robustFit=1
    #combine -M MultiDimFit zlepton_multidim_momres.root -P r_s${i} --floatOtherPOIs=1 --setPhysicsModelParameterRange r_s${i}=0.9,1.1 --algo=grid --points=1000 -m 122${i} --minimizerTolerance 0.001   --robustFit=1
    #combine -M MultiDimFit zlepton_multidim_pdf.root -P r_s${i} --floatOtherPOIs=1 --setPhysicsModelParameterRange r_s${i}=0.9,1.1 --algo=grid --points=600 -m 123${i}  --minimizerTolerance 0.001 --robustFit=1
    #combine -M MultiDimFit zlepton_multidim_qcd.root -P r_s${i} --floatOtherPOIs=1 --setPhysicsModelParameterRange r_s${i}=0.9,1.1 --algo=grid --points=500 -m 124${i}  --minimizerTolerance 0.001 --robustFit=1
    #combine -M MultiDimFit zlepton_multidim_lumi.root -P r_s${i} --floatOtherPOIs=1 --setPhysicsModelParameterRange r_s${i}=0.9,1.1 --algo=grid --points=150 -m 125${i}  --minimizerTolerance 0.001 --robustFit=1
    #combine -M MultiDimFit zlepton_multidim_leplumi.root -P r_s${i} --floatOtherPOIs=1 --setPhysicsModelParameterRange r_s${i}=0.9,1.1 --algo=grid --points=150 -m 126${i}  --minimizerTolerance 0.001 --robustFit=1
    #combine -M MultiDimFit zlepton_multidim_leplumimom.root -P r_s${i} --floatOtherPOIs=1 --setPhysicsModelParameterRange r_s${i}=0.9,1.1 --algo=grid --points=150 -m 127${i}  --minimizerTolerance 0.001 --robustFit=1

    #combine -M MultiDimFit zlepton_multidim_leplumimompdf.root -P r_s${i} --floatOtherPOIs=1 --setPhysicsModelParameterRange r_s${i}=0.9,1.1 --algo=grid --points=150 -m 128${i} --minimizerTolerance 0.001 --robustFit=1
    #combine -M MultiDimFit zlepton_multidim_allsys.root -P r_s${i} --floatOtherPOIs=1 --setPhysicsModelParameterRange r_s${i}=0.9,1.1 --algo=grid --points=150 -m 129${i} --minimizerTolerance 0.001 --robustFit=1


#combine -M MultiDimFit all.root -P r_s${i} --floatOtherPOIs=1 --setPhysicsModelParameterRange r_s${i}=0.9,1.1 --algo=grid --points=150 -m 129${i} --minimizerTolerance 0.001 --robustFit=1

combine -M MultiDimFit all_200_last.root -P r_s${i} --floatOtherPOIs=1 --setPhysicsModelParameterRange r_s${i}=0.9,1.1 --algo=grid --points=150 -m 1292${i} --minimizerTolerance 0.001 --robustFit=1
combine -M MultiDimFit stat_200_last.root -P r_s${i} --floatOtherPOIs=1 --setPhysicsModelParameterRange r_s${i}=0.9,1.1 --algo=grid --points=150 -m 1252${i} --minimizerTolerance 0.001 --robustFit=1


done
