//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Mar 16 04:17:31 2017 by ROOT version 6.02/05
// from TTree HggRazor/Info on selected razor inclusive events
// found on file: /afs/cern.ch/user/s/sixie/eos/cms/store/group/phys_susy/razor/Run2Analysis/HggRazor/jobs/HggRazor_SMS-TChiWH_HToGG_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.Job206Of223_675_250.root
//////////////////////////////////////////////////////////

#ifndef HggTree_h
#define HggTree_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include <vector>

class HggTree {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Float_t         genMetPt;
   Float_t         N2Pt;
   Float_t         N2Eta;
   Float_t         N2Phi;
   Float_t         N2Mass;
   Float_t         N3Pt;
   Float_t         N3Eta;
   Float_t         N3Phi;
   Float_t         N3Mass;
   Float_t         HPt;
   Float_t         HEta;
   Float_t         HPhi;
   Float_t         HMass;
   Float_t         ZPt;
   Float_t         ZEta;
   Float_t         ZPhi;
   Float_t         ZMass;
   Float_t         N1FromN2Pt;
   Float_t         N1FromN2Eta;
   Float_t         N1FromN2Phi;
   Float_t         N1FromN2Mass;
   Float_t         N1FromN3Pt;
   Float_t         N1FromN3Eta;
   Float_t         N1FromN3Phi;
   Float_t         N1FromN3Mass;
   Float_t         weight;
   Float_t         pileupWeight;
   Float_t         pileupWeightUp;
   Float_t         pileupWeightDown;
   Float_t         triggerEffWeight;
   Float_t         triggerEffSFWeight;
   Float_t         photonEffSF;
   Float_t         ISRSystWeightUp;
   Float_t         ISRSystWeightDown;
   Int_t           NISRJets;
   Float_t         ptISR;
   Float_t         btagCorrFactor;
   Float_t         sf_btagUp;
   Float_t         sf_btagDown;
   Float_t         sf_bmistagUp;
   Float_t         sf_bmistagDown;
   Float_t         sf_facScaleUp;
   Float_t         sf_facScaleDown;
   Float_t         sf_renScaleUp;
   Float_t         sf_renScaleDown;
   Float_t         sf_facRenScaleUp;
   Float_t         sf_facRenScaleDown;
   std::vector<float>   *pdfWeights;
   std::vector<float>   *sf_pdf;
   Bool_t          Flag_HBHENoiseFilter;
   Bool_t          Flag_HBHEIsoNoiseFilter;
   Bool_t          Flag_badChargedCandidateFilter;
   Bool_t          Flag_badMuonFilter;
   Bool_t          Flag_badGlobalMuonFilter;
   Bool_t          Flag_duplicateMuonFilter;
   Bool_t          Flag_CSCTightHaloFilter;
   Bool_t          Flag_hcalLaserEventFilter;
   Bool_t          Flag_EcalDeadCellTriggerPrimitiveFilter;
   Bool_t          Flag_goodVertices;
   Bool_t          Flag_trackingFailureFilter;
   Bool_t          Flag_eeBadScFilter;
   Bool_t          Flag_ecalLaserCorrFilter;
   Bool_t          Flag_trkPOGFilters;
   Bool_t          Flag_trkPOG_manystripclus53X;
   Bool_t          Flag_trkPOG_toomanystripclus53X;
   Bool_t          Flag_trkPOG_logErrorTooManyClusters;
   Bool_t          Flag_METFilters;
   Bool_t          Flag_hasEcalGainSwitch;
   UInt_t          run;
   UInt_t          lumi;
   UInt_t          event;
   Bool_t          passedDiphotonTrigger;
   UInt_t          NPU;
   UInt_t          nPV;
   Int_t           nLooseBTaggedJets;
   Int_t           nMediumBTaggedJets;
   Int_t           nLooseMuons;
   Int_t           nTightMuons;
   Int_t           nLooseElectrons;
   Int_t           nTightElectrons;
   Int_t           nTightTaus;
   Float_t         MR;
   Float_t         MR_JESUp;
   Float_t         MR_JESDown;
   Float_t         Rsq;
   Float_t         Rsq_JESUp;
   Float_t         Rsq_JESDown;
   Float_t         t1Rsq;
   Float_t         t1Rsq_JESUp;
   Float_t         t1Rsq_JESDown;
   Float_t         genMetRsq;
   Float_t         MET;
   Float_t         MET_JESUp;
   Float_t         MET_JESDown;
   Float_t         t1MET;
   Float_t         t1MET_JESUp;
   Float_t         t1MET_JESDown;
   Float_t         HT;
   Int_t           nSelectedPhotons;
   Float_t         mGammaGamma;
   Float_t         pTGammaGamma;
   Float_t         mGammaGammaSC;
   Float_t         pTGammaGammaSC;
   Float_t         sigmaMoverM;
   Int_t           box;
   Float_t         pho1E;
   Float_t         pho1Pt;
   Float_t         pho1Eta;
   Float_t         pho1Phi;
   Float_t         pho1SC_E;
   Float_t         pho1SC_Pt;
   Float_t         pho1SC_Eta;
   Float_t         pho1SC_Phi;
   Float_t         pho1SigmaIetaIeta;
   Float_t         pho1R9;
   Float_t         pho1HoverE;
   Float_t         pho1sumChargedHadronPt;
   Float_t         pho1sumNeutralHadronEt;
   Float_t         pho1sumPhotonEt;
   Float_t         pho1sigmaEOverE;
   Bool_t          pho1passEleVeto;
   Bool_t          pho1passIso;
   Int_t           pho1MotherID;
   Float_t         pho2E;
   Float_t         pho2Pt;
   Float_t         pho2Eta;
   Float_t         pho2Phi;
   Float_t         pho2SC_E;
   Float_t         pho2SC_Pt;
   Float_t         pho2SC_Eta;
   Float_t         pho2SC_Phi;
   Float_t         pho2SigmaIetaIeta;
   Float_t         pho2R9;
   Float_t         pho2HoverE;
   Float_t         pho2sumChargedHadronPt;
   Float_t         pho2sumNeutralHadronEt;
   Float_t         pho2sumPhotonEt;
   Float_t         pho2sigmaEOverE;
   Bool_t          pho2passEleVeto;
   Bool_t          pho2passIso;
   Int_t           pho2MotherID;
   Float_t         mbbZ;
   Float_t         mbbH;
   Float_t         mbbZ_L;
   Float_t         mbbH_L;
   Int_t           n_Jets;
   Float_t         jet_E[50];   //[n_Jets]
   Float_t         jet_Pt[50];   //[n_Jets]
   Float_t         jet_Eta[50];   //[n_Jets]
   Float_t         jet_Phi[50];   //[n_Jets]
   Bool_t          jetIsCSVL[50];   //[n_Jets]
   Bool_t          jetIsCSVM[50];   //[n_Jets]
   Bool_t          jetIsCSVT[50];   //[n_Jets]
   Int_t           n_Jets_JESUp;
   Int_t           n_Jets_JESDown;
   Bool_t          HLTDecision[500];
   Int_t           nGenParticle;
   Int_t           gParticleMotherId[500];   //[nGenParticle]
   Int_t           gParticleMotherIndex[500];   //[nGenParticle]
   Int_t           gParticleId[500];   //[nGenParticle]
   Int_t           gParticleStatus[500];   //[nGenParticle]
   Float_t         gParticleE[500];   //[nGenParticle]
   Float_t         gParticlePt[500];   //[nGenParticle]
   Float_t         gParticlePhi[500];   //[nGenParticle]
   Float_t         gParticleEta[500];   //[nGenParticle]
   Int_t           mChi;
   Int_t           mLSP;

