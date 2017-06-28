//C++ INCLUDES
#include <vector>
#include <fstream>
//ROOT INCLUDES
//#include <TSYSTEM.h>
#include <TSystem.h>
#include <TTree.h>
#include <TLatex.h>
#include <TString.h>
#include <TFile.h>
#include <TH1D.h>
#include <TF1.h>
#include <TBox.h>
#include <TCanvas.h>
#include <TGraph.h>
#include <TGraphErrors.h>
#include <TRandom3.h>
#include <TLegend.h>
#include <TMath.h>
#include <TROOT.h>
#include <Math/GaussIntegrator.h>
#include <Math/IntegratorOptions.h>
//ROOFIT INCLUDES
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
//#include <RealVar.h>
//LOCAL INCLUDES
#include "RunTwoFitMgg.hh"
#include "DefinePdfs.hh"
#include "CustomPdfs.hh"

//Axis
const float axisTitleSize = 0.06;
const float axisTitleOffset = .8;

const float axisTitleSizeRatioX   = 0.18;
const float axisLabelSizeRatioX   = 0.12;
const float axisTitleOffsetRatioX = 0.84;

const float axisTitleSizeRatioY   = 0.15;
const float axisLabelSizeRatioY   = 0.108;
const float axisTitleOffsetRatioY = 0.52;

//Margins
const float leftMargin   = 0.12;
const float rightMargin  = 0.05;
const float topMargin    = 0.07;
const float bottomMargin = 0.12;

RooWorkspace* DoubleGausFit( TTree* tree, float forceSigma, bool sameMu, float forceMu, TString mggName )
{
  RooWorkspace* ws = new RooWorkspace( "ws", "" );
  RooRealVar mgg( mggName, "m_{#gamma#gamma}", 103, 160, "GeV" );
  mgg.setBins(57);
  //mgg.setRange( "signal", 110, 140. );
  mgg.setRange( "signal", 103, 160. );

  /*
  RooRealVar mgg( mggName, "m_{#gamma#gamma}", 100, 1000, "GeV" );
  mgg.setBins(180);
  mgg.setRange( "signal", 600, 850. );
  */
  
  //ws->var("dGauss_signal_gauss_Ns")->setVal( 1600 );
  
  RooDataSet data( "data", "", RooArgSet(mgg), RooFit::Import( *tree ) );
  int npoints = data.numEntries();
  //-----------------------
  //C r e a t e  doubleGaus
  //-----------------------
  TString tag;
  if( sameMu )
    {
      tag = MakeDoubleGauss( "dGauss_signal", mgg, *ws );
      ws->var("dGauss_signal_gauss_Ns")->setVal( (double)npoints );
    }
  else
    {
      tag = MakeFullDoubleGauss( "dGauss_signal", mgg, *ws );
      ws->var("dGauss_signal_DG_Ns")->setVal( (double)npoints );
    }
  
  //ws->pdf( tag )->fitTo( data, RooFit::Strategy(0), RooFit::Extended( kTRUE ), RooFit::Range("signal") );
  RooFitResult* sres = ws->pdf( tag )->fitTo( data, RooFit::Strategy(2), RooFit::Extended( kTRUE ), RooFit::Save( kTRUE ), RooFit::Range("signal") );
  
  sres->SetName( tag + "_sres" );
  ws->import( *sres );
  
  RooPlot* frame = mgg.frame();
  data.plotOn( frame );
  ws->pdf( tag )->plotOn( frame, RooFit::LineColor( kBlue ), RooFit::Range("Full"), RooFit::NormRange("Full") );
  ws->import( mgg );
  ws->import( data );
  frame->SetName( tag + "_frame" );
  ws->import( *frame );

  return ws;
};


RooWorkspace* DoubleCBFit( TTree* tree, TString mggName, float muCB, float sigmaCB )
{
  RooWorkspace* ws = new RooWorkspace( "ws", "" );
  //RooRealVar mgg( mggName, "m_{#gamma#gamma}", 103, 160, "GeV" );
  //mgg.setBins(57);
  //mgg.setRange( "signal", 103, 160. );

  RooRealVar mgg( mggName, "m_{#gamma#gamma}", 230, 6000, "GeV" );
  mgg.setBins(80);
  //mgg.setRange( "signal", muCB-50*sigmaCB, muCB+50*sigmaCB );

  RooDataSet data( "data", "", RooArgSet(mgg), RooFit::Import( *tree ) );
  int npoints = data.numEntries();

  std::cout << "===========================================" << std::endl;
  std::cout << "==============Nentries: " << npoints << "=============" << std::endl;
  std::cout << "===========================================" << std::endl;
  //---------------------------------
  //C r e a t e  Double Crystall Ball
  //---------------------------------
  TString tag = MakeDoubleCB( "Signal", mgg, *ws );
  
  ws->var( tag + "_Ns" )->setVal( (double)npoints );
  ws->var( tag + "_muCB")->setVal( muCB );
  ws->var( tag + "_sigmaCB")->setVal( 1.0*sigmaCB );
  RooPlot* frame;
  if ( muCB < 2000 )
    {
      mgg.setRange( "signal", muCB-50*sigmaCB, muCB+50*sigmaCB );
      frame = mgg.frame( muCB-50*sigmaCB, muCB+50*sigmaCB, 100 );
      ws->var( tag + "_muCB")->setVal( muCB );
      ws->var( tag + "_sigmaCB")->setVal( sigmaCB );
      ws->var( tag + "_alpha1")->setVal( 1. );
      ws->var( tag + "_alpha2")->setVal( 1.8 );
      ws->var( tag + "_n1")->setVal( 2.7 );
      ws->var( tag + "_n2")->setVal( 4.5 );
    }
  else if ( muCB < 3000 )
    {
      mgg.setRange( "signal", muCB-50*sigmaCB, muCB+50*sigmaCB );
      frame = mgg.frame( muCB-50*sigmaCB, muCB+50*sigmaCB, 200 );
      ws->var( tag + "_muCB")->setVal( muCB );
      ws->var( tag + "_sigmaCB")->setVal( sigmaCB );
      ws->var( tag + "_alpha1")->setVal( 0.9 );
      ws->var( tag + "_alpha2")->setVal( 2.0 );
      ws->var( tag + "_n1")->setVal( 3.2 );
      ws->var( tag + "_n2")->setVal( 4.4 );
    }
  else if ( muCB < 4500 )
    {
      mgg.setRange( "signal", muCB-50*sigmaCB, muCB+50*sigmaCB );
      frame = mgg.frame( muCB-50*sigmaCB, muCB+50*sigmaCB, 100 );
      ws->var( tag + "_muCB")->setVal( 0.99*muCB );
      ws->var( tag + "_sigmaCB")->setVal( sigmaCB );
      ws->var( tag + "_alpha1")->setVal( 1.1 );
      ws->var( tag + "_alpha2")->setVal( 2.0 );
      ws->var( tag + "_n1")->setVal( 3.7 );
      ws->var( tag + "_n2")->setVal( 5.0 );
    }
  else if ( muCB < 5000. )
    {
      mgg.setRange( "signal", muCB-8*sigmaCB, muCB+8*sigmaCB );
      frame = mgg.frame( muCB-8*sigmaCB, muCB+8*sigmaCB, 100 );
      ws->var( tag + "_muCB")->setVal( 0.988*muCB );
      ws->var( tag + "_sigmaCB")->setVal( sigmaCB );
      ws->var( tag + "_alpha1")->setVal( 1.3 );
      ws->var( tag + "_alpha2")->setVal( 1.8 );
      ws->var( tag + "_n1")->setVal( 1.5 );
      ws->var( tag + "_n2")->setVal( 2.8 );
    }
  else
    {
      mgg.setRange( "signal", muCB-6*sigmaCB, muCB+3*sigmaCB );
      frame = mgg.frame( muCB-6*sigmaCB, muCB+3*sigmaCB, 100 );
      ws->var( tag + "_muCB")->setVal( 0.988*muCB );
      ws->var( tag + "_sigmaCB")->setVal( sigmaCB );
      ws->var( tag + "_alpha1")->setVal( 0.6 );
      ws->var( tag + "_alpha2")->setVal( 1.6 );
      ws->var( tag + "_n1")->setVal( 1.0 );
      ws->var( tag + "_n2")->setVal( 2.8 );
    }

  
  RooFitResult* sres = ws->pdf( tag )->fitTo( data, RooFit::Strategy(2), RooFit::Extended( kTRUE ), RooFit::Save( kTRUE ), RooFit::Range("signal") );
  sres->SetName( "SignalFitResult" );
  ws->import( *sres );
  
  
  //RooPlot* frame = mgg.frame( muCB-5*sigmaCB, muCB+5*sigmaCB, 100 );
  data.plotOn( frame );
  ws->pdf( tag )->plotOn( frame, RooFit::LineColor( kBlue ), RooFit::Range("signal"), RooFit::NormRange("signal") );
  ws->import( mgg );
  ws->import( data );
  frame->SetName( "SignalFitPlot" );
  ws->import( *frame );

  //TString tag2 = MakeDoubleCBInterpolateNE( "SignalInterpol", mgg, *ws );
  
  return ws;
};


RooWorkspace* DoubleCBFitHggRazor( TTree* tree, TString mggName, float muCB, float sigmaCB )
{
  RooWorkspace* ws = new RooWorkspace( "ws", "" );
  RooRealVar mgg( mggName, "m_{#gamma#gamma}", 103, 160, "GeV" );
  mgg.setBins(57);
  mgg.setRange( "signal", 103, 160. );

  RooDataSet data( "data", "", RooArgSet(mgg), RooFit::Import( *tree ) );
  int npoints = data.numEntries();

  //---------------------------------
  //C r e a t e  Double Crystall Ball
  //---------------------------------
  TString tag = MakeDoubleCB( "Signal", mgg, *ws );
  
  ws->var( tag + "_Ns" )->setVal( (double)npoints );
  ws->var( tag + "_muCB")->setVal( muCB );
  ws->var( tag + "_sigmaCB")->setVal( 1.0*sigmaCB );
  RooPlot* frame = mgg.frame( muCB-50*sigmaCB, muCB+50*sigmaCB, 100 );
  ws->var( tag + "_alpha1")->setVal( 1.5296 );
  ws->var( tag + "_alpha2")->setVal( 3.5 );
  ws->var( tag + "_n1")->setVal( 4.8 );
  ws->var( tag + "_n2")->setVal( 0.48 );
  
  RooFitResult* sres = ws->pdf( tag )->fitTo( data, RooFit::Strategy(2), RooFit::Extended( kTRUE ), RooFit::Save( kTRUE ), RooFit::Range("signal") );
  sres->SetName( "SignalFitResult" );
  ws->import( *sres );
  
  data.plotOn( frame );
  ws->pdf( tag )->plotOn( frame, RooFit::LineColor( kBlue ), RooFit::Range("signal"), RooFit::NormRange("signal") );
  ws->import( mgg );
  ws->import( data );
  frame->SetName( "SignalFitPlot" );
  ws->import( *frame );

  
  return ws;
};

RooWorkspace* MakeSideBandFit( TTree* tree, float forceSigma, bool constrainMu, float forceMu, TString mggName )
{
  RooWorkspace* ws = new RooWorkspace( "ws", "" );
  
  RooRealVar mgg(mggName,"m_{#gamma#gamma}",103,160,"GeV");
  mgg.setBins(57);
  mgg.setRange("low", 103, 121);
  mgg.setRange("high", 129, 160);
  mgg.setRange("signal", 103, 160);
  
  RooRealVar w( "xsecSF", "w", 0, 10000 );

  //TString tag3 = MakeDoubleExp( "sideband_fit", mgg, *ws );
  TString tag3 = MakeDoubleExpN1N2( "sideband_fit", mgg, *ws ); 
  
  //RooDataSet data( "data", "", RooArgSet(mgg, w), RooFit::WeightVar(w), RooFit::Import(*tree) );
  //Sideband Fit
  RooDataSet data( "data", "", RooArgSet(mgg), RooFit::Import(*tree) );
  ws->pdf( tag3 )->fitTo( data, RooFit::Strategy(0), RooFit::Extended(kTRUE), RooFit::Range("low,high") );
  RooFitResult* bres = ws->pdf( tag3 )->fitTo( data, RooFit::Strategy(2), RooFit::Extended(kTRUE), RooFit::Save(kTRUE), RooFit::Range("low,high") );
  //Full Fit
  //ws->pdf( tag3 )->fitTo( data, RooFit::Strategy(0), RooFit::Extended(kTRUE), RooFit::Range("Full") );
  //RooFitResult* bres = ws->pdf( tag3 )->fitTo( data, RooFit::Strategy(2), RooFit::Save(kTRUE), RooFit::Extended(kTRUE), RooFit::Range("Full") );

  mgg.setRange("sregion", 121, 129);
  RooAbsReal* sint = ws->pdf( tag3 )->createIntegral( mgg, RooFit::NormSet(mgg), RooFit::Range("sregion") ) ; 
  RooAbsReal* Nfit = ws->pdf( tag3 )->createIntegral( mgg, RooFit::Range("Full") ) ;
  std::cout << sint->getVal() << std::endl;
  float N_sideband = data.sumEntries(Form("(mgg>%0.2f && mgg <121) || (mgg>129 && mgg<%0.2f)",103.,160.));
  /*
  double n1 = ws->var("sideband_fitNbkg1")->getVal();
  double n2 = ws->var("sideband_fitNbkg2")->getVal();
  double Nbkg = n1*n1 + n2*n2; 

  std::cout << "-----------------------------------" << std::endl;
  std::cout << "Ntotal: " << data.sumEntries( ) << std::endl;
  std::cout << "Nfit: " << Nfit->getVal() << std::endl;
  std::cout << "Nbkg: " << Nbkg << std::endl;
  std::cout << "sf: "  << Nbkg*sint->getVal()/N_sideband << std::endl;
  std::cout << "-----------------------------------" << std::endl;
  */
  bres->SetName( tag3 + "_b_fitres" );
  ws->import( *bres );

  RooPlot *fmgg = mgg.frame();
  data.plotOn(fmgg);
  ws->pdf( tag3 )->plotOn(fmgg,RooFit::LineColor(kRed),RooFit::Range("Full"),RooFit::NormRange("Full"));
  ws->pdf( tag3 )->plotOn(fmgg,RooFit::LineColor(kBlue), RooFit::LineStyle(kDashed), RooFit::Range("low,high"),RooFit::NormRange("low,high"));
  //ws->pdf( tag3 )->plotOn(fmgg,RooFit::LineColor(kBlue), RooFit::LineStyle(kDashed), RooFit::Range("low,high"),RooFit::NormRange("Full"));
  fmgg->SetName( tag3 + "_frame" );
  ws->import( *fmgg );

  RooPlot* pdfFrame = mgg.frame();
  ws->pdf( tag3 )->plotOn( pdfFrame, RooFit::LineColor(kViolet), RooFit::Range("Full"), RooFit::NormRange("Full") );
  pdfFrame->SetName( tag3+"_pdfframe" );
  ws->import( *pdfFrame );
  ws->import( mgg );
  return ws;
};

void MakePlot( TTree* tree,  RooWorkspace& w, TString pdfName, TString mggName )
{
  RooRealVar mgg(mggName,"m_{#gamma#gamma}",100,400,"GeV");
  mgg.setBins(30);
  mgg.setRange("low", 103, 121);
  mgg.setRange("high", 129, 160);
  
  mgg.setRange("low_v2", 100, 121);
  mgg.setRange("high_v2", 129, 400);
  
  mgg.setRange("signal", 103, 160);
  mgg.setRange("sig", 121., 129.);

  TString tag3 = MakeDoubleExpN1N2( "sideband_fit_v2", mgg, w );
  RooDataSet data( "data", "", RooArgSet(mgg), RooFit::Import(*tree) );
  //fullFit
  //w.pdf( tag3 )->fitTo( data, RooFit::Strategy(0), RooFit::Extended(kTRUE), RooFit::Range("Full") );
  //RooFitResult* bres = w.pdf( tag3 )->fitTo( data, RooFit::Strategy(2), RooFit::Save(kTRUE), RooFit::Extended(kTRUE), RooFit::Range("Full") );
  //sidebandFit
  w.pdf( tag3 )->fitTo( data, RooFit::Strategy(0), RooFit::Extended(kTRUE), RooFit::Range("low_v2,high_v2") );
  RooFitResult* bres = w.pdf( tag3 )->fitTo( data, RooFit::Strategy(2), RooFit::Save(kTRUE), RooFit::Extended(kTRUE), RooFit::Range("low_v2,high_v2") );
  
  RooPlot *fmgg = mgg.frame();
  data.plotOn(fmgg);
  //w.pdf( pdfName )->plotOn( fmgg, RooFit::LineColor(kBlue), RooFit::Range("low,high"), RooFit::NormRange("low,high") );
  
  //w.pdf( pdfName )->plotOn( fmgg, RooFit::LineColor(kBlue), RooFit::LineStyle(kDashed), RooFit::Range("Full"), RooFit::NormRange("low_v2,high_v2") );
  w.pdf( pdfName )->plotOn( fmgg, RooFit::LineColor(kGreen), RooFit::Range("Full"), RooFit::NormRange("low,high") );
  //w.pdf( tag3 )->plotOn( fmgg, RooFit::LineColor(kRed), RooFit::Range("Full"), RooFit::NormRange("low_v2,high_v2") );
  fmgg->SetName( "pdf_goldenbin_test" );
  w.import( *fmgg );
  
  return;
};


double GetIntegral( RooWorkspace& w, TString pdfName, TString mggName )
{
  RooAbsPdf* NewModel = w.pdf( pdfName );
  RooRealVar* mgg = w.var( mggName );
  mgg->setRange("sig", 121, 129);
  //mgg->setRange("sig", 103.0, 160.);
  RooAbsReal* fIntegral = NewModel->createIntegral(*mgg);
  RooAbsReal* fIntegral2 = NewModel->createIntegral(*mgg, RooFit::NormSet(*mgg), RooFit::Range("sig") );
  std::cout << "test Int: " << fIntegral->getVal() << std::endl;
  std::cout << "test Int2: " << fIntegral2->getVal() << std::endl;
  mgg->setMax(400);
  mgg->setMin(100);
  mgg->setRange("sig", 129, 400);
  fIntegral2 = NewModel->createIntegral(*mgg, RooFit::NormSet(*mgg), RooFit::Range("sig") );
  std::cout << "test Int2': " << fIntegral2->getVal() << std::endl;
  return fIntegral2->getVal();
};

