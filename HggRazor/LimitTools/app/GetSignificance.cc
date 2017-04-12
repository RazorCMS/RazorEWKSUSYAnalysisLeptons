#include <iostream>
#include <vector>
#include <fstream>
#include <assert.h>
//ROOT INCLUDES
#include <TFile.h>
#include <TROOT.h>
//LOCAL INCLUDES
#include "HggRazorSystematics.hh"
#include "CommandLineInput.hh"
#include "AssortedFunctions.hh"
//---------------
//Binning
//---------------
const int nMR = 4;

//highpt
int highpt_nRsq[nMR] = {7,5,3,2};
float  highptMRedges[] = {150.0, 312.5, 625, 1250, 10000};
float  highptRSQedges0[7] = {0,0.027,0.052,0.077,0.102,0.127,1.0};
float  highptRSQedges1[5] = {0,0.022,0.047,0.072,1.0};
float  highptRSQedges2[3] = {0,0.021,1.0};
float  highptRSQedges3[2] = {0,1.0};

//highres
int highres_nRsq[nMR] = {9,5,3,2};
float  highresMRedges[] = {150,237.5,475,950,10000};
float  highresRSQedges0[9] = {0,0.028,0.053,0.078,0.103,0.128,0.153,0.178,1.0};
float  highresRSQedges1[5] = {0,0.035,0.06,0.085,1.0};
float  highresRSQedges2[3] = {0,0.018,1.0};
float  highresRSQedges3[2] = {0,1.0};

//lowres
int lowres_nRsq[nMR] = {7,6,3,2};
float  lowresMRedges[] = {150,200,400,800,10000};
float  lowresRSQedges0[7] = {0,0.049,0.074,0.099,0.124,0.149,1.0};
float  lowresRSQedges1[6] = {0,0.023,0.048,0.073,0.098,1.0};
float  lowresRSQedges2[3] = {0,0.02,1.0};
float  lowresRSQedges3[2] = {0,1.0};

//----------------
//Static Variables
//----------------
//float HggRazorSystematics::Lumi  = 2300.0;
float HggRazorSystematics::NR_kf = 1.37;
int HggRazorSystematics::n_PdfSys = 60;

void SetMapBinning( std::map<std::pair<float, float>, std::vector<float>>& myMap, TString category = "highpt" );
/*
//--------------------------
float bin0[4] = {150,0.165,10000,1};
float bin1[4] = {150,0.105,200,0.165};
float bin2[4] = {200,0.105,10000,0.165};
float bin3[4] = {450,0.02,10000,0.105};
float bin4[4] = {950,0,10000,0.02};
float bin5[4] = {250,0.055,450,0.07};
float bin6[4] = {250,0.07,450,0.105};
float bin7[4] = {250,0.045,450,0.055};
float bin8[4] = {450,0,950,0.01};
float bin9[4] = {150,0,250,0.075};
float bin10[4] = {150,0.075,250,0.105};
float bin11[4] = {250,0,450,0.025};
float bin12[4] = {450,0.01,550,0.02};
float bin13[4] = {550,0.01,950,0.02};
float bin14[4] = {250,0.025,350,0.045};
float bin15[4] = {350,0.025,450,0.045};
std::vector<float*> SetBinning()
{
  std::vector<float*> myVec;
  myVec.push_back(bin0);
  myVec.push_back(bin1);
  myVec.push_back(bin2);
  myVec.push_back(bin3);
  myVec.push_back(bin4);
  myVec.push_back(bin5);
  myVec.push_back(bin6);
  myVec.push_back(bin7);
  myVec.push_back(bin8);
  myVec.push_back(bin9);
  myVec.push_back(bin10);
  myVec.push_back(bin11);
  myVec.push_back(bin12);
  myVec.push_back(bin13);
  myVec.push_back(bin14);
  myVec.push_back(bin15);
  for( auto tmp : myVec )
    {
      std::cout << "adding bin: " << tmp[0] << "," <<  tmp[1] << "," << tmp[2] << "," << tmp[3] << std::endl;
    }
  return myVec;
};
*/

