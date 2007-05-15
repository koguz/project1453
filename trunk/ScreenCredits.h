#ifndef SCREENCREDITS__H__
#define SCREENCREDITS__H__

#include "SDLScreen.h"
#include "SDLWidget.h"
#include "SDLButton.h"


class ScreenCredits:public SDLScreen
{
	public:
	SDLWidget *arka;
	SDLButton *anaEkranaDon;
	
	ScreenCredits(SDL_Surface* screen);
};


#endif
