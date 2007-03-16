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
	SDL_Surface* getString();
	
	int getWidth();
	int getHeight();
	
	void drawMe(SDL_Surface* screen, int x, int y);
	
	static TTF_Font* font;
	
	private:
	int w; 
	int h;
	SDL_Surface *s;
	
};


#endif

