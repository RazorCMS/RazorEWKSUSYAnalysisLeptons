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

int HggRazorClass::n_ptgg   = 26;
float HggRazorClass::ptgg_l = 0.;
float HggRazorClass::ptgg_h = 520.;

int HggRazorClass::n_sigmaMoverM   = 80;
float HggRazorClass::sigmaMoverM_l = .0;
float HggRazorClass::sigmaMoverM_h = .04;

int HggRazorClass::n_mr   = 25;
float HggRazorClass::mr_l = 0.;
float HggRazorClass::mr_h = 2500.;

int HggRazorClass::n_rsq   = 30;
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

int HggRazorClass::n_met = 30;
float HggRazorClass::met_l = .0;
float HggRazorClass::met_h = 600;

int HggRazorClass::n_mt = 15;
float HggRazorClass::mt_l = .0;
float HggRazorClass::mt_h = 150;


int HggRazorClass::n_ptlep = 20;
float HggRazorClass::ptlep_l = .0;
float HggRazorClass::ptlep_h = 400;

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
/*
//DATA
//GammaGamma

TString cut = "mGammaGamma > 103. && mGammaGamma < 160. && abs( pho1SC_Eta ) < 1.4442 && abs( pho2SC_Eta ) < 1.4442 && ( pho1Pt > 40. || pho2Pt > 40. ) && pho1Pt > 25. && pho2Pt> 25. && pho1passEleVeto == 1 && pho2passEleVeto == 1 && pho1passIso == 1 && pho2passIso == 1 && (Flag_HBHENoiseFilter == 1 && Flag_goodVertices == 1 && Flag_eeBadScFilter == 1 && Flag_HBHEIsoNoiseFilter == 1 && Flag_CSCTightHaloFilter == 1 )";

//MC
//GammaGamma
TString cut_mc = "mGammaGamma > 103. && mGammaGamma < 160. && abs( pho1SC_Eta ) < 1.4442 && abs( pho2SC_Eta ) < 1.4442 && ( pho1Pt > 40. || pho2Pt > 40. ) && pho1Pt > 25. && pho2Pt> 25. && pho1passEleVeto == 1 && pho2passEleVeto == 1 && pho1passIso == 1 && pho2passIso == 1  ";
*/
/*
//highpt

//Data
TString cut = "mGammaGamma > 103. && mGammaGamma < 160. && abs( pho1SC_Eta ) < 1.4442 && abs( pho2SC_Eta ) < 1.4442 && ( pho1Pt > 40. || pho2Pt > 40. ) && pho1Pt > 25. && pho2Pt> 25. && pho1passEleVeto == 1 && pho2passEleVeto == 1 && pho1passIso == 1 && pho2passIso == 1 && (Flag_HBHENoiseFilter == 1 && Flag_goodVertices == 1 && Flag_eeBadScFilter == 1 && Flag_HBHEIsoNoiseFilter == 1 && Flag_CSCTightHaloFilter == 1 ) && MR>150 && pTGammaGamma>110. && box>4 ";

//MC
TString cut_mc = "mGammaGamma > 103. && mGammaGamma < 160. && abs( pho1SC_Eta ) < 1.4442 && abs( pho2SC_Eta ) < 1.4442 && ( pho1Pt > 40. || pho2Pt > 40. ) && pho1Pt > 25. && pho2Pt> 25. && pho1passEleVeto == 1 && pho2passEleVeto == 1 && pho1passIso == 1 && pho2passIso == 1 && MR>150 && pTGammaGamma>110. && box>4 ";
*/


/*
//hbb

//Data
TString cut = "mGammaGamma > 103. && mGammaGamma < 160. && abs( pho1SC_Eta ) < 1.4442 && abs( pho2SC_Eta ) < 1.4442 && ( pho1Pt > 40. || pho2Pt > 40. ) && pho1Pt > 25. && pho2Pt> 25. && pho1passEleVeto == 1 && pho2passEleVeto == 1 && pho1passIso == 1 && pho2passIso == 1 && (Flag_HBHENoiseFilter == 1 && Flag_goodVertices == 1 && Flag_eeBadScFilter == 1 && Flag_HBHEIsoNoiseFilter == 1 && Flag_CSCTightHaloFilter == 1 ) && MR > 150. && pTGammaGamma < 110 && abs(mbbH-125.)<15 && box>4 ";

//MC
TString cut_mc = "mGammaGamma > 103. && mGammaGamma < 160. && abs( pho1SC_Eta ) < 1.4442 && abs( pho2SC_Eta ) < 1.4442 && ( pho1Pt > 40. || pho2Pt > 40. ) && pho1Pt > 25. && pho2Pt> 25. && pho1passEleVeto == 1 && pho2passEleVeto == 1 && pho1passIso == 1 && pho2passIso == 1 && MR > 150. && pTGammaGamma < 110 && abs(mbbH-125.)<15 && box>4";
*/

