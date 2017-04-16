//C++ INCLUDES
#include <iostream>
#include <map>
#include <stdlib.h>
//ROOT INCLUDES
#include <TString.h>
#include <THStack.h>
//LOCAL INCLUDES
#include "HggTree.hh"
#include "HggRazorClass.hh"
#include "HggAux.hh"
#include "CommandLineInput.hh"
#include "TChainTools.hh"
#include "PlotCosmetics.hh"

// D e f i n e  B i n n i n g
//---------------------------
//H
int HggRazorClass::n_mgg   = 57;
float HggRazorClass::mgg_l = 103.;
float HggRazorClass::mgg_h = 160.;

//HighMass Diphotons
//int HggRazorClass::n_mgg   = 50;
//float HggRazorClass::mgg_l = 230.;
//float HggRazorClass::mgg_h = 1230.;

//Z
//int HggRazorClass::n_mgg = 60;
//float HggRazorClass::mgg_l = 60.;
//float HggRazorClass::mgg_h = 120.;

int HggRazorClass::n_ptgg   = 52;
float HggRazorClass::ptgg_l = 0.;
float HggRazorClass::ptgg_h = 520.;

int HggRazorClass::n_sigmaMoverM   = 80;
float HggRazorClass::sigmaMoverM_l = .0;
float HggRazorClass::sigmaMoverM_h = .04;

int HggRazorClass::n_mr   = 50;
float HggRazorClass::mr_l = 130.;
float HggRazorClass::mr_h = 2630.;

int HggRazorClass::n_rsq   = 60;
float HggRazorClass::rsq_l = .0;
float HggRazorClass::rsq_h = 3.0;

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


//photon1
int HggRazorClass::n_pho1pt   = 70;
float HggRazorClass::pho1pt_l = .0;
float HggRazorClass::pho1pt_h = 700.0;

int HggRazorClass::n_pho1eta   = 30;
float HggRazorClass::pho1eta_l = -3.0;
float HggRazorClass::pho1eta_h = 3.0;

int HggRazorClass::n_pho1phi   = 40;
float HggRazorClass::pho1phi_l = -4.0;
float HggRazorClass::pho1phi_h = 4.0;

int HggRazorClass::n_pho1sigmaIetaIeta   = 50;
float HggRazorClass::pho1sigmaIetaIeta_l = .0;
float HggRazorClass::pho1sigmaIetaIeta_h = .02;

int HggRazorClass::n_pho1r9   = 50;
float HggRazorClass::pho1r9_l = 0.0;
float HggRazorClass::pho1r9_h = 1.5;

int HggRazorClass::n_pho1HoverE   = 30;
float HggRazorClass::pho1HoverE_l = 0.0;
float HggRazorClass::pho1HoverE_h = .06;

int HggRazorClass::n_pho1sumChargedHadronPt   = 50;
float HggRazorClass::pho1sumChargedHadronPt_l = 0.0;
float HggRazorClass::pho1sumChargedHadronPt_h = 5.0;

int HggRazorClass::n_pho1sumNeutralHadronEt   = 50;
float HggRazorClass::pho1sumNeutralHadronEt_l = 0.0;
float HggRazorClass::pho1sumNeutralHadronEt_h = 5.0;

int HggRazorClass::n_pho1sumPhotonEt   = 50;
float HggRazorClass::pho1sumPhotonEt_l = 0.0;
float HggRazorClass::pho1sumPhotonEt_h = 5.0;

int HggRazorClass::n_pho1sigmaEoverE   = 80;
float HggRazorClass::pho1sigmaEoverE_l = .00;
float HggRazorClass::pho1sigmaEoverE_h = .04;

//photon2
int HggRazorClass::n_pho2pt   = 70;
float HggRazorClass::pho2pt_l = .0;
float HggRazorClass::pho2pt_h = 700.0;

int HggRazorClass::n_pho2eta   = 30;
float HggRazorClass::pho2eta_l = -3.0;
float HggRazorClass::pho2eta_h = 3.0;

