//C++ INCLUDES
#include <iostream>
#include <map>
#include <assert.h>
#include <fstream>
//ROOT INCLUDES
#include <TString.h>
//LOCAL INCLUDES
#include "HggTree.hh"
#include "HggRazorClass.hh"
#include "HggAux.hh"
#include "CommandLineInput.hh"
#include "TChainTools.hh"

// D e f i n e  B i n n i n g
//---------------------------
int HggRazorClass::n_mgg = 60;
float HggRazorClass::mgg_l = 60.;
float HggRazorClass::mgg_h = 120.;

int HggRazorClass::n_ptgg = 70;
float HggRazorClass::ptgg_l = 20.;
float HggRazorClass::ptgg_h = 720.;

int HggRazorClass::n_sigmaMoverM = 100;
float HggRazorClass::sigmaMoverM_l = .0;
float HggRazorClass::sigmaMoverM_h = .02;

int HggRazorClass::n_mr = 160;
float HggRazorClass::mr_l = 130.;
float HggRazorClass::mr_h = 8130.;

int HggRazorClass::n_rsq = 125;
float HggRazorClass::rsq_l = .0;
float HggRazorClass::rsq_h = 5.0;

//photon1
int HggRazorClass::n_pho1pt = 70;
float HggRazorClass::pho1pt_l = .0;
float HggRazorClass::pho1pt_h = 700.0;

int HggRazorClass::n_pho1eta = 50;
float HggRazorClass::pho1eta_l = -3.0;
float HggRazorClass::pho1eta_h = 3.0;

int HggRazorClass::n_pho1phi = 50;
float HggRazorClass::pho1phi_l = -2*3.1416;
float HggRazorClass::pho1phi_h = 2*3.1416;

int HggRazorClass::n_pho1sigmaIetaIeta = 50;
float HggRazorClass::pho1sigmaIetaIeta_l = .0;
float HggRazorClass::pho1sigmaIetaIeta_h = .06;

int HggRazorClass::n_pho1r9 = 50;
float HggRazorClass::pho1r9_l = 0.0;
float HggRazorClass::pho1r9_h = 1.5;

int HggRazorClass::n_pho1HoverE = 50;
float HggRazorClass::pho1HoverE_l = 0.0;
float HggRazorClass::pho1HoverE_h = .2;

int HggRazorClass::n_pho1sumChargedHadronPt = 50;
float HggRazorClass::pho1sumChargedHadronPt_l = 0.0;
float HggRazorClass::pho1sumChargedHadronPt_h = 30.0;

int HggRazorClass::n_pho1sumNeutralHadronEt = 50;
float HggRazorClass::pho1sumNeutralHadronEt_l = 0.0;
float HggRazorClass::pho1sumNeutralHadronEt_h = 30.0;

int HggRazorClass::n_pho1sumPhotonEt = 50;
float HggRazorClass::pho1sumPhotonEt_l = 0.0;
float HggRazorClass::pho1sumPhotonEt_h = 30.0;

int HggRazorClass::n_pho1sigmaEoverE = 150;
float HggRazorClass::pho1sigmaEoverE_l = .006;
float HggRazorClass::pho1sigmaEoverE_h = .015;

//photon2
int HggRazorClass::n_pho2pt = 70;
float HggRazorClass::pho2pt_l = .0;
float HggRazorClass::pho2pt_h = 700.0;

int HggRazorClass::n_pho2eta = 50;
float HggRazorClass::pho2eta_l = -3.0;
float HggRazorClass::pho2eta_h = 3.0;

int HggRazorClass::n_pho2phi = 50;
float HggRazorClass::pho2phi_l = -2*3.1416;
float HggRazorClass::pho2phi_h = 2*3.1416;

int HggRazorClass::n_pho2sigmaIetaIeta = 50;
float HggRazorClass::pho2sigmaIetaIeta_l = .0;
float HggRazorClass::pho2sigmaIetaIeta_h = .06;

int HggRazorClass::n_pho2r9 = 50;
float HggRazorClass::pho2r9_l = 0.0;
float HggRazorClass::pho2r9_h = 1.5;

int HggRazorClass::n_pho2HoverE = 50;
float HggRazorClass::pho2HoverE_l = 0.0;
float HggRazorClass::pho2HoverE_h = .2;

int HggRazorClass::n_pho2sumChargedHadronPt = 50;
float HggRazorClass::pho2sumChargedHadronPt_l = 0.0;
float HggRazorClass::pho2sumChargedHadronPt_h = 30.0;

int HggRazorClass::n_pho2sumNeutralHadronEt = 50;
float HggRazorClass::pho2sumNeutralHadronEt_l = 0.0;
float HggRazorClass::pho2sumNeutralHadronEt_h = 30.0;

int HggRazorClass::n_pho2sumPhotonEt = 50;
float HggRazorClass::pho2sumPhotonEt_l = 0.0;
float HggRazorClass::pho2sumPhotonEt_h = 30.0;

int HggRazorClass::n_pho2sigmaEoverE = 150;
float HggRazorClass::pho2sigmaEoverE_l = .006;
float HggRazorClass::pho2sigmaEoverE_h = .02;
int HggRazorClass::n_njets = 11;
float HggRazorClass::njets_l = .0;
float HggRazorClass::njets_h = 10;

int HggRazorClass::n_unroll_highPt  = 15;
int HggRazorClass::n_unroll_highRes = 10;

float HggRazorClass::highPt_MR[6] = {150., 200., 300., 500., 1600., 10000.};
float HggRazorClass::highPt_R0[6] = {0.0, 0.05, 0.1, 0.15, 0.2, 2.0};
float HggRazorClass::highPt_R1[5] = {0.0, 0.05, 0.1, 0.15, 2.0};
float HggRazorClass::highPt_R2[4] = {0.0, 0.05, 0.1, 2.0};
float HggRazorClass::highPt_R3[3] = {0.0, 0.05, 2.0};
float HggRazorClass::highPt_R4[2] = {0.0, 2.0};

