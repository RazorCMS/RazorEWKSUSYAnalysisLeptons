//////////////////////////////////////////////////////////////////////////
// Susy Mgg Fit
// Fits Mgg distribution from a tree
// Cristian Pena (Caltech)
/////////////////////////////////////////////////////////////////////////

#ifndef __CINT__
#include "RooGlobalFunc.h"
#endif
#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooGaussian.h"
#include "RooExponential.h"
#include "RooAddPdf.h"
#include "RooArgList.h"

#include "TTree.h"
#include "TFile.h"
#include "TString.h"

#include "TCanvas.h"
#include "RooPlot.h"
#include "TAxis.h"

using namespace RooFit ;

const double m_low  = 103.;
const double m_high = 160.;

const double mu_low  = 120.;
const double mu_high = 130.;
const double mu_init = 126.;

const double sigma_low  = 0.1;
const double sigma_high = 10.;
const double sigma_init = 1.5;

const double lambda_low  = -50;
const double lambda_high = -0.0001;
const double lambda_init = -0.02;

void doSusyMggFit( std::string rootFname )
{

  // G e t t i n g   T r e e
  //------------------------
  //TFile* fin = new TFile("/Users/cmorgoth/Work/syn_hgg_analysis/DoublePhoton_22Jan2013_Run2012ABCD_v9__HighRes.root");
  TFile* fin = new TFile( rootFname.c_str() );
  TTree* tree = (TTree*)fin->Get("SusyHggTree");
  

  // A p p l y  C u t s
  //------------------------
  TString cut = "MR>250. && t1Rsq>0.05 && pho1_pt>25. && pho2_pt>25. && (pho1_pt>40. || pho2_pt>40.) && pho1_pass_iso==1 && pho2_pass_iso==1 && ptgg>20. && fabs(pho1_eta)<1.44 && fabs(pho2_eta)<1.44 && mgg>103. && mgg<160.";
  TTree* t = tree->CopyTree( cut );
  
  
  // G e t t i n g  D a t a s e t
  //-----------------------------
  RooRealVar mgg( "mgg", "mgg", m_low, m_high );
  RooDataSet dataset( "dataset", "dataset", RooArgSet( mgg ), Import(*t) ) ;
  dataset.Print();
  RooPlot* frameMgg = mgg.frame( Title("Mgg unbinned dataset") );
  dataset.plotOn( frameMgg, Binning( 38 ) );

  
  // S e t u p   m o d e l 
  // ---------------------
  // Declare variables x,mean,sigma with associated name, title, initial value and allowed range
  RooRealVar x( "x", "x", m_low, m_high );
  RooRealVar mu( "mu","mu of gaussian", mu_init, mu_low, mu_high ) ;
  RooRealVar sigma( "sigma", "width of gaussian", sigma_init, sigma_low, sigma_high ) ;
  RooRealVar lambda( "lambda", "exponent of exponential", lambda_init, lambda_low, lambda_high );
  
  // Build gaussian p.d.f in terms of x,mu and sigma
  RooGaussian gauss("gauss","gaussian PDF", x , mu, sigma) ;  
  RooExponential exp( "exp" , "exponentianl PDF", x, lambda );

  //Construct signal+bkg
  RooRealVar nsig( "nsig", "#singal events", 27, 0, 1000 );
  RooRealVar nbkg( "nbkg", "#background events", 115, 0, 1000 );
  RooAddPdf model( "model", "s+b", RooArgList( gauss, exp ), RooArgList( nsig, nbkg) );
  // Construct plot frame in 'x'
  RooPlot* xframe = x.frame(Title("Gaussian p.d.f.")) ;
  
  
  // S e t u p  m o d e l  f o r  mgg
  //-----------------------------------------
  // Build signal and background pdf using, mu, sigma, and lambda
  RooGaussian Signal( "signal", "signal gaussian PDF", mgg, mu, sigma) ;  
  RooExponential Bkg( "bkg" , "bkg exponentianl PDF", mgg, lambda );
  //Construct bkg only
  
  //Construct singal+bkg
  //RooAddPdf modelMgg( "modelMgg", "Mgg s+b", RooArgList( Signal, Bkg ), RooArgList( nsig, nbkg) );
  RooAddPdf modelMgg( "modelMgg", "Mgg s+b", RooArgList( Signal, Bkg ), nsig );
  
  
  // P l o t   m o d e l   a n d   c h a n g e   p a r a m e t e r   v a l u e s
  // ---------------------------------------------------------------------------
  
  // Plot gauss in frame (i.e. in x) 
  model.plotOn(xframe) ;
  // Change the value of sigma to 1.5
  sigma.setVal( sigma_init );
  //Change the value of mu/mu to 126.1
  mu.setVal( mu_init );
  //Change the value of ambda
  lambda.setVal( lambda_init );
  
  // Plot gauss in frame (i.e. in x) and draw frame on canvas
  model.plotOn(xframe,LineColor(kRed)) ;
  
  
  // G e n e r a t e   e v e n t s 
  // -----------------------------
  
  // Generate a dataset of 1000 events in x from gauss
  RooDataSet* data = model.generate( x, 142 ) ;  
  
  // Make a second plot frame in x and draw both the 
  // data and the p.d.f in the frame
  RooPlot* xframe2 = x.frame(Title("Gaussian p.d.f. with data")) ;
  data->plotOn( xframe2, Binning( 38 ) ) ;
  model.plotOn(xframe2) ;
  

  // F i t   m o d e l   t o   d a t a
  // -----------------------------

  // Fit pdf to data
  model.fitTo(*data) ;

  // Print values of mu and sigma (that now reflect fitted values and errors)
  mu.Print() ;
  sigma.Print() ;
  
  //print lambda
  lambda.Print();
  
  double fit_mu   = mu.getVal( );
  double fit_sigma  = sigma.getVal( );
  double fit_lambda = lambda.getVal( );
  
  // Draw all frames on a canvas
  TCanvas* c = new TCanvas("rf101_basics","rf101_basics",800,400) ;
  c->Divide(2) ;
  c->cd(1) ; gPad->SetLeftMargin(0.15) ; xframe->GetYaxis()->SetTitleOffset(1.6) ; xframe->Draw() ;
  c->cd(2) ; gPad->SetLeftMargin(0.15) ; xframe2->GetYaxis()->SetTitleOffset(1.6) ; xframe2->Draw() ;
  c->SaveAs("test.pdf");
  delete c;
  
  
  //F i t  M g g M o d e l   t o   H g g   D a t a
  //----------------------------------------------
  nsig.setVal( 0.1 );
  //nbkg.setVal( 100 );
  Bkg.plotOn( frameMgg, LineColor( kDashed ) );
  modelMgg.plotOn( frameMgg, Components( Bkg ), LineStyle( kDashed ) );
  modelMgg.plotOn( frameMgg, Components( Signal ), LineColor( kRed ) );
  modelMgg.plotOn( frameMgg );
  //Bkg.fitTo( dataset );
  
  mu.setVal( fit_mu );
  sigma.setVal( fit_sigma );
  lambda.setVal( fit_lambda );
  //modelMgg.fitTo( dataset, Extended( kTRUE ) );
  modelMgg.fitTo( dataset );

  mgg.setRange( "myRange", 122.04, 128.96 ) ;
  RooAbsReal* intSignal = Signal.createIntegral( mgg, mgg, "myRange" );
  //Bkg.fitTo( dataset );
  RooAbsReal* intBkg = Bkg.createIntegral( mgg, mgg, "myRange" );
  //intSignal->Print();
  std::cout << "Int: " << 142.*nsig.getVal( )*intSignal->getVal() << std::endl;
  std::cout << "Int: " << 142.*( 1. - nsig.getVal( ) )*intBkg->getVal() << std::endl;
  
  //print mu and sigma
  mu.Print();
  sigma.Print();
  //print lambda
  lambda.Print();
  
  //Creating Canvas
  c = new TCanvas("rf101_basics","rf101_basics",800,400) ;
  c->cd(); gPad->SetLeftMargin(0.15);
  frameMgg->GetYaxis()->SetTitleOffset(1.6);
  frameMgg->GetXaxis()->SetTitle("m_{#gamma#gamma} (GeV)");
  frameMgg->Draw();
  c->SaveAs("test_mgg_susy.pdf");
  
  return;
};
