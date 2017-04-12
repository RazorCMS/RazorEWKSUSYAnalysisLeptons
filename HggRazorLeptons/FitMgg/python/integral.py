from optparse import OptionParser
import ROOT as rt
import sys
from array import *


if __name__ == '__main__':
    parser = OptionParser()

    (options,args) = parser.parse_args()
     
    for f in args:
        if f.lower().endswith('.root'):
            rootFile = rt.TFile(f)

    w = rootFile.Get("w1")
    mgg = w.var("mgg")
    pdf = w.pdf("sideband_fitpdf_dExp_N1N2")
    function = pdf.asTF(rt.RooArgList(mgg))

    mgg.setRange("signal",103,160)
    
    xlow = mgg.getMin("signal")
    xup = mgg.getMax("signal")
    
    xmin = mgg.getMin()
    xmax = mgg.getMax()
    
    integral = function.Integral(xlow,xup)/function.Integral(xmin,xmax)

    print "integral from xlow=%i to xup=%i is %f"%(xlow,xup,integral)
                            
