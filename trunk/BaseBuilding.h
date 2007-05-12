#ifndef BASEBUILDING__H__
#define BASEBUILDING__H__

#include <iostream>
#include <string>
#include <vector>
#include "BaseObject.h"
#include "BaseGraphicObject.h"
#include "Sprite.h"

using namespace std;

class BaseBuilding:public BaseObject, public BaseGraphicObject
{
	public:
	BaseBuilding();
	BaseBuilding(SDL_Surface *scr, Player *p, string n);
	~BaseBuilding();
	
	void setState(string state);
	
	virtual SDL_Surface* getImg() 
	{ 
		sprite.setState(curState);
		return sprite.getImg();
	}
	
	virtual SDL_Rect getFrame()
	{
		sprite.setState(curState);
		SDL_Rect r = sprite.getFrame();
		return r;
	}
	
	BaseObject* nowBuilding;
	SDLProgressBar* nowBuildingBar;
	SDLProgressBar* sbar;
	SDLLabel *birimAdi;
	
	bool isClicked(int x, int y);
	
	void update();
	int getSize();
	int getSizeSqr();
	int getSight();
	
	bool onScreen(int x1, int x2, int y1, int y2);
	void draw(SDL_Rect s,SDL_Rect d);
// 	void draw(SDL_Rect s, SDL_Rect d, int tile);
	
	protected:
	int sight;
	int size;
	
	// grafikler
	string curState;
	Sprite sprite;
};




#endif

