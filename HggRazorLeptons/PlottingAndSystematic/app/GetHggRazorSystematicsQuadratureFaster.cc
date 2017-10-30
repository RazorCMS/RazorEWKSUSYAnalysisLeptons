#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <assert.h>
//ROOT INCLUDES
#include <TFile.h>
#include <TROOT.h>
//#include <RooArgSet.h>
//LOCAL INCLUDES
#include "HggAux.hh"
#include "HggRazorSystematics.hh"
#include "CommandLineInput.hh"

const bool _debug = true;



//----------------------------------------------
//Load Binning
//----------------------------------------------
std::vector<float*> SetBinning(std::vector<Bin> bins, std::string category)
{

  std::vector<float*> myVec;
  for(int i=0; i<bins.size(); ++i) {
    float *tmpbin = new float[5];
    if (bins[i].box == category) {
      tmpbin[0] = bins[i].x1;
      tmpbin[1] = bins[i].y1;
      tmpbin[2] = bins[i].x2;
      tmpbin[3] = bins[i].y2;
      tmpbin[4] = bins[i].bin;
      myVec.push_back(tmpbin);
    }
  }

  return myVec;
};

//----------------
//Static Variables
//----------------
float HggRazorSystematics::NR_kf = 1.0;
int   HggRazorSystematics::n_PdfSys = 60;


