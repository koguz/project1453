#ifndef SCREENMAIN___H_
#define SCREENMAIN___H_

#include "SDLScreen.h"
#include "SDLWidget.h"
#include "SDLButton.h"

class ScreenMain:public SDLScreen
{
	public:
	SDLWidget *arka;
	SDLButton *oyun, *ayarlar, *credits, *cikis, *single;
	ScreenMain(SDL_Surface* screen);
	~ScreenMain();
};



#endif
