// Synth

#include "mirsynth.h"
#include <math.h>

//-------------------------------------------------------------------------------------------------------
AudioEffect* createEffectInstance (audioMasterCallback audioMaster)
{
	return new MirSynth (audioMaster);
}

//-----------------------------------------------------------------------------------------
// MirSynthProgram
//-----------------------------------------------------------------------------------------
MirSynthProgram::MirSynthProgram ()
{
			for (int i=0;i<kNumParams;i++)
			{
				params[i] = 0.5f;
			}
			params[kEnv1Attack] = 0.0f;
			params[kEnv2Attack] = 0.0f;
			params[kEnv3Attack] = 0.0f;
			params[kEnv4Attack] = 0.0f;
			params[kEnv1Release] = 0.2f;
			params[kEnv2Release] = 0.2f;
			params[kEnv3Release] = 0.2f;
			params[kEnv4Release] = 0.2f;

			params[kOsc1Sync] = 0.0f;
			params[kOsc2Sync] = 0.0f;
			params[kOsc3Sync] = 0.0f;
			params[kOsc4Sync] = 0.0f;
			params[kOsc1Level] = 0.8f;
			params[kOsc2Level] = 0.0f;
			params[kOsc3Level] = 0.0f;
			params[kOsc4Level] = 0.0f;

			params[kLfo1Range] = 0.0f;
			params[kLfo2Range] = 0.0f;
			params[kLfo3Range] = 0.0f;
			params[kLfo4Range] = 0.0f;

			params[kLfo1Rate] = 0.1f;
			params[kLfo2Rate] = 0.1f;
			params[kLfo3Rate] = 0.1f;
			params[kLfo4Rate] = 0.1f;

			params[kLfo1Waveform] = 0.0f;
			params[kLfo2Waveform] = 0.0f;
			params[kLfo3Waveform] = 0.0f;
			params[kLfo4Waveform] = 0.0f;

			params[kLfo1Mono] = 0.0f;

			params[kFilter1Type] = 0.0f;
			params[kFilter2Type] = 0.2f;

			params[kFilter1Mix] = 1.0f;
			params[kFilter2Mix] = 1.0f;

			for (VstInt32 i=0;i<32;i++)
			{
				params[kModDestination01+i] = 0.0f;
				params[kModSource01+i] = 0.0f;
			}

	
	vst_strncpy (name, "Default", kVstMaxProgNameLen);
}

//-----------------------------------------------------------------------------------------
// MirSynth
//-----------------------------------------------------------------------------------------
MirSynth::MirSynth (audioMasterCallback audioMaster)
: AudioEffectX (audioMaster, kNumPrograms, kNumParams)
{
	out_buffer = new float [2];
	voice_buffer = new float [2];
	globals = new cGlobals();
	Glob = globals;
	Glob->sampleRate = getSampleRate();
	Glob->sampleTime = 1.0f / Glob->sampleRate;

	lfo[0] = new cLFO(1,	&(Glob->zLfoRate[0]),
							&(Glob->parameters[kLfo1PhaseShift]->value),
							&(Glob->parameters[kLfo1Delay]->value),
							&(Glob->parameters[kLfo1Fade]->value),
							&(Glob->iLfoWave[0]),
							&(Glob->parameters[kLfo1Mono]->value),
							&(Glob->lfoValue[0]));
	lfo[1] = new cLFO(2,	&(Glob->zLfoRate[1]),
							&(Glob->parameters[kLfo2PhaseShift]->value),
							&(Glob->parameters[kLfo2Delay]->value),
							&(Glob->parameters[kLfo2Fade]->value),
							&(Glob->iLfoWave[1]),
							&(Glob->parameters[kLfo2Mono]->value),
							&(Glob->lfoValue[1]));
	lfo[2] = new cLFO(3,	&(Glob->zLfoRate[2]),
							&(Glob->parameters[kLfo3PhaseShift]->value),
							&(Glob->parameters[kLfo3Delay]->value),
							&(Glob->parameters[kLfo3Fade]->value),
							&(Glob->iLfoWave[2]),
							&(Glob->parameters[kLfo3Mono]->value),
							&(Glob->lfoValue[2]));
	lfo[3] = new cLFO(4,	&(Glob->zLfoRate[3]),
							&(Glob->parameters[kLfo4PhaseShift]->value),
							&(Glob->parameters[kLfo4Delay]->value),
							&(Glob->parameters[kLfo4Fade]->value),
							&(Glob->iLfoWave[3]),
							&(Glob->parameters[kLfo4Mono]->value),
							&(Glob->lfoValue[3]));
	for (VstInt32 i=0;i<4;i++)
	{
		if (lfo[i])	lfo[i]->resetGlobal();
	}

	filter[0] = new cGlobFilter();
	filter[1] = new cGlobFilter();

	programs = new MirSynthProgram[kNumPrograms];

	char *str;
	str = new char[kVstMaxProgNameLen];
	for (VstInt32 i = 0; i < 16; i++)
	{
		sprintf(str, "Preset %.2d", i);
		vst_strncpy (programs[i].name, str, kVstMaxProgNameLen);
		channelPrograms[i] = i;
	}

	if (programs) 
	{
		defaultPresets();
		defaultPresets2();
		defaultPresets3();
	/*	defaultPresets4();
		defaultPresets5();
		defaultPresets6();
		defaultPresets7();
		defaultPresets8();
		defaultPresets9();
		defaultPresets10();*/
	}

	if (audioMaster)
	{
		setNumInputs (0);
		setNumOutputs (kNumOutputs);
		canProcessReplacing ();
		isSynth ();
		setUniqueID ('tst2');			
	}

	for (int i=0;i<MAX_POLYPHONY;i++)
  	  voices[i] = new cVoice();
	
	editor = new cMirEditor(this);

	initProcess ();
	suspend ();
}

