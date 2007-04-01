#ifndef SDLPROGBAR__H__
#define SDLPROGBAR__H__

#include <iostream>
#include <string>
#include "Headers.h"
#include "SDLWidget.h"

using namespace std;

class SDLProgressBar:public SDLWidget
{
	public:
	SDLProgressBar(int w, int h, Uint32 c=BLUE, int minimum=0, int maximum=100);
	~SDLProgressBar();
	
	virtual void drawWidget(SDL_Surface *screen)
	{
		rectangleColor(screen, px1, py1, px2, py2, BLACK);
		if (v == max)
		{
			boxColor(screen, px1+1, py1+1, px2-1, py2-1, c);
		}
		else if (v==min)
		{
			boxColor(screen, px1+1, py1+1, px2-1, py2-1, GRAY);
		}
		else 
		{
			int val = (w * v)/max;
			boxColor(screen, px1+1, py1+1, px1+1+val, py2-1, c);
			if (v != max)
				boxColor(screen, px1+1+val, py1+1, px2-1, py2-1, GRAY);
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