RooWorkspace* MakeSignalBkgFit( TTree* treeData, TTree* treeSignal, TTree* treeSMH, TString mggName, bool isHighMass, TString name )
{
  //------------------------------------------------
  // C r e a t e   s i g n a l  s h a p e from TTree
  //------------------------------------------------
  //TFile* ftmp = new TFile("tmp_output_OurID.root", "recreate");
  RooWorkspace* ws = new RooWorkspace( "ws", "" );
  RooRealVar mgg( mggName, "m_{#gamma#gamma}", 0, 10000, "GeV" );
  if ( isHighMass )
    {
      //mgg = RooRealVar( mggName, "m_{#gamma#gamma}", 230, 1230, "GeV" );//HighMass
      mgg.SetNameTitle( mggName, "m_{#gamma#gamma}" );
      mgg.setMin( 230. );
      mgg.setMax( 1230. );
      mgg.setUnit( "GeV" );
      mgg.setBins(200);
      mgg.setRange( "signal", 500., 1000. );
      mgg.setRange( "full", 230., 1230. );
      mgg.setRange( "high", 850., 1230.);
      mgg.setRange( "low", 230., 650.);
    }
  else
    {
      mgg.SetNameTitle( mggName, "m_{#gamma#gamma}" );
      mgg.setMin( 103. );
      mgg.setMax( 160. );
      mgg.setUnit( "GeV" );
      mgg.setBins(57);
      mgg.setRange( "signal", 115, 129. );
      mgg.setRange( "high", 129., 160. );
      mgg.setRange( "low", 103., 121. );
      mgg.setRange( "full", 103., 160. );
      mgg.setRange( "Full", 103., 160. );
    }

  //--------------------------------
  //I m p or t i n g   D a t a
  //--------------------------------

  //Getting signal shape from signal MC
  //-----------------------
  //C r e a t e  doubleGaus
  //-----------------------
  bool sameMu = false;
  TString tagSignal, tagSignal2, tagSMH;
  TString tag;
  RooDataSet data( "data", "", RooArgSet(mgg), RooFit::Import(*treeData) );
  RooDataSet dataSignal( "dataSignal", "", RooArgSet(mgg), RooFit::Import(*treeSignal) );
  RooDataSet dataSMH( "dataSMH", "", RooArgSet(mgg), RooFit::Import(*treeSMH) );
  //---------------------------------
  //D e f i n e   s i g n a l   P D F
  //---------------------------------
  int npoints = dataSignal.numEntries();
  if( sameMu )
    {
      tagSignal = MakeDoubleGauss( "dGauss_signal", mgg, *ws );
      ws->var("dGauss_signal_gauss_Ns")->setVal( (double)npoints );
      if ( isHighMass ) ws->var("dGauss_signal_gauss_mu")->setVal(750);
    }
  else
    {
      tagSignal = MakeFullDoubleGauss( "dGauss_signal", mgg, *ws );
      tagSignal2 = MakeDoubleCB( "DCB_signal", mgg, *ws );
      ws->var("DCB_signal_DCB_Ns")->setVal( (double)npoints );
      if ( isHighMass )
	{
	  ws->var("dGauss_signal_DG_mu1")->setVal( 750 );
	  ws->var("dGauss_signal_DG_mu2")->setVal( 750 );
	  ws->var("DCB_signal_DCB_muCB")->setVal( 750 );
	  ws->var("DCB_signal_DCB_sigmaCB")->setVal( 20 );
	}
    }

  RooFitResult* sres = ws->pdf( tagSignal2 )->fitTo( dataSignal, RooFit::Strategy(2), RooFit::Extended( kTRUE ), RooFit::Save( kTRUE ), RooFit::Range("signal") );
  double gausFrac   =  ws->var("dGauss_signal_DG_frac")->getVal();
  double gausMu1    =  ws->var("dGauss_signal_DG_mu1")->getVal();
  double gausMu2    =  ws->var("dGauss_signal_DG_mu2")->getVal();
  double gausSigma1 =  ws->var("dGauss_signal_DG_sigma1")->getVal();
  double gausSigma2 =  ws->var("dGauss_signal_DG_sigma2")->getVal();

  double cbMu    =  ws->var("DCB_signal_DCB_muCB")->getVal();
  double cbSigma =  ws->var("DCB_signal_DCB_sigmaCB")->getVal();
  double cbN1    =  ws->var("DCB_signal_DCB_n1")->getVal();
  double cbN2    =  ws->var("DCB_signal_DCB_n2")->getVal();
  double cbA1    =  ws->var("DCB_signal_DCB_alpha1")->getVal();
  double cbA2    =  ws->var("DCB_signal_DCB_alpha2")->getVal();

  //Saving Signal Fit
  sres->SetName("SignalFitResult");
  ws->import( *sres );

  std::cout << "[DEBUG]: SIGNAL PLOTTING" << std::endl;
  //-----------------------------
  //S i g n a l   p l o t t i n g
  //-----------------------------
  RooPlot *fmgg2;
  if ( isHighMass ) fmgg2 = mgg.frame( 450, 1050, 120);
  //else fmgg2 = mgg.frame( 103, 160, 38);
  else fmgg2 = mgg.frame( 103, 160, 57);
  dataSignal.plotOn( fmgg2, RooFit::Range("signal") );
  ws->pdf( tagSignal2 )->plotOn( fmgg2, RooFit::LineColor(kRed), RooFit::Range("signal"), RooFit::NormRange("signal"));
  //ws->pdf( tagSignal )->plotOn(fmgg2, RooFit::LineColor(kBlue), RooFit::LineStyle(kDashed), RooFit::Range("low,high"),RooFit::NormRange("low,high"));
  fmgg2->SetName( "signalFitPlot" );
  ws->import( *fmgg2 );
  //return ws;
  //-------------------------------------
  //D e f i n e   S M - H i g g s   P D F
  //-------------------------------------
  npoints = dataSMH.numEntries();
  if( sameMu )
    {
      tagSMH = MakeDoubleGauss( "dGauss_SMH", mgg, *ws );
      ws->var("dGauss_SMH_gauss_Ns")->setVal( (double)npoints );
      if ( isHighMass ) ws->var("dGauss_SMH_gauss_mu")->setVal( 750 );
    }
  else
    {
      tagSMH = MakeFullDoubleGauss( "dGauss_SMH", mgg, *ws );
      ws->var("dGauss_SMH_DG_Ns")->setVal( (double)npoints );
      if ( isHighMass )
	{
	  ws->var("dGauss_SMH_DG_mu1")->setVal( 750 );
	  ws->var("dGauss_SMH_DG_mu2")->setVal( 750 );
	}
    }
  //RooFitResult* smhres = ws->pdf( tagSMH )->fitTo( dataSMH, RooFit::Strategy(2), RooFit::Extended( kTRUE ), RooFit::Save( kTRUE ), RooFit::Range("full") );
  double gausFrac_SMH   =  ws->var("dGauss_SMH_DG_frac")->getVal();
  double gausMu1_SMH    =  ws->var("dGauss_SMH_DG_mu1")->getVal();
  double gausMu2_SMH    =  ws->var("dGauss_SMH_DG_mu2")->getVal();
  double gausSigma1_SMH =  ws->var("dGauss_SMH_DG_sigma1")->getVal();
  double gausSigma2_SMH =  ws->var("dGauss_SMH_DG_sigma2")->getVal();
  
  //------------------------------------
  // C r e a t e   b k g  s h a p e
  //------------------------------------
  
  TString tag_bkg = MakeSingleExp( "fullsb_fit_singleExp", mgg, *ws );
  TString tag_bkg_hm;
  RooFitResult* bres = ws->pdf( tag_bkg )->fitTo( data, RooFit::Strategy(2), RooFit::Extended(kTRUE), RooFit::Save(kTRUE), RooFit::Range("Full") );
  npoints     = ws->var("fullsb_fit_singleExp_Nbkg")->getVal();
  float exp_a = ws->var("fullsb_fit_singleExp_a")->getVal();

  //high mass parameter to obtain after fit
  float hm_a, hm_b;
  
  if ( isHighMass )
    {
      tag_bkg_hm = MakeHMDiphoton( "ext_DHM_pdf", mgg, *ws );
      RooFitResult* bresHM = ws->pdf( tag_bkg_hm )->fitTo( data, RooFit::Strategy(2), RooFit::Extended(kTRUE), RooFit::Save(kTRUE), RooFit::Range("low,high") );
      hm_a = ws->var("ext_DHM_pdf_a")->getVal();
      hm_b = ws->var("ext_DHM_pdf_b")->getVal();
      bresHM->SetName("FitResultHM");
      ws->import( *bresHM );
      RooPlot* hmPlot = mgg.frame( 230, 1230, 50 );
      data.plotOn( hmPlot );
      ws->pdf( tag_bkg_hm )->plotOn( hmPlot, RooFit::NormRange("full"), RooFit::Range("full"), RooFit::LineColor( kRed ) );
      hmPlot->SetName("FitPlotHM");
      ws->import( *hmPlot );
    }
  //creating blinded dataset
  //RooDataSet* data_toys  = GenerateToys( ws->pdf( tag_bkg ), mgg, npoints);
  //RooDataSet* data_toys  = ws->pdf( tag_bkg )->generate(mgg, npoints, kFALSE, kTRUE, "", kTRUE, kFALSE);
  RooAbsData* data_toys = ws->pdf( tag_bkg )->generateBinned( mgg, npoints, RooFit::ExpectedData() );
  
  data_toys->SetName("data_toys");
  
  //---------------------------
  //bkg_pdf for composite model
  //---------------------------
  TString tag_bkg2 = MakeSingleExpNE( "BkgModelExp", mgg, *ws );
  ws->var("BkgModelExp_sExp_a")->setVal( exp_a );
  //HighMass Function
  TString tag_bkg3 = MakeHMDiphotonNE( "BkgModelHM", mgg, *ws );
  ws->var( tag_bkg3+"_a" )->setVal( hm_a );
  ws->var( tag_bkg3+"_b" )->setVal( hm_b );

  std::cout << "[DEBUG]: BEFORE HMD BKG" << std::endl;
  //-----------------------------------------
  //Define double gaussian for signal and SMH
  //-----------------------------------------
  TString tag_signal2 = MakeFullDoubleGaussNE( "DG_Signal", mgg, *ws );
  ws->var("DG_Signal_DG_frac")->setVal( gausFrac );
  ws->var("DG_Signal_DG_mu1")->setVal( gausMu1 );
  ws->var("DG_Signal_DG_mu2")->setVal( gausMu2 );
  ws->var("DG_Signal_DG_sigma1")->setVal( gausSigma1 );
  ws->var("DG_Signal_DG_sigma2")->setVal( gausSigma2 );
  //fix signal shape parameters
  ws->var("DG_Signal_DG_frac")->setConstant(kTRUE);
  ws->var("DG_Signal_DG_mu1")->setConstant(kTRUE);
  ws->var("DG_Signal_DG_mu2")->setConstant(kTRUE);
  ws->var("DG_Signal_DG_sigma1")->setConstant(kTRUE);
  ws->var("DG_Signal_DG_sigma2")->setConstant(kTRUE);

  std::cout << "[DEBUG]: PASS HMD BKG" << std::endl;
  
  TString tag_sg      = MakeSingleGaussNE( "Signal", mgg, *ws );
  ws->var("Signal_SG_mu")->setVal( gausMu1 );
  ws->var("Signal_SG_sigma")->setVal( gausSigma2 );
  //ws->var("Signal_SG_mu")->setConstant( kTRUE );
  ws->var("Signal_SG_sigma")->setConstant( kTRUE );
  
  TString tag_sDCB    = MakeDoubleCBNE( "smodel", mgg, *ws );
  //Signal DoubleCB
  ws->var("smodel_DCB_muCB")->setVal( cbMu );
  ws->var("smodel_DCB_sigmaCB")->setVal( cbSigma );
  ws->var("smodel_DCB_n1")->setVal( cbN1 );
  ws->var("smodel_DCB_n2")->setVal( cbN2 );
  ws->var("smodel_DCB_alpha1")->setVal( cbA1 );
  ws->var("smodel_DCB_alpha2")->setVal( cbA2 );
  //ws->var("smodel_DCB_muCB")->setConstant(kTRUE);
  ws->var("smodel_DCB_sigmaCB")->setConstant(kTRUE);
  ws->var("smodel_DCB_n1")->setConstant(kTRUE);
  ws->var("smodel_DCB_n2")->setConstant(kTRUE);
  ws->var("smodel_DCB_alpha1")->setConstant(kTRUE);
  ws->var("smodel_DCB_alpha2")->setConstant(kTRUE);
  std::cout << "pass doubleCB setup" << std::endl;

  TString tag_SMH2    = MakeFullDoubleGaussNE( "DG_SMH", mgg, *ws );
  ws->var("DG_SMH_DG_frac")->setVal( gausFrac_SMH );
  ws->var("DG_SMH_DG_mu1")->setVal( gausMu1_SMH );
  ws->var("DG_SMH_DG_mu2")->setVal( gausMu2_SMH );
  ws->var("DG_SMH_DG_sigma1")->setVal( gausSigma1_SMH );
  ws->var("DG_SMH_DG_sigma2")->setVal( gausSigma2_SMH );
  //fix SM-Higgs shape parameters
  ws->var("DG_SMH_DG_frac")->setConstant(kTRUE);
  ws->var("DG_SMH_DG_mu1")->setConstant(kTRUE);
  ws->var("DG_SMH_DG_mu2")->setConstant(kTRUE);
  ws->var("DG_SMH_DG_sigma1")->setConstant(kTRUE);
  ws->var("DG_SMH_DG_sigma2")->setConstant(kTRUE);
  
  std::cout << "creating s+b model" << std::endl;
  //---------------
  //S+B  m  o d e l
  //---------------
  //falling background + SM-Higgs + Signal
  //RooAddPdf* model = new RooAddPdf( "model", "model", RooArgList( *ws->pdf( tag_signal2 ), *ws->pdf( tag_SMH2 ), *ws->pdf( tag_bkg2 ) ) ) ;
  //RooAddPdf* model = new RooAddPdf( "model", "model", RooArgSet( *ws->pdf( tag_signal2 ), *ws->pdf( tag_bkg2 ) ) ) ;
  //RooAddPdf* model = new RooAddPdf( "model", "model", RooArgSet( *ws->pdf( tag_bkg2 ), *ws->pdf( tag_sg ) ) ) ;
  RooRealVar NbkgModel("NbkgModel","", npoints);
  NbkgModel.setConstant( kFALSE );

  RooRealVar NsModel("NsModel","",0.0);
  NsModel.setConstant( kFALSE );
  NsModel.setRange(-10, 1000.);

  //---------------------
  //Create s+b model
  //---------------------
  RooAddPdf* model = new RooAddPdf( "model", "model", RooArgSet( *ws->pdf( tag_bkg2 ), *ws->pdf( tag_sDCB ) ), RooArgSet(NbkgModel, NsModel) ) ;

  
  if ( isHighMass )
    {
      RooAddPdf* modelHM = new RooAddPdf( "modelHM", "modelHM", RooArgSet( *ws->pdf( tag_bkg3 ), *ws->pdf( tag_sDCB ) ), RooArgSet(NbkgModel, NsModel) ) ;
      RooFitResult* sbresHM = modelHM->fitTo( data, RooFit::Strategy(2), RooFit::Extended(kTRUE), RooFit::Save(kTRUE), RooFit::Range("full") );
      RooPlot* sbPlotHM = mgg.frame( 230., 1230., 50 );
      data.plotOn( sbPlotHM );
      modelHM->plotOn( sbPlotHM, RooFit::Components( *ws->pdf( tag_bkg3) ), RooFit::Range("full"), RooFit::NormRange("full"),
		       RooFit::LineColor( kBlue ), RooFit::LineStyle( kDashed ) );
      /*modelHM->plotOn( sbPlotHM, RooFit::Components( *ws->pdf( tag_sDCB) ), RooFit::Range("full"), RooFit::NormRange("full"),
	RooFit::LineColor( kRed ), RooFit::LineStyle( kDashed ) );*/
      modelHM->plotOn( sbPlotHM, RooFit::Range("full"), RooFit::NormRange("full"), RooFit::LineColor( kRed ) );
      
      sbPlotHM->SetName( "sbFitPlotHM" );
      sbresHM->SetName( "sbFitResultHM" );
      ws->import( *sbresHM );
      ws->import( *sbPlotHM );
    }
  
  std::cout << "entering constraints" << std::endl;
  //--------------------------------------
  //H i g g s   C o n s t r a i n s
  //--------------------------------------
  RooRealVar HiggsYield("HiggsYield","",0.5);
  RooRealVar HiggsYieldUn("HiggsYieldUn","",0.1);
  //RooGaussian SMH_Constraint("SMH_Constraint", "SMH_Constraint", *ws->var("DG_SMH_DGF_Ns"), RooFit::RooConst(0.1), RooFit::RooConst(0.01) );
  //RooGaussian SMH_Constraint("SMH_Constraint", "SMH_Constraint", *ws->var("DG_SMH_DG_Ns"), HiggsYield, HiggsYieldUn );
  RooRealVar BkgYield ("BkgYield","", npoints);
  RooRealVar BkgYieldUn("BkgYieldUn","", 0.1*sqrt(npoints));
  //RooGaussian Bkg_Constraint("Bkg_Constraint", "Bkg_Constraint", *ws->var("BkgModel_singleExp_Nbkg"), BkgYield, BkgYieldUn );

  //---------------------------
  //SMH mass constraint
  //---------------------------
  //RooRealVar HiggsMass("HiggsMass","", ws->var("Signal_SG_mu")->getVal());
  RooRealVar HiggsMass("HiggsMass","", ws->var("smodel_DCB_muCB")->getVal() );
  RooRealVar HiggsMassUn("HiggsMassUn","", 0.01*ws->var("smodel_DCB_muCB")->getVal() );//1% scale uncertainty
  std::cout << "[INFO]: MC measured mass is:  " << HiggsMass.getVal() << " +/- " << HiggsMassUn.getVal() << std::endl;
  RooGaussian HiggsMass_Constraint("SMH_Constraint", "SMH_Constraint",  *ws->var("smodel_DCB_muCB"), HiggsMass, HiggsMassUn );
  std::cout << "pass constraints" << std::endl;
  std::cout << "pass forceSigma" << std::endl;

  //---------------------
  //F i t   t o   D a t a
  //---------------------
  //RooFitResult* sbres = model->fitTo( data, RooFit::Strategy(2), RooFit::Extended(kTRUE), RooFit::Save(kTRUE), RooFit::ExternalConstraints(SMH_Constraint) ,RooFit::Range("low,high") );

  TH1F* h_1 = new TH1F("h_1", "h_1", 100, 0, 10);
  RooFitResult* sbres;
  //sbres = model->fitTo( *data_toys, RooFit::Strategy(2), RooFit::Extended(kTRUE), RooFit::Save(kTRUE), RooFit::Range("full") );
  //sbres = model->fitTo( data, RooFit::Strategy(2), RooFit::Extended(kTRUE), RooFit::Save(kTRUE), RooFit::Range("full") );
  sbres = model->fitTo( data, RooFit::Strategy(2), RooFit::Extended(kTRUE), RooFit::Save(kTRUE), RooFit::ExternalConstraints(HiggsMass_Constraint) ,RooFit::Range("full") );
  
  
  for (int i = 0; i < 100; i++ )
    {
      //ws->var("Signal_SG_Ns")->setConstant( kFALSE );
      //ws->var("Signal_SG_Ns")->setVal( 0 + 0.1*i );
      //ws->var("Signal_SG_Ns")->setConstant( kTRUE );
      //sbres = model->fitTo( *data_toys, RooFit::Strategy(2), RooFit::Extended(kTRUE), RooFit::Save(kTRUE), RooFit::Range("Full") );
      //h_1->Fill(0 + 0.1*i, sbres->minNll());
    }
  //RooFitResult* sbres = model->fitTo( data, RooFit::Strategy(2), RooFit::Extended(kTRUE), RooFit::Save(kTRUE), RooFit::Range("Full") );
  //RooFitResult* sbres = model->fitTo( data, RooFit::Strategy(2), RooFit::Extended(kTRUE), RooFit::Save(kTRUE), RooFit::ExternalConstraints(Bkg_Constraint),RooFit::Range("Full") );
  //Initialize fit parameter statuses
  int _status     = -1;
  int _status2    = -1;
  int _status3    = -1;
  int _covStatus  = -1;
  int _covStatus2 = -1;
  int _covStatus3 = -1;
  
  //--------------------------------------
  //Defining Negative Log Likelihood (NLL)
  //--------------------------------------
  //RooNLLVar* nll = (RooNLLVar*)model->createNLL( data, RooFit::Extended(kTRUE), RooFit::Range("Full") );
  //Defininf RooMinimizer Object;
  //RooMinimizer m(*nll);
  //m.setStrategy(2);
  //m.setPrintLevel(3);
  //m.minimize("Minuit2", "Migrad");
  
  //m.migrad(); 
  //RooFitResult* r = m.save(); 
  //_status    = r->status();
  //_covStatus = r->covQual();
  
  //m.hesse();
  //m.minimize("Minuit2", "Hesse");
  //RooFitResult* r2 = m.save(); 
  //_status2    = r2->status();
  //_covStatus2 = r2->covQual();

  //m.setMinimizerType("Minuit2");
  //m.migrad();
  //m.hesse();
  //m.minos();
  //m.minimize("Minuit2", "Minos");
  //RooFitResult* r3 = m.save(); 
  //_status3    = r3->status();
  //_covStatus3 = r3->covQual();
  
  //------------------------------
  //E n d  M i n i m i z a t i o n
  //------------------------------
  
  sbres->SetName("sbFitResult");
  ws->import( *sbres );

  //r->SetName("sb_fit_result_M2_migrad");
  //r2->SetName("sb_fit_result_M2_hesse");
  //r3->SetName("sb_fit_result_M2_minos");
  //
  //ws->import( *r );
  //ws->import( *r2 );
  //ws->import( *r3 );

  //---------------------------
  //Getting signal estimation
  //---------------------------
  float sVal = NsModel.getVal();
  float sErr = NsModel.getError();
  //-----------------------------
  //S + B   p l o t t i n g
  //-----------------------------
  TCanvas* c = new TCanvas( "c", "c", 2119, 33, 800, 700 );
  c->SetHighLightColor(2);
  c->SetFillColor(0);
  c->SetBorderMode(0);
  c->SetBorderSize(2);
  c->SetLeftMargin( leftMargin );
  c->SetRightMargin( rightMargin );
  c->SetTopMargin( topMargin );
  c->SetBottomMargin( bottomMargin );
  c->SetFrameBorderMode(0);
  c->SetFrameBorderMode(0);
  //create frame
  RooPlot *fmgg;
  if ( isHighMass ) fmgg = mgg.frame( 230, 1230, 50);
  //else fmgg = mgg.frame( 103, 160, 38);
  else fmgg = mgg.frame( 103, 160, 57 );
    
  data.plotOn(fmgg);
  model->plotOn( fmgg, RooFit::LineStyle(kDashed), RooFit::LineColor(kRed), RooFit::Range("Full"), RooFit::NormRange("Full"), RooFit::Components(tag_bkg2) );
  model->plotOn( fmgg, RooFit::LineColor(kBlue), RooFit::Range("Full"), RooFit::NormRange("Full"));
  fmgg->SetName( "sb_fit_frame" );
  ws->import( *fmgg );

  float maxC = fmgg->GetMaximum();
  fmgg->GetXaxis()->SetTitleSize( axisTitleSize );
  fmgg->GetXaxis()->SetTitleOffset( axisTitleOffset );
  fmgg->GetYaxis()->SetTitleSize( axisTitleSize );
  fmgg->GetYaxis()->SetTitleOffset( axisTitleOffset );
  //fmgg->SetAxisRange(0.1, maxC, "Y");
  fmgg->Draw();
  
  c->Update();
  fmgg->SetTitle("");
  /*
  TBox* box = new TBox(120, 0.105, 135, maxC-0.1);
  box->SetFillColor(kRed-9);
  box->SetFillStyle(3344);
  box->Draw("same");
  */
  TString signalYield = Form("N_{s} = %.2f #pm %.2f", sVal, sErr );
  TLatex latex;
  latex.SetNDC();
  latex.SetTextAngle(0);
  latex.SetTextColor(kBlack);    
  latex.SetTextFont(42);
  latex.SetTextAlign(31); 
  latex.SetTextSize(0.05);    
  latex.DrawLatex( 0.89, 0.87, signalYield );
  latex.Draw();
  c->SaveAs( name + ".pdf" );
  c->SaveAs( name + ".png" );
  
  //---------------------------------
  //S M - H i g g s   p l o t t i n g
  //---------------------------------
  RooPlot *fmgg3 = mgg.frame();
  dataSMH.plotOn(fmgg3);
  //ws->pdf( tagSMH )->plotOn(fmgg3, RooFit::LineColor(kRed), RooFit::Range("Full"), RooFit::NormRange("Full"));
  //ws->pdf( tagSMH )->plotOn(fmgg3, RooFit::LineColor(kBlue), RooFit::LineStyle(kDashed), RooFit::Range("low,high"),RooFit::NormRange("low,high"));
  fmgg3->SetName( "smh_fit_frame" );
  ws->import( *fmgg3 );
  

  //-------------------------------------
  //P r o f i l e d   L i k e l i h o o d 
  //-------------------------------------
  /*
    profile in Ns to obtain significance.
  */
  //RooArgSet poi   = RooArgSet( *ws->var("DG_Signal_DG_Ns") );
  //RooArgSet poi   = RooArgSet( *ws->var("Signal_SG_Ns") );
  RooArgSet poi   = RooArgSet( NsModel );
  //RooAbsReal* nll = model->createNLL( *data_toys, RooFit::Extended(kTRUE) );
  //RooAbsReal* nll = model->createNLL( data, RooFit::Extended(kTRUE) );
  RooAbsReal* nll = model->createNLL( data);
  RooFormulaVar n2ll = RooFormulaVar("n2ll", "2*@0", RooArgList(*nll) );
  RooAbsReal* p2ll = n2ll.createProfile( poi );
  //--------------------------------------
  // l i k e l i h o o d   p l o t t i n g
  //--------------------------------------
  
  //RooPlot* fns = ws->var("DG_Signal_DG_Ns")->frame( RooFit::Range(0, 30, true) );
  //RooPlot* fns = ws->var("Signal_SG_Ns")->frame( RooFit::Range(-10, 10, true) );
  //RooPlot* fns = NsModel.frame( RooFit::Range(-10, 10, true) );
  RooPlot* fns = NsModel.frame( RooFit::Range(sVal-2.*sErr, sVal+2.*sErr, true) );
  //RooPlot* fns = ws->var("DG_Signal_DG_Ns")->frame( RooFit::Range( sVal-5.*sErr, sVal+5.*sErr, true) );
  fns->SetMinimum(0);
  fns->SetMaximum(12);
  n2ll.plotOn( fns, RooFit::ShiftToZero(), RooFit::LineColor(kBlue) );
  fns->SetMinimum(0);
  fns->SetMaximum(12);
  p2ll->plotOn( fns, RooFit::LineColor(kBlack) );
  fns->SetName("nll");
  ws->import( *fns );
  
  //ws->Write("w_sb");
  //h_1->Write("h_1");
  //ftmp->Close();
  return ws;
}

void MakeDataCardHMD( TTree* treeData, TString mggName, float Signal_Yield, std::string Signal_CF, float mass, TString binNumber, TString category, TString year )
{
  std::cout << "====================================================================" << std::endl;
  std::cout << "entering datacard: " << Signal_Yield << " Year: " << year << std::endl;
  std::cout << "====================================================================" << std::endl;

  std::stringstream ss_signal;
  ss_signal << Signal_CF;
  float tmp;
  std::vector<float> signal_sys;
  //------------------------------
  //Signal systematics into vector
  //------------------------------
  while ( ss_signal.good() )
    {
      ss_signal >> tmp;
      signal_sys.push_back( 1.0 + tmp );
      //std::cout << "tmp: " << tmp << std::endl;
      if ( ss_signal.eof() ) break;
    }

  
  //------------------------------------------------
  // Define Workspace and create variables
  //------------------------------------------------
  TString combinedRootFileName = Form("HggRazorWorkspace_m%.0f_tmp.root", mass);
  TFile* ftmp = new TFile( combinedRootFileName, "recreate");
  RooWorkspace* ws = new RooWorkspace( "ws", "" );

  bool isEBEB = false;
  
  if ( isEBEB ) mggName = "mGammaGamma_EBEB";
  else mggName = "mGammaGamma_EBEE";

  //RooRealVar mgg( mggName, "m_{#gamma#gamma}", 230, 6000, "GeV" );//EBEBE
  RooRealVar mgg( mggName, "m_{#gamma#gamma}", 330, 6000, "GeV" );//EBEE

  
  mgg.setUnit( "GeV" );
  //mgg.setRange( "signal", 600., 900. );
  //mgg.setRange( "high", 850., 10000.);
  //mgg.setRange( "low", 230., 650.);//EBEB

  if ( isEBEB )
    {
      //mgg.setBins(39080);//230-6000
      //mgg.setRange( "full", 230., 10000. );//EBEB
      

      mgg.setBins(23080);//230-6000
      //mgg.setBins(288);//only for visual fits
      mgg.setRange( "full", 230., 6000. );//EBEB
    }
  else
    {
      //mgg.setBins(38680);
      //mgg.setRange( "full", 330., 10000. );//EBEE
      mgg.setBins(22680);
      mgg.setRange( "full", 330., 6000. );//EBEE
    }
      
  //----------------
  //Retreive dataset
  //----------------
  treeData->GetBranch("mGammaGamma")->SetName( mggName );
  RooDataSet data( "data", "", RooArgSet(mgg), RooFit::Import(*treeData) );
  //ws->import(mgg, RooFit::RenameVariable( "mGammaGamma", "mgg") );
  //mgg.SetName("mGammaGamma_EBEE");
  
  //------------------------------------
  // C r e a t e   b k g  s h a p e
  //------------------------------------
  TString tag_bkg;
  
  //Initializing Nbkg
  int npoints = data.numEntries();
  //set Nbkg Initial Value
  
  //---------------------
  //F i t   t o   D a t a
  //---------------------
  float sExp_a;
  float Nbkg;
  float NbkgUn;
  float BkgNormUn;
  //HighMassDiphoton
  float hmd_a;
  float hmd_b;
  RooFitResult* bres;
  tag_bkg = MakeHMDiphoton( "Bkg_fit_HMDiphoton", mgg, *ws );
  ws->var(tag_bkg+"_Nbkg")->setVal( npoints );
  ws->var(tag_bkg+"_a")->setVal( 0.03 );
  ws->var(tag_bkg+"_b")->setVal( -0.403 );
  //ws->var(tag_bkg+"_a")->setVal( 1.490177 );
  //ws->var(tag_bkg+"_b")->setVal( -0.4817967 );
 
  bres = ws->pdf( tag_bkg )->fitTo( data, RooFit::Strategy(2), RooFit::Extended(kTRUE), RooFit::Save(kTRUE), RooFit::Range("full") );

  bres->SetName("BkgOnlyFitResult");
  hmd_a = ws->var( tag_bkg+"_a")->getVal();
  hmd_b = ws->var( tag_bkg+"_b")->getVal();
  Nbkg   = ws->var( tag_bkg+"_Nbkg")->getVal();
  NbkgUn = ws->var( tag_bkg+"_Nbkg")->getError();
  
  RooAbsData* data_toys = ws->pdf( tag_bkg )->generateBinned( mgg, npoints, RooFit::ExpectedData() );
  //--------------------------------
  // m o d e l   1   p l o t t i n g
  //--------------------------------
  RooPlot *fmgg;
  if ( isEBEB ) fmgg = mgg.frame(230, 1630, 70);//EBEB
  else fmgg = mgg.frame(230, 1630, 70);//EBEE
  
  data.plotOn(fmgg);
  ws->pdf( tag_bkg )->plotOn(fmgg,RooFit::LineColor(kRed),RooFit::Range("full"),RooFit::NormRange("full"));
  fmgg->SetName( "BkgOnlyFitPlot" );
  ws->import( *bres );
  ws->import( *fmgg );
  ws->import( data );

  float SignaYieldOriginal = Signal_Yield;//2.69(1/fb)*10fb
  float effSF_EBEB = 0.9627*0.9627;
  float effSF_EBEE = 0.9627*0.9352;

  for ( int i = 0; i < 1501; i++ )
    {
      float _mass = 500. + (float)2*i;
      if ( isEBEB )
	{
	  if ( year == "2015" ) Signal_Yield = SignaYieldOriginal*( 2.44392e-01+(3.40500e-04)*_mass-(1.42193e-07)*pow(_mass,2)+(3.08615e-11)*pow(_mass,3)-(2.75671e-15)*pow(_mass,4) );
	  else if ( year == "2016" ) Signal_Yield = SignaYieldOriginal*effSF_EBEB*( 2.52927e-01+(3.26565e-04)*_mass-(1.34127e-07)*pow(_mass,2)+(2.86419e-11)*pow(_mass,3)-(2.52305e-15)*pow(_mass,4) );
	  else 
	    {
	      std::cerr <<  "year: " << year << "not defined, could not find eff*acc; TERMINATING!!" << std::endl;
	      exit (EXIT_FAILURE);
	    }
	}
      else
	{
	  if ( year == "2015" ) Signal_Yield = SignaYieldOriginal*( 1.61828e-01+(6.99351e-05)*_mass-(9.55028e-08)*pow(_mass,2)+(2.92184e-11)*pow(_mass,3)-(2.82880e-15)*pow(_mass,4) );
	  else if ( year == "2016" ) Signal_Yield = SignaYieldOriginal*effSF_EBEE*( 1.64433e-01+(5.87817e-05)*_mass-(8.72622e-08)*pow(_mass,2)+(2.69219e-11)*pow(_mass,3)-(2.60707e-15)*pow(_mass,4) );
	  else 
	    {
	      std::cerr <<  "year: " << year << "not defined, could not find eff*acc; TERMINATING!!" << std::endl;
	      exit (EXIT_FAILURE);
	    }
	}
      
      TString combineRootFile;
      if ( isEBEB ) combineRootFile = Form("HggRazorWorkspace_EBEB_m%0.f.root", _mass);
      else combineRootFile = Form("HggRazorWorkspace_EBEE_m%0.f.root", _mass);
      TFile* _fout = new TFile( combineRootFile, "RECREATE" );
      //-------------------------------------------------------
      // P r e p a r a t i o n   t o   C o m b i n e  I n p u t
      //-------------------------------------------------------
      RooWorkspace* combine_ws = new RooWorkspace( "combine_ws", "" );
      //------------
      //Signal Model
      //------------
      TString tagSignalInterpol;
      if ( category == "inclusive" )
	{
	  if ( isEBEB )
	    {
	      if ( year == "2015" ) tagSignalInterpol = MakeDoubleCBInterpolateNE( Form("SignalInterpol_EBEB_m%.0f", _mass) , mgg, *combine_ws, "EBEB" );
	      else if ( year == "2016" ) tagSignalInterpol = MakeDoubleCBInterpolateNE2016( Form("SignalInterpol_EBEB_m%.0f", _mass) , mgg, *combine_ws, "EBEB" );
	      else 
		{
		  std::cerr <<  "year: " << year << "not defined, could not find appropiate signal mode; TERMINATING!!" << std::endl;
		  exit (EXIT_FAILURE);
		}
	    }
	  else
	    {
	      if ( year == "2015" ) tagSignalInterpol = MakeDoubleCBInterpolateNE( Form("SignalInterpol_EBEE_m%.0f", _mass) , mgg, *combine_ws, "EBEE" );
	      else if ( year == "2016" ) tagSignalInterpol = MakeDoubleCBInterpolateNE2016( Form("SignalInterpol_EBEE_m%.0f", _mass) , mgg, *combine_ws, "EBEE" );
	      else 
		{
		  std::cerr <<  "year: " << year << "not defined, could not find appropiate signal mode; TERMINATING!!" << std::endl;
		  exit (EXIT_FAILURE);
		}
	    }
	  combine_ws->var( tagSignalInterpol+"_mass" )->setVal( _mass );
	  combine_ws->var( tagSignalInterpol+"_mass" )->setConstant(kTRUE);
	  RooRealVar SignalInterpol_norm( tagSignalInterpol + "_norm", "", Signal_Yield );
	  combine_ws->import( SignalInterpol_norm );
	}
      else
	{
	  std::cerr << "category: " <<  category << " NOT DEFINED for HM Analysis, terminating" << std::endl;
	  exit (EXIT_FAILURE);
	}

      
      //--------------------
      //GetFWHM
      //--------------------
      RooRealVar* mymass     = new RooRealVar( "my_f_mass", "#mass_{CB}", _mass, "" );
      mymass->setConstant( kTRUE );
      
      double fwhm;
      if ( isEBEB )
	{
	  if ( year == "2015" ) 
	    {
	      RooIntepolateDSCB_W0p014_Spin0_EBEB* myCB = new RooIntepolateDSCB_W0p014_Spin0_EBEB( "dummy" , "", mgg, *mymass );
	      TF1* myTF1  = myCB->asTF( RooArgList(mgg), RooArgList( *mymass ) );
	      double maxY = myTF1->GetMaximum();
	      double maxX = myTF1->GetMaximumX();
	      double _low = myTF1->GetX( 0.5*maxY , 0, maxX );
	      double _high = myTF1->GetX( 0.5*maxY , maxX, 6000 );
	      fwhm = _high - _low;
	    }
	  else if ( year == "2016" )
	    {
	      RooIntepolateDSCB_W0p014_Spin0_EBEB_2016* myCB2 = new RooIntepolateDSCB_W0p014_Spin0_EBEB_2016( "dummy" , "", mgg, *mymass );
	      TF1* myTF1  = myCB2->asTF( RooArgList(mgg), RooArgList( *mymass ) );
	      double maxY = myTF1->GetMaximum();
	      double maxX = myTF1->GetMaximumX();
	      double _low = myTF1->GetX( 0.5*maxY , 0, maxX );
	      double _high = myTF1->GetX( 0.5*maxY , maxX, 6000 );
	      fwhm = _high - _low;
	    }
	  else 
	    {
	      std::cerr <<  "year: " << year << "not defined, could not find appropiate signal mode; TERMINATING!!" << std::endl;
	      exit (EXIT_FAILURE);
	    }
	  
	}
      else
	{
	  if ( year == "2015" )
	    {
	      RooIntepolateDSCB_W0p014_Spin0_EBEE* myCB3 = new RooIntepolateDSCB_W0p014_Spin0_EBEE( "dummy" , "", mgg, *mymass );
	      TF1* myTF1  = myCB3->asTF( RooArgList(mgg), RooArgList( *mymass ) );
	      double maxY = myTF1->GetMaximum();
	      double maxX = myTF1->GetMaximumX();
	      double _low = myTF1->GetX( 0.5*maxY , 0, maxX );
	      double _high = myTF1->GetX( 0.5*maxY , maxX, 6000 );
	      fwhm = _high - _low;
	    }
	  else if ( year == "2016" )
	    {
	      RooIntepolateDSCB_W0p014_Spin0_EBEE_2016* myCB4 = new RooIntepolateDSCB_W0p014_Spin0_EBEE_2016( "dummy" , "", mgg, *mymass );
	      TF1* myTF1  = myCB4->asTF( RooArgList(mgg), RooArgList( *mymass ) );
	      double maxY = myTF1->GetMaximum();
	      double maxX = myTF1->GetMaximumX();
	      double _low = myTF1->GetX( 0.5*maxY , 0, maxX );
	      double _high = myTF1->GetX( 0.5*maxY , maxX, 6000 );
	      fwhm = _high - _low;
	    }
	  else 
	    {
	      std::cerr <<  "year: " << year << "not defined, could not find appropiate signal mode; TERMINATING!!" << std::endl;
	      exit (EXIT_FAILURE);
	    }
	 
	}

      std::cout << "----> " << _mass << " " << fwhm << std::endl;
      RooRealVar* _fwhm     = new RooRealVar( "FWHM", "FWHM", fwhm, "" );
      combine_ws->import( *_fwhm );
      //---------
      //Bkg model
      //---------
      TString combineBkg;
      if ( isEBEB ) combineBkg = MakeHMDiphotonNE( Form("Bkg_EBEB_m%.0f", _mass), mgg, *combine_ws );
      else combineBkg = MakeHMDiphotonNE( Form("Bkg_EBEE_m%.0f", _mass), mgg, *combine_ws );
      
      combine_ws->var( combineBkg + "_a" )->setVal( hmd_a );
      combine_ws->var( combineBkg + "_b" )->setVal( hmd_b );
      RooRealVar Bkg_norm(  combineBkg + "_norm", "", Nbkg );
      Bkg_norm.setConstant(kFALSE);
      combine_ws->import( Bkg_norm );

      TString copyBkgName;
      if ( isEBEB ) copyBkgName = "biasTermBkg_EBEB";
      else copyBkgName = "biasTermBkg_EBEE";
      RooAbsPdf* copyBkg    = (RooAbsPdf*)combine_ws->pdf( combineBkg )->clone( copyBkgName );
      combine_ws->import( *copyBkg );
     
      TString copySignalName;
      if ( isEBEB ) copySignalName = "biasTermSignal_EBEB";
      else copySignalName = "biasTermSignal_EBEE";
      RooAbsPdf* copySignal = (RooAbsPdf*)combine_ws->pdf( tagSignalInterpol )->clone( copySignalName );
      combine_ws->import( *copySignal );

      RooRealVar Nbeta( "Nbeta", "", Signal_Yield );
      combine_ws->import( Nbeta );
      
      if ( isEBEB )
	{
	  RooRealVar theta( "theta_EBEB", "", 0, -5, 5);
	  combine_ws->import( theta );
	}
      else
	{
	  RooRealVar theta( "theta_EBEE", "", 0, -5, 5);
	  combine_ws->import( theta );  
	}
      
      
      TString dataName;
      if( isEBEB ) dataName = Form("data_EBEB_m%0.f", _mass);
      else dataName = Form("data_EBEE_m%0.f", _mass);
      
      data.SetName( dataName );
      combine_ws->import( data );


      //ws->renameSet("mGammaGamma", "mGammaGamma_EBEE");
      ws->Write("w_sb");
      
      combine_ws->Write("combineWS");
      _fout->Close();
      
      TString dataCardName;
      if ( isEBEB ) dataCardName = Form("HggRazorCard_EBEB_m%.0f.txt", _mass);
      else dataCardName = Form("HggRazorCard_EBEE_m%.0f.txt", _mass);
      
      std::ofstream ofs( dataCardName , std::ofstream::out );
      TString det;
      if ( isEBEB ) det = "EBEB";
      else det = "EBEE";

      bool _bias = true;
      
      if ( !_bias )
	{
	  ofs << "imax 1 number of bins\njmax 1 number of processes minus 1\nkmax * number of nuisance parameters\n";
	  ofs << "----------------------------------------------------------------------------------------\n";
	  ofs << "shapes Bkg\t\tbin"      << binNumber << "\t" << combineRootFile << " combineWS:" << combineBkg << "\n";
	  ofs << "shapes signal\t\tbin"   << binNumber << "\t" << combineRootFile << " combineWS:" << tagSignalInterpol << "\n";
	  ofs << "shapes data_obs\t\tbin" << binNumber << "\t" << combineRootFile << " combineWS:" << dataName << "\n";
	  ofs << "----------------------------------------------------------------------------------------\n";
	  ofs << "bin\t\tbin" << binNumber << "\n";
	  ofs << "observation\t-1.0\n";
	  ofs << "----------------------------------------------------------------------------------------\n";
	  ofs << "bin\t\t\t\t\t\tbin" << binNumber << "\t\tbin" << binNumber << "\n";
	  ofs << "process\t\t\t\t\t\tsignal\t\tBkg\n";
	  ofs << "process\t\t\t\t\t\t0\t\t1\n";
	  ofs << "rate\t\t\t\t\t\t1\t\t1\n";
	  ofs << "----------------------------------------------------------------------------------------\n";
	  ofs << "CMS_Lumi\t\t\tlnN\t\t1.062\t\t-\n";
	  ofs << "Photon_Trigger_" << det << "\t\t\tlnN\t\t1.08\t\t-\n";
	  ofs << "PdfNorm_" << det << "\t\t\t\tlnN\t\t1.06\t\t-\n";
	  int totalSys = signal_sys.size();
	  ofs << "mu_Global_" << det << "\t\t\tparam\t\t 0 " <<  _mass*0.01 <<  "\n";
	}
      else
	{
	  double biasYield;
	  if ( isEBEB )
	    {
	      if ( year == "2015" ) biasYield = ( 0.06*pow( _mass/600. , -4.0 ) + 1e-6)*fwhm*SignaYieldOriginal/3.0;//2015
	      else if ( year == "2016" ) biasYield = pow( _mass, 2.2-0.4*TMath::Log(_mass) )*fwhm*SignaYieldOriginal/10.;//2016
	      else
		{
		  std::cerr <<  "year: " << year << "not defined, could not find BIAS TERM; TERMINATING!!" << std::endl;
		  exit (EXIT_FAILURE);
		}
	    }
	  else
	    {
	      if ( year == "2015" ) biasYield = 0.1*pow( _mass/600. , -5.0 )*fwhm*SignaYieldOriginal/3.0;//2015
	      else if ( year == "2016" ) biasYield = ( 0.10*pow(_mass/600.,-5.0 ) + 2e-5 )*fwhm*SignaYieldOriginal/10.;//2016
	      else
		{
		  std::cerr <<  "year: " << year << "not defined, could not find BIAS TERM; TERMINATING!!" << std::endl;
		  exit (EXIT_FAILURE);
		}
	    }
	  std::cout << "----------" << Signal_Yield << " " << " " << biasYield << " " << fwhm <<  std::endl;

	  /*ofs << "imax 1 number of bins\njmax 3 number of processes minus 1\nkmax * number of nuisance parameters\n";
	  ofs << "----------------------------------------------------------------------------------------\n";
	  ofs << "shapes Bkg\t\tbin"          << binNumber << "\t" << combineRootFile << " combineWS:" << combineBkg << "\n";
	  ofs << "shapes biasSignal\tbin"   << binNumber << "\t" << combineRootFile << " combineWS:"   << copySignalName << "\n";
	  ofs << "shapes biasBkg\t\tbin"      << binNumber << "\t" << combineRootFile << " combineWS:" << copyBkgName << "\n";
	  ofs << "shapes signal\t\tbin"       << binNumber << "\t" << combineRootFile << " combineWS:" << tagSignalInterpol << "\n";
	  ofs << "shapes data_obs\t\tbin"     << binNumber << "\t" << combineRootFile << " combineWS:" << dataName << "\n";
	  ofs << "----------------------------------------------------------------------------------------\n";
	  ofs << "bin\t\tbin" << binNumber << "\n";
	  ofs << "observation\t-1.0\n";
	  ofs << "----------------------------------------------------------------------------------------\n";
	  ofs << "bin\t\t\t\tbin" << binNumber << "\t\tbin" << binNumber << "\t\tbin" << binNumber << "\t\tbin" << binNumber << "\n";
	  ofs << "process\t\t\t\tsignal\t\tBkg\t\tbiasSignal\tbiasBkg\n";
	  ofs << "process\t\t\t\t0\t\t1\t\t2\t\t3\n";
	  ofs << "rate\t\t\t\t1\t\t1\t\t1\t\t1\n";
	  ofs << "----------------------------------------------------------------------------------------\n";
	  ofs << "CMS_Lumi\t\tlnN\t1.027\t\t-\t\t-\t\t-\n";
	  ofs << "Photon_Trigger_" << det << "\tlnN\t1.10\t\t-\t\t-\t\t-\n";
	  ofs << "PdfNorm_" << det << "\t\tlnN\t1.06\t\t-\t\t-\t\t-\n";
	  int totalSys = signal_sys.size();
	  ofs << "mu_Global_" << det << "\t\tparam\t\t 0 " <<  _mass*0.01 <<  "\n";
	  ofs << "theta_" << det << "\t\tparam\t\t 0 1\n";
	  ofs << "SignalNbias_" << det <<"\trateParam bin0 biasSignal (@0*" << biasYield <<") theta_" << det << "\n";
	  ofs << "BkgNbias_"    << det <<"\t\trateParam bin0 biasBkg (@0*-" << biasYield <<") theta_" << det << "\n";
	  */
	  ofs << "imax 1 number of bins\njmax 2 number of processes minus 1\nkmax * number of nuisance parameters\n";
	  ofs << "----------------------------------------------------------------------------------------\n";
	  ofs << "shapes Bkg\t\tbin"          << binNumber << "\t" << combineRootFile << " combineWS:" << combineBkg << "\n";
	  ofs << "shapes biasSignal\tbin"   << binNumber << "\t" << combineRootFile << " combineWS:"   << copySignalName << "\n";
	  ofs << "shapes signal\t\tbin"       << binNumber << "\t" << combineRootFile << " combineWS:" << tagSignalInterpol << "\n";
	  ofs << "shapes data_obs\t\tbin"     << binNumber << "\t" << combineRootFile << " combineWS:" << dataName << "\n";
	  ofs << "----------------------------------------------------------------------------------------\n";
	  ofs << "bin\t\tbin" << binNumber << "\n";
	  ofs << "observation\t-1.0\n";
	  ofs << "----------------------------------------------------------------------------------------\n";
	  ofs << "bin\t\t\t\tbin" << binNumber << "\t\tbin" << binNumber << "\t\tbin" << binNumber << "\n";
	  ofs << "process\t\t\t\tsignal\t\tBkg\t\tbiasSignal\n";
	  ofs << "process\t\t\t\t0\t\t1\t\t2\n";
	  ofs << "rate\t\t\t\t1\t\t1\t\t1\n";
	  ofs << "----------------------------------------------------------------------------------------\n";
	  ofs << "CMS_Lumi\t\tlnN\t1.057\t\t-\t\t-\n";
	  ofs << "Photon_Trigger_Eff" << "\tlnN\t1.08\t\t-\t\t-\n";
	  ofs << "PdfNorm" << "\t\t\tlnN\t1.06\t\t-\t\t-\n";
	  int totalSys = signal_sys.size();
	  ofs << "mu_Global_" << det << "\t\tparam\t\t 0 " <<  _mass*0.01 <<  "\n";
	  ofs << "theta_" << det << "\t\tparam\t\t 0 1\n";
	  ofs << "SignalNbias_" << det <<"\trateParam bin biasSignal (@0*" << biasYield <<") theta_" << det << "\n";
	}
      ofs.close();
      //ws->Write();
    }
  return;
};

