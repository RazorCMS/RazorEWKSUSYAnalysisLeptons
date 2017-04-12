{
  gROOT->Reset();
  TFile* f = new TFile("workspace.root");
  RooWorkspace* w = (RooWorkspace*)f->Get("w");
  RooAbsPdf* myPdf = w->pdf("pdf_binbin9_nuis");
  myPdf->Print();
  RooRealVar *mgg = w->var("mGammaGamma_bin9");
  mgg->Print("");
  RooRealVar* mu = w->var("SMH_bin9_DCB_muCB");
  RooRealVar* mu_s = w->var("signal_bin9_DCB_muCB");
  RooRealVar* smh_jes = w->var("Photon_Trigger");
  
  TFile* f2 = new TFile("HggRazorWorkspace_bin9.root");
  RooWorkspace* myws = (RooWorkspace*)f2->Get("combineWS");
  RooAbsData *data = myws->data("data_bin9");
  data->Print();
  RooPlot* plot = mgg->frame();
  data->plotOn(plot);
  plot->Draw();

  RooArgSet *params = myPdf->getParameters(*data);
  std::cout << params->getRealValue("Photon_Trigger") << std::endl;
  params->Print();
  
  myPdf->plotOn(plot);
  mu->setVal(120);
  mu_s->setVal(120);
  myPdf->plotOn(plot,RooFit::LineColor(kBlack));
  smh_jes->setVal(-5.0);
  mu->setVal(124.618);
  mu_s->setVal(124.618);
  myPdf->plotOn(plot,RooFit::LineColor(kRed));
  plot->Draw();
}
