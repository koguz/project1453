#include "Units.h"

Koylu::Koylu(SDL_Surface *scr):BaseUnit(scr, "Köylü")
{
	hitpoints = 20;
	buildRate = 1000; // 1 saniyede 1 HP
	armor = 2;
	damage = 10;
	range = 1;
	sight = 4;
	speed = 10;
	morale = 60;
	xp = 0;
	kills = 0;
	addReq("Temel Teknoloji");
	faction = "Osmanlı";
	cost = Cost(0, 400, 0);
	
	
	hotspot.x = hotspot.y = 20;
	hotspot.w = hotspot.h = 32;
	cx = cy = 32; 
	
	selected = false;
	
	SDL_Rect t;
	t.w = t.h = 64;
	
	Sprite t2("graphics/units/osmanli/koylu.png");
	
	for(int i=0;i<8;i++)
	{
		sprites[i] = t2;
		sprites[i].addState("dur");
		sprites[i].addState("yuru");
		
		t.x = i*64;
		t.y = 0;
		sprites[i].addFrameToState("dur", t, 1000);
		
		for (int j=0;j<2;j++)
		{
			t.x = i*64;
			t.y = 64 + (j*64);
			sprites[i].addFrameToState("yuru", t, 100);
		}		
	}
	yon = N;
	komutlar = new SDLScreen(screen);
	setState("dur");
	
	healthBar = new SDLProgressBar(28, 4, GREEN, 0, hitpoints);
}

void Koylu::setCommandCalis()
{
	setState("calis");
}

Azab::Azab(SDL_Surface *scr):BaseUnit(scr, "Azab")
{
	hitpoints = 30;
	armor = 3;
	damage = 20;
	range = 1;
	sight = 4;
	speed = 15;
	morale = 50;
	xp = 0;
	kills = 0;
	addReq("Asker Ocağı");
	faction = "Osmanlı";
	cost = Cost(0, 600, 0);
}


Piyade::Piyade(SDL_Surface *scr):BaseUnit(scr, "Piyade")
{
	hitpoints = 40;
	armor = 5;
	damage = 30;
	range = 1;
	sight = 4;
	speed = 15;
	morale = 70;
	xp = 10;
	kills = 0;
	addReq("Asker Ocağı");
	addReq("Demirci");
	faction = "Osmanlı";
	cost = Cost(200, 600, 0);
}

Serf::Serf(SDL_Surface *scr):BaseUnit(scr, "Serf")
{
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
	addReq("Temel Teknoloji");
	faction = "Bizans";
	cost = Cost(0, 300, 0);
}


