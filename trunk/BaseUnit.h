#ifndef BASEUNIT__H__
#define BASEUNIT__H__

#include <iostream>
#include <string>
#include <list>
#include "Headers.h"
#include "BaseObject.h"
#include "BaseGraphicObject.h"
#include "SDLScreen.h"
#include "Sprite.h"

using namespace std;

class BaseUnit:public BaseObject, public BaseGraphicObject
{
	public: 
	BaseUnit(SDL_Surface *scr, string n);
	enum direction { N=0, NE=1, E=2, SE=3, S=4, SW=5, W=6, NW=7 };
	void setState(string state) { curState = state; }
	void setYon(direction d) { yon = d; }
	bool isWaiting() { return waiting; }
	
	virtual void issueCommand(int x, int y) { cout << "base unit issueCommand is called, err??" << endl; }
	virtual void defaultAction(int tx, int ty) { cout << "base unit default action is called, err?" << endl; }
	
	virtual SDL_Surface* getImg()
	{
		sprites[yon].setState(curState);
		return sprites[yon].getImg();
	}
	
	void moveToTarget(int tx, int ty);
	void actionDur();
	void setCommandYuru();
	list<Coordinates> target;
	list<string>commandList;
	
	void update();
	SDL_Rect getFrame();
	SDL_Rect hotspot;

	protected:
	int armor;
	int damage;
	int range;
	int sight;
	int speed;
	int morale;
	int xp;
	int kills;
	
	// grafikler için
	string waitingCommand;
	bool waiting;
	direction yon;
	string curState;
	Sprite sprites[8];
		
};



#endif
