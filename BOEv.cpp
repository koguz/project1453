#include "BOEv.h"

SDL_Surface* Ev::spriteImg = 0;

Ev::Ev(SDL_Surface *scr, Player *p):BaseBuilding(scr, p, "Ev")
{
	cost = Cost(200, 0, 200); 
	addReq("Temel Teknoloji");
	faction = "Osmanlı";
	if (scr==0 && p==0) return;
	
	hitpoints = 400;
	buildRate = 50;
	sight = 4;
	size = 2;
	
	hotspot.x = hotspot.y = 0;
	hotspot.w = hotspot.h = 64;
	
	if (spriteImg == 0)
	{
		spriteImg = loadImg("graphics/buildings/osmanli/ev.png");
	}
	
	sprite = Sprite(spriteImg);
	sprite.addState("saglam");
	
	SDL_Rect t;
	t.x = t.y = 0;
	t.w = spriteImg->w;
	t.h = spriteImg->h;
	
	sprite.addFrameToState("saglam", t, 1000);
	
	setState("saglam");
	
// 	setResim("graphics/buildings/osmanli/ev.png");
}

