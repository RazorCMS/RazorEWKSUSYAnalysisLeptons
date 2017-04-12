#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <assert.h>
//ROOT INCLUDES
#include <TSystem.h>
#include <TFile.h>
#include <TTree.h>
#include <TH1F.h>
#include <TROOT.h>
#include <TF1.h>
//ROOFIT INCLUDES
#include <RooWorkspace.h>
#include <RooAbsPdf.h>
#include <RooRealVar.h>
//LOCAL INCLUDES
#include "AssortedFunctions.hh"
#include "CommandLineInput.hh"

struct Res
{
  float FWHM;
  float Norm;
};

int main( int argc, char* argv[] )
{

  gROOT->Reset();
  gSystem->Load("/Users/cmorgoth/Work/git/RazorEWKSUSYAnalysis/HggRazor/FitMgg/include/libCustomPdfs.so");
  
  std::string inputFile = ParseCommandLine( argc, argv, "-inputFile=" );
  if (  inputFile == "" )
    {
      std::cerr << "[ERROR]: please provide an input list file using --inputFile=<path_to_list_file>" << std::endl;
      return -1;
    }

  std::string isList = ParseCommandLine( argc, argv, "-isList=" );
  if (  isList == "yes" )
    {
      std::cout << "[INFO]: Running on list mode: you have use --isList=yes" << std::endl;
    }
  else
    {
      std::cout << "[INFO]: Running on ROOT file mode: if you want to provide a list of ROOT files use --isList=yes" << std::endl;
    }
  
  //-----------------
  //print config file?
  //-----------------
  std::string  isConfig = ParseCommandLine( argc, argv, "-isConfig=" );
  if ( isConfig == "" )
    {
      std::cerr << "[ERROR]: please provide a config option. Use --isConfig=<yes/no>" << std::endl;
      return -1;
    }
  
  if ( isList == "yes")
    {
      TFile* fin;
      TTree* tree;
      TH1F* h_mgg;
      std::map<float,Res> mymap;
      std::ifstream ifs ( inputFile.c_str(), std::ifstream::in );
      if ( ifs.is_open() )
	{
	  while ( ifs.good() )
	    {
	      std::string fname;
	      ifs >> fname;
	      if ( ifs.eof() ) break;
	      fin = new TFile( fname.c_str(), "READ");
	      //std::cout << "[INFO]: checking file: " << inputFile << std::endl;
	      assert( fin );
	      //std::cout << "[INFO]: file: " << inputFile << " passed check\n\n"<< std::endl;

	      int low  = fname.find("_M-")+3;
	      int high = fname.find(".root") - low;
	      std::string mass = fname.substr( low, high );
	      float _mass = atof( mass.c_str() );

	      //------------------------
	      //Getting Workspace and others
	      //------------------------
	      RooWorkspace* ws  = (RooWorkspace*)fin->Get("w_sFit");
	      RooAbsPdf* pdf    = ws->pdf("SignalDCB_pdf");
	      RooRealVar* mgg   = ws->var("mGammaGamma");
	      RooRealVar* mu    = ws->var("Signal_DCB_muCB");
	      RooRealVar* sigma = ws->var("Signal_DCB_sigmaCB");
	      RooRealVar* n1    = ws->var("Signal_DCB_n1");
	      RooRealVar* n2    = ws->var("Signal_DCB_n2");
	      RooRealVar* a1    = ws->var("Signal_DCB_alpha1");
	      RooRealVar* a2    = ws->var("Signal_DCB_alpha2");
	      
	      TF1* myTF1 = pdf->asTF( RooArgList(*mgg), RooArgList(*a1,*a2,*mu,*sigma,*n1,*n2));
	      double maxY = myTF1->GetMaximum();
	      double maxX = myTF1->GetMaximumX();
	      double _low = myTF1->GetX( 0.5*maxY , 0, maxX );
	      double _high = myTF1->GetX( 0.5*maxY , maxX, 10000 );
	      double fwhm = _high - _low;
	      Res tmpRes;
	      
	      tmpRes.FWHM = fwhm;
	      tmpRes.Norm = fwhm/(2.350*_mass);
	      if ( mymap.find(_mass) == mymap.end() )
		{
		  mymap[_mass] = tmpRes;
		}
	      
	      fin->Close();
	    }

	  if( isConfig != "yes" )
	    {
	      std::cout << "\\begin{table}\n\\centering\n\\caption{\\label{tab:Resolution} my resolution table}\n";
	      std::cout << "\\begin{tabular}{r*{3}{c}}\n\\hline\n";
	      std::cout << "$\\mathrm{M_{G}}$ (GeV) & FWHM (GeV) & FWHM/(2.35*$\\mathrm{M_{G}}$)  \\\\\n\\hline\n";
	      for ( auto tmp : mymap )
		{
		  TString formatTable = Form("%0.f & %.3f & %.2e\\\\",  tmp.first, tmp.second.FWHM,
					     tmp.second.Norm );
		  //std::cout << tmp.first << " & " << tmp.second.effSigma << " & " << tmp.second.FWHM << std::endl;
		  std::cout << formatTable << std::endl;
		}
	      std::cout << "\\hline\n\\end{tabular}\n\\end{table}\n";
	    }
	  else
	    {
	      for ( auto tmp : mymap ) std::cout << tmp.first << "\t" <<  tmp.second.FWHM << std::endl;
	    }
	}
      else
	{
	  std::cerr << "Unable to open file: " << inputFile << std::endl;
	}
    }
  else
    {
      TFile* fin = new TFile( inputFile.c_str(), "READ");
      std::cout << "[INFO]: checking file: " << inputFile << std::endl;
      assert( fin );
      std::cout << "[INFO]: file: " << inputFile << " passed check\n\n"<< std::endl;

      int low  = inputFile.find("_M-")+3;
      int high = inputFile.find(".root") - low;
      std::string mass = inputFile.substr( low, high );
      float _mass = atof( mass.c_str() );
      
      RooWorkspace* ws  = (RooWorkspace*)fin->Get("w_sFit");
      RooAbsPdf* pdf    = ws->pdf("SignalDCB_pdf");
      RooRealVar* mgg   = ws->var("mGammaGamma");
      RooRealVar* mu    = ws->var("Signal_DCB_muCB");
      RooRealVar* sigma = ws->var("Signal_DCB_sigmaCB");
      RooRealVar* n1    = ws->var("Signal_DCB_n1");
      RooRealVar* n2    = ws->var("Signal_DCB_n2");
      RooRealVar* a1    = ws->var("Signal_DCB_alpha1");
      RooRealVar* a2    = ws->var("Signal_DCB_alpha2");

      TF1* myTF1 = pdf->asTF( RooArgList(*mgg), RooArgList(*a1,*a2,*mu,*sigma,*n1,*n2));
      double maxY = myTF1->GetMaximum();
      double maxX = myTF1->GetMaximumX();
      double _low = myTF1->GetX( 0.5*maxY , 0, maxX );
      double _high = myTF1->GetX( 0.5*maxY , maxX, 10000 );
      std::cout << "low: " << _low << ", high: " << _high
		<< "; FWHM : " << _high - _low << ", norm: " << (_high - _low)/(2.35*_mass) << std::endl;
      
      fin->Close();
    }
  return 0;
}