RooWorkspace* MakeDataCard( TTree* treeData, TTree* treeSignal, TTree* treeSMH, TString mggName, float SMH_Yield, std::string SMH_CF,
			    float Signal_Yield, std::string Signal_CF, TString binNumber, TString category, bool isHighMass,
			    TString sModel, TString f1, bool _signalOnly )
{
  std::cout << "entering datacard: " << SMH_Yield << " " << Signal_Yield << std::endl;
  std::stringstream ss_smh, ss_signal;
  ss_smh << SMH_CF;
  ss_signal << Signal_CF;
  float tmp;
  std::vector<float> smh_sys, signal_sys;
  //---------------------------
  //SMH systematics into vector
  //---------------------------
  while ( ss_smh.good() )
    {
      ss_smh >> tmp;
      smh_sys.push_back( 1.0 + tmp );
      //std::cout << "tmp: " << tmp << std::endl;
      if ( ss_smh.eof() ) break;
    }
  //------------------------------
  //Signal systematics into vector
  //------------------------------
  while ( ss_signal.good() )
    {
      ss_signal >> tmp;
      signal_sys.push_back( 1.0 + tmp );
      //std::cout << "tmp: " << tmp << std::endl;
      if ( ss_signal.eof() ) break;
    }
  
  //------------------------------------------------
  // C r e a t e   s i g n a l  s h a p e from TTree
  //------------------------------------------------
  system ("mkdir -p HggRazorDataCards/" + sModel );
  TString combinedRootFileName = "HggRazorDataCards/" + sModel + "/HggRazorWorkspace_bin" + binNumber + ".root";
  TFile* ftmp = new TFile( combinedRootFileName, "recreate");
  
  RooWorkspace* ws = new RooWorkspace( "ws", "" );
  mggName = mggName + "_bin" + binNumber;
  RooRealVar mgg( mggName, "m_{#gamma#gamma}", 103, 160, "GeV" );
  //mgg.SetNameTitle( mggName, "m_{#gamma#gamma}" );
  mgg.setMin( 103. );
  mgg.setMax( 160. );
  mgg.setUnit( "GeV" );
  mgg.setBins(57);
  mgg.setRange( "signal", 115, 129. );
  mgg.setRange( "high", 129., 160. );
  mgg.setRange( "low", 103., 121. );
  mgg.setRange( "full", 103., 160. );
  mgg.setRange( "Full", 103., 160. );
  
  //--------------------------------
  //I m p or t i n g   D a t a
  //--------------------------------

  //Getting signal shape from signal MC
  //-----------------------
  //C r e a t e  doubleGaus
  //-----------------------
  bool sameMu = false;
  TString tagSignal, tagSignalInterpol, tagSMH;
  TString tag;
  treeData->GetBranch("mGammaGamma")->SetName( mggName );
  RooDataSet data( "data", "", RooArgSet(mgg), RooFit::Import(*treeData) );
  treeSignal->GetBranch("mGammaGamma")->SetName( mggName );
  RooDataSet dataSignal( "dataSignal", "", RooArgSet(mgg), RooFit::Import(*treeSignal) );
  treeSMH->GetBranch("mGammaGamma")->SetName( mggName );
  RooDataSet dataSMH( "dataSMH", "", RooArgSet(mgg), RooFit::Import(*treeSMH) );
  //---------------------------------
  //D e f i n e   s i g n a l   P D F
  //---------------------------------
  int npoints = dataSignal.numEntries();
  int npoints_signal = dataSignal.numEntries();
  if( sameMu )
    {
      tagSignal = MakeDoubleGauss( "DG_signal", mgg, *ws );
      ws->var("DG_signal_gauss_Ns")->setVal( (double)npoints );
    }
  else
    {
      //tagSignal = MakeFullDoubleGauss( "DG_signal_bin"+binNumber , mgg, *ws );
      //ws->var(tagSignal+"_Ns")->setVal( (double)npoints );

      tagSignal = MakeDoubleCB( "DCB_Signal_bin"+ binNumber, mgg, *ws );
      ws->var(tagSignal+"_Ns")->setVal( (double)npoints );
      //--------------------------
      //Setting initial parameters
      //--------------------------
      ws->var(tagSignal+"_muCB")->setVal( 125.0 );
      ws->var(tagSignal+"_sigmaCB")->setVal( 1.2 );
      ws->var(tagSignal+"_alpha1")->setVal( 1.6 );
      ws->var(tagSignal+"_n1")->setVal( 2.9 );
      ws->var(tagSignal+"_alpha2")->setVal( 1.9 );
      ws->var(tagSignal+"_n2")->setVal( 3.2 );
      if ( binNumber.Atof() == 8 ) ws->var(tagSignal+"_n2")->setVal( 1.8 );
      if ( binNumber.Atof() >= 14 )
	{
	  ws->var(tagSignal+"_sigmaCB")->setVal( 2 );
	  ws->var(tagSignal+"_alpha1")->setVal( 0.9 );
	  ws->var(tagSignal+"_n1")->setVal( 2.2 );
	  ws->var(tagSignal+"_alpha2")->setVal( 1.95 );
	  ws->var(tagSignal+"_n2")->setVal( 2.1 );
	}
      
    }

  std::cout << tagSignal << std::endl;
  RooFitResult* sres = ws->pdf( tagSignal )->fitTo( dataSignal, RooFit::Strategy(2), RooFit::Extended( kTRUE ), RooFit::Save( kTRUE ), RooFit::Range("full") );
  sres->SetName("SignalFitResult");
  ws->import( *sres );
  
  double DCB_mu_s    = ws->var(tagSignal+"_muCB")->getVal( );
  double DCB_sigma_s = ws->var(tagSignal+"_sigmaCB")->getVal( );
  double DCB_a1_s    = ws->var(tagSignal+"_alpha1")->getVal( );
  double DCB_n1_s    = ws->var(tagSignal+"_n1")->getVal( );
  double DCB_a2_s    = ws->var(tagSignal+"_alpha2")->getVal( );
  double DCB_n2_s    = ws->var(tagSignal+"_n2")->getVal( );
  //-------------------------------------
  //D e f i n e   S M - H i g g s   P D F
  //-------------------------------------
  npoints = dataSMH.numEntries();
  if( sameMu )
    {
      tagSMH = MakeDoubleGauss( "DG_SMH", mgg, *ws );
      ws->var("DG_SMH_gauss_Ns")->setVal( (double)npoints );
    }
  else
    {
      //tagSMH = MakeFullDoubleGauss( "DG_SMH_bin"+binNumber, mgg, *ws );
      //ws->var(tagSMH+"_Ns")->setVal( (double)npoints );
      tagSMH = MakeDoubleCB( "DCB_SMH_bin"+ binNumber, mgg, *ws );
      ws->var(tagSMH+"_Ns")->setVal( (double)npoints );
      //--------------------------
      //Setting initial parameters
      //--------------------------
      ws->var(tagSMH+"_muCB")->setVal( 125.0 );
      ws->var(tagSMH+"_sigmaCB")->setVal( 1.22 );
      ws->var(tagSMH+"_alpha1")->setVal( 1.3 );
      ws->var(tagSMH+"_n1")->setVal( 4.4 );
      ws->var(tagSMH+"_alpha2")->setVal( 1.9 );
      //ws->var(tagSMH+"_n2")->setVal( 4.8 );
      ws->var(tagSMH+"_n2")->setVal( 2.8 );
      if ( binNumber.Atof() >= 14 )
	{
	  ws->var(tagSMH+"_sigmaCB")->setVal( 2 );
	  ws->var(tagSMH+"_alpha1")->setVal( 0.9 );
	  ws->var(tagSMH+"_n1")->setVal( 2.2 );
	  ws->var(tagSMH+"_alpha2")->setVal( 1.95 );
	  ws->var(tagSMH+"_n2")->setVal( 2.1 );
	}
    }
  
  RooFitResult* smhres  = ws->pdf( tagSMH )->fitTo( dataSMH, RooFit::Strategy(2), RooFit::Extended( kTRUE ), RooFit::Save( kTRUE ), RooFit::Range("full") );
  smhres->SetName("SMHFitResult");
  ws->import( *smhres );
  /*
  //double gaussian relic
  double gausFrac_SMH   =  ws->var(tagSMH+"_frac")->getVal();
  double gausMu1_SMH    =  ws->var(tagSMH+"_mu1")->getVal();
  double gausMu2_SMH    =  ws->var(tagSMH+"_mu2")->getVal();
  double gausSigma1_SMH =  ws->var(tagSMH+"_sigma1")->getVal();
  double gausSigma2_SMH =  ws->var(tagSMH+"_sigma2")->getVal();
  */
  double DCB_mu_smh    = ws->var(tagSMH+"_muCB")->getVal( );
  double DCB_sigma_smh = ws->var(tagSMH+"_sigmaCB")->getVal( );
  double DCB_a1_smh    = ws->var(tagSMH+"_alpha1")->getVal( );
  double DCB_n1_smh    = ws->var(tagSMH+"_n1")->getVal( );
  double DCB_a2_smh    = ws->var(tagSMH+"_alpha2")->getVal( );
  double DCB_n2_smh    = ws->var(tagSMH+"_n2")->getVal( );

  
  npoints = data.numEntries();
  //set Nbkg Initial Value
  std::cout << "entering constraints" << std::endl;
  //--------------------------------------
  //H i g g s   C o n s t r a i n s
  //--------------------------------------
  RooRealVar HiggsYield("HiggsYield","", SMH_Yield);
  //RooRealVar HiggsYieldUn("HiggsYieldUn","",SMH_YieldUn);
  //float SMH_NormUn = SMH_YieldUn/SMH_Yield;
  //RooGaussian SMH_Constraint("SMH_Constraint", "SMH_Constraint", *ws->var("DG_SMH_DGF_Ns"), RooFit::RooConst(0.1), RooFit::RooConst(0.01) );
  //RooGaussian SMH_Constraint("SMH_Constraint", "SMH_Constraint", *ws->var(tagSMH+"_Ns"), HiggsYield, HiggsYieldUn );
  std::cout << "pass constraints" << std::endl;
  std::cout << "pass forceSigma" << std::endl;

  //---------------------
  //F i t   t o   D a t a
  //---------------------
  float sExp_a;
  float Nbkg;
  float NbkgUn;
  float BkgNormUn;
  //HighMassDiphoton
  float hmd_a;
  float hmd_b;
  RooFitResult* bres;

  
  //------------------------------------
  // C r e a t e   b k g  s h a p e
  //------------------------------------
  TString tag_bkg;
  if ( f1 == "doubleExp" )
    {
      tag_bkg = MakeDoubleExp( f1 + "_fullsb_fit", mgg, *ws );
    }
  else if ( f1 == "singleExp" )
    {
      tag_bkg = MakeSingleExp( f1 + "_fullsb_fit", mgg, *ws );
    }
  else if ( f1 == "modExp" )
    {
      tag_bkg = MakeModExp( f1 + "_fullsb_fit", mgg, *ws );
    }
  else if ( f1 == "singlePow" )
    {
      tag_bkg = MakeSinglePow( f1 + "_fullsb_fit", mgg, *ws );
    }
  else if ( f1 == "doublePow" )
    {
      tag_bkg = MakeDoublePow( f1 + "_fullsb_fit", mgg, *ws );
    }
  else if ( f1 == "poly2" )
    {
      tag_bkg = MakePoly2( f1 + "_fullsb_fit", mgg, *ws );
    }
  else if ( f1 == "poly3" )
    {
      tag_bkg = MakePoly3( f1 + "_fullsb_fit", mgg, *ws );
    }
  else if ( f1 == "poly4" )
    {
      tag_bkg = MakePoly4( f1 + "_fullsb_fit", mgg, *ws );
    }
  else
    {
      std::cout << "[ERROR]: fit option not recognized. QUITTING PROGRAM" << std::endl;
      exit (EXIT_FAILURE);
    }
  std::cout << "[INFO]: f1 is a " << f1 << std::endl;

  //Original SingleExp
  //tag_bkg = MakeSingleExp( "fullsb_fit_singleExp", mgg, *ws );
  //ws->var("fullsb_fit_singleExp_Nbkg")->setVal( npoints );


  ws->var( f1 + "_fullsb_fit_Nbkg")->setVal( npoints );
  //bres = ws->pdf( tag_bkg )->fitTo( data, RooFit::Strategy(2), RooFit::Extended(kTRUE), RooFit::Save(kTRUE), RooFit::Range("low,high") );
  bres = ws->pdf( tag_bkg )->fitTo( data, RooFit::Strategy(2), RooFit::Extended(kTRUE), RooFit::Save(kTRUE), RooFit::Range("full") );//do FT for lxplus
  bres->SetName("BkgOnlyFitResult");
  ws->import( *bres );
  

  /*
  sExp_a = ws->var("fullsb_fit_singleExp_a")->getVal();
  Nbkg   = ws->var("fullsb_fit_singleExp_Nbkg")->getVal();
  NbkgUn = ws->var("fullsb_fit_singleExp_Nbkg")->getError();
  BkgNormUn = 1.0 + NbkgUn/Nbkg;//input a lnN to combine
  */

  
  //------------------------------------------------------------------------------
  //Define and obtain initial pdf parameters for f1, using sideband fit parameters
  //------------------------------------------------------------------------------
  double dE_N1, dE_N2, dE_a1, dE_a2;//doubleExp
  double sE_N, sE_a;//singleExp
  double mE_N, mE_a, mE_m;//modExp
  double sP_N, sP_a;//singlePow
  double dP_N, dP_f, dP_a1, dP_a2;//doubleExp
  double pC, p0, p1, p2, p3, pN;//poly2,pol3;
  if ( f1 == "doubleExp" )
    {
      dE_N1  = ws->var( f1 + "_fullsb_fit_Nbkg" )->getVal();
      dE_a1  = ws->var( f1 + "_fullsb_fit_a1" )->getVal();
      dE_a2  = ws->var( f1 + "_fullsb_fit_a2" )->getVal();
    }
  else if ( f1 == "singleExp" )
    {
      sE_N  = ws->var( f1 + "_fullsb_fit_Nbkg" )->getVal();
      sE_a  = ws->var( f1 + "_fullsb_fit_a" )->getVal();
    }
  else if ( f1 == "modExp" )
    {
      mE_N  = ws->var( f1 + "_fullsb_fit_Nbkg" )->getVal();
      mE_a  = ws->var( f1 + "_fullsb_fit_a" )->getVal();
      mE_m  = ws->var( f1 + "_fullsb_fit_m" )->getVal();
    }
  else if ( f1 == "singlePow" )
    {
      sP_N  = ws->var( f1 + "_fullsb_fit_Nbkg" )->getVal();
      sP_a  = ws->var( f1 + "_fullsb_fit_a" )->getVal();
    }
  else if ( f1 == "doublePow" )
    {
      dP_N   = ws->var( f1 + "_fullsb_fit_Nbkg" )->getVal();
      dP_f   = ws->var( f1 + "_fullsb_fit_f" )->getVal();
      dP_a1  = ws->var( f1 + "_fullsb_fit_a1" )->getVal();
      dP_a2  = ws->var( f1 + "_fullsb_fit_a2" )->getVal();
    }
  else if ( f1 == "poly2" )
    {
      pN = ws->var( f1 + "_fullsb_fit_Nbkg" )->getVal();
      pC = ws->var( f1 + "_fullsb_fit_pC" )->getVal();
      p0 = ws->var( f1 + "_fullsb_fit_p0" )->getVal();
      p1 = ws->var( f1 + "_fullsb_fit_p1" )->getVal();
    }
  else if ( f1 == "poly3" )
    {
      pN = ws->var( f1 + "_fullsb_fit_Nbkg" )->getVal();
      pC = ws->var( f1 + "_fullsb_fit_pC" )->getVal();
      p0 = ws->var( f1 + "_fullsb_fit_p0" )->getVal();
      p1 = ws->var( f1 + "_fullsb_fit_p1" )->getVal();
      p2 = ws->var( f1 + "_fullsb_fit_p2" )->getVal();
    }
  else if ( f1 == "poly4" )
    {
      pN = ws->var( f1 + "_fullsb_fit_Nbkg" )->getVal();
      pC = ws->var( f1 + "_fullsb_fit_pC" )->getVal();
      p0 = ws->var( f1 + "_fullsb_fit_p0" )->getVal();
      p1 = ws->var( f1 + "_fullsb_fit_p1" )->getVal();
      p2 = ws->var( f1 + "_fullsb_fit_p2" )->getVal();
      p3 = ws->var( f1 + "_fullsb_fit_p3" )->getVal();
    }
  else
    {
      std::cout << "[ERROR]: fit option not recognized. QUITTING PROGRAM" << std::endl;
      exit (EXIT_FAILURE);
    }

  Nbkg   = ws->var( f1 + "_fullsb_fit_Nbkg")->getVal();
  NbkgUn = ws->var( f1 + "_fullsb_fit_Nbkg")->getError();
  BkgNormUn = 1.0 + NbkgUn/Nbkg;//input a lnN to combine
    
  //RooDataSet* data_toys = GenerateToys( ws->pdf( tag_bkg ), mgg, npoints);
  RooAbsData* data_toys = ws->pdf( tag_bkg )->generateBinned( mgg, npoints, RooFit::ExpectedData() );
  data_toys->SetName("data_bin"+binNumber);
  data.SetName("data_bin"+binNumber);
  //--------------------------------
  // m o d e l   1   p l o t t i n g
  //--------------------------------
  TCanvas* c = new TCanvas( "c", "c", 2119, 33, 800, 700 );
  c->SetHighLightColor(2);
  c->SetFillColor(0);
  c->SetBorderMode(0);
  c->SetBorderSize(2);
  c->SetLeftMargin( leftMargin );
  c->SetRightMargin( rightMargin );
  c->SetTopMargin( topMargin );
  c->SetBottomMargin( bottomMargin );
  c->SetFrameBorderMode(0);
  c->SetFrameBorderMode(0);
  
  RooPlot *fmgg = mgg.frame();
  //data_toys->plotOn(fmgg);

  RooDataSet* dataCut = (RooDataSet*) data.reduce(RooFit::Name("dataCut"),RooFit::SelectVars(RooArgSet(mgg)),RooFit::CutRange("low"));
  RooDataSet* dataHigh = (RooDataSet*) data.reduce(RooFit::Name("dataHigh"),RooFit::SelectVars(RooArgSet(mgg)),RooFit::CutRange("high"));
  dataCut->append(*dataHigh);
  //data.plotOn(fmgg,RooFit::Invisible());
  //
  data.plotOn(fmgg);
  //dataCut->plotOn(fmgg);
  //data.plotOn(fmgg,RooFit::Invisible());
  ws->pdf( tag_bkg )->plotOn(fmgg,RooFit::LineColor(kBlue));
  //ws->pdf( tag_bkg )->plotOn(fmgg,RooFit::LineColor(kBlue), RooFit::LineStyle(kDashed) );
  //ws->pdf( tag_bkg )->plotOn(fmgg,RooFit::LineColor(kRed), RooFit::Range("Full"), RooFit::NormRange("full"));
  //ws->pdf( tag_bkg )->plotOn(fmgg,RooFit::LineColor(kBlue), RooFit::LineStyle(kDashed), RooFit::Range("low,high"),RooFit::NormRange("full"));
  
  //data.plotOn(fmgg);
  //ws->pdf( tag_bkg)->plotOn(fmgg,RooFit::LineColor(kRed),RooFit::Range("Full"),RooFit::NormRange("Full"));
  //ws->pdf( tag_bkg)->plotOn(fmgg,RooFit::LineColor(kBlue), RooFit::LineStyle(kDashed), RooFit::Range("low,high"),RooFit::NormRange("low,high"));
  float maxC = fmgg->GetMaximum();
  fmgg->GetXaxis()->SetTitleSize( axisTitleSize );
  fmgg->GetXaxis()->SetTitleOffset( axisTitleOffset );
  fmgg->GetYaxis()->SetTitleSize( axisTitleSize );
  fmgg->GetYaxis()->SetTitleOffset( axisTitleOffset );
  fmgg->SetAxisRange(0.1, maxC, "Y");
  fmgg->Draw();
  
  c->Update();
  fmgg->SetTitle("");
  TBox* box = new TBox(121, 0.105, 129, maxC-0.1);
  box->SetFillColor(kRed-9);
  box->SetFillStyle(3344);
  box->Draw("same");
  c->SaveAs( "HggRazorDataCards/" + sModel + "/bkgFit_bin" + binNumber + ".pdf" );
  fmgg->SetName( "BkgOnlyFitPlot" );
  //ws->import( *model );
  ws->import( *bres );
  ws->import( *fmgg );
  
  //-----------------------------
  //S i g n a l   p l o t t i n g
  //-----------------------------
  RooPlot *fmgg2 = mgg.frame();
  dataSignal.plotOn(fmgg2);
  ws->pdf( tagSignal )->plotOn(fmgg2, RooFit::LineColor(kRed), RooFit::Range("Full"), RooFit::NormRange("Full"));
  //ws->pdf( tagSignal )->plotOn(fmgg2, RooFit::LineColor(kBlue), RooFit::LineStyle(kDashed), RooFit::Range("low,high"),RooFit::NormRange("low,high"));
  //fmgg2->SetStats();
  fmgg2->Draw();
  TLatex* mytex = new TLatex();;
  mytex->SetNDC(kTRUE);
  mytex->DrawLatex(0.8, 0.7, Form("N = %d", npoints_signal));
  mytex->Draw("same");
  c->Update();
  c->SaveAs( "HggRazorDataCards/" + sModel + "/signalFit_bin" + binNumber + ".pdf" );
  fmgg2->SetName( "SignalFitPlot" );
  ws->import( *fmgg2 );

  //---------------------------------
  //S M - H i g g s   p l o t t i n g
  //---------------------------------
  RooPlot *fmgg3 = mgg.frame();
  dataSMH.plotOn(fmgg3);
  ws->pdf( tagSMH )->plotOn(fmgg3, RooFit::LineColor(kRed), RooFit::Range("Full"), RooFit::NormRange("Full"));
  //ws->pdf( tagSMH )->plotOn(fmgg3, RooFit::LineColor(kBlue), RooFit::LineStyle(kDashed), RooFit::Range("low,high"),RooFit::NormRange("low,high"));
  fmgg3->Draw();
  c->SaveAs( "HggRazorDataCards/" + sModel + "/smhFit_bin" + binNumber + ".pdf" );
  fmgg3->SetName( "SMHFitPlot" );
  ws->import( *fmgg3 );

  //-------------------------------------------------------
  // P r e p a r a t i o n   t o   C o m b i n e  I n p u t
  //-------------------------------------------------------
  ws->Write("w_sb");

  //--------------
  //SMH line shape
  //--------------
  RooWorkspace* combine_ws = new RooWorkspace( "combine_ws", "" );
  TString combineSMH;
  if ( category == "highres" || category == "inclusive" ) combineSMH = MakeDoubleCBNE( "SMH_bin"+binNumber, mgg, *combine_ws, true );
  else combineSMH = MakeDoubleCBNE( "SMH_bin"+binNumber, mgg, *combine_ws, true, true, category );
  combine_ws->var( combineSMH+"_muCB")->setVal( DCB_mu_smh );
  combine_ws->var( combineSMH+"_sigmaCB")->setVal( DCB_sigma_smh );
  combine_ws->var( combineSMH+"_alpha1")->setVal( DCB_a1_smh );
  combine_ws->var( combineSMH+"_n1")->setVal( DCB_n1_smh );
  combine_ws->var( combineSMH+"_alpha2")->setVal( DCB_a2_smh );
  combine_ws->var( combineSMH+"_n2")->setVal( DCB_n1_smh );
  
  combine_ws->var( combineSMH+"_muCB")->setConstant(kTRUE);
  combine_ws->var( combineSMH+"_sigmaCB")->setConstant(kTRUE);
  combine_ws->var( combineSMH+"_alpha1")->setConstant(kTRUE);
  combine_ws->var( combineSMH+"_n1")->setConstant(kTRUE);
  combine_ws->var( combineSMH+"_alpha2")->setConstant(kTRUE);
  combine_ws->var( combineSMH+"_n2")->setConstant(kTRUE);
  RooRealVar SMH_norm( combineSMH+"_norm" ,"", SMH_Yield);
  combine_ws->import( SMH_norm );
  //-----------------
  //Signal line shape
  //-----------------
  TString combineSignal;
  if ( category == "highres" || category == "inclusive" )
    {
      combineSignal = MakeDoubleCBNE( "signal_bin"+binNumber, mgg, *combine_ws, true );
      //tagSignalInterpol = MakeDoubleCBInterpolateNE( "SignalInterpol" + binNumber, mgg, *combine_ws, true );
      //combine_ws->var( tagSignalInterpol+"_mass" )->setConstant(kTRUE);
      RooRealVar SignalInterpol_norm( tagSignalInterpol + "_norm", "", Signal_Yield );
      //Signal_norm.setConstant(kFALSE);
      combine_ws->import( SignalInterpol_norm );
    }
  else
    {
      combineSignal = MakeDoubleCBNE( "signal_bin"+binNumber, mgg, *combine_ws, true, true, category );
      //tagSignalInterpol = MakeDoubleCBInterpolateNE( "SignalInterpol" + binNumber, mgg, *combine_ws, true, true, category );
      //combine_ws->var( tagSignalInterpol+"_mass" )->setConstant(kTRUE);
      RooRealVar SignalInterpol_norm( tagSignalInterpol + "_norm", "", Signal_Yield );
      //Signal_norm.setConstant(kFALSE);
      combine_ws->import( SignalInterpol_norm );
    }

  combine_ws->var( combineSignal+"_muCB")->setVal( DCB_mu_s );
  combine_ws->var( combineSignal+"_sigmaCB")->setVal( DCB_sigma_s );
  combine_ws->var( combineSignal+"_alpha1")->setVal( DCB_a1_s );
  combine_ws->var( combineSignal+"_n1")->setVal( DCB_n1_s );
  combine_ws->var( combineSignal+"_alpha2")->setVal( DCB_a2_s );
  combine_ws->var( combineSignal+"_n2")->setVal( DCB_n1_s );
  //if ( binNumber.Atof() == 17 || binNumber.Atof() == 19 || binNumber.Atof() == 20 )
  //if ( binNumber.Atof() >= 0 )
  if ( npoints_signal < 500 )//number of signal events less than 300, use SMH shape
    {
      //USE SMH SHAPE!!
      combine_ws->var( combineSignal+"_muCB")->setVal( DCB_mu_smh );
      combine_ws->var( combineSignal+"_sigmaCB")->setVal( DCB_sigma_smh );
      combine_ws->var( combineSignal+"_alpha1")->setVal( DCB_a1_smh );
      combine_ws->var( combineSignal+"_n1")->setVal( DCB_n1_smh );
      combine_ws->var( combineSignal+"_alpha2")->setVal( DCB_a2_smh );
      combine_ws->var( combineSignal+"_n2")->setVal( DCB_n1_smh );
    }
 
  
  combine_ws->var( combineSignal+"_muCB")->setConstant(kTRUE);
  combine_ws->var( combineSignal+"_sigmaCB")->setConstant(kTRUE);
  combine_ws->var( combineSignal+"_alpha1")->setConstant(kTRUE);
  combine_ws->var( combineSignal+"_n1")->setConstant(kTRUE);
  combine_ws->var( combineSignal+"_alpha2")->setConstant(kTRUE);
  combine_ws->var( combineSignal+"_n2")->setConstant(kTRUE);
  
  RooRealVar Signal_norm( combineSignal + "_norm", "", Signal_Yield );
  combine_ws->import( Signal_norm );

  
  //---------
  //Bkg model
  //---------
  TString combineBkg;
  if ( f1 == "doubleExp" )
    {
      combineBkg = MakeDoubleExpNE( f1 + "_Bkg_bin" + binNumber, mgg, *combine_ws );
      combine_ws->var( combineBkg + "_a1" )->setVal( dE_a1 );
      combine_ws->var( combineBkg + "_a2" )->setVal( dE_a2 );
    }
  else if ( f1 == "singleExp" )
    {
      combineBkg = MakeSingleExpNE( f1 + "_Bkg_bin" + binNumber, mgg, *combine_ws );
      combine_ws->var( combineBkg + "_a" )->setVal( sE_a );
    }
  else if ( f1 == "modExp" )
    {
      combineBkg = MakeModExpNE( f1 + "_Bkg_bin" + binNumber, mgg, *combine_ws );
      combine_ws->var( combineBkg + "_a" )->setVal( mE_a );
      combine_ws->var( combineBkg + "_m" )->setVal( mE_m );
    }
  else if ( f1 == "singlePow" )
    {
      combineBkg = MakeSinglePowNE( f1 + "_Bkg_bin" + binNumber, mgg, *combine_ws );
      combine_ws->var( combineBkg + "_a" )->setVal( sP_a );
    }
  else if ( f1 == "doublePow" )
    {
      combineBkg = MakeDoublePowNE( f1 + "_Bkg_bin" + binNumber, mgg, *combine_ws );
      combine_ws->var( combineBkg + "_a1" )->setVal( dP_a1 );
      combine_ws->var( combineBkg + "_a2" )->setVal( dP_a2 );
      combine_ws->var( combineBkg + "_f" )->setVal( dP_f );
    }
  else if ( f1 == "poly2" )
    {
      combineBkg = MakePoly2NE( f1 + "_Bkg_bin" + binNumber, mgg, *combine_ws );
      combine_ws->var( combineBkg + "_pC" )->setVal( pC );
      combine_ws->var( combineBkg + "_p0" )->setVal( p0 );
      combine_ws->var( combineBkg + "_p1" )->setVal( p1 );
    }
  else if ( f1 == "poly3" )
    {
      combineBkg = MakePoly3NE( f1 + "_Bkg_bin" + binNumber, mgg, *combine_ws );
      combine_ws->var( combineBkg + "_pC" )->setVal( pC );
      combine_ws->var( combineBkg + "_p0" )->setVal( p0 );
      combine_ws->var( combineBkg + "_p1" )->setVal( p1 );
      combine_ws->var( combineBkg + "_p2" )->setVal( p2 );
    }
  else if ( f1 == "poly4" )
    {
      combineBkg = MakePoly4NE( f1 + "_Bkg_bin" + binNumber, mgg, *combine_ws );
      combine_ws->var( combineBkg + "_pC" )->setVal( pC );
      combine_ws->var( combineBkg + "_p0" )->setVal( p0 );
      combine_ws->var( combineBkg + "_p1" )->setVal( p1 );
      combine_ws->var( combineBkg + "_p2" )->setVal( p2 );
      combine_ws->var( combineBkg + "_p3" )->setVal( p3 );
    }
  else
    {
      std::cout << "[ERROR]: fit option not recognized. QUITTING PROGRAM" << std::endl;
      exit (EXIT_FAILURE);
    }
  
  //combineBkg = MakeSingleExpNE( "Bkg_bin"+binNumber, mgg, *combine_ws );
  //combine_ws->var( combineBkg + "_a" )->setVal( sExp_a );
  RooRealVar Bkg_norm(  combineBkg + "_norm", "", Nbkg );
  Bkg_norm.setConstant(kFALSE);
  combine_ws->import( Bkg_norm );


  //-----------------------
  //Importing dataset
  //-----------------------
  //combine_ws->import( *data_toys );
  combine_ws->import( data );//import real data
  
  combine_ws->Write("combineWS");
  ftmp->cd();
  ftmp->Close();

  std::cout << "[INFO]: Creating combine datacard" << std::endl;
  //std::string bNumber( binNumber );//TString to std::string
  combinedRootFileName = "HggRazorWorkspace_bin" + binNumber + ".root";
  TString dataCardName = "HggRazorDataCards/" + sModel + "/HggRazorCard_bin" + binNumber + ".txt";
  std::ofstream ofs( dataCardName , std::ofstream::out );

  int combinedBinNumber = atoi(binNumber); // this is equal to binNumber, except for the LowRes bins, where it is equal to the number of the corresponding HighRes bin
  if ( combinedBinNumber > 13 ) {
      combinedBinNumber -= 5;
  }
  
  //correction is of the form N+ = nominal/(1+highres_sigmaMoverM_corr)
  //correction is of the form N- = nominal*(1+2*highres_sigmaMoverM_corr)/(1+highres_sigmaMoverM_corr)
  const float highres_sigmaMoverM_corr = -0.10749;
  //Caveat: the order in the datacard is inverted from highres since only one nuisance controls both fluctuations
  //correction is of the form N+ = nominal*(1+2*lowres_sigmaMoverM_corr)/(1+lowres_sigmaMoverM_corr)
  //correction is of the form N- = nominal/(1+lowres_sigmaMoverM_corr)
  const float lowres_sigmaMoverM_corr = 0.24268;
  
  if ( !_signalOnly )
    {
      ofs << "imax 1 number of bins\njmax 2 number of processes minus 1\nkmax * number of nuisance parameters\n";
      ofs << "----------------------------------------------------------------------------------------\n";
      ofs << "shapes Bkg\t\tbin"      << binNumber << "\t" << combinedRootFileName << " combineWS:" << combineBkg << "\n";
      ofs << "shapes SMH\t\tbin"      << binNumber << "\t" << combinedRootFileName << " combineWS:" << combineSMH << "\n";
      ofs << "shapes signal\t\tbin"   << binNumber << "\t" << combinedRootFileName << " combineWS:" << combineSignal << "\n";
      ofs << "shapes data_obs\t\tbin" << binNumber << "\t" << combinedRootFileName << " combineWS:" << "data_bin" << binNumber << "\n";
      ofs << "----------------------------------------------------------------------------------------\n";
      ofs << "bin\t\tbin" << binNumber << "\n";
      ofs << "observation\t-1.0\n";
      ofs << "----------------------------------------------------------------------------------------\n";
      ofs << "bin\t\t\t\t\t\tbin" << binNumber << "\t\tbin" << binNumber << "\t\tbin" << binNumber << "\n";
      ofs << "process\t\t\t\t\t\tsignal\t\tSMH\t\tBkg\n";
      ofs << "process\t\t\t\t\t\t0\t\t1\t\t2\n";
      ofs << "rate\t\t\t\t\t\t1\t\t1\t\t1\n";
      ofs << "----------------------------------------------------------------------------------------\n";
      ofs << "CMS_Lumi\t\t\tlnN\t\t1.026\t\t1.026\t\t-\n";
      ofs << "Photon_Trigger\t\t\tlnN\t\t1.05\t\t1.05\t\t-\n";
      //ofs << "ScaleNorm\t\t\tlnN\t\t-\t\t0.931/1.065\t\t-\n"; //instead allow scale variations to change xsection
      ofs << "PdfNorm\t\t\t\tlnN\t\t-\t\t0.948/1.062\t\t-\n";
      
      if ( category == "highres" ) {
	ofs << "SigmaMoverMEfficiency\t\t\t\tlnN\t\t" << (1.+2.*highres_sigmaMoverM_corr)/(1.+highres_sigmaMoverM_corr) << "/" << 1./(1.+highres_sigmaMoverM_corr) << "\t\t" << (1.+2.*highres_sigmaMoverM_corr)/(1.+highres_sigmaMoverM_corr) << "/" << 1./(1.+highres_sigmaMoverM_corr) << "\t\t-\n";
      } else if (category == "lowres" ) {
	ofs << "SigmaMoverMEfficiency\t\t\t\tlnN\t\t" << (1.+2.*lowres_sigmaMoverM_corr)/(1.+lowres_sigmaMoverM_corr) << "/" << 1./(1.+lowres_sigmaMoverM_corr) << "\t\t" << (1.+2.*lowres_sigmaMoverM_corr)/(1.+lowres_sigmaMoverM_corr) << "/" << 1./(1.+lowres_sigmaMoverM_corr) << "\t\t-\n";
      }

      int totalSys = smh_sys.size();
      int ctr = 0;
      for( int isys = 0; isys < totalSys; isys++ )
	{
	  if ( isys == 0 )
	    {
	      ofs << "SMH_JES\t\t\t\tlnN\t\t-\t\t" << smh_sys.at(isys+1) << "/" << smh_sys.at(isys) << "\t\t-\n";
	    }
	  else if ( isys == 2 )
	    {
	      //ofs << "SMH_facScale_bin" << combinedBinNumber << "\t\t\tlnN\t\t-\t\t" << smh_sys.at(isys+1) << "/" << smh_sys.at(isys) << "\t\t-\n";
	      ofs << "SMH_facScale_bin" << combinedBinNumber << "\t\t\tlnN\t\t-\t\t" << smh_sys.at(isys+1) << "\t\t-\n";
	    }
	  else if ( isys == 4 )
	    {
	      //ofs << "SMH_renScale_bin" << combinedBinNumber << "\t\t\tlnN\t\t-\t\t" << smh_sys.at(isys+1) << "/" << smh_sys.at(isys) << "\t\t-\n";
	      ofs << "SMH_renScale_bin" << combinedBinNumber << "\t\t\tlnN\t\t-\t\t" << smh_sys.at(isys+1) << "\t\t-\n";
	    }
	  else if ( isys == 6 )
	    {
	      //ofs << "SMH_facRenScale_bin" << combinedBinNumber << "\t\t\tlnN\t\t-\t\t" << smh_sys.at(isys+1) << "/" << smh_sys.at(isys) << "\t\t-\n";
	      ofs << "SMH_facRenScale_bin" << combinedBinNumber << "\t\t\tlnN\t\t-\t\t" << smh_sys.at(isys+1) << "\t\t-\n";
	    }
	  else if ( isys > 7 )
	    {
	      ofs << "SMH_pdf" << ctr << "\t\t\tlnN\t\t-\t\t" << smh_sys.at(isys) << "\t\t-\n";
	      ctr++;
	    }
	}
      ofs << "mu_Global\t\t\tparam\t\t 0 1.25\n";
      if ( category != "highres" ) ofs << category << "_mu_Global\t\t\tparam\t\t 0 1.25\n";
      if ( category == "hzbb" )
	{
	  ofs << "SMH_btag\t\t\tlnN\t\t-\t\t" << "0.961/1.04" "\t\t-\n";
	  ofs << "SMH_misstag\t\t\tlnN\t\t-\t\t" << "0.992/1.008" << "\t\t-\n";
	}
      
      //----------------------------------
      //Signal Systematics
      //----------------------------------
      ctr = 0;
      for( int isys = 0; isys < signal_sys.size(); isys++ )
	{
	  if ( isys == 0 )
	    {
	      ofs << "Signal_JES\t\t\t\tlnN\t\t" << signal_sys.at(isys+1) << "/" << signal_sys.at(isys) << "\t\t-\t\t-\n";
	    }
	  else if ( isys == 2 )
	    {
	      ofs << "Signal_ISR\t\t\tlnN\t\t" << signal_sys.at(isys+1) << "/" << signal_sys.at(isys) << "\t\t-\t\t-\n";
	    }
	  else if ( isys == 4 )
	    {
	      //ofs << "Signal_facScale_bin" << combinedBinNumber << "\t\t\tlnN\t\t" << signal_sys.at(isys+1) << "/" << signal_sys.at(isys) << "\t\t-\t\t-\n";
	      ofs << "Signal_facScale" << "\t\t\tlnN\t\t" << signal_sys.at(isys+1) << "/" << signal_sys.at(isys) << "\t\t-\t\t-\n";
	    }
	  else if ( isys == 6 )
	    {
	      //ofs << "Signal_renScale_bin" << combinedBinNumber << "\t\t\tlnN\t\t" << signal_sys.at(isys+1) << "/" << signal_sys.at(isys) << "\t\t-\t\t-\n";
	      ofs << "Signal_renScale" << "\t\t\tlnN\t\t" << signal_sys.at(isys+1) << "/" << signal_sys.at(isys) << "\t\t-\t\t-\n";
	    }
	  else if ( isys == 8 )
	    {
	      //ofs << "Signal_facRenScale_bin" << combinedBinNumber << "\t\t\tlnN\t\t" << signal_sys.at(isys+1) << "/" << signal_sys.at(isys) << "\t\t-\t\t-\n";
	      ofs << "Signal_facRenScale" << "\t\t\tlnN\t\t" << signal_sys.at(isys+1) << "/" << signal_sys.at(isys) << "\t\t-\t\t-\n";
	    }
	  else if ( isys >= 10 && isys <= 69 )
	    {
	      //--------------------
	      //No signal PDF systematic as SUSY group prescription
	      //--------------------
	      //ofs << "Signal_pdf" << ctr << "\t\t\tlnN\t\t" << signal_sys.at(isys) << "\t\t-\t\t-\n";
	      ctr++;
	    }
	  else if ( isys == 70 ) 
	    {
	      if (signal_sys.at(isys) != 1.0) {
		ofs << "Signal_FastsimMet" << "\t\t\tlnN\t\t" << signal_sys.at(isys) << "\t\t-\t\t-\n";
	      }
	    }
	  else if ( isys == 71 ) 
	    {
	      if (signal_sys.at(isys) != 1.0) {
		ofs << "Signal_FastsimPileup" << "\t\t\tlnN\t\t" << signal_sys.at(isys) << "\t\t-\t\t-\n";
	      }
	    } 
	  else {
	    //Weird: more than expected
	  }
	}
      
      if ( category == "hzbb" )
	{
	  ofs << "Signal_btag\t\t\tlnN\t\t" << "0.961/1.04\t\t-\t\t-\n";
	  ofs << "Signal_misstag\t\t\tlnN\t\t" << "0.992/1.008\t\t-\t\t-\n";
	}
      //ofs << "SMH_renScale\t\t\tlnN\t\t-\t\t" << SMH_renScale << "\t\t-\n";
      //ofs << "SMH_facRenScale\t\t\tlnN\t\t-\t\t" << SMH_facRenScale << "\t\t-\n";
      //ofs << "BkgNorm_bin" << binNumber << "\t\t\tlnN\t\t-\t\t-\t\t" << BkgNormUn << std::endl;
    }
  else
    {
      ofs << "imax 1 number of bins\njmax 1 number of processes minus 1\nkmax * number of nuisance parameters\n";
      ofs << "----------------------------------------------------------------------------------------\n";
      ofs << "shapes Bkg\t\tbin"      << binNumber << "\t" << combinedRootFileName << " combineWS:" << combineBkg << "\n";
      ofs << "shapes signal\t\tbin"   << binNumber << "\t" << combinedRootFileName << " combineWS:" << combineSignal << "\n";
      ofs << "shapes data_obs\t\tbin" << binNumber << "\t" << combinedRootFileName << " combineWS:" << "data_bin" << binNumber << "\n";
      ofs << "----------------------------------------------------------------------------------------\n";
      ofs << "bin\t\tbin" << binNumber << "\n";
      ofs << "observation\t-1.0\n";
      ofs << "----------------------------------------------------------------------------------------\n";
      ofs << "bin\t\t\t\t\t\tbin" << binNumber << "\t\tbin" << binNumber << "\n";
      ofs << "process\t\t\t\t\t\tsignal\t\tBkg\n";
      ofs << "process\t\t\t\t\t\t0\t\t1\n";
      ofs << "rate\t\t\t\t\t\t1\t\t1\n";
      ofs << "----------------------------------------------------------------------------------------\n";
      ofs << "CMS_Lumi\t\t\tlnN\t\t1.057\t\t-\n";
      ofs << "Photon_Trigger\t\t\tlnN\t\t1.05\t\t-\n";
      int totalSys = smh_sys.size();
      int ctr = 0;
      //----------------------------------
      //Signal Systematics
      //----------------------------------
      for( int isys = 0; isys < totalSys; isys++ )
	{
	  if ( isys == 0 )
	    {
	      ofs << "Signal_JES\t\t\t\tlnN\t\t" << signal_sys.at(isys+1) << "/" << signal_sys.at(isys) << "\t\t-\n";
	    }
	  else if ( isys == 2 )
	    {
	      ofs << "Signal_facScale\t\t\tlnN\t\t" << signal_sys.at(isys+1) << "/" << signal_sys.at(isys) << "\t\t-\n";
	    }
	  else if ( isys == 4 )
	    {
	      ofs << "Signal_renScale\t\t\tlnN\t\t" << signal_sys.at(isys+1) << "/" << signal_sys.at(isys) << "\t\t-\n";
	    }
	  else if ( isys == 6 )
	    {
	      ofs << "Signal_facRenScale\t\t\tlnN\t\t" << signal_sys.at(isys+1) << "/" << signal_sys.at(isys) << "\t\t-\n";
	    }
	  else if ( isys > 7 )
	    {
	      //--------------------
	      //No signal PDF systematic as SUSY group prescription
	      //--------------------
	      //ofs << "Signal_pdf" << ctr << "\t\t\tlnN\t\t" << signal_sys.at(isys) << "\t\t-\n";
	      ctr++;
	    }
	}
      
      if ( category == "hzbb" )
	{
	  ofs << "Signal_btag\t\t\tlnN\t\t" << "0.961/1.04\t\t-\n";
	  ofs << "Signal_misstag\t\t\tlnN\t\t" << "0.992/1.008\t\t-\n";
	}
      ofs << "mu_Global\t\t\tparam\t\t 0 1.25\n";
      if ( category != "highres" ) ofs << category << "_mu_Global\t\t\tparam\t\t 0 1.25\n";
    }
  ofs.close();
  return ws;
};


