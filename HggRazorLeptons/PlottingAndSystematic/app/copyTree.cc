#include <iostream>
#include <algorithm>
#include <stdlib.h>
//ROOT INCLUDES
#include <TFile.h>
#include <TTree.h>
#include <TH1F.h>
#include <TROOT.h>
#include <TLorentzVector.h>
#include <TString.h>


int main( )
{
  gROOT->Reset();
  TString sampleName = "/Users/cmorgoth/Work/data/SusyEWK/MC/QCD_BKG_1pb_weighted_RemovedPromptPhotons";
  TFile *oldfile = new TFile(sampleName+".root");

  TTree *oldtree = (TTree*)oldfile->Get("HggRazorLeptons");
  TH1F* nevents = (TH1F*)oldfile->Get("NEvents");
  Long64_t nentries = oldtree->GetEntries();

  double kf = 3.46974;
  float weight;
  int pho1MotherID, pho2MotherID;
  oldtree->SetBranchAddress("weight", &weight);
  oldtree->SetBranchAddress("pho1MotherID", &pho1MotherID);
  oldtree->SetBranchAddress("pho2MotherID", &pho2MotherID);

  //TString processName = "gammaJet";
  //TString processName = "qcd";
  //TString processName = "wg";
  //TString processName = "ttg";
  TString processName = "none";
  
  double total_rm, total;
  total_rm = 0.0;
  total = 0.0;
  //Create a new file + a clone of old tree in new file
  TFile *newfile = new TFile(sampleName+"_KF_OneEleBox.root","recreate");
  TTree *newtree = oldtree->CloneTree(0);
  for (Long64_t i=0;i<nentries; i++) {
    oldtree->GetEntry(i);
    total += weight;
    
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
    if ( prompt_prompt && processName == "gammaJet" )
      {
	total_rm += weight;
	continue;
      }
    
    //remove events which are not fake-fake
    if ( !isFakeFake && processName == "qcd" )
      {
	total_rm += weight;
	continue;
      }
    
    //remove events which are not fake from WG and TTG
    if ( prompt_prompt && (processName == "wg" || processName == "ttg") )
      {	
	total_rm += weight;
	continue;
      }
    
    weight = kf*weight;
    newtree->Fill();
  }
  newtree->Print();
  newtree->AutoSave();
  nevents->Write();
  delete oldfile;
  delete newfile;

  std::cout << "==============================================" << std::endl;
  std::cout << "[info]: process " << processName << ". Removed " << 100.0*total_rm/total << "% of events" << std::endl;
  std::cout << "==============================================" << std::endl;
}
