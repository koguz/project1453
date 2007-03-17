#ifndef UO__KOYLU__H__
#define UO__KOYLU__H__

#include "BaseUnit.h"
#include "BOEv.h"

class Koylu:public BaseUnit
{
	public:
	Koylu(SDL_Surface *scr=0, Player *p=0);
	~Koylu();
	
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
	static SDL_Surface* spriteImg;
	void setCommandCalis();
};

#endif
