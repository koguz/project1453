#ifndef PLAYER__H__
#define PLAYER__H__

#include <iostream>
#include <string>
#include <list>
#include <vector>

#include "Cost.h"
#include "Buildings.h"
#include "Units.h"
#include "Technologies.h"

using namespace std;

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
	bool isMultipleSelecting() { return (drawing && dragging); }
	bool isValidSelection();
	
	// 
	void update();
	void buildStartingUnits(int x, int y);
	
	string getFaction() { return faction; }
	int getWoodAmount() { return wood.getAmount(); }
	int getFoodAmount() { return food.getAmount(); }
	int getStoneAmount() { return stone.getAmount(); }
	
	// 
	bool haveReqs(BaseObject* o);
	
	void addCost(Cost a);
	void subtractCost(Cost a);
	
	void eventHandler(SDL_Event *event);
	
// 	// osmanlı birimleri
// 	void createKoylu();
// 	void createAzab();
// 	void createPiyade();
// 	
// 	// osmanlı binaları
// 	
// 	// bizans birimleri
// 	void createSerf();
};

#endif
