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
		createKoylu(true);
		
		SehirMerkezi* e = new SehirMerkezi(screen, this);
		e->instantBuild();
		e->setPosition(128, 320);
		Player *me = this;
// 		e->createKoylu->dugme->clicked = makeFunctor((CBFunctor0*)0, *me, &Player::createKoylu);
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
	// öncelikle bakalim yapabiliyor muyuz...
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
	
	// paradan kes
	subtractCost(temp->getCost());
	
	//( temp->setPosition(360, 450); // FIXME fixed point?
	// 
	// nesneler.push_back(temp);
	return temp;
}

void Player::createKoylu(bool instant)
{
	Koylu *temp = new Koylu(screen, this);
	if (instant) 
	{
		temp->instantBuild();
		temp->setPosition(360, 450);
		nesneler.push_back(temp);
		return;
	}
	
	
}
/*
void Player::createPiyade()
{
	// sonra
	return;
}

*/

void Player::update()
{
	SDL_Rect dest;
	dest.w = dest.h = 64;
	
	list<BaseObject*>::iterator iter;
	for(iter=nesneler.begin();iter!=nesneler.end();iter++)
	{
		if (!(*iter)->build())
			break;
		if ((*iter)->getType() == BaseObject::UNIT)
		{
			BaseUnit* birim = (BaseUnit*)(*iter);
			birim->update();
			birim->draw();
		}
		else if ((*iter)->getType() == BaseObject::BUILDING)
		{
			BaseBuilding* b = (BaseBuilding*)(*iter);
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
	list<BaseObject*>::iterator iter;
	for(iter=nesneler.begin();iter!=nesneler.end();iter++)
	{
		if ((*iter)->getType() == BaseObject::UNIT)
		{
			BaseUnit* birim = (BaseUnit*)(*iter);
			if (birim->isSelected())
				birim->komutlar->eventHandler(event);
		}
		else if ((*iter)->getType() == BaseObject::BUILDING)
		{
			BaseBuilding* b = (BaseBuilding*)(*iter);
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
			if (mx > 600)
				break;
			if (event->button.button == SDL_BUTTON_LEFT) 
			{
				// önce seçilen birine bir komut verilmişmi
				bool tmm = false;
				list<BaseObject*>::iterator iter;
				for(iter=nesneler.begin();iter!=nesneler.end();iter++)
				{
					if ((*iter)->getType() == BaseObject::UNIT)
					{
						BaseUnit* birim = (BaseUnit*)(*iter);
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
				for(iter=nesneler.begin();iter!=nesneler.end();iter++)
				{
					if ((*iter)->getType() == BaseObject::UNIT || (*iter)->getType() == BaseObject::BUILDING)
					{
						BaseGraphicObject* birim = (BaseUnit*)(*iter);
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
					
					for(iter=nesneler.begin();iter!=nesneler.end();iter++)
					{
						if ((*iter)->getType() == BaseObject::UNIT)
						{
							BaseUnit* birim = (BaseUnit*)(*iter);
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
				list<BaseObject*>::iterator iter;
				for(iter=nesneler.begin();iter!=nesneler.end();iter++)
				{
					if ((*iter)->getType() == BaseObject::UNIT)
					{
						BaseUnit* birim = (BaseUnit*)(*iter);
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
				list<BaseObject*>::iterator iter;
				for(iter=nesneler.begin();iter!=nesneler.end();iter++)
				{
					if ((*iter)->getType() == BaseObject::UNIT)
					{
						BaseUnit* birim = (BaseUnit*)(*iter);
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
		list<BaseObject*>::iterator j;
		for (j=nesneler.begin();j!=nesneler.end();j++)
		{
			if ((*j)->getName() == t[i])
				have = true;
		}
		if (!have) return false;
	}
	return have;
}
