#ifndef BASEBUILDING__H__
#define BASEBUILDING__H__

#include <iostream>
#include <string>
#include <vector>
// #include "Headers.h"
#include "BaseObject.h"
#include "BaseGraphicObject.h"
// #include "SDLScreen.h"
// #include "Player.h"

using namespace std;

// class Player;
// class SDLWidget;
// struct Coordinates;
// class SDLProgressBar;

class BaseBuilding:public BaseObject, public BaseGraphicObject
{
	protected:
	int sight;
	int size;
	SDLWidget *resim;
	
	public:
	BaseBuilding();
	BaseBuilding(SDL_Surface *scr, Player *p, string n);
	virtual SDL_Surface* getImg() { return resim->getWidget(); }
	BaseObject* nowBuilding;
	SDLProgressBar* nowBuildingBar;
	
	void setResim(char* path);
	
	void update();
};




#endif

