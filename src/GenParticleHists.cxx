#include "include/GenParticleHists.h"
#include "SFrameTools/include/EventCalc.h"
#include <iostream>

using namespace std;


GenParticleHists::GenParticleHists(const char* name, p_type particle) : BaseHists(name), m_partn(particle)
{
  // named default constructor
   
}

GenParticleHists::~GenParticleHists(){

}

void GenParticleHists::Init()
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
  Book( TH1F( "pt_4"   , "fourth p_{T}", 100, 0 , 600));
  Book( TH1F( "pt_4_ly", "fourth p_{T}", 100, 0 , 600));

  Book( TH1F( "eta", "#eta", 100, -10 , 10));
  Book( TH1F( "eta_ly", "#eta", 100, -10 , 10));
  Book( TH1F( "eta_1"   , "first #eta", 100, -10 , 10));
  Book( TH1F( "eta_1_ly", "first #eta", 100, -10 , 10));
  Book( TH1F( "eta_2"   , "second #eta", 100, -10 , 10));
  Book( TH1F( "eta_2_ly", "second #eta", 100, -10 , 10));
  Book( TH1F( "eta_3"   , "third #eta", 100, -10 , 10));
  Book( TH1F( "eta_3_ly", "third #eta", 100, -10 , 10));
  Book( TH1F( "eta_4"   , "fourth #eta", 100, -10 , 10));
  Book( TH1F( "eta_4_ly", "fourth #eta", 100, -10 , 10));

  Book( TH1F( "phi", "#phi", 100, -4 , 4));
  Book( TH1F( "phi_ly", "#phi", 100, -4 , 4));
  Book( TH1F( "phi_1"   , "first #phi", 100, -4 , 4));
  Book( TH1F( "phi_1_ly", "first #phi", 100, -4 , 4));
  Book( TH1F( "phi_2"   , "second #phi", 100, -4 , 4));
  Book( TH1F( "phi_2_ly", "second #phi", 100, -4 , 4));
  Book( TH1F( "phi_3"   , "third  #phi", 100, -4 , 4));
  Book( TH1F( "phi_3_ly", "third #phi", 100, -4 , 4));
  Book( TH1F( "phi_4"   , "fourth #phi", 100, -4 , 4));
  Book( TH1F( "phi_4_ly", "fourth #phi", 100, -4 , 4));


  Book( TH1F( "mass", "mass", 100, 0 , 1000));
  Book( TH1F( "mass_ly", "mass", 100, 0 , 1000));
  Book( TH1F( "mass_1", "first mass", 100, 0 , 1000));
  Book( TH1F( "mass_1_ly", "first mass", 100, 0 , 1000));
  Book( TH1F( "mass_2", "second mass", 100, 0 , 1000));
  Book( TH1F( "mass_2_ly", "second mass", 100, 0 , 1000));
  Book( TH1F( "mass_3", "third mass", 100, 0 , 1000));
  Book( TH1F( "mass_3_ly", "third mass", 100, 0 , 1000));
  Book( TH1F( "mass_4", "fourth mass", 100, 0 , 1000));
  Book( TH1F( "mass_4_ly", "fourth mass", 100, 0 , 1000));


  Book( TH1F( "energy", "E", 100, 0 , 1000));
  Book( TH1F( "energy_ly", "E", 100, 0 , 1000));
  Book( TH1F( "energy_1"   , "first E", 100, 0 , 1000));
  Book( TH1F( "energy_1_ly", "first E", 100, 0 , 1000));
  Book( TH1F( "energy_2"   , "second E", 100, 0 , 1000));
  Book( TH1F( "energy_2_ly", "second E", 100, 0 , 1000));
  Book( TH1F( "energy_3"   , "third E", 100, 0 , 1000));
  Book( TH1F( "energy_3_ly", "third E", 100, 0 , 1000));
  Book( TH1F( "energy_4"   , "fourth E", 100, 0 , 1000));
  Book( TH1F( "energy_4_ly", "fourth E", 100, 0 , 1000));


  Book( TH1F( "pairmass", "mass(i,j)", 100, 0 , 3000));
  Book( TH1F( "pairmass_ly", "mass(i,j)", 100, 0 , 3000));
  Book( TH1F( "delR", "#Delta R(i,j)", 100, 0 , 20));
  Book( TH1F( "delR_ly", "#Delta R(i,jet)", 100, 0 ,20));

}

void GenParticleHists::Fill()
{
  // fill the histograms


  EventCalc* calc = EventCalc::Instance();
  LuminosityHandler* lumih = calc->GetLumiHandler();

  BaseCycleContainer* bcc = calc->GetBaseCycleContainer();
  
  //GenZt GenParZt= calc->Gen_Zt;
  std::vector<GenParticle> Particle;

  //cout<<"NTop: "<<calc->Gen_Zt.Top().size()<<endl;

  switch(m_partn)
    {
    case l:
      Particle=calc->Gen_Zt.lquarks();
      break;
    case b:
      Particle=calc->Gen_Zt.b();
      break;
    case top:        
      Particle=calc->Gen_Zt.Top();
      break;
    case tprime:      
      Particle=calc->Gen_Zt.Tprime();
      break;
    case electron:   
      Particle=calc->Gen_Zt.electrons();
      break;
    case muon:
      Particle=calc->Gen_Zt.muons();
      break;
    case neutrino:    
      Particle=calc->Gen_Zt.neutrinos();
      break;
    case Z:
      Particle= calc->Gen_Zt.Z();
      break;
    case W:        
      Particle=calc->Gen_Zt.WTop();
      break;   
    case VirW:
      Particle=calc->Gen_Zt.VirW();
      break;
    case gluon:
      Particle=calc->Gen_Zt.gluons();
      break;
    }


  // important: get the event weight
  double weight = calc->GetWeight();
 
  //cout<<weight<<endl;

  int NPart = Particle.size();
  
  Hist("number_part")->Fill(NPart,weight);
  Hist("number_part_ly")->Fill(NPart,weight);


  //cout<< m_partn<<" "<<NPart<<endl;

  //cout<<NPart<<Particle.at(0).pt() <<endl;



  for(int i=0 ; i<NPart; i++){

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
  }

  for(int i =0; i<NPart-1; i++){
    for(int p = 0; p<NPart; p++){
      if(p+i<NPart){ 
	Hist("pairmass")->Fill((Particle.at(p).v4()+Particle.at(p+i).v4()).M(),weight);
	Hist("pairmass_ly")->Fill((Particle.at(p).v4()+Particle.at(p+i).v4()).M(),weight);
	Hist("delR")->Fill(deltaR(Particle.at(p).v4(),Particle.at(p+i).v4()),weight);
	Hist("delR_ly")->Fill(deltaR(Particle.at(p).v4(),Particle.at(p+i).v4()),weight);	
      }
    }
  }

  
  
  
  
}


void GenParticleHists::Finish()
{
 

}

