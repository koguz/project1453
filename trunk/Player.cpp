#include "Player.h"

Player::Player()
{
	Tech* t = new TemelTech();
	t->instantBuild();
	addTech(t);
	screen = 0;
	
	wood.setAmount(1000);
	food.setAmount(1000);
	stone.setAmount(1000);
	faction = "Osmanlı";
	lastMsgTime = 0;
	cok = 0;
	harita = 0;
}

Player::Player(SDL_Surface *scr, string p_faction, int w, int f, int s)
{
	harita = 0;
	screen = scr;
	Tech* t = new TemelTech;
	t->instantBuild();
	addTech(t);
	
	faction = p_faction;
	wood.setAmount(w);
	food.setAmount(f);
	stone.setAmount(s);
	lastMsgTime = 0;
	cok = new SDLScreen(screen);
	
	SDL_Rect trect;
	trect.x = trect.y = 0;
	trect.w = trect.h = 32;
	
	Player *me = this;
	
	clist = new SDLTextView("boş", 100, 4);
	clist->setPosition(660, 210);
	cok->addWidget(clist);
	
	yuru = new SDLCommandButton(screen, trect, "Seçilileri Yürüt");
	yuru->setPosition(665,295);
	yuru->dugme->clicked = makeFunctor((CBFunctor0*)0, *me, &Player::hepsiYuru);
	cok->addWidget(yuru);
	
	trect.x = 32; trect.y = 0;
	dur = new SDLCommandButton(screen, trect, "Seçilileri Durdur");
	dur->setPosition(705,295);
	dur->dugme->clicked = makeFunctor((CBFunctor0*)0, *me, &Player::hepsiDur);
	cok->addWidget(dur);
}

Player::~Player()
{
	for (int i=0;i<units.size();i++)
	{
		BaseUnit* u = units[i];
		units[i] = 0;
		delete u;
	}
	units.clear();
	for (int i=0;i<buildings.size();i++)
	{
		BaseBuilding* b = buildings[i];
		buildings[i] = 0;
		delete b;
	}
	buildings.clear();
	for (int i=0;i<techs.size();i++)
	{
		Tech* t = techs[i];
		techs[i] = 0;
		delete t;
	}
	techs.clear();
}

string Player::getFaction() { return faction; }
int Player::getWoodAmount() { return wood.getAmount(); }
int Player::getFoodAmount() { return food.getAmount(); }
int Player::getStoneAmount() { return stone.getAmount(); }
void Player::addUnit(BaseUnit* b) { units.push_back(b); }
void Player::addTech(Tech* t) { techs.push_back(t); }
void Player::addBuilding(BaseBuilding* b) { buildings.push_back(b); }
void Player::addMessage(string m) { lastMsgTime = SDL_GetTicks(); messages.push_front(m); }

void Player::hepsiYuru()
{
	for(int i=0;i<units.size();i++)
	{
		if (units[i]->isSelected())
			units[i]->setCommandYuru();
	}
}

void Player::hepsiDur()
{
	for(int i=0;i<units.size();i++)
	{
		if (units[i]->isSelected())
			units[i]->actionDur();
	}
}

void Player::buildStartingUnits(int x, int y)
{
	if (faction == "Osmanlı")
	{
		Koylu *temp = new Koylu(screen, this);
		temp->instantBuild();
		temp->setTilePos(x, y);
		addUnit(temp);
	}
	else if (faction == "Bizans")
	{
		Serf *s = new Serf(screen, this);
		s->instantBuild();
		s->setTilePos(x, y);
		addUnit(s);
	}
}

void Player::addCost(Cost a)
{
	wood.setAmount(wood.getAmount() + a.getWoodAmount());
	food.setAmount(food.getAmount() + a.getFoodAmount());
	stone.setAmount(stone.getAmount() + a.getStoneAmount());
}

void Player::subtractCost(Cost a)
{
	wood.setAmount(wood.getAmount() - a.getWoodAmount());
	food.setAmount(food.getAmount() - a.getFoodAmount());
	stone.setAmount(stone.getAmount() - a.getStoneAmount());
}

bool Player::yeniBirim(BaseUnit *temp)
{
	if (!haveReqs(temp))
	{
		addMessage("Bu birim için gereksinimler karşılanmamış...");
		delete temp;
		return false;
	}
	if (!temp->getCost().compare(wood, food, stone))
	{
		addMessage("Bu birim için kaynaklar yetersiz...");
		delete temp;
		return false;
	}
	if (units.size() >= getHousing())
	{
		addMessage("Bu birim için yeterli ev yok...");
		delete temp;
		return false;
	}
	
	subtractCost(temp->getCost());
	delete temp;
	return true;
}

