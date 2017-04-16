#ifndef HGG_RAZOR_CLASS_HH
#define HGG_RAZOR_CLASS_HH
//C++ INCLUDES
#include <iostream>
#include <string>
#include <sstream>
//ROOT INCLUDES
#include <TH1F.h>
#include <TH2F.h>
#include <TString.h>
//LOCAL INCLUDES
#include "HggTree.hh"
#include "HggAux.hh"

class HggRazorClass : public HggTree
{
public:
  HggRazorClass( );
  HggRazorClass( TTree* tree );
  HggRazorClass( TTree* tree, TString processName, TString boxName, bool info = false, bool debug = false );
  ~HggRazorClass( );
  //higgs
  bool InitMggHisto( );
  bool InitPtggHisto( );
  bool InitSigmaMoverMHisto( );
  
  bool InitMrHisto( );
  bool InitRsqHisto( );
  //photon1
  bool InitPho1Pt( );
  bool InitPho1Eta( );
  bool InitPho1Phi( );
  bool InitPho1SigmaIetaIeta( );
  bool InitPho1R9( );
  bool InitPho1HoverE( );
  bool InitPho1SumChargedHadronPt( );
  bool InitPho1SumNeutralHadronEt( );
  bool InitPho1SumPhotonEt( );
  bool InitPho1SigmaEoverE( );
  
  //photon2
  bool InitPho2Pt( );
  bool InitPho2Eta( );
  bool InitPho2Phi( );
  bool InitPho2SigmaIetaIeta( );
  bool InitPho2R9( );
  bool InitPho2HoverE( );
  bool InitPho2SumChargedHadronPt( );
  bool InitPho2SumNeutralHadronEt( );
  bool InitPho2SumPhotonEt( );
  bool InitPho2SigmaEoverE( );

  //MET and Lepton
  bool InitMET( );
  bool InitMT( );
  
  
  bool InitNjets( );
  bool InitMrRsqHisto( );
  bool InitMrRsqCustomHisto( int nx, float* bx, int ny, float* by );
  bool IntUnrollHistos( );
  void Loop();
  void CreateEffTable( float ntotal );
  void PrintEventInfo(  std::map< std::string, double > eventList );
  void PrintEventInfo( std::vector< std::pair<long int, long int> > eventList );
  void PrintEventInfo( );
  float GetYields( float mr, float rsq, float mgg_l, float mgg_h );
  float GetYields( float mr, float rsq, float mgg_l, float mgg_h, double& err );
  bool WriteOutput( TString outName = "default" );
  TH1F GetMr();
  TH1F GetRsq();
  TH1F GetMgg();
  TH1F GetPtgg();
  TH1F GetHisto( HistoTypes htype );
  float GetHighPtGB( double mr, double r2 );
  float GetHighResGB( double mr, double r2 );
  static float GetHggBF( );
private:

  static constexpr float hggBF = 2.28e-3;
  
  bool _debug;
  bool _info;
  TString processName;
  TString boxName;
  
  // D e f i n e   B i n n i n g
  //----------------------------
  static int   n_mgg;
  static float mgg_l;
  static float mgg_h;
  TH1F* h_mgg;
  
  static int   n_ptgg;
  static float ptgg_l;
  static float ptgg_h;
  TH1F* h_ptgg;

  static int   n_sigmaMoverM;
  static float sigmaMoverM_l;
  static float sigmaMoverM_h;
  TH1F* h_sigmaMoverM;

  static int   n_mr;
  static float mr_l;
  static float mr_h;
  TH1F* h_mr;

  static int   n_rsq;
  static float rsq_l;
  static float rsq_h;
  TH1F* h_rsq;
  
  //unroll plots
  static int n_unroll_highPt;
  TH1F* h_unroll_highPt;
  
  static int n_unroll_highRes;
  TH1F* h_unroll_highRes;

  static float highPt_MR[6];
  static float highPt_R0[6];
  static float highPt_R1[5];
  static float highPt_R2[4];
  static float highPt_R3[3];
  static float highPt_R4[2];

