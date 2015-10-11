#ifndef __modulationconstants_h__

#define __modulationconstants_h__

#include "../vst2.x/audioeffectx.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>
#ifndef __vstgui__
#include "../vstgui/vstgui.h"
#endif

enum
{
	jMD_none = 0,
	jMD_osc1Pitch,
	jMD_osc1Pan,
	jMD_osc1Level,
	jMD_osc2Pitch,
	jMD_osc2Pan,
	jMD_osc2Level,
	jMD_osc3Pitch,
	jMD_osc3Pan,
	jMD_osc3Level,
	jMD_osc4Pitch,
	jMD_osc4Pan,
	jMD_osc4Level,
	jMD_voicePitch,
	jMD_ampVolume,
	jMD_env1Attack,
	jMD_env1Decay,
	jMD_env1Sustain,
	jMD_env1Time,
	jMD_env1Release,
	jMD_env2Attack,
	jMD_env2Decay,
	jMD_env2Sustain,
	jMD_env2Time,
	jMD_env2Release,
	jMD_env3Attack,
	jMD_env3Decay,
	jMD_env3Sustain,
	jMD_env3Time,
	jMD_env3Release,
	jMD_env4Attack,
	jMD_env4Decay,
	jMD_env4Sustain,
	jMD_env4Time,
	jMD_env4Release,
	jMD_lfo1Rate,
	jMD_lfo1Phase,
	jMD_lfo1Delay,
	jMD_lfo1Fade,
	jMD_lfo2Rate,
	jMD_lfo2Phase,
	jMD_lfo2Delay,
	jMD_lfo2Fade,
	jMD_lfo3Rate,
	jMD_lfo3Phase,
	jMD_lfo3Delay,
	jMD_lfo3Fade,
	jMD_lfo4Rate,
	jMD_lfo4Phase,
	jMD_lfo4Delay,
	jMD_lfo4Fade,
	jMD_filter1Cutoff,
	jMD_filter1Q,
	jMD_filter1KeyFlw,
	jMD_filter1Wet,
	jMD_filter2Cutoff,
	jMD_filter2Q,
	jMD_filter2KeyFlw,
	jMD_filter2Wet,
	jMD_total,

	jMS_none = 0,
	jMS_velocity,
	jMS_afterTouch,
	jMS_pitchBend,
	jMS_modWheel,
	jMS_note,
	jMS_env1,
	jMS_env2,
	jMS_env3,
	jMS_env4,
	jMS_lfo1,
	jMS_lfo2,
	jMS_lfo3,
	jMS_lfo4,
	jMS_c1,
	jMS_c2,
	jMS_c3,
	jMS_c4,
	jMS_c5,
	jMS_c6,
	jMS_c7,
	jMS_c8,
	jMS_c9,
	jMS_c10,
	jMS_c11,
	jMS_c12,
	jMS_c13,
	jMS_c14,
	jMS_c15,
	jMS_c16,
	jMS_total
};

void getDestName(VstInt32 value, char* text);
void getSourceName(VstInt32 value, char* text);

#endif