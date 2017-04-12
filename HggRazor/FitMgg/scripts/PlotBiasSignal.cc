#include <iostream>
#include <vector>
#include <TFile.h>
#include <TTree.h>
#include <TH1F.h>
#include <TF1.h>
#include <TDirectory.h>

struct AnaBin
{
  double MR_high;
  double MR_low;
  double Rsq_high;
  double Rsq_low;
  double nevents;
};

void PlotBiasSignal( TString fname, TString SoverB = "1" )
{
  TFile* f = new TFile( fname, "READ");
  assert( f );

  TTree* tree = (TTree*)f->Get("biasTree");
  
  //Ns
  tree->Draw("(Ns-Ns_hat)>>_h_Ns_bias(50, -10,10)", "status==0 && covStatus==3 && status2==0 && covStatus2==3");
  TH1F* h_Ns_bias = (TH1F*)gDirectory->Get("_h_Ns_bias");
  
  tree->Draw("(Ns-Ns_hat)/Ns_sigma>>_h_Ns_pull(50, -3,3)", "status==0 && covStatus==3 && status2==0 && covStatus2==3");
  TH1F* h_Ns_pull = (TH1F*)gDirectory->Get("_h_Ns_pull");

  //Nbkg
  tree->Draw("(Nbkg-Nbkg_hat)>>_h_Nbkg_bias(50, -10,10)", "status==0 && covStatus==3 && status2==0 && covStatus2==3");
  TH1F* h_Nbkg_bias = (TH1F*)gDirectory->Get("_h_Nbkg_bias");
  
  tree->Draw("(Nbkg-Nbkg_hat)/Nbkg_sigma>>_h_Nnkg_pull(50, -3,3)", "status==0 && covStatus==3 && status2==0 && covStatus2==3");
  TH1F* h_Nbkg_pull = (TH1F*)gDirectory->Get("_h_Nbkg_pull");

  //alpha
  tree->Draw("(alpha-alpha_hat)>>_h_alpha_bias(50, -10,10)", "status==0 && covStatus==3 && status2==0 && covStatus2==3");
  TH1F* h_alpha_bias = (TH1F*)gDirectory->Get("_h_alpha_bias");
  
  tree->Draw("(alpha-alpha_hat)/alpha_sigma>>_h_alpha_pull(50, -3,3)", "status==0 && covStatus==3 && status2==0 && covStatus2==3");
  TH1F* h_alpha_pull = (TH1F*)gDirectory->Get("_h_alpha_pull");

  //Ns_Nbkg_Correlation
  tree->Draw("Ns_hat:Nbkg_hat>>_h_Ns_Nbkg(50, 0, 100, 50, -20, 20)", "status==0 && covStatus==3 && status2==0 && covStatus2==3");
  TH1F* h_Ns_Nbkg = (TH1F*)gDirectory->Get("_h_Ns_Nbkg");
  h_Ns_Nbkg->Draw("colz");

  //Ns_Nbkg_Correlation
  tree->Draw("Ns_hat:alpha_hat-alpha>>_h_Ns_alpha(50, -0.2, 0.2, 50, -20, 20)", "status==0 && covStatus==3 && status2==0 && covStatus2==3");
  TH1F* h_Ns_alpha = (TH1F*)gDirectory->Get("_h_Ns_alpha");
  h_Ns_alpha->Draw("colz");
  
  return;
};
