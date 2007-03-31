#ifndef SDLLABEL__H_
#define SDLLABEL__H_

#include <iostream>
#include <string>
#include <sstream>
#include "Headers.h"
#include "SDLWidget.h"
#include "SDLFont.h"


using namespace std;

class SDLLabel:public SDLWidget
{
	public: 
	SDLLabel(); 
	SDLLabel(string lbl, int s=14); 
	SDLLabel(int lbl, int s=14);
	~SDLLabel();
	
	virtual void drawWidget(SDL_Surface *screen)
	{
		SDL_Rect dest;
		
		dest.x = px1;
		dest.y = py1;
		dest.w = widget->w;
		dest.h = widget->h;
		
		SDL_BlitSurface(widget, NULL, screen, &dest);
	}
	
	void setText(string lbl);
	void setText(int lbl); 
	string getText();
	
	protected:
	string label;
	int size; 
};



#endif

