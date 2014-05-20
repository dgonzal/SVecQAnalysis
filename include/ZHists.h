#ifndef ZHists_H
#define ZHists_H

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





class ZHists : public BaseHists {

 public:
  /// Named constructor
  ZHists(const char* name);
  
  /// Default destructor
  ~ZHists();
  
  void Init();
  
  void Fill();
  
  void Finish();
  
  
 private:
 
  
  
}; // class ZHists


#endif // ZHists_H
