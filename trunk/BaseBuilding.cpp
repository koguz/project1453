#include "BaseBuilding.h"
#include "Player.h"

BaseBuilding::BaseBuilding()
{
	nowBuilding = 0;
	nowBuildingBar = 0;
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
	
	komutlar = new SDLScreen(screen);
	birimAdi = new SDLLabel(n, 12);
	birimAdi->setPosition(695, 205);
	komutlar->addWidget(birimAdi);
	
}

void BaseBuilding::setState(string state) { curState = state; }

BaseBuilding::~BaseBuilding() { }

void BaseBuilding::update() 
{
	if (selected)
	{
		healthBar->setValue(currentHp);
		sbar->setValue(currentHp);
	}
	if (nowBuilding != 0)
	{
		if (nowBuilding->build())
		{
			switch(nowBuilding->getType())
			{
				case BaseObject::UNIT:
					parent->addUnit((BaseUnit*)nowBuilding);
					break;
				case BaseObject::BUILDING:
					parent->addBuilding((BaseBuilding*)nowBuilding);
					break;
				case BaseObject::TECH:
					parent->addTech((Tech*)nowBuilding);
					break;
				default:
					cerr << "Yapılan nesne eklenemedi..." << endl;
					break;
			}
// 			parent->addObject(nowBuilding);
			nowBuilding = 0;
			nowBuildingBar->setShow(false);
		}
		else
		{
			nowBuildingBar->setValue(nowBuilding->getCurHp());
		}
	}
}

