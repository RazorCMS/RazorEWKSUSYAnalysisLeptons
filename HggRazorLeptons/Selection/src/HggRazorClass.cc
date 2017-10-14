//C++ INCLUDES
#include <iostream>
#include <fstream>
#include <math.h>
//ROOT INCLUDES
//LOCAL INCLUDES
#include "HggRazorClass.hh"

HggRazorClass::HggRazorClass( ){ };

HggRazorClass::HggRazorClass( TTree* tree ) : HggTree( tree ), _info( false ), _debug( false )
{
  std::cout << "[DEBUG]: n_mgg: " << n_mgg << std::endl;
  InitMggHisto();
  InitPtggHisto();
};

HggRazorClass::HggRazorClass( TTree* tree, TString processName, TString boxName, bool info, bool debug ) : HggTree( tree ), _info( info ), _debug( debug )
{
  //processName
  if ( processName == "" )
    {
      this->processName = "dummy_process";
    }
  else
    {
      this->processName = processName;
    }
  //boxName
  if ( boxName == "" )
    {
      this->boxName = "dummy_box";
    }
  else
    {
      this->boxName = boxName;
    }
  //higgs
  InitMggHisto();
  InitPtggHisto();
  InitSigmaMoverMHisto( );
  //razor
  InitMrHisto();
  InitRsqHisto();
  IntUnrollHistos();
  //photon1
  InitPho1Pt();
  InitPho1Eta();
  InitPho1Phi( );
  InitPho1SigmaIetaIeta( );
  InitPho1R9( );
  InitPho1HoverE( );
  InitPho1SumChargedHadronPt( );
  InitPho1SumNeutralHadronEt( );
  InitPho1SumPhotonEt( );
  InitPho1SigmaEoverE( );
  //photon2
  InitPho2Pt();
  InitPho2Eta();
  InitPho2Phi( );
  InitPho2SigmaIetaIeta( );
  InitPho2R9( );
  InitPho2HoverE( );
  InitPho2SumChargedHadronPt( );
  InitPho2SumNeutralHadronEt( );
  InitPho2SumPhotonEt( );
  InitPho2SigmaEoverE( );
  //jets
  InitNjets();
  InitMrRsqHisto();
  //met+mt
  InitMET();
  InitMT();	     
  InitLepPt();
};

HggRazorClass::~HggRazorClass()
{
  if ( _debug ) std::cout << "[DEBUG]: Entering Destructor" << std::endl;
  if (h_mgg) delete h_mgg;
  if (h_ptgg) delete h_ptgg;
  if ( _debug ) std::cout << "[DEBUG]: Finishing Destructor" << std::endl;
};

bool HggRazorClass::InitMggHisto( )
{
  if ( n_mgg == 0 || mgg_l == mgg_h )
    {
      std::cerr << "[ERROR]: mgg histogram parameters not initialized" << std::endl;
      return false;
    }
  if ( _debug ) std::cout << "[DEBUG]: Initializing mgg histogram" << std::endl;
  h_mgg = new TH1F( this->processName + "_" + this->boxName +  "_mgg", "mgg", n_mgg, mgg_l, mgg_h );
  return true;
};

bool HggRazorClass::InitPtggHisto( )
{
  if ( n_ptgg == 0 || ptgg_l == ptgg_h )
    {
      std::cerr << "[ERROR]: ptgg histogram parameters not initialized" << std::endl;
      return false;
    }
  if ( _debug ) std::cout << "[DEBUG]: Initializing ptgg histogram" << std::endl;
  h_ptgg = new TH1F( this->processName + "_" + this->boxName +  "_ptgg", "ptgg", n_ptgg, ptgg_l, ptgg_h );
  return true;
};

bool HggRazorClass::InitSigmaMoverMHisto( )
{
  if ( n_sigmaMoverM == 0 || sigmaMoverM_l == sigmaMoverM_h )
    {
      std::cerr << "[ERROR]: sigmaMoverM histogram parameters not initialized" << std::endl;
      return false;
    }
  if ( _debug ) std::cout << "[DEBUG]: Initializing sigmaMoverM histogram" << std::endl;
  h_sigmaMoverM = new TH1F( this->processName + "_" + this->boxName +  "_sigmaMoverM", "sigmaMoverM", n_sigmaMoverM, sigmaMoverM_l, sigmaMoverM_h );
  return true;
};

bool HggRazorClass::InitMrHisto( )
{
  if ( n_mr == 0 || mr_l == mr_h )
    {
      std::cerr << "[ERROR]: mr histogram parameters not initialized" << std::endl;
      return false;
    }
  if ( _debug ) std::cout << "[DEBUG]: Initializing mr histogram" << std::endl;
  h_mr = new TH1F( this->processName + "_" + this->boxName +  "_mr", "mr", n_mr, mr_l, mr_h );
  return true;
};

bool HggRazorClass::InitRsqHisto( )
{
  if ( n_rsq == 0 || rsq_l == rsq_h )
    {
      std::cerr << "[ERROR]: rsq histogram parameters not initialized" << std::endl;
      return false;
    }
  if ( _debug ) std::cout << "[DEBUG]: Initializing rsq histogram" << std::endl;
  h_rsq = new TH1F( this->processName + "_" + this->boxName +  "_rsq", "rsq", n_rsq, rsq_l, rsq_h );
  return true;
};


bool HggRazorClass::InitPho1Pt( )
{
  if ( n_pho1pt == 0 || pho1pt_l == pho1pt_h )
    {
      std::cerr << "[ERROR]: pho1pt histogram parameters not initialized" << std::endl;
      return false;
    }
  if ( _debug ) std::cout << "[DEBUG]: Initialized pho1pt histogram" << std::endl;
  h_pho1pt = new TH1F( this->processName + "_" + this->boxName + "_pho1pt", "pho1pt", n_pho1pt, pho1pt_l, pho1pt_h);
  return true;
};

