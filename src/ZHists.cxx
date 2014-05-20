#include "include/ZHists.h"
#include "SFrameTools/include/EventCalc.h"
#include <iostream>

using namespace std;


ZHists::ZHists(const char* name) : BaseHists(name)
{
  // named default constructor
   
}

ZHists::~ZHists(){

}

void ZHists::Init()
{
  // missing ET and HT
  Book( TH1F( "number_part", "multiplicity",16,-.5,15.5) );
  Book( TH1F( "number_part_ly", "multiplicity",16,-0.5,15.5) );

  Book( TH1F( "pt", "p_{T}", 100, 0 , 600));
  Book( TH1F( "pt_ly", "p_{T}", 100, 0 , 600));
  Book( TH1F( "pt_1"   , "first p_{T}", 100, 0 , 600));
  Book( TH1F( "pt_1_ly", "first p_{T}", 100, 0 , 600));
  Book( TH1F( "pt_2"   , "second p_{T}", 100, 0 , 600));
  Book( TH1F( "pt_2_ly", "second p_{T}", 100, 0 , 600));
  Book( TH1F( "pt_3"   , "third p_{T}", 100, 0 , 600));
  Book( TH1F( "pt_3_ly", "third p_{T}", 100, 0 , 600));
 
  Book( TH1F( "eta", "#eta", 100, -10 , 10));
  Book( TH1F( "eta_ly", "#eta", 100, -10 , 10));
  Book( TH1F( "eta_1"   , "first #eta", 100, -10 , 10));
  Book( TH1F( "eta_1_ly", "first #eta", 100, -10 , 10));
  Book( TH1F( "eta_2"   , "second #eta", 100, -10 , 10));
  Book( TH1F( "eta_2_ly", "second #eta", 100, -10 , 10));
  Book( TH1F( "eta_3"   , "third #eta", 100, -10 , 10));
  Book( TH1F( "eta_3_ly", "third #eta", 100, -10 , 10));
 
  Book( TH1F( "phi", "#phi", 100, -4 , 4));
  Book( TH1F( "phi_ly", "#phi", 100, -4 , 4));
  Book( TH1F( "phi_1"   , "first #phi", 100, -4 , 4));
  Book( TH1F( "phi_1_ly", "first #phi", 100, -4 , 4));
  Book( TH1F( "phi_2"   , "second #phi", 100, -4 , 4));
  Book( TH1F( "phi_2_ly", "second #phi", 100, -4 , 4));
  Book( TH1F( "phi_3"   , "third  #phi", 100, -4 , 4));
  Book( TH1F( "phi_3_ly", "third #phi", 100, -4 , 4));

  Book( TH1F( "mass", "mass", 100, 0 , 1000));
  Book( TH1F( "mass_ly", "mass", 100, 0 , 1000));
  Book( TH1F( "mass_1", "first mass", 100, 0 , 1000));
  Book( TH1F( "mass_1_ly", "first mass", 100, 0 , 1000));
  Book( TH1F( "mass_2", "second mass", 100, 0 , 1000));
  Book( TH1F( "mass_2_ly", "second mass", 100, 0 , 1000));
  Book( TH1F( "mass_3", "third mass", 100, 0 , 1000));
  Book( TH1F( "mass_3_ly", "third mass", 100, 0 , 1000));

  Book( TH1F( "energy", "E", 100, 0 , 1000));
  Book( TH1F( "energy_ly", "E", 100, 0 , 1000));
  Book( TH1F( "energy_1"   , "first E", 100, 0 , 1000));
  Book( TH1F( "energy_1_ly", "first E", 100, 0 , 1000));
  Book( TH1F( "energy_2"   , "second E", 100, 0 , 1000));
  Book( TH1F( "energy_2_ly", "second E", 100, 0 , 1000));
  Book( TH1F( "energy_3"   , "third E", 100, 0 , 1000));
  Book( TH1F( "energy_3_ly", "third E", 100, 0 , 1000));

}

void ZHists::Fill()
{
  // fill the histograms
  /*

  EventCalc* calc = EventCalc::Instance();
  LuminosityHandler* lumih = calc->GetLumiHandler();

  BaseCycleContainer* bcc = calc->GetBaseCycleContainer();
 
  // important: get the event weight
  double weight = calc->GetWeight();
 
  GenParticle gen = Particle.at(i);
  
  //std::cout<<gen.eta()<<" "<<weight<<std::endl;

  Hist("pt"       )->Fill(gen.pt(),weight);	 
  Hist("pt_ly"    )->Fill(gen.pt(),weight);	 
  Hist("eta"      )->Fill(gen.eta(),weight);	 
  Hist("eta_ly"   )->Fill(gen.eta(),weight);	 
  Hist("phi"      )->Fill(gen.phi(),weight);	 
  Hist("phi_ly"   )->Fill(gen.phi(),weight);	
  Hist("mass"     )->Fill(gen.v4().M(),weight);
  Hist("mass_ly"  )->Fill(gen.v4().M(),weight);
  Hist("energy"   )->Fill(gen.v4().E(),weight);
  Hist("energy_ly")->Fill(gen.v4().E(),weight);

  
  if(i<4){
    
    TString hname = TString::Format("pt_%d", i+1);
    Hist(hname)->Fill(gen.pt(),weight);
    hname = TString::Format("pt_%d_ly", i+1);
    Hist(hname)->Fill(gen.pt(),weight);
    hname = TString::Format("eta_%d", i+1);
    Hist(hname)->Fill(gen.eta(),weight);
    hname = TString::Format("eta_%d_ly", i+1);
    Hist(hname)->Fill(gen.eta(),weight);
    hname = TString::Format("phi_%d", i+1);
    Hist(hname)->Fill(gen.phi(),weight);    
    hname = TString::Format("phi_%d_ly", i+1);	 
    Hist(hname)->Fill(gen.phi(),weight);
    hname = TString::Format("energy_%d", i+1);
    Hist(hname)->Fill(gen.v4().E(),weight);
    hname = TString::Format("energy_%d_ly", i+1);
    Hist(hname)->Fill(gen.v4().E(),weight);
    hname = TString::Format("mass_%d", i+1);
    Hist(hname)->Fill(gen.v4().M(),weight);
    hname = TString::Format("mass_%d_ly", i+1);
    Hist(hname)->Fill(gen.v4().M(),weight);
  }
  */
  
  
}


void ZHists::Finish()
{
 

}

