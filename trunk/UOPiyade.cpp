#include "UOPiyade.h"

SDL_Surface* Piyade::spriteImg = 0;

Piyade::Piyade()
{
	cost.set(0, 600, 0);
	addReq("Temel Teknoloji");
	addReq("Asker Ocağı");
	faction = "Osmanlı";
	sndSelected = 0;
	sndConfirmed = 0;
	yuru = dur = resim = saldir = 0;
}

Piyade::Piyade(SDL_Surface *scr, Player *p):BaseUnit(scr, p, "Piyade")
{
	cost.set(0, 600, 0);
	addReq("Temel Teknoloji");
	addReq("Asker Ocağı");
	faction = "Osmanlı";
	
	hitpoints = 30;
	buildRate = 1200;
	armor = 4;
	damage = 20;
	range = 1;
	sight = 4;
	speed = 40;
	morale = 60;
	xp = 20;
	kills = 0;
	
	hotspot.x = 20; hotspot.y = 29;
	hotspot.w = hotspot.h = 32;
	cx = 36; cy = 44;
	
	selected = false;
	
	SDL_Rect t;
	t.w = t.h = 72;
	
	if (spriteImg == 0)
	{
		spriteImg = loadImg("graphics/units/osmanli/piyade.png");
	}
	
	
	for(int i=0;i<8;i++)
	{
		sprites[i].setImg(spriteImg);
		sprites[i].addState("dur");
		sprites[i].addState("yuru");
		
		t.x = i*72;
		t.y = 0;
		sprites[i].addFrameToState("dur", t, 1000);
		sprites[i].addFrameToState("saldir", t, 1000);
		
		for (int j=0;j<4;j++)
		{
			t.x = i*72;
			t.y = 72 + (j*72);
			sprites[i].addFrameToState("yuru", t, 100);
		}
	}
	
	yon = S;
	setState("dur");
	
	sndSelected = new SDLMixer("wavs/ottoman/piyade01.ogg");
	sndConfirmed = new SDLMixer("wavs/ottoman/piyade02.ogg");
	
	SDL_Rect trect;
	trect.x = trect.y = 0;
	trect.w = trect.h = 32;
	
	Piyade *me = this;
	
	trect.x = 160; trect.y = 0;
	resim = new SDLCommandButton(screen, trect, "Piyade");
	resim->setPosition(655, 205);
	komutlar->addWidget(resim);
	
	trect.x = 0;
	yuru = new SDLCommandButton(screen, trect, "Yürü");
	yuru->setPosition(665,295);
	yuru->dugme->clicked = makeFunctor((CBFunctor0*)0, *me, &Piyade::setCommandYuru);
	komutlar->addWidget(yuru);
	
	trect.x = 32; trect.y = 0;
	dur = new SDLCommandButton(screen, trect, "Dur");
	dur->setPosition(705,295);
	dur->dugme->clicked = makeFunctor((CBFunctor0*)0, *me, &Piyade::actionDur);
	komutlar->addWidget(dur);
	
	trect.x = 64; trect.y = 0;
	saldir = new SDLCommandButton(screen, trect, "Saldır");
	saldir->setPosition(745, 295);
	komutlar->addWidget(saldir);
	
	sbar = new SDLProgressBar(90, 14, GREEN, 0, hitpoints);
	sbar->setPosition(695, 223);
	komutlar->addWidget(sbar);
	
}

void Piyade::defAct(int tx, int ty)
{
	switch(parent->harita->getTileInfo(tx, ty))
	{
		case Map::BOS:
			moveToTarget(tx, ty);
			sndConfirmed->play();
			break;
		default:
			parent->addMessage("Burası için bana bir görev tanımlanmamış :(");
			break;
	}
}


void Piyade::recurseTargetTiles(int tx, int ty)
{
	if (parent->harita->getTileInfo(tax, tay) != Map::BOS)
	{
		actionDur();
// 		parent->addMessage("Oraya yürüyemiyorum :(");
		return;
	}
	int is = tx - 1;
	if (is < 0) is=0;
	int ie = tx + 1;
	if (ie > parent->harita->getTx()) ie = parent->harita->getTx();
	
	int js = ty - 1;
	if (js < 0) js=0;
	int je = ty + 1;
	if (je > parent->harita->getTy()) je = parent->harita->getTy();
	
	int g, h, min; // f = g+h;
	vector<int> fl; // buraya degerleri aticas
	vector<Coordinates> cl;
	
	Coordinates tmp;
	
	for(int i=is;i<=ie;i++)
	{
		for(int j=js;j<=je;j++)
		{
			if (parent->harita->getTileInfo(i, j) == Map::BOS && !buVarMi(i, j))
			{
				if ( abs(i-tx) == 1 && abs(j-ty) == 1 )
					g = 14; // capraz daha zahmetli
				else g = 10;
				h = 10*(int)hypot(abs(tax-i), abs(tay-j)); // hypot = hipotenüsü ne kadar... tek tek alinca sorun cikiyor :(
				if ( !(i == tx && j == ty))
				{
					tmp.x = i;
					tmp.y = j;
					fl.push_back(g + h);
					cl.push_back(tmp);
				}
			}
		}
	}
	
	min = fl[0];
	int sec = 0;
	for (int i=1;i<fl.size();i++)
	{
		if (fl[i] < min)
		{
			min = fl[i];
			sec = i;
		}
	}
	
	targetTiles.push_back(cl[sec]);
	if (!(cl[sec].x == tax && cl[sec].y == tay))
	{
		recurseTargetTiles(cl[sec].x, cl[sec].y);
	}
}

void Piyade::pUpdate()
{
	if (!areWeThereYet && targetTiles.empty())
	{
		recurseTargetTiles(posx, posy);
		areWeThereYet = true;
	}
	else if (!targetTiles.empty())
	{
		Coordinates temp = targetTiles.front();
		if (target.empty())
		{
			if (parent->harita->getTileInfo(temp.x, temp.y) == Map::BOS)
			{
				calWalkTile(temp.x, temp.y);
				calc = true;
			}
			else
			{
				targetTiles.clear();
				recurseTargetTiles(posx, posy);
			}
		}
		else if (calc)
		{
			targetTiles.pop_front();
			calc = false;
		}
	}
}

void Piyade::command(int x, int y)
{
	if (waitingCommand == "yuru")
	{
		waiting = false;
		moveToTarget(x, y);
		sndConfirmed->play();
	}
}

Piyade::~Piyade()
{
	delete sndSelected;
	delete sndConfirmed;
}