bool HggRazorClass::InitPho1Eta( )
{
  if ( n_pho1eta == 0 || pho1eta_l == pho1eta_h )
    {
      std::cerr << "[ERROR]: pho1eta histogram parameters not initialized" << std::endl;
      return false;
    }
  if ( _debug ) std::cout << "[DEBUG]: Initialized pho1eta histogram" << std::endl;
  h_pho1eta = new TH1F( this->processName + "_" + this->boxName + "_pho1eta", "pho1eta", n_pho1eta, pho1eta_l, pho1eta_h);
  return true;
};

bool HggRazorClass::InitPho1Phi( )
{
  if ( n_pho1phi == 0 || pho1phi_l == pho1phi_h )
    {
      std::cerr << "[ERROR]: pho1phi histogram parameters not initialized" << std::endl;
      return false;
    }
  if ( _debug ) std::cout << "[DEBUG]: Initialized pho1phi histogram" << std::endl;
  h_pho1phi = new TH1F( this->processName + "_" + this->boxName + "_pho1phi", "pho1phi", n_pho1phi, pho1phi_l, pho1phi_h);
  return true;
};

bool HggRazorClass::InitPho1SigmaIetaIeta( )
{
  if ( n_pho1sigmaIetaIeta == 0 || pho1sigmaIetaIeta_l == pho1sigmaIetaIeta_h )
    {
      std::cerr << "[ERROR]: pho1sigmaIetaIeta histogram parameters not initialized" << std::endl;
      return false;
    }
  if ( _debug ) std::cout << "[DEBUG]: Initialized pho1sigmaIetaIeta histogram" << std::endl;
  h_pho1sigmaIetaIeta = new TH1F( this->processName + "_" + this->boxName + "_pho1sigmaIetaIeta", "pho1sigmaIetaIeta", n_pho1sigmaIetaIeta, pho1sigmaIetaIeta_l, pho1sigmaIetaIeta_h);
  return true;
};

bool HggRazorClass::InitPho1R9( )
{
  if ( n_pho1r9 == 0 || pho1r9_l == pho1r9_h )
    {
      std::cerr << "[ERROR]: pho1r9 histogram parameters not initialized" << std::endl;
      return false;
    }
  if ( _debug ) std::cout << "[DEBUG]: Initialized pho1r9 histogram" << std::endl;
  h_pho1r9 = new TH1F( this->processName + "_" + this->boxName + "_pho1r9", "pho1r9", n_pho1r9, pho1r9_l, pho1r9_h);
  return true;
};

bool HggRazorClass::InitPho1HoverE( )
{
  if ( n_pho1HoverE == 0 || pho1HoverE_l == pho1HoverE_h )
    {
      std::cerr << "[ERROR]: pho1HoverE histogram parameters not initialized" << std::endl;
      return false;
    }
  if ( _debug ) std::cout << "[DEBUG]: Initialized pho1HoverE histogram" << std::endl;
  h_pho1HoverE = new TH1F( this->processName + "_" + this->boxName + "_pho1HoverE", "pho1HoverE", n_pho1HoverE, pho1HoverE_l, pho1HoverE_h);
  return true;
};

bool HggRazorClass::InitPho1SumChargedHadronPt( )
{
  if ( n_pho1sumChargedHadronPt == 0 || pho1sumChargedHadronPt_l == pho1sumChargedHadronPt_h )
    {
      std::cerr << "[ERROR]: pho1sumChargedHadronPt histogram parameters not initialized" << std::endl;
      return false;
    }
  if ( _debug ) std::cout << "[DEBUG]: Initialized pho1sumChargedHadronPt histogram" << std::endl;
  h_pho1sumChargedHadronPt = new TH1F( this->processName + "_" + this->boxName + "_pho1sumChargedHadronPt", "pho1sumChargedHadronPt", n_pho1sumChargedHadronPt, pho1sumChargedHadronPt_l, pho1sumChargedHadronPt_h);
  return true;
};

bool HggRazorClass::InitPho1SumNeutralHadronEt( )
{
  if ( n_pho1sumNeutralHadronEt == 0 || pho1sumNeutralHadronEt_l == pho1sumNeutralHadronEt_h )
    {
      std::cerr << "[ERROR]: pho1sumNeutralHadronEt histogram parameters not initialized" << std::endl;
      return false;
    }
  if ( _debug ) std::cout << "[DEBUG]: Initialized pho1sumNeutralHadronEt histogram" << std::endl;
  h_pho1sumNeutralHadronEt = new TH1F( this->processName + "_" + this->boxName + "_pho1sumNeutralHadronEt", "pho1sumNeutralHadronEt", n_pho1sumNeutralHadronEt, pho1sumNeutralHadronEt_l, pho1sumNeutralHadronEt_h);
  return true;
};

bool HggRazorClass::InitPho1SumPhotonEt( )
{
  if ( n_pho1sumPhotonEt == 0 || pho1sumPhotonEt_l == pho1sumPhotonEt_h )
    {
      std::cerr << "[ERROR]: pho1sumPhotonEt histogram parameters not initialized" << std::endl;
      return false;
    }
  if ( _debug ) std::cout << "[DEBUG]: Initialized pho1sumPhotonEt histogram" << std::endl;
  h_pho1sumPhotonEt = new TH1F( this->processName + "_" + this->boxName + "_pho1sumPhotonEt", "pho1sumPhotonEt", n_pho1sumPhotonEt, pho1sumPhotonEt_l, pho1sumPhotonEt_h);
  return true;
};

bool HggRazorClass::InitPho1SigmaEoverE( )
{
  if ( n_pho1sigmaEoverE == 0 || pho1sigmaEoverE_l == pho1sigmaEoverE_h )
    {
      std::cerr << "[ERROR]: pho1sigmaEoverE histogram parameters not initialized" << std::endl;
      return false;
    }
  if ( _debug ) std::cout << "[DEBUG]: Initialized pho1sigmaEoverE histogram" << std::endl;
  h_pho1sigmaEoverE = new TH1F( this->processName + "_" + this->boxName + "_pho1sigmaEoverE", "pho1sigmaEoverE", n_pho1sigmaEoverE, pho1sigmaEoverE_l, pho1sigmaEoverE_h);
  return true;
};

