#! /bin/bash

mkdir -p submit
mkdir -p submit/err
mkdir -p submit/log

for i in `seq 0 8`;
do
    echo "#!/bin/sh " > submit/bash_submit_bin$i.sh
    echo cd $PWD >> submit/bash_submit_bin$i.sh
    echo cd /afs/cern.ch/work/c/cpena/public/combineDiphotonHM/CMSSW_7_4_7/src/ >> submit/bash_submit_bin$i.sh
    echo "eval \`scramv1 run -sh\`;" >> submit/bash_submit_bin$i.sh
    echo cd - >> submit/bash_submit_bin$i.sh 
    echo combine -M MaxLikelihoodFit HggRazorCard_bin$i.txt --saveNormalizations --plots --saveShapes --saveWithUncertainties -n _bin$i --minimizerStrategy=2  --setPhysicsModelParameterRanges r=-20,20 >> submit/bash_submit_bin$i.sh
    bsub -q 1nh -e /$PWD/submit/err/err_ML_$i.err -o /$PWD/submit/log/log_ML_$i.log source $PWD/submit/bash_submit_bin$i.sh
    sleep 0.2
done
