//C++
#include <iostream>
#include <fstream>
#include <map>
#include <stdlib.h>
//ROOT
#include <TFile.h>
#include <TTree.h>
#include <TGraph.h>
#include <TAxis.h>
#include <TCanvas.h>
#include <TStyle.h>
#include <TLatex.h>
#include <TLegend.h>
//LOCAL INCLUDES
#include "CommandLineInput.hh"

struct Limit
{
  double obs;
  double exp0p025;
  double exp0p16;
  double exp0p5;
  double exp0p84;
  double exp0p975;
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
TString lumiText = "12.92 fb^{-1} (13 TeV)";

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


  std::map<float, Limit> mymap;
  
  std::string fname;
  if( ifs.is_open() )
    {
      while( ifs.good() )
	{
	  ifs >> fname;
	  if ( ifs.eof() ) break;
	  //	  std::cout << "fname: " << fname << std::endl;
	  TFile* fin = new TFile( fname.c_str(), "READ" );
	  if ( fin->IsZombie() ) continue;
	  int low  = fname.find(".mH")+3;
	  int high = fname.find(".root") - low;
	  std::string mass = fname.substr( low, high );
	  float _mass = atof( mass.c_str() );
	  TTree* tree = (TTree*)fin->Get("limit");
	  double limit;
	  Limit tmpLimit;
	  tree->SetBranchAddress( "limit", &limit );
	  tree->GetEntry(0);
	  tmpLimit.exp0p025 = limit*1.;
	  tree->GetEntry(1);
	  tmpLimit.exp0p16 = limit*1.;
	  tree->GetEntry(2);
	  tmpLimit.exp0p5 = limit*1.;
	  tree->GetEntry(3);
	  tmpLimit.exp0p84 = limit*1.;
	  tree->GetEntry(4);
	  tmpLimit.exp0p975 = limit*1.;
	  tree->GetEntry(5);
	  tmpLimit.obs = limit*1.;
	  //std::cout << "mass: " << mass << "-> " << exp0p025 << " " << exp0p16 << " " << exp0p5 << " " << exp0p84
	  //<< " " << exp0p975 << " " << obs << std::endl;
	  if ( mymap.find( _mass ) == mymap.end() )
	    {
	      mymap[_mass] = tmpLimit;
	    }
	  delete fin;
	}
    }
  else
    {
      std::cerr << "[ERROR] can't open file " << inputList << std::endl;
    }

  int npoints = mymap.size();
  float x[npoints];
  float expL[npoints];
  float obsL[npoints];
  
  float xp[2*npoints];
  float OneS[2*npoints];
  float TwoS[2*npoints];
   

  int ctr = 0;
  for ( auto tmp : mymap )
    {
      if ( tmp.first >= 500 && tmp.first < 3000 ) std::cout << "mass: " << tmp.first << " expL: " << tmp.second.exp0p975 << ", obs: "
							   << tmp.second.obs << std::endl;
      x[ctr]    = tmp.first;
      obsL[ctr] = tmp.second.obs;
      expL[ctr] = tmp.second.exp0p5;
      
      xp[ctr] = tmp.first;
      xp[2*npoints-(ctr+1)] = tmp.first;     

      OneS[ctr] = tmp.second.exp0p16;
      OneS[2*npoints-(ctr+1)] = tmp.second.exp0p84;

      TwoS[ctr] = tmp.second.exp0p025;
      TwoS[2*npoints-(ctr+1)] = tmp.second.exp0p975;
       
      ctr++;
    }

  TFile* out = new TFile("out_test.root", "recreate");
  TGraph* gObs = new TGraph(npoints, x, obsL);
  TGraph* gExp = new TGraph(npoints, x, expL);
  TGraph* gOneS = new TGraph(2*npoints, xp, OneS);
  TGraph* gTwoS = new TGraph(2*npoints, xp, TwoS);

  TCanvas* c = new TCanvas( "c", "c", 2119, 33, 800, 700 );
  c->SetHighLightColor(2);
  c->SetFillColor(0);
  c->SetBorderMode(0);
  c->SetBorderSize(2);
  c->SetLeftMargin( leftMargin );
  c->SetRightMargin( rightMargin );
  c->SetTopMargin( topMargin );
  c->SetBottomMargin( bottomMargin );
  c->SetFrameBorderMode(0);
  c->SetFrameBorderMode(0);

  gStyle->SetPaintTextFormat("4.3f");
  
  gTwoS->SetFillColor(kSpring-3);
  gTwoS->SetLineColor(kSpring-3);
  gOneS->SetFillColor(kSpring+10);
  gOneS->SetLineColor(kSpring+10);
  gExp->SetLineWidth(3);
  gExp->SetLineStyle(2);
  gObs->SetLineWidth(2);
  gObs->SetMarkerSize(0.5);
  gObs->SetMarkerStyle(20);

  gTwoS->SetTitle("");
  gTwoS->GetXaxis()->SetTitleSize(0.05);
  gTwoS->GetXaxis()->SetTitle("M_{G} (GeV)");
  gTwoS->GetYaxis()->SetTitleSize(0.05);
  gTwoS->GetYaxis()->CenterTitle(kTRUE);
  gTwoS->GetYaxis()->SetTitle("95% C.L. limit #sigma(pp#rightarrowG#rightarrow#gamma#gamma) (fb)");

  //gTwoS->GetYaxis()->SetRangeUser(0,20.6);
  gTwoS->GetYaxis()->SetRangeUser(0,10.6);
  gTwoS->GetXaxis()->SetRangeUser(450,3300);
  
  gTwoS->Draw("AFL");
  gOneS->Draw("FL");
  gExp->Draw("PL");
  gObs->Draw("PL");

  TLegend* leg = new TLegend( 0.6, 0.58, 0.89, 0.89, NULL, "brNDC" );
  leg->SetBorderSize(0);
  leg->SetLineColor(1);
  leg->SetLineStyle(1);
  leg->SetLineWidth(1);
  leg->SetFillColor(0);
  leg->SetFillStyle(1001);
  leg->SetTextSize(0.04);
  leg->AddEntry( gExp, " Expected limit", "l" );
  leg->AddEntry( gOneS, " #pm1 #sigma", "f" );
  leg->AddEntry( gTwoS, " #pm2 #sigma", "f" );
  leg->AddEntry( gObs, " Observed limit", "l" );
  leg->Draw();

  AddCMS(c);

  c->SetLogx();
  c->SaveAs("NarrowResLimit_BIAS_fix.pdf");
  c->SaveAs("NarrowResLimit_BIAS_fix.C");
  
  gObs->GetXaxis()->SetRangeUser(0, 30);
  gObs->Write("gObs");
  gExp->Write("gExp");
  gOneS->Write("gOneS");
  gTwoS->Write("gTwoS");
  
  out->Close();
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
