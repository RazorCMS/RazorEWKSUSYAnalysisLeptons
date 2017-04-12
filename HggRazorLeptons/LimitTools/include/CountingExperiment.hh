#ifndef PlotBias_HH
#define PlotBias_HH
//C++ INCLUDES
#include <string>
#include <utility>
#include <map>
#include <fstream>
#include <sstream>
//ROOT INCLUDES
#include <TH1F.h>
#include <TH2F.h>
#include <TString.h>

struct ProcessStruct
{
  TH2F* h_inc;
  TH2F* h_sr;
};

//Functions
TH2F* Create2DHisto( TTree* tree, std::map<float, std::vector<float>> bMap, float RsqBinSize = 0.01, TString pName = "dummy", const float lumi = 2300., const float kf = 1.0 );
void CreateDataCard( std::map<TString,ProcessStruct> psMap, float* MRedges, std::vector<float*> RSQbinning, float rsqBinSize = 0.001 );
void CreateDataCard( std::map<TString,ProcessStruct> psMap, std::map<float, std::vector<float>> bMap, float rsqBinSize = 0.001, TString cat = "dummy" );

float GetSRYield( TH2F* h, float* MRedges, std::vector<float*> RSQbinning, float rsqBinSize = 0.001 );
float GetSRYield( TH2F* h, float mrLow, float rsqLow, float rsqHigh, float rsqBinStep = 0.001 );

void PlotSignalModel( std::string fname = "", std::string outDir = "bias_plots");

#endif
