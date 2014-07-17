#include "include/RecoHists.h"
#include "SFrameTools/include/EventCalc.h"
#include "include/RecoZt.h"

#include <iostream>

using namespace std;


RecoHists::RecoHists(const char* name) : BaseHists(name)
{
  // named default constructor
   
}

RecoHists::~RecoHists(){

}

void RecoHists::Init()
{
  
  
  Book( TH1F( "pt_Z", "p_{T} Z", 100, 0 , 1000));
  Book( TH1F( "pt_Z_ly", "p_{T} Z", 100, 0 , 1000));

  Book( TH1F( "eta_Z", "#eta Z", 100, -10 , 10));
  Book( TH1F( "eta_Z_ly", "#eta Z", 100, -10 , 10));
  
  Book( TH1F( "phi_Z", "#phi Z", 100, -4 , 4));
  Book( TH1F( "phi_Z_ly", "#phi Z", 100, -4 , 4));
  
  Book( TH1F( "mass_Z", "mass Z", 100, 0 , 1000));
  Book( TH1F( "mass_Z_ly", "mass Z", 100, 0 , 1000));
 
  Book( TH1F( "energy_Z", "E Z", 100, 0 , 1500));
  Book( TH1F( "energy_Z_ly", "E Z", 100, 0 , 1500));
  
  Book( TH1F( "pt_t", "p_{T} t", 100, 0 , 1000));
  Book( TH1F( "pt_t_ly", "p_{T} t", 100, 0 , 1000));

  Book( TH1F( "eta_t", "#eta t", 100, -10 , 10));
  Book( TH1F( "eta_t_ly", "#eta t", 100, -10 , 10));
  
  Book( TH1F( "phi_t", "#phi t", 100, -4 , 4));
  Book( TH1F( "phi_t_ly", "#phi t", 100, -4 , 4));
  
  Book( TH1F( "mass_t", "mass t", 100, 0 , 400));
  Book( TH1F( "mass_t_ly", "mass t", 100, 0 , 400));
 
  Book( TH1F( "energy_t", "E t", 100, 200 , 1500));
  Book( TH1F( "energy_t_ly", "E t", 100, 0 , 1500));

  Book( TH1F( "chi2", "chi2", 100, 0 , 1000));
  Book( TH1F( "chi2_ly", "chi2", 100, 0 , 1000));

  Book( TH1F( "pt_tprime", "p_{T} T'", 100, 0 , 1000));
  Book( TH1F( "pt_tprime_ly", "p_{T} T'", 100, 0 , 1000));

  Book( TH1F( "eta_tprime", "#eta T'", 100, -10 , 10));
  Book( TH1F( "eta_tprime_ly", "#eta T'", 100, -10 , 10));
  
  Book( TH1F( "phi_tprime", "#phi T'", 100, -4 , 4));
  Book( TH1F( "phi_tprime_ly", "#phi T'", 100, -4 , 4));
  
  Book( TH1F( "mass_tprime", "mass T'", 100, 0 ,2500));
  Book( TH1F( "mass_tprime_ly", "mass T'", 100, 0 , 2500));
 
  Book( TH1F( "energy_tprime", "E T'", 100, 0 , 1500));
  Book( TH1F( "energy_tprime_ly", "E T'", 100, 0 , 1500));

}

void RecoHists::Fill()
{
  // fill the histograms
 

  EventCalc* calc = EventCalc::Instance();
  LuminosityHandler* lumih = calc->GetLumiHandler();

  BaseCycleContainer* bcc = calc->GetBaseCycleContainer();
 
  // important: get the event weight
  double weight = calc->GetWeight();
  
  RecoZt_hyp RecoHyp= calc->Reco_Zt.get_best_chi2();

  LorentzVector zboson = RecoHyp.Z;

  Hist("pt_Z"       )->Fill(zboson.pt(),weight);	 
  Hist("pt_Z_ly"    )->Fill(zboson.pt(),weight);	 
  Hist("eta_Z"      )->Fill(zboson.eta(),weight);	 
  Hist("eta_Z_ly"   )->Fill(zboson.eta(),weight);	 
  Hist("phi_Z"      )->Fill(zboson.phi(),weight);	 
  Hist("phi_Z_ly"   )->Fill(zboson.phi(),weight);	
  Hist("mass_Z"     )->Fill(zboson.isTimelike()? zboson.M() : sqrt(zboson.M2()),weight);
  Hist("mass_Z_ly"  )->Fill(zboson.isTimelike()? zboson.M() : sqrt(zboson.M2()),weight);
  Hist("energy_Z"   )->Fill(zboson.E(),weight);
  Hist("energy_Z_ly")->Fill(zboson.E(),weight);

  LorentzVector tquark = RecoHyp.t;

  Hist("pt_t"       )->Fill(tquark.pt(),weight);	 
  Hist("pt_t_ly"    )->Fill(tquark.pt(),weight);	 
  Hist("eta_t"      )->Fill(tquark.eta(),weight);	 
  Hist("eta_t_ly"   )->Fill(tquark.eta(),weight);	 
  Hist("phi_t"      )->Fill(tquark.phi(),weight);	 
  Hist("phi_t_ly"   )->Fill(tquark.phi(),weight);	
  Hist("mass_t"     )->Fill(tquark.isTimelike()? tquark.M() : sqrt(tquark.M2()),weight);
  Hist("mass_t_ly"  )->Fill(tquark.isTimelike()? tquark.M() : sqrt(tquark.M2()),weight);
  Hist("energy_t"   )->Fill(tquark.E(),weight);
  Hist("energy_t_ly")->Fill(tquark.E(),weight);
 
 
  double chi2 = (tquark.M()-173)*(tquark.M()-173)*0.02 + (zboson.M()-91)*(zboson.M()-91)*0.1;

  Hist("chi2")->Fill(chi2,weight);
  Hist("chi2_ly")->Fill(chi2,weight);


  LorentzVector tprime = RecoHyp.t+RecoHyp.Z;

  Hist("pt_tprime"       )->Fill(tprime.pt(),weight);	 
  Hist("pt_tprime_ly"    )->Fill(tprime.pt(),weight);	 
  Hist("eta_tprime"      )->Fill(tprime.eta(),weight);	 
  Hist("eta_tprime_ly"   )->Fill(tprime.eta(),weight);	 
  Hist("phi_tprime"      )->Fill(tprime.phi(),weight);	 
  Hist("phi_tprime_ly"   )->Fill(tprime.phi(),weight);	
  Hist("mass_tprime"     )->Fill(tprime.isTimelike()? tprime.M() : sqrt(tprime.M2()),weight);
  Hist("mass_tprime_ly"  )->Fill(tprime.isTimelike()? tprime.M() : sqrt(tprime.M2()),weight);
  Hist("energy_tprime"   )->Fill(tprime.E(),weight);
  Hist("energy_tprime_ly")->Fill(tprime.E(),weight);
  
}


void RecoHists::Finish()
{
 

}