float bin0[4] = {600,0.01,10000,1};
float bin1[4] = {150,0.175,600,1};
float bin2[4] = {150,0,400,0.175};
float bin3[4] = {400,0,600,0.025};
float bin4[4] = {400,0.025,600,0.175};
float bin5[4] = {600,0,950,0.01};
float bin6[4] = {950,0,10000,0.01};

std::vector<float*> SetBinning()
{
  std::vector<float*> myVec;
  myVec.push_back(bin0);
  myVec.push_back(bin1);
  myVec.push_back(bin2);
  myVec.push_back(bin3);
  myVec.push_back(bin4);
  myVec.push_back(bin5);
  myVec.push_back(bin6);
  return myVec;
};

int main( int argc, char* argv[] )
{

  gROOT->Reset();

  //Non-resonant ROOT file
  std::string bkgFile = ParseCommandLine( argc, argv, "-bkgFile=" );
  if (  bkgFile == "" )
    {
      std::cerr << "[ERROR]: please provide an bkg file file using --bkgFile=<bkgFile>" << std::endl;
      return -1;
    }

  //SMH ROOT file
  std::string smhFile = ParseCommandLine( argc, argv, "-smhFile=" );
  if (  smhFile == "" )
    {
      std::cerr << "[ERROR]: please provide an SMH file file using --smhFile=<smhFile>" << std::endl;
      return -1;
    }

  //Signal ROOT file
  std::string signalFile = ParseCommandLine( argc, argv, "-signalFile=" );
  if (  signalFile == "" )
    {
      std::cerr << "[ERROR]: please provide an signal file file using --signalFile=<signalFile>" << std::endl;
      return -1;
    }
  
  //-----------------
  //Selection TString
  //-----------------
  std::string categoryMode = ParseCommandLine( argc, argv, "-category=" );
  if (  categoryMode == "" )
    {
      std::cerr << "[ERROR]: please provide the category. Use --category=<highpt,hzbb,highres,lowres>" << std::endl;
      return -1;
    }
  
  TString cut = "mGammaGamma > 103. && mGammaGamma < 160. && pho1passIso == 1 && pho2passIso == 1 && pho1passEleVeto == 1 && pho2passEleVeto == 1 && abs(pho1Eta) <1.48 && abs(pho2Eta)<1.48 && (pho1Pt>40||pho2Pt>40)  && pho1Pt> 25. && pho2Pt>25.";
  TString categoryCutString;
  TString massWindowCut;
  if (categoryMode == "highpt")
    {
      categoryCutString = " && pTGammaGamma >= 110 ";
      massWindowCut     = " && mGammaGamma > 122.96 && mGammaGamma < 127.04";
    }
  else if (categoryMode == "hzbb")
    {
      categoryCutString = " && pTGammaGamma < 110 && ( abs(mbbH_L-125.) < 15. || ( abs(mbbH_L-125.) >= 15. && abs(mbbZ_L-91.) < 15 ) )";
      massWindowCut     = " && mGammaGamma > 122.5 && mGammaGamma < 127.5";
    }
  else if (categoryMode == "highres")
    {
      categoryCutString = " && pTGammaGamma < 110 && abs(mbbH_L-125.) >= 15 && abs(mbbZ_L-91.) >= 15 && sigmaMoverM < 0.0085";
      massWindowCut     = " && mGammaGamma > 122.98 && mGammaGamma < 127.02";
    }
  else if (categoryMode == "lowres")
    {
      categoryCutString  = " && pTGammaGamma < 110 && abs(mbbH_L-125.) >= 15 && abs(mbbZ_L-91.) >= 15 && sigmaMoverM >= 0.0085 ";
      massWindowCut      = " && mGammaGamma > 120.0 && mGammaGamma < 130.00";
    }
  else
    {
      std::cerr << "[ERROR]: please provide a valid category: <highpt,hzbb,highres, lowres>" << std::endl;
      return -1;
    }

  cut = cut + categoryCutString + massWindowCut;
  std::cout << "CUT: " << cut << std::endl;

  
  std::vector<float*> myBinningVect = SetBinning();
  std::cout << "vector size: " << myBinningVect.size() << std::endl;
  for( auto tmp : myBinningVect )
    {
      std::cout << "adding bin: " << tmp[0] << "," <<  tmp[1] << "," << tmp[2] << "," << tmp[3] << std::endl;
    }
  
  //---------------------
  //Non-resonant Bkg File
  //---------------------
  TFile* fbkg = new TFile( bkgFile.c_str(), "READ");
  std::cout << "[INFO]: checking file: " << bkgFile << std::endl;
  assert( fbkg );
  std::cout << "[INFO]: file: " << bkgFile << " passed check\n\n"<< std::endl;
  //------------------------------
  //Getting Non-resonant Bkg TTree
  //------------------------------
  TTree* bkgTree = (TTree*)fbkg->Get("HggRazor");
  assert( bkgTree );

  //---------------------
  //SMH Bkg File
  //---------------------
  TFile* fsmh = new TFile( smhFile.c_str(), "READ");
  std::cout << "[INFO]: checking file: " << smhFile << std::endl;
  assert( fsmh );
  std::cout << "[INFO]: file: " << smhFile << " passed check\n\n"<< std::endl;
  //------------------------------
  //Getting SMH Bkg TTree
  //------------------------------
  TTree* smhTree = (TTree*)fsmh->Get("HggRazor");
  assert( smhTree );

  //---------------------
  //Signal File
  //---------------------
  TFile* fs = new TFile( signalFile.c_str(), "READ");
  std::cout << "[INFO]: checking file: " << signalFile << std::endl;
  assert( fs );
  std::cout << "[INFO]: file: " << signalFile << " passed check\n\n"<< std::endl;
  //------------------------------
  //Getting Signal TTree
  //------------------------------
  TTree* sTree = (TTree*)fs->Get("HggRazor");
  assert( sTree );

  
  TFile* tmp = new TFile("tmp.root", "RECREATE");
  TTree* cutBkgTree = bkgTree->CopyTree( cut );
  TTree* cutSMHTree = smhTree->CopyTree( cut );
  TTree* cutSTree   = sTree->CopyTree( cut );
  
  //-----------------------------
  //Map container for the binning
  //-----------------------------
  std::map<std::pair<float, float>, std::vector<float>> binningMap;
  SetMapBinning( binningMap, categoryMode );
  //---------------------------
  //Create HggSystematic object
  //---------------------------
  HggRazorSystematics* hggSys = new HggRazorSystematics( cutBkgTree, "NR", categoryMode, "", true, true );
  hggSys->SetBinningVector( myBinningVect );
  hggSys->InitMrRsqTH2Poly( 1 );
  hggSys->PrintBinning();
  hggSys->LoopNominal();
  hggSys->WriteOutput( "histoMR_Rsq" );


  HggRazorSystematics* hggSMH = new HggRazorSystematics( cutSMHTree, "SMH", categoryMode, "",true, true );
  hggSMH->SetBinningVector( myBinningVect );
  hggSMH->InitMrRsqTH2Poly( 1 );
  hggSMH->PrintBinning();
  hggSMH->LoopNominal();
  hggSMH->WriteOutput( "histoMR_Rsq" );

  HggRazorSystematics* hggSignal = new HggRazorSystematics( cutSTree, "signal", categoryMode, "", true, true );
  hggSignal->SetBinningVector( myBinningVect );
  hggSignal->InitMrRsqTH2Poly( 1 );
  hggSignal->PrintBinning();
  hggSignal->LoopNominal();
  hggSignal->WriteOutput( "histoMR_Rsq" );


  int nbins = hggSignal->GetSizeVector();
  TH2Poly* h2pNR     = hggSys->GetNominalTH2Poly();
  TH2Poly* h2pSMH    = hggSMH->GetNominalTH2Poly();
  TH2Poly* h2pSignal = hggSignal->GetNominalTH2Poly();

  double b[100];
  double s[100];
  double obs[100];
  for( int i = 1; i <= nbins; i++ )
    {
      b[i-1] = h2pNR->GetBinContent(i) + h2pSMH->GetBinContent(i);
      s[i-1] = h2pSignal->GetBinContent(i);
      std::cout << "b[]: " << b[i-1] << " s[]" << s[i-1] << std::endl;
      obs[i-1] = b[i-1] + s[i-1];
    }

  double mu   = GetBestFitSignalStrength( nbins, b, s, obs );
  double qnot = GetQnotTestStatistics( nbins, b, s, obs, mu );
  std::cout << "best mu: " << mu << " significance: " << sqrt(qnot) << std::endl;
  /*
  //-----------------------------
  //Map container for the binning
  //-----------------------------
  std::map<std::pair<float, float>, std::vector<float>> binningMap;
  SetMapBinning( binningMap, categoryMode );
  
  //---------------------------
  //Create HggSystematic object
  //---------------------------
  HggRazorSystematics* hggSys = new HggRazorSystematics();
  hggSys->PrintBinning();
  hggSys->SetBinningMap( binningMap );
  hggSys->PrintBinning();
  hggSys->Loop();
  */
  return 0;
}


