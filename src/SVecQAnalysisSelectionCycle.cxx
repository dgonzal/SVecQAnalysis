// $Id: SVecQAnalysisSelectionCycle.cxx,v 1.10 2012/12/07 14:21:51 peiffer Exp $

#include <iostream>

using namespace std;

#include "include/SVecQAnalysisSelectionCycle.h"
#include "include/SVecQAnalysisHists.h"

#include "include/GenZt.h"

//#include "JetCorrectorParameters.h"



#include "SFrameAnalysis/include/EventHists.h"
#include "SFrameAnalysis/include/JetHists.h"
#include "SFrameAnalysis/include/MuonHists.h"
#include "SFrameAnalysis/include/ElectronHists.h"
#include "include/RecoHists.h"

#include "include/GenParticleHists.h"
#include "include/GenJetsHists.h"


#include "SFrameAnalysis/include/SelectionModules.h"
#include "include/SVecQ_SelectionModules.h"



ClassImp( SVecQAnalysisSelectionCycle );

SVecQAnalysisSelectionCycle::SVecQAnalysisSelectionCycle()
   : AnalysisCycle() {

  // constructor, declare additional variables that should be 
  // obtained from the steering-xml file
  
  DeclareProperty("Lepton_Selection", m_Lepton_Selection );

  // set the integrated luminosity per bin for the lumi-yield control plots
  SetIntLumiPerBin(500.);

}

SVecQAnalysisSelectionCycle::~SVecQAnalysisSelectionCycle() 
{
  // destructor
}

void SVecQAnalysisSelectionCycle::BeginCycle() throw( SError ) 
{
  // Start of the job, general set-up and definition of 
  // objects are done here

  // Important: first call BeginCycle of base class
  AnalysisCycle::BeginCycle();

  return;

}

void SVecQAnalysisSelectionCycle::EndCycle() throw( SError ) 
{
  // clean-up, info messages and final calculations after the analysis

  
  // call the base cycle class for all standard methods
  AnalysisCycle::EndCycle();

  return;

}

