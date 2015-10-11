#ifndef __cmireditor_h__
#include "cMirEditor.h"
#endif

#ifndef __mirsynth__
#include "mirsynth.h"
#endif

#include <stdio.h>

enum
{
	kBackground = 128,
	kKnob01,
	kOscSync,
	kOscWave,
	kLfoWave,
	kLfoMono,
	kFType,
	kFRouting,
	kModAmtBtn,
	kModDestinations,
	kModSources,
	kDump
};

cMirEditor::cMirEditor (AudioEffect *effect)
 : AEffGUIEditor (effect) 
{
	bBackground = new CBitmap(kBackground);
	rect.left   = 0;
	rect.top    = 0;
	rect.right  = (short)bBackground->getWidth ();
	rect.bottom = (short)bBackground->getHeight ();
	synth = effect;

	for (int i=0;i<kNumParams;i++)
	{
		controllers[i] = 0;
		displays[i] = 0;
	}
	bKnob01 = new CBitmap(kKnob01);
	bWavBtn01 = new CBitmap(kOscWave);
	bWavBtn02 = new CBitmap(kLfoWave);
	bSyncBtn01 = new CBitmap(kOscSync);
	bLfoMonoBtn01 = new CBitmap(kLfoMono);
	bFilterBtn01 = new CBitmap(kFType);
	bFilterBtn02 = new CBitmap(kFRouting);
	bModAmtKnob = new CBitmap(kModAmtBtn);
	bModDestinations = new CBitmap(kModDestinations);
	bModSources = new CBitmap(kModSources);
	bDump = new CBitmap(kDump);

}
cMirEditor::~cMirEditor()
{
	if (bBackground) bBackground->forget();
	bBackground = 0;
	if (bKnob01) bKnob01->forget();
	if (bWavBtn01) bWavBtn01->forget();
	if (bWavBtn02) bWavBtn02->forget();
	if (bSyncBtn01) bSyncBtn01->forget();
	if (bLfoMonoBtn01) bLfoMonoBtn01->forget();
	if (bFilterBtn01) bFilterBtn01->forget();
	if (bFilterBtn02) bFilterBtn02->forget();
	if (bModAmtKnob) bModAmtKnob->forget();
	if (bModDestinations) bModDestinations->forget();
	if (bModSources) bModSources->forget();

}

