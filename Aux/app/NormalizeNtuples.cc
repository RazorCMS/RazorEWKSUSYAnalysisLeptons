//C++ INCLUDES
#include <iostream>
#include <map>
#include <fstream>
//ROOT INCLUDES
#include <TString.h>
#include <TH1F.h>
#include <TFile.h>
#include <TTree.h>
//LOCAL INCLUDES
#include "CommandLineInput.hh"
#include "TChainTools.hh"
#include "HggAux.hh"


int main ( int argc, char* argv[] )
{
  //getting lists of root files to scale 
  std::string inputFile = ParseCommandLine( argc, argv, "-inputFile=" );
  if ( inputFile == "" )
    {
      std::cerr << "[ERROR]: Please provide a valid input list" << std::endl;
      std::cout << "[INFO]: options are:\n --inputFile=<your_xsec_file>\n --treeName=<yourTTree>\n --lumi=<lumi (fb-1)>\n (optional) --treeOpt=FullTree, runs on HggRazor\n";
      return -1;
    }
  
  //-------------------------
  //Define lumi in pb-1
  //-------------------------
  float lumi = 1e3;//xsec units are in pb, so need to convert 1fb-1 to 1e3 pb-1;
  std::string _lumi = ParseCommandLine( argc, argv, "--lumi=" );
  if ( _lumi != "" )
    {
      lumi = atof( _lumi.c_str() )*1000.;//convertion to pb-1
    }
  
  std::cout << "LUMI LUMI: " << lumi << std::endl;
  std::string treeOpt = ParseCommandLine( argc, argv, "-treeOpt=" );
  bool splitTrees = true;
  std::string treeName = ParseCommandLine( argc, argv, "-treeName=" );
  
  if ( treeOpt == "" )
    {
      std::cout << "[INFO]: tree Option not provided, using split trees" << std::endl;
    }
  
  if ( treeOpt == "FullTree" )
    {
      std::cout << "[INFO]: FullTree option provided, running on HggRazor TTree" << std::endl;
      splitTrees = false;
      if ( treeName == "" ) treeName = "HggRazor";
    }
  
  //checks for a particular TTree name
  if ( treeName != "" )
    {
      std::cout << "[INFO]: Using a Tree named: " << treeName << std::endl;
      splitTrees = false;
    }
  
  std::cout << "[INFO]: inputFile: " << inputFile << std::endl;
  std::cout << "[INFO]: treeName: " << treeName << std::endl;
  std::cout << "[INFO]: lumi: " << lumi << " (pb-1)"<< std::endl;

  TFile* f;
  TFile* fout;
  TH1F*  h_ngen;
  TTree* tree;
  TTree* newTree;
  //L o o p i n g  o v e r   l i s t
  //--------------------------------
  std::ifstream ifs ( inputFile.c_str(), std::fstream::in );
  std::string rootFile;
  float xsec;
  std::string outRootFile;
  if ( ifs.is_open() )
    {
      while ( ifs.good() )
	{
	  ifs >> xsec >> rootFile;
	  if ( ifs.eof() ) break;
	  float sf = -99.0;
	  f = new TFile( rootFile.c_str() );
	  outRootFile = rootFile.substr( 0, rootFile.find( ".root" ) ) + "_Normalized.root";
	  if ( xsec > .0 )
	    {
	      h_ngen = (TH1F*)f->Get("NEvents");
	      double ngen = h_ngen->Integral();
	      sf = GetXsecSF( lumi , xsec, ngen );
	      std::cout << "[INFO]: Normalizing file -> " << outRootFile << std::endl;
	      std::cout << "[INFO]: xsec -> " << xsec << " ngen-> " << ngen << " sf-> " << sf << std::endl;
	    }
	  else
	    {
	      sf = 1.0;
	      std::cout << "[INFO]: Data detected, using xsecSF = 1.0 in -> " << outRootFile << std::endl;
	    }
	  fout = new TFile( outRootFile.c_str(), "recreate" );
	  if ( splitTrees )
	    {
	      // L o o p i n g   o v e r   b o x e s
	      //------------------------------------
	      for ( const auto& box : Boxes() )
		{
		  std::string boxName = GetBoxString( box );
		  std::cout << "[INFO]: box = " << boxName << std::endl;
		  tree   = (TTree*)f->Get( boxName.c_str() );
		  newTree = CloneAndAddSF( tree, sf );
		  newTree->Write();
		}
	    }
	  else
	    {
	      std::cout << "[INFO]: TTree = " << treeName << std::endl;
	      tree   = (TTree*)f->Get( treeName.c_str() );
	      newTree = CloneAndAddSF( tree, sf );
	      newTree->Write();
	    }
	  delete fout;
	}
    }
  else
    {
      std::cerr << "[ERROR]: Unable to open file-> " << inputFile << std::endl;
      return -1;
    }
  
  return 0;
}
