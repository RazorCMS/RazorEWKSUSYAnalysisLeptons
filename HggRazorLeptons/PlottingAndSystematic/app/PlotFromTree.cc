//C++ INCLUDES
#include <iostream>
#include <map>
//ROOT INCLUDES
#include <TString.h>
#include <THStack.h>
#include <TMath.h>
//LOCAL INCLUDES
#include "HggTree.hh"
#include "HggRazorClass.hh"
#include "HggAux.hh"
#include "CommandLineInput.hh"
#include "TChainTools.hh"
#include "PlotCosmetics.hh"

// D e f i n e  B i n n i n g
//---------------------------
int HggRazorClass::n_mgg = 38;
float HggRazorClass::mgg_l = 103.;
float HggRazorClass::mgg_h = 160.;
/*
int HggRazorClass::n_mgg = 5;
float HggRazorClass::mgg_l = 117.5;
float HggRazorClass::mgg_h = 132.5;
*/
int HggRazorClass::n_ptgg = 70;
float HggRazorClass::ptgg_l = 20.;
float HggRazorClass::ptgg_h = 720.;

int HggRazorClass::n_sigmaMoverM = 200;
float HggRazorClass::sigmaMoverM_l = .0;
float HggRazorClass::sigmaMoverM_h = .05;

int HggRazorClass::n_mr = 160;
float HggRazorClass::mr_l = 130.;
float HggRazorClass::mr_h = 8130.;

int HggRazorClass::n_rsq = 125;
float HggRazorClass::rsq_l = .0;
float HggRazorClass::rsq_h = 5.0;

int HggRazorClass::n_unroll_highPt  = 15;
int HggRazorClass::n_unroll_highRes = 10;

float HggRazorClass::highPt_MR[6] = {150., 200., 300., 500., 1600., 3000.};
float HggRazorClass::highPt_R0[6] = {0.0, 0.05, 0.1, 0.15, 0.2, 2.0};
float HggRazorClass::highPt_R1[5] = {0.0, 0.05, 0.1, 0.15, 2.0};
float HggRazorClass::highPt_R2[4] = {0.0, 0.05, 0.1, 2.0};
float HggRazorClass::highPt_R3[3] = {0.0, 0.05, 2.0};
float HggRazorClass::highPt_R4[2] = {0.0, 2.0};

float HggRazorClass::highRes_MR[5] = {150., 250., 400., 1400., 3000.};
float HggRazorClass::highRes_R0[5] = {0.0, 0.05, 0.1, 0.15, 2.0};
float HggRazorClass::highRes_R1[4] = {0.0, 0.05, 0.1, 2.0};
float HggRazorClass::highRes_R2[3] = {0.0, 0.05, 1.0};
float HggRazorClass::highRes_R3[2] = {0.0, 2.0};

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
float HggRazorClass::pho1sigmaIetaIeta_l = -3.0;
float HggRazorClass::pho1sigmaIetaIeta_h = 3.0;

int HggRazorClass::n_pho1r9 = 50;
float HggRazorClass::pho1r9_l = 0.0;
float HggRazorClass::pho1r9_h = 1.5;

int HggRazorClass::n_pho1HoverE = 50;
float HggRazorClass::pho1HoverE_l = -3.0;
float HggRazorClass::pho1HoverE_h = 3.0;

int HggRazorClass::n_pho1sumChargedHadronPt = 50;
float HggRazorClass::pho1sumChargedHadronPt_l = -3.0;
float HggRazorClass::pho1sumChargedHadronPt_h = 3.0;

int HggRazorClass::n_pho1sumNeutralHadronEt = 50;
float HggRazorClass::pho1sumNeutralHadronEt_l = -3.0;
float HggRazorClass::pho1sumNeutralHadronEt_h = 3.0;

int HggRazorClass::n_pho1sumPhotonEt = 50;
float HggRazorClass::pho1sumPhotonEt_l = -3.0;
float HggRazorClass::pho1sumPhotonEt_h = 3.0;

