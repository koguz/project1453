#include "UOKoylu.h"

SDL_Surface* Koylu::spriteImg = 0;

Koylu::Koylu()
{
	cost.set(0, 400, 0); 
	addReq("Temel Teknoloji");
	faction = "Osmanlı";
	sndSelected = 0;
	sndConfirmed = 0;
	sndBuilding = 0;
	sndOk = 0;
	sndTamam = 0;
	sndHata = 0;
	yuru = dur = calis = resim = 0;
	insa = 0; binaTamam = 0;
}

Koylu::Koylu(SDL_Surface *scr, Player *p):BaseUnit(scr, p, "Köylü")
{
	cost.set(0, 400, 0); 
	addReq("Temel Teknoloji");
	faction = "Osmanlı";
	
	// temel bileşenler
	hitpoints = 20;
	buildRate = 1000;
	armor = 2;
	damage = 10;
	range = 1;
	sight = 3;
	speed = 20;
	morale = 60;
	xp = 10;
	kills = 0;
	
	// grafiksel bileşenler
// 	hotspot.x = hotspot.y = 0;
	hotspot.x = 20; hotspot.y = 29;
	hotspot.w = hotspot.h = 32;
	cx = 36; cy = 44; 
	
	selected = false;
	
	SDL_Rect t;
	t.w = t.h = 72;
	
	if (spriteImg == 0)
	{
		spriteImg = loadImg("graphics/units/osmanli/koylu.png");
	}
	
	for(int i=0;i<8;i++)
	{
		sprites[i].setImg(spriteImg);
		sprites[i].addState("dur");
		sprites[i].addState("yuru");
		sprites[i].addState("calis");
		
		t.x = i*72;
		t.y = 0;
		sprites[i].addFrameToState("dur", t, 1000);
		sprites[i].addFrameToState("calis", t, 1000);
		
		for (int j=0;j<4;j++)
		{
			t.x = i*72;
			t.y = 72 + (j*72);
			sprites[i].addFrameToState("yuru", t, 100);
		}
		
		for (int j=0;j<2;j++)
		{
			t.x = i*72;
			t.y = 360 + (j*72);
			sprites[i].addFrameToState("calis", t, 100);
		}
	}
	
	yon = S;
	setState("dur");
// 	healthBar = new SDLProgressBar(32, 4, GREEN, 0, hitpoints);
	
	insa = 0;
	
	// sesler
	sndSelected = new SDLMixer("wavs/ottoman/koylu01.ogg");
	sndConfirmed = new SDLMixer("wavs/ottoman/koylu02.ogg");
	sndBuilding = new SDLMixer("wavs/ottoman/koylu03.ogg");
	sndOk = new SDLMixer("wavs/ottoman/koylu04.ogg");
	sndTamam = new SDLMixer("wavs/ottoman/koylu05.ogg");
	sndHata = new SDLMixer("wavs/ottoman/koylu06.ogg");
	binaTamam = new SDLMixer("wavs/ui/binaTamam.ogg");
	
	// alt ekran: komutlar
	SDL_Rect trect;
	trect.x = trect.y = 0;
	trect.w = trect.h = 32;
	
	Koylu *me = this;
	
	trect.x = 96; trect.y = 0;
	resim = new SDLCommandButton(screen, trect, "Köylü");
	resim->setPosition(655, 205);
	komutlar->addWidget(resim);
	
	trect.x = 0;
	yuru = new SDLCommandButton(screen, trect, "Yürü");
	yuru->setPosition(665,295);
	yuru->dugme->clicked = makeFunctor((CBFunctor0*)0, *me, &Koylu::setCommandYuru);
	komutlar->addWidget(yuru);
	
	trect.x = 32; trect.y = 0;
	dur = new SDLCommandButton(screen, trect, "Dur");
	dur->setPosition(705,295);
	dur->dugme->clicked = makeFunctor((CBFunctor0*)0, *me, &Koylu::actionDur);
	komutlar->addWidget(dur);
	
	trect.x = 288; trect.y = 0;
	calis = new SDLCommandButton(screen, trect, "Çalış / Saldır");
	calis->setPosition(745, 295);
	komutlar->addWidget(calis);
	
	trect.x = 128; trect.y = 32;
	smerkezi = new SDLCommandButton(screen, trect, "Şehir Merkezi Yap", SehirMerkezi().getCost());
	smerkezi->setPosition(665, 335);
	smerkezi->dugme->clicked = makeFunctor((CBFunctor0*)0, *me, &Koylu::setCommandMerkezYap);
	komutlar->addWidget(smerkezi);
	
	trect.x = 64; trect.y = 32;
	ev = new SDLCommandButton(screen, trect, "Ev Yap", Ev().getCost());
	ev->setPosition(705, 335);
	ev->dugme->clicked = makeFunctor((CBFunctor0*)0, *me, &Koylu::setCommandEvYap);
	komutlar->addWidget(ev);
	
	trect.x = 160; trect.y = 32;
	tarla = new SDLCommandButton(screen, trect, "Tarla Yap");
	tarla->setPosition(745, 335);
	komutlar->addWidget(tarla);
	
	trect.x = 96; trect.y = 32;
	maden = new SDLCommandButton(screen, trect, "Maden Yap");
	maden->setPosition(665, 375);
	komutlar->addWidget(maden);
	
	trect.x = 32; trect.y = 32;
	demirci = new SDLCommandButton(screen, trect, "Demirci Yap");
	demirci->setPosition(705, 375);
	komutlar->addWidget(demirci);
	
	trect.x = 0; trect.y = 32;
	asker = new SDLCommandButton(screen, trect, "Asker Ocağı Yap", AskerOcagi().getCost());
	asker->setPosition(745, 375);
	asker->dugme->clicked = makeFunctor((CBFunctor0*)0, *me, &Koylu::setCommandAskerOcagiYap);
	komutlar->addWidget(asker);
	
	sbar = new SDLProgressBar(90, 14, GREEN, 0, hitpoints);
	sbar->setPosition(695, 223);
	komutlar->addWidget(sbar);
}

