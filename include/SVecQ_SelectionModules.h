#ifndef SVecQ_SelectionModules_H
#define SVecQ_SelectionModules_H

#include "SFrameAnalysis/include/SelectionModules.h"
#include "include/GenZt.h"


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




#endif
