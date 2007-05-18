#include "BOEv.h"

SDL_Surface* Ev::spriteImg = 0;

Ev::Ev()
{
	cost.set(200, 0, 200); 
	addReq("Temel Teknoloji");
	faction = "Osmanlı";
}

Ev::Ev(SDL_Surface *scr, Player *p):BaseBuilding(scr, p, "Ev")
{
	cost.set(200, 0, 200); 
	addReq("Temel Teknoloji");
	faction = "Osmanlı";
	
	hitpoints = 400;
	buildRate = 50;
	sight = 4;
	size = 2;
	
	hotspot.x = hotspot.y = 0;
	hotspot.w = hotspot.h = 64;
	cx = cy = 32;
	
	if (spriteImg == 0)
	{
		spriteImg = loadImg("graphics/buildings/osmanli/ev.png");
	}
	
	sprite = Sprite(spriteImg);
	sprite.addState("saglam");
	sprite.addState("insaa");
	
	SDL_Rect t;
	t.x = t.y = 0;
	t.w = spriteImg->w;
	t.h = spriteImg->h/2;

	sprite.addFrameToState("saglam", t, 1000);
	t.y = 64;
	sprite.addFrameToState("insaa", t, 1000);
	
	setState("insaa");
	sbar = new SDLProgressBar(90, 14, GREEN, 0, hitpoints);
	sbar->setPosition(695, 223);
	komutlar->addWidget(sbar);
	selected = false;
	curState = "insaa";
	
	SDL_Rect trect;
	trect.x = 64; trect.y = 32;
	trect.w = trect.h = 32;
	
	resim = new SDLCommandButton(screen, trect, name);
	resim->setPosition(655, 205);
	komutlar->addWidget(resim);
	
// 	healthBar = new SDLProgressBar(128, 4, GREEN, 0, hitpoints);
}


Ev::~Ev()
{
	
}
