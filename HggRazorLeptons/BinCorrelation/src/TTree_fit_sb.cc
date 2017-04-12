#define tree_fit_sb_cxx
#include <iostream>

#include "TTree_fit_sb.hh"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <RooRealVar.h>
#include <RooMsgService.h>
//#include <MsgTopic.h>
#include <RooGlobalFunc.h>

void tree_fit_sb::Loop()
{
//   In a ROOT session, you can do:
//      root> .L tree_fit_sb.C
//      root> tree_fit_sb t
//      root> t.GetEntry(12); // Fill t data members with entry number 12
//      root> t.Show();       // Show values of entry 12
//      root> t.Show(16);     // Read and show values of entry 16
//      root> t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
  RooMsgService::instance().getStream(1).removeTopic(RooFit::NumIntegration) ;
  if (fChain == 0) return;

   TH1F* h = new TH1F("h", "", 100, 0, 1 );
   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      if ( jentry % 100 == 0 ) std::cout << "entry #" << jentry << std::endl;
      //std::cout << "Photon_Trigger: " << Photon_Trigger << std::endl;
      this->GetSystematics();
      this->SetSystematics();
      
      h->Fill( this->GetIntegral( "pdf_binch1_nuis", "mGammaGamma_bin0" ) );
      this->GetIntegral( "pdf_binch2_nuis", "mGammaGamma_bin1" );
      this->GetIntegral( "pdf_binch7_nuis", "mGammaGamma_bin2" );
      this->GetIntegral( "pdf_binch8_nuis", "mGammaGamma_bin3" );
      this->GetIntegral( "pdf_binch9_nuis", "mGammaGamma_bin4" );
      this->GetIntegral( "pdf_binch10_nuis", "mGammaGamma_bin5" );
      this->GetIntegral( "pdf_binch11_nuis", "mGammaGamma_bin6" );
      this->GetIntegral( "pdf_binch12_nuis", "mGammaGamma_bin7" );
      this->GetIntegral( "pdf_binch13_nuis", "mGammaGamma_bin8" );

      this->GetIntegral( "pdf_binch14_highResBin9_nuis", "mGammaGamma_bin9" );
      this->GetIntegral( "pdf_binch14_lowResBin9_nuis", "mGammaGamma_bin14" );
      
      this->GetIntegral( "pdf_binch3_highResBin10_nuis", "mGammaGamma_bin10" );
      this->GetIntegral( "pdf_binch3_lowResBin10_nuis", "mGammaGamma_bin15" );
      
      this->GetIntegral( "pdf_binch4_highResBin11_nuis", "mGammaGamma_bin11" );
      this->GetIntegral( "pdf_binch4_lowResBin11_nuis", "mGammaGamma_bin16" );
      
      this->GetIntegral( "pdf_binch5_highResBin12_nuis", "mGammaGamma_bin12" );
      this->GetIntegral( "pdf_binch5_lowResBin12_nuis", "mGammaGamma_bin17" );
      
      this->GetIntegral( "pdf_binch6_highResBin13_nuis", "mGammaGamma_bin13" );
      this->GetIntegral( "pdf_binch6_lowResBin13_nuis", "mGammaGamma_bin18" );
      
      
      // if (Cut(ientry) < 0) continue;
   }
   TFile *fout = new TFile("test_corr.root", "RECREATE");
   h->Write();
   fout->Close();
};

double tree_fit_sb::GetIntegral( TString pdfName, TString varName )
{
  RooAbsPdf* myPdf = ws->pdf( pdfName );
  //RooArgSet *params = myPdf->getParameters(*data);
  //std::cout << params->getRealValue("Photon_Trigger") << std::endl;
  //params->Print();
  RooRealVar *mgg = ws->var( varName );
  //RooRealVar *mgg = w->var("mGammaGamma_bin9");
  mgg->setMin( 103. );
  mgg->setMax( 160. );
  mgg->setUnit( "GeV" );
  mgg->setBins(57);
  mgg->setRange( "signal", 122, 129. );
  mgg->setRange( "high", 135., 160. );
  mgg->setRange( "low", 103., 120. );
  mgg->setRange( "full", 103., 160. );
  mgg->setRange( "Full", 103., 160. );

  myPdf->createIntegral( *mgg );
  RooAbsReal* igx = myPdf->createIntegral( *mgg );
  //std::cout << Nbkg->getVal() << " +/- " << Nbkg->getError() << std::endl;
  RooAbsReal* igx_sig = myPdf->createIntegral( *mgg, RooFit::NormSet(*mgg), RooFit::Range("signal"));
  //std::cout << "sig: " << igx_sig->getVal() << std::endl;
  return igx_sig->getVal();
};

