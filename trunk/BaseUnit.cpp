#include "BaseUnit.h"

BaseUnit::BaseUnit(SDL_Surface *scr, string n):BaseObject(n), BaseGraphicObject(scr)
{
	hitpoints = 20; // hit points
	armor = 1; // over 10
	damage = 10; // minimum damage
	range = 1; // minimum range
	sight = 4; // radius of sight circle
	speed = 10; // below average speed
	morale = 50; // over 100
	xp = 0; // no xp
	kills = 0; // no kills
	
	waitingCommand = "yok";
	waiting = false;
}

SDL_Rect BaseUnit::getFrame()
{
	sprites[yon].setState(curState);
	SDL_Rect r = sprites[yon].getFrame();
	return r;
}

void BaseUnit::actionDur()
{
	target.clear();
	commandList.clear();
	setState("dur");
}

void BaseUnit::setCommandYuru()
{
	waitingCommand = "yuru";
	waiting = true;
}

void BaseUnit::moveToTarget(int tx, int ty)
{
	target.clear();
	int smx = posx;
	int smy = posy;
	tx -= cx;
	ty -= cy;
	Coordinates temp;
	
	if (abs(tx-smx) > abs(ty-smy))
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

void BaseUnit::update()
{
	Coordinates temp;
	if (!target.empty())
	{
		setState("yuru");
		temp = target.front();
		// ne tarafa bakacagiz?
		if ( (posx > temp.x) && (posy == temp.y) )
			setYon(W);
		else if ( (posx > temp.x) && (posy > temp.y) )
			setYon(NW);
		else if ( (posx > temp.x) && (posy < temp.y) )
			setYon(SW);
		else if ( (posx < temp.x) && (posy == temp.y) )
			setYon(E);
		else if ( (posx < temp.x) && (posy > temp.y) )
			setYon(NE);
		else if ( (posx < temp.x) && (posy < temp.y) )
			setYon(SE);
		else if ( (posx == temp.x) && (posy > temp.y) )
			setYon(N);
		else if ( (posx == temp.x) && (posy < temp.y) )
			setYon(S);
		
		posx = temp.x;
		posy = temp.y;
		
		target.pop_front();
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

