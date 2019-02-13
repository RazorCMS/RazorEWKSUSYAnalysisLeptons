#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <assert.h>
//ROOT INCLUDES
#include <TFile.h>
#include <TROOT.h>
#include <TCanvas.h>
#include <TColor.h>
#include <TF1.h>
#include <TIterator.h>
#include <TMath.h>
#include <RooArgSet.h>
#include <RooAbsArg.h>
#include <RooAbsCollection.h>
#include <RooAbsReal.h>
#include <RooAbsPdf.h>
#include <RooRealVar.h>
#include <RooFitResult.h>
#include <RooWorkspace.h>
#include <RooRandom.h>
#include <RooPlot.h>
//LOCAL INCLUDES
#include "HggRazorSystematics.hh"
#include "CommandLineInput.hh"
#include "DefinePdfs.hh"

const bool _debug = true;

float GetSignal( std::string fname, int bin, std::string cat = "inclusiveElectron" );
float GetSignalErr( std::string fname, int bin, std::string cat = "inclusiveElectron" );
float GetSMH( std::string fname, int bin, std::string cat = "inclusiveElectron" );
float GetSMH_PF( std::string fname, int bin, std::string cat = "inclusiveElectron" ); //postfit
float GetSMHErr( std::string fname, int bin, std::string cat = "inclusiveElectron" );
float GetSMHErr_PF( std::string fname, int bin, std::string cat = "inclusiveElectron" ); //postfit
float GetNbkg( std::string fname, std::string f1, int bin, bool _err = false, std::string cat = "inclusiveElectron" );
float GetErrorFromToys(RooWorkspace *ws, RooFitResult *fr, TString pdfName, 
        unsigned int ntoys = 1000, int binNum = 0, bool plotBkgFuncs = false);
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

float HighRes_SF = 1.0/1.1834218302;
float LowRes_SF  = 1./0.8841933224;

