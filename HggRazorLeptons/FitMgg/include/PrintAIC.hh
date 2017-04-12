#ifndef PrintAIC_HH
#define PrintAIC_HH
//C++ INCLUDES
#include <map>
#include <vector>
//ROOT INCLUDES
//ROOFIT INCLUDES
#include <RooWorkspace.h>
#include <RooPlot.h>

//LOCAL INCLUDES

void PrintAICTable(std::string category, std::string LowMRcut, std::string HighMRcut, std::string LowRSQcut, std::string HighRSQcut, std::map<std::string, double> delta_aic_map, std::map<std::string, double> delta_aic_map_2,std::map<std::string, double> delta_aic_map_3, std::map<std::string, double> aic_weight_map, std::map<std::string, double> aic_weight_map_2, std::map<std::string, double> aic_weight_map_3, RooWorkspace *w[], std::map< std::string, double> fitStatus_1_map , std::map< std::string, double> fitStatus_2_map , std::map<std::string, double> fitStatus_3_map , std::map<std::string, double> fitStatus_4_map);
void PlotSidebandFit(std::string MRcut,std::string RSQcut, RooWorkspace *w[]);

#endif
