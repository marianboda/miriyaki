// Trieda cLFO
#ifndef __clfo_h__
#define __clfo_h__
#include "../vst2.x/audioeffectx.h"
#include <math.h>
#include "cGlobals.h"

class cLFO
{
  public:
    cLFO(	VstInt32   pId,
			float *pRate,
			float *pPhaseShift,
			float *pDelay,
			float *pFade,
			VstInt32 *pWaveform,
			float *pMono,
			float *pLfoValue);
    ~cLFO();
	void reset();
	void resetGlobal();

	void generate();
	void getDelay();
	void getFade();
	void shiftPhase();
	float getSample();

	void (cLFO::*getValue)();

	VstInt32 baseSamples;
	float baseStep;
	double phase;
	float previousSample;
	float lastSample;
	bool isReset;
	double originalPhase;
	VstInt32 id;
	float *rate;
	float *phaseShift;
	float *delay;
	float *fade;
	VstInt32 *waveform;
	float *mono;
	float *lfoValue;
	float fadeAmp;

	float step;
	VstInt32 delaySamples;
	float oldDelay;
	float oldRate;

	float oldFade;
	float fadeStep;
	

	float modRate;
	float modPhaseShift;
	float modDelay;
	float modFade;
	
	VstInt32 timer;

};
 
#endif