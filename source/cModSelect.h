#ifndef __cmodselect_h__
#define __cmodselect_h__

#include "../vstgui/vstcontrols.h"
#include "modulationConstants.h"
#include "cGlobals.h"

class cModSelect : public CControl
{
public:
   cModSelect (const CRect &size, CControlListener *listener, long tag,
                  CBitmap *background, long states, bool pIsSource = true, long style = kPreListenerUpdate);
   virtual ~cModSelect ();

   virtual void draw (CDrawContext*);
   virtual void mouse (CDrawContext *pContext, CPoint &where, long button = -1);

   virtual long getStyle () const { return style; }
   virtual void setStyle (long newStyle) { style = newStyle; }

   enum {
      kPreListenerUpdate,       // listener sa zavola pred volanim metody doIdleStuff
      kPostListenerUpdate,      // listener sa zavola po volani metody doIdleStuff
   };

   CLASS_METHODS(cModSelect, CControl)
protected:
   long style;
   long statesCount;
   bool isSource;
};

#endif