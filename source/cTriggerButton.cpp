//------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "cTriggerButton.h"

//------------------------------------------------------------------------
// cTriggerButton
//------------------------------------------------------------------------

cTriggerButton::cTriggerButton (const CRect &size, CControlListener *listener,
                  CBitmap *background, char pOscId)
: CControl (size, listener, -1, background)
{
	oscId = pOscId;
}

//------------------------------------------------------------------------
cTriggerButton::~cTriggerButton ()
{}

//------------------------------------------------------------------------
void cTriggerButton::draw (CDrawContext *pContext)
{
   CCoord off;

	if (pBackground)
		{

			off = (value != 0.f) ?(pBackground->getHeight()/2) : 0;

			if (bTransparencyEnabled)
				pBackground->drawTransparent (pContext, size, CPoint (0, off));
			else
				pBackground->draw (pContext, size, CPoint (0, off));
		}
   setDirty (false);
}

//------------------------------------------------------------------------
void cTriggerButton::mouse (CDrawContext *pContext, CPoint &where, long button)
{
   if (!bMouseEnabled) return;   
   if (button == -1) button = pContext->getMouseButtons ();
   if (listener && button & (kAlt | kShift | kControl | kApple))
   {
      if (listener->controlModifierClicked (pContext, this, button) != 0)
         return;
   }
   if (!(button & kLButton)) return;

   float fEntryState = value;

   beginEdit ();
   
   bool turnOff = false;

   if (pContext->getMouseButtons () == kLButton)
   {
      do
      {
         if (where.h >= size.left && where.v >= size.top  &&
             where.h <= size.right && where.v <= size.bottom)
				 value = (fEntryState == 0.f)? 1.f : 0.f;
         else
            {
              value = fEntryState;
              turnOff = true;
            }

         if (isDirty () && listener)
            listener->valueChanged (pContext, this);
         
         getMouseLocation (pContext, where);
         
         doIdleStuff ();
      }
      while ((pContext->getMouseButtons () == kLButton)&&(!turnOff));
   }

   value = 0.0f;
   if (listener) listener->valueChanged (pContext, this);

   endEdit ();
}
