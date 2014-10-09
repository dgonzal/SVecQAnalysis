#ifndef RecoHists_H
#define RecoHists_H

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





class RecoHists : public BaseHists {

 public:
  /// Named constructor
  RecoHists(const char* name, int factor = 1);
  
  /// Default destructor
  ~RecoHists();
  
  void Init();
  
  void Fill();
  
  void Finish();
  
  
 private:
  int m_factor;
  
  
}; // class RecoHists


#endif // RecoHists_H
