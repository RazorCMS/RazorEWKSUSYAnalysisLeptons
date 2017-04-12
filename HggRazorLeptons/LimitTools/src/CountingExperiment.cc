//C++
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
//ROOT
#include <TTree.h>
#include <TFile.h>
#include <TString.h>
#include <TCanvas.h>
#include <TLatex.h>
#include <TStyle.h>
#include <TAxis.h>
#include <TF1.h>
//RooFit
#include <RooRealVar.h>
#include <RooWorkspace.h>
#include <RooDataSet.h>
#include <RooPlot.h>
#include <RooGaussian.h>
//LOCAL
#include "HggAux.hh"
#include "CountingExperiment.hh"

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


TH2F* Create2DHisto( TTree* tree, std::map<float, std::vector<float>> bMap, float RsqBinSize, TString pName, const float lumi, const float kf )
{
  //-------------------------
  //C r e a t i n g   T H 2 F
  //-------------------------
  const int n_RSQedges = (int)5.0/RsqBinSize + 1;
  float RSQedges[n_RSQedges];
  for ( int j = 0; j < n_RSQedges; j++ )
    {
      RSQedges[j] = (float)j*RsqBinSize;
      //std::cout << "edge j = " << j << " , val-> " << RSQedges[j] << std::endl;
    }
  const int n_MRedges = bMap.size();
  float MRedges[n_MRedges+1];
  int ctr = 0;
  for ( auto& tmp : bMap )
    {
      MRedges[ctr] = tmp.first;
      //std::cout << MRedges[ctr] << std::endl;
      ctr++;
    }
  MRedges[n_MRedges] = 10000;
  TH2F* _hRazor = new TH2F( pName + "_hRazor", pName + "_hRazor", n_MRedges, MRedges, n_RSQedges-1, RSQedges);
  //TH2F* _hRazor = new TH2F( "h", "h", 20, 150,5000, 500, 0, 5);
  
  
  float mr, rsq, weight, pileupWeight;
  tree->SetBranchStatus("*", 0);
  tree->SetBranchStatus("MR", 1);
  tree->SetBranchStatus("t1Rsq", 1);
  tree->SetBranchStatus("weight", 1);
  tree->SetBranchStatus("pileupWeight", 1);
  tree->SetBranchAddress("MR", &mr);
  tree->SetBranchAddress("t1Rsq", &rsq);
  tree->SetBranchAddress("weight", &weight);
  tree->SetBranchAddress("pileupWeight", &pileupWeight);
  long nentries = tree->GetEntries();
  for ( long i = 0; i < nentries; i++ )
    {
      tree->GetEntry(i);
      if ( i%10000 == 0 )
	{
	  //std::cout << "[INFO]: entry #" << i << std::endl;
	  //std::cout << "mr: " << mr << " , rsq: " << rsq << std::endl;
	}
      
      if( pName == "data" || pName == "signal" || pName == "signal_SR" )
	{
	  //std::cout << "pName: " << pName << std::endl;
	  _hRazor->Fill(mr, rsq, lumi*kf*weight);
	}
      else
	{
	  _hRazor->Fill(mr, rsq, lumi*kf*weight*pileupWeight);
	}
    }
  std::cout << pName << " " << _hRazor->Integral() << std::endl;
  return _hRazor;
};