//Photon2
bool HggRazorClass::InitPho2Pt( )
{
  if ( n_pho2pt == 0 || pho2pt_l == pho2pt_h )
    {
      std::cerr << "[ERROR]: pho2pt histogram parameters not initialized" << std::endl;
      return false;
    }
  if ( _debug ) std::cout << "[DEBUG]: Initialized pho1pt histogram" << std::endl;
  h_pho2pt = new TH1F( this->processName + "_" + this->boxName + "_pho2pt", "pho2pt", n_pho2pt, pho2pt_l, pho2pt_h);
  return true;
};

bool HggRazorClass::InitPho2Eta( )
{
  if ( n_pho2eta == 0 || pho2eta_l == pho2eta_h )
    {
      std::cerr << "[ERROR]: pho2eta histogram parameters not initialized" << std::endl;
      return false;
    }
  if ( _debug ) std::cout << "[DEBUG]: Initialized pho2eta histogram" << std::endl;
  h_pho2eta = new TH1F( this->processName + "_" + this->boxName + "_pho2eta", "pho2eta", n_pho2eta, pho2eta_l, pho2eta_h);
  return true;
};

bool HggRazorClass::InitPho2Phi( )
{
  if ( n_pho2phi == 0 || pho2phi_l == pho2phi_h )
    {
      std::cerr << "[ERROR]: pho2phi histogram parameters not initialized" << std::endl;
      return false;
    }
  if ( _debug ) std::cout << "[DEBUG]: Initialized pho2phi histogram" << std::endl;
  h_pho2phi = new TH1F( this->processName + "_" + this->boxName + "_pho2phi", "pho2phi", n_pho2phi, pho2phi_l, pho2phi_h);
  return true;
};

bool HggRazorClass::InitPho2SigmaIetaIeta( )
{
  if ( n_pho2sigmaIetaIeta == 0 || pho2sigmaIetaIeta_l == pho2sigmaIetaIeta_h )
    {
      std::cerr << "[ERROR]: pho2sigmaIetaIeta histogram parameters not initialized" << std::endl;
      return false;
    }
  if ( _debug ) std::cout << "[DEBUG]: Initialized pho2sigmaIetaIeta histogram" << std::endl;
  h_pho2sigmaIetaIeta = new TH1F( this->processName + "_" + this->boxName + "_pho2sigmaIetaIeta", "pho2sigmaIetaIeta", n_pho2sigmaIetaIeta, pho2sigmaIetaIeta_l, pho2sigmaIetaIeta_h);
  return true;
};

bool HggRazorClass::InitPho2R9( )
{
  if ( n_pho2r9 == 0 || pho2r9_l == pho2r9_h )
    {
      std::cerr << "[ERROR]: pho2r9 histogram parameters not initialized" << std::endl;
      return false;
    }
  if ( _debug ) std::cout << "[DEBUG]: Initialized pho2r9 histogram" << std::endl;
  h_pho2r9 = new TH1F( this->processName + "_" + this->boxName + "_pho2r9", "pho2r9", n_pho2r9, pho2r9_l, pho2r9_h);
  return true;
};

bool HggRazorClass::InitPho2HoverE( )
{
  if ( n_pho2HoverE == 0 || pho2HoverE_l == pho2HoverE_h )
    {
      std::cerr << "[ERROR]: pho2HoverE histogram parameters not initialized" << std::endl;
      return false;
    }
  if ( _debug ) std::cout << "[DEBUG]: Initialized pho2HoverE histogram" << std::endl;
  h_pho2HoverE = new TH1F( this->processName + "_" + this->boxName + "_pho2HoverE", "pho2HoverE", n_pho2HoverE, pho2HoverE_l, pho2HoverE_h);
  return true;
};

bool HggRazorClass::InitPho2SumChargedHadronPt( )
{
  if ( n_pho2sumChargedHadronPt == 0 || pho2sumChargedHadronPt_l == pho2sumChargedHadronPt_h )
    {
      std::cerr << "[ERROR]: pho2sumChargedHadronPt histogram parameters not initialized" << std::endl;
      return false;
    }
  if ( _debug ) std::cout << "[DEBUG]: Initialized pho2sumChargedHadronPt histogram" << std::endl;
  h_pho2sumChargedHadronPt = new TH1F( this->processName + "_" + this->boxName + "_pho2sumChargedHadronPt", "pho2sumChargedHadronPt", n_pho2sumChargedHadronPt, pho2sumChargedHadronPt_l, pho2sumChargedHadronPt_h);
  return true;
};

bool HggRazorClass::InitPho2SumNeutralHadronEt( )
{
  if ( n_pho2sumNeutralHadronEt == 0 || pho2sumNeutralHadronEt_l == pho2sumNeutralHadronEt_h )
    {
      std::cerr << "[ERROR]: pho2sumNeutralHadronEt histogram parameters not initialized" << std::endl;
      return false;
    }
  if ( _debug ) std::cout << "[DEBUG]: Initialized pho2sumNeutralHadronEt histogram" << std::endl;
  h_pho2sumNeutralHadronEt = new TH1F( this->processName + "_" + this->boxName + "_pho2sumNeutralHadronEt", "pho2sumNeutralHadronEt", n_pho2sumNeutralHadronEt, pho2sumNeutralHadronEt_l, pho2sumNeutralHadronEt_h);
  return true;
};

bool HggRazorClass::InitPho2SumPhotonEt( )
{
  if ( n_pho2sumPhotonEt == 0 || pho2sumPhotonEt_l == pho2sumPhotonEt_h )
    {
      std::cerr << "[ERROR]: pho2sumPhotonEt histogram parameters not initialized" << std::endl;
      return false;
    }
  if ( _debug ) std::cout << "[DEBUG]: Initialized pho2sumPhotonEt histogram" << std::endl;
  h_pho2sumPhotonEt = new TH1F( this->processName + "_" + this->boxName + "_pho2sumPhotonEt", "pho2sumPhotonEt", n_pho2sumPhotonEt, pho2sumPhotonEt_l, pho2sumPhotonEt_h);
  return true;
};

