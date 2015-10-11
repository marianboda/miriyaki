#include "cOscillator.h"

cOscillator::cOscillator(float *pLevel,float *pPan, VstInt32 *pWaveform,float *pSync, bool *phaseReset, char pId, float *modPitch)
{
	note = 0;
	phase = 0.f;
	
	level = pLevel;
	pan = pPan;
	waveform = pWaveform;
	sync = pSync;
	voicePitch = modPitch;
	id = pId;
};
cOscillator::~cOscillator()
{};

void cOscillator::getSample(float *out)
{
	float tempSample = 0.0f;
	if (Glob->oscReset[id])
	{
		phase = 0.f;
		Glob->oscReset[id] = false;
	}

	float totalLevel = *level * externalLevel;

	if (totalLevel > 0.f)
	{
		float totalPan = min(max(*pan + externalPan*0.5f,-1.f),1.f);

		float levelL = ((totalPan<=0.5) ? 1.0f : 2.0f - 2* totalPan) * totalLevel;
		float levelR = ((totalPan>=0.5) ? 1.0f : 2* totalPan) * totalLevel;


		if (phaseStep < 0.5)
		{
			switch (*waveform)
			{
				case (0):	tempSample = Glob->waveform->getSineSample(phase);break;
				case (1):	tempSample = Glob->waveform->getTriangleSample(phase, oldExponent);break;
				case (2):	tempSample = Glob->waveform->getSawSample(phase, oldExponent);break;
				case (3):	tempSample = Glob->waveform->getSquareSample(phase, oldExponent);break;
				case (4):	tempSample = Glob->waveform->getNoiseSample(phase);break;
				default :	tempSample = 0.0f;break;
			}
		}
		
		out[0] = levelL * tempSample;
		out[1] = levelR * tempSample;
	}
	else
	{
		out[0] = out[1] = 0.0f;
	}
};

void cOscillator::play()
{
	phase = 0.f;
	oldExponent = Glob->zOscTune[id-1] + *voicePitch + externalPitch;
	phaseStep = Glob->masterFrequency * pow(2.0,oldExponent) * Glob->sampleTime;
};

void cOscillator::shiftPhase()
{
	double newExponent = Glob->zOscTune[id-1] + *voicePitch + externalPitch;
	if (oldExponent != newExponent)
	{
		phaseStep = Glob->masterFrequency * pow(2.0,newExponent) * Glob->sampleTime;
		oldExponent = newExponent;
	}

	phase += phaseStep;
	if (phase >= 1.f)
	{
		phase -= floor(phase);
		for (int i=1;i<5;i++)
		{
			if (Glob->synchro[id][i] == 1)
			{
				Glob->oscReset[i] = true;
			}
		}
	}
}
