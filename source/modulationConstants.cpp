#include "modulationConstants.h"

void getDestName(VstInt32 index, char* text)
{
switch (index)
	{
		case (jMD_osc1Pitch):		vst_strncpy (text, "osc1 pitch", 18);break;
		case (jMD_osc1Pan):			vst_strncpy (text, "osc1 pan", 18);break;
		case (jMD_osc1Level):		vst_strncpy (text, "osc1 level", 18);break;
		case (jMD_osc2Pitch):		vst_strncpy (text, "osc2 pitch", 18);break;
		case (jMD_osc2Pan):			vst_strncpy (text, "osc2 pan", 18);break;
		case (jMD_osc2Level):		vst_strncpy (text, "osc2 level", 18);break;
		case (jMD_osc3Pitch):		vst_strncpy (text, "osc3 pitch", 18);break;
		case (jMD_osc3Pan):			vst_strncpy (text, "osc3 pan", 18);break;
		case (jMD_osc3Level):		vst_strncpy (text, "osc3 level", 18);break;
		case (jMD_osc4Pitch):		vst_strncpy (text, "osc4 pitch", 18);break;
		case (jMD_osc4Pan):			vst_strncpy (text, "osc4 pan", 18);break;
		case (jMD_osc4Level):		vst_strncpy (text, "osc4 level", 18);break;
		case (jMD_voicePitch):		vst_strncpy (text, "voice pitch", 18);break;
		case (jMD_ampVolume):		vst_strncpy (text, "amp volume", 18);break;
		case (jMD_env1Attack):		vst_strncpy (text, "env1 attack", 18);break;
		case (jMD_env1Decay):		vst_strncpy (text, "env1 decay", 18);break;
		case (jMD_env1Sustain):		vst_strncpy (text, "env1 sustain", 18);break;
		case (jMD_env1Time):		vst_strncpy (text, "env1 time", 18);break;
		case (jMD_env1Release):		vst_strncpy (text, "env1 release", 18);break;
		case (jMD_env2Attack):		vst_strncpy (text, "env2 attack", 18);break;
		case (jMD_env2Decay):		vst_strncpy (text, "env2 decay", 18);break;
		case (jMD_env2Sustain):		vst_strncpy (text, "env2 sustain", 18);break;
		case (jMD_env2Time):		vst_strncpy (text, "env2 time", 18);break;
		case (jMD_env2Release):		vst_strncpy (text, "env2 release", 18);break;
		case (jMD_env3Attack):		vst_strncpy (text, "env3 attack", 18);break;
		case (jMD_env3Decay):		vst_strncpy (text, "env3 decay", 18);break;
		case (jMD_env3Sustain):		vst_strncpy (text, "env3 sustain", 18);break;
		case (jMD_env3Time):		vst_strncpy (text, "env3 time", 18);break;
		case (jMD_env3Release):		vst_strncpy (text, "env3 release", 18);break;
		case (jMD_env4Attack):		vst_strncpy (text, "env4 attack", 18);break;
		case (jMD_env4Decay):		vst_strncpy (text, "env4 decay", 18);break;
		case (jMD_env4Sustain):		vst_strncpy (text, "env4 sustain", 18);break;
		case (jMD_env4Time):		vst_strncpy (text, "env4 time", 18);break;
		case (jMD_env4Release):		vst_strncpy (text, "env4 release", 18);break;
		case (jMD_lfo1Rate):		vst_strncpy (text, "lfo1 rate", 18);break;
		case (jMD_lfo1Phase):		vst_strncpy (text, "lfo1 phase", 18);break;
		case (jMD_lfo1Delay):		vst_strncpy (text, "lfo1 delay", 18);break;
		case (jMD_lfo1Fade):		vst_strncpy (text, "lfo1 fade", 18);break;
		case (jMD_lfo2Rate):		vst_strncpy (text, "lfo2 rate", 18);break;
		case (jMD_lfo2Phase):		vst_strncpy (text, "lfo2 phase", 18);break;
		case (jMD_lfo2Delay):		vst_strncpy (text, "lfo2 delay", 18);break;
		case (jMD_lfo2Fade):		vst_strncpy (text, "lfo2 fade", 18);break;
		case (jMD_lfo3Rate):		vst_strncpy (text, "lfo3 rate", 18);break;
		case (jMD_lfo3Phase):		vst_strncpy (text, "lfo3 phase", 18);break;
		case (jMD_lfo3Delay):		vst_strncpy (text, "lfo3 delay", 18);break;
		case (jMD_lfo3Fade):		vst_strncpy (text, "lfo3 fade", 18);break;
		case (jMD_lfo4Rate):		vst_strncpy (text, "lfo4 rate", 18);break;
		case (jMD_lfo4Phase):		vst_strncpy (text, "lfo4 phase", 18);break;
		case (jMD_lfo4Delay):		vst_strncpy (text, "lfo4 delay", 18);break;
		case (jMD_lfo4Fade):		vst_strncpy (text, "lfo4 fade", 18);break;
		case (jMD_filter1Cutoff):	vst_strncpy (text, "filter1 cutoff", 18);break;
		case (jMD_filter1Q):		vst_strncpy (text, "filter1 q", 18);break;
		case (jMD_filter1KeyFlw):	vst_strncpy (text, "filter1 keyflw", 18);break;
		case (jMD_filter1Wet):		vst_strncpy (text, "filter1 wet", 18);break;
		case (jMD_filter2Cutoff):	vst_strncpy (text, "filter2 cutoff", 18);break;
		case (jMD_filter2Q):		vst_strncpy (text, "filter2 q", 18);break;
		case (jMD_filter2KeyFlw):	vst_strncpy (text, "filter2 keyflw", 18);break;
		case (jMD_filter2Wet):		vst_strncpy (text, "filter2 wet", 18);break;
		default:					vst_strncpy (text, "---", 18);break;
	}	
}

