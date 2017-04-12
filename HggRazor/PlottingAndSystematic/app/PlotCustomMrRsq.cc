//C++ INCLUDES
#include <iostream>
#include <map>
//ROOT INCLUDES
#include <TString.h>
#include <TH1D.h>
#include <TFile.h>
//LOCAL INCLUDES
#include "HggAux.hh"
#include "CommandLineInput.hh"
#include "TChainTools.hh"
#include "PlotCosmetics.hh"

#define _debug 1
#define TYPES 4
std::string plots[TYPES] = { "mgg", "ptgg", "mr", "rsq" };
  
int main ( int argc, char* argv[] )
{
  std::cout << "[INFO]: Initializing program" << std::endl;
  std::string inputFile = ParseCommandLine( argc, argv, "-inputFile=" );
  std::string histoMake = ParseCommandLine( argc, argv, "-histoMake=" );
  std::string outDir    = ParseCommandLine( argc, argv, "-outDir=" );
  std::string option    = ParseCommandLine( argc, argv, "-option=" );
  std::string boxName    = ParseCommandLine( argc, argv, "-boxName=" );
  std::string histoName = histoMake;
  if ( inputFile == "" )
    {
      std::cerr << "[ERROR]: Please provide an input file using --inputFile=<your_input_file>" << std::endl;
      return -1;
    }
  std::map< std::string, std::string > mapList;
  FillMapList( mapList, inputFile );
  if ( _debug ) std::cout << "[DEBUG]: map size: " << mapList.size() << std::endl;
  
  TFile* f;
  TH2F* h_mr_rsq;
  TH1D* h;
  TH1D* data;
  TH1D* mc = NULL;
  THStack* stack = new THStack( "hs" , "Hgg Stack " );
  TLegend* leg = new TLegend( 0.7, 0.58, 0.95, 0.89, NULL, "brNDC" );
  
  for( auto& myMap : mapList )
    {
      if ( _debug ) std::cout << "[DEBUG]: first: " << myMap.first << " second: " << myMap.second << std::endl;
    }

  if ( histoMake != "all" )
    {
      //L o o p  o v e r   p r o c e s s e s
      //------------------------------------
      for( const auto& process : Process() )
	{
	  std::string processName = GetProcessString( process );
	  std::cout << "[INFO]: process name: " << processName << std::endl;
	  if ( mapList.find( processName ) == mapList.end() )
	    {
	      std::cout << "[WARNING]: missing process-> " << processName << std::endl;
	      continue;
	    }
	  // R e t r i e v i n g  H i s t o
	  //-------------------------------
	  f = new TFile( mapList[processName].c_str() );
	  if ( histoName == "" || histoName == "MrRsqCustom" )
	    {
	      h_mr_rsq = (TH2F*)f->Get( "mr_rsq_custom" );
	      std::cout << "[INFO]: Number of events (5 fb-1) -> " << h_mr_rsq->Integral() << std::endl;
	      MakeCustomMrRsq( h_mr_rsq, processName );
	    }
	  else if ( histoName == "mgg" )
	    {
	      h = (TH1D*)f->Get( "mgg" );
	      TH1D* h_s = GetStyledHisto( h, process );
	      if ( option == "stack" )
		{
		  if ( process != Process::data )
		    {
		      stack->Add( h_s, "histo" );
		      if ( mc == NULL )
			{
			  mc = new TH1D( *h );
			}
		      else
			{
			  mc->Add( h );
			}
		    }
		  else
		    {
		      data = h_s;
		    }
		  AddLegend( h_s, leg, process );
		}
	    }
	  else if ( histoName == "ptgg" )
	    {
	      h = (TH1D*)f->Get( "ptgg" );
	      TH1D* h_s = GetStyledHisto( h, process );
	      if ( option == "stack" )
		{
		  if ( process != Process::data )
		    {
		      stack->Add( h_s, "histo" );
		      if ( mc == NULL )
			{
			  mc = new TH1D( *h );
			}
		      else
			{
			  mc->Add( h );
			}
		    }
		  else
		    {
		      data = h_s;
		    }
		  AddLegend( h_s, leg, process );
		}
	    }
	  else if ( histoName == "mr" )
	    {
	      h = (TH1D*)f->Get( "mr" );
	      TH1D* h_s = GetStyledHisto( h, process );
	      if ( option == "stack" )
		{
		  if ( process != Process::data )
		    {
		      stack->Add( h_s, "histo" );
		      if ( mc == NULL )
			{
			  mc = new TH1D( *h );
			}
		      else
			{
			  mc->Add( h );
			}
		    }
		  else
		    {
		      data = h_s;
		    }
		  AddLegend( h_s, leg, process );
		}
	    }
	  else if ( histoName == "rsq" )
	    {
	      h = (TH1D*)f->Get( "rsq" );
	      TH1D* h_s = GetStyledHisto( h, process );
	      if ( option == "stack" )
		{
		  if ( process != Process::data )
		    {
		      stack->Add( h_s, "histo" );
		      if ( mc == NULL )
			{
			  mc = new TH1D( *h );
			}
		      else
			{
			  mc->Add( h );
			}
		    }
		  else
		    {
		      data = h_s;
		    }
		  AddLegend( h_s, leg, process );
		}
	    }
	}
      
      if ( outDir != "" )
	{
	  //MakeStackPlot( stack, histoName, outDir + "/" + histoName + "_" + boxName, leg );
	  MakeStackPlot( stack, data, mc, histoName, outDir + "/" + histoName + "_" + boxName, leg );
	}
      else
	{
	  //MakeStackPlot( stack, histoName, histoName + "_" + boxName, leg );
	  MakeStackPlot( stack, data, mc, histoName, histoName + "_" + boxName, leg );
	}
    }
  else
    {
      for ( int i = 0; i < TYPES; i++ )
	{
	  histoName = plots[i];
	  std::cout << "[INFO]: histogram name: " << histoName << std::endl;
	  delete stack;
	  stack = new THStack( "hs" , "Hgg Stack " );
	  delete leg;
	  leg = new TLegend( 0.73, 0.7, 0.93, 0.89, NULL, "brNDC" );
	  //L o o p  o v e r   p r o c e s s e s
	  //------------------------------------
	  for( const auto& process : Process() )
	    {
	      std::string processName = GetProcessString( process );
	      std::cout << "[INFO]: process name: " << processName << std::endl;
	      if ( mapList.find( processName ) == mapList.end() )
		{
		  std::cout << "[WARNING]: missing process-> " << processName << std::endl;
		  continue;
		}
	      // R e t r i e v i n g  H i s t o
	      //-------------------------------
	      f = new TFile( mapList[processName].c_str() );
	      
	      if ( histoName == "" || histoName == "MrRsqCustom" )
		{
		  h_mr_rsq = (TH2F*)f->Get( "mr_rsq_custom" );
		  std::cout << "[INFO]: Number of events (5 fb-1) -> " << h_mr_rsq->Integral() << std::endl;
		  MakeCustomMrRsq( h_mr_rsq, processName );
		}
	      else if ( histoName == "mgg" )
		{
		  h = (TH1D*)f->Get( "mgg" );
		  TH1D* h_s = GetStyledHisto( h, process );
		  if ( process == Process::gammaJet ) h_s->Smooth( 1 );
		  if ( option == "stack" )
		    {
		      stack->Add( h_s, "histo" );
		      AddLegend( h_s, leg, process );
		    }
		}
	      else if ( histoName == "ptgg" )
		{
		  h = (TH1D*)f->Get( "ptgg" );
		  TH1D* h_s = GetStyledHisto( h, process );
		  if ( option == "stack" )
		    {
		      stack->Add( h_s, "histo" );
		      AddLegend( h_s, leg, process );
		    }
		}
	      else if ( histoName == "mr" )
		{
		  h = (TH1D*)f->Get( "mr" );
		  TH1D* h_s = GetStyledHisto( h, process );
		  if ( option == "stack" )
		    {
		      stack->Add( h_s, "histo" );
		      AddLegend( h_s, leg, process );
		    }
		}
	      else if ( histoName == "rsq" )
		{
		  h = (TH1D*)f->Get( "rsq" );
		  TH1D* h_s = GetStyledHisto( h, process );
		  if ( option == "stack" )
		    {
		      stack->Add( h_s, "histo" );
		      AddLegend( h_s, leg, process );
		    }
		}
	    }
	  
	  if ( outDir != "" )
	    {
	  MakeStackPlot( stack, histoName, outDir + "/" + histoName + "_" + boxName, leg );
	    }
	  else
	    {
	      MakeStackPlot( stack, histoName, histoName + "_" + boxName, leg ); 
	    }
	}
    }
  return 0;
}
