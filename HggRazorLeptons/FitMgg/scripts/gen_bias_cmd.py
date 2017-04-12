#!/usr/bin/env python
#this script submit the jobs to lxplus batch to run multiple bins of biasSignal test, the bins are from bin_list.list
# example: cd ../; make; cd scripts; cmsenv; python batch_submitBiasSignalBackground.py bin_list.list
# modify the inputFile and queue to your own situation. Usually you need to modify the queue because the example "cmscaf1nd" is not open to everyone.

import subprocess, time, sys, os, shlex

print "RUNNING BIAS TEST"

inputList = "/afs/cern.ch/work/z/zhicaiz/public/BiasSignalTest_result_2016BCDEFG_20161011/trees/"

outputDir ="Bias_output/Bias_plots/"
SoverB = ["0.0"]

AICw = ["AICw1", "AICw2","AICw3","AICw4","AICw5","AICw6","AICw7"]
AICfunc = ["AICfunc1", "AICfunc2","AICfunc3","AICfunc4","AICfunc5","AICfunc6","AICfunc7"]

queue = "cmscaf1nd" # change this to the queue you want to use in lxplus batch

if __name__ == "__main__":
	bin_list_filename = sys.argv[1]
	
	pwd = os.getcwd()
	work_directory = pwd.replace("scripts","")
	
	#env_script_no = open("bias_plot_status_no_cmd.sh","w")
	env_script_yes = open("bias_plot_status_yes_cmd.sh","w")

	with open(bin_list_filename,"r") as bin_list_file:
		for this_bin in bin_list_file:
			bin_array = shlex.split(this_bin)
			for SoverB_index in range(len(SoverB)):
				env_script_yes.write("mkdir -p "+outputDir+"/"+bin_array[0]+"_"+bin_array[1]+"_"+bin_array[3]+"/SoB_"+SoverB[SoverB_index] + "\n")
				env_script_yes.write("./PlotAllBiasTest --fitFunc=doubleTailCrystalBall --inputFile="+inputList+bin_array[0]+"_"+bin_array[1]+"_"+bin_array[3]+"/SoB_"+SoverB[SoverB_index]+"/Tree/list.list --mode=table2 --requireFitStatus=yes --category="+bin_array[0]+" --SoB="+SoverB[SoverB_index]+" --LowMRcut="+bin_array[1]+" --HighMRcut="+bin_array[2]+" --LowRSQcut="+bin_array[3]+" --HighRSQcut="+bin_array[4]+" ")	
				for fidx in range((len(bin_array)-5)/2):
					env_script_yes.write(" --"+AICfunc[fidx]+"="+bin_array[fidx*2+5]+" --"+AICw[fidx]+"="+bin_array[fidx*2+6])
				env_script_yes.write(" --outputDir="+outputDir+ "/"+bin_array[0]+"_"+bin_array[1]+"_"+bin_array[3]+"/SoB_"+SoverB[SoverB_index]+ " > "+outputDir+ "/"+bin_array[0]+"_"+bin_array[1]+"_"+bin_array[3]+"/SoB_"+SoverB[SoverB_index]+"/log.log \n")