bool HggRazorClass::InitPho2SigmaEoverE( )
{
  if ( n_pho2sigmaEoverE == 0 || pho2sigmaEoverE_l == pho2sigmaEoverE_h )
    {
      std::cerr << "[ERROR]: pho2sigmaEoverE histogram parameters not initialized" << std::endl;
      return false;
    }
  if ( _debug ) std::cout << "[DEBUG]: Initialized pho2sigmaEoverE histogram" << std::endl;
  h_pho2sigmaEoverE = new TH1F( this->processName + "_" + this->boxName + "_pho2sigmaEoverE", "pho2sigmaEoverE", n_pho2sigmaEoverE, pho2sigmaEoverE_l, pho2sigmaEoverE_h);
  return true;
};

//NJETS
bool HggRazorClass::InitNjets( )
{
  if ( n_njets == 0 || njets_l == njets_h )
    {
      std::cerr << "[ERROR]: njets histogram parameters not initialized" << std::endl;
      return false;
    }
  if ( _debug ) std::cout << "[DEBUG]: Initialized njets histogram" << std::endl;
  h_njets = new TH1F( this->processName + "_" + this->boxName + "_njets", "njets", n_njets, njets_l, njets_h);
  return true;
};

//MET
bool HggRazorClass::InitMET( )
{
  if ( n_met == 0 || met_l == met_h )
    {
      std::cerr << "[ERROR]: MET histogram parameters not initialized" << std::endl;
      return false;
    }
  if ( _debug ) std::cout << "[DEBUG]: Initialized MET histogram" << std::endl;
  h_met = new TH1F( this->processName + "_" + this->boxName + "_met", "met", n_met, met_l, met_h);
  return true;
};

//MT
bool HggRazorClass::InitMT( )
{
  if ( n_mt == 0 || mt_l == mt_h )
    {
      std::cerr << "[ERROR]: MT histogram parameters not initialized" << std::endl;
      return false;
    }
  if ( _debug ) std::cout << "[DEBUG]: Initialized MT histogram" << std::endl;
  h_mt = new TH1F( this->processName + "_" + this->boxName + "_mt", "mt", n_mt, mt_l, mt_h);
  return true;
};

//MT
bool HggRazorClass::InitLepPt( )
{
  if ( n_ptlep == 0 || ptlep_l == ptlep_h )
    {
      std::cerr << "[ERROR]: Lepton Pt histogram parameters not initialized" << std::endl;
      return false;
    }
  if ( _debug ) std::cout << "[DEBUG]: Initialized Lepton Pt histogram" << std::endl;
  h_ptlep = new TH1F( this->processName + "_" + this->boxName + "_ptlep", "ptlep", n_ptlep, ptlep_l, ptlep_h);
  return true;
};

//2D Histos
bool HggRazorClass::InitMrRsqHisto( )
{
  if ( ( n_rsq == 0 || rsq_l == rsq_h )  || ( n_mr == 0 || mr_l == mr_h ) )
    {
      std::cerr << "[ERROR]: mr_rsq histogram parameters not initialized" << std::endl;
      return false;
    }
  if ( _debug ) std::cout << "[DEBUG]: Initializing mr_rsq histogram" << std::endl;
  h_mr_rsq = new TH2F( this->processName + "_" + this->boxName +  "_mr_rsq", "mr_rsq", n_mr, mr_l, mr_h, n_rsq, rsq_l, rsq_h );
  return true; 
};


bool HggRazorClass::InitMrRsqCustomHisto( int nx, float* bx, int ny, float* by )
{
  if ( ( nx == 0 || bx == NULL )  || ( ny == 0 || by == NULL ) )
    {
      std::cerr << "[ERROR]: Custom mr_rsq histogram parameters not initialized" << std::endl;
      return false;
    }
  if ( _debug ) std::cout << "[DEBUG]: Initializing custom mr_rsq histogram" << std::endl;
  h_mr_rsq_c = new TH2F( this->processName + "_" + this->boxName +  "_mr_rsq_c", "mr_rsq", nx, bx, ny, by );
  return true; 
};

bool HggRazorClass::IntUnrollHistos( )
{
  if ( n_unroll_highPt <= 0  ||  n_unroll_highRes <= 0 )
    {
      std::cerr << "[ERROR]: unrolled plots are no properly initializem, check n_bins" << std::endl;
      return false;
    }
  
  h_unroll_highPt = new TH1F("unrolledHighPt", "unrolledHighPt", n_unroll_highPt, 0, n_unroll_highPt);
  h_unroll_highRes = new TH1F("unrolledHighRes", "unrolledHighRes", n_unroll_highRes, 0, n_unroll_highRes);
  return true;
};

