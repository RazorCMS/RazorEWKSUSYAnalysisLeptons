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
  
  // primary input file -- will take bin edges, yields, and systematics from here
  std::string inputCF = ParseCommandLine( argc, argv, "-inputCF=" );
  if (  inputCF == "" )
    {
      std::cerr << "[ERROR]: please provide an input file using --inputCF=<path_to_file>" << std::endl;
      return -1;
    }
  // secondary input file -- will take yields from here and add them to the primary input file yields
  std::string secondInputCF = ParseCommandLine( argc, argv, "-secondInputCF=" );
  if ( secondInputCF != "" ) 
    {
      std::cerr << "[INFO]: secondary input config file provided: " << secondInputCF << std::endl;
    }
  else
    {
      std::cerr << "[INFO]: you have NOT provided a secondary input config file, ARE YOU SURE? to provide a secondary file, please use: --secondInputCF=<path_to_second_file>" << std::endl;
    }
  
  //-----------------
  //Output file TString
  //-----------------
  std::string outputFile = ParseCommandLine( argc, argv, "-outputFile=" );
  if (  outputFile == "" )
    {
      std::cerr << "[ERROR]: please provide an output file using --outputFile=<outputfile>" << std::endl;
      return -1;
    }

  std::string dataFile = ParseCommandLine( argc, argv, "-dataFile=" );
  if (  dataFile == "" )
    {
      std::cerr << "[ERROR]: please provide an input data file using --dataFile=<path_to_file>" << std::endl;
      return -1;
    }

  std::string smhFile = ParseCommandLine( argc, argv, "-smhFile=" );
  if (  smhFile == "" )
    {
      std::cerr << "[ERROR]: please provide an input SMH file using --smhFile=<path_to_file>" << std::endl;
      return -1;
    }
  
  std::string signalFile = ParseCommandLine( argc, argv, "-signalFile=" );
  if (  signalFile == "" )
    {
      std::cerr << "[ERROR]: please provide an input SIGNAL file using --signalFile=<path_to_file>" << std::endl;
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


  //-----------------
  //Binning File 
  //-----------------
  std::string binDefinitionFilename = ParseCommandLine( argc, argv, "-binningFile=" );
  if ( binDefinitionFilename == "" )
    {
      std::cerr << "[ERROR]: please provide the bin definition file. Use --binningFile=<binningFile>" << std::endl;
      return -1;
    } 
  


  //--------------------------------------------------------------------
  //Load Binning
  //--------------------------------------------------------------------
  std::vector<Bin> binVector;
  std::map<int,Bin> mapBinNumberToBin;
  std::ifstream binDefFile( binDefinitionFilename.c_str(), std::fstream::in );
  if ( binDefFile.is_open() ) {
    float x1, x2, y1, y2;
    int binN;
    std::string box, f1;
    while ( binDefFile.good() )
      {
	binDefFile >> binN >> x1 >> x2 >> y1 >> y2 >> box >> f1;
	if ( binDefFile.eof() ) break;
	Bin mybin;
	mybin.bin = binN;
	mybin.f1 = f1;
	mybin.box = box;
	mybin.x1 = x1;
	mybin.x2 = x2;
	mybin.y1 = y1;
	mybin.y2 = y2;

	binVector.push_back(mybin);
	mapBinNumberToBin[binN] = mybin;
      }
  } else {
    std::cout << "Unable to open binning lookup table" << std::endl;
  }



  //--------------------------------------------------------------------
  //Load datacard config files
  //--------------------------------------------------------------------
  std::ifstream ifs( inputCF.c_str(), std::ifstream::in );
  assert(ifs);
  // get secondary input stream, if provided
  std::ifstream ifs2;
  if ( secondInputCF != "" ) {
      ifs2.open( secondInputCF.c_str(), std::ifstream::in );
      assert(ifs2);
  }
  

  //****************************
  //Output File
  //****************************
  std::ofstream outf;
  outf.open(outputFile.c_str());  

  std::string configCardName;

  std::string category, Bkg_f1;
  float SMH, Signal;
  float MR_l, MR_h, Rsq_l, Rsq_h;
  int binNumber;
  Bkg_f1 = "singleExp";
  std::cerr << "[INFO]: opening configDataCard: "<< inputCF << std::endl;
  outf << "#! /bin/bash\ncd " << currentDir << "\neval `scramv1 run -sh`;\n";
  //outf << "cd /afs/cern.ch/work/c/cpena/public/combineDiphotonHM/CMSSW_7_4_7/src/\neosmount eos\ncd -;\n";
  while( ifs.good() )
    {
      std::vector<float> smh_sys;
      std::vector<float> sig_sys;

      std::stringstream SMH_sys;
      std::stringstream Signal_sys;
      // first 6 items are: category, MR range, Rsq range, SM Higgs yield
      ifs >> binNumber >> category >> MR_l >> MR_h >> Rsq_l >> Rsq_h >> SMH;
      //check for consistency
      if (!(
	    mapBinNumberToBin[binNumber].x1 == MR_l &&
	    mapBinNumberToBin[binNumber].x2 == MR_h &&
	    mapBinNumberToBin[binNumber].y1 == Rsq_l &&
	    mapBinNumberToBin[binNumber].y2 == Rsq_h
	    )) {
	std::cout << "Error: Bin " << binNumber << " is inconsistent with the MR-Rsq boundaries provided\n";
	std::cout << category << " " << MR_l << " " << MR_h << " " << Rsq_l << " " << Rsq_h << "\n";
	std::cout << mapBinNumberToBin[binNumber].box << " " << mapBinNumberToBin[binNumber].x1 << " " << mapBinNumberToBin[binNumber].x2 << " " << mapBinNumberToBin[binNumber].y1  << " " << mapBinNumberToBin[binNumber].y2 << "\n";	
	std::cout << bool(mapBinNumberToBin[binNumber].x1 == MR_l) << " "
		  << bool(mapBinNumberToBin[binNumber].x2 == MR_h) << " "
		  << bool(mapBinNumberToBin[binNumber].y1 == Rsq_l) << " "
		  << bool(mapBinNumberToBin[binNumber].y2 == Rsq_h) << " "
		  << "\n";
	return -1;
      }

      if ( category.find("#") != std::string::npos ) continue;
      
      //-------------------------------
      //Getting all systematics for SMH
      //-------------------------------
      std::string SMH_SYS;
      float SMH_SYS_F;
      // the next 68 items are the systematics on SM Higgs (put in quotes, separated by spaces)
      for ( int i = 0; i < 68; i++ )
	{
	  ifs >> SMH_SYS;
	  if ( SMH_SYS == "nan" || SMH_SYS == "-nan" || SMH_SYS == "inf"  || SMH_SYS == "-inf" ) SMH_SYS_F = 0;
	  else SMH_SYS_F = atof( SMH_SYS.c_str() );
	  
	  smh_sys.push_back( SMH_SYS_F );
	}
      //--------------------------------------------
      //Getting all yield and systematics for SIGNAL
      //--------------------------------------------
      std::string SIGNAL_SYS;
      float SIGNAL_SYS_F;
      // next is the signal yield
      ifs >> Signal;
      // the next 70 items are the systematics on the signal (put in quotes, separated by spaces)
      for ( int i = 0; i < 72; i++ )
	{
	  ifs >> SIGNAL_SYS;
	  if ( SIGNAL_SYS == "nan" || SIGNAL_SYS == "-nan" || SIGNAL_SYS == "inf"  || SIGNAL_SYS == "-inf" ) SIGNAL_SYS_F = 0;
	  else SIGNAL_SYS_F = atof( SIGNAL_SYS.c_str() );
	  
	  sig_sys.push_back( SIGNAL_SYS_F );
	}
      if ( ifs.eof() ) break;
      
      //---------------------------------------------------
      // if available, get line from secondary input source
      //---------------------------------------------------
      if ( secondInputCF != "" )
	{
	  if ( ifs2.good() )
	    {
	      std::string category2;
	      float SMH2, Signal2;
	      float MR_l2, MR_h2, Rsq_l2, Rsq_h2;
	      int binNumber2;
	      ifs2 >> binNumber2 >> category2 >> MR_l2 >> MR_h2 >> Rsq_l2 >> Rsq_h2 >> SMH2;
	      std::cout << "File 2: " << category2 << " " << MR_l2 << " " << MR_h2 << " " 
			    << Rsq_l2 << " " << Rsq_h2
			    << std::endl;
	      // make sure input is sane and warn if not
	      if ( !(category == category2 && MR_l == MR_l2 && MR_h == MR_h2 && Rsq_l == Rsq_l2 && Rsq_h == Rsq_h2) )
		{
		  std::cerr << "WARNING: bin definition is not the same in the two input files!\n"
			    << "File 1: " << category << " " << MR_l << " " << MR_h << " " << Rsq_l 
			    << " " << Rsq_h << std::endl
			    << "File 2: " << category2 << " " << MR_l2 << " " << MR_h2 << " " 
			    << Rsq_l2 << " " << Rsq_h2
			    << std::endl;
		}
	     
	      
	      //-----------------------------------
	      //Getting SMH SYSTEMATIC for 2ND FILE
	      //-----------------------------------
	      std::string SMH_SYS;
	      float SMH_SYS_F;
	      // the next 68 items are the systematics on the standard model Higgs (put in quotes, separated by spaces)
	      for ( int i = 0; i < 68; i++ ) {
		ifs2 >> SMH_SYS;
		if ( SMH_SYS == "nan" || SMH_SYS == "-nan" || SMH_SYS == "inf"  || SMH_SYS == "-inf" ) SMH_SYS_F = 0;
		else SMH_SYS_F = atof( SMH_SYS.c_str() );
		
		if ( SMH2 + SMH != 0 ) smh_sys[i] = ( SMH_SYS_F*SMH2 + smh_sys[i]*SMH )/( SMH2 + SMH );//RELATIVE UNCERTAINTY ADDED FULLY CORRELATED
		else smh_sys[i] = 0;
	      }
	      //------------------------------------------------
	      //Getting SIGNAL YIELD AND SYSTEMATIC for 2ND FILE
	      //------------------------------------------------
	      std::string SIGNAL_SYS;
	      float SIGNAL_SYS_F;
	      // get the signal yield
	      ifs2 >> Signal2;
	      // the next 70 items are the systematics on the signal (put in quotes, separated by spaces)
	      for ( int i = 0; i < 70; i++ ) {
		ifs2 >> SIGNAL_SYS;
		if ( SIGNAL_SYS == "nan" || SIGNAL_SYS == "-nan" || SIGNAL_SYS == "inf"  || SIGNAL_SYS == "-inf" ) SIGNAL_SYS_F = 0;
		else SIGNAL_SYS_F = atof( SIGNAL_SYS.c_str() );
		
		if ( Signal2+Signal != 0 ) sig_sys[i] = ( SIGNAL_SYS_F*Signal2+sig_sys[i]*Signal )/(Signal2+Signal);//RELATIVE UNCERTAINTY ADDED FULLY CORRELATED
		else sig_sys[i] = 0;
	      }
	      
	      // add the SM Higgs yields together
	      SMH = SMH + SMH2;
	      // add the signal yields together
	      Signal = Signal + Signal2;
	    }
	  else
	    {
	      std::cerr << "WARNING: secondary input file " << secondInputCF << " is out of input!" << std::endl;
	    }
	}

      SMH_sys << "\"";
      for (int i=0; i<smh_sys.size()-1; i++) {
	SMH_sys << smh_sys[i] << " ";
      }
      SMH_sys << smh_sys[smh_sys.size()-1] << "\"";
      
      Signal_sys << "\"";
      for (int i=0; i<sig_sys.size()-1; i++) {
	Signal_sys << sig_sys[i] << " ";
      }
      Signal_sys << sig_sys[sig_sys.size()-1] << "\"";

      Bkg_f1 = "singleExp";
      Bkg_f1 = mapBinNumberToBin[binNumber].f1;
      
      Signal = 1.0*Signal; //scaling signal by 5
      outf << "./MakeFitRun2 " 
	   << "--inputFile=" << dataFile
	   << " --inputFileSignal=" << signalFile
	   << " --inputFileSMH=" << smhFile
	<< " --treeName=HggRazorLeptons --runPeriod=run2 --dataMode=data+signal --fitMode=datacardexpected --category=" << category<< " --LowMRcut=" << MR_l
	//<< " --treeName=HggRazorLeptons --runPeriod=run2 --dataMode=data+signal --fitMode=datacard --category=" << category<< " --LowMRcut=" << MR_l
	//<< " --treeName=HggRazor --runPeriod=run2 --dataMode=data+signal --fitMode=datacard --category=" << category<< " --LowMRcut=" << MR_l 
	   << " --HighMRcut=" << MR_h << " --LowRSQcut=" << Rsq_l << " --HighRSQcut=" << Rsq_h << " --f1=" << Bkg_f1
	   << " --SMH_Yield=" << SMH << " --SMH_CL=" << SMH_sys.str()
	   << " --Signal_Yield=" << Signal << " --Signal_CL=" << Signal_sys.str()
	   << " --sModel=" << sModel
	   << " --binNumber=" << binNumber << " --detector=ebeb";

      //------------------
      //finalizing command
      //------------------
      if ( usePtGammaGamma ) outf << " --usePtGammaGamma=yes";
      
      if ( sOnly ) outf << " --sOnly=yes" << std::endl;
      else outf << std::endl;

      //SMH_sys.str(std::string());
      //Signal_sys.str(std::string());
      
    }
 
  outf << "rm test_out_" << sModel << ".root;\n";
/*
  //Do Combine DataCard step
  outf << "\n\n";
  outf << "cd HggRazorDataCards/" << sModel << "\n"; 
  
  //count number of high res bins
  int NBinsHighRes = 0;
  for (int i=0; i<binVector.size(); i++) {
    if (binVector[i].box == "highres") NBinsHighRes++;
  }
  
  for (int i=0; i<binVector.size(); i++) {
    if (binVector[i].box == "highpt" || binVector[i].box == "hzbb" ) {
      outf << "cp HggRazorCard_bin" << binVector[i].bin << ".txt" << " "
  	   << "HggRazorCombinedCard_bin" << binVector[i].bin << ".txt" 
  	   << "\n";
    } else if (binVector[i].box == "highres") {
      outf << "combineCards.py highResBin" << binVector[i].bin 
	   << "=HggRazorCard_bin" << binVector[i].bin << ".txt" 
	   << " lowResBin" << binVector[i].bin 
	   << "=HggRazorCard_bin" << binVector[i].bin+NBinsHighRes << ".txt"
	   << " > HggRazorCombinedCard_bin" << binVector[i].bin << ".txt"
	   << "\n";
    }		  
  }

  outf << "combineCards.py HggRazorCard_bin0.txt HggRazorCard_bin1.txt HggRazorCard_bin2.txt HggRazorCard_bin3.txt HggRazorCard_bin4.txt HggRazorCard_bin5.txt HggRazorCard_bin6.txt HggRazorCard_bin7.txt HggRazorCard_bin8.txt HggRazorCard_bin9.txt HggRazorCard_bin10.txt HggRazorCard_bin11.txt HggRazorCard_bin12.txt HggRazorCard_bin13.txt HggRazorCard_bin14.txt HggRazorCard_bin15.txt HggRazorCard_bin16.txt HggRazorCard_bin17.txt HggRazorCard_bin18.txt > combineAll.txt\n"
       << "combine -M Asymptotic combineAll.txt --minimizerStrategy=1 -n _combineAll\n"
       << "combine -M ProfileLikelihood --signif combineAll.txt -n _all.nsigma --setPhysicsModelParameterRanges r=-20,20 --uncapped=1\n"
       << "combine -M ProfileLikelihood --pvalue combineAll.txt -n _all.pvalue --setPhysicsModelParameterRanges r=-20,20 --uncapped=1\n"
       << "hadd PL_nsigma_npvalue_all.root higgsCombine_all.nsigma.ProfileLikelihood.mH120.root higgsCombine_all.pvalue.ProfileLikelihood.mH120.root"
       << "\ncd - \n";
*/
  
  //outf << "\nrm test*root\n";


  //outf << "\ncd /afs/cern.ch/work/c/cpena/public/combineDiphotonHM/CMSSW_7_4_7/src\neval `scramv1 run -sh`;\ncd -\n";
  //Do Combine DataCard step
  //outf << "\n\n";
  //outf << "cd HggRazorDataCards/" << sModel << "\n";
  // outf << "combineCards.py HggRazorCard_bin0.txt HggRazorCard_bin1.txt HggRazorCard_bin2.txt HggRazorCard_bin3.txt HggRazorCard_bin4.txt HggRazorCard_bin5.txt HggRazorCard_bin6.txt HggRazorCard_bin7.txt HggRazorCard_bin8.txt > combineAll.txt\n"
  //outf << "combineCards.py HggRazorCard_bin0.txt HggRazorCard_bin1.txt HggRazorCard_bin2.txt HggRazorCard_bin3.txt HggRazorCard_bin4.txt HggRazorCard_bin5.txt HggRazorCard_bin6.txt HggRazorCard_bin7.txt > combineAll.txt\n"
  //outf << "combineCards.py HggRazorCard_bin*.txt > combineAll.txt\n"
       //<< "combine -M Asymptotic combineAll.txt > limit.txt \n"
       //<< "combine -M Asymptotic combineAll.txt --minimizerStrategy=1 -n _combineAll \n"
       //<< "combine -M ProfileLikelihood --signif combineAll.txt -n _all.nsigma --setPhysicsModelParameterRanges r=-20,20 --uncapped=1\n"
       //<< "combine -M ProfileLikelihood --pvalue combineAll.txt -n _all.pvalue --setPhysicsModelParameterRanges r=-20,20 --uncapped=1\n"
       //<< "hadd PL_nsigma_npvalue_all.root higgsCombine_all.nsigma.ProfileLikelihood.mH120.root higgsCombine_all.pvalue.ProfileLikelihood.mH120.root"
       //<< "\nrm core* \n"
       //<< "\ncd - \n";
  
  //close files
  ifs.close();  
  if ( secondInputCF != "" ) ifs2.close();
  
  return 0;
}
