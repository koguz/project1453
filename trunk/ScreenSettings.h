#ifndef SCREENSETTINGS__H__
#define SCREENSETTINGS__H__

#include "SDLScreen.h"
#include "SDLWidget.h"
#include "SDLCombo.h"
#include "SDLLabel.h"
#include "SDLButton.h"
#include "SDLCheckBox.h"
#include "SDLMusic.h"

class ScreenSettings:public SDLScreen
{
	public:
	SDLWidget *arka, *imgYeniceri2, *optionPane;
	SDLLabel *baslik, *muzikvol;
	SDLCheckBox *monoff;
	SDLCombo *mvol;
	SDLButton *tamam, *iptal;
	void accept();
	void reset();
	
	ScreenSettings(SDL_Surface *screen);
};


#endif
