#include "BaseGraphicObject.h"

BaseGraphicObject::BaseGraphicObject()
{
}

BaseGraphicObject::BaseGraphicObject(SDL_Surface *scr, Player *p)
{
	parent = p;
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


void BaseGraphicObject::draw()
{
	// TODO - burada hala sabit sayılar var :( UNUTMA!
	SDL_Rect dest;
	dest.w = dest.h = getImg()->w;
	dest.x = posx;
	dest.y = posy;
	SDL_Rect src = getFrame();
	SDL_BlitSurface(getImg(), &src, screen, &dest);
	if (isSelected())
	{
		int ux1 = posx + hotspot.x;
		int ux2 = ux1 + 4;
		int ux3 = posx + hotspot.w + hotspot.x + - 4;
		int ux4 = ux3 + 4;
		int uy1 = posy + hotspot.y;
		int uy2 = uy1 + 4;
		int uy3 = posy + hotspot.h + hotspot.y - 4;
		int uy4 = uy3 + 4;
		lineColor(screen, ux1, uy1, ux2, uy1, 0x00FF00FF);
		lineColor(screen, ux3, uy1, ux4, uy1, 0x00FF00FF);
		lineColor(screen, ux1, uy4, ux2, uy4, 0x00FF00FF);
		lineColor(screen, ux3, uy4, ux4, uy4, 0x00FF00FF);
		lineColor(screen, ux1, uy1, ux1, uy2, 0x00FF00FF);
		lineColor(screen, ux1, uy3, ux1, uy4, 0x00FF00FF);
		lineColor(screen, ux4, uy1, ux4, uy2, 0x00FF00FF);
		lineColor(screen, ux4, uy3, ux4, uy4, 0x00FF00FF);
		
		// burası healthBar
		int hx = ux1;
		int hy = uy1 - 10;
		healthBar->setPosition(hx, hy);
		healthBar->drawWidget(screen);
		if (komutlar != 0)
			komutlar->display();
	}
}
