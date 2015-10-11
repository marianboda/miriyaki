#include "cModAmtKnob.h"
//------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "cTriggerButton.h"

//------------------------------------------------------------------------
// cModAmtKnob
//------------------------------------------------------------------------

cModAmtKnob::cModAmtKnob (const CRect &size, CControlListener *listener, long tag, long subPixmaps, CCoord heightOfOneImage, CBitmap *background, CPoint &offset)
: CAnimKnob (size, listener, tag, subPixmaps, heightOfOneImage,  background, offset)
{
	
}

//------------------------------------------------------------------------
cModAmtKnob::~cModAmtKnob ()
{}

//------------------------------------------------------------------------
void cModAmtKnob::draw (CDrawContext *pContext)
{
   CCoord off;

	if (pBackground)
		{
			off = (glrint(value*200)) *(pBackground->getHeight()/201);
			if (bTransparencyEnabled)
				pBackground->drawTransparent (pContext, size, CPoint (0, off));
			else
				pBackground->draw (pContext, size, CPoint (0, off));
		}
   setDirty (false);
}

//------------------------------------------------------------------------

void cModAmtKnob::mouse (CDrawContext *pContext, CPoint &where, long button)
{
   if (!bMouseEnabled) return;
   if (button == -1) button = pContext->getMouseButtons ();
   if (!(button & kLButton)) return;

   if (listener && button & (kAlt | kShift | kControl | kApple))
   {
      if (listener->controlModifierClicked (pContext, this, button) != 0)
         return;
   }

   if (checkDefaultValue (pContext, button)) return;

   float old = oldValue;
   CPoint firstPoint;
   float fEntryState = value;
   float middle = (vmax - vmin) * 0.5f;
   float range = 200.f;
   float coef = (vmax - vmin) / range;
   long  oldButton = button;

   VstInt32 mode = kLinearMode;
   VstInt32 modeLinear = true;

   if (mode == kLinearMode && (button & kLButton))
   {
      if (button & kShift)
         range *= zoomFactor;
      firstPoint = where;
      modeLinear = true;
      coef = (vmax - vmin) / range;
   }

   CPoint oldWhere (-1, -1);

   beginEdit ();
   do
   {
      button = pContext->getMouseButtons ();
      if (where != oldWhere)
      {
         oldWhere = where;
         if (modeLinear)
         {
            CCoord diff = (firstPoint.v - where.v);
            if (button != oldButton)
            {
               range = 400.f;
               if (button & kShift)
                  range *= zoomFactor;
   
               float coef2 = (vmax - vmin) / range;
               fEntryState += diff * (coef - coef2);
               coef = coef2;
               oldButton = button;
            }
            value = fEntryState + diff * coef;
            bounceValue ();
         }
         if (isDirty () && listener)
            listener->valueChanged (pContext, this);
      }
      getMouseLocation (pContext, where);
      doIdleStuff ();

   } while (button & kLButton);

   endEdit ();
}