void tree_fit_sb::SetSystematics()
{
  ws->var("CMS_Lumi")->setVal(systematics[0]);
  ws->var("Photon_Trigger")->setVal(systematics[1]);
  ws->var("SMH_JES")->setVal(systematics[2]);
  ws->var("SMH_btag")->setVal(systematics[3]);
  ws->var("SMH_misstag")->setVal(systematics[4]);
  //facRenScale
  for ( int i = 0; i <= 13; i++ )  ws->var(Form("SMH_facRenScale_bin%d", i))->setVal(systematics[5+i]);
  //facScale
  for ( int i = 0; i <= 13; i++ )  ws->var(Form("SMH_facScale_bin%d", i))->setVal(systematics[19+i]);
  //renScale
  for ( int i = 0; i <= 13; i++ )  ws->var(Form("SMH_renScale_bin%d", i))->setVal(systematics[33+i]);
  //PDFs
  for ( int i = 0; i <= 59; i++ )  ws->var(Form("SMH_pdf%d", i))->setVal(systematics[47+i]);

  //-----------------------------------
  //S i g n a l   S y s t e m a t i c s 
  //-----------------------------------
  ws->var("Signal_ISR")->setVal(systematics[107]);
  ws->var("Signal_JES")->setVal(systematics[108]);
  ws->var("Signal_btag")->setVal(systematics[109]);
  ws->var("Signal_misstag")->setVal(systematics[110]);
  
  //facRenScale
  for ( int i = 0; i <= 13; i++ )  ws->var(Form("Signal_facRenScale_bin%d", i))->setVal(systematics[111+i]);
  //facScale
  for ( int i = 0; i <= 13; i++ )  ws->var(Form("Signal_facScale_bin%d", i))->setVal(systematics[125+i]);
  //renScale
  for ( int i = 0; i <= 13; i++ )  ws->var(Form("Signal_renScale_bin%d", i))->setVal(systematics[139+i]);
  //PDFs
  for ( int i = 0; i <= 57; i++ )  ws->var(Form("Signal_pdf%d", i))->setVal(systematics[153+i]);
  
  ws->var("mu_Global")->setVal(systematics[213]);
  ws->var("hzbb_mu_Global")->setVal(systematics[214]);
  ws->var("highpt_mu_Global")->setVal(systematics[215]);
  ws->var("lowres_mu_Global")->setVal(systematics[216]);
};

