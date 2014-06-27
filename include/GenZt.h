#ifndef GenZt_H
#define GenZt_H
 
#include "TLorentzVector.h"
#include "SFrameTools/include/Objects.h"
#include "SFrameTools/include/BaseCycleContainer.h"
#include "include/Utils.h"


class GenZt
{
 public:
  GenZt(BaseCycleContainer* bcc);
  ~GenZt();
   
  std::vector<GenParticle> Tprime(){return m_Tprime;}
  std::vector<GenParticle> Top(){return m_Top;}
  std::vector<GenParticle> WTop(){return m_WTop;}
  std::vector<GenParticle> Z(){return m_Z;}
  std::vector<GenParticle> b(){return m_b;}
  std::vector<GenParticle> neutrinos(){return m_neutrinos;}
  std::vector<GenParticle> muons(){return m_muons;}
  std::vector<GenParticle> electrons(){return m_electron;}
  std::vector<GenParticle> lquarks(){return m_lquarks;}
  std::vector<GenParticle> VirW(){return m_virW;}
  std::vector<GenParticle> gluons(){return m_gluons;}

  std::vector<LorentzVector> m_had_combi;
  std::vector<LorentzVector> m_z_lep;
  std::vector<LorentzVector> m_t_lep;


 private:

  void Fill_z_lep();
  void Fill_t_lep();

  std::vector<GenParticle> m_b;
  std::vector<GenParticle> m_neutrinos;
  std::vector<GenParticle> m_muons;
  std::vector<GenParticle> m_electron;
  std::vector<GenParticle> m_Top;
  std::vector<GenParticle> m_WTop;
  std::vector<GenParticle> m_Z;
  std::vector<GenParticle> m_Tprime;
  std::vector<GenParticle> m_lquarks;
  std::vector<GenParticle> m_virW;
  std::vector<GenParticle> m_gluons;
};

#endif //GenZt_H
