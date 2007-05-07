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
	Coordinates getPosition();
	
	void select(); 
	void unselect();
	bool isSelected(); 
	
	bool isMouseOver(int x, int y); // burada da dikkat etmek gerekecek
	
	virtual SDL_Surface* getImg() { return 0; }
	virtual SDL_Rect getFrame() { return hotspot; }
	virtual void playSelected() {}
	virtual void playConfirmed() {}
	
	// bu fonksiyonu harita cagirabilir, 
	// burada haritanın bilgilerine ihtiyacimiz olacak
	void draw(SDL_Rect s, SDL_Rect d); 
	bool onScreen(int x1, int x2, int y1, int y2);
	
	void drawSubScreen();
	Player *parent; 
	
	SDL_Rect hotspot;
	
	SDLScreen* getScreen();
	SDLProgressBar *healthBar;
	SDLScreen *komutlar;
	SDLScreen *komutTanim;
	
	protected:
	int posx, posy; 
	int cx, cy; // cx ve cy merkez noktaları
	SDL_Surface* screen;
	SDL_Surface* loadImg(char *f);
	bool selected;
};


#endif
