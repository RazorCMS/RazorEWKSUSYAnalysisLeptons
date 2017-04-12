//C++ INCLUDES
#include <fstream>
//ROOT INCLUDES
#include <TBranch.h>
//LOCAL INCLUDES
#include "TChainTools.hh"

bool AddTChain( TChain* chain, std::string fileList )
{
  std::ifstream ifs ( fileList.c_str(), std::fstream::in );
  std::string tmpRootFile;
  if( ifs.is_open() )
    {
      while( ifs.good() )
	{
	  ifs >> tmpRootFile;
	  if ( ifs.eof() ) break;
	  if ( tmpRootFile.at( 0 ) == '#' )
	    {
	      std::cout << "[INFO]: skipping-> " << tmpRootFile << std::endl;
	      continue;
	    }
	  std::cout << "[INFO]: chaininig-> " << tmpRootFile << std::endl;
	  chain->Add( tmpRootFile.c_str() );
	}
    }
  else
    {
      std::cerr << "[ERROR]: Unable to open file-> " << fileList << std::endl;
      return false;
    }
  return true;
};

float GetXsecSF( float lumi , float xsec, double ngen )
{
  return lumi*xsec/ngen;
};

bool AddSfBranch( TChain* chain, float sf )
{
  if ( chain == NULL )
    {
      std::cerr << "[ERROR]: NULL TChain" << std::endl;
      return false;
    }
  // A d d i n g   B r a n c h
  //--------------------------
  TBranch* b = chain->Branch("xsecSF",&sf,"xsecSF/F");
  long long nentries = chain->GetEntries();
  for ( int i = 0; i < nentries; i++ )
    {
      chain->GetEntry(i);
      b->Fill();
    }
  chain->Print();
  return true;
};

bool AddSfBranch( TTree* tree, float sf )
{
  if ( tree == NULL )
    {
      std::cerr << "[ERROR]: NULL TTree" << std::endl;
      return false;
    }
  // A d d i n g   B r a n c h
  //--------------------------
  TBranch* b = tree->Branch("xsecSF",&sf,"xsecSF/F");
  long long nentries = tree->GetEntries();
  for ( int i = 0; i < nentries; i++ )
    {
      tree->GetEntry(i);
      b->Fill();
    }
  //tree->Print();
  return true;
};

TTree* CloneAndAddSF( TTree* tree, float sf )
{
  if ( tree == NULL )
    {
      std::cerr << "[ERROR]: NULL TTree" << std::endl;
      return NULL;
    }
  // A d d i n g   B r a n c h
  //--------------------------
  TTree* newtree = tree->CloneTree(0);
  TBranch* b = newtree->Branch("xsecSF",&sf,"xsecSF/F");
  long long nentries = tree->GetEntries();
  for ( int i = 0; i < nentries; i++ )
    {
      tree->GetEntry(i);
      newtree->Fill();
    }
  //tree->Print();
  return newtree;
};
