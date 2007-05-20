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
	areWeThereYet = true;
	calc = false;
	
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
	targetTiles.clear();
// 	commandList.clear();
	setState("dur");
}

void BaseUnit::setCommandYuru()
{
	SDLCursor::setCursorTarget();
	SDLCursor::locked = true;
	waitingCommand = "yuru";
	waiting = true;
}

void BaseUnit::cancelBaseActions()
{
	SDLCursor::locked = false;
	SDLCursor::setCursorMain();
	waiting = false;
	waitingCommand = "yok";
}

int BaseUnit::getSight()
{
	return sight;
}


bool BaseUnit::onScreen(int x1, int x2, int y1, int y2)
{
	int px1 = wx;
	int py1 = wy;
	int px2 = px1 + 32;
	int py2 = py1 + 32;
	
	return
	(
		(
			((px1 >= x1) && (px1 < x2)) ||
			((px2 >= x1) && (px2 < x2)) 
		) && 
		(
			((py1 >= y1) && (py1 < y2)) ||
			((py2 >= y1) && (py2 < y2)) 
		)
	);
}

void BaseUnit::draw(SDL_Rect s, SDL_Rect d)
{
	SDL_Rect src = getFrame();
	src.x += s.x + hotspot.x;
	src.y += s.y + hotspot.y;
	src.w = s.w;
	src.h = s.h;
	SDL_BlitSurface(getImg(), &src, screen, &d);
	if (isSelected())
	{
		SDL_Rect m = d;
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
	
// 	commandList.push_back("yuru");
// 	cout << "base: "  << commandList.size() << endl;
}

void BaseUnit::moveToTarget(int tx, int ty)
{
	if ( (tx == posx) && (ty == posy) ) // oyalama beni :)
		return;
	SDLCursor::locked = false;
	SDLCursor::setCursorMain();
	tax = tx;
	tay = ty;
	areWeThereYet = false;
	targetTiles.clear();
	target.clear();
// 	commandList.push_back("yuru");
// 	calWalkTile(tx, ty);
}

bool BaseUnit::buVarMi(int a, int b)
{
	if (a == posx && b == posy)
		return true;
// 	if (targetTiles.size() > 0)
// 	{
		list<Coordinates>::iterator i;
		for(i=targetTiles.begin();i != targetTiles.end(); i++)
		{
			if ((*i).x == a && (*i).y == b)
				return true;
		}
// 	}
	return false;
}

void BaseUnit::yoneBak(int x, int y)
{
	if ( (posx > x) && (posy == y) )
		setYon(W);
	else if ( (posx > x) && (posy > y) )
		setYon(NW);
	else if ( (posx > x) && (posy < y) )
		setYon(SW);
	else if ( (posx < x) && (posy == y) )
		setYon(E);
	else if ( (posx < x) && (posy > y) )
		setYon(NE);
	else if ( (posx < x) && (posy < y) )
		setYon(SE);
	else if ( (posx == x) && (posy > y) )
		setYon(N);
	else if ( (posx == x) && (posy < y) )
		setYon(S);
}

void BaseUnit::lookDirection(int x, int y)
{
	if ( (wx > x) && (wy == y) )
		setYon(W);
	else if ( (wx > x) && (wy > y) )
		setYon(NW);
	else if ( (wx > x) && (wy < y) )
		setYon(SW);
	else if ( (wx < x) && (wy == y) )
		setYon(E);
	else if ( (wx < x) && (wy > y) )
		setYon(NE);
	else if ( (wx < x) && (wy < y) )
		setYon(SE);
	else if ( (wx == x) && (wy > y) )
		setYon(N);
	else if ( (wx == x) && (wy < y) )
		setYon(S);
}

void BaseUnit::doUpdate()
{
	if (selected)
	{
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
	
// 	if (commandList.size() > 0)
// 	{
// 		string tstate = commandList.front();
// 		if (tstate == "yuru")
// 		{
// 			if ( (SDL_GetTicks() - lastUpdate) > (1000 / speed) )
// 			{
// 				Coordinates temp;
// 				temp = target.front();
// 				// ne tarafa bakacagiz?
// 				lookDirection(temp.x, temp.y);
// 				
// 				wx = temp.x;
// 				wy = temp.y;
// 				posx = wx / 32;
// 				posy = wy / 32;
// 				target.pop_front();
// 				
// 				lastUpdate = SDL_GetTicks();
// 			}	
// 		}
// 	}
	
	if (!target.empty())
	{
		setState("yuru");
		if ( (SDL_GetTicks() - lastUpdate) > (1000 / speed) )
		{
			Coordinates temp;
			temp = target.front();
			// ne tarafa bakacagiz?
			lookDirection(temp.x, temp.y);
			
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
// 		cout << "commandList size: " << commandList.size() << endl;
// 		string tstate = commandList.front();
		if (curState == "yuru")
		{
// 			commandList.pop_front();
			setState("dur");
		}
// 		if (!commandList.empty())
// 		{
// 			string tstate = commandList.front();
// 			if (tstate == "yuru")
// 			{
// 				commandList.pop_front();
// 				setState("dur");
// 			}
// 			else if (tstate == "vur")
// 			{
// 				commandList.pop_front();
// 				setState("vur");
// 			}
// 		}
	}
}

