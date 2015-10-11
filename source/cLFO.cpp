#include "cLFO.h"

cLFO:: cLFO(VstInt32 pId, float *pRate, float *pPhaseShift, float *pDelay, float *pFade, VstInt32 *pWaveform, float *pMono, float *pLfoValue)
{
	id = pId;

	rate = pRate;
	phaseShift = pPhaseShift;
	delay = pDelay;
	fade = pFade;
	waveform = pWaveform;
	mono = pMono;
	lfoValue = pLfoValue;
	originalPhase = 0.0;
	timer = 0;
	fadeAmp = 0.f;
	getValue = NULL;
	lastSample = Glob->waveform->getLfoSHSample();
	previousSample = Glob->waveform->getLfoSHSample();
	*lfoValue = 0;
	isReset = true;

	baseSamples = 12 * Glob->sampleRate;
};
cLFO::~cLFO()
{};
void cLFO::getDelay()
{
	float newDelay = *delay + modDelay;
	if (oldDelay != newDelay)
	{
		delaySamples = glrint(powf(newDelay,3) * baseSamples);
		oldDelay = newDelay;
	}
	timer += 1;
	if (timer > delaySamples)
		{
			getValue = &cLFO::getFade;
			timer = 0;
			getFade();
		}
}
void cLFO::getFade()
{
	float newFade = *fade + modFade;
	if (newFade != oldFade)
	{
		float lTime = powf(newFade,3);
		if (lTime > 0)
			fadeStep = 1.f/(lTime * baseSamples);
		else
			fadeStep = 1.f;
		oldFade = newFade;
	}

	fadeAmp += fadeStep;

	if (fadeAmp >= 1.f)
	{
		fadeAmp = 1.f;
		getValue = &cLFO::generate;
		generate();
	}
	else
	{
		shiftPhase();
		*lfoValue = fadeAmp * getSample();
	}
}
void cLFO::generate()
{
	shiftPhase();
	*lfoValue = getSample();

}

void cLFO::shiftPhase()
{
	float newRate = min(5.f,*rate + modRate*2);

	if (oldRate != newRate)
	{
		step = baseStep * powf(10.f,newRate);
		oldRate = newRate;
	}
	originalPhase += step;

	
	float realPhaseShift = *phaseShift + modPhaseShift;


	phase = originalPhase + realPhaseShift;
	if (phase > 1.)			
	{
		isReset = true;
		originalPhase -= floor(phase);
		phase -= floor(phase);
	}
	else if (phase < 0)
	{
		isReset = false;
		originalPhase -= floor(phase);
		phase -= floor(phase);
	}
	else
		isReset = false;

}

float cLFO::getSample()
{
	switch (*waveform)
	{
		case (0): return Glob->waveform->getLfoSineSample((float)phase);break;
		case (1): return Glob->waveform->getLfoTriangleSample((float)phase);break;
		case (2): return Glob->waveform->getLfoSawSample((float)phase);break;
		case (3): return Glob->waveform->getLfoSquareSample((float)phase);break;
		case (4):	if (isReset) 
						lastSample = Glob->waveform->getLfoSHSample();
					return lastSample;
					break;
		case (5):	if (isReset)
					{
						previousSample = lastSample;
						lastSample = Glob->waveform->getLfoSHSample();
					}
					return (float)(lastSample*phase + previousSample*(1-phase));
					break;
		default: return 0.f;break;
	}

}

void cLFO::reset()
{
	originalPhase = 0.f;
	timer = 0;
	*lfoValue = 0.f;
	getValue = &cLFO::getDelay;
	baseSamples = 12 * Glob->sampleRate;
	fadeAmp = 0;
	isReset = true;
	baseStep = 0.01 * Glob->sampleTime;

	oldRate = min(5.f,*rate + modRate*2);
	step = baseStep * powf(10.f,oldRate);

	oldDelay = *delay + modDelay;
	delaySamples = glrint(powf(oldDelay,3) * baseSamples);

	oldFade = *fade + modFade;
	float lTime = powf(oldFade,3);
	if (lTime > 0)
		fadeStep = 1.f/(lTime * baseSamples);
	else
		fadeStep = 1.f;

}

void cLFO::resetGlobal()
{
	originalPhase = 0.f;
	timer = 0;
	*lfoValue = 0.f;
	getValue = &cLFO::generate;
	fadeAmp = 0;
	isReset = true;
	baseStep = 0.01 * Glob->sampleTime;

	oldRate = min(5.f,*rate + modRate);
	step = baseStep * powf(10.f,oldRate);
}