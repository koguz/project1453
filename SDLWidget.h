#ifndef SDLWIDGET_H_
#define SDLWIDGET_H_

#define BLACK 0x000000FF
#define WHITE 0xFFFFFFFF
#define GRAY  0xCCCCCCFF
#define DARKGRAY 0xAAAAAAFF
#define DARKERGRAY 0x444444FF
#define BLUE 0x336699FF
#define GREEN 0x00FF00FF

#include <iostream>
#include "Headers.h"
#include "callback.h"

using namespace std;

/* Base class for all the widgets. */

class SDLWidget
{
	public:
	SDLWidget();
	SDLWidget(char *fileName);
	enum WidgetType { WIDGET, LABEL, BUTTON, COMBO, COMBOOPTION, CHECKBOX, TEXTVIEW, LIST, LISTITEM, COMBUTTON, PROGRESSBAR };
	virtual ~SDLWidget();
	
	WidgetType getType();
	bool isMouseOver(int x, int y);
	bool isShown();
	void setShow(bool b);
	
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
	
	virtual void handleMouseEvent (int eventType, int button, int x, int y)
	{
		// This function does nothing for base widget
	}
	
	int getWidth();
	int getHeight();
	SDL_Surface* getWidget();
	
	protected:
	SDL_Surface *widget; 
	WidgetType tip; 
	int px1, px2, py1, py2, w, h;
	bool show;
};

#endif /*SDLWIDGET_H_*/

