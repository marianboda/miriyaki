#ifndef __functions_h__
#define __functions_h__

#include "../vst2.x/audioeffectx.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>

void floatToOctave (float value, char* string);
void floatToCoarse (float value, char* string);
void floatToFine (float value, char* string);
void floatToPan (float value, char* string);
void floatToLevel (float value, char* string);
void floatToFloat (float value, char* string);
void floatToEnvTime (float value, char* string);
void floatToOscWaveform (float value, char* string);
void floatToPhase (float value, char* string);
void floatToRange (float value, char* string);
void floatToRate (float value, char* string);

void floatToCutoffFreq(float value, char* string);
void floatToQ(float value, char* string);


inline int glrint (double const x)
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