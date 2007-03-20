#include "UBSerf.h"

Serf::Serf()
{
	addReq("Temel Teknoloji");
	faction = "Bizans";
	cost.set(0, 300, 0);
}

Serf::Serf(SDL_Surface *scr, Player *p):BaseUnit(scr, p, "Serf")
{
	addReq("Temel Teknoloji");
	faction = "Bizans";
	cost.set(0, 300, 0);
	
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

Serf::~Serf()
{
	
}