int main( int argc, char* argv[] )
{

  gROOT->Reset();
  gErrorIgnoreLevel = kWarning;

  std::map<Bin, std::string> myMap;
  std::map<std::string, Bin> myMap2;
  
  std::vector<Bin> binVector;
  //std::ifstream input( "data/HggRazor2016n2017_Binning.txt", std::fstream::in );
  std::ifstream input( "data/HggRazor2016n2017_Binning_bin33.txt", std::fstream::in );
  
  if ( input.is_open() )
    {
      float x1, x2, y1, y2;
      int binN;
      float binn;
      std::string box, f1;
      while ( input.good() )
	{
	  input >> binN >> x1 >> x2 >> y1 >> y2 >> box >> f1;
	  if ( input.eof() ) break;
	  Bin mybin;
	  mybin.bin = binN;
	  mybin.f1 = f1;
	  mybin.box = box;
	  mybin.x1 = x1;
	  mybin.x2 = x2;
	  mybin.y1 = y1;
	  mybin.y2 = y2;
	  std::stringstream ss;
	  binn=(float)binN;
	  //ss << binn << "_" << x1 << "-" << x2 << "_" << y1 << "-" << y2;
	  ss << box << "_" << x1 << "-" << x2 << "_" << y1 << "-" << y2;
	  binVector.push_back(mybin);
	  if ( myMap.find( mybin ) == myMap.end() ) myMap[mybin] = f1;
	  if ( myMap2.find( ss.str() ) == myMap2.end() ) myMap2[ss.str()] = mybin;
	}
    }
  else
    {
      std::cout << "Unable to open binning lookup table" << std::endl;
    }

  for ( auto tmp : myMap2 )
    {
      std::cout << tmp.first << " " << tmp.second.f1 << std::endl;
    }

  //------------------------
  //categoryMode
  //------------------------
  std::string categoryMode = "highpt";
/*
 * std::string categoryMode = ParseCommandLine( argc, argv, "-category=" );
  if (  categoryMode == "" )
    {
	categoryMode="highpt";
      std::cerr << "[ERROR]: please provide the category. Use --category=<highpt,hbb,zbb,highres,lowres,muhighpt,mulowpt,elehighpt,elelowpt,twoleptons>" << std::endl;
      return 0;
    }  
*/
  //------------------------
  //fit result directory
  //------------------------
  std::string fitResultDir = ParseCommandLine( argc, argv, "-fitResultDir=" );
  if (  fitResultDir == "" )
    {
      std::cerr << "[ERROR]: please provide a fit result directory. For example, use --fitResultDir=/afs/cern.ch/work/c/cpena/public/CMSSW_7_6_3/src/RazorEWKSUSYAnalysis/HggRazor/PlottingAndSystematic" << std::endl;
      return -1;
    }
  std::cout << "[INFO] : Using fitResultDir = " << fitResultDir << "\n";
/*
	std::cout << "\\begin{table*}[htb]\n\\begin{center}\n\\caption{.\\label{tab:SMHBkgPrediction}}\n\\def\\arraystretch{1.5}";
	std::cout << "\n\\begin{tabular}{|c|c|c|c|c|c|c|}\n\\hline\n& & & \\multicolumn{2}{c|}{Bkg} & & \\\\";
	std::cout << "\n\\hline\n\\small";
	std::cout << "\nBin & Category & Signal & SMH & Nbkg & S/B (\\%) & S/Sqrt(B) (\\%) \\\\\n\\hline\n";
  for ( auto tmp: binVector )
    {
      //----------------------------
      //Key string to find bin
      //----------------------------
      //std::cout<< tmp.bin << "\n"<<std::endl;
      std::stringstream ss_fn;
      ss_fn << fitResultDir << "/HggRazorWorkspace_bin" << tmp.bin << ".root";
      //std::cout<< tmp.bin << "\n"<<std::endl;
      //std::cout<< tmp.box << "\n"<<std::endl;
      //std::cout<< ss_fn.str() << "\n"<<std::endl;
      std::stringstream ss_fnfit;
      ss_fnfit << fitResultDir << "/mlfit_bin" << tmp.bin << ".root";

      float Ns = GetSignal( ss_fn.str(), tmp.bin, categoryMode );
      float NsErr = GetSignalErr( ss_fn.str(), tmp.bin, categoryMode );
      float Nsmh = GetSMH( ss_fn.str(), tmp.bin, categoryMode );
      float NsmhErr = GetSMHErr( ss_fn.str(), tmp.bin, categoryMode );
      float Nbkg = GetNbkg( ss_fnfit.str(),tmp.f1 ,tmp.bin, false,categoryMode );
      float NB = Nsmh+Nbkg;
      float s1 = Ns/NB;
      float s2 = Ns/sqrt(NB);

	TString line = Form("%d & %s & %.2f $\\pm$ %.2f & %.2f $\\pm$ %.1f & %.2f & %.2f  & %.2f   \\\\", tmp.bin, tmp.box.c_str(), Ns, NsErr, Nsmh, NsmhErr, Nbkg, s1*100, s2*100);
	std::cout << line << std::endl;
    }
  std::cout << "\\hline\n\\end{tabular}\n\\end{center}\n\\end{table*}" << std::endl;


  std::cout << "\\begin{table*}[h]\n\\begin{center}\n\\topcaption{.}\n\\small\n\\begin{tabular}{|cc|cccc|c|}\n\\hline";
  
  std::cout <<"\n           &          &                   & Yields        &                 &                        & Obs. Local \\\\";
  std::cout << "\nBin        & Category &  Non-Resonant Bkg & Exp. SM Higgs & Fitted SM Higgs &  Best Fit Signal       & Significance   \\\\\n\\hline\n";
  for ( auto tmp: binVector )
    {
      //----------------------------
      //Key string to find bin
      //----------------------------
      //std::cout<< tmp.bin << "\n"<<std::endl;
      std::stringstream ss_fn;
      ss_fn << fitResultDir << "/HggRazorWorkspace_bin" << tmp.bin << ".root";
      //std::cout<< tmp.bin << "\n"<<std::endl;
      //std::cout<< tmp.box << "\n"<<std::endl;
      //std::cout<< ss_fn.str() << "\n"<<std::endl;
      std::stringstream ss_fnfit;
      ss_fnfit << fitResultDir << "/mlfit_bin" << tmp.bin << ".root";

      float Ns = GetSignal( ss_fn.str(), tmp.bin, categoryMode );
      float NsErr = GetSignalErr( ss_fn.str(), tmp.bin, categoryMode );
      float Nsmh = GetSMH( ss_fn.str(), tmp.bin, categoryMode );
      float NsmhErr = GetSMHErr( ss_fn.str(), tmp.bin, categoryMode );
      float Nbkg = GetNbkg( ss_fnfit.str(),tmp.f1 ,tmp.bin, false,categoryMode );
      float Nsmh_pf = GetSMH_PF( ss_fnfit.str(),  tmp.bin, categoryMode );
      float NsmhErr_pf = GetSMHErr_PF( ss_fnfit.str(), tmp.bin, categoryMode );

      std::stringstream ss_sigma;
      ss_sigma << fitResultDir << "/PL_nsigma_npvalue_bin" << tmp.bin << ".root";
      //std::cout<< ss_sigma.str() << "\n"<<std::endl;

      TFile* fsigma = new TFile( ss_sigma.str().c_str(), "READ");
      TTree* limit = (TTree*)fsigma->Get("limit");
      double _limit;
      limit->SetBranchAddress( "limit", &_limit );
      limit->GetEntry(0);
      delete fsigma;

	TString line = Form("%d & %s & %.1f & %.1f$\\pm$%.1f & %.1f$\\pm$%.1f & %.1f$\\pm$%.1f & %.1f\\\\",
			  tmp.bin, tmp.box.c_str(), Nbkg, Nsmh, NsmhErr, Nsmh_pf, NsmhErr_pf, Ns, NsErr, _limit);

	std::cout << line << std::endl;
    }
  std::cout << "\\hline\n\\end{tabular}\n\\end{center}\n\\end{table*}" << std::endl;

  std::cout << "\\begin{table*}[h]\n\\begin{center}\n\\topcaption{.}\n\\small\n\\begin{tabular}{|cc|ccc|cc|c|}\n\\hline";
  
  std::cout <<"\n           &          &                   & Yields   &        & limit &   & Obs. Local \\\\";
  std::cout << "\nBin        & Category &  Non-Resonant Bkg & SM Higgs & Signal & exp & obs & Significance   \\\\\n\\hline\n";
  for ( auto tmp: binVector )
    {
      //----------------------------
      //Key string to find bin
      //----------------------------
      //std::cout<< tmp.bin << "\n"<<std::endl;
      std::stringstream ss_fn;
      ss_fn << fitResultDir << "/HggRazorWorkspace_bin" << tmp.bin << ".root";
      //std::cout<< tmp.bin << "\n"<<std::endl;
      //std::cout<< tmp.box << "\n"<<std::endl;
      //std::cout<< ss_fn.str() << "\n"<<std::endl;
      std::stringstream ss_fnfit;
      ss_fnfit << fitResultDir << "/mlfit_bin" << tmp.bin << ".root";

      float Ns = GetSignal( ss_fn.str(), tmp.bin, categoryMode );
      float NsErr = GetSignalErr( ss_fn.str(), tmp.bin, categoryMode );
      float Nsmh = GetSMH( ss_fn.str(), tmp.bin, categoryMode );
      float NsmhErr = GetSMHErr( ss_fn.str(), tmp.bin, categoryMode );
      float Nbkg = GetNbkg( ss_fnfit.str(),tmp.f1 ,tmp.bin, false,categoryMode );
      float Nsmh_pf = GetSMH_PF( ss_fnfit.str(),  tmp.bin, categoryMode );
      float NsmhErr_pf = GetSMHErr_PF( ss_fnfit.str(), tmp.bin, categoryMode );

      std::stringstream ss_fnlimit;
      ss_fnlimit << fitResultDir << "/higgsCombine_combinebin" << tmp.bin << ".Asymptotic.mH120.root";

      TFile* flimit = new TFile( ss_fnlimit.str().c_str(), "READ");
      TTree* fnlimit = (TTree*)flimit->Get("limit");
      //double _combinelimit;
      //fnlimit->SetBranchAddress( "limit", &_combinelimit );
      double _exp;
      fnlimit->SetBranchAddress( "limit", &_exp );
      fnlimit->GetEntry(2);
      //double _exp = fnlimit->GetEntry(2);
      double _obs;
      fnlimit->SetBranchAddress( "limit", &_obs );
      fnlimit->GetEntry(5);
      //double _obs = fnlimit->GetEntry(5);
      delete flimit;

      std::stringstream ss_sigma;
      ss_sigma << fitResultDir << "/PL_nsigma_npvalue_bin" << tmp.bin << ".root";
      //std::cout<< ss_sigma.str() << "\n"<<std::endl;

      TFile* fsigma = new TFile( ss_sigma.str().c_str(), "READ");
      TTree* limit = (TTree*)fsigma->Get("limit");
      double _limit;
      limit->SetBranchAddress( "limit", &_limit );
      limit->GetEntry(0);
      delete fsigma;

	TString line = Form("%d & %s & %.1f & %.1f & %.1f & %.1f & %.1f & %.1f\\\\",
			  tmp.bin, tmp.box.c_str(), Nbkg, Nsmh, Ns, _exp, _obs, _limit);
			  //tmp.bin, tmp.box.c_str(), Nbkg, Nsmh, Ns, _combinelimit, _obs, _limit);

	std::cout << line << std::endl;
    }
  std::cout << "\\hline\n\\end{tabular}\n\\end{center}\n\\end{table*}" << std::endl;

  std::cout << "\\begin{table*}[h]\n\\begin{center}\n\\topcaption{.}\n\\small\n\\begin{tabular}{|cc|ccc|cc|}\n\\hline";
  
  std::cout <<"\n           &          &                   & Yields   &        & limit &    \\\\";
  std::cout << "\nBin        & Category &  Non-Resonant Bkg & SM Higgs & Signal & exp & obs \\\\\n\\hline\n";
  for ( auto tmp: binVector )
    {
      //----------------------------
      //Key string to find bin
      //----------------------------
      //std::cout<< tmp.bin << "\n"<<std::endl;
      std::stringstream ss_fn;
      ss_fn << fitResultDir << "/HggRazorWorkspace_bin" << tmp.bin << ".root";
      //std::cout<< tmp.bin << "\n"<<std::endl;
      //std::cout<< tmp.box << "\n"<<std::endl;
      //std::cout<< ss_fn.str() << "\n"<<std::endl;
      std::stringstream ss_fnfit;
      ss_fnfit << fitResultDir << "/mlfit_bin" << tmp.bin << ".root";

      float Ns = GetSignal( ss_fn.str(), tmp.bin, categoryMode );
      float NsErr = GetSignalErr( ss_fn.str(), tmp.bin, categoryMode );
      float Nsmh = GetSMH( ss_fn.str(), tmp.bin, categoryMode );
      float NsmhErr = GetSMHErr( ss_fn.str(), tmp.bin, categoryMode );
      float Nbkg = GetNbkg( ss_fnfit.str(),tmp.f1 ,tmp.bin, false,categoryMode );
      float Nsmh_pf = GetSMH_PF( ss_fnfit.str(),  tmp.bin, categoryMode );
      float NsmhErr_pf = GetSMHErr_PF( ss_fnfit.str(), tmp.bin, categoryMode );

      std::stringstream ss_fnlimit;
      ss_fnlimit << fitResultDir << "/higgsCombine_combinebin" << tmp.bin << ".Asymptotic.mH120.root";

      TFile* flimit = new TFile( ss_fnlimit.str().c_str(), "READ");
      TTree* fnlimit = (TTree*)flimit->Get("limit");
      double _exp;
      fnlimit->SetBranchAddress( "limit", &_exp );
      fnlimit->GetEntry(2);
      delete flimit;

      TFile* flimit2 = new TFile( ss_fnlimit.str().c_str(), "READ");
      TTree* fnlimit2 = (TTree*)flimit2->Get("limit");
      double _obs;
      fnlimit2->SetBranchAddress( "limit", &_obs );
      fnlimit2->GetEntry(5);
      delete flimit2;

	TString line = Form("%d & %s & %.2f & %.2f & %.2f & %.2f & %.2f \\\\",
			  tmp.bin, tmp.box.c_str(), Nbkg, Nsmh, Ns, _exp, _obs);
			  

	std::cout << line << std::endl;
    }
  std::cout << "\\hline\n\\end{tabular}\n\\end{center}\n\\end{table*}" << std::endl;
  std::cout << "\\begin{table*}[h]\n\\begin{center}\n\\topcaption{.}\n\\small\n\\begin{tabular}{|cc|ccc|cc|}\n\\hline";
  
  std::cout <<"\n           &          &                   & Yields   &        & limit & Obs. Local \\\\";
  std::cout << "\nBin        & Category &  Non-Resonant Bkg & SM Higgs & Signal & exp & Significance   \\\\\n\\hline\n";
  for ( auto tmp: binVector )
    {
      //----------------------------
      //Key string to find bin
      //----------------------------
      //std::cout<< tmp.bin << "\n"<<std::endl;
      std::stringstream ss_fn;
      ss_fn << fitResultDir << "/HggRazorWorkspace_bin" << tmp.bin << ".root";
      //std::cout<< tmp.bin << "\n"<<std::endl;
      //std::cout<< tmp.box << "\n"<<std::endl;
      //std::cout<< ss_fn.str() << "\n"<<std::endl;
      std::stringstream ss_fnfit;
      ss_fnfit << fitResultDir << "/mlfit_bin" << tmp.bin << ".root";

      float Ns = GetSignal( ss_fn.str(), tmp.bin, categoryMode );
      float NsErr = GetSignalErr( ss_fn.str(), tmp.bin, categoryMode );
      float Nsmh = GetSMH( ss_fn.str(), tmp.bin, categoryMode );
      float NsmhErr = GetSMHErr( ss_fn.str(), tmp.bin, categoryMode );
      float Nbkg = GetNbkg( ss_fnfit.str(),tmp.f1 ,tmp.bin, false,categoryMode );
      float Nsmh_pf = GetSMH_PF( ss_fnfit.str(),  tmp.bin, categoryMode );
      float NsmhErr_pf = GetSMHErr_PF( ss_fnfit.str(), tmp.bin, categoryMode );

      std::stringstream ss_fnlimit;
      ss_fnlimit << fitResultDir << "/higgsCombine_combinebin" << tmp.bin << ".Asymptotic.mH120.root";

      TFile* flimit = new TFile( ss_fnlimit.str().c_str(), "READ");
      TTree* fnlimit = (TTree*)flimit->Get("limit");
      double _exp;
      fnlimit->SetBranchAddress( "limit", &_exp );
      fnlimit->GetEntry(2);
      delete flimit;

      std::stringstream ss_sigma;
      ss_sigma << fitResultDir << "/PL_nsigma_npvalue_bin" << tmp.bin << ".root";
      //std::cout<< ss_sigma.str() << "\n"<<std::endl;

      TFile* fsigma = new TFile( ss_sigma.str().c_str(), "READ");
      TTree* limit = (TTree*)fsigma->Get("limit");
      double _limit;
      limit->SetBranchAddress( "limit", &_limit );
      limit->GetEntry(0);
      delete fsigma;

	TString line = Form("%d & %s & %.2f & %.2f & %.2f & %.2f & %.1f \\\\",
			  tmp.bin, tmp.box.c_str(), Nbkg, Nsmh, Ns, _exp, _limit);
			  

	std::cout << line << std::endl;
    }
  std::cout << "\\hline\n\\end{tabular}\n\\end{center}\n\\end{table*}" << std::endl;
*/
  std::string fdata = "/eos/cms/store/group/phys_susy/razor/Run2Analysis/SusyEwkHgg/FinalNtuples_2016+2017/DoubleEG_2016n2017_GoodLumi_skimmed.root";
  TFile* f_data = new TFile(fdata.c_str(),"READ");
  TTree* tree = (TTree*)f_data->Get("HggRazorLeptons");
  TString cut_baseline = "mGammaGamma > 122. && mGammaGamma < 129. && pho1passIso == 1 && pho2passIso == 1 && pho1passEleVeto == 1 && pho2passEleVeto == 1 && abs(pho1SC_Eta) <1.4442 && abs(pho2SC_Eta)<1.4442 && (pho1Pt/mGammaGamma>1./3. || pho2Pt/mGammaGamma>1./3.) && pho1Pt/mGammaGamma>1./4. && pho2Pt/mGammaGamma>1./4. && pho1R9>0.5 && pho2R9>0.5 "; 
/*
  std::cout << "\\begin{table*}[h]\n\\begin{center}\n\\topcaption{.}\n\\small\n\\begin{tabular}{|cc|c|ccc|cc|}\n\\hline";
  
  std::cout <<"\n           &          &       &                   & Yields   &        & limit & Obs. Local \\\\";
  std::cout << "\nBin        & Category & Data & Non-Resonant Bkg & SM Higgs & Signal & exp & Significance   \\\\\n\\hline\n";
*/
  std::cout << "\\begin{table*}[h]\n\\begin{center}\n\\topcaption{.}\n\\small\n\\begin{tabular}{|cc|c|cccc|cc|}\n\\hline";
  
  std::cout <<"\n            &          &      &                  & Yields        &                 &        & limit & Obs. Local \\\\";
  std::cout << "\nBin        & Category & Data & Non-Resonant Bkg & Exp. SM Higgs & Fitted SM Higgs & Signal & exp   & Significance   \\\\\n\\hline\n";
  for ( auto tmp: binVector )
    {
      //----------------------------
      //Key string to find bin
      //----------------------------
      //std::cout<< tmp.bin << "\n"<<std::endl;
      std::stringstream ss_fn;
      ss_fn << fitResultDir << "/HggRazorWorkspace_bin" << tmp.bin << ".root";
      //std::cout<< tmp.bin << "\n"<<std::endl;
      //std::cout<< tmp.box << "\n"<<std::endl;
      TString categoryCutString;
      if (tmp.box == "highpt") categoryCutString          = " && box==5 ";
      else if (tmp.box == "hbbhighpt") categoryCutString  = " && pTGammaGamma >= 110 && box==6";
      else if (tmp.box == "hbblowpt") categoryCutString   = " && pTGammaGamma < 110 && box==6";
      else if (tmp.box == "zbbhighpt") categoryCutString  = " && pTGammaGamma >= 110 && box==7";
      else if (tmp.box == "zbblowpt") categoryCutString   = " && pTGammaGamma < 110 && box==7";
      else if (tmp.box == "highres") categoryCutString    = " && box==8 ";
      else if (tmp.box == "lowres") categoryCutString     = " && box==9 ";
      else if (tmp.box == "muhighpt") categoryCutString   = " && pTGammaGamma >= 110 && box == 3 && lep1Pt > 20. ";
      else if (tmp.box == "mulowpt") categoryCutString    = " && pTGammaGamma < 110 && box == 3 && lep1Pt > 20. ";
      else if (tmp.box == "elehighpt") categoryCutString  = " && pTGammaGamma >= 110 && box == 4 && lep1Pt > 20. ";
      else if (tmp.box == "elelowpt") categoryCutString   = " && pTGammaGamma < 110 && box == 4 && lep1Pt > 20. ";
      else if (tmp.box == "twoleptons") categoryCutString = " && (box == 0 || box == 1 || box == 2)";
      //std::cout<< categoryCutString << "\n"<<std::endl;
      //std::cout<< "MR " <<tmp.x1 << "," << tmp.x2 << "; R2 " << tmp.y1 << " , " << tmp.y2 << "\n"<<std::endl;
      std::stringstream ss_binCut;
      if(tmp.x2==10000 && tmp.y2==1)
      	ss_binCut << " && MR > " << tmp.x1 << " && t1Rsq > " << tmp.y1;
      else if(tmp.x2==10000 && tmp.y2!=1)
      	ss_binCut << " && MR > " << tmp.x1 << " && t1Rsq > " << tmp.y1 << " && t1Rsq < " << tmp.y2;
      else if(tmp.x2!=10000 && tmp.y2==1)
      	ss_binCut << " && MR > " << tmp.x1 << " && MR < " << tmp.x2 << "&& t1Rsq > " << tmp.y1;
      else if(tmp.x2!=10000 && tmp.y2!=1)
      	ss_binCut << " && MR > " << tmp.x1 << " && MR < " << tmp.x2 << "&& t1Rsq > " << tmp.y1 << " && t1Rsq < " << tmp.y2;
      //std::cout<< ss_binCut.str() << "\n"<<std::endl;

      TString Cut;
      Cut = cut_baseline + categoryCutString + ss_binCut.str();
      //std::cout<< Cut << "\n"<<std::endl;
  
      int Ndata = tree->GetEntries(Cut);
      //std::cout<< Ndata << "\n"<<std::endl;

      
      //std::cout<< ss_fn.str() << "\n"<<std::endl;
      std::stringstream ss_fnfit;
      ss_fnfit << fitResultDir << "/mlfit_bin" << tmp.bin << ".root";


      float Ns = GetSignal( ss_fnfit.str(), tmp.bin, categoryMode );
      float NsErr = GetSignalErr( ss_fnfit.str(), tmp.bin, categoryMode );
      float Nsmh = GetSMH( ss_fnfit.str(), tmp.bin, categoryMode );
      float NsmhErr = GetSMHErr( ss_fnfit.str(), tmp.bin, categoryMode );
      float Nbkg = GetNbkg( ss_fnfit.str(),tmp.f1 ,tmp.bin, false,categoryMode );
      float NbkgErr = GetNbkg( ss_fnfit.str(),tmp.f1 ,tmp.bin, true,categoryMode );
      float Nsmh_pf = GetSMH_PF( ss_fnfit.str(),  tmp.bin, categoryMode );
      float NsmhErr_pf = GetSMHErr_PF( ss_fnfit.str(), tmp.bin, categoryMode );

      std::stringstream ss_fnlimit;
      ss_fnlimit << fitResultDir << "/higgsCombine_combinebin" << tmp.bin << ".Asymptotic.mH120.root";

      TFile* flimit = new TFile( ss_fnlimit.str().c_str(), "READ");
      TTree* fnlimit = (TTree*)flimit->Get("limit");
      double _exp;
      fnlimit->SetBranchAddress( "limit", &_exp );
      fnlimit->GetEntry(2);
      delete flimit;

      std::stringstream ss_sigma;
      ss_sigma << fitResultDir << "/PL_nsigma_npvalue_bin" << tmp.bin << ".root";
      //std::cout<< ss_sigma.str() << "\n"<<std::endl;

      TFile* fsigma = new TFile( ss_sigma.str().c_str(), "READ");
      TTree* limit = (TTree*)fsigma->Get("limit");
      double _limit;
      limit->SetBranchAddress( "limit", &_limit );
      limit->GetEntry(0);
      delete fsigma;

	//TString line = Form("%d & %s & %d & %.2f $\\pm$ %.2f & %.2f $\\pm$ %.2f & %.2f $\\pm$ %.2f &  %.2f $\\pm$ %.2f & %.2f & %.1f \\\\",
	//		  tmp.bin, tmp.box.c_str(), Ndata, Nbkg, NbkgErr, Nsmh, NsmhErr, Nsmh_pf, NsmhErr_pf, Ns, NsErr, _exp, _limit);
	TString line = Form("&  %.1f $\\pm$ %.1f  ",
			  Ns, NsErr);
			  

	std::cout << line << std::endl;
    }
  std::cout << "\\hline\n\\end{tabular}\n\\end{center}\n\\end{table*}" << std::endl;
  return 0;
};

