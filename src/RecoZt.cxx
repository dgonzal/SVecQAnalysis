#include "include/RecoZt.h"
#include "../../SFrameTools/include/TopFitCalc.h" 

using namespace std;


/*
Strategy: Split the reconstruction depending on the channel and special topologies
make sure that nothing is used more then once in the reconstruction
*/



RecoZt::RecoZt(BaseCycleContainer* bcc){

  EventCalc* calc = EventCalc::Instance();
  m_bcc = calc->GetBaseCycleContainer();
  //Fill_z_lep();
  //Fill_t_lep();
  //m_had_combi = Fill_had_combi(*bcc->genjets);

}

RecoZt::~RecoZt(){
  // default destructor, does nothing
}


void RecoZt::Fill_2_lep(const vector<Particle> & jets, const vector<Particle> & muons, const vector<Particle> & electrons ){
  unsigned int n_jets = jets.size();
  if(n_jets>9) n_jets=9; //avoid crashes in events with many jets
  unsigned int max_j = myPow(3, n_jets);

  vector<Particle> leptons; 

  if(muons.size()==2)
	leptons = muons;
  else if (electrons.size()==2)
	leptons = electrons;
  else
	//m_logger << ERROR << "There are not exactly either two muons or electrons in the event" << SLogger::endmsg;
	cout<< "There are not exactly either two muons or electrons in the event"<<endl;

  LorentzVector Z_v4 = leptons.at(0).v4()+leptons.at(1).v4();

  for (unsigned int j=0; j < max_j; j++) {
    int num = j;
    LorentzVector top_v4(0,0,0,0);
    RecoZt_hyp p_hyp;
    p_hyp.Z = Z_v4;
    for (unsigned int k=0; k<n_jets; k++) {
      // num is the k-th digit of j if you
      // write j in a base-3 system. According
      // to the value of this digit (which takes
      // values from 0 to 2,
      // in all possible combinations with the other digits),
      // decide how to treat the jet.

      if(num%3==1) {
	top_v4 = top_v4 + jets.at(k).v4();
      }
      num /= 3;
    }
    if(top_v4.pt()>0){
    	p_hyp.t = top_v4;
	m_Hyp.push_back(p_hyp);   
    }

   }
}

void RecoZt::Fill_3_lep(const vector<Particle> & jets, const vector<Particle> & muons, const vector<Particle> & electrons){
  unsigned int n_jets = jets.size();
  if(n_jets>5) n_jets=5; //avoid crashes in events with many jets
  unsigned int max_j = myPow(3, n_jets);

  vector<Particle> Zleptons; 
  Particle tlep;

  if(muons.size()==2){
	Zleptons = muons;
	tlep = electrons.at(0);
  }
  else if (electrons.size()==2){
	Zleptons = electrons;
	tlep = muons.at(0);
  }
  else{
	//m_logger << ERROR << "There are not exactly either two muons or electrons in the event" << SLogger::endmsg;
	cout<< "There are not exactly either two muons or electrons in the event"<<endl;
  }

  LorentzVector Z_v4 = Zleptons.at(0).v4()+Zleptons.at(1).v4();

  EventCalc* calc = EventCalc::Instance();
  std::vector<LorentzVector> neutrinos = calc->NeutrinoReconstruction(tlep.v4(), m_bcc->met->v4());

  for(unsigned int i=0; i<neutrinos.size();i++){

  for (unsigned int j=0; j < max_j; j++) {
    int num = j;
    LorentzVector Z_v4(0,0,0,0);
    LorentzVector top_v4=tlep.v4();
    for (unsigned int k=0; k<n_jets; k++) {
      // num is the k-th digit of j if you
      // write j in a base-3 system. According
      // to the value of this digit (which takes
      // values from 0 to 2,
      // in all possible combinations with the other digits),
      // decide how to treat the jet.

      if(num%3==0) {
	Z_v4 = Z_v4 + jets.at(k).v4();
      }
      if(num%3==1) {
	top_v4 = top_v4 + jets.at(k).v4();
      }
      num /= 3;
    }
  
  }
 }
}

   
void RecoZt::Fill_had_combi(const vector<Particle> & jets){

  unsigned int n_jets = jets.size();
  if(n_jets>9) n_jets=9; //avoid crashes in events with many jets
  unsigned int max_j = myPow(3, n_jets);
  for (unsigned int j=0; j < max_j; j++) {
    int num = j;
    LorentzVector Z_v4(0,0,0,0);
    LorentzVector top_v4(0,0,0,0);
    RecoZt_hyp p_Hyp;

    for (unsigned int k=0; k<n_jets; k++) {
      // num is the k-th digit of j if you
      // write j in a base-3 system. According
      // to the value of this digit (which takes
      // values from 0 to 2,
      // in all possible combinations with the other digits),
      // decide how to treat the jet.

      if(num%3==0) {
	Z_v4 = Z_v4 + jets.at(k).v4();
      }
      if(num%3==1) {
	top_v4 = top_v4 + jets.at(k).v4();
      }
      num /= 3;
    }
   if(Z_v4.pt()>0 && top_v4.pt()>0){
	p_Hyp.Z=Z_v4;
	p_Hyp.t=top_v4;
	m_Hyp.push_back(p_Hyp);	
   }

  }
}

