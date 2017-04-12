//C++ INCLUDES
#include <iostream>
#include <string>
//ROOT INCLUDES
//LOCAL INCLUDES
#include "CombineHelper.hh"
#include "CommandLineInput.hh"

int main ( int argc, char** argv )
{
  //getting lists of root files to scale 
  std::string dataCard = ParseCommandLine( argc, argv, "-dataCard=" );
  if ( dataCard == "" )
    {
      std::cerr << "[ERROR]: Please provide a valid dataCard" << std::endl;
      std::cout << "[INFOR]: options are:\n --dataCard=<your_dataCard>\n";
      return -1;
    }
  std::cout << "test1: " << CreateCombineCommand( dataCard ) << std::endl;
  CreateSignalScan( dataCard, 2, 3, 4 );
  //CreateSignalScan();
  std::cout << GetCurrentDir() << std::endl;
  return 0;
};
