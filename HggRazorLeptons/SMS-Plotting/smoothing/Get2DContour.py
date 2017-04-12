from optparse import OptionParser
import ROOT as rt
import sys
import glob
from math import *
import os
from array import *
import numpy as np
from scipy.interpolate import Rbf, interp1d
import itertools
import operator

def interpolate2D(hist,epsilon=1,smooth=0,diagonalOffset=0,fixLSP0=False,refHist=None):
    x = array('d',[])
    y = array('d',[])
    z = array('d',[])
    
    binWidth = float(hist.GetXaxis().GetBinWidth(1))
    
    for i in range(1, hist.GetNbinsX()+1):
        for j in range(1, hist.GetNbinsY()+1):
            if hist.GetBinContent(i,j)>0.:
                if refHist!=None and refHist.GetBinContent(i,j) > 0.:
                        x.append(hist.GetXaxis().GetBinCenter(i))
                        y.append(hist.GetYaxis().GetBinCenter(j))
                        z.append(rt.TMath.Log(hist.GetBinContent(i,j)/refHist.GetBinContent(i,j)))
                else:
                    x.append(hist.GetXaxis().GetBinCenter(i))
                    y.append(hist.GetYaxis().GetBinCenter(j))
                    z.append(rt.TMath.Log(hist.GetBinContent(i,j)))

    mgMin = hist.GetXaxis().GetBinCenter(1)
    mgMax = hist.GetXaxis().GetBinCenter(hist.GetNbinsX())#+hist.GetXaxis().GetBinWidth(hist.GetNbinsX())
    mchiMin = hist.GetYaxis().GetBinCenter(1)
    mchiMax = hist.GetYaxis().GetBinCenter(hist.GetNbinsY())#+hist.GetYaxis().GetBinWidth(hist.GetNbinsY())
    
    myX = np.linspace(mgMin, mgMax,int((mgMax-mgMin)/binWidth+1))
    myY = np.linspace(mchiMin, mchiMax, int((mchiMax-mchiMin)/binWidth+1))
    myXI, myYI = np.meshgrid(myX,myY)

    rbf = Rbf(x, y, z,function='multiquadric', epsilon=epsilon,smooth=smooth)
    myZI = rbf(myXI, myYI)
    
    rbf_nosmooth = Rbf(x, y, z, function='multiquadric',epsilon=epsilon,smooth=10)
    otherY = array('d',[mchiMin])
    lineXI, lineYI = np.meshgrid(myX,otherY)
    lineZI = rbf_nosmooth(lineXI, lineYI)

    for i in range(1, hist.GetNbinsX()+1):
        for j in range(1, hist.GetNbinsY()+1):
            xLow = hist.GetXaxis().GetBinCenter(i)
            yLow = hist.GetYaxis().GetBinCenter(j)
            if j==1 and fixLSP0:
                hist.SetBinContent(i,j,rt.TMath.Exp(lineZI[j-1][i-1]))
                continue
            if xLow >= yLow+diagonalOffset-binWidth/2.:
                if refHist!=None:                    
                    hist.SetBinContent(i,j,refHist.GetBinContent(i,j)*rt.TMath.Exp(myZI[j-1][i-1]))
                else:
                    hist.SetBinContent(i,j,rt.TMath.Exp(myZI[j-1][i-1]))
    return hist


