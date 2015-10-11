// Trieda cVoice
#ifndef __cmireditor_h__
#define __cmireditor_h__
#include "cGlobals.h"
#include "cMultiStateButton.h"
#include "cSyncButton.h"
#include "cTriggerButton.h"
#include "cEnvDisplay.h"
#include "cModAmtKnob.h"
#include "cModselect.h"
#include "functions.h"
#include "modulationConstants.h"

#ifndef __vstgui__
#include "../vstgui/vstgui.h"
#endif

//-----------------------------------------------------------------------------
class cMirEditor : public AEffGUIEditor, public CControlListener
{
public:
	cMirEditor(AudioEffect *effect);
	virtual ~cMirEditor();

public:
	virtual bool open (void* ptr);
	virtual void close ();
	virtual void setParameter (VstInt32 index, float value);
	virtual void valueChanged (CDrawContext* context, CControl* control);
	
	void createKnob(CAnimKnob* &knob, VstInt32 posX,VstInt32 posY, VstInt32 parameter);
	void createDisplay(CParamDisplay* &display, VstInt32 posX,VstInt32 posY, VstInt32 parameter, void (*convert)(float,char*) );
	void createWavButton(cMultiStateButton* button,  VstInt32 posX,VstInt32 posY, VstInt32 parameter);
	void createSyncButton(cSyncButton* button,  VstInt32 posX,VstInt32 posY, VstInt32 parameter, VstInt32 oscId);
	void createLfoWavButton(cMultiStateButton* button,  VstInt32 posX,VstInt32 posY, VstInt32 parameter);
	void createFilterTypeButton(cMultiStateButton* button,  VstInt32 posX,VstInt32 posY, VstInt32 parameter);
	void createLfoMonoButton(cMultiStateButton* button,  VstInt32 posX,VstInt32 posY, VstInt32 parameter);
	void createLfoBlock(CPoint pPos, CAnimKnob* knobs[], CParamDisplay* display[],
			cMultiStateButton* &btnWaveform, cMultiStateButton* &btnMono,
			VstInt32 pRange,VstInt32 pRate,	VstInt32 pPhase,
			VstInt32 pDelay,VstInt32 pWaveform,VstInt32 pMono,VstInt32 pFade);
	void createFilterBlock(CPoint pPos, CAnimKnob* knobs[],	CParamDisplay* display[],
			VstInt32 pCutOff,VstInt32 pQ,VstInt32 pKeyFollow,
			VstInt32 pMix,VstInt32 pType);

	void createModKnob(cModAmtKnob* knob, VstInt32 posX,VstInt32 posY, VstInt32 parameter);
	void createModSlot(CPoint pPos, cModAmtKnob* knobs[], long index);

private:
	CBitmap *bBackground;
	CBitmap *bKnob01;
	CBitmap *bWavBtn01;
	CBitmap *bWavBtn02;
	CBitmap *bSyncBtn01;
	CBitmap *bLfoMonoBtn01;
	CBitmap *bFilterBtn01;
	CBitmap *bFilterBtn02;
	CBitmap *bModAmtKnob;
	CBitmap *bModDestinations;
	CBitmap *bModSources;
	CBitmap *bDump;

	CFrame  *mainFrame;

	CControl* controllers[kNumParams];
	CParamDisplay* displays[kNumParams];

	AudioEffect *synth;
	// Oscilatory --------------------------------------------------------
		// Oscilator 1 -----------------
			CAnimKnob *knobOsc1Octave;
			CParamDisplay *dispOsc1Octave;
			CAnimKnob *knobOsc1Coarse;
			CParamDisplay *dispOsc1Coarse;
			CAnimKnob *knobOsc1Fine;
			CParamDisplay *dispOsc1Fine;
			CAnimKnob *knobOsc1Level;
			CParamDisplay *dispOsc1Level;
			CAnimKnob *knobOsc1Pan;
			CParamDisplay *dispOsc1Pan;

			cMultiStateButton *btnOsc1Waveform;
			cSyncButton *btnOsc1Sync;
		// Oscilator 2 -----------------
			CAnimKnob *knobOsc2Octave;
			CParamDisplay *dispOsc2Octave;
			CAnimKnob *knobOsc2Coarse;
			CParamDisplay *dispOsc2Coarse;
			CAnimKnob *knobOsc2Fine;
			CParamDisplay *dispOsc2Fine;
			CAnimKnob *knobOsc2Level;
			CParamDisplay *dispOsc2Level;
			CAnimKnob *knobOsc2Pan;
			CParamDisplay *dispOsc2Pan;

			cMultiStateButton *btnOsc2Waveform;
			cSyncButton *btnOsc2Sync;
		// Oscilator 3 -----------------
			CAnimKnob *knobOsc3Octave;
			CParamDisplay *dispOsc3Octave;
			CAnimKnob *knobOsc3Coarse;
			CParamDisplay *dispOsc3Coarse;
			CAnimKnob *knobOsc3Fine;
			CParamDisplay *dispOsc3Fine;
			CAnimKnob *knobOsc3Level;
			CParamDisplay *dispOsc3Level;
			CAnimKnob *knobOsc3Pan;
			CParamDisplay *dispOsc3Pan;