//-----------------------------------------------------------------------------------------
MirSynth::~MirSynth ()
{
	if (programs) delete[] programs;
	if (out_buffer) delete out_buffer;
	if (voice_buffer) delete voice_buffer;
	for (int i=0;i<MAX_POLYPHONY;i++)
	{
		if (voices[i]) delete voices[i];
	}
	for (int i=0;i<4;i++)
	{
		if (lfo[i]) delete lfo[i];
	}
	for (int i=0;i<2;i++)
	{
		if (filter[i]) delete filter[i];
	}

	delete globals;	Glob = 0;
	if (editor) delete editor;
}

//-----------------------------------------------------------------------------------------
void MirSynth::setProgram (VstInt32 program)
{
	if (program < 0 || program >= kNumPrograms)
		return;
	
	MirSynthProgram *ap = &programs[program];
	curProgram = program;

	for (int i=0;i<kNumParams;i++)
	{
		setParameter(i,ap->params[i]);
	}
	vst_strncpy (Glob->currentProgramName, ap->name, kVstMaxProgNameLen);
}

//-----------------------------------------------------------------------------------------
void MirSynth::setProgramName (char* name)
{
	vst_strncpy (programs[curProgram].name, name, kVstMaxProgNameLen);
	vst_strncpy (Glob->currentProgramName,  name, kVstMaxProgNameLen);

}
//-----------------------------------------------------------------------------------------
void MirSynth::getProgramName (char* name)
{
	vst_strncpy (name, programs[curProgram].name, kVstMaxProgNameLen);
}

//-----------------------------------------------------------------------------------------
void MirSynth::getParameterLabel (VstInt32 index, char* label)
{
	Glob->parameters[index]->getLabel(label);
}

//-----------------------------------------------------------------------------------------
void MirSynth::getParameterDisplay (VstInt32 index, char* text)
{
	Glob->parameters[index]->getDisplayValue(text);
}

//-----------------------------------------------------------------------------------------
void MirSynth::getParameterName (VstInt32 index, char* label)
{
	Glob->parameters[index]->getName(label);
}