RooWorkspace* MakeDataCardExpected( TTree* treeData, TTree* treeSignal, TTree* treeSMH, TString mggName, float SMH_Yield,
				    float Signal_Yield, TString binNumber, TString category, bool isHighMass,
				    TString sModel, TString f1, bool _signalOnly )
{
  std::cout << "entering datacard: " << SMH_Yield << " " << Signal_Yield << std::endl;
  //comment out SMH_CF Signal_CF stuff
/*
  std::stringstream ss_smh, ss_signal;
  ss_smh << SMH_CF;
  ss_signal << Signal_CF;
  float tmp;
  std::vector<float> smh_sys, signal_sys;
  //---------------------------
  //SMH systematics into vector
  //---------------------------
  while ( ss_smh.good() )
    {
      ss_smh >> tmp;
      smh_sys.push_back( 1.0 + tmp );
      //std::cout << "tmp: " << tmp << std::endl;
      if ( ss_smh.eof() ) break;
    }
  //------------------------------
  //Signal systematics into vector
  //------------------------------
  while ( ss_signal.good() )
    {
      ss_signal >> tmp;
      signal_sys.push_back( 1.0 + tmp );
      //std::cout << "tmp: " << tmp << std::endl;
      if ( ss_signal.eof() ) break;
    } 
*/
  //------------------------------------------------
  // C r e a t e   s i g n a l  s h a p e from TTree
  //------------------------------------------------
  system ("mkdir -p HggRazorDataCards/" + sModel );
  TString combinedRootFileName = "HggRazorDataCards/" + sModel + "/HggRazorWorkspace_bin" + binNumber + ".root";
  TFile* ftmp = new TFile( combinedRootFileName, "recreate");
  
  RooWorkspace* ws = new RooWorkspace( "ws", "" );
  mggName = mggName + "_bin" + binNumber;
  RooRealVar mgg( mggName, "m_{#gamma#gamma}", 103, 160, "GeV" );
  //mgg.SetNameTitle( mggName, "m_{#gamma#gamma}" );
  mgg.setMin( 103. );
  mgg.setMax( 160. );
  mgg.setUnit( "GeV" );
  mgg.setBins(57);
  mgg.setRange( "signal", 115, 129. );
  mgg.setRange( "high", 129., 160. );
  mgg.setRange( "low", 103., 121. );
  mgg.setRange( "full", 103., 160. );
  mgg.setRange( "Full", 103., 160. );
  
  //--------------------------------
  //I m p or t i n g   D a t a
  //--------------------------------

  //Getting signal shape from signal MC
  //-----------------------
  //C r e a t e  doubleGaus
  //-----------------------
  bool sameMu = false;
  TString tagSignal, tagSignalInterpol, tagSMH;
  TString tag;
  treeData->GetBranch("mGammaGamma")->SetName( mggName );
  RooDataSet data( "data", "", RooArgSet(mgg), RooFit::Import(*treeData) );
  treeSignal->GetBranch("mGammaGamma")->SetName( mggName );
  RooDataSet dataSignal( "dataSignal", "", RooArgSet(mgg), RooFit::Import(*treeSignal) );
  treeSMH->GetBranch("mGammaGamma")->SetName( mggName );
  RooDataSet dataSMH( "dataSMH", "", RooArgSet(mgg), RooFit::Import(*treeSMH) );
  //---------------------------------
  //D e f i n e   s i g n a l   P D F
  //---------------------------------
  int npoints = dataSignal.numEntries();
  int npoints_signal = dataSignal.numEntries();
  if( sameMu )
    {
      tagSignal = MakeDoubleGauss( "DG_signal", mgg, *ws );
      ws->var("DG_signal_gauss_Ns")->setVal( (double)npoints );
    }
  else
    {
      //tagSignal = MakeFullDoubleGauss( "DG_signal_bin"+binNumber , mgg, *ws );
      //ws->var(tagSignal+"_Ns")->setVal( (double)npoints );

      tagSignal = MakeDoubleCB( "DCB_Signal_bin"+ binNumber, mgg, *ws );
      ws->var(tagSignal+"_Ns")->setVal( (double)npoints );
      //--------------------------
      //Setting initial parameters
      //--------------------------
      ws->var(tagSignal+"_muCB")->setVal( 125.0 );
      ws->var(tagSignal+"_sigmaCB")->setVal( 1.2 );
      ws->var(tagSignal+"_alpha1")->setVal( 1.6 );
      ws->var(tagSignal+"_n1")->setVal( 2.9 );
      ws->var(tagSignal+"_alpha2")->setVal( 1.9 );
      ws->var(tagSignal+"_n2")->setVal( 3.2 );
      if ( binNumber.Atof() == 8 ) ws->var(tagSignal+"_n2")->setVal( 1.8 );
      if ( binNumber.Atof() >= 14 )
	{
	  ws->var(tagSignal+"_sigmaCB")->setVal( 2 );
	  ws->var(tagSignal+"_alpha1")->setVal( 0.9 );
	  ws->var(tagSignal+"_n1")->setVal( 2.2 );
	  ws->var(tagSignal+"_alpha2")->setVal( 1.95 );
	  ws->var(tagSignal+"_n2")->setVal( 2.1 );
	}
      
    }

  std::cout << tagSignal << std::endl;
  RooFitResult* sres = ws->pdf( tagSignal )->fitTo( dataSignal, RooFit::Strategy(2), RooFit::Extended( kTRUE ), RooFit::Save( kTRUE ), RooFit::Range("full") );
  sres->SetName("SignalFitResult");
  ws->import( *sres );
  
  double DCB_mu_s    = ws->var(tagSignal+"_muCB")->getVal( );
  double DCB_sigma_s = ws->var(tagSignal+"_sigmaCB")->getVal( );
  double DCB_a1_s    = ws->var(tagSignal+"_alpha1")->getVal( );
  double DCB_n1_s    = ws->var(tagSignal+"_n1")->getVal( );
  double DCB_a2_s    = ws->var(tagSignal+"_alpha2")->getVal( );
  double DCB_n2_s    = ws->var(tagSignal+"_n2")->getVal( );
  //-------------------------------------
  //D e f i n e   S M - H i g g s   P D F
  //-------------------------------------
  npoints = dataSMH.numEntries();
  if( sameMu )
    {
      tagSMH = MakeDoubleGauss( "DG_SMH", mgg, *ws );
      ws->var("DG_SMH_gauss_Ns")->setVal( (double)npoints );
    }
  else
    {
      //tagSMH = MakeFullDoubleGauss( "DG_SMH_bin"+binNumber, mgg, *ws );
      //ws->var(tagSMH+"_Ns")->setVal( (double)npoints );
      tagSMH = MakeDoubleCB( "DCB_SMH_bin"+ binNumber, mgg, *ws );
      ws->var(tagSMH+"_Ns")->setVal( (double)npoints );
      //--------------------------
      //Setting initial parameters
      //--------------------------
      ws->var(tagSMH+"_muCB")->setVal( 125.0 );
      ws->var(tagSMH+"_sigmaCB")->setVal( 1.22 );
      ws->var(tagSMH+"_alpha1")->setVal( 1.3 );
      ws->var(tagSMH+"_n1")->setVal( 4.4 );
      ws->var(tagSMH+"_alpha2")->setVal( 1.9 );
      //ws->var(tagSMH+"_n2")->setVal( 4.8 );
      ws->var(tagSMH+"_n2")->setVal( 2.8 );
      if ( binNumber.Atof() >= 14 )
	{
	  ws->var(tagSMH+"_sigmaCB")->setVal( 2 );
	  ws->var(tagSMH+"_alpha1")->setVal( 0.9 );
	  ws->var(tagSMH+"_n1")->setVal( 2.2 );
	  ws->var(tagSMH+"_alpha2")->setVal( 1.95 );
	  ws->var(tagSMH+"_n2")->setVal( 2.1 );
	}
    }
  
  RooFitResult* smhres  = ws->pdf( tagSMH )->fitTo( dataSMH, RooFit::Strategy(2), RooFit::Extended( kTRUE ), RooFit::Save( kTRUE ), RooFit::Range("full") );
  smhres->SetName("SMHFitResult");
  ws->import( *smhres );
  
  double DCB_mu_smh    = ws->var(tagSMH+"_muCB")->getVal( );
  double DCB_sigma_smh = ws->var(tagSMH+"_sigmaCB")->getVal( );
  double DCB_a1_smh    = ws->var(tagSMH+"_alpha1")->getVal( );
  double DCB_n1_smh    = ws->var(tagSMH+"_n1")->getVal( );
  double DCB_a2_smh    = ws->var(tagSMH+"_alpha2")->getVal( );
  double DCB_n2_smh    = ws->var(tagSMH+"_n2")->getVal( );

  
  npoints = data.numEntries();
  //set Nbkg Initial Value
  std::cout << "entering constraints" << std::endl;
  //--------------------------------------
  //H i g g s   C o n s t r a i n s
  //--------------------------------------
  RooRealVar HiggsYield("HiggsYield","", SMH_Yield);
  //RooRealVar HiggsYieldUn("HiggsYieldUn","",SMH_YieldUn);
  //float SMH_NormUn = SMH_YieldUn/SMH_Yield;
  //RooGaussian SMH_Constraint("SMH_Constraint", "SMH_Constraint", *ws->var("DG_SMH_DGF_Ns"), RooFit::RooConst(0.1), RooFit::RooConst(0.01) );
  //RooGaussian SMH_Constraint("SMH_Constraint", "SMH_Constraint", *ws->var(tagSMH+"_Ns"), HiggsYield, HiggsYieldUn );
  std::cout << "pass constraints" << std::endl;
  std::cout << "pass forceSigma" << std::endl;

  //---------------------
  //F i t   t o   D a t a
  //---------------------
  float sExp_a;
  float Nbkg;
  float NbkgUn;
  float BkgNormUn;
  //HighMassDiphoton
  float hmd_a;
  float hmd_b;
  RooFitResult* bres;

  
  //------------------------------------
  // C r e a t e   b k g  s h a p e
  //------------------------------------
  TString tag_bkg;
  if ( f1 == "doubleExp" )
    {
      tag_bkg = MakeDoubleExp( f1 + "_fullsb_fit", mgg, *ws );
    }
  else if ( f1 == "singleExp" )
    {
      tag_bkg = MakeSingleExp( f1 + "_fullsb_fit", mgg, *ws );
    }
  else if ( f1 == "modExp" )
    {
      tag_bkg = MakeModExp( f1 + "_fullsb_fit", mgg, *ws );
    }
  else if ( f1 == "singlePow" )
    {
      tag_bkg = MakeSinglePow( f1 + "_fullsb_fit", mgg, *ws );
    }
  else if ( f1 == "doublePow" )
    {
      tag_bkg = MakeDoublePow( f1 + "_fullsb_fit", mgg, *ws );
    }
  else if ( f1 == "poly2" )
    {
      tag_bkg = MakePoly2( f1 + "_fullsb_fit", mgg, *ws );
    }
  else if ( f1 == "poly3" )
    {
      tag_bkg = MakePoly3( f1 + "_fullsb_fit", mgg, *ws );
    }
  else if ( f1 == "poly4" )
    {
      tag_bkg = MakePoly4( f1 + "_fullsb_fit", mgg, *ws );
    }
  else
    {
      std::cout << "[ERROR]: fit option not recognized. QUITTING PROGRAM" << std::endl;
      exit (EXIT_FAILURE);
    }
  std::cout << "[INFO]: f1 is a " << f1 << std::endl;

  //Original SingleExp
  //tag_bkg = MakeSingleExp( "fullsb_fit_singleExp", mgg, *ws );
  //ws->var("fullsb_fit_singleExp_Nbkg")->setVal( npoints );


  ws->var( f1 + "_fullsb_fit_Nbkg")->setVal( npoints );
  //bres = ws->pdf( tag_bkg )->fitTo( data, RooFit::Strategy(2), RooFit::Extended(kTRUE), RooFit::Save(kTRUE), RooFit::Range("low,high") );
  bres = ws->pdf( tag_bkg )->fitTo( data, RooFit::Strategy(2), RooFit::Extended(kTRUE), RooFit::Save(kTRUE), RooFit::Range("full") );//do FT for lxplus
  bres->SetName("BkgOnlyFitResult");
  ws->import( *bres );
  

    
  //------------------------------------------------------------------------------
  //Define and obtain initial pdf parameters for f1, using sideband fit parameters
  //------------------------------------------------------------------------------
  double dE_N1, dE_N2, dE_a1, dE_a2;//doubleExp
  double sE_N, sE_a;//singleExp
  double mE_N, mE_a, mE_m;//modExp
  double sP_N, sP_a;//singlePow
  double dP_N, dP_f, dP_a1, dP_a2;//doubleExp
  double pC, p0, p1, p2, p3, pN;//poly2,pol3;
  if ( f1 == "doubleExp" )
    {
      dE_N1  = ws->var( f1 + "_fullsb_fit_Nbkg" )->getVal();
      dE_a1  = ws->var( f1 + "_fullsb_fit_a1" )->getVal();
      dE_a2  = ws->var( f1 + "_fullsb_fit_a2" )->getVal();
    }
  else if ( f1 == "singleExp" )
    {
      sE_N  = ws->var( f1 + "_fullsb_fit_Nbkg" )->getVal();
      sE_a  = ws->var( f1 + "_fullsb_fit_a" )->getVal();
    }
  else if ( f1 == "modExp" )
    {
      mE_N  = ws->var( f1 + "_fullsb_fit_Nbkg" )->getVal();
      mE_a  = ws->var( f1 + "_fullsb_fit_a" )->getVal();
      mE_m  = ws->var( f1 + "_fullsb_fit_m" )->getVal();
    }
  else if ( f1 == "singlePow" )
    {
      sP_N  = ws->var( f1 + "_fullsb_fit_Nbkg" )->getVal();
      sP_a  = ws->var( f1 + "_fullsb_fit_a" )->getVal();
    }
  else if ( f1 == "doublePow" )
    {
      dP_N   = ws->var( f1 + "_fullsb_fit_Nbkg" )->getVal();
      dP_f   = ws->var( f1 + "_fullsb_fit_f" )->getVal();
      dP_a1  = ws->var( f1 + "_fullsb_fit_a1" )->getVal();
      dP_a2  = ws->var( f1 + "_fullsb_fit_a2" )->getVal();
    }
  else if ( f1 == "poly2" )
    {
      pN = ws->var( f1 + "_fullsb_fit_Nbkg" )->getVal();
      pC = ws->var( f1 + "_fullsb_fit_pC" )->getVal();
      p0 = ws->var( f1 + "_fullsb_fit_p0" )->getVal();
      p1 = ws->var( f1 + "_fullsb_fit_p1" )->getVal();
    }
  else if ( f1 == "poly3" )
    {
      pN = ws->var( f1 + "_fullsb_fit_Nbkg" )->getVal();
      pC = ws->var( f1 + "_fullsb_fit_pC" )->getVal();
      p0 = ws->var( f1 + "_fullsb_fit_p0" )->getVal();
      p1 = ws->var( f1 + "_fullsb_fit_p1" )->getVal();
      p2 = ws->var( f1 + "_fullsb_fit_p2" )->getVal();
    }
  else if ( f1 == "poly4" )
    {
      pN = ws->var( f1 + "_fullsb_fit_Nbkg" )->getVal();
      pC = ws->var( f1 + "_fullsb_fit_pC" )->getVal();
      p0 = ws->var( f1 + "_fullsb_fit_p0" )->getVal();
      p1 = ws->var( f1 + "_fullsb_fit_p1" )->getVal();
      p2 = ws->var( f1 + "_fullsb_fit_p2" )->getVal();
      p3 = ws->var( f1 + "_fullsb_fit_p3" )->getVal();
    }
  else
    {
      std::cout << "[ERROR]: fit option not recognized. QUITTING PROGRAM" << std::endl;
      exit (EXIT_FAILURE);
    }

  Nbkg   = ws->var( f1 + "_fullsb_fit_Nbkg")->getVal();
  NbkgUn = ws->var( f1 + "_fullsb_fit_Nbkg")->getError();
  BkgNormUn = 1.0 + NbkgUn/Nbkg;//input a lnN to combine
    
  //RooDataSet* data_toys = GenerateToys( ws->pdf( tag_bkg ), mgg, npoints);
  //RooAbsData* data_toys = ws->pdf( tag_bkg )->generateBinned( mgg, npoints, RooFit::ExpectedData() );
  RooDataHist* data_toys = ws->pdf( tag_bkg )->generateBinned( mgg, npoints, RooFit::ExpectedData() );
  RooDataHist* data_toys_smh = ws->pdf( tagSMH )->generateBinned( mgg, SMH_Yield, RooFit::ExpectedData() );
  data_toys->add(*data_toys_smh);
  data_toys->SetName("data_bin"+binNumber);
  data.SetName("data_bin"+binNumber);
  //--------------------------------
  // m o d e l   1   p l o t t i n g
  //--------------------------------
  TCanvas* c = new TCanvas( "c", "c", 2119, 33, 800, 700 );
  c->SetHighLightColor(2);
  c->SetFillColor(0);
  c->SetBorderMode(0);
  c->SetBorderSize(2);
  c->SetLeftMargin( leftMargin );
  c->SetRightMargin( rightMargin );
  c->SetTopMargin( topMargin );
  c->SetBottomMargin( bottomMargin );
  c->SetFrameBorderMode(0);
  c->SetFrameBorderMode(0);
  
  RooPlot *fmgg = mgg.frame();
  //data_toys->plotOn(fmgg);

  RooDataSet* dataCut = (RooDataSet*) data.reduce(RooFit::Name("dataCut"),RooFit::SelectVars(RooArgSet(mgg)),RooFit::CutRange("low"));
  RooDataSet* dataHigh = (RooDataSet*) data.reduce(RooFit::Name("dataHigh"),RooFit::SelectVars(RooArgSet(mgg)),RooFit::CutRange("high"));
  dataCut->append(*dataHigh);
  //data.plotOn(fmgg,RooFit::Invisible());
  //
  data.plotOn(fmgg);
  //dataCut->plotOn(fmgg);
  //data.plotOn(fmgg,RooFit::Invisible());
  ws->pdf( tag_bkg )->plotOn(fmgg,RooFit::LineColor(kBlue));
  //ws->pdf( tag_bkg )->plotOn(fmgg,RooFit::LineColor(kBlue), RooFit::LineStyle(kDashed) );
  //ws->pdf( tag_bkg )->plotOn(fmgg,RooFit::LineColor(kRed), RooFit::Range("Full"), RooFit::NormRange("full"));
  //ws->pdf( tag_bkg )->plotOn(fmgg,RooFit::LineColor(kBlue), RooFit::LineStyle(kDashed), RooFit::Range("low,high"),RooFit::NormRange("full"));
  
  //data.plotOn(fmgg);
  //ws->pdf( tag_bkg)->plotOn(fmgg,RooFit::LineColor(kRed),RooFit::Range("Full"),RooFit::NormRange("Full"));
  //ws->pdf( tag_bkg)->plotOn(fmgg,RooFit::LineColor(kBlue), RooFit::LineStyle(kDashed), RooFit::Range("low,high"),RooFit::NormRange("low,high"));
  float maxC = fmgg->GetMaximum();
  fmgg->GetXaxis()->SetTitleSize( axisTitleSize );
  fmgg->GetXaxis()->SetTitleOffset( axisTitleOffset );
  fmgg->GetYaxis()->SetTitleSize( axisTitleSize );
  fmgg->GetYaxis()->SetTitleOffset( axisTitleOffset );
  fmgg->SetAxisRange(0.1, maxC, "Y");
  fmgg->Draw();
  
  c->Update();
  fmgg->SetTitle("");
  TBox* box = new TBox(121, 0.105, 129, maxC-0.1);
  box->SetFillColor(kRed-9);
  //box->SetFillStyle(3344);
  box->Draw("same");
  c->SaveAs( "HggRazorDataCards/" + sModel + "/bkgFit_bin" + binNumber + ".pdf" );
  fmgg->SetName( "BkgOnlyFitPlot" );
  //ws->import( *model );
  ws->import( *bres );
  ws->import( *fmgg );
  
  //-----------------------------
  //S i g n a l   p l o t t i n g
  //-----------------------------
  RooPlot *fmgg2 = mgg.frame();
  dataSignal.plotOn(fmgg2);
  ws->pdf( tagSignal )->plotOn(fmgg2, RooFit::LineColor(kRed), RooFit::Range("Full"), RooFit::NormRange("Full"));
  //ws->pdf( tagSignal )->plotOn(fmgg2, RooFit::LineColor(kBlue), RooFit::LineStyle(kDashed), RooFit::Range("low,high"),RooFit::NormRange("low,high"));
  //fmgg2->SetStats();
  fmgg2->Draw();
  TLatex* mytex = new TLatex();;
  mytex->SetNDC(kTRUE);
  mytex->DrawLatex(0.8, 0.7, Form("N = %d", npoints_signal));
  mytex->Draw("same");
  c->Update();
  c->SaveAs( "HggRazorDataCards/" + sModel + "/signalFit_bin" + binNumber + ".pdf" );
  fmgg2->SetName( "SignalFitPlot" );
  ws->import( *fmgg2 );

  //---------------------------------
  //S M - H i g g s   p l o t t i n g
  //---------------------------------
  RooPlot *fmgg3 = mgg.frame();
  dataSMH.plotOn(fmgg3);
  ws->pdf( tagSMH )->plotOn(fmgg3, RooFit::LineColor(kRed), RooFit::Range("Full"), RooFit::NormRange("Full"));
  //ws->pdf( tagSMH )->plotOn(fmgg3, RooFit::LineColor(kBlue), RooFit::LineStyle(kDashed), RooFit::Range("low,high"),RooFit::NormRange("low,high"));
  fmgg3->Draw();
  c->SaveAs( "HggRazorDataCards/" + sModel + "/smhFit_bin" + binNumber + ".pdf" );
  fmgg3->SetName( "SMHFitPlot" );
  ws->import( *fmgg3 );

  //-------------------------------------------------------
  // P r e p a r a t i o n   t o   C o m b i n e  I n p u t
  //-------------------------------------------------------
  ws->Write("w_sb");

  //--------------
  //SMH line shape
  //--------------
  RooWorkspace* combine_ws = new RooWorkspace( "combine_ws", "" );
  TString combineSMH;
  if ( category == "highres" || category == "inclusive" ) combineSMH = MakeDoubleCBNE( "SMH_bin"+binNumber, mgg, *combine_ws, true );
  else combineSMH = MakeDoubleCBNE( "SMH_bin"+binNumber, mgg, *combine_ws, true, true, category );
  combine_ws->var( combineSMH+"_muCB")->setVal( DCB_mu_smh );
  combine_ws->var( combineSMH+"_sigmaCB")->setVal( DCB_sigma_smh );
  combine_ws->var( combineSMH+"_alpha1")->setVal( DCB_a1_smh );
  combine_ws->var( combineSMH+"_n1")->setVal( DCB_n1_smh );
  combine_ws->var( combineSMH+"_alpha2")->setVal( DCB_a2_smh );
  combine_ws->var( combineSMH+"_n2")->setVal( DCB_n1_smh );
  
  combine_ws->var( combineSMH+"_muCB")->setConstant(kTRUE);
  combine_ws->var( combineSMH+"_sigmaCB")->setConstant(kTRUE);
  combine_ws->var( combineSMH+"_alpha1")->setConstant(kTRUE);
  combine_ws->var( combineSMH+"_n1")->setConstant(kTRUE);
  combine_ws->var( combineSMH+"_alpha2")->setConstant(kTRUE);
  combine_ws->var( combineSMH+"_n2")->setConstant(kTRUE);
  RooRealVar SMH_norm( combineSMH+"_norm" ,"", SMH_Yield);
  combine_ws->import( SMH_norm );
  //-----------------
  //Signal line shape
  //-----------------
  TString combineSignal;
  if ( category == "highres" || category == "inclusive" )
    {
      combineSignal = MakeDoubleCBNE( "signal_bin"+binNumber, mgg, *combine_ws, true );
      //tagSignalInterpol = MakeDoubleCBInterpolateNE( "SignalInterpol" + binNumber, mgg, *combine_ws, true );
      //combine_ws->var( tagSignalInterpol+"_mass" )->setConstant(kTRUE);
      RooRealVar SignalInterpol_norm( tagSignalInterpol + "_norm", "", Signal_Yield );
      //Signal_norm.setConstant(kFALSE);
      combine_ws->import( SignalInterpol_norm );
    }
  else
    {
      combineSignal = MakeDoubleCBNE( "signal_bin"+binNumber, mgg, *combine_ws, true, true, category );
      //tagSignalInterpol = MakeDoubleCBInterpolateNE( "SignalInterpol" + binNumber, mgg, *combine_ws, true, true, category );
      //combine_ws->var( tagSignalInterpol+"_mass" )->setConstant(kTRUE);
      RooRealVar SignalInterpol_norm( tagSignalInterpol + "_norm", "", Signal_Yield );
      //Signal_norm.setConstant(kFALSE);
      combine_ws->import( SignalInterpol_norm );
    }

  combine_ws->var( combineSignal+"_muCB")->setVal( DCB_mu_s );
  combine_ws->var( combineSignal+"_sigmaCB")->setVal( DCB_sigma_s );
  combine_ws->var( combineSignal+"_alpha1")->setVal( DCB_a1_s );
  combine_ws->var( combineSignal+"_n1")->setVal( DCB_n1_s );
  combine_ws->var( combineSignal+"_alpha2")->setVal( DCB_a2_s );
  combine_ws->var( combineSignal+"_n2")->setVal( DCB_n1_s );
  //if ( binNumber.Atof() == 17 || binNumber.Atof() == 19 || binNumber.Atof() == 20 )
  //if ( binNumber.Atof() >= 0 )
  if ( npoints_signal < 500 )//number of signal events less than 300, use SMH shape
    {
      //USE SMH SHAPE!!
      combine_ws->var( combineSignal+"_muCB")->setVal( DCB_mu_smh );
      combine_ws->var( combineSignal+"_sigmaCB")->setVal( DCB_sigma_smh );
      combine_ws->var( combineSignal+"_alpha1")->setVal( DCB_a1_smh );
      combine_ws->var( combineSignal+"_n1")->setVal( DCB_n1_smh );
      combine_ws->var( combineSignal+"_alpha2")->setVal( DCB_a2_smh );
      combine_ws->var( combineSignal+"_n2")->setVal( DCB_n1_smh );
    }
 
  
  combine_ws->var( combineSignal+"_muCB")->setConstant(kTRUE);
  combine_ws->var( combineSignal+"_sigmaCB")->setConstant(kTRUE);
  combine_ws->var( combineSignal+"_alpha1")->setConstant(kTRUE);
  combine_ws->var( combineSignal+"_n1")->setConstant(kTRUE);
  combine_ws->var( combineSignal+"_alpha2")->setConstant(kTRUE);
  combine_ws->var( combineSignal+"_n2")->setConstant(kTRUE);
  
  RooRealVar Signal_norm( combineSignal + "_norm", "", Signal_Yield );
  combine_ws->import( Signal_norm );

  
  //---------
  //Bkg model
  //---------
  TString combineBkg;
  if ( f1 == "doubleExp" )
    {
      combineBkg = MakeDoubleExpNE( f1 + "_Bkg_bin" + binNumber, mgg, *combine_ws );
      combine_ws->var( combineBkg + "_a1" )->setVal( dE_a1 );
      combine_ws->var( combineBkg + "_a2" )->setVal( dE_a2 );
    }
  else if ( f1 == "singleExp" )
    {
      combineBkg = MakeSingleExpNE( f1 + "_Bkg_bin" + binNumber, mgg, *combine_ws );
      combine_ws->var( combineBkg + "_a" )->setVal( sE_a );
    }
  else if ( f1 == "modExp" )
    {
      combineBkg = MakeModExpNE( f1 + "_Bkg_bin" + binNumber, mgg, *combine_ws );
      combine_ws->var( combineBkg + "_a" )->setVal( mE_a );
      combine_ws->var( combineBkg + "_m" )->setVal( mE_m );
    }
  else if ( f1 == "singlePow" )
    {
      combineBkg = MakeSinglePowNE( f1 + "_Bkg_bin" + binNumber, mgg, *combine_ws );
      combine_ws->var( combineBkg + "_a" )->setVal( sP_a );
    }
  else if ( f1 == "doublePow" )
    {
      combineBkg = MakeDoublePowNE( f1 + "_Bkg_bin" + binNumber, mgg, *combine_ws );
      combine_ws->var( combineBkg + "_a1" )->setVal( dP_a1 );
      combine_ws->var( combineBkg + "_a2" )->setVal( dP_a2 );
      combine_ws->var( combineBkg + "_f" )->setVal( dP_f );
    }
  else if ( f1 == "poly2" )
    {
      combineBkg = MakePoly2NE( f1 + "_Bkg_bin" + binNumber, mgg, *combine_ws );
      combine_ws->var( combineBkg + "_pC" )->setVal( pC );
      combine_ws->var( combineBkg + "_p0" )->setVal( p0 );
      combine_ws->var( combineBkg + "_p1" )->setVal( p1 );
    }
  else if ( f1 == "poly3" )
    {
      combineBkg = MakePoly3NE( f1 + "_Bkg_bin" + binNumber, mgg, *combine_ws );
      combine_ws->var( combineBkg + "_pC" )->setVal( pC );
      combine_ws->var( combineBkg + "_p0" )->setVal( p0 );
      combine_ws->var( combineBkg + "_p1" )->setVal( p1 );
      combine_ws->var( combineBkg + "_p2" )->setVal( p2 );
    }
  else if ( f1 == "poly4" )
    {
      combineBkg = MakePoly4NE( f1 + "_Bkg_bin" + binNumber, mgg, *combine_ws );
      combine_ws->var( combineBkg + "_pC" )->setVal( pC );
      combine_ws->var( combineBkg + "_p0" )->setVal( p0 );
      combine_ws->var( combineBkg + "_p1" )->setVal( p1 );
      combine_ws->var( combineBkg + "_p2" )->setVal( p2 );
      combine_ws->var( combineBkg + "_p3" )->setVal( p3 );
    }
  else
    {
      std::cout << "[ERROR]: fit option not recognized. QUITTING PROGRAM" << std::endl;
      exit (EXIT_FAILURE);
    }
  
  //combineBkg = MakeSingleExpNE( "Bkg_bin"+binNumber, mgg, *combine_ws );
  //combine_ws->var( combineBkg + "_a" )->setVal( sExp_a );
  RooRealVar Bkg_norm(  combineBkg + "_norm", "", Nbkg );
  Bkg_norm.setConstant(kFALSE);
  combine_ws->import( Bkg_norm );


  //-----------------------
  //Importing dataset
  //-----------------------
  combine_ws->import( *data_toys );
  //combine_ws->import( data );//import real data
  
  combine_ws->Write("combineWS");
  ftmp->cd();
  ftmp->Close();

  std::cout << "[INFO]: Creating combine datacard" << std::endl;
  //std::string bNumber( binNumber );//TString to std::string
  combinedRootFileName = "HggRazorWorkspace_bin" + binNumber + ".root";
  TString dataCardName = "HggRazorDataCards/" + sModel + "/HggRazorCard_bin" + binNumber + ".txt";
  std::ofstream ofs( dataCardName , std::ofstream::out );

  int combinedBinNumber = atoi(binNumber); // this is equal to binNumber, except for the LowRes bins, where it is equal to the number of the corresponding HighRes bin
  if ( combinedBinNumber > 13 ) {
      combinedBinNumber -= 5;
  }
  
  //correction is of the form N+ = nominal/(1+highres_sigmaMoverM_corr)
  //correction is of the form N- = nominal*(1+2*highres_sigmaMoverM_corr)/(1+highres_sigmaMoverM_corr)
  const float highres_sigmaMoverM_corr = -0.10749;
  //Caveat: the order in the datacard is inverted from highres since only one nuisance controls both fluctuations
  //correction is of the form N+ = nominal*(1+2*lowres_sigmaMoverM_corr)/(1+lowres_sigmaMoverM_corr)
  //correction is of the form N- = nominal/(1+lowres_sigmaMoverM_corr)
  const float lowres_sigmaMoverM_corr = 0.24268;
  
      ofs << "imax 1 number of bins\njmax 1 number of processes minus 1\nkmax * number of nuisance parameters\n";
      ofs << "----------------------------------------------------------------------------------------\n";
      ofs << "shapes Bkg\t\tbin"      << binNumber << "\t" << combinedRootFileName << " combineWS:" << combineBkg << "\n";
      ofs << "shapes signal\t\tbin"   << binNumber << "\t" << combinedRootFileName << " combineWS:" << combineSignal << "\n";
      ofs << "shapes data_obs\t\tbin" << binNumber << "\t" << combinedRootFileName << " combineWS:" << "data_bin" << binNumber << "\n";
      ofs << "----------------------------------------------------------------------------------------\n";
      ofs << "bin\t\tbin" << binNumber << "\n";
      ofs << "observation\t-1.0\n";
      ofs << "----------------------------------------------------------------------------------------\n";
      ofs << "bin\t\t\t\t\t\tbin" << binNumber << "\t\tbin" << binNumber << "\n";
      ofs << "process\t\t\t\t\t\tsignal\t\tBkg\n";
      ofs << "process\t\t\t\t\t\t0\t\t1\n";
      ofs << "rate\t\t\t\t\t\t1\t\t1\n";
      ofs << "----------------------------------------------------------------------------------------\n";
      ofs << "CMS_Lumi\t\t\tlnN\t\t1.057\t\t-\n";
      ofs << "Photon_Trigger\t\t\tlnN\t\t1.05\t\t-\n";
      if ( category == "hzbb" )
	{
	  ofs << "Signal_btag\t\t\tlnN\t\t" << "0.961/1.04\t\t-\n";
	  ofs << "Signal_misstag\t\t\tlnN\t\t" << "0.992/1.008\t\t-\n";
	}
      ofs << "mu_Global\t\t\tparam\t\t 0 1.25\n";
      if ( category != "highres" ) ofs << category << "_mu_Global\t\t\tparam\t\t 0 1.25\n";
    
  ofs.close();
  return ws;
};

