#ifndef SVecQAnalysisHistsNew_H
#define SVecQAnalysisHistsNew_H

#include "SFrameTools/include/AnalysisModule.h"

/**
 *   SVecQAnalysis class for booking and filling histograms, the new version using AnalysisModule mechanisms.
 */

class SVecQAnalysisHistsNew: public Hists {
public:
    // use the same constructor arguments as Hists for forwarding:
    SVecQAnalysisHistsNew(Context & ctx, const string & dirname);

    virtual void fill(EventCalc & ev);
};


#endif
