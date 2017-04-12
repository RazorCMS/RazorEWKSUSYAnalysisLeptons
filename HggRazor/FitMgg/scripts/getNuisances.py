### Plot post-fit nuisances for the mGammaGamma fits in each analysis bin

import sys,os
import ROOT as rt

class RootIterator(object):
    """A wrapper around the ROOT iterator so that it can be used in python"""
    def __init__(self, o):
        if hasattr(o,'Class') and o.Class().InheritsFrom('TIterator'):
            self.iter = o
        elif hasattr(o,'createIterator'):
            self.iter = o.createIterator()
        elif hasattr(o,'MakeIterator'):
            self.iter = o.MakeIterator()
        elif hasattr(o,'componentIterator'):
            self.iter = o.componentIterator()
        else:
            self.iter = None
    def __iter__(self):
        return self
    def next(self):
        n = self.iter.Next()
        if n is None or not n:
            raise StopIteration()
        return n

def getStdDev(cov, nuis):
    """Get the standard deviation of a nuisance using the covariance matrix"""
    xbin = cov.GetXaxis().FindBin(nuis)
    ybin = cov.GetYaxis().FindBin(nuis)
    variance = cov.GetBinContent(xbin,ybin)
    return (variance)**(0.5)

if __name__ == '__main__':
    rt.gROOT.SetBatch()
    fnames = [ "mlfit_bin%d.root"%(ibin) for ibin in range(14) ]
    #fnames.append("mlfit_allbins.root")
    c = rt.TCanvas("c","c",400,300)
    #histogram for mu_Global
    mu = rt.TH1F("mu",";Bin number;#mu",14,0,14)
    #histogram showing percent difference in Higgs yield pre- and post-fit
    smhPercDiff = rt.TH1F("smhPercDiff",";Bin number;(N_{postfit}-N_{prefit})/N_{prefit}",14,0,14)
    smhErrPercDiff = rt.TH1F("smhErrPercDiff",";Bin number;(#sigma_{postfit}-#sigma_{prefit})/#sigma_{prefit}",14,0,14)
    smhYieldsPre = []
    smhErrsPre = []
    smhYieldsPost = []
    smhErrsPost = []
    for fname in fnames:
        if 'allbins' in fname:
            binnum = -1
        else:
            binnum = int(os.path.basename(fname).replace('mlfit_bin','').replace('.root',''))
        #open the fit file
        f = rt.TFile(fname)
        #get the prefit normalization
        norm_prefit = f.Get("norm_prefit")
        #get the postfit normalization
        norm_fit_s = f.Get("norm_fit_s")
        #get the prefit nuisances
        nuisances_prefit = f.Get("nuisances_prefit")
        #get the fit results
        fit_s = f.Get("fit_s")
        nuisances_postfit = fit_s.floatParsFinal()

        #histogram for nuisances
        if binnum >= 0:
            h = rt.TH1F("h","Postfit nuisances for bin %d"%(binnum),72,0,72)
        else:
            h = rt.TH1F("h","Postfit nuisances (combined fit)",72,0,72)

        #get normalization
        smhPre = 0.0
        smhErrPre = 0.0
        smhPost = 0.0
        smhErrPost = 0.0
        print "PREFIT:"
        for norm in RootIterator(norm_prefit):
            if 'SMH' in norm.GetName():
                print norm.GetName(),":",norm.getVal(),"+/-",norm.getError()
                #accumulate yields
                smhPre += norm.getVal()
                smhErrPre = ( (smhErrPre)**2 + (norm.getError())**2 )**(0.5)
        print "POSTFIT:"
        for norm in RootIterator(norm_fit_s):
            if 'SMH' in norm.GetName():
                print norm.GetName(),":",norm.getVal(),"+/-",norm.getError()
                #accumulate yields
                smhPost += norm.getVal()
                smhErrPost = ( (smhErrPost)**2 + (norm.getError())**2 )**(0.5)
        #put into histograms
        if binnum >= 0:
            smhPercDiff.SetBinContent( binnum+1, (smhPost-smhPre)/smhPre )
            smhPercDiff.SetBinError(binnum+1, 0)
            smhErrPercDiff.SetBinContent( binnum+1, (smhErrPost-smhErrPre)/smhErrPre )
            smhErrPercDiff.SetBinError(binnum+1, 0)
            smhYieldsPre.append(smhPre)
            smhYieldsPost.append(smhPost)
            smhErrsPre.append(smhErrPre)
            smhErrsPost.append(smhErrPost)
        #iterate on nuisances
        print "NUISANCES:"
        for nuis in RootIterator(nuisances_prefit):
            name = nuis.GetName()
            if name.startswith("SMH"):
                #print "Prefit:",name,":",nuis.getVal(),"+/-",nuis.getError()
                #find postfit nuisance
                post = nuisances_postfit.find(name).getVal()
                err = nuisances_postfit.find(name).getError()
                #print "Postfit:",name,":",post,"+/-",err
                h.Fill(name,post)
                ibin = h.GetXaxis().FindBin(name)
                h.SetBinError(ibin,err)
            elif "mu_Global" in name: 
                post = nuisances_postfit.find(name).getVal()
                err = nuisances_postfit.find(name).getError()
                print name,":",post,"+/-",err
                if name == "mu_Global" and binnum >= 0:
                    mu.SetBinContent(binnum+1, post)
                    mu.SetBinError(binnum+1, err)
        h.SetStats(0)
        h.SetMarkerStyle(20)
        h.SetMarkerSize(0.5)
        h.SetLineWidth(2)
        h.SetMarkerColor(rt.kBlack)
        h.SetLineColor(rt.kBlue)
        h.GetXaxis().SetLabelSize(0.02)
        h.Draw("pe")
        if binnum >= 0:
            c.Print("nuis%d.pdf"%(binnum))
        else:
            c.Print("nuisAll.pdf")

    smhPercDiff.GetYaxis().SetRangeUser(-0.005, 0.005)
    smhPercDiff.SetBinContent(3,-999)
    smhPercDiff.GetYaxis().SetTitleOffset(1.3)
    smhErrPercDiff.SetMinimum(-0.4)
    for hist in [ mu, smhPercDiff, smhErrPercDiff ]:
        hist.SetStats(0)
        hist.SetMarkerStyle(20)
        hist.SetMarkerSize(0.5)
        hist.SetLineWidth(2)
        hist.SetMarkerColor(rt.kBlack)
        hist.SetLineColor(rt.kBlue)
        hist.Draw("pe")
        c.Print("%s.pdf"%(hist.GetName()))
    with open("higgsyields.tex","w") as f_out:
        f_out.write("\\hline\nBin & Prefit yield & Postfit yield \\\\\n\\hline\n")
        for i,pre in enumerate(smhYieldsPre):
            f_out.write("%d & %.2f $\\pm$ %.2f & %.2f $\\pm$ %.2f \\\\\n"%(i,pre,smhErrsPre[i],smhYieldsPost[i],smhErrsPost[i]))
            f_out.write("\\hline\n")
