#include "BOSehirMerkezi.h"

SDL_Surface* SehirMerkezi::spriteImg = 0;

SehirMerkezi::SehirMerkezi()
{
	cost.set(800, 0, 800); 
	addReq("Temel Teknoloji");
	faction = "Osmanlı";
	btnKoylu = resim = 0;
}

SehirMerkezi::SehirMerkezi(SDL_Surface *scr, Player *p):BaseBuilding(scr, p,"Şehir Merkezi")
{
	cost.set(800, 0, 800); 
	addReq("Temel Teknoloji");
	faction = "Osmanlı";
	
	state = 1;
	hitpoints = 1200;
	currentHp = 1;
	sight = 4;
	size = 4;
	
	hotspot.x = hotspot.y = 0;
	hotspot.w = hotspot.h = 128;
	cx = cy = 64;
	
	if (spriteImg == 0)
	{
		spriteImg = loadImg("graphics/buildings/osmanli/merkez.png");
	}
	
	sprite = Sprite(spriteImg);
	sprite.addState("saglam");
	sprite.addState("insaa");
	
	SDL_Rect t;
	t.x = t.y = 0;
	t.w = 128;
	t.h = 128;
	
	sprite.addFrameToState("saglam", t, 1000);
	
	t.x = 0;
	t.y = 128;
	sprite.addFrameToState("insaa", t, 1000);
	
	setState("insaa");
	
	SDL_Rect trect;
	trect.x = 96; trect.y = 0;
	trect.w = trect.h = 32;
	
	SehirMerkezi *me = this;
	
	nowBuildingBar = new SDLProgressBar(130, 10, GREEN, 0, 1);
	nowBuildingBar->setPosition(655, 250);
	nowBuildingBar->setShow(false);
	komutlar->addWidget(nowBuildingBar);
	
	btnKoylu = new SDLCommandButton(screen, trect, "Yeni Köylü", Koylu().getCost());
	btnKoylu->setPosition(665, 270);
	btnKoylu->dugme->clicked = makeFunctor((CBFunctor0*)0, *me, &SehirMerkezi::createKoylu);
	komutlar->addWidget(btnKoylu);
	
	
	trect.x = 128; trect.y = 32;
	resim = new SDLCommandButton(screen, trect, name);
	resim->setPosition(655, 205);
	komutlar->addWidget(resim);
	
	sbar = new SDLProgressBar(90, 14, GREEN, 0, hitpoints);
	sbar->setPosition(695, 223);
	komutlar->addWidget(sbar);
	selected = false;
	curState = "insaa";
}

SehirMerkezi::~SehirMerkezi()
{
}

void SehirMerkezi::createKoylu()
{
	if (curState == "insaa")
	{
		parent->addMessage("Bina henüz inşaa edilmedi!");
		return;
	}
	if (nowBuilding != 0)
	{
		parent->addMessage("Şu an başka bir birim üretiliyor!");
		return;
	}
	
	if (!parent->yeniKoylu())
		return;
	
	Koylu *ykoylu = new Koylu(screen, parent);
	ykoylu->setTilePos(posx+2, posy+4);
	
	nowBuilding = (BaseObject*) ykoylu;
	nowBuildingBar->setMax(ykoylu->getMaxHp());
	nowBuildingBar->setShow(true);
}

