#ifndef SDLPROGBAR__H__
#define SDLPROGBAR__H__

#include <iostream>
#include <string>
#include "Headers.h"
#include "SDLWidget.h"
// #include "SDLFont.h"

using namespace std;

class SDLProgressBar:public SDLWidget
{
	public:
	SDLProgressBar(int w, int h, Uint32 c=BLUE, int minimum=0, int maximum=100);
	
	virtual void drawWidget(SDL_Surface *screen)
	{
		rectangleColor(screen, px1, py1, px2, py2, c);
		if (v!=min)
		{
			int val = (w * v)/max;
			boxColor(screen, px1+1, py1+1, px1+val, py2-1, c);
		}
	}
	
	int getValue();
	void setValue(int p);
	void setMax(int m);
	
	protected:
	Uint32 c;
	int v;
	int min;
	int max;	
};



#endif
