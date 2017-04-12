#include <iostream>

#include <TSystem.h>
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

  TString fname = "EBEB/HggRazorWorkspace_EBEB_m750.root";
  bool blind = false;
  bool isEBEB = false;
  double min = 230.;
  double max = 1630.;
  
  gROOT->Reset();
  gSystem->Load("include/libCustomPdfs.so");
  TFile* fin = new TFile( fname, "READ");
  RooWorkspace *ws  = (RooWorkspace*)fin->Get("w_sb");
  RooFitResult* res = (RooFitResult*)ws->obj("BkgOnlyFitResult");


  TFile* fout = new TFile("TGraphFitMggEBEB.root", "RECREATE");
  TCanvas* cv = new TCanvas( "cv", "cv", 2119, 33, 800, 700 );
  cv->SetHighLightColor(2);
  cv->SetFillColor(0);
  cv->SetBorderMode(0);
  cv->SetBorderSize(2);
  cv->SetLeftMargin( leftMargin );
  cv->SetRightMargin( rightMargin );
  cv->SetTopMargin( topMargin );
  cv->SetBottomMargin( bottomMargin );
  cv->SetFrameBorderMode(0);
  cv->SetFrameBorderMode(0);

    
  RooRealVar * mass = ws->var("mGammaGamma_EBEB");
  mass->setRange("all", min, max);
  mass->setBins(70);
  mass->setRange("blind", 700, 800);
  mass->setRange("low", min, 700);
  mass->setRange("high", 800, max);
  
  mass->setUnit("GeV");
  mass->SetTitle("m_{#gamma#gamma}");
  
  RooAbsPdf * pdf = ws->pdf("Bkg_fit_HMDiphoton_HMDiphoton_ext_HMDiphoton");
  //RooPlot *plot = mass->frame(min,max,max-min);
  //RooPlot *plot = mass->frame(min,max, 70);
  RooPlot *plot = mass->frame(70);
  plot->SetTitle("");
  
  RooAbsData* data = ws->data("data")->reduce(Form("mGammaGamma_EBEB > %f && mGammaGamma_EBEB < %f",min,max));
  //RooAbsData* data = ws->data("data")->reduce(Form("mGammaGamma_EBEB > %f && mGammaGamma_EBEB < %f",320,max));
  double nTot = data->sumEntries();
  double nTot2 = ws->data("data")->reduce( Form("mGammaGamma_EBEB > %f && mGammaGamma_EBEB < %f", 330., max) )->sumEntries();
  std::cout << "nTot2: " << nTot2 << std::endl;
  
  if( blind ) data = data->reduce("mGammaGamma_EBEB < 700 || mGammaGamma_EBEB > 800");
  double nBlind = data->sumEntries();
  double norm = nTot/nBlind; //normalization for the plot
  
  data->plotOn( plot, RooFit::Invisible() );
  pdf->plotOn( plot, RooFit::NormRange( "all" ), RooFit::Range("all"), RooFit::LineWidth(0.1) );
  plot->SetName("myCurve");
  plot->Print();

  TH1F* h_tmp = new TH1F("h", "_h", 70, min, max);
  TH1F* h_tmp2 = new TH1F("h2", "_h2", 70, min, max);
  TH1F* h_tmp3 = new TH1F("h3", "_h3", 70, min, max);
  h_tmp->SetBinErrorOption(TH1::kPoisson);
  h_tmp2->SetBinErrorOption(TH1::kPoisson);
  data->fillHistogram( h_tmp, *mass);
  h_tmp2->SetLineColor(kBlack);
  h_tmp2->SetMarkerColor(kBlack);
  h_tmp2->SetMarkerStyle(20);
  //h_tmp->SetLineWidth(2);
  h_tmp2->SetStats(0);
  h_tmp3->SetLineColor(kBlack);
  h_tmp3->SetMarkerColor(kBlack);
  h_tmp3->SetMarkerStyle(20);
  //h_tmp->SetLineWidth(2);
  h_tmp3->SetStats(0);
  h_tmp3->SetTitle("");
  for ( int i = 1; i <= h_tmp->GetNbinsX(); i++ )
    {
      h_tmp2->SetBinContent(i,h_tmp->GetBinContent(i));
      h_tmp3->SetBinContent(i,h_tmp->GetBinContent(i));
      if( h_tmp3->GetBinContent(i) == 0.0 )
	{
	  h_tmp3->SetBinError(i,1.84); 
	  h_tmp3->SetBinContent(i,0.000001);
	  }
      else
	{
	  h_tmp3->SetBinError(i,0);
	  h_tmp3->SetBinContent(i,0);
	}
      
    }

 
  //ws->var("mGammaGamma_EBEB")->setRange(min,max);
 
  //add the fix error band
  RooCurve* c = plot->getCurve("Bkg_fit_HMDiphoton_HMDiphoton_ext_HMDiphoton_Norm[mGammaGamma_EBEB]_Range[all]_NormRange[all]");
  const int Nc = c->GetN();
  std::cout << "===================" << std::endl;
  std::cout << "-->" << Nc << std::endl;
  //TGraphErrors errfix(Nc);
  //TGraphErrors errfix2(Nc);
  TGraphAsymmErrors* errfix  = new TGraphAsymmErrors(Nc);
  TGraphAsymmErrors* errfix2 = new TGraphAsymmErrors(Nc);

  double sigma[2*Nc];
  double sigma2[2*Nc];
  double xp[2*Nc];
  Double_t *x = c->GetX();
  Double_t *y = c->GetY();
  double NtotalFit = ws->var("Bkg_fit_HMDiphoton_HMDiphoton_ext_Nbkg")->getVal();
  std::cout << "ndata: " << nTot << ", nFit: " << NtotalFit << std::endl;
  ws->var("mGammaGamma_EBEB")->setRange(230,max);
  //ws->var("mGammaGamma_EBEE")->setRange(330,max);
  TH1F* hp = (TH1F*)pdf->createHistogram("mGammaGamma_EBEB", 70);
  //TH1F* hp = (TH1F*)pdf->createHistogram("mGammaGamma_EBEE", 65);
  hp->Scale( NtotalFit );
  
  for( int i = 0; i < Nc; i++ )
    {
      errfix->SetPoint(i,x[i],y[i]);
      errfix2->SetPoint(i,x[i],y[i]);
      xp[i] = x[i];
      xp[2*Nc-(i+1)] = x[i];
      mass->setVal(x[i]);
      //std::cout << x[i] << " " << y[i] << std::endl; 
      double shapeErr = pdf->getPropagatedError(*res)*NtotalFit;
      double statUn = y[i]/sqrt(NtotalFit);
      double totalErr = TMath::Sqrt( shapeErr*shapeErr + statUn*statUn );
      //std::cout << x[i] << " " << y[i] << " " << NtotalFit << " " << shapeErr << " " << statUn << std::endl;
      //total normalization error
      //double totalErr = TMath::Sqrt( shapeErr*shapeErr + y[i]*y[i]/NtotalFit ); 
      if ( y[i] - totalErr > .0 )
	{
	  errfix->SetPointError(i, 0, 0, totalErr, totalErr );
	  sigma[i] = y[i]-totalErr;
	  sigma[2*Nc-(i+1)] = y[i]+totalErr;
	}
      else
	{
	  errfix->SetPointError(i, 0, 0, y[i]-0.01, totalErr );
	  sigma[i] = 0.01;
	  sigma[2*Nc-(i+1)] = y[i]+totalErr;
	}
      //2sigma
      if ( y[i] -  2.*totalErr > .0 )
	{
	  errfix2->SetPointError(i, 0, 0, 2.*totalErr,  2.*totalErr );
	  sigma2[i] = y[i]-2.0*totalErr;
	  sigma2[2*Nc-(i+1)] = y[i]+2.0*totalErr;
	}
      else
	{
	  errfix2->SetPointError(i, 0, 0, y[i]-0.01,  2.*totalErr );
	  sigma2[i] = 0.01;
	  sigma2[2*Nc-(i+1)] = y[i]+2.0*totalErr;
	}
      /*
	std::cout << x[i] << " " << y[i] << " "
	<< " ,pdf get Val: " << pdf->getVal()
	<< " ,pdf get Prop Err: " << pdf->getPropagatedError(*res)*NtotalFit
	<< " stat uncertainty: " << TMath::Sqrt(y[i]) << " Ntot: " << NtotalFit <<  std::endl;
      */
    }
  
  errfix->SetFillColor(kAzure-2);
  errfix2->SetFillColor(kRed+2);
  TGraph* gsigma = new TGraph(2*Nc, xp, sigma);
  TGraph* gsigma2 = new TGraph(2*Nc, xp, sigma2);
  gsigma2->SetFillColor(kAzure-2);
  gsigma2->SetLineColor(kAzure-2);
  gsigma->SetFillColor(kAzure-4);
  gsigma->SetLineColor(kAzure-4);
  
  //pdf->plotOn(plot,RooFit::NormRange( "low,high" ),RooFit::FillColor(kGreen),RooFit::Range("Full"), RooFit::VisualizeError(*res,2.0,kFALSE));
  //pdf->plotOn(plot,RooFit::NormRange( "low,high" ),RooFit::FillColor(kYellow),RooFit::Range("Full"), RooFit::VisualizeError(*res,1.0,kFALSE));
  //pdf->plotOn(plot,RooFit::NormRange( "low,high" ),RooFit::FillColor(kGreen),RooFit::Range("Full"), RooFit::VisualizeError(*res,2.0,kTRUE));
  //pdf->plotOn(plot,RooFit::NormRange( "low,high" ),RooFit::FillColor(kYellow),RooFit::Range("Full"), RooFit::VisualizeError(*res,1.0,kTRUE));


  //plot->addObject(&errfix,"4");
  //plot->addObject(&errfix2,"4");
  //plot->addObject(&errfix,"4");

  //data->plotOn(plot);
  TBox blindBox(121,plot->GetMinimum()-(plot->GetMaximum()-plot->GetMinimum())*0.015,130,plot->GetMaximum());
  blindBox.SetFillColor(kGray);

  if(blind) {
    //plot->addObject(&blindBox);
    //pdf->plotOn(plot,RooFit::NormRange( "low,high" ),RooFit::FillColor(kGreen),RooFit::Range("Full"), RooFit::VisualizeError(*res,2.0,kTRUE));
    //pdf->plotOn(plot,RooFit::NormRange( "low,high" ),RooFit::FillColor(kYellow),RooFit::Range("Full"), RooFit::VisualizeError(*res,1.0,kTRUE));
  }
  
  //plot->addObject(&errfix,"4");
  //data->plotOn(plot);
  
  //pdf->plotOn(plot,RooFit::Normalization( norm ) );
  //pdf->plotOn(plot,RooFit::NormRange( "low,high" ),RooFit::Range("Full"),RooFit::LineWidth(1.5) );
  pdf->plotOn( plot, RooFit::NormRange( "all" ),RooFit::Range("all"), RooFit::LineWidth(2), RooFit::LineColor(kWhite) );
  //data->plotOn(plot);
  /*
    pdf->plotOn(plot,RooFit::Normalization(norm),RooFit::Range("all"),RooFit::LineWidth(0.8) );
    //pdf->plotOn(plot,RooFit::Normalization(norm),RooFit::FillColor(kGreen),RooFit::Range("all"), RooFit::VisualizeError(*res,2.0,kFALSE));
    //pdf->plotOn(plot,RooFit::Normalization(norm),RooFit::FillColor(kYellow),RooFit::Range("all"), RooFit::VisualizeError(*res,1.0,kFALSE));
    pdf->plotOn(plot,RooFit::Normalization(norm),RooFit::FillColor(kGreen),RooFit::Range("all"), RooFit::VisualizeError(*res,2.0,kTRUE));
    pdf->plotOn(plot,RooFit::Normalization(norm),RooFit::FillColor(kYellow),RooFit::Range("all"), RooFit::VisualizeError(*res,1.0,kTRUE));
    data->plotOn(plot);
    pdf->plotOn(plot,RooFit::Normalization(norm),RooFit::Range("all"),RooFit::LineWidth(0.8) );
  */
  TLatex lbl0(0.12,0.96,"CMS Preliminary");
  lbl0.SetNDC();
  lbl0.SetTextSize(0.042);
  plot->addObject(&lbl0);
  
  
  TLatex lbl2(0.6,0.96,"#sqrt{s}=8 TeV  L = 19.78 fb^{-1}");
  lbl2.SetNDC();
  lbl2.SetTextSize(0.042);
  plot->addObject(&lbl2);
  
  
  int iObj=-1;
  TNamed *obj;
  while( (obj = (TNamed*)plot->getObject(++iObj)) ) {
    obj->SetName(Form("Object_%d",iObj));
  }
  
  //plot->Draw();

  RooPlot *plot2 = mass->frame(min,max, 70);
  plot2->SetTitle("");
  data->plotOn( plot2 );
  pdf->plotOn( plot2, RooFit::NormRange( "all" ),RooFit::Range("all"), RooFit::LineWidth(2), RooFit::LineColor(kRed) );
  TH1F* dummy = new TH1F("dummy", "dummy", 70, 230, 320);
  dummy->SetLineColor(kRed);
  dummy->SetLineWidth(2);
  
  //h_tmp2->Draw("sameE0");
  //h_tmp2->Draw("sameE1");
  //h_tmp3->Draw("sameE1");
  errfix->SetMarkerStyle(20);
  errfix->SetMarkerSize(1);
  //plot2->Draw();

  gsigma2->SetTitle("");
  //gsigma2->GetYaxis()->SetRangeUser(0.1,600);
  gsigma2->GetYaxis()->SetRangeUser(0.1,200);
  gsigma2->GetXaxis()->SetTitleSize(0.05);
  gsigma2->GetYaxis()->SetTitleSize(0.05);
  gsigma2->GetYaxis()->SetTitle("Events / ( 20 GeV )");
  gsigma2->GetXaxis()->SetRangeUser(230.,1610);
  gsigma2->GetXaxis()->SetTitle("m_{#gamma#gamma} (GeV)");
  gsigma2->Draw("AF");
  gsigma->Draw("F");
  plot2->Draw("same");
  h_tmp2->Draw("sameE0");
  h_tmp2->Draw("sameE1");
  h_tmp3->Draw("sameE1");

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

  float lumifont = 42;
  float cmsSize = 0.06;
  TLatex latex;
  latex.SetNDC();
  latex.SetTextAngle(0);
  latex.SetTextColor(kBlack);    
  latex.SetTextFont(lumifont);
  latex.SetTextAlign(31); 
  latex.SetTextSize(cmsSize);    
  latex.DrawLatex(0.6, 0.85, "EBEE");
  
  AddCMS(cv);
  
  TString det;
  if ( isEBEB ) det = "EBEB";
  else det = "EBEE";
  
  cv->SetLogy();
  //cv.SetLogx();
  cv->SaveAs("mgg_data_fit" + det + ".png");
  cv->SaveAs("mgg_data_fit" + det + ".pdf");
  cv->SaveAs("mgg_data_fit" + det + ".C");

  fout->cd();
  errfix->Write("fit1");
  errfix2->Write("fit2");
  hp->Write("hp");
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

