#ifndef BASEOBJECT__H__
#define BASEOBJECT__H__

#include <iostream>
#include <string>
#include <vector>
#include "Headers.h"
#include "Cost.h"

/* BaseObject is the parent of three main objects;
 * Technology, Unit and Building.
 * These three have a lot in common, like the
 * Cost or Requirements list. So they share this
 * parent 
 */

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