//-----------------------------------------------------------------------------------------
void MirSynth::setParameter (VstInt32 index, float value)
{
	MirSynthProgram *ap = &programs[curProgram];

	switch (index)
	{
		case kOsc1Octave:	setOctave(1,value); break;
		case kOsc1Coarse:	setCoarse(1,value); break;
		case kOsc1Fine:		setFine(1,value); 	break;
		case kOsc1Waveform:	setOscWaveform(1,value);	break;
		case kOsc1Level:	setOscLevel(1,value);	break;
		case kOsc1Pan:		setOscPan(1,value);	break;
		case kOsc1Sync:		setOscSync(1,value);	break;

		case kOsc2Octave:	setOctave(2,value); break;
		case kOsc2Coarse:	setCoarse(2,value); break;
		case kOsc2Fine:		setFine(2,value); 	break;
		case kOsc2Waveform:	setOscWaveform(2,value);	break;
		case kOsc2Level:	setOscLevel(2,value);	break;
		case kOsc2Pan:		setOscPan(2,value);	break;
		case kOsc2Sync:		setOscSync(2,value);	break;

		case kOsc3Octave:	setOctave(3,value); break;
		case kOsc3Coarse:	setCoarse(3,value); break;
		case kOsc3Fine:		setFine(3,value); 	break;
		case kOsc3Waveform:	setOscWaveform(3,value);	break;
		case kOsc3Level:	setOscLevel(3,value);	break;
		case kOsc3Pan:		setOscPan(3,value);	break;
		case kOsc3Sync:		setOscSync(3,value);	break;

		case kOsc4Octave:	setOctave(4,value); break;
		case kOsc4Coarse:	setCoarse(4,value); break;
		case kOsc4Fine:		setFine(4,value); 	break;
		case kOsc4Waveform:	setOscWaveform(4,value);	break;
		case kOsc4Level:	setOscLevel(4,value);	break;
		case kOsc4Pan:		setOscPan(4,value);	break;
		case kOsc4Sync:		setOscSync(4,value);	break;

		case kEnv1Attack:	setEnvAttack(1,value); break;
		case kEnv1Decay:	setEnvDecay(1,value); break;
		case kEnv1Sustain:	setEnvSustain(1,value); break;
		case kEnv1Time:		setEnvTime(1,value); break;
		case kEnv1Release:	setEnvRelease(1,value); break;

		case kEnv2Attack:	setEnvAttack(2,value); break;
		case kEnv2Decay:	setEnvDecay(2,value); break;
		case kEnv2Sustain:	setEnvSustain(2,value); break;
		case kEnv2Time:		setEnvTime(2,value); break;
		case kEnv2Release:	setEnvRelease(2,value); break;

		case kEnv3Attack:	setEnvAttack(3,value); break;
		case kEnv3Decay:	setEnvDecay(3,value); break;
		case kEnv3Sustain:	setEnvSustain(3,value); break;
		case kEnv3Time:		setEnvTime(3,value); break;
		case kEnv3Release:	setEnvRelease(3,value); break;

		case kEnv4Attack:	setEnvAttack(4,value); break;
		case kEnv4Decay:	setEnvDecay(4,value); break;
		case kEnv4Sustain:	setEnvSustain(4,value); break;
		case kEnv4Time:		setEnvTime(4,value); break;
		case kEnv4Release:	setEnvRelease(4,value); break;

		case kLfo1Range:		setLfoRange(1,value); break;
		case kLfo1Rate:			setLfoRate(1,value); break;
		case kLfo1PhaseShift:	setLfoPhaseShift(1,value); break;
		case kLfo1Delay:		setLfoDelay(1,value); break;
		case kLfo1Fade:			setLfoFade(1,value); break;
		case kLfo1Waveform:		setLfoWaveform(1,value);break;

		case kLfo2Range:		setLfoRange(2,value); break;
		case kLfo2Rate:			setLfoRate(2,value); break;
		case kLfo2PhaseShift:	setLfoPhaseShift(2,value); break;
		case kLfo2Delay:		setLfoDelay(2,value); break;
		case kLfo2Fade:			setLfoFade(2,value); break;
		case kLfo2Waveform:		setLfoWaveform(2,value);break;

		case kLfo3Range:		setLfoRange(3,value); break;
		case kLfo3Rate:			setLfoRate(3,value); break;
		case kLfo3PhaseShift:	setLfoPhaseShift(3,value); break;
		case kLfo3Delay:		setLfoDelay(3,value); break;
		case kLfo3Fade:			setLfoFade(3,value); break;
		case kLfo3Waveform:		setLfoWaveform(3,value);break;

		case kLfo4Range:		setLfoRange(4,value); break;
		case kLfo4Rate:			setLfoRate(4,value); break;
		case kLfo4PhaseShift:	setLfoPhaseShift(4,value); break;
		case kLfo4Delay:		setLfoDelay(4,value); break;
		case kLfo4Fade:			setLfoFade(4,value); break;
		case kLfo4Waveform:		setLfoWaveform(4,value);break;

		case kFilter1CutOff:	setFilterCutoff(1,value);break;
		case kFilter1Q:			setFilterQ(1,value);break;
		case kFilter1KeyFollow:	setFilterKeyFollow(1,value);break;
		case kFilter1Mix:		setFilterMix(1,value);break;
		case kFilter1Type:		setFilterType(1,value);break;

		case kFilter2CutOff:	setFilterCutoff(2,value);break;
		case kFilter2Q:			setFilterQ(2,value);break;
		case kFilter2KeyFollow:	setFilterKeyFollow(2,value);break;
		case kFilter2Mix:		setFilterMix(2,value);break;
		case kFilter2Type:		setFilterType(2,value);break;


		case kFilterRouting:	setFilterRouting(value);break;

		case kModDestination01:	
		case kModDestination02:	
		case kModDestination03:	
		case kModDestination04:	
		case kModDestination05:	
		case kModDestination06:	
		case kModDestination07:	
		case kModDestination08:	
		case kModDestination09:	
		case kModDestination10:	
		case kModDestination11:	
		case kModDestination12:	
		case kModDestination13:	
		case kModDestination14:	
		case kModDestination15:	
		case kModDestination16:	
		case kModDestination17:	
		case kModDestination18:	
		case kModDestination19:	
		case kModDestination20:	
		case kModDestination21:	
		case kModDestination22:	
		case kModDestination23:	
		case kModDestination24:	
		case kModDestination25:	
		case kModDestination26:	
		case kModDestination27:	
		case kModDestination28:	
		case kModDestination29:	
		case kModDestination30:	
		case kModDestination31:	
		case kModDestination32:	
								setModDst(index,value);break;
		case kModSource01:	
		case kModSource02:	
		case kModSource03:	
		case kModSource04:	
		case kModSource05:	
		case kModSource06:	
		case kModSource07:	
		case kModSource08:	
		case kModSource09:	
		case kModSource10:	
		case kModSource11:	
		case kModSource12:	
		case kModSource13:	
		case kModSource14:	
		case kModSource15:
		case kModSource16:	
		case kModSource17:	
		case kModSource18:	
		case kModSource19:	
		case kModSource20:	
		case kModSource21:	
		case kModSource22:	
		case kModSource23:	
		case kModSource24:	
		case kModSource25:	
		case kModSource26:	
		case kModSource27:	
		case kModSource28:	
		case kModSource29:	
		case kModSource30:	
		case kModSource31:	
		case kModSource32:	
								setModSrc(index,value);break;
		case kModAmt01:	
		case kModAmt02:	
		case kModAmt03:	
		case kModAmt04:	
		case kModAmt05:	
		case kModAmt06:	
		case kModAmt07:	
		case kModAmt08:	
		case kModAmt09:	
		case kModAmt10:	
		case kModAmt11:	
		case kModAmt12:	
		case kModAmt13:	
		case kModAmt14:	
		case kModAmt15:	
		case kModAmt16:	
		case kModAmt17:	
		case kModAmt18:	
		case kModAmt19:	
		case kModAmt20:	
		case kModAmt21:	
		case kModAmt22:	
		case kModAmt23:	
		case kModAmt24:	
		case kModAmt25:	
		case kModAmt26:	
		case kModAmt27:	
		case kModAmt28:	
		case kModAmt29:	
		case kModAmt30:	
		case kModAmt31:	
		case kModAmt32:	
								setModAmt(index,value);break;


		case kMasterVolume:	Glob->parameters[kMasterVolume]->setValue(value);
							ap->params[kMasterVolume] = value;	break;
		default: Glob->parameters[index]->value = ap->params[index] = value; break;
	}
	
	if(editor)
	{
		((cMirEditor *)editor)->setParameter(index, value);
	}
}

