#ifndef SVecQ_SelectionModules_H
#define SVecQ_SelectionModules_H

#include "SFrameAnalysis/include/SelectionModules.h"
#include "include/GenZt.h"

class relIsoMu : public SelectionModule {
 public:
  relIsoMu(double relIso);
  ~relIsoMu(){};

   virtual bool pass(BaseCycleContainer*);
   virtual std::string description();


 private:
   double m_relIso;
};

class JetFirstDeltaR : public SelectionModule {
 public:
  JetFirstDeltaR(double deltR_min);
  ~JetFirstDeltaR(){};

   virtual bool pass(BaseCycleContainer*);
   virtual std::string description();


 private:
   double m_deltR_min;
};

class GenLeptonSelection: public SelectionModule {
 public:
  GenLeptonSelection(int NLepton_min, int NLepton_max, double eta_max, double pt_min);
  ~GenLeptonSelection(){};

   virtual bool pass(BaseCycleContainer*);
   virtual std::string description();


 private:
   int m_NLepton_min;
   int m_NLepton_max;
   double m_eta_max;
   double m_pt_min;
};

class GenMissingHTSelection: public SelectionModule {
 public:
  GenMissingHTSelection(double min, double max);
  ~GenMissingHTSelection(){};

   virtual bool pass(BaseCycleContainer*);
   virtual std::string description();


 private:
   double m_max;
   double m_min;
};

class hadZmass: public SelectionModule {
 public:
  hadZmass(double min, double max);
  ~hadZmass(){};

   virtual bool pass(BaseCycleContainer*);
   virtual std::string description();


 private:
   double m_max;
   double m_min;
};

class NSumLepSel: public SelectionModule {
  public:
	NSumLepSel(int min, int max);
	~NSumLepSel(){};


   virtual bool pass(BaseCycleContainer*);
   virtual std::string description();

  private:
	int m_min;
	int m_max;
};

class lepZmass: public SelectionModule {
 public:
  lepZmass(double min, double max);
  ~lepZmass(){};

   virtual bool pass(BaseCycleContainer*);
   virtual std::string description();


 private:
   double m_max;
   double m_min;
};


class GenTopTag : public SelectionModule {
 public:
  GenTopTag();
  ~GenTopTag(){};
  
  virtual bool pass(BaseCycleContainer*);
  virtual std::string description();


 private:
   
};

class GenNeutrino : public SelectionModule {
 public:
  GenNeutrino(int N_min, int N_max,double eta_max=10, double pt_min=20);
  ~GenNeutrino(){};
  
  virtual bool pass(BaseCycleContainer*);
  virtual std::string description();


 private:
  double m_pt_min;
  double m_eta_max;
  int m_N_min;
  int m_N_max;
};

#endif
