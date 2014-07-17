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
  
  RecoZt();
  ~RecoZt();
  
  vector<RecoZt_hyp> Hyp(){return m_Hyp;}
  
  void reset(){m_Hyp.clear();}
  
  void Fill_1_lep(const vector<Jet> & jets, const vector<Muon> & muons, const vector<Electron> & electrons, const LorentzVector & met );
  void Fill_2_lep(const vector<Jet> & jets, const vector<Muon> & muons, const vector<Electron> & electrons );
  void Fill_3_lep(const vector<Jet> & jets, const vector<Muon> & muons, const vector<Electron> & electrons, const LorentzVector & met );
  void Fill_had_combi(const vector<Jet>& jets, MET* met);

  
  RecoZt_hyp get_best_chi2();
  
 private:
  vector<RecoZt_hyp> m_Hyp;	
  
};

#endif //RecoZt_H
