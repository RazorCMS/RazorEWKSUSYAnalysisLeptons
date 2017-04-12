# Make a basic plot showing the fitted significance in each analysis bin

import ROOT as rt

rt.gROOT.SetBatch()
c = rt.TCanvas("c","c",400,300)
h = rt.TH1F("h","Significance;Bin", 21, 0, 21)
h2 = rt.TH1F("h2","Significance;Bin", 21, 0, 21)
for ibin in range(21):
    f = rt.TFile("higgsCombine_bin%d.nsigma.ProfileLikelihood.mH120.root"%(ibin))
    t = f.Get("limit")
    t.GetEntry(0)
    h.Fill(ibin, t.limit)
    h.SetBinError(ibin+1,0.0)
    print t.limit
h.SetMarkerColor(rt.kBlack)
h.SetMinimum(-3.7)
h.SetMaximum(3.0)
h.SetStats(0)
h.SetMarkerStyle(20)
h.Draw("p")
h2.SetLineColor(rt.kBlack)
h2.Draw("lsame")
c.Print("significance.pdf")
