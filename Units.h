#ifndef UNITS__H__
#define UNITS__H__

#include "BaseUnit.h"
#include "Technologies.h"
#include "Buildings.h"

class Koylu:public BaseUnit
{
	public:
	Koylu(SDL_Surface *scr=0, Player *p=0);
	
	virtual void defaultAction(int tx, int ty)
	{
		moveToTarget(tx, ty);
	}
	
	virtual void issueCommand(int x, int y)
	{
		if (waitingCommand == "yuru")
		{
			waiting = false;
			moveToTarget(x, y);
		}
	}
	
	void setCommandCalis();
};

class Azab:public BaseUnit
{
	public:
	Azab(SDL_Surface *scr=0, Player *p=0);
};

class Piyade:public BaseUnit
{
	public:
	Piyade(SDL_Surface *scr=0, Player *p=0);
};

class Serf:public BaseUnit
{
	public:
	Serf(SDL_Surface *scr=0, Player *p=0);
};

#endif
