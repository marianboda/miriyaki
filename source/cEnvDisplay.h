#ifndef __cenvdisplay_h__
#define __cenvdisplay_h__

#include "../vstgui/vstcontrols.h"
#include "cGlobals.h"

class cEnvDisplay : public CView
{
public:
   cEnvDisplay (const CRect &size,
                CBitmap *background,
                float *pAttack,
                float *pDecay,
                float *pSustain,
                float *pTime,
                float *pRelease);
                
   virtual ~cEnvDisplay ();

   virtual void draw (CDrawContext*);
   virtual void mouse (CDrawContext *pContext, CPoint &where, long button = -1);
	void drawAntiAliasedLine(CDrawContext *context, CPoint p1, CPoint p2, CColor color);
	void blendPixel(CDrawContext *context, CPoint point, CColor color);
	void drawPixelWithGlow(CDrawContext *context, CPoint point, CColor color);
	void drawLine(CDrawContext *context, CPoint pPoint1,CPoint pPoint2, CColor color);

   CLASS_METHODS(cEnvDisplay, CView)
protected:
   float *attack;
   float *decay;
   float *sustain;
   float *time;
   float *release;

   CBitmap *background;
  
};
float frac(float x);
float invfrac(float x);

#endif