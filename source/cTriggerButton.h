#ifndef __ctriggerbutton_h__
#define __ctriggerbutton_h__

#include "../vstgui/vstcontrols.h"

class cTriggerButton : public CControl
{
public:
   cTriggerButton (const CRect &size, CControlListener *listener,
                  CBitmap *background, char pOscId);
   virtual ~cTriggerButton ();

   virtual void draw (CDrawContext*);
   virtual void mouse (CDrawContext *pContext, CPoint &where, long button = -1);

   virtual long getStyle () const { return style; }
   virtual void setStyle (long newStyle) { style = newStyle; }

   CLASS_METHODS(cTriggerButton, CControl)
protected:
   long style;
   char oscId;
};

#endif