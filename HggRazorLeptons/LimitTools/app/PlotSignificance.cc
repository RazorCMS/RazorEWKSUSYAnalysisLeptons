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
#include <TLine.h>
//LOCAL INCLUDES
#include "CommandLineInput.hh"

struct Sig
{
  double sigma;
  double pvalue;
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


  std::map<float, Sig> mymap;
  
  std::string fname;
  if( ifs.is_open() )
    {
      while( ifs.good() )
	{
	  ifs >> fname;
	  if ( ifs.eof() ) break;
	  std::cout << "fname: " << fname << std::endl;
	  TFile* fin = new TFile( fname.c_str(), "READ" );
	  int low  = fname.find("_m")+2;
	  int high = fname.find(".root") - low;
	  std::string mass = fname.substr( low, high );
	  float _mass = atof( mass.c_str() );
	  TTree* tree = (TTree*)fin->Get("limit");
	  double limit;
	  Sig tmpLimit;
	  tree->SetBranchAddress( "limit", &limit );
	  tree->GetEntry(0);
	  tmpLimit.sigma = limit;
	  tree->GetEntry(1);
	  tmpLimit.pvalue = limit;
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
  float sigma[npoints];
  float pval[npoints];

  int ctr = 0;
  for ( auto tmp : mymap )
    {
      //if ( tmp.second.pvalue != 0.5 ) std::cout << "mass: " << tmp.first << " pval: " << tmp.second.pvalue << std::endl;
      if ( tmp.second.pvalue == 0.0  || tmp.second.pvalue > 0.50 )
	{
	  tmp.second.sigma = 0.0;
	  tmp.second.pvalue = 0.5;
	};

      std::cout << "mass: " << tmp.first << " pval: " << tmp.second.pvalue << std::endl;
      
      x[ctr]     = tmp.first;
      sigma[ctr] = tmp.second.sigma;
      pval[ctr]  = tmp.second.pvalue;
      ctr++;
    }

  TFile* out = new TFile("out_test_significance.root", "recreate");
  TGraph* gsigma = new TGraph(npoints, x, sigma);
  TGraph* gpval = new TGraph(npoints, x, pval);
  
  TCanvas* c = new TCanvas( "c", "c", 2119, 33, 800, 700 );
  c->SetHighLightColor(2);
  c->SetFillColor(0);
  c->SetBorderMode(0);
  c->SetBorderSize(2);
  c->SetLeftMargin( leftMargin );
  c->SetRightMargin( 1.6*rightMargin );
  c->SetTopMargin( topMargin );
  c->SetBottomMargin( bottomMargin );
  c->SetFrameBorderMode(0);
  c->SetFrameBorderMode(0);

  gStyle->SetPaintTextFormat("4.3f");
  
  gpval->SetLineColor(kAzure-2);
  gpval->SetMarkerColor(kAzure-2);
  gpval->SetMarkerSize(1);
  gpval->SetMarkerStyle(20);
  gpval->SetLineWidth(3);

  gpval->SetTitle("");
  gpval->GetXaxis()->SetTitleSize(0.05);
  gpval->GetXaxis()->SetTitle("M_{G} (GeV)");
  gpval->GetYaxis()->SetTitleSize(0.05);
  //gsigma->GetYaxis()->CenterTitle(kTRUE);
  gpval->GetYaxis()->SetTitle("p_{0}");

  gpval->GetYaxis()->SetRangeUser(0.001, 0.6);
  gpval->GetXaxis()->SetRangeUser(450,3300);
  
  //gpval->Draw("APC");
  gpval->Draw("APL");

  TLegend* leg = new TLegend( 0.6, 0.27, 0.89, 0.35, NULL, "brNDC" );
  leg->SetBorderSize(0);
  leg->SetLineColor(1);
  leg->SetLineStyle(1);
  leg->SetLineWidth(1);
  leg->SetFillColor(0);
  leg->SetFillStyle(1001);
  leg->SetTextSize(0.04);
  leg->AddEntry( gpval, " J=0; observed p_{0}", "l" );
  leg->Draw();

  TLine *line = new TLine(450, 0.15865, 3400, 0.15865);
  line->SetLineStyle(2);
  line->Draw();
  TLatex latex;
  latex.SetNDC();
  latex.SetTextAngle(0);
  latex.SetTextColor(kBlack);    
  latex.SetTextFont(42);
  latex.SetTextAlign(31); 
  latex.SetTextSize(0.05);    
  latex.DrawLatex(0.99, 0.75, "1 #sigma");

  TLine *line2 = new TLine(450, 0.02275, 3400, 0.02275);
  line2->SetLineStyle(2);
  line2->Draw();
  latex.DrawLatex(0.99, 0.5, "2 #sigma");

  TLine *line3 = new TLine(450, 0.00135, 3400, 0.00135);
  line3->SetLineStyle(2);
  line3->Draw();
  latex.DrawLatex(0.99, 0.14, "3 #sigma");


  latex.DrawLatex(0.87, 0.42, "#frac{#Gamma}{M_{G}} = 1.4#times10^{-4} ");
  AddCMS(c);

  c->SetLogx();
  c->SetLogy();
  c->SaveAs("NarrowResLimit_pval_BIAS.pdf");
  c->SaveAs("NarrowResLimit_pval_BIAS.C");
  
  gsigma->Write("gSigma");
  gpval->Write("gPval");
  
  out->Close();
  return 0;
}


bool AddCMS( TCanvas* C )
{
  C->cd();
  float lumix = 0.955;
  float lumiy = 0.945;
  float lumifont = 42;
  
  float cmsx = 0.22;
  float cmsy = 0.940;
  float cmsTextFont   = 61;  // default is helvetic-bold
  float extrax = cmsx + 0.198;
  float extray = cmsy;
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
