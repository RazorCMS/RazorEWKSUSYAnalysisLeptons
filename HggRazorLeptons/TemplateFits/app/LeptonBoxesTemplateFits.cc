/// \file
/// \ingroup tutorial_roofit
/// \notebook -js
///  'SPECIAL PDFS' RooFit tutorial macro #706
///
///  Histogram based p.d.f.s and functions
///
/// \macro_image
/// \macro_output
/// \macro_code
/// \author 07/2008 - Wouter Verkerke 


#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooGaussian.h"
#include "RooConstVar.h"
#include "RooPolynomial.h"
#include "RooHistPdf.h"
#include "RooDataHist.h"
#include "TCanvas.h"
#include "TAxis.h"
#include "RooPlot.h"
#include "TH1D.h"
#include "TFile.h"
#include "RooAddPdf.h"
using namespace RooFit ;


int main( int argc, char** argv )
{

  //----------------------------------------------
  //Retrieve Histograms
  //----------------------------------------------
  TFile* fin = new TFile("/Users/cmorgoth/git/RazorEWKSUSYAnalysisLeptons/HggRazorLeptons/TemplateFits/../PlottingAndSystematic/histograms_OneEle.root", "READ");
  TH1D* hdata = (TH1D*)fin->Get("mt_data");
  TH1D* hgg   = (TH1D*)fin->Get("mt_diphoton");
  TH1D* hgj   = (TH1D*)fin->Get("mt_gammaJet");
  
  TH1D* hwgg  = (TH1D*)fin->Get("mt_wgg");
  TH1D* hwg  = (TH1D*)fin->Get("mt_wg");
  TH1D* hzgg  = (TH1D*)fin->Get("mt_zgg");
  
  TH1D* htg  = (TH1D*)fin->Get("mt_tg");
  TH1D* httg  = (TH1D*)fin->Get("mt_ttg");
  TH1D* httgg  = (TH1D*)fin->Get("mt_ttgg");

  hgg->Add(hgj);
  
  hwgg->Add(hzgg);
  hwgg->Add(hwg);
  hwgg->Scale(0.362879);

  httgg->Add(htg);
  httgg->Add(httg);
  
  
  // C r e a t e   p d f   f o r   s a m p l i n g 
  // ---------------------------------------------
  RooRealVar x("x","x",0,150) ;
  //RooRealVar x("x","x",-10,10) ;
  //  RooPolynomial p("p","p",x,RooArgList(RooConst(0.01),RooConst(-0.01),RooConst(0.0004))) ;

  
  //RooDataHist data("data", "data", x, RooFit::Import(*hdata), 1.0);

  //TH1* hh = new TH1D("demo","demo histo",100,-20,20) ;
  RooDataHist data("data","data",x,hdata);
  RooDataHist ggHist("ggHist","ggHist",x,hgg);
  RooDataHist gjHist("gjHist","gjHist",x,hgj);
  RooDataHist wggHist("wggHist","wggHist",x,hwgg);
  RooDataHist ttggHist("ttggHist","ttggHist",x,httgg);
  
  //RooDataHist ggHist("ggHist","ggHist",x,hgg);
  // C r e a t e   l o w   s t a t s   h i s t o g r a m
  // ---------------------------------------------------
  
  // Sample 500 events from p
  x.setBins(15);
  //RooDataSet* data1 = p.generate(x,500) ;
  
  // Create a binned dataset with 20 bins and 500 events
  //RooDataHist* hist1 = data1->binnedClone() ;
  
  // Represent GG HISTOGRAM PDF in dh as pdf in x
  RooHistPdf ggHistPDF("ggHistPDF","ggHistPDF",x,ggHist,0) ;
  // Represent GJ HISTOGRAM PDF in dh as pdf in x
  RooHistPdf gjHistPDF("gjHistPDF","gjHistPDF",x,gjHist,0) ;
  // Represent WGG HISTOGRAM PDF in dh as pdf in x
  RooHistPdf wggHistPDF("wggHistPDF","wggHistPDF",x,wggHist,0) ;
  // Represent ttGG HISTOGRAM PDF in dh as pdf in x
  RooHistPdf ttggHistPDF("ttggHistPDF","ttggHistPDF",x,ttggHist,0) ;


  double qcdInitValue  = hgg->Integral();
  double wggInitValue  = hwgg->Integral();
  double ttggInitValue = httgg->Integral();

  RooRealVar nqcd( "nqcd", "#singal events", qcdInitValue, 0, 1000 );
  RooRealVar nwgg( "nwgg", "#background events", wggInitValue, 0, 1000 );
  RooRealVar nttgg( "nttgg", "#background events2", ttggInitValue, 0, 1000 );
  nwgg.setConstant(kTRUE);
  nttgg.setConstant(kTRUE);
  RooAddPdf model( "model", "myModel", RooArgList( ggHistPDF, wggHistPDF, ttggHistPDF ), RooArgList( nqcd, nwgg, nttgg) );
  // F i t   m o d e l   t o   d a t a
  // -----------------------------
  // Fit pdf to data
  model.fitTo(data) ;


  // Plot unbinned data and histogram pdf overlaid
  RooPlot* frame1 = x.frame(Title("Low statistics histogram pdf"),Bins(40)) ;
  data.plotOn(frame1) ;
  model.plotOn(frame1,RooFit::LineColor(kRed)) ;  
  //ggHistPDF.plotOn(frame1,RooFit::LineColor(kBlue)) ;
  //wggHistPDF.plotOn(frame1,RooFit::LineColor(kGreen)) ;
  
  
  TCanvas* c = new TCanvas("rf706_histpdf","rf706_histpdf",800,400) ;  
  frame1->Draw() ;
  c->SaveAs("fit.pdf");

  std::cout << "=======================================" << std::endl;
  std::cout << "[INFO]: qcd k-factor: " << nqcd.getVal()/qcdInitValue << std::endl;
  std::cout << "[INFO]: wg/wgg/zgg k-factor: " << nwgg.getVal()/wggInitValue << std::endl;
  std::cout << "=======================================" << std::endl;
  
  
  return 0;
}
