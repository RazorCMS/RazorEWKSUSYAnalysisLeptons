//C++ INCLUDES
#include <iostream>
#include <math.h>
#include <string>
#include <assert.h>
//ROOT INCLUDES
#include <TFitResult.h>
#include <TCanvas.h>
//LOCAL INCLUDES
#include "HggRazorSystematics.hh"

HggRazorSystematics::HggRazorSystematics( ){ };

HggRazorSystematics::HggRazorSystematics( TTree* tree ) : HggTree( tree ), _info( false ), _debug( false )
{

};

HggRazorSystematics::HggRazorSystematics( TTree* tree, TString processName, TString boxName, std::string analysisTag, bool info, bool debug ) : HggTree( tree ), _analysisTag(analysisTag), _info( info ), _useISRPtCorrection(false), _debug( debug )
{
  //processName
  if ( processName == "" )
    {
      this->processName = "dummy_process";
    }
  else
    {
      this->processName = processName;
    }
  //boxName
  if ( boxName == "" )
    {
      this->boxName = "dummy_box";
    }
  else
    {
      this->boxName = boxName;
    }

};


HggRazorSystematics::HggRazorSystematics( TTree* tree, TString processName, TString boxName, std::string analysisTag, bool info, bool useISRPtCorrection, bool debug ) : HggTree( tree ), _analysisTag(analysisTag), _info( info ), _useISRPtCorrection(useISRPtCorrection), _debug( debug )
{
  //processName
  if ( processName == "" )
    {
      this->processName = "dummy_process";
    }
  else
    {
      this->processName = processName;
    }
  //boxName
  if ( boxName == "" )
    {
      this->boxName = "dummy_box";
    }
  else
    {
      this->boxName = boxName;
    }  

};


HggRazorSystematics::~HggRazorSystematics()
{
  if ( _debug ) std::cout << "[DEBUG]: Entering Destructor" << std::endl;
  
  if ( this->h2p != NULL ) delete h2p;
  if ( this->h2p_eff != NULL ) delete h2p_eff;
  if ( this->h2p_ISRUp != NULL ) delete h2p_ISRUp;
  if ( this->h2p_ISRDown != NULL ) delete h2p_ISRDown;
  if ( this->h2p_facScaleUp != NULL ) delete h2p_facScaleUp;
  if ( this->h2p_facScaleDown != NULL ) delete h2p_facScaleDown;
  if ( this->h2p_renScaleUp != NULL ) delete h2p_renScaleUp;
  if ( this->h2p_renScaleDown != NULL ) delete h2p_renScaleDown;
  if ( this->h2p_facRenScaleUp != NULL ) delete h2p_facRenScaleUp;
  if ( this->h2p_facRenScaleDown != NULL ) delete h2p_facRenScaleDown;
  if ( this->h2p_genMet != NULL ) delete h2p_genMet;
  if ( this->h2p_pileupLowNPV != NULL ) delete h2p_pileupLowNPV;
  if ( this->h2p_pileupHighNPV != NULL ) delete h2p_pileupHighNPV;
  if ( this->h2p_pileupLowNPVErrSqr != NULL ) delete h2p_pileupLowNPVErrSqr;
  if ( this->h2p_pileupHighNPVErrSqr != NULL ) delete h2p_pileupHighNPVErrSqr;
  
  if ( this->NEvents != NULL ) delete NEvents;
  if ( this->SumScaleWeights != NULL ) delete SumScaleWeights;
  if ( this->SumPdfWeights != NULL ) delete SumPdfWeights;
  //if ( this->ISRHist != NULL ) delete ISRHist;
  
  if ( _debug ) std::cout << "[DEBUG]: Finishing Destructor" << std::endl;
};

void HggRazorSystematics::PrintBinning()
{
  if ( _debug ) std::cout << "[INFO]: this is the binning for category <" << this->boxName << ">" << std::endl;
  if ( this->binningMap.size() == 0 ) std::cerr << "[WARNING]: no binning defined yet, please use object->SetBinningMap( yourMap );" << std::endl;
  for ( auto tmp : this->binningMap )
    {
      std::cout << "MR: " << tmp.first.first << "-" << tmp.first.second << " GeV --> Rsq: ";
      for ( auto tmp2 : tmp.second ) std::cout << tmp2 << ", ";
      std::cout << "\n";
    }
}

void HggRazorSystematics::LoadNPVTarget(std::string filename) {
  TFile *file = TFile::Open(filename.c_str(),"READ");
  TH1F *tmp = (TH1F*)file->Get("NPV_2016")->Clone();
  assert(tmp);
  NPVTarget = (TH1F*)tmp->Clone("NPV_2016");
  NPVTarget->SetDirectory(0);
  file->Close();
  std::cout << "Load npv target: " << NPVTarget->GetXaxis()->GetNbins() << "\n";
}

