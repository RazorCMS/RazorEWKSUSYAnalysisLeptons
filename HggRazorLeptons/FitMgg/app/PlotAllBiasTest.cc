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
#include "PlotBias.hh"
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
  std::map< std::pair <std::string, std::string>, double > mean_err_map;//mean values for bias or fit error are strored
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
  /*
  std::string doubleGaus = ParseCommandLine( argc, argv, "-useDoubleGaus=" );
  bool _doubleGaus = false;
  if (  doubleGaus == "" )
    {
      std::cerr << "[WARNING]: please indicate whether to use double gaus to fit bias or not by using --useDoubleGaus=<yes/no>" << std::endl;
    }
  
  if ( doubleGaus == "yes" || doubleGaus == "Yes" || doubleGaus == "YES" ) _doubleGaus = true;
 
*/
  std::string fitFunc = ParseCommandLine( argc, argv, "-fitFunc=" );
  if (fitFunc == "") 
  {
      std::cerr << "[WARNING]: please provide the bias fit function by using --fitFunc=<singleGaus/doubleGaus/crystalBall/doublecrystalBall/doubleTailCrystalBall>" << std::endl;
      std::cerr << "[WARNING]: fit function not indicated, use default one: singleGaus" <<std::endl;
      fitFunc = "singleGaus";
  }


  std::string categoryMode = ParseCommandLine( argc, argv, "-category=" );
  if (  categoryMode == "" )
    {
      std::cout << "[WARNING]: please provide the category. Use --category=<highpt,highres,lowres>" << std::endl;
      categoryMode = "??";
    }
 
  std::string LowMRcut = ParseCommandLine( argc, argv, "-LowMRcut=" );
  std::string HighMRcut = ParseCommandLine( argc, argv, "-HighMRcut=" );
  std::string LowRSQcut = ParseCommandLine( argc, argv, "-LowRSQcut=" );
  std::string HighRSQcut = ParseCommandLine( argc, argv, "-HighRSQcut=" );
  std::string SoB = ParseCommandLine( argc, argv, "-SoB=" );

  if (  SoB == "" )
    {
      std::cout << "[WARNING]: please provide the category. Use --category=<highpt,highres,lowres>" << std::endl;
      SoB = "??";
    }
 
  std::string BinSelection = ParseCommandLine( argc, argv, "-BinSelection=" );
  if (  BinSelection == "" && ( LowMRcut == "" || LowRSQcut == "" ) )
    {
      std::cout << "[WARNING]: please provide MR cut and Rsq cut. use --LowMRcut=<yourLowMRCut> --LowRSQcut=<yourLowRSQCut>" << std::endl;
      LowMRcut = "??";
      LowRSQcut = "??";
    }

  if (  BinSelection == "" && ( HighMRcut == "" || HighRSQcut == "" ) )
    {
      std::cout << "[WARNING]: please provide High-MR cut and High-Rsq cut. use --HighMRcut=<yourHighMRCut> --HighRSQcut=<HighRSQCut>" << std::endl;
      HighMRcut = "??";
      HighRSQcut = "??";
    }


  std::string AICw1 = ParseCommandLine( argc, argv, "-AICw1=" );
  std::string AICw2 = ParseCommandLine( argc, argv, "-AICw2=" );
  std::string AICw3 = ParseCommandLine( argc, argv, "-AICw3=" );
  std::string AICw4 = ParseCommandLine( argc, argv, "-AICw4=" );
  std::string AICw5 = ParseCommandLine( argc, argv, "-AICw5=" );
  std::string AICw6 = ParseCommandLine( argc, argv, "-AICw6=" );
  std::string AICw7 = ParseCommandLine( argc, argv, "-AICw7=" );

  std::string AICfunc1 = ParseCommandLine( argc, argv, "-AICfunc1=" );
  std::string AICfunc2 = ParseCommandLine( argc, argv, "-AICfunc2=" );
  std::string AICfunc3 = ParseCommandLine( argc, argv, "-AICfunc3=" );
  std::string AICfunc4 = ParseCommandLine( argc, argv, "-AICfunc4=" );
  std::string AICfunc5 = ParseCommandLine( argc, argv, "-AICfunc5=" );
  std::string AICfunc6 = ParseCommandLine( argc, argv, "-AICfunc6=" );
  std::string AICfunc7 = ParseCommandLine( argc, argv, "-AICfunc7=" );
  



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
	      PlotBias( biasFile, outputDir );
	    }
	  else if ( mode == "table" )
	    {
	      std::pair<double, double> pair = GetMeanRms( biasFile, "data_bias", "bias" );
	      //-----------------------------------
	      //G e t t i n g   p a i r   n a m e s 
	      //-----------------------------------
	      std::string findName = "biasTest_";
	      int begin_s = biasFile.find( findName ) + findName.size();
	      int end_s   = biasFile.find_last_of( "_" );
	      std::string f1 = biasFile.substr( begin_s, end_s - begin_s);
	      begin_s = end_s + 1;
	      end_s   = biasFile.find( ".root" );
	      std::string f2 = biasFile.substr( begin_s, end_s - begin_s);
	      std::pair< std::string, std::string > tmp_p = std::make_pair( f1, f2 );
	      if ( mean_map.find( tmp_p ) == mean_map.end() )
		{
		  mean_map[tmp_p] = pair.first;
		  rms_map[tmp_p] = pair.second;
		}
	      std::cout << "pass" << std::endl;
	    }
	  else if ( mode == "table2" )
	    {
	      std::string rootFile;
	      rootFile = biasFile;
	      //-----------------------------------
	      //G e t t i n g   p a i r   n a m e s 
	      //-----------------------------------
	      std::string findName = "biasTest_";
	      std::string findName2 = "_Tree.root";
	      int begin_s = biasFile.find( findName );
	      int aux_end_s =  biasFile.find( findName2 );
	      std::string aux_s = biasFile.substr(begin_s, aux_end_s - begin_s );
	      begin_s = aux_s.find( findName ) + findName.size();
	      int end_s   = aux_s.find_last_of( "_" );
	      std::string f1 = aux_s.substr( begin_s, end_s - begin_s);
	      begin_s = end_s + 1;
	      end_s   = aux_s.size();
	      std::string f2 = aux_s.substr( begin_s, end_s - begin_s );
	      std::pair< std::string, std::string > tmp_p = std::make_pair( f1, f2 );
	      std::cout << "f1: " << f1 << " f2: " << f2 << std::endl;
	      double mean_err = 0.0; 
	      double mean = FitBias(&mean_err,  rootFile.c_str(), f1.c_str(), f2.c_str(), outputDir, _fitStatus, fitFunc );
	       if ( mean_map.find( tmp_p ) == mean_map.end() )
		 {
		   mean_map[tmp_p] = mean;
		 }
		if ( mean_err_map.find( tmp_p ) == mean_err_map.end() )
		 {
		   mean_err_map[tmp_p] = mean_err;
		 }

	       std::cout << "mean--> " << mean << std::endl;
	    }
	  else if ( mode == "tableFitErr" )
	    {
	      std::pair<double, double> pair_fe = GetMeanRms( biasFile, "data_Nse", "NsignalError" );
	      std::pair<double, double> pair_bias = GetMeanRms( biasFile, "data_bias", "bias" );
	      //-----------------------------------
	      //G e t t i n g   p a i r   n a m e s 
	      //-----------------------------------
	      std::string findName = "biasTest_";
	      int begin_s = biasFile.find( findName ) + findName.size();
	      int end_s   = biasFile.find_last_of( "_" );
	      std::string f1 = biasFile.substr( begin_s, end_s - begin_s);
	      begin_s = end_s + 1;
	      end_s   = biasFile.find( ".root" );
	      std::string f2 = biasFile.substr( begin_s, end_s - begin_s);
	      std::pair< std::string, std::string > tmp_p = std::make_pair( f1, f2 );
	      if ( mean_map.find( tmp_p ) == mean_map.end() )
		{
		  if ( pair_fe.first != 0 )
		    {
		      mean_map[tmp_p] = pair_bias.first/pair_fe.first;
		    }
		  else
		    {
		      mean_map[tmp_p] = -999;
		    }
		  rms_map[tmp_p] = pair_fe.second;
		}
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


  if ( mode == "table" )
    {
      MakeTable( mean_map, "mean" );
      MakeTable( rms_map, "rms" );
    }

  if ( mode == "table2" )
    {
        std::vector<std::string> v_func_name;// = new std::vector<std::string>;
	std::map<std::string, std::string> func_map;
	if(AICfunc1!="")
	{
	func_map.insert( std::pair<std::string, std::string>(AICfunc1,AICw1));
	v_func_name.push_back(AICfunc1);
	}
	if(AICfunc2!="")
	{
	func_map.insert( std::pair<std::string, std::string>(AICfunc2,AICw2));
	v_func_name.push_back(AICfunc2);
	}
	if(AICfunc3!="")
	{
	func_map.insert( std::pair<std::string, std::string>(AICfunc3,AICw3));
	v_func_name.push_back(AICfunc3);
	}
	if(AICfunc4!="")
	{
	func_map.insert( std::pair<std::string, std::string>(AICfunc4,AICw4));
	v_func_name.push_back(AICfunc4);
	}
	if(AICfunc5!="")
	{
	func_map.insert( std::pair<std::string, std::string>(AICfunc5,AICw5));
	v_func_name.push_back(AICfunc5);
	}
	if(AICfunc6!="")
	{
	func_map.insert( std::pair<std::string, std::string>(AICfunc6,AICw6));
	v_func_name.push_back(AICfunc6);
	}
	if(AICfunc7!="")
	{
	func_map.insert( std::pair<std::string, std::string>(AICfunc7,AICw7));
	v_func_name.push_back(AICfunc7);
	}
	
	std::cout<<"map of functions: "<<std::endl;
	//std::sort(func_map.begin(),func_map.end());
	//for(auto tmp:func_map)
	for(int i=0;i<v_func_name.size();i++)
	{
		std::cout<<v_func_name[i]<<"   "<<func_map[v_func_name[i]]<<std::endl;
	}
      MakeTable2( mean_map, mean_err_map, "mean", categoryMode, LowMRcut, HighMRcut, LowRSQcut, HighRSQcut, SoB, func_map,v_func_name);
    }
  
  if ( mode == "tableFitErr" )
    {
      MakeTable( mean_map, "mean" );
    }
  
  /*
  for ( auto& tmp : mean_map )
    {
      std::cout << tmp.first.first << " " << tmp.first.second << " " << tmp.second << std::endl; 
    }
  */
  std::cout << "[INFO]: finishing... " << std::endl;
  return 0;	
}
