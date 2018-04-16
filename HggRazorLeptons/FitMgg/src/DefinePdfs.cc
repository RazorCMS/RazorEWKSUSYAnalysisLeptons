//C++ INCLUDES
#include <vector>
//ROOT INCLUDES
#include <TTree.h>
#include <TLatex.h>
#include <TString.h>
#include <TFile.h>
#include <TH1D.h>
#include <TF1.h>
#include <TCanvas.h>
#include <TGraph.h>
#include <TGraphErrors.h>
#include <TRandom3.h>
#include <TLegend.h>
#include <TMath.h>
#include <TBox.h>
//ROOFIT INCLUDES
#include <RooWorkspace.h>
#include <RooDataSet.h>
#include <RooRealVar.h>
#include <RooExponential.h>
#include <RooAddPdf.h>
#include <RooGaussian.h>
#include <RooFitResult.h>
#include <RooPlot.h>
#include <RooExtendPdf.h>
#include <RooStats/SPlot.h>
#include <RooStats/ModelConfig.h>
#include <RooGenericPdf.h>
#include <RooFormulaVar.h>
#include <RooBernstein.h>
#include <RooChebychev.h>
#include <RooMinuit.h>
//LOCAL INCLUDES
#include "DefinePdfs.hh"
#include "CustomPdfs.hh"

TString MakeSingleGaussNE( TString tag, RooRealVar& mgg, RooWorkspace& w )
{
  //------------------------------
  //C r e a t e  V a r i a b l e s
  //------------------------------
  RooRealVar* mu     = new RooRealVar( tag+"_SG_mu", "#mu", 125, "" );
  RooRealVar* sigma = new RooRealVar( tag+"_SG_sigma", "#sigma", 1.0, "" );
  mu->setConstant(kFALSE);
  sigma->setConstant(kFALSE);
  
  //------------------
  //C r e a t e  p.d.f
  //------------------
  TString pdf_name   = tag+"_SG";
  RooGaussian* gauss    = new RooGaussian( tag+"_SG", "", mgg, *mu, *sigma );
  
  w.import( *gauss );
  
  return pdf_name;
};

TString MakeSingleGauss( TString tag, RooRealVar& mgg, RooWorkspace& w )
{
  //------------------------------
  //C r e a t e  V a r i a b l e s
  //------------------------------
  RooRealVar* mu     = new RooRealVar( tag+"_SG_mu", "#mu", 125, "" );
  RooRealVar* sigma = new RooRealVar( tag+"_SG_sigma", "#sigma", 1.0, "" );
  mu->setConstant(kFALSE);
  sigma->setConstant(kFALSE);
  
  RooRealVar* Ns     = new RooRealVar( tag+"_SG_Ns", "N_{s}", 1e5, "events");
  Ns->setConstant(kFALSE);
  //------------------
  //C r e a t e  p.d.f
  //------------------
  RooGaussian* gauss    = new RooGaussian( tag+"_SG", "", mgg, *mu, *sigma );
  
  //------------------------------------
  //C r e a t e   E x t e n d e d  p.d.f
  //------------------------------------
  TString ex_pdf_name          = tag+"_SG_ext";
  RooAddPdf* ex_doublegauss = new RooAddPdf( ex_pdf_name, "extSG", RooArgList(*gauss), RooArgList(*Ns) );
  w.import( *ex_doublegauss );
  
  return ex_pdf_name;
};


TString MakeDoubleGauss( TString tag, RooRealVar& mgg, RooWorkspace& w )
{
  //------------------------------
  //C r e a t e  V a r i a b l e s
  //------------------------------
  RooRealVar* mu     = new RooRealVar( tag+"_gauss_mu", "#mu", 125, "" );
  RooRealVar* sigma1 = new RooRealVar( tag+"_gauss_sigma1", "#sigma_{1}", 1.0, "" );
  RooRealVar* sigma2 = new RooRealVar( tag+"_gauss_sigma2", "#sigma_{2}", 3.0, "" );
  mu->setConstant(kFALSE);
  sigma1->setConstant(kFALSE);
  sigma2->setConstant(kFALSE);
  
  RooRealVar* frac   = new RooRealVar( tag+"_frac", "frac", 0.5, .0, 1.0 );
  
  RooRealVar* Ns     = new RooRealVar( tag+"_gauss_Ns", "N_{s}", 1e5, "events");
  Ns->setConstant(kFALSE);
  //Ns->setRange(0,1e5);
  //------------------
  //C r e a t e  p.d.f
  //------------------
  RooGaussian* gauss1    = new RooGaussian( tag+"_gauss1", "", mgg, *mu, *sigma1 );
  RooGaussian* gauss2    = new RooGaussian( tag+"_gauss2", "", mgg, *mu, *sigma2 );
  RooAddPdf* doublegauss = new RooAddPdf( tag + "_doublegauss", "", RooArgList( *gauss1, *gauss2 ), *frac );

  //------------------------------------
  //C r e a t e   E x t e n d e d  p.d.f
  //------------------------------------
  TString ex_pdf_name          = tag+"_doublegauss_ext";
  RooAddPdf* ex_doublegauss = new RooAddPdf( ex_pdf_name, "extDgauss", RooArgList(*doublegauss), RooArgList(*Ns) );
  w.import( *ex_doublegauss );
  
  return ex_pdf_name;
};

TString MakeDoubleGaussNE( TString tag, RooRealVar& mgg, RooWorkspace& w, bool _globalScale )
{
  //------------------------------
  //C r e a t e  V a r i a b l e s
  //------------------------------
  RooRealVar* mu     = new RooRealVar( tag+"_DGS_mu", "#mu", 125, "" );
  RooRealVar* sigma1 = new RooRealVar( tag+"_DGS_sigma1", "#sigma_{1}", 1.0, "" );
  RooRealVar* sigma2 = new RooRealVar( tag+"_DGS_sigma2", "#sigma_{2}", 3.0, "" );
  mu->setConstant(kFALSE);
  sigma1->setConstant(kFALSE);
  sigma2->setConstant(kFALSE);
  
  RooRealVar* frac   = new RooRealVar( tag+"_DGS_frac", "frac", 0.5, .0, 1.0 );
  
  //------------------
  //C r e a t e  p.d.f
  //------------------
  RooGaussian* gauss1    = new RooGaussian( tag+"_DGS_G1", "", mgg, *mu, *sigma1 );
  RooGaussian* gauss2    = new RooGaussian( tag+"_DGS_G2", "", mgg, *mu, *sigma2 );
  TString pdf_name       = tag+"_DGS";
  RooAddPdf* doublegauss = new RooAddPdf( pdf_name, "", RooArgList( *gauss1, *gauss2 ), *frac );
  w.import( *doublegauss );
  
  return pdf_name;
};

