#ifndef SDLCHECKBOX__H_
#define SDLCHECKBOX__H_

#include <iostream>
#include <string>
#include "SDLWidget.h"
#include "SDLButton.h"
#include "SDLFont.h"


using namespace std;


class SDLCheckBox:public SDLWidget
{
	public:
	SDLCheckBox(string label);
	void toggle();
	SDLButton *button;
	
	bool isChecked() { return on; }
	
	virtual void drawWidget(SDL_Surface* screen)
	{
		button->drawWidget(screen);
		if (on)
			check->drawWidget(screen);
		yazi->drawMe(screen, px1 + 30, py1 + ((24-yazi->getHeight())/2));
	}
	
	virtual void setPosition(int x, int y)
	{
		px1 = px2 = x;
		py1 = py2 = y;
		w = 30;
		h = 0;
		button->setPosition(x, y);
		check->setPosition(x+6, y+5);
	}
	
	protected:
	SDL_Surface *metin;
	SDLWidget *check;
	SDLFont *yazi;
	bool on;
	void setOn() { on = true; }
	void setOff() { on = false; }
};


#endif

