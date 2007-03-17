#include "Player.h"

Player::Player()
{
	Tech* t = new TemelTech();
	t->instantBuild();
	nesneler.push_back(t);
	screen = 0;
	
	wood.setAmount(1000);
	food.setAmount(1000);
	stone.setAmount(1000);
	faction = "Osmanlı";
}

Player::Player(SDL_Surface *scr, string p_faction, int w, int f, int s)
{
	screen = scr;
	Tech* t = new TemelTech;
	t->instantBuild();
	nesneler.push_back(t);
	
	faction = p_faction;
	wood.setAmount(w);
	food.setAmount(f);
	stone.setAmount(s);
	drawing = dragging = false;
}

Player::~Player()
{
	nesneler.clear();
}

bool Player::isMultipleSelecting() { return (drawing && dragging); }
string Player::getFaction() { return faction; }
int Player::getWoodAmount() { return wood.getAmount(); }
int Player::getFoodAmount() { return food.getAmount(); }
int Player::getStoneAmount() { return stone.getAmount(); }
void Player::addObject(BaseObject* b) { nesneler.push_back(b); }

void Player::buildStartingUnits(int x, int y)
{
	if (faction == "Osmanlı")
	{
		Koylu *temp = new Koylu(screen, this);
		temp->instantBuild();
		temp->setPosition(360, 450);
		nesneler.push_back(temp);
		
		SehirMerkezi* e = new SehirMerkezi(screen, this);
		e->instantBuild();
		e->setPosition(128, 320);
		nesneler.push_back(e);
	}
	else if (faction == "Bizans")
	{
		Serf *s = new Serf(screen, this);
		s->instantBuild();
		s->setPosition(x, y);
		nesneler.push_back(s);
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

Koylu* Player::yeniKoylu()
{
	Koylu *temp = new Koylu();
	if (!haveReqs(temp))
	{
		cout << "Bu birim için gereksinimler karşılanmamış..." << endl;
		delete temp;
		return 0;
	}
	if (!temp->getCost().compare(wood, food, stone))
	{
		cout << "Bu birim için kaynaklar yetersiz..." << endl;
		delete temp;
		return 0;
	}
	delete temp;
	temp = new Koylu(screen, this);
	subtractCost(temp->getCost());
	return temp;
}

void Player::update()
{
	for(int i=0;i<nesneler.size();i++)
	{
		if (!nesneler[i]->build())
			break;
		if (nesneler[i]->getType() == BaseObject::UNIT)
		{
			BaseUnit* birim = (BaseUnit*)nesneler[i];
			birim->update();
			birim->draw();
		}
		else if (nesneler[i]->getType() == BaseObject::BUILDING)
		{
			BaseBuilding* b = (BaseBuilding*)nesneler[i];
			b->update();
			b->draw();
		}
	}
	if (isMultipleSelecting())
	{
		rectangleColor(screen, rsx1, rsy1, rsx2, rsy2, 0x00FF00FF);
	}
}


void Player::eventHandler(SDL_Event *event)
{
	for(int i=0;i<nesneler.size();i++)
	{
		if (nesneler[i]->getType() == BaseObject::UNIT)
		{
			BaseUnit* birim = (BaseUnit*)nesneler[i];
			if (birim->isSelected())
				birim->komutlar->eventHandler(event);
		}
		else if (nesneler[i]->getType() == BaseObject::BUILDING)
		{
			BaseBuilding* b = (BaseBuilding*)nesneler[i];
			if (b->isSelected())
				b->komutlar->eventHandler(event);
		}
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
				for(int i=0;i<nesneler.size();i++)
				{
					if (nesneler[i]->getType() == BaseObject::UNIT)
					{
						BaseUnit* birim = (BaseUnit*)nesneler[i];
						if (birim->isWaiting())
						{
							birim->issueCommand(mx, my);
							tmm = true;
						}
					}
				}
				if (tmm)
					break;
				bool single = false;
				for(int i=0;i<nesneler.size();i++)
				{
					if (nesneler[i]->getType() == BaseObject::UNIT || nesneler[i]->getType() == BaseObject::BUILDING)
					{
						BaseGraphicObject* birim = (BaseUnit*)nesneler[i];
						ux1 = birim->getX() + birim->hotspot.x;
						ux2 = ux1 + birim->hotspot.w;
						uy1 = birim->getY() + birim->hotspot.y;
						uy2 = uy1 + birim->hotspot.h;
						if (
							(mx > ux1) &&
							(mx < ux2) &&
							(my > uy1) &&
							(my < uy2)
							)
						{
							if (!single)
							{
								// sadece bir adam seciliyor (olur da ust uste gelirlerse)
								birim->select();
								// current = birim->getEkran();
								single = true;
								empty = false;
							}
						}
						else birim->unselect();
					}
				}
				if (empty)
				{
					// current = birimler;
					
					for(int i=0;i<nesneler.size();i++)
					{
						if (nesneler[i]->getType() == BaseObject::UNIT)
						{
							BaseUnit* birim = (BaseUnit*)nesneler[i];
							birim->unselect();
						}
					}
					
					// bir kare seçim başlıyor o zaman...
					drawing = true;
					rsx1 = event->motion.x;
					rsy1 = event->motion.y;
				}
			}
			else if (event->button.button == SDL_BUTTON_RIGHT)
			{
				for(int i=0;i<nesneler.size();i++)
				{
					if (nesneler[i]->getType() == BaseObject::UNIT)
					{
						BaseUnit* birim = (BaseUnit*)nesneler[i];
						if (birim->isSelected())
							birim->defaultAction(mx, my);
					}
				}
			}
			break;
		
		case SDL_MOUSEBUTTONUP:
			// bakalim kimleri sectik
			if (event->button.button = SDL_BUTTON_LEFT && drawing)
			{
				for(int i=0;i<nesneler.size();i++)
				{
					if (nesneler[i]->getType() == BaseObject::UNIT)
					{
						BaseUnit* birim = (BaseUnit*)nesneler[i];
						int smx = birim->getCenter().x;
						int smy = birim->getCenter().y;
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
								birim->select();
						}
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
		for (int j=0;j<nesneler.size();j++)
		{
			if (nesneler[j]->getName() == t[i])
				have = true;
		}
		if (!have) return false;
	}
	return have;
}