/*
//Zbb
//Data
TString cut = "mGammaGamma > 103. && mGammaGamma < 160. && abs( pho1SC_Eta ) < 1.4442 && abs( pho2SC_Eta ) < 1.4442 && ( pho1Pt > 40. || pho2Pt > 40. ) && pho1Pt > 25. && pho2Pt> 25. && pho1passEleVeto == 1 && pho2passEleVeto == 1 && pho1passIso == 1 && pho2passIso == 1 && (Flag_HBHENoiseFilter == 1 && Flag_goodVertices == 1 && Flag_eeBadScFilter == 1 && Flag_HBHEIsoNoiseFilter == 1 && Flag_CSCTightHaloFilter == 1 ) && MR > 150. && pTGammaGamma < 110 && abs(mbbH-125.)>=15 && abs(mbbZ-91.)<15 && box>4 ";

//MC
TString cut_mc = "mGammaGamma > 103. && mGammaGamma < 160. && abs( pho1SC_Eta ) < 1.4442 && abs( pho2SC_Eta ) < 1.4442 && ( pho1Pt > 40. || pho2Pt > 40. ) && pho1Pt > 25. && pho2Pt> 25. && pho1passEleVeto == 1 && pho2passEleVeto == 1 && pho1passIso == 1 && pho2passIso == 1 && MR > 150. && pTGammaGamma < 110 && abs(mbbH-125.)>=15 && abs(mbbZ-91.)<15 && box>4 ";
*/

/*
//highres
//Data
TString cut = "mGammaGamma > 103. && mGammaGamma < 160. && abs( pho1SC_Eta ) < 1.4442 && abs( pho2SC_Eta ) < 1.4442 && ( pho1Pt > 40. || pho2Pt > 40. ) && pho1Pt > 25. && pho2Pt> 25. && pho1passEleVeto == 1 && pho2passEleVeto == 1 && pho1passIso == 1 && pho2passIso == 1 && (Flag_HBHENoiseFilter == 1 && Flag_goodVertices == 1 && Flag_eeBadScFilter == 1 && Flag_HBHEIsoNoiseFilter == 1 && Flag_CSCTightHaloFilter == 1 ) && MR > 150. && pTGammaGamma < 110 && abs(mbbH-125.)>=15 && abs(mbbZ-91.)>=15 && sigmaMoverM<0.0085 && box>4 ";

//MC
TString cut_mc = "mGammaGamma > 103. && mGammaGamma < 160. && abs( pho1SC_Eta ) < 1.4442 && abs( pho2SC_Eta ) < 1.4442 && ( pho1Pt > 40. || pho2Pt > 40. ) && pho1Pt > 25. && pho2Pt> 25. && pho1passEleVeto == 1 && pho2passEleVeto == 1 && pho1passIso == 1 && pho2passIso == 1 && MR > 150. && pTGammaGamma < 110 && abs(mbbH-125.)>=15 && abs(mbbZ-91.)>=15 && sigmaMoverM<0.0085 && box>4 ";
*/

