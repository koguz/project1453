#include "BaseGraphicObject.h"

BaseGraphicObject::BaseGraphicObject()
{
	komutlar = 0;
	komutTanim = 0;
	healthBar = 0;
	wx = wy = 0;
}

BaseGraphicObject::BaseGraphicObject(SDL_Surface *scr, Player *p)
{
	parent = p;
	screen = scr;
	komutlar = 0;
	komutTanim = 0;
	selected = false;
	healthBar = 0;
	wx = wy = 0;
}

BaseGraphicObject::~BaseGraphicObject()
{
	delete komutlar;
	delete komutTanim;
	delete healthBar;
}

int BaseGraphicObject::getX() { return wx; }
int BaseGraphicObject::getY()  { return wy; }
int BaseGraphicObject::getTx() { return posx; }
int BaseGraphicObject::getTy()  { return posy; }
void BaseGraphicObject::select() { selected = true; }
void BaseGraphicObject::unselect() { selected = false; }
bool BaseGraphicObject::isSelected() { return selected; }
SDLScreen* BaseGraphicObject::getScreen() { return komutlar; } 

void BaseGraphicObject::setPosition(int x, int y)
{
	wx = x;
	wy = y;
}

void BaseGraphicObject::setTilePos(int x, int y)
{
	posx = x;
	posy = y;
	setPosition(x*32, y*32);
}

Coordinates BaseGraphicObject::getCenter()
{
	// bu fonksiyona değinmek gerekecek
	Coordinates t;
	t.x = posx + cx;
	t.y = posy + cy;
	return t;
}

Coordinates BaseGraphicObject::getPosition()
{
	Coordinates t;
	t.x = posx;
	t.y = posy;
	return t;
}

bool BaseGraphicObject::isMouseOver(int mx, int my)
{
	int ux1 = getX();
	int ux2 = ux1 + 32;
	int uy1 = getY();
	int uy2 = uy1 + 32;
	if (
		(mx > ux1) &&
		(mx < ux2) &&
		(my > uy1) &&
		(my < uy2)
	)
		return true;
	else return false;
}

SDL_Surface* BaseGraphicObject::loadImg(char* f)
{
	SDL_Surface *t = IMG_Load(f);
	SDL_SetAlpha(t, SDL_SRCALPHA | SDL_RLEACCEL, SDL_ALPHA_OPAQUE);
// 	SDL_Surface *toRet = SDL_DisplayFormatAlpha(t);
// 	SDL_FreeSurface(t);
// 	return toRet;
	return t;
}

void BaseGraphicObject::drawSubScreen()
{
	if (komutlar!=0)
		komutlar->display();
}
