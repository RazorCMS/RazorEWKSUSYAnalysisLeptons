#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <assert.h>
//ROOT INCLUDES
#include <TFile.h>
#include <TROOT.h>
#include <TCanvas.h>
#include <TColor.h>
#include <TF1.h>
#include <TIterator.h>
#include <TMath.h>
#include <RooArgSet.h>
#include <RooAbsArg.h>
#include <RooAbsCollection.h>
#include <RooAbsReal.h>
#include <RooAbsPdf.h>
#include <RooRealVar.h>
#include <RooFitResult.h>
#include <RooWorkspace.h>
#include <RooRandom.h>
#include <RooPlot.h>
#include <RooDataSet.h>
//LOCAL INCLUDES
#include "HggRazorSystematics.hh"
#include "CommandLineInput.hh"
#include "DefinePdfs.hh"

const bool _debug = true;

float GetNobs( std::string fname, int bin, std::string cat = "highpt" );

float GetNs( std::string fname, int bin, std::string cat = "highpt" );
float GetNsErr( std::string fname, int bin, std::string cat = "highpt" );
//
float GetSMH( std::string fname, int bin, std::string cat = "highpt" );
float GetSMHErr( std::string fname, int bin, std::string cat = "highpt" );
float GetSMH_PF( std::string fname, int bin, std::string cat = "highpt" );//postfit b-only
float GetSMHErr_PF( std::string fname, int bin, std::string cat = "highpt" );//postfit b-only

float GetSMH_SB( std::string fname, int bin, std::string cat = "highpt" );//postfit s+b
float GetSMHErr_SB( std::string fname, int bin, std::string cat = "highpt" );//postfit s+b

float GetNbkg( std::string fname, std::string f1, int bin, bool _err = false, std::string cat = "highpt" );
float GetErrorFromToys(RooWorkspace *ws, RooFitResult *fr, TString pdfName, 
        unsigned int ntoys = 1000, int binNum = 0, bool plotBkgFuncs = false);

//----------------------------------------------                                                                                                                             
//Load Binning                                                                                                                                                               
//----------------------------------------------                                                                                                                             
std::vector<float*> SetBinning(std::vector<Bin> bins, std::string category)
{

  std::vector<float*> myVec;
  for(int i=0; i<bins.size(); ++i) {
    float *tmpbin = new float[5];
    if (bins[i].box == category) {
      tmpbin[0] = bins[i].x1;
      tmpbin[1] = bins[i].y1;
      tmpbin[2] = bins[i].x2;
      tmpbin[3] = bins[i].y2;
      tmpbin[4] = bins[i].bin;
      myVec.push_back(tmpbin);
    }
  }

  return myVec;
};



//----------------
//Static Variables
//----------------
float HggRazorSystematics::NR_kf = 1.0;
int   HggRazorSystematics::n_PdfSys = 60;

float HighRes_SF = 1.0/1.1834218302;
float LowRes_SF  = 1./0.8841933224;

