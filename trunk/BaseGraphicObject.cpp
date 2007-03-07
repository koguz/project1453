#include "BaseGraphicObject.h"

BaseGraphicObject::BaseGraphicObject(SDL_Surface *scr)
{
	screen = scr;
	komutlar = 0;
}


void BaseGraphicObject::setPosition(int x, int y)
{
	posx = x;
	posy = y;
}


Coordinates BaseGraphicObject::getCenter()
{
	Coordinates t;
	t.x = posx + cx;
	t.y = posy + cy;
	return t;
}

