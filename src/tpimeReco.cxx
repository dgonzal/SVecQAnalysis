#include "include/tprimeReco.h"

using namespace std;

tprimeReco::tprimeReco(BaseCycleContainer* bcc){
  std::vector< Electron >* electrons = bcc->electrons;
  std::vector< Muon >* muons = bcc->muons;
  
  for(int i =0; i<electrons->size(); i++){
    LorentzVector Z = electrons->at(i).v4();
    for(int p =1; p<(electrons->size()-i); p++){
      Z +=  electrons->at(i+p).v4();
      m_lepZ.push_back(Z);
    }
  }

  for(int i =0; i<muons->size(); i++){
    LorentzVector Z = muons->at(i).v4();
    for(int p =1; p<(muons->size()-i); p++){
      Z +=  muons->at(i+p).v4();
      m_lepZ.push_back(Z);
    }
  }

  std::vector< Jet >* jets = bcc->jets; 
  int NJets = jets->size();
  
  for(int i =0; i<NJets; i++){
    LorentzVector Z = jets->at(i).v4();
    m_hadZ.push_back(Z);
    for(int p =1; p<(NJets-i); p++){
      Z +=  jets->at(i+p).v4();
      m_hadZ.push_back(Z);
    }
  }
  
}

tprimeReco::~tprimeReco(){
  // default destructor, does nothing
}

