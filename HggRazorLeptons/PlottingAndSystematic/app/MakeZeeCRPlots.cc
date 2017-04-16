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
int HggRazorClass::n_mgg = 60;
float HggRazorClass::mgg_l = 60.;
float HggRazorClass::mgg_h = 120.;

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
//Zee MR150 Cuts
//-----------------------------------
//EBEB
// TString cut = "MR>150 && pho1passEleVeto == 0 && pho2passEleVeto == 0 && pho1passIso == 1 && pho2passIso == 1 && abs( pho1Eta ) < 1.479 && abs( pho2Eta ) < 1.479 && mGammaGamma>60. && mGammaGamma<120. && pho1Pt>30 && pho2Pt>20";
// TString cut_mc = "MR>150 && pho1passEleVeto == 0 && pho2passEleVeto == 0 && pho1passIso == 1 && pho2passIso == 1 && abs( pho1Eta ) < 1.479 && abs( pho2Eta ) < 1.479 && mGammaGamma>60. && mGammaGamma<120. && pho1Pt>30 && pho2Pt>20";

//EBEE
//TString cut = "pho1passEleVeto == 0 && pho2passEleVeto == 0 && pho1passIso == 1 && pho2passIso == 1 && ( ( abs( pho1Eta ) < 1.479 && abs( pho2Eta ) > 1.479 ) || (abs( pho1Eta ) > 1.479 && abs( pho2Eta ) < 1.479 ) ) && ( HLTDecision[30] == 1 || HLTDecision[31] == 1 ) && mGammaGamma>60. && mGammaGamma<120.";
//TString cut_mc = "pho1passEleVeto == 0 && pho2passEleVeto == 0 && pho1passIso == 1 && pho2passIso == 1 && ( ( abs( pho1Eta ) < 1.479 && abs( pho2Eta ) > 1.479 ) || (abs( pho1Eta ) > 1.479 && abs( pho2Eta ) < 1.479 ) )  && ( HLTDecision[30] == 1 || HLTDecision[31] == 1 ) && mGammaGamma>60. && mGammaGamma<120.";

//EEEE
//TString cut = "pho1passEleVeto == 0 && pho2passEleVeto == 0 && pho1passIso == 1 && pho2passIso == 1 && abs( pho1Eta ) > 1.479 && abs( pho2Eta ) > 1.479 && ( HLTDecision[30] == 1 || HLTDecision[31] == 1 ) && mGammaGamma>60. && mGammaGamma<120.";
//TString cut_mc = "pho1passEleVeto == 0 && pho2passEleVeto == 0 && pho1passIso == 1 && pho2passIso == 1 && abs( pho1Eta ) > 1.479 && abs( pho2Eta ) > 1.479  && ( HLTDecision[30] == 1 || HLTDecision[31] == 1 ) && mGammaGamma>60. && mGammaGamma<120.";

//-----------------------------------
//Zee Inclusive Cuts
//-----------------------------------
//EBEB
TString cut = "pho1passEleVeto == 0 && pho2passEleVeto == 0 && pho1passIso == 1 && pho2passIso == 1 && abs( pho1Eta ) < 1.479 && abs( pho2Eta ) < 1.479 && mGammaGamma>60. && mGammaGamma<120. && pho1Pt>40 && pho2Pt>25";
TString cut_mc = "pho1passEleVeto == 0 && pho2passEleVeto == 0 && pho1passIso == 1 && pho2passIso == 1 && abs( pho1Eta ) < 1.479 && abs( pho2Eta ) < 1.479 && mGammaGamma>60. && mGammaGamma<120. && pho1Pt>40 && pho2Pt>25";


//---------------------
//T r i g g e r   C u t 
//---------------------
//photons
TString triggerCut_80X = "&& HLTDecision[84] ";
TString triggerCut_76X = "&& HLTDecision[84] ";

