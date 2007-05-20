#include "BOAsker.h"

SDL_Surface* AskerOcagi::spriteImg = 0;

AskerOcagi::AskerOcagi()
{
	cost.set(700, 0, 400); 
	addReq("Temel Teknoloji");
	faction = "Osmanlı";
}

AskerOcagi::AskerOcagi(SDL_Surface *scr, Player *p):BaseBuilding(scr, p, "Asker Ocağı")
{
	cost.set(700, 0, 400); 
	addReq("Temel Teknoloji");
	faction = "Osmanlı";
	
	hitpoints = 800;
	buildRate = 50;
	sight = 5;
	size = 4;
	
	hotspot.x = hotspot.y = 0;
	hotspot.w = hotspot.h = 128;
	cx = cy = 64;
	
	if (spriteImg == 0)
	{
		spriteImg = loadImg("graphics/buildings/osmanli/asker.png");
	}
	
	sprite = Sprite(spriteImg);
	sprite.addState("saglam");
	sprite.addState("insaa");
	
	SDL_Rect t;
	t.x = t.y = 0;
	t.w = 128;
	t.h = 128;

	sprite.addFrameToState("saglam", t, 1000);
	
	t.y = 128;
	sprite.addFrameToState("insaa", t, 1000);
	
	setState("insaa");
	sbar = new SDLProgressBar(90, 14, GREEN, 0, hitpoints);
	sbar->setPosition(695, 223);
	komutlar->addWidget(sbar);
	selected = false;
	curState = "insaa";
	
	SDL_Rect trect;
	trect.x = 0; trect.y = 32;
	trect.w = trect.h = 32;
	
	resim = new SDLCommandButton(screen, trect, name);
	resim->setPosition(655, 205);
	komutlar->addWidget(resim);
	
// 	healthBar = new SDLProgressBar(128, 4, GREEN, 0, hitpoints);
}


AskerOcagi::~AskerOcagi()
{
	
}