int main( int argc, char* argv[] )
{

  gROOT->Reset();
  gErrorIgnoreLevel = kWarning;

  std::map<Bin, std::string> myMap;
  std::map<std::string, Bin> myMap2;
  
  std::vector<Bin> binVector;
  //std::ifstream input( "data/HggRazor2016Binning.txt", std::fstream::in );
  //std::ifstream input( "data/HggRazor2016Binning_ICHEP.txt", std::fstream::in );
  std::ifstream input( "data/HggRazor2016Binning_Moriond.txt", std::fstream::in );
  
  if ( input.is_open() )
    {
      float x1, x2, y1, y2;
      int binN;
      std::string box, f1;
      while ( input.good() )
	{
	  input >> binN >> x1 >> x2 >> y1 >> y2 >> box >> f1;
	  if ( input.eof() ) break;
	  Bin mybin;
	  mybin.bin = binN;
	  mybin.f1 = f1;
	  mybin.box = box;
	  mybin.x1 = x1;
	  mybin.x2 = x2;
	  mybin.y1 = y1;
	  mybin.y2 = y2;
	  std::stringstream ss;
	  ss << box << "_" << x1 << "-" << x2 << "_" << y1 << "-" << y2;
	  binVector.push_back(mybin);
	  if ( myMap.find( mybin ) == myMap.end() ) myMap[mybin] = f1;
	  if ( myMap2.find( ss.str() ) == myMap2.end() ) myMap2[ss.str()] = mybin;
	}
    }
  else
    {
      std::cout << "Unable to open binning lookup table" << std::endl;
    }

  for ( auto tmp : myMap2 )
    {
      std::cout << tmp.first << " " << tmp.second.f1 << std::endl;
    }
  
  //-----------------
  //Selection TString
  //-----------------
  std::string categoryMode = ParseCommandLine( argc, argv, "-category=" );
  if (  categoryMode == "" )
    {
      std::cerr << "[ERROR]: please provide the category. Use --category=<highpt,hzbb,highres,lowres>" << std::endl;
      return -1;
    }

  //------------------------
  //fit result directory
  //------------------------
  std::string fitResultDir = ParseCommandLine( argc, argv, "-fitResultDir=" );
  if (  fitResultDir == "" )
    {
      std::cerr << "[ERROR]: please provide a fit result directory. For example, use --fitResultDir=/afs/cern.ch/work/c/cpena/public/CMSSW_7_6_3/src/RazorEWKSUSYAnalysis/HggRazor/PlottingAndSystematic" << std::endl;
      return -1;
    }
  std::cout << "[INFO] : Using fitResultDir = " << fitResultDir << "\n";

  
  std::vector<float*> myVectBinning;
  myVectBinning = SetBinning(binVector, categoryMode );

  TH2Poly* nominal = new TH2Poly("nominal_SMH", "", 150, 10000, 0, 1 );
  for ( auto tmp : myVectBinning ) nominal->AddBin( tmp[0], tmp[1], tmp[2], tmp[3] );

  std::cout << "\\begin{table*}[h]\n\\begin{center}\n\\caption{b-only vs approximation is observed.}\n\\small\n\\begin{tabular}{|ccccc|}\n\\hline";
  
  std::cout << "\nBin        & Category & nominal &  b-only fit & approximation \\\\\n\\hline\n";
  for ( auto tmp: myVectBinning )
    {
      int bin   = nominal->FindBin( tmp[0]+10, tmp[1]+0.0001 );
      //----------------------------
      //Key string to find bin
      //----------------------------
      std::stringstream ss;
      ss << categoryMode << "_" << tmp[0] << "-" << tmp[2] << "_" << tmp[1] << "-" << tmp[3];


      //------------------------
      //combine Workspace file
      //------------------------
      std::stringstream ws_fn;
      ws_fn << fitResultDir << "/HggRazorWorkspace_bin" << myMap2[ss.str()].bin << ".root";

      float Nobs = GetNobs( ws_fn.str(),  myMap2[ss.str()].bin, categoryMode );
      //std::cout << "Nobs: " << Nobs << std::endl;
      //-------------------------
      //fitresult filename
      //-------------------------
      std::stringstream ss_fn;
      ss_fn << fitResultDir << "/mlfit_bin" << myMap2[ss.str()].bin << ".root";

      float Ns = GetNs( ss_fn.str(),  myMap2[ss.str()].bin, categoryMode );
      float NsErr = GetNsErr( ss_fn.str(),  myMap2[ss.str()].bin, categoryMode );
      
      float Nbkg = GetNbkg( ss_fn.str(),  myMap2[ss.str()].f1, myMap2[ss.str()].bin, false, categoryMode );
      float NbkgErr = GetNbkg( ss_fn.str(),  myMap2[ss.str()].f1, myMap2[ss.str()].bin, true, categoryMode );
      
      //--------------
      //Get prefit SMH
      //--------------
      float Nsmh = GetSMH( ss_fn.str(),  myMap2[ss.str()].bin, categoryMode );
      float NsmhErr = GetSMHErr( ss_fn.str(),  myMap2[ss.str()].bin, categoryMode );

      //----------------------
      //Get postfit b-only SMH
      //----------------------
      float Nsmh_pf = GetSMH_PF( ss_fn.str(),  myMap2[ss.str()].bin, categoryMode );
      float NsmhErr_pf = GetSMHErr_PF( ss_fn.str(),  myMap2[ss.str()].bin, categoryMode );

      //-------------------
      //Get postfit b_b SMH
      //-------------------
      float Nsmh_sb = GetSMH_SB( ss_fn.str(),  myMap2[ss.str()].bin, categoryMode );
      float NsmhErr_sb = GetSMHErr_SB( ss_fn.str(),  myMap2[ss.str()].bin, categoryMode );

      //-------------------------------------------------------------
      // Use Cristian's Formula for postfit (b-only) SMH contribution
      //-------------------------------------------------------------
      //float smh_pf_theory = (Nobs/(Nobs+NsmhErr*NsmhErr))*Nsmh + (NsmhErr*NsmhErr/(Nobs+NsmhErr*NsmhErr))*(Nobs-Nbkg);
      //Nobs = Ns + Nbkg + Nsmh_sb;
      float smh_pf_theory = (Nobs/(Nobs+NsmhErr*NsmhErr))*Nsmh + (NsmhErr*NsmhErr/(Nobs+NsmhErr*NsmhErr))*(Nobs-Nbkg);
      //std::cout << "bin" << bin << " " << Nobs << " " << Ns + Nbkg + Nsmh_pf << std::endl;
      
      std::stringstream ss_sigma;
      ss_sigma << fitResultDir << "/PL_nsigma_npvalue_uncapped_bin" << myMap2[ss.str()].bin << ".root";
      TFile* fsigma = new TFile( ss_sigma.str().c_str(), "READ");
      TTree* limit = (TTree*)fsigma->Get("limit");
      double _limit;
      limit->SetBranchAddress( "limit", &_limit );
      limit->GetEntry(0);
      delete fsigma;
      TString line = Form("%d & %s & %.4f & %.4f  & %.4f\\\\",
			  myMap2[ss.str()].bin, categoryMode.c_str(), Nsmh, Nsmh_pf, smh_pf_theory );
      
      std::cout << line << std::endl;
    }
  
  std::cout << "\\hline\n\\end{tabular}\n\\end{center}\n\\end{table*}" << std::endl;

  
  return 0;
};


