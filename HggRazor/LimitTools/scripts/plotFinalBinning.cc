#include <iostream>
#include <assert.h>
//ROOT INCLUDES
#include <TFile.h>
#include <TH2F.h>
#include <TH2Poly.h>
#include <TAxis.h>
#include <TCanvas.h>

void plotFinalBinning( TString fname, TString category)
{
  TFile* f = new TFile( fname );
  assert( f );
  TH2Poly* h2p = (TH2Poly*)f->Get("h2p_bFull");


  TCanvas* c = new TCanvas( "c", "c", 2119, 33, 800, 700 );
  c->SetHighLightColor(2);
  c->SetFillColor(0);
  c->SetBorderMode(0);
  c->SetBorderSize(2);
  /*
  c->SetLeftMargin( leftMargin );
  c->SetRightMargin( rightMargin );
  c->SetTopMargin( topMargin );
  c->SetBottomMargin( bottomMargin );
  */
  c->SetFrameBorderMode(0);
  c->SetFrameBorderMode(0);

  
  h2p->SetStats( 0 );
  h2p->SetTitle("");
  h2p->SetYTitle("R^{2}");
  h2p->SetXTitle("M_{R} (GeV)");
  //h2p->GetYaxis()->SetRangeUser(1e-3, 1.0);
  //h2p->GetXaxis()->SetRangeUser(100, 10000);
  
  h2p->Draw("text");

  //c->SetLogy();
  //c->Range( 150, 1e-5, 1e4, 1 );
  c->SetLogx();
  c->SetLogz();
  h2p->GetYaxis()->SetRangeUser(1e-5, .3);
  c->Update();
  
  return;
};
