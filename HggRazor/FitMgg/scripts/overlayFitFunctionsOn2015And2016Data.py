### Get the best-fit function shape from the combined 2015+2016 background fit and overlay it on 2015 and 2016 data separately

import ROOT as rt
rt.gROOT.SetBatch()

dir_2015 = "HggRazorDataCards/sb300_lsp1_unblinded_76X2p3.txt"
dir_2016 = "HggRazorDataCards/sb300_lsp1_unblinded_80X4p0.txt"
dir_combined = "HggRazorDataCards/sb300_lsp1_unblinded_76X2p3_80X4p0.txt"

c = rt.TCanvas("c","c",800,600)

for ibin in range(21):
    if ibin in [3,5,9,15,16,17]: continue 
    ## open the fit files from 2015 and 2016 to get the fit functions and datasets
    # 2015
    f2015 = rt.TFile( "%s/HggRazorWorkspace_bin%d.root"%(dir_2015,ibin) )
    w2015 = f2015.Get("combineWS")
    mgg2015 = w2015.var("mGammaGamma_bin%d"%(ibin))
    pdf2015 = w2015.pdf("singleExp_Bkg_bin%d_sExp"%(ibin))
    data2015 = w2015.data("data_bin%d"%(ibin))

    # 2016
    f2016 = rt.TFile( "%s/HggRazorWorkspace_bin%d.root"%(dir_2016,ibin) )
    w2016 = f2016.Get("combineWS")
    pdf2016 = w2016.pdf("singleExp_Bkg_bin%d_sExp"%(ibin))
    data2016 = w2016.data("data_bin%d"%(ibin))
    mgg2016 = w2016.var("mGammaGamma_bin%d"%(ibin))

    # open the fit result file from 2015+2016 to get the best-fit parameters
    fcombined = rt.TFile( "%s/mlfit_bin%d.root"%(dir_combined,ibin) )
    fresult = fcombined.Get("fit_s")
    slope = fresult.floatParsFinal().find("singleExp_Bkg_bin%d_sExp_a"%(ibin))

    #set the fit function slope
    w2015.var("singleExp_Bkg_bin%d_sExp_a"%(ibin)).setVal(slope.getVal())
    w2016.var("singleExp_Bkg_bin%d_sExp_a"%(ibin)).setVal(slope.getVal())

    #plot for 2015
    plot2015 = mgg2015.frame()
    data2015.plotOn(plot2015)
    pdf2015.plotOn(plot2015)
    plot2015.Draw()
    c.Print("bin%d_2015.pdf"%(ibin))

    #plot for 2016
    plot2016 = mgg2016.frame()
    data2016.plotOn(plot2016)
    pdf2016.plotOn(plot2016)
    plot2016.Draw()
    c.Print("bin%d_2016.pdf"%(ibin))
