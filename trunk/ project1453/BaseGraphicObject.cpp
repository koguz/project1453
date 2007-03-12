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

bool BaseGraphicObject::isMouseOver(int mx, int my)
{
	return true;
// 	if (
// 		(mx > px1) &&
// 		(mx < px2) &&
// 		(my > py1) &&
// 		(my < py2)
// 		)
// 		return true;
// 	else return false;
}

