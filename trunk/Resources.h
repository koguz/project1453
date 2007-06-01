#ifndef RESOURCESALL__H__
#define RESOURCESALL__H__

#include "Resource.h"

/* Resources Wood, Food and Stone */

class Wood:public Resource
{
	public:
	Wood();
	Wood(int a);
};

class Food:public Resource
{
	public:
	Food();
	Food(int a);
};

class Stone:public Resource
{
	public:
	Stone();
	Stone(int a);
};

#endif
