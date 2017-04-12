#if !defined(__CINT__) || defined(__MAKECINT__)
#include <TROOT.h>
#include <TSystem.h>
#include <TFile.h>
#include <TTree.h>
#include <TLegend.h>
#include <TGaxis.h>
#include <vector>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <TH1.h>

#include <CompareHggMC.hh>

TString cat_lab[5] = { "Inclusive", "HighPT","HZbb","HighRes","LowRes" };

#endif

void CompareHggMC() { return; }

void draw(Category cat, TString var,
          Config fB, vector<Config> fC,
          Int_t nbins, Int_t xmin, Int_t xmax) {
  
  TCanvas *c1 = MakeCanvas("c1", "c1", 800, 800);

  c1->Divide(1,2,0,0);
  c1->cd(1)->SetPad(0,0.3,1.0,1.0);
  c1->cd(1)->SetTopMargin(0.1);
  c1->cd(1)->SetBottomMargin(0.01); //0.01
  c1->cd(1)->SetLeftMargin(0.15);
  c1->cd(1)->SetRightMargin(0.07);
  c1->cd(1)->SetTickx(1);
  c1->cd(1)->SetTicky(1);

  c1->cd(2)->SetPad(0,0,1.0,0.3);
  c1->cd(2)->SetTopMargin(0.01);
  c1->cd(2)->SetBottomMargin(0.45);//0.25
  c1->cd(2)->SetLeftMargin(0.15);
  c1->cd(2)->SetRightMargin(0.07);
  c1->cd(2)->SetTickx(1);
  c1->cd(2)->SetTicky(1);
  gStyle->SetTitleOffset(1.100,"Y");

  c1->cd(1);

  TH1D *hB = returnPlot(cat, var, fB, nbins, xmin, xmax);
  vector<TH1D*> hComps;
  for (int i=0; i<fC.size(); i++) {
    hComps.push_back(returnPlot(cat, var, fC[i], nbins, xmin, xmax));
  }

  hB->SetTitle("");
  hB->GetYaxis()->SetTitle("Events [10ifb]");

  TString xtitle=cat_lab[cat];
  xtitle += " ";
  xtitle += var;

  hB->GetYaxis()->SetRangeUser(0.0001, 1.3*hB->GetMaximum());
  hB->GetYaxis()->SetNdivisions(310,kTRUE);

  hB->DrawCopy("hist");

  for (int i=0; i<hComps.size(); i++) {
    hComps[i]->DrawCopy("histsame");
  }

  TLegend *leg = new TLegend(0.5, 0.6, 0.9, 0.85);
  leg->SetShadowColor(0); leg->SetFillColor(0); leg->SetLineColor(0);
  leg->AddEntry(hB, fB.getLabel(), "l");
  for (int i=0; i<hComps.size(); i++) {
    leg->AddEntry(hComps[i], fC[i].getLabel(), "l");
  }

  leg->Draw();

  c1->cd(2);

  TH1D *rB = returnRatio(hB,hB,"hBB");
  vector<TH1D*> rComps;
  for (int i=0; i<fC.size(); i++) {
    char rname[50];
    sprintf(rname, "hb%i",i);
    rComps.push_back(returnRatio(hComps[i],hB,rname));
  }

  rB->GetYaxis()->SetRangeUser(0,5);
  rB->GetXaxis()->SetTitle(xtitle);
  rB->GetYaxis()->SetTitle("Ratio");

  rB->DrawCopy("hist");
  for (int i=0; i<rComps.size(); i++) {
    rComps[i]->DrawCopy("histsame");
  }

  c1->SaveAs(cat_lab[cat]+"/"+fB.getSampleName()+"_compare_"+var+".png");

  c1->cd(1);
  c1->cd(1)->SetLogy();

  hB->GetYaxis()->SetRangeUser(3e-7, 130*hB->GetMaximum());

  hB->DrawCopy("hist");

  for (int i=0; i<hComps.size(); i++) {
    hComps[i]->DrawCopy("histsame");
  }  

  leg->Draw();

  c1->SaveAs(cat_lab[cat]+"/"+fB.getSampleName()+"_compare_log_"+var+".png");

  delete hB; delete rB;
  hB=0; rB=0;
  for (int i=0; i<hComps.size(); i++) {
    delete hComps[i]; delete rComps[i];
    hComps[i]=0; rComps[i]=0;
  }
  delete c1; delete leg;
  c1=0; leg=0;

}

