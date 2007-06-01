#ifndef SCREENGAME__H__
#define SCREENGAME__H__

#include "SDLScreen.h"

class ScreenGame:public SDLScreen
{
	public:
	ScreenGame(SDL_Surface* screen);
	
	// NOTE bu aşağıdaki SDLWidgetlar olmayacak gibi
	SDLWidget *arka, *woodIcon, *foodIcon, *stoneIcon;
};


#endif