bool HggRazorSystematics::InitMrRsqTH2Poly( int mode )
{
  if ( mode == 0 )
    {
      if ( _debug ) std::cout << "[INFO]: Creating TH2Poly mode: " << mode << std::endl;
      if ( this->binningMap.size() == 0 )
	{
	  std::cerr << "[ERROR]: Imposible to create TH2Poly; no binning defined yet, please use object->SetBinningMap( yourMap );" << std::endl;
	  return false;
	}
      h2p = new TH2Poly(this->processName+"_nominal", "", 0, 10000, 0, 1);
      h2p_Err = new TH2Poly(this->processName+"_nominal_err", "", 0, 10000, 0, 1);
      h2p_eff = new TH2Poly(this->processName+"_eff", "", 0, 10000, 0, 1);
      
      h2p_ISRUp      = new TH2Poly(this->processName+"_ISRUp", "", 0, 10000, 0, 1);
      h2p_ISRDown    = new TH2Poly(this->processName+"_ISRDown", "", 0, 10000, 0, 1);
      h2p_facScaleUp      = new TH2Poly(this->processName+"_facScaleUp", "", 0, 10000, 0, 1);
      h2p_facScaleDown    = new TH2Poly(this->processName+"_facScaleDown", "", 0, 10000, 0, 1);
      h2p_renScaleUp      = new TH2Poly(this->processName+"_renScaleUp", "", 0, 10000, 0, 1);
      h2p_renScaleDown    = new TH2Poly(this->processName+"_renScaleDown", "", 0, 10000, 0, 1);
      h2p_facRenScaleUp   = new TH2Poly(this->processName+"_facRenScaleUp", "", 0, 10000, 0, 1);
      h2p_facRenScaleDown = new TH2Poly(this->processName+"_facRenScaleDown", "", 0, 10000, 0, 1);
      h2p_JesUp           = new TH2Poly(this->processName+"_JesUp", "", 0, 10000, 0, 1);
      h2p_JesDown         = new TH2Poly(this->processName+"_JesDown", "", 0, 10000, 0, 1);
      for( int i = 0; i < n_PdfSys; i++ )
	{
	  TString PdfSysName = Form(this->processName+"_PdfEigenVect_%d",i);
	  h2p_Pdf[i] = new TH2Poly( PdfSysName, "", 0, 10000, 0, 1);
	}
      //btag
      h2p_btagUp   = new TH2Poly(this->processName+"_btagUp", "", 0, 10000, 0, 1);
      h2p_btagDown = new TH2Poly(this->processName+"_btagDown", "", 0, 10000, 0, 1);
      //misstag
      h2p_misstagUp   = new TH2Poly(this->processName+"_misstagUp", "", 0, 10000, 0, 1);
      h2p_misstagDown = new TH2Poly(this->processName+"_misstagDown", "", 0, 10000, 0, 1);
      //genmet
      h2p_genMet   = new TH2Poly(this->processName+"_genMet", "", 0, 10000, 0, 1);
      //pileup
      h2p_pileupLowNPV   = new TH2Poly(this->processName+"_pileupLowNPV", "", 0, 10000, 0, 1);
      h2p_pileupHighNPV   = new TH2Poly(this->processName+"_pileupHighNPV", "", 0, 10000, 0, 1);
      h2p_pileupLowNPVErrSqr   = new TH2Poly(this->processName+"_pileupLowNPVErrSqr", "", 0, 10000, 0, 1);
      h2p_pileupHighNPVErrSqr   = new TH2Poly(this->processName+"_pileupHighNPVErrSqr", "", 0, 10000, 0, 1);

      //adding bins
      for ( auto tmp : this->binningMap )
	{
	  int RsqSize = tmp.second.size();
	  for ( int i = 0; i < RsqSize-1; i++ )
	    {
	      h2p->AddBin( tmp.first.first, tmp.second.at(i), tmp.first.second, tmp.second.at(i+1) );
	      h2p_Err->AddBin( tmp.first.first, tmp.second.at(i), tmp.first.second, tmp.second.at(i+1) );
	      h2p_eff->AddBin( tmp.first.first, tmp.second.at(i), tmp.first.second, tmp.second.at(i+1) );

	      h2p_ISRUp->AddBin( tmp.first.first, tmp.second.at(i), tmp.first.second, tmp.second.at(i+1) );
	      h2p_ISRDown->AddBin( tmp.first.first, tmp.second.at(i), tmp.first.second, tmp.second.at(i+1) );
	      h2p_facScaleUp->AddBin( tmp.first.first, tmp.second.at(i), tmp.first.second, tmp.second.at(i+1) );
	      h2p_facScaleDown->AddBin( tmp.first.first, tmp.second.at(i), tmp.first.second, tmp.second.at(i+1) );
	      h2p_renScaleUp->AddBin( tmp.first.first, tmp.second.at(i), tmp.first.second, tmp.second.at(i+1) );
	      h2p_renScaleDown->AddBin( tmp.first.first, tmp.second.at(i), tmp.first.second, tmp.second.at(i+1) );
	      h2p_facRenScaleUp->AddBin( tmp.first.first, tmp.second.at(i), tmp.first.second, tmp.second.at(i+1) );
	      h2p_facRenScaleDown->AddBin( tmp.first.first, tmp.second.at(i), tmp.first.second, tmp.second.at(i+1) );
	      h2p_JesUp->AddBin( tmp.first.first, tmp.second.at(i), tmp.first.second, tmp.second.at(i+1) );
	      h2p_JesDown->AddBin( tmp.first.first, tmp.second.at(i), tmp.first.second, tmp.second.at(i+1) );
	      for ( int ipdf = 0; ipdf < n_PdfSys; ipdf++ ) h2p_Pdf[ipdf]->AddBin( tmp.first.first, tmp.second.at(i), tmp.first.second, tmp.second.at(i+1) );
	      h2p_btagUp->AddBin( tmp.first.first, tmp.second.at(i), tmp.first.second, tmp.second.at(i+1) );
	      h2p_btagDown->AddBin( tmp.first.first, tmp.second.at(i), tmp.first.second, tmp.second.at(i+1) );
	      h2p_misstagUp->AddBin( tmp.first.first, tmp.second.at(i), tmp.first.second, tmp.second.at(i+1) );
	      h2p_misstagDown->AddBin( tmp.first.first, tmp.second.at(i), tmp.first.second, tmp.second.at(i+1) );
	      h2p_genMet->AddBin( tmp.first.first, tmp.second.at(i), tmp.first.second, tmp.second.at(i+1) );
	      h2p_pileupLowNPV->AddBin( tmp.first.first, tmp.second.at(i), tmp.first.second, tmp.second.at(i+1) );
	      h2p_pileupHighNPV->AddBin( tmp.first.first, tmp.second.at(i), tmp.first.second, tmp.second.at(i+1) );
	      h2p_pileupLowNPVErrSqr->AddBin( tmp.first.first, tmp.second.at(i), tmp.first.second, tmp.second.at(i+1) );
	      h2p_pileupHighNPVErrSqr->AddBin( tmp.first.first, tmp.second.at(i), tmp.first.second, tmp.second.at(i+1) );
	    }
	}
      
      return true;
    }
  else if ( mode == 1 )
    {
      if ( _debug ) std::cout << "[INFO]: Creating TH2Poly mode: " << mode << std::endl;
      if ( this->binningVect.size() == 0 )
	{
	  std::cerr << "[ERROR]: Imposible to create TH2Poly; no binning defined yet, please use object->SetBinningVect( yourVect );" << std::endl;
	  return false;
	}

      
      h2p = new TH2Poly(this->processName+"_nominal", "", 0, 10000, 0, 1);
      h2p_Err = new TH2Poly(this->processName+"_nominal_err", "", 0, 10000, 0, 1);
      h2p_eff = new TH2Poly(this->processName+"_eff", "", 0, 10000, 0, 1);
      
      h2p_ISRUp      = new TH2Poly(this->processName+"_ISRUp", "", 0, 10000, 0, 1);
      h2p_ISRDown    = new TH2Poly(this->processName+"_ISRDown", "", 0, 10000, 0, 1);

      h2p_facScaleUp      = new TH2Poly(this->processName+"_facScaleUp", "", 0, 10000, 0, 1);
      h2p_facScaleDown    = new TH2Poly(this->processName+"_facScaleDown", "", 0, 10000, 0, 1);

      h2p_renScaleUp      = new TH2Poly(this->processName+"_renScaleUp", "", 0, 10000, 0, 1);
      h2p_renScaleDown    = new TH2Poly(this->processName+"_renScaleDown", "", 0, 10000, 0, 1);

      h2p_facRenScaleUp   = new TH2Poly(this->processName+"_facRenScaleUp", "", 0, 10000, 0, 1);
      h2p_facRenScaleDown = new TH2Poly(this->processName+"_facRenScaleDown", "", 0, 10000, 0, 1);

      h2p_JesUp           = new TH2Poly(this->processName+"_JesUp", "", 0, 10000, 0, 1);
      h2p_JesDown         = new TH2Poly(this->processName+"_JesDown", "", 0, 10000, 0, 1);
      
      for( int i = 0; i < n_PdfSys; i++ )
	{
	  TString PdfSysName = Form(this->processName+"_PdfEigenVect_%d",i);
	  h2p_Pdf[i] = new TH2Poly( PdfSysName, "", 0, 10000, 0, 1);
	}
      
      h2p_btagUp           = new TH2Poly(this->processName+"_btagUp", "", 0, 10000, 0, 1);
      h2p_btagDown         = new TH2Poly(this->processName+"_btagDown", "", 0, 10000, 0, 1);
      
      h2p_misstagUp        = new TH2Poly(this->processName+"_misstagUp", "", 0, 10000, 0, 1);
      h2p_misstagDown      = new TH2Poly(this->processName+"_misstagDown", "", 0, 10000, 0, 1);
      
      h2p_genMet           = new TH2Poly(this->processName+"_genMet", "", 0, 10000, 0, 1);
      h2p_pileupLowNPV     = new TH2Poly(this->processName+"_pileupLowNPV", "", 0, 10000, 0, 1);
      h2p_pileupHighNPV    = new TH2Poly(this->processName+"_pileupHighNPV", "", 0, 10000, 0, 1);
      h2p_pileupLowNPVErrSqr     = new TH2Poly(this->processName+"_pileupLowNPVErrSqr", "", 0, 10000, 0, 1);
      h2p_pileupHighNPVErrSqr    = new TH2Poly(this->processName+"_pileupHighNPVErrSqr", "", 0, 10000, 0, 1);

      for ( auto tmp : binningVect )
	{
	  if ( _debug ) std::cout << "adding bin: " << tmp[0] << "," <<  tmp[1] << "," << tmp[2] << "," << tmp[3] << std::endl;
	  h2p->AddBin(tmp[0], tmp[1], tmp[2], tmp[3]);
	  h2p_Err->AddBin(tmp[0], tmp[1], tmp[2], tmp[3]);
	  h2p_eff->AddBin(tmp[0], tmp[1], tmp[2], tmp[3]);
	  
	  h2p_ISRUp->AddBin(tmp[0], tmp[1], tmp[2], tmp[3]);
	  h2p_ISRDown->AddBin(tmp[0], tmp[1], tmp[2], tmp[3]);
	  
	  h2p_facScaleUp->AddBin(tmp[0], tmp[1], tmp[2], tmp[3]);
	  h2p_facScaleDown->AddBin(tmp[0], tmp[1], tmp[2], tmp[3]);
	  
	  h2p_renScaleUp->AddBin(tmp[0], tmp[1], tmp[2], tmp[3]);
	  h2p_renScaleDown->AddBin(tmp[0], tmp[1], tmp[2], tmp[3]);
	  
	  h2p_facRenScaleUp->AddBin(tmp[0], tmp[1], tmp[2], tmp[3]);
	  h2p_facRenScaleDown->AddBin(tmp[0], tmp[1], tmp[2], tmp[3]);
	  
	  h2p_JesUp->AddBin(tmp[0], tmp[1], tmp[2], tmp[3]);
	  h2p_JesDown->AddBin(tmp[0], tmp[1], tmp[2], tmp[3]);
	  
	  for ( int ipdf = 0; ipdf < n_PdfSys; ipdf++ ) h2p_Pdf[ipdf]->AddBin(tmp[0], tmp[1], tmp[2], tmp[3]);

	  h2p_btagUp->AddBin(tmp[0], tmp[1], tmp[2], tmp[3]);
	  h2p_btagDown->AddBin(tmp[0], tmp[1], tmp[2], tmp[3]);
	  
	  h2p_misstagUp->AddBin(tmp[0], tmp[1], tmp[2], tmp[3]);
	  h2p_misstagDown->AddBin(tmp[0], tmp[1], tmp[2], tmp[3]);

	  h2p_genMet->AddBin(tmp[0], tmp[1], tmp[2], tmp[3]);
	  h2p_pileupLowNPV->AddBin(tmp[0], tmp[1], tmp[2], tmp[3]);
	  h2p_pileupHighNPV->AddBin(tmp[0], tmp[1], tmp[2], tmp[3]);
	  h2p_pileupLowNPVErrSqr->AddBin(tmp[0], tmp[1], tmp[2], tmp[3]);
	  h2p_pileupHighNPVErrSqr->AddBin(tmp[0], tmp[1], tmp[2], tmp[3]);
	}

      return true;
    }

  return true;
};

