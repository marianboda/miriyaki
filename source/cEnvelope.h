// Trieda cEnvelope
#ifndef __cenvelope_h__
#define __cenvelope_h__
#include "../vst2.x/audioeffectx.h"
#include <math.h>
#include "cGlobals.h"

class cEnvelope
{
  public:
    cEnvelope(	float *pAttack,
				float *pDecay,
				float *pSustain,
				float *pTime,
				float *pRelease,
				float *pEnvValue,
				bool  *pPlaying);

    ~cEnvelope();
	void getAttack();
	void getDecay();
	void getSustain();
	void getRelease();
	void getOff();
	void play();
	void releaseNote();

	VstInt32 offCounter;

	float *attack;
	float *decay;
	float *sustain;
	float *time;
	float *release;
	void (cEnvelope::*getValue)();
	float *envValue;
	bool *playing;
	bool *stop;
	float timeCounter;

	float modAttack;
	float modDecay;
	float modSustain;
	float modTime;
	float modRelease;

	float oldTotalAttack;
	float oldTotalDecay;
	float oldTotalSustain;
	float oldTotalTime;
	float oldTotalRelease;

	float attackStep;
	float decayStep;
	float timeStep;
	float releaseStep;

	VstInt32 decayCounter;
	VstInt32 decayEnd;
	
  private:
};
 
#endif