/*
//lowres

//Data
TString cut = "mGammaGamma > 103. && mGammaGamma < 160. && abs( pho1SC_Eta ) < 1.4442 && abs( pho2SC_Eta ) < 1.4442 && ( pho1Pt > 40. || pho2Pt > 40. ) && pho1Pt > 25. && pho2Pt> 25. && pho1passEleVeto == 1 && pho2passEleVeto == 1 && pho1passIso == 1 && pho2passIso == 1 && (Flag_HBHENoiseFilter == 1 && Flag_goodVertices == 1 && Flag_eeBadScFilter == 1 && Flag_HBHEIsoNoiseFilter == 1 && Flag_CSCTightHaloFilter == 1 ) && MR > 150. && pTGammaGamma < 110 && abs(mbbH-125.)>=15 && abs(mbbZ-91.)>=15 && sigmaMoverM>=0.0085 && box>4 ";

//MC
TString cut_mc = "mGammaGamma > 103. && mGammaGamma < 160. && abs( pho1SC_Eta ) < 1.4442 && abs( pho2SC_Eta ) < 1.4442 && ( pho1Pt > 40. || pho2Pt > 40. ) && pho1Pt > 25. && pho2Pt> 25. && pho1passEleVeto == 1 && pho2passEleVeto == 1 && pho1passIso == 1 && pho2passIso == 1 && MR > 150. && pTGammaGamma < 110 && abs(mbbH-125.)>=15 && abs(mbbZ-91.)>=15 && sigmaMoverM>=0.0085 && box>4 ";
*/

//---------------
//Zee control region
//---------------
//Data
//TString cut = "abs( pho1SC_Eta ) < 1.4442 && abs( pho2SC_Eta ) < 1.4442 && ( pho1Pt > 40. || pho2Pt > 40. ) && pho1Pt > 25. && pho2Pt> 25. && mGammaGamma > 75 && mGammaGamma < 120 && pho1passEleVeto == 0 && pho2passEleVeto == 0 && pho1passIso == 1 && pho2passIso == 1 && (Flag_HBHENoiseFilter == 1 && Flag_goodVertices == 1 && Flag_eeBadScFilter == 1 && Flag_HBHEIsoNoiseFilter == 1 && Flag_CSCTightHaloFilter == 1 ) && MR > 150. && pTGammaGamma < 110 && abs(mbbH_L-125.)>=15 && abs(mbbZ_L-91.)>=15";

//MC
//TString cut_mc = "abs( pho1SC_Eta ) < 1.4442 && abs( pho2SC_Eta ) < 1.4442 && ( pho1Pt > 40. || pho2Pt > 40. ) && pho1Pt > 25. && pho2Pt> 25. && mGammaGamma > 75 && mGammaGamma < 120 && pho1passEleVeto == 0 && pho2passEleVeto == 0 && pho1passIso == 1 && pho2passIso == 1 && MR > 150. && pTGammaGamma < 110 && abs(mbbH_L-125.)>=15 && abs(mbbZ_L-91.)>=15";

/*
//Data
TString cut = "abs( pho1SC_Eta ) < 1.4442 && abs( pho2SC_Eta ) < 1.4442 && ( pho1Pt > 40. || pho2Pt > 40. ) && pho1Pt > 25. && pho2Pt> 25. && mGammaGamma > 75 && mGammaGamma < 120 && pho1passEleVeto == 0 && pho2passEleVeto == 0 && pho1passIso == 1 && pho2passIso == 1 && (Flag_HBHENoiseFilter == 1 && Flag_goodVertices == 1 && Flag_eeBadScFilter == 1 && Flag_HBHEIsoNoiseFilter == 1 && Flag_CSCTightHaloFilter == 1 ) && MR > 150. && pTGammaGamma < 110 && abs(mbbH_L-125.)>=15 && abs(mbbZ_L-91.)>=15 && sigmaMoverM >= 0.0085";

//MC
TString cut_mc = "abs( pho1SC_Eta ) < 1.4442 && abs( pho2SC_Eta ) < 1.4442 && ( pho1Pt > 40. || pho2Pt > 40. ) && pho1Pt > 25. && pho2Pt> 25. && mGammaGamma > 75 && mGammaGamma < 120 && pho1passEleVeto == 0 && pho2passEleVeto == 0 && pho1passIso == 1 && pho2passIso == 1 && MR > 150. && pTGammaGamma < 110 && abs(mbbH_L-125.)>=15 && abs(mbbZ_L-91.)>=15 && sigmaMoverM >= 0.0085";
*/




//--------------------------------
//D i p h o t o n  M a s s   C u t 
//--------------------------------
TString mggCut = "1";

