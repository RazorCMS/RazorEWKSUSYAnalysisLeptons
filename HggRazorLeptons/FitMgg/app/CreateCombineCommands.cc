#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <assert.h>
//LOCAL INCLUDES
#include "CommandLineInput.hh"
#include "HggAux.hh"


int main( int argc, char* argv[] )
{
  
  
  //-----------------
  //Output file TString
  //-----------------
  std::string outputFile = ParseCommandLine( argc, argv, "-outputFile=" );
  if (  outputFile == "" )
    {
      std::cerr << "[ERROR]: please provide an output file using --outputFile=<outputfile>" << std::endl;
      return -1;
    }

  std::string sModel = ParseCommandLine( argc, argv, "-sModel=" );
  if (  sModel == "" )
    {
      std::cerr << "[ERROR]: please provide an input sModel name --sModel=<signalModelName>" << std::endl;
      return -1;
    }

  std::string currentDir = ParseCommandLine( argc, argv, "-currentDir=" );
  if (  currentDir == "" )
    {
      std::cerr << "[ERROR]: please provide the current directory --currentDir=<mycurrentDir>" << std::endl;
      return -1;
    }
  
  bool sOnly = false;
  std::string sOnlyOpt = ParseCommandLine( argc, argv, "-sOnly=" );
  if ( sOnlyOpt == "yes" )
    {
      std::cerr << "[INFO]: ignoring SM Higgs contribution to the fit" << std::endl;
      sOnly = true;
    }
  
  bool usePtGammaGamma = false;
  std::string usePtGammaGammaOpt = ParseCommandLine( argc, argv, "-usePtGammaGamma=" );
  if ( usePtGammaGammaOpt == "yes" )
    {
      std::cerr << "[INFO]: applying cut on pTGammaGamma" << std::endl;
      usePtGammaGamma = true;
    }

  //****************************
  //Output File
  //****************************
  std::ofstream outf;
  outf.open(outputFile.c_str());  
 
  outf << "#! /bin/bash\ncd " << currentDir << "\neval `scramv1 run -sh`;\n";
  //Do Combine DataCard step
  outf << "\n\n";
  outf << "cd /afs/cern.ch/work/c/cpena/public/combineDiphotonHM/CMSSW_7_4_7/src/\n"; 
  outf << "eval `scramv1 runtime -sh` \n"; 
  outf << "\ncd -\n"; 
  outf << "cd HggRazorDataCards/" << sModel << "\n"; 
  

  outf << "combineCards.py HggRazorCard_bin0.txt HggRazorCard_bin1.txt HggRazorCard_bin2.txt HggRazorCard_bin3.txt HggRazorCard_bin4.txt HggRazorCard_bin5.txt HggRazorCard_bin6.txt HggRazorCard_bin7.txt HggRazorCard_bin8.txt > combineAll.txt\n"
       << "combine -M Asymptotic combineAll.txt > limit.txt\n"
//       << "combine -M Asymptotic combineAll.txt --minimizerStrategy=1 -n _combineAll\n"
//       << "combine -M ProfileLikelihood --signif combineAll.txt -n _all.nsigma --setPhysicsModelParameterRanges r=-20,20 --uncapped=1\n"
//       << "combine -M ProfileLikelihood --pvalue combineAll.txt -n _all.pvalue --setPhysicsModelParameterRanges r=-20,20 --uncapped=1\n"
//       << "hadd PL_nsigma_npvalue_all.root higgsCombine_all.nsigma.ProfileLikelihood.mH120.root higgsCombine_all.pvalue.ProfileLikelihood.mH120.root"
       << "\ncd - \n";
  outf << "eval `scramv1 runtime -sh` \n"; 


  return 0;
}
