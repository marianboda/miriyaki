//------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <windows.h>
#include <gdiplus.h>
 using namespace Gdiplus; 
#pragma comment(lib, "gdiplus.lib")

#include "cEnvDisplay.h"

//------------------------------------------------------------------------
// cEnvDisplay
//------------------------------------------------------------------------

cEnvDisplay::cEnvDisplay (const CRect &size, CBitmap *pBackground,
				float *pAttack, float *pDecay, float *pSustain,
				float *pTime, float *pRelease)
: CView (size)
{
   attack = pAttack;
   decay = pDecay;
   sustain = pSustain;
   time = pTime;
   release = pRelease;
   background = pBackground;
   setDirty(true);
}

//------------------------------------------------------------------------
cEnvDisplay::~cEnvDisplay ()
{}

//------------------------------------------------------------------------
void cEnvDisplay::draw (CDrawContext *pContext)
{
	if (background)
		{
			CPoint lOffset(293,18);

			if (bTransparencyEnabled)
				background->drawTransparent (pContext, size, CPoint (0, 0));
			else
				background->draw (pContext, size, CPoint (0, 0));
	}
			//pContext->setFillColor(kBlackCColor);
	CPoint p1(size.left + 5, size.bottom - 5);
	CPoint p2(size.left+5+floor(*attack * 13), size.top + 5);
	CPoint p3(size.left+5+floor(*attack * 13)+floor(*decay * 13),size.bottom - 5 - floor(*sustain * 24 + 0.5));
	CPoint p4(size.right-18, size.bottom - 5 - floor(*sustain * 24 + 0.5));
	CPoint p5(size.right-18 + floor(*release * 13),size.bottom-5);

	if (*time > 0.5)
		p4.y = size.bottom - 5 - floor((*sustain * 24) + ((*time-0.5)*2 * (1-*sustain)*24)+0.5);
	else 
		p4.y = size.bottom - 5 - floor((*sustain * 24) - ((-*time+0.5)*2 * (24-(1-*sustain) * 24))+0.5);

	float tempX = p3.x + 40*cosf(M_PI*(*time-0.5));
	float tempY = p3.y - 40*sinf(M_PI*(*time-0.5));

	if ((p3.y - tempY) > 0)
	{
		if (p3.y - size.top - 5 == 0)
		{
			tempX = p4.x;
			tempY = p3.y;
		}
		else
		{
			float ratio = (tempX - p3.x)/(float)(p3.y - tempY);
			float bound = (p4.x - p3.x)/(float)(p3.y - size.top - 5);

			if (ratio > bound)
			{
				tempX = p4.x;
				if (tempX != p3.x)
				{
					tempY = p3.y - ((tempX-p3.x) / ratio);
					p4.y = tempY;
				}
				else
				{
					tempY = size.top - 5;
					p4.y = size.top + 5;
				}

			}
			else
			{
				tempY = size.top + 5;
				p4.y = size.top + 5;
				tempX = (p3.y - tempY) * ratio + p3.x;
			}
		}
	}
	else if (p3.y - tempY == 0)
	{
		tempX = p4.x;
	}
	else
	{
		if (p3.y - size.bottom + 5 == 0)
		{
			tempX = p4.x;
			tempY = p3.y;
		}
		else
		{
			float ratio = (tempX - p3.x)/(float)(tempY - p3.y);
			float bound = (p4.x - p3.x)/(float)(size.bottom - 5 - p3.y);

			if (ratio > bound)
			{
				tempX = p4.x;
				if (tempX != p3.x)
				{
					tempY = p3.y + ((tempX-p3.x) / ratio);
					p4.y = tempY;
				}
				else
				{
					tempY = size.bottom - 5;
					p4.y = size.bottom - 5;
				}
			}
			else
			{
				tempY = size.bottom - 5;
				p4.y = size.bottom - 5;
				tempX = (tempY - p3.y) * ratio + p3.x;
			}
		}
	}



	CPoint pp4(tempX,tempY);

	CColor color;
	color(215,255,135,255);
	drawLine(pContext,p1,p2,color);
	drawLine(pContext,p2,p3,color);
	drawLine(pContext,p3,pp4,color);
	drawLine(pContext,pp4,p4,color);
	drawLine(pContext,p4,p5,color);
	
   setDirty (false);
}

