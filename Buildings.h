#ifndef BUILDINGS__H__
#define BUILDINGS__H__

#include <iostream>
#include <string>
#include "BaseBuilding.h"
#include "Technologies.h"

using namespace std;

class Ev:public BaseBuilding
{
	public:
	Ev(SDL_Surface *screen);
};


class SehirMerkezi:public BaseBuilding
{
	public:
	int state;
	SehirMerkezi(SDL_Surface *screen);
};

class AskerOcagi:public BaseBuilding
{
	public:
	AskerOcagi(SDL_Surface *screen);
};

class Demirci:public BaseBuilding
{
	public:
	Demirci(SDL_Surface *screen);
};

#endif