void HggRazorSystematics::Loop()
{
  if ( _debug ) std::cout << "[DEBUG]: Entering Loop" << std::endl;
  if (fChain == 0)
    {
      std::cerr << "[ERROR]: TTree is NULL;" << std::endl;
      return;
    }
  if ( h2p == NULL )
    {
      std::cerr << "[ERROR]: TH2Poly has not been created; impossible to fill TH2Poly, please use: obj->InitMrRsqTH2Poly();" << std::endl;
      return;
    }

   if ( h2p_eff == NULL )
    {
      std::cerr << "[ERROR]: TH2Poly has not been created; impossible to fill TH2Poly, please check efficiecy TH2Poly;" << std::endl;
      return;
    }
  
  if ( (this->NEvents == NULL || this->SumScaleWeights == NULL || this->SumPdfWeights == NULL ) && this->processName != "signal" )
    {
      std::cerr << "[ERROR]: NEvents and/or SumScaleWeights and/or SumPdfWeights have not been set" << std::endl;
      return;
    }
  
  if ( this->processName == "signal")
    {
      if ( this->ISRHist == NULL ) {
	std::cerr << "[ERROR]: ISRHist has not been set for the signal process" << std::endl;
	return;
      }
      if ( this->ISRPtHist == NULL ) {
	std::cerr << "[ERROR]: ISRPtHist has not been set for the signal process" << std::endl;
	return;
      }
    }

  if ( _debug ) std::cout << "[DEBUG]: Setting N_events and N_facScale" << std::endl; 

  float N_events;
  //factorization/renormalization 
  const int n_facScaleSys = 6;
  float N_facScale[n_facScaleSys];
  //PDF
  float N_Pdf[n_PdfSys];

  N_events = this->NEvents->GetBinContent(1);
  for ( int i = 0; i < n_facScaleSys; i++ ) {
    N_facScale[i] = this->SumScaleWeights->GetBinContent( i+1 );
  }
  for ( int i = 0; i < n_PdfSys; i++ ) {
    N_Pdf[i] = this->SumPdfWeights->GetBinContent( i+1 );
  }
    
  if ( _debug ) std::cout << "[DEBUG]: Passed N_events, N_facScale, N_PDF" << std::endl;


  //****************************************************
  //Signal ISR Correction
  //****************************************************
  //double ISRCorrection[7] = { 1, 0.882, 0.792, 0.702, 0.648, 0.601, 0.515};//ICHEP
  double ISRCorrection[7] = { 1, 0.920, 0.821, 0.715, 0.662, 0.561, 0.511};//Moriond
  double PtISRCorrection[8] = { 1, 1.052, 1.179, 1.150, 1.057, 1.000, 0.912, 0.783};//Moriond

  if( this->processName == "signal" )
    {

      if (!_useISRPtCorrection) {
	if ( this->ISRHist ) {
	  if ( _debug ) std::cout << "[DEBUG]: beginning ISR setup 0" << std::endl;
	  double tmpTotal = 0;
	  for (int i = 1; i <= 7; i++) tmpTotal += this->ISRHist->GetBinContent(i);
	  double tmpCorrTotal = 0;
	  if ( _debug ) std::cout << "[DEBUG]: beginning ISR setup 1" << std::endl;
	  for (int i = 1; i <= 7; i++) tmpCorrTotal += ISRCorrection[i-1] * this->ISRHist->GetBinContent(i);
	  if ( _debug ) std::cout << "[DEBUG]: beginning ISR setup 2" << std::endl;
	  for (int i = 0; i < 7; i++) ISRCorrection[i] = ISRCorrection[i]*tmpTotal/tmpCorrTotal;
	  if ( _debug ) std::cout << "[DEBUG]: beginning ISR setup 3" << std::endl;
	  
	  std::cout << "[DEBUG] : total = " << tmpTotal << " , tmpCorrTotal = " << tmpCorrTotal 
		    << " , Original Bin 1 = " << this->ISRHist->GetBinContent(1) << " , "
		    << " ISRCorrection[0] = " << ISRCorrection[0] << "\n";
	  
	}
	else
	  {
	    std::cout << "[ERROR] : ISRHist has not been loaded.\n";
	  }
      }
      //Use ISR Pt Correction for EWK SUSY production
      else {
	if ( this->ISRPtHist ) {
	  if ( _debug ) std::cout << "[DEBUG]: beginning ISR setup 0" << std::endl;
	  double tmpTotal = 0;
	  for (int i = 1; i <= 8; i++) tmpTotal += this->ISRPtHist->GetBinContent(i);
	  double tmpCorrTotal = 0;
	  if ( _debug ) std::cout << "[DEBUG]: beginning ISR setup 1" << std::endl;
	  for (int i = 1; i <= 8; i++) tmpCorrTotal += PtISRCorrection[i-1] * this->ISRPtHist->GetBinContent(i);
	  if ( _debug ) std::cout << "[DEBUG]: beginning ISR setup 2" << std::endl;
	  for (int i = 0; i < 8; i++) PtISRCorrection[i] = PtISRCorrection[i]*tmpTotal/tmpCorrTotal;
	  if ( _debug ) std::cout << "[DEBUG]: beginning ISR setup 3" << std::endl;
	  
	  std::cout << "[DEBUG] : total = " << tmpTotal << " , tmpCorrTotal = " << tmpCorrTotal 
		    << " , Original Bin 1 = " << this->ISRPtHist->GetBinContent(1) << " , "
		    << " ISRCorrection[0] = " << PtISRCorrection[0] << "\n";
	  
	}
	else
	  {
	    std::cout << "[ERROR] : ISRPtHist has not been loaded.\n";
	  }
      }


    }
  

  if ( _debug ) std::cout << "[DEBUG]: Passed the ISR setup" << std::endl;
  Long64_t nentries = fChain->GetEntriesFast();
  Long64_t nbytes = 0, nb = 0;
  double total_in = 0, total_rm = 0;
  
  std::cout << "Nentries: " << fChain->GetEntries() << std::endl;
  for (Long64_t jentry=0; jentry < nentries; jentry++ )
    {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;

      //std::cout << "here"
      //require diphoton trigger
      TString DiphotonTrigger;
      if (_analysisTag == "Razor2016_80X")
	{
	  DiphotonTrigger = "(HLTDecision[82]||HLTDecision[83]||HLTDecision[93])";
	}
      else if (_analysisTag == "Razor2017_92X")
	{
	  DiphotonTrigger = "(HLTDecision[54]||HLTDecision[55])";
	}
      else
	{
	  DiphotonTrigger = "1";
	}

      if (!(_useISRPtCorrection && this->processName == "signal")) {
	if (!DiphotonTrigger) continue;//Ommit for FastSim
      }

      //require MET filters, Omit for FastSim
      if (!(_useISRPtCorrection && this->processName == "signal")) {
	if (!(Flag_HBHENoiseFilter == 1 && Flag_goodVertices == 1 && Flag_eeBadScFilter == 1 && Flag_HBHEIsoNoiseFilter == 1)) continue;
      }


      double ISRCorrValue = 1.0;
      if( this->processName == "signal" ) {
	if (!_useISRPtCorrection) {
	  ISRCorrValue = ISRCorrection[std::min(NISRJets,6)];
	} else {
	  ISRCorrValue = PtISRCorrection[ISRPtHist->GetXaxis()->FindFixBin(ptISR)-1];
	}
      }
      //ISRCorrValue = 1.0;

      float commonW = 0;
      if (_analysisTag == "Razor2015_76X")
	{
	  commonW = this->Lumi*weight*pileupWeight*btagCorrFactor*photonEffSF*ISRCorrValue;
	}
      else if (_analysisTag == "Razor2016_80X")
	{
	  if (_useISRPtCorrection && this->processName == "signal") {
	    commonW = this->Lumi*weight*btagCorrFactor*triggerEffSFWeight*photonEffSF*triggerEffWeight*ISRCorrValue;//FastSim
	    //commonW = this->Lumi*weight*btagCorrFactor*triggerEffSFWeight*photonEffSF*triggerEffWeight;//FastSim
	  } else {
	    commonW = this->Lumi*weight*pileupWeight*btagCorrFactor*triggerEffSFWeight*photonEffSF*ISRCorrValue;//FullSim
	    //commonW = this->Lumi*weight*pileupWeight*btagCorrFactor*triggerEffSFWeight*photonEffSF;//FullSim
	  }
	}
      else if (_analysisTag == "Razor2017_92X")
	{
	  if (_useISRPtCorrection && this->processName == "signal") {
	    commonW = this->Lumi*weight*btagCorrFactor*triggerEffSFWeight*photonEffSF*triggerEffWeight*ISRCorrValue;//FastSim
	    //commonW = this->Lumi*weight*btagCorrFactor*triggerEffSFWeight*photonEffSF*triggerEffWeight;//FastSim
	  } else {
	    commonW = this->Lumi*weight*pileupWeight*btagCorrFactor*triggerEffSFWeight*photonEffSF*ISRCorrValue;//FullSim
	    //commonW = this->Lumi*weight*pileupWeight*btagCorrFactor*triggerEffSFWeight*photonEffSF;//FullSim
	  }
	}
      else
	{
	  std::cout << "Analysis Tag " << _analysisTag << " not recognized. Error!\n";
	  return;
	}
      
      double myRsq = t1Rsq;

      h2p->Fill( MR, fmin(myRsq,0.999), commonW );	      
      h2p_Err->Fill( MR, fmin(myRsq,0.999), commonW*commonW );
      h2p_eff->Fill( MR, fmin(myRsq,0.999), weight/N_events );

      //btagging
      h2p_btagUp->Fill( MR, fmin(myRsq,0.999), commonW*sf_btagUp );
      h2p_btagDown->Fill( MR, fmin(myRsq,0.999), commonW*sf_btagDown );
	      
      h2p_misstagUp->Fill( MR, fmin(myRsq,0.999), commonW*sf_bmistagUp );
      h2p_misstagDown->Fill( MR, fmin(myRsq,0.999), commonW*sf_bmistagDown );
	            
      //JES Up/Down
      h2p_JesUp->Fill( MR_JESUp, fmin(t1Rsq_JESUp,0.999), commonW );
      h2p_JesDown->Fill( MR_JESDown, fmin(t1Rsq_JESDown,0.99), commonW );
    
      if( this->processName == "signal" ) {
	//************************************************************
	//Renormalize scale weights to the nominal cross section
	// Protect against samples without theory uncertainty info.
	// If they are missing just make them 0.
	//************************************************************
	h2p_ISRUp->Fill( MR, fmin(myRsq,0.999), commonW/ISRCorrValue );
	h2p_ISRDown->Fill( MR, fmin(myRsq,0.999), commonW/ISRCorrValue );

	if( fabs(N_facScale[0]) > 0) h2p_facScaleUp->Fill( MR, fmin(myRsq,0.999), commonW*sf_facScaleUp*N_events/N_facScale[0] );
	else h2p_facScaleUp->Fill( MR, fmin(myRsq,0.999), commonW );
	  
	if( fabs(N_facScale[1]) > 0) h2p_facScaleDown->Fill( MR, fmin(myRsq,0.999), commonW*sf_facScaleDown*N_events/N_facScale[1] );
	else h2p_facScaleDown->Fill( MR, fmin(myRsq,0.999), commonW );
	  
	if( fabs(N_facScale[2]) > 0) h2p_renScaleUp->Fill( MR, fmin(myRsq,0.999), commonW*sf_renScaleUp*N_events/N_facScale[2] );
	else h2p_renScaleUp->Fill( MR, fmin(myRsq,0.999), commonW );
	  
	if( fabs(N_facScale[3]) > 0 ) h2p_renScaleDown->Fill( MR, fmin(myRsq,0.999), commonW*sf_renScaleDown*N_events/N_facScale[3] );
	else h2p_renScaleDown->Fill( MR, fmin(myRsq,0.999), commonW );
	  
	if( fabs(N_facScale[4]) > 0 ) h2p_facRenScaleUp->Fill( MR, fmin(myRsq,0.999), commonW*sf_facRenScaleUp*N_events/N_facScale[4] );
	else h2p_facRenScaleUp->Fill( MR, fmin(myRsq,0.999), commonW );
	  
	if( fabs(N_facScale[5]) > 0 ) h2p_facRenScaleDown->Fill( MR, fmin(myRsq,0.999), commonW*sf_facRenScaleDown*N_events/N_facScale[5] );
	else h2p_facRenScaleDown->Fill( MR, fmin(myRsq,0.999), commonW );
	  

      }
      else {
	//************************************************************
	//Do not renormalize scale weights to the nominal cross section
	//************************************************************
	h2p_facScaleUp->Fill( MR, fmin(myRsq,0.999), commonW*sf_facScaleUp );
	h2p_facScaleDown->Fill( MR, fmin(myRsq,0.999), commonW*sf_facScaleDown );

	h2p_renScaleUp->Fill( MR, fmin(myRsq,0.999), commonW*sf_renScaleUp );
	h2p_renScaleDown->Fill( MR, fmin(myRsq,0.999), commonW*sf_renScaleDown );

	h2p_facRenScaleUp->Fill( MR, fmin(myRsq,0.999), commonW*sf_facRenScaleUp );
	h2p_facRenScaleDown->Fill( MR, fmin(myRsq,0.999), commonW*sf_facRenScaleDown );
      }
	

      for ( int ipdf = 0; ipdf < n_PdfSys; ipdf++ )
	{
	  //protect against missing pdf vector
	  if (ipdf < sf_pdf->size() && fabs(N_Pdf[ipdf]) > 0 ) {
	    h2p_Pdf[ipdf]->Fill( MR, fmin(myRsq,0.999), commonW*sf_pdf->at(ipdf)*N_events/N_Pdf[ipdf] );
	  } else {
	    h2p_Pdf[ipdf]->Fill( MR, fmin(myRsq,0.999), commonW );
	  }
	}
    
      //genmet
      if (_useISRPtCorrection && this->processName == "signal") {
	h2p_genMet->Fill( MR, fmin(genMetRsq,0.999), commonW );
      }

      //pileup for fastsim signals
      if (_useISRPtCorrection && this->processName == "signal") {
	if (nPV < 20) {
	  h2p_pileupLowNPV->Fill( MR, fmin(myRsq,0.999), commonW );
	  h2p_pileupLowNPVErrSqr->Fill( MR, fmin(myRsq,0.999), commonW*commonW );
	} else {
	  h2p_pileupHighNPV->Fill( MR, fmin(myRsq,0.999), commonW );
	  h2p_pileupHighNPVErrSqr->Fill( MR, fmin(myRsq,0.999), commonW*commonW );
	}
      }
      
    } //loop over events
    
 
  if ( _debug ) std::cout << "[DEBUG]: Finishing Loop" << std::endl;
};

