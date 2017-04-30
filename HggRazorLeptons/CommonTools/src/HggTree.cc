#define HggTree_cxx
//LOCAL INCLUDES
#include "HggTree.hh"
//ROOT INCLUDES
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void HggTree::Loop()
{
  if (fChain == 0) return;
  
  Long64_t nentries = fChain->GetEntriesFast();
  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;
    // if (Cut(ientry) < 0) continue;
  }
};

void HggTree::Clone( float kf )
{
  TFile* newfile = new TFile("test_clone_HggRazorLeptons.root", "RECREATE");
  TTree* newtree = this->fChain->CloneTree( 0 );
  //newtree->Print();
  int nentries = this->fChain->GetEntries();
  float weight;
  newtree->SetBranchAddress("weight", &weight);
  for ( int i = 0; i < nentries; i++ )
    {
      this->fChain->GetEntry(i);
      weight = kf*this->weight;
      newtree->Fill();
    }
  newtree->Write();
  delete newfile;
  
};
