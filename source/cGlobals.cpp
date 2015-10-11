#include "cGlobals.h"


cGlobals::cGlobals()
{
	initialised = false;
	lifeTimeCounter = 0;
	waveform = new cWaveform();
	masterFrequency = 4.087899458 * 2; // Hz
	currentProgramName = new char[kVstMaxProgNameLen];

	rFilterCutOffKnobStep[0] = 0.5f;
	rFilterCutOffKnobValue[0] = 0.5f;
	rFilterCutOffKnobStep[1] = 0.5f;
	rFilterCutOffKnobValue[1] = 0.5f;

	int i;
		for (i=0;i<kNumParams;i++) 
		{
			parameters[i] = new cParameter(i);
		}
		parameters[kOsc1Octave]->setType(kParamOscOctave,1);
		parameters[kOsc1Coarse]->setType(kParamOscCoarse,1);
		parameters[kOsc1Fine]->setType(kParamOscFine,1);
		parameters[kOsc1Pan]->setType(kParamOscPan,1);
		parameters[kOsc1Level]->setType(kParamOscLevel,1);
		parameters[kOsc1Waveform]->setType(kParamOscWaveform,1);
		parameters[kOsc1Sync]->setType(kParamOscSync,1);

		parameters[kOsc2Octave]->setType(kParamOscOctave,2);
		parameters[kOsc2Coarse]->setType(kParamOscCoarse,2);
		parameters[kOsc2Fine]->setType(kParamOscFine,2);
		parameters[kOsc2Pan]->setType(kParamOscPan,2);
		parameters[kOsc2Level]->setType(kParamOscLevel,2);
		parameters[kOsc2Waveform]->setType(kParamOscWaveform,2);
		parameters[kOsc2Sync]->setType(kParamOscSync,2);

		parameters[kOsc3Octave]->setType(kParamOscOctave,3);
		parameters[kOsc3Coarse]->setType(kParamOscCoarse,3);
		parameters[kOsc3Fine]->setType(kParamOscFine,3);
		parameters[kOsc3Pan]->setType(kParamOscPan,3);
		parameters[kOsc3Level]->setType(kParamOscLevel,3);
		parameters[kOsc3Waveform]->setType(kParamOscWaveform,3);
		parameters[kOsc3Sync]->setType(kParamOscSync,3);

		parameters[kOsc4Octave]->setType(kParamOscOctave,4);
		parameters[kOsc4Coarse]->setType(kParamOscCoarse,4);
		parameters[kOsc4Fine]->setType(kParamOscFine,4);
		parameters[kOsc4Pan]->setType(kParamOscPan,4);
		parameters[kOsc4Level]->setType(kParamOscLevel,4);
		parameters[kOsc4Waveform]->setType(kParamOscWaveform,4);
		parameters[kOsc4Sync]->setType(kParamOscSync,4);

		parameters[kEnv1Attack]->setType(kParamEnvAttack,1);
		parameters[kEnv1Decay]->setType(kParamEnvDecay,1);
		parameters[kEnv1Sustain]->setType(kParamEnvSustain,1);
		parameters[kEnv1Time]->setType(kParamEnvTime,1);
		parameters[kEnv1Release]->setType(kParamEnvRelease,1);

		parameters[kEnv2Attack]->setType(kParamEnvAttack,2);
		parameters[kEnv2Decay]->setType(kParamEnvDecay,2);
		parameters[kEnv2Sustain]->setType(kParamEnvSustain,2);
		parameters[kEnv2Time]->setType(kParamEnvTime,2);
		parameters[kEnv2Release]->setType(kParamEnvRelease,2);

		parameters[kEnv3Attack]->setType(kParamEnvAttack,3);
		parameters[kEnv3Decay]->setType(kParamEnvDecay,3);
		parameters[kEnv3Sustain]->setType(kParamEnvSustain,3);
		parameters[kEnv3Time]->setType(kParamEnvTime,3);
		parameters[kEnv3Release]->setType(kParamEnvRelease,3);

		parameters[kEnv4Attack]->setType(kParamEnvAttack,4);
		parameters[kEnv4Decay]->setType(kParamEnvDecay,4);
		parameters[kEnv4Sustain]->setType(kParamEnvSustain,4);
		parameters[kEnv4Time]->setType(kParamEnvTime,4);
		parameters[kEnv4Release]->setType(kParamEnvRelease,4);

		parameters[kLfo1Range]->setType(kParamLfoRange,1);
		parameters[kLfo1Rate]->setType(kParamLfoRate,1);
		parameters[kLfo1PhaseShift]->setType(kParamLfoPhase,1);
		parameters[kLfo1Delay]->setType(kParamLfoDelay,1);
		parameters[kLfo1Fade]->setType(kParamLfoFade,1);
		parameters[kLfo1Fade]->setType(kParamLfoWaveform,1);
		parameters[kLfo1Fade]->setType(kParamLfoMono,1);

		parameters[kMasterVolume]->setType(kParamMasterVolume,1);

		for (i=0;i<4;i++)
		{
			oscPhaseReset[i] = false;
			lfoValue[i] = 0;
		}

		iFilterType[0] = iFilterType[1] = 1;
		rAllOscVolume = 1.f;
		
		for (i=0;i<5;i++)
		{
			for (int j=0;j<5;j++)
				synchro[i][j] = 0;
		}
		for (i=0;i<5;i++)
		{
			oscReset[i] = 0;
		}
};
cGlobals::~cGlobals()
{
	delete waveform;
	for (int i=0;i<kNumParams;i++)
		delete parameters[i];
};
void cGlobals::interpolate()
{
	for (int i=0;i<4;i++)
	{
		interpolateFineKnob(i);
		interpolateKnob(&(parameters[kOsc1Pan+i]->value),&rOscPanKnobValue[i], &rOscPanKnobStep[i]);
		interpolateKnob(&(parameters[kOsc1Level+i]->value),&rOscLevelKnobValue[i], &rOscLevelKnobStep[i]);

		interpolateKnob(&(parameters[kEnv1Sustain+i]->value),&rEnvSustainKnobValue[i], &rEnvSustainKnobStep[i]);

		interpolateKnob(&zLfoTargetRate[i],&zLfoRate[i], &zLfoRateStep[i]);
		interpolateKnob(&(parameters[kLfo1PhaseShift+i]->value),&rLfoPhaseKnobValue[i], &rLfoPhaseKnobStep[i]);
	}
	for (int i=0;i<2;i++)
	{
		interpolateKnob(&(parameters[kFilter1CutOff + i]->value),		&rFilterCutOffKnobValue[i],		&rFilterCutOffKnobStep[i]);
		interpolateKnob(&(parameters[kFilter1Q + i]->value),			&rFilterQKnobValue[i],			&rFilterQKnobStep[i]);
		interpolateKnob(&(parameters[kFilter1KeyFollow + i]->value),	&rFilterKeyFollowKnobValue[i],	&rFilterKeyFollowKnobStep[i]);
		interpolateKnob(&(parameters[kFilter1Mix + i]->value),			&rFilterMixKnobValue[i],		&rFilterMixKnobStep[i]);
	}
	for (int i=0;i<32;i++)
	{
		interpolateKnob(&fAmt[i],&rAmt[i], &rAmtStep[i]);
	}
};