int HggRazorClass::n_pho1sigmaEoverE = 50;
float HggRazorClass::pho1sigmaEoverE_l = -3.0;
float HggRazorClass::pho1sigmaEoverE_h = 3.0;

int HggRazorClass::n_pho2pt = 200;
float HggRazorClass::pho2pt_l = .0;
float HggRazorClass::pho2pt_h = 1000.0;

int HggRazorClass::n_pho2eta = 50;
float HggRazorClass::pho2eta_l = -3.0;
float HggRazorClass::pho2eta_h = 3.0;

int HggRazorClass::n_pho2phi = 50;
float HggRazorClass::pho2phi_l = -2*3.1416;
float HggRazorClass::pho2phi_h = 2*3.1416;

int HggRazorClass::n_pho2sigmaIetaIeta = 50;
float HggRazorClass::pho2sigmaIetaIeta_l = -3.0;
float HggRazorClass::pho2sigmaIetaIeta_h = 3.0;

int HggRazorClass::n_pho2r9 = 50;
float HggRazorClass::pho2r9_l = 0.0;
float HggRazorClass::pho2r9_h = 1.5;

int HggRazorClass::n_pho2HoverE = 50;
float HggRazorClass::pho2HoverE_l = -3.0;
float HggRazorClass::pho2HoverE_h = 3.0;

int HggRazorClass::n_pho2sumChargedHadronPt = 50;
float HggRazorClass::pho2sumChargedHadronPt_l = -3.0;
float HggRazorClass::pho2sumChargedHadronPt_h = 3.0;

int HggRazorClass::n_pho2sumNeutralHadronEt = 50;
float HggRazorClass::pho2sumNeutralHadronEt_l = -3.0;
float HggRazorClass::pho2sumNeutralHadronEt_h = 3.0;

int HggRazorClass::n_pho2sumPhotonEt = 50;
float HggRazorClass::pho2sumPhotonEt_l = -3.0;
float HggRazorClass::pho2sumPhotonEt_h = 3.0;

int HggRazorClass::n_pho2sigmaEoverE = 50;
float HggRazorClass::pho2sigmaEoverE_l = -3.0;
float HggRazorClass::pho2sigmaEoverE_h = 3.0;


int HggRazorClass::n_njets = 11;
float HggRazorClass::njets_l = .0;
float HggRazorClass::njets_h = 10;

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

float hpt_k[2]  = { 1.44, 1.69};
float hres_k[2] = { 1.03, 1.14};
float lres_k[2] = { 1.02, 1.45};
//A p p l y   B a s e l i n e   C u t
//-----------------------------------
//TString cut = "MR > 0.0 && t1Rsq > 0.0 && abs( pho1Eta ) < 1.44 && abs( pho2Eta ) < 1.44 && ( pho1Pt > 40. || pho2Pt > 40. ) && pho1Pt > 25. && pho2Pt> 25. && trigger == 1";
TString cut = "MR > 0.0 && Rsq > 0.0 && abs( pho1Eta ) < 1.44 && abs( pho2Eta ) < 1.44 && ( pho1Pt > 40. || pho2Pt > 40. ) && pho1Pt > 25. && pho2Pt> 25. && pTGammaGamma>20 && mGammaGamma>103 && mGammaGamma<160";

//TString mggCut = "mGammaGamma > 117. 5 && mGammaGamma < 132.5";
TString mggCut = "1";

#define _debug 1

