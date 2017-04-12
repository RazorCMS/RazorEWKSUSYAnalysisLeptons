#include <iostream>
#include <TROOT.h>
#include <TH1F.h>
#include <TRandom3.h>
#include <TFile.h>

void TestGaussSquare()
{
  gROOT->Reset();
  TRandom3* r = new TRandom3( 0 );
  TH1F* h_gaus    = new TH1F("gauss", "gauss", 100,-10,10);
  TH1F* h_gausSqr = new TH1F("gaussSqr", "gausSqr", 100, -10,10);
  
  for ( int i = 0; i < 10000; i++ )
    {
      double rndGauss = r->Gaus(0,1);
      h_gaus->Fill( rndGauss );
      h_gausSqr->Fill( rndGauss*rndGauss );
    }
  TFile* fout = new TFile("fout.root", "RECREATE");
  h_gaus->Write();
  h_gausSqr->Write();
  fout->Close();
}
