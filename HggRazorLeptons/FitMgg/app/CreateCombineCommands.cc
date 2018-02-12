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
  

  //outf << "combineCards.py HggRazorCard_bin0.txt HggRazorCard_bin1.txt HggRazorCard_bin2.txt HggRazorCard_bin3.txt HggRazorCard_bin4.txt HggRazorCard_bin5.txt HggRazorCard_bin6.txt HggRazorCard_bin7.txt HggRazorCard_bin8.txt > combineAll.txt\n"
  //outf << "combineCards.py HggRazorCard_bin*.txt > combineAll.txt\n"
  //outf << "combineCards.py HggRazorCard_bin0.txt HggRazorCard_bin1.txt HggRazorCard_bin2.txt HggRazorCard_bin3.txt HggRazorCard_bin4.txt HggRazorCard_bin5.txt HggRazorCard_bin6.txt HggRazorCard_bin7.txt HggRazorCard_bin8.txt HggRazorCard_bin9.txt HggRazorCard_bin10.txt HggRazorCard_bin11.txt HggRazorCard_bin12.txt HggRazorCard_bin13.txt HggRazorCard_bin14.txt HggRazorCard_bin15.txt HggRazorCard_bin16.txt HggRazorCard_bin17.txt HggRazorCard_bin18.txt HggRazorCard_bin19.txt HggRazorCard_bin20.txt HggRazorCard_bin21.txt HggRazorCard_bin22.txt HggRazorCard_bin23.txt HggRazorCard_bin24.txt HggRazorCard_bin25.txt HggRazorCard_bin26.txt HggRazorCard_bin27.txt HggRazorCard_bin28.txt HggRazorCard_bin29.txt HggRazorCard_bin30.txt HggRazorCard_bin31.txt HggRazorCard_bin32.txt HggRazorCard_bin33.txt HggRazorCard_bin34.txt HggRazorCard_bin35.txt HggRazorCard_bin36.txt > combineAll.txt\n"
  outf << "combineCards.py HggRazorCard_bin0.txt HggRazorCard_bin1.txt HggRazorCard_bin2.txt HggRazorCard_bin3.txt HggRazorCard_bin4.txt HggRazorCard_bin5.txt HggRazorCard_bin6.txt HggRazorCard_bin7.txt HggRazorCard_bin8.txt HggRazorCard_bin9.txt HggRazorCard_bin10.txt HggRazorCard_bin11.txt HggRazorCard_bin12.txt HggRazorCard_bin13.txt HggRazorCard_bin14.txt HggRazorCard_bin15.txt HggRazorCard_bin16.txt HggRazorCard_bin17.txt HggRazorCard_bin18.txt HggRazorCard_bin19.txt HggRazorCard_bin20.txt HggRazorCard_bin21.txt HggRazorCard_bin22.txt HggRazorCard_bin23.txt HggRazorCard_bin24.txt HggRazorCard_bin25.txt HggRazorCard_bin26.txt HggRazorCard_bin27.txt HggRazorCard_bin28.txt HggRazorCard_bin29.txt HggRazorCard_bin30.txt HggRazorCard_bin31.txt HggRazorCard_bin32.txt HggRazorCard_bin33.txt HggRazorCard_bin34.txt HggRazorCard_bin35.txt > combineAll.txt\n"
       << "echo \" [DEBUG] 0 \" \n"
       << "combine -M Asymptotic combineAll.txt --minimizerStrategy=1 -n _combineAll --rMax=1.0\n"
       << "echo \" [DEBUG] 1 \" \n"
       << "combine -M ProfileLikelihood --signif combineAll.txt -n _all.nsigma --setPhysicsModelParameterRanges r=-20,20 --uncapped=1\n"
       << "echo \" [DEBUG] 2 \" \n"
       << "combine -M ProfileLikelihood --pvalue combineAll.txt -n _all.pvalue --setPhysicsModelParameterRanges r=-20,20 --uncapped=1\n"
       << "echo \" [DEBUG] 3 \" \n"
       << "hadd PL_nsigma_npvalue_all.root higgsCombine_all.nsigma.ProfileLikelihood.mH120.root higgsCombine_all.pvalue.ProfileLikelihood.mH120.root\n"
       << "echo \" [DEBUG] 4 \" \n"
/*       << "combineCards.py HggRazorCard_bin0.txt HggRazorCard_bin1.txt HggRazorCard_bin2.txt HggRazorCard_bin3.txt HggRazorCard_bin4.txt HggRazorCard_bin5.txt HggRazorCard_bin6.txt HggRazorCard_bin7.txt HggRazorCard_bin8.txt HggRazorCard_bin9.txt HggRazorCard_bin10.txt HggRazorCard_bin11.txt HggRazorCard_bin12.txt HggRazorCard_bin13.txt HggRazorCard_bin14.txt HggRazorCard_bin15.txt HggRazorCard_bin16.txt HggRazorCard_bin17.txt HggRazorCard_bin18.txt HggRazorCard_bin19.txt HggRazorCard_bin20.txt HggRazorCard_bin21.txt HggRazorCard_bin22.txt HggRazorCard_bin23.txt > combineHadronic.txt\n"
       << "echo \" [DEBUG] 5 \" \n"
       << "combine -M Asymptotic combineHadronic.txt --minimizerStrategy=1 -n _combineHadronic --rMax=1.0 \n"
       << "echo \" [DEBUG] 6 \" \n"
       << "combine -M ProfileLikelihood --signif combineHadronic.txt -n _hadronic.nsigma --setPhysicsModelParameterRanges r=-20,20 --uncapped=1\n"
       << "echo \" [DEBUG] 7 \" \n"
       << "combine -M ProfileLikelihood --pvalue combineHadronic.txt -n _hadronic.pvalue --setPhysicsModelParameterRanges r=-20,20 --uncapped=1\n"
       << "echo \" [DEBUG] 8 \" \n"
       << "hadd PL_nsigma_npvalue_hadronic.root higgsCombine_hadronic.nsigma.ProfileLikelihood.mH120.root higgsCombine_hadronic.pvalue.ProfileLikelihood.mH120.root\n"
       << "echo \" [DEBUG] 9 \" \n"
*/
       << "\ncd - \n";
  outf << "eval `scramv1 runtime -sh` \n"; 


  return 0;
}