TString MakeFullDoubleGauss( TString tag, RooRealVar& mgg, RooWorkspace& w )
{
 //------------------------------
  //C r e a t e  V a r i a b l e s
  //------------------------------
  //DGF: Double Gaussian Full
  RooRealVar* mu1     = new RooRealVar( tag + "_DG_mu1", "#mu1", 125, "" );
  RooRealVar* mu2     = new RooRealVar( tag + "_DG_mu2", "#mu2", 125, "" );
  RooRealVar* sigma1 = new RooRealVar( tag  + "_DG_sigma1", "#sigma_{1}", 1.0, "" );
  RooRealVar* sigma2 = new RooRealVar( tag  + "_DG_sigma2", "#sigma_{2}", 3.0, "" );
  mu1->setConstant(kFALSE);
  mu2->setConstant(kFALSE);
  sigma1->setConstant(kFALSE);
  sigma2->setConstant(kFALSE);
  
  RooRealVar* frac   = new RooRealVar( tag + "_DG_frac", "frac", 0.5, .0, 1.0 );
  
  RooRealVar* Ns     = new RooRealVar( tag + "_DG_Ns", "N_{s}", 1e5, "events");
  Ns->setConstant(kFALSE);
  //Ns->setRange(0,1e5);
  //------------------
  //C r e a t e  p.d.f
  //------------------
  RooGaussian* gauss1    = new RooGaussian( tag + "_G1", "", mgg, *mu1, *sigma1 );
  RooGaussian* gauss2    = new RooGaussian( tag + "_G2", "", mgg, *mu2, *sigma2 );
  RooAddPdf* doublegauss = new RooAddPdf( tag   + "_SummedG1G2", "", RooArgList( *gauss1, *gauss2 ), *frac );

  //------------------------------------
  //C r e a t e   E x t e n d e d  p.d.f
  //------------------------------------
  TString ex_pdf_name          = tag + "_DG";
  RooAddPdf* ex_doublegauss = new RooAddPdf( ex_pdf_name, "extDgauss", RooArgList(*doublegauss), RooArgList(*Ns) );
  w.import( *ex_doublegauss );
  
  return ex_pdf_name;
};

TString MakeFullDoubleGaussNE( TString tag, RooRealVar& mgg, RooWorkspace& w, bool _globalScale, bool _categoryScale, TString category )
{
  //------------------------------
  //C r e a t e  V a r i a b l e s
  //------------------------------
  //DGF: Double Gaussian Full
  RooRealVar* mu1     = new RooRealVar( tag + "_DG_mu1", "#mu1", 125, "" );
  RooRealVar* mu2     = new RooRealVar( tag + "_DG_mu2", "#mu2", 125, "" );
  RooRealVar* sigma1 = new RooRealVar( tag  + "_DG_sigma1", "#sigma_{1}", 1.0, "" );
  RooRealVar* sigma2 = new RooRealVar( tag  + "_DG_sigma2", "#sigma_{2}", 3.0, "" );
  mu1->setConstant(kFALSE);
  mu2->setConstant(kFALSE);
  sigma1->setConstant(kFALSE);
  sigma2->setConstant(kFALSE);
  
  RooRealVar* frac   = new RooRealVar( tag + "_DG_frac", "frac", 0.5, .0, 1.0 );
  //------------------
  //C r e a t e  p.d.f
  //------------------
  RooGaussian* gauss1;
  RooGaussian* gauss2; 
  if ( _globalScale && _categoryScale )
    {
      RooRealVar* muGlobal = new RooRealVar( "mu_Global", "#mu_{global}", 0, "" );
      RooRealVar* muCat    = new RooRealVar( category+"_mu_Global", "#mu_{"+category+"}", 0, "" );
      RooFormulaVar* mu1G  = new RooFormulaVar( tag + "_DG_mu1G", "#mu_{1} - #mu_{g} - #mu_{"+category+"}", "(@0-@1-@2)", RooArgList(*mu1, *muGlobal, *muCat) );
      RooFormulaVar* mu2G  = new RooFormulaVar( tag + "_DG_mu2G", "#mu_{2} - #mu_{g} - #mu_{"+category+"}", "(@0-@1-@2)", RooArgList(*mu2, *muGlobal, *muCat) );
      gauss1 = new RooGaussian( tag + "_G1", "", mgg, *mu1G, *sigma1 );
      gauss2 = new RooGaussian( tag + "_G2", "", mgg, *mu2G, *sigma2 );
    }
  else if ( _globalScale && !_categoryScale )
    {
      RooRealVar* muGlobal = new RooRealVar( "mu_Global", "#mu_{g}", 0, "" );
      RooFormulaVar* mu1G  = new RooFormulaVar( tag + "_DG_mu1G", "#mu_{1} - #mu_{g}", "(@0-@1)", RooArgList(*mu1, *muGlobal) );
      RooFormulaVar* mu2G  = new RooFormulaVar( tag + "_DG_mu2G", "#mu_{2} - #mu_{g}", "(@0-@1)", RooArgList(*mu2, *muGlobal) );
      gauss1 = new RooGaussian( tag + "_G1", "", mgg, *mu1G, *sigma1 );
      gauss2 = new RooGaussian( tag + "_G2", "", mgg, *mu2G, *sigma2 );
    }
  else if ( !_globalScale && _categoryScale )
    {
      RooRealVar* muCat    = new RooRealVar( category+"_mu_Global", "#mu_{"+category+"}", 0, "" );
      RooFormulaVar* mu1G  = new RooFormulaVar( tag + "_DG_mu1G", "#mu_{1} - #mu_{"+category+"}", "(@0-@1)", RooArgList(*mu1, *muCat) );
      RooFormulaVar* mu2G  = new RooFormulaVar( tag + "_DG_mu2G", "#mu_{2} - #mu_{"+category+"}", "(@0-@1)", RooArgList(*mu2, *muCat) );
      gauss1 = new RooGaussian( tag + "_G1", "", mgg, *mu1G, *sigma1 );
      gauss2 = new RooGaussian( tag + "_G2", "", mgg, *mu2G, *sigma2 );
    }
  else
    {
      gauss1 = new RooGaussian( tag + "_G1", "", mgg, *mu1, *sigma1 );
      gauss2 = new RooGaussian( tag + "_G2", "", mgg, *mu2, *sigma2 );
    }

  //----------------------------
  //Define out tag and RooAddPdf
  //----------------------------
  TString pdf_name          = tag + "_DG";
  RooAddPdf* doublegauss = new RooAddPdf( pdf_name, "", RooArgList( *gauss1, *gauss2 ), *frac );
  w.import( *doublegauss );
  
  return pdf_name;
};

