//C++ INCLUDES
#include <iostream>
//ROOT INCLUDES
#include <TFile.h>
#include <TTree.h>
//LOCAL INCLUDES
#include "makeInvertedANFit_v2.hh"
#include "CommandLineInput.hh"

int main( int argc, char* argv[])
{
  std::string inputFile = ParseCommandLine( argc, argv, "-inputFile=" );
  if (  inputFile == "" )
    {
      std::cerr << "[ERROR]: please provide an input file using --inputFile=<path_to_file>" << std::endl;
      return -1;
    }

  std::string inputFile2 = ParseCommandLine( argc, argv, "-inputFile2=" );
  if (  inputFile2 == "" )
    {
      std::cerr << "[INFO]: using a single root file, provide an second input file using --inputFile2=<path_to_file>" << std::endl;
    }

  std::string treeName = ParseCommandLine( argc, argv, "-treeName=" );
  if (  treeName == "" )
    {
      std::cout << "[WARNING]: user did not provide a tree name, if you wish to provide one use --treeName=<yourTreeName>" << std::endl;
      treeName = "HighRes";
    }

  std::string MRcut = ParseCommandLine( argc, argv, "-MRcut=" );
  if (  MRcut == "" )
    {
      std::cout << "[WARNING]: user did not provide a MR cut, if you wish to provide one use --MRcut=<yourMRcut>" << std::endl;
      MRcut = "350.";
    }

  std::string RSQcut = ParseCommandLine( argc, argv, "-RSQcut=" );
  if (  RSQcut == "" )
    {
      std::cout << "[WARNING]: user did not provide a MR cut, if you wish to provide one use --RSQcut=<yourRSQcut>" << std::endl;
      RSQcut = "0.035";
    }

  std::string dataMode = ParseCommandLine( argc, argv, "-dataMode=" );
  if (  dataMode == "" )
    {
      std::cerr << "[ERROR]: please provide a data type, it could be either mc or data. Use --dataMode=<data/mc>" << std::endl;
      return -1;
    }
  
  std::cout << "[INFO]: tree name is :" << treeName << std::endl;
  std::cout << "[INFO]: data/mc mode :" << dataMode << std::endl;

  TTree* tree;
  TFile* f;
  if ( dataMode == "data" )
    {
      f = new TFile( inputFile.c_str() );
      tree = (TTree*)f->Get( treeName.c_str() );
    }
  else if ( dataMode == "mc" )
    {
      f = new TFile( inputFile.c_str() , "update");
      tree = (TTree*)f->Get( treeName.c_str() );
    }
 
  TTree* mc_tree;
  if ( inputFile2 != "" )
    {
      f = new TFile( inputFile2.c_str(), "update" );
      mc_tree = (TTree*)f->Get( treeName.c_str() );
    }
  
  TString cut = "abs(pho1Eta) <1.48 && abs(pho2Eta)<1.48 && (pho1Pt>40||pho2Pt>40)  && pho1Pt> 25. && pho2Pt>25.&& mGammaGamma > 103. && mGammaGamma<160 && pTGammaGamma > 20 && trigger == 1 && pho1R9>0.9 && pho2R9>0.9 && pTGammaGamma < 110.";
  
  //TString cut = "abs(pho1Eta) <1.48 && abs(pho2Eta)<1.48 && (pho1Pt>40||pho2Pt>40)  && pho1Pt> 25. && pho2Pt>25.&& mGammaGamma > 103. && mGammaGamma<160 && pTGammaGamma > 20 && trigger == 1";
  cut = cut + " && MR > " + MRcut + " && t1Rsq > " + RSQcut;

  float forceSigma = 1.5;
  bool constrainMu = false;
  float forceMu    = -1;
  TString mggName  = "mGammaGamma";
  RooWorkspace* w;
  RooWorkspace* w2;
  if ( dataMode == "data" )
    {
      w = makeInvertedANFit( tree->CopyTree( cut ), forceSigma, constrainMu, forceMu, mggName );
    }
  else if ( dataMode == "mc" )
    {
      w = makeMCFit( tree->CopyTree( cut ), forceSigma, constrainMu, forceMu, mggName );
    }
  else if ( dataMode == "hybrid" && inputFile2 != "" )
    {
      w = makeInvertedANFit( tree->CopyTree( cut ), forceSigma, constrainMu, forceMu, mggName );
      w2 = makeMCFit( mc_tree->CopyTree( cut ), forceSigma, constrainMu, forceMu, mggName );
    }
  else
    {
      std::cout << "[ERROR]: please provide a valid dataMode, i.e data or mc" << std::endl;
      return -1;
    }

  TFile* fout = new TFile( "test_out.root", "recreate" );
  w->Write("w1");
  w2->Write("w2");
  fout->Close();
    
  return 0;	
}
