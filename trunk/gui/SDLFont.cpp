#include "SDLFont.h"

SDLFont::SDLFont(string str, int size, SDL_Color color)
{
	if (!TTF_WasInit() && TTF_Init() == -1)
	{
		cout << "err at sdl_ttf init" << endl;
		return;
	}
	TTF_Font *font;
	/// Font used here is a constant value: font.ttf
	font = TTF_OpenFont("font.ttf", size);
	if (!font)
	{
		cout << "err at loading font" << endl;
		return;
	}
	
	TTF_SetFontStyle(font, TTF_STYLE_NORMAL);
	if (TTF_SizeUTF8(font, str.c_str(), &w, &h))
	{
		cout << "err at size" << endl;
		return;
	}
	if (!(s=TTF_RenderUTF8_Blended(font, str.c_str(), color)))
	{
		cout << "err at render" << endl;
		return;
	}
}

void SDLFont::drawMe(SDL_Surface* screen, int x, int y)
{
	SDL_Rect dest;
	dest.x = x;
	dest.y = y;
	dest.w = s->w;
	dest.h = s->w;
	SDL_BlitSurface(s, NULL, screen, &dest);
}