float GetSignal( std::string fname, int bin, std::string cat )
{
  TFile* fin = TFile::Open( fname.c_str(), "READ");
  //signal_bin10_DCB_norm

/*
  RooWorkspace* myws = (RooWorkspace*)fin->Get("combineWS");
  std::stringstream ss;
  ss << "signal_bin" << bin << "_DCB_norm";
  //std::cout<< ss.str() << "\n"<<std::endl;
  RooRealVar* ss2 = (RooRealVar*)(myws->var( ss.str().c_str() ));
  return ss2->getVal();
*/
  //RooArgSet* norm_fit_s = (RooArgSet*) fin->Get("norm_fit_s");
  RooArgSet* norm_fit_s = (RooArgSet*) fin->Get("norm_prefit");

  std::stringstream ss;
  ss << "bin" << bin << "/signal";
  //std::cout<< ss.str() << "\n"<<std::endl;
  RooRealVar* ss2 = (RooRealVar*)norm_fit_s->find( ss.str().c_str() );
  return ss2->getVal();
};

float GetSignalErr( std::string fname, int bin, std::string cat )
{
  TFile* fin = TFile::Open( fname.c_str(), "READ");
  //signal_bin10_DCB_norm

/*
  RooWorkspace* myws = (RooWorkspace*)fin->Get("combineWS");
  std::stringstream ss;
  ss << "signal_bin" << bin << "_DCB_norm";
  //std::cout<< ss.str() << "\n"<<std::endl;
  RooRealVar* ss2 = (RooRealVar*)(myws->var( ss.str().c_str() ));
  return ss2->getError();
*/
  //RooArgSet* norm_fit_s = (RooArgSet*) fin->Get("norm_fit_s");
  RooArgSet* norm_fit_s = (RooArgSet*) fin->Get("norm_prefit");

  std::stringstream ss;
  ss << "bin" << bin << "/signal";
  //std::cout<< ss.str() << "\n"<<std::endl;
  RooRealVar* ss2 = (RooRealVar*)norm_fit_s->find( ss.str().c_str() );
  return ss2->getError();
};

