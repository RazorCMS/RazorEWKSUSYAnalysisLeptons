#! /bin/bash

mkdir -p submit
mkdir -p submit/err
mkdir -p submit/log

for i in `seq 0 8`;
do
    echo "#!/bin/sh " > submit/bash_submit_significance_bin$i.sh
    echo cd $PWD >> submit/bash_submit_significance_bin$i.sh
    echo cd /afs/cern.ch/work/c/cpena/public/combineDiphotonHM/CMSSW_7_4_7/src/ >> submit/bash_submit_significance_bin$i.sh
    echo "eval \`scramv1 run -sh\`;" >> submit/bash_submit_significance_bin$i.sh
    echo cd - >> submit/bash_submit_significance_bin$i.sh 
    echo combine -M ProfileLikelihood --signif HggRazorCard_bin$i.txt -n _bin$i.nsigma --setPhysicsModelParameterRanges r=-20,20 --uncapped=1 >> submit/bash_submit_significance_bin$i.sh
    echo combine -M ProfileLikelihood --signif --pvalue HggRazorCard_bin$i.txt -n _bin$i.pvalue --setPhysicsModelParameterRanges r=-20,20 --uncapped=1 >> submit/bash_submit_significance_bin$i.sh
    echo hadd PL_nsigma_npvalue_bin$i.root higgsCombine_bin$i.nsigma.ProfileLikelihood.mH120.root higgsCombine_bin$i.pvalue.ProfileLikelihood.mH120.root >> submit/bash_submit_significance_bin$i.sh
    bsub -q 1nh -e $PWD/submit/err/err_Significance$i.err  -e $PWD/submit/log/log_Significance$i.log source $PWD/submit/bash_submit_significance_bin$i.sh
    sleep 0.2
done
