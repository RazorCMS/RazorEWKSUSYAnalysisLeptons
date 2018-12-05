#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <assert.h>
//ROOT INCLUDES
#include <TFile.h>
#include <TROOT.h>
#include <TH2Poly.h>
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
      std::cerr << "[ERROR]: please provide the category. Use --category=<inclusiveElectron,inclusiveMuon,twoLeptons>" << std::endl;
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
      std::cerr << "[ERROR]: please provide the analysisTag. Use --analysisTag=<Razor2015_76X,Razor2016_80X,Razor2017_92X>" << std::endl;
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
  
  const float highres_sigmaMoverM_corr = 1.0 - 0.10749;//1.0+(data-MC)/MC
  const float lowres_sigmaMoverM_corr = 1.0 + 0.24268;//1.0+(data-MC)/MC

  //-----------------
  //Load Binning
  //-----------------
  std::vector<Bin> binVector;
  //std::cout << binDefinitionFilename << std::endl;
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

  TString cut;
  TString cutSignal;
  TString triggerCut;
  if ( analysisTag == "Razor2016_80X" ) 
    {
      //cut = "mGammaGamma > 103. && mGammaGamma < 160. && pho1passIso == 1 && pho2passIso == 1 && pho1passEleVeto == 1 && pho2passEleVeto == 1 && abs(pho1Eta) <1.48 && abs(pho2Eta)<1.48 && (pho1Pt>40||pho2Pt>40)  && pho1Pt> 25. && pho2Pt>25. ";
      cut = "mGammaGamma > 103. && mGammaGamma < 160. && pho1passIso == 1 && pho2passIso == 1 && pho1passEleVeto == 1 && pho2passEleVeto == 1 && abs(pho1SC_Eta) <1.4442 && abs(pho2SC_Eta)<1.4442 && (pho1Pt/mGammaGamma>1./3. || pho2Pt/mGammaGamma>1./3.) && pho1Pt/mGammaGamma>1./4. && pho2Pt/mGammaGamma>1./4. && pho1R9>0.5 && pho2R9>0.5 ";
      //triggerCut = " ";
      //triggerCut = " &&  HLTDecision[82]  ";
      triggerCut = " && ( HLTDecision[82] || HLTDecision[83] ) ";
      //triggerCut = " && ( HLTDecision[82] || HLTDecision[83] || HLTDecision[93] ) ";
    } 
  else if ( analysisTag == "Razor2017_92X" ) 
    {
      cut = "mGammaGamma > 103. && mGammaGamma < 160. && pho1passIso == 1 && pho2passIso == 1 && pho1passEleVeto == 1 && pho2passEleVeto == 1 && abs(pho1SC_Eta) <1.4442 && abs(pho2SC_Eta)<1.4442 && (pho1Pt/mGammaGamma>1./3. || pho2Pt/mGammaGamma>1./3.) && pho1Pt/mGammaGamma>1./4. && pho2Pt/mGammaGamma>1./4. && pho1R9>0.5 && pho2R9>0.5 ";
      //triggerCut = " && HLTDecision[54]  ";
      triggerCut = " && ( HLTDecision[54] || HLTDecision[55] ) ";
    } 
    cutSignal = cut;

  //--------------------------
  //Category CUT Strings
  //--------------------------
  TString categoryCutString;
  if (categoryMode == "highpt") categoryCutString          = " && box==5 ";
  else if (categoryMode == "hbb") categoryCutString        = " && box==6";
  else if (categoryMode == "hbbhighpt") categoryCutString  = " && pTGammaGamma >= 110 && box==6";
  else if (categoryMode == "hbblowpt") categoryCutString   = " && pTGammaGamma < 110 && box==6";
  else if (categoryMode == "zbb") categoryCutString        = " && box==7";
  else if (categoryMode == "zbbhighpt") categoryCutString  = " && pTGammaGamma >= 110 && box==7";
  else if (categoryMode == "zbblowpt") categoryCutString   = " && pTGammaGamma < 110 && box==7";
  else if (categoryMode == "highres") categoryCutString    = " && box==8 ";
  else if (categoryMode == "lowres") categoryCutString     = " && box==9 ";
  else if (categoryMode == "muhighpt") categoryCutString   = " && pTGammaGamma >= 110 && box == 3 && lep1Pt > 20. ";
  else if (categoryMode == "mulowpt") categoryCutString    = " && pTGammaGamma < 110 && box == 3 && lep1Pt > 20. ";
  else if (categoryMode == "elehighpt") categoryCutString  = " && pTGammaGamma >= 110 && box == 4 && lep1Pt > 20. ";
  else if (categoryMode == "elelowpt") categoryCutString   = " && pTGammaGamma < 110 && box == 4 && lep1Pt > 20. ";
  else if (categoryMode == "twoleptons") categoryCutString = " && (box == 0 || box == 1 || box == 2)";
  else if (categoryMode == "inclusive") categoryCutString  = "";
  else if (categoryMode == "ele") categoryCutString        = "&& box == 4 && lep1Pt > 20. ";
  
  //TString metFilterCut = " && (Flag_HBHENoiseFilter == 1 && Flag_CSCTightHaloFilter == 1 && Flag_goodVertices == 1 && Flag_eeBadScFilter == 1 && Flag_HBHEIsoNoiseFilter == 1)";
  TString metFilterCut2016 = " && (Flag_HBHENoiseFilter == 1 && Flag_CSCTightHaloFilter == 1 && Flag_goodVertices == 1 && Flag_HBHEIsoNoiseFilter == 1 && Flag_EcalDeadCellTriggerPrimitiveFilter==1 && Flag_badMuonFilter==1  && Flag_badChargedCandidateFilter==1 )";
  //TString metFilterCut2017 = " && (Flag_HBHENoiseFilter == 1 && Flag_CSCTightHaloFilter == 1 && Flag_goodVertices == 1 && Flag_HBHEIsoNoiseFilter == 1 && Flag_EcalDeadCellTriggerPrimitiveFilter==1 && Flag_badMuonFilter==1  && Flag_badChargedCandidateFilter==1 )";
  TString metFilterCut2017 = " && (Flag_HBHENoiseFilter == 1 && Flag_CSCTightHaloFilter == 1 && Flag_goodVertices == 1 && Flag_HBHEIsoNoiseFilter == 1 && Flag_EcalDeadCellTriggerPrimitiveFilter==1 && Flag_BadPFMuonFilter==1  && Flag_BadChargedCandidateFilter==1 && Flag_ecalBadCalibFilter==1) ";
  TString metFilterCut = " && (Flag_HBHENoiseFilter == 1 && Flag_goodVertices == 1 && Flag_eeBadScFilter == 1 && Flag_HBHEIsoNoiseFilter == 1)";

    TString triggerCutSignal = "";
    TString triggerCutSignal2016 = " && ( HLTDecision[82] || HLTDecision[83] ) ";
    //using 2016 signal for pre-approval
    TString triggerCutSignal2017 = " && ( HLTDecision[82] || HLTDecision[83] ) ";
    TString metFilterCutSignal = "";
    TString metFilterCut2016Signal = " && (Flag_HBHENoiseFilter == 1 && Flag_CSCTightHaloFilter == 1 && Flag_goodVertices == 1 && Flag_HBHEIsoNoiseFilter == 1 && Flag_EcalDeadCellTriggerPrimitiveFilter==1 && Flag_badMuonFilter==1  && Flag_badChargedCandidateFilter==1 )";
    //using 2016 signal for pre-approval
    TString metFilterCut2017Signal = " && (Flag_HBHENoiseFilter == 1 && Flag_CSCTightHaloFilter == 1 && Flag_goodVertices == 1 && Flag_HBHEIsoNoiseFilter == 1 && Flag_EcalDeadCellTriggerPrimitiveFilter==1 && Flag_badMuonFilter==1  && Flag_badChargedCandidateFilter==1 )";
  