   // List of branches
   TBranch        *b_genMetPt;   //!
   TBranch        *b_N2Pt;   //!
   TBranch        *b_N2Eta;   //!
   TBranch        *b_N2Phi;   //!
   TBranch        *b_N2Mass;   //!
   TBranch        *b_N3Pt;   //!
   TBranch        *b_N3Eta;   //!
   TBranch        *b_N3Phi;   //!
   TBranch        *b_N3Mass;   //!
   TBranch        *b_HPt;   //!
   TBranch        *b_HEta;   //!
   TBranch        *b_HPhi;   //!
   TBranch        *b_HMass;   //!
   TBranch        *b_ZPt;   //!
   TBranch        *b_ZEta;   //!
   TBranch        *b_ZPhi;   //!
   TBranch        *b_ZMass;   //!
   TBranch        *b_N1FromN2Pt;   //!
   TBranch        *b_N1FromN2Eta;   //!
   TBranch        *b_N1FromN2Phi;   //!
   TBranch        *b_N1FromN2Mass;   //!
   TBranch        *b_N1FromN3Pt;   //!
   TBranch        *b_N1FromN3Eta;   //!
   TBranch        *b_N1FromN3Phi;   //!
   TBranch        *b_N1FromN3Mass;   //!
   TBranch        *b_weight;   //!
   TBranch        *b_pileupWeight;   //!
   TBranch        *b_pileupWeightUp;   //!
   TBranch        *b_pileupWeightDown;   //!
   TBranch        *b_triggerEffWeight;   //!
   TBranch        *b_triggerEffSFWeight;   //!
   TBranch        *b_photonEffSF;   //!
   TBranch        *b_ISRSystWeightUp;   //!
   TBranch        *b_ISRSystWeightDown;   //!
   TBranch        *b_NISRJets;   //!
   TBranch        *b_ptISR;   //!
   TBranch        *b_btagCorrFactor;   //!
   TBranch        *b_sf_btagUp;   //!
   TBranch        *b_sf_btagDown;   //!
   TBranch        *b_sf_bmistagUp;   //!
   TBranch        *b_sf_bmistagDown;   //!
   TBranch        *b_sf_facScaleUp;   //!
   TBranch        *b_sf_facScaleDown;   //!
   TBranch        *b_sf_renScaleUp;   //!
   TBranch        *b_sf_renScaleDown;   //!
   TBranch        *b_sf_facRenScaleUp;   //!
   TBranch        *b_sf_facRenScaleDown;   //!
   TBranch        *b_pdfWeights;   //!
   TBranch        *b_sf_pdf;   //!
   TBranch        *b_Flag_HBHENoiseFilter;   //!
   TBranch        *b_Flag_HBHEIsoNoiseFilter;   //!
   TBranch        *b_Flag_badChargedCandidateFilter;   //!
   TBranch        *b_Flag_badMuonFilter;   //!
   TBranch        *b_Flag_badGlobalMuonFilter;   //!
   TBranch        *b_Flag_duplicateMuonFilter;   //!
   TBranch        *b_Flag_CSCTightHaloFilter;   //!
   TBranch        *b_Flag_hcalLaserEventFilter;   //!
   TBranch        *b_Flag_EcalDeadCellTriggerPrimitiveFilter;   //!
   TBranch        *b_Flag_goodVertices;   //!
   TBranch        *b_Flag_trackingFailureFilter;   //!
   TBranch        *b_Flag_eeBadScFilter;   //!
   TBranch        *b_Flag_ecalLaserCorrFilter;   //!
   TBranch        *b_Flag_trkPOGFilters;   //!
   TBranch        *b_Flag_trkPOG_manystripclus53X;   //!
   TBranch        *b_Flag_trkPOG_toomanystripclus53X;   //!
   TBranch        *b_Flag_trkPOG_logErrorTooManyClusters;   //!
   TBranch        *b_Flag_METFilters;   //!
   TBranch        *b_Flag_hasEcalGainSwitch;   //!
   TBranch        *b_run;   //!
   TBranch        *b_lumi;   //!
   TBranch        *b_event;   //!
   TBranch        *b_passedDiphotonTrigger;   //!
   TBranch        *b_npu;   //!
   TBranch        *b_nPV;   //!
   TBranch        *b_nLooseBTaggedJets;   //!
   TBranch        *b_nMediumBTaggedJets;   //!
   TBranch        *b_nLooseMuons;   //!
   TBranch        *b_nTightMuons;   //!
   TBranch        *b_nLooseElectrons;   //!
   TBranch        *b_nTightElectrons;   //!
   TBranch        *b_nTightTaus;   //!
   TBranch        *b_MR;   //!
   TBranch        *b_MR_JESUp;   //!
   TBranch        *b_MR_JESDown;   //!
   TBranch        *b_Rsq;   //!
   TBranch        *b_Rsq_JESUp;   //!
   TBranch        *b_Rsq_JESDown;   //!
   TBranch        *b_t1Rsq;   //!
   TBranch        *b_t1Rsq_JESUp;   //!
   TBranch        *b_t1Rsq_JESDown;   //!
   TBranch        *b_genMetRsq;   //!
   TBranch        *b_MET;   //!
   TBranch        *b_MET_JESUp;   //!
   TBranch        *b_MET_JESDown;   //!
   TBranch        *b_t1MET;   //!
   TBranch        *b_t1MET_JESUp;   //!
   TBranch        *b_t1MET_JESDown;   //!
   TBranch        *b_HT;   //!
   TBranch        *b_nSelectedPhotons;   //!
   TBranch        *b_mGammaGamma;   //!
   TBranch        *b_pTGammaGamma;   //!
   TBranch        *b_mGammaGammaSC;   //!
   TBranch        *b_pTGammaGammaSC;   //!
   TBranch        *b_sigmaMoverM;   //!
   TBranch        *b_box;   //!
   TBranch        *b_pho1E;   //!
   TBranch        *b_pho1Pt;   //!
   TBranch        *b_pho1Eta;   //!
   TBranch        *b_pho1Phi;   //!
   TBranch        *b_pho1SC_E;   //!
   TBranch        *b_pho1SC_Pt;   //!
   TBranch        *b_pho1SC_Eta;   //!
   TBranch        *b_pho1SC_Phi;   //!
   TBranch        *b_pho1SigmaIetaIeta;   //!
   TBranch        *b_pho1R9;   //!
   TBranch        *b_pho1HoverE;   //!
   TBranch        *b_pho1sumChargedHadronPt;   //!
   TBranch        *b_pho1sumNeutralHadronEt;   //!
   TBranch        *b_pho1sumPhotonEt;   //!
   TBranch        *b_pho1sigmaEOverE;   //!
   TBranch        *b_pho1passEleVeto;   //!
   TBranch        *b_pho1passIso;   //!
   TBranch        *b_pho1MotherID;   //!
   TBranch        *b_pho2E;   //!
   TBranch        *b_pho2Pt;   //!
   TBranch        *b_pho2Eta;   //!
   TBranch        *b_pho2Phi;   //!
   TBranch        *b_pho2SC_E;   //!
   TBranch        *b_pho2SC_Pt;   //!
   TBranch        *b_pho2SC_Eta;   //!
   TBranch        *b_pho2SC_Phi;   //!
   TBranch        *b_pho2SigmaIetaIeta;   //!
   TBranch        *b_pho2R9;   //!
   TBranch        *b_pho2HoverE;   //!
   TBranch        *b_pho2sumChargedHadronPt;   //!
   TBranch        *b_pho2sumNeutralHadronEt;   //!
   TBranch        *b_pho2sumPhotonEt;   //!
   TBranch        *b_pho2sigmaEOverE;   //!
   TBranch        *b_pho2passEleVeto;   //!
   TBranch        *b_pho2passIso;   //!
   TBranch        *b_pho2MotherID;   //!
   TBranch        *b_mbbZ;   //!
   TBranch        *b_mbbH;   //!
   TBranch        *b_mbbZ_L;   //!
   TBranch        *b_mbbH_L;   //!
   TBranch        *b_n_Jets;   //!
   TBranch        *b_jet_E;   //!
   TBranch        *b_jet_Pt;   //!
   TBranch        *b_jet_Eta;   //!
   TBranch        *b_jet_Phi;   //!
   TBranch        *b_jetIsCSVL;   //!
   TBranch        *b_jetIsCSVM;   //!
   TBranch        *b_jetIsCSVT;   //!
   TBranch        *b_n_Jets_JESUp;   //!
   TBranch        *b_n_Jets_JESDown;   //!
   TBranch        *b_HLTDecision;   //!
   TBranch        *b_nGenParticle;   //!
   TBranch        *b_gParticleMotherId;   //!
   TBranch        *b_gParticleMotherIndex;   //!
   TBranch        *b_gParticleId;   //!
   TBranch        *b_gParticleStatus;   //!
   TBranch        *b_gParticleE;   //!
   TBranch        *b_gParticlePt;   //!
   TBranch        *b_gParticlePhi;   //!
   TBranch        *b_gParticleEta;   //!
   TBranch        *b_mChi;   //!
   TBranch        *b_mLSP;   //!

