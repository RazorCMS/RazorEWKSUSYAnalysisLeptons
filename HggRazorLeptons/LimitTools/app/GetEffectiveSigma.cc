#include <iostream>
#include <vector>
#include <fstream>
#include <assert.h>
//ROOT INCLUDES
#include <TFile.h>
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
  //-----------------
  //Selection TString
  //-----------------
  std::string categoryMode = ParseCommandLine( argc, argv, "-category=" );
  if (  categoryMode == "" )
    {
      std::cerr << "[ERROR]: please provide the category. Use --category=<highpt,hzbb,highres,lowres>" << std::endl;
      return -1;
    }
  
  TString cut = "mGammaGamma > 103. && mGammaGamma < 160. && pho1passIso == 1 && pho2passIso == 1 && pho1passEleVeto == 1 && pho2passEleVeto == 1 && abs(pho1Eta) <1.48 && abs(pho2Eta)<1.48 && (pho1Pt>40||pho2Pt>40)  && pho1Pt> 25. && pho2Pt>25.";
  TString categoryCutString;

  if (categoryMode == "highpt") categoryCutString = " && pTGammaGamma >= 110 ";
  else if (categoryMode == "hzbb") categoryCutString = " && pTGammaGamma < 110 && ( abs(mbbH_L-125.) < 15. || ( abs(mbbH_L-125.) >= 15. && abs(mbbZ_L-91.) < 15 ) )";
  else if (categoryMode == "highres") categoryCutString = " && pTGammaGamma < 110 && abs(mbbH_L-125.) >= 15 && abs(mbbZ_L-91.) >= 15 && sigmaMoverM < 0.0085";
  else if (categoryMode == "lowres") categoryCutString  = " && pTGammaGamma < 110 && abs(mbbH_L-125.) >= 15 && abs(mbbZ_L-91.) >= 15 && sigmaMoverM >= 0.0085 ";
  else if (categoryMode == "inclusive") categoryCutString = "";

  cut = cut + categoryCutString;

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
  
  if (categoryMode == "highpt") cutTree->Draw("mGammaGamma>>h_mgg(228,103,160)", "weight*pileupWeight*btagCorrFactor*triggerEffSFWeight*photonEffSF*(1)", "goff");
  else if (categoryMode == "hzbb") cutTree->Draw("mGammaGamma>>h_mgg(95,103,160)", "weight*pileupWeight*btagCorrFactor*triggerEffSFWeight*photonEffSF*(1)", "goff");
  else if (categoryMode == "highres") cutTree->Draw("mGammaGamma>>h_mgg(228,103,160)", "weight*pileupWeight*btagCorrFactor*triggerEffSFWeight*photonEffSF*(1)", "goff");
  else if (categoryMode == "lowres") cutTree->Draw("mGammaGamma>>h_mgg(95,103,160)", "weight*pileupWeight*btagCorrFactor*triggerEffSFWeight*photonEffSF*(1)", "goff");
  else if (categoryMode == "inclusive") cutTree->Draw("mGammaGamma>>h_mgg(95,103,160)", "weight*pileupWeight*btagCorrFactor*triggerEffSFWeight*photonEffSF*(1)", "goff");
  
  TH1F* h_mgg = (TH1F*)tmp->Get("h_mgg");
  double effSigma = GetEffSigma( h_mgg );
  std::cout << "[RESULT]: category: " << categoryMode << "; Effective Sigma = " << effSigma << std::endl;
  h_mgg->Write("mgg");
  tmp->Close();
  
  return 0;
}
