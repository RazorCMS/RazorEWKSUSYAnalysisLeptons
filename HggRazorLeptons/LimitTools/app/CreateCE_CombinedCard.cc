//C++ INCLUDES
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <utility>
#include <assert.h>
//ROOT INCLUDES
#include <TFile.h>
#include <TTree.h>
#include <TMath.h>
//LOCAL INCLUDES
#include "CountingExperiment.hh"
#include "CommandLineInput.hh"
#include "HggAux.hh"



const float lumi = 2317.;
const float nonRes_kfactor = 1.37;

const float rsqStep = 0.001;

//-------------
//B i n n i n g 
//-------------
/*
//MASTER BINNING
//highpt
const int n_highptMRedges = 5;
float  highptMRedges[] = {150,250,500,1000,10000};
const int n_highptRSQedges0 = 6;
float  highptRSQedges0[] = {0,0.028,0.053,0.078,0.128,5.0};
const int n_highptRSQedges1 = 6;
float  highptRSQedges1[] = {0,0.027,0.052,0.077,0.102,5.0};
const int n_highptRSQedges2 = 4;
float  highptRSQedges2[] = {0,0.011,0.036,5.0};
const int n_highptRSQedges3 = 2;
float  highptRSQedges3[] = {0,5.0};
//highres
const int n_highresMRedges = 5;
float  highresMRedges[] = {150,225,450,900,10000};
const int n_highresRSQedges0 = 8;
float  highresRSQedges0[] = {0,0.036,0.061,0.086,0.111,0.136,0.186,5.0};
const int n_highresRSQedges1 = 6;
float  highresRSQedges1[] = {0,0.027,0.052,0.077,0.102,5.0};
const int n_highresRSQedges2 = 3;
float  highresRSQedges2[] = {0,0.022,5.0};
const int n_highresRSQedges3 = 2;
float  highresRSQedges3[] = {0,5.0};
//lowres
const int n_lowresMRedges = 5;
float  lowresMRedges[] = {150,225,450,900,10000};
const int n_lowresRSQedges0 = 9;
float  lowresRSQedges0[] = {0,0.036,0.061,0.086,0.111,0.136,0.161,0.186,5.0};
const int n_lowresRSQedges1 = 6;
float  lowresRSQedges1[] = {0,0.022,0.047,0.072,0.097,5.0};
const int n_lowresRSQedges2 = 3;
float  lowresRSQedges2[] = {0,0.019,5.0};
const int n_lowresRSQedges3 = 2;
float  lowresRSQedges3[] = {0,5.0};
*/

//min bin count 10
//HighPt
const int n_highptMRedges = 5;
float  highptMRedges[] = {150,250,500,1000,10000};
const int n_highptRSQedges0 = 5;
float  highptRSQedges0[] = {0,0.046,0.071,0.121,5.0};
const int n_highptRSQedges1 = 5;
float  highptRSQedges1[] = {0,0.044,0.069,0.094,5.0};
const int n_highptRSQedges2 = 3;
float  highptRSQedges2[] = {0,0.034,5.0};
const int n_highptRSQedges3 = 2;
float  highptRSQedges3[] = {0,5.0};
//HighRes
const int n_highresMRedges = 5;
float  highresMRedges[] = {150,237.5,475,950,10000};
const int n_highresRSQedges0 = 9;
float  highresRSQedges0[] = {0,0.028,0.053,0.078,0.103,0.128,0.153,0.178,5.0};
const int n_highresRSQedges1 = 5;
float  highresRSQedges1[] = {0,0.035,0.06,0.085,5.0};
const int n_highresRSQedges2 = 3;
float  highresRSQedges2[] = {0,0.018,5.0};
const int n_highresRSQedges3 = 2;
float  highresRSQedges3[] = {0,5.0};
//LowRes
const int n_lowresMRedges = 5;
float  lowresMRedges[] = {150,200,400,800,10000};
const int n_lowresRSQedges0 = 7;
float  lowresRSQedges0[] = {0,0.049,0.074,0.099,0.124,0.149,5.0};
const int n_lowresRSQedges1 = 6;
float  lowresRSQedges1[] = {0,0.023,0.048,0.073,0.098,5.0};
const int n_lowresRSQedges2 = 3;
float  lowresRSQedges2[] = {0,0.02,5.0};
const int n_lowresRSQedges3 = 2;
float  lowresRSQedges3[] = {0,5.0};

