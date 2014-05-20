#ifndef tprimeReco_H
#define tprimeReco_H
 
#include "TLorentzVector.h"
#include "SFrameTools/include/Objects.h"
#include "SFrameTools/include/BaseCycleContainer.h"

using namespace std;

class tprimeReco
{
 public:
  tprimeReco(BaseCycleContainer* bcc);
  ~tprimeReco();
   
  vector<LorentzVector> hadZ(){return m_hadZ;}
  vector<LorentzVector> lepZ(){return m_lepZ;};
  //invZ

 private:
  vector<LorentzVector> m_hadZ;
  vector<LorentzVector> m_lepZ;
 
};

#endif //tprimeReco_H