float GetNobs( std::string fname, int bin, std::string cat )
{
  TFile* fin = TFile::Open( fname.c_str(), "READ");
  RooWorkspace* ws = (RooWorkspace*)fin->Get("combineWS");
  RooDataSet* data = (RooDataSet*)ws->data(Form("data_bin%d",bin));
  return data->sumEntries( Form("mGammaGamma_bin%d > 122. && mGammaGamma_bin%d < 129.", bin, bin) );
};

float GetNs( std::string fname, int bin, std::string cat )
{
  TFile* fin = TFile::Open( fname.c_str(), "READ");
  RooArgSet* norm_fit_s = (RooArgSet*)fin->Get("norm_fit_s");

  //return norm_fit_s->getRealValue("bin11/signal");
  std::stringstream ss;
  if ( cat == "highres" ) ss << "highResBin" << bin << "/signal";
  else if ( cat == "lowres" ) ss << "lowResBin" << bin << "/signal";
  else ss << "bin" << bin << "/signal";
  RooRealVar* ss2 = (RooRealVar*)norm_fit_s->find( ss.str().c_str() );
  return ss2->getVal();
};

float GetNsErr( std::string fname, int bin, std::string cat )
{
  TFile* fin = TFile::Open( fname.c_str(), "READ");
  RooArgSet* norm_fit_s = (RooArgSet*) fin->Get("norm_fit_s");
  //return norm_fit_s->getRealValue("bin11/signal");
  std::stringstream ss;
  if ( cat == "highres" ) ss << "highResBin" << bin << "/signal";
  else if ( cat == "lowres" ) ss << "lowResBin" << bin << "/signal";
  else ss << "bin" << bin << "/signal";
  RooRealVar* ss2 = (RooRealVar*)norm_fit_s->find( ss.str().c_str() );
  

  RooFitResult* fitResult = (RooFitResult*)fin->Get("fit_s");
  RooArgSet frArgSet = fitResult->floatParsFinal();
  RooRealVar* r = (RooRealVar*)frArgSet.find("r");
  double factor = ss2->getVal()/r->getVal();
  if ( r->getVal() > 0 )
    {
      if ( r->getErrorLo() != 0.0 ) return fabs(factor*r->getErrorLo());
    }
  else
    {
      if ( r->getErrorHi() != 0.0 ) return fabs(factor*r->getErrorHi());
    }
  
  return fabs(factor*r->getError());
  //return r->getError();
  /*
  std::stringstream ss;
  if ( cat == "highres" ) ss << "highResBin" << bin << "/signal";
  else if ( cat == "lowres" ) ss << "lowResBin" << bin << "/signal";
  else ss << "bin" << bin << "/signal";
  RooRealVar* ss2 = (RooRealVar*)norm_fit_s->find( ss.str().c_str() );
  return ss2->getError();
  */
  return ss2->getError();
};


float GetSMH( std::string fname, int bin, std::string cat )
{
  TFile* fin = TFile::Open( fname.c_str(), "READ");
  //RooArgSet* norm_fit_s = (RooArgSet*) fin->Get("norm_fit_s");
  RooArgSet* norm_fit_s = (RooArgSet*) fin->Get("norm_prefit");

  std::stringstream ss;
  if ( cat == "highres" ) ss << "highResBin" << bin << "/SMH";
  else if ( cat == "lowres" ) ss << "lowResBin" << bin << "/SMH";
  else ss << "bin" << bin << "/SMH";
  RooRealVar* ss2 = (RooRealVar*)norm_fit_s->find( ss.str().c_str() );
  return ss2->getVal();
};