void HggRazorSystematics::LoopNominal()
  {
    if ( _debug ) std::cout << "[DEBUG]: Entering Loop" << std::endl;
  if (fChain == 0)
    {
      std::cerr << "[ERROR]: TTree is NULL;" << std::endl;
      return;
    }
  if ( h2p == NULL )
    {
      std::cerr << "[ERROR]: TH2Poly has not been created; impossible to fill TH2Poly, please use: obj->InitMrRsqTH2Poly();" << std::endl;
      return;
    }
  
  Long64_t nentries = fChain->GetEntriesFast();
  Long64_t nbytes = 0, nb = 0;
  double total_in = 0, total_rm = 0;
  
  for (Long64_t jentry=0; jentry < nentries; jentry++ )
    {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      
      if ( t1Rsq < 1.0 )
	{
	  if( processName == "NR" )
	    {
	      h2p->Fill( MR, t1Rsq, this->NR_kf*this->Lumi*weight*pileupWeight );
	    }
	  else if( processName == "signal" )
	    {
	      h2p->Fill( MR, t1Rsq, this->Lumi*weight );
	    }
	  else
	    {
	      h2p->Fill( MR, t1Rsq, this->Lumi*weight*pileupWeight );
	    }
	}
      else
	{
	  if( processName == "NR" )
	    {
	      h2p->Fill( MR, 0.999, this->NR_kf*this->Lumi*weight*pileupWeight );
	    }
	  else if ( processName == "signal" )
	    {
	      h2p->Fill( MR, 0.999, this->Lumi*weight );
	    }
	  else
	    {
	      h2p->Fill( MR, 0.999, this->Lumi*weight*pileupWeight );
	    }
	}
    }

  if ( _debug ) std::cout << "[DEBUG]: Finishing Loop" << std::endl;
};