void SetMapBinning( std::map<std::pair<float, float>, std::vector<float>>& myMap, TString category )
{
  if ( category == "highpt" )
    {
      for ( int i = 0; i < nMR; i++ )
	{
	  std::vector<float> vect;
	  for ( int j = 0; j < highpt_nRsq[i]; j++ )
	    {
	      switch (i)
		{
		case 0:
		  vect.push_back(highptRSQedges0[j]);
		  break;
		case 1:
		  vect.push_back(highptRSQedges1[j]);
		  break;
		case 2:
		  vect.push_back(highptRSQedges2[j]);
		  break;
		case 3:
		  vect.push_back(highptRSQedges3[j]);
		  break;
		default:
		  std::cerr << "MR bins exceeds number of defined Rsq binning!! Do nothing" << std::endl;
		  break;
		}
	    }
	  std::pair<float, float> mypair = std::make_pair( highptMRedges[i], highptMRedges[i+1] );
	  std::cout << mypair.first << " " << mypair.second << std::endl;
	  myMap[mypair] = vect;
	}
    }
  else if ( category == "hzbb" )
    {
      std::vector<float> vect;
      vect.push_back( 0.0 );
      vect.push_back( 1.0 );
      std::pair<float, float> mypair = std::make_pair( 150., 10000. );
      std::cout << mypair.first << " " << mypair.second << std::endl;
      myMap[mypair] = vect;
    }
  else if ( category == "highres" )
    {
      for ( int i = 0; i < nMR; i++ )
	{
	  std::vector<float> vect;
	  for ( int j = 0; j < highres_nRsq[i]; j++ )
	    {
	      switch (i)
		{
		case 0:
		  vect.push_back(highresRSQedges0[j]);
		  break;
		case 1:
		  vect.push_back(highresRSQedges1[j]);
		  break;
		case 2:
		  vect.push_back(highresRSQedges2[j]);
		  break;
		case 3:
		  vect.push_back(highresRSQedges3[j]);
		  break;
		default:
		  std::cerr << "MR bins exceeds number of defined Rsq binning!! Do nothing" << std::endl;
		  break;
		}
	    }
	  std::pair<float, float> mypair = std::make_pair( highresMRedges[i], highresMRedges[i+1] );
	  std::cout << mypair.first << " " << mypair.second << std::endl;
	  myMap[mypair] = vect;
	}
    }
  else if ( category == "lowres" )
    {
      for ( int i = 0; i < nMR; i++ )
	{
	  std::vector<float> vect;
	  for ( int j = 0; j < lowres_nRsq[i]; j++ )
	    {
	      switch (i)
		{
		case 0:
		  vect.push_back(lowresRSQedges0[j]);
		  break;
		case 1:
		  vect.push_back(lowresRSQedges1[j]);
		  break;
		case 2:
		  vect.push_back(lowresRSQedges2[j]);
		  break;
		case 3:
		  vect.push_back(lowresRSQedges3[j]);
		  break;
		default:
		  std::cerr << "MR bins exceeds number of defined Rsq binning!! Do nothing" << std::endl;
		  break;
		}
	    }
	  std::pair<float, float> mypair = std::make_pair( lowresMRedges[i], lowresMRedges[i+1] );
	  std::cout << mypair.first << " " << mypair.second << std::endl;
	  myMap[mypair] = vect;
	}
    }
  return;
};
