//------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "cSyncButton.h"

//------------------------------------------------------------------------
// cSyncButton
//------------------------------------------------------------------------

cSyncButton::cSyncButton (const CRect &size, CControlListener *listener, long tag,
                            CBitmap *background, long states, long pOscId, long style)
: CControl (size, listener, tag, background)
, style (style)
{
	statesCount = states;
	oscId = pOscId;
}

//------------------------------------------------------------------------
cSyncButton::~cSyncButton ()
{}

//------------------------------------------------------------------------
void cSyncButton::draw (CDrawContext *pContext)
{
   CCoord off;
   int intOffset;

	if (pBackground)
		{
			intOffset = (int)floor(value * statesCount);
			if (intOffset > statesCount-1) intOffset = statesCount-1;
			if (intOffset >= oscId)
				intOffset += 1;

			off = intOffset * (pBackground->getHeight () / (statesCount + 1));

			if (bTransparencyEnabled)
				pBackground->drawTransparent (pContext, size, CPoint (0, off));
			else
				pBackground->draw (pContext, size, CPoint (0, off));
		}
   setDirty (false);
}

//------------------------------------------------------------------------
void cSyncButton::mouse (CDrawContext *pContext, CPoint &where, long button)
{
   if (!bMouseEnabled)
      return;

    if (button == -1) button = pContext->getMouseButtons ();
   if (!(button & kLButton))
      return;

   if (listener && button & (kAlt | kShift | kControl | kApple))
   {
      if (listener->controlModifierClicked (pContext, this, button) != 0)
         return;
   }
	if (button & (kAlt | kShift))
		{
			value = floor(value * statesCount - 1.0f) / (float)statesCount;
			if (value < 0.0f)
				value = (float)(statesCount-1) / (float)statesCount ;
		}
	else
		{
			value = floor(value * statesCount + 1.0f) / (float)statesCount;
			if (value >= 1.0f)
				value = 0.f;
		}
   if (listener && style == kPostListenerUpdate)
   {
      beginEdit ();
      listener->valueChanged (pContext, this);
      endEdit ();
   }
   doIdleStuff ();
   
   if (listener && style == kPreListenerUpdate)
   {
      beginEdit ();
      listener->valueChanged (pContext, this);
      endEdit ();
   }
}
