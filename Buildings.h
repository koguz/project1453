#ifndef BUILDINGS__H__
#define BUILDINGS__H__

#include <iostream>
#include <string>
#include "BaseBuilding.h"
#include "Technologies.h"
#include "Units.h"
#include "Player.h"

using namespace std;

class Ev:public BaseBuilding
{
	public:
	Ev();
	Ev(SDL_Surface *screen, Player *p);
};


class SehirMerkezi:public BaseBuilding
{
	public:
	int state;
	SehirMerkezi();
	SehirMerkezi(SDL_Surface *screen, Player *p);
	SDLCommandButton* createKoylu;
};

class AskerOcagi:public BaseBuilding
{
	public:
	AskerOcagi();
	AskerOcagi(SDL_Surface *screen, Player *p);
};

class Demirci:public BaseBuilding
{
	public:
	Demirci();
	Demirci(SDL_Surface *screen, Player *p);
};

#endif
