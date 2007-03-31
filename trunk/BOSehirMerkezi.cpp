#include "BOSehirMerkezi.h"

SDL_Surface* SehirMerkezi::spriteImg = 0;

SehirMerkezi::SehirMerkezi()
{
	cost.set(400, 0, 400); 
	addReq("Temel Teknoloji");
	faction = "Osmanlı";
}

SehirMerkezi::SehirMerkezi(SDL_Surface *scr, Player *p):BaseBuilding(scr, p,"Şehir Merkezi (I)")
{
	cost.set(400, 0, 400); 
	addReq("Temel Teknoloji");
	faction = "Osmanlı";
	
	state = 1;
	hitpoints = 1000;
	sight = 8;
	size = 4;
	
	hotspot.x = hotspot.y = 0;
	hotspot.w = hotspot.h = 128;
	cx = cy = 64;
	
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
	trect.x = 128; trect.y = 0;
	trect.w = trect.h = 32;
	
	SehirMerkezi *me = this;
	
	nowBuildingBar = new SDLProgressBar(120, 10, GREEN, 0, 1);
	nowBuildingBar->setPosition(655, 245);
	nowBuildingBar->setShow(false);
	komutlar->addWidget(nowBuildingBar);
	
	btnKoylu = new SDLCommandButton(screen, trect, "Yeni Köylü", Koylu().getCost());
	btnKoylu->setPosition(655, 205);
	btnKoylu->dugme->clicked = makeFunctor((CBFunctor0*)0, *me, &SehirMerkezi::createKoylu);
	komutlar->addWidget(btnKoylu);
}

SehirMerkezi::~SehirMerkezi()
{
// 	delete btnKoylu;
}

void SehirMerkezi::createKoylu()
{
	if (nowBuilding != 0)
	{
		parent->addMessage("Şu an başka bir birim üretiliyor!");
		return;
	}
	
	if (!parent->yeniKoylu())
		return;
	
	Koylu *ykoylu = new Koylu(screen, parent);
	ykoylu->setPosition(200, 200);
	
	nowBuilding = (BaseObject*) ykoylu;
	nowBuildingBar->setMax(ykoylu->getMaxHp());
	nowBuildingBar->setShow(true);
}

