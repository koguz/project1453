#ifndef SDLLABEL__H_
#define SDLLABEL__H_

#include <iostream>
#include <string>
#include "Headers.h"
#include "SDLWidget.h"
#include "SDLFont.h"


using namespace std;

class SDLLabel:public SDLWidget
{
	public: 
	SDLLabel();
	SDLLabel(string lbl);
	
	virtual void drawWidget(SDL_Surface *screen)
	{
		SDL_Rect dest;
		
		dest.x = px1;
		dest.y = py1;
		dest.w = widget->w;
		dest.h = widget->h;
		
		SDL_BlitSurface(widget, NULL, screen, &dest);
	}
	
	protected:
	string label;
};



#endif

