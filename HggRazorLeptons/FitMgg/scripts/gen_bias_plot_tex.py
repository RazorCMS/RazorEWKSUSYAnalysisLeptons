#!/usr/bin/env python
#this script submit the jobs to lxplus batch to run multiple bins of biasSignal test, the bins are from bin_list.list
# example: cd ../; make; cd scripts; cmsenv; python batch_submitBiasSignalBackground.py bin_list.list
# modify the inputFile and queue to your own situation. Usually you need to modify the queue because the example "cmscaf1nd" is not open to everyone.

import subprocess, time, sys, os, shlex

SoverB = ["0.0","1.0","3.0","5.0"]

queue = "cmscaf1nd" # change this to the queue you want to use in lxplus batch

if __name__ == "__main__":
	bin_list_filename = sys.argv[1]
	
	fitName=["singleExp", "doubleExp", "modExp", "singlePow", "doublePow", "poly2", "poly3"]
	
	env_script_n = "bias_plot_tex.tex" 
	env_script_f = open(env_script_n, 'w')
	with open(bin_list_filename,"r") as bin_list_file:
		for this_bin in bin_list_file:
			bin_array = shlex.split(this_bin)
			for SoverB_index in range(len(SoverB)):
				for f1 in range(len(fitName)):
					for f2 in range(len(fitName)): 
						env_script_f.write("\\begin{figure}[H] \n")
						env_script_f.write("\\begin{center}\n")	
						env_script_f.write("\\includegraphics[width=\\columnwidth]{../BiasSignalTest_result/plots/"+bin_array[0]+"_"+bin_array[1]+"_"+bin_array[3]+"/SoB_"+SoverB[SoverB_index]+"/"+fitName[f1]+"_"+fitName[f2]+".pdf} \n")	
						env_script_f.write("\\caption{f1="+fitName[f1]+", f2="+fitName[f2]+", S/B="+SoverB[SoverB_index]+", "+bin_array[0]+", $"+bin_array[1]+"<M_R<"+bin_array[2]+", "+bin_array[3]+"<R^2<"+bin_array[4]+"$.} \n")	
						env_script_f.write("\\end{center} \n")	
						env_script_f.write("\\end{figure} \n")	
						env_script_f.write(" \n")	
						env_script_f.write(" \n")	
