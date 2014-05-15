#ifndef GenJetsHists_H
#define GenJetsHists_H

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





class GenJetsHists : public BaseHists {

 public:
  /// Named constructor
  GenJetsHists(const char* name);
  
  /// Default destructor
  ~GenJetsHists();
  
  void Init();
  
  void Fill();
  
  void Finish();
  

 private:
 
  
  
}; // class GenJetsHists


#endif // GenJetsHists_H
