#ifndef SCREENGAMETYPE__H__
#define SCREENGAMETYPE__H__

#include "SDLScreen.h"

class ScreenGameType:public SDLScreen
{
	public:
	SDLWidget *arka, *imgYeniceri;
	SDLCombo *ulke, *rakipTip;
	SDLListView *haritalar;
	SDLLabel *title, *lblUlke, *lblRakip, *lblHarita, *err;
	SDLButton *anaEkranaDon, *baslat;
	
	ScreenGameType(SDL_Surface* screen);
};


#endif
