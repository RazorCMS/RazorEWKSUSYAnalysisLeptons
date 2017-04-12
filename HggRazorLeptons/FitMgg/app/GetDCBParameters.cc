//C++
#include <iostream>
#include <fstream>
#include <string>
//ROOT
#include <TFile.h>
#include <TString.h>
//ROOFIT
#include <RooWorkspace.h>
#include <RooRealVar.h>

int main()
{
  std::ifstream ifs( "listGluGlu.txt", std::ifstream::in );
  
  if ( ifs.is_open() )
    {
      std::string fname;
      TFile* fin;
      while ( ifs.good() )
	{
	  ifs >> fname;
	  int low   = fname.find("M-")+2;
	  int high  = fname.find(".root");
	  std::string mass = fname.substr( low, high-low );
	  if ( ifs.eof() ) break;
	  //std::cout << "fname: " << fname << std::endl;
	  fin = new TFile( fname.c_str() , "READ" );
	  RooWorkspace* ws = (RooWorkspace*)fin->Get("w_sFit");
	  //ws->Print();
	  double mu     = ws->var("Signal_DCB_muCB")->getVal();
	  double sigma  = ws->var("Signal_DCB_sigmaCB")->getVal();
	  double alpha1 = ws->var("Signal_DCB_alpha1")->getVal();
	  double n1     = ws->var("Signal_DCB_n1")->getVal();
	  double alpha2 = ws->var("Signal_DCB_alpha2")->getVal();
	  double n2     = ws->var("Signal_DCB_n2")->getVal();
	  std::cout << mass << " " << mu << " " << sigma << " " << alpha1 << " " << n1 << " " << alpha2 << " " << n2 << std::endl;
	  delete ws;
	}
    }
  else
    {
      std::cout << "[INFO]: could not open txt file" << std::endl;
    }
  
  return 0;
}