   HggTree(TTree *tree=0);
   virtual ~HggTree();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef HggTree_cxx
HggTree::HggTree(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/afs/cern.ch/user/s/sixie/eos/cms/store/group/phys_susy/razor/Run2Analysis/HggRazor/jobs/HggRazor_SMS-TChiWH_HToGG_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.Job206Of223_675_250.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("/afs/cern.ch/user/s/sixie/eos/cms/store/group/phys_susy/razor/Run2Analysis/HggRazor/jobs/HggRazor_SMS-TChiWH_HToGG_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.Job206Of223_675_250.root");
      }
      f->GetObject("HggRazor",tree);

   }
   Init(tree);
}

HggTree::~HggTree()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t HggTree::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t HggTree::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void HggTree::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   pdfWeights = 0;
   sf_pdf = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("genMetPt", &genMetPt, &b_genMetPt);
   fChain->SetBranchAddress("N2Pt", &N2Pt, &b_N2Pt);
   fChain->SetBranchAddress("N2Eta", &N2Eta, &b_N2Eta);
   fChain->SetBranchAddress("N2Phi", &N2Phi, &b_N2Phi);
   fChain->SetBranchAddress("N2Mass", &N2Mass, &b_N2Mass);
   fChain->SetBranchAddress("N3Pt", &N3Pt, &b_N3Pt);
   fChain->SetBranchAddress("N3Eta", &N3Eta, &b_N3Eta);
   fChain->SetBranchAddress("N3Phi", &N3Phi, &b_N3Phi);
   fChain->SetBranchAddress("N3Mass", &N3Mass, &b_N3Mass);
   fChain->SetBranchAddress("HPt", &HPt, &b_HPt);
   fChain->SetBranchAddress("HEta", &HEta, &b_HEta);
   fChain->SetBranchAddress("HPhi", &HPhi, &b_HPhi);
   fChain->SetBranchAddress("HMass", &HMass, &b_HMass);
   fChain->SetBranchAddress("ZPt", &ZPt, &b_ZPt);
   fChain->SetBranchAddress("ZEta", &ZEta, &b_ZEta);
   fChain->SetBranchAddress("ZPhi", &ZPhi, &b_ZPhi);
   fChain->SetBranchAddress("ZMass", &ZMass, &b_ZMass);
   fChain->SetBranchAddress("N1FromN2Pt", &N1FromN2Pt, &b_N1FromN2Pt);
   fChain->SetBranchAddress("N1FromN2Eta", &N1FromN2Eta, &b_N1FromN2Eta);
   fChain->SetBranchAddress("N1FromN2Phi", &N1FromN2Phi, &b_N1FromN2Phi);
   fChain->SetBranchAddress("N1FromN2Mass", &N1FromN2Mass, &b_N1FromN2Mass);
   fChain->SetBranchAddress("N1FromN3Pt", &N1FromN3Pt, &b_N1FromN3Pt);
   fChain->SetBranchAddress("N1FromN3Eta", &N1FromN3Eta, &b_N1FromN3Eta);
   fChain->SetBranchAddress("N1FromN3Phi", &N1FromN3Phi, &b_N1FromN3Phi);
   fChain->SetBranchAddress("N1FromN3Mass", &N1FromN3Mass, &b_N1FromN3Mass);
   fChain->SetBranchAddress("weight", &weight, &b_weight);
   fChain->SetBranchAddress("pileupWeight", &pileupWeight, &b_pileupWeight);
   fChain->SetBranchAddress("pileupWeightUp", &pileupWeightUp, &b_pileupWeightUp);
   fChain->SetBranchAddress("pileupWeightDown", &pileupWeightDown, &b_pileupWeightDown);
   fChain->SetBranchAddress("triggerEffWeight", &triggerEffWeight, &b_triggerEffWeight);
   fChain->SetBranchAddress("triggerEffSFWeight", &triggerEffSFWeight, &b_triggerEffSFWeight);
   fChain->SetBranchAddress("photonEffSF", &photonEffSF, &b_photonEffSF);
   fChain->SetBranchAddress("ISRSystWeightUp", &ISRSystWeightUp, &b_ISRSystWeightUp);
   fChain->SetBranchAddress("ISRSystWeightDown", &ISRSystWeightDown, &b_ISRSystWeightDown);
   fChain->SetBranchAddress("NISRJets", &NISRJets, &b_NISRJets);
   fChain->SetBranchAddress("ptISR", &ptISR, &b_ptISR);
   fChain->SetBranchAddress("btagCorrFactor", &btagCorrFactor, &b_btagCorrFactor);
   fChain->SetBranchAddress("sf_btagUp", &sf_btagUp, &b_sf_btagUp);
   fChain->SetBranchAddress("sf_btagDown", &sf_btagDown, &b_sf_btagDown);
   fChain->SetBranchAddress("sf_bmistagUp", &sf_bmistagUp, &b_sf_bmistagUp);
   fChain->SetBranchAddress("sf_bmistagDown", &sf_bmistagDown, &b_sf_bmistagDown);
   fChain->SetBranchAddress("sf_facScaleUp", &sf_facScaleUp, &b_sf_facScaleUp);
   fChain->SetBranchAddress("sf_facScaleDown", &sf_facScaleDown, &b_sf_facScaleDown);
   fChain->SetBranchAddress("sf_renScaleUp", &sf_renScaleUp, &b_sf_renScaleUp);
   fChain->SetBranchAddress("sf_renScaleDown", &sf_renScaleDown, &b_sf_renScaleDown);
   fChain->SetBranchAddress("sf_facRenScaleUp", &sf_facRenScaleUp, &b_sf_facRenScaleUp);
   fChain->SetBranchAddress("sf_facRenScaleDown", &sf_facRenScaleDown, &b_sf_facRenScaleDown);
   fChain->SetBranchAddress("pdfWeights", &pdfWeights, &b_pdfWeights);
   fChain->SetBranchAddress("sf_pdf", &sf_pdf, &b_sf_pdf);
   fChain->SetBranchAddress("Flag_HBHENoiseFilter", &Flag_HBHENoiseFilter, &b_Flag_HBHENoiseFilter);
   fChain->SetBranchAddress("Flag_HBHEIsoNoiseFilter", &Flag_HBHEIsoNoiseFilter, &b_Flag_HBHEIsoNoiseFilter);
   fChain->SetBranchAddress("Flag_badChargedCandidateFilter", &Flag_badChargedCandidateFilter, &b_Flag_badChargedCandidateFilter);
   fChain->SetBranchAddress("Flag_badMuonFilter", &Flag_badMuonFilter, &b_Flag_badMuonFilter);
   fChain->SetBranchAddress("Flag_badGlobalMuonFilter", &Flag_badGlobalMuonFilter, &b_Flag_badGlobalMuonFilter);
   fChain->SetBranchAddress("Flag_duplicateMuonFilter", &Flag_duplicateMuonFilter, &b_Flag_duplicateMuonFilter);
   fChain->SetBranchAddress("Flag_CSCTightHaloFilter", &Flag_CSCTightHaloFilter, &b_Flag_CSCTightHaloFilter);
   fChain->SetBranchAddress("Flag_hcalLaserEventFilter", &Flag_hcalLaserEventFilter, &b_Flag_hcalLaserEventFilter);
   fChain->SetBranchAddress("Flag_EcalDeadCellTriggerPrimitiveFilter", &Flag_EcalDeadCellTriggerPrimitiveFilter, &b_Flag_EcalDeadCellTriggerPrimitiveFilter);
   fChain->SetBranchAddress("Flag_goodVertices", &Flag_goodVertices, &b_Flag_goodVertices);
   fChain->SetBranchAddress("Flag_trackingFailureFilter", &Flag_trackingFailureFilter, &b_Flag_trackingFailureFilter);
   fChain->SetBranchAddress("Flag_eeBadScFilter", &Flag_eeBadScFilter, &b_Flag_eeBadScFilter);
   fChain->SetBranchAddress("Flag_ecalLaserCorrFilter", &Flag_ecalLaserCorrFilter, &b_Flag_ecalLaserCorrFilter);
   fChain->SetBranchAddress("Flag_trkPOGFilters", &Flag_trkPOGFilters, &b_Flag_trkPOGFilters);
   fChain->SetBranchAddress("Flag_trkPOG_manystripclus53X", &Flag_trkPOG_manystripclus53X, &b_Flag_trkPOG_manystripclus53X);
   fChain->SetBranchAddress("Flag_trkPOG_toomanystripclus53X", &Flag_trkPOG_toomanystripclus53X, &b_Flag_trkPOG_toomanystripclus53X);
   fChain->SetBranchAddress("Flag_trkPOG_logErrorTooManyClusters", &Flag_trkPOG_logErrorTooManyClusters, &b_Flag_trkPOG_logErrorTooManyClusters);
   fChain->SetBranchAddress("Flag_METFilters", &Flag_METFilters, &b_Flag_METFilters);
   fChain->SetBranchAddress("Flag_hasEcalGainSwitch", &Flag_hasEcalGainSwitch, &b_Flag_hasEcalGainSwitch);
   fChain->SetBranchAddress("run", &run, &b_run);
   fChain->SetBranchAddress("lumi", &lumi, &b_lumi);
   fChain->SetBranchAddress("event", &event, &b_event);
   fChain->SetBranchAddress("passedDiphotonTrigger", &passedDiphotonTrigger, &b_passedDiphotonTrigger);
   fChain->SetBranchAddress("NPU", &NPU, &b_npu);
   fChain->SetBranchAddress("nPV", &nPV, &b_nPV);
   fChain->SetBranchAddress("nLooseBTaggedJets", &nLooseBTaggedJets, &b_nLooseBTaggedJets);
   fChain->SetBranchAddress("nMediumBTaggedJets", &nMediumBTaggedJets, &b_nMediumBTaggedJets);
   fChain->SetBranchAddress("nLooseMuons", &nLooseMuons, &b_nLooseMuons);
   fChain->SetBranchAddress("nTightMuons", &nTightMuons, &b_nTightMuons);
   fChain->SetBranchAddress("nLooseElectrons", &nLooseElectrons, &b_nLooseElectrons);
   fChain->SetBranchAddress("nTightElectrons", &nTightElectrons, &b_nTightElectrons);
   fChain->SetBranchAddress("nTightTaus", &nTightTaus, &b_nTightTaus);
   fChain->SetBranchAddress("MR", &MR, &b_MR);
   fChain->SetBranchAddress("MR_JESUp", &MR_JESUp, &b_MR_JESUp);
   fChain->SetBranchAddress("MR_JESDown", &MR_JESDown, &b_MR_JESDown);
   fChain->SetBranchAddress("Rsq", &Rsq, &b_Rsq);
   fChain->SetBranchAddress("Rsq_JESUp", &Rsq_JESUp, &b_Rsq_JESUp);
   fChain->SetBranchAddress("Rsq_JESDown", &Rsq_JESDown, &b_Rsq_JESDown);
   fChain->SetBranchAddress("t1Rsq", &t1Rsq, &b_t1Rsq);
   fChain->SetBranchAddress("t1Rsq_JESUp", &t1Rsq_JESUp, &b_t1Rsq_JESUp);
   fChain->SetBranchAddress("t1Rsq_JESDown", &t1Rsq_JESDown, &b_t1Rsq_JESDown);
   fChain->SetBranchAddress("genMetRsq", &genMetRsq, &b_genMetRsq);
   fChain->SetBranchAddress("MET", &MET, &b_MET);
   fChain->SetBranchAddress("MET_JESUp", &MET_JESUp, &b_MET_JESUp);
   fChain->SetBranchAddress("MET_JESDown", &MET_JESDown, &b_MET_JESDown);
   fChain->SetBranchAddress("t1MET", &t1MET, &b_t1MET);
   fChain->SetBranchAddress("t1MET_JESUp", &t1MET_JESUp, &b_t1MET_JESUp);
   fChain->SetBranchAddress("t1MET_JESDown", &t1MET_JESDown, &b_t1MET_JESDown);
   fChain->SetBranchAddress("HT", &HT, &b_HT);
   fChain->SetBranchAddress("nSelectedPhotons", &nSelectedPhotons, &b_nSelectedPhotons);
   fChain->SetBranchAddress("mGammaGamma", &mGammaGamma, &b_mGammaGamma);
   fChain->SetBranchAddress("pTGammaGamma", &pTGammaGamma, &b_pTGammaGamma);
   fChain->SetBranchAddress("mGammaGammaSC", &mGammaGammaSC, &b_mGammaGammaSC);
   fChain->SetBranchAddress("pTGammaGammaSC", &pTGammaGammaSC, &b_pTGammaGammaSC);
   fChain->SetBranchAddress("sigmaMoverM", &sigmaMoverM, &b_sigmaMoverM);
   fChain->SetBranchAddress("box", &box, &b_box);
   fChain->SetBranchAddress("pho1E", &pho1E, &b_pho1E);
   fChain->SetBranchAddress("pho1Pt", &pho1Pt, &b_pho1Pt);
   fChain->SetBranchAddress("pho1Eta", &pho1Eta, &b_pho1Eta);
   fChain->SetBranchAddress("pho1Phi", &pho1Phi, &b_pho1Phi);
   fChain->SetBranchAddress("pho1SC_E", &pho1SC_E, &b_pho1SC_E);
   fChain->SetBranchAddress("pho1SC_Pt", &pho1SC_Pt, &b_pho1SC_Pt);
   fChain->SetBranchAddress("pho1SC_Eta", &pho1SC_Eta, &b_pho1SC_Eta);
   fChain->SetBranchAddress("pho1SC_Phi", &pho1SC_Phi, &b_pho1SC_Phi);
   fChain->SetBranchAddress("pho1SigmaIetaIeta", &pho1SigmaIetaIeta, &b_pho1SigmaIetaIeta);
   fChain->SetBranchAddress("pho1R9", &pho1R9, &b_pho1R9);
   fChain->SetBranchAddress("pho1HoverE", &pho1HoverE, &b_pho1HoverE);
   fChain->SetBranchAddress("pho1sumChargedHadronPt", &pho1sumChargedHadronPt, &b_pho1sumChargedHadronPt);
   fChain->SetBranchAddress("pho1sumNeutralHadronEt", &pho1sumNeutralHadronEt, &b_pho1sumNeutralHadronEt);
   fChain->SetBranchAddress("pho1sumPhotonEt", &pho1sumPhotonEt, &b_pho1sumPhotonEt);
   fChain->SetBranchAddress("pho1sigmaEOverE", &pho1sigmaEOverE, &b_pho1sigmaEOverE);
   fChain->SetBranchAddress("pho1passEleVeto", &pho1passEleVeto, &b_pho1passEleVeto);
   fChain->SetBranchAddress("pho1passIso", &pho1passIso, &b_pho1passIso);
   fChain->SetBranchAddress("pho1MotherID", &pho1MotherID, &b_pho1MotherID);
   fChain->SetBranchAddress("pho2E", &pho2E, &b_pho2E);
   fChain->SetBranchAddress("pho2Pt", &pho2Pt, &b_pho2Pt);
   fChain->SetBranchAddress("pho2Eta", &pho2Eta, &b_pho2Eta);
   fChain->SetBranchAddress("pho2Phi", &pho2Phi, &b_pho2Phi);
   fChain->SetBranchAddress("pho2SC_E", &pho2SC_E, &b_pho2SC_E);
   fChain->SetBranchAddress("pho2SC_Pt", &pho2SC_Pt, &b_pho2SC_Pt);
   fChain->SetBranchAddress("pho2SC_Eta", &pho2SC_Eta, &b_pho2SC_Eta);
   fChain->SetBranchAddress("pho2SC_Phi", &pho2SC_Phi, &b_pho2SC_Phi);
   fChain->SetBranchAddress("pho2SigmaIetaIeta", &pho2SigmaIetaIeta, &b_pho2SigmaIetaIeta);
   fChain->SetBranchAddress("pho2R9", &pho2R9, &b_pho2R9);
   fChain->SetBranchAddress("pho2HoverE", &pho2HoverE, &b_pho2HoverE);
   fChain->SetBranchAddress("pho2sumChargedHadronPt", &pho2sumChargedHadronPt, &b_pho2sumChargedHadronPt);
   fChain->SetBranchAddress("pho2sumNeutralHadronEt", &pho2sumNeutralHadronEt, &b_pho2sumNeutralHadronEt);
   fChain->SetBranchAddress("pho2sumPhotonEt", &pho2sumPhotonEt, &b_pho2sumPhotonEt);
   fChain->SetBranchAddress("pho2sigmaEOverE", &pho2sigmaEOverE, &b_pho2sigmaEOverE);
   fChain->SetBranchAddress("pho2passEleVeto", &pho2passEleVeto, &b_pho2passEleVeto);
   fChain->SetBranchAddress("pho2passIso", &pho2passIso, &b_pho2passIso);
   fChain->SetBranchAddress("pho2MotherID", &pho2MotherID, &b_pho2MotherID);
   fChain->SetBranchAddress("mbbZ", &mbbZ, &b_mbbZ);
   fChain->SetBranchAddress("mbbH", &mbbH, &b_mbbH);
   fChain->SetBranchAddress("mbbZ_L", &mbbZ_L, &b_mbbZ_L);
   fChain->SetBranchAddress("mbbH_L", &mbbH_L, &b_mbbH_L);
   fChain->SetBranchAddress("n_Jets", &n_Jets, &b_n_Jets);
   fChain->SetBranchAddress("jet_E", jet_E, &b_jet_E);
   fChain->SetBranchAddress("jet_Pt", jet_Pt, &b_jet_Pt);
   fChain->SetBranchAddress("jet_Eta", jet_Eta, &b_jet_Eta);
   fChain->SetBranchAddress("jet_Phi", jet_Phi, &b_jet_Phi);
   fChain->SetBranchAddress("jetIsCSVL", jetIsCSVL, &b_jetIsCSVL);
   fChain->SetBranchAddress("jetIsCSVM", jetIsCSVM, &b_jetIsCSVM);
   fChain->SetBranchAddress("jetIsCSVT", jetIsCSVT, &b_jetIsCSVT);
   fChain->SetBranchAddress("n_Jets_JESUp", &n_Jets_JESUp, &b_n_Jets_JESUp);
   fChain->SetBranchAddress("n_Jets_JESDown", &n_Jets_JESDown, &b_n_Jets_JESDown);
   fChain->SetBranchAddress("HLTDecision", HLTDecision, &b_HLTDecision);
   fChain->SetBranchAddress("nGenParticle", &nGenParticle, &b_nGenParticle);
   fChain->SetBranchAddress("gParticleMotherId", gParticleMotherId, &b_gParticleMotherId);
   fChain->SetBranchAddress("gParticleMotherIndex", gParticleMotherIndex, &b_gParticleMotherIndex);
   fChain->SetBranchAddress("gParticleId", gParticleId, &b_gParticleId);
   fChain->SetBranchAddress("gParticleStatus", gParticleStatus, &b_gParticleStatus);
   fChain->SetBranchAddress("gParticleE", gParticleE, &b_gParticleE);
   fChain->SetBranchAddress("gParticlePt", gParticlePt, &b_gParticlePt);
   fChain->SetBranchAddress("gParticlePhi", gParticlePhi, &b_gParticlePhi);
   fChain->SetBranchAddress("gParticleEta", gParticleEta, &b_gParticleEta);
   fChain->SetBranchAddress("mChi", &mChi, &b_mChi);
   fChain->SetBranchAddress("mLSP", &mLSP, &b_mLSP);
   Notify();
}

Bool_t HggTree::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void HggTree::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t HggTree::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef HggTree_cxx
