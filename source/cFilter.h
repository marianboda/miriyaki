// Trieda cFilter
#ifndef __cfilter_h__
#define __cfilter_h__
#include "../vst2.x/audioeffectx.h"
#include <math.h>
#include "cGlobals.h"

class cFilter
{
  public:
    cFilter(VstInt32 pId, float *pCutOff, float *pQ, float *pKeyFollow, float *pMix, VstInt32 *pType, VstInt32 *pNote);
    ~cFilter();

	void killDenormal(double &val);
	void killDenormal(float &val);

    VstInt32 id;
    VstInt32 *type;
    float *cutOff;
    float *q;
    float *keyFollow;
    float *mix;    
	VstInt32 *note;

	double rCutOff;

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
	void setCoefficients();
	void reset();
	float getBuffSum();

	float modCutOff;
	float modQ;
	float modKeyFlw;
	float modMix;

	double oldKeyFlw;
	double oldCutOff;


	double fCutOff;

};
 
#endif