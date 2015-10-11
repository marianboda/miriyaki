#include "functions.h"

void floatToOctave (float value, char* string)
{
	VstInt32 lOct = (VstInt32)floor(value*9-4);
	if (lOct < -4)
		lOct = -4;
	else if (lOct > 4)
		lOct = 4;

	 sprintf (string, "%d", (int)(lOct));
}
void floatToCoarse (float value, char* string)
{
	VstInt32 lCoa = (VstInt32)floor(value*25-12);
	if (lCoa < -12)
		lCoa = -12;
	else if (lCoa > 12)
		lCoa = 12;

	 sprintf (string, "%d", (int)(lCoa));
}
void floatToFine (float value, char* string)
{
	VstInt32 lFin = (VstInt32)floor(value*201-100);
	if (lFin < -100)
		lFin = -100;
	else if (lFin > 100)
		lFin = 100;
	if (lFin > 0)
		sprintf (string, "+%d", (int)(lFin));
	else
		sprintf (string, "%d", (int)(lFin));
}


void floatToPan (float value, char* string)
{
	VstInt32 lPan = (VstInt32)floor(value*201-100);
	if (lPan < -100)
		lPan = -100;
	else if (lPan > 100)
		lPan = 100;
	
	if (lPan == 0)
		sprintf (string, "0");
	else if (lPan>0)
		sprintf (string, "%d R", (int)(lPan));
	else
		sprintf (string, "%d L", (int)(0-lPan));
}
void floatToLevel (float value, char* string)
{
	VstInt32 lLev = (VstInt32)floor(value*100);
	if (lLev > 100)
		lLev = 100;

	 sprintf (string, "%d", (int)(lLev));
}
void floatToEnvTime (float value, char* string)
{
	float lTime = powf(value,3.0f) * 12;
	if (lTime > 1)
		sprintf (string, "%.1fs", lTime);
	else if (lTime > 0.1f)
	{
		float lTimeMs = 1000 * lTime;
		sprintf (string, "%.0fms", lTimeMs);
	}
	else if (lTime > 0.01f)
	{
		float lTimeMs = 1000 * lTime;
		sprintf (string, "%.1fms", lTimeMs);
	}
	else
	{
		float lTimeMs = 1000 * lTime;
		sprintf (string, "%.2fms", lTimeMs);
	}
}
void floatToFloat (float value, char* string)
{
	sprintf (string, "%.3f", value);
}
void floatToOscWaveform (float value, char* string)
{
	VstInt32 i;

	i = (VstInt32) floor (value*5);
	if (i > 4)
		i=4;
	switch (i)
	{
		case 0: sprintf (string, "sine");break;
		case 1: sprintf (string, "triangle");break;
		case 2: sprintf (string, "sawtooth");break;
		case 3: sprintf (string, "square");break;
		case 4: sprintf (string, "noise");break;
	}
}
void floatToPhase (float value, char* string)
{
	VstInt32 lPhase = (VstInt32)floor(value*361-180);
	if (lPhase < -180)		lPhase = -180;
	else if (lPhase > 180)	lPhase = 180;
	if (lPhase > 0)
		sprintf (string, "+%d", (int)(lPhase));
	else
		sprintf (string, "%d", (int)(lPhase));
}
void floatToRange (float value, char* string)
{
	float lRange = 0.01 * powf(10,value*3);
	
	if (lRange >= 10.f)
	{
		lRange = 10.f;
		sprintf (string, "%.1fHz", lRange);
	}
	else
		sprintf (string, "%.2fHz", lRange);
}
void floatToRate (float value, char* string)
{
	float lRate = powf(10,value);
	sprintf (string, "%.2fx", lRate);
}

void floatToCutoffFreq (float value, char* string)
{
	float lCutoff = 20 + powf(value,4.0f) *19980.f;
	if (lCutoff < 1000.f)
		sprintf (string, "%.0fHz", lCutoff);
	else if (lCutoff < 10000.f)
		sprintf (string, "%.2fk", (lCutoff / 1000.f));
	else
		sprintf (string, "%.1fk", (lCutoff / 1000.f));
}
void floatToQ (float value, char* string)
{
	VstInt32 lQ = (VstInt32)floor(10*value+0.5);
	if (lQ > 10) lQ = 10;
	
	
	sprintf (string, "%i", lQ);
}
