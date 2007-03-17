#include "SDLFont.h"

TTF_Font* SDLFont::font = 0;

SDLFont::SDLFont(string str, int size, SDL_Color color)
{
	if (!TTF_WasInit() && TTF_Init() == -1)
	{
		cout << "Yazı karakteri sistemi başlatılamadı" << endl;
		return;
	}
	
	if (font == 0)
		font = TTF_OpenFont("font.ttf", 14);
	
	if (!font)
	{
		cout << "Yazı karakteri yüklenemedi" << endl;
		return;
	}
	
	TTF_SetFontStyle(font, TTF_STYLE_NORMAL);
	if (TTF_SizeUTF8(font, str.c_str(), &w, &h))
	{
		cout << "Yazı karakterine boyut verilemedi" << endl;
		return;
	}
	if (!(s=TTF_RenderUTF8_Blended(font, str.c_str(), color)))
	{
		cout << "Yazı karakteri görüntülenemedi" << endl;
		return;
	}
}

SDLFont::~SDLFont()
{
// 	SDL_FreeSurface(s);
}

int SDLFont::getWidth() { return w; }
int SDLFont::getHeight() { return h; }
SDL_Surface* SDLFont::getString() { return s; }

void SDLFont::drawMe(SDL_Surface* screen, int x, int y)
{
	SDL_Rect dest;
	dest.x = x;
	dest.y = y;
	dest.w = s->w;
	dest.h = s->w;
	SDL_BlitSurface(s, NULL, screen, &dest);
}