if __name__ == '__main__':

    rt.gStyle.SetOptStat(0)
    rt.gROOT.ProcessLine(".L swissCrossInterpolate.h+")
    rt.gSystem.Load("swissCrossInterpolate_h.so")
    
    nRebins = 1
    diagonalOffset = 150
    mgMin = 250
    mgMax = 550
    mchiMin = 0
    mchiMax = 300

    binWidth = 50 # to be changed to 25
    
    tfile = rt.TFile.Open('/afs/cern.ch/work/c/cpena/public/combineDiphotonHM/CMSSW_7_4_7/src/RazorEWKSUSYAnalysis/HggRazor/SMS-Plotting/smoothing/test_limit.root')
    xsecULRaw = tfile.Get('limit_exp_up')
    xsecUL = rt.TH2D(xsecULRaw.GetName()+'_fixRange',xsecULRaw.GetName()+'_fixRange',7,mgMin-binWidth/2.,mgMax+binWidth/2.,7,mchiMin-binWidth/2., mchiMax+binWidth/2.)
    
    for i in range(1,xsecUL.GetNbinsX()+1):
        for j in range(1,xsecUL.GetNbinsY()+1):
            xCen = xsecUL.GetXaxis().GetBinCenter(i)
            yCen = xsecUL.GetYaxis().GetBinCenter(j)
            xsecUL.SetBinContent(i,j,xsecULRaw.GetBinContent(xsecULRaw.FindBin(xCen,yCen)))
            print yCen, xCen, xsecULRaw.GetBinContent(xsecULRaw.FindBin(xCen,yCen))
    # do swiss cross average in real domain
    rebinXsecUL = rt.swissCrossInterpolate(xsecUL,"NE")

    # do scipy multi-quadratic interpolation in log domain
    #rebinXsecUL = interpolate2D(rebinXsecUL,epsilon=5,smooth=5,diagonalOffset=diagonalOffset,fixLSP0=False)

    # do swiss cross rebin + average in real domain
    for i in xrange(0,nRebins):
        rebinXsecUL = rt.swissCrossRebin(rebinXsecUL,"NE")
        
    binWidth = 25
    
    rebinXsecULFixRange = rt.TH2D(rebinXsecUL.GetName()+'_fixRange',rebinXsecUL.GetName()+'_fixRange',13,mgMin-binWidth/2.,mgMax+binWidth/2.,13,mchiMin-binWidth/2., mchiMax+binWidth/2.)    
    
    for i in range(1,rebinXsecULFixRange.GetNbinsX()+1):
        for j in range(1,rebinXsecULFixRange.GetNbinsY()+1):
            xCen = rebinXsecULFixRange.GetXaxis().GetBinCenter(i)
            yCen = rebinXsecULFixRange.GetYaxis().GetBinCenter(j)
            rebinXsecULFixRange.SetBinContent(i, j ,rebinXsecUL.GetBinContent(rebinXsecUL.FindBin(xCen,yCen)))





    # done with rebinning and interpolation of histograms


    
    xsecGluino =  rt.TH2D("xsecGluino","xsecGluino",13,mgMin-binWidth/2.,mgMax+binWidth/2.,13,mchiMin-binWidth/2., mchiMax+binWidth/2.)
    
    thyXsec = {}
    thyXsecErr = {}
    for mg in range(100,2000+5,5):    
        for line in open('stop13TeV.txt','r'):
            line = line.replace('\n','')
            if str(mg)==line.split(',')[0]:
                thyXsec[mg] = float(line.split(',')[1]) #pb
                thyXsecErr[mg] = 0.01*float(line.split(',')[2])      
    
    for i in xrange(1,xsecGluino.GetNbinsX()+1):
        for j in xrange(1,xsecGluino.GetNbinsY()+1):
            xCen = xsecGluino.GetXaxis().GetBinCenter(i)
            yCen = xsecGluino.GetYaxis().GetBinCenter(j)
            if xCen > 500 or yCen > 250:
                continue
            if xCen >= yCen+diagonalOffset+25 and xCen <= mgMax:
                xsecVal = thyXsec[int(xCen)]
                xsecErr =  thyXsecErr[int(xCen)]
                xsecGluino.SetBinContent(i,j,xsecVal)
                #xsecGluinoPlus.SetBinContent(i,j,xsecVal*(1+xsecErr))
        

    c = rt.TCanvas("c","c",500,500)

    # subtract the predicted xsec
    subXsecUL = rebinXsecULFixRange.Clone()
    subXsecUL.Add(xsecGluino,-1)

    contours = array('d',[0.0])
    subXsecUL.SetContour(1,contours)
        
        
    c.SetLogz(0)
    subXsecUL.Draw("CONT Z LIST")
    c.Update()
        
    conts = rt.gROOT.GetListOfSpecials().FindObject("contours")

    rebinXsecULFixRange.Draw("COLZ")
    rebinXsecULFixRange.GetXaxis().SetRangeUser(mgMin,mgMax)
    rebinXsecULFixRange.GetYaxis().SetRangeUser(mchiMin,mchiMax)
    rebinXsecULFixRange.SetMinimum(1e-1)
    rebinXsecULFixRange.SetMaximum(10)
    rebinXsecULFixRange.Draw("COLZ")
    c.Update()
        
    contour0 = conts.At(0)
    curv = contour0.First()
    finalcurv = rt.TGraph(1)
    try:
        curv.SetLineWidth(3)
        curv.SetLineColor(rt.kBlack)
        curv.Draw("lsame")
        finalcurv = curv.Clone()
        maxN = curv.GetN()
    except AttributeError:
        print "ERROR: no curve drawn"
        
    for i in xrange(1, contour0.GetSize()):
        curv = contour0.After(curv)
        curv.SetLineWidth(3)
        curv.SetLineColor(rt.kRed)
        curv.Draw("lsame")
        if curv.GetN()>maxN:
            maxN = curv.GetN()
            finalcurv = curv.Clone()

    contourFinal = finalcurv

        
    c.SetLogz(1)
    c.Print("T2bH_Obs.pdf")


    output = rt.TFile.Open('test_limit_rebin.root','recreate')
    output.cd()
    xsecUL.Write()
    rebinXsecULFixRange.Write()
    xsecGluino.Write()
    contourFinal.Write()
    subXsecUL.Write("sub_2d")
    output.Close()


        
