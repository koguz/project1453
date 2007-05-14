#ifndef BASEOBJECT__H__
#define BASEOBJECT__H__

#include <iostream>
#include <string>
#include <vector>
#include "Headers.h"
#include "Cost.h"

// temel olan 3 nesne: tech, bina, birim
class BaseObject
{
	public:
	BaseObject();
	BaseObject(string n);
	~BaseObject();
	enum ObjectType { UNIT, BUILDING, TECH };
	ObjectType getType();
	Cost getCost();
	string getName();
	string getFaction();
	vector<string> getReqs();
	void addReq(string r);
	void addCurHp(int v);
	int getCurHp();
	int getMaxHp();
	bool build();
	bool tam();
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

