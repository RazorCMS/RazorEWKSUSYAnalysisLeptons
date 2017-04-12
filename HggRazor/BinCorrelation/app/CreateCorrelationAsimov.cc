#include <iostream>
#include <fstream>

#include <TFile.h>
#include <TDirectoryFile.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TString.h>
#include <RooDataSet.h>
#include "CommandLineInput.hh"

float* GetNbkg( TString fname );


int main( int argc, char** argv)
{
  std::cout << "[INFO]: Initializing program" << std::endl;
  
  float nr_un[19]  = {2.4,2.5,1.9,36.7,14.5,2.3,2.7,2.5,3.1,16.5,2.7,4.4,19.3,4.6,28.3,3.0,10.4,13.5,5.1};
  float smh_un[19] = {1.2,0.9,1.8,21.5,6.8,1.4,4.2,2.4,0.4,24.2,0.6,1.4,16.4,3.1,16.5,0.3,1.2,8.5,2.1};
  float total_un[19];
  
  for ( int i = 0; i < 19; i++ ) total_un[i] = sqrt(nr_un[i]*nr_un[i] + smh_un[i]*smh_un[i]);
  
  std::string inputFile = ParseCommandLine( argc, argv, "-inputFile=" );
  if (  inputFile == "" )
    {
      std::cerr << "[ERROR]: please provide an input file using --inputFile=<path_to_file>" << std::endl;
      return -1;
    }

  std::ifstream ifs( inputFile.c_str(), std::ifstream::in );
  
  TH1F* h_bin[19];
  float nevents[19];
  float mean[19];
  float rms[19];
  float corr[19][19];
  
  for ( int i = 0; i < 19; i++ ) h_bin[i] = new TH1F( Form("bin%d",i), Form("bin%d",i), 100, 0, 100);
  TString ifname;
  if ( ifs.is_open() )
    {
      while ( ifs.good() )
	{
	  ifs >> ifname;
	  if ( ifs.eof() ) break;
	  float* bkg = GetNbkg( ifname );
	  for ( int i = 0; i < 19; i++ )
	    {
	      if( !std::isnan( bkg[i] ) && bkg[i] < 4000.)
		{
		  h_bin[i]->Fill( bkg[i] );
		  nevents[i]++;
		  mean[i] += bkg[i];
		}
	    }
	  
	}
    }
  else
    {
      std::cerr << "[ERROR]: unable to open file" << inputFile << ". Quitting..."<< std::endl;
      return -1;
    }
  ifs.close();

  for ( int i = 0; i < 19; i++ ) mean[i] = mean[i]/nevents[i];
  //-----------------------------------
  //Second iteration to get covariances
  //-----------------------------------
  std::ifstream ifs2( inputFile.c_str(), std::ifstream::in );
  if ( ifs2.is_open() )
    {
      while ( ifs2.good() )
	{
	  ifs2 >> ifname;
	  if ( ifs2.eof() ) break;
	  float* bkg = GetNbkg( ifname );
	  for ( int i = 0; i < 19; i++ )
	    {
	      if( !std::isnan( bkg[i] ) && bkg[i] < 4000.)
		{
		  rms[i] += pow(bkg[i]-mean[i],2)/nevents[i];
		  //if( i == 0 ) std::cout << bkg[i] << std::endl;
		}
	    }

	  for ( int i = 0; i < 19; i++ )
	    {
	      for ( int j = 0; j < 19; j++ )
		{
		  if( (!std::isnan( bkg[i] ) && bkg[i] < 4000.) && (!std::isnan( bkg[j] ) && bkg[j] < 4000.) )
		    {
		      corr[i][j] += (bkg[i]-mean[i])*(bkg[j]-mean[j])/nevents[i];
		    }
		}
	    }
	  
	}
    }
  else
    {
      std::cerr << "[ERROR]: unable to open file" << inputFile << ". Quitting..."<< std::endl;
      return -1;
    }
  ifs2.close();
  
  for( int i = 0; i < 19; i++ ) std::cout << i << " " << nevents[i] << " mean: " << mean[i] << ", rms: " << sqrt(rms[i]) << std::endl;


  TFile* fout = new TFile("histos_correlation.root", "recreate");
  TH2F* hcorr = new TH2F("corr", "corr", 19, 0, 19, 19, 0, 19);
  TH2F* hcov = new TH2F("cov", "cov", 19, 0, 19, 19, 0, 19);
  for( int i = 0; i < 19; i++ )
    {
      for( int j = 0; j < 19; j++ )
	{
	  std::cout << i << "," << j << " corr: " << total_un[i]*total_un[j]*corr[i][j]/(sqrt(rms[i])*sqrt(rms[j])) << std::endl;
	  hcov->SetBinContent(i+1,j+1,total_un[i]*total_un[j]*corr[i][j]/(sqrt(rms[i])*sqrt(rms[j])));
	  hcorr->SetBinContent(i+1,j+1,corr[i][j]/(sqrt(rms[i])*sqrt(rms[j])));
	  //else std::cout << i << "," << j << " corr: " << corr[i][j]/ << std::endl;
	}
    }
  
  h_bin[0]->Write();
  hcorr->Write();
  hcov->Write();
  fout->Close();
  return 0;
}

float* GetNbkg( TString fname )
{
  float* Nbkg = new float[19];
  TFile* fin = new TFile( fname, "read");
  TDirectoryFile* toys = (TDirectoryFile*)fin->Get("toys");
  RooDataSet* data  = (RooDataSet*)toys->Get("toy_asimov");
  //data->Print();
  TH1F* h[19];
  for ( int i = 0; i < 19; i++ )
    {
      h[i]    = (TH1F*)data->createHistogram( Form("mGammaGamma_bin%d",i), 57);
      Nbkg[i] = h[i]->Integral(20,26);//mgg in (122,129) GeV
    }
  delete fin;
  return Nbkg;
}