int HggRazorClass::n_pho2phi   = 40;
float HggRazorClass::pho2phi_l = -4.0;
float HggRazorClass::pho2phi_h = 4.0;

int HggRazorClass::n_pho2sigmaIetaIeta   = 50;
float HggRazorClass::pho2sigmaIetaIeta_l = .0;
float HggRazorClass::pho2sigmaIetaIeta_h = .02;

int HggRazorClass::n_pho2r9   = 50;
float HggRazorClass::pho2r9_l = 0.0;
float HggRazorClass::pho2r9_h = 1.5;

int HggRazorClass::n_pho2HoverE   = 30;
float HggRazorClass::pho2HoverE_l = 0.0;
float HggRazorClass::pho2HoverE_h = .06;

int HggRazorClass::n_pho2sumChargedHadronPt   = 50;
float HggRazorClass::pho2sumChargedHadronPt_l = 0.0;
float HggRazorClass::pho2sumChargedHadronPt_h = 5.0;

int HggRazorClass::n_pho2sumNeutralHadronEt   = 50;
float HggRazorClass::pho2sumNeutralHadronEt_l = 0.0;
float HggRazorClass::pho2sumNeutralHadronEt_h = 5.0;

int HggRazorClass::n_pho2sumPhotonEt   = 50;
float HggRazorClass::pho2sumPhotonEt_l = 0.0;
float HggRazorClass::pho2sumPhotonEt_h = 5.0;

int HggRazorClass::n_pho2sigmaEoverE = 80;
float HggRazorClass::pho2sigmaEoverE_l = .0;
float HggRazorClass::pho2sigmaEoverE_h = .04;

int HggRazorClass::n_njets = 11;
float HggRazorClass::njets_l = .0;
float HggRazorClass::njets_h = 10;


int HggRazorClass::n_met = 11;
float HggRazorClass::met_l = .0;
float HggRazorClass::met_h = 10;

int HggRazorClass::n_mt = 11;
float HggRazorClass::mt_l = .0;
float HggRazorClass::mt_h = 10;

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

float hpt_k[2]  = { 1.0, 1.0};
float hres_k[2] = { 1.0, 1.0};
float lres_k[2] = { 1.0, 1.0};

//-----------------------------------
//A p p l y   B a s e l i n e   C u t
//-----------------------------------

//DATA
//GammaGamma

TString cut = "mGammaGamma>103 && mGammaGamma<160 && abs( pho1SC_Eta ) < 1.4442 && abs( pho2SC_Eta ) < 1.4442 && ( pho1Pt > 40. || pho2Pt > 40. ) && pho1Pt > 25. && pho2Pt> 25. && pho1passEleVeto == 1 && pho2passEleVeto == 1 && pho1passIso == 1 && pho2passIso == 1 && (Flag_HBHENoiseFilter == 1 && Flag_goodVertices == 1 && Flag_eeBadScFilter == 1 && Flag_HBHEIsoNoiseFilter == 1 && Flag_CSCTightHaloFilter == 1 )";

//MC
//GammaGamma
TString cut_mc = "mGammaGamma>103 && mGammaGamma<160 && abs( pho1SC_Eta ) < 1.4442 && abs( pho2SC_Eta ) < 1.4442 && ( pho1Pt > 40. || pho2Pt > 40. ) && pho1Pt > 25. && pho2Pt> 25. && pho1passEleVeto == 1 && pho2passEleVeto == 1 && pho1passIso == 1 && pho2passIso == 1";


//---------------
//Zee control region
//---------------
//Data
//TString cut = "abs( pho1SC_Eta ) < 1.4442 && abs( pho2SC_Eta ) < 1.4442 && ( pho1Pt > 40. || pho2Pt > 40. ) && pho1Pt > 25. && pho2Pt> 25. && mGammaGamma > 75 && mGammaGamma < 120 && pho1passEleVeto == 0 && pho2passEleVeto == 0 && pho1passIso == 1 && pho2passIso == 1 && (Flag_HBHENoiseFilter == 1 && Flag_goodVertices == 1 && Flag_eeBadScFilter == 1 && Flag_HBHEIsoNoiseFilter == 1 && Flag_CSCTightHaloFilter == 1 )";