void HggRazorClass::Loop()
{

  if ( _debug ) std::cout << "[DEBUG]: Entering Loop" << std::endl;
  if (fChain == 0) return;
  if ( h_mgg == NULL || h_ptgg == NULL )
    {
      std::cerr << "[ERROR]: Histograms are not initialized" << std::endl;
      return;
    }

  //---------------------------------------
  //SigmaMoverM Reweighting 
  //---------------------------------------
  //TFile* fsmom = new TFile("/Users/cmorgoth/Work/git/RazorEWKSUSYAnalysis/HggRazor/PlottingAndSystematic/data/SigmaMoverM_ZToHScaleFactor.root");
  //TFile* fsmom = new TFile("/afs/cern.ch/user/j/jmao/work/public/releases/CMSSW_9_2_1/src/RazorEWKSUSYAnalysisLeptons/HggRazorLeptons/PlottingAndSystematic/data/SigmaMoverM_ZToHScaleFactor.root");
  TFile* fsmom = new TFile("/Users/cmorgoth/git/RazorEWKSUSYAnalysisLeptons/HggRazorLeptons/PlottingAndSystematic/SigmaMoverM_ZToHScaleFactor.root");
  TH1F* hSigmaMoverM_reweight = (TH1F*)fsmom->Get("SigmaMoverM_ZToHScaleFactor");
  if ( hSigmaMoverM_reweight == NULL )
    {
      std::cerr << "Missing SigmaMoverM reweighting histogram; please check location; the path is defined in /Users/cmorgoth/Work/git/RazorEWKSUSYAnalysis/HggRazor/CommonTools/src/HggRazorSystematics.cc" << std::endl;
      return;
    }
  
  Long64_t nentries = fChain->GetEntriesFast();
  Long64_t nbytes = 0, nb = 0;
  double total_in = 0, total_rm = 0;
  std::cout << "[INFO]: nentries: " << nentries << std::endl;
  for (Long64_t jentry=0; jentry < nentries; jentry++ )
    {
      Long64_t ientry = LoadTree(jentry);
      
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;

      //SigmaMoverM Correction
      double SigmaMoverMreweight = hSigmaMoverM_reweight->GetBinContent(hSigmaMoverM_reweight->FindFixBin(sigmaMoverM +0.0000000000001));
      SigmaMoverMreweight = 1.;
      //std::cout << "SigmaMoverMreweight: " << SigmaMoverMreweight << std::endl;

      //**********************************************************
      //Calculate weights
      //**********************************************************

       float w = 0;
       if ( this->processName == "data" || this->processName == "signal")
	 {
	   w = 1.0;
	 }
       else
	 {
	   w = weight*pileupWeight*btagCorrFactor*triggerEffSFWeight*photonEffSF;//FullSim
	 }
       
      total_in += w;
      bool pho1_isFake = false;
      bool pho2_isFake = false;
      bool isFakeFake = false;
      bool isFake = false;
      bool prompt_prompt = false;
      bool prompt_fake = false;
      if ( !((abs(pho1MotherID) >= 1 && abs(pho1MotherID) <= 6) || pho1MotherID == 21 || pho1MotherID == 2212 || abs(pho1MotherID) == 11 || abs(pho1MotherID) == 13 || abs(pho1MotherID) == 15) ) pho1_isFake = true;
      if ( !((abs(pho2MotherID) >= 1 && abs(pho2MotherID) <= 6) || pho2MotherID == 21 || pho2MotherID == 2212) || abs(pho1MotherID) == 11 || abs(pho1MotherID) == 13 || abs(pho1MotherID) == 15) pho2_isFake = true;
      if ( pho1_isFake && pho2_isFake ) isFakeFake = true;
      if ( pho1_isFake || pho2_isFake ) isFake = true;
      if ( !pho1_isFake && !pho2_isFake ) prompt_prompt = true;
      if ( !pho1_isFake || !pho2_isFake ) prompt_fake = true;
      
      //removing events which are not prompt-fake
      if ( prompt_prompt && this->processName == "gammaJet" )
	{
	  //std::cout << "[INFO]: avoding prompt-prompt in gammaJet sample" << std::endl;
	  total_rm += w;
	  continue;
	}

      //remove events which are not fake-fake
      if ( !isFakeFake && this->processName == "qcd" )
	{
	  //std::cout << "[INFO]: avoding prompt-fake and prompt-prompt in qcd sample" << std::endl;
	  total_rm += w;
	  continue;
	}

      //remove events which are not fake from WG and TTG
      if ( prompt_prompt && (this->processName == "wg" || this->processName == "ttg") )
	{
	  //std::cout << "[INFO]: avoding prompt-fake and prompt-prompt in qcd sample" << std::endl;
	  total_rm += w;
	  continue;
	}
      
      h_mgg->Fill( mGammaGamma, w );
      h_ptgg->Fill( pTGammaGamma, w );
      h_sigmaMoverM->Fill( sigmaMoverM, w*SigmaMoverMreweight );
      
      h_mr->Fill( MR, w );
      h_rsq->Fill( t1Rsq, w );
      h_mr_rsq->Fill( MR, t1Rsq, w );
      //photon1
      h_pho1pt->Fill( pho1Pt, w );
      h_pho1eta->Fill( pho1Eta, w );
      h_pho1phi->Fill( pho1Phi, w );
      h_pho1sigmaIetaIeta->Fill( pho1SigmaIetaIeta, w );
      h_pho1r9->Fill( pho1R9, w );
      h_pho1HoverE->Fill( pho1HoverE, w );
      h_pho1sumChargedHadronPt->Fill( pho1sumChargedHadronPt, w );
      h_pho1sumNeutralHadronEt->Fill( pho1sumNeutralHadronEt, w );
      h_pho1sumPhotonEt->Fill( pho1sumPhotonEt, w );
      h_pho1sigmaEoverE->Fill( pho1sigmaEOverE, w );

      //photon2
      h_pho2pt->Fill( pho2Pt, w );
      h_pho2eta->Fill( pho2Eta, w );
      h_pho2phi->Fill( pho2Phi, w );
      h_pho2sigmaIetaIeta->Fill( pho2SigmaIetaIeta, w );
      h_pho2r9->Fill( pho2R9, w );
      h_pho2HoverE->Fill( pho2HoverE, w );
      h_pho2sumChargedHadronPt->Fill( pho2sumChargedHadronPt, w );
      h_pho2sumNeutralHadronEt->Fill( pho2sumNeutralHadronEt, w );
      h_pho2sumPhotonEt->Fill( pho2sumPhotonEt, w );
      h_pho2sigmaEoverE->Fill( pho2sigmaEOverE, w );
      //njets
      h_njets->Fill( n_Jets, w );
      //met
      h_met->Fill( t1MET, w );
      //mt
      h_mt->Fill( lep1MT, w );
      //ptlep
      h_ptlep->Fill( lep1Pt, w );
      if ( pTGammaGamma > 110. ) h_unroll_highPt->Fill( GetHighPtGB(MR, t1Rsq), w);
      if ( pTGammaGamma < 110. ) h_unroll_highRes->Fill( GetHighResGB(MR, t1Rsq), w);
      if ( h_mr_rsq_c != NULL ) h_mr_rsq_c->Fill( MR, Rsq, w );
    }
  
  std::cout << "[DEBUG]: " << this->processName << " removing " << (total_rm/total_in)*100. << " % of events" << std::endl;
  std::cout << "[DEBUG]: " << this->processName << "Yield: " <<  h_mgg->Integral() << std::endl;
  if ( _debug ) std::cout << "[DEBUG]: Finishing Loop" << std::endl;
};