Koylu::~Koylu()
{
	delete sndSelected;
	delete sndConfirmed;
	delete sndBuilding;
	delete sndOk;
	delete sndTamam;
	delete binaTamam;
}

void Koylu::command(int x, int y)
{
// 	cout << commandList.size() << endl;
	if (waitingCommand == "yuru")
	{
		waiting = false;
		moveToTarget(x, y);
		sndConfirmed->play();
		return;
	}
	if (waitingCommand == "merkezYap")
	{
		if (parent->harita->uygun())
		{
			waiting = false;
			parent->harita->endBuildSel();
			parent->addOsMerkez(x, y);
			goToAndBuild(x, y, 4);
			sndBuilding->play();
		}
		else
		{
			parent->addMessage("Burası uygun değil!");
			sndHata->play();
		}
		return;
	}
	if (waitingCommand == "evYap")
	{
		if (parent->harita->uygun())
		{
			waiting = false;
			parent->harita->endBuildSel();
			parent->addOsEv(x, y);
			goToAndBuild(x, y, 2);
			sndTamam->play();
		}
		else
		{
			parent->addMessage("Burası uygun değil!");
			sndHata->play();
		}
		return;
	}
	if (waitingCommand == "askerYap")
	{
		if (parent->harita->uygun())
		{
			waiting = false;
			parent->harita->endBuildSel();
			parent->addAsker(x, y);
			goToAndBuild(x, y, 4);
			sndBuilding->play();
		}
		else
		{
			parent->addMessage("Burası uygun değil!");
			sndHata->play();
		}
		return;
	}
}

