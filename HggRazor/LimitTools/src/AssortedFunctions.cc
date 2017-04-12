#include <iostream>

//ROOT INCLUDES
#include <TH1.h>
#include <TF1.h>
#include <TAxis.h>
//LOCAL INCLUDES
#include "AssortedFunctions.hh"

double GetEffSigma( TH1* hist )
{

  TAxis *xaxis = hist->GetXaxis();
  int nb = xaxis->GetNbins();
  if(nb < 10) {
    std::cout << "effsigma: Not a valid histo. nbins = " << nb << std::endl;
    return 0.;
  }
  
  double bwid = xaxis->GetBinWidth(1);
  if(bwid == 0) {
    std::cout << "effsigma: Not a valid histo. bwid = " << bwid << std::endl;
    return 0.;
  }
  double xmax = xaxis->GetXmax();
  double xmin = xaxis->GetXmin();
  double ave = hist->GetMean();
  double rms = hist->GetRMS();

  double total=0.;
  for(int i=0; i<nb+2; i++) {
    total+=hist->GetBinContent(i);
  }
  //   if(total < 100.) {
  //     std::cout << "effsigma: Too few entries " << total << std::endl;
  //     return 0.;
  //   }
  int ierr=0;
  int ismin=999;
  
  double rlim=0.683*total;
  int nrms=rms/(bwid);    // Set scan size to +/- rms
  if ( nrms > nb/10 ) nrms=nb/10; // Could be tuned...

  double widmin=9999999.;
  for( int iscan = -nrms; iscan < nrms+1; iscan++ ) { // Scan window centre
    int ibm    = (ave-xmin)/bwid+1+iscan;
    double x   = (ibm-0.5)*bwid+xmin;
    double xj  = x;
    double xk  = x;
    int jbm    = ibm;
    int kbm    = ibm;
    double bin = hist->GetBinContent(ibm);
    total      = bin;
    for ( int j = 1; j < nb; j++ ){
      if ( jbm < nb )
	{
	  jbm++;
	  xj += bwid;
	  bin = hist->GetBinContent(jbm);
	  total += bin;
	  if ( total > rlim ) break;
	}
      else ierr=1;
      
      if( kbm > 0 )
	{
	  kbm--;
	  xk -= bwid;
	  bin = hist->GetBinContent(kbm);
	  total += bin;
	  if ( total > rlim ) break;
	}
      else ierr=1;
    }
    
    double dxf=(total-rlim)*bwid/bin;//accounting for excess
    double wid=(xj-xk+bwid-dxf)*0.5;
    if(wid < widmin)
      {
	//std::cout << "rms: " << rms << " nRms: " << nrms << " --> min width: " << wid << " , iscan: " << iscan << std::endl;
	widmin=wid;
	ismin=iscan;
      }   
  }
  
  if(ismin == nrms || ismin == -nrms) ierr=3;
  if(ierr != 0)
    {
      std::cout << "effsigma: Error of type " << ierr << std::endl;
      return -1;
    }
  
  return widmin;
  
};

double GetFWHM( TH1* h )
{
  
  double _maxY = h->GetMaximum();
  double bw    = h->GetBinWidth(1);
  double xlow  = h->GetBinLowEdge(1);
  double _maxX = xlow + bw*((double)h->GetMaximumBin() - 1.) + bw*0.50;
  int _maxBin  = h->GetMaximumBin();

  TF1* gaus = new TF1("gaus", "gaus", h->GetBinLowEdge(_maxBin-4), h->GetBinLowEdge(_maxBin+5));
  h->Fit( gaus, "RLQ");
  double fitMax = gaus->GetParameter(0);
  //std::cout << "MAX FIT: " << fitMax << " histoMax: " <<  h->GetBinLowEdge(_maxBin-4) << " " << _maxY << std::endl;
  
  int niter = h->GetNbinsX()/3;
  double lowEnd  = -1;
  double highEnd = -1;
  //--------------
  //High End
  //--------------
  for ( int i = 1; i <= niter; i++ )
    {
      int iBin = _maxBin+i;
      if ( h->GetBinContent( iBin ) < 0.50*fitMax )
	{
	  //std::cout << h->GetBinContent( iBin ) << " "  << h->GetBinContent( iBin-1 ) << " " << h->GetBinCenter( iBin ) << " "  << h->GetBinCenter( iBin-1 ) << std::endl;
	  double slope = (h->GetBinContent( iBin ) - h->GetBinContent( iBin-1 ))/(h->GetBinCenter( iBin )-h->GetBinCenter( iBin-1 ));
	  highEnd = (0.50*fitMax-h->GetBinContent( iBin-1 ))/slope + h->GetBinCenter( iBin-1 );
	  //highEnd = h->GetBinLowEdge( iBin );
	  break;
	}
    }

  //------------------
  //Low End
  //------------------
  for ( int i = 1; i <= niter; i++ )
    {
      int iBin = _maxBin-i;
      if ( h->GetBinContent( iBin ) < 0.50*fitMax )
	{
	  //std::cout << h->GetBinContent( iBin ) << " "  << h->GetBinContent( iBin+1 ) << " " << h->GetBinCenter( iBin ) << " "  << h->GetBinCenter( iBin+1 ) << std::endl;
	  double slope = (h->GetBinContent( iBin+1 ) - h->GetBinContent( iBin ))/(h->GetBinCenter( iBin+1 )-h->GetBinCenter( iBin ));
	  lowEnd = (0.50*fitMax-h->GetBinContent( iBin ))/slope + h->GetBinCenter( iBin );
	  //lowEnd = h->GetBinLowEdge( _maxBin-i );
	  break;
	}
    }
  //std::cout << highEnd << " "  << lowEnd << std::endl;
  return highEnd-lowEnd;
};


double GetBestFitSignalStrength( int n, double* b, double* s, double* obs )
{
  int nsteps = 2e3;
  double mu_steps = 1.0e-2;
  double minNll = 9999999;
  double bestMu = -1;
  for( int i = 0; i < nsteps; i++ )
    {
      double mu = mu_steps*i;
      double nll = 0;
      for( int j = 0; j < n; j++ ) nll += -( obs[j]*std::log(mu*s[j]+b[j]) -(mu*s[j]+b[j]) );
      //std::cout << "mu: " << mu << ", nll: " << nll << std::endl;
      if ( nll < minNll )
	{
	  minNll = nll;
	  bestMu = mu;
	  //std::cout << "mu: " << mu << ", minNll: " << minNll << std::endl;
	}
    }
  return bestMu;
};


double GetQnotTestStatistics( int n, double* b, double* s, double* obs, double mu )
{
  double qnot = 0;
  for( int j = 0; j < n; j++ ) qnot += ( ( obs[j]*std::log(b[j]) - b[j] ) - ( obs[j]*std::log(mu*s[j]+b[j]) -(mu*s[j]+b[j]) ) );
  return -2.*qnot;
};
