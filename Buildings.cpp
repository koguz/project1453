#include "Buildings.h"

Ev::Ev(SDL_Surface *scr):BaseBuilding(scr, "Ev")
{
	hitpoints = 400;
	buildRate = 50;
	sight = 4;
	size = 2;
	addReq("Temel Teknoloji");
	faction = "Osmanlı";
	cost = Cost(200, 0, 200);
		
	// 
	setResim("graphics/buildings/osmanli/ev.png");
	healthBar = new SDLProgressBar(64, 4, GREEN, 0, hitpoints);
	
	komutlar = new SDLScreen(screen);
	SDL_Rect trect;
	trect.x = 44; trect.y = 0;
	trect.w = trect.h = 44;
	
	SDLCommandButton* dur = new SDLCommandButton(screen, trect, "Dur");
	dur->setPosition(648, 195);
	dur->dugme->clicked = 0;
	komutlar->addWidget(dur);
}

SehirMerkezi::SehirMerkezi(SDL_Surface *scr):BaseBuilding(scr, "Şehir Merkezi (I)")
{
	state = 1;
	hitpoints = 1000;
	sight = 8;
	size = 4;
	addReq("Temel Teknoloji");
	faction = "Osmanlı";
	cost = Cost(400, 0, 400);
	
	// 
	setResim("graphics/buildings/osmanli/sehirMerkezi1.png");
	healthBar = new SDLProgressBar(128, 4, GREEN, 0, hitpoints);
	
	komutlar = new SDLScreen(screen);
	SDL_Rect trect;
	trect.x = 176; trect.y = 0;
	trect.w = trect.h = 44;
	
	createKoylu = new SDLCommandButton(screen, trect, "Yeni Köylü", new Koylu(screen));
	createKoylu->setPosition(648, 195);
	// createKoylu->dugme->clicked = 0;
	komutlar->addWidget(createKoylu);
}

AskerOcagi::AskerOcagi(SDL_Surface *scr):BaseBuilding(scr, "Asker Ocağı")
{
	hitpoints = 800;
	sight= 6;
	size = 4;
	addReq("Temel Teknoloji");
	faction = "Osmanlı";
	cost = Cost(200, 0, 400);
}

Demirci::Demirci(SDL_Surface *scr):BaseBuilding(scr, "Demirci")
{
	hitpoints = 600;
	sight = 4;
	size = 3;
	addReq("Temel Teknoloji");
	faction = "Osmanlı";
	cost = Cost(0, 0, 500);
}

