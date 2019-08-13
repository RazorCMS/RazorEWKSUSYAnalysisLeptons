//C++
#include <iostream>
#include <fstream>
#include <map>
#include <stdlib.h>
#include <utility>
//ROOT
#include <TFile.h>
#include <TTree.h>
#include <TGraph.h>
#include <TGraphErrors.h>
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
const float bottomMargin = 0.14;

//CMS STANDARD
TString CMSText = "CMS";
TString extraText   = "";
//TString extraText   = "Preliminary";
//TString lumiText = "2.32 fb^{-1} (13 TeV)";
//TString lumiText = "35.9 fb^{-1} (13 TeV)";
TString lumiText = "77.5 fb^{-1} (13 TeV)";

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
  std::ifstream ifs ( inputList.c_str(), std::ifstream::in );//input file list
  
  //-----------------
  //xsec list
  //-----------------
  std::string xsecFile = ParseCommandLine( argc, argv, "-xsecFile=" );
  if (  xsecFile == "" )
    {
      std::cerr << "[ERROR]: please provide an inputList. Use --xsecFile=" << std::endl;
      return -1;
    }
  
  std::ifstream ifs_xsec ( xsecFile.c_str(), std::ifstream::in );//xsec file
  std::map<float, std::pair<float,float>> xsecMap;
  const float hggBF = 2.27e-03;
  if( ifs_xsec.is_open() )
    {
      float _massXS, _XS, _xsec_un;
      while( ifs_xsec.good() )
	  {
	    ifs_xsec >> _massXS >>  _XS >> _xsec_un;
	    if ( ifs_xsec.eof() ) break;
	    //std::cout << "mass: " << _massXS << " xsec: " << _XS << std::endl;
	    std::pair<float, float> mypair = std::make_pair(_XS,_xsec_un);
	    if ( xsecMap.find( _massXS ) == xsecMap.end() )
	    {
	      xsecMap[_massXS] = mypair;
	    }
	}
    }
  else
    {
      std::cout << "unable to open xsec file; please check path: " << xsecFile << std::endl;
    }

  for ( auto tmp : xsecMap )
    {
      std::cout << "mass: " << tmp.first << " xsec: " << tmp.second.first << "+/-"<< tmp.second.second << std::endl;
    }

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
          int low = fname.find("April19Limits/");
	  int high = fname.find("_Asymptotic.root");
	  std::string mass = fname.substr( low+14, high-(low+14) );
	  float _mass = atof( mass.c_str() );
	  std::cout << "mass: " << _mass << std::endl;
	  TTree* tree = (TTree*)fin->Get("limit");
	  double limit;
	  Limit tmpLimit;
	  double limitSF = 1.0;
	  tree->SetBranchAddress( "limit", &limit );
	  tree->GetEntry(0);
	  tmpLimit.exp0p025 = limit*limitSF*xsecMap[_mass].first;
	  tree->GetEntry(1);
	  tmpLimit.exp0p16 = limit*limitSF*xsecMap[_mass].first;
	  tree->GetEntry(2);
	  tmpLimit.exp0p5 = limit*limitSF*xsecMap[_mass].first;
	  tree->GetEntry(3);
	  tmpLimit.exp0p84 = limit*limitSF*xsecMap[_mass].first;
	  tree->GetEntry(4);
	  tmpLimit.exp0p975 = limit*limitSF*xsecMap[_mass].first;
	  tree->GetEntry(5);
	  tmpLimit.obs = limit*limitSF*xsecMap[_mass].first;
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
  float theory[npoints];
  float theory_up[npoints];
  float theory_down[npoints];
  
  float xp[2*npoints];
  float OneS[2*npoints];
  float TwoS[2*npoints];
   

  int ctr = 0;
  for ( auto tmp : mymap )
    {
      //if ( tmp.first >= 500 && tmp.first < 3000 ) std::cout << "mass: " << tmp.first << " expL: " << tmp.second.exp0p975 << ", obs: "
      //<< tmp.second.obs << std::endl;


      std::cout << "mass: " << tmp.first << " " << tmp.second.exp0p5 << " xsec: " << xsecMap[tmp.first].first << std::endl;
      x[ctr]      = tmp.first;
      obsL[ctr]   = tmp.second.obs;
      expL[ctr]   = tmp.second.exp0p5;
      theory[ctr] = xsecMap[tmp.first].first;//original model xsec;
      theory_up[ctr] = xsecMap[tmp.first].first+xsecMap[tmp.first].second;
      theory_down[ctr] = xsecMap[tmp.first].first-xsecMap[tmp.first].second;//original model xsec uncertainty;
      
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
  TGraph* gTheory = new TGraph(npoints, x, theory);
  TGraph* gTheory_up = new TGraph(npoints, x, theory_up);
  TGraph* gTheory_down = new TGraph(npoints, x, theory_down);
    
  
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
  c->SetLogy();

  gStyle->SetPaintTextFormat("4.3f");
  gStyle->SetLabelSize(.05, "XY");

  /*
  gTwoS->SetFillColor(kSpring-3);
  gTwoS->SetLineColor(kSpring-3);
  gOneS->SetFillColor(kSpring+10);
  gOneS->SetLineColor(kSpring+10);
  */

  gTwoS->SetFillColor(kOrange);
  gTwoS->SetLineColor(kOrange);
  gOneS->SetFillColor(kGreen+1);
  gOneS->SetLineColor(kGreen+1);
  
  gExp->SetLineWidth(3);
  gExp->SetLineStyle(2);
  //gExp->SetLineColor(kBlue);
  gObs->SetLineWidth(2);
  gObs->SetMarkerSize(0.5);
  gObs->SetMarkerStyle(20);
  gObs->SetLineWidth(3);
  
  gTheory->SetLineWidth(3);
  //gTheory->SetLineStyle(2);
  gTheory->SetLineColor(kRed);
  
  gTheory_up->SetLineWidth(3);
  gTheory_up->SetLineStyle(2);
  gTheory_up->SetLineColor(kRed);

  gTheory_down->SetLineWidth(3);
  gTheory_down->SetLineStyle(2);
  gTheory_down->SetLineColor(kRed);
  
  //gTwoS->SetLineWidth(3);
  //gTwoS->SetLineStyle(2);
  //gTwoS->SetLineColor(kBlack);
  gTwoS->SetTitle("");
  gTwoS->GetXaxis()->SetTitleSize(0.05);
  gTwoS->GetXaxis()->SetLabelOffset( 0.003);
  gTwoS->GetYaxis()->SetLabelOffset( 0.003);
  gTwoS->GetXaxis()->SetTitleOffset( 1.21);
  gTwoS->GetYaxis()->SetTitleOffset( 0.99);
  gTwoS->GetXaxis()->SetTitle("Higgsino mass m_{#tilde{#chi}^{0}_{1}} [GeV]");
  gTwoS->GetYaxis()->SetTitleSize(0.05);
  //gTwoS->GetYaxis()->CenterTitle(kTRUE);
  //gTwoS->GetYaxis()->SetTitle("95% C.L. limit #sigma(pp#rightarrow #tilde{#chi}^{0}_{2} #tilde{#chi}^{0}_{2}) (pb)");
  gTwoS->GetYaxis()->SetTitle("#sigma^{95%}_{excl} [pb]");

  //gTwoS->GetYaxis()->SetRangeUser(0,15);
  gTwoS->GetYaxis()->SetRangeUser(0,15);
  gTwoS->SetMaximum(1000);
  //gTwoS->SetMinimum(0.1); //HZ
  gTwoS->SetMinimum(0.1-0.01); //HH
  //gTwoS->GetYaxis()->SetRangeUser(0,15);
  //gTwoS->GetXaxis()->SetRangeUser(150,400);
  //gTwoS->GetXaxis()->SetRangeUser(120,450);
  gTwoS->GetXaxis()->SetLimits(125,450);
  
  gTwoS->Draw("AFC");
  gOneS->Draw("FC");
  gExp->Draw("C");
  gObs->Draw("C");
  gTheory->Draw("PC");
  gTheory_up->Draw("PC");
  gTheory_down->Draw("PC");
/*
  TLegend* leg = new TLegend( 0.51, 0.68-0.05, 0.89, 0.75-0.05, NULL, "brNDC" );
  leg->SetBorderSize(0);
  leg->SetLineColor(1);
  leg->SetLineStyle(1);
  leg->SetLineWidth(1);
  leg->SetFillColor(0);
  leg->SetFillStyle(1001);
  leg->SetTextSize(0.04);

  leg->AddEntry( gTheory, " NLO+NNL theory #pm s.d.", "l");
  leg->Draw();
 
  TLegend* leg2 = new TLegend( 0.51, 0.37-0.05, 0.89, 0.62-0.05, NULL, "brNDC" );
  leg2->SetBorderSize(0);
  leg2->SetLineColor(1);
  leg2->SetLineStyle(1);
  leg2->SetLineWidth(1);
  leg2->SetFillColor(0);
  leg2->SetFillStyle(1001);
  leg2->SetTextSize(0.04);
  //leg2->AddEntry( gObs, " Observed", "l" );
  leg2->AddEntry( gExp, " Expected", "l" );
  leg2->AddEntry( gOneS, " 68% expected", "f" );
  leg2->AddEntry( gTwoS, " 95% expected", "f" );
  
  leg2->Draw();
*/
  TLegend* leg = new TLegend( 0.51, 0.75-5*0.065-0.02, 0.85, 0.75-0.05-0.02, NULL, "brNDC" );
  leg->SetBorderSize(0);
  leg->SetLineColor(1);
  leg->SetLineStyle(1);
  leg->SetLineWidth(1);
  leg->SetFillColor(0);
  leg->SetFillStyle(1001);
  leg->SetTextSize(0.04);

  leg->AddEntry( gTheory, " NLO+NLL theory", "l");
  leg->AddEntry( gObs, " Observed limit (95% CL)", "l" );
  leg->AddEntry( gExp, " Median expected limit", "l" );
  leg->AddEntry( gOneS, " 68% expected", "f" );
  leg->AddEntry( gTwoS, " 95% expected", "f" );
  leg->Draw("SAME");

  //95% CL label
  float cmsx = 0.81;
  float cmsy = 0.63-0.05;
  float cmsSize = 0.04;
  float cmsTextFont = 41;  // default is helvetic-bold
  TLatex latex;
  latex.SetNDC();
  latex.SetTextAngle(0);
  latex.SetTextColor(kBlack);    
  latex.SetTextAlign(31); 
  latex.SetTextSize(cmsSize);    
  latex.SetTextFont(cmsTextFont);
  //latex.DrawLatex(cmsx, cmsy, "95% CL upper limits");

  TLatex latex2;
  cmsx = 0.15;
  cmsy = 0.87;
  latex2.SetNDC();
  latex2.SetTextSize(0.048);   
  latex2.SetTextFont(42);
  //HH
  latex2.DrawLatex(cmsx, cmsy, "pp #rightarrow #tilde{#chi}^{0,#pm}_{i} #tilde{#chi}^{0,#pm}_{j} #rightarrow  #tilde{#chi}^{0}_{1} #tilde{#chi}^{0}_{1} + X_{soft}; #tilde{#chi}^{0}_{1} #rightarrow H #tilde{G} (100%)");
  latex2.DrawLatex(cmsx+0.3, cmsy-0.08, "m_{#tilde{G}} = 1 GeV;  m_{#tilde{#chi}^{0}_{2}} #approx m_{#tilde{#chi}^{#pm}_{1}} #approx m_{#tilde{#chi}^{0}_{1}}");
  //HZ
  //latex2.DrawLatex(cmsx, cmsy, "pp #rightarrow #tilde{#chi}^{0,#pm}_{i} #tilde{#chi}^{0,#pm}_{j} #rightarrow  #tilde{#chi}^{0}_{1} #tilde{#chi}^{0}_{1} + X_{soft}; #tilde{#chi}^{0}_{1} #rightarrow H #tilde{G} (50%)");
  //latex2.DrawLatex(cmsx+0.51, cmsy-0.08, "#tilde{#chi}^{0}_{1} #rightarrow Z #tilde{G} (50%)");
  //latex2.DrawLatex(cmsx+0.30, cmsy-0.14, "m_{#tilde{G}} = 1GeV;  m_{#tilde{#chi}^{0}_{2}} #approx m_{#tilde{#chi}^{#pm}_{1}} #approx m_{#tilde{#chi}^{0}_{1}}");
  //1D WH
  //latex2.DrawLatex(cmsx+0.15, cmsy, "pp #rightarrow #tilde{#chi}^{#pm}_{1} #tilde{#chi}^{0}_{2} ; #tilde{#chi}^{#pm}_{1} #rightarrow W^{#pm} #tilde{#chi}^{0}_{1}, #tilde{#chi}^{0}_{2} #rightarrow H #tilde{#chi}^{0}_{1}");
  //std::cout << "hola " << latex2.GetTextFont() << std::endl;
  TLatex latex3;
  latex3.SetNDC();
  latex3.SetTextSize(0.038);   
  latex3.SetTextFont(42);
  latex2.DrawLatex(0.2, 0.66, "#bf{EWP analysis}");
  AddCMS(c);

  //c->SetLogx();
  c->SaveAs("NarrowResLimit_BIAS_fix.pdf");
  c->SaveAs("NarrowResLimit_BIAS_fix.C");
  
  gObs->GetXaxis()->SetRangeUser(0, 30);
  gObs->Write("gObs");
  gExp->GetXaxis()->SetRangeUser(0, 30);
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
  
  float cmsx = 0.25;
  float cmsy = 0.94;
  float cmsTextFont   = 61;  // default is helvetic-bold
  float extrax = cmsx +0.20;
  float extray = cmsy;
  //float extrax = cmsx + 0.078;
  //float extray = cmsy - 0.04;
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
