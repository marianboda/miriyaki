//------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>


#include "cModSelect.h"

//------------------------------------------------------------------------
// cModSelect
//------------------------------------------------------------------------

cModSelect::cModSelect (const CRect &size, CControlListener *listener, long tag,
                            CBitmap *background, long states, bool pIsSource, long style)
: CControl (size, listener, tag, background)
, style (style)
{
	statesCount = states;
	isSource = pIsSource;
}

//------------------------------------------------------------------------
cModSelect::~cModSelect ()
{}

//------------------------------------------------------------------------
void cModSelect::draw (CDrawContext *pContext)
{
   CCoord off;

	if (pBackground)
		{
			off = min((int)floor(value * statesCount),statesCount-1) * (pBackground->getHeight () / statesCount);

			if (bTransparencyEnabled)
				pBackground->drawTransparent (pContext, size, CPoint (0, off));
			else
				pBackground->draw (pContext, size, CPoint (0, off));
		}
   setDirty (false);
}

//------------------------------------------------------------------------
void cModSelect::mouse (CDrawContext *pContext, CPoint &where, long button)
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

		{

			CRect r;
            r.offset (where.x, where.y);
            r.offset (-50, 0);
			COptionMenu *menu = new COptionMenu(r,NULL, 0);
			char str[] = "12345678901234567890";
			if (isSource)
			{
				for (VstInt32 i=0; i<jMS_total; i++)
				{
					getSourceName(i,str);
					menu->addEntry (str,i);
				}
			}
			else
			{
				for (VstInt32 i=0; i<jMD_total; i++)
				{
					getDestName(i,str);
					menu->addEntry (str,i);
				}
			}

			getFrame ()->addView (menu);
            menu->takeFocus ();
			long res = menu->getLastResult ();
            getFrame ()->removeView (menu);
			if (res != -1)
			{
				value = (float)(res) / (float)(statesCount-1);
				if (value > 1.f) value = 1.f;

			}
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
