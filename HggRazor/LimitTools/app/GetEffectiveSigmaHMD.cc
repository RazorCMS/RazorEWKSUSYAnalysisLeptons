#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <assert.h>
//ROOT INCLUDES
#include <TFile.h>
#include <TTree.h>
#include <TH1F.h>
#include <TROOT.h>
//LOCAL INCLUDES
#include "AssortedFunctions.hh"
#include "CommandLineInput.hh"

struct Res
{
  float effSigma;
  float FWHM;
};

int main( int argc, char* argv[] )
{

  gROOT->Reset();
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
  //Selection TString
  //-----------------
  std::string categoryMode = ParseCommandLine( argc, argv, "-category=" );
  if (  categoryMode == "" )
    {
      std::cerr << "[ERROR]: please provide the category. Use --category=<ebeb,ebee>" << std::endl;
      return -1;
    }
  
  TString cut = "pho1passIso == 1 && pho2passIso == 1 && pho1passEleVeto == 1 && pho2passEleVeto == 1 && pho1Pt> 75. && pho2Pt>75.";
  TString categoryCutString;

  if (categoryMode == "ebeb")
    {
      categoryCutString = " && mGammaGamma >= 230 && abs(pho1DefaultSC_Eta) <1.4442 && abs(pho2DefaultSC_Eta) < 1.4442";
    }
  else if (categoryMode == "ebee")
    {
      categoryCutString = " && mGammaGamma >= 320 && ( (abs(pho1DefaultSC_Eta) < 1.4442 && abs(pho2DefaultSC_Eta) > 1.566) || (abs(pho1DefaultSC_Eta) > 1.566 && abs(pho2DefaultSC_Eta) < 1.4442) )";
    }
  else
    {
      std::cerr << "category: " << categoryMode << ", NOT VALID; Terminating" << std::endl;
      return -1;
    }
  
  cut = cut + categoryCutString;


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
	      int high = fname.find("_TuneCUEP8M1_13TeV-pythia8.root") - low;
	      std::string mass = fname.substr( low, high );
	      float _mass = atof( mass.c_str() );
	      //------------------------
	      //Getting TTree and Histos
	      //------------------------
	      tree = (TTree*)fin->Get("HggRazor");
	      assert( tree );
	      
	      TFile* tmp = new TFile("tmp.root", "RECREATE");
	      TTree* cutTree = tree->CopyTree( cut );
	      
	      if ( categoryMode == "ebeb") cutTree->Draw("mGammaGamma>>h_mgg(10000,0,10000)", "weight*pileupWeight*(1)", "goff");
	      else cutTree->Draw("mGammaGamma>>h_mgg(5000,0,10000)", "weight*pileupWeight*(1)", "goff");
	      
	      h_mgg = (TH1F*)tmp->Get("h_mgg");
	      double effSigma = GetEffSigma( h_mgg );
	      double fwhm     = GetFWHM( h_mgg );
	      //std::cout << mass << " & " << effSigma << " & " << fwhm << std::endl;
	      Res tmpRes;
	      tmpRes.effSigma = effSigma;
	      tmpRes.FWHM = fwhm;
	      if ( mymap.find(_mass) == mymap.end() )
		{
		  mymap[_mass] = tmpRes;
		}
	      h_mgg->Write("mgg");
	      tmp->Close();
	    }
	  
	  std::cout << "\\begin{table}\n\\centering\n\\caption{\\label{tab:Resolution} my resolution table}\n";
	  std::cout << "\\begin{tabular}{r*{4}{c}}\n\\hline\n";
	  std::cout << "$\\mathrm{M_{G}}$ (GeV) & $\\sigma_{eff}$ (GeV) & FWHM (GeV) & FWHM/(2.35*$\\mathrm{M_{G}}$)  \\\\\n\\hline\n";
	  for ( auto tmp : mymap )
	    {
	      TString formatTable = Form("%0.f & %.3f & %.3f & %.2e\\\\",  tmp.first, tmp.second.effSigma, tmp.second.FWHM,
					 tmp.second.FWHM/(2.35*tmp.first) );
	      //std::cout << tmp.first << " & " << tmp.second.effSigma << " & " << tmp.second.FWHM << std::endl;
	      std::cout << formatTable << std::endl;
	    }
	  std::cout << "\\hline\n\\end{tabular}\n\\end{table}\n";
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
      
      //------------------------
      //Getting TTree and Histos
      //------------------------
      TTree* tree = (TTree*)fin->Get("HggRazor");
      assert( tree );
      
      TFile* tmp = new TFile("tmp.root", "RECREATE");
      TTree* cutTree = tree->CopyTree( cut );
      
      if ( categoryMode == "ebeb") cutTree->Draw("mGammaGamma>>h_mgg(10000,0,10000)", "weight*pileupWeight*(1)", "goff");
      else cutTree->Draw("mGammaGamma>>h_mgg(5000,0,10000)", "weight*pileupWeight*(1)", "goff");
      
      TH1F* h_mgg = (TH1F*)tmp->Get("h_mgg");
      double effSigma = GetEffSigma( h_mgg );
      double fwhm     = GetFWHM( h_mgg );
      std::cout << "[RESULT]: category: " << categoryMode << "; Effective Sigma = " << effSigma << "; FWHM = " << fwhm << std::endl;
      h_mgg->Write("mgg");
      tmp->Close();
    }
  return 0;
}
