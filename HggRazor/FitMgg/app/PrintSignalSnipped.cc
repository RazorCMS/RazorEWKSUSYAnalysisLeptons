//C++
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <stdlib.h>
#include <algorithm>

//ROOT
#include <TFile.h>
#include <TTree.h>
#include <TGraph.h>
#include <TAxis.h>
#include <TCanvas.h>
#include <TStyle.h>
#include <TLatex.h>
#include <TLegend.h>
#include <TSystem.h>
#include <RooWorkspace.h>
#include <RooRealVar.h>
//LOCAL INCLUDES
#include "CommandLineInput.hh"

struct DSCB
{
  double mu;
  double sigma;
  double n1;
  double n2;
  double a1;
  double a2;
};


const float lumi = 5;
//Axis
const float axisTitleSize = 0.06;
const float axisTitleOffset = .8;

const float axisTitleSizeRatioX   = 0.18;
const float axisLabelSizeRatioX   = 0.12;
const float axisTitleOffsetRatioX = 0.94;

const float axisTitleSizeRatioY   = 0.15;
const float axisLabelSizeRatioY   = 0.108;
const float axisTitleOffsetRatioY = 0.32;

//Margins
const float leftMargin   = 0.12;
const float rightMargin  = 0.05;
const float topMargin    = 0.07;
const float bottomMargin = 0.12;

//CMS STANDARD
TString CMSText = "CMS";
TString extraText   = "Preliminary";
//TString lumiText = "2.32 fb^{-1} (13 TeV)";
TString lumiText = "2.69 fb^{-1} (13 TeV)";

bool AddCMS( TCanvas* C );