void HggRazorClass::CreateEffTable( float ntotal )
{
  if ( _debug ) std::cout << "[DEBUG]: Entering Loop" << std::endl;
  if (fChain == 0) return;

  Long64_t nentries = fChain->GetEntriesFast();
  Long64_t nbytes = 0, nb = 0;
  double total_in = 0, total_rm = 0;
  std::cout << "[INFO]: nentries: " << nentries << std::endl;
  float EBEBcut = 0;
  float EBEEcut = 0;
  
  float EleVetoIso_EBEB = 0;
  float EleVetoIso_EBEE = 0;

  float PtCuts_EBEB = 0;
  float PtCuts_EBEE = 0;
  
  float mggCutEBEB = 0;
  float mggCutEBEE = 0;
  
  for (Long64_t jentry=0; jentry < nentries; jentry++ )
    {
      Long64_t ientry = LoadTree(jentry);
      
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;

      if ( fabs( pho1Eta ) < 1.48 && fabs( pho2Eta ) < 1.48 )
	{
	  EBEBcut++;
	   if ( pho1passIso && pho2passIso && pho1passEleVeto && pho2passEleVeto ) EleVetoIso_EBEB++;
	   if ( pho1passIso && pho2passIso && pho1passEleVeto && pho2passEleVeto && pho1Pt > 75. && pho2Pt > 75 ) PtCuts_EBEB++;
	   if ( pho1passIso && pho2passIso && pho1passEleVeto && pho2passEleVeto && pho1Pt > 75. && pho2Pt > 75 && mGammaGamma > 230 ) mggCutEBEB++;
	}
      if ( ( (fabs( pho1Eta ) > 1.48 && fabs( pho2Eta ) < 1.48 ) || (fabs( pho1Eta ) < 1.48 && fabs( pho2Eta ) > 1.48 ) ) )
	{
	  EBEEcut++;
	  if ( pho1passIso && pho2passIso && pho1passEleVeto && pho2passEleVeto ) EleVetoIso_EBEE++;
	  if ( pho1passIso && pho2passIso && pho1passEleVeto && pho2passEleVeto && pho1Pt > 75. && pho2Pt > 75 ) PtCuts_EBEE++;
	  if ( pho1passIso && pho2passIso && pho1passEleVeto && pho2passEleVeto && pho1Pt > 75. && pho2Pt > 75 && mGammaGamma > 320 ) mggCutEBEE++;
	}
      
     
     
      
    }

  std::cout << "total eff:" << 100.*nentries/ntotal << "%" << std::endl;
  std::cout << "===================================" << std::endl;
  std::cout << "EBEBcut: " << 100.*EBEBcut/ntotal << "%" << std::endl;
  std::cout << "EleVetoIsoEBEB: " << 100.*EleVetoIso_EBEB/ntotal << "%" << std::endl;
  std::cout << "PtCutsEBEB: " << 100.*PtCuts_EBEB/ntotal << "%" << std::endl;
  std::cout << "mggCutEBEB: " << 100.*mggCutEBEB/ntotal << "%" << std::endl;

  std::cout << "===================================" << std::endl;
  std::cout << "EBEEcut: " << 100.*EBEEcut/ntotal << "%" << std::endl;
  std::cout << "EleVetoIsoEBEE: " << 100.*EleVetoIso_EBEE/ntotal << "%" << std::endl;
  std::cout << "PtCutsEBEE: " << 100.*PtCuts_EBEE/ntotal << "%" << std::endl;
  std::cout << "mggCutEBEE: " << 100.*mggCutEBEE/ntotal << "%" << std::endl;
 
  
};

void HggRazorClass::PrintEventInfo( )
{
  if ( _debug ) std::cout << "[DEBUG]: Entering Loop" << std::endl;
  if (fChain == 0) return;
  
  Long64_t nentries = fChain->GetEntriesFast();
  Long64_t nbytes = 0, nb = 0;
  double total_in = 0, total_rm = 0;
  std::cout << "[INFO]: nentries: " << nentries << std::endl;
  std::ofstream ofs ( "eventListData.txt", std::ofstream::out );
  for (Long64_t jentry=0; jentry < nentries; jentry++ )
    {
      Long64_t ientry = LoadTree(jentry);
      
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      //ofs << run << ":" << lumi << ":" << event << " " << mGammaGamma << " " << pTGammaGamma << "\n";
      ofs << run << ":" << lumi << ":" << event << " " << mGammaGamma << "\n";

		
    }
  ofs.close();
};

void HggRazorClass::PrintEventInfo(  std::vector< std::pair<long int, long int> > eventList )
{
  if ( _debug ) std::cout << "[DEBUG]: Entering Loop" << std::endl;
  if (fChain == 0) return;
  
  Long64_t nentries = fChain->GetEntriesFast();
  Long64_t nbytes = 0, nb = 0;
  double total_in = 0, total_rm = 0;
  std::cout << "[INFO]: nentries: " << nentries << std::endl;
  
  for (Long64_t jentry=0; jentry < nentries; jentry++ )
    {
      Long64_t ientry = LoadTree(jentry);
      
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      std::pair<long int, long int> myPair = std::make_pair(run,event);
      for ( auto tmp : eventList )
	{
	  if ( tmp.first == run && tmp.second == event )
	    {
	      std::cout << run << " " << lumi << " " << event << " " << mGammaGamma << " " << pho1Pt << " " << pho1Eta << " " << pho1SC_Eta
			<< " " << pho1passIso << " " << pho1passEleVeto << " " << pho1sumChargedHadronPt << " " << pho1sumNeutralHadronEt << " "  << pho1sumPhotonEt
			<< " " << pho2Pt << " " << pho2Eta << " " << pho2SC_Eta << " " << pho2passIso << " " << pho2passEleVeto
			<< " " << pho2sumChargedHadronPt << " " << pho2sumNeutralHadronEt << " "  << pho2sumPhotonEt;
	      if ( pho1passIso == 0 || pho2passIso == 0 ) std::cout << " Iso!" << std::endl;
	      else if ( ( fabs(pho1SC_Eta) > 1.4442 && fabs(pho1SC_Eta) < 1.566 ) || ( fabs(pho2SC_Eta) > 1.4442 && fabs(pho2SC_Eta) < 1.566 ) ) std::cout << " crack!\n";
	      else if ( mGammaGamma < 230.0 ) std::cout << " mgg!\n";
	      else std::cout << "\n";
	    }
	}
    }
  
};