float GetSMH( std::string fname, int bin, std::string cat )
{
  TFile* fin = TFile::Open( fname.c_str(), "READ");
  //SMH_bin10_DCB_norm
/*
  RooWorkspace* myws = (RooWorkspace*)fin->Get("combineWS");
  std::stringstream ss;
  ss << "SMH_bin" << bin << "_DCB_norm";
  //std::cout<< ss.str() << "\n"<<std::endl;
  RooRealVar* ss2 = (RooRealVar*)(myws->var( ss.str().c_str() ));
  return ss2->getVal();
*/
  RooArgSet* norm_fit_s = (RooArgSet*) fin->Get("norm_prefit");
  std::stringstream ss;
  ss << "bin" << bin << "/SMH";
  //std::cout<< ss.str() << "\n"<<std::endl;
  RooRealVar* ss2 = (RooRealVar*)norm_fit_s->find( ss.str().c_str() );
  return ss2->getVal();
};

float GetSMHErr( std::string fname, int bin, std::string cat )
{
  TFile* fin = TFile::Open( fname.c_str(), "READ");
  //SMH_bin10_DCB_norm
/*
  RooWorkspace* myws = (RooWorkspace*)fin->Get("combineWS");
  std::stringstream ss;
  ss << "SMH_bin" << bin << "_DCB_norm";
  //std::cout<< ss.str() << "\n"<<std::endl;
  RooRealVar* ss2 = (RooRealVar*)(myws->var( ss.str().c_str() ));
  return ss2->getError();
*/
  RooArgSet* norm_fit_s = (RooArgSet*) fin->Get("norm_prefit");
  std::stringstream ss;
  ss << "bin" << bin << "/SMH";
  //std::cout<< ss.str() << "\n"<<std::endl;
  RooRealVar* ss2 = (RooRealVar*)norm_fit_s->find( ss.str().c_str() );
  return ss2->getError();
};

