#ifndef BUILDINGS__H__
#define BUILDINGS__H__

#include <iostream>
#include <string>
// #include "Headers.h"
#include "BaseBuilding.h"
// #include "Technologies.h"
#include "Units.h"
#include "Player.h"
#include "SDLCommandButton.h"

// class Player;

using namespace std;

class Ev:public BaseBuilding
{
	public:
	Ev(SDL_Surface *screen=0, Player *p=0);
};


class SehirMerkezi:public BaseBuilding
{
	public:
	int state;
	SehirMerkezi(SDL_Surface *screen=0, Player *p=0);
	SDLCommandButton* btnKoylu;
	void createKoylu();
};

class AskerOcagi:public BaseBuilding
{
	public:
	AskerOcagi(SDL_Surface *screen=0, Player *p=0);
};

class Demirci:public BaseBuilding
{
	public:
	Demirci(SDL_Surface *screen, Player *p);
};

#endif
