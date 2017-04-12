#ifndef MAKE_INVERTED_ANFIT_V2_HH
#define MAKE_INVERTED_ANFIT_V2_HH

//ROOT INCLUDES

#include <TTree.h>
#include <TString.h>
//ROOFIT INCLUDES
#include <RooRealVar.h>
#include <RooWorkspace.h>

TString makeDoubleExp(TString tag, RooRealVar& mgg,RooWorkspace& w);
TString makeSingleExp(TString tag, RooRealVar& mgg,RooWorkspace& w);
TString makeTripleExp(TString tag, RooRealVar& mgg,RooWorkspace& w);
TString makeModExp(TString tag, RooRealVar& mgg,RooWorkspace& w);
TString makeSinglePow(TString tag, RooRealVar& mgg,RooWorkspace& w);
TString makeDoublePow(TString tag, RooRealVar& mgg,RooWorkspace& w);
TString makePoly2(TString tag, RooRealVar& mgg,RooWorkspace& w);
TString makePoly3(TString tag, RooRealVar& mgg,RooWorkspace& w);
TString makePoly4(TString tag, RooRealVar& mgg,RooWorkspace& w);
TString makeGauss( TString tag, RooRealVar& mgg, RooWorkspace& w );
TString makeDoubleGauss( TString tag, RooRealVar& mgg, RooWorkspace& w );

RooWorkspace* makeInvertedANFit(TTree* tree, float forceSigma, bool constrainMu, float forceMu, TString mggName );
RooWorkspace* makeMCFit( TTree* tree, float forceSigma, bool constrainMu, float forceMu, TString mggName );
  
#endif
