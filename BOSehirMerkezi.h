#ifndef BO__SMERKEZ__H__
#define BO__SMERKEZ__H__

#include "BaseBuilding.h"
#include "SDLCommandButton.h"
#include "Player.h"
#include "UOKoylu.h"

using namespace std;


/* The city center is where more villagers come from. 
 * It also provides accomodation for 5 units 
 */
class SehirMerkezi:public BaseBuilding
{
	public:
	int state;
	SehirMerkezi();
	SehirMerkezi(SDL_Surface *screen, Player *p);
	~SehirMerkezi();
	SDLCommandButton *btnKoylu, *resim;
	void createKoylu();
	
	static SDL_Surface* spriteImg;
};

#endif