float GetSMHErr( std::string fname, int bin, std::string cat )
{
  TFile* fin = TFile::Open( fname.c_str(), "READ");
  //RooArgSet* norm_fit_s = (RooArgSet*) fin->Get("norm_fit_s");
  RooArgSet* norm_fit_s = (RooArgSet*) fin->Get("norm_prefit");
  std::stringstream ss;
  if ( cat == "highres" ) ss << "highResBin" << bin << "/SMH";
  else if ( cat == "lowres" ) ss << "lowResBin" << bin << "/SMH";
  else ss << "bin" << bin << "/SMH";
  RooRealVar* ss2 = (RooRealVar*)norm_fit_s->find( ss.str().c_str() );
  return ss2->getError();
};

float GetSMH_PF( std::string fname, int bin, std::string cat )
{
  TFile* fin = TFile::Open( fname.c_str(), "READ");
  RooArgSet* norm_fit_s = (RooArgSet*) fin->Get("norm_fit_b");
  //RooArgSet* norm_fit_s = (RooArgSet*) fin->Get("norm_prefit");

  std::stringstream ss;
  if ( cat == "highres" ) ss << "highResBin" << bin << "/SMH";
  else if ( cat == "lowres" ) ss << "lowResBin" << bin << "/SMH";
  else ss << "bin" << bin << "/SMH";
  RooRealVar* ss2 = (RooRealVar*)norm_fit_s->find( ss.str().c_str() );
  return ss2->getVal();
};

float GetSMHErr_PF( std::string fname, int bin, std::string cat )
{
  TFile* fin = TFile::Open( fname.c_str(), "READ");
  RooArgSet* norm_fit_s = (RooArgSet*) fin->Get("norm_fit_b");
  //RooArgSet* norm_fit_s = (RooArgSet*) fin->Get("norm_prefit");
  std::stringstream ss;
  if ( cat == "highres" ) ss << "highResBin" << bin << "/SMH";
  else if ( cat == "lowres" ) ss << "lowResBin" << bin << "/SMH";
  else ss << "bin" << bin << "/SMH";
  RooRealVar* ss2 = (RooRealVar*)norm_fit_s->find( ss.str().c_str() );
  return ss2->getError();
};

float GetSMH_SB( std::string fname, int bin, std::string cat )
{
  TFile* fin = TFile::Open( fname.c_str(), "READ");
  RooArgSet* norm_fit_s = (RooArgSet*) fin->Get("norm_fit_s");
  
  std::stringstream ss;
  if ( cat == "highres" ) ss << "highResBin" << bin << "/SMH";
  else if ( cat == "lowres" ) ss << "lowResBin" << bin << "/SMH";
  else ss << "bin" << bin << "/SMH";
  RooRealVar* ss2 = (RooRealVar*)norm_fit_s->find( ss.str().c_str() );
  return ss2->getVal();
};

float GetSMHErr_SB( std::string fname, int bin, std::string cat )
{
  TFile* fin = TFile::Open( fname.c_str(), "READ");
  RooArgSet* norm_fit_s = (RooArgSet*) fin->Get("norm_fit_s");

  std::stringstream ss;
  if ( cat == "highres" ) ss << "highResBin" << bin << "/SMH";
  else if ( cat == "lowres" ) ss << "lowResBin" << bin << "/SMH";
  else ss << "bin" << bin << "/SMH";
  RooRealVar* ss2 = (RooRealVar*)norm_fit_s->find( ss.str().c_str() );
  return ss2->getError();
};

