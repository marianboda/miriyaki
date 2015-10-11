#include "cVoice.h"

cVoice::cVoice()
{
	note = 0;
	noteTune = 0.f;
	sampleRate = Glob->sampleRate;
	isPlaying = false;
	isGenerating = false;
	isPressed = false;
	isFadingOut = false;

	env1Value = 0.f;
	env2Value = 0.f;
	env3Value = 0.f;
	env4Value = 0.f;
	env1Playing = false;
	env2Playing = false;
	env3Playing = false;
	env4Playing = false;

	modOutPitch = 1.0f;

	keyFlwMultiplier = 1.0;

	for (int i=0;i<4;i++)
	{
		lfoValue[i] = 0.1f;
		lfo[i] = NULL;
	}

	osc1 = new cOscillator(	&(Glob->rOscLevelKnobValue[0]),
							&(Glob->rOscPanKnobValue[0]),
							&(Glob->iOscWave[0]),
							&(Glob->parameters[kOsc1Sync]->value),
							&(Glob->oscPhaseReset[0]), 1,
							&finalTune);
	osc2 = new cOscillator(	&(Glob->rOscLevelKnobValue[1]),
							&(Glob->rOscPanKnobValue[1]),
							&(Glob->iOscWave[1]),
							&(Glob->parameters[kOsc2Sync]->value),
							&(Glob->oscPhaseReset[1]), 2,
							&finalTune);
	osc3 = new cOscillator(	&(Glob->rOscLevelKnobValue[2]),
							&(Glob->rOscPanKnobValue[2]),
							&(Glob->iOscWave[2]),
							&(Glob->parameters[kOsc3Sync]->value),
							&(Glob->oscPhaseReset[2]), 3,
							&finalTune);
	osc4 = new cOscillator(	&(Glob->rOscLevelKnobValue[3]),
							&(Glob->rOscPanKnobValue[3]),
							&(Glob->iOscWave[3]),
							&(Glob->parameters[kOsc4Sync]->value),
							&(Glob->oscPhaseReset[3]), 4,
							&finalTune);

	env1 = new cEnvelope(	&(Glob->parameters[kEnv1Attack]->value),
							&(Glob->parameters[kEnv1Decay]->value),
							&(Glob->rEnvSustainKnobValue[0]),
							&(Glob->parameters[kEnv1Time]->value),
							&(Glob->parameters[kEnv1Release]->value),
							&(env1Value),
							&(env1Playing));
	env2 = new cEnvelope(	&(Glob->parameters[kEnv2Attack]->value),
							&(Glob->parameters[kEnv2Decay]->value),
							&(Glob->rEnvSustainKnobValue[1]),
							&(Glob->parameters[kEnv2Time]->value),
							&(Glob->parameters[kEnv2Release]->value),
							&(env2Value),
							&(env2Playing));
	env3 = new cEnvelope(	&(Glob->parameters[kEnv3Attack]->value),
							&(Glob->parameters[kEnv3Decay]->value),
							&(Glob->rEnvSustainKnobValue[2]),
							&(Glob->parameters[kEnv3Time]->value),
							&(Glob->parameters[kEnv3Release]->value),
							&(env3Value),
							&(env3Playing));
	env4 = new cEnvelope(	&(Glob->parameters[kEnv4Attack]->value),
							&(Glob->parameters[kEnv4Decay]->value),
							&(Glob->rEnvSustainKnobValue[3]),
							&(Glob->parameters[kEnv4Time]->value),
							&(Glob->parameters[kEnv4Release]->value),
							&(env4Value),
							&(env4Playing));

	lfo[0] = new cLFO(1,	&(Glob->zLfoRate[0]),
							&(Glob->rLfoPhaseKnobValue[0]),
							&(Glob->parameters[kLfo1Delay]->value),
							&(Glob->parameters[kLfo1Fade]->value),
							&(Glob->iLfoWave[0]),
							&(Glob->parameters[kLfo1Mono]->value),
							&(lfoValue[0]));
	lfo[1] = new cLFO(2,	&(Glob->zLfoRate[1]),
							&(Glob->rLfoPhaseKnobValue[1]),
							&(Glob->parameters[kLfo2Delay]->value),
							&(Glob->parameters[kLfo2Fade]->value),
							&(Glob->iLfoWave[1]),
							&(Glob->parameters[kLfo2Mono]->value),
							&(lfoValue[1]));
	lfo[2] = new cLFO(3,	&(Glob->zLfoRate[2]),
							&(Glob->rLfoPhaseKnobValue[2]),
							&(Glob->parameters[kLfo3Delay]->value),
							&(Glob->parameters[kLfo3Fade]->value),
							&(Glob->iLfoWave[2]),
							&(Glob->parameters[kLfo3Mono]->value),
							&(lfoValue[2]));
	lfo[3] = new cLFO(4,	&(Glob->zLfoRate[3]),
							&(Glob->rLfoPhaseKnobValue[3]),
							&(Glob->parameters[kLfo4Delay]->value),
							&(Glob->parameters[kLfo4Fade]->value),
							&(Glob->iLfoWave[3]),
							&(Glob->parameters[kLfo4Mono]->value),
							&(lfoValue[3]));

	filter[0] = new cFilter(1,	&(Glob->rFilterCutOffKnobValue[0]),
								&(Glob->rFilterQKnobValue[0]),
								&(Glob->rFilterKeyFollowKnobValue[0]),
								&(Glob->rFilterMixKnobValue[0]),
								&(Glob->iFilterType[0]),
								&note);
	filter[1] = new cFilter(2,	&(Glob->rFilterCutOffKnobValue[1]),
								&(Glob->rFilterQKnobValue[1]),
								&(Glob->rFilterKeyFollowKnobValue[1]),
								&(Glob->rFilterMixKnobValue[1]),
								&(Glob->iFilterType[1]),
								&note);



	mod = new cModulation();

	mod->source[jMS_note] = &modInNote;
	mod->source[jMS_velocity] = &modInVelocity;
	mod->source[jMS_env1] = &env1Value;
	mod->source[jMS_env2] = &env2Value;
	mod->source[jMS_env3] = &env3Value;
	mod->source[jMS_env4] = &env4Value;
	mod->source[jMS_lfo1] = &lfoValue[0];
	mod->source[jMS_lfo2] = &lfoValue[1];
	mod->source[jMS_lfo3] = &lfoValue[2];
	mod->source[jMS_lfo4] = &lfoValue[3];
	mod->source[jMS_afterTouch] = &(Glob->midiAfterTouch);
	mod->source[jMS_modWheel] = &(Glob->midiModWheel);
	mod->source[jMS_pitchBend] = &(Glob->midiPitchBend);

	mod->source[jMS_c1] = &(Glob->midiController[21]);
	mod->source[jMS_c2] = &(Glob->midiController[22]);
	mod->source[jMS_c3] = &(Glob->midiController[23]);
	mod->source[jMS_c4] = &(Glob->midiController[24]);
	mod->source[jMS_c5] = &(Glob->midiController[25]);
	mod->source[jMS_c6] = &(Glob->midiController[26]);
	mod->source[jMS_c7] = &(Glob->midiController[27]);
	mod->source[jMS_c8] = &(Glob->midiController[28]);
	mod->source[jMS_c9] = &(Glob->midiController[29]);
	mod->source[jMS_c10] = &(Glob->midiController[30]);
	mod->source[jMS_c11] = &(Glob->midiController[31]);
	mod->source[jMS_c12] = &(Glob->midiController[32]);
	mod->source[jMS_c13] = &(Glob->midiController[33]);
	mod->source[jMS_c14] = &(Glob->midiController[34]);
	mod->source[jMS_c15] = &(Glob->midiController[35]);
	mod->source[jMS_c16] = &(Glob->midiController[36]);


	mod->destination[jMD_ampVolume] = &modOutAmpVol;
	mod->destination[jMD_voicePitch] = &modOutPitch;
	mod->destination[jMD_osc1Pitch] = &(osc1->externalPitch);
	mod->destination[jMD_osc2Pitch] = &(osc2->externalPitch);
	mod->destination[jMD_osc3Pitch] = &(osc3->externalPitch);
	mod->destination[jMD_osc4Pitch] = &(osc4->externalPitch);
	mod->destination[jMD_osc1Level] = &(osc1->externalLevel);
	mod->destination[jMD_osc2Level] = &(osc2->externalLevel);
	mod->destination[jMD_osc3Level] = &(osc3->externalLevel);
	mod->destination[jMD_osc4Level] = &(osc4->externalLevel);
	mod->destination[jMD_osc1Pan] = &(osc1->externalPan);
	mod->destination[jMD_osc2Pan] = &(osc2->externalPan);
	mod->destination[jMD_osc3Pan] = &(osc3->externalPan);
	mod->destination[jMD_osc4Pan] = &(osc4->externalPan);
	mod->destination[jMD_env1Attack] = &(env1->modAttack);
	mod->destination[jMD_env1Decay] = &(env1->modDecay);
	mod->destination[jMD_env1Sustain] = &(env1->modSustain);
	mod->destination[jMD_env1Time] = &(env1->modTime);
	mod->destination[jMD_env1Release] = &(env1->modRelease);
	mod->destination[jMD_env2Attack] = &(env2->modAttack);
	mod->destination[jMD_env2Decay] = &(env2->modDecay);
	mod->destination[jMD_env2Sustain] = &(env2->modSustain);
	mod->destination[jMD_env2Time] = &(env2->modTime);
	mod->destination[jMD_env2Release] = &(env2->modRelease);
	mod->destination[jMD_env3Attack] = &(env3->modAttack);
	mod->destination[jMD_env3Decay] = &(env3->modDecay);
	mod->destination[jMD_env3Sustain] = &(env3->modSustain);
	mod->destination[jMD_env3Time] = &(env3->modTime);
	mod->destination[jMD_env3Release] = &(env3->modRelease);
	mod->destination[jMD_env4Attack] = &(env4->modAttack);
	mod->destination[jMD_env4Decay] = &(env4->modDecay);
	mod->destination[jMD_env4Sustain] = &(env4->modSustain);
	mod->destination[jMD_env4Time] = &(env4->modTime);
	mod->destination[jMD_env4Release] = &(env4->modRelease);

	mod->destination[jMD_filter1Cutoff] = &(filter[0]->modCutOff);
	mod->destination[jMD_filter1Q] = &(filter[0]->modQ);
	mod->destination[jMD_filter1KeyFlw] = &(filter[0]->modKeyFlw);
	mod->destination[jMD_filter1Wet] = &(filter[0]->modMix);
	mod->destination[jMD_filter2Cutoff] = &(filter[1]->modCutOff);
	mod->destination[jMD_filter2Q] = &(filter[1]->modQ);
	mod->destination[jMD_filter2KeyFlw] = &(filter[1]->modKeyFlw);
	mod->destination[jMD_filter2Wet] = &(filter[1]->modMix);

	mod->destination[jMD_lfo1Rate] =	&(lfo[0]->modRate);
	mod->destination[jMD_lfo2Rate] =	&(lfo[1]->modRate);
	mod->destination[jMD_lfo3Rate] =	&(lfo[2]->modRate);
	mod->destination[jMD_lfo4Rate] =	&(lfo[3]->modRate);
	mod->destination[jMD_lfo1Phase] =	&(lfo[0]->modPhaseShift);
	mod->destination[jMD_lfo2Phase] =	&(lfo[1]->modPhaseShift);
	mod->destination[jMD_lfo3Phase] =	&(lfo[2]->modPhaseShift);
	mod->destination[jMD_lfo4Phase] =	&(lfo[3]->modPhaseShift);
	mod->destination[jMD_lfo1Delay] =	&(lfo[0]->modDelay);
	mod->destination[jMD_lfo2Delay] =	&(lfo[1]->modDelay);
	mod->destination[jMD_lfo3Delay] =	&(lfo[2]->modDelay);
	mod->destination[jMD_lfo4Delay] =	&(lfo[3]->modDelay);
	mod->destination[jMD_lfo1Fade] =	&(lfo[0]->modFade);
	mod->destination[jMD_lfo2Fade] =	&(lfo[1]->modFade);
	mod->destination[jMD_lfo3Fade] =	&(lfo[2]->modFade);
	mod->destination[jMD_lfo4Fade] =	&(lfo[3]->modFade);


};
cVoice::~cVoice()
{
	if (osc1) delete osc1;
	if (osc2) delete osc2;
	if (osc3) delete osc3;
	if (osc4) delete osc4;
	if (env1) delete env1;
	if (env2) delete env2;
	if (env3) delete env3;
	if (env4) delete env4;
	for (int i=0;i<4;i++)
	{
		if (lfo[i]) delete lfo[i];
	}
	if (filter[0]) delete filter[0];
	if (filter[1]) delete filter[1];
	if (mod) delete mod;
};


