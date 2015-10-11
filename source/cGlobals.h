// Trieda cGlobals

#ifndef __cglobals_h__
#define __cglobals_h__
#include "../vst2.x/audioeffectx.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "cWaveform.h"
#include "cParameter.h"
#include "modulationConstants.h"
#include <iostream>
#include <fstream>
using namespace std;
#include <sys/stat.h> 

enum
{
	MAX_POLYPHONY = 10,
	kNumPrograms = 64,
	kNumOutputs = 2,

	kOsc1Octave = 0,
	kOsc2Octave,
	kOsc3Octave,
	kOsc4Octave,
	kOsc1Coarse,
	kOsc2Coarse,
	kOsc3Coarse,
	kOsc4Coarse,
	kOsc1Fine,
	kOsc2Fine,
	kOsc3Fine,
	kOsc4Fine,
	kOsc1Waveform,
	kOsc2Waveform,
	kOsc3Waveform,
	kOsc4Waveform,
	kOsc1Level,
	kOsc2Level,
	kOsc3Level,
	kOsc4Level,
	kOsc1Pan,
	kOsc2Pan,
	kOsc3Pan,
	kOsc4Pan,
	kOsc1Sync,
	kOsc2Sync,
	kOsc3Sync,
	kOsc4Sync,

	kEnv1Attack,
	kEnv2Attack,
	kEnv3Attack,
	kEnv4Attack,
	kEnv1Decay,
	kEnv2Decay,
	kEnv3Decay,
	kEnv4Decay,
	kEnv1Sustain,
	kEnv2Sustain,
	kEnv3Sustain,
	kEnv4Sustain,
	kEnv1Time,
	kEnv2Time,
	kEnv3Time,
	kEnv4Time,
	kEnv1Release,
	kEnv2Release,
	kEnv3Release,
	kEnv4Release,

	kLfo1Range,
	kLfo2Range,
	kLfo3Range,
	kLfo4Range,
	kLfo1Rate,
	kLfo2Rate,
	kLfo3Rate,
	kLfo4Rate,
	kLfo1PhaseShift,
	kLfo2PhaseShift,
	kLfo3PhaseShift,
	kLfo4PhaseShift,
	kLfo1Delay,
	kLfo2Delay,
	kLfo3Delay,
	kLfo4Delay,
	kLfo1Fade,
	kLfo2Fade,
	kLfo3Fade,
	kLfo4Fade,
	kLfo1Waveform,
	kLfo2Waveform,
	kLfo3Waveform,
	kLfo4Waveform,
	kLfo1Mono,
	kLfo2Mono,
	kLfo3Mono,
	kLfo4Mono,

	kFilter1Type,
	kFilter2Type,
	kFilter1CutOff,
	kFilter2CutOff,
	kFilter1Q,
	kFilter2Q,
	kFilter1KeyFollow,
	kFilter2KeyFollow,
	kFilter1Mix,
	kFilter2Mix,
	
	kFilterRouting,

	kModAmt01,
	kModAmt02,
	kModAmt03,
	kModAmt04,
	kModAmt05,
	kModAmt06,
	kModAmt07,
	kModAmt08,
	kModAmt09,
	kModAmt10,
	kModAmt11,
	kModAmt12,
	kModAmt13,
	kModAmt14,
	kModAmt15,
	kModAmt16,
	kModAmt17,
	kModAmt18,
	kModAmt19,
	kModAmt20,
	kModAmt21,
	kModAmt22,
	kModAmt23,
	kModAmt24,
	kModAmt25,
	kModAmt26,
	kModAmt27,
	kModAmt28,
	kModAmt29,
	kModAmt30,
	kModAmt31,
	kModAmt32,
	kModSource01,
	kModSource02,
	kModSource03,
	kModSource04,
	kModSource05,
	kModSource06,
	kModSource07,
	kModSource08,
	kModSource09,
	kModSource10,
	kModSource11,
	kModSource12,
	kModSource13,
	kModSource14,
	kModSource15,
	kModSource16,
	kModSource17,
	kModSource18,
	kModSource19,
	kModSource20,
	kModSource21,
	kModSource22,
	kModSource23,
	kModSource24,
	kModSource25,
	kModSource26,
	kModSource27,
	kModSource28,
	kModSource29,
	kModSource30,
	kModSource31,
	kModSource32,
	kModDestination01,
	kModDestination02,
	kModDestination03,
	kModDestination04,
	kModDestination05,
	kModDestination06,
	kModDestination07,
	kModDestination08,
	kModDestination09,
	kModDestination10,
	kModDestination11,
	kModDestination12,
	kModDestination13,
	kModDestination14,
	kModDestination15,
	kModDestination16,
	kModDestination17,
	kModDestination18,
	kModDestination19,
	kModDestination20,
	kModDestination21,
	kModDestination22,
	kModDestination23,
	kModDestination24,
	kModDestination25,
	kModDestination26,
	kModDestination27,
	kModDestination28,
	kModDestination29,
	kModDestination30,
	kModDestination31,
	kModDestination32,

