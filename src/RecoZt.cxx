#include "include/RecoZt.h"
#include "../../SFrameTools/include/TopFitCalc.h" 

using namespace std;


/*
Strategy: Split the reconstruction depending on the channel and special topologies
make sure that nothing is used more then once in the reconstruction
*/



RecoZt::RecoZt(){

  //Fill_z_lep();
  //Fill_t_lep();
  //m_had_combi = Fill_had_combi(*bcc->genjets);

}

RecoZt::~RecoZt(){
  // default destructor, does nothing
}


void RecoZt::Fill_2_lep(const vector<Jet> & jets, const vector<Muon> & muons, const vector<Electron> & electrons ){
  unsigned int n_jets = jets.size();
  if(n_jets>9) n_jets=9; //avoid crashes in events with many jets
  unsigned int max_j = myPow(3, n_jets);

  LorentzVector Z_v4;

  if(muons.size()==2)
  	Z_v4 = muons.at(0).v4()+muons.at(1).v4();
  else if (electrons.size()==2)
  	Z_v4 = electrons.at(0).v4()+electrons.at(1).v4();
  else
	//m_logger << ERROR << "There are not exactly either two muons or electrons in the event" << SLogger::endmsg;
	cout<< "There are not exactly either two muons or electrons in the event"<<endl;


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

void RecoZt::Fill_3_lep(const vector<Jet> & jets, const vector<Muon> & muons, const vector<Electron> & electrons, const LorentzVector& met){
  unsigned int n_jets = jets.size();
  if(n_jets>5) n_jets=5; //avoid crashes in events with many jets
  unsigned int max_j = myPow(3, n_jets);
  
  LorentzVector tlep;
  LorentzVector Z_v4;
  
  if(muons.size()>=2){
    Z_v4 = muons.at(0).v4()+muons.at(1).v4();
    tlep = electrons.at(0).v4();
  }
  else if (electrons.size()>=2){
    Z_v4 = electrons.at(0).v4()+electrons.at(1).v4();
    tlep = muons.at(0).v4();
  }
  else{
    //m_logger << ERROR << "There are not exactly either two muons or electrons in the event" << SLogger::endmsg;
    cout<< "There are not exactly either two muons or electrons in the event"<<endl;
  }


  EventCalc* calc = EventCalc::Instance();
  std::vector<LorentzVector> neutrinos = calc->NeutrinoReconstruction(tlep, met);
  
  for(unsigned int i=0; i<neutrinos.size();i++){
    
    for (unsigned int j=0; j < max_j; j++) {
      int num = j;
      LorentzVector Z_v4(0,0,0,0);
      LorentzVector top_v4=tlep;
      RecoZt_hyp p_Hyp;

      for (unsigned int k=0; k<n_jets; k++) {
	// num is the k-th digit of j if you
	// write j in a base-3 system. According
	// to the value of this digit (which takes
	// values from 0 to 2,
	// in all possible combinations with the other digits),
	// decide how to treat the jet.
	
	if(num%3==0) {
	  Z_v4 = Z_v4 ;
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
}


void RecoZt::Fill_1_lep(const vector<Jet> & jets, const vector<Muon> & muons, const vector<Electron> & electrons, const LorentzVector& met){
  unsigned int n_jets = jets.size();
  if(n_jets>9) n_jets=9; //avoid crashes in events with many jets
  unsigned int max_j = myPow(3, n_jets);
  
  LorentzVector tlep;
  
  if(muons.size()==1){
    tlep = muons.at(0).v4();
  }
  else if (electrons.size()==1){
    tlep = muons.at(0).v4();
  }
  else{
    //m_logger << ERROR << "There are not exactly either two muons or electrons in the event" << SLogger::endmsg;
    cout<< "There are not exactly either two muons or electrons in the event"<<endl;
  }

  EventCalc* calc = EventCalc::Instance();
  std::vector<LorentzVector> neutrinos = calc->NeutrinoReconstruction(tlep, met);
  
  for(unsigned int i=0; i<neutrinos.size();i++){
    
    for (unsigned int j=0; j < max_j; j++) {
      int num = j;
      LorentzVector Z_v4(0,0,0,0);
      LorentzVector top_v4=tlep+neutrinos[i];
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
}

   
void RecoZt::Fill_had_combi(const vector<Jet> & jets, MET* met){
  unsigned int n_jets = jets.size();
  if(n_jets>7) n_jets=7; //avoid crashes in events with many jets
  unsigned int max_j = myPow(3, n_jets);

  for(int i =0; i<2; ++i){
    for (unsigned int j=0; j < max_j; j++) {
      int num = j;
      LorentzVector Z_v4(0,0,0,0);
      LorentzVector top_v4(0,0,0,0);
      RecoZt_hyp p_Hyp;
      if(i == 1) Z_v4 = met->v4();

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
	  top_v4 = top_v4 +jets.at(k).v4();
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
}

RecoZt_hyp RecoZt::get_best_chi2(){
  double chi2 = 9999999999;
  unsigned int position =-1;


  for (unsigned int i = 0; i < m_Hyp.size(); i++){
    
    if(chi2 > (m_Hyp.at(i).t.M()-173)*(m_Hyp.at(i).t.M()-173)*0.02 +(m_Hyp.at(i).Z.M()-91)*(m_Hyp.at(i).Z.M()-91)*0.1){
    chi2 = (m_Hyp.at(i).t.M()-173)*(m_Hyp.at(i).t.M()-173)*0.02 + (m_Hyp.at(i).Z.M()-91)*(m_Hyp.at(i).Z.M()-91)*0.1;
    position = i;
    }
  }
  if(position<0) cout<<"No Valid reconstruction"<<endl;
  return m_Hyp.at(position); 

}