float HggRazorSystematics::GetHighPtGB( double mr, double r2 )
{
  int mr_bin = -1;
  int r2_bin = -1;
  return 0;
};

float HggRazorSystematics::GetHighResGB( double mr, double r2 )
{
  int mr_bin = -1;
  int r2_bin = -1;
  return 0;
};



float HggRazorSystematics::GetYields( float mr, float rsq, float mgg_l, float mgg_h )
{
  Long64_t nentries = fChain->GetEntriesFast();
  Long64_t nbytes = 0, nb = 0;
  float sel_events = .0;
  
  for (Long64_t jentry=0; jentry < nentries; jentry++ )
    {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
      if (  MR > mr && Rsq > rsq
	    && mGammaGamma > mgg_l && mGammaGamma < mgg_h
	    && fabs( pho1Eta ) < 1.48 && fabs( pho2Eta ) < 1.48 && pho1Pt > 25. && pho2Pt > 25.
	    && ( pho1Pt > 40. || pho2Pt > 40. ) && pTGammaGamma > 20. )
	{
	  sel_events += weight*this->Lumi;
	}
    }
  if ( _debug ) std::cout << "[DEBUG]: Finishing Loop" << std::endl;
  return sel_events;
};

float HggRazorSystematics::GetYields( float mr, float rsq, float mgg_l, float mgg_h, double& err )
{
  Long64_t nentries = fChain->GetEntriesFast();
  Long64_t nbytes = 0, nb = 0;
  float sel_events = .0;
  err = .0;
  for (Long64_t jentry=0; jentry < nentries; jentry++ )
    {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
      if (  MR > mr && Rsq > rsq
	    && mGammaGamma > mgg_l && mGammaGamma < mgg_h
	    && fabs( pho1Eta ) < 1.48 && fabs( pho2Eta ) < 1.48 && pho1Pt > 25. && pho2Pt > 25.
	    && ( pho1Pt > 40. || pho2Pt > 40. ) && pTGammaGamma > 20. )
	{
	  sel_events += weight*this->Lumi;
	  err += weight*this->Lumi*weight*this->Lumi;
	}
    }
  if ( _debug ) std::cout << "[DEBUG]: Finishing Loop" << std::endl;
  err = sqrt(err);
  return sel_events;
};

