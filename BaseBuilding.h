#ifndef BASEBUILDING__H__
#define BASEBUILDING__H__

#include <iostream>
#include <string>
#include <vector>
#include "BaseObject.h"

// NOTE - bu binaların "build queue'su olabilir...

using namespace std;

class BaseBuilding:public BaseObject
{
	protected:
	int hitpoints;
	int currentHp;
	int sight;
	int size;
	
	public:
	BaseBuilding(string n);
};




#endif

