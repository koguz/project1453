#include "BaseGraphicObject.h"

BaseGraphicObject::BaseGraphicObject()
{
	komutlar = 0;
	komutTanim = 0;
	healthBar = 0;
}

BaseGraphicObject::BaseGraphicObject(SDL_Surface *scr, Player *p)
{
	parent = p;
	screen = scr;
	komutlar = 0;
	komutTanim = 0;
	selected = false;
	healthBar = 0;
}

BaseGraphicObject::~BaseGraphicObject()
{
	delete komutlar;
	delete komutTanim;
	delete healthBar;
}

int BaseGraphicObject::getX() { return posx; }
int BaseGraphicObject::getY()  { return posy; }
void BaseGraphicObject::select() { selected = true; }
void BaseGraphicObject::unselect() { selected = false; }
bool BaseGraphicObject::isSelected() { return selected; }
SDLScreen* BaseGraphicObject::getScreen() { return komutlar; } 

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
	int ux1 = getX() + hotspot.x;
	int ux2 = ux1 + hotspot.w;
	int uy1 = getY() + hotspot.y;
	int uy2 = uy1 + hotspot.h;
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
	SDL_Surface *toRet = SDL_DisplayFormatAlpha(t);
	SDL_FreeSurface(t);
	return toRet;
}

void BaseGraphicObject::draw()
{
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
// 		if (komutlar != 0)
// 			komutlar->display();
	}
}

void BaseGraphicObject::drawSubScreen()
{
	if (komutlar!=0)
		komutlar->display();
}