int main ( int argc, char* argv[] )
{
  std::cout << "[INFO]: Initializing program" << std::endl;
  std::cout << "[INFO]: Hgg Branching Fraction = " << HggRazorClass::GetHggBF() << std::endl;
  //Map Containing the lists for different processes 
  std::map< std::string, std::string > mapList;
  std::string inputFile = ParseCommandLine( argc, argv, "-inputFile=" );
  if (  inputFile == "" )
    {
      std::cerr << "[ERROR]: please provide an input file using --inputFile=<path_to_file>" << std::endl;
      return -1;
    }

  std::string run = ParseCommandLine( argc, argv, "-run=" );
  if (  run == "" )
    {
      std::cout << "[WARNING]: please provide a valid run, use --run=<run1/run2>" << std::endl;
      run = "run1";
    }

  std::cout << "=================================" << std::endl;
  std::cout << "===========set parameters========" << std::endl;
  std::cout << "[INFO]: input file: " << inputFile << std::endl;
  std::cout << "[INFO]: run: " << run << std::endl;
  std::cout << "=================================" << std::endl;
  
  FillMapList( mapList, inputFile );
  if ( _debug ) std::cout << "[DEBUG]: map size: " << mapList.size() << std::endl;
  
  for( auto& myMap : mapList )
    {
      if ( _debug ) std::cout << "[DEBUG]: first: " << myMap.first << " second: " << myMap.second << std::endl;
    }
  
  TFile* f;
  TTree* tree;
  TChain* chain;
  TTree* cutTree;
  HggRazorClass* hggclass;
  THStack* stack;
  TLegend* leg;
  TH1D* data;
  TH1D* mc;

  const int nprocesses = 6;
  const int nplots = 4;
  double k_f = 1.0;
  const double lumi_frac = 0.253; // (5./19.8)
  const int mod = 0; 
  for( const auto& box : Boxes() )
    {
      std::string boxName = GetBoxString( box );
      int ctr = 0;
      Histos histos[nprocesses];
      
      for( const auto& process : Process() )
	{
	  std::string processName = GetProcessString( process );
	  if ( process == Process::data && run == "run2" )
	    {
	      std::cout << "[INFO]: run2 will skip data category" << std::endl;
	      continue;
	    }
	  if ( process == Process::qcd ) continue;
	  //if ( process == Process::qcd || process == Process::gammaJet || process == Process::diphoton ) continue;
	  std::cout << "====================================" << std::endl;
	  std::cout << "[INFO]: process name: " << processName << std::endl;
	  std::cout << "====================================" << std::endl;


	  if ( process == Process::gammaJet || process == Process::diphoton || process == Process::qcd )
	    {
	      //13/8 TeV
	      k_f = hres_k[mod]*lumi_frac;
	      if ( box == Boxes::HighPt ) k_f = hpt_k[mod]*lumi_frac;
	      if ( box == Boxes::LowRes ) k_f = lres_k[mod]*lumi_frac;
	    }
	  
	  // R e t r i e v i n g  T r e e
	  //-----------------------------
	  chain   = new TChain( boxName.c_str() );
	  AddTChain( chain, mapList[processName] );
	  
	  //need to create temporary root file to store cutTree
	  TFile* tmp = new TFile("tmp","recreate");
	  //A p p l y i n g  C u t s
	  //------------------------
	  cutTree = (TTree*)chain->CopyTree( cut + " && " + mggCut );
	  if ( cutTree == NULL )
	    {
	      std::cout << "[WARNING]: Empty selected tree: " << boxName << std::endl;
	      continue;
	    }
	  //C r e a t in g   S e l e c t i o n   O b j e c t
	  //------------------------------------------------
	  hggclass = new HggRazorClass( cutTree, processName, boxName, false, false );
	  if ( box == Boxes::HighPt )
	    {
	      hggclass->InitMrRsqCustomHisto( N_HighPt, MR_HighPt, N_HighPt, Rsq_HighPt );
	    }
	  else if ( box == Boxes::HighRes || box == Boxes::LowRes )
	    {
	      hggclass->InitMrRsqCustomHisto( N_HighRes, MR_HighRes, N_HighRes, Rsq_HighRes );
	    }
	  else if( box == Boxes::Hbb || box == Boxes::Zbb )
	    {
	      hggclass->InitMrRsqCustomHisto( N_Hbb, MR_Hbb, N_Hbb, Rsq_Hbb );
	    }
	  else
	    {
	      std::cout << "[WARNING]: Undefined box->" << std::endl;
	    }
	  //Creating Histos
	  hggclass->Loop();
	  //Assigning Histos
	  histos[ctr].process = process;
	  for ( const auto& htmp : HistoTypes() )
	    {
	      TH1F h_scale = hggclass->GetHisto( htmp );
	      if ( run == "run2" ) h_scale.Scale( k_f ); 
	      histos[ctr].AssignHisto( htmp, h_scale );
	    }
	  ctr++;
	  //hggclass->WriteOutput( boxName );
	  //Cosmetics
	}
      //Plotting
      for ( const auto& htmp : HistoTypes() )
	{
	  std::string histoName = GetHistoTypesString( htmp );
	  std::cout << "making " <<  histoName << std::endl;
	  stack = new THStack( "hs" , "Hgg Stack " );
	  leg = new TLegend( 0.7, 0.58, 0.93, 0.89, NULL, "brNDC" );
	  bool _isFirstMC = true;
	  for (  int i  = 0; i < nprocesses; i++ )
	    {
	      std::cout << "DEB "<< std::endl;
	      TH1F* tmp_h = new TH1F( histos[i].GetHisto( htmp ) );
	      std::cout << "DEB "<< std::endl;
	      TH1D* h_s = GetStyledHisto( (TH1D*)tmp_h, histos[i].process );
	      std::cout << "DEB "<< std::endl;
	      if ( histos[i].process == Process::data )
		{
		  std::cout << "DEBdata "<< std::endl;
		  data = new TH1D ( *h_s ); 
		}
	      else
		{
		  stack->Add( h_s, "histo" );
		  if ( mc == NULL || _isFirstMC )
		    {
		      std::cout << "creating mc" << std::endl;
		      mc = new TH1D( *h_s );
		      _isFirstMC = false;
		    }
		  else
		    {
		      std::cout << "DEBmc "<< std::endl;
		      mc->Add( h_s );
		    }
		}
	      std::cout << i << " " << GetProcessString( histos[i].process ) << std::endl;
	      AddLegend( h_s, leg, histos[i].process );
	    }
	  if ( run == "run2" )
	    {
	      //MakeStackPlot( stack, histoName, "plots/13TeV/" + histoName + "_" + boxName + "_Inclusive_Resonant", leg );
	      //MakeStackPlot( stack, histoName, "plots/13TeV/" + histoName + "_" + boxName + "_Mr250Rsq0p05_Resonant", leg );
	      //MakeStackPlot( stack, histoName, "plots/13TeV/Hybrid/" + histoName + "_" + boxName + "_Inclusive_Resonant", leg );
	      //MakeStackPlot( stack, histoName, "plots/13TeV/Hybrid/Resonant/" + histoName + "_" + boxName + "_Mr400_Rsq0p05_Resonant", leg );
	      //MakeStackPlot( stack, histoName, "plots/13TeV/Hybrid/Full/" + histoName + "_" + boxName + "_Mr200_Rsq0p02_Full", leg );
	      MakeStackPlot( stack, histoName, "plots/13TeV/Hybrid/Full/" + histoName + "_" + boxName + "_Inclusive_Full", leg );
	    }
	  else
	    {
	      //MakeStackPlot( stack, data, mc, histoName, "plots/8TeV/" + histoName + "_" + boxName + "_Mr250_Rsq0p035", leg );
	      MakeStackPlot( stack, data, mc, histoName, "plots/8TeV/" + histoName + "_" + boxName + "_Inclusive", leg );
	    }
	  std::cout << "leaving " <<  histoName << std::endl;
	  delete leg;
	  delete stack;
	  delete mc;
	  //mc = NULL;
	  if ( run != "run2" ) delete data;
	}
    }
  return 0;
}
