//////////////////////////////////////////////////////////////////////////
// 'BASIC FUNCTIONALITY' RooFit tutorial macro #101
// Fitting, plotting, toy data generation on one-dimensional p.d.f
// pdf = gauss(x,m,s) 
// 07/2008 - Wouter Verkerke 
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

int main()
{

  // G e t t i n g   T r e e
  //------------------------
  
  TFile* fin = new TFile("/Users/cmorgoth/Work/syn_hgg_analysis/RazorHggCat_Total.root");
  TTree* tree = (TTree*)fin->Get("HighRes");
  /*
    TFile* fin = new TFile("/Users/cmorgoth/Work/syn_hgg_analysis/DoublePhoton_22Jan2013_Run2012ABCD_v9__HighRes.root");
    TTree* tree = (TTree*)fin->Get("SusyHggTree");
  */
  // A p p l y  C u t s
  //------------------------
  TString cut = "MR>250. && t1Rsq>0.05 && pho1Pt>25. && pho2Pt>25. && (pho1Pt>40. || pho2Pt>40.) && pTGammaGamma>20.0 && fabs(pho1Eta)<1.44 && fabs(pho2Eta)<1.44 && mGammaGamma>103. && mGammaGamma<160.";
  //TString cut = "MR>400. && t1Rsq>0.05 && pho1Pt>25. && pho2Pt>25. && (pho1Pt>40. || pho2Pt>40.) && pTGammaGamma>20.0 && fabs(pho1Eta)<1.44 && fabs(pho2Eta)<1.44 && mGammaGamma>103. && mGammaGamma<160.";
  //TString cut = "MR>250. && t1Rsq>0.05 && pho1_pt>25. && pho2_pt>25. && (pho1_pt>40. || pho2_pt>40.) && pho1_pass_iso==1 && pho2_pass_iso==1 && ptgg>20. && fabs(pho1_eta)<1.44 && fabs(pho2_eta)<1.44 && mgg>103. && mgg<160.";
  TTree* t = tree->CopyTree( cut );
  
  
  // G e t t i n g  D a t a s e t
  //-----------------------------
  RooRealVar mGammaGamma( "mGammaGamma", "mGammaGamma", 103., 160. );
  RooDataSet dataset( "dataset", "dataset", RooArgSet( mGammaGamma ), Import(*t) ) ;
  dataset.Print();
  RooPlot* frameMgg = mGammaGamma.frame( Title("Mgg unbinned dataset") );
  dataset.plotOn( frameMgg, Binning( 38 ) );

  
  // S e t u p   m o d e l 
  // ---------------------
  // Declare variables x,mean,sigma with associated name, title, initial value and allowed range
  RooRealVar x( "x", "x", 103., 160. );
  RooRealVar mean( "mean","mean of gaussian", 126., 103., 160. ) ;
  RooRealVar sigma( "sigma", "width of gaussian", 1, 0.1, 10 ) ;
  RooRealVar lambda( "lambda", "exponent of exponential", -0.1, -10, 10 );
  
  // Build gaussian p.d.f in terms of x,mean and sigma
  RooGaussian gauss("gauss","gaussian PDF",x,mean,sigma) ;  
  RooExponential exp( "exp" , "exponentianl PDF", x, lambda );

  //Construct signal+bkg
  RooRealVar nsig( "nsig", "#singal events", 1, 0, 1000 );
  RooRealVar nbkg( "nbkg", "#background events", 1, 0, 1000 );
  RooAddPdf model( "model", "s+b", RooArgList( gauss, exp ), RooArgList( nsig, nbkg) );
  // Construct plot frame in 'x'
  RooPlot* xframe = x.frame(Title("Gaussian p.d.f.")) ;


  // S e t u p  m o d e l  f o r  mGammaGamma
  //-----------------------------------------
  // Build signal and background pdf using, mean, sigma, and lambda
  RooGaussian Signal( "signal", "signal gaussian PDF", mGammaGamma, mean, sigma) ;  
  RooExponential Bkg( "bkg" , "bkg exponentianl PDF", mGammaGamma, lambda );
  //Construct bkg only
  
  //Construct singal+bkg
  RooAddPdf modelMgg( "modelMgg", "Mgg s+b", RooArgList( Signal, Bkg ), RooArgList( nsig, nbkg) );
  
  
  // P l o t   m o d e l   a n d   c h a n g e   p a r a m e t e r   v a l u e s
  // ---------------------------------------------------------------------------
  
  // Plot gauss in frame (i.e. in x) 
  model.plotOn(xframe) ;

  // Change the value of sigma to 1.5
  sigma.setVal( 1.5 );
  //Change the value of mu/mean to 126.1
  mean.setVal( 126.1 );

  //Change the value of ambda
  lambda.setVal( -0.01 );

  // Plot gauss in frame (i.e. in x) and draw frame on canvas
  model.plotOn(xframe,LineColor(kRed)) ;
  

  // G e n e r a t e   e v e n t s 
  // -----------------------------

  // Generate a dataset of 1000 events in x from gauss
  RooDataSet* data = model.generate( x, 1507 ) ;  
  
  // Make a second plot frame in x and draw both the 
  // data and the p.d.f in the frame
  RooPlot* xframe2 = x.frame(Title("Gaussian p.d.f. with data")) ;
  data->plotOn( xframe2, Binning( 38 ) ) ;
  model.plotOn(xframe2) ;
  

  // F i t   m o d e l   t o   d a t a
  // -----------------------------

  // Fit pdf to data
  model.fitTo(*data) ;

  // Print values of mean and sigma (that now reflect fitted values and errors)
  mean.Print() ;
  sigma.Print() ;

  //print lambda
  lambda.Print();

  double fit_mean   = mean.getVal( );
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
  nsig.setVal( 12 );
  nbkg.setVal( 135 );
  Bkg.plotOn( frameMgg, LineColor( kDashed ) );
  modelMgg.plotOn( frameMgg, Components( Bkg ), LineStyle( kDashed ) );
  modelMgg.plotOn( frameMgg );
  Bkg.fitTo( dataset );

  mean.setVal( fit_mean );
  sigma.setVal( fit_sigma );
  lambda.setVal( fit_lambda );
  modelMgg.fitTo( dataset, Extended( kTRUE ) );

  //print mean and sigma
  mean.Print();
  sigma.Print();
  //print lambda
  lambda.Print();

  //Creating Canvas
  c = new TCanvas("rf101_basics","rf101_basics",800,400) ;
  c->cd(); gPad->SetLeftMargin(0.15);
  frameMgg->GetYaxis()->SetTitleOffset(1.6);
  frameMgg->GetXaxis()->SetTitle("m_{#gamma#gamma} (GeV)");
  frameMgg->Draw();
  c->SaveAs("test_mgg.pdf");
  
  return 0;
}
