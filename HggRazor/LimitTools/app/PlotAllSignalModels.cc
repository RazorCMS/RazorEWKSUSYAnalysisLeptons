//C++ INCLUDES
#include <iostream>
#include <fstream>
#include <map>
#include <utility>
//ROOT INCLUDES
#include <TFile.h>
#include <TTree.h>
#include <TMath.h>
//LOCAL INCLUDES
#include "PlotSignalModels.hh"
#include "CommandLineInput.hh"
#include "HggAux.hh"

int main( int argc, char* argv[])
{
  std::string inputFile = ParseCommandLine( argc, argv, "-inputFile=" );
  std::string outputDir = ParseCommandLine( argc, argv, "-outputDir=" );

  if (outputDir == "")
    {
      outputDir = "plot_bias";
    }
  std::string cmd_mkdir = "mkdir -p "+outputDir;
  system(cmd_mkdir.c_str());	
  if (  inputFile == "" )
    {
      std::cerr << "[ERROR]: please provide an input file using --inputFile=<path_to_file>" << std::endl;
      std::cerr << "[INFO]: This file is a text file with the path to the bias test root files" << std::endl;
      return -1;
    }

  std::string mode = ParseCommandLine( argc, argv, "-mode=" );
  
  std::map< std::pair <std::string, std::string>, double > mean_map;//mean values for bias or fit error are strored
  std::map< std::pair <std::string, std::string>, double > mean_map_aux;//use to obtain both bias and fit errors.
  std::map< std::pair <std::string, std::string>, double > rms_map;
  if (  mode == "" )
    {
      std::cerr << "[ERROR]: please provide a mode by using --mode=<plot/table/tableFitErr>" << std::endl;
      return -1;
    }

   
  std::string fitStatus = ParseCommandLine( argc, argv, "-requireFitStatus=" );
  bool _fitStatus = false;
  if (  fitStatus == "" )
    {
      std::cerr << "[WARNING]: please provide a fitStatus option by using --requireFitStatus=<yes/no>" << std::endl;
    }
  
  if ( fitStatus == "yes" || fitStatus == "Yes" || fitStatus == "YES" ) _fitStatus = true;
  
  std::string fitFunc = ParseCommandLine( argc, argv, "-fitFunc=" );
  if (fitFunc == "") 
  {
      std::cerr << "[WARNING]: please provide the bias fit function by using --fitFunc=<singleGaus/doubleGaus/crystalBall>" << std::endl;
      std::cerr << "[WARNING]: fit function not indicated, use default one: singleGaus" <<std::endl;
      fitFunc = "singleGaus";
  }

  std::ifstream ifs ( inputFile.c_str(), std::ifstream::in );
  if ( ifs.is_open() )
    {
      while ( ifs.good() )
	{
	  std::string biasFile;
	  ifs >> biasFile;
	  if ( ifs.eof() ) break;
	  if ( mode == "plot" )
	    {
	      PlotSignalModel( biasFile, outputDir );
	    }
	  else
	    {
	      std::cout << "[ERROR]: unrecognized mode -> " << mode << std::endl;
	      return -1;
	    }
	}
    }
  else
    {
      std::cerr << "[ERROR]: unable to open file -> " << inputFile << std::endl;
    }
  
  
  std::cout << "[INFO]: finishing... " << std::endl;
  return 0;	
}