void Koylu::goToAndBuild(int x, int y, int s)
{
	waitingCommand = "gitVeYap";
	
	int is = x - 1;
	if (is < 0) is=0;
	int ie = x + s;
	if (ie > parent->harita->getTx()) ie = parent->harita->getTx();
	
	int js = y - 1;
	if (js < 0) js=0;
	int je = y + s;
	if (je > parent->harita->getTy()) je = parent->harita->getTy();
	
	insax = x;
	insay = y;
	insa = parent->harita->getBuilding(x, y);
	
// 	int gitx, gity;
	int g, h, min; // f = g+h;
	vector<int> fl; // buraya degerleri aticas
	vector<Coordinates> cl;
	
	Coordinates tmp;
	
	for(int i=is;i<=ie;i++)
	{
		for(int j=js;j<=je;j++)
		{
			if (posx == i && posy == j)
			{
				tax = i;
				tay = j;
				return;
			}
			if (parent->harita->getTileInfo(i, j) == Map::BOS)
			{
				if ( abs(i-x) == 1 && abs(j-y) == 1 )
					g = 14; // capraz daha zahmetli
				else g = 10;
				h = 10*(int)hypot(abs(tax-i), abs(tay-j)); // hypot = hipotenüsü ne kadar... tek tek alinca sorun cikiyor :(
				tmp.x = i;
				tmp.y = j;
				fl.push_back(g + h);
				cl.push_back(tmp);
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
	moveToTarget(cl[sec].x, cl[sec].y);
	
}

void Koylu::defAct(int tx, int ty)
{
	// bakalim basilan yerde ne var :)
	switch(parent->harita->getTileInfo(tx, ty))
	{
		case Map::BOS:
			moveToTarget(tx, ty);
			sndConfirmed->play();
			break;
		case Map::BINA:
			goToAndBuild(tx, ty, parent->harita->getBuilding(tx, ty)->getSize());
			sndOk->play();
// 			buildBina(parent->harita->getBuilding(tx, ty));
			break;
		default:
			parent->addMessage("Burası için bana bir görev tanımlanmamış :(");
			break;
	}
}

void Koylu::kUpdate()
{
	if (waitingCommand == "gitVeYap")
	{
		if (tax == posx && tay == posy)
		{
			waitingCommand = "yok";
			setState("calis");
			yoneBak(insax, insay);
			buildBina(insa);
		}
	}
	if (curState == "calis")
	{
		if (insa != 0)
		{
			if (insa->getState() == "insaa" && !insa->tam())
				insa->addCurHp(1);
				
			else 
			{
				insa->setState("saglam");
				parent->addMessage("Bina yapımı tamamlandı: " + insa->getName());
				binaTamam->play();
				insa = 0;
				setState("dur");
			}
		}
	}
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

void Koylu::recurseTargetTiles(int tx, int ty)
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

void Koylu::iptal()
{
	parent->harita->endBuildSel();
}

void Koylu::buildBina(BaseBuilding* b)
{
	if (b == 0)
		return;
	if (!b->tam())
	{
		insa = b;
		setState("calis");
	}
}

void Koylu::setCommandCalis()
{
	setState("calis");
}

void Koylu::setCommandMerkezYap()
{
	if(!parent->yeniOsMerkez())
		return;
	waitingCommand = "merkezYap";
	waiting = true;
	parent->harita->startBuildSel(4, MapTile::CIM);
	parent->addMessage("Bu bina sadece yeşil çimler üzerine yapılabilir.");
}

void Koylu::setCommandAskerOcagiYap()
{
	if(!parent->yeniAsker())
		return;
	waitingCommand = "askerYap";
	waiting = true;
	parent->harita->startBuildSel(4, MapTile::CIM);
	parent->addMessage("Bu bina sadece yeşil çimler üzerine yapılabilir.");
}

void Koylu::setCommandEvYap()
{
	if(!parent->yeniOsEv())
		return;
	waitingCommand = "evYap";
	waiting = true;
	parent->harita->startBuildSel(2, MapTile::CIM);
	parent->addMessage("Bu bina sadece yeşil çimler üzerine yapılabilir.");
}