void SVecQAnalysisSelectionCycle::BeginInputData( const SInputData& id ) throw( SError ) 
{
  // declaration of histograms and selections.
  // AnalysisCyle expects Selections and HistCollections to be registered here.
  // Their memory will be released in AnalysisCycle::EndInputData.

  // Important: first call BeginInputData of base class
  AnalysisCycle::BeginInputData( id );

  // -------------------- set up the selections ---------------------------


  Selection* HTSel = new Selection("HTSel");
  //HTSel->addSelectionModule(new METCut(50,999999));
  if( m_Lepton_Selection=="2Lepton"){
    HTSel->addSelectionModule(new METCut(150,999999));
    HTSel->addSelectionModule(new HTCut(200));
    HTSel->addSelectionModule(new HTlepCut(200,999999));
  }

  Selection* NJetSel = new Selection("NJetSel");
  if( m_Lepton_Selection=="2Lepton")
    NJetSel->addSelectionModule(new NJetSelection(2,int_infinity(),50));
  if( m_Lepton_Selection=="1Lepton")
    NJetSel->addSelectionModule(new NJetSelection(3,int_infinity(),50));

  if( m_Lepton_Selection=="2Lepton" || m_Lepton_Selection=="0Lepton" || m_Lepton_Selection=="1Lepton"){
    NJetSel->addSelectionModule(new NJetSelection(1,int_infinity(),150));
    //NJetSel->addSelectionModule(new TwoDCut());
    //NJetSel->addSelectionModule(new NPrimaryVertexSelection(1)); //at least one good PV
  }


  Selection* MuonSel = new Selection("MuonSel");
  if( m_Lepton_Selection=="2Lepton"|| m_Lepton_Selection=="3Lepton"){
    MuonSel->addSelectionModule(new NMuonSelection(2,1000,30));
    MuonSel->addSelectionModule(new NMuonSelection(2,2,20));
    MuonSel->addSelectionModule(new NMuonSelection(1,2,45));
    MuonSel->addSelectionModule(new relIsoMu(0.15));
  }

  Selection* EleSel = new Selection("EleSel");
  if( m_Lepton_Selection=="2Lepton"|| m_Lepton_Selection=="3Lepton"){
    EleSel->addSelectionModule(new NElectronSelection(2,1000,30));
    EleSel->addSelectionModule(new NElectronSelection(2,2,20));
    EleSel->addSelectionModule(new NElectronSelection(1,2,45));
    //EleSel->addSelectionModule(new TriggerSelection("HLT_Ele30_CaloIdVT_TrkIdT_PFNoPUJet100_PFNoPUJet25_v"));
  }

  Selection* Muon1Sel = new Selection("Muon1Sel");
  if( m_Lepton_Selection=="2Lepton") Muon1Sel->addSelectionModule(new NMuonSelection(1,1,20));

  Selection* Ele1Sel = new Selection("Ele1Sel");
  if( m_Lepton_Selection=="2Lepton") Ele1Sel->addSelectionModule(new NElectronSelection(1,1,20));

  Selection* cmsTopTagSel = new Selection("cmsTopTagSel");
  cmsTopTagSel->addSelectionModule(new NCMSTopTagSelection(1,1));

  Selection* bTagSel = new Selection("bTagSel");
  bTagSel->addSelectionModule(new NBTagSelection(1, 1, e_CSVM));

  Selection* nsubjettiness = new Selection("nsubjettiness");
  //nsubjettiness->addSelectionModule(new );

  
  RegisterSelection(HTSel);
  RegisterSelection(NJetSel);
  RegisterSelection(MuonSel);
  RegisterSelection(EleSel);
  RegisterSelection(Muon1Sel);
  RegisterSelection(Ele1Sel);
  RegisterSelection(bTagSel);
  RegisterSelection(cmsTopTagSel);
  RegisterSelection(nsubjettiness);

  // ---------------- set up the histogram collections --------------------

  
  RegisterHistCollection( new JetHists("Jets") );
  RegisterHistCollection( new EventHists("Event") );
  RegisterHistCollection( new MuonHists("Muon") );
  RegisterHistCollection( new ElectronHists("Electron") );
  RegisterHistCollection( new RecoHists("RecoZt") );
 
  //Histograms with CMS Top Tag
  RegisterHistCollection( new JetHists("cmsTopTag_Jets") );
  RegisterHistCollection( new EventHists("cmsTopTag_Event") );
  RegisterHistCollection( new MuonHists("cmsTopTag_Muon") );
  RegisterHistCollection( new ElectronHists("cmsTopTag_Electron") );
  RegisterHistCollection( new RecoHists("cmsTopTag_RecoZt") );

  //Histograms with b-Tag
  RegisterHistCollection( new JetHists("bTag_Jets") );
  RegisterHistCollection( new EventHists("bTag_Event") );
  RegisterHistCollection( new MuonHists("bTag_Muon") );
  RegisterHistCollection( new ElectronHists("bTag_Electron") );
  RegisterHistCollection( new RecoHists("bTag_RecoZt") );

  //Histograms with N-Subjettiness
  RegisterHistCollection( new JetHists("nsubjettiness_Jets") );
  RegisterHistCollection( new EventHists("nsubjettiness_Event") );
  RegisterHistCollection( new MuonHists("nsubjettiness_Muon") );
  RegisterHistCollection( new ElectronHists("nsubjettiness_Electron") );
  RegisterHistCollection( new RecoHists("nsubjettiness_RecoZt") );

  //Generator Histograms
  RegisterHistCollection( new GenJetsHists("genjets"));
  RegisterHistCollection( new GenParticleHists("gen_lquarks"  ,GenParticleHists::l));
  RegisterHistCollection( new GenParticleHists("gen_bquarks"  ,GenParticleHists::b));
  RegisterHistCollection( new GenParticleHists("gen_topquarks",GenParticleHists::top));
  RegisterHistCollection( new GenParticleHists("gen_tprime"   ,GenParticleHists::tprime));
  RegisterHistCollection( new GenParticleHists("gen_electrons",GenParticleHists::electron));
  RegisterHistCollection( new GenParticleHists("gen_muons"    ,GenParticleHists::muon));
  RegisterHistCollection( new GenParticleHists("gen_neutrinos",GenParticleHists::neutrino));
  RegisterHistCollection( new GenParticleHists("gen_zboson"   ,GenParticleHists::Z));
  RegisterHistCollection( new GenParticleHists("gen_wboson"   ,GenParticleHists::W));
  RegisterHistCollection( new GenParticleHists("gen_virW"     ,GenParticleHists::VirW));
  RegisterHistCollection( new GenParticleHists("gen_gluon"    ,GenParticleHists::gluon));

  InitHistos();

}

