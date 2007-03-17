#ifndef SDLCHECKBOX__H_
#define SDLCHECKBOX__H_

#include <iostream>
#include <string>
#include "SDLWidget.h"
#include "SDLButton.h"
#include "SDLLabel.h"


using namespace std;

class SDLCheckBox:public SDLWidget
{
	public:
	SDLCheckBox(string label);
	~SDLCheckBox();
	
	void toggle();
	bool isChecked();
	
	virtual void drawWidget(SDL_Surface* screen)
	{
		button->drawWidget(screen);
		if (on)
			check->drawWidget(screen);
		yazi->drawWidget(screen);
	}
	
	virtual void setPosition(int x, int y)
	{
		SDLWidget::setPosition(x, y);
		button->setPosition(x, y);
		check->setPosition(x + ((button->getWidth() - check->getWidth()) / 2), y+ ((button->getHeight() - check->getHeight()) / 2) );
		yazi->setPosition(px1 + 10 + button->getWidth(), py1 + ( (button->getHeight() - yazi->getHeight()) / 2 ));
	}
	
	virtual void handleMouseEvent (int eventType, int button, int x, int y)
	{
		handleEvent(eventType, button, x, y);
	}
	
	protected:
	SDLButton *button;
	SDLWidget *check;
	SDLLabel *yazi;
	bool on;
	void setOn();
	void setOff();
	void handleEvent (int eventType, int button, int x, int y);
};


#endif

