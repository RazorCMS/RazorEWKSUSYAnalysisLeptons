//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Feb  9 20:00:33 2017 by ROOT version 6.02/05
// from TTree tree_fit_sb/tree_fit_sb
// found on file: mlfit_1ktoys_toy_all_toys.root
//////////////////////////////////////////////////////////

#ifndef tree_fit_sb_h
#define tree_fit_sb_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <RooWorkspace.h>
#include <TCanvas.h>
#include <RooWorkspace.h>
#include <RooAbsPdf.h>
#include <RooRealVar.h>
#include <RooAbsData.h>
#include <RooPlot.h>
#include <RooArgSet.h>
#include <RooWorkspace.h>
#include <RooDataSet.h>
#include <RooRealVar.h>
#include <RooExponential.h>
#include <RooAddPdf.h>
#include <RooGaussian.h>
#include <RooMinimizer.h>
#include <RooFitResult.h>
#include <RooPlot.h>
#include <RooExtendPdf.h>
#include <RooStats/SPlot.h>
#include <RooStats/ModelConfig.h>
#include <RooGenericPdf.h>
#include <RooFormulaVar.h>
#include <RooBernstein.h>
#include <RooMinuit.h>
#include <RooNLLVar.h>
#include <RooRandom.h>
#include <RooDataHist.h>
#include <RooHistPdf.h>
// Header file for the classes stored in the TTree if any.

class tree_fit_sb {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

  TString FullWorkspaceName;
  TString HggWorkspaceName;
  double systematics[217];
  RooWorkspace* ws;
  RooWorkspace* ws_hgg;
   // Declaration of leaf types
   Int_t           fit_status;
   Double_t        mu;
   Double_t        muErr;
   Double_t        muLoErr;
   Double_t        muHiErr;
   Int_t           numbadnll;
   Double_t        nll_min;
   Double_t        nll_nll0;
   Double_t        CMS_Lumi_In;
   Double_t        PdfNorm_In;
   Double_t        Photon_Trigger_In;
   Double_t        SMH_JES_In;
   Double_t        SMH_btag_In;
   Double_t        SMH_facRenScale_bin0_In;
   Double_t        SMH_facRenScale_bin1_In;
   Double_t        SMH_facRenScale_bin10_In;
   Double_t        SMH_facRenScale_bin11_In;
   Double_t        SMH_facRenScale_bin12_In;
   Double_t        SMH_facRenScale_bin13_In;
   Double_t        SMH_facRenScale_bin2_In;
   Double_t        SMH_facRenScale_bin3_In;
   Double_t        SMH_facRenScale_bin4_In;
   Double_t        SMH_facRenScale_bin5_In;
   Double_t        SMH_facRenScale_bin6_In;
   Double_t        SMH_facRenScale_bin7_In;
   Double_t        SMH_facRenScale_bin8_In;
   Double_t        SMH_facRenScale_bin9_In;
   Double_t        SMH_facScale_bin0_In;
   Double_t        SMH_facScale_bin1_In;
   Double_t        SMH_facScale_bin10_In;
   Double_t        SMH_facScale_bin11_In;
   Double_t        SMH_facScale_bin12_In;
   Double_t        SMH_facScale_bin13_In;
   Double_t        SMH_facScale_bin2_In;
   Double_t        SMH_facScale_bin3_In;
   Double_t        SMH_facScale_bin4_In;
   Double_t        SMH_facScale_bin5_In;
   Double_t        SMH_facScale_bin6_In;
   Double_t        SMH_facScale_bin7_In;
   Double_t        SMH_facScale_bin8_In;
   Double_t        SMH_facScale_bin9_In;
   Double_t        SMH_misstag_In;
   Double_t        SMH_pdf0_In;
   Double_t        SMH_pdf1_In;
   Double_t        SMH_pdf10_In;
   Double_t        SMH_pdf11_In;
   Double_t        SMH_pdf12_In;
   Double_t        SMH_pdf13_In;
   Double_t        SMH_pdf14_In;
   Double_t        SMH_pdf15_In;
   Double_t        SMH_pdf16_In;
   Double_t        SMH_pdf17_In;
   Double_t        SMH_pdf18_In;
   Double_t        SMH_pdf19_In;
   Double_t        SMH_pdf2_In;
   Double_t        SMH_pdf20_In;
   Double_t        SMH_pdf21_In;
   Double_t        SMH_pdf22_In;
   Double_t        SMH_pdf23_In;
   Double_t        SMH_pdf24_In;
   Double_t        SMH_pdf25_In;
   Double_t        SMH_pdf26_In;
   Double_t        SMH_pdf27_In;
   Double_t        SMH_pdf28_In;
   Double_t        SMH_pdf29_In;
   Double_t        SMH_pdf3_In;
   Double_t        SMH_pdf30_In;
   Double_t        SMH_pdf31_In;
   Double_t        SMH_pdf32_In;
   Double_t        SMH_pdf33_In;
   Double_t        SMH_pdf34_In;
   Double_t        SMH_pdf35_In;
   Double_t        SMH_pdf36_In;
   Double_t        SMH_pdf37_In;
   Double_t        SMH_pdf38_In;
   Double_t        SMH_pdf39_In;
   Double_t        SMH_pdf4_In;
   Double_t        SMH_pdf40_In;
   Double_t        SMH_pdf41_In;
   Double_t        SMH_pdf42_In;
   Double_t        SMH_pdf43_In;
   Double_t        SMH_pdf44_In;
   Double_t        SMH_pdf45_In;
   Double_t        SMH_pdf46_In;
   Double_t        SMH_pdf47_In;
   Double_t        SMH_pdf48_In;
   Double_t        SMH_pdf49_In;
   Double_t        SMH_pdf5_In;
   Double_t        SMH_pdf50_In;
   Double_t        SMH_pdf51_In;
   Double_t        SMH_pdf52_In;
   Double_t        SMH_pdf53_In;
   Double_t        SMH_pdf54_In;
   Double_t        SMH_pdf55_In;
   Double_t        SMH_pdf56_In;
   Double_t        SMH_pdf57_In;
   Double_t        SMH_pdf58_In;
   Double_t        SMH_pdf59_In;
   Double_t        SMH_pdf6_In;
   Double_t        SMH_pdf7_In;
   Double_t        SMH_pdf8_In;
   Double_t        SMH_pdf9_In;
   Double_t        SMH_renScale_bin0_In;
   Double_t        SMH_renScale_bin1_In;
   Double_t        SMH_renScale_bin10_In;
   Double_t        SMH_renScale_bin11_In;
   Double_t        SMH_renScale_bin12_In;
   Double_t        SMH_renScale_bin13_In;
   Double_t        SMH_renScale_bin2_In;
   Double_t        SMH_renScale_bin3_In;
   Double_t        SMH_renScale_bin4_In;
   Double_t        SMH_renScale_bin5_In;
   Double_t        SMH_renScale_bin6_In;
   Double_t        SMH_renScale_bin7_In;
   Double_t        SMH_renScale_bin8_In;
   Double_t        SMH_renScale_bin9_In;
   Double_t        SigmaMoverMEfficiency_In;
   Double_t        Signal_ISR_In;
   Double_t        Signal_JES_In;
   Double_t        Signal_btag_In;
   Double_t        Signal_facRenScale_bin0_In;
   Double_t        Signal_facRenScale_bin1_In;
   Double_t        Signal_facRenScale_bin10_In;
   Double_t        Signal_facRenScale_bin11_In;
   Double_t        Signal_facRenScale_bin12_In;
   Double_t        Signal_facRenScale_bin13_In;
   Double_t        Signal_facRenScale_bin2_In;
   Double_t        Signal_facRenScale_bin3_In;
   Double_t        Signal_facRenScale_bin4_In;
   Double_t        Signal_facRenScale_bin5_In;
   Double_t        Signal_facRenScale_bin6_In;
   Double_t        Signal_facRenScale_bin7_In;
   Double_t        Signal_facRenScale_bin8_In;
   Double_t        Signal_facRenScale_bin9_In;
   Double_t        Signal_facScale_bin0_In;
   Double_t        Signal_facScale_bin1_In;
   Double_t        Signal_facScale_bin10_In;
   Double_t        Signal_facScale_bin11_In;
   Double_t        Signal_facScale_bin12_In;
   Double_t        Signal_facScale_bin13_In;
   Double_t        Signal_facScale_bin2_In;
   Double_t        Signal_facScale_bin3_In;
   Double_t        Signal_facScale_bin4_In;
   Double_t        Signal_facScale_bin5_In;
   Double_t        Signal_facScale_bin6_In;
   Double_t        Signal_facScale_bin7_In;
   Double_t        Signal_facScale_bin8_In;
   Double_t        Signal_facScale_bin9_In;
   Double_t        Signal_misstag_In;
   Double_t        Signal_pdf0_In;
   Double_t        Signal_pdf1_In;
   Double_t        Signal_pdf10_In;
   Double_t        Signal_pdf11_In;
   Double_t        Signal_pdf12_In;
   Double_t        Signal_pdf13_In;
   Double_t        Signal_pdf14_In;
   Double_t        Signal_pdf15_In;
   Double_t        Signal_pdf16_In;
   Double_t        Signal_pdf17_In;
   Double_t        Signal_pdf18_In;
   Double_t        Signal_pdf19_In;
   Double_t        Signal_pdf2_In;
   Double_t        Signal_pdf20_In;
   Double_t        Signal_pdf21_In;
   Double_t        Signal_pdf22_In;
   Double_t        Signal_pdf23_In;
   Double_t        Signal_pdf24_In;
   Double_t        Signal_pdf25_In;
   Double_t        Signal_pdf26_In;
   Double_t        Signal_pdf27_In;
   Double_t        Signal_pdf28_In;
   Double_t        Signal_pdf29_In;
   Double_t        Signal_pdf3_In;
   Double_t        Signal_pdf30_In;
   Double_t        Signal_pdf31_In;
   Double_t        Signal_pdf32_In;
   Double_t        Signal_pdf33_In;
   Double_t        Signal_pdf34_In;
   Double_t        Signal_pdf35_In;
   Double_t        Signal_pdf36_In;
   Double_t        Signal_pdf37_In;
   Double_t        Signal_pdf38_In;
   Double_t        Signal_pdf39_In;
   Double_t        Signal_pdf4_In;
   Double_t        Signal_pdf40_In;
   Double_t        Signal_pdf41_In;
   Double_t        Signal_pdf42_In;
   Double_t        Signal_pdf43_In;
   Double_t        Signal_pdf44_In;
   Double_t        Signal_pdf45_In;
   Double_t        Signal_pdf46_In;
   Double_t        Signal_pdf47_In;
   Double_t        Signal_pdf48_In;
   Double_t        Signal_pdf49_In;
   Double_t        Signal_pdf5_In;
   Double_t        Signal_pdf50_In;
   Double_t        Signal_pdf51_In;
   Double_t        Signal_pdf52_In;
   Double_t        Signal_pdf53_In;
   Double_t        Signal_pdf54_In;
   Double_t        Signal_pdf55_In;
   Double_t        Signal_pdf56_In;
   Double_t        Signal_pdf57_In;
   Double_t        Signal_pdf6_In;
   Double_t        Signal_pdf7_In;
   Double_t        Signal_pdf8_In;
   Double_t        Signal_pdf9_In;
   Double_t        Signal_renScale_bin0_In;
   Double_t        Signal_renScale_bin1_In;
   Double_t        Signal_renScale_bin10_In;
   Double_t        Signal_renScale_bin11_In;
   Double_t        Signal_renScale_bin12_In;
   Double_t        Signal_renScale_bin13_In;
   Double_t        Signal_renScale_bin2_In;
   Double_t        Signal_renScale_bin3_In;
   Double_t        Signal_renScale_bin4_In;
   Double_t        Signal_renScale_bin5_In;
   Double_t        Signal_renScale_bin6_In;
   Double_t        Signal_renScale_bin7_In;
   Double_t        Signal_renScale_bin8_In;
   Double_t        Signal_renScale_bin9_In;
   Double_t        mu_Global_In;
   Double_t        hzbb_mu_Global_In;
   Double_t        highpt_mu_Global_In;
   Double_t        lowres_mu_Global_In;
   Double_t        CMS_Lumi;
   Double_t        PdfNorm;
   Double_t        Photon_Trigger;
   Double_t        SMH_JES;
   Double_t        SMH_btag;
   Double_t        SMH_facRenScale_bin0;
   Double_t        SMH_facRenScale_bin1;
   Double_t        SMH_facRenScale_bin10;
   Double_t        SMH_facRenScale_bin11;
   Double_t        SMH_facRenScale_bin12;
   Double_t        SMH_facRenScale_bin13;
   Double_t        SMH_facRenScale_bin2;
   Double_t        SMH_facRenScale_bin3;
   Double_t        SMH_facRenScale_bin4;
   Double_t        SMH_facRenScale_bin5;
   Double_t        SMH_facRenScale_bin6;
   Double_t        SMH_facRenScale_bin7;
   Double_t        SMH_facRenScale_bin8;
   Double_t        SMH_facRenScale_bin9;
   Double_t        SMH_facScale_bin0;
   Double_t        SMH_facScale_bin1;
   Double_t        SMH_facScale_bin10;
   Double_t        SMH_facScale_bin11;
   Double_t        SMH_facScale_bin12;
   Double_t        SMH_facScale_bin13;
   Double_t        SMH_facScale_bin2;
   Double_t        SMH_facScale_bin3;
   Double_t        SMH_facScale_bin4;
   Double_t        SMH_facScale_bin5;
   Double_t        SMH_facScale_bin6;
   Double_t        SMH_facScale_bin7;
   Double_t        SMH_facScale_bin8;
   Double_t        SMH_facScale_bin9;
   Double_t        SMH_misstag;
   Double_t        SMH_pdf0;
   Double_t        SMH_pdf1;
   Double_t        SMH_pdf10;
   Double_t        SMH_pdf11;
   Double_t        SMH_pdf12;
   Double_t        SMH_pdf13;
   Double_t        SMH_pdf14;
   Double_t        SMH_pdf15;
   Double_t        SMH_pdf16;
   Double_t        SMH_pdf17;
   Double_t        SMH_pdf18;
   Double_t        SMH_pdf19;
   Double_t        SMH_pdf2;
   Double_t        SMH_pdf20;
   Double_t        SMH_pdf21;
   Double_t        SMH_pdf22;
   Double_t        SMH_pdf23;
   Double_t        SMH_pdf24;
   Double_t        SMH_pdf25;
   Double_t        SMH_pdf26;
   Double_t        SMH_pdf27;
   Double_t        SMH_pdf28;
   Double_t        SMH_pdf29;
   Double_t        SMH_pdf3;
   Double_t        SMH_pdf30;
   Double_t        SMH_pdf31;
   Double_t        SMH_pdf32;
   Double_t        SMH_pdf33;
   Double_t        SMH_pdf34;
   Double_t        SMH_pdf35;
   Double_t        SMH_pdf36;
   Double_t        SMH_pdf37;
   Double_t        SMH_pdf38;
   Double_t        SMH_pdf39;
   Double_t        SMH_pdf4;
   Double_t        SMH_pdf40;
   Double_t        SMH_pdf41;
   Double_t        SMH_pdf42;
   Double_t        SMH_pdf43;
   Double_t        SMH_pdf44;
   Double_t        SMH_pdf45;
   Double_t        SMH_pdf46;
   Double_t        SMH_pdf47;
   Double_t        SMH_pdf48;
   Double_t        SMH_pdf49;
   Double_t        SMH_pdf5;
   Double_t        SMH_pdf50;
   Double_t        SMH_pdf51;
   Double_t        SMH_pdf52;
   Double_t        SMH_pdf53;
   Double_t        SMH_pdf54;
   Double_t        SMH_pdf55;
   Double_t        SMH_pdf56;
   Double_t        SMH_pdf57;
   Double_t        SMH_pdf58;
   Double_t        SMH_pdf59;
   Double_t        SMH_pdf6;
   Double_t        SMH_pdf7;
   Double_t        SMH_pdf8;
   Double_t        SMH_pdf9;
   Double_t        SMH_renScale_bin0;
   Double_t        SMH_renScale_bin1;
   Double_t        SMH_renScale_bin10;
   Double_t        SMH_renScale_bin11;
   Double_t        SMH_renScale_bin12;
   Double_t        SMH_renScale_bin13;
   Double_t        SMH_renScale_bin2;
   Double_t        SMH_renScale_bin3;
   Double_t        SMH_renScale_bin4;
   Double_t        SMH_renScale_bin5;
   Double_t        SMH_renScale_bin6;
   Double_t        SMH_renScale_bin7;
   Double_t        SMH_renScale_bin8;
   Double_t        SMH_renScale_bin9;
   Double_t        SigmaMoverMEfficiency;
   Double_t        Signal_ISR;
   Double_t        Signal_JES;
   Double_t        Signal_btag;
   Double_t        Signal_facRenScale_bin0;
   Double_t        Signal_facRenScale_bin1;
   Double_t        Signal_facRenScale_bin10;
   Double_t        Signal_facRenScale_bin11;
   Double_t        Signal_facRenScale_bin12;
   Double_t        Signal_facRenScale_bin13;
   Double_t        Signal_facRenScale_bin2;
   Double_t        Signal_facRenScale_bin3;
   Double_t        Signal_facRenScale_bin4;
   Double_t        Signal_facRenScale_bin5;
   Double_t        Signal_facRenScale_bin6;
   Double_t        Signal_facRenScale_bin7;
   Double_t        Signal_facRenScale_bin8;
   Double_t        Signal_facRenScale_bin9;
   Double_t        Signal_facScale_bin0;
   Double_t        Signal_facScale_bin1;
   Double_t        Signal_facScale_bin10;
   Double_t        Signal_facScale_bin11;
   Double_t        Signal_facScale_bin12;
   Double_t        Signal_facScale_bin13;
   Double_t        Signal_facScale_bin2;
   Double_t        Signal_facScale_bin3;
   Double_t        Signal_facScale_bin4;
   Double_t        Signal_facScale_bin5;
   Double_t        Signal_facScale_bin6;
   Double_t        Signal_facScale_bin7;
   Double_t        Signal_facScale_bin8;
   Double_t        Signal_facScale_bin9;
   Double_t        Signal_misstag;
   Double_t        Signal_pdf0;
   Double_t        Signal_pdf1;
   Double_t        Signal_pdf10;
   Double_t        Signal_pdf11;
   Double_t        Signal_pdf12;
   Double_t        Signal_pdf13;
   Double_t        Signal_pdf14;
   Double_t        Signal_pdf15;
   Double_t        Signal_pdf16;
   Double_t        Signal_pdf17;
   Double_t        Signal_pdf18;
   Double_t        Signal_pdf19;
   Double_t        Signal_pdf2;
   Double_t        Signal_pdf20;
   Double_t        Signal_pdf21;
   Double_t        Signal_pdf22;
   Double_t        Signal_pdf23;
   Double_t        Signal_pdf24;
   Double_t        Signal_pdf25;
   Double_t        Signal_pdf26;
   Double_t        Signal_pdf27;
   Double_t        Signal_pdf28;
   Double_t        Signal_pdf29;
   Double_t        Signal_pdf3;
   Double_t        Signal_pdf30;
   Double_t        Signal_pdf31;
   Double_t        Signal_pdf32;
   Double_t        Signal_pdf33;
   Double_t        Signal_pdf34;
   Double_t        Signal_pdf35;
   Double_t        Signal_pdf36;
   Double_t        Signal_pdf37;
   Double_t        Signal_pdf38;
   Double_t        Signal_pdf39;
   Double_t        Signal_pdf4;
   Double_t        Signal_pdf40;
   Double_t        Signal_pdf41;
   Double_t        Signal_pdf42;
   Double_t        Signal_pdf43;
   Double_t        Signal_pdf44;
   Double_t        Signal_pdf45;
   Double_t        Signal_pdf46;
   Double_t        Signal_pdf47;
   Double_t        Signal_pdf48;
   Double_t        Signal_pdf49;
   Double_t        Signal_pdf5;
   Double_t        Signal_pdf50;
   Double_t        Signal_pdf51;
   Double_t        Signal_pdf52;
   Double_t        Signal_pdf53;
   Double_t        Signal_pdf54;
   Double_t        Signal_pdf55;
   Double_t        Signal_pdf56;
   Double_t        Signal_pdf57;
   Double_t        Signal_pdf6;
   Double_t        Signal_pdf7;
   Double_t        Signal_pdf8;
   Double_t        Signal_pdf9;
   Double_t        Signal_renScale_bin0;
   Double_t        Signal_renScale_bin1;
   Double_t        Signal_renScale_bin10;
   Double_t        Signal_renScale_bin11;
   Double_t        Signal_renScale_bin12;
   Double_t        Signal_renScale_bin13;
   Double_t        Signal_renScale_bin2;
   Double_t        Signal_renScale_bin3;
   Double_t        Signal_renScale_bin4;
   Double_t        Signal_renScale_bin5;
   Double_t        Signal_renScale_bin6;
   Double_t        Signal_renScale_bin7;
   Double_t        Signal_renScale_bin8;
   Double_t        Signal_renScale_bin9;
   Double_t        mu_Global;
   Double_t        hzbb_mu_Global;
   Double_t        highpt_mu_Global;
   Double_t        lowres_mu_Global;
   Double_t        n_exp_final_binch10_proc_Bkg;
   Double_t        n_exp_final_binch10_proc_SMH;
   Double_t        n_exp_final_binch10_proc_signal;
   Double_t        n_exp_final_binch11_proc_Bkg;
   Double_t        n_exp_final_binch11_proc_SMH;
   Double_t        n_exp_final_binch11_proc_signal;
   Double_t        n_exp_final_binch12_proc_Bkg;
   Double_t        n_exp_final_binch12_proc_SMH;
   Double_t        n_exp_final_binch12_proc_signal;
   Double_t        n_exp_final_binch13_proc_Bkg;
   Double_t        n_exp_final_binch13_proc_SMH;
   Double_t        n_exp_final_binch13_proc_signal;
   Double_t        n_exp_final_binch14_highResBin9_proc_Bkg;
   Double_t        n_exp_final_binch14_highResBin9_proc_SMH;
   Double_t        n_exp_final_binch14_highResBin9_proc_signal;
   Double_t        n_exp_final_binch14_lowResBin9_proc_Bkg;
   Double_t        n_exp_final_binch14_lowResBin9_proc_SMH;
   Double_t        n_exp_final_binch14_lowResBin9_proc_signal;
   Double_t        n_exp_final_binch1_proc_Bkg;
   Double_t        n_exp_final_binch1_proc_SMH;
   Double_t        n_exp_final_binch1_proc_signal;
   Double_t        n_exp_final_binch2_proc_Bkg;
   Double_t        n_exp_final_binch2_proc_SMH;
   Double_t        n_exp_final_binch2_proc_signal;
   Double_t        n_exp_final_binch3_highResBin10_proc_Bkg;
   Double_t        n_exp_final_binch3_highResBin10_proc_SMH;
   Double_t        n_exp_final_binch3_highResBin10_proc_signal;
   Double_t        n_exp_final_binch3_lowResBin10_proc_Bkg;
   Double_t        n_exp_final_binch3_lowResBin10_proc_SMH;
   Double_t        n_exp_final_binch3_lowResBin10_proc_signal;
   Double_t        n_exp_final_binch4_highResBin11_proc_Bkg;
   Double_t        n_exp_final_binch4_highResBin11_proc_SMH;
   Double_t        n_exp_final_binch4_highResBin11_proc_signal;
   Double_t        n_exp_final_binch4_lowResBin11_proc_Bkg;
   Double_t        n_exp_final_binch4_lowResBin11_proc_SMH;
   Double_t        n_exp_final_binch4_lowResBin11_proc_signal;
   Double_t        n_exp_final_binch5_highResBin12_proc_Bkg;
   Double_t        n_exp_final_binch5_highResBin12_proc_SMH;
   Double_t        n_exp_final_binch5_highResBin12_proc_signal;
   Double_t        n_exp_final_binch5_lowResBin12_proc_Bkg;
   Double_t        n_exp_final_binch5_lowResBin12_proc_SMH;
   Double_t        n_exp_final_binch5_lowResBin12_proc_signal;
   Double_t        n_exp_final_binch6_highResBin13_proc_Bkg;
   Double_t        n_exp_final_binch6_highResBin13_proc_SMH;
   Double_t        n_exp_final_binch6_highResBin13_proc_signal;
   Double_t        n_exp_final_binch6_lowResBin13_proc_Bkg;
   Double_t        n_exp_final_binch6_lowResBin13_proc_SMH;
   Double_t        n_exp_final_binch6_lowResBin13_proc_signal;
   Double_t        n_exp_final_binch7_proc_Bkg;
   Double_t        n_exp_final_binch7_proc_SMH;
   Double_t        n_exp_final_binch7_proc_signal;
   Double_t        n_exp_final_binch8_proc_Bkg;
   Double_t        n_exp_final_binch8_proc_SMH;
   Double_t        n_exp_final_binch8_proc_signal;
   Double_t        n_exp_final_binch9_proc_Bkg;
   Double_t        n_exp_final_binch9_proc_SMH;
   Double_t        n_exp_final_binch9_proc_signal;