//-----------------------------------------------------------------------------------------
float MirSynth::getParameter (VstInt32 index)
{
	return Glob->parameters[index]->value;
}

//-----------------------------------------------------------------------------------------
bool MirSynth::getOutputProperties (VstInt32 index, VstPinProperties* properties)
{
	if (index < kNumOutputs)
	{
		vst_strncpy (properties->label, "miriyaki", 63);
		char temp[11] = {0};
		int2string (index + 1, temp, 10);
		vst_strncat (properties->label, temp, 63);

		properties->flags = kVstPinIsActive;
		if (index < 2)
			properties->flags |= kVstPinIsStereo;	
		return true;
	}
	return false;
}

//-----------------------------------------------------------------------------------------
bool MirSynth::getProgramNameIndexed (VstInt32 category, VstInt32 index, char* text)
{
	if (index < kNumPrograms)
	{
		vst_strncpy (text, programs[index].name, kVstMaxProgNameLen);
		return true;
	}
	return false;
}

//-----------------------------------------------------------------------------------------
bool MirSynth::getEffectName (char* name)
{
	vst_strncpy (name, "miriyaki", kVstMaxEffectNameLen);
	return true;
}

//-----------------------------------------------------------------------------------------
bool MirSynth::getVendorString (char* text)
{
	vst_strncpy (text, "bodaSynth", kVstMaxVendorStrLen);
	return true;
}

