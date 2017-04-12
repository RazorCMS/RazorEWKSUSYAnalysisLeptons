#ifndef COMPARE_HGG_MC_HH
#define COMPARE_HGG_MC_HH

#include <TROOT.h>
#include <TSystem.h>
#include <TStyle.h>
#include <TFile.h>
#include <TTree.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TGaxis.h>
#include <TH1D.h>
#include <TGraph.h>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <fstream>
#include "CalStyleRemix.hh"

using namespace std;

class Config {
public:

  Config(TString fname, TString sname, TString lab, Int_t col, Int_t sty) {
    filename   = fname;
    samplename = sname;
    label = lab;
    lineCol = col;
    lineSty = sty;
    file = new TFile(fname, "READ");
  };
  ~Config() {};
  
  TString getSampleName() { return samplename; };

  TString getLabel() {return label; };

  Int_t   getLineColor() {return lineCol; };

  Int_t   getLineStyle() {return lineSty; };

  TFile *file;

protected:

  TString filename;
  TString samplename;
  TString label;
  Int_t lineCol;
  Int_t lineSty;
};

enum Category { inc=0, highpt, hzbb, highres, lowres };

void draw(Category cat, TString var, 
	  Config fB, vector<Config> fC,
	  Int_t nbins, Int_t xmin, Int_t xmax);

TH1D* returnPlot(Category cat, TString var, Config f, 
		 Int_t nbins, Double_t xmin, Double_t xmax);

TH1D* returnRatio(TH1D* h, TH1D* b, TString name);

#endif