void SVecQAnalysisSelectionCycle::EndInputData( const SInputData& id ) throw( SError ) 
{
  AnalysisCycle::EndInputData( id );
}

void SVecQAnalysisSelectionCycle::BeginInputFile( const SInputData& id ) throw( SError ) 
{
  // Connect all variables from the Ntuple file with the ones needed for the analysis
  // The variables are commonly stored in the BaseCycleContaincer

  // important: call to base function to connect all variables to Ntuples from the input tree
  AnalysisCycle::BeginInputFile( id );
}

void SVecQAnalysisSelectionCycle::ExecuteEvent( const SInputData& id, Double_t weight) throw( SError ) 
{
  // this is the most important part: here the full analysis happens
  // user should implement selections, filling of histograms and results

  // first step: call Execute event of base class to perform basic consistency checks
  // also, the good-run selection is performed there and the calculator is reset
  AnalysisCycle::ExecuteEvent( id, weight );

  // get the histogram collections. NOTE: this could be done more performant by making
  // all thse BaseHists* vairables private member variables of SVecQAnalysisSelectionCycle and
  // setting them in BeginInputData. Then, there is no need here to call GetHistColletion ...

  static Selection* HTSel = GetSelection("HTSel");
  static Selection* NJetSel = GetSelection("NJetSel");
  static Selection* MuonSel = GetSelection("MuonSel");
  static Selection* EleSel = GetSelection("EleSel");
  static Selection* Muon1Sel = GetSelection("Muon1Sel");
  static Selection* Ele1Sel = GetSelection("Ele1Sel");
  static Selection* cmsTopTagSel = GetSelection("cmsTopTagSel");
  static Selection* bTagSel = GetSelection("bTagSel");
  static Selection* nsubjettiness = GetSelection("nsubjettiness");

  if(!HTSel->passSelection())  throw SError( SError::SkipEvent );
  if(!NJetSel->passSelection())  throw SError( SError::SkipEvent );
  if(!MuonSel->passSelection() && !EleSel->passSelection())  throw SError( SError::SkipEvent );
  if( m_Lepton_Selection=="2Lepton") 
    if(Muon1Sel->passSelection() || Ele1Sel->passSelection())  throw SError( SError::SkipEvent );



  EventCalc* calc = EventCalc::Instance();
  BaseCycleContainer* bcc = calc->GetBaseCycleContainer();
  
 

  BaseHists* Jets = GetHistCollection("Jets");
  BaseHists* Event = GetHistCollection("Event");
  BaseHists* Muon = GetHistCollection("Muon");
  BaseHists* Electron = GetHistCollection("Electron");
  BaseHists* RecoZt = GetHistCollection("RecoZt");
  
  BaseHists* bTag_Jets = GetHistCollection("bTag_Jets");
  BaseHists* bTag_Event = GetHistCollection("bTag_Event");
  BaseHists* bTag_Muon = GetHistCollection("bTag_Muon");
  BaseHists* bTag_Electron = GetHistCollection("bTag_Electron");
  BaseHists* bTag_RecoZt = GetHistCollection("bTag_RecoZt");

  BaseHists* cmsTopTag_Jets = GetHistCollection("cmsTopTag_Jets");
  BaseHists* cmsTopTag_Event = GetHistCollection("cmsTopTag_Event");
  BaseHists* cmsTopTag_Muon = GetHistCollection("cmsTopTag_Muon");
  BaseHists* cmsTopTag_Electron = GetHistCollection("cmsTopTag_Electron");
  BaseHists* cmsTopTag_RecoZt = GetHistCollection("cmsTopTag_RecoZt");

  BaseHists* nsubjettiness_Jets = GetHistCollection("nsubjettiness_Jets");
  BaseHists* nsubjettiness_Event = GetHistCollection("nsubjettiness_Event");
  BaseHists* nsubjettiness_Muon = GetHistCollection("nsubjettiness_Muon");
  BaseHists* nsubjettiness_Electron = GetHistCollection("nsubjettiness_Electron");
  BaseHists* nsubjettiness_RecoZt = GetHistCollection("nsubjettiness_RecoZt");

  // start the analysis

  //cout<<m_Lepton_Selection<<endl;
  if( m_Lepton_Selection=="1Lepton")
    calc->Reco_Zt.Fill_1_lep(*bcc->jets,*bcc->muons,*bcc->electrons, bcc->met->v4());
  if( m_Lepton_Selection=="2Lepton")
    calc->Reco_Zt.Fill_2_lep(*bcc->jets,*bcc->muons,*bcc->electrons);
  if( m_Lepton_Selection=="3Lepton")
    calc->Reco_Zt.Fill_3_lep(*bcc->jets,*bcc->muons,*bcc->electrons, bcc->met->v4());
  if( m_Lepton_Selection=="0Lepton")
    calc->Reco_Zt.Fill_had_combi(*bcc->jets, bcc->met);


  RecoZt->Fill();
  Jets->Fill();
  Event->Fill();
  Muon->Fill();
  Electron->Fill();

 if(bTagSel->passSelection()){ 
  bTag_RecoZt->Fill();
  bTag_Jets->Fill();
  bTag_Event->Fill();
  bTag_Muon->Fill();
  bTag_Electron->Fill();
}
 if(cmsTopTagSel->passSelection()){ 
  cmsTopTag_Jets->Fill();
  cmsTopTag_Event->Fill();
  cmsTopTag_Muon->Fill();
  cmsTopTag_Electron->Fill();
  cmsTopTag_RecoZt->Fill();
}
 if(nsubjettiness->passSelection()){ 
  nsubjettiness_RecoZt->Fill();
  nsubjettiness_Jets->Fill();
  nsubjettiness_Event->Fill();
  nsubjettiness_Muon->Fill();
  nsubjettiness_Electron->Fill();
}
  //return;

  if(bcc->isRealData)  throw SError( SError::SkipEvent );
  

  calc->Gen_Zt.identify(bcc);

  BaseHists* genjets   = GetHistCollection("genjets"  );
  BaseHists* gen_lquarks   = GetHistCollection("gen_lquarks"  );
  BaseHists* gen_bquarks   = GetHistCollection("gen_bquarks"  );
  BaseHists* gen_topquarks = GetHistCollection("gen_topquarks");
  BaseHists* gen_tprime    = GetHistCollection("gen_tprime"   );
  BaseHists* gen_electrons = GetHistCollection("gen_electrons");
  BaseHists* gen_muons     = GetHistCollection("gen_muons"    );
  BaseHists* gen_neutrinos = GetHistCollection("gen_neutrinos");
  BaseHists* gen_zboson    = GetHistCollection("gen_zboson"   );
  BaseHists* gen_wboson    = GetHistCollection("gen_wboson"   );   
  BaseHists* gen_virW      = GetHistCollection("gen_virW"     );
  BaseHists* gen_gluon     = GetHistCollection("gen_gluon"    );

  genjets       ->Fill();  
  gen_lquarks   ->Fill();  
  gen_bquarks   ->Fill(); 
  gen_topquarks ->Fill();
  gen_tprime    ->Fill(); 
  gen_electrons ->Fill();
  gen_muons     ->Fill();
  gen_neutrinos ->Fill();
  gen_zboson    ->Fill();
  gen_wboson    ->Fill();
  gen_virW      ->Fill();  
  gen_gluon     ->Fill();  
  
  return;
  
}