int main( int argc, char* argv[] )
{
  srand(time(NULL));
  //RooFit::PrintLevel(5);
  //RooMsgService::instance().setGlobalKillBelow(RooFit::FATAL);
  gROOT->Reset();
  std::string inputList = ParseCommandLine( argc, argv, "-inputList=" );
  if (  inputList == "" )
    {
      std::cerr << "[ERROR]: please provide an input list file using --inputList=<path_to_list_file>" << std::endl;
      return -1;
    }
  //-----------------
  //Selection TString
  //-----------------
  std::string categoryMode = ParseCommandLine( argc, argv, "-category=" );
  if (  categoryMode == "" )
    {
      std::cerr << "[ERROR]: please provide the category. Use --category=<highpt,hzbb,highres,lowres>" << std::endl;
      return -1;
    }

  //-----------------
  //Output file TString
  //-----------------
  std::string outputFile = ParseCommandLine( argc, argv, "-outputFile=" );
  if (  outputFile == "" )
    {
      std::cerr << "[ERROR]: please provide an output file using --outputFile=<outputfile>" << std::endl;
      return -1;
    }
 
  //-----------------
  //Lumi Normalization
  //-----------------
  double lumi = 0;
  std::string lumiString = ParseCommandLine( argc, argv, "-lumi=" );
  if (  lumiString == "" )
    {
      std::cerr << "[ERROR]: please provide the luminosity. For example, use --lumi=2000" << std::endl;
      return -1;
    }
  lumi = float(atoi(lumiString.c_str()));
  std::cerr << "[INFO] : Using Luminosity = " << lumi << "\n";

  //-----------------
  //Analysis Tag
  //-----------------
  std::string analysisTag = ParseCommandLine( argc, argv, "-analysisTag=" );
  if ( analysisTag == "" )
    {
      std::cerr << "[ERROR]: please provide the analysisTag. Use --analysisTag=<Razor2015_76X,Razor2016_80X>" << std::endl;
      return -1;
    }

  
  //-----------------
  //pTGammaGamma cut
  //-----------------
  std::string usePtGammaGamma = ParseCommandLine( argc, argv, "-usePtGammaGamma=" );
  if ( usePtGammaGamma == "yes" )
    {
      std::cerr << "[INFO]: enabling pTGammaGamma cut for all boxes" << std::endl;
    } 
  
  //-----------------
  //Binning File 
  //-----------------
  std::string binDefinitionFilename = ParseCommandLine( argc, argv, "-binningFile=" );
  if ( binDefinitionFilename == "" )
    {
      std::cerr << "[ERROR]: please provide the bin definition file. Use --binningFile=<binningFile>" << std::endl;
      return -1;
    } 
  

  //-----------------
  //EWK SUSY Signals
  //-----------------
  bool isEWKSUSYSignal = false;
  std::string isEWKSUSYSignalString = ParseCommandLine( argc, argv, "-EWKSUSYSignal=" );
  if ( isEWKSUSYSignalString == "" )
    {
      std::cerr << "[ERROR]: please specify if signal is EWK SUSY Signal. Use --EWKSUSYSignal=<0,1>" << std::endl;
      return -1;
    } 
  if (isEWKSUSYSignalString == "1" || isEWKSUSYSignalString == "true" ) isEWKSUSYSignal = true;



  //----------------------
  //SigmaMoverM correction
  //----------------------
  //(scale MC to data/MC ratio)
  // correction is derived as (data-MC)/MC --> correction is 1+(data-MC)/MC;
  
  const float highres_sigmaMoverM_corr = 1.0 - 0.10749 ;//1.0+(data-MC)/MC
  const float lowres_sigmaMoverM_corr = 1.0 + 0.24268;//1.0+(data-MC)/MC

  //-----------------
  //Load Binning
  //-----------------
  std::vector<Bin> binVector;
  std::ifstream binDefFile( binDefinitionFilename.c_str(), std::fstream::in );
  if ( binDefFile.is_open() ) {
    float x1, x2, y1, y2;
    int binN;
    std::string box, f1;
    while ( binDefFile.good() ) {
      binDefFile >> binN >> x1 >> x2 >> y1 >> y2 >> box >> f1;
      if ( binDefFile.eof() ) break;
      Bin mybin;
      mybin.bin = binN;
      mybin.f1 = f1;
      mybin.box = box;
      mybin.x1 = x1;
      mybin.x2 = x2;
      mybin.y1 = y1;
      mybin.y2 = y2;
      binVector.push_back(mybin);
    }
  } else {
    std::cout << "Unable to open binning lookup table" << std::endl;
  }


  TString cut = "mGammaGamma > 103. && mGammaGamma < 160. && pho1passIso == 1 && pho2passIso == 1 && pho1passEleVeto == 1 && pho2passEleVeto == 1 && abs(pho1Eta) <1.48 && abs(pho2Eta)<1.48 && (pho1Pt>40||pho2Pt>40)  && pho1Pt> 25. && pho2Pt>25.";
  if (usePtGammaGamma == "yes") {
      cut = cut + " && pTGammaGamma > 20 ";
  }

  TString categoryCutString;
  if (categoryMode == "highpt") categoryCutString          = " && pTGammaGamma >= 110 && box > 4 ";
  else if (categoryMode == "hbb") categoryCutString        = " && pTGammaGamma < 110 && abs(mbbH-125.) < 15. && box > 4";
  else if (categoryMode == "zbb") categoryCutString        = " && pTGammaGamma < 110 && abs(mbbH-125.) >= 15. && abs(mbbZ-91.) < 15. && box > 4";
  else if (categoryMode == "highres") categoryCutString    = " && pTGammaGamma < 110 && abs(mbbH-125.) >= 15 && abs(mbbZ-91.) >= 15 && sigmaMoverM < 0.0085 && box > 4";
  else if (categoryMode == "lowres") categoryCutString     = " && pTGammaGamma < 110 && abs(mbbH-125.) >= 15 && abs(mbbZ-91.) >= 15 && sigmaMoverM >= 0.0085 && box > 4";
  else if (categoryMode == "muhighpt") categoryCutString   = " && pTGammaGamma >= 110 && box == 3 && lep1Pt > 15. ";
  else if (categoryMode == "mulowpt") categoryCutString    = " && pTGammaGamma < 110 && box == 3 && lep1Pt > 15. ";
  else if (categoryMode == "elehighpt") categoryCutString  = " && pTGammaGamma >= 110 && box == 4 && lep1Pt > 20. ";
  else if (categoryMode == "elelowpt") categoryCutString   = " && pTGammaGamma < 110 && box == 4 && lep1Pt > 20. ";
  else if (categoryMode == "twoleptons") categoryCutString = " && (box == 0 || box == 1 || box == 2)";
  else if (categoryMode == "inclusive") categoryCutString  = "";

  TString triggerCut = " && ( HLTDecision[82] || HLTDecision[83] || HLTDecision[93] ) ";
  TString metFilterCut = " && (Flag_HBHENoiseFilter == 1 && Flag_goodVertices == 1 && Flag_eeBadScFilter == 1 && Flag_HBHEIsoNoiseFilter == 1)";
  
  //For fastsim signals, turn off trigger and met filters
  if (isEWKSUSYSignal) 
    {
      triggerCut = "";
      metFilterCut = "";
    }
  


  if ( analysisTag == "Razor2015_76X" ) 
    {
      cut = cut + categoryCutString + triggerCut+ metFilterCut;  
    } 
  else if ( analysisTag == "Razor2016_80X" ) 
    {
      cut = cut + categoryCutString + triggerCut + metFilterCut;//FullSim
    } 
  else 
    {
      std::cerr << "Analysis Tag " << analysisTag << " not recognized. Error!\n";
      return -1;
    }
  std::cerr << "[INFO] : Using Analysis Tag: " << analysisTag  << "\n";

  std::cerr << "===========================================================================" << std::endl;
  std::cerr << "[INFO]: cut--> " << cut << std::endl;
  std::cerr << "===========================================================================" << std::endl;
  
  std::ifstream ifs( inputList, std::ifstream::in );
  assert(ifs);

  std::vector<std::pair<float,float>> facScaleSys;
  std::vector<std::pair<float,float>> renScaleSys;
  std::vector<std::pair<float,float>> facRenScaleSys;

  std::vector<float*> myVectBinning;

  //get correct binning category in case of nonstandard box choice
  std::string binCategory = categoryMode;
  if ( categoryMode == "highreslowres" ) {
      binCategory = "highres"; //use highres binning
  }
  else if ( categoryMode == "highpthighres" || categoryMode == "highptlowres" ) {
      binCategory = "highpt"; //use highpt binning
  }

  myVectBinning = SetBinning(binVector, binCategory);

  if (!(binCategory == "highpt" || binCategory == "hbb" || binCategory == "zbb" || binCategory == "highres"|| binCategory == "lowres"
	|| binCategory == "muhighpt" || binCategory == "mulowpt" || binCategory == "elehighpt" || binCategory == "elelowpt"
	|| binCategory == "twoleptons") )
     {
       std::cerr << "[ERROR]: category is not <highpt/hbb/zbb/highres/lowres/muhighpt/mulowpt/elehighpt/elelowpt/twoleptons>; quitting" << std::endl;
       return -1;
     } 

  TH2Poly* nominal;
  TH2Poly* nominalS = new TH2Poly("nominal_Signal", "", 150, 10000, 0, 1 );

  TH2Poly* ISRUpS   = new TH2Poly("ISRUpS", "", 150, 10000, 0, 1 );
  TH2Poly* ISRDownS = new TH2Poly("ISRDownS", "", 150, 10000, 0, 1 );

  TH2Poly* facScaleUp;
  TH2Poly* facScaleDown;
  TH2Poly* facScaleUpS   = new TH2Poly("facScaleUpS", "", 150, 10000, 0, 1 );
  TH2Poly* facScaleDownS = new TH2Poly("facScaleDownS", "", 150, 10000, 0, 1 );
  
  TH2Poly* renScaleUp;
  TH2Poly* renScaleDown;
  TH2Poly* renScaleUpS   = new TH2Poly("renScaleUpS", "", 150, 10000, 0, 1 );
  TH2Poly* renScaleDownS = new TH2Poly("renScaleDownS", "", 150, 10000, 0, 1 );
  
  TH2Poly* facRenScaleUp;
  TH2Poly* facRenScaleDown;
  TH2Poly* facRenScaleUpS   = new TH2Poly("facRenScaleUpS", "", 150, 10000, 0, 1 );
  TH2Poly* facRenScaleDownS = new TH2Poly("facRenScaleDownS", "", 150, 10000, 0, 1 );
  
  TH2Poly* JesUp;
  TH2Poly* JesDown;
  TH2Poly* JesUpS   = new TH2Poly("JesUpS", "", 150, 10000, 0, 1 );//signal
  TH2Poly* JesDownS = new TH2Poly("JesDownS", "", 150, 10000, 0, 1 );//signal

  TH2Poly* btagUp;
  TH2Poly* btagDown;
  TH2Poly* btagUpS   = new TH2Poly("btagUpS", "", 150, 10000, 0, 1 );//signal
  TH2Poly* btagDownS = new TH2Poly("btagDownS", "", 150, 10000, 0, 1 );//signal

  TH2Poly* misstagUp;
  TH2Poly* misstagDown;
  TH2Poly* misstagUpS   = new TH2Poly("misstagUpS", "", 150, 10000, 0, 1 );//signal
  TH2Poly* misstagDownS = new TH2Poly("misstagDownS", "", 150, 10000, 0, 1 );//signal
  
  TH2Poly* genMetS = new TH2Poly("genMet_Signal", "", 150, 10000, 0, 1 );//signal
  TH2Poly* pileupS = new TH2Poly("pileup_Signal", "", 150, 10000, 0, 1 );//signal

  TH2Poly* pdf[60];
  TH2Poly* pdfS[60];
  for ( int i = 0; i < 60; i++ )
    {
      TString pdfName = Form("pdf%d", i);
      pdfS[i] = new TH2Poly( pdfName+"S", "", 150, 10000, 0, 1 );
    }
  
  //---------------------------------
  //Getting SMH root file with yields
  //---------------------------------
  TFile* fSMH;
  if (categoryMode == "highpt") fSMH = new TFile("data/SMH_Histos_2017/fullSys_highpt.root", "read");
  else if (categoryMode == "hbb") fSMH = new TFile("data/SMH_Histos_2017/fullSys_hbb.root", "read");
  else if (categoryMode == "zbb") fSMH = new TFile("data/SMH_Histos_2017/fullSys_zbb.root", "read");
  else if (categoryMode == "highres") fSMH = new TFile("data/SMH_Histos_2017/fullSys_highres.root", "read");
  else if (categoryMode == "lowres") fSMH = new TFile("data/SMH_Histos_2017/fullSys_lowres.root", "read");
  else if (categoryMode == "muhighpt") fSMH = new TFile("data/SMH_Histos_2017/fullSys_muhighpt.root", "read");
  else if (categoryMode == "mulowpt") fSMH = new TFile("data/SMH_Histos_2017/fullSys_mulowpt.root", "read");
  else if (categoryMode == "elehighpt") fSMH = new TFile("data/SMH_Histos_2017/fullSys_elehighpt.root", "read");
  else if (categoryMode == "elelowpt") fSMH = new TFile("data/SMH_Histos_2017/fullSys_elelowpt.root", "read");
  else if (categoryMode == "twoleptons") fSMH = new TFile("data/SMH_Histos_2017/fullSys_twoleptons.root", "read");

  assert(fSMH);
  //-------------------
  //Getting SMH TH2Poly
  //-------------------
  nominal         = (TH2Poly*)fSMH->Get("SMH_nominal");
  facScaleUp      = (TH2Poly*)fSMH->Get("facScaleUp");
  facScaleDown    = (TH2Poly*)fSMH->Get("facScaleDown");
  renScaleUp      = (TH2Poly*)fSMH->Get("renScaleUp");
  renScaleDown    = (TH2Poly*)fSMH->Get("renScaleDown");
  facRenScaleUp   = (TH2Poly*)fSMH->Get("facRenScaleUp");
  facRenScaleDown = (TH2Poly*)fSMH->Get("facRenScaleDown");
  JesUp           = (TH2Poly*)fSMH->Get("JesUp");
  JesDown         = (TH2Poly*)fSMH->Get("JesDown");
  btagUp          = (TH2Poly*)fSMH->Get("btagUp");
  btagDown        = (TH2Poly*)fSMH->Get("btagDown");
  misstagUp       = (TH2Poly*)fSMH->Get("misstagUp");
  misstagDown     = (TH2Poly*)fSMH->Get("misstagDown");

  for ( int i = 0; i < 60; i++ )
    {
      TString pdfName = Form("pdf%d", i);
      pdf[i] = (TH2Poly*)fSMH->Get( pdfName );
    }
  
  std::map< std::pair<float,float>, float > sysMap;
  for ( auto tmp : myVectBinning )
    {
      nominalS->AddBin( tmp[0], tmp[1], tmp[2], tmp[3] );
      ISRUpS->AddBin( tmp[0], tmp[1], tmp[2], tmp[3] );
      ISRDownS->AddBin( tmp[0], tmp[1], tmp[2], tmp[3] );
      facScaleUpS->AddBin( tmp[0], tmp[1], tmp[2], tmp[3] );
      facScaleDownS->AddBin( tmp[0], tmp[1], tmp[2], tmp[3] );
      renScaleUpS->AddBin( tmp[0], tmp[1], tmp[2], tmp[3] );
      renScaleDownS->AddBin( tmp[0], tmp[1], tmp[2], tmp[3] );
      facRenScaleUpS->AddBin( tmp[0], tmp[1], tmp[2], tmp[3] );
      facRenScaleDownS->AddBin( tmp[0], tmp[1], tmp[2], tmp[3] );
      JesUpS->AddBin( tmp[0], tmp[1], tmp[2], tmp[3] );
      JesDownS->AddBin( tmp[0], tmp[1], tmp[2], tmp[3] );

      //btag
      btagUpS->AddBin( tmp[0], tmp[1], tmp[2], tmp[3] );
      btagDownS->AddBin( tmp[0], tmp[1], tmp[2], tmp[3] );
      //misstag
      misstagUpS->AddBin( tmp[0], tmp[1], tmp[2], tmp[3] );
      misstagDownS->AddBin( tmp[0], tmp[1], tmp[2], tmp[3] );
      //pdf
      for( int i = 0; i < 60; i++ ) pdfS[i]->AddBin( tmp[0], tmp[1], tmp[2], tmp[3] );
      //fastsim systematic
      genMetS->AddBin( tmp[0], tmp[1], tmp[2], tmp[3] );
      pileupS->AddBin( tmp[0], tmp[1], tmp[2], tmp[3] );
    }
    
  std::string process, rootFileName;
  while ( ifs.good() )
    {
      ifs >> process >> rootFileName;
      if ( ifs.eof() ) break;
      if ( process.find("#") != std::string::npos ) continue;
      if ( _debug ) std::cout << process << " " << rootFileName << std::endl;
      TFile* fin = new TFile( rootFileName.c_str(), "READ");
      assert( fin );
      if ( _debug ) std::cout << "[INFO]: file: " << rootFileName << " passed check\n\n"<< std::endl;
      
      //------------------------
      //Getting TTree and Histos
      //------------------------
      TTree* tree = (TTree*)fin->Get("HggRazorLeptons");
      assert( tree );
      TH1F* NEvents = (TH1F*)fin->Get("NEvents");
      if ( process != "signal" ) assert( NEvents );
      TH1F* SumScaleWeights   = (TH1F*)fin->Get("SumScaleWeights");
      if ( process != "signal" ) assert( SumScaleWeights );
      TH1F* SumPdfWeights   = (TH1F*)fin->Get("SumPdfWeights");
      if ( process != "signal" ) assert( SumPdfWeights );     
      TH1F* ISRHist = (TH1F*)fin->Get("NISRJets");
      if ( process == "signal" ) assert( ISRHist );
      TH1F* ISRPtHist = (TH1F*)fin->Get("PtISR");
      if ( isEWKSUSYSignal && process == "signal" ) assert( ISRPtHist );
      TH1F* NPVHist = (TH1F*)fin->Get("NPV");
      if ( isEWKSUSYSignal && process == "signal" ) assert( NPVHist );
      
      
      TString tmpName = Form("%s_tmp_%d.root", outputFile.c_str(), rand());
      TFile* tmp = new TFile( tmpName , "RECREATE");
      TTree* cutTree = tree->CopyTree( cut );
      assert( cutTree );
      TString currentProcess = process.c_str();

      //---------------------------
      //Create HggSystematic object
      //---------------------------
      HggRazorSystematics* hggSys = new HggRazorSystematics( cutTree, currentProcess, binCategory, analysisTag, _debug, isEWKSUSYSignal, _debug );
      hggSys->SetLumi(lumi);
      //hggSys->PrintBinning();
      //hggSys->SetBinningMap( binningMap );
      //hggSys->PrintBinning();
      hggSys->SetBinningVector( myVectBinning );
      hggSys->InitMrRsqTH2Poly( 1 );
      hggSys->SetNeventsHisto( NEvents );
      hggSys->SetFacScaleWeightsHisto( SumScaleWeights );
      hggSys->SetPdfWeightsHisto( SumPdfWeights );
      hggSys->SetISRHisto( ISRHist );
      hggSys->SetNPVHisto( NPVHist );
      hggSys->LoadNPVTarget("/Users/cmorgoth/git/RazorEWKSUSYAnalysisLeptons/HggRazorLeptons/PlottingAndSystematic/data/PileUpDistribution/NPVTarget_2016.root");
      if ( isEWKSUSYSignal ) hggSys->SetISRPtHisto( ISRPtHist );
      
      hggSys->Loop();
      for ( auto tmp: myVectBinning )
	{
	  int bin = nominalS->FindBin( tmp[0]+10, tmp[1]+0.0001 );
	  if ( currentProcess == "signal" )
	    {
	      nominalS->SetBinContent( bin, hggSys->GetNominalYield( tmp[0], tmp[1] ) );
	      std::pair<float, float> facSys;
	    
	      //JES
	      facSys = hggSys->GetJesSystematic( tmp[0], tmp[1] );
	      JesUpS->SetBinContent( bin, facSys.first );
	      JesDownS->SetBinContent( bin, facSys.second );
	      //btag
	      facSys = hggSys->GetBtagSystematic( tmp[0], tmp[1] );
	      btagUpS->SetBinContent( bin, facSys.first );
	      btagDownS->SetBinContent( bin, facSys.second );
	      //misstag
	      facSys = hggSys->GetMisstagSystematic( tmp[0], tmp[1] );
	      misstagUpS->SetBinContent( bin, facSys.first );
	      misstagDownS->SetBinContent( bin, facSys.second );

	      //Signal ISR systematic
	      facSys = hggSys->GetISRSystematic( tmp[0], tmp[1] );
	      ISRUpS->SetBinContent( bin,  facSys.first );
	      ISRDownS->SetBinContent( bin, facSys.second );

	      //facScale
	      facSys = hggSys->GetFacScaleSystematic( tmp[0], tmp[1] );
	      //facSys = std::pair<float,float>(0,0);
	      facScaleUpS->SetBinContent( bin, facSys.first );
	      facScaleDownS->SetBinContent( bin, facSys.second );
	      //renScale
	      facSys = hggSys->GetRenScaleSystematic( tmp[0], tmp[1] );
	      //facSys = std::pair<float,float>(0,0);
	      renScaleUpS->SetBinContent( bin, facSys.first );
	      renScaleDownS->SetBinContent( bin, facSys.second );
	      //facRenScale
	      facSys = hggSys->GetFacRenScaleSystematic( tmp[0], tmp[1] );
	      //facSys = std::pair<float,float>(0,0);
	      facRenScaleUpS->SetBinContent( bin,  facSys.first );
	      facRenScaleDownS->SetBinContent( bin, facSys.second );

	      //PDF
	      for ( int ipdf = 0; ipdf < 60; ipdf++ ) 
		{
		  pdfS[ipdf]->SetBinContent( bin, hggSys->GetPdfSystematic( ipdf, tmp[0], tmp[1] ) );
		}
	      
	      //FastSim
	      genMetS->SetBinContent( bin, hggSys->GetGenMetSystematic( tmp[0], tmp[1] ) );
	      pileupS->SetBinContent( bin, hggSys->GetNominalError( tmp[0], tmp[1] ) );
	    }
	  else
	    {
	      std::cout << "[INFO]: ERROR!!!! PROCESS DIFFERENT FROM SIGNAL. Please Check your input list!!\nTerminating" << std::endl;
	      exit(1);
	    }
	}
      
      hggSys->WriteOutput( Form("histoMR_Rsq_%d", rand()) );
      delete hggSys;
      if ( _debug ) std::cout << "deleted hggSys" << std::endl;
      //delete tmp;
      system ( "rm " + tmpName );
      if ( _debug ) std::cout << "deleted tmp File" << std::endl;
    }

  float facScaleTotal[2] = {0,0};
  for ( auto tmp : facScaleSys )
    {
      //std::cout << "Up: " << tmp.first << " , Down: " << tmp.second << std::endl;
      facScaleTotal[0] += tmp.first;
      facScaleTotal[1] += tmp.second;
    } 
  
  
  //********************************************************
  //Print output
  //********************************************************
  std::ofstream outf;
  outf.open(outputFile.c_str());  

  /*
  std::cout << "#category\t\tmr_l\tmr_h\trsq_l\trsq_h\tSMHY\t\tFSU\t\tFSD";
  for( int ipdf = 0; ipdf < 60; ipdf++ ) std::cout << "\t\tPDF" << ipdf;
  std::cout << "\t\tJESU\t\tJESD"<< std::endl;
  */
   for ( auto tmp: myVectBinning )
     {
       int bin   = nominal->FindBin( tmp[0]+10, tmp[1]+0.0001 );
       float nom = nominal->GetBinContent( bin );
       float nomS = nominalS->GetBinContent( bin );
       std::cout << "nomS: " << nomS << std::endl;
       std::cout << "nomB: " << nom << std::endl;
       float totalFractionalUncertaintySqr = 0;

       //ISR systematic
       ISRUpS->SetBinContent( bin, (nomS > 0) ? ISRUpS->GetBinContent(bin)/nomS: 0 );
       ISRDownS->SetBinContent( bin, (nomS > 0) ? ISRDownS->GetBinContent(bin)/nomS: 0 );

       //Fac
       facScaleUpS->SetBinContent( bin, (nomS > 0) ? facScaleUpS->GetBinContent(bin)/nomS : 0);
       facScaleDownS->SetBinContent( bin, (nomS > 0) ? facScaleDownS->GetBinContent(bin)/nomS : 0 );
       //Ren
       renScaleUpS->SetBinContent( bin, (nomS > 0) ? renScaleUpS->GetBinContent(bin)/nomS : 0 );
       renScaleDownS->SetBinContent( bin, (nomS > 0) ? renScaleDownS->GetBinContent(bin)/nomS : 0 );
       //facRen
       facRenScaleUpS->SetBinContent( bin, (nomS > 0) ? facRenScaleUpS->GetBinContent(bin)/nomS : 0 );
       facRenScaleDownS->SetBinContent( bin, (nomS > 0) ? facRenScaleDownS->GetBinContent(bin)/nomS : 0 );
       //JES
       JesUpS->SetBinContent( bin, (nomS > 0) ? JesUpS->GetBinContent( bin )/nomS : 0 );
       JesDownS->SetBinContent( bin, (nomS > 0) ? JesDownS->GetBinContent( bin )/nomS : 0 );

       //btag
       btagUpS->SetBinContent( bin, (nomS > 0) ? btagUpS->GetBinContent( bin )/nomS : 0 );
       btagDownS->SetBinContent( bin, (nomS > 0) ? btagDownS->GetBinContent( bin )/nomS : 0 );
       //misstag
       misstagUpS->SetBinContent( bin, (nomS > 0) ? misstagUpS->GetBinContent( bin )/nomS : 0 );
       misstagDownS->SetBinContent( bin, (nomS > 0) ? misstagDownS->GetBinContent( bin )/nomS : 0 );

       outf << tmp[4] << "\t" << categoryMode << "\t" << tmp[0] << "\t" << tmp[2] << " \t" << tmp[1] << "\t" << tmp[3] << "\t"
	    << nominal->GetBinContent( bin ) << "\t"
	    << JesUp->GetBinContent( bin ) << "\t" <<  JesDown->GetBinContent( bin ) << "\t"
	    <<  facScaleUp->GetBinContent( bin ) << "\t" <<  facScaleDown->GetBinContent( bin ) << "\t"
	    <<  renScaleUp->GetBinContent( bin ) << "\t" <<  renScaleDown->GetBinContent( bin ) << "\t"
	    <<  facRenScaleUp->GetBinContent( bin ) << "\t" <<  facRenScaleDown->GetBinContent( bin ) << "\t";
       
       totalFractionalUncertaintySqr += pow( (fabs(JesUp->GetBinContent( bin )) + fabs(JesDown->GetBinContent( bin )))/2,2) 
	 + pow( (fabs(facScaleUp->GetBinContent( bin )) + fabs(facScaleDown->GetBinContent( bin )))/2,2) 
	 + pow( (fabs(renScaleUp->GetBinContent( bin )) + fabs(renScaleDown->GetBinContent( bin )))/2,2) 
	 + pow( (fabs(facRenScaleUp->GetBinContent( bin )) + fabs(facRenScaleDown->GetBinContent( bin )))/2,2);

       for( int ipdf = 0; ipdf < 60; ipdf++ )
	 {
	   outf << pdf[ipdf]->GetBinContent( bin ) << "\t";
	   totalFractionalUncertaintySqr += pow( pdf[ipdf]->GetBinContent( bin ) ,2);
	 }

       //add total cross section uncertainties
       totalFractionalUncertaintySqr += 
	 pow( 0.04 ,2)  //lumi
	 + pow( 0.05 ,2)  //photon selection
	 //+ pow( 0.067 ,2)  //scale variation
	 + pow( 0.057 ,2)  //PDF
	 ;

       if (tmp[5] == 8) totalFractionalUncertaintySqr += pow( 0.04 ,2); //for btag efficiency systematic

       //Signal
       if ( categoryMode == "highres") nomS = highres_sigmaMoverM_corr*nomS;
       if ( categoryMode == "lowres") nomS = lowres_sigmaMoverM_corr*nomS;
       outf <<  nomS << "\t"
	    << JesUpS->GetBinContent( bin ) << "\t" <<  JesDownS->GetBinContent( bin ) << "\t"
	    << ISRUpS->GetBinContent( bin ) << "\t" <<  ISRDownS->GetBinContent( bin ) << "\t"
	    << facScaleUpS->GetBinContent( bin ) << "\t" <<  facScaleDownS->GetBinContent( bin ) << "\t"
	    <<  renScaleUpS->GetBinContent( bin )    << "\t" <<  renScaleDownS->GetBinContent( bin ) << "\t"
	    <<  facRenScaleUpS->GetBinContent( bin ) << "\t" <<  facRenScaleDownS->GetBinContent( bin ) << "\t";
       
       for( int ipdf = 0; ipdf < 60; ipdf++ )
	 {
	   if ( ipdf < 59 ) outf << ((nomS > 0) ? pdfS[ipdf]->GetBinContent( bin )/nomS : 0) << "\t";
	   else outf << ((nomS > 0) ? pdfS[ipdf]->GetBinContent( bin )/nomS : 0) << "\t";
	 }
      
       //Normalizing FastSIm
       if ( (nomS > 0) ) {
	 if (genMetS->GetBinContent( bin )/nomS <= -1) {
	   genMetS->SetBinContent( bin, -0.99);
	 } else {
	   genMetS->SetBinContent( bin, (nomS > 0) ? genMetS->GetBinContent( bin )/nomS : 0 );
	 }
	 if (pileupS->GetBinContent( bin )/nomS <= -1) {
	   pileupS->SetBinContent( bin, -0.99);
	 } else {
	   pileupS->SetBinContent( bin, (nomS > 0) ? pileupS->GetBinContent( bin )/nomS : 0 );
	 }
       } else {
	 genMetS->SetBinContent( bin, 0);
	 pileupS->SetBinContent( bin, 0 );
       }

       
       if ( isEWKSUSYSignal ) 
	 {
	   outf << genMetS->GetBinContent( bin ) << "\t";
	   outf << pileupS->GetBinContent( bin ) << "\n";
	 } 
       else 
	 {
	   outf << "0.0" << "\t";
	   outf << "0.0" << "\n";
	 }
       
       std::cout << "Bin : " << bin << " " << tmp[0] << " " << tmp[1] << " " << tmp[2] << " " << tmp[3] << " : "
	    << nom << " +/- " << 100*sqrt(totalFractionalUncertaintySqr) << "%\n";
 
     }

   outf.close();
   

   /*
   TFile* sF = new TFile( Form("fullSys_categoryMode_%d.root", rand()), "recreate" );
   nominal->Write("SMH_nominal");
   facScaleUp->Write("facScaleUp");
   facScaleDown->Write("facScaleDown");
   renScaleUp->Write("renScaleUp");
   renScaleDown->Write("renScaleDown");
   facRenScaleUp->Write("facRenScaleUp");
   facRenScaleDown->Write("facRenScaleDown");
   JesUp->Write("JesUp");
   JesDown->Write("JesDown");
   btagUp->Write("btagUp");
   btagDown->Write("btagDown");
   misstagUp->Write("misstagUp");
   misstagDown->Write("misstagDown");
   for( int ipdf = 0; ipdf < 60; ipdf++ ) pdf[ipdf]->Write();
   sF->Close();
   */
   return 0;
};