void HggRazorClass::PrintEventInfo(  std::map< std::string, double > eventList )
{
  if ( _debug ) std::cout << "[DEBUG]: Entering Loop" << std::endl;
  if (fChain == 0) return;
  
  Long64_t nentries = fChain->GetEntriesFast();
  Long64_t nbytes = 0, nb = 0;
  double total_in = 0, total_rm = 0;
  std::cout << "[INFO]: nentries: " << nentries << std::endl;
  TFile* fout = new TFile("massDiff.root", "RECREATE");
  TH1F* h_m = new TH1F( "h_m", "h_m", 10000, -1e-5, 1e-5 );
  for (Long64_t jentry=0; jentry < nentries; jentry++ )
    {
      Long64_t ientry = LoadTree(jentry);
      
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      std::stringstream ss;
      ss << run << ":" << lumi << ":"  << event;
      std::string key = ss.str();
      for ( auto tmp : eventList )
	{
	  if ( tmp.first == key )
	    {
	      h_m->Fill( (mGammaGamma - tmp.second)/tmp.second );
	    }
	}
    }

  h_m->Write("massDiff");
  fout->Close();
  delete fout;
};

float HggRazorClass::GetHighPtGB( double mr, double r2 )
{
  int mr_bin = -1;
  int r2_bin = -1;
  for ( int i = 1; i < 6; i++ )
    {
      if ( mr > highPt_MR[i-1] && mr < highPt_MR[i] ) mr_bin = i-1;
    }
  int max_r2_bins = 6;
  if ( mr_bin == 0 )
    {
      for (  int i = 1; i < max_r2_bins; i++ )
	{
	  if ( r2 > highPt_R0[i-1] && r2 < highPt_R0[i] ) r2_bin = i-1;
	}
    }
  else if ( mr_bin == 1 )
    {
      for (  int i = 1; i < max_r2_bins-1; i++ )
	{
	  if ( r2 > highPt_R1[i-1] && r2 < highPt_R1[i] ) r2_bin = i-1;
	}
    }
  else if ( mr_bin == 2 )
    {
      for (  int i = 1; i < max_r2_bins-2; i++ )
	{
	  if ( r2 > highPt_R2[i-1] && r2 < highPt_R2[i] ) r2_bin = i-1;
	}
    }
  else if ( mr_bin == 3 )
    {
      for (  int i = 1; i < max_r2_bins-3; i++ )
	{
	  if ( r2 > highPt_R3[i-1] && r2 < highPt_R3[i] ) r2_bin = i-1;
	}
    }
  else if ( mr_bin == 4 )
    {
      for (  int i = 1; i < max_r2_bins-4; i++ )
	{
	  if ( r2 > highPt_R4[i-1] && r2 < highPt_R4[i] ) r2_bin = i-1;
	}
    }
  else
    {
      if ( mr > highPt_MR[0] ) std::cerr << "MR HighPt BIN NOT FOUND!!!, check bin boundaries! MR: " << mr  << ", Rsq: " << t1Rsq << std::endl;
    }
  
  if ( r2_bin < 0  || mr_bin < 0 ) return -1;
  if ( mr_bin == 0 ) return  r2_bin;
  if ( mr_bin == 1 ) return  5 + r2_bin;
  if ( mr_bin == 2 ) return  9 + r2_bin;
  if ( mr_bin == 3 ) return  12 + r2_bin;
  if ( mr_bin == 4 ) return  14 + r2_bin;
};

float HggRazorClass::GetHighResGB( double mr, double r2 )
{
  int mr_bin = -1;
  int r2_bin = -1;
  for ( int i = 1; i < 5; i++ )
    {
      if ( mr > highRes_MR[i-1] && mr < highRes_MR[i] ) mr_bin = i-1;
    }
  int max_r2_bins = 5;
  if ( mr_bin == 0 )
    {
      for (  int i = 1; i < max_r2_bins; i++ )
	{
	  if ( r2 > highRes_R0[i-1] && r2 < highRes_R0[i] ) r2_bin = i-1;
	}
    }
  else if ( mr_bin == 1 )
    {
      for (  int i = 1; i < max_r2_bins-1; i++ )
	{
	  if ( r2 > highRes_R1[i-1] && r2 < highRes_R1[i] ) r2_bin = i-1;
	}
    }
  else if ( mr_bin == 2 )
    {
      for (  int i = 1; i < max_r2_bins-2; i++ )
	{
	  if ( r2 > highRes_R2[i-1] && r2 < highRes_R2[i] ) r2_bin = i-1;
	}
    }
  else if ( mr_bin == 3 )
    {
      for (  int i = 1; i < max_r2_bins-3; i++ )
	{
	  if ( r2 > highRes_R3[i-1] && r2 < highRes_R3[i] ) r2_bin = i-1;
	}
    }
  else
    {
      if ( mr > highRes_MR[0] ) std::cerr << "MR HighRes BIN NOT FOUND!!!, check bin boundaries! MR: " << mr  << ", Rsq: " << t1Rsq << std::endl;
    }
  
  if ( r2_bin < 0  || mr_bin < 0 ) return -1;
  if ( mr_bin == 0 ) return  r2_bin;
  if ( mr_bin == 1 ) return  4 + r2_bin;
  if ( mr_bin == 2 ) return  7 + r2_bin;
  if ( mr_bin == 3 ) return  9 + r2_bin;
};



