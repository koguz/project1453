#include "BaseBuilding.h"
#include "Player.h"

BaseBuilding::BaseBuilding()
{
	
}

BaseBuilding::BaseBuilding(SDL_Surface *scr, Player *p, string n):BaseObject(n), BaseGraphicObject(scr, p)
{
	nowBuilding = 0;
	nowBuildingBar = 0;
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
	if (nowBuilding != 0)
	{
		if (nowBuilding->build())
		{
			parent->addObject(nowBuilding);
			nowBuilding = 0;
			nowBuildingBar->setShow(false);
		}
		else
		{
			nowBuildingBar->setValue(nowBuilding->getCurHp());
		}
	}
}

