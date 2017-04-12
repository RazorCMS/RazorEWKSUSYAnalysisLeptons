### Plot kinematic distributions for events in analysis bin 0 
### Requires EOS to be mounted in the current directory

import ROOT as rt 
import sys

def cleanstring(s):
    for c in '+-*/!@#$%^&()[]{}?\\_:=':
        s = s.replace(c,'')
    return s

if __name__ == '__main__':
    rt.gROOT.SetBatch()

    f = rt.TFile.Open("eos/cms/store/group/phys_susy/razor/Run2Analysis/HggRazor/ICHEP2016Combined/V3p4_PhotonCorrJuly20_RegularSelectionSequence_20160720/HggRazor_DoubleEG_Run2_MRSkim_2p3+12p9ifb.root")
    t = f.Get("HggRazor")

    cuts = "mGammaGamma > 103. && mGammaGamma < 160. && pho1passIso == 1 && pho2passIso == 1 && pho1passEleVeto == 1 && pho2passEleVeto == 1 && abs(pho1Eta) <1.48 && abs(pho2Eta)<1.48 && (pho1Pt>40||pho2Pt>40)  && pho1Pt> 25. && pho2Pt>25. && pTGammaGamma >= 110  && (Flag_HBHENoiseFilter == 1 && Flag_goodVertices == 1 && Flag_eeBadScFilter == 1 && Flag_HBHEIsoNoiseFilter == 1) && MR > 600 && MR < 10000 && t1Rsq > 0.025 && t1Rsq < 1.0 && ( HLTDecision[82] || HLTDecision[83] || HLTDecision[93] )"
    cutsSignal = cuts + " && mGammaGamma > 122 && mGammaGamma < 129"

    #make histograms
    histparams = [("MR", "M_{R}", (100, 600, 1000)),
                  ("t1Rsq", "R^{2}", (100, 0.025, 0.3)),
                  ("n_Jets", "N_{jets}", (10, 0, 10)),
                  ("nLooseBTaggedJets", "N_{b} (loose CSV)", (5, 0, 5)),
                  ("t1MET", "MET", (100, 0, 300)),
                  ("HT", "H_{T}", (100, 300, 1000)),
                  ("sigmaMoverM", "#sigma_{M}/M", (100, 0, 0.03)),
                  ("pho1Pt", "Photon 1 p_{T}", (100, 20, 400)),
                  ("pho1R9", "Photon 1 R_{9}", (100, 0.4, 1)),
                  ("pho1SigmaIetaIeta", "Photon 1 #sigma_{i#eta i#eta}", (100, 0, 0.02)),
                  ("pho2Pt", "Photon 2 p_{T}", (100, 20, 300)),
                  ("pho2R9", "Photon 2 R_{9}", (100, 0.4, 1)),
                  ("pho2SigmaIetaIeta", "Photon 2 #sigma_{i#eta i#eta}", (100, 0, 0.02)),
                 ]
    histparams2D = [
                  ("pho1Eta:pho1Phi", "Photon #eta vs #phi", (100, -3.2, 3.2, 100, -1.6, 1.6))
                 ]
    hists = {}
    histsSignal = {}
    hists2D = {}
    for params in histparams:
        hists[params[0]] = rt.TH1F(cleanstring(params[0]),params[1],*params[2])
        histsSignal[params[0]] = rt.TH1F(cleanstring(params[0])+"Signal",params[1],*params[2])
    for params in histparams2D:
        hists2D[params[0]] = rt.TH2F(cleanstring(params[0]),params[1],*params[2])

    #fill histograms and print
    c = rt.TCanvas("c", "c", 800, 600)
    for name,hist in hists.iteritems():
        cleanname = cleanstring(name)
        t.Draw(name+'>>'+cleanname, cuts)
        t.Draw(name+'>>'+cleanname+"Signal", cutsSignal)
        histsSignal[name].SetLineColor(rt.kGreen)
        hist.Draw()
        histsSignal[name].Draw("same")
        leg = rt.TLegend(0.6,0.6,0.8,0.7)
        leg.AddEntry(hist,"Bin 0")
        leg.AddEntry(histsSignal[name], "Bin 0, 122 < m_{#gamma#gamma} < 129")
        leg.Draw()
        c.Print('plots/bin0_'+cleanname+'.pdf')
    for name,hist in hists2D.iteritems():
        cleanname = cleanstring(name)
        t.Draw(name+'>>'+cleanname, cutsSignal)
        hist.SetStats(0)
        hist.Draw("colz")
        c.Print('plots/bin0_'+cleanname+'.pdf')
