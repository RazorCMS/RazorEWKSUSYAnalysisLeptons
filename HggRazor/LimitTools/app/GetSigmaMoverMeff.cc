#include <iostream>
#include <vector>
#include <fstream>
#include <assert.h>
//ROOT INCLUDES
#include <TFile.h>
#include <TGraph.h>
#include <TTree.h>
#include <TH1F.h>
#include <TROOT.h>
//LOCAL INCLUDES
#include "AssortedFunctions.hh"
#include "CommandLineInput.hh"

int main( int argc, char* argv[] )
{

  gROOT->Reset();
  std::string inputFile = ParseCommandLine( argc, argv, "-inputFile=" );
  if (  inputFile == "" )
    {
      std::cerr << "[ERROR]: please provide an input list file using --inputFile=<path_to_list_file>" << std::endl;
      return -1;
    }
  
  
  TString cut = "mGammaGamma > 103. && mGammaGamma < 160. && pho1passIso == 1 && pho2passIso == 1 && pho1passEleVeto == 1 && pho2passEleVeto == 1 && abs(pho1Eta) <1.48 && abs(pho2Eta)<1.48 && (pho1Pt>40||pho2Pt>40)  && pho1Pt> 25. && pho2Pt>25. && pTGammaGamma < 110 && abs(mbbH_L-125.) >= 15 && abs(mbbZ_L-91.) >= 15";
  
  
  TFile* fin = new TFile( inputFile.c_str(), "READ");
  std::cout << "[INFO]: checking file: " << inputFile << std::endl;
  assert( fin );
  std::cout << "[INFO]: file: " << inputFile << " passed check\n\n"<< std::endl;
      
  //------------------------
  //Getting TTree and Histos
  //------------------------
  TTree* tree = (TTree*)fin->Get("HggRazor");
  assert( tree );
  
  TFile* tmp = new TFile("tmp.root", "RECREATE");
  TTree* cutTree = tree->CopyTree( cut );
  

  
  cutTree->Draw("mGammaGamma>>h_mgg(95,103,160)", "weight*pileupWeight*btagCorrFactor*triggerEffSFWeight*photonEffSF*(1)", "goff");
  
  TH1F* h_mgg = (TH1F*)tmp->Get("h_mgg");
  double n_total = h_mgg->Integral();

  float sigmaMoverMcut = 0.005;
  float sigmaCut[500];
  float eff[500];
  for (int i = 0; i < 500; i++ )
    {
      TString tmpH = Form("mGammaGamma >> h_mgg%d(95,103,160)", i);
      TString tmpH1 = Form("h_mgg%d", i);
      cutTree->Draw(tmpH, Form("weight*pileupWeight*btagCorrFactor*triggerEffSFWeight*photonEffSF*(sigmaMoverM < %f)", sigmaMoverMcut), "goff");
      
      TH1F* h_mgg_cut = (TH1F*)tmp->Get(tmpH1);
      double n_total_cut = h_mgg_cut->Integral();
      std::cout << "sigmaMoverM: " << sigmaMoverMcut << "; eff: " << n_total_cut/n_total<< std::endl;
      sigmaCut[i] = sigmaMoverMcut;
      eff[i] = n_total_cut/n_total;
      sigmaMoverMcut += 0.00025;
    }

  TGraph* gr = new TGraph( 500, sigmaCut, eff);
  
  h_mgg->Write("mgg");
  gr->Write("eff");
  tmp->Close();
  
  return 0;
}
