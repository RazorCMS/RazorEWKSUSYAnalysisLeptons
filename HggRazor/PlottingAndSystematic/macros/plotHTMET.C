#include "TFile.h"
#include "TTree.h"
#include "TH2F.h"
#include "TCanvas.h"
#include "TColor.h"
#include "TLine.h"
#include "TLegend.h"
#include "TLatex.h"
#include <string>
#include <iostream>

void plotHTMET(string category = "highpt") {

  //File for Run1
  // TFile *fileData = new TFile("/afs/cern.ch/user/s/sixie/eos/cms/store/group/phys_susy/razor/run1/HggRazor/AlexRaidDisk/DoublePhoton_22Jan2013_Run2012ABCD_v9.root","READ");

  //File without photon ID applied
  // TFile *fileData = new TFile("/afs/cern.ch/user/s/sixie/eos/cms/store/group/phys_susy/razor/Run2Analysis/HggRazor/2016/V3p3_PhotonCorrJune16/HggRazor_DoubleEG_2015+2016_GoodLumiGolden6p3ifb_MR150Skim.root","READ");

  //File with photon ID applied
  TFile *fileData = new TFile("/afs/cern.ch/user/s/sixie/eos/cms/store/group/phys_susy/razor/Run2Analysis/HggRazor/ICHEP2016Combined/V3p4_WithPhotonID/HggRazor_DoubleEG_Run2_MRSkim_2p3+4ifb.root","READ");
  TTree *tree = (TTree*)fileData->Get("HggRazor");
 

  string categoryCutString = "";
  if (category == "highpt") categoryCutString = " && pTGammaGamma >= 110";
  else if (category == "hzbb") categoryCutString = " && pTGammaGamma < 110 && (abs(mbbZ_L-91.2) < 25 || abs(mbbH_L-125) < 25)";
  else if (category == "hbb") categoryCutString = " && pTGammaGamma < 110 && abs(mbbH_L-125) < 25";
  else if (category == "zbb") categoryCutString = " && pTGammaGamma < 110 && abs(mbbZ_L-91.2) < 25 ";
  else if (category == "highres") categoryCutString = "&& abs(mbbH_L-125)>=25 && abs(mbbZ_L-91.2)>=25 && pTGammaGamma < 110 && sigmaMoverM < 0.0085 ";
  else if (category == "lowres") categoryCutString = " && abs(mbbH_L-125)>=25 && abs(mbbZ_L-91.2)>=25 && pTGammaGamma < 110 && !(sigmaMoverM < 0.0085) ";

  string signalRegionCutString = "&& mGammaGamma > 122 && mGammaGamma < 129";
  // if (category == "highpt") signalRegionCutString = " && mGammaGamma > 121.88 && mGammaGamma < 129.12";
  // else if (category == "hbb") signalRegionCutString = " && mGammaGamma > 121 && mGammaGamma < 130";
  // else if (category == "zbb") signalRegionCutString = " && mGammaGamma > 121 && mGammaGamma < 130 ";
  // else if (category == "highres") signalRegionCutString = " && mGammaGamma > 122.08 && mGammaGamma < 128.92 ";
  // else if (category == "lowres") signalRegionCutString = " && mGammaGamma > 120 && mGammaGamma < 131";

  TH2F *HTMETSideband = new TH2F("HTMETSideband",";H_{T} (GeV); MET (GeV) ; ", 135, 150,1500, 30 , 0.0, 300);
  TH2F *HTMETSignal = new TH2F("HTMETSignal",";H_{T} (GeV); MET (GeV) ; ", 135, 150,1500, 30 , 0.0, 300);

  // tree->Draw("t1Rsq:MR>>HTMETSideband", ("(abs(pho1Eta) <1.44 && abs(pho2Eta)<1.44 && (pho1Pt>40||pho2Pt>40)&&pho1Pt>25 && pho2Pt>25 && pho1passIso && pho2passIso && pho1passEleVeto && pho2passEleVeto && ((mGammaGamma > 105 && mGammaGamma < 120) || (mGammaGamma > 131 && mGammaGamma < 160)) && MR > 150 && t1Rsq >= 0.0 " + categoryCutString+ " )").c_str(),"");
  // tree->Draw("t1Rsq:MR>>HTMETSignal", ("abs(pho1Eta) <1.44 && abs(pho2Eta)<1.44 && (pho1Pt>40||pho2Pt>40)&&pho1Pt>25 && pho2Pt>25 && pho1passIso && pho2passIso && MR > 150 && t1Rsq >= 0.0 " + categoryCutString + signalRegionCutString).c_str(),"");
  tree->Draw("t1MET:HT>>HTMETSideband", ("(abs(pho1Eta) <1.44 && abs(pho2Eta)<1.44 && (pho1Pt>40||pho2Pt>40)&&pho1Pt>25 && pho2Pt>25 && pho1passIso && pho2passIso && ((mGammaGamma > 105 && mGammaGamma < 120) || (mGammaGamma > 131 && mGammaGamma < 160)) && MR > 150 && t1Rsq > 0.0 " + categoryCutString+ " )").c_str(),"");
  tree->Draw("t1MET:HT>>HTMETSignal", ("abs(pho1Eta) <1.44 && abs(pho2Eta)<1.44 && (pho1Pt>40||pho2Pt>40)&&pho1Pt>25 && pho2Pt>25 && pho1passIso && pho2passIso && MR > 150 && t1Rsq > 0.0 " + categoryCutString + signalRegionCutString).c_str(),"");

  std::cout << "draw string: " <<  ("(abs(pho1Eta) <1.44 && abs(pho2Eta)<1.44 && (pho1Pt>40||pho2Pt>40)&&pho1Pt>25 && pho2Pt>25 && ((mGammaGamma > 105 && mGammaGamma < 120) || (mGammaGamma > 131 && mGammaGamma < 160)) && MR > 150 && t1Rsq >= 0.0 " + categoryCutString+ " )") << "\n";


  //color palette
  const Int_t Number = 2;
  Double_t Red[Number]    =  { 0.90, 1.00};
  Double_t Green[Number]  =  { 0.90, 0.00};
  Double_t Blue[Number]   =  { 0.90, 0.00};
  Double_t Length[Number] =  { 0.00, 1.00};
  Int_t nb=50;
  TColor::CreateGradientColorTable(Number,Length,Red,Green,Blue,nb);
  

 //Draw Plots
 TCanvas *cv = 0;
 TLegend *legend= 0;
 TLatex *tex = 0;

 cv = new TCanvas("cv","cv", 800,600); 
 HTMETSideband->SetStats(0);
 HTMETSignal->SetStats(0);

 HTMETSideband->Draw("colz");
 //HTMETSignal->Draw("scat,same");
 HTMETSignal->SetMarkerStyle(20);
 HTMETSignal->SetMarkerColor(kBlack);
 if (category == "lowres") {
   HTMETSignal->SetMarkerSize(0.6);
 } else {
   HTMETSignal->SetMarkerSize(0.8);
 }

 string categoryText = "";
 if (category == "highpt") categoryText = "HighPt Category";
  else if (category == "hbb") categoryText = "Hbb Category";
  else if (category == "zbb") categoryText = "Zbb Category";
  else if (category == "highres") categoryText = "HighRes Category";
  else if (category == "lowres") categoryText = "LowRes Category";

 tex = new TLatex();
 tex->SetNDC();
 tex->SetTextSize(0.040);
 tex->SetTextFont(42);
 tex->SetTextColor(kBlack);
 tex->DrawLatex(0.7, 0.92, "6.3 fb^{-1} (13 TeV)");
 tex->DrawLatex(0.45, 0.92, categoryText.c_str());
 tex->Draw();
 
 TLatex *CMSLabel = new TLatex();
 CMSLabel->SetNDC();
 CMSLabel->SetTextSize(0.050);
 CMSLabel->SetTextFont(42);
 CMSLabel->SetTextColor(kBlack);
 CMSLabel->DrawLatex(0.1,0.92,"#bf{CMS}");
 CMSLabel->SetTextSize(0.045);
 CMSLabel->DrawLatex(0.19,0.92,"Preliminary");
 CMSLabel->Draw();
 
 HTMETSideband->SetFillColor(kRed);

 legend = new TLegend(0.50,0.70,0.87,0.87);
 legend->SetTextSize(0.04);
 legend->SetBorderSize(0);
 //legend->SetFillStyle(0);
 legend->AddEntry(HTMETSignal , "Signal Region" , "P");
 legend->AddEntry(HTMETSideband , "Sideband Region" , "F");
 legend->Draw();


 // if (category == "highpt") {
 //   TLine *l1 = new TLine(600,0,600,0.3);
 //   l1->SetLineWidth(3);
 //   l1->SetLineStyle(1);
 //   l1->SetLineColor(kGray+2);
 //   l1->Draw();

 //   TLine *l2 = new TLine(450,0,450,0.13);
 //   l2->SetLineWidth(3);
 //   l2->SetLineStyle(1);
 //   l2->SetLineColor(kGray+2);
 //   l2->Draw();

 //   TLine *l3 = new TLine(1250,0,1250,0.025);
 //   l3->SetLineWidth(3);
 //   l3->SetLineStyle(1);
 //   l3->SetLineColor(kGray+2);
 //   l3->Draw();

 //   TLine *l10 = new TLine(150,0.13,600,0.13);
 //   l10->SetLineWidth(3);
 //   l10->SetLineStyle(1);
 //   l10->SetLineColor(kGray+2);
 //   l10->Draw();

 //   TLine *l11 = new TLine(450,0.035,600,0.035);
 //   l11->SetLineWidth(3);
 //   l11->SetLineStyle(1);
 //   l11->SetLineColor(kGray+2);
 //   l11->Draw();

 //   TLine *l12 = new TLine(600,0.025,1500,0.025);
 //   l12->SetLineWidth(3);
 //   l12->SetLineStyle(1);
 //   l12->SetLineColor(kGray+2);
 //   l12->Draw();

 //   TLine *l13 = new TLine(600,0.015,1250,0.015);
 //   l13->SetLineWidth(3);
 //   l13->SetLineStyle(1);
 //   l13->SetLineColor(kGray+2);
 //   l13->Draw();

 // }


 // if (category == "hzbb") {


 // }
 // if (category == "hbb") {


 // }

 // if (category == "zbb") {
 

 // }

 // if (category == "highres") {
 //   TLine *l1 = new TLine(250,0,250,0.3);
 //   l1->SetLineWidth(3);
 //   l1->SetLineStyle(1);
 //   l1->SetLineColor(kGray+2);
 //   l1->Draw();

 //   TLine *l2 = new TLine(600,0,600,0.05);
 //   l2->SetLineWidth(3);
 //   l2->SetLineStyle(1);
 //   l2->SetLineColor(kGray+2);
 //   l2->Draw();

 //   TLine *l10 = new TLine(150,0.175,250,0.175);
 //   l10->SetLineWidth(3);
 //   l10->SetLineStyle(1);
 //   l10->SetLineColor(kGray+2);
 //   l10->Draw();

 //   TLine *l11 = new TLine(250,0.05,1500,0.05);
 //   l11->SetLineWidth(3);
 //   l11->SetLineStyle(1);
 //   l11->SetLineColor(kGray+2);
 //   l11->Draw();



 // }


 // if (category == "lowres") {
 //   TLine *l1 = new TLine(400,0,400,0.15);
 //   l1->SetLineWidth(3);
 //   l1->SetLineStyle(1);
 //   l1->SetLineColor(kGray+2);
 //   l1->Draw();

 //   TLine *l2 = new TLine(500,0,500,0.3);
 //   l2->SetLineWidth(3);
 //   l2->SetLineStyle(1);
 //   l2->SetLineColor(kGray+2);
 //   l2->Draw();

 //   TLine *l3 = new TLine(800,0,800,0.01);
 //   l3->SetLineWidth(3);
 //   l3->SetLineStyle(1);
 //   l3->SetLineColor(kGray+2);
 //   l3->Draw();

 //   TLine *l10 = new TLine(150,0.15,500,0.15);
 //   l10->SetLineWidth(3);
 //   l10->SetLineStyle(1);
 //   l10->SetLineColor(kGray+2);
 //   l10->Draw();

 //   TLine *l11 = new TLine(400,0.015,500,0.015);
 //   l11->SetLineWidth(3);
 //   l11->SetLineStyle(1);
 //   l11->SetLineColor(kGray+2);
 //   l11->Draw();

 //   TLine *l12 = new TLine(500,0.01,1500,0.01);
 //   l12->SetLineWidth(3);
 //   l12->SetLineStyle(1);
 //   l12->SetLineColor(kGray+2);
 //   l12->Draw();


 // }




 HTMETSignal->Draw("scat,same");


   //cv->SetGrid();
 cv->SaveAs( ("HggRazor_HTMET_" + category + ".png").c_str());
 cv->SaveAs( ("HggRazor_HTMET_" + category + ".pdf").c_str());

 

}

