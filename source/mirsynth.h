// Trieda

#ifndef __mirsynth__
#define __mirsynth__
#include "cVoice.h"
#include "cOscillator.h"
#include "cLFO.h"
#include "cModulation.h"
#include "cGlobals.h"
#include "../vst2.x/audioeffectx.h"
#include "cMirEditor.h"
#include "cGlobFilter.h"

//------------------------------------------------------------------------------------------
// MirSynthProgram
//------------------------------------------------------------------------------------------
class MirSynthProgram
{
friend class MirSynth;
public:
	MirSynthProgram ();
	~MirSynthProgram () {}

private:
	float params[kNumParams];
	char name[kVstMaxProgNameLen+1];
};

//------------------------------------------------------------------------------------------
// VstXSynth
//------------------------------------------------------------------------------------------
class MirSynth : public AudioEffectX
{
public:
	MirSynth (audioMasterCallback audioMaster);
	~MirSynth ();

	virtual void processReplacing (float** inputs, float** outputs, VstInt32 sampleFrames);
	virtual VstInt32 processEvents (VstEvents* events);

	virtual void setProgram (VstInt32 program);
	virtual void setProgramName (char* name);
	virtual void getProgramName (char* name);
	virtual bool getProgramNameIndexed (VstInt32 category, VstInt32 index, char* text);

	virtual void setParameter (VstInt32 index, float value);
	virtual float getParameter (VstInt32 index);
	virtual void getParameterLabel (VstInt32 index, char* label);
	virtual void getParameterDisplay (VstInt32 index, char* text);
	virtual void getParameterName (VstInt32 index, char* text);
	
	virtual void setSampleRate (float sampleRate);
	virtual void setBlockSize (VstInt32 blockSize);
	virtual void resume();
	
	virtual bool getOutputProperties (VstInt32 index, VstPinProperties* properties);
		
	virtual bool getEffectName (char* name);
	virtual bool getVendorString (char* text);
	virtual bool getProductString (char* text);
	virtual VstInt32 getVendorVersion ();
	virtual VstInt32 canDo (char* text);

	virtual VstInt32 getNumMidiInputChannels ();
	virtual VstInt32 getNumMidiOutputChannels ();


	void defaultPresets();
	void defaultPresets2();
	void defaultPresets3();
	/*void defaultPresets4();
	void defaultPresets5();
	void defaultPresets6();
	void defaultPresets7();
	void defaultPresets8();
	void defaultPresets9();
	void defaultPresets10();*/

	void setOctave(VstInt32 oscId, float value);
	void setCoarse(VstInt32 oscId, float value);
	void setFine(VstInt32 oscId, float value);
	void setOscLevel(VstInt32 oscId, float value);
	void setOscPan(VstInt32 oscId, float value);
	void setOscSync(VstInt32 oscId, float value);
	void setOscWaveform(VstInt32 oscId, float value);

	void setEnvAttack(VstInt32 envId, float value);
	void setEnvDecay(VstInt32 envId, float value);
	void setEnvSustain(VstInt32 envId, float value);
	void setEnvTime(VstInt32 envId, float value);
	void setEnvRelease(VstInt32 envId, float value);

	void setLfoRange(VstInt32 lfoId, float value);
	void setLfoRate(VstInt32 lfoId, float value);
	void turnOnLfoRateInterpolation(VstInt32 lfoId);

	void setLfoPhaseShift(VstInt32 lfoId, float value);
	void setLfoDelay(VstInt32 lfoId, float value);
	void setLfoFade(VstInt32 lfoId, float value);
	void setLfoWaveform(VstInt32 oscId, float value);

	void setFilterCutoff(VstInt32 oscId, float value);
	void setFilterQ(VstInt32 oscId, float value);
	void setFilterKeyFollow(VstInt32 oscId, float value);
	void setFilterMix(VstInt32 oscId, float value);
	void setFilterType(VstInt32 oscId, float value);
	void setFilterRouting(float value);
	void setModSrc(VstInt32 index, float value);
	void setModDst(VstInt32 index, float value);
	void setModAmt(VstInt32 index, float value);


	
private:

	cGlobals *globals;

	cVoice* voices[MAX_POLYPHONY];
	float *out_buffer;
	float *voice_buffer;
	cLFO *lfo[4];
	cGlobFilter *filter[2];

	MirSynthProgram* programs;
	VstInt32 channelPrograms[16];

	VstInt32 playingCount;

	void initProcess ();
	void fillProgram (VstInt32 channel, VstInt32 prg, MidiProgramName* mpn);
};

#endif
