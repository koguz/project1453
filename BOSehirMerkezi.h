#ifndef BO__SMERKEZ__H__
#define BO__SMERKEZ__H__

#include "BaseBuilding.h"
#include "SDLCommandButton.h"
#include "Player.h"
#include "UOKoylu.h"

using namespace std;

class SehirMerkezi:public BaseBuilding
{
	public:
	int state;
	SehirMerkezi(SDL_Surface *screen=0, Player *p=0);
	~SehirMerkezi();
	SDLCommandButton* btnKoylu;
	void createKoylu();
	
	static SDL_Surface* spriteImg;
};

#endif