float GetSMH_PF( std::string fname, int bin, std::string cat )
{
  TFile* fin = TFile::Open( fname.c_str(), "READ");
  RooArgSet* norm_fit_s = (RooArgSet*) fin->Get("norm_fit_s");
  //RooArgSet* norm_fit_s = (RooArgSet*) fin->Get("norm_prefit");

  std::stringstream ss;
  ss << "bin" << bin << "/SMH";
  //std::cout<< ss.str() << "\n"<<std::endl;
  RooRealVar* ss2 = (RooRealVar*)norm_fit_s->find( ss.str().c_str() );
  return ss2->getVal();
};

float GetSMHErr_PF( std::string fname, int bin, std::string cat )
{
  TFile* fin = TFile::Open( fname.c_str(), "READ");
  RooArgSet* norm_fit_s = (RooArgSet*) fin->Get("norm_fit_s");
  //RooArgSet* norm_fit_s = (RooArgSet*) fin->Get("norm_prefit");
  std::stringstream ss;
  ss << "bin" << bin << "/SMH";
  RooRealVar* ss2 = (RooRealVar*)norm_fit_s->find( ss.str().c_str() );
  return ss2->getError();
};


/*
float GetNbkg( std::string fname, std::string f1, int bin, bool _err, std::string cat )
{
  TFile* fin = TFile::Open( fname.c_str(), "READ");
  //singlePow_Bkg_bin10_spow_norm

  RooWorkspace* myws = (RooWorkspace*)fin->Get("combineWS");
  TString mggName = "mGammaGamma";
  RooRealVar mgg( mggName, "m_{#gamma#gamma}", 103, 160, "GeV" );
  mgg.setMin( 103. );
  mgg.setMax( 160. );
  mgg.setUnit( "GeV" );
  mgg.setBins(57);
  mgg.setRange( "signal", 122, 129. );
  mgg.setRange( "high", 135., 160. );
  mgg.setRange( "low", 103., 120. );
  mgg.setRange( "full", 103., 160. );
  mgg.setRange( "Full", 103., 160. );

  std::stringstream ss;
  if ( f1 == "singleExp" )
	ss << "singleExp_Bkg_bin" << bin << "_sExp_norm";
  else if ( f1 == "singlePow" )
	ss << "singlePow_Bkg_bin" << bin << "_spow_norm";
  else if ( f1 == "poly2" )
	ss << "poly2_Bkg_bin" << bin << "_pol2_norm";
  else if ( f1 == "poly3" )
	ss << "poly3_Bkg_bin" << bin << "_pol3_norm";
  //std::cout<< ss.str() << "\n"<<std::endl;
  RooRealVar* ss2 = (RooRealVar*)(myws->var( ss.str().c_str() ));
  return ss2->getVal();

  //return 0;
};
*/

