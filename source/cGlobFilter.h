// Trieda cGlobFilter
#ifndef __cglobfilter_h__
#define __cglobfilter_h__
#include "../vst2.x/audioeffectx.h"
#include <math.h>
#include "cGlobals.h"

class cGlobFilter
{
  public:
    cGlobFilter();
    ~cGlobFilter();

	void killDenormal(double &val);
	void killDenormal(float &val);

	double inL1;
	double inL2;
	double outL1;
	double outL2;

	double inR1;
	double inR2;
	double outR1;
	double outR2;

	double b0,a1,a2,b1,b2,w0,sin_w0,cos_w0, alpha;

	void process(float *signal);
	void setCoefficients(double pCutOff, double pQ, VstInt32 pType);
	void reset();
};
 
#endif