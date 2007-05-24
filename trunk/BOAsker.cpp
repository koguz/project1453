#include "BOAsker.h"

SDL_Surface* AskerOcagi::spriteImg = 0;

AskerOcagi::AskerOcagi()
{
	cost.set(700, 0, 400); 
	addReq("Temel Teknoloji");
	faction = "Osmanlı";
}

AskerOcagi::AskerOcagi(SDL_Surface *scr, Player *p):BaseBuilding(scr, p, "Asker Ocağı")
{
	cost.set(700, 0, 400); 
	addReq("Temel Teknoloji");
	faction = "Osmanlı";
	
	hitpoints = 800;
	buildRate = 50;
	sight = 5;
	size = 4;
	
	hotspot.x = hotspot.y = 0;
	hotspot.w = hotspot.h = 128;
	cx = cy = 64;
	
	if (spriteImg == 0)
	{
		spriteImg = loadImg("graphics/buildings/osmanli/asker.png");
	}
	
	sprite = Sprite(spriteImg);
	sprite.addState("saglam");
	sprite.addState("insaa");
	
	SDL_Rect t;
	t.x = t.y = 0;
	t.w = 128;
	t.h = 128;

	sprite.addFrameToState("saglam", t, 1000);
	
	t.y = 128;
	sprite.addFrameToState("insaa", t, 1000);
	
	setState("insaa");
	sbar = new SDLProgressBar(90, 14, GREEN, 0, hitpoints);
	sbar->setPosition(695, 223);
	komutlar->addWidget(sbar);
	selected = false;
	curState = "insaa";
	
	AskerOcagi* me = this;
	
	SDL_Rect trect;
	trect.x = 0; trect.y = 32;
	trect.w = trect.h = 32;
	
	resim = new SDLCommandButton(screen, trect, name);
	resim->setPosition(655, 205);
	komutlar->addWidget(resim);
	
	nowBuildingBar = new SDLProgressBar(130, 10, GREEN, 0, 1);
	nowBuildingBar->setPosition(655,250);
	nowBuildingBar->setShow(false);
	komutlar->addWidget(nowBuildingBar);
 	
	trect.x = 160; trect.y = 0;
	piyade = new SDLCommandButton(screen, trect, "Yeni Piyade", Piyade().getCost());
	piyade->setPosition(665, 270);
	piyade->dugme->clicked = makeFunctor((CBFunctor0*)0, *me, &AskerOcagi::createPiyade);
	komutlar->addWidget(piyade);

	trect.x = 224; 
	yeniceri = new SDLCommandButton(screen, trect, "Yeni Yeniçeri", Yeniceri().getCost());
	yeniceri->dugme->clicked = makeFunctor((CBFunctor0*)0, *me, &AskerOcagi::createYeniceri);
	yeniceri->setPosition(705, 270);
	komutlar->addWidget(yeniceri);
}


void AskerOcagi::createPiyade() 
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
	if (!parent->yeniPiyade())
		return;
	
	Piyade *ypiyade = new Piyade(screen, parent);
	ypiyade->setTilePos(posx+2, posy+4);
	
	nowBuilding = (BaseObject*) ypiyade;
	nowBuildingBar->setMax(ypiyade->getMaxHp());
	nowBuildingBar->setShow(true);
}
void AskerOcagi::createYeniceri() 
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
	if (!parent->yeniYeniceri())
		return;
	
	Yeniceri *yceri = new Yeniceri(screen, parent);
	yceri->setTilePos(posx+2, posy+4);
	
	nowBuilding = (BaseObject*) yceri;
	nowBuildingBar->setMax(yceri->getMaxHp());
	nowBuildingBar->setShow(true);
}

AskerOcagi::~AskerOcagi()
{
	
}