float GetNbkg( std::string fname, std::string f1, int bin, bool _err, std::string cat )
{
  RooFit::PrintLevel(5);
  RooMsgService::instance().setGlobalKillBelow(RooFit::FATAL);
  TFile* fin = TFile::Open( fname.c_str(), "READ");
  RooFitResult* fit_r = (RooFitResult*)fin->Get("fit_s");
  /*fin = TFile::Open( "/Users/cmorgoth/Work/git/RazorEWKSUSYAnalysis/HggRazor/FitMgg/MaxLikelihoodFits/sb300_lsp1_unblinded_6p3ifb_Fixed/HggRazorWorkspace_bin8.root", "READ");
  RooWorkspace* myws = (RooWorkspace*)fin->Get("combineWS");
  RooRealVar* mymgg = (RooRealVar*)myws->var("mGammaGamma_bin8");
  RooAbsPdf* mypdf = (RooAbsPdf*)myws->pdf("singleExp_Bkg_bin8_sExp");
  myws->var("singleExp_Bkg_bin8_sExp_a")->setVal(-2.0071e-02);
  mymgg->setRange( "signal", 120, 130. );
  RooAbsReal* myigx = mypdf->createIntegral(*mymgg, RooFit::NormSet(*mymgg), RooFit::Range("signal"));;
  std::cout << "test--> " << myigx->getVal() << std::endl;
  myws = (RooWorkspace*)fin->Get("w_sb");
  RooFitResult* FR = (RooFitResult*)myws->obj("BkgOnlyFitResult");
  */
  TFile* ftmp = new TFile( "ws_tmp.root", "recreate");
  
 
  RooWorkspace* ws = new RooWorkspace( "ws", "" );
  TString mggName = "mGammaGamma";
/*
  RooRealVar mgg( mggName, "m_{#gamma#gamma}", 103, 160, "GeV" );
  //mgg.SetNameTitle( mggName, "m_{#gamma#gamma}" );
  mgg.setMin( 103. );
  mgg.setMax( 160. );
  mgg.setUnit( "GeV" );
  mgg.setBins(57);
  mgg.setRange( "signal", 122, 129. );
  mgg.setRange( "high", 135., 160. );
  mgg.setRange( "low", 103., 120. );
  mgg.setRange( "full", 103., 160. );
  mgg.setRange( "Full", 103., 160. );
*/
  RooRealVar mgg( mggName, "m_{#gamma#gamma}", 100, 180, "GeV" );
  //mgg.SetNameTitle( mggName, "m_{#gamma#gamma}" );
  mgg.setMin( 100. );
  mgg.setMax( 180. );
  mgg.setUnit( "GeV" );
  mgg.setBins(57);
  mgg.setRange( "signal", 122, 129. );
  mgg.setRange( "high", 135., 180. );
  mgg.setRange( "low", 100., 120. );
  mgg.setRange( "full", 100., 180. );
  mgg.setRange( "Full", 100., 180. );
  if ( f1 == "singleExp" )
    {
      int realBin = bin;
      if ( cat == "lowres" ) realBin = realBin+5;
      std::stringstream ss;
      ss << "singleExp_Bkg_bin" << realBin << "_sExp_a";
      RooRealVar *alpha = (RooRealVar*)fit_r->floatParsFinal().find( ss.str().c_str() );
      
      std::stringstream ss_2;
      if ( cat == "highres" ) ss_2 << "shapeBkg_Bkg_highResBin" << bin << "__norm";
      else if ( cat == "lowres" ) ss_2 << "shapeBkg_Bkg_lowResBin" << bin << "__norm";
      else ss_2 << "shapeBkg_Bkg_bin" << bin << "__norm";
      RooRealVar *Nbkg = (RooRealVar*)fit_r->floatParsFinal().find( ss_2.str().c_str() );
      
      
      TString pdf = MakeSingleExpNE( Form("%s_Bkg_bin%d",f1.c_str(),realBin), mgg, *ws );
      ws->var( pdf + "_a" )->setVal( alpha->getVal() );
      RooAbsReal* igx = ws->pdf( pdf )->createIntegral(mgg);
      //std::cout << Nbkg->getVal() << " +/- " << Nbkg->getError() << std::endl;
      RooAbsReal* igx_sig = ws->pdf( pdf )->createIntegral(mgg, RooFit::NormSet(mgg), RooFit::Range("signal"));
      //std::cout << Nbkg->getVal()*igx_sig->getVal() << " +/- " << Nbkg->getError()*igx_sig->getVal() << std::endl;
      if ( _err ) {
        return GetErrorFromToys( ws, fit_r, pdf, 10000, realBin );
      }
      //if ( _err ) return Nbkg->getError()*igx_sig->getVal();
      return Nbkg->getVal()*igx_sig->getVal();
      //double shapeErr = ws->pdf( pdf )->getPropagatedError(*fit_r)*Nbkg->getVal();
      /*
      RooArgSet* paramSet = mypdf->getParameters( RooArgSet(*mymgg) );
      paramSet->Print();
      TF1* myPdf = mypdf->asTF( RooArgList(*mymgg), RooArgList(*paramSet) );
      TMatrixDSym covMatrix = FR->covarianceMatrix();
      double params[1];
      params[0] = myPdf->GetParameter(0);
      double corrP[1];
      corrP[0] = 8.15e-03;
      
      double integ2_full = myPdf->Integral(103, 160);
      double integ2_signal = myPdf->Integral(120, 130);
      //double shapeErr = mypdf->getPropagatedError(*fit_r)*Nbkg->getVal();
      //double intErr = myPdf->IntegralError( 120., 130., params, covMatrix.GetMatrixArray(), 1e-14 );
      std::cout << params[0] << std::endl;
      double intErr = myPdf->IntegralError( 120., 130., params, corrP );
      std::cout << integ2_signal << " " << integ2_full << " " << intErr << std::endl;
      //return alpha->getVal();
      myPdf->Write();
      ftmp->Close();
      */
    }
  else if ( f1 == "singlePow" )
    {
      int realBin = bin;
      std::stringstream ss;
      ss << "singlePow_Bkg_bin" << realBin << "_spow_a";
      RooRealVar *alpha = (RooRealVar*)fit_r->floatParsFinal().find( ss.str().c_str() );

      std::stringstream ss_2;
      ss_2 << "shapeBkg_Bkg_bin" << bin << "__norm";
      RooRealVar *Nbkg = (RooRealVar*)fit_r->floatParsFinal().find( ss_2.str().c_str() );


      TString pdf = MakeSinglePowNE( Form("%s_Bkg_bin%d",f1.c_str(),realBin), mgg, *ws );
      ws->var( pdf + "_a" )->setVal( alpha->getVal() );
      RooAbsReal* igx = ws->pdf( pdf )->createIntegral(mgg);
      RooAbsReal* igx_sig = ws->pdf( pdf )->createIntegral(mgg, RooFit::NormSet(mgg), RooFit::Range("signal"));
      if ( _err ) {
        return GetErrorFromToys( ws, fit_r, pdf, 10000, realBin );
      }
      return Nbkg->getVal()*igx_sig->getVal();
    }
  else if ( f1 == "poly2" )
    {
      int realBin = bin;
      if ( cat == "lowres" ) realBin = realBin+5;
      std::stringstream ss0;
      ss0 << "poly2_Bkg_bin" << realBin << "_pol2_p0";
      RooRealVar *p0 = (RooRealVar*)fit_r->floatParsFinal().find( ss0.str().c_str() );
      std::stringstream ss1;
      ss1 << "poly2_Bkg_bin" << realBin << "_pol2_p1";
      RooRealVar *p1 = (RooRealVar*)fit_r->floatParsFinal().find( ss1.str().c_str() );
      std::stringstream ssC;
      ssC << "poly2_Bkg_bin" << realBin << "_pol2_pC";
      RooRealVar *pC = (RooRealVar*)fit_r->floatParsFinal().find( ssC.str().c_str() );

      std::stringstream ss_2;
      if ( cat == "highres" ) ss_2 << "shapeBkg_Bkg_highResBin" << bin << "__norm";
      else if ( cat == "lowres" ) ss_2 << "shapeBkg_Bkg_lowResBin" << bin << "__norm";
      else ss_2 << "shapeBkg_Bkg_bin" << bin << "__norm";
      RooRealVar *Nbkg = (RooRealVar*)fit_r->floatParsFinal().find( ss_2.str().c_str() );
      
      
      TString pdf = MakePoly2NE( Form("%s_Bkg_bin%d",f1.c_str(),realBin), mgg, *ws );
      ws->var( pdf + "_p0" )->setVal( p0->getVal() );
      ws->var( pdf + "_p1" )->setVal( p1->getVal() );
      ws->var( pdf + "_pC" )->setVal( pC->getVal() );
      RooAbsReal* igx = ws->pdf( pdf )->createIntegral(mgg);
      //std::cout << Nbkg->getVal() << " +/- " << Nbkg->getError() << std::endl;
      RooAbsReal* igx_sig = ws->pdf( pdf )->createIntegral(mgg, RooFit::NormSet(mgg), RooFit::Range("signal"));
      //std::cout << Nbkg->getVal()*igx_sig->getVal() << " +/- " << Nbkg->getError()*igx_sig->getVal() << std::endl;
      if ( _err ) {
        return GetErrorFromToys( ws, fit_r, pdf, 10000, realBin );
      }
      //if ( _err ) return Nbkg->getError()*igx_sig->getVal();
      return Nbkg->getVal()*igx_sig->getVal();
    }
  else if ( f1 == "poly3" )
    {
      int realBin = bin;
      if ( cat == "lowres" ) realBin = realBin+5;
      std::stringstream ss0;
      ss0 << "poly3_Bkg_bin" << realBin << "_pol3_p0";
      //std::cout << ss0.str() << std::endl;
      RooRealVar *p0 = (RooRealVar*)fit_r->floatParsFinal().find( ss0.str().c_str() );
      std::stringstream ss1;
      ss1 << "poly3_Bkg_bin" << realBin << "_pol3_p1";
      RooRealVar *p1 = (RooRealVar*)fit_r->floatParsFinal().find( ss1.str().c_str() );
      std::stringstream ss2;
      ss2 << "poly3_Bkg_bin" << realBin << "_pol3_p2";
      RooRealVar *p2 = (RooRealVar*)fit_r->floatParsFinal().find( ss2.str().c_str() );
      std::stringstream ssC;
      ssC << "poly3_Bkg_bin" << realBin << "_pol3_pC";
      RooRealVar *pC = (RooRealVar*)fit_r->floatParsFinal().find( ssC.str().c_str() );
      //std::cout << pC->getVal() << std::endl;

      std::stringstream ss_2;
      if ( cat == "highres" ) ss_2 << "shapeBkg_Bkg_highResBin" << bin << "__norm";
      else if ( cat == "lowres" ) ss_2 << "shapeBkg_Bkg_lowResBin" << bin << "__norm";
      else ss_2 << "shapeBkg_Bkg_bin" << bin << "__norm";
      RooRealVar *Nbkg = (RooRealVar*)fit_r->floatParsFinal().find( ss_2.str().c_str() );

      
      TString pdf = MakePoly3NE( Form("%s_Bkg_bin%d",f1.c_str(),realBin), mgg, *ws );
      ws->var( pdf + "_p0" )->setVal( p0->getVal() );
      ws->var( pdf + "_p1" )->setVal( p1->getVal() );
      ws->var( pdf + "_p2" )->setVal( p2->getVal() );
      ws->var( pdf + "_pC" )->setVal( pC->getVal() );
      RooAbsReal* igx = ws->pdf( pdf )->createIntegral(mgg);
      //std::cout << Nbkg->getVal() << " +/- " << Nbkg->getError() << std::endl;
      RooAbsReal* igx_sig = ws->pdf( pdf )->createIntegral(mgg, RooFit::NormSet(mgg), RooFit::Range("signal"));
      //std::cout << Nbkg->getVal()*igx_sig->getVal() << " +/- " << Nbkg->getError()*igx_sig->getVal() << std::endl;
      if ( _err ) {
        return GetErrorFromToys( ws, fit_r, pdf, 10000, realBin );
      }
      //if ( _err ) return Nbkg->getError()*igx_sig->getVal();
      return Nbkg->getVal()*igx_sig->getVal();
    }
  else if ( f1 == "modExp" )
    {
      int realBin = bin;
      if ( cat == "lowres" ) realBin = realBin+5;
      std::stringstream ss;
      ss << "modExp_Bkg_bin" << realBin << "_mexp_a";
      RooRealVar *alpha = (RooRealVar*)fit_r->floatParsFinal().find( ss.str().c_str() );
      std::stringstream ssm;
      ssm << "modExp_Bkg_bin" << realBin << "_mexp_m";
      RooRealVar *m = (RooRealVar*)fit_r->floatParsFinal().find( ssm.str().c_str() );
      
      std::stringstream ss_2;
      if ( cat == "highres" ) ss_2 << "shapeBkg_Bkg_highResBin" << bin << "__norm";
      else if ( cat == "lowres" ) ss_2 << "shapeBkg_Bkg_lowResBin" << bin << "__norm";
      else ss_2 << "shapeBkg_Bkg_bin" << bin << "__norm";
      RooRealVar *Nbkg = (RooRealVar*)fit_r->floatParsFinal().find( ss_2.str().c_str() );
      
      
      TString pdf = MakeModExpNE( Form("%s_Bkg_bin%d",f1.c_str(),realBin), mgg, *ws );
      ws->var( pdf + "_a" )->setVal( alpha->getVal() );
      ws->var( pdf + "_m" )->setVal( m->getVal() );
      RooAbsReal* igx = ws->pdf( pdf )->createIntegral(mgg);
      //std::cout << Nbkg->getVal() << " +/- " << Nbkg->getError() << std::endl;
      RooAbsReal* igx_sig = ws->pdf( pdf )->createIntegral(mgg, RooFit::NormSet(mgg), RooFit::Range("signal"));
      //std::cout << Nbkg->getVal()*igx_sig->getVal() << " +/- " << Nbkg->getError()*igx_sig->getVal() << std::endl;
      if ( _err ) {
        return GetErrorFromToys( ws, fit_r, pdf, 10000, realBin );
      }
      //if ( _err ) return Nbkg->getError()*igx_sig->getVal();
      return Nbkg->getVal()*igx_sig->getVal();
    }
  else if ( f1 == "doubleExp" )
    {
      int realBin = bin;
      if ( cat == "lowres" ) realBin = realBin+5;
      std::stringstream ssa1;
      ssa1 << "doubleExp_Bkg_bin" << realBin << "_doubleExp_a1";
      RooRealVar *alpha1 = (RooRealVar*)fit_r->floatParsFinal().find( ssa1.str().c_str() );
      std::stringstream ssa2;
      ssa2 << "doubleExp_Bkg_bin" << realBin << "_doubleExp_a2";
      RooRealVar *alpha2 = (RooRealVar*)fit_r->floatParsFinal().find( ssa2.str().c_str() );
      std::stringstream ssfrac;
      ssfrac << "doubleExp_Bkg_bin" << realBin << "_doubleExp_frac";
      RooRealVar *frac = (RooRealVar*)fit_r->floatParsFinal().find( ssfrac.str().c_str() );
      
      std::stringstream ss_2;
      if ( cat == "highres" ) ss_2 << "shapeBkg_Bkg_highResBin" << bin << "__norm";
      else if ( cat == "lowres" ) ss_2 << "shapeBkg_Bkg_lowResBin" << bin << "__norm";
      else ss_2 << "shapeBkg_Bkg_bin" << bin << "__norm";
      RooRealVar *Nbkg = (RooRealVar*)fit_r->floatParsFinal().find( ss_2.str().c_str() );
      
      
      TString pdf = MakeDoubleExpNE( Form("%s_Bkg_bin%d",f1.c_str(),realBin), mgg, *ws );
      ws->var( pdf + "_a1" )->setVal( alpha1->getVal() );
      ws->var( pdf + "_a2" )->setVal( alpha2->getVal() );
      ws->var( pdf + "_frac" )->setVal( frac->getVal() );
      RooAbsReal* igx = ws->pdf( pdf )->createIntegral(mgg);
      //std::cout << Nbkg->getVal() << " +/- " << Nbkg->getError() << std::endl;
      RooAbsReal* igx_sig = ws->pdf( pdf )->createIntegral(mgg, RooFit::NormSet(mgg), RooFit::Range("signal"));
      //std::cout << Nbkg->getVal()*igx_sig->getVal() << " +/- " << Nbkg->getError()*igx_sig->getVal() << std::endl;
      if ( _err ) {
        return GetErrorFromToys( ws, fit_r, pdf, 10000, realBin );
      }
      //if ( _err ) return Nbkg->getError()*igx_sig->getVal();
      return Nbkg->getVal()*igx_sig->getVal();
    }

  return 0;
};

