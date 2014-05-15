#ifndef GenParticleHists_H
#define GenParticleHists_H

#include "SFrameTools/include/BaseHists.h"
#include "SFrameTools/include/Objects.h"
#include "include/GenZt.h"


/**
 *   SVecQAnalysis class for booking and filling histograms
 *
 *   This class books and fills a collection of histograms.
 *   It should have a unique name, such that the histograms
 *   of multiple instances of this class are ordered in the
 *   output file. 
 *   Always sort your histograms and used methods topically.
 *   This example collection can be used for data and reconstructed
 *   MC events.
 *   
 *   @version $Revision: 1.2 $
 */





class GenParticleHists : public BaseHists {

 public:
  enum p_type{
    tprime,
    neutrino,
    Z,
    W,
    l,
    b,
    top,
    muon,
    electron,
    gluon,
    VirW,
    genjets,
  }; 

  /// Named constructor
  GenParticleHists(const char* name, p_type particle);
  
  /// Default destructor
  ~GenParticleHists();
  
  void Init();
  
  void Fill();
  
  void Finish();
  

 private:
  p_type m_partn;
  
  
}; // class GenParticleHists


#endif // GenParticleHists_H
