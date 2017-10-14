#ifndef HGG_AUX_HH
#define HGG_AUX_HH
//C++ INCLUDES
#include <string>
#include <map>
//ROOT INCLUDES
#include <TString.h>
#include <TLegend.h>
#include <TH1F.h>
//LOCAL INCLUDES


enum class Boxes{ HighPt, Hbb, Zbb, HighRes, LowRes, Last };
// R e d e f i n i n g   O p e r a t o r   t o   L o o p   O v e r   B o x e s
//----------------------------------------------------------------------------
Boxes begin( Boxes box );
Boxes end( Boxes box );
Boxes& operator++( Boxes& box );
Boxes operator*( Boxes box );

std::string GetBoxString( Boxes box );


//--------------------------------------------------------------------------------
// Binning class
//--------------------------------------------------------------------------------
struct Bin
{
  std::string box;
  std::string f1;
  int bin;
  float x1;
  float x2;
  float y1;
  float y2;
  
  bool const operator== (const Bin &b) const
  {
    return bin == b.bin;
  }
  
  bool const operator< (const Bin &b) const
  {
    return bin < b.bin;
  }
};


enum class Process{ gammaJet, diphoton, qcd, ggH, vbfH, vH, bbH, ttH, w, wg, wgg, znunu, zgg, dy, tt, tg, ttg, ttgg, top, vv, ww, zz, wz, signal,data, unknown, Last };
struct Yields
{
  float gammaJet[2];
  float diphoton[2];
  float qcd[2];
  float ggH[2];
  float vbfH[2];
  float vH[2];
  float ttH[2];
  float data[2];
};
// R e d e f i n i n g   O p e r a t o r   t o   L o o p   O v e r   P r o c e s s
//--------------------------------------------------------------------------------
Process begin( Process process );
Process end( Process process );
Process& operator++( Process& process );
Process operator*( Process process );
std::string GetProcessString( Process process );

enum class HistoTypes{ mr, rsq, mgg, ptgg, sigmaMoverM, pho1pt, pho1eta, pho1phi, pho1sigmaIetaIeta, pho1r9, pho1HoverE, pho1sumChargedHadronPt, pho1sumNeutralHadronEt, pho1sumPhotonEt, pho1sigmaEoverE, pho2pt, pho2eta, pho2phi, pho2sigmaIetaIeta, pho2r9, pho2HoverE, pho2sumChargedHadronPt, pho2sumNeutralHadronEt, pho2sumPhotonEt, pho2sigmaEoverE, njets, met, mt, ptlep, unrollHighPt, unrollHighRes, Last};
HistoTypes begin( HistoTypes htype );
HistoTypes end( HistoTypes htype );
HistoTypes& operator++( HistoTypes& htype );
HistoTypes operator*( HistoTypes htype );
std::string GetHistoTypesString( HistoTypes htype );

Process GetProcessString( std::string process );

enum class FitFunction{ singleExp, doubleExp, modExp, singlePow, doublePow, poly2, poly3, Last };
// R e d e f i n i n g   O p e r a t o r   t o   L o o p   O v e r   F i t F u n c t i o n s
//------------------------------------------------------------------------------------------
FitFunction begin( FitFunction fitf );
FitFunction end( FitFunction fitf );
FitFunction& operator++( FitFunction& fitf );
FitFunction operator*( FitFunction fitf );
std::string GetFitFunctionString( FitFunction  fitf );

struct Histos
{
  Process process;
  TString processName;
  TH1F mr;
  TH1F rsq;
  TH1F unrollHighPt;
  TH1F unrollHighRes;
  TH1F mgg;
  TH1F ptgg;
  TH1F sigmaMoverM;
  
  TH1F pho1pt;
  TH1F pho1eta;
  TH1F pho1phi;
  TH1F pho1sigmaIetaIeta;
  TH1F pho1r9;
  TH1F pho1HoverE;
  TH1F pho1sumChargedHadronPt;
  TH1F pho1sumNeutralHadronEt;
  TH1F pho1sumPhotonEt;
  TH1F pho1sigmaEoverE;
  
  TH1F pho2pt;
  TH1F pho2eta;
  TH1F pho2phi;
  TH1F pho2sigmaIetaIeta;
  TH1F pho2r9;
  TH1F pho2HoverE;
  TH1F pho2sumChargedHadronPt;
  TH1F pho2sumNeutralHadronEt;
  TH1F pho2sumPhotonEt;
  TH1F pho2sigmaEoverE;
  
  TH1F njets;
  TH1F met;
  TH1F mt;
  TH1F ptlep;
  bool AssignHisto( HistoTypes htype, TH1F h );
  TH1F GetHisto( HistoTypes htype );
};

bool FillMapList( std::map< std::string, std::string >& thisMap, std::string inputList );
#endif
