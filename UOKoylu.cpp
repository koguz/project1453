#include "UOKoylu.h"

SDL_Surface* Koylu::spriteImg = 0;

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
	
	if (spriteImg == 0)
	{
		spriteImg = loadImg("graphics/units/osmanli/koylu.png");
	}
	
	for(int i=0;i<8;i++)
	{
		Sprite *temp = new Sprite(spriteImg);
		temp->addState("dur");
		temp->addState("yuru");
		
		t.x = i*64;
		t.y = 0;
		temp->addFrameToState("dur", t, 1000);
		
		for (int j=0;j<2;j++)
		{
			t.x = i*64;
			t.y = 64 + (j*64);
			temp->addFrameToState("yuru", t, 100);
		}
		sprites[i] = *temp;
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

Koylu::~Koylu()
{
}

void Koylu::setCommandCalis()
{
	setState("calis");
}