/*
//min bin count 18
//HighPt
const int n_highptMRedges = 5;
float  highptMRedges[] = {150,250,500,1000,10000};
const int n_highptRSQedges0 = 4;
float  highptRSQedges0[] = {0,0.054,0.104,5.0};
const int n_highptRSQedges1 = 4;
float  highptRSQedges1[] = {0,0.038,0.088,5.0};
const int n_highptRSQedges2 = 3;
float  highptRSQedges2[] = {0,0.03,5.0};
const int n_highptRSQedges3 = 2;
float  highptRSQedges3[] = {0,5.0};
//HighRes
const int n_highresMRedges = 5;
float  highresMRedges[] = {150,187.5,375,750,10000};
const int n_highresRSQedges0 = 5;
float  highresRSQedges0[] = {0,0.058,0.108,0.158,5.0};
const int n_highresRSQedges1 = 4;
float  highresRSQedges1[] = {0,0.071,0.121,5.0};
const int n_highresRSQedges2 = 3;
float  highresRSQedges2[] = {0,0.026,5.0};
const int n_highresRSQedges3 = 2;
float  highresRSQedges3[] = {0,5.0};
//LowRes
const int n_lowresMRedges = 5;
float  lowresMRedges[] = {150,200,400,800,10000};
const int n_lowresRSQedges0 = 5;
float  lowresRSQedges0[] = {0,0.064,0.114,0.164,5.0};
const int n_lowresRSQedges1 = 4;
float  lowresRSQedges1[] = {0,0.056,0.106,5.0};
const int n_lowresRSQedges2 = 3;
float  lowresRSQedges2[] = {0,0.02,5.0};
const int n_lowresRSQedges3 = 2;
float  lowresRSQedges3[] = {0,5.0};
*/
//30 events per bin
/*
//HighPt
const int n_highptMRedges = 5;
float  highptMRedges[] = {150,225,450,900,10000};
const int n_highptRSQedges0 = 3;
float  highptRSQedges0[] = {0,0.069,5.0};
const int n_highptRSQedges1 = 5;
float  highptRSQedges1[] = {0,0.037,0.062,0.087,5.0};
const int n_highptRSQedges2 = 3;
float  highptRSQedges2[] = {0,0.029,5.0};
const int n_highptRSQedges3 = 2;
float  highptRSQedges3[] = {0,5.0};
//HighRes
const int n_highresMRedges = 4;
float  highresMRedges[] = {162.5,325,650,10000};
const int n_highresRSQedges0 = 7;
float  highresRSQedges0[] = {0,0.032,0.057,0.082,0.107,0.132,5.0};
const int n_highresRSQedges1 = 3;
float  highresRSQedges1[] = {0,0.029,5.0};
const int n_highresRSQedges2 = 2;
float  highresRSQedges2[] = {0,5.0};
//HighPt
const int n_lowresMRedges = 5;
float  lowresMRedges[] = {150,175,350,700,10000};
const int n_lowresRSQedges0 = 6;
float  lowresRSQedges0[] = {0,0.032,0.057,0.082,0.132,5.0};
const int n_lowresRSQedges1 = 6;
float  lowresRSQedges1[] = {0,0.042,0.067,0.092,0.117,5.0};
const int n_lowresRSQedges2 = 3;
float  lowresRSQedges2[] = {0,0.023,5.0};
const int n_lowresRSQedges3 = 2;
float  lowresRSQedges3[] = {0,5.0};
*/

//hbb
const int n_hbbMRedges = 2;
float  hbbMRedges[] = {150,10000};
const int n_hbbRSQedges0 = 2;
float  hbbRSQedges0[] = {0,5.0};
//zbb
const int n_zbbMRedges = 2;
float  zbbMRedges[] = {150,10000};
const int n_zbbRSQedges0 = 2;
float  zbbRSQedges0[] = {0,5.0};

