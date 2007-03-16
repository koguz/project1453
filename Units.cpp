#include "Units.h"

// NOTE bu birimleri de ayırmak gerekecek sanki :(

Koylu::Koylu(SDL_Surface *scr, Player *p):BaseUnit(scr, p, "Köylü")
{
	cost = Cost(0, 400, 0); 
	addReq("Temel Teknoloji");
	faction = "Osmanlı";
	if (scr==0 && p==0) return;
	
	// temel bileşenler
	hitpoints = 20;
	buildRate = 1000; 
	armor = 2;
	damage = 10;
	range = 1;
	sight = 4;
	speed = 10;
	morale = 60;
	xp = 0;
	kills = 0;
	
	// grafiksel bileşenler
	hotspot.x = hotspot.y = 18;
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
	setState("dur");
	healthBar = new SDLProgressBar(32, 4, GREEN, 0, hitpoints);
	
	// alt ekran: komutlar
	komutlar = new SDLScreen(screen);
	SDL_Rect trect;
	trect.x = trect.y = 0;
	trect.w = trect.h = 44;
	
	Koylu *me = this;
	
	SDLCommandButton* yuru = new SDLCommandButton(screen, trect, "Yürü");
	yuru->setPosition(648,195);
	yuru->dugme->clicked = makeFunctor((CBFunctor0*)0, *me, &Koylu::setCommandYuru);
	komutlar->addWidget(yuru);
	
	trect.x = 44; trect.y = 0;
	SDLCommandButton* dur = new SDLCommandButton(screen, trect, "Dur");
	dur->setPosition(697,195);
	dur->dugme->clicked = makeFunctor((CBFunctor0*)0, *me, &Koylu::actionDur);
	komutlar->addWidget(dur);
	
	trect.x = 88; trect.y = 0;
	SDLCommandButton* ev = new SDLCommandButton(screen, trect, "Ev Yap", new Ev);
	ev->setPosition(746, 195);
	komutlar->addWidget(ev);
}

void Koylu::setCommandCalis()
{
	setState("calis");
}

Azab::Azab(SDL_Surface *scr, Player *p):BaseUnit(scr, p, "Azab")
{
	addReq("Asker Ocağı");
	faction = "Osmanlı";
	cost = Cost(0, 600, 0);
	if (scr == 0 && p == 0) return;
	
	
	hitpoints = 30;
	armor = 3;
	damage = 20;
	range = 1;
	sight = 4;
	speed = 15;
	morale = 50;
	xp = 0;
	kills = 0;
}


Piyade::Piyade(SDL_Surface *scr, Player *p):BaseUnit(scr, p, "Piyade")
{
	addReq("Asker Ocağı");
	addReq("Demirci");
	faction = "Osmanlı";
	cost = Cost(200, 600, 0);
	if (scr == 0 && p == 0) return;
	
	
	hitpoints = 40;
	armor = 5;
	damage = 30;
	range = 1;
	sight = 4;
	speed = 15;
	morale = 70;
	xp = 10;
	kills = 0;
}

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