TString MakeDoubleCB( TString tag, RooRealVar& mgg, RooWorkspace& w )
{
  //------------------------------
  //C r e a t e  V a r i a b l e s
  //------------------------------
  //DCB: Double Crystal Ball
  RooRealVar* mu     = new RooRealVar( tag + "_DCB_muCB", "#mu_{CB}", 125, "" );
  RooRealVar* sigma  = new RooRealVar( tag + "_DCB_sigmaCB", "#sigma_{CB}", 1.1, "" );
  RooRealVar* alpha1   = new RooRealVar( tag  + "_DCB_alpha1", "#alpha_{1}", 1.5, "" );
  RooRealVar* alpha2   = new RooRealVar( tag  + "_DCB_alpha2", "#alpha_{2}", 2.8, "" );
  RooRealVar* n1       = new RooRealVar( tag  + "_DCB_n1", "#n_{1}", 3.6, "" );
  RooRealVar* n2       = new RooRealVar( tag  + "_DCB_n2", "#n_{2}", 1.0, "" );
  mu->setConstant(kFALSE);
  sigma->setConstant(kFALSE);
  alpha1->setConstant(kFALSE);
  alpha1->setRange(0, 1000);
  alpha2->setConstant(kFALSE);
  alpha2->setRange(0, 1000);
  n1->setConstant(kFALSE);
  n1->setRange(0, 1000);
  n2->setConstant(kFALSE);
  n2->setRange(0, 1000);
  
  RooRealVar* Ns     = new RooRealVar( tag + "_DCB_Ns", "N_{s}", 1e5, "events");
  Ns->setConstant(kFALSE);
  
  RooDoubleCB* dCB = new RooDoubleCB( tag + "DCB_pdf", "", mgg, *mu, *sigma, *alpha1, *n1, *alpha2, *n2 );
  
  //------------------------------------
  //C r e a t e   E x t e n d e d  p.d.f
  //------------------------------------
  TString ex_pdf_name          = tag + "_DCB";
  RooAddPdf* ex_dCB = new RooAddPdf( ex_pdf_name, "extDCB", RooArgList(*dCB), RooArgList(*Ns) );
  w.import( *ex_dCB );
  
  return ex_pdf_name;
};

TString MakeDoubleCBNE( TString tag, RooRealVar& mgg, RooWorkspace& w, bool _globalScale, bool _categoryScale, TString category )
{
  //------------------------------
  //C r e a t e  V a r i a b l e s
  //------------------------------
  //DCB: Double Crystal Ball
  RooRealVar* mu       = new RooRealVar( tag + "_DCB_muCB", "#mu_{CB}", 125, "" );
  RooRealVar* sigma    = new RooRealVar( tag + "_DCB_sigmaCB", "#sigma_{CB}", 1.1, "" );
  RooRealVar* alpha1   = new RooRealVar( tag  + "_DCB_alpha1", "#alpha_{1}", 1.5, "" );
  RooRealVar* alpha2   = new RooRealVar( tag  + "_DCB_alpha2", "#alpha_{2}", 2.8, "" );
  RooRealVar* n1       = new RooRealVar( tag  + "_DCB_n1", "#n_{1}", 3.6, "" );
  RooRealVar* n2       = new RooRealVar( tag  + "_DCB_n2", "#n_{2}", 1.0, "" );
  mu->setConstant(kFALSE);
  sigma->setConstant(kFALSE);
  alpha1->setConstant(kFALSE);
  alpha1->setRange(0, 1000);
  alpha2->setConstant(kFALSE);
  alpha2->setRange(0, 1000);
  n1->setConstant(kFALSE);
  n1->setRange(0, 1000);
  n2->setConstant(kFALSE);
  n2->setRange(0, 1000);

  TString pdf_name = tag + "_DCB";
  RooDoubleCB* dCB;
  if ( _globalScale && _categoryScale )
    {
      RooRealVar* muGlobal = new RooRealVar( "mu_Global", "#mu_{global}", 0, "" );
      RooRealVar* muCat    = new RooRealVar( category+"_mu_Global", "#mu_{"+category+"}", 0, "" );
      RooFormulaVar* mggp  = new RooFormulaVar( tag + "_DG_mggp", "m_{gg} - #mu_{g} - #mu_{"+category+"}", "(@0-@1-@2)", RooArgList(mgg, *muGlobal, *muCat) );
      dCB = new RooDoubleCB( pdf_name , "", *mggp, *mu, *sigma, *alpha1, *n1, *alpha2, *n2 );
    }
  else if ( _globalScale && !_categoryScale )
    {
      RooRealVar* muGlobal = new RooRealVar( "mu_Global", "#mu_{g}", 0, "" );
      RooFormulaVar* mggp  = new RooFormulaVar( tag + "_DG_muG", "m_{gg} - #mu_{g}", "(@0-@1)", RooArgList(mgg, *muGlobal) );
      dCB = new RooDoubleCB( pdf_name , "", *mggp, *mu, *sigma, *alpha1, *n1, *alpha2, *n2 );
    }
  else if ( !_globalScale && _categoryScale )
    {
      RooRealVar* muCat    = new RooRealVar( category+"_mu_Global", "#mu_{"+category+"}", 0, "" );
      RooFormulaVar* mggp  = new RooFormulaVar( tag + "_DG_muG", "mgg - #mu_{"+category+"}", "(@0-@1)", RooArgList(mgg, *muCat) );
      dCB = new RooDoubleCB( pdf_name , "", *mggp, *mu, *sigma, *alpha1, *n1, *alpha2, *n2 );
    }
  else
    {
      dCB = new RooDoubleCB( pdf_name , "", mgg, *mu, *sigma, *alpha1, *n1, *alpha2, *n2 );
    }

  
  w.import( *dCB );
  
  return pdf_name;
};

//----------------
//
//-----------------
TString MakeDoubleCBInterpolate( TString tag, RooRealVar& mgg, RooWorkspace& w )
{
   //------------------------------
  //C r e a t e  V a r i a b l e s
  //------------------------------
  //DCB: Double Crystal Ball Interpolation
  RooRealVar* mass     = new RooRealVar( tag + "_DCBI_mass", "#mass_{CB}", 750, "" );
  mass->setConstant(kFALSE);
    
  
  RooRealVar* Ns     = new RooRealVar( tag + "_DCBI_Ns", "N_{s}", 1e5, "events");
  Ns->setConstant(kFALSE);
  
  //RooDoubleCBInterpolate* dCB = new RooDoubleCBInterpolate( tag + "DCBI_pdf", "", mgg, *mass );
  RooIntepolateDSCB_W0p014_Spin0_EBEE* dCB = new RooIntepolateDSCB_W0p014_Spin0_EBEE( tag + "DCBI_pdf", "", mgg, *mass );
  
  //------------------------------------
  //C r e a t e   E x t e n d e d  p.d.f
  //------------------------------------
  TString ex_pdf_name          = tag + "_DCBI";
  RooAddPdf* ex_dCB = new RooAddPdf( ex_pdf_name, "extDCBI", RooArgList(*dCB), RooArgList(*Ns) );
  w.import( *ex_dCB );
  
  return ex_pdf_name;
};


