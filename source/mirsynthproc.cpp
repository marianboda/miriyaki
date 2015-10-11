#include "mirsynth.h"

unsigned short combineBytes(unsigned char First, unsigned char Second)
{
   unsigned short _14bit;
   _14bit = (unsigned short)Second;
   _14bit <<= 7;
   _14bit |= (unsigned short)First;
   return(_14bit);
}

//-----------------------------------------------------------------------------------------
// MirSynth
//-----------------------------------------------------------------------------------------
void MirSynth::setSampleRate (float sampleRate)
{
	AudioEffectX::setSampleRate (sampleRate);
	Glob->sampleRate = sampleRate;
	Glob->sampleTime = 1.f/sampleRate;
}
void MirSynth::resume()
{
   AudioEffectX::resume();
   Glob->sampleRate = getSampleRate();
   Glob->sampleTime = 1.0f / Glob->sampleRate;
}


//-----------------------------------------------------------------------------------------
void MirSynth::setBlockSize (VstInt32 blockSize)
{
	AudioEffectX::setBlockSize (blockSize);
}

//-----------------------------------------------------------------------------------------
void MirSynth::initProcess ()
{
}

//-----------------------------------------------------------------------------------------
void MirSynth::processReplacing (float** inputs, float** outputs, VstInt32 sampleFrames)
{
	float* out1 = outputs[0];
	float* out2 = outputs[1];

	{
		while (--sampleFrames >= 0)
		{
			Glob->interpolate();
			(lfo[0]->*(lfo[0]->getValue))();
			(lfo[1]->*(lfo[1]->getValue))();
			(lfo[2]->*(lfo[2]->getValue))();
			(lfo[3]->*(lfo[3]->getValue))();

			
			out_buffer[0]=0.f;
			out_buffer[1]=0.f;
			for (int i=0;i<MAX_POLYPHONY;i++)
				{
					if (voices[i]->isPlaying)
					{
						voices[i]->getSample(voice_buffer);
						out_buffer[0] += voice_buffer[0]; 
						out_buffer[1] += voice_buffer[1]; 
					}
				}

			filter[0]->process(out_buffer);
			filter[1]->process(out_buffer);

			(*out1++) = out_buffer[0];
			(*out2++) = out_buffer[1];
		}
	}						
}

//-----------------------------------------------------------------------------------------
VstInt32 MirSynth::processEvents (VstEvents* ev)
{
	for (VstInt32 i = 0; i < ev->numEvents; i++)
	{
		if ((ev->events[i])->type != kVstMidiType)
			continue;

		Glob->lifeTimeCounter += 1;

		VstMidiEvent* event = (VstMidiEvent*)ev->events[i];
		char* midiData = event->midiData;
		VstInt32 status = midiData[0] & 0xf0;	// ignoracia kanalu
		if (status == 0x90 || status == 0x80)	// noty
		{
			VstInt32 i=0;
			VstInt32 note = midiData[1] & 0x7f;
			VstInt32 velocity = midiData[2] & 0x7f;
			if ((status == 0x80)||(velocity == 0))
			{
				while((i<MAX_POLYPHONY) && ((!voices[i]->isPressed)||(voices[i]->getNote() != note)))
				{
					i++;
				}
				if (i<MAX_POLYPHONY)
					voices[i]->stopNote();
			}
			else
			{
				while((i<MAX_POLYPHONY) && (voices[i]->isPlaying))
				{
					i++;
				}
				if (i<MAX_POLYPHONY)
					voices[i]->playNote(note, velocity, event->deltaFrames, Glob->lifeTimeCounter);
				else
				{
					
					VstInt64 minValue = voices[0]->noteBirth;
					VstInt32 minIndex = 0;
					i=1;
					while(i<MAX_POLYPHONY)
					{
						if (minValue > voices[i]->noteBirth)
						{
							minValue = voices[i]->noteBirth;
							minIndex = i;
						}
						i++;
					}
					voices[minIndex]->changeNote(note, velocity, event->deltaFrames, Glob->lifeTimeCounter);

				}

			}
		}
		else if (status == 0xb0)
		{
			if (midiData[1] == 0x7e || midiData[1] == 0x78)	// vsetky noty vypnut
			{
				for (VstInt32 i=0;i<MAX_POLYPHONY;i++)
					voices[i]->stopNote();
			}
			else if (midiData[1] == 0x01)	// modulacne koliesko
				Glob->midiModWheel = (midiData[2] & 0x7f) / 127.f;
			else
			{
				char m = midiData[1]; // midi kontrolery
				if (m>=0 && m<128)
					Glob->midiController[m] = (midiData[2] & 0x7f) / 127.f;
			}

		}
		else if (status == 0xd0) // midi aftertouch
		{
			Glob->midiAfterTouch = (midiData[1] & 0x7f) / 127.f;
		}
		else if (status == 0xe0) // pitch-bend
		{
			Glob->midiPitchBend = (combineBytes(midiData[1] & 0x7f,midiData[2] & 0x7f)-8192)/8192.f;
		}
		event++;
	}
	return 1;
}

