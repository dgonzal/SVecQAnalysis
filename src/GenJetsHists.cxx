#include "include/GenJetsHists.h"
#include "SFrameTools/include/EventCalc.h"
#include "SFrameTools/include/Objects.h"

#include <iostream>

using namespace std;


GenJetsHists::GenJetsHists(const char* name) : BaseHists(name)
{
  // named default constructor
   
}

GenJetsHists::~GenJetsHists(){

}

void GenJetsHists::Init()
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


  Book( TH1F( "pairmass", "mass(i,j)", 100, 0 , 1500));
  Book( TH1F( "pairmass_ly", "mass(i,j)", 100, 0 , 1500));
  Book( TH1F( "delR", "#Delta R(i,j)", 100, 0 , 20));
  Book( TH1F( "delR_ly", "#Delta R(i,jet)", 100, 0 ,20));


  Book( TH1F( "HT_electron", "H_{T,e}", 100, 0 , 1500));
  Book( TH1F( "HT_electron_ly", "H_{T,e}", 100, 0 , 1500));
  
  Book( TH1F( "HT_muon", "H_{T, #mu}", 100, 0 , 1500));
  Book( TH1F( "HT_muon_ly", "H_{T, #mu}", 100, 0 , 1500));
  
  Book( TH1F( "HT_neutrino", "H_{T, #nu}", 100, 0 , 1500));
  Book( TH1F( "HT_neutrino_ly", "H_{T, #nu}", 100, 0 , 1500));
  
  Book( TH1F( "HT_b", "H_{T, b}", 100, 0 , 1500));
  Book( TH1F( "HT_b_ly", "H_{T, b}", 100, 0 , 1500));
  Book( TH1F( "HT_l", "H_{T, light}", 100, 0 , 1500));
  Book( TH1F( "HT_l_ly", "H_{T, light}", 100, 0 , 1500));
  
  Book( TH1F( "HT_genjets", "H_{T, genjets}", 100, 0 , 1500));
  Book( TH1F( "HT_genjets_ly", "H_{T, genjets}", 100, 0 , 1500));
  


  Book( TH1F( "HT_lepton", "H_{T, lep}", 100, 0 , 1500));
  Book( TH1F( "HT_lepton_ly", "H_{T, lep}", 100, 0 , 1500));
  
  Book( TH1F( "HT_lepton_met", "H_{T, lep+met}", 100, 0 , 1500));
  Book( TH1F( "HT_lepton_met_ly", "H_{T, lep+met}", 100, 0 , 1500));
  
  Book( TH1F( "HT", "H_{T}", 100, 0 , 1500));
  Book( TH1F( "HT_ly", "H_{T}", 100, 0 , 1500));
  
  Book( TH1F( "zhadreco", "chi Z_{had}", 100, 0 , 400));
  Book( TH1F( "zlepeco", "chi Z_{lep}", 100, 0 , 400));
  Book( TH1F( "zinvreco", "chi Z_{inv}", 100, 0 , 400));

  Book( TH1F( "thadreco", "chi t_{had}", 100, 0 , 400));
  Book( TH1F( "tlepreco", "chi t_{lep}", 100, 0 , 400));

  Book( TH1F( "thadzlepreco", "chi t' -> Z_{lep}+t_{had}", 100, 0 , 1000));
  Book( TH1F( "thadzhadreco", "chi t' -> Z_{had}+t_{had}", 100, 0 , 1000));
  Book( TH1F( "tlepzlepreco", "chi t' -> Z_{lep}+t_{lep}", 100, 0 , 1000));
  Book( TH1F( "tlepzhadreco", "chi t' -> Z_{had}+t_{lep}", 100, 0 , 1000));
  Book( TH1F( "tlepzinvreco", "chi t' -> Z_{inv}+t_{lep}", 100, 0 , 1000));
  Book( TH1F( "thadzinvreco", "chi t' -> Z_{inv}+t_{had}", 100, 0 , 1000));

}

