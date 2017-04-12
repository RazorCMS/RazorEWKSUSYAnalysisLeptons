#!/bin/bash

echo "RUNNING BIAS TEST"
motherDir=/home/cmorgoth/git/RazorFramework/
workingDir=/home/cmorgoth/git/RazorFramework/HggRazor/FitMgg/
category="highres"
fitName=("singleExp" "doubleExp" "modExp" "singlePow" "doublePow" "poly2" "poly3")
MR=0.0
RSQ=0.0
Iso="no"
outDir="BiasSignal_NoInvIso_TEST_SBF"
ctr=0
cd $workingDir
mkdir -p submission
mkdir -p /mnt/hadoop/store/user/cmorgoth/$outDir/
for i in ${fitName[@]};do
    for j in ${fitName[@]};do
	outName="output/biasTest_"$i"_"$j".root"
	submitFile="submission/biasTest_"$i"_"$j".sh"
	condorFile="submission/biasTest_"$i"_"$j".sub"
	subLog="submission/biasTest_"$i"_"$j".log"
	subOut="submission/biasTest_"$i"_"$j".out"
	subError="submission/biasTest_"$i"_"$j".err"
	tmpDir="biasTestSignal_"$i"_"$j
	echo -e "#!/bin/sh\n\nsource /cvmfs/cms.cern.ch/cmsset_default.sh\nexport SCRAM_ARCH=slc5_amd64_gcc481\nexport LD_LIBRARY_PATH=/cvmfs/cms.cern.ch/slc5_amd64_gcc481/external/gcc/4.8.1/lib64/:/cvmfs/cms.cern.ch/slc5_amd64_gcc481/external/gcc/4.8.1/lib/:$LD_LIBRARY_PATH\nexport PATH=/cvmfs/cms.cern.ch/slc5_amd64_gcc481/external/gcc/4.8.1/bin:/share/apps/Python-2.7.9/:$PATH\n\nexport ROOTSYS=/home/cmorgoth/Software/RootInstall/root\nsource $ROOTSYS/bin/thisroot.sh\nexport PATH=/share/apps/Python-2.7.9/:$PATH\n\ngit config --global user.name Cristian Pena\ngit config --global user.email cristian.pena@caltech.edu\ngit config --global user.github cmorgoth\n\nexport GIT_SSL_NO_VERIFY=true\nexport https_proxy=newman.ultralight.org:3128\nexport http_proxy=newman.ultralight.org:3128\nexport SSH_ASKPASS=""\n\ncp -r $motherDir .\ncd RazorFramework/HggRazor/FitMgg/\nmake clean;make;mkdir output\n./MakeFitRun2 --inputFile=DoublePhoton_22Jan2013_Run2012ABCD_v9.root --MRcut=$MR --RSQcut=$RSQ --treeName=SusyHggTree --dataMode=data --category=$category --fitMode=biasSignal --f1=$i --f2=$j --outputFile=$outName --invertedIso=$Iso\ncp $outName /mnt/hadoop/store/user/cmorgoth/$outDir/.\necho FINISHING!!!\n" > $submitFile
	echo -e "Executable = $workingDir/$submitFile\nUniverse = vanilla\nOutput = $subOut\nLog = $subLog\nError = $subError\ngetenv = True\n\nQueue" > $condorFile
	#condor_submit $condorFile
	sleep 0.1
	ctr=$((ctr + 1))
    done
done