   // List of branches
   TBranch        *b_fit_status;   //!
   TBranch        *b_mu;   //!
   TBranch        *b_muErr;   //!
   TBranch        *b_muLoErr;   //!
   TBranch        *b_muHiErr;   //!
   TBranch        *b_numbadnll;   //!
   TBranch        *b_nll_min;   //!
   TBranch        *b_nll_nll0;   //!
   TBranch        *b_CMS_Lumi_In;   //!
   TBranch        *b_PdfNorm_In;   //!
   TBranch        *b_Photon_Trigger_In;   //!
   TBranch        *b_SMH_JES_In;   //!
   TBranch        *b_SMH_btag_In;   //!
   TBranch        *b_SMH_facRenScale_bin0_In;   //!
   TBranch        *b_SMH_facRenScale_bin1_In;   //!
   TBranch        *b_SMH_facRenScale_bin10_In;   //!
   TBranch        *b_SMH_facRenScale_bin11_In;   //!
   TBranch        *b_SMH_facRenScale_bin12_In;   //!
   TBranch        *b_SMH_facRenScale_bin13_In;   //!
   TBranch        *b_SMH_facRenScale_bin2_In;   //!
   TBranch        *b_SMH_facRenScale_bin3_In;   //!
   TBranch        *b_SMH_facRenScale_bin4_In;   //!
   TBranch        *b_SMH_facRenScale_bin5_In;   //!
   TBranch        *b_SMH_facRenScale_bin6_In;   //!
   TBranch        *b_SMH_facRenScale_bin7_In;   //!
   TBranch        *b_SMH_facRenScale_bin8_In;   //!
   TBranch        *b_SMH_facRenScale_bin9_In;   //!
   TBranch        *b_SMH_facScale_bin0_In;   //!
   TBranch        *b_SMH_facScale_bin1_In;   //!
   TBranch        *b_SMH_facScale_bin10_In;   //!
   TBranch        *b_SMH_facScale_bin11_In;   //!
   TBranch        *b_SMH_facScale_bin12_In;   //!
   TBranch        *b_SMH_facScale_bin13_In;   //!
   TBranch        *b_SMH_facScale_bin2_In;   //!
   TBranch        *b_SMH_facScale_bin3_In;   //!
   TBranch        *b_SMH_facScale_bin4_In;   //!
   TBranch        *b_SMH_facScale_bin5_In;   //!
   TBranch        *b_SMH_facScale_bin6_In;   //!
   TBranch        *b_SMH_facScale_bin7_In;   //!
   TBranch        *b_SMH_facScale_bin8_In;   //!
   TBranch        *b_SMH_facScale_bin9_In;   //!
   TBranch        *b_SMH_misstag_In;   //!
   TBranch        *b_SMH_pdf0_In;   //!
   TBranch        *b_SMH_pdf1_In;   //!
   TBranch        *b_SMH_pdf10_In;   //!
   TBranch        *b_SMH_pdf11_In;   //!
   TBranch        *b_SMH_pdf12_In;   //!
   TBranch        *b_SMH_pdf13_In;   //!
   TBranch        *b_SMH_pdf14_In;   //!
   TBranch        *b_SMH_pdf15_In;   //!
   TBranch        *b_SMH_pdf16_In;   //!
   TBranch        *b_SMH_pdf17_In;   //!
   TBranch        *b_SMH_pdf18_In;   //!
   TBranch        *b_SMH_pdf19_In;   //!
   TBranch        *b_SMH_pdf2_In;   //!
   TBranch        *b_SMH_pdf20_In;   //!
   TBranch        *b_SMH_pdf21_In;   //!
   TBranch        *b_SMH_pdf22_In;   //!
   TBranch        *b_SMH_pdf23_In;   //!
   TBranch        *b_SMH_pdf24_In;   //!
   TBranch        *b_SMH_pdf25_In;   //!
   TBranch        *b_SMH_pdf26_In;   //!
   TBranch        *b_SMH_pdf27_In;   //!
   TBranch        *b_SMH_pdf28_In;   //!
   TBranch        *b_SMH_pdf29_In;   //!
   TBranch        *b_SMH_pdf3_In;   //!
   TBranch        *b_SMH_pdf30_In;   //!
   TBranch        *b_SMH_pdf31_In;   //!
   TBranch        *b_SMH_pdf32_In;   //!
   TBranch        *b_SMH_pdf33_In;   //!
   TBranch        *b_SMH_pdf34_In;   //!
   TBranch        *b_SMH_pdf35_In;   //!
   TBranch        *b_SMH_pdf36_In;   //!
   TBranch        *b_SMH_pdf37_In;   //!
   TBranch        *b_SMH_pdf38_In;   //!
   TBranch        *b_SMH_pdf39_In;   //!
   TBranch        *b_SMH_pdf4_In;   //!
   TBranch        *b_SMH_pdf40_In;   //!
   TBranch        *b_SMH_pdf41_In;   //!
   TBranch        *b_SMH_pdf42_In;   //!
   TBranch        *b_SMH_pdf43_In;   //!
   TBranch        *b_SMH_pdf44_In;   //!
   TBranch        *b_SMH_pdf45_In;   //!
   TBranch        *b_SMH_pdf46_In;   //!
   TBranch        *b_SMH_pdf47_In;   //!
   TBranch        *b_SMH_pdf48_In;   //!
   TBranch        *b_SMH_pdf49_In;   //!
   TBranch        *b_SMH_pdf5_In;   //!
   TBranch        *b_SMH_pdf50_In;   //!
   TBranch        *b_SMH_pdf51_In;   //!
   TBranch        *b_SMH_pdf52_In;   //!
   TBranch        *b_SMH_pdf53_In;   //!
   TBranch        *b_SMH_pdf54_In;   //!
   TBranch        *b_SMH_pdf55_In;   //!
   TBranch        *b_SMH_pdf56_In;   //!
   TBranch        *b_SMH_pdf57_In;   //!
   TBranch        *b_SMH_pdf58_In;   //!
   TBranch        *b_SMH_pdf59_In;   //!
   TBranch        *b_SMH_pdf6_In;   //!
   TBranch        *b_SMH_pdf7_In;   //!
   TBranch        *b_SMH_pdf8_In;   //!
   TBranch        *b_SMH_pdf9_In;   //!
   TBranch        *b_SMH_renScale_bin0_In;   //!
   TBranch        *b_SMH_renScale_bin1_In;   //!
   TBranch        *b_SMH_renScale_bin10_In;   //!
   TBranch        *b_SMH_renScale_bin11_In;   //!
   TBranch        *b_SMH_renScale_bin12_In;   //!
   TBranch        *b_SMH_renScale_bin13_In;   //!
   TBranch        *b_SMH_renScale_bin2_In;   //!
   TBranch        *b_SMH_renScale_bin3_In;   //!
   TBranch        *b_SMH_renScale_bin4_In;   //!
   TBranch        *b_SMH_renScale_bin5_In;   //!
   TBranch        *b_SMH_renScale_bin6_In;   //!
   TBranch        *b_SMH_renScale_bin7_In;   //!
   TBranch        *b_SMH_renScale_bin8_In;   //!
   TBranch        *b_SMH_renScale_bin9_In;   //!
   TBranch        *b_SigmaMoverMEfficiency_In;   //!
   TBranch        *b_Signal_ISR_In;   //!
   TBranch        *b_Signal_JES_In;   //!
   TBranch        *b_Signal_btag_In;   //!
   TBranch        *b_Signal_facRenScale_bin0_In;   //!
   TBranch        *b_Signal_facRenScale_bin1_In;   //!
   TBranch        *b_Signal_facRenScale_bin10_In;   //!
   TBranch        *b_Signal_facRenScale_bin11_In;   //!
   TBranch        *b_Signal_facRenScale_bin12_In;   //!
   TBranch        *b_Signal_facRenScale_bin13_In;   //!
   TBranch        *b_Signal_facRenScale_bin2_In;   //!
   TBranch        *b_Signal_facRenScale_bin3_In;   //!
   TBranch        *b_Signal_facRenScale_bin4_In;   //!
   TBranch        *b_Signal_facRenScale_bin5_In;   //!
   TBranch        *b_Signal_facRenScale_bin6_In;   //!
   TBranch        *b_Signal_facRenScale_bin7_In;   //!
   TBranch        *b_Signal_facRenScale_bin8_In;   //!
   TBranch        *b_Signal_facRenScale_bin9_In;   //!
   TBranch        *b_Signal_facScale_bin0_In;   //!
   TBranch        *b_Signal_facScale_bin1_In;   //!
   TBranch        *b_Signal_facScale_bin10_In;   //!
   TBranch        *b_Signal_facScale_bin11_In;   //!
   TBranch        *b_Signal_facScale_bin12_In;   //!
   TBranch        *b_Signal_facScale_bin13_In;   //!
   TBranch        *b_Signal_facScale_bin2_In;   //!
   TBranch        *b_Signal_facScale_bin3_In;   //!
   TBranch        *b_Signal_facScale_bin4_In;   //!
   TBranch        *b_Signal_facScale_bin5_In;   //!
   TBranch        *b_Signal_facScale_bin6_In;   //!
   TBranch        *b_Signal_facScale_bin7_In;   //!
   TBranch        *b_Signal_facScale_bin8_In;   //!
   TBranch        *b_Signal_facScale_bin9_In;   //!
   TBranch        *b_Signal_misstag_In;   //!
   TBranch        *b_Signal_pdf0_In;   //!
   TBranch        *b_Signal_pdf1_In;   //!
   TBranch        *b_Signal_pdf10_In;   //!
   TBranch        *b_Signal_pdf11_In;   //!
   TBranch        *b_Signal_pdf12_In;   //!
   TBranch        *b_Signal_pdf13_In;   //!
   TBranch        *b_Signal_pdf14_In;   //!
   TBranch        *b_Signal_pdf15_In;   //!
   TBranch        *b_Signal_pdf16_In;   //!
   TBranch        *b_Signal_pdf17_In;   //!
   TBranch        *b_Signal_pdf18_In;   //!
   TBranch        *b_Signal_pdf19_In;   //!
   TBranch        *b_Signal_pdf2_In;   //!
   TBranch        *b_Signal_pdf20_In;   //!
   TBranch        *b_Signal_pdf21_In;   //!
   TBranch        *b_Signal_pdf22_In;   //!
   TBranch        *b_Signal_pdf23_In;   //!
   TBranch        *b_Signal_pdf24_In;   //!
   TBranch        *b_Signal_pdf25_In;   //!
   TBranch        *b_Signal_pdf26_In;   //!
   TBranch        *b_Signal_pdf27_In;   //!
   TBranch        *b_Signal_pdf28_In;   //!
   TBranch        *b_Signal_pdf29_In;   //!
   TBranch        *b_Signal_pdf3_In;   //!
   TBranch        *b_Signal_pdf30_In;   //!
   TBranch        *b_Signal_pdf31_In;   //!
   TBranch        *b_Signal_pdf32_In;   //!
   TBranch        *b_Signal_pdf33_In;   //!
   TBranch        *b_Signal_pdf34_In;   //!
   TBranch        *b_Signal_pdf35_In;   //!
   TBranch        *b_Signal_pdf36_In;   //!
   TBranch        *b_Signal_pdf37_In;   //!
   TBranch        *b_Signal_pdf38_In;   //!
   TBranch        *b_Signal_pdf39_In;   //!
   TBranch        *b_Signal_pdf4_In;   //!
   TBranch        *b_Signal_pdf40_In;   //!
   TBranch        *b_Signal_pdf41_In;   //!
   TBranch        *b_Signal_pdf42_In;   //!
   TBranch        *b_Signal_pdf43_In;   //!
   TBranch        *b_Signal_pdf44_In;   //!
   TBranch        *b_Signal_pdf45_In;   //!
   TBranch        *b_Signal_pdf46_In;   //!
   TBranch        *b_Signal_pdf47_In;   //!
   TBranch        *b_Signal_pdf48_In;   //!
   TBranch        *b_Signal_pdf49_In;   //!
   TBranch        *b_Signal_pdf5_In;   //!
   TBranch        *b_Signal_pdf50_In;   //!
   TBranch        *b_Signal_pdf51_In;   //!
   TBranch        *b_Signal_pdf52_In;   //!
   TBranch        *b_Signal_pdf53_In;   //!
   TBranch        *b_Signal_pdf54_In;   //!
   TBranch        *b_Signal_pdf55_In;   //!
   TBranch        *b_Signal_pdf56_In;   //!
   TBranch        *b_Signal_pdf57_In;   //!
   TBranch        *b_Signal_pdf6_In;   //!
   TBranch        *b_Signal_pdf7_In;   //!
   TBranch        *b_Signal_pdf8_In;   //!
   TBranch        *b_Signal_pdf9_In;   //!
   TBranch        *b_Signal_renScale_bin0_In;   //!
   TBranch        *b_Signal_renScale_bin1_In;   //!
   TBranch        *b_Signal_renScale_bin10_In;   //!
   TBranch        *b_Signal_renScale_bin11_In;   //!
   TBranch        *b_Signal_renScale_bin12_In;   //!
   TBranch        *b_Signal_renScale_bin13_In;   //!
   TBranch        *b_Signal_renScale_bin2_In;   //!
   TBranch        *b_Signal_renScale_bin3_In;   //!
   TBranch        *b_Signal_renScale_bin4_In;   //!
   TBranch        *b_Signal_renScale_bin5_In;   //!
   TBranch        *b_Signal_renScale_bin6_In;   //!
   TBranch        *b_Signal_renScale_bin7_In;   //!
   TBranch        *b_Signal_renScale_bin8_In;   //!
   TBranch        *b_Signal_renScale_bin9_In;   //!
   TBranch        *b_mu_Global_In;   //!
   TBranch        *b_hzbb_mu_Global_In;   //!
   TBranch        *b_highpt_mu_Global_In;   //!
   TBranch        *b_lowres_mu_Global_In;   //!
   TBranch        *b_CMS_Lumi;   //!
   TBranch        *b_PdfNorm;   //!
   TBranch        *b_Photon_Trigger;   //!
   TBranch        *b_SMH_JES;   //!
   TBranch        *b_SMH_btag;   //!
   TBranch        *b_SMH_facRenScale_bin0;   //!
   TBranch        *b_SMH_facRenScale_bin1;   //!
   TBranch        *b_SMH_facRenScale_bin10;   //!
   TBranch        *b_SMH_facRenScale_bin11;   //!
   TBranch        *b_SMH_facRenScale_bin12;   //!
   TBranch        *b_SMH_facRenScale_bin13;   //!
   TBranch        *b_SMH_facRenScale_bin2;   //!
   TBranch        *b_SMH_facRenScale_bin3;   //!
   TBranch        *b_SMH_facRenScale_bin4;   //!
   TBranch        *b_SMH_facRenScale_bin5;   //!
   TBranch        *b_SMH_facRenScale_bin6;   //!
   TBranch        *b_SMH_facRenScale_bin7;   //!
   TBranch        *b_SMH_facRenScale_bin8;   //!
   TBranch        *b_SMH_facRenScale_bin9;   //!
   TBranch        *b_SMH_facScale_bin0;   //!
   TBranch        *b_SMH_facScale_bin1;   //!
   TBranch        *b_SMH_facScale_bin10;   //!
   TBranch        *b_SMH_facScale_bin11;   //!
   TBranch        *b_SMH_facScale_bin12;   //!
   TBranch        *b_SMH_facScale_bin13;   //!
   TBranch        *b_SMH_facScale_bin2;   //!
   TBranch        *b_SMH_facScale_bin3;   //!
   TBranch        *b_SMH_facScale_bin4;   //!
   TBranch        *b_SMH_facScale_bin5;   //!
   TBranch        *b_SMH_facScale_bin6;   //!
   TBranch        *b_SMH_facScale_bin7;   //!
   TBranch        *b_SMH_facScale_bin8;   //!
   TBranch        *b_SMH_facScale_bin9;   //!
   TBranch        *b_SMH_misstag;   //!
   TBranch        *b_SMH_pdf0;   //!
   TBranch        *b_SMH_pdf1;   //!
   TBranch        *b_SMH_pdf10;   //!
   TBranch        *b_SMH_pdf11;   //!
   TBranch        *b_SMH_pdf12;   //!
   TBranch        *b_SMH_pdf13;   //!
   TBranch        *b_SMH_pdf14;   //!
   TBranch        *b_SMH_pdf15;   //!
   TBranch        *b_SMH_pdf16;   //!
   TBranch        *b_SMH_pdf17;   //!
   TBranch        *b_SMH_pdf18;   //!
   TBranch        *b_SMH_pdf19;   //!
   TBranch        *b_SMH_pdf2;   //!
   TBranch        *b_SMH_pdf20;   //!
   TBranch        *b_SMH_pdf21;   //!
   TBranch        *b_SMH_pdf22;   //!
   TBranch        *b_SMH_pdf23;   //!
   TBranch        *b_SMH_pdf24;   //!
   TBranch        *b_SMH_pdf25;   //!
   TBranch        *b_SMH_pdf26;   //!
   TBranch        *b_SMH_pdf27;   //!
   TBranch        *b_SMH_pdf28;   //!
   TBranch        *b_SMH_pdf29;   //!
   TBranch        *b_SMH_pdf3;   //!
   TBranch        *b_SMH_pdf30;   //!
   TBranch        *b_SMH_pdf31;   //!
   TBranch        *b_SMH_pdf32;   //!
   TBranch        *b_SMH_pdf33;   //!
   TBranch        *b_SMH_pdf34;   //!
   TBranch        *b_SMH_pdf35;   //!
   TBranch        *b_SMH_pdf36;   //!
   TBranch        *b_SMH_pdf37;   //!
   TBranch        *b_SMH_pdf38;   //!
   TBranch        *b_SMH_pdf39;   //!
   TBranch        *b_SMH_pdf4;   //!
   TBranch        *b_SMH_pdf40;   //!
   TBranch        *b_SMH_pdf41;   //!
   TBranch        *b_SMH_pdf42;   //!
   TBranch        *b_SMH_pdf43;   //!
   TBranch        *b_SMH_pdf44;   //!
   TBranch        *b_SMH_pdf45;   //!
   TBranch        *b_SMH_pdf46;   //!
   TBranch        *b_SMH_pdf47;   //!
   TBranch        *b_SMH_pdf48;   //!
   TBranch        *b_SMH_pdf49;   //!
   TBranch        *b_SMH_pdf5;   //!
   TBranch        *b_SMH_pdf50;   //!
   TBranch        *b_SMH_pdf51;   //!
   TBranch        *b_SMH_pdf52;   //!
   TBranch        *b_SMH_pdf53;   //!
   TBranch        *b_SMH_pdf54;   //!
   TBranch        *b_SMH_pdf55;   //!
   TBranch        *b_SMH_pdf56;   //!
   TBranch        *b_SMH_pdf57;   //!
   TBranch        *b_SMH_pdf58;   //!
   TBranch        *b_SMH_pdf59;   //!
   TBranch        *b_SMH_pdf6;   //!
   TBranch        *b_SMH_pdf7;   //!
   TBranch        *b_SMH_pdf8;   //!
   TBranch        *b_SMH_pdf9;   //!
   TBranch        *b_SMH_renScale_bin0;   //!
   TBranch        *b_SMH_renScale_bin1;   //!
   TBranch        *b_SMH_renScale_bin10;   //!
   TBranch        *b_SMH_renScale_bin11;   //!
   TBranch        *b_SMH_renScale_bin12;   //!
   TBranch        *b_SMH_renScale_bin13;   //!
   TBranch        *b_SMH_renScale_bin2;   //!
   TBranch        *b_SMH_renScale_bin3;   //!
   TBranch        *b_SMH_renScale_bin4;   //!
   TBranch        *b_SMH_renScale_bin5;   //!
   TBranch        *b_SMH_renScale_bin6;   //!
   TBranch        *b_SMH_renScale_bin7;   //!
   TBranch        *b_SMH_renScale_bin8;   //!
   TBranch        *b_SMH_renScale_bin9;   //!
   TBranch        *b_SigmaMoverMEfficiency;   //!
   TBranch        *b_Signal_ISR;   //!
   TBranch        *b_Signal_JES;   //!
   TBranch        *b_Signal_btag;   //!
   TBranch        *b_Signal_facRenScale_bin0;   //!
   TBranch        *b_Signal_facRenScale_bin1;   //!
   TBranch        *b_Signal_facRenScale_bin10;   //!
   TBranch        *b_Signal_facRenScale_bin11;   //!
   TBranch        *b_Signal_facRenScale_bin12;   //!
   TBranch        *b_Signal_facRenScale_bin13;   //!
   TBranch        *b_Signal_facRenScale_bin2;   //!
   TBranch        *b_Signal_facRenScale_bin3;   //!
   TBranch        *b_Signal_facRenScale_bin4;   //!
   TBranch        *b_Signal_facRenScale_bin5;   //!
   TBranch        *b_Signal_facRenScale_bin6;   //!
   TBranch        *b_Signal_facRenScale_bin7;   //!
   TBranch        *b_Signal_facRenScale_bin8;   //!
   TBranch        *b_Signal_facRenScale_bin9;   //!
   TBranch        *b_Signal_facScale_bin0;   //!
   TBranch        *b_Signal_facScale_bin1;   //!
   TBranch        *b_Signal_facScale_bin10;   //!
   TBranch        *b_Signal_facScale_bin11;   //!
   TBranch        *b_Signal_facScale_bin12;   //!
   TBranch        *b_Signal_facScale_bin13;   //!
   TBranch        *b_Signal_facScale_bin2;   //!
   TBranch        *b_Signal_facScale_bin3;   //!
   TBranch        *b_Signal_facScale_bin4;   //!
   TBranch        *b_Signal_facScale_bin5;   //!
   TBranch        *b_Signal_facScale_bin6;   //!
   TBranch        *b_Signal_facScale_bin7;   //!
   TBranch        *b_Signal_facScale_bin8;   //!
   TBranch        *b_Signal_facScale_bin9;   //!
   TBranch        *b_Signal_misstag;   //!
   TBranch        *b_Signal_pdf0;   //!
   TBranch        *b_Signal_pdf1;   //!
   TBranch        *b_Signal_pdf10;   //!
   TBranch        *b_Signal_pdf11;   //!
   TBranch        *b_Signal_pdf12;   //!
   TBranch        *b_Signal_pdf13;   //!
   TBranch        *b_Signal_pdf14;   //!
   TBranch        *b_Signal_pdf15;   //!
   TBranch        *b_Signal_pdf16;   //!
   TBranch        *b_Signal_pdf17;   //!
   TBranch        *b_Signal_pdf18;   //!
   TBranch        *b_Signal_pdf19;   //!
   TBranch        *b_Signal_pdf2;   //!
   TBranch        *b_Signal_pdf20;   //!
   TBranch        *b_Signal_pdf21;   //!
   TBranch        *b_Signal_pdf22;   //!
   TBranch        *b_Signal_pdf23;   //!
   TBranch        *b_Signal_pdf24;   //!
   TBranch        *b_Signal_pdf25;   //!
   TBranch        *b_Signal_pdf26;   //!
   TBranch        *b_Signal_pdf27;   //!
   TBranch        *b_Signal_pdf28;   //!
   TBranch        *b_Signal_pdf29;   //!
   TBranch        *b_Signal_pdf3;   //!
   TBranch        *b_Signal_pdf30;   //!
   TBranch        *b_Signal_pdf31;   //!
   TBranch        *b_Signal_pdf32;   //!
   TBranch        *b_Signal_pdf33;   //!
   TBranch        *b_Signal_pdf34;   //!
   TBranch        *b_Signal_pdf35;   //!
   TBranch        *b_Signal_pdf36;   //!
   TBranch        *b_Signal_pdf37;   //!
   TBranch        *b_Signal_pdf38;   //!
   TBranch        *b_Signal_pdf39;   //!
   TBranch        *b_Signal_pdf4;   //!
   TBranch        *b_Signal_pdf40;   //!
   TBranch        *b_Signal_pdf41;   //!
   TBranch        *b_Signal_pdf42;   //!
   TBranch        *b_Signal_pdf43;   //!
   TBranch        *b_Signal_pdf44;   //!
   TBranch        *b_Signal_pdf45;   //!
   TBranch        *b_Signal_pdf46;   //!
   TBranch        *b_Signal_pdf47;   //!
   TBranch        *b_Signal_pdf48;   //!
   TBranch        *b_Signal_pdf49;   //!
   TBranch        *b_Signal_pdf5;   //!
   TBranch        *b_Signal_pdf50;   //!
   TBranch        *b_Signal_pdf51;   //!
   TBranch        *b_Signal_pdf52;   //!
   TBranch        *b_Signal_pdf53;   //!
   TBranch        *b_Signal_pdf54;   //!
   TBranch        *b_Signal_pdf55;   //!
   TBranch        *b_Signal_pdf56;   //!
   TBranch        *b_Signal_pdf57;   //!
   TBranch        *b_Signal_pdf6;   //!
   TBranch        *b_Signal_pdf7;   //!
   TBranch        *b_Signal_pdf8;   //!
   TBranch        *b_Signal_pdf9;   //!
   TBranch        *b_Signal_renScale_bin0;   //!
   TBranch        *b_Signal_renScale_bin1;   //!
   TBranch        *b_Signal_renScale_bin10;   //!
   TBranch        *b_Signal_renScale_bin11;   //!
   TBranch        *b_Signal_renScale_bin12;   //!
   TBranch        *b_Signal_renScale_bin13;   //!
   TBranch        *b_Signal_renScale_bin2;   //!
   TBranch        *b_Signal_renScale_bin3;   //!
   TBranch        *b_Signal_renScale_bin4;   //!
   TBranch        *b_Signal_renScale_bin5;   //!
   TBranch        *b_Signal_renScale_bin6;   //!
   TBranch        *b_Signal_renScale_bin7;   //!
   TBranch        *b_Signal_renScale_bin8;   //!
   TBranch        *b_Signal_renScale_bin9;   //!
   TBranch        *b_mu_Global;   //!
   TBranch        *b_hzbb_mu_Global;   //!
   TBranch        *b_highpt_mu_Global;   //!
   TBranch        *b_lowres_mu_Global;   //!
   TBranch        *b_n_exp_final_binch10_proc_Bkg;   //!
   TBranch        *b_n_exp_final_binch10_proc_SMH;   //!
   TBranch        *b_n_exp_final_binch10_proc_signal;   //!
   TBranch        *b_n_exp_final_binch11_proc_Bkg;   //!
   TBranch        *b_n_exp_final_binch11_proc_SMH;   //!
   TBranch        *b_n_exp_final_binch11_proc_signal;   //!
   TBranch        *b_n_exp_final_binch12_proc_Bkg;   //!
   TBranch        *b_n_exp_final_binch12_proc_SMH;   //!
   TBranch        *b_n_exp_final_binch12_proc_signal;   //!
   TBranch        *b_n_exp_final_binch13_proc_Bkg;   //!
   TBranch        *b_n_exp_final_binch13_proc_SMH;   //!
   TBranch        *b_n_exp_final_binch13_proc_signal;   //!
   TBranch        *b_n_exp_final_binch14_highResBin9_proc_Bkg;   //!
   TBranch        *b_n_exp_final_binch14_highResBin9_proc_SMH;   //!
   TBranch        *b_n_exp_final_binch14_highResBin9_proc_signal;   //!
   TBranch        *b_n_exp_final_binch14_lowResBin9_proc_Bkg;   //!
   TBranch        *b_n_exp_final_binch14_lowResBin9_proc_SMH;   //!
   TBranch        *b_n_exp_final_binch14_lowResBin9_proc_signal;   //!
   TBranch        *b_n_exp_final_binch1_proc_Bkg;   //!
   TBranch        *b_n_exp_final_binch1_proc_SMH;   //!
   TBranch        *b_n_exp_final_binch1_proc_signal;   //!
   TBranch        *b_n_exp_final_binch2_proc_Bkg;   //!
   TBranch        *b_n_exp_final_binch2_proc_SMH;   //!
   TBranch        *b_n_exp_final_binch2_proc_signal;   //!
   TBranch        *b_n_exp_final_binch3_highResBin10_proc_Bkg;   //!
   TBranch        *b_n_exp_final_binch3_highResBin10_proc_SMH;   //!
   TBranch        *b_n_exp_final_binch3_highResBin10_proc_signal;   //!
   TBranch        *b_n_exp_final_binch3_lowResBin10_proc_Bkg;   //!
   TBranch        *b_n_exp_final_binch3_lowResBin10_proc_SMH;   //!
   TBranch        *b_n_exp_final_binch3_lowResBin10_proc_signal;   //!
   TBranch        *b_n_exp_final_binch4_highResBin11_proc_Bkg;   //!
   TBranch        *b_n_exp_final_binch4_highResBin11_proc_SMH;   //!
   TBranch        *b_n_exp_final_binch4_highResBin11_proc_signal;   //!
   TBranch        *b_n_exp_final_binch4_lowResBin11_proc_Bkg;   //!
   TBranch        *b_n_exp_final_binch4_lowResBin11_proc_SMH;   //!
   TBranch        *b_n_exp_final_binch4_lowResBin11_proc_signal;   //!
   TBranch        *b_n_exp_final_binch5_highResBin12_proc_Bkg;   //!
   TBranch        *b_n_exp_final_binch5_highResBin12_proc_SMH;   //!
   TBranch        *b_n_exp_final_binch5_highResBin12_proc_signal;   //!
   TBranch        *b_n_exp_final_binch5_lowResBin12_proc_Bkg;   //!
   TBranch        *b_n_exp_final_binch5_lowResBin12_proc_SMH;   //!
   TBranch        *b_n_exp_final_binch5_lowResBin12_proc_signal;   //!
   TBranch        *b_n_exp_final_binch6_highResBin13_proc_Bkg;   //!
   TBranch        *b_n_exp_final_binch6_highResBin13_proc_SMH;   //!
   TBranch        *b_n_exp_final_binch6_highResBin13_proc_signal;   //!
   TBranch        *b_n_exp_final_binch6_lowResBin13_proc_Bkg;   //!
   TBranch        *b_n_exp_final_binch6_lowResBin13_proc_SMH;   //!
   TBranch        *b_n_exp_final_binch6_lowResBin13_proc_signal;   //!
   TBranch        *b_n_exp_final_binch7_proc_Bkg;   //!
   TBranch        *b_n_exp_final_binch7_proc_SMH;   //!
   TBranch        *b_n_exp_final_binch7_proc_signal;   //!
   TBranch        *b_n_exp_final_binch8_proc_Bkg;   //!
   TBranch        *b_n_exp_final_binch8_proc_SMH;   //!
   TBranch        *b_n_exp_final_binch8_proc_signal;   //!
   TBranch        *b_n_exp_final_binch9_proc_Bkg;   //!
   TBranch        *b_n_exp_final_binch9_proc_SMH;   //!
   TBranch        *b_n_exp_final_binch9_proc_signal;   //!

