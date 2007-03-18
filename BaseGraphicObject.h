#ifndef BASEGRAPHICOBJECT__H__
#define BASEGRAPHICOBJECT__H__

#include <iostream>
#include <string>
#include <list>
#include "SDLScreen.h"
#include "SDLCommandButton.h"
#include "SDLProgressBar.h"

class Player;

struct Coordinates
{
	int x;
	int y;
};

class BaseGraphicObject
{
	public:
	BaseGraphicObject();
	BaseGraphicObject(SDL_Surface *scr, Player *p);
	virtual ~BaseGraphicObject();
	
	void setPosition(int x, int y);
	int getX();
	int getY();
	Coordinates getCenter();
	
	void select(); 
	void unselect();
	bool isSelected(); 
	
	bool isMouseOver(int x, int y);
	
	virtual SDL_Surface* getImg() { return 0; }
	virtual SDL_Rect getFrame() { return hotspot; }
	virtual void playSelected() {}
	virtual void playConfirmed() {}
	
	void draw();
	Player *parent;
	
	SDL_Rect hotspot;
	
	SDLScreen* getScreen();
	SDLProgressBar *healthBar;
	SDLScreen *komutlar;
	SDLScreen *komutTanim;
	protected:
	int posx, posy, cx, cy; // cx ve cy merkez noktaları
	SDL_Surface* screen;
	SDL_Surface* loadImg(char *f);
	bool selected;
};


#endif