//--------------------------------
//D i p h o t o n  M a s s   C u t 
//--------------------------------
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
  
  std::string analysisTag = ParseCommandLine( argc, argv, "-analysisTag=" );
  if ( analysisTag == "" )
    {
      std::cerr << "[ERROR]: please provide the analysisTag. Use --analysisTag=<Razor2015_76X,Razor2016_80X>" << std::endl;
      return -1;
    } 

  //get category selection
  std::string category = ParseCommandLine( argc, argv, "-category=" );
  if ( !(category == "" || category == "highpt" || category == "lowpt" || category == "highres" || category == "lowres" ))
    {
      std::cout << "[ERROR]: please provide a valid category: [\"\",\"highpt\",\"lowpt\",\"highres\",\"lowres\"]" << std::endl;
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
  //uses k-factors, defined above
  std::string useKF = ParseCommandLine( argc, argv, "-useKF=" );
  bool _useKF = false;
  if (  useKF == "yes" )
    {
      std::cout << "[INFO]: Using k-factor(s) hardcoded in main application" << std::endl;
      _useKF = true;
    }

  //plots mc and signal shapes 
  std::string signalPlot = ParseCommandLine( argc, argv, "-signalPlot=" );
  bool _signalPlot = false;
  if (  signalPlot == "yes" )
    {
      std::cout << "[INFO]: Will produce MC and signal shape plots" << std::endl;
      _signalPlot = true;
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
  if( map_size != nprocesses )
    {
      std::cerr << "[FATAL ERROR]: map size and nprocesses values are inconsistent!!, Please change nprocesses to map size: " << map_size << std::endl;
      exit( EXIT_FAILURE );
    }
  const int nplots = 4;
  double k_f = 0.796; //Difference in data/mc normalization for inclusive sample
  //double k_f = 0.978; //Difference in data/mc normalization for MR>150 cut

  double lumi = 0;
  if (analysisTag == "Razor2015_76X") lumi = 2300;
  if (analysisTag == "Razor2016_80X") lumi = 12915;

  std::cout << "[INFO]: running inclusive tree mode" << std::endl;
  int ctr = 0;
  Histos histos[nprocesses];
  for( const auto& process : Process() )
    {
      std::string processName = GetProcessString( process );

      //DY control region
      if ( !(process == Process::data || process == Process::dy) ) continue;
    
      //-----------------------------
      // R e t r i e v i n g  T r e e
      //-----------------------------
      chain   = new TChain( "HggRazor" );
      AddTChain( chain, mapList[processName] );
      //need to create temporary root file to store cutTree
      TFile* tmp = new TFile("tmp.root","recreate");

	  
      if ( chain == NULL )
	{
	  std::cout << "[WARNING]: Empty selected tree in process: " << processName << std::endl;
	  continue;
	}
      //------------------------
      //A p p l y i n g  C u t s
      //------------------------
      TString categoryCut = "";
      if (category == "highpt") categoryCut = "&& (pTGammaGamma >= 110)";
      if (category == "lowpt") categoryCut = "&& (pTGammaGamma < 110) ";
      if (category == "highres") categoryCut = "&& (pTGammaGamma < 110 && sigmaMoverM < 0.0085)";
      if (category == "lowres") categoryCut = "&& (pTGammaGamma < 110 && sigmaMoverM >= 0.0085)";
      
      if ( process == Process::data )
	{
	  TString myCut = cut;
	  if (analysisTag == "Razor2016_80X") myCut = cut+categoryCut+triggerCut_80X;
	  if (analysisTag == "Razor2015_76X") myCut = cut+categoryCut+triggerCut_76X;
	  std::cout << "CUT--> " << myCut << std::endl; 
	  cutTree = (TTree*)chain->CopyTree( myCut );
	}
      else
	{
	  TString myCut = cut;
	  if (analysisTag == "Razor2016_80X") myCut = cut+categoryCut;
	  if (analysisTag == "Razor2015_76X") myCut = cut+categoryCut+triggerCut_76X;
	  std::cout << "CUT--> " << myCut << std::endl; 
	  cutTree = (TTree*)chain->CopyTree( myCut ); 
	}
	  
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
      histos[ctr].process = process;
      //-----------------------------
      //Assigning Histograms to Array
      //-----------------------------
      std::cout << "DEB3" << std::endl;
      for ( const auto& htmp : HistoTypes() )
	{
	  std::cout << GetHistoTypesString( htmp ) << std::endl;
	  TH1F h_scale = hggclass->GetHisto( htmp );
	  histos[ctr].AssignHisto( htmp, h_scale );
	}
      std::cout << "DEB4" << std::endl;
      ctr++;
      delete hggclass;
    }
  //---------------
  //P l o t t i n g
  //---------------
  std::cout << "PLOTTING" << std::endl;
  for ( const auto& htmp : HistoTypes() )
    {
      std::string histoName = GetHistoTypesString( htmp );
      //std::cout << "histoName: " << histoName << std::endl;
      stack = new THStack( "hs" , "Hgg Stack " );
      leg = new TLegend( 0.7, 0.58, 0.93, 0.89, NULL, "brNDC" );
      leg2 = new TLegend( 0.7, 0.58, 0.93, 0.89, NULL, "brNDC" );
      bool _isFirstMC = true;
      //std::cout << "deb1: " << histoName << std::endl;
      float NormFactor = 1.0;//Scale mc to unity if required
      for (  int i  = 0; i < nprocesses; i++ )
	{
	  TH1F* tmp_h = new TH1F( histos[i].GetHisto( htmp ) );
	  TH1D* h_s = GetStyledHisto( (TH1D*)tmp_h, histos[i].process );
	  if ( histos[i].process == Process::data )
	    {
	      data = new TH1D ( *h_s );
	      if ( _shapeOnly ) data->Scale(1.0/data->Integral());
	    }
	  else if ( histos[i].process != Process::signal )
	    {
	      h_s->Scale( lumi );
	      if ( _useKF ) h_s->Scale( k_f );
	      std::cout << "stacking " << GetProcessString( histos[i].process ) << std::endl;
	      if ( mc == NULL || _isFirstMC )
		{
		  mc = new TH1D( *h_s );
		  _isFirstMC = false;
		}
	      else
		{
		  mc->Add( h_s );
		}
	    }
	  else
	    {
	      signal = new TH1D ( *h_s );
	      if ( _shapeOnly ) signal->Scale(1.0/signal->Integral());
	    }
	  //std::cout << i << " " << GetProcessString( histos[i].process ) << std::endl;
	  //if ( histos[i].process == Process::data )std::cout << "histo: " << histoName << "data->" << data->Integral() << std::endl;
	  //else std::cout << histoName << "-> " << mc->Integral() << std::endl;
	      
	  AddLegend( h_s, leg, histos[i].process );
	  if (  histos[i].process != Process::data ) AddLegend( h_s, leg2, histos[i].process );
	}
      std::cout << "===================================" << std::endl;
      std::cout << "data-> " << data->Integral() << std::endl;
      std::cout << "MC-> " << mc->Integral() << std::endl;
      std::cout << "===================================" << std::endl;
      NormFactor = mc->Integral();
      if ( _shapeOnly ) mc->Scale(1.0/NormFactor);
      for (  int i  = 0; i < nprocesses; i++ )
	{
	  TH1F* tmp_h = new TH1F( histos[i].GetHisto( htmp ) );
	  TH1D* h_s = GetStyledHisto( (TH1D*)tmp_h, histos[i].process );
	  h_s->Scale( lumi );
	  if ( _useKF ) h_s->Scale( k_f );
	  if ( _shapeOnly ) h_s->Scale(1.0/NormFactor);
	  if ( histos[i].process != Process::data && histos[i].process != Process::signal ) stack->Add( h_s, "histo" );
	}

      if ( _signalPlot ) MakeStackPlotSignal( stack, signal, histoName, "plots/" + histoName + "_" + "Signal", leg2 );
      MakeStackPlot( stack, data, mc, histoName, "plots/" + histoName + "_" + "INCLUSIVE", leg );

    }
  std::cout << "deleting hggclass object" << std::endl;
  delete hggclass;
  
  return 0;
}
