#include <iostream>
#include <vector>
//LOCAL INCLUDES
#include "HggRazorSystematics.hh"

//---------------
//Binning
//---------------
const int nMR = 4;

//highpt
int highpt_nRsq[nMR] = {7,5,3,2};
float  highptMRedges[] = {150.0, 312.5, 625, 1250, 10000};
float  highptRSQedges0[7] = {0,0.027,0.052,0.077,0.102,0.127,5.0};
float  highptRSQedges1[5] = {0,0.022,0.047,0.072,5.0};
float  highptRSQedges2[3] = {0,0.021,5.0};
float  highptRSQedges3[2] = {0,5.0};

//highres
int highres_nRsq[nMR] = {9,5,3,2};
float  highresMRedges[] = {150,237.5,475,950,10000};
float  highresRSQedges0[9] = {0,0.028,0.053,0.078,0.103,0.128,0.153,0.178,5.0};
float  highresRSQedges1[5] = {0,0.035,0.06,0.085,5.0};
float  highresRSQedges2[3] = {0,0.018,5.0};
float  highresRSQedges3[2] = {0,5.0};

//lowres
int lowres_nRsq[nMR] = {7,6,3,2};
float  lowresMRedges[] = {150,200,400,800,10000};
float  lowresRSQedges0[7] = {0,0.049,0.074,0.099,0.124,0.149,5.0};
float  lowresRSQedges1[6] = {0,0.023,0.048,0.073,0.098,5.0};
float  lowresRSQedges2[3] = {0,0.02,5.0};
float  lowresRSQedges3[2] = {0,5.0};

//----------------
//Static Variables
//----------------
float HggRazorSystematics::Lumi = 2300.0;

void SetMapBinning( std::map<std::pair<float, float>, std::vector<float>>& myMap, TString category = "highpt" );

int main()
{
  //-----------------
  //Selection TString
  //-----------------
  TString categoryMode = "highres";
  
  TString cut = "mGammaGamma > 103. && mGammaGamma < 160. && pho1passIso == 1 && pho2passIso == 1 && pho1passEleVeto == 1 && pho2passEleVeto == 1 && abs(pho1Eta) <1.48 && abs(pho2Eta)<1.48 && (pho1Pt>40||pho2Pt>40)  && pho1Pt> 25. && pho2Pt>25.";
  TString categoryCutString;

  if (categoryMode == "highpt") categoryCutString = " && pTGammaGamma >= 110 ";
  else if (categoryMode == "hzbb") categoryCutString = " && pTGammaGamma < 110 && ( abs(mbbH_L-125.) < 15. || ( abs(mbbH_L-125.) >= 15. && abs(mbbZ_L-91.) < 15 ) )";
  else if (categoryMode == "highres") categoryCutString = " && pTGammaGamma < 110 && abs(mbbH_L-125.) >= 15 && abs(mbbZ_L-91.) >= 15 && sigmaMoverM < 0.0085";
  else if (categoryMode == "lowres") categoryCutString  = " && pTGammaGamma < 110 && abs(mbbH_L-125.) >= 15 && abs(mbbZ_L-91.) >= 15 && sigmaMoverM >= 0.0085 ";
  else if (categoryMode == "inclusive") categoryCutString = "";

  //-----------------------------
  //Map container for the binning
  //-----------------------------
  std::map<std::pair<float, float>, std::vector<float>> binningMap;
  SetMapBinning( binningMap, categoryMode );
  
  //---------------------------
  //Create HggSystematic object
  //---------------------------
  HggRazorSystematics* hggSys = new HggRazorSystematics();

  return 0;
}


void SetMapBinning( std::map<std::pair<float, float>, std::vector<float>>& myMap, TString category )
{
  if ( category == "highpt" )
    {
      for ( int i = 0; i < nMR; i++ )
	{
	  std::vector<float> vect;
	  for ( int j = 0; j < highpt_nRsq[i]; j++ )
	    {
	      switch (i)
		{
		case 0:
		  vect.push_back(highptRSQedges0[j]);
		  break;
		case 1:
		  vect.push_back(highptRSQedges1[j]);
		  break;
		case 2:
		  vect.push_back(highptRSQedges2[j]);
		  break;
		case 3:
		  vect.push_back(highptRSQedges3[j]);
		  break;
		default:
		  std::cerr << "MR bins exceeds number of defined Rsq binning!! Do nothing" << std::endl;
		  break;
		}
	    }
	  std::pair<float, float> mypair = std::make_pair( highptMRedges[i], highptMRedges[i+1] );
	  std::cout << mypair.first << " " << mypair.second << std::endl;
	  myMap[mypair] = vect;
	}
    }
  else if ( category == "hzbb" )
    {
      std::vector<float> vect;
      vect.push_back( 0.0 );
      vect.push_back( 5.0 );
      std::pair<float, float> mypair = std::make_pair( 150., 10000. );
      std::cout << mypair.first << " " << mypair.second << std::endl;
      myMap[mypair] = vect;
    }
  else if ( category == "highres" )
    {
      for ( int i = 0; i < nMR; i++ )
	{
	  std::vector<float> vect;
	  for ( int j = 0; j < highres_nRsq[i]; j++ )
	    {
	      switch (i)
		{
		case 0:
		  vect.push_back(highresRSQedges0[j]);
		  break;
		case 1:
		  vect.push_back(highresRSQedges1[j]);
		  break;
		case 2:
		  vect.push_back(highresRSQedges2[j]);
		  break;
		case 3:
		  vect.push_back(highresRSQedges3[j]);
		  break;
		default:
		  std::cerr << "MR bins exceeds number of defined Rsq binning!! Do nothing" << std::endl;
		  break;
		}
	    }
	  std::pair<float, float> mypair = std::make_pair( highresMRedges[i], highresMRedges[i+1] );
	  std::cout << mypair.first << " " << mypair.second << std::endl;
	  myMap[mypair] = vect;
	}
    }
  else if ( category == "lowres" )
    {
      for ( int i = 0; i < nMR; i++ )
	{
	  std::vector<float> vect;
	  for ( int j = 0; j < lowres_nRsq[i]; j++ )
	    {
	      switch (i)
		{
		case 0:
		  vect.push_back(lowresRSQedges0[j]);
		  break;
		case 1:
		  vect.push_back(lowresRSQedges1[j]);
		  break;
		case 2:
		  vect.push_back(lowresRSQedges2[j]);
		  break;
		case 3:
		  vect.push_back(lowresRSQedges3[j]);
		  break;
		default:
		  std::cerr << "MR bins exceeds number of defined Rsq binning!! Do nothing" << std::endl;
		  break;
		}
	    }
	  std::pair<float, float> mypair = std::make_pair( lowresMRedges[i], lowresMRedges[i+1] );
	  std::cout << mypair.first << " " << mypair.second << std::endl;
	  myMap[mypair] = vect;
	}
    }
  return;
};
