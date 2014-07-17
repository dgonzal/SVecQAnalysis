#include "include/GenZt.h"

using namespace std;

vector<LorentzVector> Fill_had_combi(const vector<Particle> & jets){

  vector<LorentzVector> result;
  unsigned int n_jets = jets.size();
  if(n_jets>5) n_jets=5; //avoid crashes in events with many jets
  unsigned int max_j = myPow(3, n_jets);
  for (unsigned int j=0; j < max_j; j++) {
    int num = j;
    LorentzVector had_v4(0,0,0,0);
    for (unsigned int k=0; k<n_jets; k++) {
      // num is the k-th digit of j if you
      // write j in a base-3 system. According
      // to the value of this digit (which takes
      // values from 0 to 2,
      // in all possible combinations with the other digits),
      // decide how to treat the jet.
	
      if(num%3==0) {
	had_v4 = had_v4 + jets.at(k).v4();
	result.push_back(had_v4);
      }
      num /= 3;
    }
  }
  return result;
}

GenZt::GenZt(){
}

GenZt::~GenZt(){
  // default destructor, does nothing
}

void GenZt::reset(){
  m_Top.clear();
  m_b.clear();
  m_neutrinos.clear();
  m_muons.clear();
  m_electron.clear();
  m_WTop.clear();
  m_Z.clear();
  m_Tprime.clear();
  m_lquarks.clear();
  m_virW.clear();
  m_gluons.clear();
}

void GenZt::identify(BaseCycleContainer* bcc){
  //std::cout<<"---------------------------"<<std::endl;

  for(unsigned int i=0; i<bcc->genparticles->size(); ++i)
    {
      GenParticle genp = bcc->genparticles->at(i);
      
    
      //if(genp.pt()<20) continue;
      //std::cout<<"GenParticle pdgId: "<<genp.pdgId()<<" status: "<<genp.status() <<std::endl;
      //std::cout<<"GenParticle pdgId: "<<genp.pdgId()<<std::endl;
      //std::cout<<"---------------------------"<<std::endl;

      switch(genp.pdgId())
	{ 
	case 1:
	case -1:
	case 2:
	case -2:
	case 3:
	case -3:
	case 4:
	case -4:
	  if(genp.status()==1)m_lquarks.push_back(genp);
	  break;

	case 5:
	case -5:
	  m_b.push_back(genp);
	  break;

	case 6:
	case -6:
	  m_Top.push_back(genp);
	  break;

	case 8:
	case -8:
	  m_Tprime.push_back(genp);
	  break;

	case 9:
	case -9:
	case 21:
	case -21:
	  m_gluons.push_back(genp);
	  break;

	case 23:
	  m_Z.push_back(genp);
	  break;

	case 24:
	case -24:
	  //cout<<"W+-: "<<"pdgId "<<genp.pdgId()<<" mother1 "<<genp.mother1()<<" mother2 "<<genp.mother2()<<" status "<< genp.status() << " pT "<<genp.pt() << " mass "<<genp.v4().M()<<endl;
	  if(genp.v4().M()<500) m_WTop.push_back(genp);
	  else m_virW.push_back(genp);
	  break;

	case 11:
	case -11:
	    if(genp.status()==1)m_electron.push_back(genp);
	  break;

	case 13:
	case -13:
	    if(genp.status()==1)m_muons.push_back(genp);
	  break;

	case 12:
	case -12:
	case 14:
	case -14:
	    if(genp.status()==1)m_neutrinos.push_back(genp);
	  break;	 
      }	     
    }

  
  if(m_electron.size()>0) sort(m_electron.begin(),m_electron.end(),HigherPt());
  if(m_muons.size()>0) sort(m_muons.begin(),m_muons.end(),HigherPt());
  if(m_neutrinos.size()>0) sort(m_neutrinos.begin(),m_neutrinos.end(),HigherPt());

}


void GenZt::Fill_z_lep(){

  if(m_electron.size()>1){
    m_z_lep.push_back(m_electron.at(0).v4()+m_electron.at(1).v4());
  }
  if(m_electron.size()>2){
    m_z_lep.push_back(m_electron.at(1).v4()+m_electron.at(2).v4());
    m_z_lep.push_back(m_electron.at(0).v4()+m_electron.at(2).v4());
  }
  if(m_muons.size()>1){
    m_z_lep.push_back(m_muons.at(0).v4()+m_muons.at(1).v4());
  }
  if(m_muons.size()>2){
    m_z_lep.push_back(m_muons.at(1).v4()+m_muons.at(2).v4());
    m_z_lep.push_back(m_muons.at(0).v4()+m_muons.at(2).v4());
  }
}

void GenZt::Fill_t_lep(){
  if(m_electron.size()>0 && m_neutrinos.size()>0){
    for(unsigned int i =0;i<m_electron.size();++i)
      m_t_lep.push_back(m_electron.at(i).v4()+m_neutrinos.at(0).v4());
  }
  if(m_muons.size()>0 && m_neutrinos.size()>0){
    for(unsigned int i =0;i<m_muons.size();++i)
      m_t_lep.push_back(m_muons.at(i).v4()+m_neutrinos.at(0).v4());
  }
}




    