RooWorkspace* MakeSignalBkgFit( RooDataSet* data, RooRealVar& mgg, float mu, TString mggName, bool _Nconstraint )
{
  RooWorkspace* ws = new RooWorkspace( "ws", "" );

  mgg.setBins(57);
  mgg.setRange( "signal", 122, 129. );
  mgg.setRange("Full", 103., 160.);
  
  TString gauss = MakeSingleGaussNE("my_gauss", mgg, *ws);
  TString sExp = MakeSingleExpNE("my_sExp", mgg, *ws);

  //SMH contribution
  double h_yield = 4.2;
  double h_un    = h_yield*0.21;//30% uncertainty
 
  //------------------------
  //S+B model
  //--------------------------
  RooRealVar Nsmh( "sbModel_Nsmh", "N_{H}", h_yield, "" );
  Nsmh.setConstant(kFALSE);
  RooRealVar Nbkg( "sbModel_Nbkg", "N_{bkg}", 0, "" );
  double npoints = data->sumEntries();
  Nbkg.setVal(npoints);
  Nbkg.setConstant(kFALSE);

  //ws->var("my_gauss_SG_mu")->setConstant(kTRUE);
  ws->var("my_gauss_SG_sigma")->setVal(1.3);
  ws->var("my_gauss_SG_sigma")->setConstant(kTRUE);
  
  RooAddPdf* sbModel = new RooAddPdf( "sbModel", "sbModel", RooArgList( *ws->pdf(sExp), *ws->pdf(gauss) ), RooArgList( Nbkg, Nsmh ) );
  
  //ws->import( *sbModel );

  //-----------------------
  // Higgs Yield Constraint
  //-----------------------
  RooRealVar HiggsYield("HiggsYield","",h_yield);
  RooRealVar HiggsUncertainty("HiggsUncertainty","",h_un);
  RooGaussian HiggsConstraint("HiggsConstraint","", Nsmh,HiggsYield,HiggsUncertainty);
  

  //-------------------------------------
  //P r o f i l e d   L i k e l i h o o d 
  //-------------------------------------
  /*
    profile in Ns to obtain significance.
  */
  /*
    RooArgSet poi   = RooArgSet( *ws->var("doubleGaussSB_gauss_Ns") );
    RooAbsReal* nll = model->createNLL(data);
    RooFormulaVar n2ll = RooFormulaVar("n2ll", "2*@0", RooArgList(*nll) );
    RooAbsReal* p2ll = n2ll.createProfile( poi );
  */
  
  //sbModel->fitTo( *data, RooFit::Strategy(0), RooFit::Extended(kTRUE), RooFit::Range("Full"), RooFit::ExternalConstraints(RooArgSet(HiggsConstraint)) );
  RooFitResult* bres = sbModel->fitTo( *data, RooFit::Strategy(0), RooFit::Extended(kTRUE), RooFit::Save(kTRUE), RooFit::Range("Full"), RooFit::ExternalConstraints(RooArgSet(HiggsConstraint)) );
  //RooFitResult* bres = sbModel->fitTo( *data, RooFit::Strategy(0), RooFit::Extended(kTRUE), RooFit::Save(kTRUE), RooFit::Range("Full") );
  
  //--------------------------------
  // m o d e l   1   p l o t t i n g
  //--------------------------------
  RooPlot *fmgg = mgg.frame();
  data->plotOn(fmgg);
  sbModel->plotOn(fmgg,RooFit::LineColor(kRed),RooFit::Range("Full"),RooFit::NormRange("Full"));
  //sbModel->plotOn(fmgg,RooFit::LineColor(kBlue), RooFit::LineStyle(kDashed), RooFit::Range("low,high"),RooFit::NormRange("low,high"));
  fmgg->SetName( "fullsb_fit_frame" );
  ws->import( *sbModel );
  ws->import( *bres );
  ws->import( *fmgg );

  return ws;
  
};

