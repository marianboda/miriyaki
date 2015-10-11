#include "cParameter.h"

cParameter::cParameter(int pId)
{
  id = pId;
  value = 0.0f;
};
cParameter::~cParameter()
{};
void cParameter::setValue(float pValue)
{
  value = pValue;
}
float cParameter::getValue()
{
  return value;
}
void cParameter::getDisplayValue(char* text)
{
	switch(type)
	{
		case kParamOscOctave:		floatToOctave(value,text);break;
		case kParamOscCoarse:		floatToCoarse(value,text);break;
		case kParamOscFine:			floatToFine(value,text);break;
		case kParamOscPan:			floatToPan(value,text);break;
		case kParamOscLevel:		floatToLevel(value,text);break;
		case kParamOscSync:			getSyncDisplayValue(text);break;
		case kParamOscWaveform:		floatToOscWaveform(value,text);break;
		case kParamEnvAttack:		
		case kParamEnvDecay:		
		case kParamEnvRelease:		floatToEnvTime(value,text);break;
		case kParamEnvSustain:		floatToLevel(value,text);break;
		case kParamEnvTime:			floatToFine(value,text);break;
		case kParamLfoDelay:
		case kParamLfoFade:			floatToEnvTime(value,text);break;

		default:					floatToFloat(value,text);break;
	}
}
void cParameter::getName(char* text)
{
	switch(type)
	{
		case kParamOscOctave:		sprintf (text, "o%i oct", compId);break;
		case kParamOscCoarse:		sprintf (text, "o%i crs", compId);break;
		case kParamOscFine:			sprintf (text, "o%i fine", compId);break;
		case kParamOscPan:			sprintf (text, "o%i pan", compId);break;
		case kParamOscLevel:		sprintf (text, "o%i level", compId);break;
		case kParamOscWaveform:		sprintf (text, "o%i wave", compId);break;
		case kParamOscSync:			sprintf (text, "o%i sync", compId);break;

		case kParamEnvAttack:		sprintf (text, "e%i atk", compId);break;
		case kParamEnvDecay:		sprintf (text, "e%i dec", compId);break;
		case kParamEnvSustain:		sprintf (text, "e%i sus", compId);break;
		case kParamEnvTime:			sprintf (text, "e%i tim", compId);break;
		case kParamEnvRelease:		sprintf (text, "e%i rel", compId);break;

		case kParamMasterVolume:	sprintf (text, "master", compId);break;

		default:				sprintf (text, "u %i", type);break;
	}
}
void cParameter::getLabel(char* text)
{
	vst_strncpy (text, "Label", kVstMaxParamStrLen);
	switch(type)
	{
		case kParamOscOctave:		vst_strncpy (text, "Octave", kVstMaxParamStrLen);break;
		case kParamOscCoarse:		vst_strncpy (text, "Semitone", kVstMaxParamStrLen);break;
		case kParamOscFine:			vst_strncpy (text, "Cents", kVstMaxParamStrLen);break;
		case kParamOscPan:			vst_strncpy (text, "%", kVstMaxParamStrLen);break;
		case kParamOscLevel:		vst_strncpy (text, "%", kVstMaxParamStrLen);break;
		case kParamOscWaveform:		vst_strncpy (text, "Shape", kVstMaxParamStrLen);break;
		case kParamOscSync:			vst_strncpy (text, "", kVstMaxParamStrLen);break;

		case kParamEnvAttack:		sprintf (text, "", compId);break;
		case kParamEnvDecay:		sprintf (text, "", compId);break;
		case kParamEnvSustain:		sprintf (text, "", compId);break;
		case kParamEnvTime:			sprintf (text, "", compId);break;
		case kParamEnvRelease:		sprintf (text, "", compId);break;

		case kParamMasterVolume:	sprintf (text, "dB", compId);break;

		default:				sprintf (text, "", type);break;
	}

}
void cParameter::setType(int pType, int pCompId)
{
	type = pType;
	compId = pCompId;
}

void cParameter::getSyncDisplayValue(char *text)
{
	VstInt32 i;

	i = (VstInt32)floor(value*4);
	if (i>3)
		i = 3;
	if (i>=compId)
		i++;
	if (i==0)
		sprintf(text,"off",(int)i);
	else
		sprintf(text,"osc %i",(int)i);
}