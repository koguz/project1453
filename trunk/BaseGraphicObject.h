#ifndef BASEGRAPHICOBJECT__H__
#define BASEGRAPHICOBJECT__H__

#include <iostream>
#include <string>
#include <list>
#include "Headers.h"
#include "SDLScreen.h"

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
	
// 	virtual void update() { cout << "basegraphic cagrildi?" << endl; }
	virtual SDL_Surface* getImg() { return 0; }
	
	SDLScreen* getScreen() { return komutlar; } 
	
	protected:
	int posx, posy, cx, cy; // cx ve cy merkez noktaları
	SDL_Surface* screen;
	SDLScreen *komutlar;
	bool selected;
};


#endif
