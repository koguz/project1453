#ifndef BASEBUILDING__H__
#define BASEBUILDING__H__

#include <iostream>
#include <string>
#include <vector>
#include "Headers.h"
#include "BaseObject.h"
#include "BaseGraphicObject.h"

// NOTE - bu binaların "build queue'su olabilir...

using namespace std;

class BaseBuilding:public BaseObject, public BaseGraphicObject
{
	protected:
	int sight;
	int size;
	SDLWidget *resim;
	
	public:
	BaseBuilding(SDL_Surface *scr, string n);
	virtual SDL_Surface* getImg() { return resim->getWidget(); }
	
	void setResim(char* path);
	
	void update();
};




#endif