//-----------------------------------------------------------------------------------------
bool MirSynth::getProductString (char* text)
{
	vst_strncpy (text, "miriyaki", kVstMaxProductStrLen);
	return true;
}
//-----------------------------------------------------------------------------------------
VstInt32 MirSynth::getVendorVersion (){return 1;}
//-----------------------------------------------------------------------------------------
VstInt32 MirSynth::canDo (char* text)
{
	if (!strcmp (text, "receiveVstEvents"))
		return 1;
	if (!strcmp (text, "receiveVstMidiEvent"))
		return 1;
	if (!strcmp (text, "midiProgramNames"))
		return 1;
	return -1;	
}
//-----------------------------------------------------------------------------------------
VstInt32 MirSynth::getNumMidiInputChannels (){return 1;}
//-----------------------------------------------------------------------------------------
VstInt32 MirSynth::getNumMidiOutputChannels (){return 0;}

void MirSynth::turnOnLfoRateInterpolation(VstInt32 lfoId)
{
	int id = lfoId - 1;

	Glob->zLfoTargetRate[id] =  3 * Glob->parameters[kLfo1Range+id]->value
								+ Glob->parameters[kLfo1Rate+id]->value;
	Glob->zLfoRateStep[id] = abs((Glob->zLfoTargetRate[id] - Glob->zLfoRate[id]) * 100.0 * Glob->sampleTime);
}

void MirSynth::setOctave(VstInt32 oscId, float value)
{
	MirSynthProgram *ap = &programs[curProgram];

	int id = oscId-1;
	int oct = 0;
	switch (oscId)
	{
		case (1): oct = kOsc1Octave;	break;	
		case (2): oct = kOsc2Octave;	break;	
		case (3): oct = kOsc3Octave;	break;	
		case (4): oct = kOsc4Octave;	break;	
	}

	ap->params[oct]	= value;
	Glob->iOctave[id] = (VstInt32)floor(value*8-3.5f);
	if (Glob->iOctave[id] < -4)			Glob->iOctave[id] = -4;
	else if (Glob->iOctave[id] > 4)		Glob->iOctave[id] = 4;
	Glob->parameters[oct]->value = (4 + Glob->iOctave[id])/8.f;

	Glob->updateOscTune(id);

}

void MirSynth::setCoarse(VstInt32 oscId, float value)
{
	MirSynthProgram *ap = &programs[curProgram];
	int id = oscId-1;
	int crs = 0;
	switch (oscId)
	{
		case (1): crs = kOsc1Coarse;	break;	
		case (2): crs = kOsc2Coarse;	break;	
		case (3): crs = kOsc3Coarse;	break;	
		case (4): crs = kOsc4Coarse;	break;	
	}
	ap->params[crs]	= value;
	Glob->iCoarse[id] = (VstInt32)floor(value*24-11.5);
	if (Glob->iCoarse[id] < -12)		Glob->iCoarse[id] = -12;
	else if (Glob->iCoarse[id] > 12)	Glob->iCoarse[id] = 12;
	Glob->parameters[crs]->value = (12 + Glob->iCoarse[id])/24.f;

	Glob->updateOscTune(id);
}

void MirSynth::setFine(VstInt32 oscId, float value)
{
	MirSynthProgram *ap = &programs[curProgram];
	int id = oscId-1;
	switch (oscId)
	{
		case (1): Glob->parameters[kOsc1Fine]->value = ap->params[kOsc1Fine] = value; break;
		case (2): Glob->parameters[kOsc2Fine]->value = ap->params[kOsc2Fine] = value; break;
		case (3): Glob->parameters[kOsc3Fine]->value = ap->params[kOsc3Fine] = value; break;
		case (4): Glob->parameters[kOsc4Fine]->value = ap->params[kOsc4Fine] = value; break;
	}
	Glob->updateOscTune(id);
	Glob->rOscFineKnobStep[id] = abs((value - Glob->rOscFineKnobValue[id]) * 20.0 * Glob->sampleTime);
}