float GetNbkg( std::string fname, std::string f1, int bin, bool _err, std::string cat )
{
  RooFit::PrintLevel(5);
  RooMsgService::instance().setGlobalKillBelow(RooFit::FATAL);
  TFile* fin = TFile::Open( fname.c_str(), "READ");
  RooFitResult* fit_r = (RooFitResult*)fin->Get("fit_b");
  /*fin = TFile::Open( "/Users/cmorgoth/Work/git/RazorEWKSUSYAnalysis/HggRazor/FitMgg/MaxLikelihoodFits/sb300_lsp1_unblinded_6p3ifb_Fixed/HggRazorWorkspace_bin8.root", "READ");
  RooWorkspace* myws = (RooWorkspace*)fin->Get("combineWS");
  RooRealVar* mymgg = (RooRealVar*)myws->var("mGammaGamma_bin8");
  RooAbsPdf* mypdf = (RooAbsPdf*)myws->pdf("singleExp_Bkg_bin8_sExp");
  myws->var("singleExp_Bkg_bin8_sExp_a")->setVal(-2.0071e-02);
  mymgg->setRange( "signal", 120, 130. );
  RooAbsReal* myigx = mypdf->createIntegral(*mymgg, RooFit::NormSet(*mymgg), RooFit::Range("signal"));;
  std::cout << "test--> " << myigx->getVal() << std::endl;
  myws = (RooWorkspace*)fin->Get("w_sb");
  RooFitResult* FR = (RooFitResult*)myws->obj("BkgOnlyFitResult");
  */
  TFile* ftmp = new TFile( "ws_tmp.root", "recreate");
  
 
  RooWorkspace* ws = new RooWorkspace( "ws", "" );
  TString mggName = "mGammaGamma";
  RooRealVar mgg( mggName, "m_{#gamma#gamma}", 103, 160, "GeV" );
  //mgg.SetNameTitle( mggName, "m_{#gamma#gamma}" );
  mgg.setMin( 103. );
  mgg.setMax( 160. );
  mgg.setUnit( "GeV" );
  mgg.setBins(57);
  mgg.setRange( "signal", 122., 129. );
  mgg.setRange( "high", 135., 160. );
  mgg.setRange( "low", 103., 120. );
  mgg.setRange( "full", 103., 160. );
  mgg.setRange( "Full", 103., 160. );
  if ( f1 == "singleExp" )
    {
      int realBin = bin;
      if ( cat == "lowres" ) realBin = realBin+5;
      std::stringstream ss;
      ss << "singleExp_Bkg_bin" << realBin << "_sExp_a";
      RooRealVar *alpha = (RooRealVar*)fit_r->floatParsFinal().find( ss.str().c_str() );
      
      std::stringstream ss_2;
      if ( cat == "highres" ) ss_2 << "shapeBkg_Bkg_highResBin" << bin << "__norm";
      else if ( cat == "lowres" ) ss_2 << "shapeBkg_Bkg_lowResBin" << bin << "__norm";
      else ss_2 << "shapeBkg_Bkg_bin" << bin << "__norm";
      RooRealVar *Nbkg = (RooRealVar*)fit_r->floatParsFinal().find( ss_2.str().c_str() );
      
      
      TString pdf = MakeSingleExpNE( Form("%s_Bkg_bin%d",f1.c_str(),realBin), mgg, *ws );
      ws->var( pdf + "_a" )->setVal( alpha->getVal() );
      RooAbsReal* igx = ws->pdf( pdf )->createIntegral(mgg, RooFit::NormSet(mgg), RooFit::Range("Full"));
      //std::cout << Nbkg->getVal() << " +/- " << Nbkg->getError() << std::endl;
      RooAbsReal* igx_sig = ws->pdf( pdf )->createIntegral(mgg, RooFit::NormSet(mgg), RooFit::Range("signal"));
      std::cout << "bin" <<  bin << "alpha: " << alpha->getVal() << " Nbkg: " << Nbkg->getVal() << " total int: " << igx->getVal() << " window: " << igx_sig->getVal() << std::endl;
      //std::cout << Nbkg->getVal()*igx_sig->getVal() << " +/- " << Nbkg->getError()*igx_sig->getVal() << std::endl;
      if ( _err ) {
        return GetErrorFromToys( ws, fit_r, pdf, 10000, realBin );
      }
      //if ( _err ) return Nbkg->getError()*igx_sig->getVal();
      return Nbkg->getVal()*igx_sig->getVal();
      //double shapeErr = ws->pdf( pdf )->getPropagatedError(*fit_r)*Nbkg->getVal();
      /*
      RooArgSet* paramSet = mypdf->getParameters( RooArgSet(*mymgg) );
      paramSet->Print();
      TF1* myPdf = mypdf->asTF( RooArgList(*mymgg), RooArgList(*paramSet) );
      TMatrixDSym covMatrix = FR->covarianceMatrix();
      double params[1];
      params[0] = myPdf->GetParameter(0);
      double corrP[1];
      corrP[0] = 8.15e-03;
      
      double integ2_full = myPdf->Integral(103, 160);
      double integ2_signal = myPdf->Integral(120, 130);
      //double shapeErr = mypdf->getPropagatedError(*fit_r)*Nbkg->getVal();
      //double intErr = myPdf->IntegralError( 120., 130., params, covMatrix.GetMatrixArray(), 1e-14 );
      std::cout << params[0] << std::endl;
      double intErr = myPdf->IntegralError( 120., 130., params, corrP );
      std::cout << integ2_signal << " " << integ2_full << " " << intErr << std::endl;
      //return alpha->getVal();
      myPdf->Write();
      ftmp->Close();
      */
    }
  else if ( f1 == "poly2" )
    {
      int realBin = bin;
      if ( cat == "lowres" ) realBin = realBin+5;
      std::stringstream ss0;
      ss0 << "poly2_Bkg_bin" << realBin << "_pol2_p0";
      RooRealVar *p0 = (RooRealVar*)fit_r->floatParsFinal().find( ss0.str().c_str() );
      std::stringstream ss1;
      ss1 << "poly2_Bkg_bin" << realBin << "_pol2_p1";
      RooRealVar *p1 = (RooRealVar*)fit_r->floatParsFinal().find( ss1.str().c_str() );
      std::stringstream ssC;
      ssC << "poly2_Bkg_bin" << realBin << "_pol2_pC";
      RooRealVar *pC = (RooRealVar*)fit_r->floatParsFinal().find( ssC.str().c_str() );

      std::stringstream ss_2;
      if ( cat == "highres" ) ss_2 << "shapeBkg_Bkg_highResBin" << bin << "__norm";
      else if ( cat == "lowres" ) ss_2 << "shapeBkg_Bkg_lowResBin" << bin << "__norm";
      else ss_2 << "shapeBkg_Bkg_bin" << bin << "__norm";
      RooRealVar *Nbkg = (RooRealVar*)fit_r->floatParsFinal().find( ss_2.str().c_str() );
      
      
      TString pdf = MakePoly2NE( Form("%s_Bkg_bin%d",f1.c_str(),realBin), mgg, *ws );
      ws->var( pdf + "_p0" )->setVal( p0->getVal() );
      ws->var( pdf + "_p1" )->setVal( p1->getVal() );
      ws->var( pdf + "_pC" )->setVal( pC->getVal() );
      RooAbsReal* igx = ws->pdf( pdf )->createIntegral(mgg);
      //std::cout << Nbkg->getVal() << " +/- " << Nbkg->getError() << std::endl;
      RooAbsReal* igx_sig = ws->pdf( pdf )->createIntegral(mgg, RooFit::NormSet(mgg), RooFit::Range("signal"));
      //std::cout << Nbkg->getVal()*igx_sig->getVal() << " +/- " << Nbkg->getError()*igx_sig->getVal() << std::endl;
      if ( _err ) {
        return GetErrorFromToys( ws, fit_r, pdf, 10000, realBin );
      }
      //if ( _err ) return Nbkg->getError()*igx_sig->getVal();
      return Nbkg->getVal()*igx_sig->getVal();
    }
  else if ( f1 == "poly3" )
    {
      int realBin = bin;
      if ( cat == "lowres" ) realBin = realBin+5;
      std::stringstream ss0;
      ss0 << "poly3_Bkg_bin" << realBin << "_pol3_p0";
      RooRealVar *p0 = (RooRealVar*)fit_r->floatParsFinal().find( ss0.str().c_str() );
      std::stringstream ss1;
      ss1 << "poly3_Bkg_bin" << realBin << "_pol3_p1";
      RooRealVar *p1 = (RooRealVar*)fit_r->floatParsFinal().find( ss1.str().c_str() );
      std::stringstream ss2;
      ss2 << "poly3_Bkg_bin" << realBin << "_pol3_p2";
      RooRealVar *p2 = (RooRealVar*)fit_r->floatParsFinal().find( ss2.str().c_str() );
      std::stringstream ssC;
      ssC << "poly3_Bkg_bin" << realBin << "_pol3_pC";
      RooRealVar *pC = (RooRealVar*)fit_r->floatParsFinal().find( ssC.str().c_str() );
      //std::cout << pC->getVal() << std::endl;

      std::stringstream ss_2;
      if ( cat == "highres" ) ss_2 << "shapeBkg_Bkg_highResBin" << bin << "__norm";
      else if ( cat == "lowres" ) ss_2 << "shapeBkg_Bkg_lowResBin" << bin << "__norm";
      else ss_2 << "shapeBkg_Bkg_bin" << bin << "__norm";
      RooRealVar *Nbkg = (RooRealVar*)fit_r->floatParsFinal().find( ss_2.str().c_str() );

      
      TString pdf = MakePoly3NE( Form("%s_Bkg_bin%d",f1.c_str(),realBin), mgg, *ws );
      ws->var( pdf + "_p0" )->setVal( p0->getVal() );
      ws->var( pdf + "_p1" )->setVal( p1->getVal() );
      ws->var( pdf + "_p2" )->setVal( p2->getVal() );
      ws->var( pdf + "_pC" )->setVal( pC->getVal() );
      RooAbsReal* igx = ws->pdf( pdf )->createIntegral(mgg, RooFit::NormSet(mgg), RooFit::Range("Full"));
      //std::cout << Nbkg->getVal() << " +/- " << Nbkg->getError() << std::endl;
      RooAbsReal* igx_sig = ws->pdf( pdf )->createIntegral(mgg, RooFit::NormSet(mgg), RooFit::Range("signal"));
      //std::cout << Nbkg->getVal()*igx_sig->getVal() << " +/- " << Nbkg->getError()*igx_sig->getVal() << std::endl;
      std::cout << "bin" <<  bin << " Nbkg: " << Nbkg->getVal() << " total int: " << igx->getVal() << " window: " << igx_sig->getVal() << std::endl;
      if ( _err ) {
        return GetErrorFromToys( ws, fit_r, pdf, 10000, realBin );
      }
      //if ( _err ) return Nbkg->getError()*igx_sig->getVal();
      return Nbkg->getVal()*igx_sig->getVal();
    }
  else if ( f1 == "modExp" )
    {
      int realBin = bin;
      if ( cat == "lowres" ) realBin = realBin+5;
      std::stringstream ss;
      ss << "modExp_Bkg_bin" << realBin << "_mexp_a";
      RooRealVar *alpha = (RooRealVar*)fit_r->floatParsFinal().find( ss.str().c_str() );
      std::stringstream ssm;
      ssm << "modExp_Bkg_bin" << realBin << "_mexp_m";
      RooRealVar *m = (RooRealVar*)fit_r->floatParsFinal().find( ssm.str().c_str() );
      
      std::stringstream ss_2;
      if ( cat == "highres" ) ss_2 << "shapeBkg_Bkg_highResBin" << bin << "__norm";
      else if ( cat == "lowres" ) ss_2 << "shapeBkg_Bkg_lowResBin" << bin << "__norm";
      else ss_2 << "shapeBkg_Bkg_bin" << bin << "__norm";
      RooRealVar *Nbkg = (RooRealVar*)fit_r->floatParsFinal().find( ss_2.str().c_str() );
      
      
      TString pdf = MakeModExpNE( Form("%s_Bkg_bin%d",f1.c_str(),realBin), mgg, *ws );
      ws->var( pdf + "_a" )->setVal( alpha->getVal() );
      ws->var( pdf + "_m" )->setVal( m->getVal() );
      RooAbsReal* igx = ws->pdf( pdf )->createIntegral(mgg);
      //std::cout << Nbkg->getVal() << " +/- " << Nbkg->getError() << std::endl;
      RooAbsReal* igx_sig = ws->pdf( pdf )->createIntegral(mgg, RooFit::NormSet(mgg), RooFit::Range("signal"));
      //std::cout << Nbkg->getVal()*igx_sig->getVal() << " +/- " << Nbkg->getError()*igx_sig->getVal() << std::endl;
      if ( _err ) {
        return GetErrorFromToys( ws, fit_r, pdf, 10000, realBin );
      }
      //if ( _err ) return Nbkg->getError()*igx_sig->getVal();
      return Nbkg->getVal()*igx_sig->getVal();
    }
  else if ( f1 == "doubleExp" )
    {
      int realBin = bin;
      if ( cat == "lowres" ) realBin = realBin+5;
      std::stringstream ssa1;
      ssa1 << "doubleExp_Bkg_bin" << realBin << "_doubleExp_a1";
      RooRealVar *alpha1 = (RooRealVar*)fit_r->floatParsFinal().find( ssa1.str().c_str() );
      std::stringstream ssa2;
      ssa2 << "doubleExp_Bkg_bin" << realBin << "_doubleExp_a2";
      RooRealVar *alpha2 = (RooRealVar*)fit_r->floatParsFinal().find( ssa2.str().c_str() );
      std::stringstream ssfrac;
      ssfrac << "doubleExp_Bkg_bin" << realBin << "_doubleExp_frac";
      RooRealVar *frac = (RooRealVar*)fit_r->floatParsFinal().find( ssfrac.str().c_str() );
      
      std::stringstream ss_2;
      if ( cat == "highres" ) ss_2 << "shapeBkg_Bkg_highResBin" << bin << "__norm";
      else if ( cat == "lowres" ) ss_2 << "shapeBkg_Bkg_lowResBin" << bin << "__norm";
      else ss_2 << "shapeBkg_Bkg_bin" << bin << "__norm";
      RooRealVar *Nbkg = (RooRealVar*)fit_r->floatParsFinal().find( ss_2.str().c_str() );
      
      
      TString pdf = MakeDoubleExpNE( Form("%s_Bkg_bin%d",f1.c_str(),realBin), mgg, *ws );
      ws->var( pdf + "_a1" )->setVal( alpha1->getVal() );
      ws->var( pdf + "_a2" )->setVal( alpha2->getVal() );
      ws->var( pdf + "_frac" )->setVal( frac->getVal() );
      RooAbsReal* igx = ws->pdf( pdf )->createIntegral(mgg);
      //std::cout << Nbkg->getVal() << " +/- " << Nbkg->getError() << std::endl;
      RooAbsReal* igx_sig = ws->pdf( pdf )->createIntegral(mgg, RooFit::NormSet(mgg), RooFit::Range("signal"));
      //std::cout << Nbkg->getVal()*igx_sig->getVal() << " +/- " << Nbkg->getError()*igx_sig->getVal() << std::endl;
      if ( _err ) {
        return GetErrorFromToys( ws, fit_r, pdf, 10000, realBin );
      }
      //if ( _err ) return Nbkg->getError()*igx_sig->getVal();
      return Nbkg->getVal()*igx_sig->getVal();
    }

  return 0;
};