RooWorkspace* MakeSignalBkgFit( TTree* tree, float forceSigma, bool constrainMu, float forceMu, TString mggName )
{

  //-------------------------------------
  // C r e a t e   s i g n a l  s h a p e
  //------------------------------------- 
  //Getting signal shape from MC
  TFile* fsignal = new TFile("signalModels/RSGraviton_750GeV.root", "read");
  RooWorkspace* wsignal = (RooWorkspace*)fsignal->Get("w_sFit");
  RooAbsPdf* signalPdf = wsignal->pdf("dGauss_signal_doublegauss");
  double gausFrac   =  wsignal->var("dGauss_signal_frac")->getVal();
  double gausMu     =  wsignal->var("dGauss_signal_gauss_mu")->getVal();
  double gausSigma1 =  wsignal->var("dGauss_signal_gauss_sigma1")->getVal();
  double gausSigma2 =  wsignal->var("dGauss_signal_gauss_sigma2")->getVal();

  delete fsignal;
  //fsignal->Close();
  
  TFile* ftmp = new TFile("tmp_output_OurID.root", "recreate");
  RooWorkspace* ws = new RooWorkspace( "ws", "" );
  /*  RooRealVar mgg(mggName,"m_{#gamma#gamma}",103,160,"GeV");
  mgg.setBins(38);
  mgg.setRange("low", 103, 120);
  mgg.setRange("high", 131, 160);
  mgg.setRange("signal", 103, 160);*/
  
  RooRealVar mgg( mggName, "m_{#gamma#gamma}", 220, 1000, "GeV" );
  mgg.setBins(39);
  mgg.setRange( "signal", 650, 850. );
  mgg.setRange("high", 850, 1000);
  mgg.setRange("low", 220, 650);
  //--------------------------------
  //I m p or t i n g   D a t a
  //--------------------------------
  RooDataSet data( "data", "", RooArgSet(mgg), RooFit::Import(*tree) );
  
  //------------------------------------
  // C r e a t e   b k g  s h a p e
  //------------------------------------
  //TString tag_bkg = MakeDoubleExpN1N2( "fullsb_fit_bkg", mgg, *ws );
  TString tag_bkg = MakeDoubleExpN1N2( "fullsb_fit_doubleExp", mgg, *ws );
  //TString tag_bkg = MakeSingleExp( "fullsb_fit_singleExp", mgg, *ws );
  TString tag_bkg2 = MakeSingleExp( "fullsb_fit_singleExp2", mgg, *ws );
  
  
  std::cout << "reading model from file" << std::endl;
  //Define arbitrarily a double gaussian
  //TString tag_signal = MakeDoubleGauss( "doubleGaussSB1", mgg, *ws );
  TString tag_signal2 = MakeDoubleGauss( "doubleGaussSB", mgg, *ws );

  std::cout << "creating s+b model" << std::endl;
  //---------------
  //S+B  m  o d e l
  //---------------
  RooAddPdf* model = new RooAddPdf( "model", "model", RooArgSet( *ws->pdf( tag_signal2 ), *ws->pdf( tag_bkg ) ) ) ;
  //RooAddPdf* model2 = new RooAddPdf( "model2", "model2", RooArgSet( *ws->pdf( tag_signal2 ), *ws->pdf( tag_bkg2 ) ) ) ;
  //Fixing gaussian parameter for 2nd model
  ws->var("doubleGaussSB_gauss_Ns")->setVal( 0 );
  ws->var("doubleGaussSB_frac")->setVal( gausFrac );
  ws->var("doubleGaussSB_gauss_mu")->setVal( gausMu );
  ws->var("doubleGaussSB_gauss_sigma1")->setVal( gausSigma1 );
  ws->var("doubleGaussSB_gauss_sigma2")->setVal( gausSigma2 );
  ws->var("doubleGaussSB_gauss_Ns")->setConstant(kTRUE);
  ws->var("doubleGaussSB_frac")->setConstant(kTRUE);
  ws->var("doubleGaussSB_gauss_mu")->setConstant(kTRUE);
  ws->var("doubleGaussSB_gauss_sigma1")->setConstant(kTRUE);
  ws->var("doubleGaussSB_gauss_sigma2")->setConstant(kTRUE);

  std::cout << "entering constraints" << std::endl;
  //--------------------------------------
  //H i g g s   C o n s t r a i n s
  //--------------------------------------
  /*
  RooRealVar HiggsMass("HiggsMass","",128.7);
  RooRealVar HiggsMassError("HiggsMassError","",0.4);
  RooGaussian HiggsMassConstraint("HiggsMassConstraint","", *ws->var("fullsb_fit_signal_gauss_mu"),HiggsMass,HiggsMassError);
  std::cout << "pass constraints" << std::endl;
  std::cout << "entering forceSigma" << std::endl;
  if( forceSigma != -1 ) {
    ws->var("fullsb_fit_signal_gauss_sigma1")->setVal( forceSigma );
    ws->var("fullsb_fit_signal_gauss_sigma1")->setConstant(true);
    ws->var("fullsb_fit_signal_frac")->setVal( 1.0 );
    ws->var("fullsb_fit_signal_frac")->setConstant(true);
  }
  */
  std::cout << "pass forceSigma" << std::endl;

  //---------------------
  //F i t   t o   D a t a
  //---------------------
  
  model->fitTo( data, RooFit::Strategy(0), RooFit::Extended(kTRUE), RooFit::Range("Full") );
  RooFitResult* bres = model->fitTo( data, RooFit::Strategy(0), RooFit::Extended(kTRUE), RooFit::Save(kTRUE), RooFit::Range("Full") );
  
  //model2->fitTo( data, RooFit::Strategy(0), RooFit::Extended(kTRUE), RooFit::Range("Full") );
  //RooFitResult* bres2 = model->fitTo( data, RooFit::Strategy(0), RooFit::Extended(kTRUE), RooFit::Save(kTRUE), RooFit::Range("Full") );
 

  //-------------------------------------
  //P r o f i l e d   L i k e l i h o o d 
  //-------------------------------------
  /*
    profile in Ns to obtain significance.
  */
  RooArgSet poi   = RooArgSet( *ws->var("doubleGaussSB_gauss_Ns") );
  RooAbsReal* nll = model->createNLL(data);
  RooFormulaVar n2ll = RooFormulaVar("n2ll", "2*@0", RooArgList(*nll) );
  RooAbsReal* p2ll = n2ll.createProfile( poi );
    
  
  /*
  model->fitTo( data, RooFit::Strategy(0), RooFit::Extended(kTRUE), RooFit::Range("Full"), RooFit::ExternalConstraints(RooArgSet(HiggsMassConstraint)) );
  RooFitResult* bres = model->fitTo( data, RooFit::Strategy(0), RooFit::Extended(kTRUE), RooFit::Save(kTRUE), RooFit::Range("Full"), RooFit::ExternalConstraints(RooArgSet(HiggsMassConstraint)) );
  */
  //--------------------------------
  // m o d e l   1   p l o t t i n g
  //--------------------------------
  RooPlot *fmgg = mgg.frame();
  data.plotOn(fmgg);
  model->plotOn(fmgg,RooFit::LineColor(kRed),RooFit::Range("Full"),RooFit::NormRange("Full"));
  model->plotOn(fmgg,RooFit::LineColor(kBlue), RooFit::LineStyle(kDashed), RooFit::Range("low,high"),RooFit::NormRange("low,high"));
  fmgg->SetName( "fullsb_fit_frame" );
  ws->import( *model );
  ws->import( *bres );
  ws->import( *fmgg );
  
  //--------------------------------
  // m o d e l   2   p l o t t i n g
  //--------------------------------
  /*
  RooPlot *fmgg2 = mgg.frame();
  data.plotOn(fmgg2);
  model2->plotOn(fmgg2,RooFit::LineColor(kRed),RooFit::Range("Full"),RooFit::NormRange("Full"));
  model2->plotOn(fmgg2,RooFit::LineColor(kBlue), RooFit::LineStyle(kDashed), RooFit::Range("low,high"),RooFit::NormRange("low,high"));
  fmgg2->SetName( "fullsb_fit_frame2" );
  ws->import( *model2 );
  ws->import( *bres2 );
  ws->import( *fmgg2 );*/

  //--------------------------------------
  // l i k e l i h o o d   p l o t t i n g
  //--------------------------------------
  RooPlot* fns = ws->var("doubleGaussSB_gauss_Ns")->frame( RooFit::Range(0, 20, true) );
  fns->SetMinimum(0);
  fns->SetMaximum(6);
  n2ll.plotOn( fns, RooFit::ShiftToZero(), RooFit::LineColor(kBlue) );
  p2ll->plotOn( fns, RooFit::LineColor(kBlack) );
  fns->SetName("nll_trick");
  ws->import( *fns );
  ws->Write("w_sb");
  ftmp->Close();
  return ws;
};

RooWorkspace* MakeSideBandFitAIC( TTree* tree, float forceSigma, bool constrainMu, float forceMu, TString mggName, double& AIC, TString ffName = "doubleExp" )
{
  RooWorkspace* ws = new RooWorkspace( "ws", "" );
  
  RooRealVar mgg(mggName,"m_{#gamma#gamma}",103,160,"GeV");
  mgg.setBins(57);
  mgg.setRange("low", 103, 121);
  mgg.setRange("high", 129, 160);
  mgg.setRange("Full", 103, 160);

  TString tag;
  if ( ffName == "doubleExp" )
    {
      tag = MakeDoubleExpN1N2( "sideband_fit_doubleExp", mgg, *ws );
      std::cout << "[INFO]: Running double exponential fit" << std::endl; 
    }
  else if ( ffName == "singleExp" )
    {
      tag = MakeSingleExp( "sideband_fit_singleExp", mgg, *ws );
      std::cout << "[INFO]: Running single exponential fit" << std::endl; 
    }
  else if ( ffName == "modExp" )
    {
      tag = MakeModExp( "sideband_fit_modExp", mgg, *ws );
      std::cout << "[INFO]: Running modified exponential fit" << std::endl; 
    }
  else if ( ffName == "singlePow" )
    {
      tag = MakeSinglePow( "sideband_fit_singlePow", mgg, *ws );
      std::cout << "[INFO]: Running single pow fit" << std::endl; 
    }
  else if ( ffName == "doublePow" )
    {
      tag = MakeDoublePow( "sideband_fit_doublePow", mgg, *ws );
      std::cout << "[INFO]: Running double pow fit" << std::endl; 
    }
  else if ( ffName == "poly2" )
    {
      tag = MakePoly2( "sideband_fit_poly2", mgg, *ws );
      std::cout << "[INFO]: Running poly2 fit" << std::endl; 
    }
  else if ( ffName == "poly3" )
    {
      tag = MakePoly3( "sideband_fit_poly3", mgg, *ws );
      std::cout << "[INFO]: Running poly3 fit" << std::endl; 
    }
  else
    {
      std::cout << "[ERROR]: fit option not recognized. QUITTING PROGRAM" << std::endl;
      exit (EXIT_FAILURE);
    }
  
  std::cout << "[INFO]: ENTERING FIT" << std::endl;
  //Sideband Fit
  RooDataSet data( "data", "", RooArgSet(mgg), RooFit::Import(*tree) );
  //ws->pdf( tag )->fitTo( data, RooFit::Strategy(0), RooFit::Extended(kTRUE), RooFit::Range("low,high") );
  //RooFitResult* bres = ws->pdf( tag )->fitTo( data, RooFit::Strategy(0), RooFit::Extended(kTRUE), RooFit::Save(kTRUE), RooFit::Range("low,high") );
  RooFitResult* bres = ws->pdf( tag )->fitTo( data, RooFit::Strategy(0), RooFit::Extended(kTRUE), RooFit::Save(kTRUE), RooFit::Range("Full") );
  //ws->pdf( tag )->fitTo( data, RooFit::Strategy(0), RooFit::Extended(kTRUE), RooFit::Range("Full") );
  //RooFitResult* bres = ws->pdf( tag )->fitTo( data, RooFit::Strategy(2), RooFit::Extended(kTRUE), RooFit::Save(kTRUE), RooFit::Range("low,high") );
    
  bres->SetName( tag + "_b_fitres" );
  std::cout << "[INFO]: PASS FIT" << std::endl;
  //---------------------
  //g e t t i n g   n l l 
  //---------------------
  double minNll = bres->minNll();
  //RooAbsReal* nll = ws->pdf( tag )->createNLL(data,  RooFit::Strategy(2), RooFit::Extended(kTRUE), RooFit::Range("low,high") );
  RooAbsReal* nll = ws->pdf( tag )->createNLL(data, RooFit::Extended(kTRUE), RooFit::Range("Full") );
  std::cout << "nll_nll->" << nll->getVal() << std::endl;
  std::cout << "minNll->" << minNll << std::endl;
  RooArgSet* floatPars = ws->pdf( tag )->getParameters(data);
  double K = floatPars->getSize() - 1.;
  std::cout << "K -> " << K << std::endl;
  double n = data.sumEntries(" (mgg>103 && mgg<121) || (mgg>129 && mgg<160)");
  std::cout << "n -> " << n << std::endl;
  AIC = 2*minNll + 2*K + 2*K*(K+1)/(n-K-1);
  std::cout << "AIC: " << AIC << std::endl;
  /*
  RooPlot* fns = ws->var("sideband_fit_doubleExp_a1")->frame( );
  nll->plotOn( fns, RooFit::LineColor(kBlue) );
  fns->SetName("nll_trick");
  ws->import( *fns );
  */
  ws->import( *bres );
  
  RooPlot *fmgg = mgg.frame();
  data.plotOn(fmgg);
  ws->pdf( tag )->plotOn(fmgg,RooFit::LineColor(kRed),RooFit::Range("Full"),RooFit::NormRange("Full"));
  ws->pdf( tag )->plotOn(fmgg,RooFit::LineColor(kBlue), RooFit::LineStyle(kDashed), RooFit::Range("low,high"),RooFit::NormRange("low,high"));
  
  fmgg->SetName( tag + "_frame" );
  ws->import( *fmgg );
  
  RooPlot* pdfFrame = mgg.frame();
  ws->pdf( tag )->plotOn( pdfFrame, RooFit::LineColor(kViolet), RooFit::Range("Full"), RooFit::NormRange("Full") );
  pdfFrame->SetName( tag+"_pdfframe" );
  ws->import( *pdfFrame );
  ws->import( mgg );

  return ws;
};

RooWorkspace* DoBiasTest( TTree* tree, TString mggName, TString f1, TString f2, int ntoys, int npoints )
{
  RooRandom::randomGenerator()->SetSeed( 0 );
  RooWorkspace* ws = new RooWorkspace( "ws", "" );
  
  RooRealVar mgg( mggName,"m_{#gamma#gamma}", 103, 160, "GeV" );
  mgg.setBins(38);
  mgg.setRange("low", 103, 121);
  mgg.setRange("high", 129, 160);
  mgg.setRange("sig", 121, 129);
  mgg.setRange("Full", 103, 160);
  /*
  TString tag1, tag2;
  if ( f1 == "doubleExp" )
    {
      tag1 = MakeDoubleExpN1N2( "sideband_fit_doubleExp", mgg, *ws );
      std::cout << "[INFO]: Running double exponential fit" << std::endl; 
    }
  else if ( f1 == "singleExp" )
    {
      tag1 = MakeSingleExp( "sideband_fit_singleExp", mgg, *ws );
      std::cout << "[INFO]: Running single exponential fit" << std::endl; 
    }
  else if ( f1 == "modExp" )
    {
      tag1 = MakeModExp( "sideband_fit_modExp", mgg, *ws );
      std::cout << "[INFO]: Running modified exponential fit" << std::endl; 
    }
  else if ( f1 == "singlePow" )
    {
      tag1 = MakeSinglePow( "sideband_fit_singlePow", mgg, *ws );
      std::cout << "[INFO]: Running single pow fit" << std::endl; 
    }
  else if ( f1 == "doublePow" )
    {
      tag1 = MakeDoublePow( "sideband_fit_doublePow", mgg, *ws );
      std::cout << "[INFO]: Running double pow fit" << std::endl; 
    }
  else if ( f1 == "poly2" )
    {
      tag1 = MakePoly2( "sideband_fit_poly2", mgg, *ws );
      std::cout << "[INFO]: Running poly2 fit" << std::endl; 
    }
  else if ( f1 == "poly3" )
    {
      tag1 = MakePoly3( "sideband_fit_poly3", mgg, *ws );
      std::cout << "[INFO]: Running poly3 fit" << std::endl; 
    }
  else
    {
      std::cout << "[ERROR]: fit option not recognized. QUITTING PROGRAM" << std::endl;
      exit (EXIT_FAILURE);
    }
  //------------------
  //f2
  //------------------
  if ( f2 == "doubleExp" )
    {
      tag2 = MakeDoubleExpN1N2( "sideband_fit_doubleExp", mgg, *ws );
      std::cout << "[INFO]: Running double exponential fit" << std::endl; 
    }
  else if ( f2 == "singleExp" )
    {
      tag2 = MakeSingleExp( "sideband_fit_singleExp", mgg, *ws );
      std::cout << "[INFO]: Running single exponential fit" << std::endl; 
    }
  else if ( f2 == "modExp" )
    {
      tag2 = MakeModExp( "sideband_fit_modExp", mgg, *ws );
      std::cout << "[INFO]: Running modified exponential fit" << std::endl; 
    }
  else if ( f2 == "singlePow" )
    {
      tag2 = MakeSinglePow( "sideband_fit_singlePow", mgg, *ws );
      std::cout << "[INFO]: Running single pow fit" << std::endl; 
    }
  else if ( f2 == "doublePow" )
    {
      tag2 = MakeDoublePow( "sideband_fit_doublePow", mgg, *ws );
      std::cout << "[INFO]: Running double pow fit" << std::endl; 
    }
  else if ( f2 == "poly2" )
    {
      tag2 = MakePoly2( "sideband_fit_poly2", mgg, *ws );
      std::cout << "[INFO]: Running poly2 fit" << std::endl; 
    }
  else if ( f2 == "poly3" )
    {
      tag2 = MakePoly3( "sideband_fit_poly3", mgg, *ws );
      std::cout << "[INFO]: Running poly3 fit" << std::endl; 
    }
  else
    {
      std::cout << "[ERROR]: fit option not recognized. QUITTING PROGRAM" << std::endl;
      exit (EXIT_FAILURE);
    }
  */
  TString tag1, tag2, tag2p;
  if ( f1 == "doubleExp" )
    {
      tag1 = MakeDoubleExpN1N2( "doubleExp_1", mgg, *ws );
      std::cout << "[INFO]: Running double exponential fit" << std::endl; 
    }
  else if ( f1 == "singleExp" )
    {
      tag1 = MakeSingleExp( "singleExp_1", mgg, *ws );
      std::cout << "[INFO]: Running single exponential fit" << std::endl; 
    }
  else if ( f1 == "modExp" )
    {
      tag1 = MakeModExp( "modExp_1", mgg, *ws );
      std::cout << "[INFO]: Running modified exponential fit" << std::endl; 
    }
  else if ( f1 == "singlePow" )
    {
      tag1 = MakeSinglePow( "singlePow_1", mgg, *ws );
      std::cout << "[INFO]: Running single pow fit" << std::endl; 
    }
  else if ( f1 == "doublePow" )
    {
      tag1 = MakeDoublePow( "doublePow_1", mgg, *ws );
      std::cout << "[INFO]: Running double pow fit" << std::endl; 
    }
  else if ( f1 == "poly2" )
    {
      tag1 = MakePoly2( "poly2_1", mgg, *ws );
      std::cout << "[INFO]: Running poly2 fit" << std::endl; 
    }
  else if ( f1 == "poly3" )
    {
      tag1 = MakePoly3( "poly3_1", mgg, *ws );
      std::cout << "[INFO]: Running poly3 fit" << std::endl; 
    }
  else
    {
      std::cout << "[ERROR]: fit option not recognized. QUITTING PROGRAM" << std::endl;
      exit (EXIT_FAILURE);
    }
  //------------------
  //f2
  //------------------
  if ( f2 == "doubleExp" )
    {
      tag2  = MakeDoubleExpN1N2( f2 + "_2", mgg, *ws );
      tag2p = MakeDoubleExpN1N2( f2 + "_prime", mgg, *ws );
      std::cout << "[INFO]: Running double exponential fit" << std::endl; 
    }
  else if ( f2 == "singleExp" )
    {
      tag2  = MakeSingleExp( f2 + "_2", mgg, *ws );
      tag2p = MakeSingleExp( f2 + "_prime", mgg, *ws );
      std::cout << "[INFO]: Running single exponential fit" << std::endl; 
    }
  else if ( f2 == "modExp" )
    {
      tag2  = MakeModExp( f2 + "_2", mgg, *ws );
      tag2p = MakeModExp( f2 + "_prime", mgg, *ws );
      std::cout << "[INFO]: Running modified exponential fit" << std::endl; 
    }
  else if ( f2 == "singlePow" )
    {
      tag2  = MakeSinglePow( f2 + "_2", mgg, *ws );
      tag2p = MakeSinglePow( f2 + "_prime", mgg, *ws );
      std::cout << "[INFO]: Running single pow fit" << std::endl; 
    }
  else if ( f2 == "doublePow" )
    {
      tag2  = MakeDoublePow( f2 + "_2", mgg, *ws );
      tag2p = MakeDoublePow( f2 + "_prime", mgg, *ws );
      std::cout << "[INFO]: Running double pow fit" << std::endl; 
    }
  else if ( f2 == "poly2" )
    {
      tag2  = MakePoly2( f2 + "_2", mgg, *ws );
      tag2p = MakePoly2( f2 + "_prime", mgg, *ws );
      std::cout << "[INFO]: Running poly2 fit" << std::endl; 
    }
  else if ( f2 == "poly3" )
    {
      tag2  = MakePoly3( f2 + "_2", mgg, *ws );
      tag2p = MakePoly3( f2 + "_prime", mgg, *ws );
      std::cout << "[INFO]: Running poly3 fit" << std::endl; 
    }
  else
    {
      std::cout << "[ERROR]: fit option not recognized. QUITTING PROGRAM" << std::endl;
      exit (EXIT_FAILURE);
    }
    
  
  
  RooDataSet data( "data", "", RooArgSet(mgg), RooFit::Import(*tree) );
  npoints = data.numEntries();
  //Sideband Fit (not working with poly2 and poly3)
  //ws->pdf( tag1 )->fitTo( data, RooFit::Strategy(0), RooFit::Extended(kTRUE), RooFit::Range("low,high") );
  //RooFitResult* bres = ws->pdf( tag1 )->fitTo( data, RooFit::Strategy(2), RooFit::Extended(kTRUE), RooFit::Save(kTRUE), RooFit::Range("low,high") );
  //FullFit
  RooFitResult* bres = ws->pdf( tag1 )->fitTo( data, RooFit::Strategy(0), RooFit::Save(kTRUE), RooFit::Extended(kTRUE), RooFit::Range("low,high") );
  //RooFitResult* bres = ws->pdf( tag1 )->fitTo( data, RooFit::Strategy(0), RooFit::Extended(kTRUE), RooFit::Save(kTRUE), RooFit::Range("low,high") );

  RooPlot* f1_frame = mgg.frame();
  f1_frame->SetName("f1_frame");
  data.plotOn( f1_frame );
  ws->pdf( tag1 )->plotOn( f1_frame, RooFit::LineColor( kRed), RooFit::Range("low,high"), RooFit::NormRange("low,high") );
  ws->import( *f1_frame );
  RooAbsReal* f1Integral = ws->pdf( tag1 )->createIntegral(mgg, RooFit::NormSet(mgg), RooFit::Range("sig") );
  std::cout << "f1 Int: " << f1Integral->getVal() << std::endl;
  
  RooDataSet* data_toys;
  RooFitResult* bres_toys;
  double n; 
  RooAbsReal* fIntegral;
  RooAbsReal* fIntegral2;
  RooRealVar bias("bias", "bias", -5.0, 5.0, "");
  RooDataSet data_bias( "data_bias", "bias data", bias);
  bias.setBins(100);
  
  
  //-----------------------
  //do a fit to bias data
  //-----------------------
  ws->pdf( tag2p )->fitTo( data, RooFit::Strategy(0), RooFit::Extended(kTRUE), RooFit::Range("low,high") );
  RooPlot* pFrame = mgg.frame();
  pFrame->SetName("pFitFrame");
  data.plotOn( pFrame );
  ws->pdf( tag2p )->plotOn( pFrame, RooFit::LineColor(kBlue), RooFit::Range("low,high"), RooFit::NormRange("low,high") );
  ws->pdf( tag2p )->plotOn( pFrame, RooFit::LineStyle(kDashed), RooFit::LineColor(kRed), RooFit::Range("Full"), RooFit::NormRange("low,high") );
  ws->import( *pFrame );
  
  double dE_N1, dE_N2, dE_a1, dE_a2;//doubleExp
  double sE_N, sE_a;//singleExp
  double mE_N, mE_a, mE_m;//modExp
  double sP_N, sP_a;//singlePow
  double dP_N, dP_f, dP_a1, dP_a2;//doubleExp
  double pC, p0, p1, p2, pN;//poly2,pol3;
  if ( f2 == "doubleExp" )
    {
      dE_N1  = ws->var( f2 + "_prime_Nbkg1" )->getVal();
      dE_N2  = ws->var( f2 + "_prime_Nbkg2" )->getVal();
      dE_a1  = ws->var( f2 + "_prime_a1" )->getVal();
      dE_a2  = ws->var( f2 + "_prime_a2" )->getVal();
    }
  else if ( f2 == "singleExp" )
    {
      sE_N  = ws->var( f2 + "_prime_Nbkg" )->getVal();
      sE_a  = ws->var( f2 + "_prime_a" )->getVal();
    }
  else if ( f2 == "modExp" )
    {
      mE_N  = ws->var( f2 + "_prime_Nbkg" )->getVal();
      mE_a  = ws->var( f2 + "_prime_a" )->getVal();
      mE_m  = ws->var( f2 + "_prime_m" )->getVal();
    }
  else if ( f2 == "singlePow" )
    {
      sP_N  = ws->var( f2 + "_prime_Nbkg" )->getVal();
      sP_a  = ws->var( f2 + "_prime_a" )->getVal();
    }
  else if ( f2 == "doublePow" )
    {
      dP_N   = ws->var( f2 + "_prime_Nbkg" )->getVal();
      dP_f   = ws->var( f2 + "_prime_f" )->getVal();
      dP_a1  = ws->var( f2 + "_prime_a1" )->getVal();
      dP_a2  = ws->var( f2 + "_prime_a2" )->getVal();
    }
  else if ( f2 == "poly2" )
    {
      pN = ws->var( f2 + "_prime_Nbkg" )->getVal();
      pC = ws->var( f2 + "_prime_pC" )->getVal();
      p0 = ws->var( f2 + "_prime_p0" )->getVal();
      p1 = ws->var( f2 + "_prime_p1" )->getVal();
    }
  else if ( f2 == "poly3" )
    {
      pN = ws->var( f2 + "_prime_Nbkg" )->getVal();
      pC = ws->var( f2 + "_prime_pC" )->getVal();
      p0 = ws->var( f2 + "_prime_p0" )->getVal();
      p1 = ws->var( f2 + "_prime_p1" )->getVal();
      p2 = ws->var( f2 + "_prime_p2" )->getVal();
    }
  else
    {
      std::cout << "[ERROR]: fit option not recognized. QUITTING PROGRAM" << std::endl;
      exit (EXIT_FAILURE);
    }
  for ( int i = 0; i < ntoys; i++ )
    {
      //-----------------------------
      //G e n e r a t i n g   t o y s
      //-----------------------------
      data_toys = GenerateToys( ws->pdf( tag1 ), mgg, npoints );
      //ws->pdf( tag2 )->fitTo( *data_toys, RooFit::Strategy(0), RooFit::Extended(kTRUE), RooFit::Range("low,high") );
      //RooFitResult* bres_toys = ws->pdf( tag2 )->fitTo( *data_toys, RooFit::Strategy(2), RooFit::Extended(kTRUE), RooFit::Save(kTRUE), RooFit::Range("low,high") );
      if ( f2 == "doubleExp" )
      	{
	  ws->var( f2 + "_2_Nbkg1")->setVal( dE_N1 );
	  ws->var( f2 + "_2_Nbkg2")->setVal( dE_N2 );
	  ws->var( f2 + "_2_a1")->setVal( dE_a1 );
	  ws->var( f2 + "_2_a2")->setVal( dE_a2 );
	}
      else if ( f2 == "singleExp" )
	{
	  ws->var( f2 + "_2_Nbkg" )->setVal( sE_N );
	  ws->var( f2 + "_2_a" )->setVal( sE_a );
	}
      else if ( f2 == "modExp" )
	{
	  ws->var( f2 + "_2_Nbkg" )->setVal( mE_N );
	  ws->var( f2 + "_2_a" )->setVal( mE_a );
	  ws->var( f2 + "_2_m" )->setVal( mE_m );
	}
      else if ( f2 == "singlePow" )
	{
	  ws->var( f2 + "_2_Nbkg" )->setVal( sP_N );
	  ws->var( f2 + "_2_a" )->setVal( sP_a );
	}
      else if ( f2 == "doublePow" )
	{
	  ws->var( f2 + "_2_Nbkg" )->setVal( dP_N );
	  ws->var( f2 + "_2_f" )->setVal( dP_f );
	  ws->var( f2 + "_2_a1" )->setVal( dP_a1 );
	  ws->var( f2 + "_2_a2" )->setVal( dP_a2 );
	}
      else if ( f2 == "poly2" )
	{
	  ws->var( f2 + "_2_Nbkg" )->setVal( pN );
	  ws->var( f2 + "_2_pC" )->setVal( pC );
	  ws->var( f2 + "_2_p0" )->setVal( p0 );
	  ws->var( f2 + "_2_p1" )->setVal( p1 );
	}
      else if ( f2 == "poly3" )
	{
	  ws->var( f2 + "_2_Nbkg" )->setVal( pN );
	  ws->var( f2 + "_2_pC" )->setVal( pC );
	  ws->var( f2 + "_2_p0" )->setVal( p0 );
	  ws->var( f2 + "_2_p1" )->setVal( p1 );
	  ws->var( f2 + "_2_p2" )->setVal( p2 );
	}
      else
	{
	  ws->pdf( tag2 )->fitTo( *data_toys, RooFit::Strategy(0), RooFit::Extended(kTRUE), RooFit::Range("low,high") );
	}
      
      
      bres_toys = ws->pdf( tag2 )->fitTo( *data_toys, RooFit::Strategy(0), RooFit::Extended(kTRUE), RooFit::Save(kTRUE), RooFit::Range("Full") );
      bres_toys->SetName("bres_toys");
      
      fIntegral2 = ws->pdf( tag2 )->createIntegral(mgg, RooFit::NormSet(mgg), RooFit::Range("sig") );
      std::cout << "test Int2: " << fIntegral2->getVal() << std::endl;
      //std::cout << "signal events fit: " <<  (fIntegral2->getVal())*pow(ws->var("sideband_fit_singleExpse_Nbkg")->getVal(),2) << std::endl;
      bias =  (fIntegral2->getVal() - f1Integral->getVal())/f1Integral->getVal();
      data_bias.add(RooArgSet(bias));
    }
  RooPlot* f_mgg = mgg.frame();
  f_mgg->SetName("toys_plot");
  data_toys->plotOn( f_mgg );
  ws->pdf( tag2 )->plotOn( f_mgg, RooFit::LineColor(kBlue), RooFit::Range("Full"), RooFit::NormRange("Full"));

  RooPlot* f_bias = bias.frame();
  f_bias->SetName("bias_plot");
  data_bias.plotOn( f_bias );
  ws->import( mgg );
  ws->import( bias );
  ws->import( data_bias );
  ws->import( *f_mgg );
  ws->import( *bres_toys );
  ws->import( *f_bias );

  return ws;
};

