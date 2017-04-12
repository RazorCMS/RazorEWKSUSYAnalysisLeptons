{
  gROOT->Reset();
  //Margins
  const float leftMargin   = 0.12;
  const float rightMargin  = 0.05;
  const float topMargin    = 0.07;
  const float bottomMargin = 0.12;
  
  
  const int nhistos = 4;
  TString treeName = "HighRes";
  TString cut = "(MR > 0.0 && t1Rsq > 0.0 && abs( pho1Eta ) < 1.44 && abs( pho2Eta ) < 1.44 && ( pho1Pt > 40. || pho2Pt > 40. ) && pho1Pt > 25. && pho2Pt> 25. && pTGammaGamma>20 && mGammaGamma>103 && mGammaGamma<160 && trigger==1)";
  
  TString beginning = "R9_";
  //TString extra_string = "_HighRes_Mr250Rsq0p05";
  TString extra_string = "_HighRes_Inclusive_Normalized";
  bool _normalize = true;
  
  TFile* f0 = new TFile("/Users/cmorgoth/Work/data/HggRazorRun1/data/DataPhotonDoubleCheck_GoodLumi.root");
  
  TTree* t0 = (TTree*)f0->Get( treeName );
  t0->Draw("MR>>t0_mr(40, 0, 2000.)", cut, "goff");
  t0->Draw("Rsq>>t0_rsq(30, 0, 1.5)", cut, "goff");
  t0->Draw("mGammaGamma>>t0_mgg(38, 103, 160.)", cut, "goff");
  t0->Draw("pho2sigmaEOverE>>t0_pho1seoe(500, 0, 0.1)", cut, "goff");
  TH1F* h_t0[nhistos];
  h_t0[0] = (TH1F*)gDirectory->Get("t0_mr");
  h_t0[1] = (TH1F*)gDirectory->Get("t0_rsq");
  h_t0[2] = (TH1F*)gDirectory->Get("t0_mgg");
  h_t0[3] = (TH1F*)gDirectory->Get("t0_pho1seoe");

  //TFile* f1 = new TFile("/Users/cmorgoth/Work/data/HggRazorRun1/data/DataPhotonMediumIso_DoubleChecked_GoodLumi.root");
  //TFile* f1 = new TFile("/Users/cmorgoth/Work/data/HggRazorRun1/data/DataPhotonVeryLooseIso_DoubleChecked_GoodLumi.root");
  TFile* f1 = new TFile("/Users/cmorgoth/Work/data/HggRazorRun1/data/DataPhotonR9_DoubleChecked_GoodLumi.root");
  
  TTree* t1 = (TTree*)f1->Get( treeName );
  t1->Draw("MR>>t1_mr(40, 0, 2000.)", cut, "goff");
  t1->Draw("Rsq>>t1_rsq(30, 0, 1.5)", cut, "goff");
  t1->Draw("mGammaGamma>>t1_mgg(38, 103, 160.)", cut, "goff");
  t1->Draw("pho2sigmaEOverE>>t1_pho1seoe(500, 0, 0.1)", cut, "goff");
  TH1F* h_t1[nhistos];
  h_t1[0] = (TH1F*)gDirectory->Get("t1_mr");
  h_t1[1] = (TH1F*)gDirectory->Get("t1_rsq");
  h_t1[2] = (TH1F*)gDirectory->Get("t1_mgg");
  h_t1[3] = (TH1F*)gDirectory->Get("t1_pho1seoe");

  for ( int i = 0; i < nhistos; i++ )
    {
      h_t0[i]->Sumw2();
      h_t1[i]->Sumw2();
    }
  
  double n0, n1, err0, err1;
  n0 = h_t0[2]->IntegralAndError( 1, h_t0[2]->GetNbinsX(), err0, "" );
  n1 = h_t1[2]->IntegralAndError( 1, h_t1[2]->GetNbinsX(), err1, "" );
  std::cout << "Box: " << treeName << ", mgg 13TeV/8TeV -> " <<   n1/n0 << " \\pm " << (n1/n0)*sqrt( err1*err1/(n1*n1) + err0*err0/(n0*n0) ) <<  std::endl;
  //Normalizing to unit integral;
  for (  int i = 0; i < nhistos; i++ )
    {
      if (  _normalize ) h_t0[i]->Scale( 1.0/h_t0[i]->Integral() );
      h_t0[i]->SetLineColor( kRed );
      h_t0[i]->SetLineWidth(2);
      h_t0[i]->SetMarkerStyle(20);
      h_t0[i]->SetMarkerColor( kRed );
      h_t0[i]->SetStats( 0 );
      if ( _normalize ) h_t1[i]->Scale( 1.0/h_t1[i]->Integral() );
      h_t1[i]->SetLineWidth(2);
      h_t1[i]->SetMarkerStyle(20);
      h_t1[i]->SetMarkerColor( kBlue );
    }
  
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
  
  
  const int i_histo = 2;
  h_t0[i_histo]->SetTitle("");
  h_t0[i_histo]->GetXaxis()->SetTitleSize( 0.06 );
  h_t0[i_histo]->GetXaxis()->SetTitleOffset( 0.7 );
  h_t0[i_histo]->SetXTitle("m_{#gamma#gamma} (GeV)");

  h_t0[i_histo]->GetYaxis()->SetTitleSize( 0.06 );
  h_t0[i_histo]->GetYaxis()->SetTitleOffset( 1.03 );
  h_t0[i_histo]->SetYTitle("events / 1.5 GeV");
  if ( _normalize ) h_t0[i_histo]->SetYTitle("a.u");
  h_t0[i_histo]->Draw("E");
  h_t0[i_histo]->GetYaxis()->SetRangeUser(0.0, 2.0*h_t0[2]->GetMaximum() );
  h_t1[i_histo]->Draw("sameE");

  TLegend* leg = new TLegend( 0.65, 0.58, 0.89, 0.89, NULL, "brNDC" );
  leg->SetBorderSize(0);
  leg->SetLineColor(1);
  leg->SetLineStyle(1);
  leg->SetLineWidth(1);
  leg->SetFillColor(0);
  leg->SetFillStyle(1001);
  leg->SetTextSize(.03);
  //leg->AddEntry( h_t0[i_histo], "defaul isolation", "lep" );
  //leg->AddEntry( h_t1[i_histo], "very loose isolation", "lep" );
  //leg->AddEntry( h_t1[i_histo], "medium isolation", "lep" );
  leg->AddEntry( h_t0[i_histo], "#sigma_{E}/E", "lep" );
  leg->AddEntry( h_t1[i_histo], "R_{9}", "lep" );
  leg->Draw();

  c->SaveAs( beginning + "mgg" + extra_string + ".pdf");
  c->SaveAs( beginning + "mgg" + extra_string + ".C")
}
