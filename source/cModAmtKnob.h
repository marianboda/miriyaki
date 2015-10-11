#ifndef __cmodamtknob_h__
#define __cmodamtknob_h__

#include "../vstgui/vstcontrols.h"
#include "functions.h"

class cModAmtKnob : public CAnimKnob
{
public:
   cModAmtKnob (const CRect &size, CControlListener *listener, long tag, long subPixmaps, CCoord heightOfOneImage, CBitmap *background, CPoint &offset);
   virtual ~cModAmtKnob ();

   virtual void draw (CDrawContext*);
   virtual void mouse (CDrawContext *pContext, CPoint &where, long button = -1);
   CLASS_METHODS(cModAmtKnob, CAnimKnob)
protected:
};

#endif