#ifndef COMBINEHELPER_HH
#define COMBINEHELPER_HH 1

#include <iostream>
#include <string>
#include <stdlib.h>

std::string CreateCombineCommand( std::string dataCard = "dummy.txt", std::string outputName = "test_combine",
				  double singlePoint = 1.0, int fork = 1, int ntoys = 500 , int iterations = 1 );

void CreateSignalScan( std::string dataCard = "dummy.txt", double min = 0.0, double max = 5.0, int npoints = 50 );
std::string GetCurrentDir();
#endif