void getSourceName(VstInt32 index, char* text)
{
switch (index)
	{
		case (jMS_velocity):	vst_strncpy (text, "velocity", 18);break;
		case (jMS_afterTouch):	vst_strncpy (text, "aftertouch", 18);break;
		case (jMS_pitchBend):	vst_strncpy (text, "pitch-bend", 18);break;
		case (jMS_modWheel):	vst_strncpy (text, "mod-wheel", 18);break;
		case (jMS_note):		vst_strncpy (text, "note", 18);break;
		case (jMS_env1):		vst_strncpy (text, "env 1", 18);break;
		case (jMS_env2):		vst_strncpy (text, "env 2", 18);break;
		case (jMS_env3):		vst_strncpy (text, "env 3", 18);break;
		case (jMS_env4):		vst_strncpy (text, "env 4", 18);break;
		case (jMS_lfo1):		vst_strncpy (text, "lfo 1", 18);break;
		case (jMS_lfo2):		vst_strncpy (text, "lfo 2", 18);break;
		case (jMS_lfo3):		vst_strncpy (text, "lfo 3", 18);break;
		case (jMS_lfo4):		vst_strncpy (text, "lfo 4", 18);break;
		case (jMS_c1):			vst_strncpy (text, "controller 1", 18);break;
		case (jMS_c2):			vst_strncpy (text, "controller 2", 18);break;
		case (jMS_c3):			vst_strncpy (text, "controller 3", 18);break;
		case (jMS_c4):			vst_strncpy (text, "controller 4", 18);break;
		case (jMS_c5):			vst_strncpy (text, "controller 5", 18);break;
		case (jMS_c6):			vst_strncpy (text, "controller 6", 18);break;
		case (jMS_c7):			vst_strncpy (text, "controller 7", 18);break;
		case (jMS_c8):			vst_strncpy (text, "controller 8", 18);break;
		case (jMS_c9):			vst_strncpy (text, "controller 9", 18);break;
		case (jMS_c10):			vst_strncpy (text, "controller 10", 18);break;
		case (jMS_c11):			vst_strncpy (text, "controller 11", 18);break;
		case (jMS_c12):			vst_strncpy (text, "controller 12", 18);break;
		case (jMS_c13):			vst_strncpy (text, "controller 13", 18);break;
		case (jMS_c14):			vst_strncpy (text, "controller 14", 18);break;
		case (jMS_c15):			vst_strncpy (text, "controller 15", 18);break;
		case (jMS_c16):			vst_strncpy (text, "controller 16", 18);break;
		default:				vst_strncpy (text, "---", 18);break;
	}	
}