#include <assert.h>
//ROOT INCLUDES
#include <TFile.h>
#include <TTree.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TDirectory.h>
#include <TROOT.h>
#include <TRandom3.h>
#include <TH2Poly.h>
//LOCAL INCLUDES
#include "AssortedFunctions.hh"
#include "CommandLineInput.hh"

struct binEdges
{
  int xl;
  int yl;
  int xh;
  int yh;
};

struct finalBin
{
  int xl;
  int yl;
  int xh;
  int yh;
  float b_nr;
  float b_smh;
  float b_full;
  float s;
  bool _final;
};

const float NBKG = 10.0;

int main( int argc, char* argv[] )
{
  gROOT->Reset();

  //-----------------
  //Selection TString
  //-----------------
  std::string categoryMode = ParseCommandLine( argc, argv, "-category=" );
  if (  categoryMode == "" )
    {
      std::cerr << "[ERROR]: please provide the category. Use --category=<highpt,hzbb,highres,lowres,inclusive>" << std::endl;
      return -1;
    }

  //-----------------
  //Selection TString
  //-----------------
  std::string lumi = ParseCommandLine( argc, argv, "-lumi=" );
  if (  lumi == "" )
    {
      std::cerr << "[ERROR]: please provide the integrated luminosity. Use --lumi=<lumi(pb-1)>" << std::endl;
      return -1;
    }

  TString cut = "mGammaGamma > 103. && mGammaGamma < 160. && pho1passIso == 1 && pho2passIso == 1 && pho1passEleVeto == 1 && pho2passEleVeto == 1 && abs(pho1Eta) <1.48 && abs(pho2Eta)<1.48 && (pho1Pt>40||pho2Pt>40)  && pho1Pt> 25. && pho2Pt>25. && MR > 0. && t1Rsq > 0.0 && box == 2";
  TString categoryCutString;
  TString massWindowCut;
  if (categoryMode == "highpt")
    {
      categoryCutString = " && pTGammaGamma >= 110 ";
      massWindowCut     = " && mGammaGamma > 122.96 && mGammaGamma < 127.04";
    }
  else if (categoryMode == "hzbb")
    {
      categoryCutString = " && pTGammaGamma < 110 && ( abs(mbbH_L-125.) < 15. || ( abs(mbbH_L-125.) >= 15. && abs(mbbZ_L-91.) < 15 ) )";
      massWindowCut     = " && mGammaGamma > 122.5 && mGammaGamma < 127.5";
    }
  else if (categoryMode == "highres")
    {
      categoryCutString = " && pTGammaGamma < 110 && abs(mbbH_L-125.) >= 15 && abs(mbbZ_L-91.) >= 15 && sigmaMoverM < 0.0085";
      massWindowCut     = " && mGammaGamma > 122.98 && mGammaGamma < 127.02";
    }
  else if (categoryMode == "lowres")
    {
      categoryCutString  = " && pTGammaGamma < 110 && abs(mbbH_L-125.) >= 15 && abs(mbbZ_L-91.) >= 15 && sigmaMoverM >= 0.0085 ";
      massWindowCut      = " && mGammaGamma > 120.0 && mGammaGamma < 130.00";
    }
  else if ( categoryMode == "inclusive" )
    {
      categoryCutString = " ";
      massWindowCut     = " && mGammaGamma > 122. && mGammaGamma < 129.0";
    }
  else
    {
      std::cerr << "[ERROR]: please provide a valid category: <highpt,hzbb,highres, lowres>" << std::endl;
      return -1;
    }

  cut = cut + categoryCutString;
  massWindowCut = cut + categoryCutString + massWindowCut;
  
  TFile* fb = new TFile("/Users/cmorgoth/Work/data/HggRazorLepton/V3p13_Apr132017/HggRazorLeptons_NonResonant_MuBox_Pythia8_1pb_weighted.root");
  assert(fb);
  TTree* bkgTree = (TTree*)fb->Get("HggRazorLeptons");
  assert(bkgTree);

  TFile* fsmh = new TFile("/Users/cmorgoth/Work/data/HggRazorLepton/V3p13_Apr132017/HggRazorLeptons_SMH_1pb_weighted.root");
  assert(fsmh);
  TTree* smhTree = (TTree*)fsmh->Get("HggRazorLeptons");
  assert(smhTree);

  TFile* fs = new TFile("/Users/cmorgoth/Work/data/HggRazorLepton/V3p13_Apr132017/FastsimSignal/SMS-TChiWH_325_50_1pb_weighted.root");
  assert(fs);
  TTree* sTree = (TTree*)fs->Get("HggRazorLeptons");
  assert(sTree);
  
 
  //------------------------------
  //------------------------------
  //Non-resonant bkg histograms
  //------------------------------
  //------------------------------
    
  //---------------
  //full mgg region
  //---------------
  TString bkgCut = "weight*pileupWeight*"+lumi+"*(" + cut + ")";
  std::cout << "bkgCut: " << bkgCut << std::endl;
  bkgTree->Draw("t1MET:pTGammaGamma>>bkgH(200,0,10000, 200,0, 10000)", bkgCut, "goff");
  TH2F* bkgH = (TH2F*)gDirectory->Get("bkgH");
  //-----------------
  //mgg signal region
  //-----------------
  TString bkgCutSR = "weight*pileupWeight*"+lumi+"*(" + massWindowCut + ")";
  std::cout << "bkgCutSR: " << bkgCutSR << std::endl;
  bkgTree->Draw("t1MET:pTGammaGamma>>bkgSRH(200,0,10000, 200,0, 10000)", bkgCutSR, "goff");
  TH2F* bkgSRH = (TH2F*)gDirectory->Get("bkgSRH");
  
  //------------------------------
  //------------------------------
  //SM higgs bkg histograms
  //------------------------------
  //------------------------------
  TString smhCutSR = "weight*pileupWeight*"+lumi+"*(" + massWindowCut + ")";
  std::cout << "smhCutSR: " << smhCutSR << std::endl;
  smhTree->Draw("t1MET:pTGammaGamma>>smhSRH(200,0,10000, 200,0, 10000)", smhCutSR, "goff");
  TH2F* smhSRH = (TH2F*)gDirectory->Get("smhSRH");

  //------------------------------
  //------------------------------
  //signal model histogram
  //------------------------------
  //------------------------------
  TString sCutSR = "weight*"+lumi+"*(" + massWindowCut + ")";//SR:Signal Region
   std::cout << "sCutSR: " << sCutSR << std::endl;
  sTree->Draw("t1MET:pTGammaGamma>>sSRH(200,0,10000, 200,0, 10000)", sCutSR, "goff");
  TH2F* sSRH = (TH2F*)gDirectory->Get("sSRH");
  
  
  TFile* fout = new TFile("test_qnot.root", "RECREATE");
  bkgH->Write("bkgH");
  bkgSRH->Write("bkgSRH");
  smhSRH->Write("smhSRH");
  sSRH->Write("sSRH");
  

  double b_nr[100];//non-resonant bkg
  double b_smh[100];//smh bkg
  double b[100];
  double s[100];//signal is fixed
  double obs[100];
  double bFull[100];

  double bestBkgNR[2];
  double bestBkgSMH[2];
  double bestBkgFull[2];
  double bestS[2];
  
  //------------------------
  //------------------------
  //Binning Algorithm 
  //------------------------
  //------------------------
  //MET
  TH1F* sigmaMET;
  TH1F* fbkg0MET;
  TH1F* fbkg1MET;
  TH1F* bkg0MET;
  TH1F* bkg1MET;
  TH1F* smh0MET;
  TH1F* smh1MET;
  TH1F* s0MET;
  TH1F* s1MET;
  //pTgg
  TH1F* sigmapTgg;
  TH1F* fbkg0pTgg;
  TH1F* fbkg1pTgg;
  TH1F* bkg0pTgg;
  TH1F* bkg1pTgg;
  TH1F* smh0pTgg;
  TH1F* smh1pTgg;
  TH1F* s0pTgg;
  TH1F* s1pTgg;

  bool splitI     = true;
  bool splitII    = true;
  int binMETsplit  = 1;
  int binRSQsplit = 1;
  int nsplits = 2;
  float MET_L = 0.;
  float MET_H = 10000.;
  float pTgg_L = .0;
  float pTgg_H = 10000.;
  int nMETbins  = 2000;
  int npTggbins = 2000;

  float binWidth_MET  = (MET_H - MET_L)/nMETbins;
  float binWidth_pTgg = (pTgg_H - pTgg_L)/npTggbins;
  
  finalBin bE;
  bE.xl = 1;
  bE.xh = nMETbins;
  bE.yl = 1;
  bE.yh = npTggbins;
  bE._final = false;
  std::map<int, finalBin> myMap;
  int nfbins = 0;
  myMap[nfbins] = bE;
  float maxSignificance = -99;
  for ( int k = 0; k < 60; k++ )//loop to create bins
    {
      std::cout << "[INFO]: iteration: " << k << std::endl;
           
      int partitionType = -1;//MET = 0, pTgg = 1
      int maxIbin = -1;
      int maxBin = -1;
      std::cout << "==========" << std::endl;
      for( int ibin = 0; ibin <= k; ibin++ )//loop around already created bins
	{
	  //std::cout << "[INFO]: splitting ibin: " << ibin << std::endl;
	  //std::cout << " analyzing bin " << ibin << " :"<< myMap[ibin].xl << "-" << myMap[ibin].xh << "," << myMap[ibin].yl << "-" << myMap[ibin].yh << std::endl;

	  //MET
	  TString index = Form("_%d_%d", k, ibin);
	  sigmaMET = new TH1F("sigmaMET"+index, "sigma-MET", 30, 0, 1500);
	  fbkg0MET = new TH1F("fbkg0MET"+index, "fbkg0-MET", 30, 0, 1500);
	  fbkg1MET = new TH1F("fbkg1MET"+index, "fbkg1-MET", 30, 0, 1500);
	  bkg0MET  = new TH1F("bkg0MET"+index, "bkg0-MET", 30, 0, 1500);
	  bkg1MET  = new TH1F("bkg1MET"+index, "bkg1-MET", 30, 0, 1500);
	  smh0MET  = new TH1F("smh0MET"+index, "smh0-MET", 30, 0, 1500);
	  smh1MET  = new TH1F("smh1MET"+index, "smh1-MET", 30, 0, 1500);
	  s0MET    = new TH1F("s0MET"+index, "s0-MET", 30, 0, 1500);
	  s1MET    = new TH1F("s1MET"+index, "s1-MET", 30, 0, 1500);
	  //pTgg
	  sigmapTgg = new TH1F("sigmapTgg"+index, "sigma-pTgg", 30, 0, 1500);
	  fbkg0pTgg = new TH1F("fbkg0pTgg"+index, "fbkg0-pTgg", 30, 0, 1500);//full bkg bin0
	  fbkg1pTgg = new TH1F("fbkg1pTgg"+index, "fbkg1-pTgg", 30, 0, 1500);//full bkg bin1
	  bkg0pTgg  = new TH1F("bkg0pTgg"+index, "bkg0-pTgg", 30, 0, 1500);//sr bkg bin0
	  bkg1pTgg  = new TH1F("bkg1pTgg"+index, "bkg1-pTgg", 30, 0, 1500);//sr bkg bin1
	  smh0pTgg  = new TH1F("smh0pTgg"+index, "smh0-pTgg", 30, 0, 1500);//sr smh bin0
	  smh1pTgg  = new TH1F("smh1pTgg"+index, "smh1-pTgg", 30, 0, 1500);//sr smh bin1
	  s0pTgg    = new TH1F("s0pTgg"+index, "s0-pTgg", 30, 0, 1500);//sr signal bin0
	  s1pTgg    = new TH1F("s1pTgg"+index, "s1-pTgg", 30, 0, 1500);//sr signal bin1
	  
	  for (int bb = 0; bb < k+2; bb++ )
	    {
	      b[bb]     = 0.0;
	      s[bb]     = 0.0;
	      obs[bb]   = 0;
	      b_nr[bb]  = 0.0;
	      b_smh[bb] = 0.0;
	    }
	  int former_ibin = 0;
	  for ( int ifb = 0; ifb <= k; ifb++ )//add bins that are not going to be partitioned
	    {
	      if ( ifb != ibin )//exclude bin being partitioned
		{
		  b[former_ibin]   = myMap[ifb].b_nr + myMap[ifb].b_smh;
		  s[former_ibin]   = myMap[ifb].s;
		  obs[former_ibin] = b[former_ibin] + s[former_ibin];
		  //std::cout << "adding existing bin info: " << myMap[ifb].xl << "-" << myMap[ifb].xh << "," << myMap[ifb].yl << "-" << myMap[ifb].yh << std::endl;
		  //std::cout << "adding existing bin info: " << b[former_ibin] << " " << s[former_ibin] << std::endl;
		  former_ibin++;
		}
	    }

	  //for (int bb = 0; bb < k+2; bb++ ) std::cout << "Init-->b[" << bb << "] = " << b[bb] << std::endl;
	  if( myMap[ibin]._final )
	    {
	      //std::cout << ibin << " skipping final bin: " << myMap[ibin].xl << "-" << myMap[ibin].xh << "," << myMap[ibin].yl << "-" << myMap[ibin].yh << std::endl; 
	      continue;//do not split bin if already final
	    }
	  
	  float MET  = MET_L;
	  for ( int i = 1; i <= nMETbins; i++ )//sum over MET bin ins histogram
	    {
	      if ( i > myMap[ibin].xl && i < myMap[ibin].xh ) //checks that i (MET bin) is above the boundary of the current ibin
		{
		  bFull[k+0] = bkgH->Integral( myMap[ibin].xl, i-1, myMap[ibin].yl, myMap[ibin].yh );
		  bFull[k+1] = bkgH->Integral( i, myMap[ibin].xh, myMap[ibin].yl, myMap[ibin].yh );
		  b_nr[k+0]  = bkgSRH->Integral( myMap[ibin].xl, i-1, myMap[ibin].yl, myMap[ibin].yh );
		  b_nr[k+1]  = bkgSRH->Integral( i, myMap[ibin].xh, myMap[ibin].yl, myMap[ibin].yh );
		  b_smh[k+0] = smhSRH->Integral( myMap[ibin].xl, i-1, myMap[ibin].yl, myMap[ibin].yh );
		  b_smh[k+1] = smhSRH->Integral( i, myMap[ibin].xh, myMap[ibin].yl, myMap[ibin].yh );
		  s[k+0]     = sSRH->Integral( myMap[ibin].xl, i-1, myMap[ibin].yl, myMap[ibin].yh );
		  s[k+1]     = sSRH->Integral( i, myMap[ibin].xh, myMap[ibin].yl, myMap[ibin].yh );
		  b[k+0]     = b_nr[k+0] + b_smh[k+0];
		  b[k+1]     = b_nr[k+1] + b_smh[k+1];
		  obs[k+0]   = b[k+0] + s[k+0];
		  obs[k+1]   = b[k+1] + s[k+1];
		}
	      else
		{
		  continue;
		}
	      if ( b[k+0] == 0  || b[k+1] == 0 ) continue;//avoid nans
	      if ( bFull[k+0] < NBKG || bFull[k+1] <= NBKG ) continue;//avoid bins with small counts
	      
	      double mu   = GetBestFitSignalStrength( k+2, b, s, obs );
	      double qnot = GetQnotTestStatistics( k+2, b, s, obs, mu );
	      /*std::cout << "==========" << std::endl;
	      std::cout << "MET: " << MET << " best fit mu: " << mu << " ==> nsigma = " << sqrt( qnot )
			<< " --> b: " << b[k+0] << ", " << b[k+1] << "; obs: " << obs[k+0] << ", " << obs[k+1] << std::endl;
	      */
	      //-----------------------
	      //filling info histograms
	      //-----------------------
	      sigmaMET->SetBinContent(i, sqrt(qnot) );
	      fbkg0MET->SetBinContent( i, bFull[k+0] );
	      fbkg1MET->SetBinContent( i, bFull[k+1] );
	      bkg0MET->SetBinContent( i, b_nr[k+0] );
	      bkg1MET->SetBinContent( i, b_nr[k+1] );
	      smh0MET->SetBinContent( i, b_smh[k+0] );
	      smh1MET->SetBinContent( i, b_smh[k+1] );
	      s0MET->SetBinContent( i, s[k+0] );
	      s1MET->SetBinContent( i, s[k+1] );
	      MET += binWidth_MET; 
	    }

	  if ( sigmaMET->GetMaximum() > 1.001*maxSignificance && sigmaMET->GetMaximum() > 0 )
	    {
	      maxSignificance = sigmaMET->GetMaximum();
	      maxBin = sigmaMET->GetMaximumBin();
	      partitionType = 1;
	      maxIbin = ibin;
	      bestBkgNR[0]   = bkg0MET->GetBinContent(maxBin);
	      bestBkgNR[1]   = bkg1MET->GetBinContent(maxBin);
	      bestBkgSMH[0]  = smh0MET->GetBinContent(maxBin);
	      bestBkgSMH[1]  = smh1MET->GetBinContent(maxBin);
	      bestBkgFull[0] = fbkg0MET->GetBinContent(maxBin);
	      bestBkgFull[1] = fbkg1MET->GetBinContent(maxBin);
	      bestS[0]       = s0MET->GetBinContent(maxBin);
	      bestS[1]       = s1MET->GetBinContent(maxBin);
	      std::cout << "MET: Improved significance: " << maxSignificance << " " << maxBin << " maxIbin " << maxIbin << std::endl;
	      std::cout << "new bins: " << myMap[ibin].xl << "," << maxBin << " - " << maxBin << "," <<  myMap[ibin].xh << std::endl;
	      std::cout << "Bkg0: " << bestBkgFull[0] << "," << bestBkgFull[1] << std::endl;
	      //std::cout << " analyzing bin " << ibin << " :"<< myMap[ibin].xl << "-" << myMap[ibin].xh << "," << myMap[ibin].yl << "-" << myMap[ibin].yh << std::endl;
	      //for (int bb = 0; bb < k+2; bb++ ) std::cout << "b[" << bb << "] = " << b[bb] << std::endl;
	    }
	  
	  float pTgg  = pTgg_L;
	  for ( int i = 1; i <= npTggbins; i++ )
	    {
	      if ( i > myMap[ibin].yl && i < myMap[ibin].yh ) 
		{
		  //std::cout << myMap[ibin].xl << " " <<  myMap[ibin].xh << " " << myMap[ibin].yl << " " << i << std::endl;
		  bFull[k+0] = bkgH->Integral( myMap[ibin].xl, myMap[ibin].xh, myMap[ibin].yl, i-1 );
		  bFull[k+1] = bkgH->Integral( myMap[ibin].xl, myMap[ibin].xh, i, myMap[ibin].yh );
		  b_nr[k+0]  = bkgSRH->Integral( myMap[ibin].xl, myMap[ibin].xh, myMap[ibin].yl, i-1 );
		  b_nr[k+1]  = bkgSRH->Integral( myMap[ibin].xl, myMap[ibin].xh, i, myMap[ibin].yh );
		  b_smh[k+0] = smhSRH->Integral( myMap[ibin].xl, myMap[ibin].xh, myMap[ibin].yl, i-1 );
		  b_smh[k+1] = smhSRH->Integral( myMap[ibin].xl, myMap[ibin].xh, i, myMap[ibin].yh );
		  s[k+0]     = sSRH->Integral( myMap[ibin].xl, myMap[ibin].xh, myMap[ibin].yl, i-1 );
		  s[k+1]     = sSRH->Integral( myMap[ibin].xl, myMap[ibin].xh, i, myMap[ibin].yh );
		  b[k+0]     = b_nr[k+0] + b_smh[k+0];
		  b[k+1]     = b_nr[k+1] + b_smh[k+1];
		  obs[k+0]   = b[k+0] + s[k+0];
		  obs[k+1]   = b[k+1] + s[k+1];
		}
	      else
		{
		  continue;
		}
	       
	      if ( b[k+0] == 0 || b[k+1] == 0 ) continue;
	      if ( bFull[k+0] <= NBKG || bFull[k+1] <= NBKG ) continue;//avoid bins with small counts
	      double mu   = GetBestFitSignalStrength( k+2, b, s, obs );
	      double qnot = GetQnotTestStatistics( k+2, b, s, obs, mu );
	      
	      /*std::cout << "==========" << std::endl;
	      std::cout << " pTgg: " << pTgg << " best fit mu: " << mu << " ==> nsigma = " << sqrt( qnot )
			<< " --> bF: " << bFull[k+0] << ", " << bFull[k+1]
			<< " --> b: " << b[k+0] << ", " << b[k+1]
			<< "; s: " << s[k+0] << ", " << s[k+1]
			<< "; obs: " << obs[k+0] << ", " << obs[k+1] << std::endl;
	      */
	      
	      //-----------------------
	      //filling info histograms
	      //-----------------------
	      sigmapTgg->SetBinContent(i, sqrt(qnot) );
	      fbkg0pTgg->SetBinContent( i, bFull[k+0] );
	      fbkg1pTgg->SetBinContent( i, bFull[k+1] );
	      bkg0pTgg->SetBinContent( i, b_nr[k+0] );
	      bkg1pTgg->SetBinContent( i, b_nr[k+1] );
	      smh0pTgg->SetBinContent( i, b_smh[k+0] );
	      smh1pTgg->SetBinContent( i, b_smh[k+1] );
	      s0pTgg->SetBinContent( i, s[k+0] );
	      s1pTgg->SetBinContent( i, s[k+1] );
	      pTgg += binWidth_pTgg; 
	    }

	  if ( sigmapTgg->GetMaximum() > 1.001*maxSignificance && sigmapTgg->GetMaximum() > 0)
	    {
	      maxSignificance = sigmapTgg->GetMaximum();
	      maxBin = sigmapTgg->GetMaximumBin();
	      partitionType = 2;
	      maxIbin = ibin;
	      bestBkgNR[0]   = bkg0pTgg->GetBinContent(maxBin);
	      bestBkgNR[1]   = bkg1pTgg->GetBinContent(maxBin);
	      bestBkgSMH[0]  = smh0pTgg->GetBinContent(maxBin);
	      bestBkgSMH[1]  = smh1pTgg->GetBinContent(maxBin);
	      bestBkgFull[0] = fbkg0pTgg->GetBinContent(maxBin);
	      bestBkgFull[1] = fbkg1pTgg->GetBinContent(maxBin);
	      bestS[0]       = s0pTgg->GetBinContent(maxBin);
	      bestS[1]       = s1pTgg->GetBinContent(maxBin);
	      std::cout << "pTgg: Improved significance: " << maxSignificance << " " << maxBin << " maxIbin " << maxIbin << std::endl;
	      std::cout << "new bins: " << myMap[ibin].yl << "," << maxBin << " - " << maxBin << ","<<  myMap[ibin].yh << std::endl;
	      std::cout << "Bkg0: " << bestBkgFull[0] << "," << bestBkgFull[1] << std::endl;
	      
	      //for (int bb = 0; bb < k+2; bb++ ) std::cout << "b[" << bb << "] = " << b[bb] << std::endl;
	    }
	  
	  sigmaMET->Write();
	  fbkg0MET->Write();
	  fbkg1MET->Write();
	  bkg0MET->Write();
	  bkg1MET->Write();
	  smh0MET->Write();
	  smh1MET->Write();
	  s0MET->Write();
	  s1MET->Write();
	  
	  sigmapTgg->Write();
	  fbkg0pTgg->Write();
	  fbkg1pTgg->Write();
	  bkg0pTgg->Write();
	  bkg1pTgg->Write();
	  smh0pTgg->Write();
	  smh1pTgg->Write();
	  s0pTgg->Write();
	  s1pTgg->Write();
	  //MET
	  delete sigmaMET;
	  delete fbkg0MET;
	  delete fbkg1MET;
	  delete bkg0MET;
	  delete bkg1MET;
	  delete smh0MET;
	  delete smh1MET;
	  delete s0MET;
	  delete s1MET;
	  //pTgg
	  delete sigmapTgg;
	  delete fbkg0pTgg;
	  delete fbkg1pTgg;
	  delete bkg0pTgg;
	  delete bkg1pTgg;
	  delete smh0pTgg;
	  delete smh1pTgg;
	  delete s0pTgg;
	  delete s1pTgg;
	}
      
      if ( partitionType == 1 )
	{
	  std::map<int, finalBin> tmpMap;
	  int itmp = 0;
	  for ( auto tmp: myMap )
	    {
	      if ( tmp.first != maxIbin )
		{
		  tmpMap[itmp] = tmp.second;
		  itmp++;
		}
	      else
		{
		  //std::cout << "skippen maxIBin: " << maxIbin << " when cloning map" << std::endl;
		}
	    }
	  std::cout << "splitting in MET @ " << maxBin << ", significance = " << maxSignificance << " nsigmas" << std::endl;
	  std::cout << "MET @ " << maxBin << " NBkg0: " << bestBkgFull[0]
		    << " NBkg1: " << bestBkgFull[1] << std::endl;
	  finalBin fb;
	  //filling low bin
	  fb.xl     = myMap[maxIbin].xl;
	  fb.xh     = maxBin-1;
	  fb.yl     = myMap[maxIbin].yl;
	  fb.yh     = myMap[maxIbin].yh;
	  fb.b_full = bestBkgFull[0];
	  fb.b_nr   = bestBkgNR[0];
	  fb.b_smh  = bestBkgSMH[0];
	  fb.s      = bestS[0];
	  fb._final = false;
	  tmpMap[itmp] = fb;
	  if ( (fb.b_full - NBKG) < NBKG )
	    {
	      std::cout << "MET: First partition is at minimum bkg events: " << fb.b_full << std::endl;
	      tmpMap[itmp]._final = true;
	    }
	  itmp++;
	  //filling high bin
	  fb.xl     = maxBin;
	  fb.xh     = myMap[maxIbin].xh;
	  fb.yl     = myMap[maxIbin].yl;
	  fb.yh     = myMap[maxIbin].yh;
	  fb.b_full = bestBkgFull[1];
	  fb.b_nr   = bestBkgNR[1];
	  fb.b_smh  = bestBkgSMH[1];
	  fb.s      = bestS[1];
	  fb._final = false;
	  tmpMap[itmp] = fb;
	  if ( (fb.b_full - NBKG) < NBKG )
	    {
	      std::cout << "MET: Second partition is at minimum bkg events: " << fb.b_full << std::endl;
	      tmpMap[itmp]._final = true;
	    }
	  myMap = tmpMap;
	}
      else if ( partitionType == 2 )
	{
	  std::cout << "splitting in pTgg @ " << maxBin << ", significance = " << maxSignificance << " nsigmas" << std::endl;
	  std::cout << "pTgg @ " << maxBin << " NBkg0: " << bestBkgFull[0]
		    << " NBkg1: " << bestBkgFull[1] << std::endl;
	  
	  std::map<int, finalBin> tmpMap;
	  int itmp = 0;
	  for ( auto tmp: myMap )
	    {
	      if ( tmp.first != maxIbin )
		{
		  tmpMap[itmp] = tmp.second;
		  itmp++;
		}
	      else
		{
		  //std::cout << "skippen maxIBin: " << maxIbin << " when cloning map" << std::endl;
		}
	    }
	  finalBin fb;
	  //fill low bin
	  fb.xl     = myMap[maxIbin].xl;
	  fb.xh     = myMap[maxIbin].xh;
	  fb.yl     = myMap[maxIbin].yl;
	  fb.yh     = maxBin-1;
	  fb.b_full = bestBkgFull[0];
	  fb.b_nr   = bestBkgNR[0];
	  fb.b_smh  = bestBkgSMH[0];
	  fb.s      = bestS[0];
	  fb._final = false;
	  tmpMap[itmp] = fb;
	  if ( (fb.b_full - NBKG) < NBKG )
	    {
	      std::cout << "pTgg: First partition is at minimum bkg events: " << fb.b_full << std::endl;
	      tmpMap[itmp]._final = true;
	    }
	  itmp++;
	  //filling high bin
	  fb.xl     = myMap[maxIbin].xl;
	  fb.xh     = myMap[maxIbin].xh;
	  fb.yl     = maxBin;
	  fb.yh     = myMap[maxIbin].yh;
	  fb.b_full = bestBkgFull[1];
	  fb.b_nr   = bestBkgNR[1];
	  fb.b_smh  = bestBkgSMH[1];
	  fb.s      = bestS[1];
	  fb._final = false;
	  tmpMap[itmp] = fb;
	  if ( (fb.b_full - NBKG) < NBKG )
	    {
	      std::cout << "pTgg: Second partition is at minimum bkg events: " << fb.b_full << std::endl;
	      tmpMap[itmp]._final = true;
	    }
	  myMap = tmpMap;
	}
      else
	{
	  std::cout << "[INFO]: Significance has not been improved by more than 1%, best significance is: " << maxSignificance << std::endl;
	  std::cout << "[INFO]: Binning process has terminated" << std::endl;
	  break;
	}

      for(int kk = 0; kk < 2; kk++)
	{
	  bestBkgNR[kk]   = -1;
	  bestBkgSMH[kk]  = -1;
	  bestBkgFull[kk] = -1;
	  bestS[kk]       = -1;
	}
    }
  /*
  TRandom3 r1(0);
  TRandom3 r2(0);
  TH1F* h_qnot = new TH1F("h_qnot", "h_qnot", 1000, 0, 20);
  for ( int i = 0; i < 1e7; i ++ )
    {
      for ( int j = 0; j < n; j++ )
	{
	  b[j] = b_nr[j] + b_smh[j];
	  double bNonRes = r1.PoissonD( b_nr[j] );
	  double bSMH = r2.PoissonD( b_smh[j] );
	  obs[j] = bNonRes + bSMH;
	}
      double mu   = GetBestFitSignalStrength( n, b, s, obs );
      double qnot = GetQnotTestStatistics( n, b, s, obs, mu );
      h_qnot->Fill( qnot );
    }
  */

  TH2Poly* h2p = new TH2Poly();
  TH2Poly* h2p_nr = new TH2Poly();
  TH2Poly* h2p_smh = new TH2Poly();
  TH2Poly* h2p_s = new TH2Poly();
  TH2Poly* h2p_SoverSqrtB = new TH2Poly();
 
  int ctr = 0;
  for ( auto tmp : myMap )
    {
      /*std::cout << "BIN #" << tmp.first << "--> xl: " << tmp.second.xl << ", xh: " << tmp.second.xh
		<< ", yl: " << tmp.second.yl << ", yh: " << tmp.second.yh
		<< "; b: " << tmp.second.b_nr + tmp.second.b_smh 
		<< ", s: " << tmp.second.s << std::endl;
      */
      double MET_bw  = (MET_H-MET_L)/nMETbins;
      double pTgg_bw = (pTgg_H-pTgg_L)/npTggbins;
      
      double MET_low   = MET_L + MET_bw*(tmp.second.xl - 1);
      double MET_high  = MET_L + MET_bw*((tmp.second.xh+1) - 1);//had to artificially subtract 1 from the xh in the code above, restoring the correct values here
      double pTgg_low  = pTgg_L + pTgg_bw*(tmp.second.yl - 1);
      double pTgg_high = pTgg_L + pTgg_bw*((tmp.second.yh+1) - 1);//had to artificially subtract 1 from the xh in the code above, restoring the correct values here
      if ( pTgg_high > 9000.0 ) pTgg_high  = 10000.0;
      if ( MET_high > 9000.0 ) MET_high = 10000.0;

      /*std::cout << "BIN #" << tmp.first << "--> xl: " << MET_low << ", xh: " << MET_high
		<< ", yl: " << pTgg_low << ", yh: " << pTgg_high
		<< "; b: " << tmp.second.b_nr + tmp.second.b_smh 
		<< ", s: " << tmp.second.s << std::endl;
      */

     
      std::cout << "float bin_" << categoryMode << ctr << "[4] = {" << MET_low<< "," << pTgg_low << "," <<  MET_high << "," <<  pTgg_high << "};\n";
      ctr++;
      
      h2p->AddBin( MET_low, pTgg_low, MET_high, pTgg_high );
      h2p_nr->AddBin( MET_low, pTgg_low, MET_high, pTgg_high );
      h2p_smh->AddBin( MET_low, pTgg_low, MET_high, pTgg_high );
      h2p_s->AddBin( MET_low, pTgg_low, MET_high, pTgg_high );
      h2p_SoverSqrtB->AddBin( MET_low, pTgg_low, MET_high, pTgg_high );
      int bin = h2p->FindBin( MET_low+0.5*MET_bw, pTgg_low+0.5*pTgg_bw );
      h2p->SetBinContent( bin, tmp.second.b_full);
      h2p_nr->SetBinContent( bin, tmp.second.b_nr);
      h2p_smh->SetBinContent( bin, tmp.second.b_smh);
      h2p_s->SetBinContent( bin, tmp.second.s);
      h2p_SoverSqrtB->SetBinContent( bin, tmp.second.s/sqrt(tmp.second.b_nr+tmp.second.s) );
    }

  std::cout << "std::vector<float*> SetBinning_" << categoryMode << "()\n{\n";
  std::cout << "std::vector<float*> myVec;\n";
  for( int i = 0; i < myMap.size(); i++ )
    {
      std::cout << "myVec.push_back(bin_" << categoryMode << i << ");\n";
    }
  std::cout << "return myVec;\n}\n";


  std::cout << "\\begin{table*}[htbH]\n\\begin{center}\n";
  std::cout << "\\topcaption{" << categoryMode << " category binning. The non-resonant, "
	    << "SM Higgs, and signal () expected yields for an integrated luminosity correspondint to 2.3~$\\mathrm{fb}^{-1}$ \\label{tab:binning-" << categoryMode << "}}\n";
  std::cout << "\\def\\arraystretch{1.5}\n\\begin{tabular}{|c|c|c|c|}\n\\hline\n";
  std::cout << "$\\mathrm{M_{R}}\\otimes\\mathrm{R^{2}}$ & non-resonant (MC) & SM Higgs & Signal\\\\\n\\hline\n";
  for( auto tmp : myMap )
    {
      double MET_bw  = (MET_H-MET_L)/nMETbins;
      double pTgg_bw = (pTgg_H-pTgg_L)/npTggbins;
      
      double MET_low   = MET_L + MET_bw*(tmp.second.xl - 1);
      double MET_high  = MET_L + MET_bw*((tmp.second.xh+1) - 1);//had to artificially subtract 1 from the xh in the code above, restoring the correct values here
      double pTgg_low  = pTgg_L + pTgg_bw*(tmp.second.yl - 1);
      double pTgg_high = pTgg_L + pTgg_bw*((tmp.second.yh+1) - 1);//had to artificially subtract 1 from the xh in the code above, restoring the correct values here
      if ( pTgg_high > 9000.0 ) pTgg_high  = 10000.0;
      if ( MET_high > 9000.0 ) MET_high = 10000.0;
      
      TString s = Form("%.0f-%.0f\\GeV $\\otimes$ %.3f-%.3f & %.2f & %.2f & %.2f \\\\", MET_low, MET_high, pTgg_low, pTgg_high, tmp.second.b_nr, tmp.second.b_smh, tmp.second.s);
      std::cout << s << std::endl;
      /*std::cout << MET_low << "-" << MET_high << "\\GeV $\\otimes$ "
		<< pTgg_low << "-"  << pTgg_high;
      std::cout << " & " << tmp.second.b_nr << " & "
		<< tmp.second.b_smh << " & "  << tmp.second.s << "\\\\" << std::endl;
      */
    }
  std::cout << "\\hline\n\\end{tabular}\n\\end{center}\n\\end{table*}" << std::endl;
  
  //h_qnot->Write();
  h2p->Write("h2p_bFull");
  h2p_nr->Write("h2pSR_bNR");
  h2p_smh->Write("h2pSR_bSMH");
  h2p_s->Write("h2pSR_Signal");
  h2p_SoverSqrtB->Write("h2pSR_SoverSqrtB");
  fout->Close();
  
  return 0;
}