bool cMirEditor::open(void *ptr)
{
	AEffGUIEditor::open(ptr);
	CRect size (0, 0, bBackground->getWidth (), bBackground->getHeight ());
	mainFrame = new CFrame (size, ptr, this);
	mainFrame->setBackground (bBackground);




	CPoint point(0,0);
	
	// Oscilatory ---------------------------------------------------------------
	    // Oscilator 1 -------------------------------
			createKnob(knobOsc1Octave,82,29,kOsc1Octave);
			createDisplay(dispOsc1Octave,78,57,kOsc1Octave,floatToOctave);
			createKnob(knobOsc1Coarse,122,29,kOsc1Coarse);
			createDisplay(dispOsc1Coarse,118,57,kOsc1Coarse,floatToCoarse);
			createKnob(knobOsc1Fine,162,29,kOsc1Fine);
			createDisplay(dispOsc1Fine,158,57,kOsc1Fine,floatToFine);
			createKnob(knobOsc1Pan,202,29,kOsc1Pan);
			createDisplay(dispOsc1Pan,198,57,kOsc1Pan,floatToPan);
			createKnob(knobOsc1Level,242,29,kOsc1Level);
			createDisplay(dispOsc1Level,238,57,kOsc1Level,floatToLevel);
			createWavButton(btnOsc1Waveform,14,20,kOsc1Waveform);
			createSyncButton(btnOsc1Sync,42,54,kOsc1Sync,1);
	    // Oscilator 2 -------------------------------
			createKnob(knobOsc2Octave,82,94,kOsc2Octave);
			createDisplay(dispOsc2Octave,78,122,kOsc2Octave,floatToOctave);
			createKnob(knobOsc2Coarse,122,94,kOsc2Coarse);
			createDisplay(dispOsc2Coarse,118,122,kOsc2Coarse,floatToCoarse);
			createKnob(knobOsc2Fine,162,94,kOsc2Fine);
			createDisplay(dispOsc2Fine,158,122,kOsc2Fine,floatToFine);
			createKnob(knobOsc2Pan,202,94,kOsc2Pan);
			createDisplay(dispOsc2Pan,198,122,kOsc2Pan,floatToPan);
			createKnob(knobOsc2Level,242,94,kOsc2Level);
			createDisplay(dispOsc2Level,238,122,kOsc2Level,floatToLevel);
			createWavButton(btnOsc2Waveform,14,85,kOsc2Waveform);
			createSyncButton(btnOsc2Sync,42,119,kOsc2Sync,2);
	    // Oscilator 3 -------------------------------
			createKnob(knobOsc3Octave,82,159,kOsc3Octave);
			createDisplay(dispOsc3Octave,78,187,kOsc3Octave,floatToOctave);
			createKnob(knobOsc3Coarse,122,159,kOsc3Coarse);
			createDisplay(dispOsc3Coarse,118,187,kOsc3Coarse,floatToCoarse);
			createKnob(knobOsc3Fine,162,159,kOsc3Fine);
			createDisplay(dispOsc3Fine,158,187,kOsc3Fine,floatToFine);
			createKnob(knobOsc3Pan,202,159,kOsc3Pan);
			createDisplay(dispOsc3Pan,198,187,kOsc3Pan,floatToPan);
			createKnob(knobOsc3Level,242,159,kOsc3Level);
			createDisplay(dispOsc3Level,238,187,kOsc3Level,floatToLevel);
			createWavButton(btnOsc3Waveform,14,150,kOsc3Waveform);
			createSyncButton(btnOsc3Sync,42,184,kOsc3Sync,3);
	    // Oscilator 4 -------------------------------
			createKnob(knobOsc4Octave,82,224,kOsc4Octave);
			createDisplay(dispOsc4Octave,78,252,kOsc4Octave,floatToOctave);
			createKnob(knobOsc4Coarse,122,224,kOsc4Coarse);
			createDisplay(dispOsc4Coarse,118,252,kOsc4Coarse,floatToCoarse);
			createKnob(knobOsc4Fine,162,224,kOsc4Fine);
			createDisplay(dispOsc4Fine,158,252,kOsc4Fine,floatToFine);
			createKnob(knobOsc4Pan,202,224,kOsc4Pan);
			createDisplay(dispOsc4Pan,198,252,kOsc4Pan,floatToPan);
			createKnob(knobOsc4Level,242,224,kOsc4Level);
			createDisplay(dispOsc4Level,238,252,kOsc4Level,floatToLevel);
			createWavButton(btnOsc4Waveform,14,215,kOsc4Waveform);
			createSyncButton(btnOsc4Sync,42,249,kOsc4Sync,4);
	// Obalky --------------------------------------------------------
		// Obalka 1 -----------------
			createKnob(knobEnv1Attack,365,29,kEnv1Attack);
			createDisplay(dispEnv1Attack,361,57,kEnv1Attack,floatToEnvTime);
			createKnob(knobEnv1Decay,405,29,kEnv1Decay);
			createDisplay(dispEnv1Decay,401,57,kEnv1Decay,floatToEnvTime);
			createKnob(knobEnv1Sustain,445,29,kEnv1Sustain);
			createDisplay(dispEnv1Sustain,441,57,kEnv1Sustain,floatToLevel);
			createKnob(knobEnv1Time,485,29,kEnv1Time);
			createDisplay(dispEnv1Time,481,57,kEnv1Time,floatToFine);
			createKnob(knobEnv1Release,525,29,kEnv1Release);
			createDisplay(dispEnv1Release,521,57,kEnv1Release,floatToEnvTime);

			env1Monitor = new cEnvDisplay(CRect(293,18,357,52),NULL,
				&(Glob->parameters[kEnv1Attack]->value),
				&(Glob->parameters[kEnv1Decay]->value),
				&(Glob->parameters[kEnv1Sustain]->value),
				&(Glob->parameters[kEnv1Time]->value),
				&(Glob->parameters[kEnv1Release]->value));
			mainFrame->addView (env1Monitor);

		// Obalka 2 -----------------
			createKnob(knobEnv2Attack,365,94,kEnv2Attack);
			createDisplay(dispEnv2Attack,361,122,kEnv2Attack,floatToEnvTime);
			createKnob(knobEnv2Decay,405,94,kEnv2Decay);
			createDisplay(dispEnv2Decay,401,122,kEnv2Decay,floatToEnvTime);
			createKnob(knobEnv2Sustain,445,94,kEnv2Sustain);
			createDisplay(dispEnv2Sustain,441,122,kEnv2Sustain,floatToLevel);
			createKnob(knobEnv2Time,485,94,kEnv2Time);
			createDisplay(dispEnv2Time,481,122,kEnv2Time,floatToFine);
			createKnob(knobEnv2Release,525,94,kEnv2Release);
			createDisplay(dispEnv2Release,521,122,kEnv2Release,floatToEnvTime);

			env2Monitor = new cEnvDisplay(CRect(293,83,357,117),NULL,
				&(Glob->parameters[kEnv2Attack]->value),
				&(Glob->parameters[kEnv2Decay]->value),
				&(Glob->parameters[kEnv2Sustain]->value),
				&(Glob->parameters[kEnv2Time]->value),
				&(Glob->parameters[kEnv2Release]->value));
			mainFrame->addView (env2Monitor);			

		// Obalka 3 -----------------
			createKnob(knobEnv3Attack,365,159,kEnv3Attack);
			createDisplay(dispEnv3Attack,361,187,kEnv3Attack,floatToEnvTime);
			createKnob(knobEnv3Decay,405,159,kEnv3Decay);
			createDisplay(dispEnv3Decay,401,187,kEnv3Decay,floatToEnvTime);
			createKnob(knobEnv3Sustain,445,159,kEnv3Sustain);
			createDisplay(dispEnv3Sustain,441,187,kEnv3Sustain,floatToLevel);
			createKnob(knobEnv3Time,485,159,kEnv3Time);
			createDisplay(dispEnv3Time,481,187,kEnv3Time,floatToFine);
			createKnob(knobEnv3Release,525,159,kEnv3Release);
			createDisplay(dispEnv3Release,521,187,kEnv3Release,floatToEnvTime);

			env3Monitor = new cEnvDisplay(CRect(293,148,357,182),NULL,
				&(Glob->parameters[kEnv3Attack]->value),
				&(Glob->parameters[kEnv3Decay]->value),
				&(Glob->parameters[kEnv3Sustain]->value),
				&(Glob->parameters[kEnv3Time]->value),
				&(Glob->parameters[kEnv3Release]->value));
			mainFrame->addView (env3Monitor);		
			
		// Obalka 4 -----------------
			createKnob(knobEnv4Attack,365,224,kEnv4Attack);
			createDisplay(dispEnv4Attack,361,252,kEnv4Attack,floatToEnvTime);
			createKnob(knobEnv4Decay,405,224,kEnv4Decay);
			createDisplay(dispEnv4Decay,401,252,kEnv4Decay,floatToEnvTime);
			createKnob(knobEnv4Sustain,445,224,kEnv4Sustain);
			createDisplay(dispEnv4Sustain,441,252,kEnv4Sustain,floatToLevel);
			createKnob(knobEnv4Time,485,224,kEnv4Time);
			createDisplay(dispEnv4Time,481,252,kEnv4Time,floatToFine);
			createKnob(knobEnv4Release,525,224,kEnv4Release);
			createDisplay(dispEnv4Release,521,252,kEnv4Release,floatToEnvTime);

			env4Monitor = new cEnvDisplay(CRect(293,213,357,247),NULL,
				&(Glob->parameters[kEnv4Attack]->value),
				&(Glob->parameters[kEnv4Decay]->value),
				&(Glob->parameters[kEnv4Sustain]->value),
				&(Glob->parameters[kEnv4Time]->value),
				&(Glob->parameters[kEnv4Release]->value));
			mainFrame->addView (env4Monitor);		

		// LFO ---------------------------
			createLfoBlock(CPoint(290,283), knobs1Lfo, disps1Lfo, btnLfo1Waveform, btnLfo1Mono, kLfo1Range,kLfo1Rate,kLfo1PhaseShift,
				kLfo1Delay,kLfo1Waveform,kLfo1Mono,kLfo1Fade);
			createLfoBlock(CPoint(290,348), knobs2Lfo, disps2Lfo, btnLfo2Waveform, btnLfo2Mono, kLfo2Range,kLfo2Rate,kLfo2PhaseShift,
				kLfo2Delay,kLfo2Waveform,kLfo2Mono,kLfo2Fade);
			createLfoBlock(CPoint(290,413), knobs3Lfo, disps3Lfo, btnLfo3Waveform, btnLfo3Mono, kLfo3Range,kLfo3Rate,kLfo3PhaseShift,
				kLfo3Delay,kLfo3Waveform,kLfo3Mono,kLfo3Fade);
			createLfoBlock(CPoint(290,478), knobs4Lfo, disps4Lfo, btnLfo4Waveform, btnLfo4Mono, kLfo4Range,kLfo4Rate,kLfo4PhaseShift,
				kLfo4Delay,kLfo4Waveform,kLfo4Mono,kLfo4Fade);
		// Filtre ---------------------------
			createFilterBlock(CPoint(7,283), knobs1Filter, disps1Filter, kFilter1CutOff,kFilter1Q,kFilter1KeyFollow,
				kFilter1Mix,kFilter1Type);
			createFilterBlock(CPoint(7,348), knobs2Filter, disps2Filter,kFilter2CutOff,kFilter2Q,kFilter2KeyFollow,
				kFilter2Mix,kFilter2Type);

			size (248,323,248+37,323+44);
			btnFilterRouting = new cMultiStateButton(size,this,kFilterRouting,bFilterBtn02,2);
			btnFilterRouting->setValue(effect->getParameter(kFilterRouting));
			mainFrame->addView (btnFilterRouting);
			controllers[kFilterRouting] = btnFilterRouting;

	//-------------------------------------------------------------------

			for (VstInt32 i=0;i<32;i++)
			{
				createModSlot(CPoint(575,19+16*i), knobModAmt, i);
			}

			size (231,515,231+50,515+22);
			dump = new CKickButton(size, this, 10000, bDump, CPoint(0,0));
			//dump->setValue(0.f);
			//mainFrame->addView (dump);
			
	frame = mainFrame;
	return true;
}
void cMirEditor::close()
{
	for (int i=0;i<kNumParams;i++)
	{
		if (controllers[i] != NULL)
			controllers[i] = NULL;
		if (displays[i] != NULL) 
			displays[i] = NULL;
	}
	if (frame) delete frame;
	frame = 0;
}

