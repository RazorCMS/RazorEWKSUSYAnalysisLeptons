#! /bin/bash

signalDir=/afs/cern.ch/work/c/cpena/public/combineDiphotonHM/CMSSW_7_4_7/src/
outDir=/afs/cern.ch/work/c/cpena/public/combineDiphotonHM/CMSSW_7_4_7/src//RazorEWKSUSYAnalysis/HggRazor/PlottingAndSystematic/data/lists/MoriondMarch11SignalOnly

for i in $(ls $signalDir/HggRazor_SMS-T2bH_mSbottom-* | awk -F -T2bH_ '{ print $2 }' | awk -F _TuneCUETP8M1 '{print $1}');
do
    ###80_X
    echo -e "signal\t"$signalDir/"HggRazor_SMS-T2bH_"$i"_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_1pb_weighted.root" >> $outDir/list_$i.txt
done