void cVoice::getSample(float *out)
{
	mod->modulate();
	finalTune = noteTune + modOutPitch;

	if (isGenerating)
	{
		if ((!env1Playing)&&(!env2Playing)&&(!env3Playing)&&(!env4Playing)&&(isPlaying))
		{
			fadeOut();
		}
		if (isFadingOut)
		{
				stopGenerating();
		}
		else if (isPlaying)
		{
			(env1->*(env1->getValue))();
			(env2->*(env2->getValue))();
			(env3->*(env3->getValue))();
			(env4->*(env4->getValue))();
			
			if (Glob->parameters[kLfo1Mono]->value <0.5f)(lfo[0]->*(lfo[0]->getValue))();
			else lfoValue[0] = Glob->lfoValue[0];
			if (Glob->parameters[kLfo2Mono]->value <0.5f)(lfo[1]->*(lfo[1]->getValue))();
			else lfoValue[1] = Glob->lfoValue[1];
			if (Glob->parameters[kLfo3Mono]->value <0.5f)(lfo[2]->*(lfo[2]->getValue))();
			else lfoValue[2] = Glob->lfoValue[2];
			if (Glob->parameters[kLfo4Mono]->value <0.5f)(lfo[3]->*(lfo[3]->getValue))();
			else lfoValue[3] = Glob->lfoValue[3];

			osc1->shiftPhase();
			osc2->shiftPhase();
			osc3->shiftPhase();
			osc4->shiftPhase();

			osc1->getSample(out);
			float osc1L = out[0];
			float osc1R = out[1];
			osc2->getSample(out);
			float osc2L = out[0];
			float osc2R = out[1];
			osc3->getSample(out);
			float osc3L = out[0];
			float osc3R = out[1];
			osc4->getSample(out);
			float osc4L = out[0];
			float osc4R = out[1];
			float tmpF = 0.2f;
			out[0] = tmpF*((osc1L + osc2L) + (osc3L + osc4L));
			out[1] = tmpF*((osc1R + osc2R) + (osc3R + osc4R));
		}
		else
		{
			out[0] = 0.0f;
			out[1] = 0.0f;
		}
	}
	else
	{
		out[0] = 0.0f;
		out[1] = 0.0f;
		if (filter[1]->getBuffSum() <= 0.0001f)
			stopAll();
	}

	if (Glob->iFilterRouting == 0)
	{
		filter[0]->process(out);
		filter[1]->process(out);
	}
	else
	{
		float o1[2],o2[2];
		o1[0] = out[0];
		o1[1] = out[1];
		o2[0] = out[0];
		o2[1] = out[1];

		filter[0]->process((float *)&o1);
		filter[1]->process((float *)&o2);

		out[0] = (o1[0] + o2[0]) * 0.5f;
		out[1] = (o1[1] + o2[1]) * 0.5f;

	}
	out[0] *= (modOutAmpVol);
	out[1] *= (modOutAmpVol);
};

