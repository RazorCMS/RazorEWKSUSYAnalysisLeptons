#if !defined(__CINT__) || defined(__MAKECINT__)
#include <TROOT.h>
#include <TSystem.h>
#include <TFile.h>
#include <TTree.h>
#include <TLegend.h>
#include <TGaxis.h>
#include <vector>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <TH1.h>

#include "CompareHggMC.hh"

using namespace std;

#endif

int main() {

  SetStyle();

  //gROOT->Reset();

  //Config(TString fname, TString sname, TString lab, Int_t col, Int_t sty)

  Config amc_vbf("/afs/cern.ch/user/j/jlawhorn/eos/cms/store/group/phys_susy/razor/Run2Analysis/HggRazor/2016/V3p4_HiggsVar_July10/VBFHToGG_M125_13TeV_amcatnlo_pythia8_MiniAODv1_1pb_weighted.root", "amc_vbf","aMC@NLO", 1, 1);

  vector<Config> conf_list;
  conf_list.push_back(Config("/afs/cern.ch/user/j/jlawhorn/eos/cms/store/group/phys_susy/razor/Run2Analysis/HggRazor/2016/V3p4_HiggsVar_July10/VBFHToGG_M-125_13TeV_powheg_pythia8_MiniAODv1_1pb_weighted.root", "pow_vbf", "POWHEG", 2, 1));
  conf_list.push_back(Config("/afs/cern.ch/user/j/jlawhorn/eos/cms/store/group/phys_susy/razor/Run2Analysis/HggRazor/2016/V3p4_HiggsVar_July10/VBFHToGG_M125_13TeV_amcatnlo_pythia8_DownPS_MiniAODv1_1pb_weighted.root", "ps_d_vbf", "PS down", 9, 2));
  conf_list.push_back(Config("/afs/cern.ch/user/j/jlawhorn/eos/cms/store/group/phys_susy/razor/Run2Analysis/HggRazor/2016/V3p4_HiggsVar_July10/VBFHToGG_M125_13TeV_amcatnlo_pythia8_UpPS_MiniAODv1_1pb_weighted.root", "ps_u_vbf", "PS up", 8, 2));
  conf_list.push_back(Config("/afs/cern.ch/user/j/jlawhorn/eos/cms/store/group/phys_susy/razor/Run2Analysis/HggRazor/2016/V3p4_HiggsVar_July10/VBFHToGG_M125_13TeV_amcatnlo_pythia8_CUETP8M1Down_MiniAODv1_1pb_weighted.root", "ue_d_vbf", "UE down", 41, 5));
  conf_list.push_back(Config("/afs/cern.ch/user/j/jlawhorn/eos/cms/store/group/phys_susy/razor/Run2Analysis/HggRazor/2016/V3p4_HiggsVar_July10/VBFHToGG_M125_13TeV_amcatnlo_pythia8_CUETP8M1Up_MiniAODv1_1pb_weighted.root", "ue_u_vbf", "UE down", 46, 5));
  
  Int_t nMR=15, lMR=0, hMR=1500;
  Int_t nRs=10, lRs=0, hRs=1.0;

  //void draw(Category cat, TString var,
  //Config fB, vector<Config> fC,
  //Int_t nbins, Int_t xmin, Int_t xmax)

  //enum Category { inc=0, highpt, hzbb, highres, lowres };
  
  draw(inc, "MR", amc_vbf, conf_list, nMR, lMR, hMR);
  draw(inc, "Rsq", amc_vbf, conf_list, nRs, lRs, hRs);

  draw(highpt, "MR", amc_vbf, conf_list, nMR, lMR, hMR);
  draw(highpt, "Rsq", amc_vbf, conf_list, nRs, lRs, hRs);

  draw(hzbb, "MR", amc_vbf, conf_list, nMR, lMR, hMR);
  draw(hzbb, "Rsq", amc_vbf, conf_list, nRs, lRs, hRs);

  draw(highres, "MR", amc_vbf, conf_list, nMR, lMR, hMR);
  draw(highres, "Rsq", amc_vbf, conf_list, nRs, lRs, hRs);

  draw(lowres, "MR", amc_vbf, conf_list, nMR, lMR, hMR);
  draw(lowres, "Rsq", amc_vbf, conf_list, nRs, lRs, hRs);

  return 0;

}
