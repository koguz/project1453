#ifndef BASEOBJECT__H__
#define BASEOBJECT__H__

#include <iostream>
#include <string>
#include <vector>
#include "Headers.h"
#include "Cost.h"

class BaseObject
{
	public:
// 	BaseObject();
	BaseObject(string n);
	enum ObjectType { UNIT, BUILDING, TECH };
	ObjectType getType() { return tip; }
	Cost getCost() { return cost; }
	string getName() { return name; }
	string getFaction() { return faction; }
	vector<string> getReqs() { return reqList; }
	void addReq(string r);
	int getCurHp() { return currentHp; }
	int getMaxHp() { return hitpoints; }
	bool build();
	void instantBuild();
	
	friend bool operator==(BaseObject &a, BaseObject &b);
	
	protected:
	int hitpoints;
	int currentHp;
	string name;
	bool built;
	int buildRate;
	Uint32 sayac;
	vector<string> reqList;
	string faction;
	ObjectType tip;
	Cost cost;
};

#endif

