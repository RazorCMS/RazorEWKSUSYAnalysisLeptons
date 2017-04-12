

void PlotFitResults(int option = 0) {

  string label = "";
   if (option == 0) {
     label = "_2p3+4p0";
    } else if (option == 1) {
     label = "_2p3+5p8";   
    } else if (option == 2) {
     label = "_2p3+DCS"; 
    }

  TFile *f = 0;
  for(int i=0; i<=20; i++) {

    f = TFile::Open(Form("/afs/cern.ch/work/s/sixie/public/releases/run2/CMSSW_7_4_2/src/RazorEWKSUSYAnalysis/HggRazor/FitMgg/output_bin%d%s.root",i,label.c_str()));    
    if (!f) continue;
    
    RooWorkspace *workspace = (RooWorkspace*)f->Get("w_sb");

    TCanvas *cv = new TCanvas("cv","cv",800,600);
    workspace->obj("sb_fit_frame")->Draw();
    cv->SaveAs(Form("bin%d%s.png",i,label.c_str()));

    cout << "Bin " << i << "\n";
    workspace->obj("sbFitResult")->Print();

    f->Close();

  }



}