//------------------------------------------------------------------------
void cEnvDisplay::mouse (CDrawContext *pContext, CPoint &where, long button)
{

}
void cEnvDisplay::blendPixel(CDrawContext *context, CPoint point, CColor color)
{
   CColor current_color, dest_color;
   int temp;

   current_color = context->getPoint(point);

   temp = current_color.red + (int)((float)(color.red-current_color.red) * ((float)color.alpha/255.0f));
   if(temp > 255)
      temp = 255;
   dest_color.red = temp;

   temp = current_color.green + (int)((float)(color.green-current_color.green) * ((float)color.alpha/255.0f));
   if(temp > 255)
      temp = 255;
   dest_color.green = temp;

   temp = current_color.blue + (int)((float)(color.blue-current_color.blue) * ((float)color.alpha/255.0f));
   if(temp > 255)
      temp = 255;
   dest_color.blue = temp;

   dest_color.alpha = current_color.alpha;

   context->drawPoint(point, dest_color);
}

void cEnvDisplay::drawLine(CDrawContext *context, CPoint pPoint1,CPoint pPoint2, CColor color)
{
	float grad, xd, yd;
	float xgap, ygap, xend, yend, xf, yf, brightness1 , brightness2;
	int ix1, ix2, iy1, iy2;
	float x1, x2, y1, y2, temp;
	unsigned char c1, c2;
	CColor tempColor;

		x1 = pPoint1.x;
		x2 = pPoint2.x;
		y1 = pPoint1.y;
		y2 = pPoint2.y;

	xd = (x2-x1);
	yd = (y2-y1);

	if (abs(xd) > abs(yd))
	{
		if (x1>x2)
		{
			temp = x1; x1 = x2; x2 = temp;
			temp = y1; y1 = y2; y2 = temp;
			xd = (x2-x1);
			yd = (y2-y1);
		}
		grad = yd/xd;
		// POINT 1 ------------------------------------
		xend = floor(x1+0.5f);
		yend = y1 + grad*(xend-x1);
		xgap = invfrac(x1+0.5f);
		ix1 = (int) xend;
		iy1 = (int) yend;

		brightness1 = invfrac(yend) * xgap;
		brightness2 =    frac(yend) * xgap;
		c1 = (unsigned char)(brightness1 * 255);
		c2 = (unsigned char)(brightness2 * 255);	

		tempColor(color.red,color.green,color.blue,c1);
		drawPixelWithGlow(context,CPoint(ix1,iy1),tempColor);
		tempColor.alpha = c2;
		drawPixelWithGlow(context,CPoint(ix1,iy1+1),tempColor);
		yf = yend + grad;
		// POINT 2 ------------------------------------
		xend = floor(x2+0.5f);
		yend = y2 + grad*(xend-x2);
		xgap = invfrac(x2+0.5f);
		ix2 = (int) xend;
		iy2 = (int) yend;

		brightness1 = invfrac(yend) * xgap;
		brightness2 =    frac(yend) * xgap;
		c1 = (unsigned char)(brightness1 * 255);
		c2 = (unsigned char)(brightness2 * 255);	

		tempColor(color.red,color.green,color.blue,c1);
		drawPixelWithGlow(context,CPoint(ix2,iy2),tempColor);
		tempColor.alpha = c2;
		drawPixelWithGlow(context,CPoint(ix2,iy2+1),tempColor);
		

		if ((ix1+1)<=(ix2-1))
		{
			for (int i=(ix1+1);i<=(ix2-1);i++)
			{
				brightness1 = invfrac(yf);
				brightness2 =    frac(yf);
				c1 = (unsigned char)(brightness1 * 255);
				c2 = (unsigned char)(brightness2 * 255);

				tempColor(color.red,color.green,color.blue,c1);
				drawPixelWithGlow(context,CPoint(i,(int)floor(yf)),tempColor);
				tempColor.alpha = c2;
				drawPixelWithGlow(context,CPoint(i,(int)yf+1),tempColor);

				yf = yf + grad;
			}
		}
		else
		{
			for (int i=(ix1+1);i<=(ix2-1);i--)
			{
				brightness1 = invfrac(yf);
				brightness2 =    frac(yf);
				c1 = (unsigned char)(brightness1 * 255);
				c2 = (unsigned char)(brightness2 * 255);

				tempColor(color.red,color.green,color.blue,c1);
				drawPixelWithGlow(context,CPoint(i,(int)floor(yf)),tempColor);
				tempColor.alpha = c2;
				drawPixelWithGlow(context,CPoint(i,(int)yf+1),tempColor);

				yf = yf + grad;
			}
		}

	}
	else
	{
		if (y1>y2)
		{
			temp = x1; x1 = x2; x2 = temp;
			temp = y1; y1 = y2; y2 = temp;
			xd = (x2-x1);
			yd = (y2-y1);
		}
		grad = xd/yd;
		// POINT 1 ------------------------------------
		yend = floor(y1+0.5f);
		xend = x1 + grad*(yend-y1);
		ygap = invfrac(y1+0.5f);
		ix1 = (int) xend;
		iy1 = (int) yend;

		brightness1 = invfrac(xend) * ygap;
		brightness2 =    frac(xend) * ygap;
		c1 = (unsigned char)(brightness1 * 255);
		c2 = (unsigned char)(brightness2 * 255);	

		tempColor(color.red,color.green,color.blue,c1);
		drawPixelWithGlow(context,CPoint(ix1,iy1),tempColor);
		tempColor.alpha = c2;
		drawPixelWithGlow(context,CPoint(ix1+1,iy1),tempColor);
		xf = xend + grad;
		// POINT 2 ------------------------------------
		yend = floor(y2+0.5f);
		xend = x2 + grad*(yend-y2);
		ygap = invfrac(y2+0.5f);
		ix2 = (int) xend;
		iy2 = (int) yend;

		brightness1 = invfrac(xend) * ygap;
		brightness2 =    frac(xend) * ygap;
		c1 = (unsigned char)(brightness1 * 255);
		c2 = (unsigned char)(brightness2 * 255);	

		tempColor(color.red,color.green,color.blue,c1);
		drawPixelWithGlow(context,CPoint(ix2,iy2),tempColor);
		tempColor.alpha = c2;
		drawPixelWithGlow(context,CPoint(ix2+1,iy2),tempColor);
		

		int cnt = 0;
		if ((iy1+1)<=(iy2-1))
		{
			for (int i=(iy1+1);i<=(iy2-1);i++)
			{
				if (cnt++ > 500) break;
				brightness1 = invfrac(xf);
				brightness2 =    frac(xf);
				c1 = (unsigned char)(brightness1 * 255);
				c2 = (unsigned char)(brightness2 * 255);

				tempColor(color.red,color.green,color.blue,c1);
				drawPixelWithGlow(context,CPoint((int)floor(xf),i),tempColor);
				tempColor.alpha = c2;
				drawPixelWithGlow(context,CPoint((int)floor(xf+1),i),tempColor);

				xf = xf + grad;
			}
		}
		else
		{
			for (int i=(iy1+1);i<=(iy2-1);i--)
			{
				if (cnt++ > 500) break;
				brightness1 = invfrac(xf);
				brightness2 =    frac(xf);
				c1 = (unsigned char)(brightness1 * 255);
				c2 = (unsigned char)(brightness2 * 255);

				tempColor(color.red,color.green,color.blue,c1);
				drawPixelWithGlow(context,CPoint((int)floor(xf),i),tempColor);
				tempColor.alpha = c2;
				drawPixelWithGlow(context,CPoint((int)floor(xf+1),i),tempColor);

				xf = xf + grad;
			}

		}

	}

}

void cEnvDisplay::drawPixelWithGlow(CDrawContext *context, CPoint point, CColor color)
{
	blendPixel(context,point, color);
	CColor temp;
	temp(color.red,color.green,color.blue,color.alpha/8);
	blendPixel(context,CPoint(point.x+1,point.y), temp);
	blendPixel(context,CPoint(point.x-1,point.y), temp);
	blendPixel(context,CPoint(point.x,point.y+1), temp);
	blendPixel(context,CPoint(point.x,point.y-1), temp);
	temp(color.red,color.green,color.blue,color.alpha/16);
	blendPixel(context,CPoint(point.x+1,point.y+1), temp);
	blendPixel(context,CPoint(point.x-1,point.y-1), temp);
	blendPixel(context,CPoint(point.x-1,point.y+1), temp);
	blendPixel(context,CPoint(point.x+1,point.y-1), temp);
}


float frac(float x)
{
	return x - floor(x);
}
float invfrac(float x)
{
	return 1-(frac(x));
}