TH1D* returnPlot(Category cat, TString var, Config f,
                 Int_t nbins, Double_t xmin, Double_t xmax) {
  
  TTree *t1 = (TTree*) f.file->Get("HggRazor");
  TH1D *h1 = new TH1D(f.getSampleName(), f.getSampleName(), nbins, xmin, xmax);
  h1->SetLineWidth(3);
  h1->SetLineColor(f.getLineColor());
  h1->SetLineStyle(f.getLineStyle());
  
  TString cut = "(mGammaGamma > 103. && mGammaGamma < 160. && pho1passIso == 1 && pho2passIso == 1 && pho1passEleVeto == 1 && pho2passEleVeto == 1 && abs(pho1Eta) <1.48 && abs(pho2Eta)<1.48 && (pho1Pt>40||pho2Pt>40)  && pho1Pt> 25. && pho2Pt>25.)*weight*pileupWeight*btagCorrFactor*triggerEffWeight*10000";
  TString categoryCutString;

  if      (cat == inc)     categoryCutString = "";
  else if (cat == highpt)  categoryCutString = "*(pTGammaGamma >= 110)";
  else if (cat == hzbb)    categoryCutString = "*(pTGammaGamma < 110 && ( abs(mbbH_L-125.) < 15. || ( abs(mbbH_L-125.) >= 15. && abs(mbbZ_L-91.) < 15 ) ))";
  else if (cat == highres) categoryCutString = "*(pTGammaGamma < 110 && abs(mbbH_L-125.) >= 15 && abs(mbbZ_L-91.) >= 15 && sigmaMoverM < 0.0085)";
  else if (cat == lowres)  categoryCutString = "*(pTGammaGamma < 110 && abs(mbbH_L-125.) >= 15 && abs(mbbZ_L-91.) >= 15 && sigmaMoverM >= 0.0085)";

  t1->Draw(var+">>"+f.getSampleName(), cut+categoryCutString);

  return h1;

}

TH1D* returnRatio(TH1D* h, TH1D* b, TString name) {

  TH1D* hRatio = new TH1D(name, "", h->GetNbinsX(), h->GetXaxis()->GetXmin(), h->GetXaxis()->GetXmax());
  hRatio->SetLineColor(h->GetLineColor());
  hRatio->SetLineStyle(h->GetLineStyle());
  hRatio->SetLineWidth(h->GetLineWidth());

  hRatio->GetYaxis()->SetTitleOffset(0.42);
  hRatio->GetYaxis()->SetTitleSize(0.13);
  hRatio->GetYaxis()->SetLabelSize(0.10);
  hRatio->GetXaxis()->SetTitleOffset(1.2);
  hRatio->GetXaxis()->SetTitleSize(0.13);
  hRatio->GetXaxis()->SetLabelSize(0.12);
  //hRatio->GetXaxis()->CenterTitle();
  hRatio->GetYaxis()->CenterTitle();
  hRatio->GetYaxis()->SetNdivisions(303,kTRUE);

  for (Int_t i=1; i<h->GetNbinsX()+1; i++) {
    Double_t val = h->GetBinContent(i);
    if (b->GetBinContent(i)>0) hRatio->SetBinContent(i, val/b->GetBinContent(i));
    else hRatio->SetBinContent(i, 0);
  }
  return hRatio;
}

/*
TH1D* returnRatio(TH1D* h, TGraph* b, TString name) {
  TH1D* hRatio = new TH1D(name, "", h->GetNbinsX(), h->GetXaxis()->GetXmin(), h->GetXaxis()->GetXmax());
  hRatio->SetLineColor(h->GetLineColor());
  hRatio->SetLineStyle(h->GetLineStyle());
  hRatio->SetLineWidth(h->GetLineWidth());

  hRatio->GetYaxis()->SetTitleOffset(0.42);
  hRatio->GetYaxis()->SetTitleSize(0.13);
  hRatio->GetYaxis()->SetLabelSize(0.10);
  hRatio->GetXaxis()->SetTitleOffset(1.2);
  hRatio->GetXaxis()->SetTitleSize(0.13);
  hRatio->GetXaxis()->SetLabelSize(0.12);
  //hRatio->GetXaxis()->CenterTitle();
  hRatio->GetYaxis()->CenterTitle();
  hRatio->GetYaxis()->SetNdivisions(303,kTRUE);

  for (Int_t i=1; i<h->GetNbinsX()+1; i++) {
    Double_t x=0, y=0;
    b->GetPoint(i-1, x, y);
    Double_t val = h->GetBinContent(i) - y;
    if (y!=0) hRatio->SetBinContent(i, val/y);
    else hRatio->SetBinContent(i, 0);
  }
  return hRatio;
}
*/
