#include "Buildings.h"

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

SehirMerkezi::SehirMerkezi(SDL_Surface *scr, Player *p):BaseBuilding(scr, p,"Şehir Merkezi (I)")
{
	cost = Cost(400, 0, 400); 
	addReq("Temel Teknoloji");
	faction = "Osmanlı";
	
	if (scr == 0 && p == 0) return;
	
	state = 1;
	hitpoints = 1000;
	sight = 8;
	size = 4;
	
	// BaseObject* nowBuilding;
	setResim("graphics/buildings/osmanli/sehirMerkezi1.png");
	healthBar = new SDLProgressBar(128, 4, GREEN, 0, hitpoints);
	
	komutlar = new SDLScreen(screen);
	SDL_Rect trect;
	trect.x = 176; trect.y = 0;
	trect.w = trect.h = 44;
	
	SehirMerkezi *me = this;
	
	nowBuildingBar = new SDLProgressBar(144, 10, GREEN, 0, 1);
	nowBuildingBar->setPosition(648, 245);
	nowBuildingBar->setShow(false);
	komutlar->addWidget(nowBuildingBar);
	
	btnKoylu = new SDLCommandButton(screen, trect, "Yeni Köylü", new Koylu());
	btnKoylu->setPosition(648, 195);
	btnKoylu->dugme->clicked = makeFunctor((CBFunctor0*)0, *me, &SehirMerkezi::createKoylu);
	komutlar->addWidget(btnKoylu);
}

void SehirMerkezi::createKoylu()
{
	Koylu* yeni = parent->yeniKoylu();
	if (yeni == 0)
		return;
	
	yeni->setPosition(200, 200);
	
	nowBuilding = (BaseObject*) yeni;
	nowBuildingBar->setMax(yeni->getMaxHp());
	nowBuildingBar->setShow(true);
}

AskerOcagi::AskerOcagi(SDL_Surface *scr, Player *p):BaseBuilding(scr, p, "Asker Ocağı")
{
	cost = Cost(200, 0, 400); 
	addReq("Temel Teknoloji");
	faction = "Osmanlı";
	if (p==0 && scr == 0) return;
	
	
	hitpoints = 800;
	sight= 6;
	size = 4;
}

Demirci::Demirci(SDL_Surface *scr, Player *p):BaseBuilding(scr, p, "Demirci")
{
	cost = Cost(0, 0, 500); 
	addReq("Temel Teknoloji");
	faction = "Osmanlı";
	if (scr==0, p==0) return;
	
	
	hitpoints = 600;
	sight = 4;
	size = 3;
}