void tree_fit_sb::GetSystematics()
{
  systematics[0] = CMS_Lumi;
  systematics[1] = Photon_Trigger;
  systematics[2] = SMH_JES;
  systematics[3] = SMH_btag;
  systematics[4] = SMH_misstag;
  systematics[5] = SMH_facRenScale_bin0;
  systematics[6] = SMH_facRenScale_bin1;
  systematics[7] = SMH_facRenScale_bin2;
  systematics[8] = SMH_facRenScale_bin3;
  systematics[9] = SMH_facRenScale_bin4;
  systematics[10] = SMH_facRenScale_bin5;
  systematics[11] = SMH_facRenScale_bin6;
  systematics[12] = SMH_facRenScale_bin7;
  systematics[13] = SMH_facRenScale_bin8;
  systematics[14] = SMH_facRenScale_bin9;
  systematics[15] = SMH_facRenScale_bin10;
  systematics[16] = SMH_facRenScale_bin11;
  systematics[17] = SMH_facRenScale_bin12;
  systematics[18] = SMH_facRenScale_bin13;
  systematics[19] = SMH_facScale_bin0;
  systematics[20] = SMH_facScale_bin1;
  systematics[21] = SMH_facScale_bin2;
  systematics[22] = SMH_facScale_bin3;
  systematics[23] = SMH_facScale_bin4;
  systematics[24] = SMH_facScale_bin5;
  systematics[25] = SMH_facScale_bin6;
  systematics[26] = SMH_facScale_bin7;
  systematics[27] = SMH_facScale_bin8;
  systematics[28] = SMH_facScale_bin9;
  systematics[29] = SMH_facScale_bin10;
  systematics[30] = SMH_facScale_bin11;
  systematics[31] = SMH_facScale_bin12;
  systematics[32] = SMH_facScale_bin13;
  systematics[33] = SMH_renScale_bin0;
  systematics[34] = SMH_renScale_bin1;
  systematics[35] = SMH_renScale_bin2;
  systematics[36] = SMH_renScale_bin3;
  systematics[37] = SMH_renScale_bin4;
  systematics[38] = SMH_renScale_bin5;
  systematics[39] = SMH_renScale_bin6;
  systematics[40] = SMH_renScale_bin7;
  systematics[41] = SMH_renScale_bin8;
  systematics[42] = SMH_renScale_bin9;
  systematics[43] = SMH_renScale_bin10;
  systematics[44] = SMH_renScale_bin11;
  systematics[45] = SMH_renScale_bin12;
  systematics[46] = SMH_renScale_bin13;
  systematics[47] = SMH_pdf0;
  systematics[48] = SMH_pdf1;
  systematics[49] = SMH_pdf2;
  systematics[50] = SMH_pdf3;
  systematics[51] = SMH_pdf4;
  systematics[52] = SMH_pdf5;
  systematics[53] = SMH_pdf6;
  systematics[54] = SMH_pdf7;
  systematics[55] = SMH_pdf8;
  systematics[56] = SMH_pdf9;
  systematics[57] = SMH_pdf10;
  systematics[58] = SMH_pdf11;
  systematics[59] = SMH_pdf12;
  systematics[60] = SMH_pdf13;
  systematics[61] = SMH_pdf14;
  systematics[62] = SMH_pdf15;
  systematics[63] = SMH_pdf16;
  systematics[64] = SMH_pdf17;
  systematics[65] = SMH_pdf18;
  systematics[66] = SMH_pdf19;
  systematics[67] = SMH_pdf20;
  systematics[68] = SMH_pdf21;
  systematics[69] = SMH_pdf22;
  systematics[70] = SMH_pdf23;
  systematics[71] = SMH_pdf24;
  systematics[72] = SMH_pdf25;
  systematics[73] = SMH_pdf26;
  systematics[74] = SMH_pdf27;
  systematics[75] = SMH_pdf28;
  systematics[76] = SMH_pdf29;
  systematics[77] = SMH_pdf30;
  systematics[78] = SMH_pdf31;
  systematics[79] = SMH_pdf32;
  systematics[80] = SMH_pdf33;
  systematics[81] = SMH_pdf34;
  systematics[82] = SMH_pdf35;
  systematics[83] = SMH_pdf36;
  systematics[84] = SMH_pdf37;
  systematics[85] = SMH_pdf38;
  systematics[86] = SMH_pdf39;
  systematics[87] = SMH_pdf40;
  systematics[88] = SMH_pdf41;
  systematics[89] = SMH_pdf42;
  systematics[90] = SMH_pdf43;
  systematics[91] = SMH_pdf44;
  systematics[92] = SMH_pdf45;
  systematics[93] = SMH_pdf46;
  systematics[94] = SMH_pdf47;
  systematics[95] = SMH_pdf48;
  systematics[96] = SMH_pdf49;
  systematics[97] = SMH_pdf50;
  systematics[98] = SMH_pdf51;
  systematics[99] = SMH_pdf52;
  systematics[100] = SMH_pdf53;
  systematics[101] = SMH_pdf54;
  systematics[102] = SMH_pdf55;
  systematics[103] = SMH_pdf56;
  systematics[104] = SMH_pdf57;
  systematics[105] = SMH_pdf58;
  systematics[106] = SMH_pdf59;
  //SIGNAL
  systematics[107] = Signal_ISR;
  systematics[108] = Signal_JES;
  systematics[109] = Signal_btag;
  systematics[110] = Signal_misstag;
  systematics[111] = Signal_facRenScale_bin0;
  systematics[112] = Signal_facRenScale_bin1;
  systematics[113] = Signal_facRenScale_bin2;
  systematics[114] = Signal_facRenScale_bin3;
  systematics[115] = Signal_facRenScale_bin4;
  systematics[116] = Signal_facRenScale_bin5;
  systematics[117] = Signal_facRenScale_bin6;
  systematics[118] = Signal_facRenScale_bin7;
  systematics[119] = Signal_facRenScale_bin8;
  systematics[120] = Signal_facRenScale_bin9;
  systematics[121] = Signal_facRenScale_bin10;
  systematics[122] = Signal_facRenScale_bin11;
  systematics[123] = Signal_facRenScale_bin12;
  systematics[124] = Signal_facRenScale_bin13;
  systematics[125] = Signal_facScale_bin0;
  systematics[126] = Signal_facScale_bin1;
  systematics[127] = Signal_facScale_bin2;
  systematics[128] = Signal_facScale_bin3;
  systematics[129] = Signal_facScale_bin4;
  systematics[130] = Signal_facScale_bin5;
  systematics[131] = Signal_facScale_bin6;
  systematics[132] = Signal_facScale_bin7;
  systematics[133] = Signal_facScale_bin8;
  systematics[134] = Signal_facScale_bin9;
  systematics[135] = Signal_facScale_bin10;
  systematics[136] = Signal_facScale_bin11;
  systematics[137] = Signal_facScale_bin12;
  systematics[138] = Signal_facScale_bin13;
  systematics[139] = Signal_renScale_bin0;
  systematics[140] = Signal_renScale_bin1;
  systematics[141] = Signal_renScale_bin2;
  systematics[142] = Signal_renScale_bin3;
  systematics[143] = Signal_renScale_bin4;
  systematics[144] = Signal_renScale_bin5;
  systematics[145] = Signal_renScale_bin6;
  systematics[146] = Signal_renScale_bin7;
  systematics[147] = Signal_renScale_bin8;
  systematics[148] = Signal_renScale_bin9;
  systematics[149] = Signal_renScale_bin10;
  systematics[150] = Signal_renScale_bin11;
  systematics[151] = Signal_renScale_bin12;
  systematics[152] = Signal_renScale_bin13;
  systematics[153] = Signal_pdf0;
  systematics[154] = Signal_pdf1;
  systematics[155] = Signal_pdf2;
  systematics[156] = Signal_pdf3;
  systematics[157] = Signal_pdf4;
  systematics[158] = Signal_pdf5;
  systematics[159] = Signal_pdf6;
  systematics[160] = Signal_pdf7;
  systematics[161] = Signal_pdf8;
  systematics[162] = Signal_pdf9;
  systematics[163] = Signal_pdf10;
  systematics[164] = Signal_pdf11;
  systematics[165] = Signal_pdf12;
  systematics[166] = Signal_pdf13;
  systematics[167] = Signal_pdf14;
  systematics[168] = Signal_pdf15;
  systematics[169] = Signal_pdf16;
  systematics[170] = Signal_pdf17;
  systematics[171] = Signal_pdf18;
  systematics[172] = Signal_pdf19;
  systematics[173] = Signal_pdf20;
  systematics[174] = Signal_pdf21;
  systematics[175] = Signal_pdf22;
  systematics[176] = Signal_pdf23;
  systematics[177] = Signal_pdf24;
  systematics[178] = Signal_pdf25;
  systematics[179] = Signal_pdf26;
  systematics[180] = Signal_pdf27;
  systematics[181] = Signal_pdf28;
  systematics[182] = Signal_pdf29;
  systematics[183] = Signal_pdf30;
  systematics[184] = Signal_pdf31;
  systematics[185] = Signal_pdf32;
  systematics[186] = Signal_pdf33;
  systematics[187] = Signal_pdf34;
  systematics[188] = Signal_pdf35;
  systematics[189] = Signal_pdf36;
  systematics[190] = Signal_pdf37;
  systematics[191] = Signal_pdf38;
  systematics[192] = Signal_pdf39;
  systematics[193] = Signal_pdf40;
  systematics[194] = Signal_pdf41;
  systematics[195] = Signal_pdf42;
  systematics[196] = Signal_pdf43;
  systematics[197] = Signal_pdf44;
  systematics[198] = Signal_pdf45;
  systematics[199] = Signal_pdf46;
  systematics[200] = Signal_pdf47;
  systematics[201] = Signal_pdf48;
  systematics[202] = Signal_pdf49;
  systematics[203] = Signal_pdf50;
  systematics[204] = Signal_pdf51;
  systematics[205] = Signal_pdf52;
  systematics[206] = Signal_pdf53;
  systematics[207] = Signal_pdf54;
  systematics[208] = Signal_pdf55;
  systematics[209] = Signal_pdf56;
  systematics[210] = Signal_pdf57;
  //systematics[211] = Signal_pdf58;
  //systematics[212] = Signal_pdf59;
  systematics[213] = mu_Global;
  systematics[214] = hzbb_mu_Global;
  systematics[215] = highpt_mu_Global;
  systematics[216] = lowres_mu_Global;
};
