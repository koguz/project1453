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

void Player::buildStartingUnits(int x, int y)
{
	if (faction == "Osmanlı")
	{
		Koylu* k = new Koylu(screen);
		k->instantBuild();
		k->setPosition(x, y);
		nesneler.push_back(k);
		birimler.push_back(k); // uff
	}
	else if (faction == "Bizans")
	{
		Serf *s = new Serf(screen);
		s->instantBuild();
		s->setPosition(x, y);
		nesneler.push_back(s);
		birimler.push_back(s);
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

/*
void Player::createKoylu()
{
	// öncelikle bakalim yapabiliyor muyuz...
	Koylu *temp = new Koylu();
	if (!haveReqs(temp))
	{
		cout << "Bu birim için gereksinimler karşılanmamış..." << endl;
		delete temp;
		return;
	}
	
	if (!temp->getCost().compare(wood, food, stone))
	{
		cout << "Bu birim için kaynaklar yetersiz..." << endl;
		delete temp;
		return;
	}
	
	// Bu ikisini geçtiyse, birimSirasina at... 
	birimSirasi.push_back(temp);
	// paradan kes
	subtractCost(temp->getCost());
	
	
}

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
	
	for(int i=0;i<birimler.size();i++)
	{
		BaseUnit* birim = (BaseUnit*) birimler[i];
		birim->update();
		dest.x = birim->getX();
		dest.y = birim->getY();
		SDL_Rect src = birim->getFrame();
		SDL_BlitSurface(birim->getImg(), &src, screen, &dest);
		if (birim->isSelected())
		{
			// etrafina bi kare cizelim, di mi :D
			int ux1 = birim->getX() + birim->hotspot.x;
			// int ux2 = ux1 + adamlar[i]->hotspot.w;
			int ux2 = ux1 + 4;
			int ux3 = ux2 + 19;
			int ux4 = ux3 + 4;
			int uy1 = birim->getY() + birim->hotspot.y;
			// int uy2 = uy1 + adamlar[i]->hotspot.h;
			int uy2 = uy1 + 4;
			int uy3 = uy2 + 19;
			int uy4 = uy3 + 4;
			// aacircleColor(screen, adamlar[i]->getCenter().x, adamlar[i]->getCenter().y, 18, 0x00FF00FF);
			// rectangleColor(screen, ux1, uy1, ux2, uy2, 0x00FF00FF);
			// characterColor(screen, 10, 10, 'c', 0xFFFFFFFF);
			lineColor(screen, ux1, uy1, ux2, uy1, 0x00FF00FF);
			lineColor(screen, ux3, uy1, ux4, uy1, 0x00FF00FF);
			lineColor(screen, ux1, uy4, ux2, uy4, 0x00FF00FF);
			lineColor(screen, ux3, uy4, ux4, uy4, 0x00FF00FF);
			lineColor(screen, ux1, uy1, ux1, uy2, 0x00FF00FF);
			lineColor(screen, ux1, uy3, ux1, uy4, 0x00FF00FF);
			lineColor(screen, ux4, uy1, ux4, uy2, 0x00FF00FF);
			lineColor(screen, ux4, uy3, ux4, uy4, 0x00FF00FF);
		}
	}
	
	if (isMultipleSelecting())
	{
		rectangleColor(screen, rsx1, rsy1, rsx2, rsy2, 0x00FF00FF);
	}
	
/*	
	if (!birimSirasi.empty())
	{
		BaseUnit* temp = birimSirasi.front();
		if (temp->build())
		{
			birimSirasi.pop_front();
			birimler.push_back(temp);
			cout << "birimler size: " << birimler.size() << endl;
		}
	}
*/
}


void Player::eventHandler(SDL_Event *event)
{
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
				for (unsigned int i=0;i<birimler.size();i++)
				{
					BaseUnit *birim = (BaseUnit*) birimler[i];
					if (birim->isWaiting())
					{
						birim->issueCommand(mx, my);
						tmm = true;
					}
				}
				if (tmm)
					break;
				bool single = false;
				for(unsigned int i=0;i<birimler.size();i++)
				{
					BaseUnit *birim = (BaseUnit*) birimler[i];
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
				if (empty)
				{
					// current = birimler;
					for(unsigned int i=0;i<birimler.size();i++)
						birimler[i]->unselect();
					
					// bir kare seçim başlıyor o zaman...
					drawing = true;
					rsx1 = event->motion.x;
					rsy1 = event->motion.y;
				}
			}
			else if (event->button.button == SDL_BUTTON_RIGHT)
			{
				for(int i=0;i<birimler.size();i++)
				{
					if (birimler[i]->isSelected())
					{
						BaseUnit* birim = (BaseUnit*) birimler[i];
						birim->defaultAction(mx, my);
						// adamlar[i].moveToTarget(mx, my);
					}
				}
			}
			break;
		
		case SDL_MOUSEBUTTONUP:
			// bakalim kimleri sectik
			if (event->button.button = SDL_BUTTON_LEFT && drawing)
			{
				for (int i=0;i<birimler.size();i++)
				{
					int smx = birimler.at(i)->getCenter().x;
					int smy = birimler.at(i)->getCenter().y;
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
							birimler.at(i)->select();
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
