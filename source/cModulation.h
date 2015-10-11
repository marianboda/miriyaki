// Trieda cModulation
#ifndef __cmodulation_h__
#define __cmodulation_h__
#include "../vst2.x/audioeffectx.h"
#include <math.h>
#include "cGlobals.h"

enum
{
};

class cModulation
{
  public:
    cModulation();
    ~cModulation();
	void modulate();
   float *source[jMS_total];
   float *destination[jMD_total];

  private:
};
 
#endif