//For fastsim signals, turn off trigger and met filters
  if (isEWKSUSYSignal) {
    triggerCutSignal = "";
    triggerCutSignal2016 = "";
    metFilterCutSignal = "";
    metFilterCut2016Signal = "";
    metFilterCut2017Signal = "";
  }

  if ( analysisTag == "Razor2015_76X" ) 
    {
      cut = cut + categoryCutString + triggerCut+ metFilterCut;  
    } 
  else if ( analysisTag == "Razor2016_80X" ) 
    {
      cut = cut + categoryCutString + triggerCut + metFilterCut2016;
      cutSignal = cutSignal + categoryCutString + triggerCutSignal2016 + metFilterCut2016Signal;
    } 
  else if ( analysisTag == "Razor2017_92X" ) 
    {
      cut = cut + categoryCutString + triggerCut + metFilterCut2017 ;
      //cutSignal = cut;
      cutSignal = cutSignal + categoryCutString + triggerCutSignal2017 + metFilterCut2017Signal;
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
/*
  if ( categoryMode == "highreslowres" ) {
      binCategory = "highres"; //use highres binning
  }
  else if ( categoryMode == "highpthighres" || categoryMode == "highptlowres" ) {
      binCategory = "highpt"; //use highpt binning
  }
*/
  myVectBinning = SetBinning(binVector, binCategory);
  std::cout << "[INFO]: set binning \n"<< std::endl;


  /*
  if (!(binCategory == "inclusiveElectron" || binCategory == "inclusiveMuon" || binCategory == "twoLeptons"))
     {
       std::cerr << "[ERROR]: category is not <inclusiveElectron/inclusiveMuon/twoLeptons>; quitting" << std::endl;
       return -1;
     } 
  */
  TH2Poly* nominal  = new TH2Poly("nominal_SMH", "", 0, 10000, 0, 1 );
  TH2Poly* nominalS = new TH2Poly("nominal_Signal", "", 0, 10000, 0, 1 );

  TH2Poly* ISRUpS   = new TH2Poly("ISRUpS", "", 0, 10000, 0, 1 );
  TH2Poly* ISRDownS = new TH2Poly("ISRDownS", "", 0, 10000, 0, 1 );

  TH2Poly* facScaleUp    = new TH2Poly("facScaleUp", "", 0, 10000, 0, 1 );
  TH2Poly* facScaleDown  = new TH2Poly("facScaleDown", "", 0, 10000, 0, 1 );
  TH2Poly* facScaleUpS   = new TH2Poly("facScaleUpS", "", 0, 10000, 0, 1 );
  TH2Poly* facScaleDownS = new TH2Poly("facScaleDownS", "", 0, 10000, 0, 1 );
  
  TH2Poly* renScaleUp    = new TH2Poly("renScaleUp", "", 0, 10000, 0, 1 );
  TH2Poly* renScaleDown  = new TH2Poly("renScaleDown", "", 0, 10000, 0, 1 );
  TH2Poly* renScaleUpS   = new TH2Poly("renScaleUpS", "", 0, 10000, 0, 1 );
  TH2Poly* renScaleDownS = new TH2Poly("renScaleDownS", "", 0, 10000, 0, 1 );
  
  TH2Poly* facRenScaleUp    = new TH2Poly("facRenScaleUp", "", 0, 10000, 0, 1 );
  TH2Poly* facRenScaleDown  = new TH2Poly("facRenScaleDown", "", 0, 10000, 0, 1 );
  TH2Poly* facRenScaleUpS   = new TH2Poly("facRenScaleUpS", "", 0, 10000, 0, 1 );
  TH2Poly* facRenScaleDownS = new TH2Poly("facRenScaleDownS", "", 0, 10000, 0, 1 );
  
  TH2Poly* JesUp    = new TH2Poly("JesUp", "", 0, 10000, 0, 1 );
  TH2Poly* JesDown  = new TH2Poly("JesDown", "", 0, 10000, 0, 1 );
  TH2Poly* JesUpS   = new TH2Poly("JesUpS", "", 0, 10000, 0, 1 );//signal
  TH2Poly* JesDownS = new TH2Poly("JesDownS", "", 0, 10000, 0, 1 );//signal

  TH2Poly* btagUp    = new TH2Poly("btagUp", "", 0, 10000, 0, 1 );
  TH2Poly* btagDown  = new TH2Poly("btagDown", "", 0, 10000, 0, 1 );
  TH2Poly* btagUpS   = new TH2Poly("btagUpS", "", 0, 10000, 0, 1 );//signal
  TH2Poly* btagDownS = new TH2Poly("btagDownS", "", 0, 10000, 0, 1 );//signal

  TH2Poly* misstagUp    = new TH2Poly("misstagUp", "", 0, 10000, 0, 1 );
  TH2Poly* misstagDown  = new TH2Poly("misstagDown", "", 0, 10000, 0, 1 );
  TH2Poly* misstagUpS   = new TH2Poly("misstagUpS", "", 0, 10000, 0, 1 );//signal
  TH2Poly* misstagDownS = new TH2Poly("misstagDownS", "", 0, 10000, 0, 1 );//signal
  
  TH2Poly* genMetS = new TH2Poly("genMet_Signal", "", 0, 10000, 0, 1 );//signal
  TH2Poly* pileupS = new TH2Poly("pileup_Signal", "", 0, 10000, 0, 1 );//signal

  TH2Poly* pdf[60];
  TH2Poly* pdfS[60];
  for ( int i = 0; i < 60; i++ )
    {
      TString pdfName = Form("pdf%d", i);
      pdf[i]  = new TH2Poly( pdfName, "", 0, 10000, 0, 1 );
      pdfS[i] = new TH2Poly( pdfName+"S", "", 0, 10000, 0, 1 );
    }
  std::map< std::pair<float,float>, float > sysMap;
  for ( auto tmp : myVectBinning )
    {
      nominal->AddBin( tmp[0], tmp[1], tmp[2], tmp[3] );
      nominalS->AddBin( tmp[0], tmp[1], tmp[2], tmp[3] );
      ISRUpS->AddBin( tmp[0], tmp[1], tmp[2], tmp[3] );
      ISRDownS->AddBin( tmp[0], tmp[1], tmp[2], tmp[3] );
      facScaleUp->AddBin( tmp[0], tmp[1], tmp[2], tmp[3] );
      facScaleUpS->AddBin( tmp[0], tmp[1], tmp[2], tmp[3] );
      facScaleDown->AddBin( tmp[0], tmp[1], tmp[2], tmp[3] );
      facScaleDownS->AddBin( tmp[0], tmp[1], tmp[2], tmp[3] );
      renScaleUp->AddBin( tmp[0], tmp[1], tmp[2], tmp[3] );
      renScaleUpS->AddBin( tmp[0], tmp[1], tmp[2], tmp[3] );
      renScaleDown->AddBin( tmp[0], tmp[1], tmp[2], tmp[3] );
      renScaleDownS->AddBin( tmp[0], tmp[1], tmp[2], tmp[3] );
      facRenScaleUp->AddBin( tmp[0], tmp[1], tmp[2], tmp[3] );
      facRenScaleUpS->AddBin( tmp[0], tmp[1], tmp[2], tmp[3] );
      facRenScaleDown->AddBin( tmp[0], tmp[1], tmp[2], tmp[3] );
      facRenScaleDownS->AddBin( tmp[0], tmp[1], tmp[2], tmp[3] );
      JesUp->AddBin( tmp[0], tmp[1], tmp[2], tmp[3] );
      JesUpS->AddBin( tmp[0], tmp[1], tmp[2], tmp[3] );
      JesDown->AddBin( tmp[0], tmp[1], tmp[2], tmp[3] );
      JesDownS->AddBin( tmp[0], tmp[1], tmp[2], tmp[3] );

      //btag
      btagUp->AddBin( tmp[0], tmp[1], tmp[2], tmp[3] );
      btagUpS->AddBin( tmp[0], tmp[1], tmp[2], tmp[3] );
      btagDown->AddBin( tmp[0], tmp[1], tmp[2], tmp[3] );
      btagDownS->AddBin( tmp[0], tmp[1], tmp[2], tmp[3] );
      //misstag
      misstagUp->AddBin( tmp[0], tmp[1], tmp[2], tmp[3] );
      misstagUpS->AddBin( tmp[0], tmp[1], tmp[2], tmp[3] );
      misstagDown->AddBin( tmp[0], tmp[1], tmp[2], tmp[3] );
      misstagDownS->AddBin( tmp[0], tmp[1], tmp[2], tmp[3] );
      //pdf
      for( int i = 0; i < 60; i++ )
	{
	  pdf[i]->AddBin( tmp[0], tmp[1], tmp[2], tmp[3] );
	  pdfS[i]->AddBin( tmp[0], tmp[1], tmp[2], tmp[3] );
	}
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

      TString tmpName = Form("tmp_%d.root", rand());
      TFile* tmp = new TFile( tmpName , "RECREATE");
      TTree* cutTree ;
      if ( process == "signal" ) 
      {
	cutTree= tree->CopyTree( cutSignal );
      if ( _debug ) std::cout << "[INFO]: cutSignal: " << cutSignal << " \n\n"<< std::endl;
      }
      else
      {
	 cutTree= tree->CopyTree( cut );
      if ( _debug ) std::cout << "[INFO]: cut: " << cut << " \n\n"<< std::endl;
      }
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
      hggSys->LoadNPVTarget("/data/jmao/CMSSW_9_2_1/src/RazorEWKSUSYAnalysisLeptons/HggRazorLeptons/PlottingAndSystematic/data/PileUpDistribution/NPVTarget_2016.root");
      if ( isEWKSUSYSignal ) hggSys->SetISRPtHisto( ISRPtHist );
      hggSys->Loop();
      for ( auto tmp: myVectBinning )
	{
	  int bin = nominal->FindBin( tmp[0]+10, tmp[1]+0.0001 );
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
		  //pdfS[ipdf]->SetBinContent( bin, 0 );		 
		}

	      genMetS->SetBinContent( bin, hggSys->GetGenMetSystematic( tmp[0], tmp[1] ) );
	      pileupS->SetBinContent( bin, hggSys->GetNominalError( tmp[0], tmp[1] ) );


	    }
	  else
	    {
	      nominal->SetBinContent( bin, nominal->GetBinContent(bin) + hggSys->GetNominalYield( tmp[0], tmp[1] ) );
	      //facScale
	      std::pair<float, float> facSys = hggSys->GetFacScaleSystematic( tmp[0], tmp[1] );
	      float maxSys = std::max( fabs(facSys.first) , fabs(facSys.second) );
	      facScaleUp->SetBinContent( bin, sqrt( pow( facScaleUp->GetBinContent(bin), 2 ) + pow( maxSys, 2 ) ) );
	      facScaleDown->SetBinContent( bin, sqrt( pow( facScaleDown->GetBinContent(bin), 2 ) + pow( maxSys, 2 ) ) );
	      //renScale
	      facSys = hggSys->GetRenScaleSystematic( tmp[0], tmp[1] );
	      maxSys = std::max( fabs(facSys.first) , fabs(facSys.second) );
	      renScaleUp->SetBinContent( bin, sqrt( pow( renScaleUp->GetBinContent(bin), 2 ) + pow( maxSys, 2) ) );
	      renScaleDown->SetBinContent( bin, sqrt( pow( renScaleDown->GetBinContent(bin), 2 ) + pow( maxSys, 2 ) ) );
	      //facRenScale
	      facSys = hggSys->GetFacRenScaleSystematic( tmp[0], tmp[1] );
	      maxSys = std::max( fabs(facSys.first) , fabs(facSys.second) );
	      facRenScaleUp->SetBinContent( bin, sqrt( pow( facRenScaleUp->GetBinContent(bin), 2 ) + pow( maxSys, 2 ) ) );
	      facRenScaleDown->SetBinContent( bin, sqrt( pow( facRenScaleDown->GetBinContent(bin), 2 ) + pow( maxSys, 2 ) ) );
	      //JES
	      facSys = hggSys->GetJesSystematic( tmp[0], tmp[1] );
	      JesUp->SetBinContent( bin, JesUp->GetBinContent(bin) + facSys.first );
	      JesDown->SetBinContent( bin, JesDown->GetBinContent(bin) + facSys.second );

	      //btag
	      facSys = hggSys->GetBtagSystematic( tmp[0], tmp[1] );
	      btagUp->SetBinContent( bin, btagUp->GetBinContent(bin) + facSys.first );
	      btagDown->SetBinContent( bin, btagDown->GetBinContent(bin) + facSys.second );
	      //misstag
	      facSys = hggSys->GetMisstagSystematic( tmp[0], tmp[1] );
	      misstagUp->SetBinContent( bin, misstagUp->GetBinContent(bin) + facSys.first );
	      misstagDown->SetBinContent( bin, misstagDown->GetBinContent(bin) + facSys.second );
	      //PDF
	      for ( int ipdf = 0; ipdf < 60; ipdf++ )
		{
		  pdf[ipdf]->SetBinContent( bin, sqrt( pow( pdf[ipdf]->GetBinContent(bin), 2 ) + pow( hggSys->GetPdfSystematic( ipdf, tmp[0], tmp[1] ), 2 ) ) );		  
		}
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

     std::cout << "Bin : " << bin << " " << tmp[0] << " " << tmp[1] << " " << tmp[2] << " " << tmp[3] << " : SMH yield "
 	 << nom << " ; Signal Yield " <<  nomS << "\n";

       float totalFractionalUncertaintySqr = 0;

       //ISR systematic
       ISRUpS->SetBinContent( bin, ISRUpS->GetBinContent(bin)/nomS );
       ISRDownS->SetBinContent( bin, ISRDownS->GetBinContent(bin)/nomS );

       //Fac
       facScaleUp->SetBinContent( bin, facScaleUp->GetBinContent(bin)/nom );
       facScaleDown->SetBinContent( bin, facScaleDown->GetBinContent(bin)/nom );
       facScaleUpS->SetBinContent( bin, facScaleUpS->GetBinContent(bin)/nomS );
       facScaleDownS->SetBinContent( bin, facScaleDownS->GetBinContent(bin)/nomS );
       //Ren
       renScaleUp->SetBinContent( bin, renScaleUp->GetBinContent(bin)/nom );
       renScaleDown->SetBinContent( bin, renScaleDown->GetBinContent(bin)/nom );
       renScaleUpS->SetBinContent( bin, renScaleUpS->GetBinContent(bin)/nomS );
       renScaleDownS->SetBinContent( bin, renScaleDownS->GetBinContent(bin)/nomS );
       //facRen
       facRenScaleUp->SetBinContent( bin, facRenScaleUp->GetBinContent(bin)/nom );
       facRenScaleDown->SetBinContent( bin, facRenScaleDown->GetBinContent(bin)/nom );
       facRenScaleUpS->SetBinContent( bin, facRenScaleUpS->GetBinContent(bin)/nomS );
       facRenScaleDownS->SetBinContent( bin, facRenScaleDownS->GetBinContent(bin)/nomS );
       //JES
       JesUp->SetBinContent( bin, JesUp->GetBinContent( bin )/nom );
       JesDown->SetBinContent( bin, JesDown->GetBinContent( bin )/nom );
       JesUpS->SetBinContent( bin, JesUpS->GetBinContent( bin )/nomS );
       JesDownS->SetBinContent( bin, JesDownS->GetBinContent( bin )/nomS );

       //btag
       btagUp->SetBinContent( bin, btagUp->GetBinContent( bin )/nom );
       btagDown->SetBinContent( bin, btagDown->GetBinContent( bin )/nom );
       btagUpS->SetBinContent( bin, btagUpS->GetBinContent( bin )/nomS );
       btagDownS->SetBinContent( bin, btagDownS->GetBinContent( bin )/nomS );
       //misstag
       misstagUp->SetBinContent( bin, misstagUp->GetBinContent( bin )/nom );
       misstagDown->SetBinContent( bin, misstagDown->GetBinContent( bin )/nom );
       misstagUpS->SetBinContent( bin, misstagUpS->GetBinContent( bin )/nomS );
       misstagDownS->SetBinContent( bin, misstagDownS->GetBinContent( bin )/nomS );

       if ( categoryMode == "highres") nominal->SetBinContent( bin, highres_sigmaMoverM_corr*nominal->GetBinContent( bin ) );
       if ( categoryMode == "lowres") nominal->SetBinContent( bin, lowres_sigmaMoverM_corr*nominal->GetBinContent( bin ) );
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

       genMetS->SetBinContent( bin, genMetS->GetBinContent( bin )/nomS );
       pileupS->SetBinContent( bin, pileupS->GetBinContent( bin )/nomS );

       for( int ipdf = 0; ipdf < 60; ipdf++ )
	 {
	   pdf[ipdf]->SetBinContent( bin, pdf[ipdf]->GetBinContent( bin )/nom );
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
	   //pdf[ipdf]->SetBinContent( bin, pdf[ipdf]->GetBinContent( bin )/nom );
	   //pdf[ipdf]->SetBinContent( bin, 0 ); //zero out pdf uncertainties for signal for now
	   if ( ipdf < 59 ) outf << pdfS[ipdf]->GetBinContent( bin )/nomS << "\t";
	   else outf << pdfS[ipdf]->GetBinContent( bin )/nomS << "\t";
	 }

       //genMet systematics
       if ( isEWKSUSYSignal ) {
	 outf << genMetS->GetBinContent( bin ) << "\t";
	 outf << pileupS->GetBinContent( bin ) << "\t";
       } else {
	 outf << "0.0" << "\t";
	 outf << "0.0" << "\t";
       }
       
       outf << "\n";
      
       std::cout << "Bin : " << bin << " " << tmp[0] << " " << tmp[1] << " " << tmp[2] << " " << tmp[3] << " : "
		 << "SMH Yield : " << nom << " +/- " << 100*sqrt(totalFractionalUncertaintySqr) << "%; signal: " << nomS << "\n";
 
     }

   outf.close();
   
   
   TFile* sF = new TFile( Form("fullSys_%s_%d.root", categoryMode.c_str(), rand()), "recreate" );
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
   
   return 0;
};

