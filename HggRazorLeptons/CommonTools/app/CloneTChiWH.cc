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
  std::ifstream ifs( "list.txt", std::ifstream::in );
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
	  std::string m1 = fname.substr( fname.find("TChiWH_")+7, 3 );
	  std::string m2 = fname.substr( fname.find("TChiWH_")+11, fname.find("_1pb_weighted.root")-(fname.find("TChiWH_")+11));
	  std::cout << fname << std::endl;
	  //std::cout << "m1: " << m1 << " m2: " << m2 << std::endl;
	  TTree* tree = (TTree*)oldFile->Get("HggRazor");
	  //std::cout << Form("Nevents%s%s", m1.c_str(),m2.c_str()) << std::endl;
	  TH1F* NEvents = (TH1F*)oldFile->Get( Form("NEvents%s%s", m1.c_str(),m2.c_str()) );
	  TH1F* SumWeights = (TH1F*)oldFile->Get( Form("SumWeights%s%s", m1.c_str(),m2.c_str()) );
	  TH1F*  SumScaleWeights= (TH1F*)oldFile->Get( Form("SumScaleWeights%s%s", m1.c_str(),m2.c_str()) );
	  TH1F* SumPdfWeights = (TH1F*)oldFile->Get( Form("SumPdfWeights%s%s", m1.c_str(),m2.c_str()) );
	  TH1F* NISRJets = (TH1F*)oldFile->Get( Form("NISRJets%s%s", m1.c_str(),m2.c_str()) );
	  newFile = new TFile( Form("../../../eos/cms/store/group/phys_susy/razor/Run2Analysis/HggRazor/2016/V3p12_PhotonCorrDec06_JECSep23V3_20170219/FastsimSignal/combined/SMS-TChiWH_%s_%s_tweaked_1pb_weighted.root", m1.c_str(),m2.c_str()), "RECREATE" );
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
