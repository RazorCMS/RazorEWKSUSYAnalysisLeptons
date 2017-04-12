//C++ INCLUDES
#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h> 
//ROOT INCLUDES
#include <TFile.h>
#include <TTree.h>
#include <TH1F.h>
#include <TCanvas.h>
#include <TLatex.h>
#include <RooPlot.h>

//LOCAL INCLUDES
#include "SusyHggMggFit.hh"

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
const float leftMargin   = 0.14;
const float rightMargin  = 0.05;
const float topMargin    = 0.07;
const float bottomMargin = 0.12;

//CMS STANDARD
TString CMSText = "CMS";
TString extraText   = "Preliminary";
//TString lumiText = "2.32 fb^{-1} (13 TeV)";
TString lumiText = "35.9 fb^{-1} (13 TeV)";

bool AddCMS( TCanvas* C );


int main ( int argc, char* argv[] )
{
  std::ifstream ifs( "list_of_mlfits.txt", std::ifstream::in );
  TFile* File;
  
  if ( ifs.is_open() )
    {
      while ( ifs.good() )
	{
	  std::string fname;
	  ifs >> fname;
	  if( ifs.eof() ) break;
	  File = new TFile( fname.c_str(), "READ" );
	  std::string binN = fname.substr(fname.find("bin")+3, fname.find(".root")-(fname.find("bin")+3));
	  int bin = atoi( binN.c_str() );

	  TCanvas* c = new TCanvas( "c", "c", 2119, 33, 800, 700 );
	  c->SetHighLightColor(2);
	  c->SetFillColor(0);
	  c->SetBorderMode(0);
	  c->SetBorderSize(2);
	  
	  c->SetLeftMargin( leftMargin );
	  c->SetRightMargin( rightMargin );
	  c->SetTopMargin( topMargin );
	  c->SetBottomMargin( bottomMargin );
	    
	  //c->SetFrameBorderMode(0);
	  //c->SetFrameBorderMode(0);
	  if ( bin <=8 )
	    {
	      RooPlot* plot = (RooPlot*)File->Get( Form("bin%d_fit_s",bin) );
	      plot->SetTitle("");
	      plot->GetYaxis()->SetTitleOffset(1);
	      plot->Draw();
	      AddCMS(c);
	      c->SaveAs(Form("bin%d_fit_s.pdf",bin));
	      c->SaveAs(Form("bin%d_fit_s.png",bin));
	      c->SaveAs(Form("bin%d_fit_s.C",bin));

	      //b-only
	      RooPlot* plotb = (RooPlot*)File->Get( Form("bin%d_fit_b",bin) );
	      plotb->SetTitle("");
	      plotb->GetYaxis()->SetTitleOffset(1);
	      plotb->Draw();
	      AddCMS(c);
	      c->SaveAs(Form("bin%d_fit_b.pdf",bin));
	      c->SaveAs(Form("bin%d_fit_b.png",bin));
	      c->SaveAs(Form("bin%d_fit_b.C",bin));
	    }
	  else
	    {
	      RooPlot* plot1 = (RooPlot*)File->Get( Form("highResBin%d_fit_s",bin) );
	      plot1->SetTitle("");
	      plot1->GetYaxis()->SetTitleOffset(1);
	      plot1->Draw();
	      AddCMS(c);
	      c->SaveAs(Form("highResBin%d_fit_s.pdf",bin));
	      c->SaveAs(Form("highResBin%d_fit_s.png",bin));
	      c->SaveAs(Form("highResBin%d_fit_s.C",bin));
	      //b-only
	      RooPlot* plot1b = (RooPlot*)File->Get( Form("highResBin%d_fit_b",bin) );
	      plot1b->SetTitle("");
	      plot1b->GetYaxis()->SetTitleOffset(1);
	      plot1b->Draw();
	      AddCMS(c);
	      c->SaveAs(Form("highResBin%d_fit_b.pdf",bin));
	      c->SaveAs(Form("highResBin%d_fit_b.png",bin));
	      c->SaveAs(Form("highResBin%d_fit_b.C",bin));

	      //LowRes
	      RooPlot* plot2 = (RooPlot*)File->Get( Form("lowResBin%d_fit_s",bin) );
	      plot2->SetTitle("");
	      plot2->GetYaxis()->SetTitleOffset(1);
	      plot2->Draw();
	      AddCMS(c);
	      c->SaveAs(Form("lowResBin%d_fit_s.pdf",bin));
	      c->SaveAs(Form("lowResBin%d_fit_s.png",bin));
	      c->SaveAs(Form("lowResBin%d_fit_s.C",bin));
	      //b-only
	      //LowRes
	      RooPlot* plot2b = (RooPlot*)File->Get( Form("lowResBin%d_fit_b",bin) );
	      plot2b->SetTitle("");
	      plot2b->GetYaxis()->SetTitleOffset(1);
	      plot2b->Draw();
	      AddCMS(c);
	      c->SaveAs(Form("lowResBin%d_fit_b.pdf",bin));
	      c->SaveAs(Form("lowResBin%d_fit_b.png",bin));
	      c->SaveAs(Form("lowResBin%d_fit_b.C",bin));
	      
	    }
	  delete c;
	  delete File;
	}
    }
  else
    {
      std::cout << "[ERROR]: unable to open file; quitting" << std::endl;
    }

  return 0;
}


bool AddCMS( TCanvas* C )
{
  C->cd();
  float lumix = 0.955;
  float lumiy = 0.945;
  float lumifont = 42;
  
  float cmsx = 0.245;
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
  //latex.DrawLatex(extrax, extray, extraText);
  return true;
};