void MirSynth::setOscLevel(VstInt32 oscId, float value)
{
	MirSynthProgram *ap = &programs[curProgram];
	int id = oscId-1;
    Glob->parameters[kOsc1Level + id]->value = ap->params[kOsc1Level + id] = value;

	Glob->rOscLevelKnobStep[id] = abs((value - Glob->rOscLevelKnobValue[id]) * 20.0 * Glob->sampleTime);

}
void MirSynth::setOscPan(VstInt32 oscId, float value)
{
	MirSynthProgram *ap = &programs[curProgram];
	int id = oscId-1;
	Glob->parameters[kOsc1Pan + id]->value = ap->params[kOsc1Pan + id] = value;

	Glob->rOscPanKnobStep[id] = abs((value - Glob->rOscPanKnobValue[id]) * 20.0 * Glob->sampleTime);
}
void MirSynth::setOscSync(VstInt32 oscId, float value)
{
	MirSynthProgram *ap = &programs[curProgram];
	switch (oscId)
	{
		case (1): Glob->parameters[kOsc1Sync]->value = ap->params[kOsc1Sync] = value; break;
		case (2): Glob->parameters[kOsc2Sync]->value = ap->params[kOsc2Sync] = value; break;
		case (3): Glob->parameters[kOsc3Sync]->value = ap->params[kOsc3Sync] = value; break;
		case (4): Glob->parameters[kOsc4Sync]->value = ap->params[kOsc4Sync] = value; break;
	}
	Glob->updateSynchro();
}
void MirSynth::setOscWaveform(VstInt32 oscId, float value)
{
	MirSynthProgram *ap = &programs[curProgram];
	switch (oscId)
	{
		case (1): Glob->parameters[kOsc1Waveform]->value = ap->params[kOsc1Waveform] = value; break;
		case (2): Glob->parameters[kOsc2Waveform]->value = ap->params[kOsc2Waveform] = value; break;
		case (3): Glob->parameters[kOsc3Waveform]->value = ap->params[kOsc3Waveform] = value; break;
		case (4): Glob->parameters[kOsc4Waveform]->value = ap->params[kOsc4Waveform] = value; break;
	}
	Glob->iOscWave[oscId-1] = (VstInt32)floor(value * 5.f);
	if (Glob->iOscWave[oscId-1] > 4) Glob->iOscWave[oscId-1] = 4;

}
void MirSynth::setLfoWaveform(VstInt32 oscId, float value)
{
	MirSynthProgram *ap = &programs[curProgram];
	switch (oscId)
	{
		case (1): Glob->parameters[kLfo1Waveform]->value = ap->params[kLfo1Waveform] = value; break;
		case (2): Glob->parameters[kLfo2Waveform]->value = ap->params[kLfo2Waveform] = value; break;
		case (3): Glob->parameters[kLfo3Waveform]->value = ap->params[kLfo3Waveform] = value; break;
		case (4): Glob->parameters[kLfo4Waveform]->value = ap->params[kLfo4Waveform] = value; break;
	}
	Glob->iLfoWave[oscId-1] = (VstInt32)floor(value * 6.f);
	if (Glob->iLfoWave[oscId-1] > 5) Glob->iLfoWave[oscId-1] = 5;

}
void MirSynth::setEnvAttack(VstInt32 envId, float value)
{
	MirSynthProgram *ap = &programs[curProgram];
	int id = envId-1;
	int atk = 0;
	
	switch (envId)
	{
		case (1): atk = kEnv1Attack;	break;
		case (2): atk = kEnv2Attack;	break;
		case (3): atk = kEnv3Attack;	break;
		case (4): atk = kEnv4Attack;	break;
	}
	Glob->parameters[atk]->value = ap->params[atk] = value; 
}
void MirSynth::setEnvDecay(VstInt32 envId, float value)
{
	MirSynthProgram *ap = &programs[curProgram];
	int id = envId-1;
	int dec = 0;
	int sus = 0;
	
	switch (envId)
	{
		case (1): dec = kEnv1Decay; sus = kEnv1Sustain;	break;
		case (2): dec = kEnv2Decay; sus = kEnv2Sustain;	break;
		case (3): dec = kEnv3Decay; sus = kEnv3Sustain;	break;
		case (4): dec = kEnv4Decay; sus = kEnv4Sustain;	break;
	}
	Glob->parameters[dec]->value = ap->params[dec] = value; 
}

void MirSynth::setEnvSustain(VstInt32 envId, float value)
{
	MirSynthProgram *ap = &programs[curProgram];
	int id = envId-1;
	int dec = 0;
	int sus = 0;
	
	switch (envId)
	{
		case (1): dec = kEnv1Decay; sus = kEnv1Sustain;	break;
		case (2): dec = kEnv2Decay; sus = kEnv2Sustain;	break;
		case (3): dec = kEnv3Decay; sus = kEnv3Sustain;	break;
		case (4): dec = kEnv4Decay; sus = kEnv4Sustain;	break;
	}

	Glob->parameters[sus]->value = ap->params[sus] = value; 
	Glob->rEnvSustainKnobStep[id] = abs((value - Glob->rEnvSustainKnobValue[id]) * 20.0 * Glob->sampleTime);
}

