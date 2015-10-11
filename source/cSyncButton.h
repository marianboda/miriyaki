#ifndef __csyncbutton_h__
#define __csyncbutton_h__

#include "../vstgui/vstcontrols.h"

class cSyncButton : public CControl
{
public:
   cSyncButton (const CRect &size, CControlListener *listener, long tag,
                  CBitmap *background, long states, long pOscId, long style = kPreListenerUpdate);
   virtual ~cSyncButton ();

   virtual void draw (CDrawContext*);
   virtual void mouse (CDrawContext *pContext, CPoint &where, long button = -1);

   virtual long getStyle () const { return style; }
   virtual void setStyle (long newStyle) { style = newStyle; }

   enum {
      kPreListenerUpdate,        
      kPostListenerUpdate,      
   };

   CLASS_METHODS(cSyncButton, CControl)
protected:
   long style;
   long statesCount;
   long oscId;
};

#endif