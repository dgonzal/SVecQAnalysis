// Dear emacs, this is -*- c++ -*-
// $Id: SVecQAnalysisPreSelectionCycle.h,v 1.4 2013/06/12 12:40:14 peiffer Exp $
#ifndef SVecQAnalysisPreSelectionCycle_H
#define SVecQAnalysisPreSelectionCycle_H

#include "SFrameAnalysis/include/AnalysisCycle.h"
#include "SFrameAnalysis/include/Cleaner.h"


#include "include/GenZt.h"

//#include "JetCorrectorParameters.h"



#include "SFrameAnalysis/include/EventHists.h"
#include "SFrameAnalysis/include/JetHists.h"
#include "SFrameAnalysis/include/MuonHists.h"
#include "SFrameAnalysis/include/ElectronHists.h"
#include "include/GenParticleHists.h"



#include "SFrameAnalysis/include/SelectionModules.h"
#include "include/SVecQ_SelectionModules.h"



/**
 *   @short SVecQAnalysis of an analysis cycle
 *
 *          This is an example of an analysis cycle. It can be used
 *          as a template for writing your own analysis. Also should
 *          be used for quick cross checks of the system setup.
 *
 *  @author Roman Kogler
 *  @version $Revision: 1.4 $
 */

class SVecQAnalysisPreSelectionCycle : public AnalysisCycle {

public:
  /// Default constructor
  SVecQAnalysisPreSelectionCycle();
  /// Default destructor
  ~SVecQAnalysisPreSelectionCycle();

  /// Function called at the beginning of the cycle
  void BeginCycle() throw( SError );
  /// Function called at the end of the cycle
  void EndCycle() throw( SError );

  /// Function called at the beginning of a new input data
  void BeginInputData( const SInputData& ) throw( SError );
  /// Function called after finishing to process an input data
  void EndInputData  ( const SInputData& ) throw( SError );

  /// Function called after opening each new input file
  void BeginInputFile( const SInputData& ) throw( SError );

  /// Function called for every event
  void ExecuteEvent( const SInputData&, Double_t ) throw( SError );

private:
  //
  // Put all your private variables here
  //
  std::string m_GenLepton_Selection;



  // Macro adding the functions for dictionary generation
  ClassDef( SVecQAnalysisPreSelectionCycle, 0 );
  


}; // class SVecQAnalysisPreSelectionCycle

#endif // SVecQAnalysisPreSelectionCycle_H

