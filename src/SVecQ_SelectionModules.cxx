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

  if(nlepton <= m_NLepton_max && nlepton >= m_NLepton_min){
    return true;
  }



  return false;
}


std::string GenLeptonSelection::description()
{
    char s[100];
    sprintf(s, "%d <= NLepton <= %d",m_NLepton_min, m_NLepton_max);

    return s;
}


GenMissingHTSelection::GenMissingHTSelection(double min, double max)
{
  m_min=min;
  m_max=max;
}


bool GenMissingHTSelection::pass(BaseCycleContainer* bcc)
{
  GenZt GenParZt(bcc);
  LorentzVector missingHT(0,0,0,0);


  for(unsigned int i=0;i<GenParZt.neutrinos().size(); i++ ){
    missingHT += GenParZt.neutrinos().at(i).v4();
  }

  if( missingHT.pt()>m_min &&  missingHT.pt()<m_max) return true;

  return false;
}

std::string GenMissingHTSelection::description()
{
    char s[100];
    sprintf(s, "%f <= MHT <= %f ",m_min, m_max);

    return s;
}


hadZmass::hadZmass(double min, double max)
{
  m_min=min;
  m_max=max;
}

bool hadZmass::pass(BaseCycleContainer* bcc)
{
  std::vector< Jet >* jets = bcc->jets; 
  int NJets = jets->size();
 
  for(int i =0; i<NJets; i++)
    if(jets->at(i).v4().M2()<m_max*m_max && jets->at(i).v4().M2()>m_min*m_min) return true;
  
  for(int i =0; i<NJets; i++){
    LorentzVector Z = jets->at(i).v4();
    for(int p =1; p<(NJets-i); p++){
      Z +=  jets->at(i+p).v4();
      if(Z.M2()<m_max*m_max && Z.M2()>m_min*m_min) return true;
    }
  }

  return false;
}

std::string hadZmass::description()
{
    char s[100];
    sprintf(s, "%f <= had Z_mass <= %f ",m_min, m_max);

    return s;
}


lepZmass::lepZmass(double min, double max)
{
  m_min=min;
  m_max=max;
}

bool lepZmass::pass(BaseCycleContainer* bcc)
{
  std::vector< Electron >* electrons = bcc->electrons;
  std::vector< Muon >* muons = bcc->muons;

  for(int i =0; i<electrons->size(); i++){
    LorentzVector Z = electrons->at(i).v4();
    for(int p =1; p<(electrons->size()-i); p++){
      Z +=  electrons->at(i+p).v4();
      if(Z.M2()<m_max*m_max && Z.M2()>m_min*m_min) return true;
    }
  }

  for(int i =0; i<muons->size(); i++){
    LorentzVector Z = muons->at(i).v4();
    for(int p =1; p<(muons->size()-i); p++){
      Z +=  muons->at(i+p).v4();
      if(Z.M2()<m_max*m_max && Z.M2()>m_min*m_min) return true;
    }
  }



  return false;
}

std::string lepZmass::description()
{
    char s[100];
    sprintf(s, "%f <= lep Z_mass <= %f ",m_min, m_max);

    return s;
}


GenTopTag::GenTopTag()
{
}

bool GenTopTag::pass(BaseCycleContainer* bcc)
{
  std::vector< GenTopJet >* gentopjets =bcc->topjetsgen;

  if(gentopjets->size()<1) return false;

  for(unsigned int i=0; i<gentopjets->size(); ++i){
    GenTopJet gentop = gentopjets->at(i);
    double nsubjets=gentop.subjets().size();
    double mmin =0;
    
    //at least 3 sub-jets
    if(nsubjets<3) return false;

    LorentzVector allsubjets(0,0,0,0);
    
    for(int j=0; j<nsubjets; ++j) {
      allsubjets += gentop.subjets()[j].v4();
    }
    if(!allsubjets.isTimelike()) return false;
       
    double mjet = allsubjets.M();

    if(nsubjets>=3) {
      
      std::vector<Particle> subjets = gentop.subjets();
      sort(subjets.begin(), subjets.end(), HigherPt());
      
      double m01 = 0;
      if( (subjets[0].v4()+subjets[1].v4()).isTimelike())
	m01=(subjets[0].v4()+subjets[1].v4()).M();
      double m02 = 0;
      if( (subjets[0].v4()+subjets[2].v4()).isTimelike() )
	m02=(subjets[0].v4()+subjets[2].v4()).M();
      double m12 = 0;
      if( (subjets[1].v4()+subjets[2].v4()).isTimelike() )
	m12 = (subjets[1].v4()+subjets[2].v4()).M();
      
      //minimum pairwise mass
      mmin = std::min(m01,std::min(m02,m12));
    }
  
    //minimum pairwise mass > 50 GeV/c^2
    if(mmin<50) return false;
    //jet mass between 140 and 250 GeV/c^2
    if(mjet<140 || mjet>250) return false;

    return true;

  }

  return false;

}


std::string GenTopTag::description()
{
    char s[100];
    sprintf(s, "CMSTopTag");

    return s;
}

GenNeutrino::GenNeutrino(int N_min, int N_max,double eta_max, double pt_min)
{
  m_N_min = N_min;
  m_N_max = N_max;
  m_eta_max=eta_max; 
  m_pt_min= pt_min;
}

bool GenNeutrino::pass(BaseCycleContainer* bcc)
{
  
  GenZt GenParZt(bcc);
 
  
  int neutrino =0;
  for(unsigned int i=0;i<GenParZt.neutrinos().size(); i++ ){
    if(GenParZt.neutrinos().at(i).pt()>m_pt_min && GenParZt.neutrinos().at(i).eta()<m_eta_max)
      neutrino +=1;
  }

  if(neutrino <= m_N_max && neutrino >= m_N_min){
    return true;
  }
  

  return false;


}

std::string GenNeutrino::description()
{
    char s[100];
    sprintf(s,"%d <= N Neutrinos <= %d",m_N_min, m_N_max);

    return s;
}
