#ifndef SDLFONT__H
#define SDLFONT__H

#include <iostream>
#include <string>
#include "Headers.h"

using namespace std;

class SDLFont
{
	public:
	SDLFont(string str, int size, SDL_Color color);
	SDL_Surface* getString() { return s; }
	int getWidth() { return w; }
	int getHeight() { return h; }
	void drawMe(SDL_Surface* screen, int x, int y);
	
	private:
	int w;
	int h;
	SDL_Surface *s;
};


#endif

