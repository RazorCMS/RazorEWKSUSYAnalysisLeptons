//C++ INCLUDES
#include <iostream>
#include <string>
#include <fstream>
//ROOT INCLUDES
#include <TFile.h>
#include <TTree.h>
#include <TH1F.h>

//LOCAL INCLUDES
#include "SusyHggMggFit.hh"

int main ( int argc, char* argv[] )
{
  std::ifstream ifs( "app/listTChiZH.txt", std::ifstream::in );
  TFile* oldFile;
  TFile* newFile;
  
  if ( ifs.is_open() )
    {
      while ( ifs.good() )
	{
	  std::string fname;
	  ifs >> fname;
	  if( ifs.eof() ) break;
	  oldFile = new TFile( fname.c_str(), "READ" );
	  std::string m1 = fname.substr( fname.find("TChiHZ_")+7, fname.find("_1pb_weighted.root")-(fname.find("TChiHZ_")+7) );
	  std::cout << fname << std::endl;
	  //std::cout << "m1: " << m1 << " m2: " << m2 << std::endl;
	  TTree* tree = (TTree*)oldFile->Get("HggRazor");
	  //std::cout << Form("Nevents%s%s", m1.c_str(),m2.c_str()) << std::endl;
	  TH1F* NEvents = (TH1F*)oldFile->Get( Form("NEvents%s", m1.c_str()) );
	  TH1F* SumWeights = (TH1F*)oldFile->Get( Form("SumWeights%s", m1.c_str()) );
	  TH1F*  SumScaleWeights= (TH1F*)oldFile->Get( Form("SumScaleWeights%s", m1.c_str()) );
	  TH1F* SumPdfWeights = (TH1F*)oldFile->Get( Form("SumPdfWeights%s", m1.c_str()) );
	  TH1F* NISRJets = (TH1F*)oldFile->Get( Form("NISRJets%s", m1.c_str()) );
	  newFile = new TFile( Form("/afs/cern.ch/work/c/cpena/public/combineDiphotonHM/CMSSW_7_4_7/src/eos/cms/store/group/phys_susy/razor/Run2Analysis/HggRazor/2016/V3p12_PhotonCorrDec06_JECSep23V3_20170219/FastsimSignal/combined/SMS-TChiHZ_%s_tweaked_1pb_weighted.root", m1.c_str()), "RECREATE" );
	  tree->SetBranchStatus("*",1);
	  TTree* newTree = tree->CloneTree();
	  newTree->Write();
	  NEvents->Write("NEvents");
	  SumWeights->Write("SumWeights");
	  SumScaleWeights->Write("SumScaleWeights");
	  SumPdfWeights->Write("SumPdfWeights");
	  NISRJets->Write("NISRJets");
	  delete oldFile;
	  delete newFile;
	}
    }
  else
    {
      std::cout << "[ERROR]: unable to open file; quitting" << std::endl;
    }

  return 0;
}
