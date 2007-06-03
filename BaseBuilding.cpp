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
	birimTamam = new SDLMixer("wavs/ui/birimTamam.ogg");
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
string BaseBuilding::getState() { return curState; }
int BaseBuilding::getSize() { return size; }
int BaseBuilding::getSizeSqr() { return size*size; }
int BaseBuilding::getSight() { return sight; }

BaseBuilding::~BaseBuilding() { /*delete birimTamam;*/ }

bool BaseBuilding::onScreen(int x1, int x2, int y1, int y2)
{
	int px1 = posx * 32;
	int py1 = posy * 32;
	int px2 = px1 + (size*32);
	int py2 = py1 + (size*32);
	
	return
	(
		(
			((px1 >= x1) && (px1 < x2)) ||
			((px2 >= x1) && (px2 < x2)) 
		) && 
		(
			((py1 >= y1) && (py1 < y2)) ||
			((py2 >= y1) && (py2 < y2)) 
		)
	);
}

void BaseBuilding::draw(SDL_Rect s,SDL_Rect d)
{
	SDL_Rect src = getFrame();
	src.x += s.x + hotspot.x;
	src.y += s.y + hotspot.y;
	src.w = s.w;
	src.h = s.h;
	SDL_BlitSurface(getImg(), &src, screen, &d);
	if (isSelected())
	{
		SDL_Rect m = d;
		int ux1 = m.x; 
		int ux2 = ux1 + 8;
		int ux3 = m.x + m.w - 8; 
		int ux4 = ux3 + 8;
		int uy1 = m.y; 
		int uy2 = uy1 + 8;
		int uy3 = m.y + m.h - 8; 
		int uy4 = uy3 + 8;
		
		lineColor(screen, ux1, uy1, ux2, uy1, 0x00FF00FF);
		lineColor(screen, ux3, uy1, ux4, uy1, 0x00FF00FF);
		lineColor(screen, ux1, uy4, ux2, uy4, 0x00FF00FF);
		lineColor(screen, ux3, uy4, ux4, uy4, 0x00FF00FF);
		lineColor(screen, ux1, uy1, ux1, uy2, 0x00FF00FF);
		lineColor(screen, ux1, uy3, ux1, uy4, 0x00FF00FF);
		lineColor(screen, ux4, uy1, ux4, uy2, 0x00FF00FF);
		lineColor(screen, ux4, uy3, ux4, uy4, 0x00FF00FF);
	}
}

void BaseBuilding::update() 
{
	if (selected)
	{ sbar->setValue(currentHp); }
	
	if (nowBuilding != 0)
	{
		if (nowBuilding->build())
		{
			switch(nowBuilding->getType())
			{
				case BaseObject::UNIT:
					birimTamam->play();
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
			nowBuilding = 0;
			nowBuildingBar->setShow(false);
		}
		else
		{
			nowBuildingBar->setValue(nowBuilding->getCurHp());
		}
	}
}

