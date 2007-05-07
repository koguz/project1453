#ifndef PLAYER__H__
#define PLAYER__H__

#include <iostream>
#include <string>
#include <vector>
#include <deque>

#include "BOEv.h"
#include "BOSehirMerkezi.h"
#include "TTemelTech.h"
#include "UOKoylu.h"
#include "UBSerf.h"
#include "SDLTextView.h"

using namespace std;

class Player
{
	public:
	Player();
	Player(SDL_Surface *scr, string faction, int w, int f, int s);
	~Player();
	
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
	void addUnit(BaseUnit* b);
	void addTech(Tech* t);
	void addBuilding(BaseBuilding* b);
	void addMessage(string m);
	void hepsiYuru();
	void hepsiDur();
	
	bool yeniKoylu();
	bool multipleSelect;
 	
 	private:
 	vector<BaseUnit*> units;
 	vector<BaseBuilding*> buildings;
	vector<Tech*> techs;
	deque<string> messages;
	
	SDLScreen *cok;
	SDLCommandButton *yuru, *dur;
	SDLTextView *clist; // kimler secilmis, liste...
	
	Uint32 lastMsgTime;
	string faction;
	SDL_Surface *screen;
	bool drawing;
	bool dragging;
	
	Wood wood;
	Food food;
	Stone stone;
};

#endif