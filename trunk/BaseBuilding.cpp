#include "BaseBuilding.h"
#include "Player.h"

BaseBuilding::BaseBuilding()
{
	nowBuilding = 0;
	nowBuildingBar = 0;
	selected = false;
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
	selected = false;
}

bool BaseBuilding::isClicked(int x, int y)
{
	return (
		(x >= posx) &&
		(x < posx+size) &&
		(y >= posy) &&
		(y < posy+size)
	);
}

void BaseBuilding::setState(string state) { curState = state; }
int BaseBuilding::getSize() { return size; }
int BaseBuilding::getSizeSqr() { return size*size; }
int BaseBuilding::getSight() { return sight; }

BaseBuilding::~BaseBuilding() { }

bool BaseBuilding::onScreen(int x1, int x2, int y1, int y2)
{
// 	return 
// 	( 
// 		(posx+sx >= x1) &&
// 		(posx+sx <= x2) &&
// 		(posy+sy >= y1) &&
// 		(posy+sy <= y2)
// 	);
}

void BaseBuilding::draw()
{
	SDL_Rect src = getFrame();
	SDL_Rect dest = src;
	dest.x = posx * 32;
	dest.y = posy * 32;
	SDL_BlitSurface(getImg(), &src, screen, &dest);
}

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

