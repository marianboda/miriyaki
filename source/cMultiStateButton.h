#ifndef __cmultistatebutton_h__
#define __cmultistatebutton_h__

#include "../vstgui/vstcontrols.h"

class cMultiStateButton : public CControl
{
public:
   cMultiStateButton (const CRect &size, CControlListener *listener, long tag,
                  CBitmap *background, long states, long style = kPreListenerUpdate);
   virtual ~cMultiStateButton ();

   virtual void draw (CDrawContext*);
   virtual void mouse (CDrawContext *pContext, CPoint &where, long button = -1);

   virtual long getStyle () const { return style; }
   virtual void setStyle (long newStyle) { style = newStyle; }

   enum {
      kPreListenerUpdate,       // listener sa zavola pred volanim metody doIdleStuff
      kPostListenerUpdate,      // listener sa zavola po volani metody doIdleStuff
   };

   CLASS_METHODS(cMultiStateButton, CControl)
protected:
   long style;
   long statesCount;
};

#endif