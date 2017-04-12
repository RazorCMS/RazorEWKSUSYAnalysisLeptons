{


  TFile *f = 0;

  for(int i=0; i<=20; i++) {

    f = TFile::Open(Form("/afs/cern.ch/work/s/sixie/public/releases/run2/CMSSW_7_4_2/src/RazorEWKSUSYAnalysis/HggRazor/FitMgg/HggRazorDataCards/ForPreapproval/mlfit_bin%d.root",i));
    assert(f);

    
    RooArgSet *norm_fit_s = (RooArgSet*)f->Get("norm_fit_s");
    RooAbsArg* signal = (RooAbsArg*)norm_fit_s->find(Form("bin%d/signal",i));
    RooAbsArg* bkg = (RooAbsArg*)norm_fit_s->find(Form("bin%d/Bkg",i));
    RooAbsArg* SMH = (RooAbsArg*)norm_fit_s->find(Form("bin%d/SMH",i));
    
    //cout << bkg << " & " << SMH " & " << signal << " \\\n";
    cout << "Bin " << i << "\n";
    bkg->Print();
    SMH->Print();
    signal->Print();

  }



}
