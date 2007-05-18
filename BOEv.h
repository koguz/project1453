#ifndef BO__EV__H__
#define BO__EV__H__

#include "BaseBuilding.h"
#include "SDLCommandButton.h"

using namespace std;

class Ev:public BaseBuilding
{
	public:
	Ev();
	Ev(SDL_Surface *screen, Player *p);
	~Ev();
	static SDL_Surface* spriteImg;
	SDLCommandButton *resim;
};

#endif
