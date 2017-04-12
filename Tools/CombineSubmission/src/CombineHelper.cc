//C++ INCLUDES
#include <iostream>
#include <string>
#include <sstream>
#include <unistd.h>
//ROOT INCLUDES
//LOCAL INCLUDES
#include "CombineHelper.hh"

std::string CreateCombineCommand( std::string dataCard, std::string outputName,
                                  double singlePoint, int fork, int ntoys, int iterations )
{
  std::stringstream ss;
  ss << "./combine " << dataCard << " -M HybridNew --freq --fork "
     << fork << " -T " << ntoys << " --clsAcc 0 -n " << outputName << " --saveHybridResult --saveToys -s -1 -i "
     << iterations << " --singlePoint " << singlePoint;
  
  return ss.str();
};

void CreateSignalScan( std::string dataCard, double min, double max, int npoints )
{
  int bS = dataCard.find_last_of('/') + 1;
  int lengthS = dataCard.find(".txt") - bS;
  std::string dir = dataCard.substr( bS, lengthS );
  std::cout << "dir: " << dir << std::endl;
  dir = "mkdir " + dir;
  system( dir.c_str() );
  double step = (max - min)/(double)npoints;
  for ( int i  = 0; i <= npoints; i++ )
    {
      std::stringstream ss;
      ss << "_siglePoint_" << min + step*i;
      std::string command = CreateCombineCommand( dataCard, ss.str(), min + step*i, 1, 1000, 1 );
      system( command.c_str() );
    }
  
};

std::string GetCurrentDir()
{
  char cwd[1024];
  getcwd( cwd, sizeof(cwd) );
  std::string str( cwd );
  return str;
}
