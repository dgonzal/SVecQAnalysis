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
#include "include/GenParticleHists.h"
#include "include/GenJetsHists.h"


#include "SFrameAnalysis/include/SelectionModules.h"



ClassImp( SVecQAnalysisSelectionCycle );

SVecQAnalysisSelectionCycle::SVecQAnalysisSelectionCycle()
   : AnalysisCycle() {

  // constructor, declare additional variables that should be 
  // obtained from the steering-xml file
  
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



  // ---------------- set up the histogram collections --------------------

  // histograms without any cuts
 
  RegisterHistCollection( new JetHists("Jets") );
  RegisterHistCollection( new EventHists("Event") );
  RegisterHistCollection( new MuonHists("Muon") );
  RegisterHistCollection( new ElectronHists("Electron") );

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

  
  BaseHists* Jets = GetHistCollection("Jets");
  BaseHists* Event = GetHistCollection("Event");
  BaseHists* Muon = GetHistCollection("Muon");
  BaseHists* Electron = GetHistCollection("Electron");
  

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

  // start the analysis

  Jets->Fill();
  Event->Fill();
  Muon->Fill();
  Electron->Fill();

 
  
  return;
  
}


