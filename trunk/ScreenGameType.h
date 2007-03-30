#ifndef SCREENGAMETYPE__H__
#define SCREENGAMETYPE__H__

#include "SDLScreen.h"
#include "SDLWidget.h"
#include "SDLCombo.h"
#include "SDLListView.h"
#include "SDLLabel.h"
#include "SDLButton.h"
#include "SDLTextView.h"

class ScreenGameType:public SDLScreen
{
	public:
	SDLWidget *arka, *imgYeniceri;
	SDLCombo *ulke, *rakipTip;
	SDLListView *haritalar;
	SDLLabel *title, *lblUlke, *lblRakip, *lblHarita, *lblAciklama, *err;
	SDLButton *anaEkranaDon, *baslat;
	SDLTextView *aciklama;
	
	ScreenGameType(SDL_Surface* screen);
};


#endif
