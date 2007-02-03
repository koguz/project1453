#ifndef SDLBUTTON_H_
#define SDLBUTTON_H_

#include <string>
#include "Headers.h"
#include "SDLWidget.h"
#include "SDLFont.h"

using namespace std;

class SDLButton:public SDLWidget
{
	public:
	enum ButtonState { NORMAL, OVER, PRESSED };
	SDLButton(string f, string label);
	void setState(ButtonState s) { bState = s; }
	ButtonState getState() { return bState; }
	bool isMouseOver(int x, int y);
	void handleMouseEvent(int eventType, int button, int x, int y);
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
			// font yazarken src'a gerek yok... NULL ver geç
			int fx = (w - metin->w) / 2;
			int fy = (h - metin->h) / 2;
			dest.x = px1 + fx;
			dest.y = py1 + fy;
			dest.w = metin->w;
			dest.h = metin->h;
			
			SDL_BlitSurface(metin, NULL, screen, &dest);
		}
	}
	
	protected:
	ButtonState bState;
	SDL_Surface *metin;
};

#endif /*SDLBUTTON_H_*/