//MC
//TString cut_mc = "abs( pho1SC_Eta ) < 1.4442 && abs( pho2SC_Eta ) < 1.4442 && ( pho1Pt > 40. || pho2Pt > 40. ) && pho1Pt > 25. && pho2Pt> 25. && mGammaGamma > 75 && mGammaGamma < 120 && pho1passEleVeto == 0 && pho2passEleVeto == 0 && pho1passIso == 1 && pho2passIso == 1 && MR > 150.";


//---------------------
//T r i g g e r   C u t 
//---------------------

TString triggerCut_80X = "&& (HLTDecision[82] || HLTDecision[83] || HLTDecision[93]) ";
TString triggerCut_76X = "&& (HLTDecision[82] || HLTDecision[83] || HLTDecision[93]) ";

//TString triggerCut_80X = "&& (  HLTDecision[27] || HLTDecision[44] || HLTDecision[45] || HLTDecision[217] )";
//TString triggerCut_76X = "&& (  HLTDecision[27] || HLTDecision[44] || HLTDecision[45] || HLTDecision[217] )";

//TString triggerCut_80X = "&& (  HLTDecision[84] )";
//TString triggerCut_76X = "&& (  HLTDecision[84] )";

//TString triggerCut_80X = "&& ( 1 )";
//TString triggerCut_76X = "&& ( 1 )";


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
  

  //provides shape comparison
  std::string shapeOnly = ParseCommandLine( argc, argv, "-shapeOnly=" );
  bool _shapeOnly = false;
  if (  shapeOnly == "yes" )
    {
      std::cout << "[INFO]: re-scaling all histograms to unity" << std::endl;
      _shapeOnly = true;
    }
  
  std::cout << "=================================" << std::endl;
  std::cout << "===========set parameters========" << std::endl;
  std::cout << "[INFO]: input file: " << inputFile << std::endl;
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
  TLegend* leg2;
  TH1D* data;
  TH1D* signal;
  TH1D* mc;
  TH1D* mc2 = new TH1D();

  int map_size = mapList.size();
  const int nprocesses = 2;//mc+data
  //check nprocesses and map_size consistency
  const int nplots = 4;
  // double k_f = 1.78*1.05;//Difference in data/mc normalization
  //double k_f = 1.62*1.05;//Difference in data/mc normalization
  //double k_f = 1.3291653769;
  double k_f = 2.0014889911;
  double lumi = 0;
  
  //if (analysisTag == "Razor2015_76X") lumi = 2300;
  //if (analysisTag == "Razor2016_80X") lumi = 4000;
  //if (analysisTag == "Razor2016_80X") lumi = 36200.;
  
  std::cout << "[INFO]: running inclusive tree mode" << std::endl;
  int ctr = 0;
  Histos histos[nprocesses];
  for( const auto& process : mapList )
    {
      std::string processName = process.first;
      std::cout << "[INFO] PROCESS: " << processName << " ,process #: " << ctr << std::endl;
      //DY control region
      //if ( !(process == Process::data || process == Process::dy) ) continue;

      //Diphoton
      
      /*(if ( !(process == Process::data || process == Process::diphoton || process == Process::gammaJet 
	     || process == Process::ggH  || process == Process::vbfH || process == Process::vH || process == Process::ttH)
	   ) continue;
      */

      
      //Diphoton with Signal
      /*if ( !(process == Process::data || process == Process::signal || process == Process::diphoton || process == Process::gammaJet
	|| process == Process::ggH  || process == Process::vbfH || process == Process::vH || process == Process::ttH) ) continue;
	std::cout << "[INFO] PROCESS: " << processName << " ,process #: " << ctr << std::endl;*/

      //-----------------------------
      // R e t r i e v i n g  T r e e
      //-----------------------------
      chain   = new TChain( "HggRazor" );
      std::cout << "DEBUG: " << mapList[processName] << std::endl;
      AddTChain( chain, mapList[processName] );
      //need to create temporary root file to store cutTree
      TFile* tmp = new TFile("tmp.root","recreate");

      //-------------------
      //CHECK CHAINING
      //-------------------
      if ( chain == NULL )
	{
	  std::cout << "[WARNING]: Empty selected tree in process: " << processName << std::endl;
	  continue;
	}
      //------------------------
      //A p p l y i n g  C u t s
      //------------------------
      TString myCut = cut;
      myCut = cut+triggerCut_80X;
      std::cout << "CUT--> " << myCut << std::endl; 
      cutTree = (TTree*)chain->CopyTree( myCut );
      //-------------------
      //CHECK CUT RESULT
      //-------------------
      if ( cutTree == NULL )
	{
	  std::cout << "[WARNING]: Empty selected tree in process: " << processName << std::endl;
	  continue;
	}
      
      std::cout << "[INFO]: reduced TTree has been created" << std::endl;
      //------------------------------------------------
      //C r e a t in g   S e l e c t i o n   O b j e c t
      //------------------------------------------------
      hggclass = new HggRazorClass( cutTree, processName, "INCLUSIVE", true, true );
      hggclass->InitMrRsqCustomHisto( N_HighRes, MR_HighRes, N_HighRes, Rsq_HighRes );
      //Creating Histos
      hggclass->Loop();
      //Assigning Histos
      //histos[ctr].process = process;
      //-----------------------------
      //Assigning Histograms to Array
      //-----------------------------
      histos[ctr].processName = processName;
      for ( const auto& htmp : HistoTypes() )
	{
	  std::cout << GetHistoTypesString( htmp ) << std::endl;
	  TH1F h_scale = hggclass->GetHisto( htmp );
	  histos[ctr].AssignHisto( htmp, h_scale );
	}
      ctr++;
      delete hggclass;
    }
  
  
  //---------------
  //P l o t t i n g
  //---------------
  std::cout << "[INFO]: Now Plotting" << std::endl;
  for ( const auto& htmp : HistoTypes() )
    {
      std::string histoName = GetHistoTypesString( htmp );
      //std::cout << "histoName: " << histoName << std::endl;
      leg = new TLegend( 0.7, 0.58, 0.93, 0.89, NULL, "brNDC" );
      leg2 = new TLegend( 0.7, 0.58, 0.93, 0.89, NULL, "brNDC" );
      TH1D* HistosPlot[nprocesses];
      
      for (  int i  = 0; i < nprocesses; i++ )
	{
	  TH1F* tmp_h = new TH1F( histos[i].GetHisto( htmp ) );
	  TH1D* h_s = GetStyledHisto( (TH1D*)tmp_h, histos[i].process );

	  h_s->SetMarkerStyle(20);
	  h_s->SetStats(0);
	  switch (i)
	    {
	    case 0:
	      h_s->SetLineColor(kBlue);
	      h_s->SetMarkerColor(kBlue);
	      break;
	    case 1:
	      h_s->SetLineColor(kRed);
	      h_s->SetMarkerColor(kRed);
	      break;
	    default:
	      h_s->SetLineColor(kBlack);
	      h_s->SetMarkerColor(kBlack);
	      break;
	    }
	  leg->AddEntry( h_s, histos[i].processName, "lep" );
	  HistosPlot[i] = h_s;
	  HistosPlot[i]->Scale( 1.0/HistosPlot[i]->Integral() );
	}
      
      std::cout << "===================================" << std::endl;
      std::cout << "===================================" << std::endl;
     
      //Make Plots
      PlotSameCanvas( HistosPlot, nprocesses, histoName, "plots/" + histoName + "_" + "INCLUSIVE", leg );
      //MakeStackPlot( stack, data, mc, histoName, "plots/" + histoName + "_" + "INCLUSIVE", leg );	  
    } //loop over histograms

  std::cout << "deleting hggclass object" << std::endl;
  //delete hggclass;
  return 0;
}
