#ifndef PLAYER__H__
#define PLAYER__H__

#include <iostream>
#include <string>
#include <list>
#include <vector>
#include "Buildings.h"
// #include "callback.h"
// #include "Headers.h"
// #include "Cost.h"

// #include "Units.h"
// #include "Technologies.h"

using namespace std;

class Koylu;

class Player
{
	private:
	list<BaseObject*> nesneler;
	string faction;
	SDL_Surface *screen;
	bool drawing;
	bool dragging;
	
	Wood wood;
	Food food;
	Stone stone;
	
	public:
	Player();
	Player(SDL_Surface *scr, string faction, int w, int f, int s);
	
	int rsx1, rsx2, rsy1, rsy2;
	bool isMultipleSelecting();
	bool isValidSelection();
	
	void update();
	void buildStartingUnits(int x, int y);
	
	string getFaction();
	int getWoodAmount();
	int getFoodAmount();
	int getStoneAmount();
	
	bool haveReqs(BaseObject* o);
	void addCost(Cost a);
	void subtractCost(Cost a);
	void eventHandler(SDL_Event *event);
	void addObject(BaseObject* b);
	
	Koylu* yeniKoylu();
 	void createKoylu(bool instant);
};

#endif
