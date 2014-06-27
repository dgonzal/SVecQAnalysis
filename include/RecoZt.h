#ifndef RecoZt_H
#define RecoZt_H
 
#include <vector>


#include "TLorentzVector.h"
#include "SFrameTools/include/Objects.h"
#include "SFrameTools/include/BaseCycleContainer.h"
#include "include/Utils.h"

#include "core/include/SError.h"
#include "core/include/SCycleBase.h"

using namespace std;

struct RecoZt_hyp{
 //LorentzVector b;
 LorentzVector t;
 //LorentzVector W;
 LorentzVector Z;
};


class RecoZt
{
 public:

  RecoZt(BaseCycleContainer* bcc);
  ~RecoZt();
   
  std::vector<LorentzVector> Tprime(){return m_Tprime;}
  std::vector<LorentzVector> Top(){return m_Top;}
  std::vector<LorentzVector> W(){return m_W;}
  std::vector<LorentzVector> Z(){return m_Z;}
  std::vector<LorentzVector> b(){return m_b;}
  vector<RecoZt_hyp> Hyp(){return m_Hyp;}

 private:

  void Fill_2_lep(const vector<Particle> & jets, const vector<Particle> & muons, const vector<Particle> & electrons );
  void Fill_3_lep(const vector<Particle> & jets, const vector<Particle> & muons, const vector<Particle> & electrons );
  void Fill_had_combi(const vector<Particle>& jets);

  BaseCycleContainer* m_bcc;
  vector<RecoZt_hyp> m_Hyp;	
  std::vector<LorentzVector> m_b;
  std::vector<LorentzVector> m_Top;
  std::vector<LorentzVector> m_W;
  std::vector<LorentzVector> m_Z;
  std::vector<LorentzVector> m_Tprime;
};

#endif //RecoZt_H
