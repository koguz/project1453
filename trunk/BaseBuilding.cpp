#include "BaseBuilding.h"

BaseBuilding::BaseBuilding()
{
	
}

BaseBuilding::BaseBuilding(SDL_Surface *scr, Player *p, string n):BaseObject(n), BaseGraphicObject(scr, p)
{
	hitpoints = 400;
	buildRate = 50;
	sight = 4;
	size = 2;
	tip = BUILDING;
}

void BaseBuilding::setResim(char* path)
{
	resim = new SDLWidget(path);
	hotspot.w = resim->getWidth();
	hotspot.h = resim->getHeight();
	hotspot.x = hotspot.y = 0;
}

void BaseBuilding::update() 
{
	healthBar->setValue(currentHp);
}