void cGlobals::interpolateKnob(float* fValue,float* rValue, float *step)
{
	if (*fValue != *rValue)
		{
			if (*rValue - *fValue > *step)
				*rValue -= *step;
			else if (*fValue - *rValue > *step)
				*rValue += *step;
			else
				{
					*rValue = *fValue;
				}
		}
}
void cGlobals::interpolateFineKnob(VstInt32 osc)
{
	float *rValue = &(Glob->rOscFineKnobValue[osc]);
	float *fValue = &(Glob->parameters[kOsc1Fine + osc]->value);
	float *step = &(Glob->rOscFineKnobStep[osc]);

	if (*fValue != *rValue)
		{
			if (*rValue - *fValue > *step)
				*rValue -= *step;
			else if (*fValue - *rValue > *step)
				*rValue += *step;
			else
				*rValue = *fValue;
		}
	updateOscTune(osc);
}

void cGlobals::updateSynchro()
{
	char source[5];
	char s1=0,s2=0,s3=0,s4=0;

	for (int i=0;i<5;i++)
	{
		for (int j=0;j<5;j++)
			synchro[i][j] = 0;
	}

	source[1] = getSyncSource(1);
	source[2] = getSyncSource(2);
	source[3] = getSyncSource(3);
	source[4] = getSyncSource(4);
	
	for (int i=1;i<5;i++)
	{
		s1 = source[i];
		if ((s1 != 0) && (s1 != i))
		{
			synchro[s1][i] = 1;
			s2 = source[s1];
			if ((s2 != 0) && (s2 != i))
			{
				synchro[s2][i] = 1;
				s3 = source[s2];
				if ((s3 != 0) && (s3 != i))
				{
					synchro[s3][i] = 1;
				}
			}
		}
	}

}