bool HggRazorSystematics::WriteOutput( TString outName )
{
  if ( _debug ) std::cout << "[DEBUG]: Entering WriteOutput" << std::endl;
  this->fout = new TFile( outName + "_" + this->processName + ".root", "recreate");
  if ( h2p != NULL ) h2p->Write( this->boxName + "_histo" );
  if ( h2p_eff != NULL ) h2p_eff->Write( this->boxName + "_histo_eff" );
  if ( h2p_ISRUp != NULL ) h2p_ISRUp->Write( this->boxName + "_histo_ISRUp" );
  if ( h2p_ISRDown != NULL ) h2p_ISRDown->Write( this->boxName + "_histo_ISRDown" );
  if ( h2p_facScaleUp != NULL ) h2p_facScaleUp->Write( this->boxName + "_histo_facScaleUp" );
  if ( h2p_facScaleDown != NULL ) h2p_facScaleDown->Write( this->boxName + "_histo_facScaleDown" );
  if ( h2p_renScaleUp != NULL ) h2p_renScaleUp->Write( this->boxName + "_histo_renScaleUp" );
  if ( h2p_renScaleDown != NULL ) h2p_renScaleDown->Write( this->boxName + "_histo_renScaleDown" );
  if ( h2p_facRenScaleUp != NULL ) h2p_facRenScaleUp->Write( this->boxName + "_histo_facRenScaleUp" );
  if ( h2p_facRenScaleDown != NULL ) h2p_facRenScaleDown->Write( this->boxName + "_histo_facRenScaleDown" );
  if ( h2p_JesUp != NULL ) h2p_JesUp->Write( this->boxName + "_histo_JesUp" );
  if ( h2p_JesDown != NULL ) h2p_JesDown->Write( this->boxName + "_histo_JesDown" );
  for ( int ipdf = 0; ipdf < n_PdfSys; ipdf++ )
    {
      TString PdfTH2PName = Form("histo_PdfEigenVector%d", ipdf );
      if ( h2p_Pdf[ipdf] != NULL ) h2p_Pdf[ipdf]->Write( this->boxName + "_"  + PdfTH2PName );
    }
  if ( h2p_JesUp != NULL ) h2p_btagUp->Write( this->boxName + "_histo_btagUp" );
  if ( h2p_JesDown != NULL ) h2p_btagDown->Write( this->boxName + "_histo_btagDown" );
  if ( h2p_JesUp != NULL ) h2p_misstagUp->Write( this->boxName + "_histo_misstagUp" );
  if ( h2p_JesDown != NULL ) h2p_misstagDown->Write( this->boxName + "_histo_misstagDown" );
  if ( h2p_genMet != NULL ) h2p_genMet->Write( this->boxName + "_histo_genMet" );
  if ( h2p_pileupLowNPV != NULL ) h2p_pileupLowNPV->Write( this->boxName + "_histo_pileupLowNPV" );
  if ( h2p_pileupHighNPV != NULL ) h2p_pileupHighNPV->Write( this->boxName + "_histo_pileupHighNPV" );

  fout->Close();
  if ( _debug ) std::cout << "[DEBUG]: Finishing WriteOutput" << std::endl;
  return true;
};

