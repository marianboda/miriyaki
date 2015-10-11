// Trieda cVoice
#ifndef __coscillator_h__
#define __coscillator_h__
#include "../vst2.x/audioeffectx.h"
#include <math.h>
#include "cGlobals.h"

class cOscillator
{
  public:
    cOscillator(float *pLevel,float *pPan,VstInt32 *pWaveform,float *pSync, bool *phaseReset, char pId, float *modPitch);
    ~cOscillator();
	void getSample(float *out);
	void play();
	void shiftPhase();
	double oldExponent;

	float externalPitch;
	float externalPan;
	float externalLevel;

  private:
	VstInt32 note;
	VstInt32 velocity;
	VstInt32 delta;
	float phase;
	float phaseStep;
	float sampleRate;

	float *level;
	float *pan;
	VstInt32 *waveform;
	float *sync;
	bool *phaseReset;
	float *voicePitch;

	char id;
};
 
#endif