char floatToSync(VstInt32 oscId, float value)
{
	char sourceId = (int)floor(value * 4);
			if (sourceId >= oscId)
				sourceId += 1;

	if (sourceId > 4)		sourceId = 4;
	if (sourceId == oscId)	sourceId = 0;
	return sourceId;
}

char cGlobals::getSyncSource(VstInt32 oscId)
{
	char source;
	switch (oscId)
	{
		case(1): source = floatToSync(1,parameters[kOsc1Sync]->value); break;
		case(2): source = floatToSync(2,parameters[kOsc2Sync]->value); break;
		case(3): source = floatToSync(3,parameters[kOsc3Sync]->value); break;
		case(4): source = floatToSync(4,parameters[kOsc4Sync]->value); break;
		default: source = 0; break;
	}
	return source;
}
void cGlobals::updateSrcUsed()
{
	for (int i=0;i<jMS_total;i++)
		srcUsed[i]= false;

	for (int i=0;i<32;i++)
	{
		if (iSrc[i] != 0)
			srcUsed[iSrc[i]] = true;
	}
}
void cGlobals::updateDstUsed()
{
	for (int i=0;i<jMD_total;i++)
		dstUsed[i]= false;

	for (int i=0;i<32;i++)
	{
		if (iDst[i] != 0)
			dstUsed[iDst[i]] = true;
	}
}


void cGlobals::updateOscTune(VstInt32 oscId)
{
	zOscTune[oscId] =	(Glob->parameters[kOsc1Octave+oscId]->value * 8.f - 4.f) + 
						(Glob->parameters[kOsc1Coarse+oscId]->value * 2.f - 1.f) + 
						(Glob->rOscFineKnobValue[oscId] * 2.f - 1.f)/12.f;
}

void cGlobals::dumpPreset()
{
	ofstream myfile;
	int i = 1;
	char str[255];
	sprintf(str, "c:\\preset%.3d.mir",i);
	while (fileExists(str) && i<1000)
	{
		i++;
		sprintf(str, "c:\\preset%.3d.mir",i);
	}
	myfile.open (str);
	if (myfile.is_open())
	{
		sprintf(str, "setProgramName(\"%s\");\n\n", currentProgramName );
		myfile << str;

		for (int i=0;i<kNumParams;i++)
		{
			sprintf(str, "setParameter(%d, %.5f);\n", i , parameters[i]->value );
			myfile << str;
		}
		myfile.close();
	}
}

bool cGlobals::fileExists(string strFilename) 
{
	struct stat stFileInfo;
	int intStat;
	intStat = stat(strFilename.c_str(),&stFileInfo);
	if(intStat == 0) return true;
	return false;
}

cGlobals *Glob;