float HggRazorSystematics::GetHggBF( )
{
  return hggBF;
};

bool HggRazorSystematics::SetNeventsHisto( TH1F* histo )
{
  this->NEvents = NULL;
  if ( histo == NULL )
    {
      std::cerr << "[ERROR]: Nevents histogram provided is equal to NULL" << std::endl;
      return false;
    }
  this->NEvents = new TH1F( *histo );
  return true;
};

bool HggRazorSystematics::SetISRHisto( TH1F* histo )
{
  this->ISRHist = NULL;
  if ( histo == NULL )
    {
      if (this->processName == "signal" ) std::cerr << "[ERROR]: ISR histogram provided is equal to NULL" << std::endl;
      return false;
    }
  this->ISRHist = new TH1F( *histo );

  return true;
};

bool HggRazorSystematics::SetISRPtHisto( TH1F* histo )
{
  this->ISRPtHist = NULL;
  if ( histo == NULL )
    {
      if (this->processName == "signal" ) std::cerr << "[ERROR]: ISR histogram provided is equal to NULL" << std::endl;
      return false;
    }
  this->ISRPtHist = new TH1F( *histo );

  return true;
};

bool HggRazorSystematics::SetNPVHisto( TH1F* histo )
{
  this->NPVHist = NULL;
  if ( histo == NULL )
    {
      if (this->processName == "signal" ) std::cerr << "[ERROR]: NPV histogram provided is equal to NULL" << std::endl;
      return false;
    }
  this->NPVHist = new TH1F( *histo );

  return true;
};

bool HggRazorSystematics::SetFacScaleWeightsHisto( TH1F* histo )
{
  this->SumScaleWeights = NULL;
  if ( histo == NULL )
    {
      std::cerr << "[ERROR]: Scale histogram provided is equal to NULL" << std::endl;
      return false;
    }
  this->SumScaleWeights = new TH1F( *histo );

  return true;
};

bool HggRazorSystematics::SetPdfWeightsHisto( TH1F* histo )
{
  this->SumPdfWeights = NULL;
  if ( histo == NULL )
    {
      std::cerr << "[ERROR]: PDF histogram provided is equal to NULL" << std::endl;
      return false;
    }
  this->SumPdfWeights = new TH1F( *histo );
  return true;
};

/*
float HggRazorSystematics::GetNominalYield( float mr, float rsq )
{
  int bin = h2p->FindBin( mr+10, rsq+0.0001 );

  double nominal = h2p->GetBinContent( bin );
  
  //For Fastsim samples in Spring16, we do not have the proper pileup distribution to do reweighting
  //Therefore we need to do some extrapolation 
  if ((_useISRPtCorrection && this->processName == "signal")) {
    double lowNVtx = h2p_pileupLowNPV->GetBinContent( bin );
    double highNVtx = h2p_pileupHighNPV->GetBinContent( bin );
    double lowNVtxErr = sqrt( h2p_pileupLowNPVErrSqr->GetBinContent( bin ));
    double highNVtxErr = sqrt(h2p_pileupHighNPVErrSqr->GetBinContent( bin ));
    double lowNVtxFactor = NPVHist->GetBinContent(1) / (NPVHist->GetBinContent(1) + NPVHist->GetBinContent(2));
    double highNVtxFactor = NPVHist->GetBinContent(2) / (NPVHist->GetBinContent(1) + NPVHist->GetBinContent(2));
     
    double x[2] = {14.68, 24.26};
    double ex[2] = {0, 0};
    double y[2];
    y[0] = lowNVtx/lowNVtxFactor;
    y[1] = highNVtx/highNVtxFactor;
    double ey[2];
    ey[0] = lowNVtxErr/lowNVtxFactor;
    ey[1] = highNVtxErr/highNVtxFactor;
   
    TGraphErrors *graph = new TGraphErrors(2,x,y,ex,ey);
    TFitResultPtr fitresult = graph->Fit("pol1","SMF");

    double averageYield = 0;
    double averageYieldErr = 0;
    std::cout << "bins: " << NPVTarget->GetXaxis()->GetNbins() << "\n";
    for (int i=1; i< NPVTarget->GetXaxis()->GetNbins(); i++) {
      double npv = NPVTarget->GetXaxis()->GetBinCenter(i);
      double tmpweight = NPVTarget->GetBinContent(i);

      double p0 = fitresult->Parameter(0);
      double p1 = fitresult->Parameter(1);    
      double Yield = p0 + npv * p1;
      double YieldErr = sqrt( npv*npv* fitresult->GetCovarianceMatrix()(1,1) + fitresult->GetCovarianceMatrix()(0,0) + 2*npv*fitresult->GetCovarianceMatrix()(0,1) );
      //std::cout << "npv = " << npv << " : " << tmpweight << " : " << Yield << " +/- " << YieldErr << "\n";
      averageYield += tmpweight * Yield;
      averageYieldErr += tmpweight * YieldErr;
      //std::cout << "added  : " << tmpweight*Yield  << " +/- " << tmpweight*YieldErr << "\n";
      //std::cout << "value  : " << averageYield  << " +/- " << averageYieldErr << "\n";
    }
    //nominal  = averageYield;
    //std::cout << "Average yield: " << averageYield << " +/- " << averageYieldErr << "\n";

     TCanvas cv("cv","cv", 800,800);
     graph->Draw();
     cv.SaveAs(Form("plot%d.gif",bin));
    
    delete graph;

  }
  
  return nominal;
};
*/

