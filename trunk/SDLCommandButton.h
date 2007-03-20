#ifndef SDLCOMMANDBUTTON_H_
#define SDLCOMMANDBUTTON_H_

#include <string>
#include "Headers.h"
#include "SDLScreen.h"
#include "SDLWidget.h"
#include "SDLButton.h"
#include "BaseObject.h"

using namespace std;

class SDLCommandButton:public SDLWidget
{
	public:
	SDLCommandButton(SDL_Surface *screen, SDL_Rect kare, string info, Cost c=Cost(0,0,0));
	~SDLCommandButton();
	
	
	virtual void drawWidget(SDL_Surface *screen)
	{
		SDL_Rect dest;
		dest.x = px1 + 2; dest.y = py1 + 2;
		dest.h = dest.w = 44;
		dugme->drawWidget(screen);
		SDL_BlitSurface(ana->getWidget(), &kare, screen, &dest);
		if (over) 
			aciklama->display();
	}
	
	virtual void setPosition(int x, int y)
	{
		SDLWidget::setPosition(x, y);
		dugme->setPosition(x, y);
	}
	
	virtual void handleMouseEvent(int eventType, int button, int x, int y)
	{
		handleEvent(eventType, button, x, y);
	}
	SDLButton *dugme;
	
	static SDLWidget *ana;
	
	protected:
	bool over;
	SDL_Rect kare;
	SDLWidget *woodIcon, *foodIcon, *stoneIcon;
	SDLLabel *lblWood, *lblFood, *lblStone, *lblCommand;
	string inf;
	void handleEvent(int eventType, int button, int x, int y);
	
	SDLScreen *aciklama;
	SDL_Surface *screen;
	
};



#endif
