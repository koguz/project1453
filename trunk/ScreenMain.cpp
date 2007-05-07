#include "ScreenMain.h"

ScreenMain::ScreenMain(SDL_Surface *screen):SDLScreen(screen)
{
	arka = new SDLWidget("ui/ana_sayfa3.jpg");
	arka->setPosition(0, 0);
	addWidget(arka);
	
	single = new SDLButton("ui/button.png", "Yeni Oyun");
	single->setPosition(470, 335);
	addWidget(single);
	
	ayarlar = new SDLButton("ui/button.png", "Ayarlar");
	ayarlar->setPosition(470, 385);
	addWidget(ayarlar);
	
	credits = new SDLButton("ui/button.png", "Emeği Geçenler");
	credits->setPosition(470, 435);
	addWidget(credits);
		
	cikis = new SDLButton("ui/button.png", "Oyunu Kapat");
	cikis->setPosition(470, 485);
	addWidget(cikis);
}

ScreenMain::~ScreenMain()
{
	
}