float HggRazorSystematics::GetNominalYield( float mr, float rsq )
{
         int bin = h2p->FindBin( mr+10, rsq+0.0001 );
          double nominal = h2p->GetBinContent( bin );
          std::cout << "nominal: " << nominal << std::endl;
          return nominal;
};
float HggRazorSystematics::GetNominalError( float mr, float rsq )
{
  int bin = h2p_Err->FindBin( mr+10, rsq+0.0001 );
  double nominal = h2p_Err->GetBinContent( bin );

  //For Fastsim samples in Spring16, we do not have the proper pileup distribution to do reweighting
  //Therefore we need to do some extrapolation 
  if ((_useISRPtCorrection && this->processName == "signal")) {
    double lowNVtx = h2p_pileupLowNPV->GetBinContent( bin );
    double highNVtx = h2p_pileupHighNPV->GetBinContent( bin );
    double lowNVtxErr = sqrt( h2p_pileupLowNPVErrSqr->GetBinContent( bin ));
    double highNVtxErr = sqrt(h2p_pileupHighNPVErrSqr->GetBinContent( bin ));
    double lowNVtxFactor = NPVHist->GetBinContent(1) / (NPVHist->GetBinContent(1) + NPVHist->GetBinContent(2));
    double highNVtxFactor = NPVHist->GetBinContent(2) / (NPVHist->GetBinContent(1) + NPVHist->GetBinContent(2));
     
    double x[2] = {14.68, 24.26};
    double ex[2] = {0, 0};
    double y[2];
    y[0] = lowNVtx/lowNVtxFactor;
    y[1] = highNVtx/highNVtxFactor;
    double ey[2];
    ey[0] = lowNVtxErr/lowNVtxFactor;
    ey[1] = highNVtxErr/highNVtxFactor;
   
    TGraphErrors *graph = new TGraphErrors(2,x,y,ex,ey);
    TFitResultPtr fitresult = graph->Fit("pol1","SMF");

    double averageYield = 0;
    double averageYieldErr = 0;
    std::cout << "bins: " << NPVTarget->GetXaxis()->GetNbins() << "\n";
    for (int i=1; i< NPVTarget->GetXaxis()->GetNbins(); i++) {
      double npv = NPVTarget->GetXaxis()->GetBinCenter(i);
      double tmpweight = NPVTarget->GetBinContent(i);

      double p0 = fitresult->Parameter(0);
      double p1 = fitresult->Parameter(1);    
      double Yield = p0 + npv * p1;
      double YieldErr = sqrt( npv*npv* fitresult->GetCovarianceMatrix()(1,1) + fitresult->GetCovarianceMatrix()(0,0) + 2*npv*fitresult->GetCovarianceMatrix()(0,1) );
      //std::cout << "npv = " << npv << " : " << tmpweight << " : " << Yield << " +/- " << YieldErr << "\n";
      averageYield += tmpweight * Yield;
      averageYieldErr += tmpweight * YieldErr;
    }
    nominal  = averageYieldErr;
    std::cout << "Average yield: " << averageYield << " +/- " << averageYieldErr << "\n";

    // TCanvas cv("cv","cv", 800,800);
    // graph->Draw();
    // cv.SaveAs(Form("plot%d.gif",bin));
    
    delete graph;

  }

  return nominal;

};

float HggRazorSystematics::GetGenMetSystematic( float mr, float rsq )
{
  int bin = h2p_genMet->FindBin( mr+10, rsq+0.0001 );
  float nominal     = h2p->GetBinContent( bin );
  float genmetYield = h2p_genMet->GetBinContent( bin );
  float result = nominal - genmetYield;   

  return result;
};

float HggRazorSystematics::GetEff( float mr, float rsq )
{
  int bin = h2p_eff->FindBin( mr+10, rsq+0.0001 );
  return h2p_eff->GetBinContent( bin );
};

std::pair<float, float> HggRazorSystematics::GetFacScaleSystematic( float mr, float rsq )
{
  int bin = h2p->FindBin( mr+10, rsq+0.0001 );
  float smhY      = h2p->GetBinContent( bin );
  float smhY_Up   = h2p_facScaleUp->GetBinContent( bin )-smhY;
  float smhY_Down = h2p_facScaleDown->GetBinContent( bin )-smhY;
  //std::cout << "mr: " << mr << " rsq: " << rsq << "; up: " << smhY_Up << ", down: " << smhY_Down << std::endl;
  return std::make_pair( smhY_Up, smhY_Down );
};

std::pair<float, float> HggRazorSystematics::GetISRSystematic( float mr, float rsq )
{
  int bin = h2p->FindBin( mr+10, rsq+0.0001 );
  float smhY      = h2p->GetBinContent( bin );
  float uncorrY   = h2p_ISRUp->GetBinContent( bin );
  float smhY_Up   = smhY + (uncorrY - smhY) * 0.5;
  float smhY_Down = smhY - (uncorrY - smhY) * 0.5;

  float errUp = smhY_Up - smhY;
  float errDown = smhY_Down - smhY;

  return std::make_pair( errUp , errDown );
};

std::pair<float, float> HggRazorSystematics::GetRenScaleSystematic( float mr, float rsq )
{
  int bin = h2p->FindBin( mr+10, rsq+0.0001 );
  float smhY      = h2p->GetBinContent( bin );
  float smhY_Up   = h2p_renScaleUp->GetBinContent( bin ) - smhY;
  float smhY_Down = h2p_renScaleDown->GetBinContent( bin ) - smhY;
  return std::make_pair( smhY_Up, smhY_Down );
};

std::pair<float, float> HggRazorSystematics::GetFacRenScaleSystematic( float mr, float rsq )
{
  int bin = h2p->FindBin( mr+10, rsq+0.0001 );
  float smhY      = h2p->GetBinContent( bin );
  float smhY_Up   = h2p_facRenScaleUp->GetBinContent( bin ) - smhY;
  float smhY_Down = h2p_facRenScaleDown->GetBinContent( bin ) - smhY;
  return std::make_pair( smhY_Up, smhY_Down );
};

std::pair<float, float> HggRazorSystematics::GetJesSystematic( float mr, float rsq )
{
  int bin = h2p->FindBin( mr+10, rsq+0.0001 );
  float smhY      = h2p->GetBinContent( bin );
  float smhY_Up   = h2p_JesUp->GetBinContent( bin ) - smhY;
  float smhY_Down = h2p_JesDown->GetBinContent( bin ) - smhY;
  return std::make_pair( smhY_Up, smhY_Down );
};

std::pair<float, float> HggRazorSystematics::GetBtagSystematic( float mr, float rsq )
{
  int bin = h2p->FindBin( mr+10, rsq+0.0001 );
  float smhY      = h2p->GetBinContent( bin );
  float smhY_Up   = h2p_btagUp->GetBinContent( bin ) - smhY;
  float smhY_Down = h2p_btagDown->GetBinContent( bin ) - smhY;
  return std::make_pair( smhY_Up, smhY_Down );
};

std::pair<float, float> HggRazorSystematics::GetMisstagSystematic( float mr, float rsq )
{
  int bin = h2p->FindBin( mr+10, rsq+0.0001 );
  float smhY      = h2p->GetBinContent( bin );
  float smhY_Up   = h2p_misstagUp->GetBinContent( bin ) - smhY;
  float smhY_Down = h2p_misstagDown->GetBinContent( bin ) - smhY;
  return std::make_pair( smhY_Up, smhY_Down );
};

float HggRazorSystematics::GetPdfSystematic( int i, float mr, float rsq )
{
  int bin = h2p->FindBin( mr+10, rsq+0.0001 );
  float smhY      = h2p->GetBinContent( bin );
  float smhY_Un   = h2p_Pdf[i]->GetBinContent( bin ) - smhY;
  return smhY_Un;
};
