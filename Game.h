#ifndef GAME__H__
#define GAME__H__

#include <iostream>
#include <string>
#include <sstream>
#include "SDLCursor.h"
#include "Player.h"
#include "SDLMusic.h"
#include "SDLCheckBox.h"
#include "SDLCombo.h"
#include "Map.h"

using namespace std;

/* Game represents a game with new players, goals and a map. There
 * can only be one game object at a time. 
 */

class Game
{
	public:
	SDLScreen *ui, *current, *commands, *sesayar, *eminmi;
	SDLLabel *lblemin;
	SDLButton *evet, *hayir;
	SDLButton *menu, *btnSes, *devam, *anamenu, *cikis, *sesonceki, *seskaydet;
	SDLWidget *menuArka, *arka2, *arka3;
	SDLLabel *menuTitle, *sesTitle, *muzik;
	SDLCheckBox *monoff;
	SDLCombo *mvol;
	SDLLabel *lblWood, *lblFood, *lblStone, *lblHouse;
	SDLMusic *muse;
	Map *harita;
	
	Player *human, *cpu;
	
	SDL_Surface *screen;
	int map[20][18];
	
	Game(SDL_Surface *scr, string userFaction, short ai, string mapName);
	~Game();
	
	void display();
	void eventHandler(SDL_Event *event);
	void update();
	void checkMusic();
	void displayMenu();
	void closeMenu();
	void displayVolume();
	void saveVolSets();
	int sonMu();
	void endGame();
	void quitGame();
	void quitToSystem();
	void quitAll();
	
	protected:
	bool running;
	int son;
};


#endif
