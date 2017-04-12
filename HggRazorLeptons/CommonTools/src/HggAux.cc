//C++ INCLUDES
#include <iostream>
#include <fstream>
//ROOT INCLUDES
//LOCAL INCLUDES
#include "HggAux.hh"

Boxes& operator++( Boxes& box ){ return box = (Boxes)( std::underlying_type<Boxes>::type( box ) + 1 ); };
Boxes operator*( Boxes box ){ return box; };
Boxes begin( Boxes box ){ return Boxes::HighPt; };
Boxes end( Boxes box ){ return Boxes::Last; };

Process& operator++( Process& process ){ return process = (Process)( std::underlying_type<Process>::type( process ) + 1 ); };
Process operator*( Process process ){ return process; };
Process begin( Process process ){ return Process::gammaJet; };
Process end( Process process ){ return Process::Last; };

HistoTypes& operator++( HistoTypes& htype ){ return htype = (HistoTypes)( std::underlying_type<HistoTypes>::type( htype ) + 1 ); };
HistoTypes operator*( HistoTypes htype ){ return htype; };
HistoTypes begin( HistoTypes htype ){ return HistoTypes::mr; };
HistoTypes end( HistoTypes htype ){ return HistoTypes::Last; };

FitFunction& operator++( FitFunction& fitf ){ return fitf = (FitFunction)(std::underlying_type<FitFunction>::type( fitf ) + 1 ); };
FitFunction operator*( FitFunction fitf ){ return fitf; };
FitFunction begin( FitFunction fitf ){ return FitFunction::singleExp; };
FitFunction end( FitFunction fitf ){ return FitFunction::Last; };


//---------------------------------
//H i s t o g r a m   s e c t i o n
//---------------------------------
bool Histos::AssignHisto( HistoTypes htype, TH1F h )
{
  if ( htype == HistoTypes::mr ) mr = h;
  if ( htype == HistoTypes::rsq ) rsq = h;
  if ( htype == HistoTypes::mgg ) mgg = h;
  if ( htype == HistoTypes::ptgg ) ptgg = h;
  if ( htype == HistoTypes::sigmaMoverM ) sigmaMoverM = h;
  
  if ( htype == HistoTypes::pho1pt ) pho1pt = h;
  if ( htype == HistoTypes::pho1eta ) pho1eta = h;
  if ( htype == HistoTypes::pho1phi ) pho1phi = h;
  if ( htype == HistoTypes::pho1sigmaIetaIeta ) pho1sigmaIetaIeta = h;
  if ( htype == HistoTypes::pho1r9 ) pho1r9 = h;
  if ( htype == HistoTypes::pho1HoverE ) pho1HoverE = h;
  if ( htype == HistoTypes::pho1sumChargedHadronPt ) pho1sumChargedHadronPt = h;
  if ( htype == HistoTypes::pho1sumNeutralHadronEt ) pho1sumNeutralHadronEt = h;
  if ( htype == HistoTypes::pho1sumPhotonEt ) pho1sumPhotonEt = h;
  if ( htype == HistoTypes::pho1sigmaEoverE ) pho1sigmaEoverE = h;
   
  if ( htype == HistoTypes::pho2pt ) pho2pt = h;
  if ( htype == HistoTypes::pho2eta ) pho2eta = h;
  if ( htype == HistoTypes::pho2phi ) pho2phi = h;
  if ( htype == HistoTypes::pho2sigmaIetaIeta ) pho2sigmaIetaIeta = h;
  if ( htype == HistoTypes::pho2r9 ) pho2r9 = h;
  if ( htype == HistoTypes::pho2HoverE ) pho2HoverE = h;
  if ( htype == HistoTypes::pho2sumChargedHadronPt ) pho2sumChargedHadronPt = h;
  if ( htype == HistoTypes::pho2sumNeutralHadronEt ) pho2sumNeutralHadronEt = h;
  if ( htype == HistoTypes::pho2sumPhotonEt ) pho2sumPhotonEt = h;
  if ( htype == HistoTypes::pho2sigmaEoverE ) pho2sigmaEoverE = h;
  
  if ( htype == HistoTypes::njets ) njets = h;
  if ( htype == HistoTypes::unrollHighPt ) unrollHighPt = h;
  if ( htype == HistoTypes::unrollHighRes ) unrollHighRes = h;
  return true;
};

