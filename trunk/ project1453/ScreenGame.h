#ifndef SCREENGAME__H__
#define SCREENGAME__H__

#include "SDLScreen.h"

class ScreenGame:public SDLScreen
{
	public:
	ScreenGame(SDL_Surface* screen);
	
	// NOTE bu aşağıdaki SDLWidgetlar olmayacak gibi
	// ooo burada bissürü sey olacak.
	SDLWidget *arka, *woodIcon, *foodIcon, *stoneIcon;
	
	// TODO burada en önemlisi bir ana menü
};


#endif