float GetErrorFromToys(RooWorkspace *ws, RooFitResult *fr, TString pdfName, unsigned int ntoys, int binNum, 
        bool plotBkgFuncs) {
    RooRandom::randomGenerator()->SetSeed(33333);
    TCanvas *c = new TCanvas("c","c",400,300);
    RooPlot *frame = ws->var("mGammaGamma")->frame();

    RooAbsPdf *pdf = ws->pdf(pdfName);

    // throw toys
    std::vector<float> toyYields;
    for( unsigned int itoy = 0; itoy < ntoys; itoy++ ) {
        // randomize function parameters
        RooArgList toyPars = fr->randomizePars();
        float toyNorm = -1;

        // set params to new values
        TIterator *toyIter = toyPars.createIterator();
        while( RooRealVar *curVar = (RooRealVar*)toyIter->Next() ) {
	  std::string varName = curVar->GetName();
	  if (curVar->isConstant() && varName.find("shapeBkg_Bkg") == std::string::npos ) continue;
	  
	  RooRealVar *pdfVar = ws->var( curVar->GetName() );
	  if (pdfVar) {
	    pdfVar->setVal( curVar->getVal() );
	    pdfVar->setError( curVar->getError() );
	  }
	  std::stringstream ntotalName;
	  ntotalName << "shapeBkg_Bkg_bin" << binNum << "__norm";
	  //if ( binNum <= 8 ) ntotalName << "shapeBkg_Bkg_bin" << binNum << "__norm";
	  //else if ( binNum <= 13 ) ntotalName << "shapeBkg_Bkg_highResBin" << binNum << "__norm";
	  //else if ( binNum <= 18 ) ntotalName << "shapeBkg_Bkg_lowResBin" << binNum-5 << "__norm";
	  if ( curVar->GetName() == ntotalName.str() ) toyNorm = curVar->getVal();
	}

        // get norm of pdf in signal region
        RooAbsReal *integral = pdf->createIntegral( *(ws->var("mGammaGamma")), 
                RooFit::NormSet( RooArgSet(*(ws->var("mGammaGamma"))) ), RooFit::Range("signal") );
        toyYields.push_back( integral->getVal()*toyNorm );

        // draw the curve
        if (plotBkgFuncs) {
            pdf->plotOn(frame, RooFit::LineWidth(1), RooFit::LineColor(
                    TColor::GetColor((Float_t)0.,(Float_t)0.,(Float_t)(itoy*1.0/ntoys))));
        }
    }

    if (plotBkgFuncs) {
        // draw frame with all sampled curves
        frame->Draw();
        c->Print(Form("toysenvelopebin%d.pdf",binNum));
    }

    // compute mean, min, max
    float mean = 0.0;
    float min = 999999.;
    float max = -1.;
    for( auto &yield : toyYields ) {
        mean += yield;
        if (yield > max) max = yield;
        if (yield < min) min = yield;
    }
    mean /= ntoys;
    // make histogram for illustration
    TH1F *yieldHist = new TH1F("yieldHist", Form("Toys for Bin %d", binNum), 50, min*0.9, max*1.1);
    // compute variance
    float variance = 0.0;
    for( auto &yield : toyYields ) {
        variance += (yield-mean)*(yield-mean);
        yieldHist->Fill(yield);
    }
    variance /= (ntoys-1);

    // make plot
    yieldHist->SetMarkerStyle(20);
    yieldHist->SetMarkerSize(.5);
    yieldHist->Draw("p");
    c->Print(Form("toysbin%d.pdf",binNum));
    delete yieldHist;
    delete c;
    // return standard deviation
    return sqrt(variance);
}
