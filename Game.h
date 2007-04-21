#ifndef GAME__H__
#define GAME__H__

#include <iostream>
#include <string>
#include <sstream>
#include "Player.h"
#include "SDLMusic.h"
#include "SDLCheckBox.h"
#include "SDLCombo.h"

using namespace std;


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
	SDLWidget *tileCim, *tileSari, *tileAgac, *tileToprak, *tileDeniz;//, *commandList;
	SDLMusic *muse;
	
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