void MirSynth::setEnvRelease(VstInt32 envId, float value)
{
	MirSynthProgram *ap = &programs[curProgram];
	int id = envId-1;
	int rel = 0;
	
	switch (envId)
	{
		case (1): rel = kEnv1Release;	break;
		case (2): rel = kEnv2Release;	break;
		case (3): rel = kEnv3Release;	break;
		case (4): rel = kEnv4Release;	break;
	}

	Glob->parameters[rel]->value = ap->params[rel] = value; 

}

void MirSynth::setEnvTime(VstInt32 envId, float value)
{
	MirSynthProgram *ap = &programs[curProgram];
	int id = envId-1;
	int tim = 0;
	
	switch (envId)
	{
		case (1): tim = kEnv1Time;	break;
		case (2): tim = kEnv2Time;	break;
		case (3): tim = kEnv3Time;	break;
		case (4): tim = kEnv4Time;	break;
	}

	Glob->parameters[tim]->value = ap->params[tim] = value; 

}

void MirSynth::setLfoRange(VstInt32 lfoId, float value)
{
	MirSynthProgram *ap = &programs[curProgram];
	int id = lfoId-1;
	int lRange = 0;
	
	switch (lfoId)
	{
		case (1): lRange = kLfo1Range; 	break;
		case (2): lRange = kLfo2Range;	break;
		case (3): lRange = kLfo3Range; 	break;
		case (4): lRange = kLfo4Range; 	break;
	}

	Glob->parameters[lRange]->value = ap->params[lRange] = value; 
	turnOnLfoRateInterpolation(lfoId);
}
void MirSynth::setLfoRate(VstInt32 lfoId, float value)
{
	MirSynthProgram *ap = &programs[curProgram];
	int id = lfoId-1;
	int lRange = 0;
	int lRate = 0;
	
	switch (lfoId)
	{
		case (1): lRange = kLfo1Range; lRate = kLfo1Rate; 	break;
		case (2): lRange = kLfo2Range; lRate = kLfo2Rate; 	break;
		case (3): lRange = kLfo3Range; lRate = kLfo3Rate; 	break;
		case (4): lRange = kLfo4Range; lRate = kLfo4Rate; 	break;
	}

	Glob->parameters[lRate]->value = ap->params[lRate] = value; 
	turnOnLfoRateInterpolation(lfoId);

}
void MirSynth::setLfoPhaseShift(VstInt32 lfoId, float value)
{
	MirSynthProgram *ap = &programs[curProgram];
	int id = lfoId-1;
	int lPhase = 0;
	switch (lfoId)
	{
		case (1): lPhase = kLfo1PhaseShift; 	break;
		case (2): lPhase = kLfo2PhaseShift; 	break;
		case (3): lPhase = kLfo3PhaseShift; 	break;
		case (4): lPhase = kLfo4PhaseShift; 	break;
	}

	Glob->parameters[lPhase]->value = ap->params[lPhase] = value;

	Glob->rLfoPhaseKnobStep[id] = abs((value - Glob->rLfoPhaseKnobValue[id]) * 20.0 * Glob->sampleTime);
}
void MirSynth::setLfoDelay(VstInt32 lfoId, float value)
{
	MirSynthProgram *ap = &programs[curProgram];
	int id = lfoId-1;
	int lDelay = 0;
	switch (lfoId)
	{
		case (1): lDelay = kLfo1Delay; 	break;
		case (2): lDelay = kLfo2Delay; 	break;
		case (3): lDelay = kLfo3Delay; 	break;
		case (4): lDelay = kLfo4Delay; 	break;
	}

	Glob->parameters[lDelay]->value = ap->params[lDelay] = value;
}
void MirSynth::setLfoFade(VstInt32 lfoId, float value)
{
	MirSynthProgram *ap = &programs[curProgram];
	int id = lfoId-1;
	int lFade = 0;
	switch (lfoId)
	{
		case (1): lFade = kLfo1Fade; 	break;
		case (2): lFade = kLfo2Fade; 	break;
		case (3): lFade = kLfo3Fade; 	break;
		case (4): lFade = kLfo4Fade; 	break;
	}

	Glob->parameters[lFade]->value = ap->params[lFade] = value;

}