int main( int argc, char** argv )
{

  //-----------------
  //Input File List
  //-----------------
  std::string inputList = ParseCommandLine( argc, argv, "-inputList=" );
  if (  inputList == "" )
    {
      std::cerr << "[ERROR]: please provide an inputList. Use --inputList=" << std::endl;
      return -1;
    }

  std::ifstream ifs ( inputList.c_str(), std::ifstream::in );


  gSystem->Load("include/libCustomPdfs.so");
  std::map<float, DSCB> mymap;
  std::vector<float> mymass;
  
  std::string fname;
  if( ifs.is_open() )
    {
      while( ifs.good() )
	{
	  ifs >> fname;
	  if ( ifs.eof() ) break;
	  //std::cout << "fname: " << fname << std::endl;
	  TFile* fin = new TFile( fname.c_str(), "READ" );
	  int low  = fname.find("_M-")+3;
	  int high = fname.find(".root") - low;
	  std::string mass = fname.substr( low, high );
	  float _mass = atof( mass.c_str() );
	  RooWorkspace* w = (RooWorkspace*)fin->Get("w_sFit");
	  DSCB tmpDSCB;
	  tmpDSCB.mu    = w->var("Signal_DCB_muCB")->getVal();
	  tmpDSCB.sigma = w->var("Signal_DCB_sigmaCB")->getVal();
	  tmpDSCB.n1    = w->var("Signal_DCB_n1")->getVal();
	  tmpDSCB.n2    = w->var("Signal_DCB_n2")->getVal();
	  tmpDSCB.a1    = w->var("Signal_DCB_alpha1")->getVal();
	  tmpDSCB.a2    = w->var("Signal_DCB_alpha2")->getVal();
	  
	  
	  //std::cout << "mass: " << mass << "-> " << tmpDSCB.mu << " " << tmpDSCB.sigma << " " << tmpDSCB.n1 << " " << tmpDSCB.n2 
	  //<< " " << tmpDSCB.a1 << " " << tmpDSCB.a2 << std::endl;
	  if ( mymap.find( _mass ) == mymap.end() )
	    {
	      mymap[_mass] = tmpDSCB;
	      mymass.push_back(_mass);
	    }
	  delete fin;
	}
    }
  else
    {
      std::cerr << "[ERROR] can't open file " << inputList << std::endl;
    }

 
  auto sortFloat = []( float a, float b ){ return a < b ? true : false; };
  std::sort( mymass.begin() , mymass.end(), sortFloat);
  int npoints = mymass.size();

  //Loop for mu;
  //TString className = "double RooIntepolateDSCB_W0p014_Spin0_EBEB_2016";
  TString className = "double RooIntepolateDSCB_W0p014_Spin0_EBEE_2016";
  std::cout << className << "::getMean( double m ) const\n{\n";
  for ( int i = 0; i < npoints; i++ )
    {
      float slope = (mymap[mymass[i+1]].mu - mymap[mymass[i]].mu)/(mymass[i+1] - mymass[i]);
      if ( i != npoints-1)
	{
	  std::cout << "\tif( m >=  " << mymass[i] << " && m < " << mymass[i+1] << " ) ";
	  std::cout << "return " << slope << "*(m-" << mymass[i] << ") + " << mymap[mymass[i]].mu << ";\n";
	}
      else
	{
	  std::cout << "\treturn 0;\n};\n\n";
	}
    }


  //Loop for sigma
  std::cout << className << "::getSigma( double m ) const\n{\n";
  for ( int i = 0; i < npoints; i++ )
    {
      float slope = (mymap[mymass[i+1]].sigma - mymap[mymass[i]].sigma)/(mymass[i+1] - mymass[i]);
      if ( i != npoints-1)
	{
	  std::cout << "\tif( m >=  " << mymass[i] << " && m < " << mymass[i+1] << " ) ";
	  std::cout << "return " << slope << "*(m-" << mymass[i] << ") + " << mymap[mymass[i]].sigma << ";\n";
	}
      else
	{
	  std::cout << "\treturn 0;\n};\n\n";
	}
    }

  //-----------
  //Loop for n1
  //-----------
  std::cout << className << "::getN1( double m ) const\n{\n";
  for ( int i = 0; i < npoints; i++ )
    {
      float slope = (mymap[mymass[i+1]].n1 - mymap[mymass[i]].n1)/(mymass[i+1] - mymass[i]);
      if ( i != npoints-1)
	{
	  std::cout << "\tif( m >=  " << mymass[i] << " && m < " << mymass[i+1] << " ) ";
	  std::cout << "return " << slope << "*(m-" << mymass[i] << ") + " << mymap[mymass[i]].n1 << ";\n";
	}
      else
	{
	  std::cout << "\treturn 0;\n};\n\n";
	}
    }

  //-----------
  //Loop for n2
  //-----------
  std::cout << className << "::getN2( double m ) const\n{\n";
  for ( int i = 0; i < npoints; i++ )
    {
      float slope = (mymap[mymass[i+1]].n2 - mymap[mymass[i]].n2)/(mymass[i+1] - mymass[i]);
      if ( i != npoints-1)
	{
	  std::cout << "\tif( m >=  " << mymass[i] << " && m < " << mymass[i+1] << " ) ";
	  std::cout << "return " << slope << "*(m-" << mymass[i] << ") + " << mymap[mymass[i]].n2 << ";\n";
	}
      else
	{
	  std::cout << "\treturn 0;\n};\n\n";
	}
    }
  
  //-----------
  //Loop for a1
  //-----------
  std::cout << className << "::getAlpha1( double m ) const\n{\n";
  for ( int i = 0; i < npoints; i++ )
    {
      float slope = (mymap[mymass[i+1]].a1 - mymap[mymass[i]].a1)/(mymass[i+1] - mymass[i]);
      if ( i != npoints-1)
	{
	  std::cout << "\tif( m >=  " << mymass[i] << " && m < " << mymass[i+1] << " ) ";
	  std::cout << "return " << slope << "*(m-" << mymass[i] << ") + " << mymap[mymass[i]].a1 << ";\n";
	}
      else
	{
	  std::cout << "\treturn 0;\n};\n\n";
	}
    }

  //-----------
  //Loop for a2
  //-----------
  std::cout << className << "::getAlpha2( double m ) const\n{\n";
  for ( int i = 0; i < npoints; i++ )
    {
      float slope = (mymap[mymass[i+1]].a2 - mymap[mymass[i]].a2)/(mymass[i+1] - mymass[i]);
      if ( i != npoints-1)
	{
	  std::cout << "\tif( m >=  " << mymass[i] << " && m < " << mymass[i+1] << " ) ";
	  std::cout << "return " << slope << "*(m-" << mymass[i] << ") + " << mymap[mymass[i]].a2 << ";\n";
	}
      else
	{
	  std::cout << "\treturn 0;\n};\n\n";
	}
    }

  return 0;
}


bool AddCMS( TCanvas* C )
{
  C->cd();
  float lumix = 0.955;
  float lumiy = 0.945;
  float lumifont = 42;
  
  float cmsx = 0.28;
  float cmsy = 0.875;
  float cmsTextFont   = 61;  // default is helvetic-bold
  float extrax = cmsx + 0.078;
  float extray = cmsy - 0.04;
  float extraTextFont = 52;  // default is helvetica-italics
  // ratio of "CMS" and extra text size
  float extraOverCmsTextSize  = 0.76;
  float cmsSize = 0.06;
  TLatex latex;
  latex.SetNDC();
  latex.SetTextAngle(0);
  latex.SetTextColor(kBlack);    
  float extraTextSize = extraOverCmsTextSize*cmsSize;
  latex.SetTextFont(lumifont);
  latex.SetTextAlign(31); 
  latex.SetTextSize(cmsSize);    
  latex.DrawLatex(lumix, lumiy,lumiText);

  latex.SetTextFont(cmsTextFont);
  latex.SetTextAlign(31); 
  latex.SetTextSize(cmsSize);
  latex.DrawLatex(cmsx, cmsy, CMSText);
   
  latex.SetTextFont(extraTextFont);
  latex.SetTextAlign(31); 
  latex.SetTextSize(extraTextSize);
  latex.DrawLatex(extrax, extray, extraText);
  return true;
};
