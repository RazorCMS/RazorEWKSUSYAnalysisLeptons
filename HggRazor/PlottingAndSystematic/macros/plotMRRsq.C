#include "TFile.h"
#include "TTree.h"
#include "TH2F.h"
#include "TCanvas.h"
#include "TColor.h"
#include "TLine.h"
#include "TLegend.h"
#include "TLatex.h"
#include "TPaveText.h"
#include <string>
#include <iostream>

void plotMRRsq(string category = "highpt") {

  //File for Run1
  // TFile *fileData = new TFile("/afs/cern.ch/user/s/sixie/eos/cms/store/group/phys_susy/razor/run1/HggRazor/AlexRaidDisk/DoublePhoton_22Jan2013_Run2012ABCD_v9.root","READ");

  //File without photon ID applied
  // TFile *fileData = new TFile("/afs/cern.ch/user/s/sixie/eos/cms/store/group/phys_susy/razor/Run2Analysis/HggRazor/2016/V3p3_PhotonCorrJune16/HggRazor_DoubleEG_2015+2016_GoodLumiGolden6p3ifb_MR150Skim.root","READ");

  //File with photon ID applied
  TFile *fileData = new TFile("/afs/cern.ch/user/z/zhicaiz/eos/cms/store/group/phys_susy/razor/Run2Analysis/HggRazor/2016/V3p4_PhotonCorrJuly20_RegularSelectionSequence_20160720/HggRazor_SMS-T2bH_mSbottom-300_mLSP-1_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_MiniAODv1_1pb_weighted.root","READ");
  TTree *tree = (TTree*)fileData->Get("HggRazor");

  string categoryCutString = "";
  if (category == "highpt") categoryCutString = "*(pTGammaGamma >= 110)";
  else if (category == "hzbb") categoryCutString = "*(pTGammaGamma < 110 && (abs(mbbZ_L-91.2) < 25 || abs(mbbH_L-125) < 25))";
  else if (category == "hbb") categoryCutString = "*(pTGammaGamma < 110 && abs(mbbH_L-125) < 25)";
  else if (category == "zbb") categoryCutString = "*(pTGammaGamma < 110 && abs(mbbZ_L-91.2) < 25)";
  else if (category == "highres") categoryCutString = "*(abs(mbbH_L-125)>=25 && abs(mbbZ_L-91.2)>=25 && pTGammaGamma < 110 && sigmaMoverM < 0.0085)";
  else if (category == "lowres") categoryCutString = "*(abs(mbbH_L-125)>=25 && abs(mbbZ_L-91.2)>=25 && pTGammaGamma < 110 && !(sigmaMoverM < 0.0085))";

  string signalRegionCutString = "*(mGammaGamma > 122 && mGammaGamma < 129)";

  TH2F *MRRsqSideband = new TH2F("MRRsqSideband",";M_{R} (GeV); R^{2} ; ", 135, 150,1500, 30 , 0.0, 0.3);
  TH2F *MRRsqSignal = new TH2F("MRRsqSignal",";M_{R} (GeV); R^{2} ; ", 135, 150,1500, 30 , 0.0, 0.3);

  //tree->Draw("t1Rsq:MR>>MRRsqSideband", ("(abs(pho1Eta) <1.44 && abs(pho2Eta)<1.44 && (pho1Pt>40||pho2Pt>40)&&pho1Pt>25 && pho2Pt>25 && pho1passIso && pho2passIso && pho1passEleVeto && pho2passEleVeto && ((mGammaGamma > 105 && mGammaGamma < 120) || (mGammaGamma > 131 && mGammaGamma < 160)) && MR > 150 && t1Rsq >= 0.0 " + categoryCutString+ " )").c_str(),"");
  tree->Draw("t1Rsq:MR>>MRRsqSignal", ("15215*weight*pileupWeight*triggerEffWeight*btagCorrFactor*(abs(pho1Eta) <1.44 && abs(pho2Eta)<1.44 && (pho1Pt>40||pho2Pt>40)&&pho1Pt>25 && pho2Pt>25 && pho1passIso && pho2passIso && MR > 150 && t1Rsq >= 0.0)" + categoryCutString + signalRegionCutString).c_str(),"");

  //std::cout << "draw string: " <<  ("( abs(pho1Eta) <1.44 && abs(pho2Eta)<1.44 && (pho1Pt>40||pho2Pt>40)&&pho1Pt>25 && pho2Pt>25 && ((mGammaGamma > 105 && mGammaGamma < 120) || (mGammaGamma > 131 && mGammaGamma < 160)) && MR > 150 && t1Rsq >= 0.0 " + categoryCutString+ " )") << "\n";


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
 cv->SetRightMargin(0.125);
 //MRRsqSideband->SetStats(0);
 MRRsqSignal->SetStats(0);

 //MRRsqSideband->Draw("colz");

 MRRsqSignal->Draw("colz");

MRRsqSignal->GetXaxis()->SetTitleSize(0.05);
MRRsqSignal->GetXaxis()->SetTitleOffset(0.85);
MRRsqSignal->GetXaxis()->SetLabelSize(0.04);
MRRsqSignal->GetYaxis()->SetTitleSize(0.05);
MRRsqSignal->GetYaxis()->SetTitleOffset(0.85);
MRRsqSignal->GetYaxis()->SetLabelSize(0.04);

 //MRRsqSignal->SetMarkerStyle(20);
 //MRRsqSignal->SetMarkerColor(kBlack);
 /*if (category == "lowres") {
   MRRsqSignal->SetMarkerSize(0.6);
   } else {
   MRRsqSignal->SetMarkerSize(0.8);
   }*/

 string categoryText = "";
 if (category == "highpt") categoryText = "HighPt Category";
 else if (category == "hbb") categoryText = "Hbb Category";
 else if (category == "zbb") categoryText = "Zbb Category";
 else if (category == "hzbb") categoryText = "H(#gamma#gamma)-H/Z(bb) Category";
 else if (category == "highres") categoryText = "HighRes Category";
 else if (category == "lowres") categoryText = "LowRes Category";
 
 tex = new TLatex();
 tex->SetNDC();
 tex->SetTextSize(0.040);
 tex->SetTextFont(42);
 tex->SetTextColor(kBlack);
 tex->DrawLatex(0.7, 0.92, "15.2 fb^{-1} (13 TeV)");
 tex->DrawLatex((category=="hzbb")?0.4:0.45, 0.92, categoryText.c_str());
 tex->Draw();
 
 TLatex *CMSLabel = new TLatex();
 CMSLabel->SetNDC();
 CMSLabel->SetTextSize(0.050);
 CMSLabel->SetTextFont(42);
 CMSLabel->SetTextColor(kBlack);
 CMSLabel->DrawLatex(0.1,0.92,"#bf{CMS}");
 CMSLabel->SetTextSize(0.045);
 CMSLabel->DrawLatex(0.19,0.92,"Simulation");
 CMSLabel->Draw();

 TLatex *model = new TLatex();
 model->SetNDC();
 model->SetTextSize(0.045);
 model->SetTextFont(42);
 model->SetTextColor(kBlack);
 model->DrawLatex(0.5,0.84, "m_{#tilde{b}} = 300 GeV, m_{#chi} = 1 GeV");
 model->Draw();
 
 MRRsqSideband->SetFillColor(kRed);

 legend = new TLegend(0.50,0.70,0.87,0.87);
 legend->SetTextSize(0.04);
 legend->SetBorderSize(0);
 //legend->SetFillStyle(0);
 legend->AddEntry(MRRsqSignal , "Signal Region" , "P");
 //legend->AddEntry(MRRsqSideband , "Sideband Region" , "F");
 //legend->Draw();


 if (category == "highpt") {
   TLine *l1 = new TLine(600,0,600,0.3);
   l1->SetLineWidth(3);
   l1->SetLineStyle(1);
   l1->SetLineColor(kGray+2);
   l1->Draw();

   TLine *l2 = new TLine(450,0,450,0.13);
   l2->SetLineWidth(3);
   l2->SetLineStyle(1);
   l2->SetLineColor(kGray+2);
   l2->Draw();

   TLine *l3 = new TLine(1250,0,1250,0.025);
   l3->SetLineWidth(3);
   l3->SetLineStyle(1);
   l3->SetLineColor(kGray+2);
   l3->Draw();

   TLine *l10 = new TLine(150,0.13,600,0.13);
   l10->SetLineWidth(3);
   l10->SetLineStyle(1);
   l10->SetLineColor(kGray+2);
   l10->Draw();

   TLine *l11 = new TLine(450,0.035,600,0.035);
   l11->SetLineWidth(3);
   l11->SetLineStyle(1);
   l11->SetLineColor(kGray+2);
   l11->Draw();

   TLine *l12 = new TLine(600,0.025,1500,0.025);
   l12->SetLineWidth(3);
   l12->SetLineStyle(1);
   l12->SetLineColor(kGray+2);
   l12->Draw();

   TLine *l13 = new TLine(600,0.015,1250,0.015);
   l13->SetLineWidth(3);
   l13->SetLineStyle(1);
   l13->SetLineColor(kGray+2);
   l13->Draw();

 }


 if (category == "hzbb") {

  TPaveText *bin8 = new TPaveText(170,0.28,220,0.29);
  bin8->SetFillColor(0);
  bin8->SetShadowColor(0);
  bin8->SetLineColor(0);
  //bin8->SetNDC();
  bin8->SetTextSize(0.05);
  //bin8->SetTextFont(42);
  //bin8->SetTextColor(kBlack);
  bin8->AddText("8");
  bin8->Draw();
 
}
 if (category == "hbb") {


 }

 if (category == "zbb") {
 

 }

 if (category == "highres" || category == "lowres") {
   TLine *l1 = new TLine(250,0,250,0.3);
   l1->SetLineWidth(3);
   l1->SetLineStyle(1);
   l1->SetLineColor(kGray+2);
   l1->Draw();

   TLine *l2 = new TLine(600,0,600,0.05);
   l2->SetLineWidth(3);
   l2->SetLineStyle(1);
   l2->SetLineColor(kGray+2);
   l2->Draw();

   TLine *l10 = new TLine(150,0.175,250,0.175);
   l10->SetLineWidth(3);
   l10->SetLineStyle(1);
   l10->SetLineColor(kGray+2);
   l10->Draw();

   TLine *l11 = new TLine(250,0.05,1500,0.05);
   l11->SetLineWidth(3);
   l11->SetLineStyle(1);
   l11->SetLineColor(kGray+2);
   l11->Draw();

 }


 /* if (category == "lowres") {
   TLine *l1 = new TLine(400,0,400,0.15);
   l1->SetLineWidth(3);
   l1->SetLineStyle(1);
   l1->SetLineColor(kGray+2);
   l1->Draw();

   TLine *l2 = new TLine(500,0,500,0.3);
   l2->SetLineWidth(3);
   l2->SetLineStyle(1);
   l2->SetLineColor(kGray+2);
   l2->Draw();

   TLine *l3 = new TLine(800,0,800,0.01);
   l3->SetLineWidth(3);
   l3->SetLineStyle(1);
   l3->SetLineColor(kGray+2);
   l3->Draw();

   TLine *l10 = new TLine(150,0.15,500,0.15);
   l10->SetLineWidth(3);
   l10->SetLineStyle(1);
   l10->SetLineColor(kGray+2);
   l10->Draw();

   TLine *l11 = new TLine(400,0.015,500,0.015);
   l11->SetLineWidth(3);
   l11->SetLineStyle(1);
   l11->SetLineColor(kGray+2);
   l11->Draw();

   TLine *l12 = new TLine(500,0.01,1500,0.01);
   l12->SetLineWidth(3);
   l12->SetLineStyle(1);
   l12->SetLineColor(kGray+2);
   l12->Draw();

   }*/


 if (category == "highpt") {
   TPaveText *bin0 = new TPaveText(620,0.28,670,0.29);
   bin0->SetFillColor(0);
   bin0->SetShadowColor(0);
   bin0->SetLineColor(0);
   //bin0->SetNDC();
   bin0->SetTextSize(0.05);
   //bin0->SetTextFont(42);
   //bin0->SetTextColor(kBlack);
   bin0->AddText("0");
   bin0->Draw();

   TPaveText *bin1 = new TPaveText(170,0.28,220,0.29);
   bin1->SetFillColor(0);
   bin1->SetShadowColor(0);
   bin1->SetLineColor(0);
   //bin1->SetNDC();
   bin1->SetTextSize(0.05);
   //bin1->SetTextFont(42);
   //bin1->SetTextColor(kBlack);
   bin1->AddText("1");
   bin1->Draw();

   TPaveText *bin2 = new TPaveText(1260,0.01,1310,0.02);
   bin2->SetFillColor(0);
   bin2->SetFillStyle(0);
   bin2->SetShadowColor(0);
   bin2->SetBorderSize(0);
   bin2->SetLineColorAlpha(0,0.0);
   //bin2->SetLineColor(0);
   //bin2->SetLineStyle(0);
   //bin2->SetNDC();
   bin2->SetTextSize(0.05);
   //bin2->SetTextFont(42);
   //bin2->SetTextColor(kBlack);
   bin2->AddText("2");
   bin2->Draw();

   TPaveText *bin3 = new TPaveText(170,0.115,220,0.125);
   bin3->SetFillColor(0);
   bin3->SetFillStyle(0);
   bin3->SetShadowColor(0);
   bin3->SetBorderSize(0);
   bin3->SetLineColorAlpha(0,0.0);
   //bin3->SetLineColor(0);
   //bin3->SetLineStyle(0);
   //bin3->SetNDC();
   bin3->SetTextSize(0.05);
   //bin3->SetTextFont(42);
   //bin3->SetTextColor(kBlack);
   bin3->AddText("3");
   bin3->Draw();

   TPaveText *bin4 = new TPaveText(540,0.002,590,0.012);
   bin4->SetFillColor(0);
   bin4->SetFillStyle(0);
   bin4->SetShadowColor(0);
   bin4->SetBorderSize(0);
   bin4->SetLineColorAlpha(0,0.0);
   //bin4->SetLineColor(0);
   //bin4->SetLineStyle(0);
   //bin4->SetNDC();
   bin4->SetTextSize(0.05);
   //bin4->SetTextFont(42);
   //bin4->SetTextColor(kBlack);
   bin4->AddText("4");
   bin4->Draw();

   TPaveText *bin5 = new TPaveText(460,0.115,510,0.125);
   bin5->SetFillColor(0);
   bin5->SetFillStyle(0);
   bin5->SetShadowColor(0);
   bin5->SetBorderSize(0);
   bin5->SetLineColorAlpha(0,0.0);
   //bin5->SetLineColor(0);
   //bin5->SetLineStyle(0);
   //bin5->SetNDC();
   bin5->SetTextSize(0.05);
   //bin5->SetTextFont(42);
   //bin5->SetTextColor(kBlack);
   bin5->AddText("5");
   bin5->Draw();

   TPaveText *bin6 = new TPaveText(610,0.002,660,0.012);
   bin6->SetFillColor(0);
   bin6->SetFillStyle(0);
   bin6->SetShadowColor(0);
   bin6->SetBorderSize(0);
   bin6->SetLineColorAlpha(0,0.0);
   //bin6->SetLineColor(0);
   //bin6->SetLineStyle(0);
   //bin6->SetNDC();
   bin6->SetTextSize(0.05);
   //bin6->SetTextFont(42);
   //bin6->SetTextColor(kBlack);
   bin6->AddText("6");
   bin6->Draw();

   TPaveText *bin7 = new TPaveText(1190,0.015,1240,0.025);
   bin7->SetFillColor(0);
   bin7->SetFillStyle(0);
   bin7->SetShadowColor(0);
   bin7->SetBorderSize(0);
   bin7->SetLineColorAlpha(0,0.0);
   //bin7->SetLineColor(0);
   //bin7->SetLineStyle(0);
   //bin7->SetNDC();
   bin7->SetTextSize(0.05);
   //bin7->SetTextFont(42);
   //bin7->SetTextColor(kBlack);
   bin7->AddText("7");
   bin7->Draw();
}

 if (category == "highres" || category == "lowres") {
   TPaveText *bin9 = new TPaveText(160,0.16,220,0.17);
   bin9->SetFillColor(0);
   bin9->SetFillStyle(0);
   bin9->SetShadowColor(0);
   bin9->SetBorderSize(0);
   bin9->SetLineColorAlpha(0,0.0);
   //bin9->SetLineColor(0);
   //bin9->SetLineStyle(0);
   //bin9->SetNDC();
   bin9->SetTextSize(0.05);
   //bin9->SetTextFont(42);
   //bin9->SetTextColor(kBlack);
   bin9->AddText("9");
   bin9->Draw();

   TPaveText *bin10 = new TPaveText(160,0.28,220,0.29);
   bin10->SetFillColor(0);
   bin10->SetFillStyle(0);
   bin10->SetShadowColor(0);
   bin10->SetBorderSize(0);
   bin10->SetLineColorAlpha(0,0.0);
   //bin10->SetLineColor(0);
   //bin10->SetLineStyle(0);
   //bin10->SetNDC();
   bin10->SetTextSize(0.05);
   //bin10->SetTextFont(42);
   //bin10->SetTextColor(kBlack);
   bin10->AddText("10");
   bin10->Draw();

   TPaveText *bin11 = new TPaveText(270,0.28,320,0.29);
   bin11->SetFillColor(0);
   bin11->SetFillStyle(0);
   bin11->SetShadowColor(0);
   bin11->SetBorderSize(0);
   bin11->SetLineColorAlpha(0,0.0);
   //bin11->SetLineColor(0);
   //bin11->SetLineStyle(0);
   //bin11->SetNDC();
   bin11->SetTextSize(0.05);
   //bin11->SetTextFont(42);
   //bin11->SetTextColor(kBlack);
   bin11->AddText("11");
   bin11->Draw();

   TPaveText *bin12 = new TPaveText(270,0.03,320,0.04);
   bin12->SetFillColor(0);
   bin12->SetFillStyle(0);
   bin12->SetShadowColor(0);
   bin12->SetBorderSize(0);
   bin12->SetLineColorAlpha(0,0.0);
   //bin12->SetLineColor(0);
   //bin12->SetLineStyle(0);
   //bin12->SetNDC();
   bin12->SetTextSize(0.05);
   //bin12->SetTextFont(42);
   //bin12->SetTextColor(kBlack);
   bin12->AddText("12");
   bin12->Draw();

   TPaveText *bin13 = new TPaveText(1430,0.03,1480,0.04);
   bin13->SetFillColor(0);
   bin13->SetFillStyle(0);
   bin13->SetShadowColor(0);
   bin13->SetBorderSize(0);
   bin13->SetLineColorAlpha(0,0.0);
   //bin13->SetLineColor(0);
   //bin13->SetLineStyle(0);
   //bin13->SetNDC();
   bin13->SetTextSize(0.05);
   //bin13->SetTextFont(42);
   //bin13->SetTextColor(kBlack);
   bin13->AddText("13");
   bin13->Draw();
}

 //MRRsqSignal->Draw("scat,same");


   //cv->SetGrid();
 cv->SaveAs( ("HggRazor_MRRsq_" + category + ".png").c_str());
 cv->SaveAs( ("HggRazor_MRRsq_" + category + ".pdf").c_str());

 

}

