#include "BOEv.h"

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
	
	setResim("graphics/buildings/osmanli/ev.png");
}