//-------------------------
//2015 Interpolation
//-------------------------
TString MakeDoubleCBInterpolateNE( TString tag, RooRealVar& mgg, RooWorkspace& w, TString category )
{
  RooRealVar* mass     = new RooRealVar( tag + "_DCBI_mass", "#mass_{CB}", 750, "" );
  mass->setConstant(kFALSE);
  
  TString pdf_name = tag + "_DCBI";
  
  if ( category == "EBEB" )
    {
      RooRealVar* muGlobal = new RooRealVar( "mu_Global_EBEB", "#mu_{g}", 0, "" );
      RooFormulaVar* mggp  = new RooFormulaVar( tag + "_DG_muG", "m_{gg} - #mu_{g}", "(@0-@1)", RooArgList(mgg, *muGlobal) );
      RooIntepolateDSCB_W0p014_Spin0_EBEB* dCB = new RooIntepolateDSCB_W0p014_Spin0_EBEB( pdf_name , "", *mggp, *mass );
      w.import( *dCB );
      return pdf_name;
    }
  else if ( category == "EBEE" )
    {
      RooRealVar* muGlobal = new RooRealVar( "mu_Global_EBEE", "#mu_{g}", 0, "" );
      RooFormulaVar* mggp  = new RooFormulaVar( tag + "_DG_muG", "m_{gg} - #mu_{g}", "(@0-@1)", RooArgList(mgg, *muGlobal) );
      RooIntepolateDSCB_W0p014_Spin0_EBEE* dCB = new RooIntepolateDSCB_W0p014_Spin0_EBEE( pdf_name , "", *mggp, *mass );
      w.import( *dCB );
      
      return pdf_name;
    }
  
  std::cerr << "category: " <<  category << " NOT DEFINED for HM Analysis, terminating" << std::endl;
  exit (EXIT_FAILURE);
  return "";
};

//-------------------------
//2016 Interpolation
//-------------------------
TString MakeDoubleCBInterpolateNE2016( TString tag, RooRealVar& mgg, RooWorkspace& w, TString category )
{
  RooRealVar* mass     = new RooRealVar( tag + "_DCBI_mass", "#mass_{CB}", 750, "" );
  mass->setConstant(kFALSE);
  
  TString pdf_name = tag + "_DCBI";
  
  if ( category == "EBEB" )
    {
      RooRealVar* muGlobal = new RooRealVar( "mu_Global_EBEB", "#mu_{g}", 0, "" );
      RooFormulaVar* mggp  = new RooFormulaVar( tag + "_DG_muG", "m_{gg} - #mu_{g}", "(@0-@1)", RooArgList(mgg, *muGlobal) );
      RooIntepolateDSCB_W0p014_Spin0_EBEB_2016* dCB = new RooIntepolateDSCB_W0p014_Spin0_EBEB_2016( pdf_name , "", *mggp, *mass );
      w.import( *dCB );
      return pdf_name;
    }
  else if ( category == "EBEE" )
    {
      RooRealVar* muGlobal = new RooRealVar( "mu_Global_EBEE", "#mu_{g}", 0, "" );
      RooFormulaVar* mggp  = new RooFormulaVar( tag + "_DG_muG", "m_{gg} - #mu_{g}", "(@0-@1)", RooArgList(mgg, *muGlobal) );
      RooIntepolateDSCB_W0p014_Spin0_EBEE_2016* dCB = new RooIntepolateDSCB_W0p014_Spin0_EBEE_2016( pdf_name , "", *mggp, *mass );
      w.import( *dCB );
      
      return pdf_name;
    }
  
  std::cerr << "category: " <<  category << " NOT DEFINED for HM Analysis, terminating" << std::endl;
  exit (EXIT_FAILURE);
  return "";
};


TString MakeDoubleExp(TString tag, RooRealVar& mgg, RooWorkspace& w)
{
  //------------------------------
  //C r e a t e  V a r i a b l e s
  //------------------------------
  RooRealVar* alpha1 = new RooRealVar( tag + "_a1", "#alpha_{1}", 0.25, "" );
  RooRealVar* alpha2 = new RooRealVar( tag + "_a2", "#alpha_{2}", 0.25, "" );
  alpha1->setConstant(kFALSE);
  alpha2->setConstant(kFALSE);
  //alpha1->setRange(-100,0);
  //alpha2->setRange(-100,0);
  //alpha1->setMax(0.0);
  //alpha2->setMax(0.0);

  //--------------------------------------------
  //Square variables to avoid rising exponential
  //--------------------------------------------
  RooFormulaVar* asq1 = new RooFormulaVar( tag + "_a1Sq", "#alpha^{2}_{1}", "-1*@0*@0", *alpha1);
  RooFormulaVar* asq2 = new RooFormulaVar( tag + "_a2Sq", "#alpha^{2}_{2}", "-1*@0*@0", *alpha2);
  RooRealVar* frac    = new RooRealVar( tag+"_frac", "frac", 0.5, .0, 1.0 );
  RooRealVar* Nbkg    = new RooRealVar( tag+"_Nbkg", "N_{bkg}", 100, "events" );
  Nbkg->setConstant(kFALSE);
  
  //------------------
  //C r e a t e  p.d.f
  //------------------
  RooExponential* exp1    = new RooExponential( tag+"_exp1", "", mgg, *asq1 );
  RooExponential* exp2    = new RooExponential( tag+"_exp2", "", mgg, *asq2 );
  //RooExponential* exp1    = new RooExponential( tag+"_exp1", "", mgg, *alpha1 );
  //RooExponential* exp2    = new RooExponential( tag+"_exp2", "", mgg, *alpha2 );
  RooAddPdf* doubleExp = new RooAddPdf( tag + "_doubleExp", "", RooArgList( *exp1, *exp2 ), *frac );

  //------------------------------------
  //C r e a t e   E x t e n d e d  p.d.f
  //------------------------------------
  TString ex_pdf_name          = tag+"_doubleExp_ext";
  RooAddPdf* ext_doubleExp = new RooAddPdf( ex_pdf_name,"", RooArgList( *doubleExp ), RooArgList( *Nbkg ) );
  w.import( *ext_doubleExp );
  
  return ex_pdf_name;
};

TString MakeDoubleExpNE(TString tag, RooRealVar& mgg, RooWorkspace& w)
{
  //------------------------------
  //C r e a t e  V a r i a b l e s
  //------------------------------
  RooRealVar* alpha1 = new RooRealVar( tag + "_doubleExp_a1", "#alpha_{1}", 0.04, "" );
  RooRealVar* alpha2 = new RooRealVar( tag + "_doubleExp_a2", "#alpha_{2}", 0.06, "" );
  alpha1->setConstant(kFALSE);
  alpha2->setConstant(kFALSE);
  //alpha1->setRange(-100,0);
  //alpha2->setRange(-100,0);
  //alpha1->setMin(0.0);
  //alpha2->setMin(0.0);

  //--------------------------------------------
  //Square variables to avoid rising exponential
  //--------------------------------------------
  RooFormulaVar* asq1 = new RooFormulaVar( tag + "_doubleExp_a1Sq", "#alpha^{2}_{1}", "-1*@0*@0", *alpha1);
  RooFormulaVar* asq2 = new RooFormulaVar( tag + "_doubleExp_a2Sq", "#alpha^{2}_{2}", "-1*@0*@0", *alpha2);
  RooRealVar* frac    = new RooRealVar( tag+"_doubleExp_frac", "frac", 0.5, .0, 1.0 );
  RooRealVar* Nbkg    = new RooRealVar( tag+"_doubleExp_Nbkg", "N_{bkg}", 10, "events" );
  Nbkg->setConstant(kFALSE);
  
  //------------------
  //C r e a t e  p.d.f
  //------------------
  RooExponential* exp1    = new RooExponential( tag+"_doubleExp_exp1", "", mgg, *asq1 );
  RooExponential* exp2    = new RooExponential( tag+"_doubleExp_exp2", "", mgg, *asq2 );
  //RooExponential* exp1    = new RooExponential( tag+"_exp1", "", mgg, *alpha1 );
  //RooExponential* exp2    = new RooExponential( tag+"_exp2", "", mgg, *alpha2 );
  
  TString pdfname          = tag+"_doubleExp";
  RooAddPdf* doubleExp = new RooAddPdf( pdfname, "", RooArgList( *exp1, *exp2 ), *frac );

  w.import( *doubleExp );
  
  return pdfname;
};