float HggRazorClass::highRes_MR[5] = {150., 250., 400., 1400., 10000.};
float HggRazorClass::highRes_R0[5] = {0.0, 0.05, 0.1, 0.15, 2.0};
float HggRazorClass::highRes_R1[4] = {0.0, 0.05, 0.1, 2.0};
float HggRazorClass::highRes_R2[3] = {0.0, 0.05, 1.0};
float HggRazorClass::highRes_R3[2] = {0.0, 2.0};

//C u s t o m MR_RSQ_BINNING
//--------------------------
//HighPt
const int N_HighPt = 5;
float MR_HighPt[N_HighPt+1] = {150,200,300,500,1600,3000};
float Rsq_HighPt[N_HighPt+1] = {0.01,0.05,0.10,0.15,0.20,1.00};

//HighRes
const int N_HighRes = 4;
float MR_HighRes[N_HighRes+1] = {150,250,400,1400,3000};
float Rsq_HighRes[N_HighRes+1] = {0.01,0.05,0.10,0.15,1.00};

//Hbb
const int N_Hbb = 2;
float MR_Hbb[N_Hbb+1] = {150,300,3000};
float Rsq_Hbb[N_Hbb+1] = {0.01,0.05,1.00};


#define _debug 1

//TString cut = "";
//EBEB
//TString cut = "mGammaGamma > 230. && pho1passIso == 1 && pho2passIso == 1 && pho1passEleVeto == 1 && pho2passEleVeto == 1 && abs(pho1DefaultSC_Eta) <1.4442 && abs(pho2DefaultSC_Eta) < 1.4442 && pho1Pt> 75. && pho2Pt>75. && HLTDecision[93] == 1";
//TString cut = "mGammaGamma > 230. && pho1passIso == 1 && pho2passIso == 1 && pho1passEleVeto == 1 && pho2passEleVeto == 1 && abs(pho1DefaultSC_Eta) <1.4442 && abs(pho2DefaultSC_Eta) < 1.4442 && pho1Pt> 75. && pho2Pt>75. && HLTDecision[93] == 1 && MR > -99999999 && t1Rsq > -999999999 && 1";

//EBEE
TString cut = "mGammaGamma > 330. && pho1passIso == 1 && pho2passIso == 1 && pho1passEleVeto == 1 && pho2passEleVeto == 1 && pho1Pt> 75. && pho2Pt>75. && ( (abs(pho1DefaultSC_Eta) > 1.566 && abs(pho2DefaultSC_Eta) < 1.4442) || (abs(pho1DefaultSC_Eta) < 1.4442 && abs(pho2DefaultSC_Eta) > 1.566) ) && HLTDecision[93] == 1 && MR > -99999999 && t1Rsq > -999999999 && 1 ";

int main ( int argc, char* argv[] )
{
  std::cout << "[INFO]: Initializing program" << std::endl;
  std::cout << "[INFO]: Hgg Branching Fraction = " << HggRazorClass::GetHggBF() << std::endl;
  //Map Containing the lists for different processes 
  std::string inputFile = ParseCommandLine( argc, argv, "-inputFile=" );
  if (  inputFile == "" )
    {
      std::cerr << "[ERROR]: please provide an input file using --inputFile=<path_to_file>" << std::endl;
      return -1;
    }

  
  std::string eventList = ParseCommandLine( argc, argv, "-eventList=" );
  if (  eventList == "" )
    {
      std::cerr << "[ERROR]: please provide an eventList file using --eventList=<path_to_file>" << std::endl;
      return -1;
    }

  std::ifstream ifs( eventList.c_str(), std::ifstream::in );
  assert(ifs);
  std::cout << "[DEBUG]: input eventList file asserted" << std::endl;
  std::vector< std::pair<long int, long int> > myVect;
  std::map< std::string, double > massMap;
  
  long int run, lumi, event;
  std::string key;
  double mass;
  if ( ifs.is_open() )
    {
      while ( ifs.good() )
	{
	  //ifs >> run >> lumi >> event;
	  ifs >> key >> mass;
	  if ( ifs.eof() ) break;
	  //std::cout << run << " " << lumi << " "  << event << std::endl;
	  //myVect.push_back( std::make_pair( run, event ) );
	  if ( massMap.find( key ) == massMap.end() ) massMap[key] = mass;
	  
	}
      
    }
  else
    {
      std::cout << "Unable to open: " << eventList << std::endl;
    }

  for ( auto tmp : massMap )
    {
      std::cout << tmp.first << " " << tmp.second << std::endl;
    }

    
  TFile* f = new TFile( inputFile.c_str(), "READ");
  std::cout << "[DEBUG]: asserting TFile" << std::endl;
  assert( f );
  std::cout << "[DEBUG]: TFile asserted" << std::endl;
  TTree* tree = (TTree*)f->Get("HggRazor");
  std::cout << "[DEBUG]: asserting TTree" << std::endl;
  assert( tree );
  std::cout << "[DEBUG]: TTree asserted" << std::endl;


  TFile* tmp = new TFile("tmp.root", "recreate");
  //------------------------------------------------
  //C r e a t in g   S e l e c t i o n   O b j e c t
  //------------------------------------------------
  HggRazorClass* hggclass = new HggRazorClass( tree->CopyTree( cut ), "signalHM", "inclusive", false, false );
  hggclass->PrintEventInfo( );
  hggclass->PrintEventInfo( massMap );
  
  return 0;
}