bool Player::yeniBina(BaseBuilding *temp)
{
	if (!haveReqs(temp))
	{
		addMessage("Bu bina için gereksinimler karşılanmamış...");
		delete temp;
		return false;
	}
	if (!temp->getCost().compare(wood, food, stone))
	{
		addMessage("Bu bina için kaynaklar yetersiz...");
		delete temp;
		return false;
	}
	delete temp;
	return true;
}

bool Player::yeniKoylu()
{
	Koylu *temp = new Koylu();
	return yeniBirim(temp);
}

bool Player::yeniPiyade()
{
	Piyade *temp = new Piyade();
	return yeniBirim(temp);
}

bool Player::yeniYeniceri()
{
	Yeniceri *temp = new Yeniceri();
	return yeniBirim(temp);
}

bool Player::yeniAsker()
{
	AskerOcagi *temp = new AskerOcagi();
	return yeniBina(temp);
}

void Player::addAsker(int x, int y)
{
	AskerOcagi *t = new AskerOcagi(screen, this);
	subtractCost(t->getCost());
	t->setTilePos(x, y);
	addBuilding(t);
}

bool Player::yeniOsMerkez()
{
	SehirMerkezi *temp = new SehirMerkezi();
	return yeniBina(temp);
}

bool Player::yeniOsEv()
{
	Ev *temp = new Ev();
	return yeniBina(temp);
}


void Player::addOsMerkez(int x, int y)
{
	SehirMerkezi *t = new SehirMerkezi(screen, this);
	subtractCost(t->getCost());
	t->setTilePos(x, y);
	addBuilding(t);
}

void Player::addOsEv(int x, int y)
{
	Ev *t = new Ev(screen, this);
	subtractCost(t->getCost());
	t->setTilePos(x, y);
	addBuilding(t);
}

void Player::update(int mx, int my)
{
	int top = 26;
	for(int i=0;i<5/*messages.size()*/;i++) 
	// NOTE: 5 burada sabit olsun, şişmesin 
	{
		if (i == messages.size()) break;
		SDLLabel *temp = new SDLLabel(messages[i]);
		temp->setPosition(10, top+(i*20));
		temp->drawWidget(screen);
		delete temp;
	}
	for(int i=0;i<units.size();i++)
	{
		units[i]->update();
	}
	for(int i=0;i<buildings.size();i++)
	{
		buildings[i]->update();
	}
	if ( ((SDL_GetTicks()-lastMsgTime) > 2000) && !messages.empty() )
	{
		messages.pop_back();
		lastMsgTime = SDL_GetTicks();
	}
}

int Player::getHousing()
{
	int t = 0;
	for(int i=0;i<buildings.size();i++)
	{
		if ( (buildings[i]->getName() == "Şehir Merkezi") 
			&& (buildings[i]->getState() == "saglam") )
			t += 5;
		else if ( (buildings[i]->getName() == "Ev")
			&& (buildings[i]->getState() == "saglam") )
			t += 4;
	}
	return t;
}

string Player::getHousingCount()
{
	int t = getHousing();
	int u = units.size();
	
	stringstream ss;
	ss << u << "/" << t;
	string g;
	ss >> g;
	return g;
}

void Player::eventHandler(SDL_Event *event)
{
	for(int i=0;i<units.size();i++)
	{
		if(units[i]->isSelected())
			units[i]->komutlar->eventHandler(event);
	}
	for(int i=0;i<buildings.size();i++)
	{
		if (buildings[i]->isSelected())
			buildings[i]->komutlar->eventHandler(event);
	}
}

bool Player::haveReqs(BaseObject *u)
{
	vector<string> t = u->getReqs();
		
	bool have = false;
	
	for (int i=0;i<t.size();i++)
	{
		have = false;
		for (int j=0;j<units.size();j++)
		{
			if (units[j]->getName() == t[i])
				have = true;
		}
		
		for (int j=0;j<buildings.size();j++)
		{
			if (buildings[j]->getName() == t[i])
				have = true;
		}
		
		for (int j=0;j<techs.size();j++)
		{
			if (techs[j]->getName() == t[i])
				have = true;
		}
		if (!have) return false;
	}
	return have;
}
