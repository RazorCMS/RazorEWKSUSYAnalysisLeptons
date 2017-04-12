#ifndef TCHAIN_TOOLS_HH
#define TCHAIN_TOOLS_HH 1
//C++ INCLUDES
#include <iostream>
#include <string>
//ROOT INCLUDES
#include <TChain.h>

//Add a list of root files to chain
bool AddTChain( TChain* chain, std::string fileList );
//compute scale factor according to lumi*xsec/ngen
float GetXsecSF( float lumi , float xsec, double ngen );
//Add scale factor branch to TChain
bool AddSfBranch( TChain* chain, float sf );
//Add scale factor branch to TTree
bool AddSfBranch( TTree* tree, float sf );
TTree* CloneAndAddSF( TTree* tree, float sf );

#endif