//end binning
float MRedges[]   = {150., 187.5, 375., 750., 10000.};
float RSQedges0[] = {0.0, 0.06, 0.11, 0.16, 10.0};
float RSQedges1[] = {0.0, 0.07, 0.12, 10.0};
float RSQedges2[] = {0.0, 0.03, 10.0};
float RSQedges3[] = {0.0, 10.0};



void FillBinningMap( std::map<float, std::vector<float>>& mymap,
		     int n_MRedges = 0, float* MRedges = NULL,
		     int n_RSQ0edges = 0, float* RSQ0edges = NULL,
		     int n_RSQ1edges = 0, float* RSQ1edges = NULL,
		     int n_RSQ2edges = 0, float* RSQ2edges = NULL,
		     int n_RSQ3edges = 0, float* RSQ3edges = NULL,
		     int n_RSQ4edges = 0, float* RSQ4edges = NULL,
		     int n_RSQ5edges = 0, float* RSQ5edges = NULL
		     )
{
  for ( int i = 0; i < n_MRedges-1; i++ )
    {
      std::vector<float> myvec;
      if ( mymap.find( MRedges[i] ) == mymap.end() )
	{
	  mymap[MRedges[i]] = myvec;
	  switch (i)
	    {
	    case 0:
	      for ( int j = 0; j < n_RSQ0edges; j++ ) mymap[MRedges[i]].push_back( RSQ0edges[j] );
	      break;
	    case 1:
	      for ( int j = 0; j < n_RSQ1edges; j++ ) mymap[MRedges[i]].push_back( RSQ1edges[j] );
	      break;
	    case 2:
	      for ( int j = 0; j < n_RSQ2edges; j++ ) mymap[MRedges[i]].push_back( RSQ2edges[j] );
	      break;
	    case 3:
	      for ( int j = 0; j < n_RSQ3edges; j++ ) mymap[MRedges[i]].push_back( RSQ3edges[j] );
	      break;
	    case 4:
	      for ( int j = 0; j < n_RSQ4edges; j++ ) mymap[MRedges[i]].push_back( RSQ4edges[j] );
	      break;
	    case 5:
	      for ( int j = 0; j < n_RSQ5edges; j++ ) mymap[MRedges[i]].push_back( RSQ5edges[j] );
	      break;
	    default:
	      std::cerr << "[ERROR] too many MR edges!!!" << std::endl;
	    }
	}
    }
  return;
};
std::vector<float*> stripesBins;
//stripesBins.push_back(RSQedges0);