void GenJetsHists::Fill()
{
  // fill the histograms


  EventCalc* calc = EventCalc::Instance();
  LuminosityHandler* lumih = calc->GetLumiHandler();

  BaseCycleContainer* bcc = calc->GetBaseCycleContainer();
  
  GenZt GenParZt(bcc);
  std::vector<Particle>* Particles= bcc->genjets;

 

  // important: get the event weight
  double weight = calc->GetWeight();
 

  int NPart = Particles->size();
  
  Hist("number_part")->Fill(NPart,weight);
  Hist("number_part_ly")->Fill(NPart,weight);


  //cout<<NPart<<Particle.at(0).pt() <<endl;



  for(int i=0 ; i<NPart; i++){

    Particle gen = Particles->at(i);
  

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
	Hist("pairmass")->Fill((Particles->at(p).v4()+Particles->at(p+i).v4()).M(),weight);
	Hist("pairmass_ly")->Fill((Particles->at(p).v4()+Particles->at(p+i).v4()).M(),weight);
	Hist("delR")->Fill(deltaR(Particles->at(p).v4(),Particles->at(p+i).v4()),weight);
	Hist("delR_ly")->Fill(deltaR(Particles->at(p).v4(),Particles->at(p+i).v4()),weight);	
      }
    }
  }

  
  

  LorentzVector sum_electron;
  LorentzVector sum_muon;
  LorentzVector sum_neutrino;
  LorentzVector sum_b;
  LorentzVector sum_l;
  LorentzVector sum_genjets;
  
  for(unsigned int i=0; i < GenParZt.electrons().size(); ++i)
    sum_electron = sum_electron+GenParZt.electrons().at(i).v4();
  
  for(unsigned int i=0; i < GenParZt.muons().size(); ++i)
    sum_muon += GenParZt.muons().at(i).v4();
  
  for(unsigned int i=0; i < GenParZt.neutrinos().size(); ++i)
    sum_neutrino = sum_neutrino+GenParZt.neutrinos().at(i).v4();
  
  for(unsigned int i=0; i < GenParZt.lquarks().size(); ++i)
    sum_l = sum_l+GenParZt.lquarks().at(i).v4();
  
  for(unsigned int i=0; i < GenParZt.b().size(); ++i)
    sum_b = sum_b+GenParZt.b().at(i).v4();
  
  for(unsigned int i=0; i < bcc->genjets->size(); ++i)
    sum_genjets = sum_genjets+bcc->genjets->at(i).v4();
  
  Hist("HT_electron")->Fill(fabs(sum_electron.pt()),weight);
  Hist("HT_electron_ly")->Fill(fabs(sum_electron.pt()),weight);
  
  Hist("HT_muon")->Fill(fabs(sum_muon.pt()),weight);
  Hist("HT_muon_ly")->Fill(fabs(sum_muon.pt()),weight);
  
  Hist("HT_b")->Fill(fabs(sum_b.pt()),weight);
  Hist("HT_b_ly")->Fill(fabs(sum_b.pt()),weight);
  
  Hist("HT_l")->Fill(fabs(sum_l.pt()),weight);
  Hist("HT_l_ly")->Fill(fabs(sum_l.pt()),weight);
  
  Hist("HT_genjets")->Fill(fabs(sum_genjets.pt()),weight);
  Hist("HT_genjets_ly")->Fill(fabs(sum_genjets.pt()),weight);
  
  Hist("HT_neutrino")->Fill(fabs(sum_neutrino.pt()),weight);
  Hist("HT_neutrino_ly")->Fill(fabs(sum_neutrino.pt()),weight);
  
  Hist("HT_lepton")->Fill(fabs((sum_electron+sum_muon).pt()),weight);
  Hist("HT_lepton_ly")->Fill(fabs((sum_electron+sum_muon).pt()),weight);
  
  Hist("HT_lepton_met")->Fill(fabs((sum_electron+sum_muon+sum_neutrino).pt()),weight);
  Hist("HT_lepton_met_ly")->Fill(fabs((sum_electron+sum_muon+sum_neutrino).pt()),weight);
  
  Hist("HT")->Fill(fabs((sum_electron+sum_muon+sum_neutrino+sum_genjets).pt()),weight);
  Hist("HT_ly")->Fill(fabs((sum_electron+sum_muon+sum_neutrino+sum_genjets).pt()),weight);


  double chi_z_lep = 99999;
  double chi_t_lep = 99999;

  double chi_z_had = 99999;
  double chi_t_had = 99999;

  double chi_z_inv = sum_neutrino.M()*sum_neutrino.M()/20;

  for(unsigned int i=0; i<GenParZt.m_z_lep.size(); ++i){
    double mass =GenParZt.m_z_lep.at(i).M();
    double chi = (mass-91)*(mass-91)/30;
    if(chi<chi_z_lep) chi_z_lep = chi;
  }
  
  for(unsigned int i=0; i<GenParZt.m_t_lep.size(); ++i){
    double mass =GenParZt.m_t_lep.at(i).M();
    double chi = (mass-171)*(mass-171)/50;
    if(chi<chi_t_lep) chi_t_lep = chi;
  }

  for(unsigned int i=0; i<GenParZt.m_had_combi.size(); ++i){
    double mass =GenParZt.m_had_combi.at(i).M();
    double chi_t = (mass-171)*(mass-171)/50;
    double chi_z = (mass-91)*(mass-91)/30;
    if(chi_z<chi_z_had) chi_z_had = chi_z;
    if(chi_t<chi_t_had) chi_t_had = chi_t;
  }



  Hist("zhadreco")->Fill(chi_z_had,weight);
  Hist("zlepeco" )->Fill(chi_z_lep,weight);
  Hist("zinvreco")->Fill(chi_z_inv,weight);
  Hist("thadreco")->Fill(chi_t_had,weight);
  Hist("tlepreco")->Fill(chi_t_lep,weight);

  Hist("thadzlepreco")->Fill(chi_t_had+chi_z_lep,weight);
  Hist("thadzhadreco")->Fill(chi_t_had+chi_z_had,weight);
  Hist("tlepzlepreco")->Fill(chi_t_lep+chi_z_lep,weight);
  Hist("tlepzhadreco")->Fill(chi_t_lep+chi_z_had,weight);
  Hist("tlepzinvreco")->Fill(chi_t_lep+chi_z_inv,weight);
  Hist("thadzinvreco")->Fill(chi_t_had+chi_z_inv,weight);









  
}



void GenJetsHists::Finish()
{
 

}

