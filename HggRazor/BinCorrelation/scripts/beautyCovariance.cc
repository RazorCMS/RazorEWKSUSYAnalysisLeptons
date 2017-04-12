{
  
  gROOT->Reset();
  gStyle->SetPaintTextFormat(".1f");
  TFile* fin = new TFile("histos_correlation.root");
  TH1F* h = (TH1F*)fin->Get("corr");
  //TH1F* h = (TH1F*)fin->Get("cov");
  
  h->SetStats(0);
  //h->SetTitle("Background Covariance Matrix");
  //h->SetTitle("Background Correlation Matrix");
  h->SetTitle("");
  h->SetMinimum(-1);
  h->SetMaximum(1);
  //h->SetMinimum(-4000);
  //h->SetMaximum(4000);
  gStyle->SetPaintTextFormat(".1f");
  //corr->SetMinimum(-4000);
  //corr->SetMaximum(4000);
  //x-axis labels
  h->GetXaxis()->SetBinLabel( 1 , "Bin 0");
  h->GetXaxis()->SetBinLabel( 2 , "Bin 1");
  h->GetXaxis()->SetBinLabel( 3 , "Bin 2");
  h->GetXaxis()->SetBinLabel( 4 , "Bin 3");
  h->GetXaxis()->SetBinLabel( 5 , "Bin 4");
  h->GetXaxis()->SetBinLabel( 6 , "Bin 5");
  h->GetXaxis()->SetBinLabel( 7 , "Bin 6");
  h->GetXaxis()->SetBinLabel( 8 , "Bin 7");
  h->GetXaxis()->SetBinLabel( 9 , "Bin 8");
  h->GetXaxis()->SetBinLabel( 10 , "Bin 9 HighRes");
  h->GetXaxis()->SetBinLabel( 11 , "Bin 10 HighRes");
  h->GetXaxis()->SetBinLabel( 12 , "Bin 11 HighRes");
  h->GetXaxis()->SetBinLabel( 13 , "Bin 12 HighRes");
  h->GetXaxis()->SetBinLabel( 14 , "Bin 13 HighRes");
  h->GetXaxis()->SetBinLabel( 15 , "Bin 9 LowRes");
  h->GetXaxis()->SetBinLabel( 16 , "Bin 10 LowRes");
  h->GetXaxis()->SetBinLabel( 17 , "Bin 11 LowRes");
  h->GetXaxis()->SetBinLabel( 18 , "Bin 12 LowRes");
  h->GetXaxis()->SetBinLabel( 19 , "Bin 13 LowRes");
  h->GetXaxis()->LabelsOption("v");
  //y-axis labels
  h->GetYaxis()->SetBinLabel( 1 , "Bin 0");
  h->GetYaxis()->SetBinLabel( 2 , "Bin 1");
  h->GetYaxis()->SetBinLabel( 3 , "Bin 2");
  h->GetYaxis()->SetBinLabel( 4 , "Bin 3");
  h->GetYaxis()->SetBinLabel( 5 , "Bin 4");
  h->GetYaxis()->SetBinLabel( 6 , "Bin 5");
  h->GetYaxis()->SetBinLabel( 7 , "Bin 6");
  h->GetYaxis()->SetBinLabel( 8 , "Bin 7");
  h->GetYaxis()->SetBinLabel( 9 , "Bin 8");
  h->GetYaxis()->SetBinLabel( 10 , "Bin 9 HighRes");
  h->GetYaxis()->SetBinLabel( 11 , "Bin 10 HighRes");
  h->GetYaxis()->SetBinLabel( 12 , "Bin 11 HighRes");
  h->GetYaxis()->SetBinLabel( 13 , "Bin 12 HighRes");
  h->GetYaxis()->SetBinLabel( 14 , "Bin 13 HighRes");
  h->GetYaxis()->SetBinLabel( 15 , "Bin 9 LowRes");
  h->GetYaxis()->SetBinLabel( 16 , "Bin 10 LowRes");
  h->GetYaxis()->SetBinLabel( 17 , "Bin 11 LowRes");
  h->GetYaxis()->SetBinLabel( 18 , "Bin 12 LowRes");
  h->GetYaxis()->SetBinLabel( 19 , "Bin 13 LowRes");
  //corr->SetMinimum(-4000);
  //corr->SetMaximum(4000);
  h->Draw("colz+text");

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

  float lumix = 0.955;
  float lumiy = 0.945;
  float lumifont = 42;
  
  float cmsx = 0.245;
  float cmsy = 0.940;
  float cmsTextFont   = 61;  // default is helvetic-bold
  float extrax = cmsx + 0.152;
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
  
  TFile* fout = new TFile("CorrelationMatrixHggRazor.root", "Recreate");
  h->Write("correlation");
  //TFile* fout = new TFile("CovarianceMatrixHggRazor.root", "Recreate");
  //h->Write("covariance");
  fout->Close();
  
}
