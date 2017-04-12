//C++ INCLUDES
#include <iostream>
#include <map>
//ROOT INCLUDES
#include <TString.h>
//LOCAL INCLUDES
#include "CommandLineInput.hh"
#include "ToysAndIntegralFunctions.hh"
#include "TTree_fit_sb.hh"

#define _debug 1

int main ( int argc, char* argv[] )
{
  std::cout << "[INFO]: Initializing program" << std::endl;
  
  

  GetIntegral();
  std::string inputFile = ParseCommandLine( argc, argv, "-inputFile=" );
  if (  inputFile == "" )
    {
      std::cerr << "[ERROR]: please provide an input file using --inputFile=<path_to_file>" << std::endl;
      //return -1;
    }
  
  TFile* f_in = new TFile("scripts/mlfit_1ktoys_toy_all_toys.root");
  TTree* myTree = (TTree*)f_in->Get("tree_fit_sb");
  tree_fit_sb* toy_tree = new tree_fit_sb( myTree );
  toy_tree->Loop();

  return 0;
}
