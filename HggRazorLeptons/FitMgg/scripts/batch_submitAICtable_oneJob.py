#!/usr/bin/env python
#this script submit the jobs to lxplus batch to run multiple bins of AIC test, the bins are from bin_list.list
# example: cd ../; make; cd scripts; cmsenv; python batch_submitAICtable_oneJob.py bin_list.list
# modify the inputFile and queue to your own situation. Usually you need to modify the queue because the example "cmscaf1nd" is not open to everyone.

import subprocess, time, sys, os, shlex

inputFile = "/afs/cern.ch/work/z/zhicaiz/public/RazorInput/DoubleEG_Run2015_CMSSW_7_6_March15_GoodLumi.root" #"/afs/cern.ch/work/c/cpena/public/CMSSW_7_5_3_patch1/src/RazorCommon/DoubleEG_Run2015D_TOTAL_NoCuts_GoodLumi_Jan27.root" #change this to the input ntuple you are using 

queue = "cmscaf1nd" # change this to the queue you want to use in lxplus batch

if __name__ == "__main__":
	bin_list_filename = sys.argv[1]
	
	pwd = os.getcwd()
	work_directory = pwd.replace("scripts","")
	os.system("rm -rf "+work_directory+"AIC_output/highpt")
        os.system("mkdir -p "+work_directory+"AIC_output/highpt")
        os.system("rm -rf "+work_directory+"AIC_output/highres")
        os.system("mkdir -p "+work_directory+"AIC_output/highres")
        os.system("rm -rf "+work_directory+"AIC_output/lowres")
        os.system("mkdir -p "+work_directory+"AIC_output/lowres")
        os.system("rm -rf "+work_directory+"AIC_output/hzbb")
        os.system("mkdir -p "+work_directory+"AIC_output/hzbb")
        os.system("rm -rf "+pwd+"/submit")
        os.system("mkdir -p "+pwd+"/submit")
	
	env_script_n = pwd + "/submit/" + "run_AIC_cmd.sh"
	env_script_f = open(env_script_n, 'w')
	
	env_script_f.write("#!/bin/bash\n")
	env_script_f.write("cd " + work_directory + "\n")
	env_script_f.write("ulimit -c 0\n")
	env_script_f.write("eval `scramv1 runtime -sh`\n")
	env_script_f.write("source /afs/cern.ch/work/c/cpena/public/myRootHacked6/bin/thisroot.sh \n")
	
	with open(bin_list_filename,"r") as bin_list_file:
		for this_bin in bin_list_file:
			bin_array = shlex.split(this_bin)
			env_script_f.write("./MakeFitRun2 --inputFile="+inputFile+" --treeName=HggRazor --LowMRcut="+bin_array[1]+" --HighMRcut="+bin_array[2]+" --LowRSQcut="+bin_array[3]+" --HighRSQcut="+bin_array[4]+" --dataMode=data --category="+bin_array[0]+" --fitMode=AIC2 --runPeriod=run2 --outputFile="+work_directory+"AIC_output/"+bin_array[0]+"/"+ bin_array[0]+"_"+bin_array[1]+"_"+bin_array[3]+".root"+" \n")
			
	changePermission = subprocess.Popen(['chmod 777 ' + env_script_n], stdout=subprocess.PIPE, shell=True);
	debugout = changePermission.communicate()
	submit_s = 'bsub -q '+queue+' -o ' + pwd + "/submit/run_AIC.log" + ' "source ' + env_script_n + '"'
	print "[submit_AICtable]  '-- " + submit_s
	submitJobs = subprocess.Popen([submit_s], stdout=subprocess.PIPE, shell=True);
	output = (submitJobs.communicate()[0]).splitlines()
	print "[submit_AICtable]  '-- " + output[0]		