void CreateDataCard( std::map<TString,ProcessStruct> psMap, std::map<float, std::vector<float>> bMap, float rsqBinSize, TString cat )
{
  const int nprocesses = psMap.size();
  for ( auto& tmp : bMap )
    {
      const int nj = tmp.second.size() - 1;
      std::cout << "nj: " << nj << std::endl;
      for ( int j = 0; j < nj; j++ )
	{
	  std::stringstream ss;
	  ss << "combineCards/CountingExp/" << cat << "_SCE_MR_" << tmp.first;
	  ss << "_RSQ_" << tmp.second[j] << "_" << tmp.second[j+1] << ".txt"; 
	  std::ofstream ofs ( ss.str().c_str(), std::ofstream::out );
	  ofs << "# Simple counting experiment, with one signal and a few background processes\n";
	  ofs << "imax 1 number of channels\n";
	  ofs << "jmax "<< nprocesses-1 << " number of backgrounds\n";
	  ofs << "kmax 1 number of number of nuisance parameters (sources of systematical uncertainties)\n";
	  ofs << "------------\n";
	  ofs << "# we have just one channel, in which we observe xx events\n";
	  ofs << "bin 1\n";
	  float nonResYield = GetSRYield( psMap["NonRes"].h_sr, tmp.first, tmp.second[j], tmp.second[j+1], rsqBinSize );
	  ofs << "observation " << nonResYield << "\n\n";
	  ofs << "# now we list the expected events for signal and all backgrounds in that bin\n";
	  ofs << "# the second 'process' line must have a positive number for backgrounds, and 0 for signal\n";
	  ofs << "# then we list the independent sources of uncertainties, and give their effect (syst. error)\n";
	  ofs << "# on each process and bin\n\n";
	  ofs << "bin";
	  for ( int i = 0; i < nprocesses; i++ ) ofs << "\t\t1";
	  ofs << "\nprocess\t\tsignal";
	  for ( auto& tmp : psMap ) if ( tmp.first != "signal" ) ofs << "\t\t" << tmp.first;
	  ofs << "\nprocess";
	  for ( int i = 0; i < nprocesses; i++ ) ofs << "\t\t" << i;
	  ofs << "\nrate\t\t" << GetSRYield( psMap["signal"].h_sr, tmp.first, tmp.second[j], tmp.second[j+1], rsqBinSize );
	  for ( auto& tmp2 : psMap )
	    {
	      if ( tmp2.first != "signal" )
		{
		  float yield = GetSRYield( tmp2.second.h_sr, tmp.first, tmp.second[j], tmp.second[j+1], rsqBinSize );
		  ofs << "\t" << yield;
		}
	    }
	  ofs << "\n------------\n";
	  ofs << "lumi\tlnN";
	  for ( int i = 0; i < nprocesses; i++ ) ofs << "\t1.2";
	  ofs.close();
	}
    }
};

void CreateDataCard( std::map<TString,ProcessStruct> psMap, float* MRedges, std::vector<float*> RSQbinning, float rsqBinSize )
{
  const int nprocesses = psMap.size();
  int nb[4] = {5, 4, 3, 2};
  for ( int i = 0; i < 4; i++ )
    {
      int nj = nb[i];
      std::cout << "nj: " << nj << std::endl;
      for ( int j = 0; j < nj-1; j++ )
	{
	  std::stringstream ss;
	  ss << "combineCards/CountingExp/HighRes_SCE_MR_" << MRedges[i] << "_" <<  MRedges[i+1];
	  ss << "_RSQ_" << RSQbinning.at(i)[j] << "_" << RSQbinning.at(i)[j+1] << ".txt"; 
	  std::ofstream ofs ( ss.str().c_str(), std::ofstream::out );
	  ofs << "# Simple counting experiment, with one signal and a few background processes\n";
	  ofs << "imax 1 number of channels\n";
	  ofs << "jmax "<< nprocesses-1 << " number of backgrounds\n";
	  ofs << "kmax 1 number of number of nuisance parameters (sources of systematical uncertainties)\n";
	  ofs << "------------\n";
	  ofs << "# we have just one channel, in which we observe xx events\n";
	  ofs << "bin 1\n";
	  float nonResYield = GetSRYield( psMap["NonRes"].h_sr, MRedges[i], RSQbinning.at(i)[j], RSQbinning.at(i)[j+1], rsqBinSize );
	  ofs << "observation " << nonResYield << "\n\n";
	  ofs << "# now we list the expected events for signal and all backgrounds in that bin\n";
	  ofs << "# the second 'process' line must have a positive number for backgrounds, and 0 for signal\n";
	  ofs << "# then we list the independent sources of uncertainties, and give their effect (syst. error)\n";
	  ofs << "# on each process and bin\n\n";
	  ofs << "bin";
	  for ( int i = 0; i < nprocesses; i++ ) ofs << "\t\t1";
	  ofs << "\nprocess\t\tsignal";
	  for ( auto& tmp : psMap ) if ( tmp.first != "signal" ) ofs << "\t\t" << tmp.first;
	  ofs << "\nprocess";
	  for ( int i = 0; i < nprocesses; i++ ) ofs << "\t\t" << i;
	  ofs << "\nrate\t\t" << GetSRYield( psMap["signal"].h_sr, MRedges[i], RSQbinning.at(i)[j], RSQbinning.at(i)[j+1], rsqBinSize );
	  for ( auto& tmp : psMap )
	    {
	      if ( tmp.first != "signal" )
		{
		  float yield = GetSRYield( tmp.second.h_sr, MRedges[i], RSQbinning.at(i)[j], RSQbinning.at(i)[j+1], rsqBinSize );
		  ofs << "\t" << yield;
		}
	    }
	  ofs << "\n------------\n";
	  ofs << "lumi\tlnN";
	  for ( int i = 0; i < nprocesses; i++ ) ofs << "\t1.2";
	  ofs.close();
	}
    }
  
};


