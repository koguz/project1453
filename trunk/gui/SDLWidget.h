#ifndef SDLWIDGET_H_
#define SDLWIDGET_H_

#define BLACK 0x000000FF
#define WHITE 0xFFFFFFFF
#define GRAY  0xCCCCCCFF
#define DARKGRAY 0xAAAAAAFF
#define DARKERGRAY 0x444444FF
#define BLUE 0x336699FF

#include <iostream>
#include "Headers.h"
#include "callback.h"

using namespace std;

class SDLWidget
{
	public:
	SDLWidget();
	SDLWidget(char *fileName);
	enum WidgetType { WIDGET, BUTTON, COMBO, COMBOOPTION, CHECKBOX, TEXTVIEW };
	WidgetType getType() { return tip; }
	
	virtual void drawWidget(SDL_Surface *screen)
	{
		SDL_Rect src, dest;
		src.x = 0;
		src.y = 0;
		src.w = w;
		src.h = h;
		
		dest.x = px1;
		dest.y = py1;
		dest.w = w;
		dest.h = h;
		
		SDL_BlitSurface(widget, &src, screen, &dest);
	}
	
	virtual void setPosition(int x, int y)
	{
		px1 = x;
		py1 = y;
		px2 = px1 + w;
		py2 = py1 + h;
	}
	
	int getWidth() { return w; }
	int getHeight() { return h; }
	
	protected:
	SDL_Surface *widget;
	WidgetType tip;
	int px1, px2, py1, py2;
	int w, h;
};

#endif /*SDLWIDGET_H_*/

