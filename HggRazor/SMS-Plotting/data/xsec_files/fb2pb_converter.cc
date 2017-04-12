#include <iostream>
#include <fstream>

int main( )
{
  std::ifstream ifs( "xsec_TChiWH_RazorEW_Format.txt", std::ifstream::in );
  double mass, xsec, xsecUn;
  if ( ifs.is_open() )
    {
      while ( ifs.good() )
	{
	  ifs >> mass >> xsec >> xsecUn;
	  if ( ifs.eof() ) break;
	  std::cout << mass << " "  << xsec/1000. << " " << xsecUn/1000. << std::endl;
	}
    }
  else
    {
      std::cout << "[ERROR] unable to open file; quitting" << std::endl;
    }
  return 0;
}
