#include "BOSehirMerkezi.h"

SDL_Surface* SehirMerkezi::spriteImg = 0;

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
	
	hotspot.x = hotspot.y = 0;
	hotspot.w = hotspot.h = 128;
	
	if (spriteImg == 0)
	{
		spriteImg = loadImg("graphics/buildings/osmanli/sehirMerkezi1.png");
	}
	
	sprite = Sprite(spriteImg);
	sprite.addState("saglam");
	
	SDL_Rect t;
	t.x = t.y = 0;
	t.w = spriteImg->w;
	t.h = spriteImg->h;
	
	sprite.addFrameToState("saglam", t, 1000);
	
	setState("saglam");
	
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

SehirMerkezi::~SehirMerkezi()
{
	delete btnKoylu;
}

void SehirMerkezi::createKoylu()
{
	if (nowBuilding != 0)
	{
		cerr << "Şu an başka bir birim üretiliyor, daha sonra tekrar deneyin!" << endl;
		return;
	}
	
	Koylu* yeni = parent->yeniKoylu();
	if (yeni == 0)
		return;
	
	yeni->setPosition(200, 200);
	
	nowBuilding = (BaseObject*) yeni;
	nowBuildingBar->setMax(yeni->getMaxHp());
	nowBuildingBar->setShow(true);
}

