#include "cEnvelope.h"

cEnvelope::cEnvelope(float *pAttack, float *pDecay, float *pSustain, float *pTime, 
					 float *pRelease, float *pEnvValue, bool *pPlaying)
{
	attack = pAttack;
	decay = pDecay;
	sustain = pSustain;
	time = pTime;
	release = pRelease;

	playing = pPlaying;
	getValue = &cEnvelope::getAttack;
	envValue = pEnvValue;
	timeCounter = 0.f;
	offCounter = 0;

	modAttack = 0.f;
	modDecay = 0.f;
	modSustain = 0.f;
	modTime = 0.f;
	modRelease = 0.f;

};
cEnvelope::~cEnvelope()
{
};
void cEnvelope::play()
{
	*playing = true;
	getValue = &cEnvelope::getAttack;
	*envValue = 0.0f;

	oldTotalAttack = max(min(*attack + modAttack,1.0f),0.f);
	if (oldTotalAttack == 0.f)	attackStep = 1.0f;
	else						attackStep = 1.0f / (powf(oldTotalAttack,3)*12*Glob->sampleRate);

}
void cEnvelope::releaseNote()
{
	getValue = &cEnvelope::getRelease;

	oldTotalRelease = max(min(*release + modRelease,1.0f),0.f);
	if (oldTotalRelease == 0.f)	releaseStep = 1.0f;
	else						releaseStep = 1.0f / (powf(oldTotalRelease,3)*12*Glob->sampleRate);

}
void cEnvelope::getAttack()
{
	float newTotalAttack = max(min(*attack + modAttack,1.0f),0.f);
	if (oldTotalAttack != newTotalAttack)
	{
		if (newTotalAttack == 0.f)	attackStep = 1.0f;
		else						attackStep = 1.0f / (powf(newTotalAttack,3)*12*Glob->sampleRate);
		oldTotalAttack = newTotalAttack;
	}

	*envValue += attackStep;
	if (*envValue >= 1.f)
	{
		oldTotalDecay = max(min(*decay + modDecay,1.0f),0.f);
		float realSustain = max(min(*sustain + modSustain,1.f),0.f);

		if (oldTotalDecay == 0.f)	
		{
			getValue = &cEnvelope::getSustain;
			timeCounter = 0.f;

			oldTotalTime = max(min(*time + modTime,1.0f),0.f);
			float tempTime = oldTotalTime * 2 - 1.0f;
			
			if		(abs(tempTime)<0.03f)	timeStep = 0.f;
			else if (tempTime == 1.0f)		timeStep = 1.0f;
			else if (tempTime == -1.0f)		timeStep = -1.0f;
			else if (tempTime >0 )			timeStep = (float)(1.0f / (powf(1.0f-tempTime,3)*50*Glob->sampleRate));
			else							timeStep = (float)(1.0f / (powf(-1.0f-tempTime,3)*50*Glob->sampleRate));

			getSustain();
		}
		else
		{
			float fDE = powf(oldTotalDecay,3)*12*Glob->sampleRate;
			float realSustain = max(min(*sustain + modSustain,1.f),0.f);

			decayEnd = (VstInt32) fDE;
			decayStep = (1.0f - realSustain) / fDE;		
			decayCounter = 0;
			getValue = &cEnvelope::getDecay;
			getDecay();
		}
	}
}
void cEnvelope::getDecay()
{
	decayCounter += 1;

	float newTotalDecay = max(min(*decay + modDecay,1.0f),0.f);
	if (oldTotalDecay != newTotalDecay)
	{
		float realSustain = max(min(*sustain + modSustain,1.f),0.f);
		if (newTotalDecay == 0.f)	decayStep = 1.f;
		else						decayStep = (1.0f - realSustain) / (powf(newTotalDecay,3)*12*Glob->sampleRate);
		oldTotalDecay = newTotalDecay;
	}

	float realSustain = max(min(*sustain + modSustain,1.f),0.f);

	*envValue -= decayStep;

	if (*envValue <= realSustain)
	{
		if  ( (decayStep > 0.f)||(decayCounter >= decayEnd) )
		{
			getValue = &cEnvelope::getSustain;
			timeCounter = 0.f;

			oldTotalTime = max(min(*time + modTime,1.0f),0.f);
			float tempTime = oldTotalTime * 2 - 1.0f;
			
			if		(abs(tempTime)<0.03f)	timeStep = 0.f;
			else if (tempTime == 1.0f)		timeStep = 1.0f;
			else if (tempTime == -1.0f)		timeStep = -1.0f;
			else if (tempTime >0 )			timeStep = (float)(1.0f / (powf(1.0f-tempTime,3)*50*Glob->sampleRate));
			else							timeStep = (float)(1.0f / (powf(-1.0f-tempTime,3)*50*Glob->sampleRate));
			getSustain();
		}
	}
}
void cEnvelope::getSustain()
{
float newTotalTime =  max(min(*time + modTime,1.0f),0.f);
	if (newTotalTime != oldTotalTime)
	{
		float tempTime = newTotalTime * 2 - 1.0f;
		if		(abs(tempTime)<0.03f)	timeStep = 0.f;
		else if (tempTime == 1.0f)		timeStep = 1.0f;
		else if (tempTime == -1.0f)		timeStep = -1.0f;
		else if (tempTime >0 )			timeStep = (float)(1.0f / (powf(1.0f-tempTime,3)*50*Glob->sampleRate));
		else							timeStep = (float)(1.0f / (powf(-1.0f-tempTime,3)*50*Glob->sampleRate));
	}

	float realSustain = max(min(*sustain + modSustain,1.f),0.f);

	timeCounter += timeStep;
	*envValue = realSustain + timeCounter;

	if (*envValue <= 0.f)
	{
		*envValue = 0.f;
		getValue = &cEnvelope::getOff;
		*playing = false;
	}
	else if (*envValue >= 1.f)
	{
		*envValue = 1.f;
	}
}
void cEnvelope::getRelease()
{
	float newTotalRelease = max(min(*release + modRelease,1.0f),0.f);
	if (newTotalRelease != oldTotalRelease)
	{
		if (newTotalRelease == 0.f)	releaseStep = 1.0f;
		else						releaseStep = 1.0f / (powf(newTotalRelease,3)*12*Glob->sampleRate);
		oldTotalRelease = newTotalRelease;
	}

	*envValue -= releaseStep;
	if (*envValue <= 0.f)
	{
		*envValue = 0.f;
		getValue = &cEnvelope::getOff;
		*playing = false;
	}
}
void cEnvelope::getOff()
{
}