void cMirEditor::setParameter (VstInt32 index, float value)
{
	if (controllers[index]) controllers[index]->setValue(effect->getParameter(index));
	if (displays[index]) displays[index]->setValue(effect->getParameter(index));
	
	switch (index)
	{
		case kEnv1Attack: case kEnv1Decay: case kEnv1Sustain: case kEnv1Time: case kEnv1Release:
			if (env1Monitor) env1Monitor->setDirty();break;
		case kEnv2Attack: case kEnv2Decay: case kEnv2Sustain: case kEnv2Time: case kEnv2Release:
			if (env2Monitor) env2Monitor->setDirty();break;
		case kEnv3Attack: case kEnv3Decay: case kEnv3Sustain: case kEnv3Time: case kEnv3Release:
			if (env3Monitor) env3Monitor->setDirty();break;
		case kEnv4Attack: case kEnv4Decay: case kEnv4Sustain: case kEnv4Time: case kEnv4Release:
			if (env4Monitor) env4Monitor->setDirty();break;
	}
}
void cMirEditor::valueChanged (CDrawContext* context, CControl* control)
{
	long tag = control->getTag ();
	if (tag < 8000)
	{
		effect->setParameterAutomated (tag, control->getValue ());
		if (displays[tag]) displays[tag]->setValue(effect->getParameter(tag));
			control->setDirty(true);
		if (displays[tag]) displays[tag]->setDirty(true);
	}
	else
		if (control->getValue () > 0.f)
			Glob->dumpPreset();
}

