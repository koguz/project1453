#include "ScreenMain.h"

ScreenMain::ScreenMain(SDL_Surface *screen):SDLScreen(screen)
{
	arka = new SDLWidget("ui/1453.jpg");
	arka->setPosition(0, 0);
	addWidget(arka);
	
	oyun = new SDLButton("ui/dugme.jpg", "Yeni Oyun");
	oyun->setPosition(458, 400);
	addWidget(oyun);
	
	single = new SDLButton("ui/dugme.jpg", "Tek Görev");
	single->setPosition(458, 440);
	addWidget(single);
	
	ayarlar = new SDLButton("ui/dugme.jpg", "Ayarlar");
	ayarlar->setPosition(458, 480);
	addWidget(ayarlar);
	
	credits = new SDLButton("ui/dugme.jpg", "Emeği Geçenler");
	credits->setPosition(458, 520);
	addWidget(credits);
		
	cikis = new SDLButton("ui/dugme.jpg", "Oyunu Kapat");
	cikis->setPosition(458, 560);
	addWidget(cikis);
}

ScreenMain::~ScreenMain()
{
	
}