float GetSRYield( TH2F* h, float* MRedges, std::vector<float*> RSQbinning, float rsqBinSize )
{
  float binCount = 0.0;
  int nb[4] = {5, 4, 3, 2};
  for ( int i = 0; i < 4; i++ )
    {
      int nj = nb[i];
      std::cout << "nj: " << nj << std::endl;
      for ( int j = 0; j < nj-1; j++ )
	{
	  float rsq_low = RSQbinning.at(i)[j];
	  int steps = (int)( (RSQbinning.at(i)[j+1] - RSQbinning.at(i)[j])/(float)0.010 );
	  std::cout << "rsq_low: " << rsq_low << " " << RSQbinning.at(i)[j+1] << " diff: " << RSQbinning.at(i)[j+1] - RSQbinning.at(i)[j] << " steps: " << steps << std::endl;
	  binCount = 0.0;
	  for ( int k = 0; k < steps; k++ )
	    {
	      float rsq = rsq_low + (float)k*0.01;
	      float bcontent = h->GetBinContent( h->FindBin( MRedges[i], rsq ) );
	      //if ( bcontent != 0.0 ) std::cout << MRedges[i] << "," << rsq << " --> " << bcontent << std::endl;
	      binCount += bcontent;
	    }
	  std::cout << i << " bin count: " << binCount << std::endl;
	}
    }
  
};

float GetSRYield( TH2F* h, float mrLow, float rsqLow, float rsqHigh, float rsqBinStep )
{
  int steps = (int)( (rsqHigh-rsqLow)/rsqBinStep );
  float binCount = 0;
  for ( int k = 0; k < steps; k++ )
    {
      float rsq = rsqLow + (float)k*rsqBinStep;
      float bcontent = h->GetBinContent( h->FindBin( mrLow, rsq ) );
      //if ( bcontent != 0.0 ) std::cout << mrLow << "," << rsq << " --> " << bcontent << std::endl;
      binCount += bcontent;
    }
  std::cout << mrLow << " " << rsqLow<< "-" << rsqHigh << " --> bin count: " << binCount << std::endl;
  return binCount;
}

