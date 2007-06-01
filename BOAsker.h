#ifndef BO__ASKERO__H__
#define BO__ASKERO__H__

#include "BaseBuilding.h"
#include "SDLCommandButton.h"
#include "UOPiyade.h"
#include "UOYeniceri.h"
#include "Player.h"

using namespace std;

/* The building for the Ottoman Empire which 
 * creates new units for the army
 */
class AskerOcagi:public BaseBuilding
{
	public:
	AskerOcagi();
	AskerOcagi(SDL_Surface *screen, Player *p);
	~AskerOcagi();
	static SDL_Surface* spriteImg;
	SDLCommandButton *resim, *piyade, *yeniceri;
	void createPiyade();
	void createYeniceri();
};

#endif
