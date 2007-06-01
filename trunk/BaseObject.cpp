#include "BaseObject.h"

BaseObject::BaseObject()
{
}

BaseObject::ObjectType BaseObject::getType()  { return tip; }
Cost BaseObject::getCost() { return cost; }
string BaseObject::getName() { return name; }
string BaseObject::getFaction() { return faction; }
vector<string> BaseObject::getReqs() { return reqList; }
int BaseObject::getCurHp() { return currentHp; }
int BaseObject::getMaxHp() { return hitpoints; }

BaseObject::BaseObject(string n)
{
	name = n;
	built = false;
	sayac = SDL_GetTicks();
	currentHp = 0;
}

BaseObject::~BaseObject() {}

bool BaseObject::tam()
{
	return (hitpoints == currentHp);
}

void BaseObject::addReq(string r)
{
	reqList.push_back(r);
}

void BaseObject::addCurHp(int v)
{
	// Negative values can also be added
	currentHp += v;
	if (currentHp > hitpoints)
		currentHp = hitpoints;
	if (currentHp < 0)
		currentHp = 0;
}

bool BaseObject::build()
{
	if (built) return true;
	Uint32 now = SDL_GetTicks();
	if (now - sayac > buildRate)
	{
		sayac = SDL_GetTicks();
		currentHp++;
		if (currentHp == hitpoints)
		{
			built = true;
			return true;
		}
		else return false;
	}
	return false;
}

void BaseObject::instantBuild()
{
	currentHp = hitpoints;
	built = true;
}
