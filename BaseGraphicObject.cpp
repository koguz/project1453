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
	// buna da değinmek gerekecek
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
// 	SDL_Surface *toRet = SDL_DisplayFormatAlpha(t);
// 	SDL_FreeSurface(t);
// 	return toRet;
	return t;
}

bool BaseGraphicObject::onScreen(int x1, int x2, int y1, int y2)
{
	return 
	( 
		(posx >= x1) &&
		(posx <= x2) &&
		(posy >= y1) &&
		(posy <= y2)
	);
}

void BaseGraphicObject::draw(SDL_Rect s, SDL_Rect d)
{
	SDL_Rect src = getFrame();
	src.x += s.x + hotspot.x;
	src.y += s.y + hotspot.y;
	src.w = s.w;
	src.h = s.h;
	
	SDL_BlitSurface(getImg(), &src, screen, &d);
	if (isSelected())
	{
		// TODO -- sonra düşünüces bunu
		SDL_Rect m = d;
// 		if (m.w != 32 || m.h != 32)
// 		{
// 			m.x = m.x - (32 - m.w);
// 			m.y = m.y - (32 - m.h);
// 			m.w = m.h = 32;
// 		}
		int ux1 = m.x; 
		int ux2 = ux1 + 4;
		int ux3 = m.x + m.w - 4; 
		int ux4 = ux3 + 4;
		int uy1 = m.y; 
		int uy2 = uy1 + 4;
		int uy3 = m.y + m.h - 4; 
		int uy4 = uy3 + 4;
		
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

void BaseGraphicObject::drawSubScreen()
{
	if (komutlar!=0)
		komutlar->display();
}
