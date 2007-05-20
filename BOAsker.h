#ifndef BO__ASKERO__H__
#define BO__ASKERO__H__

#include "BaseBuilding.h"
#include "SDLCommandButton.h"

using namespace std;

class AskerOcagi:public BaseBuilding
{
	public:
	AskerOcagi();
	AskerOcagi(SDL_Surface *screen, Player *p);
	~AskerOcagi();
	static SDL_Surface* spriteImg;
	SDLCommandButton *resim;
};

#endif