TH1F Histos::GetHisto( HistoTypes htype )
{
  TH1F h;
  if ( htype == HistoTypes::mr ) return mr;
  if ( htype == HistoTypes::rsq ) return rsq;
  if ( htype == HistoTypes::mgg ) return mgg;
  if ( htype == HistoTypes::ptgg ) return ptgg;
  if ( htype == HistoTypes::sigmaMoverM ) return sigmaMoverM;

  if ( htype == HistoTypes::pho1pt ) return pho1pt;
  if ( htype == HistoTypes::pho1eta ) return pho1eta;
  if ( htype == HistoTypes::pho1phi ) return pho1phi;
  if ( htype == HistoTypes::pho1sigmaIetaIeta ) return pho1sigmaIetaIeta;
  if ( htype == HistoTypes::pho1r9 ) return pho1r9;
  if ( htype == HistoTypes::pho1HoverE ) return pho1HoverE;
  if ( htype == HistoTypes::pho1sumChargedHadronPt ) return pho1sumChargedHadronPt;
  if ( htype == HistoTypes::pho1sumNeutralHadronEt ) return pho1sumNeutralHadronEt;
  if ( htype == HistoTypes::pho1sumPhotonEt ) return pho1sumPhotonEt;
  if ( htype == HistoTypes::pho1sigmaEoverE ) return pho1sigmaEoverE;
  
  if ( htype == HistoTypes::pho2pt ) return pho2pt;
  if ( htype == HistoTypes::pho2eta ) return pho2eta;
  if ( htype == HistoTypes::pho2phi ) return pho2phi;
  if ( htype == HistoTypes::pho2sigmaIetaIeta ) return pho2sigmaIetaIeta;
  if ( htype == HistoTypes::pho2r9 ) return pho2r9;
  if ( htype == HistoTypes::pho2HoverE ) return pho2HoverE;
  if ( htype == HistoTypes::pho2sumChargedHadronPt ) return pho2sumChargedHadronPt;
  if ( htype == HistoTypes::pho2sumNeutralHadronEt ) return pho2sumNeutralHadronEt;
  if ( htype == HistoTypes::pho2sumPhotonEt ) return pho2sumPhotonEt;
  if ( htype == HistoTypes::pho2sigmaEoverE ) return pho2sigmaEoverE;
  
  if ( htype == HistoTypes::njets ) return njets;
  if ( htype == HistoTypes::unrollHighPt ) return unrollHighPt;
  if ( htype == HistoTypes::unrollHighRes ) return unrollHighRes;
  return h;
};

std::string GetHistoTypesString( HistoTypes htype )
{
  if ( htype == HistoTypes::mr ) return "mr";
  if ( htype == HistoTypes::rsq ) return "rsq";
  if ( htype == HistoTypes::mgg ) return "mgg";
  if ( htype == HistoTypes::ptgg ) return "ptgg";
  if ( htype == HistoTypes::sigmaMoverM ) return "sigmaMoverM";

  if ( htype == HistoTypes::pho1pt ) return "pho1pt";
  if ( htype == HistoTypes::pho1eta ) return "pho1eta";
  if ( htype == HistoTypes::pho1phi ) return "pho1phi";
  if ( htype == HistoTypes::pho1sigmaIetaIeta ) return "pho1sigmaIetaIeta";
  if ( htype == HistoTypes::pho1r9 ) return "pho1r9";
  if ( htype == HistoTypes::pho1HoverE ) return "pho1HoverE";
  if ( htype == HistoTypes::pho1sumChargedHadronPt ) return "pho1sumChargedHadronPt";
  if ( htype == HistoTypes::pho1sumNeutralHadronEt ) return "pho1sumNeutralHadronEt";
  if ( htype == HistoTypes::pho1sumPhotonEt ) return "pho1sumPhotonEt";
  if ( htype == HistoTypes::pho1sigmaEoverE ) return "pho1sigmaEoverE";
    
  if ( htype == HistoTypes::pho2pt ) return "pho2pt";
  if ( htype == HistoTypes::pho2eta ) return "pho2eta";
  if ( htype == HistoTypes::pho2phi ) return "pho2phi";
  if ( htype == HistoTypes::pho2sigmaIetaIeta ) return "pho2sigmaIetaIeta";
  if ( htype == HistoTypes::pho2r9 ) return "pho2r9";
  if ( htype == HistoTypes::pho2HoverE ) return "pho2HoverE";
  if ( htype == HistoTypes::pho2sumChargedHadronPt ) return "pho2sumChargedHadronPt";
  if ( htype == HistoTypes::pho2sumNeutralHadronEt ) return "pho2sumNeutralHadronEt";
  if ( htype == HistoTypes::pho2sumPhotonEt ) return "pho2sumPhotonEt";
  if ( htype == HistoTypes::pho2sigmaEoverE ) return "pho2sigmaEoverE";
  
  if ( htype == HistoTypes::njets ) return "njets";
  if ( htype == HistoTypes::unrollHighPt ) return "unrollHighPt";
  if ( htype == HistoTypes::unrollHighRes ) return "unrollHighRes";
  
  std::cerr << "[ERROR]: Htype not found" << std::endl;
  return "";
};

