#! /bin/bash

signalDir=/afs/cern.ch/work/c/cpena/public/combineDiphotonHM/CMSSW_7_4_7/src/
outDir=/afs/cern.ch/work/c/cpena/public/combineDiphotonHM/CMSSW_7_4_7/src/RazorEWKSUSYAnalysis/HggRazor/PlottingAndSystematic/data/lists/MoriondFeb27SignalOnlyTChiHZ/

for i in $(ls $signalDir/SMS-TChiHZ_*_tweaked_1pb_weighted.root | awk -F SMS-TChiHZ_ '{ print $2 }' | awk -F _tweaked_1pb_weighted.root '{print $1}');
do
    ###80_X
    echo -e "signal\t"$signalDir/"SMS-TChiHZ_"$i"_tweaked_1pb_weighted.root" > $outDir/list_$i.txt
done
