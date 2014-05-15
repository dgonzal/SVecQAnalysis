#include "include/GenZt.h"

using namespace std;

GenZt::GenZt(BaseCycleContainer* bcc){
  


  //std::cout<<"---------------------------"<<std::endl;

  for(unsigned int i=0; i<bcc->genparticles->size(); ++i)
    {
      GenParticle genp = bcc->genparticles->at(i);
      
      if(genp.pt()<20) continue;
      //std::cout<<"GenParticle pdgId: "<<genp.pdgId()<<" pT: "<<genp.pt() <<std::endl;
      //std::cout<<"GenParticle pdgId: "<<genp.pdgId()<<std::endl;

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
	  m_lquarks.push_back(genp);
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
	    m_electron.push_back(genp);
	  break;

	case 13:
	case -13:
	    m_muons.push_back(genp);
	  break;

	case 12:
	case -12:
	case 14:
	case -14:
	    m_neutrinos.push_back(genp);
	  break;

	  

      }
	     
    }
}

GenZt::~GenZt(){
  // default destructor, does nothing
}

