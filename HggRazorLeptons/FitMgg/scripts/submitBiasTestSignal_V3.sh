#!/bin/bash

echo "RUNNING BIAS TEST"
motherDir=/home/cmorgoth/git/RazorFramework/
workingDir=/home/cmorgoth/git/RazorFramework/HggRazor/FitMgg/
category="highres"
#fitName=("singleExp" "doubleExp" "modExp" "singlePow" "doublePow" "poly2" "poly3" "poly4")
fitName=("singleExp" "modExp" "singlePow" "poly2")
MR=0.0
RSQ=0.0
Iso="no"
sfrac=0.0
outDir="BiasSignal_NoInvIso_GB_SBF_SoverB_0p0_10x_SBF_FULL_V3"
ctr=0
cd $workingDir
mkdir -p submission
mkdir -p /mnt/hadoop/store/user/cmorgoth/$outDir/
for i in ${fitName[@]};do
    for j in ${fitName[@]};do
	outName="output/biasTest_"$i"_"$j".root"
	outName2="output/biasTest_"$i"_"$j"_Tree.root"
	submitFile="submission/biasTest_"$i"_"$j".sh"
	condorFile="submission/biasTest_"$i"_"$j".sub"
	subLog="submission/biasTest_"$i"_"$j".log"
	subOut="submission/biasTest_"$i"_"$j".out"
	subError="submission/biasTest_"$i"_"$j".err"
	tmpDir="biasTestSignal_"$i"_"$j
	echo -e "#!/bin/sh\nexport SCRAM_ARCH=slc5_amd64_gcc472\nsource /cvmfs/cms.cern.ch/cmsset_default.sh\nexport LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/home/cmorgoth/git/BSMatLHC/hepmc/lib/\nmkdir $tmpDir\ncd $tmpDir\n\ncmsrel CMSSW_6_2_0;cd CMSSW_6_2_0/src;cmsenv;source /home/cmorgoth/Software/RootInstall/root/bin/thisroot.sh\ncp -r $motherDir .\ncd RazorFramework/HggRazor/FitMgg/\nmake clean;make;mkdir output\n./MakeFitRun2 --inputFile=DoublePhoton_22Jan2013_Run2012ABCD_v9.root --MRcut=$MR --RSQcut=$RSQ --treeName=SusyHggTree --dataMode=data --category=$category --fitMode=biasSignal --f1=$i --f2=$j --outputFile=$outName --invertedIso=$Iso --signalFraction=$sfrac\ncp $outName /mnt/hadoop/store/user/cmorgoth/$outDir/.\ncp $outName2 /mnt/hadoop/store/user/cmorgoth/$outDir/.\necho FINISHING!!!\n" > $submitFile
	echo -e "Executable = $workingDir/$submitFile\nUniverse = vanilla\nOutput = $subOut\nLog = $subLog\nError = $subError\ngetenv = True\n\nQueue" > $condorFile
	condor_submit $condorFile
	sleep 0.1
	ctr=$((ctr + 1))
    done
done