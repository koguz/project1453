#ifndef BASEBUILDING__H__
#define BASEBUILDING__H__

#include <iostream>
#include <string>
#include <vector>
#include "BaseObject.h"
#include "BaseGraphicObject.h"
#include "Sprite.h"
#include "SDLMixer.h"

using namespace std;

/* The base class which all other buildings are derived. 
 * It derives from both BaseObject & BaseGraphicObject
 */

class BaseBuilding:public BaseObject, public BaseGraphicObject
{
	public:
	BaseBuilding();
	BaseBuilding(SDL_Surface *scr, Player *p, string n);
	~BaseBuilding();
	
	void setState(string state);
	string getState();
	
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
	
	protected:
	int sight;
	int size;
	SDLMixer *birimTamam;
	
	// grafikler
	string curState;
	Sprite sprite;
};




#endif