std::string GetBoxString( Boxes box )
{
  if ( box == Boxes::HighPt )
    {
      return "HighPt";
    }
  else if ( box == Boxes::Hbb )
    {
      return "Hbb";
    }
  else if ( box == Boxes::Zbb )
    {
      return "Zbb";
    }
  else if ( box == Boxes::HighRes )
    {
      return "HighRes";
    }
  else if( box == Boxes::LowRes )
    {
      return "LowRes";
    }
  else
    {
      std::cerr << "[ERROR]: Box not found" << std::endl;
    }
  return "";
};

std::string GetProcessString( Process process )
{
  if ( process == Process::ttH )
    {
      return "ttH";
    }
  else if ( process == Process::vH )
    {
      return "vH";
    }
  else if ( process == Process::ggH )
    {
      return "ggH";
    }
  else if ( process == Process::vbfH )
    {
      return "vbfH";
    }
  else if( process == Process::qcd )
    {
      return "qcd";
    }
  else if( process == Process::diphoton )
    {
      return "diphoton";
    }
  else if( process == Process::gammaJet )
    {
      return "gammaJet";
    }
  else if ( process == Process::signal )
    {
      return "signal";
    }
  else if ( process == Process::data )
    {
      return "data";
    }
   else if ( process == Process::dy )
    {
      return "dy";
    }
   else if ( process == Process::dy )
    {
      return "w";
    }
   else if ( process == Process::dy )
    {
      return "znunu";
    }
   else if ( process == Process::dy )
    {
      return "tt";
    }
   else if ( process == Process::dy )
    {
      return "top";
    }
  else if ( process == Process::dy )
    {
      return "vv";
    }
   else if ( process == Process::dy )
    {
      return "ww";
    }
   else if ( process == Process::dy )
    {
      return "zz";
    }
   else if ( process == Process::dy )
    {
      return "wz";
    }
   else
    {
      std::cerr << "[ERROR]: Process not found" << std::endl;
    }
  return "";
};


Process GetProcessString( std::string process )
{
  if ( process == "ttH" )
    {
      return Process::ttH;
    }
  else if ( process == "tt" )
    {
      return Process::tt;
    }
  else if ( process == "w" )
    {
      return Process::w;
    }
  else if ( process == "dy" )
    {
      return Process::dy;
    }
  else if ( process == "top" )
    {
      return Process::top;
    }
  else if ( process == "vv" )
    {
      return Process::vv;
    }
  else if ( process == "ww" )
    {
      return Process::ww;
    }
  else if ( process == "zz" )
    {
      return Process::zz;
    }
  else if ( process == "wz" )
    {
      return Process::wz;
    }
  else if ( process == "znunu" )
    {
      return Process::znunu;
    }
  else if ( process == "vH" )
    {
      return Process::vH;
    }
  else if ( process == "ggH" )
    {
      return Process::ggH;
    }
  else if ( process == "vbfH" )
    {
      return Process::vbfH;
    }
  else if( process == "qcd" )
    {
      return Process::qcd;
    }
  else if( process == "diphoton" )
    {
      return Process::diphoton;
    }
  else if( process == "gammaJet" )
    {
      return Process::gammaJet;
    }
  else if ( process == "signal" )
    {
      return Process::signal;
    }
  else if( process == "data" )
    {
      return Process::data;
    }
  else
    {
      std::cerr << "[ERROR] (HggAux): Process not found" << std::endl;
    }

  return Process::unknown;
};
std::string GetFitFunctionString( FitFunction  fitf )
{
  if ( fitf == FitFunction::singleExp )
    {
      return "singleExp";
    }
  else if ( fitf == FitFunction::doubleExp )
    {
      return "doubleExp";
    }
  else if ( fitf == FitFunction::modExp )
    {
      return "modExp";
    }
  else if ( fitf == FitFunction::singlePow )
    {
      return "singlePow";
    }
  else if( fitf == FitFunction::doublePow )
    {
      return "doublePow";
    }
  else if( fitf == FitFunction::poly2 )
    {
      return "poly2";
    }
  else if( fitf == FitFunction::poly3 )
    {
      return "poly3";
    }
  else
    {
      std::cerr << "[ERROR]: FitFunction not found" << std::endl;
    }
  return "";
};
//Fill map with input lists
bool FillMapList( std::map< std::string, std::string >& thisMap, std::string inputList )
{
  std::string key;
  std::string val;
  
  std::ifstream ifs ( inputList.c_str(), std::fstream::in );
  if ( ifs.is_open() )
    {
      while( ifs.good() )
	{
	  if ( ifs.eof() ) break;
	  ifs >> key >> val;
	  if ( thisMap.find( key ) == thisMap.end() )
	    {
	      thisMap[key] = val;
	    }
	}
    }
  else
    {
      std::cerr << "[ERROR]: Unable to Open File-> " << inputList << std::endl;
      return false;
    }
  return true;
};
