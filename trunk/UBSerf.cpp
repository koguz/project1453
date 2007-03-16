#include "UBSerf.h"

Serf::Serf(SDL_Surface *scr, Player *p):BaseUnit(scr, p, "Serf")
{
	addReq("Temel Teknoloji");
	faction = "Bizans";
	cost = Cost(0, 300, 0);
	if (scr == 0 && p == 0) return;
	
	
	hitpoints = 20;
	buildRate = 1000;
	armor = 2;
	damage = 10;
	range = 1;
	sight = 3;
	speed = 10;
	morale = 40;
	xp = 0;
	kills = 0;
}

