#ifndef UB__SERF__H__
#define UB__SERF__H__

#include "BaseUnit.h"

class Serf:public BaseUnit
{
	public:
	Serf();
	Serf(SDL_Surface *scr, Player *p);
	~Serf();
};

#endif