float HggRazorClass::GetYields( float mr, float rsq, float mgg_l, float mgg_h )
{
  Long64_t nentries = fChain->GetEntriesFast();
  Long64_t nbytes = 0, nb = 0;
  float sel_events = .0;
  
  for (Long64_t jentry=0; jentry < nentries; jentry++ )
    {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
      if (  MR > mr && Rsq > rsq
	    && mGammaGamma > mgg_l && mGammaGamma < mgg_h
	    && fabs( pho1Eta ) < 1.48 && fabs( pho2Eta ) < 1.48 && pho1Pt > 25. && pho2Pt > 25.
	    && ( pho1Pt > 40. || pho2Pt > 40. ) && pTGammaGamma > 20. )
	{
	  sel_events += weight;
	}
    }
  if ( _debug ) std::cout << "[DEBUG]: Finishing Loop" << std::endl;
  return sel_events;
};

float HggRazorClass::GetYields( float mr, float rsq, float mgg_l, float mgg_h, double& err )
{
  Long64_t nentries = fChain->GetEntriesFast();
  Long64_t nbytes = 0, nb = 0;
  float sel_events = .0;
  err = .0;
  for (Long64_t jentry=0; jentry < nentries; jentry++ )
    {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
      if (  MR > mr && Rsq > rsq
	    && mGammaGamma > mgg_l && mGammaGamma < mgg_h
	    && fabs( pho1Eta ) < 1.48 && fabs( pho2Eta ) < 1.48 && pho1Pt > 25. && pho2Pt > 25.
	    && ( pho1Pt > 40. || pho2Pt > 40. ) && pTGammaGamma > 20. )
	{
	  sel_events += weight;
	  err += weight*weight;
	}
    }
  if ( _debug ) std::cout << "[DEBUG]: Finishing Loop" << std::endl;
  err = sqrt(err);
  return sel_events;
};

bool HggRazorClass::WriteOutput( TString outName )
{
  if ( _debug ) std::cout << "[DEBUG]: Entering WriteOutput" << std::endl;
  this->fout = new TFile( outName + "_" + this->processName + ".root", "recreate");
  h_mgg->Write("mgg");
  h_ptgg->Write("ptgg");
  h_mr->Write("mr");
  h_rsq->Write("rsq");
  h_mr_rsq->Write("mr_rsq");
  h_mr_rsq_c->Write("mr_rsq_custom");
  fout->Close();
  if ( _debug ) std::cout << "[DEBUG]: Finishing WriteOutput" << std::endl;
  return true;
};

float HggRazorClass::GetHggBF( )
{
  return hggBF;
};

TH1F HggRazorClass::GetMr()
{
  return *h_mr;
};

TH1F HggRazorClass::GetRsq()
{
  return *h_rsq;
};

TH1F HggRazorClass::GetMgg()
{
  return *h_mgg;
};

TH1F HggRazorClass::GetPtgg()
{
  return *h_ptgg;
};

TH1F HggRazorClass::GetHisto( HistoTypes htype )
{
  TH1F h;
  if ( htype == HistoTypes::mr )   return *h_mr;
  if ( htype == HistoTypes::rsq )  return *h_rsq;
  if ( htype == HistoTypes::mgg )  return *h_mgg;
  if ( htype == HistoTypes::ptgg ) return *h_ptgg;
  if ( htype == HistoTypes::sigmaMoverM ) return *h_sigmaMoverM;
  
  if ( htype == HistoTypes::pho1pt ) return *h_pho1pt;
  if ( htype == HistoTypes::pho1eta ) return *h_pho1eta;
  if ( htype == HistoTypes::pho1phi ) return *h_pho1phi;
  if ( htype == HistoTypes::pho1sigmaIetaIeta ) return *h_pho1sigmaIetaIeta;
  if ( htype == HistoTypes::pho1r9 ) return *h_pho1r9;
  if ( htype == HistoTypes::pho1HoverE ) return *h_pho1HoverE;
  if ( htype == HistoTypes::pho1sumChargedHadronPt ) return *h_pho1sumChargedHadronPt;
  if ( htype == HistoTypes::pho1sumNeutralHadronEt ) return *h_pho1sumNeutralHadronEt;
  if ( htype == HistoTypes::pho1sumPhotonEt ) return *h_pho1sumPhotonEt;
  if ( htype == HistoTypes::pho1sigmaEoverE ) return *h_pho1sigmaEoverE;
  
  if ( htype == HistoTypes::pho2pt ) return *h_pho2pt;
  if ( htype == HistoTypes::pho2eta ) return *h_pho2eta;
  if ( htype == HistoTypes::pho2phi ) return *h_pho2phi;
  if ( htype == HistoTypes::pho2sigmaIetaIeta ) return *h_pho2sigmaIetaIeta;
  if ( htype == HistoTypes::pho2r9 ) return *h_pho2r9;
  if ( htype == HistoTypes::pho2HoverE ) return *h_pho2HoverE;
  if ( htype == HistoTypes::pho2sumChargedHadronPt ) return *h_pho2sumChargedHadronPt;
  if ( htype == HistoTypes::pho2sumNeutralHadronEt ) return *h_pho2sumNeutralHadronEt;
  if ( htype == HistoTypes::pho2sumPhotonEt ) return *h_pho2sumPhotonEt;
  if ( htype == HistoTypes::pho2sigmaEoverE ) return *h_pho2sigmaEoverE;
  
  if ( htype == HistoTypes::njets ) return *h_njets;
  if ( htype == HistoTypes::met ) return *h_met;
  if ( htype == HistoTypes::mt ) return *h_mt;
  if ( htype == HistoTypes::ptlep ) return *h_ptlep;
  
  if ( htype == HistoTypes::unrollHighPt ) return *h_unroll_highPt;
  if ( htype == HistoTypes::unrollHighRes ) return *h_unroll_highRes;
  
  std::cerr << "[ERROR]: HISTOGRAM TO BE RETURNED HAS NOT BEEN DEFINED, RETURNING AN EMPTY HISTO (see HggRazorClass.cc:GetHisto)" << std::endl;

  return h;
};
