#ifndef GAME__H__
#define GAME__H__

#include <iostream>
#include <string>
#include <sstream>
#include "SDLScreen.h"
#include "Resources.h"
#include "Player.h"
#include "Cost.h"
#include "Tech.h"
#include "BaseBuilding.h"

using namespace std;


class Game
{
	public:
	SDLScreen *ui; // for general ui, displaying player status etc.
	SDLScreen *commands; // for units, which can change when a unit/building selected...
	SDLLabel *lblWood, *lblFood, *lblStone, *lblHouse;
	SDLWidget *tileCim, *tileSari, *tileAgac, *tileToprak, *tileDeniz, *commandList;
	
	Player *human, *cpu;
	
	SDL_Surface *screen;
	int map[20][18];
	
	Game(SDL_Surface *scr, string userFaction, short ai, string mapName);
	
	void display();
	void eventHandler(SDL_Event *event);
	void update();
};


#endif