int main( int argc, char* argv[])
{
  std::string inputFile = ParseCommandLine( argc, argv, "-inputFile=" );
  std::string outputDir = ParseCommandLine( argc, argv, "-outputDir=" );
  std::string category = ParseCommandLine( argc, argv, "-category=" );

  if (outputDir == "")
    {
      outputDir = "combineCards/CountingExp";
    }
  std::string cmd_mkdir = "mkdir -p "+outputDir;
  system(cmd_mkdir.c_str());	

  if (  inputFile == "" )
    {
      std::cerr << "[ERROR]: please provide an input file using --inputFile=<path_to_file>" << std::endl;
      std::cerr << "[INFO]: This file is a text file with the path to the bias test root files" << std::endl;
      return -1;
    }

  if ( category != "highpt" && category != "highres" && category != "lowres"
       && category != "hbb" && category != "zbb" && category != "hzbb" && category != "inclusive" )
    {
      std::cerr << "[ERROR]: please provide a valid category --category=<highpt/highres/lowres/hbb/zbb/hzbb/inclusive>" << std::endl;
      return -1;
    }

  
  TString process, rfName;
  std::ifstream ifs ( inputFile.c_str(), std::ifstream::in );
  std::map<TString, TString> pMap;
  //-----------------
  //reading inputlist
  //-----------------
  if ( ifs.is_open() )
    {
      while ( ifs.good() )
	{
	  ifs >> process >> rfName;
	  if ( ifs.eof() ) break;
	  if ( pMap.find( process ) == pMap.end() ) pMap[process] = rfName;
	}
    }
  else
    {
      std::cerr << "[ERROR]: unable to open file -> " << inputFile << std::endl;
    }
  ifs.close();

  //----------------------------
  //Printing process information
  //----------------------------
  for ( auto& tmp : pMap )
    {
      std::cout << "[INFO]: process-> " << tmp.first << ", file-> " << tmp.second << std::endl;
    }
  
  TFile* fout = new TFile("combineHisto.root", "RECREATE");
  //----------------
  //Define ROOT FILE
  //----------------
  TFile* f;
  TTree* tree;
  
  //-------------------
  //Number of processes
  //-------------------
  const int nProcess = pMap.size();
  TH2F* histoInc[nProcess];//Inclusive mgg histos
  TH2F* histoSR[nProcess];//mgg Signal Region (SR) histos
  std::cout << "[INFO]: number of processes is " << nProcess << std::endl;

  //--------------------
  //Define category cuts
  //--------------------
  TString cut = "pho1passIso == 1 && pho2passIso == 1 && pho1passEleVeto == 1 && pho2passEleVeto == 1 && abs(pho1Eta) <1.48 && abs(pho2Eta)<1.48 && (pho1Pt>40||pho2Pt>40)  && pho1Pt> 25. && pho2Pt>25.";
  TString mggInclusiveCut = " && mGammaGamma > 103. && mGammaGamma < 160.";
  TString categoryCutString, mggCutSR;
  //---------------------
  //B i n n i n g   M a p 
  //---------------------
  std::map<float,std::vector<float>> myBinningMap;
  if (category == "highpt")
    {
      categoryCutString = " && pTGammaGamma >= 110 ";
      mggCutSR = " && mGammaGamma > 122.04 && mGammaGamma < 128.96";
      FillBinningMap( myBinningMap,
		      n_highptMRedges, highptMRedges,
		      n_highptRSQedges0, highptRSQedges0,
		      n_highptRSQedges1, highptRSQedges1,
		      n_highptRSQedges2, highptRSQedges2,
		      n_highptRSQedges3, highptRSQedges3
		      );
    }
  else if (category == "hzbb")
    {
      categoryCutString = " && pTGammaGamma < 110 && ( abs(mbbH_L-125.) < 15. || (abs(mbbZ_L-91.) < 15. && abs(mbbH_L-125.) >= 15.) )";
      mggCutSR = " && mGammaGamma > 121.0 && mGammaGamma < 130.";
      FillBinningMap( myBinningMap,
		      n_hbbMRedges, hbbMRedges,
		      n_hbbRSQedges0, hbbRSQedges0
		      );
    }
  else if (category == "hbb")
    {
      categoryCutString = " && pTGammaGamma < 110 && abs(mbbH-125.)<15";
      mggCutSR = " && mGammaGamma > 121.0 && mGammaGamma < 130.";
      FillBinningMap( myBinningMap,
		      n_hbbMRedges, hbbMRedges,
		      n_hbbRSQedges0, hbbRSQedges0
		      );
    }
  else if (category == "zbb")
    {
      categoryCutString = " && pTGammaGamma < 110 && abs(mbbZ-91.1)<15 && abs(mbbH-125.)>=15";
      mggCutSR = " && mGammaGamma > 121.0 && mGammaGamma < 130.0";
      FillBinningMap( myBinningMap,
		      n_zbbMRedges, zbbMRedges,
		      n_zbbRSQedges0, zbbRSQedges0
		      );
    }
  else if (category == "highres")
    {
      //categoryCutString = " && pTGammaGamma < 110 && abs(mbbH-125.)>=15 && abs(mbbZ-91)>=15 && pho1sigmaEOverE < 0.015 && pho2sigmaEOverE < 0.015 ";
      //categoryCutString = " && pTGammaGamma < 110 && abs(mbbH-125.)>=15 && abs(mbbZ-91)>=15 && sigmaMoverM < 0.0072";
      //categoryCutString = " && pTGammaGamma < 110 && pho1sigmaEOverE < 0.015 && pho2sigmaEOverE < 0.015 ";
      categoryCutString = " && pTGammaGamma < 110 && abs(mbbH-125.)>=15 && abs(mbbZ-91)>=15 && sigmaMoverM < 0.0085 ";
      mggCutSR = " && mGammaGamma > 122.04 && mGammaGamma < 128.96";
      FillBinningMap( myBinningMap,
		      n_highresMRedges, highresMRedges,
		      n_highresRSQedges0, highresRSQedges0,
		      n_highresRSQedges1, highresRSQedges1,
		      n_highresRSQedges2, highresRSQedges2,
		      n_highresRSQedges3, highresRSQedges3
		      );
    }
  else if (category == "lowres")
    {
      //categoryCutString = " && pTGammaGamma < 110  && abs(mbbH-125.)>=15 && abs(mbbZ-91)>=15 && !(pho1sigmaEOverE < 0.015 && pho2sigmaEOverE < 0.015) ";
      categoryCutString = " && pTGammaGamma < 110  && abs(mbbH-125.)>=15 && abs(mbbZ-91)>=15 && sigmaMoverM >= 0.0085 ";
      mggCutSR = " && mGammaGamma > 122.04 && mGammaGamma < 128.96";
      FillBinningMap( myBinningMap,
		      n_lowresMRedges, lowresMRedges,
		      n_lowresRSQedges0, lowresRSQedges0,
		      n_lowresRSQedges1, lowresRSQedges1,
		      n_lowresRSQedges2, lowresRSQedges2,
		      n_lowresRSQedges3, lowresRSQedges3
		      );
    }
  else if (category == "inclusive")
    {
      categoryCutString = "";
      mggCutSR = " && mGammaGamma > 103.0 && mGammaGamma < 160.0";
    }

  //-------------------------
  //Binning Info
  //-------------------------
  for ( auto& tmp : myBinningMap )
    {
      std::cout << "MR: " << tmp.first << " --> {";
      for ( auto& tmp1 : tmp.second ) std::cout << tmp1 << ",";
      std::cout << "}\n";
    }
  
  int nprocess = 0;
  cut = cut + mggInclusiveCut + categoryCutString;
  TString cutSR = cut + mggCutSR + categoryCutString;
  std::cout << "[INFO]: cut applied-> " << cut << std::endl;

  //-------------------
  //Filling Rsq binning
  //-------------------
  stripesBins.push_back(RSQedges0);
  stripesBins.push_back(RSQedges1);
  stripesBins.push_back(RSQedges2);
  stripesBins.push_back(RSQedges3);

  //processstruct map
  std::map<TString, ProcessStruct> psMap;
  for ( auto& tmp : pMap )
    {
      f = new TFile( tmp.second, "READ");
      assert( f );
      tree = (TTree*)f->Get("HggRazor");
      TFile* dummy = new TFile( "dummyFile.root", "RECREATE");
      if ( tmp.first == "NonRes" )
	{
	  histoInc[nprocess] = new TH2F( *Create2DHisto( tree->CopyTree( cut ), myBinningMap, rsqStep, tmp.first, lumi, nonRes_kfactor ) );
	  histoSR[nprocess]  = new TH2F( *Create2DHisto( tree->CopyTree( cutSR ), myBinningMap, rsqStep, tmp.first+"_SR", lumi, nonRes_kfactor ) );
	}
      else
	{
	  histoInc[nprocess] = new TH2F( *Create2DHisto( tree->CopyTree( cut ), myBinningMap, rsqStep, tmp.first , lumi ) );
	  histoSR[nprocess]  = new TH2F( *Create2DHisto( tree->CopyTree( cutSR ), myBinningMap, rsqStep, tmp.first+"_SR", lumi ) );
	}
      ProcessStruct myps;
      myps.h_inc = histoInc[nprocess];
      myps.h_sr  = histoSR[nprocess];
      if ( psMap.find( tmp.first ) == psMap.end() ) psMap[tmp.first] = myps;
      nprocess++;
      delete f;
    }

  //CreateDataCard( psMap, MRedges, stripesBins, rsqStep );
  CreateDataCard( psMap, myBinningMap, rsqStep, category );
  
  fout->cd();
  histoInc[0]->Write("p0_razor");
  histoInc[1]->Write("p1_razor");

  histoSR[0]->Write("p0_razor_sr");
  histoSR[1]->Write("p1_razor_sr");
  
  
  fout->Close();
  std::cout << "[INFO]: finishing... " << std::endl;
  return 0;	
}
