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
    mgMin = 150
    mgMax = 700
    mchiMin = 0
    mchiMax = 300

    binWidth = 25 # to be changed to 25
    binWidthY = 25 # to be changed to 25
    nbinsX = (mgMax-mgMin)/binWidth + 1
    nbinsY = (mchiMax-mchiMin)/binWidthY + 1
     
    tfile = rt.TFile.Open('/afs/cern.ch/work/c/cpena/public/combineDiphotonHM/CMSSW_7_4_7/src/RazorEWKSUSYAnalysis/HggRazor/SMS-Plotting/test_limit.root')

    #####################
    ##observed limit TH2F
    #####################
    xsecULRaw = tfile.Get('limit')
    xsecUL = rt.TH2D(xsecULRaw.GetName()+'_fixRange',xsecULRaw.GetName()+'_fixRange',nbinsX,mgMin-binWidth/2.,mgMax+binWidth/2.,nbinsY,mchiMin-binWidthY/2., mchiMax+binWidthY/2.)
    ####################
    #Expected Limit TH2F
    ####################
    xsecULRaw_Exp = tfile.Get('limit_exp')
    xsecUL_Exp = rt.TH2D(xsecULRaw_Exp.GetName()+'_fixRange',xsecULRaw_Exp.GetName()+'_fixRange',nbinsX,mgMin-binWidth/2.,mgMax+binWidth/2.,nbinsY,mchiMin-binWidthY/2., mchiMax+binWidthY/2.)
    ####################
    #ExpectedUp Limit TH2F
    ####################
    xsecULRaw_ExpUp = tfile.Get('limit_exp_up')
    xsecUL_ExpUp = rt.TH2D(xsecULRaw_ExpUp.GetName()+'_fixRange',xsecULRaw_ExpUp.GetName()+'_fixRange',nbinsX,mgMin-binWidth/2.,mgMax+binWidth/2.,nbinsY,mchiMin-binWidthY/2., mchiMax+binWidthY/2.)
    ####################
    #ExpectedDown Limit TH2F
    ####################
    xsecULRaw_ExpD = tfile.Get('limit_exp_down')
    xsecUL_ExpD = rt.TH2D(xsecULRaw_ExpD.GetName()+'_fixRange',xsecULRaw_ExpD.GetName()+'_fixRange',nbinsX,mgMin-binWidth/2.,mgMax+binWidth/2.,nbinsY,mchiMin-binWidthY/2., mchiMax+binWidthY/2.)
    
    #Observed
    for i in range(1,xsecUL.GetNbinsX()+1):
        for j in range(1,xsecUL.GetNbinsY()+1):
            xCen = xsecUL.GetXaxis().GetBinCenter(i)
            yCen = xsecUL.GetYaxis().GetBinCenter(j)
            xsecUL.SetBinContent(i,j,xsecULRaw.GetBinContent(xsecULRaw.FindBin(xCen,yCen)))

    # do swiss cross average in real domain
    rebinXsecUL = rt.swissCrossInterpolate(xsecUL,"NE")

    #Expected
    for i in range(1,xsecUL_Exp.GetNbinsX()+1):
        for j in range(1,xsecUL_Exp.GetNbinsY()+1):
            xCenExp = xsecUL_Exp.GetXaxis().GetBinCenter(i)
            yCenExp = xsecUL_Exp.GetYaxis().GetBinCenter(j)
            xsecUL_Exp.SetBinContent(i,j,xsecULRaw_Exp.GetBinContent(xsecULRaw_Exp.FindBin(xCenExp,yCenExp)))

    # do swiss cross average in real domain for EXPECTED
    rebinXsecUL_Exp = rt.swissCrossInterpolate(xsecUL_Exp,"NE")

    #ExpectedUp
    for i in range(1,xsecUL_ExpUp.GetNbinsX()+1):
        for j in range(1,xsecUL_ExpUp.GetNbinsY()+1):
            xCenExpUp = xsecUL_ExpUp.GetXaxis().GetBinCenter(i)
            yCenExpUp = xsecUL_ExpUp.GetYaxis().GetBinCenter(j)
            xsecUL_ExpUp.SetBinContent(i,j,xsecULRaw_ExpUp.GetBinContent(xsecULRaw_ExpUp.FindBin(xCenExpUp,yCenExpUp)))

    # do swiss cross average in real domain for EXPECTED
    rebinXsecUL_ExpUp = rt.swissCrossInterpolate(xsecUL_ExpUp,"NE")

    #ExpectedUp
    for i in range(1,xsecUL_ExpD.GetNbinsX()+1):
        for j in range(1,xsecUL_ExpD.GetNbinsY()+1):
            xCenExpD = xsecUL_ExpD.GetXaxis().GetBinCenter(i)
            yCenExpD = xsecUL_ExpD.GetYaxis().GetBinCenter(j)
            xsecUL_ExpD.SetBinContent(i,j,xsecULRaw_ExpD.GetBinContent(xsecULRaw_ExpD.FindBin(xCenExpD,yCenExpD)))

    # do swiss cross average in real domain for EXPECTED
    rebinXsecUL_ExpD = rt.swissCrossInterpolate(xsecUL_ExpD,"NE")
    
    # do swiss cross rebin + average in real domain
    for i in xrange(0,nRebins):
        rebinXsecUL = rt.swissCrossRebin(rebinXsecUL,"NE")
        rebinXsecUL_Exp = rt.swissCrossRebin(rebinXsecUL_Exp,"NE")
        rebinXsecUL_ExpUp = rt.swissCrossRebin(rebinXsecUL_ExpUp,"NE")
        rebinXsecUL_ExpD = rt.swissCrossRebin(rebinXsecUL_ExpD,"NE")
        
    ##################
    ##redefine binning
    ##################
    binWidth = 25
    binWidthY = 25

    nbinsX = int((mgMax-mgMin)/binWidth) + 1
    nbinsY = int((mchiMax-mchiMin)/binWidthY) + 1
    
    
    rebinXsecULFixRange = rt.TH2D(rebinXsecUL.GetName()+'_fixRange',rebinXsecUL.GetName()+'_fixRange',nbinsX,mgMin-binWidth/2.,mgMax+binWidth/2.,nbinsY,mchiMin-binWidthY/2., mchiMax+binWidthY/2.)
    rebinXsecULFixRange_Exp = rt.TH2D(rebinXsecUL_Exp.GetName()+'_fixRange',rebinXsecUL_Exp.GetName()+'_fixRange',nbinsX,mgMin-binWidth/2.,mgMax+binWidth/2.,nbinsY,mchiMin-binWidthY/2., mchiMax+binWidthY/2.)
    rebinXsecULFixRange_ExpUp = rt.TH2D(rebinXsecUL_ExpUp.GetName()+'_fixRange',rebinXsecUL_ExpUp.GetName()+'_fixRange',nbinsX,mgMin-binWidth/2.,mgMax+binWidth/2.,nbinsY,mchiMin-binWidthY/2., mchiMax+binWidthY/2.)
    rebinXsecULFixRange_ExpD = rt.TH2D(rebinXsecUL_ExpD.GetName()+'_fixRange',rebinXsecUL_ExpD.GetName()+'_fixRange',nbinsX,mgMin-binWidth/2.,mgMax+binWidth/2.,nbinsY,mchiMin-binWidthY/2., mchiMax+binWidthY/2.)
    
    for i in range(1,rebinXsecULFixRange.GetNbinsX()+1):
        for j in range(1,rebinXsecULFixRange.GetNbinsY()+1):
            #Observed
            xCen = rebinXsecULFixRange.GetXaxis().GetBinCenter(i)
            yCen = rebinXsecULFixRange.GetYaxis().GetBinCenter(j)
            rebinXsecULFixRange.SetBinContent(i, j ,rebinXsecUL.GetBinContent(rebinXsecUL.FindBin(xCen,yCen)))
            #Expected
            xCen = rebinXsecULFixRange_Exp.GetXaxis().GetBinCenter(i)
            yCen = rebinXsecULFixRange_Exp.GetYaxis().GetBinCenter(j)
            rebinXsecULFixRange_Exp.SetBinContent(i, j ,rebinXsecUL_Exp.GetBinContent(rebinXsecUL_Exp.FindBin(xCen,yCen)))
            #ExpectedUp
            xCen = rebinXsecULFixRange_ExpUp.GetXaxis().GetBinCenter(i)
            yCen = rebinXsecULFixRange_ExpUp.GetYaxis().GetBinCenter(j)
            rebinXsecULFixRange_ExpUp.SetBinContent(i, j ,rebinXsecUL_ExpUp.GetBinContent(rebinXsecUL_ExpUp.FindBin(xCen,yCen)))
            #ExpectedD
            xCen = rebinXsecULFixRange_ExpD.GetXaxis().GetBinCenter(i)
            yCen = rebinXsecULFixRange_ExpD.GetYaxis().GetBinCenter(j)
            rebinXsecULFixRange_ExpD.SetBinContent(i, j ,rebinXsecUL_ExpD.GetBinContent(rebinXsecUL_ExpD.FindBin(xCen,yCen)))

    #####################################################
    # done with rebinning and interpolation of histograms
    #####################################################

    
    xsecGluino =  rt.TH2D("xsecGluino","xsecGluino",nbinsX,mgMin-binWidth/2.,mgMax+binWidth/2.,nbinsY,mchiMin-binWidthY/2., mchiMax+binWidthY/2.)
    xsecGluinoP =  rt.TH2D("xsecGluinoP","xsecGluinoP",nbinsX,mgMin-binWidth/2.,mgMax+binWidth/2.,nbinsY,mchiMin-binWidthY/2., mchiMax+binWidthY/2.)
    xsecGluinoM =  rt.TH2D("xsecGluinoM","xsecGluinoM",nbinsX,mgMin-binWidth/2.,mgMax+binWidth/2.,nbinsY,mchiMin-binWidthY/2., mchiMax+binWidthY/2.)
    
    thyXsec = {}
    thyXsecErr = {}
    for mg in range(100,2000+5,5):    
        for line in open('TChiWH_xsec_smoothingFormat.txt','r'):
            line = line.replace('\n','')
            if str(mg)==line.split(',')[0]:
                thyXsec[mg] = float(line.split(',')[1]) #pb
                thyXsecErr[mg] = 0.01*float(line.split(',')[2])      
    
    for i in xrange(1,xsecGluino.GetNbinsX()+1):
        for j in xrange(1,xsecGluino.GetNbinsY()+1):
            xCen = xsecGluino.GetXaxis().GetBinCenter(i)
            yCen = xsecGluino.GetYaxis().GetBinCenter(j)
            
            if xCen > 700 or yCen > 300:
                continue
            if xCen >= yCen+diagonalOffset and xCen <= mgMax:
                xsecVal = thyXsec[int(xCen)]
                xsecErr =  thyXsecErr[int(xCen)]
                xsecGluino.SetBinContent(i,j,xsecVal)
                xsecGluinoP.SetBinContent(i,j,xsecVal*(1+xsecErr))
                xsecGluinoM.SetBinContent(i,j,xsecVal*(1-xsecErr))
        

    c = rt.TCanvas("c","c",500,500)

    # subtract the predicted xsec to OBSERVED
    subXsecUL = rebinXsecULFixRange.Clone()
    subXsecUL.Add(xsecGluino,-1)
    #OBSERVED+
    subXsecULP = rebinXsecULFixRange.Clone()
    subXsecULP.Add(xsecGluinoP,-1)
    #OBSERVED-
    subXsecULM = rebinXsecULFixRange.Clone()
    subXsecULM.Add(xsecGluinoM,-1)
    #Expected
    subXsecUL_Exp = rebinXsecULFixRange_Exp.Clone()
    subXsecUL_Exp.Add(xsecGluino,-1)
    #Expected+
    subXsecUL_ExpUp = rebinXsecULFixRange_ExpUp.Clone()
    subXsecUL_ExpUp.Add(xsecGluino,-1)
    #Expected-
    subXsecUL_ExpD = rebinXsecULFixRange_ExpD.Clone()
    subXsecUL_ExpD.Add(xsecGluino,-1)
    
    contours = array('d',[0.0])
    subXsecUL.SetContour(1,contours)#OBSERVED CONTOUR
   
    c.SetLogz(0)
    ###OBS
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
        curv.SetLineColor(rt.kBlack)
        curv.Draw("lsame")
        if curv.GetN()>maxN:
            maxN = curv.GetN()
            finalcurv = curv.Clone()

    contourFinal = finalcurv


    c.SetLogz(1)
    c.Print("TChiWH_Obs.pdf")
    ###OBS+
    contours1 = array('d',[0.0])
    subXsecULP.SetContour(1,contours1)#OBSERVED- CONTOUR
    c.SetLogz(0)  
    subXsecULP.Draw("CONT Z LIST")
    c.Update()
    contsP = rt.gROOT.GetListOfSpecials().FindObject("contours")

    rebinXsecULFixRange.Draw("COLZ")
    rebinXsecULFixRange.GetXaxis().SetRangeUser(mgMin,mgMax)
    rebinXsecULFixRange.GetYaxis().SetRangeUser(mchiMin,mchiMax)
    rebinXsecULFixRange.SetMinimum(1e-1)
    rebinXsecULFixRange.SetMaximum(10)
    rebinXsecULFixRange.Draw("COLZ")
    c.Update()
        
    contour0P = contsP.At(0)
    curvP = contour0P.First()
    finalcurvP = rt.TGraph(1)
    try:
        curvP.SetLineWidth(3)
        curvP.SetLineColor(rt.kBlack)
        curvP.Draw("lsame")
        finalcurvP = curvP.Clone()
        maxN = curvP.GetN()
    except AttributeError:
        print "ERROR: no curve drawn"
        
    for i in xrange(1, contour0P.GetSize()):
        curvP = contour0P.After(curvP)
        curvP.SetLineWidth(3)
        curvP.SetLineColor(rt.kBlack)
        curvP.Draw("lsame")
        if curvP.GetN()>maxN:
            maxN = curvP.GetN()
            finalcurvP = curvP.Clone()

    contourFinalP = finalcurvP
    
    c.SetLogz(1)
    c.Print("TChiWH_ObsP.pdf")

    ###OBS-
    contours2 = array('d',[0.0])
    subXsecULM.SetContour(1,contours2)#OBSERVED- CONTOUR
    c.SetLogz(0)  
    subXsecULM.Draw("CONT Z LIST")
    c.Update()
    contsM = rt.gROOT.GetListOfSpecials().FindObject("contours")

    rebinXsecULFixRange.Draw("COLZ")
    rebinXsecULFixRange.GetXaxis().SetRangeUser(mgMin,mgMax)
    rebinXsecULFixRange.GetYaxis().SetRangeUser(mchiMin,mchiMax)
    rebinXsecULFixRange.SetMinimum(1e-1)
    rebinXsecULFixRange.SetMaximum(10)
    rebinXsecULFixRange.Draw("COLZ")
    c.Update()
        
    contour0M = contsM.At(0)
    curvM = contour0M.First()
    finalcurvM = rt.TGraph(1)
    try:
        curvM.SetLineWidth(3)
        curvM.SetLineColor(rt.kBlack)
        curvM.Draw("lsame")
        finalcurvM = curvM.Clone()
        maxN = curvM.GetN()
    except AttributeError:
        print "ERROR: no curve drawn"
        
    for i in xrange(1, contour0M.GetSize()):
        curvM = contour0M.After(curvM)
        curvM.SetLineWidth(3)
        curvM.SetLineColor(rt.kBlack)
        curvM.Draw("lsame")
        if curvM.GetN()>maxN:
            maxN = curvM.GetN()
            finalcurvM = curvM.Clone()

    contourFinalM = finalcurvM
    
    c.SetLogz(1)
    c.Print("TChiWH_ObsM.pdf")

    ####
    #EXP
    ####
    contours3 = array('d',[0.0])
    subXsecUL_Exp.SetContour(1,contours3)#EXPECTED CONTOUR
    c.SetLogz(0)  
    subXsecUL_Exp.Draw("CONT Z LIST")
    c.Update()
    contsExp = rt.gROOT.GetListOfSpecials().FindObject("contours")

    rebinXsecULFixRange.Draw("COLZ")
    rebinXsecULFixRange.GetXaxis().SetRangeUser(mgMin,mgMax)
    rebinXsecULFixRange.GetYaxis().SetRangeUser(mchiMin,mchiMax)
    rebinXsecULFixRange.SetMinimum(1e-1)
    rebinXsecULFixRange.SetMaximum(10)
    rebinXsecULFixRange.Draw("COLZ")
    c.Update()
        
    contour0Exp = contsExp.At(0)
    curvExp = contour0Exp.First()
    finalcurvExp = rt.TGraph(1)
    try:
        curvExp.SetLineWidth(3)
        curvExp.SetLineColor(rt.kBlack)
        curvExp.Draw("lsame")
        finalcurvExp = curvExp.Clone()
        maxN = curvExp.GetN()
    except AttributeError:
        print "ERROR: no curve drawn"
        
    for i in xrange(1, contour0Exp.GetSize()):
        curvExp = contour0Exp.After(curvExp)
        curvExp.SetLineWidth(3)
        curvExp.SetLineColor(rt.kBlack)
        curvExp.Draw("lsame")
        if curvExp.GetN()>maxN:
            maxN = curvExp.GetN()
            finalcurvExp = curvExp.Clone()

    contourFinalExp = finalcurvExp
    
    c.SetLogz(1)
    c.Print("TChiWH_ObsExp.pdf")

    ####
    #EXP+
    ####
    contours4 = array('d',[0.0])
    subXsecUL_ExpUp.SetContour(1,contours4)#EXPECTED CONTOUR
    c.SetLogz(0)  
    subXsecUL_ExpUp.Draw("CONT Z LIST")
    c.Update()
    contsExpUp = rt.gROOT.GetListOfSpecials().FindObject("contours")

    rebinXsecULFixRange.Draw("COLZ")
    rebinXsecULFixRange.GetXaxis().SetRangeUser(mgMin,mgMax)
    rebinXsecULFixRange.GetYaxis().SetRangeUser(mchiMin,mchiMax)
    rebinXsecULFixRange.SetMinimum(1e-1)
    rebinXsecULFixRange.SetMaximum(10)
    rebinXsecULFixRange.Draw("COLZ")
    c.Update()
        
    contour0ExpUp = contsExpUp.At(0)
    curvExpUp = contour0ExpUp.First()
    finalcurvExpUp = rt.TGraph(1)
    try:
        curvExpUp.SetLineWidth(3)
        curvExpUp.SetLineColor(rt.kBlack)
        curvExpUp.Draw("lsame")
        finalcurvExpUp = curvExpUp.Clone()
        maxN = curvExpUp.GetN()
    except AttributeError:
        print "ERROR: no curve drawn"
        
    for i in xrange(1, contour0ExpUp.GetSize()):
        curvExpUp = contour0ExpUp.After(curvExpUp)
        curvExpUp.SetLineWidth(3)
        curvExpUp.SetLineColor(rt.kBlack)
        curvExpUp.Draw("lsame")
        if curvExpUp.GetN()>maxN:
            maxN = curvExpUp.GetN()
            finalcurvExpUp = curvExpUp.Clone()

    contourFinalExpUp = finalcurvExpUp
    
    c.SetLogz(1)
    c.Print("TChiWH_ObsExpUp.pdf")

    ####
    #EXP Down
    ####
    contours5 = array('d',[0.0])
    subXsecUL_ExpD.SetContour(1,contours5)#EXPECTED CONTOUR
    c.SetLogz(0)  
    subXsecUL_ExpD.Draw("CONT Z LIST")
    c.Update()
    contsExpD = rt.gROOT.GetListOfSpecials().FindObject("contours")

    rebinXsecULFixRange.Draw("COLZ")
    rebinXsecULFixRange.GetXaxis().SetRangeUser(mgMin,mgMax)
    rebinXsecULFixRange.GetYaxis().SetRangeUser(mchiMin,mchiMax)
    rebinXsecULFixRange.SetMinimum(1e-1)
    rebinXsecULFixRange.SetMaximum(10)
    rebinXsecULFixRange.Draw("COLZ")
    c.Update()
        
    contour0ExpD = contsExpD.At(0)
    curvExpD = contour0ExpD.First()
    finalcurvExpD = rt.TGraph(1)
    try:
        curvExpD.SetLineWidth(3)
        curvExpD.SetLineColor(rt.kBlack)
        curvExpD.Draw("lsame")
        finalcurvExpD = curvExpD.Clone()
        maxN = curvExpD.GetN()
    except AttributeError:
        print "ERROR: no curve drawn"
        
    for i in xrange(1, contour0ExpD.GetSize()):
        curvExpD = contour0ExpD.After(curvExpD)
        curvExpD.SetLineWidth(3)
        curvExpD.SetLineColor(rt.kBlack)
        curvExpD.Draw("lsame")
        if curvExpD.GetN()>maxN:
            maxN = curvExpD.GetN()
            finalcurvExpD = curvExpD.Clone()

    contourFinalExpD = finalcurvExpD
    
    c.SetLogz(1)
    c.Print("TChiWH_ObsExpD.pdf")
       
    ###OBS-
    #subXsecULM.Draw("CONT Z LIST")
    #c.Update()
    #contsM = rt.gROOT.GetListOfSpecials().FindObject("contours")
    
    ###Expected
    #subXsecUL_Exp.Draw("CONT Z LIST")
    #c.Update()
    #conts_Exp = rt.gROOT.GetListOfSpecials().FindObject("contours")
    
        
    


    output = rt.TFile.Open('test_limit_rebin.root','recreate')
    output.cd()
    xsecUL.Write()
    rebinXsecULFixRange.Write()
    rebinXsecULFixRange_Exp.Write("exp_2d")
    xsecGluino.Write()
    contourFinal.Write()
    contourFinalP.Write("obsUp")
    contourFinalM.Write("obsD")
    contourFinalExp.Write("exp")
    contourFinalExpUp.Write("expUp")
    contourFinalExpD.Write("expD")
    subXsecUL.Write("debugObs")
    output.Close()


        