	kMasterVolume,
	
	kNumParams,

};
//---------------------------------------------
char floatToSync(VstInt32 oscId, float value);
class cGlobals
{
  public:
    cGlobals();
    ~cGlobals();

	void getDestName(VstInt32 index, char* text);
	void interpolate();
	void interpolateKnob(float* fValue,float* rValue, float *step);
	void interpolateFineKnob(VstInt32 osc);

	bool fileExists(string strFilename);
	void dumpPreset();

	void updateSrcUsed();
	void updateDstUsed();
	void updateOscTune(VstInt32 oscId);

	void updateSynchro();
	char getSyncSource(VstInt32 oscId);
	char *currentProgramName;

	cWaveform *waveform;
	float sampleRate;
	float sampleTime;
	double masterFrequency;
	float lfoFrequencyMultipyStep;
	bool initialised;
	float envTimesExponent;

	VstInt32 synchro[5][5];// [zdroj][ciel]
	VstInt32 oscReset[5]; // 0 - nic, 1 - prirodzene, 2 - vynutene

	VstInt64 lifeTimeCounter;
	VstInt32 iLfoWave[4];

	// Oscilatory ----------------------------------------
			VstInt32 iOctave[4];
			VstInt32 iCoarse[4];
			VstInt32 iOscWave[4];
			float zOscTune[4];
			bool oscPhaseReset[4];
			float rOscFineKnobValue[4];
			float rOscFineKnobStep[4];
			float rOscPanKnobValue[4];
			float rOscPanKnobStep[4];
			float rOscLevelKnobValue[4];
			float rOscLevelKnobStep[4];

	// Obalky -----------------------------------------------
			float rEnvSustainKnobValue[4];
			float rEnvSustainKnobStep[4];
	// LFO ------------------------------------------------
			float zLfoRate[4];
			float zLfoTargetRate[4];
			float zLfoRateStep[4];

			float rLfoPhaseKnobValue[4];
			float rLfoPhaseKnobStep[4];

			float lfoValue[4];
	// Filter ------------------------------------------------
			VstInt32 iFilterType[2];
			VstInt32 iFilterRouting;

			float rFilterCutOffKnobStep[2];
			float rFilterCutOffKnobValue[2];
			float rFilterQKnobStep[2];
			float rFilterQKnobValue[2];
			float rFilterKeyFollowKnobStep[2];
			float rFilterKeyFollowKnobValue[2];
			float rFilterMixKnobStep[2];
			float rFilterMixKnobValue[2];

	// Modulacie ------------------------------------------------
			VstInt32	iSrc[32];
			VstInt32	iDst[32];
			float		fAmt[32];
			float		rAmt[32];
			float		rAmtStep[32];

			bool srcUsed[jMS_total];
			bool dstUsed[jMD_total];
	// ------------------------------------------------

	cParameter *parameters[kNumParams];

	float rAllOscVolume;
	float fMasterVolume;

	float midiModWheel;
	float midiController[128];
	float midiAfterTouch;
	float midiPitchBend;
};

extern cGlobals *Glob;

#endif