TString MakeDoubleExpN1N2( TString tag, RooRealVar& mgg, RooWorkspace& w )
{
  //RooRealVar* a1 = new RooRealVar( tag + "_a1", "", 0.6,-1.,1.);
  //RooRealVar* a2 = new RooRealVar( tag + "_a2", "", 0.4/150,-1/150.,1/150.);

  RooRealVar* a1 = new RooRealVar( tag + "_a1", "", 0.6, "");
  RooRealVar* a2 = new RooRealVar( tag + "_a2", "", 0.6, "");
  a1->setConstant(kFALSE);
  a2->setConstant(kFALSE);
  
  RooFormulaVar* a1sq = new RooFormulaVar( tag + "_a1sq","","-1*@0*@0", *a1);
  RooFormulaVar* a2sq = new RooFormulaVar( tag + "_a2sq","","-1*@0*@0", *a2);
  
  RooRealVar* NBkg1 = new RooRealVar( tag + "_Nbkg1","",10,"");
  RooRealVar* NBkg2 = new RooRealVar( tag + "_Nbkg2","",1,"");
  NBkg1->setConstant(kFALSE);
  NBkg2->setConstant(kFALSE);

  RooFormulaVar* NBkg1Sq = new RooFormulaVar( tag + "_Nbkg1Sq","","@0*@0", *NBkg1);
  RooFormulaVar* NBkg2Sq = new RooFormulaVar( tag + "_Nbkg2Sq","","@0*@0", *NBkg2);

  RooExponential* e1 = new RooExponential( tag + "_e1","", mgg, *a1sq);
  RooExponential* e2 = new RooExponential( tag + "_e2","", mgg, *a2sq);

  TString pdfName = tag+"_pdf_dExp_N1N2";
  RooAddPdf* pdf = new RooAddPdf( pdfName,"", RooArgList( *e1, *e2), RooArgList( *NBkg1Sq, *NBkg2Sq) );
  w.import( *pdf );
  return pdfName;
};

TString MakeSingleExp( TString tag, RooRealVar& mgg, RooWorkspace& w )
{
  RooRealVar* a = new RooRealVar( tag + "_a", "", -0.06, "a.u"); 
  a->setConstant(kFALSE);
  //RooFormulaVar* asq = new RooFormulaVar( tag + "_aSq","","-1*@0*@0", *a);
  RooRealVar* Nbkg = new RooRealVar( tag + "_Nbkg","",10., "events");
  Nbkg->setConstant(kFALSE);
  RooExponential* se = new RooExponential( tag + "_se","", mgg, *a);
  
  TString pdfName = tag+"_pdf_sExp_ext";
  RooAddPdf* ext_singleExp = new RooAddPdf( pdfName,"", RooArgList( *se ), RooArgList( *Nbkg ) );
  w.import( *ext_singleExp );
  return pdfName;
};

TString MakeSingleExpNE( TString tag, RooRealVar& mgg, RooWorkspace& w )
{
  RooRealVar* a = new RooRealVar( tag + "_sExp_a", "", -0.06, "a.u"); 
  a->setConstant(kFALSE);
  TString pdfName = tag+"_sExp";
  RooExponential* se = new RooExponential( pdfName,"", mgg, *a);
  w.import( *se );
  return pdfName;
};

TString MakeHMDiphoton( TString tag, RooRealVar& mgg, RooWorkspace& w )
{
  TString pdfName = tag + "_HMDiphoton_ext";
  RooRealVar* a = new RooRealVar( pdfName + "_a", "", -0.06, "a.u"); 
  a->setConstant(kFALSE);
  RooRealVar* b = new RooRealVar( pdfName + "_b", "", -0.06, "a.u"); 
  b->setConstant(kFALSE);
  //b->setRange(-5,5);

  RooRealVar* Nbkg = new RooRealVar( pdfName + "_Nbkg","",10., "events");
  Nbkg->setConstant(kFALSE);
  
  RooHMDiphoton* hmDiphoton = new RooHMDiphoton( pdfName + "_HMDiphoton", "", mgg, *a, *b );
  
 
  RooAddPdf* ext_HMDiphoton = new RooAddPdf( pdfName,"", RooArgList( *hmDiphoton ), RooArgList( *Nbkg ) );
  w.import( *ext_HMDiphoton );
  return pdfName;
};

TString MakeHMDiphotonNE( TString tag, RooRealVar& mgg, RooWorkspace& w )
{
  TString pdfName = tag + "_HMDiphoton";
  RooRealVar* a = new RooRealVar( pdfName + "_a", "", -0.06, "a.u"); 
  a->setConstant(kFALSE);
  RooRealVar* b = new RooRealVar( pdfName + "_b", "", -0.06, "a.u"); 
  b->setConstant(kFALSE);
  //b->setRange(-5,5);

  
  RooHMDiphoton* hmDiphoton = new RooHMDiphoton( pdfName, "", mgg, *a, *b );
  
  w.import( *hmDiphoton );
  return pdfName;
};

TString MakeModExp(TString tag, RooRealVar& mgg,RooWorkspace& w)
{
  RooRealVar *alpha = new RooRealVar(tag+"_a","#alpha",0.06, "");
  alpha->setConstant(kFALSE);
  alpha->setMin(0.0);
  //RooFormulaVar* aSq = new RooFormulaVar( tag + "_aSq","","-1*@0*@0", *alpha);

  RooRealVar *m = new RooRealVar(tag+"_m","m", 1, "");
  m->setMin(0.0);
  m->setConstant(kFALSE);
  //RooFormulaVar* mSq = new RooFormulaVar( tag + "_mSq","","@0*@0", *m);
  
  RooRealVar *Nbkg   = new RooRealVar(tag+"_Nbkg","N_{bkg}", 10, "events");  
  Nbkg->setConstant(kFALSE);

  //Define as exp(-(alpha^2)*x^(m^2)), to avoid infinite integrals and unphysical pdfs
  //RooGenericPdf *mexp = new RooGenericPdf(tag+"_mexp","mod_exp","exp(@0*(@1^@2))",RooArgList(*aSq,mgg,*mSq));
  RooGenericPdf *mexp = new RooGenericPdf(tag+"_mexp","mod_exp","exp(-1*@0*(@1^@2))",RooArgList(*alpha,mgg,*m));
  
  TString pdfName = tag+"_mexp_ext";
  RooAddPdf* modExp_Ext = new RooAddPdf( pdfName, "modExp", RooArgList(*mexp), RooArgList(*Nbkg) );

  w.import( *modExp_Ext );
  return pdfName;
};

