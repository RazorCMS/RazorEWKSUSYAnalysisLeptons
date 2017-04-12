#ifndef PLOT_COSMETICS_HH
#define PLOT_COSMETICS_HH 1
//C++ INCLUDES
#include <iostream>
#include <string>
//ROOT INCLUDES
#include <TChain.h>
#include <TString.h>
#include <TH1D.h>
#include <TH2F.h>
#include <THStack.h>
#include <TLegend.h>
#include <TCanvas.h>
#include <TLatex.h>
//LOCAL INCLUDES
#include "HggAux.hh"

bool MakeCustomMrRsq( TH2F* h, TString outName );
bool MakeStackPlot( THStack* s, TString var, TString outName, TLegend* leg = NULL );
bool MakeStackPlot( THStack* s, TH1D* data, TH1D* mc, TString var, TString outName, TLegend* leg = NULL, TString label = "dummy" );
bool MakeStackPlotSignal( THStack* s, TH1D* signal, TString var, TString outName, TLegend* leg, TString label = "dummy" );
bool PlotSameCanvas( TH1D** histos, int nhistos, TString var, TString outName, TLegend* leg, TString label = "dummy" );
//Create Histogram with style based in the process
TH1D* GetStyledHisto( TH1D* h, Process process );
bool SetHistoStyle( TH1D* h, Process process );


//Legend
bool AddLegend( TH1D* h, TLegend* leg, Process process );
bool AddCMS( TCanvas* C );

#endif