			cMultiStateButton *btnOsc3Waveform;
			cSyncButton *btnOsc3Sync;
		// Oscilator 4 -----------------
			CAnimKnob *knobOsc4Octave;
			CParamDisplay *dispOsc4Octave;
			CAnimKnob *knobOsc4Coarse;
			CParamDisplay *dispOsc4Coarse;
			CAnimKnob *knobOsc4Fine;
			CParamDisplay *dispOsc4Fine;
			CAnimKnob *knobOsc4Level;
			CParamDisplay *dispOsc4Level;
			CAnimKnob *knobOsc4Pan;
			CParamDisplay *dispOsc4Pan;

			cMultiStateButton *btnOsc4Waveform;
			cSyncButton *btnOsc4Sync;
	// Obalky --------------------------------------------------------
		// Obalka 1 -----------------
			CAnimKnob *knobEnv1Attack;
			CParamDisplay *dispEnv1Attack;
			CAnimKnob *knobEnv1Decay;
			CParamDisplay *dispEnv1Decay;
			CAnimKnob *knobEnv1Sustain;
			CParamDisplay *dispEnv1Sustain;
			CAnimKnob *knobEnv1Time;
			CParamDisplay *dispEnv1Time;
			CAnimKnob *knobEnv1Release;
			CParamDisplay *dispEnv1Release;

			cEnvDisplay *env1Monitor;
		// Obalka 2 -----------------
			CAnimKnob *knobEnv2Attack;
			CParamDisplay *dispEnv2Attack;
			CAnimKnob *knobEnv2Decay;
			CParamDisplay *dispEnv2Decay;
			CAnimKnob *knobEnv2Sustain;
			CParamDisplay *dispEnv2Sustain;
			CAnimKnob *knobEnv2Time;
			CParamDisplay *dispEnv2Time;
			CAnimKnob *knobEnv2Release;
			CParamDisplay *dispEnv2Release;

			cEnvDisplay *env2Monitor;
		// Obalka 3 -----------------
			CAnimKnob *knobEnv3Attack;
			CParamDisplay *dispEnv3Attack;
			CAnimKnob *knobEnv3Decay;
			CParamDisplay *dispEnv3Decay;
			CAnimKnob *knobEnv3Sustain;
			CParamDisplay *dispEnv3Sustain;
			CAnimKnob *knobEnv3Time;
			CParamDisplay *dispEnv3Time;
			CAnimKnob *knobEnv3Release;
			CParamDisplay *dispEnv3Release;

			cEnvDisplay *env3Monitor;
		// Obalka 4 -----------------
			CAnimKnob *knobEnv4Attack;
			CParamDisplay *dispEnv4Attack;
			CAnimKnob *knobEnv4Decay;
			CParamDisplay *dispEnv4Decay;
			CAnimKnob *knobEnv4Sustain;
			CParamDisplay *dispEnv4Sustain;
			CAnimKnob *knobEnv4Time;
			CParamDisplay *dispEnv4Time;
			CAnimKnob *knobEnv4Release;
			CParamDisplay *dispEnv4Release;

			cEnvDisplay *env4Monitor;
	// LFO --------------------------------------
			CAnimKnob *knobs1Lfo[5];
			CParamDisplay *disps1Lfo[5];
			cMultiStateButton *btnLfo1Waveform;
			cMultiStateButton *btnLfo1Mono;
			CAnimKnob *knobs2Lfo[5];
			CParamDisplay *disps2Lfo[5];
			cMultiStateButton *btnLfo2Waveform;
			cMultiStateButton *btnLfo2Mono;
			CAnimKnob *knobs3Lfo[5];
			CParamDisplay *disps3Lfo[5];
			cMultiStateButton *btnLfo3Waveform;
			cMultiStateButton *btnLfo3Mono;
			CAnimKnob *knobs4Lfo[5];
			CParamDisplay *disps4Lfo[5];
			cMultiStateButton *btnLfo4Waveform;
			cMultiStateButton *btnLfo4Mono;

	// Filtre --------------------------------------
			CAnimKnob *knobs1Filter[4];
			CParamDisplay *disps1Filter[4];
			CAnimKnob *knobs2Filter[4];
			CParamDisplay *disps2Filter[4];
			
			cMultiStateButton *btnFilter1Type;
			cMultiStateButton *btnFilter2Type;

			cMultiStateButton *btnFilterRouting;
	// Modulacie --------------------------------------
			cModAmtKnob *knobModAmt[32];
			cModSelect *optionModSource[32];
			cModSelect *optionModDestination[32];

			CKickButton *dump;
			
			 
};

#endif