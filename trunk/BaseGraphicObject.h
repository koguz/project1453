#ifndef BASEGRAPHICOBJECT__H__
#define BASEGRAPHICOBJECT__H__

#include <iostream>
#include <string>
#include <list>
#include "Headers.h"
#include "SDLScreen.h"
#include "SDLCommandButton.h"

struct Coordinates
{
	int x;
	int y;
};

class BaseGraphicObject
{
	public:
	BaseGraphicObject(SDL_Surface *scr);
	
	void setPosition(int x, int y);
	int getX() { return posx; }
	int getY() { return posy; }
	Coordinates getCenter();
	
	void select() { selected = true; }
	void unselect() { selected = false; }
	bool isSelected() { return selected; }
	
	bool isMouseOver(int x, int y);
	
	virtual SDL_Surface* getImg() { return 0; }
	
	virtual void draw()
	{
		
	}
	
	SDLScreen* getScreen() { return komutlar; } 
	SDLProgressBar *healthBar;
	SDLScreen *komutlar;
	SDLScreen *komutTanim;
	protected:
	int posx, posy, cx, cy; // cx ve cy merkez noktaları
	SDL_Surface* screen;
	
	SDLWidget *commandList;
	bool selected;
};


#endif
