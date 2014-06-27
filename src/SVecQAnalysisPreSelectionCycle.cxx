// $Id: SVecQAnalysisPreSelectionCycle.cxx,v 1.10 2012/12/07 14:21:51 peiffer Exp $

#include <iostream>

using namespace std;

#include "include/SVecQAnalysisPreSelectionCycle.h"
#include "include/SVecQAnalysisHists.h"


ClassImp( SVecQAnalysisPreSelectionCycle );

SVecQAnalysisPreSelectionCycle::SVecQAnalysisPreSelectionCycle()
   : AnalysisCycle() {

  // constructor, declare additional variables that should be 
  // obtained from the steering-xml file
  
  DeclareProperty( "GenLepton_Selection", m_GenLepton_Selection );


  // set the integrated luminosity per bin for the lumi-yield control plots
  SetIntLumiPerBin(500.);

}

SVecQAnalysisPreSelectionCycle::~SVecQAnalysisPreSelectionCycle() 
{
  // destructor
}

void SVecQAnalysisPreSelectionCycle::BeginCycle() throw( SError ) 
{
  // Start of the job, general set-up and definition of 
  // objects are done here

  // Important: first call BeginCycle of base class
  AnalysisCycle::BeginCycle();

  return;

}

void SVecQAnalysisPreSelectionCycle::EndCycle() throw( SError ) 
{
  // clean-up, info messages and final calculations after the analysis

  
  // call the base cycle class for all standard methods
  AnalysisCycle::EndCycle();

  return;

}

void SVecQAnalysisPreSelectionCycle::BeginInputData( const SInputData& id ) throw( SError ) 
{
  // declaration of histograms and selections.
  // AnalysisCyle expects Selections and HistCollections to be registered here.
  // Their memory will be released in AnalysisCycle::EndInputData.

  // Important: first call BeginInputData of base class
  AnalysisCycle::BeginInputData( id );

  // -------------------- set up the selections ---------------------------

  Selection* preselection = new Selection("preselection");
  //preselection->addSelectionModule(new NJetSelection(2));//at least two jets

  int NLepton_max = 100;
  int NLepton_min = 0;

  if(m_GenLepton_Selection=="1Lepton"){
    NLepton_max = 1;
    NLepton_min = 1;
  }
  else if(m_GenLepton_Selection=="2Lepton"){  
    NLepton_max = 2;
    NLepton_min = 2;
  }
  else if(m_GenLepton_Selection=="3Lepton"){  
    NLepton_max = 100;
    NLepton_min = 3;
  }
  else if(m_GenLepton_Selection=="0Lepton"){
    NLepton_max = 0;
    NLepton_min = 0;
    //preselection->addSelectionModule(new GenTopTag());
    preselection->addSelectionModule(new NCMSTopTagSelection(1,10000));	
 }
  else
    cerr<<"No existing Lepton Selection choosen"<<" "<<" "<< NLepton_max<<" "<<NLepton_min<<endl;
/*	
  NLepton_max = 1;
  NLepton_min = 1;
*/
  //cout<<NLepton_max<<" "<<NLepton_min<<endl;

  preselection->addSelectionModule(new GenLeptonSelection(NLepton_min, NLepton_max,2.5,40));

  RegisterSelection(preselection);



 

  // ---------------- set up the histogram collections --------------------

  // histograms without any cuts
 
  InitHistos();

}

void SVecQAnalysisPreSelectionCycle::EndInputData( const SInputData& id ) throw( SError ) 
{
  AnalysisCycle::EndInputData( id );
}

void SVecQAnalysisPreSelectionCycle::BeginInputFile( const SInputData& id ) throw( SError ) 
{
  // Connect all variables from the Ntuple file with the ones needed for the analysis
  // The variables are commonly stored in the BaseCycleContaincer

  // important: call to base function to connect all variables to Ntuples from the input tree
  AnalysisCycle::BeginInputFile( id );
}

void SVecQAnalysisPreSelectionCycle::ExecuteEvent( const SInputData& id, Double_t weight) throw( SError ) 
{
  // this is the most important part: here the full analysis happens
  // user should implement selections, filling of histograms and results

  // first step: call Execute event of base class to perform basic consistency checks
  // also, the good-run selection is performed there and the calculator is reset
  AnalysisCycle::ExecuteEvent( id, weight );

  // get the histogram collections. NOTE: this could be done more performant by making
  // all thse BaseHists* vairables private member variables of SVecQAnalysisPreSelectionCycle and
  // setting them in BeginInputData. Then, there is no need here to call GetHistColletion ...


  EventCalc* calc = EventCalc::Instance();
  BaseCycleContainer* bcc = calc->GetBaseCycleContainer();



  Cleaner cleaner;
  static Selection* preselection = GetSelection("preselection");

  
  if(bcc->muons) cleaner.MuonCleaner_noIso(40,2.1);
  if(bcc->electrons) cleaner.ElectronCleaner_noIso(40,2.4);
  if(bcc->jets) cleaner.JetLeptonSubtractor(m_corrector,false);
  if(!bcc->isRealData && bcc->jets) cleaner.JetEnergyResolutionShifter();
  if(bcc->jets) cleaner.JetCleaner(50,2.4,true);
  
  

  if(!preselection->passSelection())  throw SError( SError::SkipEvent );

  //cout<<"got through the event"<<endl;
  
  WriteOutputTree();

  //cout<<"wrote the event"<<endl;

  return;
  
}