TString MakeModExpNE(TString tag, RooRealVar& mgg,RooWorkspace& w)
{
  RooRealVar *alpha = new RooRealVar(tag+"_mexp_a","#alpha",0.06, "");
  alpha->setConstant(kFALSE);
  alpha->setMin(0.0);
  RooFormulaVar* aSq = new RooFormulaVar( tag + "_mexp_aSq","","-1*@0*@0", *alpha);

  RooRealVar *m = new RooRealVar(tag+"_mexp_m","m", 1., "");
  m->setMin(0.0);
  m->setConstant(kFALSE);
  //RooFormulaVar* mSq = new RooFormulaVar( tag + "_mSq","","@0*@0", *m);

  TString pdfName = tag+"_mexp";
  //Define as exp(-(alpha^2)*x^(m^2)), to avoid infinite integrals and unphysical pdfs
  //RooGenericPdf *mexp = new RooGenericPdf(tag+"_mexp","mod_exp","exp(@0*(@1^@2))",RooArgList(*aSq,mgg,*mSq));
  RooGenericPdf *mexp = new RooGenericPdf(tag+"_mexp","mod_exp","exp(@0*(@1^@2))",RooArgList(*aSq,mgg,*m));
  w.import( *mexp );
  return pdfName;
};

TString MakeSinglePow(TString tag, RooRealVar& mgg,RooWorkspace& w) 
{
  RooRealVar *alpha  = new RooRealVar(tag+"_a","#alpha",-1);
  alpha->setConstant(kFALSE);
  //RooFormulaVar* asq = new RooFormulaVar( tag + "_aSq","","-1*@0*@0", *alpha);
  RooRealVar *Nbkg    = new RooRealVar(tag+"_Nbkg","N_{bkg}",10, "events");
  Nbkg->setConstant(kFALSE);

  RooGenericPdf *pow = new RooGenericPdf(tag+"_spow","","@0^@1",RooArgList(mgg,*alpha));
  //RooGenericPdf *pow = new RooGenericPdf(tag+"_spow","","@0^@1",RooArgList(mgg,*asq));
  TString pdfName     = tag+"_spow_ext";
  w.import( *(new RooAddPdf( pdfName,"", RooArgList(*pow), RooArgList(*Nbkg) )) );
  return pdfName;
};

TString MakeSinglePowNE(TString tag, RooRealVar& mgg,RooWorkspace& w) 
{
  RooRealVar *alpha  = new RooRealVar(tag+"_spow_a","#alpha",-1);
  alpha->setConstant(kFALSE);
  //RooFormulaVar* asq = new RooFormulaVar( tag + "_aSq","","-1*@0*@0", *alpha);

  TString pdfName     = tag+"_spow";
  RooGenericPdf *pow = new RooGenericPdf( pdfName, "", "@0^@1", RooArgList(mgg,*alpha));
  //RooGenericPdf *pow = new RooGenericPdf(tag+"_spow","","@0^@1",RooArgList(mgg,*asq));
  
  w.import( *pow );
  return pdfName;
};

TString MakeDoublePow(TString tag, RooRealVar& mgg,RooWorkspace& w)
{
  RooRealVar *alpha1  = new RooRealVar(tag+"_a1","#alpha_{1}",-1.0,"");
  RooRealVar *alpha2  = new RooRealVar(tag+"_a2","#alpha_{2}",-2.0,"");
  alpha1->setConstant(kFALSE);
  alpha2->setConstant(kFALSE);
  //alpha1->setRange(-100, 0);
  //alpha2->setRange(-100, 0);
  alpha1->setMax(0.0);
  alpha2->setMax(0.0);
  RooFormulaVar* asq1 = new RooFormulaVar( tag + "_aSq1","","-1*@0*@0", *alpha1);
  RooFormulaVar* asq2 = new RooFormulaVar( tag + "_aSq2","","-1*@0*@0", *alpha2);
  
  RooRealVar *f       = new RooRealVar(tag+"_f","f",0.5, 0.0, 1.0);
  RooRealVar *Nbkg    = new RooRealVar(tag+"_Nbkg","N_{bkg}",10,"events");
  Nbkg->setConstant(kFALSE);
  
  RooGenericPdf *pow1 = new RooGenericPdf(tag+"_dpow_pow1","","@0^@1",RooArgList(mgg,*alpha1));
  RooGenericPdf *pow2 = new RooGenericPdf(tag+"_dpow_pow2","","@0^@1",RooArgList(mgg,*alpha2));
  //RooGenericPdf *pow1 = new RooGenericPdf(tag+"_dpow_pow1","","@0^@1",RooArgList(mgg,*asq1));
  //RooGenericPdf *pow2 = new RooGenericPdf(tag+"_dpow_pow2","","@0^@1",RooArgList(mgg,*asq2));

  TString pdfName = tag+"_dpow_ext";
  RooAddPdf *add      = new RooAddPdf( tag+"_dpow","",*pow1,*pow2,*f);  
  w.import( *(new RooAddPdf( pdfName,"", RooArgList(*add), RooArgList(*Nbkg) )) );
  
  return pdfName;
};

TString MakeDoublePowNE(TString tag, RooRealVar& mgg,RooWorkspace& w)
{
  RooRealVar *alpha1  = new RooRealVar(tag+"_dpow_a1","#alpha_{1}",-1.0,"");
  RooRealVar *alpha2  = new RooRealVar(tag+"_dpow_a2","#alpha_{2}",-2.0,"");
  alpha1->setConstant(kFALSE);
  alpha2->setConstant(kFALSE);
  //alpha1->setRange(-100, 0);
  //alpha2->setRange(-100, 0);
  alpha1->setMax(0.0);
  alpha2->setMax(0.0);
  RooFormulaVar* asq1 = new RooFormulaVar( tag + "_dpow_aSq1","","-1*@0*@0", *alpha1);
  RooFormulaVar* asq2 = new RooFormulaVar( tag + "_dpow_aSq2","","-1*@0*@0", *alpha2);
  
  RooRealVar *f       = new RooRealVar(tag+"_dpow_f","f",0.5, 0.0, 1.0);
  RooRealVar *Nbkg    = new RooRealVar(tag+"_dpow_Nbkg","N_{bkg}",10,"events");
  Nbkg->setConstant(kFALSE);
  
  RooGenericPdf *pow1 = new RooGenericPdf(tag+"_dpow_pow1","","@0^@1",RooArgList(mgg,*alpha1));
  RooGenericPdf *pow2 = new RooGenericPdf(tag+"_dpow_pow2","","@0^@1",RooArgList(mgg,*alpha2));
  //RooGenericPdf *pow1 = new RooGenericPdf(tag+"_dpow_pow1","","@0^@1",RooArgList(mgg,*asq1));
  //RooGenericPdf *pow2 = new RooGenericPdf(tag+"_dpow_pow2","","@0^@1",RooArgList(mgg,*asq2));

  TString pdfName = tag+"_dpow";
  RooAddPdf *add      = new RooAddPdf( pdfName,"",*pow1,*pow2,*f);  
  w.import( *add); //*(new RooAddPdf( pdfName,"", RooArgList(*add), RooArgList(*Nbkg) )) );
  
  return pdfName;
};