   tree_fit_sb(TTree *tree=0);
   virtual ~tree_fit_sb();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
  virtual void SetSystematics();
  virtual void GetSystematics();
  double GetIntegral( TString pdfName, TString varName );
};

#endif

#ifdef tree_fit_sb_cxx
tree_fit_sb::tree_fit_sb(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("mlfit_1ktoys_toy_all_toys.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("mlfit_1ktoys_toy_all_toys.root");
      }
      f->GetObject("tree_fit_sb",tree);

   }
   Init(tree);
   
   TFile* fws = new TFile("scripts/workspace_global_fit.root");
   ws = (RooWorkspace*)fws->Get("w");
   TFile* fwshgg = new TFile("scripts/HggRazorWorkspace_bin9.root");
   ws_hgg = (RooWorkspace*)fwshgg->Get("combineWS");
}

tree_fit_sb::~tree_fit_sb()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t tree_fit_sb::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t tree_fit_sb::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void tree_fit_sb::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("fit_status", &fit_status, &b_fit_status);
   fChain->SetBranchAddress("mu", &mu, &b_mu);
   fChain->SetBranchAddress("muErr", &muErr, &b_muErr);
   fChain->SetBranchAddress("muLoErr", &muLoErr, &b_muLoErr);
   fChain->SetBranchAddress("muHiErr", &muHiErr, &b_muHiErr);
   fChain->SetBranchAddress("numbadnll", &numbadnll, &b_numbadnll);
   fChain->SetBranchAddress("nll_min", &nll_min, &b_nll_min);
   fChain->SetBranchAddress("nll_nll0", &nll_nll0, &b_nll_nll0);
   fChain->SetBranchAddress("CMS_Lumi_In", &CMS_Lumi_In, &b_CMS_Lumi_In);
   fChain->SetBranchAddress("PdfNorm_In", &PdfNorm_In, &b_PdfNorm_In);
   fChain->SetBranchAddress("Photon_Trigger_In", &Photon_Trigger_In, &b_Photon_Trigger_In);
   fChain->SetBranchAddress("SMH_JES_In", &SMH_JES_In, &b_SMH_JES_In);
   fChain->SetBranchAddress("SMH_btag_In", &SMH_btag_In, &b_SMH_btag_In);
   fChain->SetBranchAddress("SMH_facRenScale_bin0_In", &SMH_facRenScale_bin0_In, &b_SMH_facRenScale_bin0_In);
   fChain->SetBranchAddress("SMH_facRenScale_bin1_In", &SMH_facRenScale_bin1_In, &b_SMH_facRenScale_bin1_In);
   fChain->SetBranchAddress("SMH_facRenScale_bin10_In", &SMH_facRenScale_bin10_In, &b_SMH_facRenScale_bin10_In);
   fChain->SetBranchAddress("SMH_facRenScale_bin11_In", &SMH_facRenScale_bin11_In, &b_SMH_facRenScale_bin11_In);
   fChain->SetBranchAddress("SMH_facRenScale_bin12_In", &SMH_facRenScale_bin12_In, &b_SMH_facRenScale_bin12_In);
   fChain->SetBranchAddress("SMH_facRenScale_bin13_In", &SMH_facRenScale_bin13_In, &b_SMH_facRenScale_bin13_In);
   fChain->SetBranchAddress("SMH_facRenScale_bin2_In", &SMH_facRenScale_bin2_In, &b_SMH_facRenScale_bin2_In);
   fChain->SetBranchAddress("SMH_facRenScale_bin3_In", &SMH_facRenScale_bin3_In, &b_SMH_facRenScale_bin3_In);
   fChain->SetBranchAddress("SMH_facRenScale_bin4_In", &SMH_facRenScale_bin4_In, &b_SMH_facRenScale_bin4_In);
   fChain->SetBranchAddress("SMH_facRenScale_bin5_In", &SMH_facRenScale_bin5_In, &b_SMH_facRenScale_bin5_In);
   fChain->SetBranchAddress("SMH_facRenScale_bin6_In", &SMH_facRenScale_bin6_In, &b_SMH_facRenScale_bin6_In);
   fChain->SetBranchAddress("SMH_facRenScale_bin7_In", &SMH_facRenScale_bin7_In, &b_SMH_facRenScale_bin7_In);
   fChain->SetBranchAddress("SMH_facRenScale_bin8_In", &SMH_facRenScale_bin8_In, &b_SMH_facRenScale_bin8_In);
   fChain->SetBranchAddress("SMH_facRenScale_bin9_In", &SMH_facRenScale_bin9_In, &b_SMH_facRenScale_bin9_In);
   fChain->SetBranchAddress("SMH_facScale_bin0_In", &SMH_facScale_bin0_In, &b_SMH_facScale_bin0_In);
   fChain->SetBranchAddress("SMH_facScale_bin1_In", &SMH_facScale_bin1_In, &b_SMH_facScale_bin1_In);
   fChain->SetBranchAddress("SMH_facScale_bin10_In", &SMH_facScale_bin10_In, &b_SMH_facScale_bin10_In);
   fChain->SetBranchAddress("SMH_facScale_bin11_In", &SMH_facScale_bin11_In, &b_SMH_facScale_bin11_In);
   fChain->SetBranchAddress("SMH_facScale_bin12_In", &SMH_facScale_bin12_In, &b_SMH_facScale_bin12_In);
   fChain->SetBranchAddress("SMH_facScale_bin13_In", &SMH_facScale_bin13_In, &b_SMH_facScale_bin13_In);
   fChain->SetBranchAddress("SMH_facScale_bin2_In", &SMH_facScale_bin2_In, &b_SMH_facScale_bin2_In);
   fChain->SetBranchAddress("SMH_facScale_bin3_In", &SMH_facScale_bin3_In, &b_SMH_facScale_bin3_In);
   fChain->SetBranchAddress("SMH_facScale_bin4_In", &SMH_facScale_bin4_In, &b_SMH_facScale_bin4_In);
   fChain->SetBranchAddress("SMH_facScale_bin5_In", &SMH_facScale_bin5_In, &b_SMH_facScale_bin5_In);
   fChain->SetBranchAddress("SMH_facScale_bin6_In", &SMH_facScale_bin6_In, &b_SMH_facScale_bin6_In);
   fChain->SetBranchAddress("SMH_facScale_bin7_In", &SMH_facScale_bin7_In, &b_SMH_facScale_bin7_In);
   fChain->SetBranchAddress("SMH_facScale_bin8_In", &SMH_facScale_bin8_In, &b_SMH_facScale_bin8_In);
   fChain->SetBranchAddress("SMH_facScale_bin9_In", &SMH_facScale_bin9_In, &b_SMH_facScale_bin9_In);
   fChain->SetBranchAddress("SMH_misstag_In", &SMH_misstag_In, &b_SMH_misstag_In);
   fChain->SetBranchAddress("SMH_pdf0_In", &SMH_pdf0_In, &b_SMH_pdf0_In);
   fChain->SetBranchAddress("SMH_pdf1_In", &SMH_pdf1_In, &b_SMH_pdf1_In);
   fChain->SetBranchAddress("SMH_pdf10_In", &SMH_pdf10_In, &b_SMH_pdf10_In);
   fChain->SetBranchAddress("SMH_pdf11_In", &SMH_pdf11_In, &b_SMH_pdf11_In);
   fChain->SetBranchAddress("SMH_pdf12_In", &SMH_pdf12_In, &b_SMH_pdf12_In);
   fChain->SetBranchAddress("SMH_pdf13_In", &SMH_pdf13_In, &b_SMH_pdf13_In);
   fChain->SetBranchAddress("SMH_pdf14_In", &SMH_pdf14_In, &b_SMH_pdf14_In);
   fChain->SetBranchAddress("SMH_pdf15_In", &SMH_pdf15_In, &b_SMH_pdf15_In);
   fChain->SetBranchAddress("SMH_pdf16_In", &SMH_pdf16_In, &b_SMH_pdf16_In);
   fChain->SetBranchAddress("SMH_pdf17_In", &SMH_pdf17_In, &b_SMH_pdf17_In);
   fChain->SetBranchAddress("SMH_pdf18_In", &SMH_pdf18_In, &b_SMH_pdf18_In);
   fChain->SetBranchAddress("SMH_pdf19_In", &SMH_pdf19_In, &b_SMH_pdf19_In);
   fChain->SetBranchAddress("SMH_pdf2_In", &SMH_pdf2_In, &b_SMH_pdf2_In);
   fChain->SetBranchAddress("SMH_pdf20_In", &SMH_pdf20_In, &b_SMH_pdf20_In);
   fChain->SetBranchAddress("SMH_pdf21_In", &SMH_pdf21_In, &b_SMH_pdf21_In);
   fChain->SetBranchAddress("SMH_pdf22_In", &SMH_pdf22_In, &b_SMH_pdf22_In);
   fChain->SetBranchAddress("SMH_pdf23_In", &SMH_pdf23_In, &b_SMH_pdf23_In);
   fChain->SetBranchAddress("SMH_pdf24_In", &SMH_pdf24_In, &b_SMH_pdf24_In);
   fChain->SetBranchAddress("SMH_pdf25_In", &SMH_pdf25_In, &b_SMH_pdf25_In);
   fChain->SetBranchAddress("SMH_pdf26_In", &SMH_pdf26_In, &b_SMH_pdf26_In);
   fChain->SetBranchAddress("SMH_pdf27_In", &SMH_pdf27_In, &b_SMH_pdf27_In);
   fChain->SetBranchAddress("SMH_pdf28_In", &SMH_pdf28_In, &b_SMH_pdf28_In);
   fChain->SetBranchAddress("SMH_pdf29_In", &SMH_pdf29_In, &b_SMH_pdf29_In);
   fChain->SetBranchAddress("SMH_pdf3_In", &SMH_pdf3_In, &b_SMH_pdf3_In);
   fChain->SetBranchAddress("SMH_pdf30_In", &SMH_pdf30_In, &b_SMH_pdf30_In);
   fChain->SetBranchAddress("SMH_pdf31_In", &SMH_pdf31_In, &b_SMH_pdf31_In);
   fChain->SetBranchAddress("SMH_pdf32_In", &SMH_pdf32_In, &b_SMH_pdf32_In);
   fChain->SetBranchAddress("SMH_pdf33_In", &SMH_pdf33_In, &b_SMH_pdf33_In);
   fChain->SetBranchAddress("SMH_pdf34_In", &SMH_pdf34_In, &b_SMH_pdf34_In);
   fChain->SetBranchAddress("SMH_pdf35_In", &SMH_pdf35_In, &b_SMH_pdf35_In);
   fChain->SetBranchAddress("SMH_pdf36_In", &SMH_pdf36_In, &b_SMH_pdf36_In);
   fChain->SetBranchAddress("SMH_pdf37_In", &SMH_pdf37_In, &b_SMH_pdf37_In);
   fChain->SetBranchAddress("SMH_pdf38_In", &SMH_pdf38_In, &b_SMH_pdf38_In);
   fChain->SetBranchAddress("SMH_pdf39_In", &SMH_pdf39_In, &b_SMH_pdf39_In);
   fChain->SetBranchAddress("SMH_pdf4_In", &SMH_pdf4_In, &b_SMH_pdf4_In);
   fChain->SetBranchAddress("SMH_pdf40_In", &SMH_pdf40_In, &b_SMH_pdf40_In);
   fChain->SetBranchAddress("SMH_pdf41_In", &SMH_pdf41_In, &b_SMH_pdf41_In);
   fChain->SetBranchAddress("SMH_pdf42_In", &SMH_pdf42_In, &b_SMH_pdf42_In);
   fChain->SetBranchAddress("SMH_pdf43_In", &SMH_pdf43_In, &b_SMH_pdf43_In);
   fChain->SetBranchAddress("SMH_pdf44_In", &SMH_pdf44_In, &b_SMH_pdf44_In);
   fChain->SetBranchAddress("SMH_pdf45_In", &SMH_pdf45_In, &b_SMH_pdf45_In);
   fChain->SetBranchAddress("SMH_pdf46_In", &SMH_pdf46_In, &b_SMH_pdf46_In);
   fChain->SetBranchAddress("SMH_pdf47_In", &SMH_pdf47_In, &b_SMH_pdf47_In);
   fChain->SetBranchAddress("SMH_pdf48_In", &SMH_pdf48_In, &b_SMH_pdf48_In);
   fChain->SetBranchAddress("SMH_pdf49_In", &SMH_pdf49_In, &b_SMH_pdf49_In);
   fChain->SetBranchAddress("SMH_pdf5_In", &SMH_pdf5_In, &b_SMH_pdf5_In);
   fChain->SetBranchAddress("SMH_pdf50_In", &SMH_pdf50_In, &b_SMH_pdf50_In);
   fChain->SetBranchAddress("SMH_pdf51_In", &SMH_pdf51_In, &b_SMH_pdf51_In);
   fChain->SetBranchAddress("SMH_pdf52_In", &SMH_pdf52_In, &b_SMH_pdf52_In);
   fChain->SetBranchAddress("SMH_pdf53_In", &SMH_pdf53_In, &b_SMH_pdf53_In);
   fChain->SetBranchAddress("SMH_pdf54_In", &SMH_pdf54_In, &b_SMH_pdf54_In);
   fChain->SetBranchAddress("SMH_pdf55_In", &SMH_pdf55_In, &b_SMH_pdf55_In);
   fChain->SetBranchAddress("SMH_pdf56_In", &SMH_pdf56_In, &b_SMH_pdf56_In);
   fChain->SetBranchAddress("SMH_pdf57_In", &SMH_pdf57_In, &b_SMH_pdf57_In);
   fChain->SetBranchAddress("SMH_pdf58_In", &SMH_pdf58_In, &b_SMH_pdf58_In);
   fChain->SetBranchAddress("SMH_pdf59_In", &SMH_pdf59_In, &b_SMH_pdf59_In);
   fChain->SetBranchAddress("SMH_pdf6_In", &SMH_pdf6_In, &b_SMH_pdf6_In);
   fChain->SetBranchAddress("SMH_pdf7_In", &SMH_pdf7_In, &b_SMH_pdf7_In);
   fChain->SetBranchAddress("SMH_pdf8_In", &SMH_pdf8_In, &b_SMH_pdf8_In);
   fChain->SetBranchAddress("SMH_pdf9_In", &SMH_pdf9_In, &b_SMH_pdf9_In);
   fChain->SetBranchAddress("SMH_renScale_bin0_In", &SMH_renScale_bin0_In, &b_SMH_renScale_bin0_In);
   fChain->SetBranchAddress("SMH_renScale_bin1_In", &SMH_renScale_bin1_In, &b_SMH_renScale_bin1_In);
   fChain->SetBranchAddress("SMH_renScale_bin10_In", &SMH_renScale_bin10_In, &b_SMH_renScale_bin10_In);
   fChain->SetBranchAddress("SMH_renScale_bin11_In", &SMH_renScale_bin11_In, &b_SMH_renScale_bin11_In);
   fChain->SetBranchAddress("SMH_renScale_bin12_In", &SMH_renScale_bin12_In, &b_SMH_renScale_bin12_In);
   fChain->SetBranchAddress("SMH_renScale_bin13_In", &SMH_renScale_bin13_In, &b_SMH_renScale_bin13_In);
   fChain->SetBranchAddress("SMH_renScale_bin2_In", &SMH_renScale_bin2_In, &b_SMH_renScale_bin2_In);
   fChain->SetBranchAddress("SMH_renScale_bin3_In", &SMH_renScale_bin3_In, &b_SMH_renScale_bin3_In);
   fChain->SetBranchAddress("SMH_renScale_bin4_In", &SMH_renScale_bin4_In, &b_SMH_renScale_bin4_In);
   fChain->SetBranchAddress("SMH_renScale_bin5_In", &SMH_renScale_bin5_In, &b_SMH_renScale_bin5_In);
   fChain->SetBranchAddress("SMH_renScale_bin6_In", &SMH_renScale_bin6_In, &b_SMH_renScale_bin6_In);
   fChain->SetBranchAddress("SMH_renScale_bin7_In", &SMH_renScale_bin7_In, &b_SMH_renScale_bin7_In);
   fChain->SetBranchAddress("SMH_renScale_bin8_In", &SMH_renScale_bin8_In, &b_SMH_renScale_bin8_In);
   fChain->SetBranchAddress("SMH_renScale_bin9_In", &SMH_renScale_bin9_In, &b_SMH_renScale_bin9_In);
   fChain->SetBranchAddress("SigmaMoverMEfficiency_In", &SigmaMoverMEfficiency_In, &b_SigmaMoverMEfficiency_In);
   fChain->SetBranchAddress("Signal_ISR_In", &Signal_ISR_In, &b_Signal_ISR_In);
   fChain->SetBranchAddress("Signal_JES_In", &Signal_JES_In, &b_Signal_JES_In);
   fChain->SetBranchAddress("Signal_btag_In", &Signal_btag_In, &b_Signal_btag_In);
   fChain->SetBranchAddress("Signal_facRenScale_bin0_In", &Signal_facRenScale_bin0_In, &b_Signal_facRenScale_bin0_In);
   fChain->SetBranchAddress("Signal_facRenScale_bin1_In", &Signal_facRenScale_bin1_In, &b_Signal_facRenScale_bin1_In);
   fChain->SetBranchAddress("Signal_facRenScale_bin10_In", &Signal_facRenScale_bin10_In, &b_Signal_facRenScale_bin10_In);
   fChain->SetBranchAddress("Signal_facRenScale_bin11_In", &Signal_facRenScale_bin11_In, &b_Signal_facRenScale_bin11_In);
   fChain->SetBranchAddress("Signal_facRenScale_bin12_In", &Signal_facRenScale_bin12_In, &b_Signal_facRenScale_bin12_In);
   fChain->SetBranchAddress("Signal_facRenScale_bin13_In", &Signal_facRenScale_bin13_In, &b_Signal_facRenScale_bin13_In);
   fChain->SetBranchAddress("Signal_facRenScale_bin2_In", &Signal_facRenScale_bin2_In, &b_Signal_facRenScale_bin2_In);
   fChain->SetBranchAddress("Signal_facRenScale_bin3_In", &Signal_facRenScale_bin3_In, &b_Signal_facRenScale_bin3_In);
   fChain->SetBranchAddress("Signal_facRenScale_bin4_In", &Signal_facRenScale_bin4_In, &b_Signal_facRenScale_bin4_In);
   fChain->SetBranchAddress("Signal_facRenScale_bin5_In", &Signal_facRenScale_bin5_In, &b_Signal_facRenScale_bin5_In);
   fChain->SetBranchAddress("Signal_facRenScale_bin6_In", &Signal_facRenScale_bin6_In, &b_Signal_facRenScale_bin6_In);
   fChain->SetBranchAddress("Signal_facRenScale_bin7_In", &Signal_facRenScale_bin7_In, &b_Signal_facRenScale_bin7_In);
   fChain->SetBranchAddress("Signal_facRenScale_bin8_In", &Signal_facRenScale_bin8_In, &b_Signal_facRenScale_bin8_In);
   fChain->SetBranchAddress("Signal_facRenScale_bin9_In", &Signal_facRenScale_bin9_In, &b_Signal_facRenScale_bin9_In);
   fChain->SetBranchAddress("Signal_facScale_bin0_In", &Signal_facScale_bin0_In, &b_Signal_facScale_bin0_In);
   fChain->SetBranchAddress("Signal_facScale_bin1_In", &Signal_facScale_bin1_In, &b_Signal_facScale_bin1_In);
   fChain->SetBranchAddress("Signal_facScale_bin10_In", &Signal_facScale_bin10_In, &b_Signal_facScale_bin10_In);
   fChain->SetBranchAddress("Signal_facScale_bin11_In", &Signal_facScale_bin11_In, &b_Signal_facScale_bin11_In);
   fChain->SetBranchAddress("Signal_facScale_bin12_In", &Signal_facScale_bin12_In, &b_Signal_facScale_bin12_In);
   fChain->SetBranchAddress("Signal_facScale_bin13_In", &Signal_facScale_bin13_In, &b_Signal_facScale_bin13_In);
   fChain->SetBranchAddress("Signal_facScale_bin2_In", &Signal_facScale_bin2_In, &b_Signal_facScale_bin2_In);
   fChain->SetBranchAddress("Signal_facScale_bin3_In", &Signal_facScale_bin3_In, &b_Signal_facScale_bin3_In);
   fChain->SetBranchAddress("Signal_facScale_bin4_In", &Signal_facScale_bin4_In, &b_Signal_facScale_bin4_In);
   fChain->SetBranchAddress("Signal_facScale_bin5_In", &Signal_facScale_bin5_In, &b_Signal_facScale_bin5_In);
   fChain->SetBranchAddress("Signal_facScale_bin6_In", &Signal_facScale_bin6_In, &b_Signal_facScale_bin6_In);
   fChain->SetBranchAddress("Signal_facScale_bin7_In", &Signal_facScale_bin7_In, &b_Signal_facScale_bin7_In);
   fChain->SetBranchAddress("Signal_facScale_bin8_In", &Signal_facScale_bin8_In, &b_Signal_facScale_bin8_In);
   fChain->SetBranchAddress("Signal_facScale_bin9_In", &Signal_facScale_bin9_In, &b_Signal_facScale_bin9_In);
   fChain->SetBranchAddress("Signal_misstag_In", &Signal_misstag_In, &b_Signal_misstag_In);
   fChain->SetBranchAddress("Signal_pdf0_In", &Signal_pdf0_In, &b_Signal_pdf0_In);
   fChain->SetBranchAddress("Signal_pdf1_In", &Signal_pdf1_In, &b_Signal_pdf1_In);
   fChain->SetBranchAddress("Signal_pdf10_In", &Signal_pdf10_In, &b_Signal_pdf10_In);
   fChain->SetBranchAddress("Signal_pdf11_In", &Signal_pdf11_In, &b_Signal_pdf11_In);
   fChain->SetBranchAddress("Signal_pdf12_In", &Signal_pdf12_In, &b_Signal_pdf12_In);
   fChain->SetBranchAddress("Signal_pdf13_In", &Signal_pdf13_In, &b_Signal_pdf13_In);
   fChain->SetBranchAddress("Signal_pdf14_In", &Signal_pdf14_In, &b_Signal_pdf14_In);
   fChain->SetBranchAddress("Signal_pdf15_In", &Signal_pdf15_In, &b_Signal_pdf15_In);
   fChain->SetBranchAddress("Signal_pdf16_In", &Signal_pdf16_In, &b_Signal_pdf16_In);
   fChain->SetBranchAddress("Signal_pdf17_In", &Signal_pdf17_In, &b_Signal_pdf17_In);
   fChain->SetBranchAddress("Signal_pdf18_In", &Signal_pdf18_In, &b_Signal_pdf18_In);
   fChain->SetBranchAddress("Signal_pdf19_In", &Signal_pdf19_In, &b_Signal_pdf19_In);
   fChain->SetBranchAddress("Signal_pdf2_In", &Signal_pdf2_In, &b_Signal_pdf2_In);
   fChain->SetBranchAddress("Signal_pdf20_In", &Signal_pdf20_In, &b_Signal_pdf20_In);
   fChain->SetBranchAddress("Signal_pdf21_In", &Signal_pdf21_In, &b_Signal_pdf21_In);
   fChain->SetBranchAddress("Signal_pdf22_In", &Signal_pdf22_In, &b_Signal_pdf22_In);
   fChain->SetBranchAddress("Signal_pdf23_In", &Signal_pdf23_In, &b_Signal_pdf23_In);
   fChain->SetBranchAddress("Signal_pdf24_In", &Signal_pdf24_In, &b_Signal_pdf24_In);
   fChain->SetBranchAddress("Signal_pdf25_In", &Signal_pdf25_In, &b_Signal_pdf25_In);
   fChain->SetBranchAddress("Signal_pdf26_In", &Signal_pdf26_In, &b_Signal_pdf26_In);
   fChain->SetBranchAddress("Signal_pdf27_In", &Signal_pdf27_In, &b_Signal_pdf27_In);
   fChain->SetBranchAddress("Signal_pdf28_In", &Signal_pdf28_In, &b_Signal_pdf28_In);
   fChain->SetBranchAddress("Signal_pdf29_In", &Signal_pdf29_In, &b_Signal_pdf29_In);
   fChain->SetBranchAddress("Signal_pdf3_In", &Signal_pdf3_In, &b_Signal_pdf3_In);
   fChain->SetBranchAddress("Signal_pdf30_In", &Signal_pdf30_In, &b_Signal_pdf30_In);
   fChain->SetBranchAddress("Signal_pdf31_In", &Signal_pdf31_In, &b_Signal_pdf31_In);
   fChain->SetBranchAddress("Signal_pdf32_In", &Signal_pdf32_In, &b_Signal_pdf32_In);
   fChain->SetBranchAddress("Signal_pdf33_In", &Signal_pdf33_In, &b_Signal_pdf33_In);
   fChain->SetBranchAddress("Signal_pdf34_In", &Signal_pdf34_In, &b_Signal_pdf34_In);
   fChain->SetBranchAddress("Signal_pdf35_In", &Signal_pdf35_In, &b_Signal_pdf35_In);
   fChain->SetBranchAddress("Signal_pdf36_In", &Signal_pdf36_In, &b_Signal_pdf36_In);
   fChain->SetBranchAddress("Signal_pdf37_In", &Signal_pdf37_In, &b_Signal_pdf37_In);
   fChain->SetBranchAddress("Signal_pdf38_In", &Signal_pdf38_In, &b_Signal_pdf38_In);
   fChain->SetBranchAddress("Signal_pdf39_In", &Signal_pdf39_In, &b_Signal_pdf39_In);
   fChain->SetBranchAddress("Signal_pdf4_In", &Signal_pdf4_In, &b_Signal_pdf4_In);
   fChain->SetBranchAddress("Signal_pdf40_In", &Signal_pdf40_In, &b_Signal_pdf40_In);
   fChain->SetBranchAddress("Signal_pdf41_In", &Signal_pdf41_In, &b_Signal_pdf41_In);
   fChain->SetBranchAddress("Signal_pdf42_In", &Signal_pdf42_In, &b_Signal_pdf42_In);
   fChain->SetBranchAddress("Signal_pdf43_In", &Signal_pdf43_In, &b_Signal_pdf43_In);
   fChain->SetBranchAddress("Signal_pdf44_In", &Signal_pdf44_In, &b_Signal_pdf44_In);
   fChain->SetBranchAddress("Signal_pdf45_In", &Signal_pdf45_In, &b_Signal_pdf45_In);
   fChain->SetBranchAddress("Signal_pdf46_In", &Signal_pdf46_In, &b_Signal_pdf46_In);
   fChain->SetBranchAddress("Signal_pdf47_In", &Signal_pdf47_In, &b_Signal_pdf47_In);
   fChain->SetBranchAddress("Signal_pdf48_In", &Signal_pdf48_In, &b_Signal_pdf48_In);
   fChain->SetBranchAddress("Signal_pdf49_In", &Signal_pdf49_In, &b_Signal_pdf49_In);
   fChain->SetBranchAddress("Signal_pdf5_In", &Signal_pdf5_In, &b_Signal_pdf5_In);
   fChain->SetBranchAddress("Signal_pdf50_In", &Signal_pdf50_In, &b_Signal_pdf50_In);
   fChain->SetBranchAddress("Signal_pdf51_In", &Signal_pdf51_In, &b_Signal_pdf51_In);
   fChain->SetBranchAddress("Signal_pdf52_In", &Signal_pdf52_In, &b_Signal_pdf52_In);
   fChain->SetBranchAddress("Signal_pdf53_In", &Signal_pdf53_In, &b_Signal_pdf53_In);
   fChain->SetBranchAddress("Signal_pdf54_In", &Signal_pdf54_In, &b_Signal_pdf54_In);
   fChain->SetBranchAddress("Signal_pdf55_In", &Signal_pdf55_In, &b_Signal_pdf55_In);
   fChain->SetBranchAddress("Signal_pdf56_In", &Signal_pdf56_In, &b_Signal_pdf56_In);
   fChain->SetBranchAddress("Signal_pdf57_In", &Signal_pdf57_In, &b_Signal_pdf57_In);
   fChain->SetBranchAddress("Signal_pdf6_In", &Signal_pdf6_In, &b_Signal_pdf6_In);
   fChain->SetBranchAddress("Signal_pdf7_In", &Signal_pdf7_In, &b_Signal_pdf7_In);
   fChain->SetBranchAddress("Signal_pdf8_In", &Signal_pdf8_In, &b_Signal_pdf8_In);
   fChain->SetBranchAddress("Signal_pdf9_In", &Signal_pdf9_In, &b_Signal_pdf9_In);
   fChain->SetBranchAddress("Signal_renScale_bin0_In", &Signal_renScale_bin0_In, &b_Signal_renScale_bin0_In);
   fChain->SetBranchAddress("Signal_renScale_bin1_In", &Signal_renScale_bin1_In, &b_Signal_renScale_bin1_In);
   fChain->SetBranchAddress("Signal_renScale_bin10_In", &Signal_renScale_bin10_In, &b_Signal_renScale_bin10_In);
   fChain->SetBranchAddress("Signal_renScale_bin11_In", &Signal_renScale_bin11_In, &b_Signal_renScale_bin11_In);
   fChain->SetBranchAddress("Signal_renScale_bin12_In", &Signal_renScale_bin12_In, &b_Signal_renScale_bin12_In);
   fChain->SetBranchAddress("Signal_renScale_bin13_In", &Signal_renScale_bin13_In, &b_Signal_renScale_bin13_In);
   fChain->SetBranchAddress("Signal_renScale_bin2_In", &Signal_renScale_bin2_In, &b_Signal_renScale_bin2_In);
   fChain->SetBranchAddress("Signal_renScale_bin3_In", &Signal_renScale_bin3_In, &b_Signal_renScale_bin3_In);
   fChain->SetBranchAddress("Signal_renScale_bin4_In", &Signal_renScale_bin4_In, &b_Signal_renScale_bin4_In);
   fChain->SetBranchAddress("Signal_renScale_bin5_In", &Signal_renScale_bin5_In, &b_Signal_renScale_bin5_In);
   fChain->SetBranchAddress("Signal_renScale_bin6_In", &Signal_renScale_bin6_In, &b_Signal_renScale_bin6_In);
   fChain->SetBranchAddress("Signal_renScale_bin7_In", &Signal_renScale_bin7_In, &b_Signal_renScale_bin7_In);
   fChain->SetBranchAddress("Signal_renScale_bin8_In", &Signal_renScale_bin8_In, &b_Signal_renScale_bin8_In);
   fChain->SetBranchAddress("Signal_renScale_bin9_In", &Signal_renScale_bin9_In, &b_Signal_renScale_bin9_In);
   fChain->SetBranchAddress("mu_Global_In", &mu_Global_In, &b_mu_Global_In);
   fChain->SetBranchAddress("hzbb_mu_Global_In", &hzbb_mu_Global_In, &b_hzbb_mu_Global_In);
   fChain->SetBranchAddress("highpt_mu_Global_In", &highpt_mu_Global_In, &b_highpt_mu_Global_In);
   fChain->SetBranchAddress("lowres_mu_Global_In", &lowres_mu_Global_In, &b_lowres_mu_Global_In);
   fChain->SetBranchAddress("CMS_Lumi", &CMS_Lumi, &b_CMS_Lumi);
   fChain->SetBranchAddress("PdfNorm", &PdfNorm, &b_PdfNorm);
   fChain->SetBranchAddress("Photon_Trigger", &Photon_Trigger, &b_Photon_Trigger);
   fChain->SetBranchAddress("SMH_JES", &SMH_JES, &b_SMH_JES);
   fChain->SetBranchAddress("SMH_btag", &SMH_btag, &b_SMH_btag);
   fChain->SetBranchAddress("SMH_facRenScale_bin0", &SMH_facRenScale_bin0, &b_SMH_facRenScale_bin0);
   fChain->SetBranchAddress("SMH_facRenScale_bin1", &SMH_facRenScale_bin1, &b_SMH_facRenScale_bin1);
   fChain->SetBranchAddress("SMH_facRenScale_bin10", &SMH_facRenScale_bin10, &b_SMH_facRenScale_bin10);
   fChain->SetBranchAddress("SMH_facRenScale_bin11", &SMH_facRenScale_bin11, &b_SMH_facRenScale_bin11);
   fChain->SetBranchAddress("SMH_facRenScale_bin12", &SMH_facRenScale_bin12, &b_SMH_facRenScale_bin12);
   fChain->SetBranchAddress("SMH_facRenScale_bin13", &SMH_facRenScale_bin13, &b_SMH_facRenScale_bin13);
   fChain->SetBranchAddress("SMH_facRenScale_bin2", &SMH_facRenScale_bin2, &b_SMH_facRenScale_bin2);
   fChain->SetBranchAddress("SMH_facRenScale_bin3", &SMH_facRenScale_bin3, &b_SMH_facRenScale_bin3);
   fChain->SetBranchAddress("SMH_facRenScale_bin4", &SMH_facRenScale_bin4, &b_SMH_facRenScale_bin4);
   fChain->SetBranchAddress("SMH_facRenScale_bin5", &SMH_facRenScale_bin5, &b_SMH_facRenScale_bin5);
   fChain->SetBranchAddress("SMH_facRenScale_bin6", &SMH_facRenScale_bin6, &b_SMH_facRenScale_bin6);
   fChain->SetBranchAddress("SMH_facRenScale_bin7", &SMH_facRenScale_bin7, &b_SMH_facRenScale_bin7);
   fChain->SetBranchAddress("SMH_facRenScale_bin8", &SMH_facRenScale_bin8, &b_SMH_facRenScale_bin8);
   fChain->SetBranchAddress("SMH_facRenScale_bin9", &SMH_facRenScale_bin9, &b_SMH_facRenScale_bin9);
   fChain->SetBranchAddress("SMH_facScale_bin0", &SMH_facScale_bin0, &b_SMH_facScale_bin0);
   fChain->SetBranchAddress("SMH_facScale_bin1", &SMH_facScale_bin1, &b_SMH_facScale_bin1);
   fChain->SetBranchAddress("SMH_facScale_bin10", &SMH_facScale_bin10, &b_SMH_facScale_bin10);
   fChain->SetBranchAddress("SMH_facScale_bin11", &SMH_facScale_bin11, &b_SMH_facScale_bin11);
   fChain->SetBranchAddress("SMH_facScale_bin12", &SMH_facScale_bin12, &b_SMH_facScale_bin12);
   fChain->SetBranchAddress("SMH_facScale_bin13", &SMH_facScale_bin13, &b_SMH_facScale_bin13);
   fChain->SetBranchAddress("SMH_facScale_bin2", &SMH_facScale_bin2, &b_SMH_facScale_bin2);
   fChain->SetBranchAddress("SMH_facScale_bin3", &SMH_facScale_bin3, &b_SMH_facScale_bin3);
   fChain->SetBranchAddress("SMH_facScale_bin4", &SMH_facScale_bin4, &b_SMH_facScale_bin4);
   fChain->SetBranchAddress("SMH_facScale_bin5", &SMH_facScale_bin5, &b_SMH_facScale_bin5);
   fChain->SetBranchAddress("SMH_facScale_bin6", &SMH_facScale_bin6, &b_SMH_facScale_bin6);
   fChain->SetBranchAddress("SMH_facScale_bin7", &SMH_facScale_bin7, &b_SMH_facScale_bin7);
   fChain->SetBranchAddress("SMH_facScale_bin8", &SMH_facScale_bin8, &b_SMH_facScale_bin8);
   fChain->SetBranchAddress("SMH_facScale_bin9", &SMH_facScale_bin9, &b_SMH_facScale_bin9);
   fChain->SetBranchAddress("SMH_misstag", &SMH_misstag, &b_SMH_misstag);
   fChain->SetBranchAddress("SMH_pdf0", &SMH_pdf0, &b_SMH_pdf0);
   fChain->SetBranchAddress("SMH_pdf1", &SMH_pdf1, &b_SMH_pdf1);
   fChain->SetBranchAddress("SMH_pdf10", &SMH_pdf10, &b_SMH_pdf10);
   fChain->SetBranchAddress("SMH_pdf11", &SMH_pdf11, &b_SMH_pdf11);
   fChain->SetBranchAddress("SMH_pdf12", &SMH_pdf12, &b_SMH_pdf12);
   fChain->SetBranchAddress("SMH_pdf13", &SMH_pdf13, &b_SMH_pdf13);
   fChain->SetBranchAddress("SMH_pdf14", &SMH_pdf14, &b_SMH_pdf14);
   fChain->SetBranchAddress("SMH_pdf15", &SMH_pdf15, &b_SMH_pdf15);
   fChain->SetBranchAddress("SMH_pdf16", &SMH_pdf16, &b_SMH_pdf16);
   fChain->SetBranchAddress("SMH_pdf17", &SMH_pdf17, &b_SMH_pdf17);
   fChain->SetBranchAddress("SMH_pdf18", &SMH_pdf18, &b_SMH_pdf18);
   fChain->SetBranchAddress("SMH_pdf19", &SMH_pdf19, &b_SMH_pdf19);
   fChain->SetBranchAddress("SMH_pdf2", &SMH_pdf2, &b_SMH_pdf2);
   fChain->SetBranchAddress("SMH_pdf20", &SMH_pdf20, &b_SMH_pdf20);
   fChain->SetBranchAddress("SMH_pdf21", &SMH_pdf21, &b_SMH_pdf21);
   fChain->SetBranchAddress("SMH_pdf22", &SMH_pdf22, &b_SMH_pdf22);
   fChain->SetBranchAddress("SMH_pdf23", &SMH_pdf23, &b_SMH_pdf23);
   fChain->SetBranchAddress("SMH_pdf24", &SMH_pdf24, &b_SMH_pdf24);
   fChain->SetBranchAddress("SMH_pdf25", &SMH_pdf25, &b_SMH_pdf25);
   fChain->SetBranchAddress("SMH_pdf26", &SMH_pdf26, &b_SMH_pdf26);
   fChain->SetBranchAddress("SMH_pdf27", &SMH_pdf27, &b_SMH_pdf27);
   fChain->SetBranchAddress("SMH_pdf28", &SMH_pdf28, &b_SMH_pdf28);
   fChain->SetBranchAddress("SMH_pdf29", &SMH_pdf29, &b_SMH_pdf29);
   fChain->SetBranchAddress("SMH_pdf3", &SMH_pdf3, &b_SMH_pdf3);
   fChain->SetBranchAddress("SMH_pdf30", &SMH_pdf30, &b_SMH_pdf30);
   fChain->SetBranchAddress("SMH_pdf31", &SMH_pdf31, &b_SMH_pdf31);
   fChain->SetBranchAddress("SMH_pdf32", &SMH_pdf32, &b_SMH_pdf32);
   fChain->SetBranchAddress("SMH_pdf33", &SMH_pdf33, &b_SMH_pdf33);
   fChain->SetBranchAddress("SMH_pdf34", &SMH_pdf34, &b_SMH_pdf34);
   fChain->SetBranchAddress("SMH_pdf35", &SMH_pdf35, &b_SMH_pdf35);
   fChain->SetBranchAddress("SMH_pdf36", &SMH_pdf36, &b_SMH_pdf36);
   fChain->SetBranchAddress("SMH_pdf37", &SMH_pdf37, &b_SMH_pdf37);
   fChain->SetBranchAddress("SMH_pdf38", &SMH_pdf38, &b_SMH_pdf38);
   fChain->SetBranchAddress("SMH_pdf39", &SMH_pdf39, &b_SMH_pdf39);
   fChain->SetBranchAddress("SMH_pdf4", &SMH_pdf4, &b_SMH_pdf4);
   fChain->SetBranchAddress("SMH_pdf40", &SMH_pdf40, &b_SMH_pdf40);
   fChain->SetBranchAddress("SMH_pdf41", &SMH_pdf41, &b_SMH_pdf41);
   fChain->SetBranchAddress("SMH_pdf42", &SMH_pdf42, &b_SMH_pdf42);
   fChain->SetBranchAddress("SMH_pdf43", &SMH_pdf43, &b_SMH_pdf43);
   fChain->SetBranchAddress("SMH_pdf44", &SMH_pdf44, &b_SMH_pdf44);
   fChain->SetBranchAddress("SMH_pdf45", &SMH_pdf45, &b_SMH_pdf45);
   fChain->SetBranchAddress("SMH_pdf46", &SMH_pdf46, &b_SMH_pdf46);
   fChain->SetBranchAddress("SMH_pdf47", &SMH_pdf47, &b_SMH_pdf47);
   fChain->SetBranchAddress("SMH_pdf48", &SMH_pdf48, &b_SMH_pdf48);
   fChain->SetBranchAddress("SMH_pdf49", &SMH_pdf49, &b_SMH_pdf49);
   fChain->SetBranchAddress("SMH_pdf5", &SMH_pdf5, &b_SMH_pdf5);
   fChain->SetBranchAddress("SMH_pdf50", &SMH_pdf50, &b_SMH_pdf50);
   fChain->SetBranchAddress("SMH_pdf51", &SMH_pdf51, &b_SMH_pdf51);
   fChain->SetBranchAddress("SMH_pdf52", &SMH_pdf52, &b_SMH_pdf52);
   fChain->SetBranchAddress("SMH_pdf53", &SMH_pdf53, &b_SMH_pdf53);
   fChain->SetBranchAddress("SMH_pdf54", &SMH_pdf54, &b_SMH_pdf54);
   fChain->SetBranchAddress("SMH_pdf55", &SMH_pdf55, &b_SMH_pdf55);
   fChain->SetBranchAddress("SMH_pdf56", &SMH_pdf56, &b_SMH_pdf56);
   fChain->SetBranchAddress("SMH_pdf57", &SMH_pdf57, &b_SMH_pdf57);
   fChain->SetBranchAddress("SMH_pdf58", &SMH_pdf58, &b_SMH_pdf58);
   fChain->SetBranchAddress("SMH_pdf59", &SMH_pdf59, &b_SMH_pdf59);
   fChain->SetBranchAddress("SMH_pdf6", &SMH_pdf6, &b_SMH_pdf6);
   fChain->SetBranchAddress("SMH_pdf7", &SMH_pdf7, &b_SMH_pdf7);
   fChain->SetBranchAddress("SMH_pdf8", &SMH_pdf8, &b_SMH_pdf8);
   fChain->SetBranchAddress("SMH_pdf9", &SMH_pdf9, &b_SMH_pdf9);
   fChain->SetBranchAddress("SMH_renScale_bin0", &SMH_renScale_bin0, &b_SMH_renScale_bin0);
   fChain->SetBranchAddress("SMH_renScale_bin1", &SMH_renScale_bin1, &b_SMH_renScale_bin1);
   fChain->SetBranchAddress("SMH_renScale_bin10", &SMH_renScale_bin10, &b_SMH_renScale_bin10);
   fChain->SetBranchAddress("SMH_renScale_bin11", &SMH_renScale_bin11, &b_SMH_renScale_bin11);
   fChain->SetBranchAddress("SMH_renScale_bin12", &SMH_renScale_bin12, &b_SMH_renScale_bin12);
   fChain->SetBranchAddress("SMH_renScale_bin13", &SMH_renScale_bin13, &b_SMH_renScale_bin13);
   fChain->SetBranchAddress("SMH_renScale_bin2", &SMH_renScale_bin2, &b_SMH_renScale_bin2);
   fChain->SetBranchAddress("SMH_renScale_bin3", &SMH_renScale_bin3, &b_SMH_renScale_bin3);
   fChain->SetBranchAddress("SMH_renScale_bin4", &SMH_renScale_bin4, &b_SMH_renScale_bin4);
   fChain->SetBranchAddress("SMH_renScale_bin5", &SMH_renScale_bin5, &b_SMH_renScale_bin5);
   fChain->SetBranchAddress("SMH_renScale_bin6", &SMH_renScale_bin6, &b_SMH_renScale_bin6);
   fChain->SetBranchAddress("SMH_renScale_bin7", &SMH_renScale_bin7, &b_SMH_renScale_bin7);
   fChain->SetBranchAddress("SMH_renScale_bin8", &SMH_renScale_bin8, &b_SMH_renScale_bin8);
   fChain->SetBranchAddress("SMH_renScale_bin9", &SMH_renScale_bin9, &b_SMH_renScale_bin9);
   fChain->SetBranchAddress("SigmaMoverMEfficiency", &SigmaMoverMEfficiency, &b_SigmaMoverMEfficiency);
   fChain->SetBranchAddress("Signal_ISR", &Signal_ISR, &b_Signal_ISR);
   fChain->SetBranchAddress("Signal_JES", &Signal_JES, &b_Signal_JES);
   fChain->SetBranchAddress("Signal_btag", &Signal_btag, &b_Signal_btag);
   fChain->SetBranchAddress("Signal_facRenScale_bin0", &Signal_facRenScale_bin0, &b_Signal_facRenScale_bin0);
   fChain->SetBranchAddress("Signal_facRenScale_bin1", &Signal_facRenScale_bin1, &b_Signal_facRenScale_bin1);
   fChain->SetBranchAddress("Signal_facRenScale_bin10", &Signal_facRenScale_bin10, &b_Signal_facRenScale_bin10);
   fChain->SetBranchAddress("Signal_facRenScale_bin11", &Signal_facRenScale_bin11, &b_Signal_facRenScale_bin11);
   fChain->SetBranchAddress("Signal_facRenScale_bin12", &Signal_facRenScale_bin12, &b_Signal_facRenScale_bin12);
   fChain->SetBranchAddress("Signal_facRenScale_bin13", &Signal_facRenScale_bin13, &b_Signal_facRenScale_bin13);
   fChain->SetBranchAddress("Signal_facRenScale_bin2", &Signal_facRenScale_bin2, &b_Signal_facRenScale_bin2);
   fChain->SetBranchAddress("Signal_facRenScale_bin3", &Signal_facRenScale_bin3, &b_Signal_facRenScale_bin3);
   fChain->SetBranchAddress("Signal_facRenScale_bin4", &Signal_facRenScale_bin4, &b_Signal_facRenScale_bin4);
   fChain->SetBranchAddress("Signal_facRenScale_bin5", &Signal_facRenScale_bin5, &b_Signal_facRenScale_bin5);
   fChain->SetBranchAddress("Signal_facRenScale_bin6", &Signal_facRenScale_bin6, &b_Signal_facRenScale_bin6);
   fChain->SetBranchAddress("Signal_facRenScale_bin7", &Signal_facRenScale_bin7, &b_Signal_facRenScale_bin7);
   fChain->SetBranchAddress("Signal_facRenScale_bin8", &Signal_facRenScale_bin8, &b_Signal_facRenScale_bin8);
   fChain->SetBranchAddress("Signal_facRenScale_bin9", &Signal_facRenScale_bin9, &b_Signal_facRenScale_bin9);
   fChain->SetBranchAddress("Signal_facScale_bin0", &Signal_facScale_bin0, &b_Signal_facScale_bin0);
   fChain->SetBranchAddress("Signal_facScale_bin1", &Signal_facScale_bin1, &b_Signal_facScale_bin1);
   fChain->SetBranchAddress("Signal_facScale_bin10", &Signal_facScale_bin10, &b_Signal_facScale_bin10);
   fChain->SetBranchAddress("Signal_facScale_bin11", &Signal_facScale_bin11, &b_Signal_facScale_bin11);
   fChain->SetBranchAddress("Signal_facScale_bin12", &Signal_facScale_bin12, &b_Signal_facScale_bin12);
   fChain->SetBranchAddress("Signal_facScale_bin13", &Signal_facScale_bin13, &b_Signal_facScale_bin13);
   fChain->SetBranchAddress("Signal_facScale_bin2", &Signal_facScale_bin2, &b_Signal_facScale_bin2);
   fChain->SetBranchAddress("Signal_facScale_bin3", &Signal_facScale_bin3, &b_Signal_facScale_bin3);
   fChain->SetBranchAddress("Signal_facScale_bin4", &Signal_facScale_bin4, &b_Signal_facScale_bin4);
   fChain->SetBranchAddress("Signal_facScale_bin5", &Signal_facScale_bin5, &b_Signal_facScale_bin5);
   fChain->SetBranchAddress("Signal_facScale_bin6", &Signal_facScale_bin6, &b_Signal_facScale_bin6);
   fChain->SetBranchAddress("Signal_facScale_bin7", &Signal_facScale_bin7, &b_Signal_facScale_bin7);
   fChain->SetBranchAddress("Signal_facScale_bin8", &Signal_facScale_bin8, &b_Signal_facScale_bin8);
   fChain->SetBranchAddress("Signal_facScale_bin9", &Signal_facScale_bin9, &b_Signal_facScale_bin9);
   fChain->SetBranchAddress("Signal_misstag", &Signal_misstag, &b_Signal_misstag);
   fChain->SetBranchAddress("Signal_pdf0", &Signal_pdf0, &b_Signal_pdf0);
   fChain->SetBranchAddress("Signal_pdf1", &Signal_pdf1, &b_Signal_pdf1);
   fChain->SetBranchAddress("Signal_pdf10", &Signal_pdf10, &b_Signal_pdf10);
   fChain->SetBranchAddress("Signal_pdf11", &Signal_pdf11, &b_Signal_pdf11);
   fChain->SetBranchAddress("Signal_pdf12", &Signal_pdf12, &b_Signal_pdf12);
   fChain->SetBranchAddress("Signal_pdf13", &Signal_pdf13, &b_Signal_pdf13);
   fChain->SetBranchAddress("Signal_pdf14", &Signal_pdf14, &b_Signal_pdf14);
   fChain->SetBranchAddress("Signal_pdf15", &Signal_pdf15, &b_Signal_pdf15);
   fChain->SetBranchAddress("Signal_pdf16", &Signal_pdf16, &b_Signal_pdf16);
   fChain->SetBranchAddress("Signal_pdf17", &Signal_pdf17, &b_Signal_pdf17);
   fChain->SetBranchAddress("Signal_pdf18", &Signal_pdf18, &b_Signal_pdf18);
   fChain->SetBranchAddress("Signal_pdf19", &Signal_pdf19, &b_Signal_pdf19);
   fChain->SetBranchAddress("Signal_pdf2", &Signal_pdf2, &b_Signal_pdf2);
   fChain->SetBranchAddress("Signal_pdf20", &Signal_pdf20, &b_Signal_pdf20);
   fChain->SetBranchAddress("Signal_pdf21", &Signal_pdf21, &b_Signal_pdf21);
   fChain->SetBranchAddress("Signal_pdf22", &Signal_pdf22, &b_Signal_pdf22);
   fChain->SetBranchAddress("Signal_pdf23", &Signal_pdf23, &b_Signal_pdf23);
   fChain->SetBranchAddress("Signal_pdf24", &Signal_pdf24, &b_Signal_pdf24);
   fChain->SetBranchAddress("Signal_pdf25", &Signal_pdf25, &b_Signal_pdf25);
   fChain->SetBranchAddress("Signal_pdf26", &Signal_pdf26, &b_Signal_pdf26);
   fChain->SetBranchAddress("Signal_pdf27", &Signal_pdf27, &b_Signal_pdf27);
   fChain->SetBranchAddress("Signal_pdf28", &Signal_pdf28, &b_Signal_pdf28);
   fChain->SetBranchAddress("Signal_pdf29", &Signal_pdf29, &b_Signal_pdf29);
   fChain->SetBranchAddress("Signal_pdf3", &Signal_pdf3, &b_Signal_pdf3);
   fChain->SetBranchAddress("Signal_pdf30", &Signal_pdf30, &b_Signal_pdf30);
   fChain->SetBranchAddress("Signal_pdf31", &Signal_pdf31, &b_Signal_pdf31);
   fChain->SetBranchAddress("Signal_pdf32", &Signal_pdf32, &b_Signal_pdf32);
   fChain->SetBranchAddress("Signal_pdf33", &Signal_pdf33, &b_Signal_pdf33);
   fChain->SetBranchAddress("Signal_pdf34", &Signal_pdf34, &b_Signal_pdf34);
   fChain->SetBranchAddress("Signal_pdf35", &Signal_pdf35, &b_Signal_pdf35);
   fChain->SetBranchAddress("Signal_pdf36", &Signal_pdf36, &b_Signal_pdf36);
   fChain->SetBranchAddress("Signal_pdf37", &Signal_pdf37, &b_Signal_pdf37);
   fChain->SetBranchAddress("Signal_pdf38", &Signal_pdf38, &b_Signal_pdf38);
   fChain->SetBranchAddress("Signal_pdf39", &Signal_pdf39, &b_Signal_pdf39);
   fChain->SetBranchAddress("Signal_pdf4", &Signal_pdf4, &b_Signal_pdf4);
   fChain->SetBranchAddress("Signal_pdf40", &Signal_pdf40, &b_Signal_pdf40);
   fChain->SetBranchAddress("Signal_pdf41", &Signal_pdf41, &b_Signal_pdf41);
   fChain->SetBranchAddress("Signal_pdf42", &Signal_pdf42, &b_Signal_pdf42);
   fChain->SetBranchAddress("Signal_pdf43", &Signal_pdf43, &b_Signal_pdf43);
   fChain->SetBranchAddress("Signal_pdf44", &Signal_pdf44, &b_Signal_pdf44);
   fChain->SetBranchAddress("Signal_pdf45", &Signal_pdf45, &b_Signal_pdf45);
   fChain->SetBranchAddress("Signal_pdf46", &Signal_pdf46, &b_Signal_pdf46);
   fChain->SetBranchAddress("Signal_pdf47", &Signal_pdf47, &b_Signal_pdf47);
   fChain->SetBranchAddress("Signal_pdf48", &Signal_pdf48, &b_Signal_pdf48);
   fChain->SetBranchAddress("Signal_pdf49", &Signal_pdf49, &b_Signal_pdf49);
   fChain->SetBranchAddress("Signal_pdf5", &Signal_pdf5, &b_Signal_pdf5);
   fChain->SetBranchAddress("Signal_pdf50", &Signal_pdf50, &b_Signal_pdf50);
   fChain->SetBranchAddress("Signal_pdf51", &Signal_pdf51, &b_Signal_pdf51);
   fChain->SetBranchAddress("Signal_pdf52", &Signal_pdf52, &b_Signal_pdf52);
   fChain->SetBranchAddress("Signal_pdf53", &Signal_pdf53, &b_Signal_pdf53);
   fChain->SetBranchAddress("Signal_pdf54", &Signal_pdf54, &b_Signal_pdf54);
   fChain->SetBranchAddress("Signal_pdf55", &Signal_pdf55, &b_Signal_pdf55);
   fChain->SetBranchAddress("Signal_pdf56", &Signal_pdf56, &b_Signal_pdf56);
   fChain->SetBranchAddress("Signal_pdf57", &Signal_pdf57, &b_Signal_pdf57);
   fChain->SetBranchAddress("Signal_pdf6", &Signal_pdf6, &b_Signal_pdf6);
   fChain->SetBranchAddress("Signal_pdf7", &Signal_pdf7, &b_Signal_pdf7);
   fChain->SetBranchAddress("Signal_pdf8", &Signal_pdf8, &b_Signal_pdf8);
   fChain->SetBranchAddress("Signal_pdf9", &Signal_pdf9, &b_Signal_pdf9);
   fChain->SetBranchAddress("Signal_renScale_bin0", &Signal_renScale_bin0, &b_Signal_renScale_bin0);
   fChain->SetBranchAddress("Signal_renScale_bin1", &Signal_renScale_bin1, &b_Signal_renScale_bin1);
   fChain->SetBranchAddress("Signal_renScale_bin10", &Signal_renScale_bin10, &b_Signal_renScale_bin10);
   fChain->SetBranchAddress("Signal_renScale_bin11", &Signal_renScale_bin11, &b_Signal_renScale_bin11);
   fChain->SetBranchAddress("Signal_renScale_bin12", &Signal_renScale_bin12, &b_Signal_renScale_bin12);
   fChain->SetBranchAddress("Signal_renScale_bin13", &Signal_renScale_bin13, &b_Signal_renScale_bin13);
   fChain->SetBranchAddress("Signal_renScale_bin2", &Signal_renScale_bin2, &b_Signal_renScale_bin2);
   fChain->SetBranchAddress("Signal_renScale_bin3", &Signal_renScale_bin3, &b_Signal_renScale_bin3);
   fChain->SetBranchAddress("Signal_renScale_bin4", &Signal_renScale_bin4, &b_Signal_renScale_bin4);
   fChain->SetBranchAddress("Signal_renScale_bin5", &Signal_renScale_bin5, &b_Signal_renScale_bin5);
   fChain->SetBranchAddress("Signal_renScale_bin6", &Signal_renScale_bin6, &b_Signal_renScale_bin6);
   fChain->SetBranchAddress("Signal_renScale_bin7", &Signal_renScale_bin7, &b_Signal_renScale_bin7);
   fChain->SetBranchAddress("Signal_renScale_bin8", &Signal_renScale_bin8, &b_Signal_renScale_bin8);
   fChain->SetBranchAddress("Signal_renScale_bin9", &Signal_renScale_bin9, &b_Signal_renScale_bin9);
   fChain->SetBranchAddress("mu_Global", &mu_Global, &b_mu_Global);
   fChain->SetBranchAddress("hzbb_mu_Global", &hzbb_mu_Global, &b_hzbb_mu_Global);
   fChain->SetBranchAddress("highpt_mu_Global", &highpt_mu_Global, &b_highpt_mu_Global);
   fChain->SetBranchAddress("lowres_mu_Global", &lowres_mu_Global, &b_lowres_mu_Global);
   fChain->SetBranchAddress("n_exp_final_binch10_proc_Bkg", &n_exp_final_binch10_proc_Bkg, &b_n_exp_final_binch10_proc_Bkg);
   fChain->SetBranchAddress("n_exp_final_binch10_proc_SMH", &n_exp_final_binch10_proc_SMH, &b_n_exp_final_binch10_proc_SMH);
   fChain->SetBranchAddress("n_exp_final_binch10_proc_signal", &n_exp_final_binch10_proc_signal, &b_n_exp_final_binch10_proc_signal);
   fChain->SetBranchAddress("n_exp_final_binch11_proc_Bkg", &n_exp_final_binch11_proc_Bkg, &b_n_exp_final_binch11_proc_Bkg);
   fChain->SetBranchAddress("n_exp_final_binch11_proc_SMH", &n_exp_final_binch11_proc_SMH, &b_n_exp_final_binch11_proc_SMH);
   fChain->SetBranchAddress("n_exp_final_binch11_proc_signal", &n_exp_final_binch11_proc_signal, &b_n_exp_final_binch11_proc_signal);
   fChain->SetBranchAddress("n_exp_final_binch12_proc_Bkg", &n_exp_final_binch12_proc_Bkg, &b_n_exp_final_binch12_proc_Bkg);
   fChain->SetBranchAddress("n_exp_final_binch12_proc_SMH", &n_exp_final_binch12_proc_SMH, &b_n_exp_final_binch12_proc_SMH);
   fChain->SetBranchAddress("n_exp_final_binch12_proc_signal", &n_exp_final_binch12_proc_signal, &b_n_exp_final_binch12_proc_signal);
   fChain->SetBranchAddress("n_exp_final_binch13_proc_Bkg", &n_exp_final_binch13_proc_Bkg, &b_n_exp_final_binch13_proc_Bkg);
   fChain->SetBranchAddress("n_exp_final_binch13_proc_SMH", &n_exp_final_binch13_proc_SMH, &b_n_exp_final_binch13_proc_SMH);
   fChain->SetBranchAddress("n_exp_final_binch13_proc_signal", &n_exp_final_binch13_proc_signal, &b_n_exp_final_binch13_proc_signal);
   fChain->SetBranchAddress("n_exp_final_binch14_highResBin9_proc_Bkg", &n_exp_final_binch14_highResBin9_proc_Bkg, &b_n_exp_final_binch14_highResBin9_proc_Bkg);
   fChain->SetBranchAddress("n_exp_final_binch14_highResBin9_proc_SMH", &n_exp_final_binch14_highResBin9_proc_SMH, &b_n_exp_final_binch14_highResBin9_proc_SMH);
   fChain->SetBranchAddress("n_exp_final_binch14_highResBin9_proc_signal", &n_exp_final_binch14_highResBin9_proc_signal, &b_n_exp_final_binch14_highResBin9_proc_signal);
   fChain->SetBranchAddress("n_exp_final_binch14_lowResBin9_proc_Bkg", &n_exp_final_binch14_lowResBin9_proc_Bkg, &b_n_exp_final_binch14_lowResBin9_proc_Bkg);
   fChain->SetBranchAddress("n_exp_final_binch14_lowResBin9_proc_SMH", &n_exp_final_binch14_lowResBin9_proc_SMH, &b_n_exp_final_binch14_lowResBin9_proc_SMH);
   fChain->SetBranchAddress("n_exp_final_binch14_lowResBin9_proc_signal", &n_exp_final_binch14_lowResBin9_proc_signal, &b_n_exp_final_binch14_lowResBin9_proc_signal);
   fChain->SetBranchAddress("n_exp_final_binch1_proc_Bkg", &n_exp_final_binch1_proc_Bkg, &b_n_exp_final_binch1_proc_Bkg);
   fChain->SetBranchAddress("n_exp_final_binch1_proc_SMH", &n_exp_final_binch1_proc_SMH, &b_n_exp_final_binch1_proc_SMH);
   fChain->SetBranchAddress("n_exp_final_binch1_proc_signal", &n_exp_final_binch1_proc_signal, &b_n_exp_final_binch1_proc_signal);
   fChain->SetBranchAddress("n_exp_final_binch2_proc_Bkg", &n_exp_final_binch2_proc_Bkg, &b_n_exp_final_binch2_proc_Bkg);
   fChain->SetBranchAddress("n_exp_final_binch2_proc_SMH", &n_exp_final_binch2_proc_SMH, &b_n_exp_final_binch2_proc_SMH);
   fChain->SetBranchAddress("n_exp_final_binch2_proc_signal", &n_exp_final_binch2_proc_signal, &b_n_exp_final_binch2_proc_signal);
   fChain->SetBranchAddress("n_exp_final_binch3_highResBin10_proc_Bkg", &n_exp_final_binch3_highResBin10_proc_Bkg, &b_n_exp_final_binch3_highResBin10_proc_Bkg);
   fChain->SetBranchAddress("n_exp_final_binch3_highResBin10_proc_SMH", &n_exp_final_binch3_highResBin10_proc_SMH, &b_n_exp_final_binch3_highResBin10_proc_SMH);
   fChain->SetBranchAddress("n_exp_final_binch3_highResBin10_proc_signal", &n_exp_final_binch3_highResBin10_proc_signal, &b_n_exp_final_binch3_highResBin10_proc_signal);
   fChain->SetBranchAddress("n_exp_final_binch3_lowResBin10_proc_Bkg", &n_exp_final_binch3_lowResBin10_proc_Bkg, &b_n_exp_final_binch3_lowResBin10_proc_Bkg);
   fChain->SetBranchAddress("n_exp_final_binch3_lowResBin10_proc_SMH", &n_exp_final_binch3_lowResBin10_proc_SMH, &b_n_exp_final_binch3_lowResBin10_proc_SMH);
   fChain->SetBranchAddress("n_exp_final_binch3_lowResBin10_proc_signal", &n_exp_final_binch3_lowResBin10_proc_signal, &b_n_exp_final_binch3_lowResBin10_proc_signal);
   fChain->SetBranchAddress("n_exp_final_binch4_highResBin11_proc_Bkg", &n_exp_final_binch4_highResBin11_proc_Bkg, &b_n_exp_final_binch4_highResBin11_proc_Bkg);
   fChain->SetBranchAddress("n_exp_final_binch4_highResBin11_proc_SMH", &n_exp_final_binch4_highResBin11_proc_SMH, &b_n_exp_final_binch4_highResBin11_proc_SMH);
   fChain->SetBranchAddress("n_exp_final_binch4_highResBin11_proc_signal", &n_exp_final_binch4_highResBin11_proc_signal, &b_n_exp_final_binch4_highResBin11_proc_signal);
   fChain->SetBranchAddress("n_exp_final_binch4_lowResBin11_proc_Bkg", &n_exp_final_binch4_lowResBin11_proc_Bkg, &b_n_exp_final_binch4_lowResBin11_proc_Bkg);
   fChain->SetBranchAddress("n_exp_final_binch4_lowResBin11_proc_SMH", &n_exp_final_binch4_lowResBin11_proc_SMH, &b_n_exp_final_binch4_lowResBin11_proc_SMH);
   fChain->SetBranchAddress("n_exp_final_binch4_lowResBin11_proc_signal", &n_exp_final_binch4_lowResBin11_proc_signal, &b_n_exp_final_binch4_lowResBin11_proc_signal);
   fChain->SetBranchAddress("n_exp_final_binch5_highResBin12_proc_Bkg", &n_exp_final_binch5_highResBin12_proc_Bkg, &b_n_exp_final_binch5_highResBin12_proc_Bkg);
   fChain->SetBranchAddress("n_exp_final_binch5_highResBin12_proc_SMH", &n_exp_final_binch5_highResBin12_proc_SMH, &b_n_exp_final_binch5_highResBin12_proc_SMH);
   fChain->SetBranchAddress("n_exp_final_binch5_highResBin12_proc_signal", &n_exp_final_binch5_highResBin12_proc_signal, &b_n_exp_final_binch5_highResBin12_proc_signal);
   fChain->SetBranchAddress("n_exp_final_binch5_lowResBin12_proc_Bkg", &n_exp_final_binch5_lowResBin12_proc_Bkg, &b_n_exp_final_binch5_lowResBin12_proc_Bkg);
   fChain->SetBranchAddress("n_exp_final_binch5_lowResBin12_proc_SMH", &n_exp_final_binch5_lowResBin12_proc_SMH, &b_n_exp_final_binch5_lowResBin12_proc_SMH);
   fChain->SetBranchAddress("n_exp_final_binch5_lowResBin12_proc_signal", &n_exp_final_binch5_lowResBin12_proc_signal, &b_n_exp_final_binch5_lowResBin12_proc_signal);
   fChain->SetBranchAddress("n_exp_final_binch6_highResBin13_proc_Bkg", &n_exp_final_binch6_highResBin13_proc_Bkg, &b_n_exp_final_binch6_highResBin13_proc_Bkg);
   fChain->SetBranchAddress("n_exp_final_binch6_highResBin13_proc_SMH", &n_exp_final_binch6_highResBin13_proc_SMH, &b_n_exp_final_binch6_highResBin13_proc_SMH);
   fChain->SetBranchAddress("n_exp_final_binch6_highResBin13_proc_signal", &n_exp_final_binch6_highResBin13_proc_signal, &b_n_exp_final_binch6_highResBin13_proc_signal);
   fChain->SetBranchAddress("n_exp_final_binch6_lowResBin13_proc_Bkg", &n_exp_final_binch6_lowResBin13_proc_Bkg, &b_n_exp_final_binch6_lowResBin13_proc_Bkg);
   fChain->SetBranchAddress("n_exp_final_binch6_lowResBin13_proc_SMH", &n_exp_final_binch6_lowResBin13_proc_SMH, &b_n_exp_final_binch6_lowResBin13_proc_SMH);
   fChain->SetBranchAddress("n_exp_final_binch6_lowResBin13_proc_signal", &n_exp_final_binch6_lowResBin13_proc_signal, &b_n_exp_final_binch6_lowResBin13_proc_signal);
   fChain->SetBranchAddress("n_exp_final_binch7_proc_Bkg", &n_exp_final_binch7_proc_Bkg, &b_n_exp_final_binch7_proc_Bkg);
   fChain->SetBranchAddress("n_exp_final_binch7_proc_SMH", &n_exp_final_binch7_proc_SMH, &b_n_exp_final_binch7_proc_SMH);
   fChain->SetBranchAddress("n_exp_final_binch7_proc_signal", &n_exp_final_binch7_proc_signal, &b_n_exp_final_binch7_proc_signal);
   fChain->SetBranchAddress("n_exp_final_binch8_proc_Bkg", &n_exp_final_binch8_proc_Bkg, &b_n_exp_final_binch8_proc_Bkg);
   fChain->SetBranchAddress("n_exp_final_binch8_proc_SMH", &n_exp_final_binch8_proc_SMH, &b_n_exp_final_binch8_proc_SMH);
   fChain->SetBranchAddress("n_exp_final_binch8_proc_signal", &n_exp_final_binch8_proc_signal, &b_n_exp_final_binch8_proc_signal);
   fChain->SetBranchAddress("n_exp_final_binch9_proc_Bkg", &n_exp_final_binch9_proc_Bkg, &b_n_exp_final_binch9_proc_Bkg);
   fChain->SetBranchAddress("n_exp_final_binch9_proc_SMH", &n_exp_final_binch9_proc_SMH, &b_n_exp_final_binch9_proc_SMH);
   fChain->SetBranchAddress("n_exp_final_binch9_proc_signal", &n_exp_final_binch9_proc_signal, &b_n_exp_final_binch9_proc_signal);
   Notify();
}

Bool_t tree_fit_sb::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void tree_fit_sb::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t tree_fit_sb::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef tree_fit_sb_cxx