void cMirEditor::createKnob(CAnimKnob* &knob, VstInt32 posX,VstInt32 posY, VstInt32 parameter)
{
	CRect size(posX,posY,posX+29,posY+29);
	CPoint point(0,0);
	knob = new CAnimKnob(size,this,parameter,128,29,bKnob01,point);
	knob->setValue(effect->getParameter(parameter));
	mainFrame->addView(knob);
	controllers[parameter] = knob;
}

void cMirEditor::createDisplay(CParamDisplay* &display, VstInt32 posX,VstInt32 posY, VstInt32 parameter, void (*convert)(float,char*) )
																								
{
	CRect size (posX,posY,posX+38,posY+11);
	display = new CParamDisplay (size,0,kCenterText);
	display->setFont(kNormalFontSmaller);
	display->setFontColor (kBlackCColor);
	display->setTransparency(true);
	display->setBackColor (kTransparentCColor);
	display->setFrameColor (kTransparentCColor);
	display->setStringConvert(convert);
	display->setValue(effect->getParameter(parameter));
	mainFrame->addView (display);
	displays[parameter] = display;

}
void cMirEditor::createWavButton(cMultiStateButton* button,  VstInt32 posX,VstInt32 posY, VstInt32 parameter)
{
	CRect size (posX,posY,posX+57,posY+30);
	button = new cMultiStateButton(size,this,parameter,bWavBtn01,5);
	button->setValue(effect->getParameter(parameter));
	mainFrame->addView (button);
	controllers[parameter] = button;
}
void cMirEditor::createLfoWavButton(cMultiStateButton* button,  VstInt32 posX,VstInt32 posY, VstInt32 parameter)
{
	CRect size (posX,posY,posX+57,posY+30);
	button = new cMultiStateButton(size,this,parameter,bWavBtn02,6);
	button->setValue(effect->getParameter(parameter));
	mainFrame->addView (button);
	controllers[parameter] = button;
}
void cMirEditor::createFilterTypeButton(cMultiStateButton* button,  VstInt32 posX,VstInt32 posY, VstInt32 parameter)
{
	CRect size (posX,posY,posX+57,posY+30);
	button = new cMultiStateButton(size,this,parameter,bFilterBtn01,4);
	button->setValue(effect->getParameter(parameter));
	mainFrame->addView (button);
	controllers[parameter] = button;
}
void cMirEditor::createLfoMonoButton(cMultiStateButton* button,  VstInt32 posX,VstInt32 posY, VstInt32 parameter)
{
	CRect size (posX,posY,posX+31,posY+14);
	button = new cMultiStateButton(size,this,parameter,bLfoMonoBtn01,2);
	button->setValue(effect->getParameter(parameter));
	mainFrame->addView (button);
	controllers[parameter] = button;
}


