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
	rsx1 = rsx2 = rsy1 = rsy2 = -1;
	lastMsgTime = 0;
}

Player::Player(SDL_Surface *scr, string p_faction, int w, int f, int s)
{
	screen = scr;
	Tech* t = new TemelTech;
	t->instantBuild();
	addTech(t);
	
	faction = p_faction;
	wood.setAmount(w);
	food.setAmount(f);
	stone.setAmount(s);
	drawing = dragging = false;
	rsx1 = rsx2 = rsy1 = rsy2 = -1;
	lastMsgTime = 0;
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

bool Player::isMultipleSelecting() { return (drawing && dragging); }
string Player::getFaction() { return faction; }
int Player::getWoodAmount() { return wood.getAmount(); }
int Player::getFoodAmount() { return food.getAmount(); }
int Player::getStoneAmount() { return stone.getAmount(); }
void Player::addUnit(BaseUnit* b) { units.push_back(b); }
void Player::addTech(Tech* t) { techs.push_back(t); }
void Player::addBuilding(BaseBuilding* b) { buildings.push_back(b); }
void Player::addMessage(string m) { lastMsgTime = SDL_GetTicks(); messages.push_front(m); }

void Player::buildStartingUnits(int x, int y)
{
	if (faction == "Osmanlı")
	{
		Koylu *temp = new Koylu(screen, this);
		temp->instantBuild();
		temp->setPosition(360, 450);
		addUnit(temp);
		
		SehirMerkezi* e = new SehirMerkezi(screen, this);
		e->instantBuild();
		e->setPosition(128, 320);
		addBuilding(e);
	}
	else if (faction == "Bizans")
	{
		Serf *s = new Serf(screen, this);
		s->instantBuild();
		s->setPosition(x, y);
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

bool Player::yeniKoylu()
{
	Koylu *temp = new Koylu();
	if (!haveReqs(temp))
	{
		addMessage("Bu birim için gereksinimler karşılanmamış...");
// 		cout << "Bu birim için gereksinimler karşılanmamış..." << endl;
		delete temp;
		return false;
	}
	if (!temp->getCost().compare(wood, food, stone))
	{
		addMessage("Bu birim için kaynaklar yetersiz...");
// 		cout << << endl;
		delete temp;
		return false;
	}
// 	delete temp;
	subtractCost(temp->getCost());
// 	temp = new Koylu(screen, this);
	delete temp;
// 	return new Koylu(screen, this);
	return true;
}

void Player::update()
{
	int top = 26;
	for(int i=0;i<5/*messages.size()*/;i++) // NOTE 5 burada sabit olsun, şişmesin 
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
		units[i]->draw();
	}
	for(int i=0;i<buildings.size();i++)
	{
		buildings[i]->update();
		buildings[i]->draw();
	}
	if (isMultipleSelecting())
	{
		rectangleColor(screen, rsx1, rsy1, rsx2, rsy2, 0x00FF00FF);
	}
	if ( ((SDL_GetTicks()-lastMsgTime) > 2000) && !messages.empty() )
	{
		messages.pop_back();
		lastMsgTime = SDL_GetTicks();
	}
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
	int mx, my, ux1, ux2, uy1, uy2;
	bool empty = true;
//	rsx1 = 0, rsx2 = 0, rsy1 = 0, rsy2 = 0;
//	drawing = false;
//	dragging = false;
	switch(event->type)
	{
		case SDL_MOUSEBUTTONDOWN:
			mx = event->motion.x;
			my = event->motion.y;
			if (mx > 600) // FIXME -- HARITA EKRANININ GENİŞLİĞİ!!
				break;
			if (event->button.button == SDL_BUTTON_LEFT) 
			{
				// önce seçilen birine bir komut verilmişmi
				bool tmm = false;
				for(int i=0;i<units.size();i++)
				{
					if(units[i]->isWaiting())
					{
						units[i]->issueCommand(mx, my);
						units[i]->playConfirmed();
						tmm = true;
					}
				}
				if (tmm)
					break;
				bool single = false;
				for(int i=0;i<units.size();i++)
				{
					if (units[i]->isMouseOver(mx, my) && !single)
					{
						units[i]->select();
						units[i]->playSelected();
						single = true;
						empty = false;
					}
					else units[i]->unselect();
				}
				
				for(int i=0;i<buildings.size();i++)
				{
					if (buildings[i]->isMouseOver(mx, my) && !single)
					{
						buildings[i]->select();
						buildings[i]->playSelected();
						single = true;
						empty = false;
					}
					else buildings[i]->unselect();
				}
				if (empty)
				{
					for(int i=0;i<units.size();i++)
						units[i]->unselect();
					for(int i=0;i<buildings.size();i++)
						buildings[i]->unselect();
					// bir kare seçim başlıyor o zaman...
					drawing = true;
					rsx1 = event->motion.x;
					rsy1 = event->motion.y;
				}
			}
			else if (event->button.button == SDL_BUTTON_RIGHT)
			{
				for(int i=0;i<units.size();i++)
				{
					if (units[i]->isSelected())
					{
						units[i]->defaultAction(mx, my);
						units[i]->playConfirmed();
					}
				}
			}
			break;
		
		case SDL_MOUSEBUTTONUP:
			// bakalim kimleri sectik
			if (event->button.button = SDL_BUTTON_LEFT && drawing)
			{
				for(int i=0;i<units.size();i++)
				{
					int smx = units[i]->getCenter().x;
					int smy = units[i]->getCenter().y;
					if  (
						(
							(smx > rsx1) &&
							(smx < rsx2) &&
							(smy > rsy1) &&
							(smy < rsy2)
						) ||
						(
							(smx < rsx1) &&
							(smx > rsx2) &&
							(smy < rsy1) &&
							(smy > rsy2)
						) ||
						(
							(smx > rsx1) &&
							(smx < rsx2) &&
							(smy < rsy1) &&
							(smy > rsy2)
						) ||
						(
							(smx < rsx1) &&
							(smx > rsx2) &&
							(smy > rsy1) &&
							(smy < rsy2)
						)
					)
					{
						if (isValidSelection())
							units[i]->select();
					}
				}
				drawing = dragging = false;
				rsx1 = rsx2 = rsy1 = rsy2 = -1;
			}
			break;
		
		case SDL_MOUSEMOTION:
			if (drawing)
			{
				dragging = true;
				rsx2 = event->motion.x;
				rsy2 = event->motion.y;
			}
			break;
	}
}


bool Player::isValidSelection()
{
	if ( (rsx1 == -1) || (rsy1 == -1) || (rsx2 == -1) || (rsy2 == -1) )
	{
		return false;
	} 
	else return true;
}


// TODO - buna bi ara bak
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
