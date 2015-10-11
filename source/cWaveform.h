// Trieda cWaveform

#ifndef __cwaveform_h__
#define __cwaveform_h__
#include "../vst2.x/audioeffectx.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <cstdlib>
#include <ctime>
#include "functions.h"
#include "windows.h"
#include "windef.h"

extern void* hInstance;

enum
{
	WAVEFORM_SIZE = 8192,
	NOISEWAVE_SIZE = 262144
};

class cWaveform
{
  public:
    cWaveform();
    ~cWaveform();
	
	float getSineSample(float pPos);
	float getSawSample(float pPos, float exponent);
	float getTriangleSample(float pPos, float exponent);
	float getSquareSample(float pPos, float exponent);
	float getNoiseSample(float pPos);
	float getLfoSineSample(float pPos);
	float getLfoSawSample(float pPos);
	float getLfoTriangleSample(float pPos);
	float getLfoSquareSample(float pPos);
	float getLfoSHSample();
	float getLfoNoiseSample(float pPos);
		VstInt32 tableSize;

private:
	float waveformSine[WAVEFORM_SIZE];
	float waveformSaw[WAVEFORM_SIZE];
	float waveformTriangle[WAVEFORM_SIZE];
	float waveformNoise[NOISEWAVE_SIZE];

	void readResources();

	static int lrint (double const x);

	float *sawTable;
	float *sawPointers[27];
	float *squareTable;
	float *squarePointers[27];
	float *triangleTable;
	float *trianglePointers[27];
	float wavSizes[27];

	float tempValue;
	float tempValue2;
	float tempFraction;
	VstInt32 SHcounter;
};

inline int cWaveform::lrint (double const x)
{ 
	int n;
	#if defined(__unix__) || defined(__GNUC__)
		// 32-bit Linux, Gnu/AT&T syntax:
		__asm ("fldl %1 \n fistpl %0 " : "=m"(n) : "m"(x) : "memory" );
	#else
		// 32-bit Windows, Intel/MASM syntax:
		__asm fld qword ptr x;
		__asm fistp dword ptr n;
	#endif
	return n;
}
 
#endif