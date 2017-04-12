#!/bin/bash

echo "RUNNING BIAS TEST"
motherDir=/home/cmorgoth/git/RazorFramework/
workingDir=/home/cmorgoth/git/RazorFramework/HggRazor/FitMgg/
category="highres"
fitName=("singleExp" "doubleExp" "modExp" "singlePow" "doublePow" "poly2" "poly3")
ctr=0
MRcut=0
RSQcut=0
invertedIso="no"
outDir="BiasTest_Nocuts_NoInvISo_V2"

mkdir -p /mnt/hadoop/store/user/cmorgoth/$outDir
cd $workingDir
mkdir -p submission
for i in ${fitName[@]};do
    for j in ${fitName[@]};do
	outName="output/biasTest_"$i"_"$j".root"
	submitFile="submission/biasTest_"$i"_"$j".sh"
	condorFile="submission/biasTest_"$i"_"$j".sub"
	subLog="submission/biasTest_"$i"_"$j".log"
	subOut="submission/biasTest_"$i"_"$j".out"
	subError="submission/biasTest_"$i"_"$j".err"
	tmpDir="biasTest_"$i"_"$j
	echo -e "#!/bin/sh\nexport SCRAM_ARCH=slc5_amd64_gcc472\nsource /cvmfs/cms.cern.ch/cmsset_default.sh\nmkdir $tmpDir\ncd $tmpDir\n\ncmsrel CMSSW_6_2_0;cd CMSSW_6_2_0/src;cmsenv;source /share/apps/root_v5.34.19/bin/thisroot.sh\ncp -r $motherDir .\ncd RazorFramework/HggRazor/FitMgg/\nmake clean;make;mkdir output\n./MakeFitRun2 --inputFile=DoublePhoton_22Jan2013_Run2012ABCD_v9.root --MRcut=$MRcut --RSQcut=$RSQcut --invertedIso=$invertedIso --treeName=SusyHggTree --dataMode=data --category=$category --fitMode=bias --f1=$i --f2=$j --outputFile=$outName\ncp $outName /mnt/hadoop/store/user/cmorgoth/$outDir/.\necho FINISHING!!!\n" > $submitFile
	echo -e "Executable = $workingDir/$submitFile\nUniverse = vanilla\nOutput = $subOut\nLog = $subLog\nError = $subError\ngetenv = True\n\nQueue" > $condorFile
	condor_submit $condorFile
	sleep 0.1
	ctr=$((ctr + 1))
    done
done