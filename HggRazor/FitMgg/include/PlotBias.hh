#ifndef PlotBias_HH
#define PlotBias_HH
//C++ INCLUDES
#include <string>
#include <utility>
#include <map>

void PlotBias( std::string fname , std::string outDir );
std::pair<double,double> GetMeanRms(  std::string fname = "", std::string dataSet = "bias_plots", std::string var = "bias" );
void MakeTable( std::map< std::pair<std::string,std::string>, double > mymap, TString type );
void MakeTable2(  std::map< std::pair<std::string,std::string>, double > mymap, std::map< std::pair<std::string,std::string>, double > mymap_err, TString type , std::string categoryMode, std::string LowMRcut, std::string HighMRcut, std::string LowRSQcut, std::string HighRSQcut, std::string SoB, std::map<std::string, std::string> func_map, std::vector<std::string> v_func_name);
//MakeTable2( mean_map, "mean", categoryMode, LowMRcut, HighMRcut, LowRSQcut, HighRSQcut, SoB, AICw1, AICw2, AICw3, AICw4, AICw5, AICw6, AICw7);
double FitBias(double* mu_bias_err, TString fname, TString f1, TString f2 , std::string outDir, bool _status, std::string fitFunc);
double crystalball_function(double *x, double *par);
double doublecrystalball_function(double *x, double *par);
double doubletailcrystalball_function(double *x, double *par);

#endif
