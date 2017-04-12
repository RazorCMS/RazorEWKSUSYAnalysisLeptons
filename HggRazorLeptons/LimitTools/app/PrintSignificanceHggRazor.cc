//C++
#include <iostream>
#include <fstream>
#include <map>
#include <stdlib.h>
#include <fstream>
#include <sstream>
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

struct Bin
{
  std::string box;
  std::string f1;
  int bin;
  float x1;
  float x2;
  float y1;
  float y2;

  
  bool const operator== (const Bin &b) const
  {
    return bin == b.bin;
  }
  
  bool const operator< (const Bin &b) const
  {
    return bin < b.bin;
  }
};



//----------------------------------------------
//New Binning From Significance Calculation 2016 
//----------------------------------------------
//HIGHPT
float bin_highpt0[4] = {600,0.025,10000,1};
float bin_highpt1[4] = {150,0.13,600,1};
float bin_highpt2[4] = {1250,0,10000,0.025};
float bin_highpt3[4] = {150,0,450,0.13};
float bin_highpt4[4] = {450,0,600,0.035};
float bin_highpt5[4] = {450,0.035,600,0.13};
float bin_highpt6[4] = {600,0,1250,0.015};
float bin_highpt7[4] = {600,0.015,1250,0.025};
std::vector<float*> SetBinning_highpt()
{
  std::vector<float*> myVec;
  myVec.push_back(bin_highpt0);
  myVec.push_back(bin_highpt1);
  myVec.push_back(bin_highpt2);
  myVec.push_back(bin_highpt3);
  myVec.push_back(bin_highpt4);
  myVec.push_back(bin_highpt5);
  myVec.push_back(bin_highpt6);
  myVec.push_back(bin_highpt7);
  return myVec;
};
//HZBB
float bin_hzbb0[4] = {150,0,10000,1};
std::vector<float*> SetBinning_hzbb()
{
  std::vector<float*> myVec;
  myVec.push_back(bin_hzbb0);
  return myVec;
};
//HIGHRES
float bin_highres0[4] = {150,0.0,250,0.175};
float bin_highres1[4] = {150,0.175,250,1};
float bin_highres2[4] = {250,0.05,10000,1};
float bin_highres3[4] = {250,0.0,600,0.05};
float bin_highres4[4] = {600,0.0,10000,0.05};
std::vector<float*> SetBinning_highres()
{
  std::vector<float*> myVec;
  myVec.push_back(bin_highres0);
  myVec.push_back(bin_highres1);
  myVec.push_back(bin_highres2);
  myVec.push_back(bin_highres3);
  myVec.push_back(bin_highres4);
  //myVec.push_back(bin_highres5);
  //myVec.push_back(bin_highres6);
  return myVec;
};
//LOWRES
float bin_lowres0[4] = {500,0.01,10000,1};
float bin_lowres1[4] = {150,0.15,500,1};
float bin_lowres2[4] = {150,0,400,0.15};
float bin_lowres3[4] = {400,0,500,0.015};
float bin_lowres4[4] = {400,0.015,500,0.15};
float bin_lowres5[4] = {500,0,800,0.01};
float bin_lowres6[4] = {800,0,10000,0.01};
std::vector<float*> SetBinning_lowres()
{
  std::vector<float*> myVec;
  myVec.push_back(bin_lowres0);
  myVec.push_back(bin_lowres1);
  myVec.push_back(bin_lowres2);
  myVec.push_back(bin_lowres3);
  myVec.push_back(bin_lowres4);
  myVec.push_back(bin_lowres5);
  myVec.push_back(bin_lowres6);
  return myVec;
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

  std::map<Bin, std::string> myMap;
  std::map<std::string, Bin> myMap2;
  
  std::ifstream input( "data/HggRazor2016Binning.txt", std::fstream::in );
  if ( input.is_open() )
    {
      float x1, x2, y1, y2;
      int binN;
      std::string box, f1;
      while ( input.good() )
	{
	  input >> binN >> x1 >> x2 >> y1 >> y2 >> box >> f1;
	  if ( input.eof() ) break;
	  Bin mybin;
	  mybin.bin = binN;
	  mybin.f1 = f1;
	  mybin.box = box;
	  mybin.x1 = x1;
	  mybin.x2 = x2;
	  mybin.y1 = y1;
	  mybin.y2 = y2;
	  std::stringstream ss;
	  ss << box << "_" << x1 << "-" << x2 << "_" << y1 << "-" << y2;
	  //myMap.find( mybin );
	  if ( myMap.find( mybin ) == myMap.end() ) myMap[mybin] = f1;
	  if ( myMap2.find( ss.str() ) == myMap2.end() ) myMap2[ss.str()] = mybin;
	  //std::cout << binN << " " <<  x1  << " " << x2 << " " << y1 << " " << y2 << " " <<  box << " " << f1 << std::endl;
	}
    }
  else
    {
      std::cout << "Unable to open binning lookup table" << std::endl;
    }

  for ( auto tmp : myMap2 )
    {
      std::cout << tmp.first << "; binN--->" << tmp.second.bin << std::endl;
    }

  //-----------------
  //Input File List
  //-----------------
  std::string inputList = ParseCommandLine( argc, argv, "-inputList=" );
  if (  inputList == "" )
    {
      std::cerr << "[ERROR]: please provide an inputList. Use --inputList=" << std::endl;
      return -1;
    }
  
  //-----------------
  //Selection TString
  //-----------------
  std::string categoryMode = ParseCommandLine( argc, argv, "-category=" );
  if (  categoryMode == "" )
    {
      std::cerr << "[ERROR]: please provide the category. Use --category=<highpt,hzbb,highres,lowres>" << std::endl;
      return -1;
    }
  std::vector<float*> myVectBinning;
  if ( categoryMode == "highpt")
    {
      myVectBinning = SetBinning_highpt();
    }
  else if ( categoryMode == "hzbb" )
    {
      myVectBinning = SetBinning_hzbb();
    }
  else if ( categoryMode == "highres" )
    {
      myVectBinning = SetBinning_highres();
    }
  else if ( categoryMode == "lowres" )
    {
      myVectBinning = SetBinning_lowres();
    }
  else
    {
      std::cerr << "[ERROR]: category is not <highpt/hzbb/highres/lowres>; quitting" << std::endl;
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
	  int low  = fname.find("_bin")+4;
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
	  //std::cout << "mass: " << mass << "-> " << tmpLimit.sigma << " " << tmpLimit.pvalue << std::endl;
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
      //if ( tmp.second.sigma != 0.0 ) std::cout << "mass: " << tmp.first << " expL: " << tmp.second.sigma << std::endl;
      //std::cout << "bin: " << tmp.first << " expL: " << tmp.second.sigma << std::endl;
      x[ctr]     = tmp.first;
      sigma[ctr] = tmp.second.sigma;
      pval[ctr]  = tmp.second.pvalue;
      ctr++;
    }

  std::cout << "\\begin{table*}[htb]\n\\footnotesize\n\\begin{center}\n\\caption{";
  std::cout << categoryMode << " category binning. SM Higgs, and signal expected yields for an integrated luminosity correspondint to 6.3~$\\mathrm{fb}^{-1}$";
  std::cout << "\\label{tab:binning-highpt}}\n\\def\\arraystretch{1.5}\n\\begin{tabular}{|c|c|c|c|}\n\\hline\n$\\mathrm{M_{R}} (GeV)\\otimes\\mathrm{R^{2}}$";
  std::cout << " & binNumber & n$\\sigma$ & p-value\\\\" << std::endl;
  std::cout << "\\hline" << std::endl;
   for ( auto tmp: myVectBinning )
    {
      std::stringstream ss;
      ss << categoryMode << "_" << tmp[0] << "-" << tmp[2] << "_" << tmp[1] << "-" << tmp[3];
      TString bbb = Form("%.0f-%.0f$\\times$%.3f-%.3f", tmp[0], tmp[2], tmp[1], tmp[3] );
      TString sigg = Form("%.1f & %.2f", mymap[myMap2[ss.str()].bin].sigma, mymap[myMap2[ss.str()].bin].pvalue );
      std::cout << bbb << "& " << myMap2[ss.str()].bin << " & " << sigg << "\\\\" << std::endl;
    }

   std::cout << "\\hline\n\\end{tabular}\n\\end{center}\n\\end{table*}" << std::endl;
   
  /*
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
  
  gsigma->Write("gObs");
  gpval->Write("gExp");
  
  out->Close();
  */
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