RooWorkspace* DoBiasTestSignal( TTree* tree, TString mggName, TString f1, TString f2, int ntoys, double frac, TString outName )
{
  RooRandom::randomGenerator()->SetSeed( 0 );
  RooWorkspace* ws = new RooWorkspace( "ws", "" );

  //Getting signal shape
  std::cout << "[INFO]: getting signal model" << std::endl;
  TFile* fsignal = new TFile("data/SM_MC_GluGluH_Fit.root", "read");
  RooWorkspace* wsignal = (RooWorkspace*)fsignal->Get("w_sFit");
  //Getting signal pdf and parementer except Ns
  RooAbsPdf* signalPdf = wsignal->pdf("dGauss_signal_doublegauss");
  double gausFrac   =  wsignal->var("dGauss_signal_frac")->getVal();
  double gausMu     =  wsignal->var("dGauss_signal_gauss_mu")->getVal();
  double gausSigma1 =  wsignal->var("dGauss_signal_gauss_sigma1")->getVal();
  double gausSigma2 =  wsignal->var("dGauss_signal_gauss_sigma2")->getVal();

  delete fsignal;

  //---------------------------------
  //Define output Tree for bias study
  //---------------------------------
  TTree* outTree = new TTree("biasTree", "tree containing bias tests");
  //define variables
  double _bias, _statUn, _biasNorm;
  double _Ns_hat, _Ns_sigma, _Ns, _alpha_hat, _alpha_sigma, _alpha, _Nbkg_hat, _Nbkg_sigma, _Nbkg;
  int _status, _status2, _status3, _covStatus, _covStatus2, _covStatus3;
  //define branches
  outTree->Branch("bias", &_bias, "bias/D");
  outTree->Branch("statUn", &_statUn, "statUn/D");
  outTree->Branch("biasNorm", &_biasNorm, "biasNorm/D");
  outTree->Branch("alpha_hat", &_alpha_hat, "alpha_hat/D");
  outTree->Branch("alpha_sigma", &_alpha_sigma, "alpha_sigma/D");
  outTree->Branch("alpha", &_alpha, "alpha/D");
  outTree->Branch("Ns_hat", &_Ns_hat, "Ns_hat/D");
  outTree->Branch("Ns_sigma", &_Ns_sigma, "Ns_sigma/D");
  outTree->Branch("Ns", &_Ns, "Ns/D");
  outTree->Branch("Nbkg_hat", &_Nbkg_hat, "Nbkg_hat/D");
  outTree->Branch("Nbkg_sigma", &_Nbkg_sigma, "Nbkg_sigma/D");
  outTree->Branch("Nbkg", &_Nbkg, "Nbkg/D");
  outTree->Branch("status", &_status, "status/I");
  outTree->Branch("covStatus", &_covStatus, "covStatus/I");
  outTree->Branch("status2", &_status2, "status2/I");
  outTree->Branch("covStatus2", &_covStatus2, "covStatus2/I");
  outTree->Branch("status3", &_status3, "status3/I");
  outTree->Branch("covStatus3", &_covStatus3, "covStatus3/I");

  //-------------------
  //Creating observable
  //-------------------
  RooRealVar mgg( mggName,"m_{#gamma#gamma}", 103, 160, "GeV" );
  mgg.setBins(38);
  mgg.setRange("low", 103, 121. );//low sideband
  mgg.setRange("high", 129, 160.);//high sideband
  mgg.setRange("sig", 121, 129);//highRes signal region
  mgg.setRange("Full", 103.0, 160.0);//Full range for this analysis

  //-----------------------------------------------------------------
  //Generate signal toys to check the signal shape in the output file
  //-----------------------------------------------------------------
  RooDataSet* signal_toys = GenerateToys( signalPdf, mgg, 1e4 );
  signal_toys->SetName("signal_toys_new");
  RooPlot* s_mgg = mgg.frame();
  s_mgg->SetName("signal_toys");
  signal_toys->plotOn( s_mgg );
  ws->import( *signal_toys );
  ws->import( *s_mgg );

  //---------------------
  //Define parent pdf #1
  //---------------------
  TString tag1, tag2, tag2p;
  if ( f1 == "doubleExp" )
    {
      //tag1 = MakeDoubleExpN1N2( f1 + "_1", mgg, *ws );
      tag1 = MakeDoubleExp( f1 + "_1", mgg, *ws );
    }
  else if ( f1 == "singleExp" )
    {
      tag1 = MakeSingleExp( f1 + "_1", mgg, *ws );
    }
  else if ( f1 == "modExp" )
    {
      tag1 = MakeModExp( f1 + "_1", mgg, *ws );
    }
  else if ( f1 == "singlePow" )
    {
      tag1 = MakeSinglePow( f1 + "_1", mgg, *ws );
    }
  else if ( f1 == "doublePow" )
    {
      tag1 = MakeDoublePow( f1 + "_1", mgg, *ws );
    }
  else if ( f1 == "poly2" )
    {
      tag1 = MakePoly2( f1 + "_1", mgg, *ws );
    }
  else if ( f1 == "poly3" )
    {
      tag1 = MakePoly3( f1 + "_1", mgg, *ws );
    }
  else if ( f1 == "poly4" )
    {
      tag1 = MakePoly4( f1 + "_1", mgg, *ws );
    }
  else
    {
      std::cout << "[ERROR]: fit option not recognized. QUITTING PROGRAM" << std::endl;
      exit (EXIT_FAILURE);
    }
  std::cout << "[INFO]: f1 is a " << f1 << std::endl;
  
  //------------------
  //Define test pdf #2
  //------------------
  if ( f2 == "doubleExp" )
    {
      //tag2  = MakeDoubleExpN1N2( f2 + "_2", mgg, *ws );
      //tag2p = MakeDoubleExpN1N2( f2 + "_prime", mgg, *ws );
      tag2  = MakeDoubleExpNE( f2 + "_2", mgg, *ws );
      tag2p = MakeDoubleExp( f2 + "_prime", mgg, *ws );
    }
  else if ( f2 == "singleExp" )
    {
      tag2  = MakeSingleExpNE( f2 + "_2", mgg, *ws );
      tag2p = MakeSingleExp( f2 + "_prime", mgg, *ws );
    }
  else if ( f2 == "modExp" )
    {
      tag2  = MakeModExpNE( f2 + "_2", mgg, *ws );
      tag2p = MakeModExp( f2 + "_prime", mgg, *ws );
    }
  else if ( f2 == "singlePow" )
    {
      tag2  = MakeSinglePowNE( f2 + "_2", mgg, *ws );
      tag2p = MakeSinglePow( f2 + "_prime", mgg, *ws );
    }
  else if ( f2 == "doublePow" )
    {
      tag2  = MakeDoublePowNE( f2 + "_2", mgg, *ws );
      tag2p = MakeDoublePow( f2 + "_prime", mgg, *ws );
    }
  else if ( f2 == "poly2" )
    {
      tag2  = MakePoly2NE( f2 + "_2", mgg, *ws );
      tag2p = MakePoly2( f2 + "_prime", mgg, *ws );
    }
  else if ( f2 == "poly3" )
    {
      tag2  = MakePoly3NE( f2 + "_2", mgg, *ws );
      tag2p = MakePoly3( f2 + "_prime", mgg, *ws );
    }
  else if ( f2 == "poly4" )
    {
      tag2  = MakePoly4NE( f2 + "_2", mgg, *ws );
      tag2p = MakePoly4( f2 + "_prime", mgg, *ws );
    }
  else
    {
      std::cout << "[ERROR]: fit option not recognized. QUITTING PROGRAM" << std::endl;
      exit (EXIT_FAILURE);
    }
  std::cout << "[INFO]: f2 is a " << f2 << std::endl;

  //-------------------------------------
  //Define data set, importing from TTree
  //-------------------------------------
  RooDataSet data( "data", "", RooArgSet(mgg), RooFit::Import(*tree) );
  //getting total n_entries and n_sideband
  //double n_sideband = data.sumEntries("(mgg > 103. && mgg < 120.) || (mgg > 135. && mgg < 160.)");
  TString sbCut = Form("(%s>%.2f && %s<%.2f) || (%s>%.2f && %s<%.2f)", mggName.Data(), 103., mggName.Data(), 121., mggName.Data(), 129., mggName.Data(), 160.);
  double n_sideband = data.sumEntries( sbCut );

  //----------------------------------------------
  //Sideband Fit to data set using parent function
  //----------------------------------------------
  RooFitResult* bres = ws->pdf( tag1 )->fitTo( data, RooFit::Strategy(2), RooFit::Extended(kTRUE), RooFit::Save(kTRUE), RooFit::Range("low,high") );
  //_alpha = ws->var( f1 + "_1_a" )->getVal();
  //FullFit
  //RooFitResult* bres = ws->pdf( tag1 )->fitTo( data, RooFit::Strategy(0), RooFit::Extended(kTRUE), RooFit::Save(kTRUE), RooFit::Range("Full") );

  //---------------------------------------
  //P l o t t i n g   s i de b a n d  f i t 
  //---------------------------------------
  RooPlot* bFrame = mgg.frame();
  bFrame->SetName("bFitFrame");
  bFrame->SetTitle("");
  data.plotOn( bFrame );
  ws->pdf( tag1 )->plotOn( bFrame, RooFit::LineColor(kBlue), RooFit::Range("low,high"), RooFit::NormRange("low,high"));
  ws->import( *bFrame );
  //saving firResult
  bres->SetName( "fit_result_f1" );
  ws->import( *bres );

  //-----------------------------------
  //g e t t i n g   i n t e g t r a l s
  //-----------------------------------
  RooAbsReal* f1Integral = ws->pdf( tag1 )->createIntegral(mgg, RooFit::NormSet(mgg), RooFit::Range("sig") );
  double f1Int = f1Integral->getVal();

  RooAbsReal* f1Integral_sb = ws->pdf( tag1 )->createIntegral(mgg, RooFit::NormSet(mgg), RooFit::Range("low,high") );
  double f1Int_sb = f1Integral_sb->getVal();
  int npoints = (int)n_sideband/f1Int_sb;//re-scaling sideband to total bkg events (N_sideband/NORMALIZE_INTEGRAL_SIDEBAND)
  npoints = 2*npoints;
  //npoints = 350;//only use this to set the number of toys bkg;

  std::cout << "npoints: " << npoints << std::endl;
  //-------------------------------
  //S i g n a l   +   B k g   P d f
  //-------------------------------
  //bkg non-extended, see tag2 above
  //TString bkgTag = MakeSinglePowNE("bkg_model", mgg, *ws );
  //signal non-extended
  TString gaussTag = MakeDoubleGaussNE("signal", mgg, *ws );
  RooRealVar Ns( "sbModel_Ns", "N_{s}", 0, "" );
  Ns.setConstant(kFALSE);
  //Ns.setRange(-1,1e4);
  RooRealVar Nbkg( "sbModel_Nbkg", "N_{bkg}", 0, "" );
  Nbkg.setVal(npoints);
  Nbkg.setConstant(kFALSE);
  RooAddPdf* sbModel = new RooAddPdf( "sbModel", "sbModel", RooArgList( *ws->pdf(tag2), *ws->pdf(gaussTag) ), RooArgList( Nbkg, Ns ) );
  ws->import( *sbModel );
  
  RooDataSet*   data_toys;
  RooFitResult* bres_toys;
  double n; 

  //---------------------
  //RooFit bias variables
  //---------------------
  RooAbsReal* fIntegral;
  RooAbsReal* fIntegral2;
  RooRealVar bias("bias", "bias", -50.0, 50.0, "");
  RooDataSet data_bias( "data_bias", "bias data", bias);

  RooRealVar NsignalError("NsignalError", "NsignalError", -5.0, 5.0, "");
  RooDataSet data_Nse( "data_Nse", "data_Nse", NsignalError);
  
  bias.setBins(100);
  NsignalError.setBins(100);
  //----------------------------------
  //Setting initial parameter for Nbkg
  //----------------------------------
  if ( f2 == "doubleExp" )
    {
      //ws->var( f2 + "_prime_Nbkg1" )->setVal(npoints);
      //ws->var( f2 + "_prime_Nbkg2" )->setVal(.0);
      ws->var( f2 + "_prime_Nbkg" )->setVal(npoints);
    }
  else if ( f2 == "singleExp" )
    {
      ws->var( f2 + "_prime_Nbkg" )->setVal(npoints);
    }
  else if ( f2 == "modExp" )
    {
      ws->var( f2 + "_prime_Nbkg" )->setVal(npoints);
    }
  else if ( f2 == "singlePow" )
    {
      ws->var( f2 + "_prime_Nbkg" )->setVal(npoints);
    }
  else if ( f2 == "doublePow" )
    {
      ws->var( f2 + "_prime_Nbkg" )->setVal(npoints);
    }
  else if ( f2 == "poly2" )
    {
      ws->var( f2 + "_prime_Nbkg" )->setVal(npoints);
    }
  else if ( f2 == "poly3" )
    {
      ws->var( f2 + "_prime_Nbkg" )->setVal( npoints );
    }
  else if ( f2 == "poly4" )
    {
      ws->var( f2 + "_prime_Nbkg" )->setVal( npoints );
    }
  else
    {
      std::cout << "[ERROR]: fit option not recognized. QUITTING PROGRAM" << std::endl;
      exit (EXIT_FAILURE);
    }

  //----------------------------------------
  //fit to data to obtain initial parameters
  //----------------------------------------
  //Generate dataset 
  data_toys = GenerateToys( ws->pdf( tag1 ), mgg, npoints );
  data_toys->SetName("dataToysBkgOnly");
  RooFitResult* bres2p = ws->pdf( tag2p )->fitTo( *data_toys, RooFit::Save(kTRUE), RooFit::Strategy(2), RooFit::Extended(kTRUE), RooFit::Range("Full") );
  //RooFitResult* bres2p = ws->pdf( tag2p )->fitTo( data, RooFit::Strategy(2), RooFit::Extended(kTRUE), RooFit::Save(kTRUE), RooFit::Range("low,high") );
  bres2p->SetName("fit_result_f2_prime");
  ws->import( *bres2p );
  
  RooPlot* pFrame = mgg.frame();
  pFrame->SetName("primeFitFrame");
  data.plotOn( pFrame );
  //---------------------------------
  //Plotting sideband fit f1, f2prime(copy of f2)
  //---------------------------------
  ws->pdf( tag2p )->plotOn( pFrame, RooFit::LineColor(kRed), RooFit::Range("low,high"), RooFit::NormRange("low,high") );
  ws->pdf( tag1 )->plotOn( pFrame, RooFit::LineColor(kBlue), RooFit::Range("low,high"), RooFit::NormRange("low,high") );
  ws->import( *pFrame );

  //------------------------------------------------------------------------------
  //Define and obtain initial pdf parameters for f2, using sideband fit parameters
  //------------------------------------------------------------------------------
  double dE_N1, dE_N2, dE_a1, dE_a2;//doubleExp
  double sE_N, sE_a;//singleExp
  double mE_N, mE_a, mE_m;//modExp
  double sP_N, sP_a;//singlePow
  double dP_N, dP_f, dP_a1, dP_a2;//doubleExp
  double pC, p0, p1, p2, p3, pN;//poly2,pol3;
  if ( f2 == "doubleExp" )
    {
      //dE_N1  = ws->var( f2 + "_prime_Nbkg1" )->getVal();
      //dE_N2  = ws->var( f2 + "_prime_Nbkg2" )->getVal();
      dE_N1  = ws->var( f2 + "_prime_Nbkg" )->getVal();
      dE_a1  = ws->var( f2 + "_prime_a1" )->getVal();
      dE_a2  = ws->var( f2 + "_prime_a2" )->getVal();
    }
  else if ( f2 == "singleExp" )
    {
      sE_N  = ws->var( f2 + "_prime_Nbkg" )->getVal();
      sE_a  = ws->var( f2 + "_prime_a" )->getVal();
      //sE_N  = ws->var( f1 + "_1_Nbkg" )->getVal();
      //sE_a  = ws->var( f1 + "_1_a" )->getVal();
    }
  else if ( f2 == "modExp" )
    {
      mE_N  = ws->var( f2 + "_prime_Nbkg" )->getVal();
      mE_a  = ws->var( f2 + "_prime_a" )->getVal();
      mE_m  = ws->var( f2 + "_prime_m" )->getVal();
    }
  else if ( f2 == "singlePow" )
    {
      sP_N  = ws->var( f2 + "_prime_Nbkg" )->getVal();
      sP_a  = ws->var( f2 + "_prime_a" )->getVal();
    }
  else if ( f2 == "doublePow" )
    {
      dP_N   = ws->var( f2 + "_prime_Nbkg" )->getVal();
      dP_f   = ws->var( f2 + "_prime_f" )->getVal();
      dP_a1  = ws->var( f2 + "_prime_a1" )->getVal();
      dP_a2  = ws->var( f2 + "_prime_a2" )->getVal();
    }
  else if ( f2 == "poly2" )
    {
      pN = ws->var( f2 + "_prime_Nbkg" )->getVal();
      pC = ws->var( f2 + "_prime_pC" )->getVal();
      p0 = ws->var( f2 + "_prime_p0" )->getVal();
      p1 = ws->var( f2 + "_prime_p1" )->getVal();
    }
  else if ( f2 == "poly3" )
    {
      pN = ws->var( f2 + "_prime_Nbkg" )->getVal();
      pC = ws->var( f2 + "_prime_pC" )->getVal();
      p0 = ws->var( f2 + "_prime_p0" )->getVal();
      p1 = ws->var( f2 + "_prime_p1" )->getVal();
      p2 = ws->var( f2 + "_prime_p2" )->getVal();
    }
  else if ( f2 == "poly4" )
    {
      pN = ws->var( f2 + "_prime_Nbkg" )->getVal();
      pC = ws->var( f2 + "_prime_pC" )->getVal();
      p0 = ws->var( f2 + "_prime_p0" )->getVal();
      p1 = ws->var( f2 + "_prime_p1" )->getVal();
      p2 = ws->var( f2 + "_prime_p2" )->getVal();
      p3 = ws->var( f2 + "_prime_p3" )->getVal();
    }
  else
    {
      std::cout << "[ERROR]: fit option not recognized. QUITTING PROGRAM" << std::endl;
      exit (EXIT_FAILURE);
    }
  
  bool _badFit = false;
  int _countPass = 0;
  TRandom3* r = new TRandom3(0);
  TRandom3* r2 = new TRandom3(0);
  std::cout << "ENTERING LOOP" << std::endl;
  for ( int i = 0; i < ntoys; i++ )
    {
      //-----------------------------------------------------------
      //Defining Number of signal toys; frac = S/B = 0,1,2,3,4,5...
      //-----------------------------------------------------------
      int stoys = int(frac*f1Int*npoints);
      double npointsP = r->PoissonD( npoints );
      Nbkg.setVal(npointsP);
      double stoysP   = r2->PoissonD( stoys );
      std::cout << "[INFO]: it-> " << i << " ======> stoys: " << stoysP << " Nbkg: " << npointsP << " nBkG SR: " << f1Int*npoints << std::endl;
      //-------------------------
      //Set Signal pdf paramaters
      //-------------------------
      Ns.setVal( stoysP );//Note initial paramenter is the true number of signal events
      ws->var(gaussTag + "_frac")->setVal( gausFrac );
      ws->var(gaussTag + "_mu")->setVal( gausMu );
      ws->var(gaussTag + "_sigma1")->setVal( gausSigma1 );
      ws->var(gaussTag + "_sigma2")->setVal( gausSigma2 );
      
      //-------------------------------------------
      //Fixing Signal pdf paramaters, float only Ns
      //-------------------------------------------
      ws->var(gaussTag + "_frac")->setConstant(kTRUE);
      ws->var(gaussTag + "_mu")->setConstant(kTRUE);
      ws->var(gaussTag + "_sigma1")->setConstant(kTRUE);
      ws->var(gaussTag + "_sigma2")->setConstant(kTRUE);

      //--------------------------------
      //Update f2 (test pdf) paramenters
      //--------------------------------
      //ws->var( f2 + "_2_Nbkg" )->setRange(0, 1e3);
      if ( f2 == "doubleExp" )
      	{
	  /*
	  ws->var( f2 + "_2_Nbkg1")->setVal( dE_N1 );
	  ws->var( f2 + "_2_Nbkg2")->setVal( dE_N2 );
	  ws->var( f2 + "_2_a1")->setVal( dE_a1 );
	  ws->var( f2 + "_2_a2")->setVal( dE_a2 );
	  */
	  /*
	  ws->var( f2 + "_2_Nbkg")->setVal( dE_N1 );
	  ws->var( f2 + "_2_a1")->setVal( dE_a1 );
	  ws->var( f2 + "_2_a2")->setVal( dE_a2 );
	  */
	  ws->var( tag2 + "_a1")->setVal( dE_a1 );
	  ws->var( tag2 + "_a2")->setVal( dE_a2 );
	
	}
      else if ( f2 == "singleExp" )
	{
	  ws->var( tag2 + "_a" )->setVal( sE_a );
	}
      else if ( f2 == "modExp" )
	{
	 // ws->var( f2 + "_2_Nbkg" )->setVal( mE_N );
	 // ws->var( f2 + "_2_a" )->setVal( mE_a );
	 // ws->var( f2 + "_2_m" )->setVal( mE_m );
	  ws->var( tag2 + "_a" )->setVal( mE_a );
	  ws->var( tag2 + "_m" )->setVal( mE_m );
	}
      else if ( f2 == "singlePow" )
	{
	  //ws->var( f2 + "_2_Nbkg" )->setVal( sP_N );
	  //ws->var( f2 + "_2_a" )->setVal( sP_a );
	  ws->var( tag2 + "_a" )->setVal( sP_a );
	}
      else if ( f2 == "doublePow" )
	{
	/*
	  ws->var( f2 + "_2_Nbkg" )->setVal( dP_N );
	  ws->var( f2 + "_2_f" )->setVal( dP_f );
	  ws->var( f2 + "_2_a1" )->setVal( dP_a1 );
	  ws->var( f2 + "_2_a2" )->setVal( dP_a2 );
	*/
	  ws->var( tag2 + "_f" )->setVal( dP_f );
	  ws->var( tag2 + "_a1" )->setVal( dP_a1 );
	  ws->var( tag2 + "_a2" )->setVal( dP_a2 );
	}
      else if ( f2 == "poly2" )
	{
	/*
	  ws->var( f2 + "_2_Nbkg" )->setVal( pN );
	  ws->var( f2 + "_2_pC" )->setVal( pC );
	  ws->var( f2 + "_2_p0" )->setVal( p0 );
	  ws->var( f2 + "_2_p1" )->setVal( p1 );
	*/
	  ws->var( tag2 + "_pC" )->setVal( pC );
	  ws->var( tag2 + "_p0" )->setVal( p0 );
	  ws->var( tag2 + "_p1" )->setVal( p1 );
	}
      else if ( f2 == "poly3" )
	{
	/*
	  ws->var( f2 + "_2_Nbkg" )->setVal( pN );
	  ws->var( f2 + "_2_pC" )->setVal( pC );
	  ws->var( f2 + "_2_p0" )->setVal( p0 );
	  ws->var( f2 + "_2_p1" )->setVal( p1 );
	  ws->var( f2 + "_2_p2" )->setVal( p2 );
	*/
	  ws->var( tag2 + "_pC" )->setVal( pC );
	  ws->var( tag2 + "_p0" )->setVal( p0 );
	  ws->var( tag2 + "_p1" )->setVal( p1 );
	  ws->var( tag2 + "_p2" )->setVal( p1 );
	
	}
      else if ( f2 == "poly4" )
	{
	  /*
	  ws->var( f2 + "_2_Nbkg" )->setVal( pN );
	  ws->var( f2 + "_2_pC" )->setVal( pC );
	  ws->var( f2 + "_2_p0" )->setVal( p0 );
	  ws->var( f2 + "_2_p1" )->setVal( p1 );
	  ws->var( f2 + "_2_p2" )->setVal( p2 );
	  ws->var( f2 + "_2_p3" )->setVal( p3 );
	*/
	  ws->var( tag2 + "_pC" )->setVal( pC );
	  ws->var( tag2 + "_p0" )->setVal( p0 );
	  ws->var( tag2 + "_p1" )->setVal( p1 );
	  ws->var( tag2 + "_p2" )->setVal( p1 );
	  ws->var( tag2 + "_p3" )->setVal( p1 );

	}
      else
	{
	  ws->pdf( tag2 )->fitTo( *data_toys, RooFit::Strategy(0), RooFit::Extended(kTRUE), RooFit::Range("low,high") );
	}

      delete data_toys;
      delete signal_toys;
      //------------------------------------
      //G e n e r a t i n g   B K G  t o y s
      //------------------------------------
      data_toys = GenerateToys( ws->pdf( tag1 ), mgg, npointsP );
      //-------------------------------------------
      //G e n e r a t i n g   s i g n a l   t o y s
      //-------------------------------------------
      signal_toys = GenerateToys( signalPdf, mgg, stoysP );
      //appending signal toys to data_toys (bkg toys)
      data_toys->append( *signal_toys );
      data_toys->SetName("dataToysSignalAndBkg");
      //-------------------------------------------------------------
      //S+B FIT (Ns is the only parameter floated for the signal pdf)
      //-------------------------------------------------------------
      //bres_toys = sbModel->fitTo( *data_toys, RooFit::Strategy(0), RooFit::Extended(kTRUE), RooFit::Save(kTRUE), RooFit::Range("Full") );

      //Initialize fit parameter statuses
      _status     = -1;
      _status2    = -1;
      _status3    = -1;
      _covStatus  = -1;
      _covStatus2 = -1;
      _covStatus3 = -1;

      //--------------------------------------
      //Defining Negative Log Likelihood (NLL)
      //--------------------------------------
      RooNLLVar* nll = (RooNLLVar*)sbModel->createNLL( *data_toys, RooFit::Extended(kTRUE), RooFit::Range("Full") );
      //Defininf RooMinimizer Object;
      RooMinimizer m(*nll);
      m.setStrategy(2);
      m.setPrintLevel(-1);
      m.setMaxFunctionCalls(5000);
      m.setMinimizerType("Minuit2");
      
      m.minimize("Minuit2", "Migrad");
      //m.migrad(); 
      RooFitResult* r = m.save(); 
      _status    = r->status();
      _covStatus = r->covQual();
      r->SetName("rMigrad");
      ws->import( *r );

      //m.hesse();
      m.minimize("Minuit2", "Hesse");
      RooFitResult* r2 = m.save(); 
      _status2    = r2->status();
      _covStatus2 = r2->covQual();
      r2->SetName("rHesse");
      ws->import( *r2 );

      m.minimize("Minuit2", "Migrad");
      r = m.save();
      _status    = r->status();
      _covStatus = r->covQual();
      m.minimize("Minuit2", "Hesse");
      r2 = m.save(); 
      _status2    = r2->status();
      _covStatus2 = r2->covQual();
      
      
      //if ( _status2 == -1 ) break;
      
      //m.minos();
      RooFitResult* r3 = m.save(); 
      _status3    = r3->status();
      _covStatus3 = r3->covQual();

      /*
      if( !( _status == 0 && _covStatus == 3 && _status2 == 0 && _covStatus == 3 ) )
	{
	  //_countPass++;
	  //continue;
      }
      */
      _countPass++;

      //---------------------------
      //Saving paramenters to TTree
      //---------------------------
      //_alpha_hat = ws->var( f2 + "_2_a" )->getVal();
      //_alpha_sigma = ws->var( f2 + "_2_a" )->getError();
      std::cout << "[INFO]: Getting parameters after fit" << std::endl;
      _Nbkg       = npointsP;
      _Nbkg_hat   = Nbkg.getVal();
      _Nbkg_sigma = Nbkg.getError();
      _Ns         = stoysP;
      _Ns_hat     = Ns.getVal();
      _Ns_sigma   = Ns.getError();
      
      //-----------------------
      //G e t t i n g   b i a s
      //-----------------------
      double Nsignal  = _Ns_hat;
      double Ns_Error = _Ns_sigma/Nsignal;
      bias =  (_Ns - _Ns_hat)/_Ns_sigma;
      _bias = _Ns - _Ns_hat;
      _statUn = _Ns_sigma;//tree variable
      _biasNorm = bias.getVal();//tree variable
      
      std::cout << "DEBUG DEBUG" << std::endl;
      NsignalError.setVal( Ns_Error );

      //appending values to bias dataset outputs
      data_bias.add( RooArgSet(bias) );
      data_Nse.add( RooArgSet(NsignalError) );

      //------------------------------------
      //F i l l i n g  o u t p u t   T r e e
      //------------------------------------
      std::cout << "before filling tree" << std::endl;
      //std::cout << "iteration:" << i << std::endl;
      outTree->Fill();
      //delete data_toys;
      //delete signal_toys;
      delete nll;
    }

  std::cout << "[DEBUG]: out of toys loop" << std::endl; 
  RooPlot* f_mgg = mgg.frame();
  f_mgg->SetName("toys_plot");
  f_mgg->SetTitle("");
  data_toys->plotOn( f_mgg );
  //ws->pdf( tag2 )->plotOn( f_mgg, RooFit::LineColor(kViolet), RooFit::Range("Full"), RooFit::NormRange("low,high"));
  
  //ws->pdf( tag2p )->plotOn( f_mgg, RooFit::LineColor(kBlue), RooFit::Range("Full"), RooFit::NormRange("Full"), RooFit::Normalization(npoints, RooAbsReal::NumEvent) );  
  //ws->pdf( tag1 )->plotOn( f_mgg, RooFit::LineColor(kGreen), RooFit::Range("Full"), RooFit::NormRange("Full"), RooFit::Normalization(npoints, RooAbsReal::NumEvent) );
  //Plotting background only component of s+b fit
  sbModel->plotOn( f_mgg, RooFit::LineStyle(kDashed), RooFit::LineColor(kRed), RooFit::Range("Full"), RooFit::NormRange("Full"), RooFit::Components(tag2));
  sbModel->plotOn( f_mgg, RooFit::LineColor(kBlue), RooFit::Range("Full"), RooFit::NormRange("Full"));
  
  RooPlot* f_bias = bias.frame();
  f_bias->SetName("bias_plot");
  data_bias.plotOn( f_bias );
  
  RooPlot* f_Nse = NsignalError.frame();
  f_Nse->SetName("NsignalError_plot");
  data_Nse.plotOn( f_Nse );
  
  ws->import( bias );
  ws->import( data_bias );
  ws->import( data_Nse );
  ws->import( *f_mgg );
  //ws->import( *bres_toys );
  ws->import( *f_bias );
  ws->import( *f_Nse );
  
  outName = outName + "_Tree.root";
  TFile* _fout = new TFile( outName, "recreate");
  outTree->Write();
  std::cout << "[INFO]: Wrote Bias TTree " << std::endl;
  _fout->Close();
  std::cout << "[INFO]: Bias Tree File Closed " << std::endl;
  return ws;
};

