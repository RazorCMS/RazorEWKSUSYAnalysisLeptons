#include <iostream>
#include <vector>
//ROOT
#include <TFile.h>
#include <TString.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TLatex.h>
#include <TTree.h>
#include <TGraph.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TString.h>
#include <TDirectory.h>


const float lumi = 2.3;
//Axis
const float axisTitleSize = 0.06;
const float axisTitleOffset = .8;

const float axisTitleSizeRatioX   = 0.18;
const float axisLabelSizeRatioX   = 0.12;
const float axisTitleOffsetRatioX = 0.84;

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
TString lumiText = "2.3 fb^{-1} (13 TeV)";

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
void CreateROC( TString fnSignal, TString fnBkg, float valCut )
{

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
  
  TString cut = "weight*(mGammaGamma > 103. && mGammaGamma < 160. && pho1passIso == 1 && pho2passIso == 1 && pho1passEleVeto == 1 && pho2passEleVeto == 1 && abs(pho1Eta) <1.48 && abs(pho2Eta)<1.48 && (pho1Pt>40||pho2Pt>40)  && pho1Pt> 25. && pho2Pt>25.)";
  
  //Signal ROOT file
  TFile* fs = new TFile( fnSignal, "READ");
  assert( fs );
  //Signal Tree
  TTree* ts = (TTree*)fs->Get("HggRazor");

  //sigmaMoverM
  ts->Draw("sigmaMoverM>>sMoverM(500,0, 0.1)", cut);
  TH1F* h_sMoverM = (TH1F*)gDirectory->Get("sMoverM");
  h_sMoverM->Scale( 1./h_sMoverM->Integral() );
  h_sMoverM->Draw();
  
  //2dsigmaEoverE
  ts->Draw("pho1sigmaEOverE:pho2sigmaEOverE>>s2dCut(1000, 0, 0.2, 1000, 0, 0.2)", cut);
  TH2F* h_s2dCut  = (TH2F*)gDirectory->Get("s2dCut");
  h_s2dCut->Scale( 1./h_s2dCut->Integral() );
  
  
  //Bkg ROOT file
  TFile* fb = new TFile( fnBkg, "READ");
  assert( fb );
  //Bkg Tree
  TTree* tb = (TTree*)fb->Get("HggRazor");
  //sigmaMoverM
  tb->Draw("sigmaMoverM>>sMoverM_bkg(500,0, 0.1)", cut);
  TH1F* h_sMoverM_bkg = (TH1F*)gDirectory->Get("sMoverM_bkg");
  h_sMoverM_bkg->Scale( 1./h_sMoverM_bkg->Integral() );
  h_sMoverM_bkg->Draw();
  //2dsigmaEoverE
  tb->Draw("pho1sigmaEOverE:pho2sigmaEOverE>>bkg2dCut(1000, 0, 0.2, 1000, 0, 0.2)", cut);
  TH2F* h_bkg2dCut  = (TH2F*)gDirectory->Get("bkg2dCut");
  h_bkg2dCut->Scale( 1.0/h_bkg2dCut->Integral() );
  
  
  const int npoints = 200;
  float _seff[npoints], _bkgR[npoints];
  
  //------------------------
  //SigmaMoverM ROC
  //------------------------
  float step = 0.10/500.00;
  float cutStep = valCut/npoints;
  for ( int j = 0; j < npoints; j++)
    {
      int bins = cutStep*j/step;
      float _signalEff = 0;
      float _bkgEff    = 0;
      for ( int i = 1; i <= bins; i++ )
	{
	  //std::cout << "sMoverM: " << (i-1)*step << ", bc: " << h_sMoverM->GetBinContent( i ) << std::endl;
	  _signalEff += h_sMoverM->GetBinContent( i );
	  _bkgEff    += h_sMoverM_bkg->GetBinContent( i );
	}
      _seff[j]   = _signalEff;
      _bkgR[j]   = _bkgEff;
      std::cout << "bin: " << bins << " cut values: " << cutStep*j << " signalEff: " << _seff[j] << " bkgRej: " << 1-_bkgR[j] << std::endl;
    }

  //----------------------------------
  //pho1SigmaEoverE && pho2SigmaEoverE
  //----------------------------------
  float _seff2d[npoints], _bkgR2d[npoints];
  float _seffN[npoints], _bkgN[npoints];//slope 1 line
  step = 0.20/1000.00;//binwidth
  valCut = 0.06;
  cutStep = valCut/npoints;//simaEoverE real step size
  float slope1Step = 1.0/npoints;
  for ( int j = 0; j < npoints; j++)
    {
      _seffN[j] =  _bkgN[j] = slope1Step*j;
      int bins = cutStep*j/step;//bin to be summed
      std::cout << bins << " sigmaMoveM: " << cutStep*j << ", signalEff : " << h_s2dCut->Integral(1,bins, 1, bins)
		<< " bkgRejection: " << 1. - h_bkg2dCut->Integral(1,bins, 1, bins) << std::endl;
      if( j != 0 )
	{
	  _seff2d[j] = h_s2dCut->Integral(1,bins, 1, bins);
	  _bkgR2d[j] = h_bkg2dCut->Integral(1,bins, 1, bins);
	}
      else
	{
	  _seff2d[j] = 0;
	  _bkgR2d[j] = 0;
	}
    }
  
  TGraph* g = new TGraph(npoints, _bkgR, _seff );
  g->SetLineColor(kRed);
  g->SetLineWidth( 2 );
  g->GetXaxis()->SetTitle("Bkg. Eff");
  g->GetYaxis()->SetTitle("Sig. Eff");
  g->SetTitle("");
  g->GetYaxis()->SetTitleSize( 0.05 );
  g->GetXaxis()->SetTitleSize( 0.05 );
  g->GetYaxis()->SetLabelSize( 0.04 );
  g->GetXaxis()->SetLabelSize( 0.04 );
  g->GetXaxis()->SetTitleOffset(1.1);
  g->GetYaxis()->SetTitleOffset(1.1);
  g->Draw("AC");
  //h_bkg2dCut->Draw("colz");
  TGraph* g2 = new TGraph(npoints, _bkgR2d, _seff2d );
  g2->SetLineColor( kBlue );
  g2->SetLineWidth( 2 );
  g2->Draw("same");

  TGraph* g3 = new TGraph(npoints, _bkgN, _seffN );
  g3->SetLineColor( kGreen );
  g3->SetLineWidth( 2 );
  g3->SetLineStyle( 2 );
  g3->Draw("same");

  TLegend *leg = new TLegend(0.7, 0.5, 0.85, 0.65, NULL,"brNDC");
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetLineColor(1);
  leg->SetLineStyle(1);
  leg->SetLineWidth(1);
  leg->SetFillColor(0);
  leg->SetFillStyle(1001);
  leg->AddEntry(g, "#sigma_{M}/M" ,"l");
  leg->AddEntry(g2, "#sigma_{E}/E" ,"l");
  leg->Draw();
  
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
  c->SaveAs("roc_curve.pdf");
  c->SaveAs("roc_curve.png");
  c->SaveAs("roc_curve.C");
  //Master ROOT file
  TFile* fout = new TFile("test_out.root", "RECREATE");
  
  h_sMoverM->Write();
  h_sMoverM_bkg->Write();
  g->Write("sigmaMoveM_roc");
  fout->Close();
};
