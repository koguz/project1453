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
	
	virtual SDL_Surface* getImg() { return resim; }
	
	virtual SDL_Rect getFrame() { return hotspot; }
	
	virtual void draw() // TODO - burada hala sabit sayılar var :( UNUTMA!
	{
		SDL_Rect dest;
		dest.w = dest.h = 64;
		dest.x = posx;
		dest.y = posy;
		SDL_Rect src = getFrame();
		SDL_BlitSurface(getImg(), &src, screen, &dest);
		if (isSelected())
		{
			int ux1 = posx + hotspot.x;
			int ux2 = ux1 + 4;
			int ux3 = ux2 + 19;
			int ux4 = ux3 + 4;
			int uy1 = posy + hotspot.y;
			int uy2 = uy1 + 4;
			int uy3 = uy2 + 19;
			int uy4 = uy3 + 4;
			lineColor(screen, ux1, uy1, ux2, uy1, 0x00FF00FF);
			lineColor(screen, ux3, uy1, ux4, uy1, 0x00FF00FF);
			lineColor(screen, ux1, uy4, ux2, uy4, 0x00FF00FF);
			lineColor(screen, ux3, uy4, ux4, uy4, 0x00FF00FF);
			lineColor(screen, ux1, uy1, ux1, uy2, 0x00FF00FF);
			lineColor(screen, ux1, uy3, ux1, uy4, 0x00FF00FF);
			lineColor(screen, ux4, uy1, ux4, uy2, 0x00FF00FF);
			lineColor(screen, ux4, uy3, ux4, uy4, 0x00FF00FF);
			
			// burası healthBar
			int hx = ux1;
			int hy = uy1 - 10;
			healthBar->setPosition(hx, hy);
			healthBar->drawWidget(screen);
			komutlar->display();
		}
	}
	
	SDL_Rect hotspot;
	
	SDLScreen* getScreen() { return komutlar; } 
	SDLProgressBar *healthBar;
	SDLScreen *komutlar;
	SDLScreen *komutTanim;
	protected:
	int posx, posy, cx, cy; // cx ve cy merkez noktaları
	SDL_Surface* screen;
	SDL_Surface* resim;
	
	SDLWidget *commandList;
	bool selected;
};


#endif