RooDataSet* GenerateToys( RooAbsPdf* pdf, RooRealVar x, int ntoys = 100 )
{
  return pdf->generate( x, ntoys);
};

RooWorkspace* MakeSideBandFitAIC_2( TTree* tree, float forceSigma, bool constrainMu, float forceMu, TString mggName, double& AIC, double& AIC_2, double& AIC_3,double& fitStatus_1, double& fitStatus_2, double& fitStatus_3, double& fitStatus_4,  TString ffName = "doubleExp")
{
  RooWorkspace* ws = new RooWorkspace( "ws", "" );
  
  RooRealVar mgg(mggName,"m_{#gamma#gamma}",103,160,"GeV");
  mgg.setBins(38);
  mgg.setRange("low", 103, 121);
  mgg.setRange("high", 129, 160);
  mgg.setRange("Full", 103, 160);

  TString tag;
  if ( ffName == "doubleExp" )
    {
      //tag = MakeDoubleExpN1N2( "sideband_fit_doubleExp", mgg, *ws );
      tag = MakeDoubleExp( "sideband_fit_doubleExp", mgg, *ws );
      std::cout << "[INFO]: Running double exponential fit" << std::endl; 
    }
  else if ( ffName == "singleExp" )
    {
      tag = MakeSingleExp( "sideband_fit_singleExp", mgg, *ws );
      std::cout << "[INFO]: Running single exponential fit" << std::endl; 
    }
  else if ( ffName == "modExp" )
    {
      tag = MakeModExp( "sideband_fit_modExp", mgg, *ws );
      std::cout << "[INFO]: Running modified exponential fit" << std::endl; 
    }
  else if ( ffName == "singlePow" )
    {
      tag = MakeSinglePow( "sideband_fit_singlePow", mgg, *ws );
      std::cout << "[INFO]: Running single pow fit" << std::endl; 
    }
  else if ( ffName == "doublePow" )
    {
      tag = MakeDoublePow( "sideband_fit_doublePow", mgg, *ws );
      //tag = MakeDoublePowN1N2( "sideband_fit_doublePow", mgg, *ws );
      std::cout << "[INFO]: Running double pow fit" << std::endl; 
    }
  else if ( ffName == "poly2" )
    {
      tag = MakePoly2( "sideband_fit_poly2", mgg, *ws );
      std::cout << "[INFO]: Running poly2 fit" << std::endl; 
    }
  else if ( ffName == "poly3" )
    {
      tag = MakePoly3( "sideband_fit_poly3", mgg, *ws );
      std::cout << "[INFO]: Running poly3 fit" << std::endl; 
    }
  else if ( ffName == "poly4" )
    {
      tag = MakePoly4( "sideband_fit_poly4", mgg, *ws );
      std::cout << "[INFO]: Running poly4 fit" << std::endl; 
    }

  else
    {
      std::cout << "[ERROR]: fit option not recognized. QUITTING PROGRAM" << std::endl;
      exit (EXIT_FAILURE);
    }

  std::cout << "====================" << std::endl;
  std::cout << "[INFO]: ENTERING FIT" << std::endl;
  std::cout << "====================" << std::endl;
  //Sideband Fit
  RooDataSet data( "data", "", RooArgSet(mgg), RooFit::Import(*tree) );
  double n = data.sumEntries(" (mGammaGamma>103 && mGammaGamma<121) || (mGammaGamma>129 && mGammaGamma<160)");
  ws->var( "sideband_fit_"+ffName+"_Nbkg")->setVal( n * 1.2);
  
  //RooFitResult* bres = ws->pdf( tag )->fitTo( data, RooFit::Strategy(2), RooFit::Extended(kTRUE), RooFit::Save(kTRUE), RooFit::Range("low,high") );
   RooNLLVar* nll = (RooNLLVar*)ws->pdf( tag )->createNLL( data, RooFit::Extended(kTRUE), RooFit::Range("low,high") );
   //Defining RooMinimizer Object;
   RooMinimizer m(*nll);
   m.setStrategy(2);
   //m.setEps(1e-4);
   //m.setMaxIterations(10000);
   //m.setMaxFunctionCalls(10000);
   m.setPrintLevel(2);
   m.minimize("Minuit2", "Migrad");

   //m.migrad(); 
   RooFitResult* bres = m.save() ; 
   //_status    = r->status();
   //_covStatus = r->covQual();
  
   fitStatus_1 = bres->status();
   fitStatus_2 = bres->covQual();
 
   m.minimize("Minuit2", "Hesse");
   RooFitResult* r2 = m.save() ; 
   //_status2    = r2->status();
   //_covStatus2 = r2->covQual();
 
//print out the status here.... 
   fitStatus_3 = r2->status();
   fitStatus_4 = r2->covQual();
  
  std::cout << "===================" << std::endl;
  std::cout << "[INFO]: LEAVING FIT" << std::endl;
  std::cout << "===================" << std::endl;
  
  bres->SetName( tag + "_b_fitres" );
  std::cout << "[INFO]: PASS FIT" << std::endl;
  //---------------------
  //g e t t i n g   n l l 
  //---------------------
  double minNll = bres->minNll();
  //RooAbsReal* nll = ws->pdf( tag )->createNLL(data, RooFit::Extended(kTRUE), RooFit::Range("low,high") );
  //RooAbsReal* nll = ws->pdf( tag )->createNLL(data, RooFit::Extended(kTRUE), RooFit::Range("Full") );
  std::cout << "nll_nll->" << nll->getVal() << std::endl;
  std::cout << "minNll->" << minNll << std::endl;
  RooArgSet* floatPars = ws->pdf( tag )->getParameters(data);
  double K = floatPars->getSize() - 1.;
  std::cout << "K -> " << K << std::endl;
  //double n = data.sumEntries(" (mgg>103 && mgg<120) || (mgg>135 && mgg<160)");

  if ( n-K-1 > 0 )
    {
      std::cout << "n -> " << n << std::endl;
      AIC = 2*minNll + 2*K + 2*K*(K+1)/(n-K-1);
      AIC_2 = 2*minNll + 2*K;// + 2*K*(K+1)/(n-K-1);
      AIC_3 = 2*minNll;// + 2*K + 2*K*(K+1)/(n-K-1);
      std::cout << "AIC: " << AIC << std::endl;
      std::cout << "AIC_2: " << AIC_2 << std::endl;
      std::cout << "AIC_3: " << AIC_3 << std::endl;
    }
  else
    {
      std::cerr << "[ERROR]: (n-K-1) zero or negative!: " << (n-K-1) << "; setting AIC to 999 " << std::endl;
      AIC   = 999.;
      AIC_2 = 999.;
      AIC_3 = 999.;
    }
  /*
  RooPlot* fns = ws->var("sideband_fit_doubleExp_a1")->frame( );
  nll->plotOn( fns, RooFit::LineColor(kBlue) );
  fns->SetName("nll_trick");
  ws->import( *fns );
  */
  ws->import( *bres );
  
  RooPlot *fmgg = mgg.frame();
  RooDataSet* dataCut = (RooDataSet*) data.reduce(RooFit::Name("dataCut"),RooFit::SelectVars(RooArgSet(mgg)),RooFit::CutRange("low"));
  RooDataSet* dataHigh = (RooDataSet*) data.reduce(RooFit::Name("dataHigh"),RooFit::SelectVars(RooArgSet(mgg)),RooFit::CutRange("high"));
  dataCut->append(*dataHigh);
  data.plotOn(fmgg,RooFit::Invisible());
  dataCut->plotOn(fmgg);
  ws->pdf( tag )->plotOn(fmgg,RooFit::LineColor(kRed), RooFit::Range("Full"), RooFit::NormRange("low,high"));
  ws->pdf( tag )->plotOn(fmgg,RooFit::LineColor(kBlue), RooFit::LineStyle(kDashed), RooFit::Range("low,high"),RooFit::NormRange("low,high"));
  
  /*
  double top_y = fmgg->GetMaximum();
  int n_g = 20;
  TGraph *grshade = new TGraph(2*n_g);
  for ( int ig = 0; ig < n_g; ig++ )
    {
      grshade->SetPoint(ig, 120., (float)ig*(top_y/(float)n_g) );
      grshade->SetPoint(n_g + ig, 135., top_y - (float)ig*(top_y/(float)n_g) );
    }
  
  grshade->SetFillStyle(3013);
  grshade->SetFillColor(16);
  grshade->Draw("f same");
  */
  fmgg->SetName( tag + "_frame" );
  ws->import( *fmgg );
  
  RooPlot* pdfFrame = mgg.frame();
  ws->pdf( tag )->plotOn( pdfFrame, RooFit::LineColor(kViolet), RooFit::Range("Full"), RooFit::NormRange("Full") );
  pdfFrame->SetName( tag+"_pdfframe" );
  ws->import( *pdfFrame );
  ws->import( mgg );

  std::cout <<ffName<<" AIC fit status:  "<< fitStatus_1 << "," << fitStatus_2 << "," << fitStatus_3 << "," << fitStatus_4 << std::endl;
  return ws;
};

RooWorkspace* SelectBinning( TH1F* mggData, TString mggName, TString f1, TString f2, int ntoys, int npoints, TString outName )
{
  TFile* fout = new TFile( outName + "_biasTree.root", "RECREATE");
  RooRandom::randomGenerator()->SetSeed( 0 );
  RooWorkspace* ws = new RooWorkspace( "ws", "" );
  
  RooRealVar mgg(mggName,"m_{#gamma#gamma}",103,160,"GeV");
  mgg.setBins(38);
  mgg.setRange("low", 103, 121);
  mgg.setRange("high", 129, 160);
  mgg.setRange("Full", 103, 160);
  //HighRes Signal Region
  mgg.setRange("sig", 121, 129);
  
  TString tag1, tag2;
  if ( f1 == "doubleExp" )
    {
      tag1 = MakeDoubleExpN1N2( f1 + "_1", mgg, *ws );
      tag2 = MakeDoubleExpN1N2( f1 + "_1_clone", mgg, *ws );
    }
  else if ( f1 == "singleExp" )
    {
      tag1 = MakeSingleExp( f1 + "_1", mgg, *ws );
      tag2 = MakeSingleExp( f1 + "_1_clone", mgg, *ws );
    }
  else if ( f1 == "modExp" )
    {
      tag1 = MakeModExp( f1 + "_1", mgg, *ws );
      tag2 = MakeModExp( f1 + "_1_clone", mgg, *ws );
    }
  else if ( f1 == "singlePow" )
    {
      tag1 = MakeSinglePow( f1 + "_1", mgg, *ws );
      tag2 = MakeSinglePow( f1 + "_1_clone", mgg, *ws );
    }
  else if ( f1 == "doublePow" )
    {
      tag1 = MakeDoublePow( f1 + "_1", mgg, *ws );
      tag2 = MakeDoublePow( f1 + "_1_clone", mgg, *ws );
    }
  else if ( f1 == "poly2" )
    {
      tag1 = MakePoly2( f1 + "_1", mgg, *ws );
      tag2 = MakePoly2( f1 + "_1_clone", mgg, *ws );
    }
  else if ( f1 == "poly3" )
    {
      tag1 = MakePoly3( f1 + "_1", mgg, *ws );
      tag2 = MakePoly3( f1 + "_1_clone", mgg, *ws );
    }
  else if ( f1 == "poly4" )
    {
      tag1 = MakePoly4( f1 + "_1", mgg, *ws );
      tag2 = MakePoly4( f1 + "_1_clone", mgg, *ws );
    }
  else
    {
      std::cout << "[ERROR]: fit option not recognized. QUITTING PROGRAM" << std::endl;
      exit (EXIT_FAILURE);
    }
  
  //-------------------
  //Creatin RooDataHist
  //-------------------
  RooDataHist data( "data", "my_data", RooArgList(mgg), mggData );
  TString totalEntriesStr = Form("(%s>%.2f && %s<%.2f)", mggName.Data(), 103., mggName.Data(), 160.);
  TString sbEntriesStr = Form("(%s>%.2f && %s<%.2f) || (%s>%.2f && %s<%.2f)", mggName.Data(), 103., mggName.Data(), 121., mggName.Data(), 129., mggName.Data(), 160.);
  //npoints = data.sumEntries( totalEntriesStr );
  int sbpoints =  data.sumEntries( sbEntriesStr );

  // Represent data in dh as pdf in x
  RooHistPdf histpdf("histpdf", "histpdf", mgg, data, 0);
  RooAbsReal* fHistInt   = histpdf.createIntegral( mgg, RooFit::NormSet(mgg), RooFit::Range("sig") );
  //mc toys dataHist
  RooDataHist* data_toys;
  
  std::cout << "=====================" << std::endl;
  std::cout << "[INFO]: total Str: " << totalEntriesStr << std::endl;
  std::cout << "[INFO]: sb Str: " << sbEntriesStr << std::endl;
  std::cout << "[INFO]: mgg variable name: " << mggName << std::endl;
  std::cout << "[INFO]: sideband entries: " << sbpoints << std::endl;
  std::cout << "[INFO]: total entries: "    << npoints << std::endl;
  std::cout << "=====================" << std::endl;
  
  TTree* biasTree = new TTree("biasTree", "Tree containing bias test information");
  double alpha_hat, alpha_true, n_hat, n_true, sigInt_hat, sigInt_true;
  double alpha_sigma, n_sigma, sigInt_sigma, sigInt_sigma2;
  double _status, _covStatus, _status2, _covStatus2, _status3, _covStatus3;
  double intTF1, intErr, intTF1_tot;
  biasTree->Branch("alpha_hat", &alpha_hat, "alpha_hat/D");
  biasTree->Branch("alpha_true", &alpha_true, "alpha_true/D");
  biasTree->Branch("alpha_sigma", &alpha_sigma, "alpha_sigma/D");
  biasTree->Branch("n_hat", &n_hat, "n_hat/D");
  biasTree->Branch("n_true", &n_true, "n_true/D");
  biasTree->Branch("n_sigma", &n_sigma, "n_sigma/D");
  biasTree->Branch("sigInt_hat", &sigInt_hat, "sigInt_hat/D");
  biasTree->Branch("sigInt_true", &sigInt_true, "sigInt_true/D");
  biasTree->Branch("sigInt_sigma", &sigInt_sigma, "sigInt_sigma/D");
  biasTree->Branch("sigInt_sigma2", &sigInt_sigma2, "sigInt_sigma2/D");
  biasTree->Branch("intTF1", &intTF1, "intTF1/D");
  biasTree->Branch("intErr", &intErr, "intErr/D");
  biasTree->Branch("intTF1_tot", &intTF1_tot, "intTF1_tot/D");
  biasTree->Branch("status", &_status,"status/D");
  biasTree->Branch("covStatus", &_covStatus,"covStatus/D");
  biasTree->Branch("status2", &_status2,"status2/D");
  biasTree->Branch("covStatus2", &_covStatus2,"covStatus2/D");
  biasTree->Branch("status3", &_status3,"status3/D");
  biasTree->Branch("covStatus3", &_covStatus3,"covStatus3/D");
  
  
  RooFitResult* bres;
  RooAbsReal* fIntegral2;
  //npoints = 1000;
  RooDataHist* data_toys2 = histpdf.generateBinned( mgg, npoints );
  ws->var("singleExp_1_clone_Nbkg")->setVal( npoints );
  RooFitResult* bres2 = ws->pdf( tag2 )->fitTo( *data_toys2, RooFit::Strategy(2), RooFit::Extended(kTRUE), RooFit::Save(kTRUE), RooFit::Range("low,high") );
  RooAbsReal* fIntTrue = ws->pdf( tag2 )->createIntegral(mgg, RooFit::NormSet(mgg), RooFit::Range("sig") );
  double alpha_clone = ws->var( f1 + "_1_clone_a")->getVal();
  
  TF1* myPdf;
  TRandom3* rnd = new TRandom3( 0 );
  //ROOT::Math::IntegratorOneDimOptions::SetDefaultIntegrator( "ADAPTIVE" );
  
  RooArgSet* paramSet = ws->pdf( tag2 )->getParameters( RooArgSet(mgg) );
  myPdf = ws->pdf( tag2 )->asTF( RooArgList(mgg), RooArgList(*paramSet) );
  //TMatrixDSym covMatrix = bres2->covarianceMatrix();
  TMatrixDSym covMatrix = bres2->correlationMatrix();
  std::cout << "Number Of Elements: " << covMatrix.GetNoElements() << std::endl;
  /*const double* pData = covMatrix.GetMatrixArray();
  for ( int j = 0; j < covMatrix.GetNoElements(); j++ )
    {
      std::cout << "par " << j << " = " << pData[j] << std::endl;
    }
  
  double* params = myPdf->GetParameters();
  */
  //sigInt_true = myPdf->Integral( 103, 160, 1e-15 );
  //sigInt_true = fIntTrue->getVal();
  alpha_true  = alpha_clone;
  double normTrueInt = fIntTrue->getVal();
  double* params;
  for ( int i = 0; i < ntoys; i++ )
    {
      n_true = rnd->PoissonD( (double)npoints );
      //n_true = (double)npoints;//avoid poisson fluctuations
      sigInt_true = n_true*normTrueInt;
      data_toys = ws->pdf( tag2 )->generateBinned( mgg, n_true );
      /*
      std::cout << "===========================" << std::endl;
      std::cout << "[INFO]: Setting N_bkg-> " << npoints << " , ntrue: " << n_true << "; and alpha-> " << alpha_clone << std::endl;
      std::cout << "===========================" << std::endl;
      */
      /*
      ws->var( f1 + "_1_Nbkg" )->setVal( n_true );
      ws->var( f1 + "_1_a" )->setVal( alpha_clone );
      bres = ws->pdf( tag1 )->fitTo( *data_toys, RooFit::Strategy(0), RooFit::Extended(kTRUE), RooFit::Save(kTRUE), RooFit::Range("low,high") );
      */
      _status = -1;
      _covStatus = -1;
      _status2 = -1;
      _covStatus2 = -1;
      _status3 = -1;
      _covStatus3 = -1;

      ws->var( f1 + "_1_Nbkg" )->setVal( n_true );
      ws->var( f1 + "_1_a" )->setVal( alpha_clone );
      //RooNLLVar* nll = (RooNLLVar*)ws->pdf( tag1 )->createNLL( *data_toys, RooFit::Extended(kTRUE), RooFit::Range("low,high") );
      RooNLLVar* nll = (RooNLLVar*)ws->pdf( tag1 )->createNLL( *data_toys, RooFit::Extended(kTRUE), RooFit::Range("Full") );
      RooMinimizer m(*nll);
      //m.fit("mhvr0");
      //ws->var( f1 + "_1_Nbkg" )->setVal( n_true );
      //ws->var( f1 + "_1_a" )->setVal( alpha_clone );
      m.migrad(); 
      RooFitResult* r = m.save() ; 
      _status    = r->status();
      _covStatus = r->covQual();
      
      m.hesse(); 
      RooFitResult* r2 = m.save() ; 
      _status2    = r2->status();
      _covStatus2 = r2->covQual();
      
      m.minos();
      RooFitResult* r3 = m.save() ; 
      _status3    = r3->status();
      _covStatus3 = r3->covQual();
      
      fIntegral2 = ws->pdf( tag1 )->createIntegral(mgg, RooFit::NormSet(mgg), RooFit::Range("sig") );
      RooAbsReal* f2int = ws->pdf( tag1 )->createIntegral(mgg, RooFit::Range("sig") );
      RooAbsReal* f3int = ws->pdf( tag1 )->createIntegral(mgg, RooFit::Range("Full") );
      RooAbsReal* f4int = ws->pdf( tag1 )->createIntegral(mgg, RooFit::NormSet(mgg), RooFit::Range("Full") );

      paramSet = ws->pdf( tag1 )->getParameters( RooArgSet(mgg) );
      myPdf = ws->pdf( tag1 )->asTF( RooArgList(mgg), RooArgList(*paramSet) );
      /*covMatrix = bres->covarianceMatrix();*/
      covMatrix = r3->covarianceMatrix();
      params = myPdf->GetParameters();
      //Getting Integrals
      intTF1     = fIntegral2->getVal();
      //intErr     = myPdf->IntegralError( 103., 160., params, covMatrix.GetMatrixArray(), 1e-14 );
      //intTF1_tot = myPdf->Integral( 103., 160., 1e-15 );

      /*
	std::cout << "=======================" << i << "==========================" << std::endl;
      std::cout << "Int RooFit Normalized --> " << fIntegral2->getVal() << std::endl;
      std::cout << "Int TF1 normalized --> " << intTF1/intTF1_tot << std::endl;
      std::cout << "Int RooFit --> " << f2int->getVal() << std::endl;
      std::cout << "Int TF1 --> " << intTF1 << std::endl;
      std::cout << "Int RooFit Total --> " << f3int->getVal() << std::endl;
      std::cout << "Int RooFit Total Normalized --> " << f4int->getVal() << std::endl;
      std::cout << "Int TF1 Total --> " << intTF1_tot << std::endl;
      std::cout << "=================================================" << std::endl;
      */
      //alpha
      alpha_hat   = ws->var( f1 + "_1_a" )->getVal();
      alpha_sigma = ws->var( f1 + "_1_a" )->getError();
      //n
      n_hat       = ws->var( f1 + "_1_Nbkg" )->getVal();
      n_sigma     = ws->var( f1 + "_1_Nbkg" )->getError();
      //signal integral
      sigInt_hat = intTF1*n_hat;
      //Single Exp Uncertainty Calculation
      //122.08, 128.92
      //getting correlation matrix parameters from correlation matrix
      TMatrixDSym corrMatrix = r3->correlationMatrix();
      const double* pData = corrMatrix.GetMatrixArray();
      //propagation of uncertainty
      double eta    = exp(-alpha_hat*122.08) - exp(-alpha_hat*128.92);
      double etaMod = 128.92*exp(-alpha_hat*128.92) - 122.08*exp(-alpha_hat*122.08);
      double xi     = exp(-alpha_hat*103.) - exp(-alpha_hat*160.);
      double xiMod  = 103.*exp(-alpha_hat*103.) - 160.*exp(-alpha_hat*160.);
      double dIdN = eta/xi;
      double dIdAlpha = n_hat*( eta*xiMod/(xi*xi) + etaMod/xi );
      double sigmaI = sqrt(dIdN*dIdN*n_sigma*n_sigma + dIdAlpha*dIdAlpha*alpha_sigma*alpha_sigma + dIdN*dIdAlpha*pData[1]*n_sigma*alpha_sigma);

      //std::cout << "dIdN: " << dIdN << " , dIdAlpha: " << dIdAlpha << std::endl;
      //std::cout << "Int: " << sigInt_hat << " +/- " << sigmaI << std::endl;
      sigInt_sigma = sigmaI;
      sigInt_sigma2 = sqrt(dIdN*dIdN*n_sigma*n_sigma + dIdAlpha*dIdAlpha*alpha_sigma*alpha_sigma);
      biasTree->Fill();
    }
  //--------
  //INTEGRAL
  //--------
  RooAbsReal* fIntegral  = ws->pdf( tag1 )->createIntegral(mgg);
  
  
  std::cout << "test Int: " << fIntegral->getVal() << std::endl;
  std::cout << "test Int2: " << fIntegral2->getVal() << std::endl;
  std::cout << "hist Int: " << fHistInt->getVal() << std::endl;
  bres2->SetName( tag2 + "_b_fitRes");
  //ws->import( *bres );

  RooPlot* fmgg = mgg.frame();
  data_toys2->plotOn( fmgg );
  ws->pdf( tag2 )->plotOn( fmgg, RooFit::LineColor(kBlue), RooFit::Range("Full"), RooFit::NormRange("low,high") );
  fmgg->SetName( tag2 + "frame" );
  ws->import( *fmgg );

  
  biasTree->Write();
  ws->Write("my_ws");
  fout->Close();
  return ws;
};
