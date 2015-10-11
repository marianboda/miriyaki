// Trieda cVoice
#ifndef __cvoice_h__
#define __cvoice_h__
#include "../vst2.x/audioeffectx.h"
#include <math.h>
#include "cOscillator.h"
#include "cEnvelope.h"
#include "cLFO.h"
#include "cFilter.h"
#include "cModulation.h"

#include "cGlobals.h"

class cVoice
{
  public:
    cVoice();
    ~cVoice();
	void getSample(float *out);
	void playNote(VstInt32 pNote,VstInt32 pVelocity, VstInt32 pDelta, VstInt64 noteBirth);
	void changeNote(VstInt32 pNote,VstInt32 pVelocity, VstInt32 pDelta, VstInt64 noteBirth);
	void stopNote();
	void stopGenerating();
	void fadeOut();
	void stopAll();
	bool isGenerating;
	bool isPlaying;
	bool isPressed;
	bool isFadingOut;
	VstInt32 getNote();
	VstInt64 noteBirth;

	float env1Value;
	float env2Value;
	float env3Value;
	float env4Value;

	bool env1Playing;
	bool env2Playing;
	bool env3Playing;
	bool env4Playing;

  private:
    cOscillator *osc1, *osc2, *osc3, *osc4;
	cEnvelope *env1, *env2, *env3, *env4;
	cLFO *lfo[4];
	cFilter *filter[2];
	cModulation *mod;

    VstInt32 note;
	VstInt32 velocity;
	VstInt32 delta;
	VstInt32 phase;
	double keyFlwMultiplier;

	float noteTune;
	float finalTune;
	float fader;

	float sampleRate;

	bool filtersPlaying;

	float lfoValue[4];

	float modInNote;
	float modInVelocity;

	float modOutAmpVol;
	float modOutPitch;

};
 
#endif