TString MakeDoublePowN1N2(TString tag, RooRealVar& mgg,RooWorkspace& w)
{
  RooRealVar *alpha1  = new RooRealVar(tag+"_a1","#alpha_{1}",-1,"");
  RooRealVar *alpha2  = new RooRealVar(tag+"_a2","#alpha_{2}",-1,"");
  alpha1->setConstant(kFALSE);
  alpha2->setConstant(kFALSE);
  RooFormulaVar* alpha1sq = new RooFormulaVar( tag + "_alpha1sq","","-1*@0*@0", *alpha1);
  RooFormulaVar* alpha2sq = new RooFormulaVar( tag + "_alpha2sq","","-1*@0*@0", *alpha2);
  
  RooRealVar* NBkg1 = new RooRealVar( tag + "_Nbkg1","",10,"");
  RooRealVar* NBkg2 = new RooRealVar( tag + "_Nbkg2","",1,"");
  NBkg1->setConstant(kFALSE);
  NBkg2->setConstant(kFALSE);
  
  RooFormulaVar* NBkg1Sq = new RooFormulaVar( tag + "_Nbkg1Sq","","@0*@0", *NBkg1);
  RooFormulaVar* NBkg2Sq = new RooFormulaVar( tag + "_Nbkg2Sq","","@0*@0", *NBkg2);
  
  RooGenericPdf *pow1 = new RooGenericPdf(tag+"_dpow_pow1","","@0^@1",RooArgList(mgg,*alpha1sq));
  RooGenericPdf *pow2 = new RooGenericPdf(tag+"_dpow_pow2","","@0^@1",RooArgList(mgg,*alpha2sq));

  TString pdfName = tag+"_dpow_ext";
  RooAddPdf* pdf = new RooAddPdf( pdfName,"", RooArgList( *pow1, *pow2), RooArgList( *NBkg1Sq, *NBkg2Sq) );
  w.import( *pdf );
  return pdfName;
};

TString MakePoly2(TString tag, RooRealVar& mgg,RooWorkspace& w)
{
  //RooRealVar *pC = new RooRealVar(tag+"_pC","C",0.5, -10,10);
  //RooRealVar *p0 = new RooRealVar(tag+"_p0","p_0",0.3, -10,10);
  //RooRealVar *p1 = new RooRealVar(tag+"_p1","p_1",0.27, -10,10);
  RooRealVar *pC = new RooRealVar(tag+"_pC","C",0.5,""); 
  pC->setConstant(kFALSE);
  RooRealVar *p0 = new RooRealVar(tag+"_p0","p_0",0.3,"");
  p0->setConstant(kFALSE);
  RooRealVar *p1 = new RooRealVar(tag+"_p1","p_1",0.27,"");
  p1->setConstant(kFALSE);
  
  RooRealVar *Nbkg   = new RooRealVar(tag+"_Nbkg","N_{bkg}",10,"events");
  Nbkg->setConstant(kFALSE);
  
  RooFormulaVar *pCmod = new RooFormulaVar(tag+"_pCmod","@0*@0",*pC);
  RooFormulaVar *p0mod = new RooFormulaVar(tag+"_p0mod","@0*@0",*p0);
  RooFormulaVar *p1mod = new RooFormulaVar(tag+"_p1mod","@0*@0",*p1);

  RooBernstein* bern = new RooBernstein(tag+"_pol2","",mgg,RooArgList(*pCmod,*p0mod,*p1mod));
  TString pdfName = tag+"_pol2_ext";
  w.import(*(new RooAddPdf( pdfName,"", RooArgList(*bern),RooArgList(*Nbkg))));
  
  return pdfName;
};

TString MakePoly2NE(TString tag, RooRealVar& mgg,RooWorkspace& w)
{
  /*
  RooRealVar *pC = new RooRealVar(tag+"_pol2_pC","C",0.5, 0,1);
  RooRealVar *p0 = new RooRealVar(tag+"_pol2_p0","p_0",0.3, 0,1);
  RooRealVar *p1 = new RooRealVar(tag+"_pol2_p1","p_1",0.27, 0,1);
  */
  RooRealVar *pC = new RooRealVar(tag+"_pol2_pC","C",0.5,"");
  pC->setConstant(kFALSE);
  RooRealVar *p0 = new RooRealVar(tag+"_pol2_p0","p_0",0.3,"");
  p0->setConstant(kFALSE);
  RooRealVar *p1 = new RooRealVar(tag+"_pol2_p1","p_1",0.27,"");
  p1->setConstant(kFALSE);
  RooRealVar *Nbkg   = new RooRealVar(tag+"_pol2_Nbkg","N_{bkg}",10,"events");
  Nbkg->setConstant(kFALSE);
  
  RooFormulaVar *pCmod = new RooFormulaVar(tag+"_pol2_pCmod","@0*@0",*pC);
  RooFormulaVar *p0mod = new RooFormulaVar(tag+"_pol2_p0mod","@0*@0",*p0);
  RooFormulaVar *p1mod = new RooFormulaVar(tag+"_pol2_p1mod","@0*@0",*p1);

  TString pdfName = tag+"_pol2";
  RooBernstein* bern = new RooBernstein(pdfName,"",mgg,RooArgList(*pCmod,*p0mod,*p1mod));
  w.import(*bern);//(new RooAddPdf( pdfName,"", RooArgList(*bern),RooArgList(*Nbkg))));
  
  return pdfName;
};


