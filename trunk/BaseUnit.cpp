#include "BaseUnit.h"

BaseUnit::BaseUnit()
{
	lastUpdate = SDL_GetTicks();
}

BaseUnit::BaseUnit(SDL_Surface *scr, Player *p, string n):BaseObject(n), BaseGraphicObject(scr, p)
{
	lastUpdate = SDL_GetTicks();
	hitpoints = 20; // hit points
	armor = 1; // over 10
	damage = 10; // minimum damage
	range = 1; // minimum range
	sight = 4; // radius of sight circle
	speed = 10; // below average speed
	morale = 50; // over 100
	xp = 0; // no xp
	kills = 0; // no kills
	
	tip = UNIT;
	tax = tay = 0;
	
	waitingCommand = "yok";
	waiting = false;
	
	komutlar = new SDLScreen(screen);
	
	birimAdi = new SDLLabel(n, 12);
	birimAdi->setPosition(695, 205);
	komutlar->addWidget(birimAdi);
	
	stArmor = new SDLLabel("Zırh: ", 10);
	stArmor->setPosition(655, 245);
	komutlar->addWidget(stArmor);
	
	stArmorVal = new SDLLabel(armor, 10);
	stArmorVal->setPosition(705, 245);
	komutlar->addWidget(stArmorVal);
	
	stDamage = new SDLLabel("Hasar: ", 10);
	stDamage->setPosition(655, 255);
	komutlar->addWidget(stDamage);
	
	stDamageVal = new SDLLabel(damage, 10);
	stDamageVal->setPosition(705, 255);
	komutlar->addWidget(stDamageVal);
	
	stRange = new SDLLabel("Menzil: ", 10);
	stRange->setPosition(655, 265);
	komutlar->addWidget(stRange);
	
	stRangeVal = new SDLLabel(range, 10);
	stRangeVal->setPosition(705, 265);
	komutlar->addWidget(stRangeVal);
	
	stSight = new SDLLabel("Görüş: ", 10);
	stSight->setPosition(655, 275);
	komutlar->addWidget(stSight);
	
	stSightVal = new SDLLabel(sight, 10);
	stSightVal->setPosition(705, 275);
	komutlar->addWidget(stSightVal);
	
	stSpeed = new SDLLabel("Hız: ", 10);
	stSpeed->setPosition(720, 245);
	komutlar->addWidget(stSpeed);
	
	stSpeedVal = new SDLLabel(speed, 10);
	stSpeedVal->setPosition(770, 245);
	komutlar->addWidget(stSpeedVal);
	
	stMorale = new SDLLabel("Moral: ", 10);
	stMorale->setPosition(720, 255);
	komutlar->addWidget(stMorale);
	
	stMoraleVal = new SDLLabel(morale, 10);
	stMoraleVal->setPosition(770, 255);
	komutlar->addWidget(stMoraleVal);
	
	stXp = new SDLLabel("Deneyim: ", 10);
	stXp->setPosition(720, 265);
	komutlar->addWidget(stXp);
	
	stXpVal = new SDLLabel(xp, 10);
	stXpVal->setPosition(770, 265);
	komutlar->addWidget(stXpVal);
	
	stKills = new SDLLabel("Ölü: ", 10);
	stKills->setPosition(720, 275);
	komutlar->addWidget(stKills);
	
	stKillsVal = new SDLLabel(kills, 10);
	stKillsVal->setPosition(770, 275);
	komutlar->addWidget(stKillsVal);
}

BaseUnit::~BaseUnit() {}

void BaseUnit::setState(string state) { curState = state; }
void BaseUnit::setYon(direction d) { yon = d; }
bool BaseUnit::isWaiting() { return waiting; }

void BaseUnit::actionDur()
{
	target.clear();
	commandList.clear();
	setState("dur");
}

void BaseUnit::setCommandYuru()
{
	SDLCursor::setCursorTarget();
	SDLCursor::locked = true;
	waitingCommand = "yuru";
	waiting = true;
}

void BaseUnit::cancelActions()
{
	SDLCursor::locked = false;
	SDLCursor::setCursorMain();
	waiting = false;
	waitingCommand = "yok";
// 	parent->harita->endBuildSel();
}

int BaseUnit::getSight()
{
	return sight;
}


bool BaseUnit::onScreen(int x1, int x2, int y1, int y2)
{
	return 
	( 
		(posx >= x1) &&
		(posx <= x2) &&
		(posy >= y1) &&
		(posy <= y2)
	);
}

