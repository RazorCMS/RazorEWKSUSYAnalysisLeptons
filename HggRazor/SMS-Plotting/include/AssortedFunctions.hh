#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <utility>

struct Limit
{
  float obs;
  float q2p5;
  float q16;
  float exp;
  float q84;
  float q97p5;
  float msb;
  float mlsp;
  float xsecL;
  float xsecUn;
  float xsecLExp;
  float xsecLExpUp;
  float xsecLExpDown;
};


void GetLimit(Limit &limit, std::string fname, float ssFactor = 1.0 );
std::pair<float, float> GetMasses(std::string fname);
float GetCrossSectionLimit( float ssLimit, float msb );
float GetCrossSectionUn( float msb );

void FillCrossSectionMap( std::string xsecfname );