void cMirEditor::createSyncButton(cSyncButton* button, VstInt32 posX,VstInt32 posY, VstInt32 parameter, VstInt32 oscId)
{
	CRect size (posX,posY,posX+31,posY+14);
	button = new cSyncButton(size,this,parameter,bSyncBtn01,4,oscId);
	button->setValue(effect->getParameter(parameter));
	mainFrame->addView (button);
	controllers[parameter] = button;
}

void cMirEditor::createLfoBlock(CPoint pPos, CAnimKnob* knobs[], CParamDisplay* display[],
			cMultiStateButton* &btnWaveform, cMultiStateButton* &btnMono,
			VstInt32 pRange,VstInt32 pRate,	VstInt32 pPhase,
			VstInt32 pDelay,VstInt32 pWaveform,VstInt32 pMono,VstInt32 pFade)
{
			int X = pPos.x;
			int Y = pPos.y;

			createKnob(knobs[0],	X+75,		Y+14,pRange);
			createDisplay(display[0],	X+71,		Y+42,pRange,floatToRange);
			createKnob(knobs[1],	X+75+40*1,	Y+14,pRate);
			createDisplay(display[1],	X+71+40*1,	Y+42,pRate,floatToRate);
			createKnob(knobs[2],	X+75+40*2,	Y+14,pPhase);
			createDisplay(display[2],	X+71+40*2,	Y+42,pPhase,floatToPhase);
			createKnob(knobs[3],	X+75+40*3,	Y+14,pDelay);
			createDisplay(display[3],	X+71+40*3,	Y+42,pDelay,floatToEnvTime);
			createKnob(knobs[4],	X+75+40*4,	Y+14,pFade);
			createDisplay(display[4],	X+71+40*4,	Y+42,pFade,floatToEnvTime);
			createLfoWavButton(btnWaveform,X+7,Y+5,pWaveform);
			createLfoMonoButton(btnMono,X+35,Y+39,pMono);
}
void cMirEditor::createFilterBlock(CPoint pPos, CAnimKnob* knobs[],	CParamDisplay* display[],
			VstInt32 pCutOff,VstInt32 pQ,VstInt32 pKeyFollow,
			VstInt32 pMix,VstInt32 pType)
{
			int X = pPos.x;
			int Y = pPos.y;

			createKnob(knobs[0],	X+75,		Y+14,pCutOff);
			createDisplay(display[0],	X+71,		Y+42,pCutOff,floatToCutoffFreq);
			createKnob(knobs[1],	X+75+40*1,	Y+14,pQ);
			createDisplay(display[1],	X+71+40*1,	Y+42,pQ,floatToQ);
			createKnob(knobs[2],	X+75+40*2,	Y+14,pKeyFollow);
			createDisplay(display[2],	X+71+40*2,	Y+42,pKeyFollow,floatToFine);
			createKnob(knobs[3],	X+75+40*3,	Y+14,pMix);
			createDisplay(display[3],	X+71+40*3,	Y+42,pMix,floatToLevel);

			createFilterTypeButton(btnFilter1Type,X+7,Y+5,pType);

}