#define _debug 0

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
  
  std::string inputType = ParseCommandLine( argc, argv, "-inputType=" );
  if (  inputType == "" )
    {
      std::cerr << "[WARNING]: please provide an input type using --inputType=<diphoton/leptons/Zee>" << std::endl;
      inputType = "diphoton";
    }
  
  std::string analysisTag = ParseCommandLine( argc, argv, "-analysisTag=" );
  if ( analysisTag == "" )
    {
      std::cerr << "[ERROR]: please provide the analysisTag. Use --analysisTag=<Razor2015_76X,Razor2016_80X>" << std::endl;
      return -1;
    } 


  std::string treeType = ParseCommandLine( argc, argv, "-treeType=" );
  if (  treeType == "" )
    {
      std::cout << "[WARNING]: please provide a valid treeType, use --treeType=<inclusive/category>" << std::endl;
      treeType = "inclusive";
    }

  std::string category = ParseCommandLine( argc, argv, "-category=" );
  if (  category == "" )
    {
      std::cout << "[WARNING]: please provide a valid category, use --category=<inclusive/highpt/hbb/zbb/highres/lowres/onemu/oneele>" << std::endl;
      treeType = "inclusive";
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


  
  //---------------------
  //T r i g g e r   C u t 
  //---------------------
  
  //TString triggerCut_80X = "&& (HLTDecision[82] || HLTDecision[83] || HLTDecision[93]) ";//diphoton triggers
  //TString triggerCut_76X = "&& (HLTDecision[82] || HLTDecision[83] || HLTDecision[93]) ";
  
  //TString triggerCut_80X = "&& (  HLTDecision[27] || HLTDecision[44] || HLTDecision[45] || HLTDecision[217] )";//dielectron triggers
  //TString triggerCut_76X = "&& (  HLTDecision[27] || HLTDecision[44] || HLTDecision[45] || HLTDecision[217] )";
  
  //TString triggerCut_80X = "&& (  HLTDecision[84] )";
  //TString triggerCut_76X = "&& (  HLTDecision[84] )";
  
  //TString triggerCut_80X = "&& ( 1 )";
  //TString triggerCut_76X = "&& ( 1 )";
  
  
  //-------------------------------------------
  //Define tree cuts based on category;
  //-------------------------------------------
  TString cut; 
  TString cut_mc; 

  TString triggerCut_80X;
  TString triggerCut_76X; 

  int nprocesses;

  if ( inputType == "diphoton" )
  {
          //data
          //GammaGamma
          cut = "mGammaGamma > 103. && mGammaGamma < 160. && abs( pho1SC_Eta ) < 1.4442 && abs( pho2SC_Eta ) < 1.4442 && ( pho1Pt > 40. || pho2Pt > 40. ) && pho1Pt > 25. && pho2Pt> 25. && pho1passEleVeto == 1 && pho2passEleVeto == 1 && pho1passIso == 1 && pho2passIso == 1 && (Flag_HBHENoiseFilter == 1 && Flag_goodVertices == 1 && Flag_eeBadScFilter == 1 && Flag_HBHEIsoNoiseFilter == 1 && Flag_CSCTightHaloFilter == 1 )";
          //MC
          //GammaGamma
          cut_mc = "mGammaGamma > 103. && mGammaGamma < 160. && abs( pho1SC_Eta ) < 1.4442 && abs( pho2SC_Eta ) < 1.4442 && ( pho1Pt > 40. || pho2Pt > 40. ) && pho1Pt > 25. && pho2Pt> 25. && pho1passEleVeto == 1 && pho2passEleVeto == 1 && pho1passIso == 1 && pho2passIso == 1";

          //---------------------
          //T r i g g e r   C u t 
          //---------------------

          triggerCut_80X = "&& (HLTDecision[82] || HLTDecision[83] || HLTDecision[93]) ";//diphoton triggers
          triggerCut_76X = "&& (HLTDecision[82] || HLTDecision[83] || HLTDecision[93]) ";

          // D e f i n e  B i n n i n g
          //---------------------------
          //H 
          //HggRazorClass::n_mgg = 57;
          //HggRazorClass::mgg_l = 103.;
          //HggRazorClass::mgg_h = 160.;

          nprocesses = 8;//mc+data
  }
  else if ( inputType == "leptons" )
  {
          //data
          //GammaGamma
          cut = "mGammaGamma > 103. && mGammaGamma < 160. && abs( pho1SC_Eta ) < 1.4442 && abs( pho2SC_Eta ) < 1.4442 && ( pho1Pt > 40. || pho2Pt > 40. ) && pho1Pt > 25. && pho2Pt> 25. && pho1passEleVeto == 1 && pho2passEleVeto == 1 && pho1passIso == 1 && pho2passIso == 1 && (Flag_HBHENoiseFilter == 1 && Flag_goodVertices == 1 && Flag_eeBadScFilter == 1 && Flag_HBHEIsoNoiseFilter == 1 && Flag_CSCTightHaloFilter == 1 )";
          //MC
          //GammaGamma
          cut_mc = "mGammaGamma > 103. && mGammaGamma < 160. && abs( pho1SC_Eta ) < 1.4442 && abs( pho2SC_Eta ) < 1.4442 && ( pho1Pt > 40. || pho2Pt > 40. ) && pho1Pt > 25. && pho2Pt> 25. && pho1passEleVeto == 1 && pho2passEleVeto == 1 && pho1passIso == 1 && pho2passIso == 1";

          //---------------------
          //T r i g g e r   C u t 
          //---------------------

          triggerCut_80X = "&& (HLTDecision[82] || HLTDecision[83] || HLTDecision[93]) ";//diphoton triggers
          triggerCut_76X = "&& (HLTDecision[82] || HLTDecision[83] || HLTDecision[93]) ";

          // D e f i n e  B i n n i n g
          //---------------------------
          //H 
          //HggRazorClass::n_mgg = 57;
          //HggRazorClass::mgg_l = 103.;
          //HggRazorClass::mgg_h = 160.;

          nprocesses = 14;//mc+data
  }
  else if ( inputType == "Zee" )
  {
          //Data
          cut = "abs( pho1SC_Eta ) < 1.4442 && abs( pho2SC_Eta ) < 1.4442 && ( pho1Pt > 40. || pho2Pt > 40. ) && pho1Pt > 25. && pho2Pt> 25. && mGammaGamma > 75 && mGammaGamma < 120 && pho1passEleVeto == 0 && pho2passEleVeto == 0 && pho1passIso == 1 && pho2passIso == 1 && (Flag_HBHENoiseFilter == 1 && Flag_goodVertices == 1 && Flag_eeBadScFilter == 1 && Flag_HBHEIsoNoiseFilter == 1 && Flag_CSCTightHaloFilter == 1 ) ";
          //MC
          cut_mc = "abs( pho1SC_Eta ) < 1.4442 && abs( pho2SC_Eta ) < 1.4442 && ( pho1Pt > 40. || pho2Pt > 40. ) && pho1Pt > 25. && pho2Pt> 25. && mGammaGamma > 75 && mGammaGamma < 120 && pho1passEleVeto == 0 && pho2passEleVeto == 0 && pho1passIso == 1 && pho2passIso == 1 ";

          //---------------------
          //T r i g g e r   C u t 
          //---------------------

          triggerCut_80X = "&& (  HLTDecision[84] )";
          triggerCut_76X = "&& (  HLTDecision[84] )";

          // D e f i n e  B i n n i n g
          //---------------------------
          //Z
          HggRazorClass::n_mgg = 60;
          HggRazorClass::mgg_l = 60.;
          HggRazorClass::mgg_h = 120.;

          nprocesses = 2;//mc+data
  }


  if ( category == "inclusive" )
    {
      cut    = cut + "";
      cut_mc = cut_mc + "";
    }
  else if ( category == "highpt" )
    {
      cut    = cut + " && MR>150 && pTGammaGamma>110. && box>4";
      cut_mc = cut_mc + " && MR>150 && pTGammaGamma>110. && box>4";
    }
  else if ( category == "hbb" )
    {
      cut    = cut + " && MR > 150. && pTGammaGamma < 110 && abs(mbbH-125.)<15 && box>4";
      cut_mc = cut_mc + " && MR > 150. && pTGammaGamma < 110 && abs(mbbH-125.)<15 && box>4";
    }
  else if ( category == "zbb" )
    {
      cut    = cut + " && MR > 150. && pTGammaGamma < 110 && abs(mbbH-125.)>=15 && abs(mbbZ-91.)<15 && box>4";
      cut_mc = cut_mc + " && MR > 150. && pTGammaGamma < 110 && abs(mbbH-125.)>=15 && abs(mbbZ-91.)<15 && box>4";
    }
  else if ( category == "highres" )
    {
      cut    = cut + " && MR > 150. && pTGammaGamma < 110 && abs(mbbH-125.)>=15 && abs(mbbZ-91.)>=15 && sigmaMoverM<0.0085 && box > 4";
      cut_mc = cut_mc + " && MR > 150. && pTGammaGamma < 110 && abs(mbbH-125.)>=15 && abs(mbbZ-91.)>=15 && sigmaMoverM<0.0085 && box > 4";
    }
  else if ( category == "lowres" )
    {
      cut    = cut + " && MR > 150. && pTGammaGamma < 110 && abs(mbbH-125.)>=15 && abs(mbbZ-91.)>=15 && sigmaMoverM>=0.0085 && box > 4";
      cut_mc = cut_mc + " && MR > 150. && pTGammaGamma < 110 && abs(mbbH-125.)>=15 && abs(mbbZ-91.)>=15 && sigmaMoverM>=0.0085 && box > 4";
    }
  else if ( category == "onemu" )
    {
      cut    = cut + " && box == 3 && lep1Pt>20 && !(mGammaGamma > 121. && mGammaGamma < 129.) && MR > 150";
      cut_mc = cut_mc + " && box == 3 && lep1Pt>20 && !(mGammaGamma > 121. && mGammaGamma < 129.) && MR > 150";
    }
  else if ( category == "oneele" )
    {
      cut    = cut + " && box == 4 && lep1Pt>25 && !(mGammaGamma > 121. && mGammaGamma < 129.) && MR > 150";
      cut_mc = cut_mc + " && box == 4 && lep1Pt>25 && !(mGammaGamma > 121. && mGammaGamma < 129.) && MR > 150";
    }




  
  std::cout << "=================================" << std::endl;
  std::cout << "===========set parameters========" << std::endl;
  std::cout << "[INFO]: input file: " << inputFile << std::endl;
  std::cout << "[INFO]: analysisTag: " << analysisTag << std::endl;
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
  //const int nprocesses = 2;//mc+data
  //const int nprocesses = 14;//mc+data
  //check nprocesses and map_size consistency
  if( map_size != nprocesses )
    {
      std::cerr << "[FATAL ERROR]: map size and nprocesses values are inconsistent!!, Please change nprocesses to map size: " << map_size << std::endl;
      exit( EXIT_FAILURE );
    }
  const int nplots = 4;
  // double k_f = 1.78*1.05;//Difference in data/mc normalization
  //double k_f = 1.62*1.05;//Difference in data/mc normalization
  //double k_f = 1.3291653769;
  //double k_f = 1.2509;//test
  //double k_f = 2.0014889911;//MORIOND HggRazor

  //double k_f  = 4.16008;
  //double k_f2 = 0.362879;


  double k_f  = 3.46974;
  double k_f2 = 0.362879;
  
  //double k_f = 1.3490409433;
  //double k_f = 1.0;
  //double k_f = 3.97;
  //double k_f = 1.6229861908;//highpt
  //double k_f = 2.5092891956;//hbb
  //double k_f = 2.3464806682;//zbb
  //double k_f = 0.6069650444;//highpt
  //double k_f = 0.9664948454;//hbb
  //double k_f = 1.0387200549;//zbb
  //double k_f = 0.6399529051;//highres
  //double k_f = 1.4101878662;//lowres
  double lumi = 0;
  
  if (analysisTag == "Razor2015_76X") lumi = 2300;
  if (analysisTag == "Razor2016_80X") lumi = 35900.;
  
  std::cout << "[INFO]: running inclusive tree mode" << std::endl;
  std::cout << "[INFO]: lumi = " << lumi/1000. << "1/fb"<< std::endl;
  std::cout << "[INFO]: k-factor = " << k_f << std::endl;
  int ctr = 0;
  Histos histos[nprocesses];

  TH1F* sigmaMoverM_data = NULL;
  TH1F* sigmaMoverM_dy = NULL;
  
  for( const auto& process : Process() )
    {
      std::string processName = GetProcessString( process );
      //std::cout << "[INFO] PROCESS: " << processName << " ,process #: " << ctr << std::endl;
      if ( ( inputType == "diphoton" ) || ( inputType == "leptons" ))
      {
              //Diphoton
              if ( !(process == Process::data || process == Process::diphoton  || process == Process::gammaJet //|| process == Process::qcd
                                      || process == Process::ggH  || process == Process::vbfH || process == Process::vH || process == Process::ttH || process == Process::bbH
                                      || process == Process::tg || process == Process::ttg || process == Process::ttgg || process == Process::wg || process == Process::wgg || process == Process::zgg)
                 ) continue;
      }
      else if ( inputType == "Zee" )
      {
              //DY control region
              if ( !(process == Process::data || process == Process::dy) ) continue;
      }


      //Diphoton with Signal
      /*
      if ( !(process == Process::data || process == Process::bbH || process == Process::diphoton || process == Process::gammaJet
	     || process == Process::ggH  || process == Process::vbfH || process == Process::vH || process == Process::ttH) ) continue;
      */
      std::cout << "[INFO] PROCESS: " << processName << " ,process #: " << ctr << std::endl;
      
      //-----------------------------
      // R e t r i e v i n g  T r e e
      //-----------------------------
      chain   = new TChain( "HggRazorLeptons" );
      std::cout << "DEBUG: " << mapList[processName] << std::endl;
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
      if ( process == Process::data )
	{
	  TString myCut = cut;
	  if (analysisTag == "Razor2016_80X") myCut = cut+triggerCut_80X;
	  if (analysisTag == "Razor2015_76X") myCut = cut+triggerCut_76X;
	  std::cout << "CUT--> " << myCut << std::endl; 
	  cutTree = (TTree*)chain->CopyTree( myCut );
	}
      else
	{
	  TString myCut = cut;
	  if (analysisTag == "Razor2016_80X") myCut = cut_mc+triggerCut_80X;
	  if (analysisTag == "Razor2015_76X") myCut = cut_mc+triggerCut_76X;
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
      //hggclass = new HggRazorClass( cutTree, processName, "INCLUSIVE", true, true );
      hggclass = new HggRazorClass( cutTree, processName, "INCLUSIVE", false, false );
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
      //TFile* fh = new TFile(Form("%s_histo.root",processName.c_str()), "recreate");
      if ( processName == "data" ) sigmaMoverM_data = new TH1F( hggclass->GetHisto( HistoTypes::sigmaMoverM ) );
      else if ( processName == "dy" ) sigmaMoverM_dy = new TH1F( hggclass->GetHisto( HistoTypes::sigmaMoverM ) );
      //h_tmp->Write(processName.c_str());
      //fh->Close();
      std::cout << "DEB4" << std::endl;
      ctr++;
      delete hggclass;
    }
  std::cout << "out of loop" << std::endl;

  //----------------------------------
  //SigmaMoverM correction calculation
  //----------------------------------

  if ( sigmaMoverM_data != NULL ) sigmaMoverM_data->Scale( 1./sigmaMoverM_data->Integral() );//re-scale to unity to get eff directly
  std::cout << "out of loop" << std::endl;
  if ( sigmaMoverM_dy != NULL ) sigmaMoverM_dy->Scale( 1./sigmaMoverM_dy->Integral() );//re-scale to unity to get eff directly
  std::cout << "out of loop" << std::endl;
  
  if( sigmaMoverM_data != NULL && sigmaMoverM_dy != NULL )
    {
      int n_boundary_data = sigmaMoverM_data->FindFixBin(0.0085) - 1;
      int n_boundary_dy   = sigmaMoverM_dy->FindFixBin(0.0085) - 1;
      float eff_data_HR = sigmaMoverM_data->Integral(1,n_boundary_data);
      float eff_dy_HR   = sigmaMoverM_dy->Integral(1,n_boundary_dy);
      float eff_data_LR = 1. - eff_data_HR;
      float eff_dy_LR   = 1. - eff_dy_HR;
      std::cout << "-------------------------------------------" << std::endl;
      std::cout << "-------------------------------------------" << std::endl;
      std::cout << "data HR eff: " << eff_data_HR << "; dy HR eff: " << eff_dy_HR << std::endl;
      std::cout << "HR data/mc correction --> " << eff_data_HR/eff_dy_HR << std::endl;
      std::cout << "-------------------------------------------" << std::endl;
      std::cout << "data LR eff: " << eff_data_LR << "; dy LR eff: " << eff_dy_LR << std::endl;
      std::cout << "LR data/mc correction --> " << eff_data_LR/eff_dy_LR << std::endl;
      std::cout << "-------------------------------------------" << std::endl;
      std::cout << "-------------------------------------------" << std::endl;
    }
  
  std::cout << "file creation" << std::endl;
  TFile* fh = new TFile("sigmaMoverM_histo.root", "recreate");
  if ( sigmaMoverM_data != NULL ) sigmaMoverM_data->Write("data");
  if ( sigmaMoverM_dy != NULL ) sigmaMoverM_dy->Write("dy");
  fh->Close();
  
  //---------------
  //P l o t t i n g
  //---------------
  std::cout << "PLOTTING" << std::endl;
  TFile* fout = new TFile("histograms.root", "RECREATE");
  
  for ( const auto& htmp : HistoTypes() ) {
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
	    //-----------------------
	    //Scaling each MC process
	    //-----------------------
	    if ( _useKF && (histos[i].process == Process::gammaJet || histos[i].process == Process::qcd|| histos[i].process == Process::diphoton) ) h_s->Scale( k_f );

	    if ( _useKF &&  (histos[i].process == Process::wg || histos[i].process == Process::wgg || histos[i].process == Process::zgg) ) h_s->Scale( k_f2 );
	   
            if ( _useKF && (histos[i].process == Process::dy) ) h_s->Scale( k_f );

	    //if ( _useKF && (histos[i].process == Process::gammaJet || histos[i].process == Process::diphoton || histos[i].process == Process::ggH || histos[i].process == Process::vbfH || histos[i].process == Process::vH || histos[i].process == Process::bbH || histos[i].process == Process::ttH) ) h_s->Scale( k_f );
	    /*if ( _useKF && (histos[i].process == Process::gammaJet || histos[i].process == Process::qcd || histos[i].process == Process::diphoton
	      || histos[i].process == Process::tg || histos[i].process == Process::ttg || histos[i].process == Process::wgg
	      || histos[i].process == Process::zgg) ) h_s->Scale( k_f );
	    */
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

	      
	AddLegend( h_s, leg, histos[i].process );
	if (  histos[i].process != Process::data ) AddLegend( h_s, leg2, histos[i].process );

	TString pname = GetProcessString( histos[i].process );
	TString hname = histoName;
	h_s->Write( hname+"_"+pname);
      }
    std::cout << "===================================" << std::endl;
    std::cout << "data-> " << data->Integral() << std::endl;
    std::cout << "MC-> " << mc->Integral() << std::endl;
    std::cout << "===================================" << std::endl;

    
    NormFactor = mc->Integral();
    if ( _shapeOnly ) mc->Scale(1.0/NormFactor);
    for (  int i  = 0; i < nprocesses; i++ ) {
      TH1F* tmp_h = new TH1F( histos[i].GetHisto( htmp ) );
      TH1D* h_s = GetStyledHisto( (TH1D*)tmp_h, histos[i].process );
      h_s->Scale( lumi );

      //--------------------------------------
      //Scaling each MC process for stack plot
      //--------------------------------------
      if ( _useKF && (histos[i].process == Process::gammaJet || histos[i].process == Process::qcd|| histos[i].process == Process::diphoton) ) h_s->Scale( k_f );
      if ( _useKF &&  (histos[i].process == Process::wg || histos[i].process == Process::wgg || histos[i].process == Process::zgg) ) h_s->Scale( k_f2 );
      //if ( _useKF && (histos[i].process == Process::gammaJet || histos[i].process == Process::diphoton || histos[i].process == Process::ggH || histos[i].process == Process::vbfH || histos[i].process == Process::vH || histos[i].process == Process::bbH || histos[i].process == Process::ttH) ) h_s->Scale( k_f );
      /*if ( _useKF && (histos[i].process == Process::gammaJet || histos[i].process == Process::qcd || histos[i].process == Process::diphoton
		      || histos[i].process == Process::tg || histos[i].process == Process::ttg || histos[i].process == Process::wgg
		      || histos[i].process == Process::zgg) ) h_s->Scale( k_f );*/
      
      if ( _shapeOnly ) h_s->Scale(1.0/NormFactor);
      if ( histos[i].process != Process::data && histos[i].process != Process::signal ) stack->Add( h_s, "histo" );
    }

    //Make Plots
    if ( _signalPlot ) MakeStackPlotSignal( stack, signal, histoName, "plots/" + histoName + "_" + "Signal", leg2 );
    MakeStackPlot( stack, data, mc, histoName, "plots/" + histoName + "_" + "INCLUSIVE", leg );
	  
  } //loop over histograms
  fout->Close();
  std::cout << "deleting hggclass object" << std::endl;
  //delete hggclass;
  return 0;
}