void cVoice::playNote(VstInt32 pNote,VstInt32 pVelocity, VstInt32 pDelta, VstInt64 birth)
{
	note = pNote;
	noteTune = note / 12.f;
	noteBirth = birth;
	velocity = pVelocity;
	delta = pDelta;
	phase = 0;

	modInVelocity = velocity / 127.f;
	modInNote = note / 127.f;

	osc1->play();
	osc2->play();
	osc3->play();
	osc4->play();

	env1->play();
	env2->play();
	env3->play();
	env4->play();

	filter[0]->reset();
	filter[1]->reset();
	
	for (int i=0;i<4;i++)
	{
		if (lfo[i]) lfo[i]->reset();
	}

	isPlaying = true;
	isGenerating = true;
	isPressed = true;
};
void cVoice::changeNote(VstInt32 pNote,VstInt32 pVelocity, VstInt32 pDelta, VstInt64 birth)
{
	note = pNote;
	noteTune = note / 12.f;
	noteBirth = birth;
	velocity = pVelocity;
	delta = pDelta;
	phase = 0;

	modInVelocity = velocity / 127.f;
	modInNote = note / 127.f;

	osc1->play();
	osc2->play();
	osc3->play();
	osc4->play();

	env1->play();
	env2->play();
	env3->play();
	env4->play();

	for (int i=0;i<4;i++)
	{
		if (lfo[i]) lfo[i]->reset();
	}

	isPlaying = true;
	isGenerating = true;
	isPressed = true;
};
 
void cVoice::stopNote()
{
	isPressed = false;
	env1->releaseNote();
	env2->releaseNote();
	env3->releaseNote();
	env4->releaseNote();
}

void cVoice::stopGenerating()
{
	isGenerating = false;	
	isFadingOut = false;
	fader = 1.0f;
}
void cVoice::fadeOut()
{
	isFadingOut = true;	
}

void cVoice::stopAll()
{
	isPressed = false;
	isPlaying = false;
}


VstInt32 cVoice::getNote()
{
	return note;
}