void BaseUnit::draw(SDL_Rect s, SDL_Rect d)
{
	SDL_Rect src = getFrame();
	src.x += s.x + hotspot.x;
	src.y += s.y + hotspot.y;
	src.w = s.w;
	src.h = s.h;
// 	rectangleColor(screen, wx, wy, wx+32, wy+32, 0xFFFFFFFF);
	SDL_BlitSurface(getImg(), &src, screen, &d);
	if (isSelected())
	{
		// TODO -- sonra düşünüces bunu
		SDL_Rect m = d;
// 		if (m.w != 32 || m.h != 32)
// 		{
// 			m.x = m.x - (32 - m.w);
// 			m.y = m.y - (32 - m.h);
// 			m.w = m.h = 32;
// 		}
		int ux1 = m.x; 
		int ux2 = ux1 + 4;
		int ux3 = m.x + m.w - 4; 
		int ux4 = ux3 + 4;
		int uy1 = m.y; 
		int uy2 = uy1 + 4;
		int uy3 = m.y + m.h - 4; 
		int uy4 = uy3 + 4;
		
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

void BaseUnit::calWalkTile(int tx, int ty)
{
	target.clear();
	int smx = wx;
	int smy = wy;
	tx = tx*32;
	ty = ty*32;
	
	Coordinates temp;
	
	if (abs(tx-smx) >= abs(ty-smy))
	{
		// once y'e gel, sonra x
		// cünkü x daha uzak
		while (ty != smy)
		{
			if (ty > smy)
				smy++;
			else if (ty < smy)
				smy--;
			
			if (tx > smx)
				smx++;
			else if (tx < smx)
				smx--;
			temp.x = smx; 
			temp.y = smy;
			target.push_back(temp);
		}
		while (tx != smx)
		{
			if (tx > smx)
				smx++;
			else if (tx < smx)
				smx--;
			temp.x = smx; 
			temp.y = smy;
			target.push_back(temp);
		}
	}
	else if (abs(tx-smx) < abs(ty-smy))
	{
		// once x'e gel, sonra y
		while (tx != smx)
		{
			if (tx > smx)
				smx++;
			else if (tx < smx)
				smx--;
			
			if (ty > smy)
				smy++;
			else if (ty < smy)
				smy--;
			temp.x = smx; 
			temp.y = smy;
			target.push_back(temp);
		}
		while (ty != smy)
		{
			if (ty > smy)
				smy++;
			else if (ty < smy)
				smy--;
			temp.x = smx; 
			temp.y = smy;
			target.push_back(temp);
		}
	}
	
	commandList.push_back("yuru");
}

void BaseUnit::moveToTarget(int tx, int ty)
{
	SDLCursor::locked = false;
	SDLCursor::setCursorMain();
	tax = tx;
	tay = ty;
	calWalkTile(tx, ty);
}

void BaseUnit::doUpdate()
{
// 	parent->harita->exploreTiles(getTx(), getTy(), getSight());
	if (selected)
	{
		healthBar->setValue(currentHp);
		sbar->setValue(currentHp);
		stArmorVal->setText(armor);
		stDamageVal->setText(damage);
		stRangeVal->setText(range);
		stSightVal->setText(sight);
		stSpeedVal->setText(speed);
		stMoraleVal->setText(morale);
		stXpVal->setText(xp);
		stKillsVal->setText(kills);
	}
	
	Coordinates temp;
	if (!target.empty())
	{
		setState("yuru");
		if ( (SDL_GetTicks() - lastUpdate) > (1000 / speed) )
		{
			temp = target.front();
			// ne tarafa bakacagiz?
			if ( (wx > temp.x) && (wy == temp.y) )
				setYon(W);
			else if ( (wx > temp.x) && (wy > temp.y) )
				setYon(NW);
			else if ( (wx > temp.x) && (wy < temp.y) )
				setYon(SW);
			else if ( (wx < temp.x) && (wy == temp.y) )
				setYon(E);
			else if ( (wx < temp.x) && (wy > temp.y) )
				setYon(NE);
			else if ( (wx < temp.x) && (wy < temp.y) )
				setYon(SE);
			else if ( (wx == temp.x) && (wy > temp.y) )
				setYon(N);
			else if ( (wx == temp.x) && (wy < temp.y) )
				setYon(S);
			
			wx = temp.x;
			wy = temp.y;
			posx = wx / 32;
			posy = wy / 32;
			target.pop_front();
			
			lastUpdate = SDL_GetTicks();
		}
	}
	else 
	{
		if (!commandList.empty())
		{
			string tstate = commandList.front();
			if (tstate == "yuru")
			{
				commandList.pop_front();
				setState("dur");
			}
			else if (tstate == "vur")
			{
				commandList.pop_front();
				setState("vur");
			}
		}
	}
}

