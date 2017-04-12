#include <iostream>
#include <fstream>

#include <TSystem.h>
#include <TDirectory.h>
#include <TTree.h>
#include <TLegend.h>
#include "TString.h"
#include <TROOT.h>
#include "TFile.h"
#include "TH1F.h"
#include "TCanvas.h"
#include "TLatex.h"
#include "TObject.h"
#include "TNamed.h"
#include "TGraphErrors.h"
#include "TGraphAsymmErrors.h"
#include "TMath.h"

#include "TBox.h"

#include "RooWorkspace.h"
#include "RooPlot.h"
#include "RooFitResult.h"
#include "RooRealVar.h"
#include "RooAbsPdf.h"
#include "RooAbsData.h"
#include "RooCurve.h"


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

  gROOT->Reset();

  TFile* fin = new TFile("TGraphFitMggEBEB.root", "READ");
  TH1F* hc   = (TH1F*)fin->Get("hp");
  //hc->SetBinErrorOption(TH1::kPoisson);
 
  fin = new TFile("2016Ref/bands_EBEB016.root", "READ");
  TGraphAsymmErrors* g = (TGraphAsymmErrors*)fin->Get("onesigma");

  const int npoints = g->GetN();
  double* y;
  y = g->GetY();

  TH1F* h = new TH1F("h", "h", 70, 230, 1630 );
  //TH1F* h = new TH1F("h", "h", 65, 330, 1630 );
  //h->SetBinErrorOption(TH1::kPoisson);
  for ( int i = 1; i <= h->GetNbinsX(); i++ )
    {
      h->SetBinContent( i, y[i-1] );
    }
  
  TFile* fout = new TFile("HistoMassEBEE.root", "RECREATE");
  
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

  /*
  TLegend* leg = new TLegend( 0.7, 0.6, 0.93, 0.89, NULL, "brNDC" );
  leg->SetBorderSize(0);
  leg->SetLineColor(1);
  leg->SetLineStyle(1);
  leg->SetLineWidth(1);
  leg->SetFillColor(0);
  leg->SetFillStyle(1001);
  leg->SetTextSize(0.04);
  leg->AddEntry( h_tmp2, " Data", "lep" );
  leg->AddEntry( dummy, " Fit model", "l" );
  leg->AddEntry( gsigma, " #pm 1 #sigma", "f" );
  leg->AddEntry( gsigma2, " #pm 2 #sigma", "f" );
  leg->Draw();
  */
  h->SetMarkerStyle(20);
  h->SetMarkerColor(kBlack);
  h->SetLineColor(kBlack);
  h->SetLineWidth(2);
  h->SetMarkerSize(2);

  hc->SetMarkerStyle(20);
  hc->SetMarkerColor(kRed);
  hc->SetLineColor(kRed);
  hc->SetLineWidth(1);
  hc->SetMarkerSize(1);
  
  h->SetStats(0);
  h->SetTitle("");
  h->SetYTitle("events / ( 20 GeV )");
  h->GetYaxis()->SetTitleSize(0.06);
  h->GetYaxis()->SetTitleOffset(0.85);
  h->SetXTitle("m_{#gamma#gamma} GeV");
  h->GetXaxis()->SetTitleSize(0.06);
  h->GetXaxis()->SetTitleOffset(0.85);
 


  TPad *pad1 = new TPad("pad1","pad1", .0, 0.31, 1., 1.);
  pad1->SetBottomMargin(0);
  pad1->SetRightMargin( rightMargin );
  pad1->SetLeftMargin( leftMargin );
  pad1->Draw();
  pad1->cd();
  
  h->Draw("E1");
  hc->Draw("same+E1");
  TLegend* leg = new TLegend( 0.7, 0.6, 0.93, 0.89, NULL, "brNDC" );
  leg->SetBorderSize(0);
  leg->SetLineColor(1);
  leg->SetLineStyle(1);
  leg->SetLineWidth(1);
  leg->SetFillColor(0);
  leg->SetFillStyle(1001);
  leg->SetTextSize(0.04);
  leg->AddEntry( h, " referemce", "lep" );
  leg->AddEntry( hc, " cross-check", "lep" );
  leg->Draw();
  
  c->cd();
  TPad *pad2 = new TPad("pad2","pad2", .0, .0, 1., 0.29);
  pad2->SetTopMargin(0.025);
  pad2->SetBottomMargin(0.3);
  pad2->SetRightMargin( rightMargin );
  pad2->SetLeftMargin( leftMargin );
  pad2->SetGridy();
  pad2->Draw();
  pad2->cd();

  //h->Sumw2();
  TH1F* ratio = new TH1F( *h );
  ratio->Divide( hc );
 
  ratio->SetMarkerStyle(20);
  ratio->SetMarkerColor(kBlue);
  ratio->SetLineColor(kBlue);
  ratio->SetLineWidth(2);
  ratio->SetMarkerSize(1);
  ratio->SetStats(0);
  ratio->SetTitle("");

  ratio->GetYaxis()->SetRangeUser(0.8,1.2);
  ratio->SetYTitle("ref./cross-check");
  ratio->GetYaxis()->SetLabelSize(0.08);
  ratio->GetXaxis()->SetLabelSize(0.12);
  ratio->GetYaxis()->SetTitleSize(0.09);
  ratio->GetYaxis()->SetTitleOffset(0.5);
  ratio->SetXTitle("m_{#gamma#gamma} GeV");
  ratio->GetXaxis()->SetTitleSize(0.15);
  ratio->GetXaxis()->SetTitleOffset(0.85);
  ratio->Draw("");

  pad1->SetLogy();
  pad1->Update();
  c->SaveAs("dataReferenceEBEE_Fit.pdf");
  c->SaveAs("dataReferenceEBEE_Fit.png");
  c->SaveAs("dataReferenceEBEE_Fit.C");
  
  h->Write("mass");
  hc->Write("mass_caltech");
  fout->Close();
  
  return 0;
};

bool AddCMS( TCanvas* C )
{
  C->cd();
  float lumix = 0.955;
  float lumiy = 0.945;
  float lumifont = 42;
  
  float cmsx = 0.32;
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

