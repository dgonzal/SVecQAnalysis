#include "include/SVecQ_SelectionModules.h"


GenLeptonSelection::GenLeptonSelection(int NLepton_min, int NLepton_max, double eta_max, double pt_min)
{
  m_NLepton_min = NLepton_min;
  m_NLepton_max = NLepton_max;
  m_eta_max=eta_max; 
  m_pt_min= pt_min;
}


bool GenLeptonSelection::pass(BaseCycleContainer* bcc)
{
  GenZt GenParZt(bcc);
  
  //int nlepton = GenParZt.muons().size() + GenParZt.electrons().size();
  //cout<<"Muon: " <<GenParZt.muons().size()<< "  Elec: "<<GenParZt.electrons().size() <<endl;
 
  int muon =0;
  int electron =0;
  for(unsigned int i=0;i<GenParZt.muons().size(); i++ ){
    if(GenParZt.muons().at(i).pt()>m_pt_min && GenParZt.muons().at(i).eta()<m_eta_max)
      muon +=1;
  }
  for(unsigned int i=0;i<GenParZt.electrons().size(); i++ ){
    if(GenParZt.electrons().at(i).pt()>m_pt_min && GenParZt.electrons().at(i).eta()<m_eta_max)
      electron +=1;
  }

  int nlepton = electron+muon;

  if(nlepton <= m_NLepton_max && nlepton >= m_NLepton_min)
    return true;
  
  return false;
}


std::string GenLeptonSelection::description()
{
    char s[100];
    sprintf(s, "%d <= NLepton <= %d ",m_NLepton_min, m_NLepton_max);

    return s;
}