float GetErrorFromToys(RooWorkspace *ws, RooFitResult *fr, TString pdfName, unsigned int ntoys, int binNum, 
        bool plotBkgFuncs) {
    RooRandom::randomGenerator()->SetSeed(33333);
    TCanvas *c = new TCanvas("c","c",400,300);
    RooPlot *frame = ws->var("mGammaGamma")->frame();

    RooAbsPdf *pdf = ws->pdf(pdfName);

    // throw toys
    std::vector<float> toyYields;
    for( unsigned int itoy = 0; itoy < ntoys; itoy++ ) {
        // randomize function parameters
        RooArgList toyPars = fr->randomizePars();
        float toyNorm = -1;

        // set params to new values
        TIterator *toyIter = toyPars.createIterator();
        while( RooRealVar *curVar = (RooRealVar*)toyIter->Next() ) {
	  std::string varName = curVar->GetName();
	  if (curVar->isConstant() && varName.find("shapeBkg_Bkg") == std::string::npos ) continue;
	  
	  RooRealVar *pdfVar = ws->var( curVar->GetName() );
	  if (pdfVar) {
	    pdfVar->setVal( curVar->getVal() );
	    pdfVar->setError( curVar->getError() );
	  }
	  std::stringstream ntotalName;
	  if ( binNum <= 8 ) ntotalName << "shapeBkg_Bkg_bin" << binNum << "__norm";
	  else if ( binNum <= 13 ) ntotalName << "shapeBkg_Bkg_highResBin" << binNum << "__norm";
	  else if ( binNum <= 18 ) ntotalName << "shapeBkg_Bkg_lowResBin" << binNum-5 << "__norm";
	  if ( curVar->GetName() == ntotalName.str() ) toyNorm = curVar->getVal();
	}

        // get norm of pdf in signal region
        RooAbsReal *integral = pdf->createIntegral( *(ws->var("mGammaGamma")), 
                RooFit::NormSet( RooArgSet(*(ws->var("mGammaGamma"))) ), RooFit::Range("signal") );
        toyYields.push_back( integral->getVal()*toyNorm );

        // draw the curve
        if (plotBkgFuncs) {
            pdf->plotOn(frame, RooFit::LineWidth(1), RooFit::LineColor(
                    TColor::GetColor((Float_t)0.,(Float_t)0.,(Float_t)(itoy*1.0/ntoys))));
        }
    }

    if (plotBkgFuncs) {
        // draw frame with all sampled curves
        frame->Draw();
        c->Print(Form("toysenvelopebin%d.pdf",binNum));
    }

    // compute mean, min, max
    float mean = 0.0;
    float min = 999999.;
    float max = -1.;
    for( auto &yield : toyYields ) {
        mean += yield;
        if (yield > max) max = yield;
        if (yield < min) min = yield;
    }
    mean /= ntoys;
    // make histogram for illustration
    TH1F *yieldHist = new TH1F("yieldHist", Form("Toys for Bin %d", binNum), 50, min*0.9, max*1.1);
    // compute variance
    float variance = 0.0;
    for( auto &yield : toyYields ) {
        variance += (yield-mean)*(yield-mean);
        yieldHist->Fill(yield);
    }
    variance /= (ntoys-1);

    // make plot
    yieldHist->SetMarkerStyle(20);
    yieldHist->SetMarkerSize(.5);
    yieldHist->Draw("p");
    c->Print(Form("toysbin%d.pdf",binNum));
    delete yieldHist;
    delete c;
    // return standard deviation
    return sqrt(variance);
}
