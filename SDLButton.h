#ifndef SDLBUTTON_H_
#define SDLBUTTON_H_

#include <string>
#include "Headers.h"
#include "SDLWidget.h"
#include "SDLLabel.h"

using namespace std;

class SDLButton:public SDLWidget
{
	public:
	enum ButtonState { NORMAL, OVER, PRESSED };
	
	SDLButton(string f, string label, int size=-1);
	~SDLButton();
	
	
	CBFunctor0 clicked; 
	virtual void drawWidget(SDL_Surface *screen)
	{
		SDL_Rect src, dest;
		src.w = w;
		src.h = h;
		src.x = 0;
		if (bState == NORMAL)
			src.y = 0;
		else if (bState == OVER)
			src.y = h;
		else if (bState == PRESSED)
			src.y = h * 2;
		
		dest.x = px1;
		dest.y = py1;
		dest.w = w;
		dest.h = h;
		SDL_BlitSurface(widget, &src, screen, &dest);
		
		if (metin != 0)
		{
			metin->drawWidget(screen);
		}
	}
	
	virtual void setPosition(int x, int y)
	{
		SDLWidget::setPosition(x, y);
		if (metin != 0)
		{
			metin->setPosition(px1 + ((w - metin->getWidth()) / 2), py1 + ((h - metin->getHeight()) / 2));
		}
	}
	
	virtual void handleMouseEvent(int eventType, int button, int x, int y)
	{
		handleEvent(eventType, button, x, y);
	}
	
	protected:
	ButtonState bState;
	SDLLabel *metin;
	void setState(ButtonState s);
	ButtonState getState();
	void handleEvent(int eventType, int button, int x, int y);
};

#endif /*SDLBUTTON_H_*/
