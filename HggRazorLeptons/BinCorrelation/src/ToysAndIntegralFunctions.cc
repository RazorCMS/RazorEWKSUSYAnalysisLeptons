//C++ INCLUDES
#include <iostream>
//ROOT INCLUDES
#include <TTree.h>
#include <TROOT.h>
#include <TFile.h>
#include <TCanvas.h>
#include <RooWorkspace.h>
#include <RooAbsPdf.h>
#include <RooRealVar.h>
#include <RooAbsData.h>
#include <RooPlot.h>
#include <RooArgSet.h>
#include <RooWorkspace.h>
#include <RooDataSet.h>
#include <RooRealVar.h>
#include <RooExponential.h>
#include <RooAddPdf.h>
#include <RooGaussian.h>
#include <RooMinimizer.h>
#include <RooFitResult.h>
#include <RooPlot.h>
#include <RooExtendPdf.h>
#include <RooStats/SPlot.h>
#include <RooStats/ModelConfig.h>
#include <RooGenericPdf.h>
#include <RooFormulaVar.h>
#include <RooBernstein.h>
#include <RooMinuit.h>
#include <RooNLLVar.h>
#include <RooRandom.h>
#include <RooDataHist.h>
#include <RooHistPdf.h>

//LOCAL INCLUDES
#include "ToysAndIntegralFunctions.hh"

double GetIntegral()
{
  gROOT->Reset();
  TFile* f = new TFile("scripts/workspace_global_fit.root");
  RooWorkspace* w = (RooWorkspace*)f->Get("w");
  RooAbsPdf* myPdf = w->pdf("pdf_binch14_highResBin9_nuis");
  myPdf->Print();
  RooRealVar *mgg = w->var("mGammaGamma_bin9");
  mgg->Print("");
  RooRealVar* mu = w->var("SMH_bin9_DCB_muCB");
  RooRealVar* mu_s = w->var("signal_bin9_DCB_muCB");
  RooRealVar* smh_jes = w->var("Photon_Trigger");
  
  TFile* f2 = new TFile("scripts/HggRazorWorkspace_bin9.root");
  RooWorkspace* myws = (RooWorkspace*)f2->Get("combineWS");
  RooAbsData *data = myws->data("data_bin9");
  data->Print();
  RooPlot* plot = mgg->frame();
  data->plotOn(plot);
  plot->Draw();

  RooArgSet *params = myPdf->getParameters(*data);
  std::cout << params->getRealValue("Photon_Trigger") << std::endl;
  params->Print();
  
  TCanvas* c = new TCanvas( "c", "c", 2119, 33, 800, 700 );
  c->SetHighLightColor(2);
  c->SetFillColor(0);
  c->SetBorderMode(0);
  c->SetBorderSize(2);
  c->SetFrameBorderMode(0);
  c->SetFrameBorderMode(0);

  myPdf->plotOn(plot);
  mu->setVal(120);
  mu_s->setVal(120);
  myPdf->plotOn(plot,RooFit::LineColor(kBlack));
  smh_jes->setVal(-5.0);
  mu->setVal(124.618);
  mu_s->setVal(124.618);
  myPdf->plotOn(plot,RooFit::LineColor(kRed));
  plot->Draw();
  c->SaveAs("test.pdf");
}
