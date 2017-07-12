#! /bin/bash

signalDir=/eos/cms/store/group/phys_susy/razor/Run2Analysis/HggRazorLeptons/V3p13_Apr132017/FastsimSignal/
smhDir=/eos/cms/store/group/phys_susy/razor/Run2Analysis/HggRazorLeptons/V3p13_Apr132017/
outDir=/afs/cern.ch/work/c/cpena/public/HggRazorLeptons/CMSSW_9_2_0_patch5/src/RazorEWKSUSYAnalysisLeptons/HggRazorLeptons/PlottingAndSystematic/data/lists/Summer2017TChiHZ/

for i in $(ls $signalDir/SMS-TChiHZ_*_1pb_weighted.root* | awk -F -TChiHZ_ '{ print $2 }' | awk -F _1pb_weighted.root '{print $1}');
do

    ###80_X
    echo -e "ggH\t"$smhDir/HggRazorLeptons_GluGluHToGG_M125_13TeV_amcatnloFXFX_pythia8_1pb_weighted.root > $outDir/list_$i.txt
    echo -e "vbfH\t"$smhDir/HggRazorLeptons_VBFHToGG_M125_13TeV_amcatnlo_pythia8_1pb_weighted.root >> $outDir/list_$i.txt
    echo -e "vH\t"$smhDir/HggRazorLeptons_VHToGG_M125_13TeV_amcatnloFXFX_madspin_pythia8_1pb_weighted.root >> $outDir/list_$i.txt
    echo -e "ttH\t"$smhDir/HggRazorLeptons_ttHJetToGG_M125_13TeV_amcatnloFXFX_madspin_pythia8_v2_1pb_weighted.root >> $outDir/list_$i.txt
    echo -e "bbH\t"$smhDir/HggRazorLeptons_bbHToGG_M-125_4FS_13TeV_amcatnlo_1pb_weighted.root >> $outDir/list_$i.txt
    echo -e "signal\t"$signalDir/"SMS-TChiHZ_"$i"_1pb_weighted.root" >> $outDir/list_$i.txt


done
