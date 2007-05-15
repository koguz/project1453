#include "ScreenCredits.h"

ScreenCredits::ScreenCredits(SDL_Surface *screen):SDLScreen(screen)
{
	arka = new SDLWidget("ui/emek.jpg");
	arka->setPosition(0, 0);
	addWidget(arka);
	
	anaEkranaDon = new SDLButton("ui/button.png", "Ana Menü");
	anaEkranaDon->setPosition(470, 485);
	addWidget(anaEkranaDon);
}