void cMirEditor::createModKnob(cModAmtKnob* knob, VstInt32 posX,VstInt32 posY, VstInt32 parameter)
{
	CRect size(posX,posY,posX+35,posY+15);
	CPoint point(0,0);
	knob = new cModAmtKnob(size,this,parameter,201,15,bModAmtKnob,point);
	knob->setValue(effect->getParameter(parameter));
	mainFrame->addView(knob);
	controllers[parameter] = knob;
}


void cMirEditor::createModSlot(CPoint pPos, cModAmtKnob* knobs[], long index)
{
			VstInt32 X = pPos.x;
			VstInt32 Y = pPos.y;
			VstInt32 kDest = kModDestination01 + index;
			VstInt32 kSource = kModSource01 + index;
			VstInt32 kAmt = kModAmt01 + index;

			createModKnob(knobs[index],	X+105, Y, kAmt);

			CRect size(X+20, Y+1, X+105, Y+14);
			optionModSource[index] = new cModSelect(size, this, kSource, bModSources, 30, true);
			optionModSource[index]->setValue(Glob->parameters[kSource]->value);
			mainFrame->addView(optionModSource[index]);
			controllers[kSource] = optionModSource[index];

			size(X+140, Y+1, X+225, Y+14);
			optionModDestination[index] = new cModSelect(size, this, kDest, bModDestinations, 59, false);
			optionModDestination[index]->setValue(Glob->parameters[kDest]->value);
			mainFrame->addView(optionModDestination[index]);
			controllers[kDest] = optionModDestination[index];

}