	// Trieda cParameter
#ifndef __cparameter_h__
#define __cparameter_h__
#include "../vst2.x/audioeffectx.h"
#include <math.h>
#include <stdio.h>
#include "functions.h"

enum
{
	kParamOscOctave = 0,
	kParamOscCoarse,
	kParamOscFine,
	kParamOscPan,
	kParamOscLevel,
	kParamOscWaveform,
	kParamOscSync,
	kParamEnvAttack,
	kParamEnvDecay,
	kParamEnvSustain,
	kParamEnvTime,
	kParamEnvRelease,

	kParamLfoRange,
	kParamLfoRate,
	kParamLfoPhase,
	kParamLfoDelay,
	kParamLfoFade,
	kParamLfoWaveform,
	kParamLfoMono,

	kParamMasterVolume,
	kParamTypesCount
};

class cParameter
{
	public:
		cParameter(int pId);
		~cParameter();
		float getValue();
		void setValue(float pValue);
		void getDisplayValue(char* text);
		void getName(char* text);
		void getLabel(char* text);
		void setType(int pType, int pCompId);

		void getSyncDisplayValue(char *text);

		float value;
		int id;	
		int type;
		int compId;
};
 
#endif