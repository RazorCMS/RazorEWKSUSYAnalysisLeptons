# Plot the profile likelihood as a function of the signal strength parameter r in each analysis bin

from subprocess import call
import ROOT as rt
from array import array

rt.gROOT.SetBatch()

c = rt.TCanvas("c","c",400,300)

nbins = 14
scanMin = 0
#scanMin = -5
scanMax = 10
for ibin in range(nbins):
    #perform scan
    call("combine -M MultiDimFit HggRazorCombinedCard_bin%d.txt --algo grid -n _bin%d --setPhysicsModelParameterRanges r=%d,%d --minimizerStrategy=2 --points 200"%(ibin,ibin,scanMin,scanMax), shell=True)
    #open combine output
    f = rt.TFile("higgsCombine_bin%d.MultiDimFit.mH120.root"%(ibin))
    t = f.Get("limit")
    #loop over tree and get (r, -2deltaNLL) for each point
    rs = []
    ls = []
    itertree = iter(t)
    next(itertree) #skip first entry
    for e in itertree:
        if e.deltaNLL < 3e3 and e.deltaNLL > -1000:
            rs.append(e.r)
            ls.append(2*e.deltaNLL)
    g = rt.TGraph( len(rs), array('f',rs), array('f',ls) )
    g.SetLineColor(rt.kBlue)
    g.SetLineWidth(2)
    g.GetXaxis().SetTitle("r")
    g.GetYaxis().SetTitle("-2 #Delta log(L)")
    g.GetYaxis().SetTitleOffset(1.5)
    g.SetTitle("")
    g.Draw("al")
    c.Print("likelihoodScan%d.pdf"%(ibin))