void MirSynth::setFilterCutoff(VstInt32 filtId, float value)
{
	MirSynthProgram *ap = &programs[curProgram];
	int id = filtId-1;
	int lCutOff = 0;
	switch (filtId)
	{
		case (1): lCutOff = kFilter1CutOff; 	break;
		case (2): lCutOff = kFilter2CutOff; 	break;
	}

	Glob->parameters[lCutOff]->value = ap->params[lCutOff] = value;
	Glob->rFilterCutOffKnobStep[id] = abs((value - Glob->rFilterCutOffKnobValue[id]) * 10.0 * Glob->sampleTime);
}
void MirSynth::setFilterQ(VstInt32 filtId, float value)
{
	MirSynthProgram *ap = &programs[curProgram];
	int id = filtId-1;
	int lQ = 0;
	switch (filtId)
	{
		case (1): lQ = kFilter1Q; 	break;
		case (2): lQ = kFilter2Q; 	break;
	}

	Glob->parameters[lQ]->value = ap->params[lQ] = value;
	Glob->rFilterQKnobStep[id] = abs((value - Glob->rFilterQKnobValue[id]) * 20.0 * Glob->sampleTime);
}
void MirSynth::setFilterKeyFollow(VstInt32 filtId, float value)
{
	MirSynthProgram *ap = &programs[curProgram];
	int id = filtId-1;

	Glob->parameters[kFilter1KeyFollow+id]->value = ap->params[kFilter1KeyFollow+id] = value;

	Glob->rFilterKeyFollowKnobStep[id] = abs((value - Glob->rFilterKeyFollowKnobValue[id]) * 20.0 * Glob->sampleTime);
}
void MirSynth::setFilterMix(VstInt32 filtId, float value)
{
	MirSynthProgram *ap = &programs[curProgram];
	int id = filtId-1;

	Glob->parameters[kFilter1Mix+id]->value = ap->params[kFilter1Mix+id] = value;

	Glob->rFilterMixKnobStep[id] = abs((value - Glob->rFilterMixKnobValue[id]) * 20.0 * Glob->sampleTime);
}

void MirSynth::setFilterType(VstInt32 filtId, float value)
{
	MirSynthProgram *ap = &programs[curProgram];
	int id = filtId-1;
	int temp = 0;
	switch (filtId)
	{
		case (1): temp = kFilter1Type; 	break;
		case (2): temp = kFilter2Type; 	break;
	}
	Glob->iFilterType[id] = (VstInt32)floor(value * 4.f + 0.5);
	if (Glob->iFilterType[id] > 3) Glob->iFilterType[id] = 3;
	Glob->parameters[temp]->value = ap->params[temp] = Glob->iFilterType[id] / 4.f;
}
void MirSynth::setFilterRouting(float value)
{
	MirSynthProgram *ap = &programs[curProgram];

	Glob->iFilterRouting = (value < 0.5) ? 0 : 1;
	Glob->parameters[kFilterRouting]->value = ap->params[kFilterRouting] = (Glob->iFilterRouting) * 0.5f;
}
void MirSynth::setModSrc(VstInt32 index, float value)
{
	MirSynthProgram *ap = &programs[curProgram];

	Glob->iSrc[index-kModSource01] = (VstInt32)floor(value * 29.0f + 0.5f);
	if (Glob->iSrc[index-kModSource01] > 29) Glob->iSrc[index-kModSource01] = 29;
	Glob->parameters[index]->value = ap->params[index] = Glob->iSrc[index-kModSource01] / 29.f;
	Glob->updateSrcUsed();
}
void MirSynth::setModDst(VstInt32 index, float value)
{
	MirSynthProgram *ap = &programs[curProgram];

	Glob->iDst[index-kModDestination01] = (VstInt32)floor(value * 58.0f + 0.5f);
	if (Glob->iDst[index-kModDestination01] > 58) Glob->iDst[index-kModDestination01] = 58;
	Glob->parameters[index]->value = ap->params[index] = Glob->iDst[index-kModDestination01] / 58.0f;
	Glob->updateDstUsed();
}
void MirSynth::setModAmt(VstInt32 index, float value)
{
	MirSynthProgram *ap = &programs[curProgram];

	VstInt32 intAmt = glrint(value * 200);
	VstInt32 modId = index-kModAmt01;
	float nV = (intAmt/200.f);
	Glob->fAmt[modId] = nV * 2.f-1.f;
	Glob->parameters[index]->value = ap->params[index] = nV;
	
	Glob->rAmtStep[modId] = abs((value - Glob->rAmt[modId]) * 20.0 * Glob->sampleTime);
}