  static float highRes_MR[5];
  static float highRes_R0[5];
  static float highRes_R1[4];
  static float highRes_R2[3];
  static float highRes_R3[2];
  
  
  //--------------
  //P h o t o n  1
  //--------------
  static int   n_pho1pt;
  static float pho1pt_l;
  static float pho1pt_h;
  TH1F* h_pho1pt;

  static int   n_pho1eta;
  static float pho1eta_l;
  static float pho1eta_h;
  TH1F* h_pho1eta;

  static int   n_pho1phi;
  static float pho1phi_l;
  static float pho1phi_h;
  TH1F* h_pho1phi;

  static int   n_pho1sigmaIetaIeta;
  static float pho1sigmaIetaIeta_l;
  static float pho1sigmaIetaIeta_h;
  TH1F* h_pho1sigmaIetaIeta;

  static int   n_pho1r9;
  static float pho1r9_l;
  static float pho1r9_h;
  TH1F* h_pho1r9;

  static int   n_pho1HoverE;
  static float pho1HoverE_l;
  static float pho1HoverE_h;
  TH1F* h_pho1HoverE;
  
  static int   n_pho1sumChargedHadronPt;
  static float pho1sumChargedHadronPt_l;
  static float pho1sumChargedHadronPt_h;
  TH1F* h_pho1sumChargedHadronPt;

  static int   n_pho1sumNeutralHadronEt;
  static float pho1sumNeutralHadronEt_l;
  static float pho1sumNeutralHadronEt_h;
  TH1F* h_pho1sumNeutralHadronEt;

  static int   n_pho1sumPhotonEt;
  static float pho1sumPhotonEt_l;
  static float pho1sumPhotonEt_h;
  TH1F* h_pho1sumPhotonEt;
  
  static int   n_pho1sigmaEoverE;
  static float pho1sigmaEoverE_l;
  static float pho1sigmaEoverE_h;
  TH1F* h_pho1sigmaEoverE;

  //--------------
  //P h o t o n  2
  //--------------
  static int   n_pho2pt;
  static float pho2pt_l;
  static float pho2pt_h;
  TH1F* h_pho2pt;

  static int   n_pho2eta;
  static float pho2eta_l;
  static float pho2eta_h;
  TH1F* h_pho2eta;

  static int   n_pho2phi;
  static float pho2phi_l;
  static float pho2phi_h;
  TH1F* h_pho2phi;

  static int   n_pho2sigmaIetaIeta;
  static float pho2sigmaIetaIeta_l;
  static float pho2sigmaIetaIeta_h;
  TH1F* h_pho2sigmaIetaIeta;

  static int   n_pho2r9;
  static float pho2r9_l;
  static float pho2r9_h;
  TH1F* h_pho2r9;

  static int   n_pho2HoverE;
  static float pho2HoverE_l;
  static float pho2HoverE_h;
  TH1F* h_pho2HoverE;
  
  static int   n_pho2sumChargedHadronPt;
  static float pho2sumChargedHadronPt_l;
  static float pho2sumChargedHadronPt_h;
  TH1F* h_pho2sumChargedHadronPt;

  static int   n_pho2sumNeutralHadronEt;
  static float pho2sumNeutralHadronEt_l;
  static float pho2sumNeutralHadronEt_h;
  TH1F* h_pho2sumNeutralHadronEt;

  static int   n_pho2sumPhotonEt;
  static float pho2sumPhotonEt_l;
  static float pho2sumPhotonEt_h;
  TH1F* h_pho2sumPhotonEt;
  
  static int   n_pho2sigmaEoverE;
  static float pho2sigmaEoverE_l;
  static float pho2sigmaEoverE_h;
  TH1F* h_pho2sigmaEoverE;
  
  //--------
  // J e t s
  //--------
  static int   n_njets;
  static float njets_l;
  static float njets_h;
  TH1F* h_njets;

  //---------
  // MET + MT
  //---------
  static int   n_met;
  static float met_l;
  static float met_h;
  TH1F* h_met;

  static int   n_mt;
  static float mt_l;
  static float mt_h;
  TH1F* h_mt;
  

  //2D Histos
  TH2F* h_mr_rsq;
  TH2F* h_mr_rsq_c;//custom binning
  // o u t p u t  r o o t  f i l e
  //------------------------------
  TFile* fout;
};

#endif