TString MakePoly3(TString tag, RooRealVar& mgg,RooWorkspace& w)
{
  RooRealVar *pC = new RooRealVar(tag+"_pC","C",1,-100,100);
  RooRealVar *p0 = new RooRealVar(tag+"_p0","p_0",1.0,-100,100);
  RooRealVar *p1 = new RooRealVar(tag+"_p1","p_1",0,-100,100);
  RooRealVar *p2 = new RooRealVar(tag+"_p2","p_2",5,-100,100);

  /*
  RooRealVar *pC = new RooRealVar(tag+"_pC","C",1, "");
  pC->setConstant(kFALSE);
  RooRealVar *p0 = new RooRealVar(tag+"_p0","p_0",1.0, "");
  p0->setConstant(kFALSE);
  RooRealVar *p1 = new RooRealVar(tag+"_p1","p_1",0,"");
  p1->setConstant(kFALSE);
  RooRealVar *p2 = new RooRealVar(tag+"_p2","p_2",5,"");
  p2->setConstant(kFALSE);
  */

  RooRealVar *Nbkg   = new RooRealVar(tag+"_Nbkg","N_{bkg}",10,"events");
  Nbkg->setConstant(kFALSE);
  
  RooFormulaVar *pCmod = new RooFormulaVar(tag+"_pCmod","@0*@0",*pC);
  RooFormulaVar *p0mod = new RooFormulaVar(tag+"_p0mod","@0*@0",*p0);
  RooFormulaVar *p1mod = new RooFormulaVar(tag+"_p1mod","@0*@0",*p1);
  RooFormulaVar *p2mod = new RooFormulaVar(tag+"_p2mod","@0*@0",*p2);
  
  RooBernstein* bern = new RooBernstein(tag+"_pol3","",mgg,RooArgList(*pCmod,*p0mod,*p1mod,*p2mod));
  //RooBernstein* bern = new RooBernstein(tag+"_pol3","",mgg,RooArgList(*pC,*p0,*p1,*p2));
  
  TString pdfName = tag+"_pol3_ext";
  w.import(*(new RooAddPdf( pdfName,"", RooArgList(*bern),RooArgList(*Nbkg))));
  
  return pdfName;
};
TString MakePoly3NE(TString tag, RooRealVar& mgg,RooWorkspace& w)
{
  /*RooRealVar *pC = new RooRealVar(tag+"_pol3_pC","C",1,-100,100);
  RooRealVar *p0 = new RooRealVar(tag+"_pol3_p0","p_0",1.0,-100,100);
  RooRealVar *p1 = new RooRealVar(tag+"_pol3_p1","p_1",0,-100,100);
  RooRealVar *p2 = new RooRealVar(tag+"_pol3_p2","p_2",5,-100,100);
  RooRealVar *Nbkg   = new RooRealVar(tag+"_pol3_Nbkg","N_{bkg}",10,"events");
  */
  RooRealVar *pC = new RooRealVar(tag+"_pol3_pC","C",1, "");
  pC->setConstant(kFALSE);
  RooRealVar *p0 = new RooRealVar(tag+"_pol3_p0","p_0",1.0, "");
  p0->setConstant(kFALSE);
  RooRealVar *p1 = new RooRealVar(tag+"_pol3_p1","p_1",0,"");
  p1->setConstant(kFALSE);
  RooRealVar *p2 = new RooRealVar(tag+"_pol3_p2","p_2",5,"");
  p2->setConstant(kFALSE);
    
  RooFormulaVar *pCmod = new RooFormulaVar(tag+"_pol3_pCmod","@0*@0",*pC);
  RooFormulaVar *p0mod = new RooFormulaVar(tag+"_pol3_p0mod","@0*@0",*p0);
  RooFormulaVar *p1mod = new RooFormulaVar(tag+"_pol3_p1mod","@0*@0",*p1);
  RooFormulaVar *p2mod = new RooFormulaVar(tag+"_pol3_p2mod","@0*@0",*p2);
  
  TString pdfName = tag+"_pol3";
  RooBernstein* bern = new RooBernstein(pdfName,"",mgg,RooArgList(*pCmod,*p0mod,*p1mod,*p2mod));
  //RooBernstein* bern = new RooBernstein(pdfName,"",mgg,RooArgList(*pC,*p0,*p1,*p2));
  
  w.import(*bern);//(new RooAddPdf( pdfName,"", RooArgList(*bern),RooArgList(*Nbkg))));
  
  return pdfName;
};

TString MakePoly4(TString tag, RooRealVar& mgg,RooWorkspace& w)
{
  RooRealVar *pC = new RooRealVar(tag+"_pC","C",1,-100,100);
  RooRealVar *p0 = new RooRealVar(tag+"_p0","p_0",1.0,-100,100);
  RooRealVar *p1 = new RooRealVar(tag+"_p1","p_1",0,-100,100);
  RooRealVar *p2 = new RooRealVar(tag+"_p2","p_2",5,-100,100);
  RooRealVar *p3 = new RooRealVar(tag+"_p3","p_3",5,-100,100);
  RooRealVar *Nbkg   = new RooRealVar(tag+"_Nbkg","N_{bkg}",10,"events");
  Nbkg->setConstant(kFALSE);
  
  RooFormulaVar *pCmod = new RooFormulaVar(tag+"_pCmod","@0*@0",*pC);
  RooFormulaVar *p0mod = new RooFormulaVar(tag+"_p0mod","@0*@0",*p0);
  RooFormulaVar *p1mod = new RooFormulaVar(tag+"_p1mod","@0*@0",*p1);
  RooFormulaVar *p2mod = new RooFormulaVar(tag+"_p2mod","@0*@0",*p2);
  RooFormulaVar *p3mod = new RooFormulaVar(tag+"_p3mod","@0*@0",*p3);
  
  RooBernstein* bern = new RooBernstein(tag+"_pol4","",mgg,RooArgList(*pCmod,*p0mod,*p1mod,*p2mod,*p3mod));
  
  TString pdfName = tag+"_pol4_ext";
  w.import(*(new RooAddPdf( pdfName,"", RooArgList(*bern),RooArgList(*Nbkg))));
  
  return pdfName;
};
TString MakePoly4NE(TString tag, RooRealVar& mgg,RooWorkspace& w)
{
  RooRealVar *pC = new RooRealVar(tag+"_pol4_pC","C",1,-100,100);
  RooRealVar *p0 = new RooRealVar(tag+"_pol4_p0","p_0",1.0,-100,100);
  RooRealVar *p1 = new RooRealVar(tag+"_pol4_p1","p_1",0,-100,100);
  RooRealVar *p2 = new RooRealVar(tag+"_pol4_p2","p_2",5,-100,100);
  RooRealVar *p3 = new RooRealVar(tag+"_pol4_p3","p_3",5,-100,100);
  RooRealVar *Nbkg   = new RooRealVar(tag+"_pol4_Nbkg","N_{bkg}",10,"events");
  Nbkg->setConstant(kFALSE);
  
  RooFormulaVar *pCmod = new RooFormulaVar(tag+"_pol4_pCmod","@0*@0",*pC);
  RooFormulaVar *p0mod = new RooFormulaVar(tag+"_pol4_p0mod","@0*@0",*p0);
  RooFormulaVar *p1mod = new RooFormulaVar(tag+"_pol4_p1mod","@0*@0",*p1);
  RooFormulaVar *p2mod = new RooFormulaVar(tag+"_pol4_p2mod","@0*@0",*p2);
  RooFormulaVar *p3mod = new RooFormulaVar(tag+"_pol4_p3mod","@0*@0",*p3);
  
  TString pdfName = tag+"_pol4";
  RooBernstein* bern = new RooBernstein(pdfName,"",mgg,RooArgList(*pCmod,*p0mod,*p1mod,*p2mod,*p3mod));
  
  w.import(*bern);//(new RooAddPdf( pdfName,"", RooArgList(*bern),RooArgList(*Nbkg))));
  
  return pdfName;
};
