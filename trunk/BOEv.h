#ifndef BO__EV__H__
#define BO__EV__H__

#include "BaseBuilding.h"

using namespace std;

class Ev:public BaseBuilding
{
	public:
	Ev(SDL_Surface *screen=0, Player *p=0);
};

#endif
