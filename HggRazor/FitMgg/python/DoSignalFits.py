from optparse import OptionParser
import ROOT as rt
import os
import sys
from array import *


#HighPt
xbins_hpt = [150,312.5,625,1250,10000]
ybins_hpt = {150:[0,0.028,0.053,0.078,0.103,0.128,10.0],
         312.5:[0,0.022,0.047,0.072,10.0],
         625:[0,0.021,10.0],
         1250:[0,10.0]
         }

#HighRes
xbins_hr = [150,237.5,475,950,10000]
ybins_hr = {150:[0,0.028,0.053,0.078,0.103,0.128,0.153,0.178,5.0],
         237.5:[0,0.035,0.06,0.085,5.0],
         475:[0,0.018,5.0],
         950:[0,5]
         }

#LowRes
xbins_lr = [150,200,400,800,10000]
ybins_lr = {150:[0,0.049,0.074,0.099,0.124,0.149,5.0],
         200:[0,0.023,0.048,0.073,0.098,5.0],
         400:[0,0.02,5.0],
         800:[0,5]
         }


if __name__ == '__main__':
    parser = OptionParser()

    (options,args) = parser.parse_args()
     
    for f in args:
        if f.lower().endswith('.root'):
            rootFile = rt.TFile(f)

    box = "LowRes"
    _inputFile = "/Users/cmorgoth/Work/data/HggRazorRun2/MC/CMSSW_7_6_March15_Ntuples/SM-Higgs_1pb_weighted.root"
    
    if box == "HighPt":
        mrlen = len( xbins_hpt )
        for ibin , mrlow in enumerate( xbins_hpt ):
            if ibin < mrlen-1:
                rsqlen = len( ybins_hpt[mrlow] )
                for jbin,rsqlow in enumerate(ybins_hpt[mrlow]): 
                    if jbin <  rsqlen-1:
                        print mrlow, xbins_hpt[ibin+1], rsqlow, ybins_hpt[mrlow][jbin+1]
                        outFile = "SignalFitResults/"+box+"_signalFit_MR_"+str(mrlow)+"_"+str(xbins_hpt[ibin+1])+"_RSQ_"+str(rsqlow)+"_"+str(ybins_hpt[mrlow][jbin+1])+".root"
                        razorcut = "--LowMRcut="+str(mrlow)+" --LowRSQcut="+str(rsqlow)
                        razorcut += " --HighMRcut="+str(xbins_hpt[ibin+1])+" --HighRSQcut="+str(ybins_hpt[mrlow][jbin+1])
                        command = "./MakeFitRun2 --inputFile="+_inputFile
                        command += " --treeName=HggRazor --dataMode=data --category=highpt --fitMode=signalFit --outputFile="+outFile+" "+razorcut
                        print outFile,"\n",command
                        os.system( command )
   
    elif box == "HighRes":
        mrlen = len( xbins_hr )
        for ibin , mrlow in enumerate( xbins_hr ):
            if ibin < mrlen-1:
                rsqlen = len( ybins_hr[mrlow] )
                for jbin,rsqlow in enumerate(ybins_hr[mrlow]): 
                    if jbin <  rsqlen-1:
                        print mrlow, xbins_hr[ibin+1], rsqlow, ybins_hr[mrlow][jbin+1]
                        outFile = "SignalFitResults/"+box+"_signalFit_MR_"+str(mrlow)+"_"+str(xbins_hr[ibin+1])+"_RSQ_"+str(rsqlow)+"_"+str(ybins_hr[mrlow][jbin+1])+".root"
                        razorcut = "--LowMRcut="+str(mrlow)+" --LowRSQcut="+str(rsqlow)
                        razorcut += " --HighMRcut="+str(xbins_hr[ibin+1])+" --HighRSQcut="+str(ybins_hr[mrlow][jbin+1])
                        command = "./MakeFitRun2 --inputFile="+_inputFile
                        command += " --treeName=HggRazor --dataMode=data --category=highres --fitMode=signalFit --outputFile="+outFile+" "+razorcut
                        print outFile,"\n",command
                        os.system( command )
                        
    elif box == "LowRes":
        mrlen = len( xbins_lr )
        for ibin , mrlow in enumerate( xbins_lr ):
            if ibin < mrlen-1:
                rsqlen = len( ybins_lr[mrlow] )
                for jbin,rsqlow in enumerate(ybins_lr[mrlow]): 
                    if jbin <  rsqlen-1:
                        print mrlow, xbins_lr[ibin+1], rsqlow, ybins_lr[mrlow][jbin+1]
                        outFile = "SignalFitResults/"+box+"_signalFit_MR_"+str(mrlow)+"_"+str(xbins_lr[ibin+1])+"_RSQ_"+str(rsqlow)+"_"+str(ybins_lr[mrlow][jbin+1])+".root"
                        razorcut = "--LowMRcut="+str(mrlow)+" --LowRSQcut="+str(rsqlow)
                        razorcut += " --HighMRcut="+str(xbins_lr[ibin+1])+" --HighRSQcut="+str(ybins_lr[mrlow][jbin+1])
                        command = "./MakeFitRun2 --inputFile="+_inputFile
                        command += " --treeName=HggRazor --dataMode=data --category=lowres --fitMode=signalFit --outputFile="+outFile+" "+razorcut
                        print outFile,"\n",command
                        os.system( command )
                            