void PlotSignalModel( std::string fname, std::string outDir )
{
  //-----------------------
  //G e t t i n g   F i l e
  //-----------------------
  TFile* f = new TFile( fname.c_str() , "READ" );
  //Getting Workspace
  RooWorkspace* w = (RooWorkspace*)f->Get("w_sFit");
  //Getting bias RooRealVar
  RooRealVar* _mu1    = w->var("dGauss_signal_DGF_mu1");
  RooRealVar* _mu2    = w->var("dGauss_signal_DGF_mu2");
  RooRealVar* _sigma1 = w->var("dGauss_signal_DGF_sigma1");
  RooRealVar* _sigma2 = w->var("dGauss_signal_DGF_sigma2");
  RooRealVar* _frac   = w->var("dGauss_signal_DGF_frac");
  RooRealVar* _Ns   = w->var("dGauss_signal_DGF_Ns");

  RooRealVar* mgg = w->var("mGammaGamma");
  mgg->setRange( "signal", 103, 160. );
  RooDataSet* data = (RooDataSet*)w->obj("data");
  //Getting RooPlot
  RooPlot* plot = (RooPlot*)w->obj("dGauss_signal_DGF_ext_frame");
  //Getting individual gaussian;
  RooGaussian* g1 = (RooGaussian*)w->obj("dGauss_signal_DGF1");
  RooGaussian* g2 = (RooGaussian*)w->obj("dGauss_signal_DGF2");
  RooAbsPdf* ge = (RooAbsPdf*)w->obj("dGauss_signal_DGF_ext");
  
  //---------------------------------
  //S e t t i n g   u p   C a n v a s 
  //---------------------------------
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

  /*
  plot->SetTitle("");
  plot->GetXaxis()->SetTitleSize( axisTitleSize );
  plot->GetXaxis()->SetTitleOffset( axisTitleOffset );
  plot->GetYaxis()->SetTitleSize( axisTitleSize );
  plot->GetYaxis()->SetTitleOffset( axisTitleOffset );
  */
  //plot->Draw();
  
  RooPlot* frame = mgg->frame();
  frame->SetTitle("");
  frame->GetXaxis()->SetTitleSize( axisTitleSize );
  frame->GetXaxis()->SetTitleOffset( axisTitleOffset );
  frame->GetYaxis()->SetTitleSize( axisTitleSize );
  frame->GetYaxis()->SetTitleOffset( axisTitleOffset );
  data->plotOn(frame);
  ge->plotOn( frame, RooFit::LineColor( kRed ), RooFit::Components( RooArgSet(*g1) ), RooFit::Range("signal"), RooFit::NormRange("signal") );
  ge->plotOn( frame, RooFit::LineColor( kGreen ), RooFit::Components( RooArgSet(*g2) ), RooFit::Range("signal"), RooFit::NormRange("signal") );
  ge->plotOn( frame, RooFit::LineColor( kBlue ), RooFit::Range("signal"), RooFit::NormRange("signal") );
  frame->Draw();
  //------------------------------
  //P l ot  M e a n  a n d   R m s 
  //------------------------------

  TString s_mu1    = Form("#mu_{1} = %.2f GeV", _mu1->getVal() );
  TString s_mu2    = Form("#mu_{2} = %.2f GeV", _mu2->getVal() );
  TString s_sigma1 = Form("#sigma_{1} = %.2f GeV", _sigma1->getVal() );
  TString s_sigma2 = Form("#sigma_{2} = %.2f GeV", _sigma2->getVal() );
  TString s_frac   = Form("#it{f} = %.2f ", _frac->getVal() );
  
  
  
  TLatex latex;
  latex.SetNDC();
  latex.SetTextAngle(0);
  latex.SetTextColor(kBlack);    
  latex.SetTextFont(42);
  latex.SetTextAlign(31); 
  latex.SetTextSize(0.04);    
  latex.DrawLatex( 0.9, 0.87, s_mu1 );
  latex.DrawLatex( 0.865, 0.87-0.06, s_sigma1 );
  latex.DrawLatex( 0.9, 0.87-2*0.06, s_mu2 );
  latex.DrawLatex( 0.865, 0.87-3*0.06, s_sigma2 );
  latex.DrawLatex( 0.805, 0.87-4*0.06, s_frac );
  
  //-----------------------
  //S a v i n g   P l o t s
  //-----------------------
  //std::string outName = fname;
  std::string findName = "biasTest_";
  int begin_s = fname.find( findName ) + findName.size();
  int end_s   = fname.find( ".root" );
  std::string outName = outDir + "/" +fname.substr( begin_s, end_s - begin_s);
  TString figName = outName;
  c->SaveAs(figName+".pdf");
  c->SaveAs(figName+".png");
  c->SaveAs(figName+".C");
  delete c;
  return;
};
