#ifndef COST__H__
#define COST__H__

#include <iostream>
#include <string>
#include "Resources.h"

using namespace std;

class Cost
{
	private:
	Wood WoodCost;
	Food FoodCost;
	Stone StoneCost;
	
	public:
	Cost();
	Cost(Wood wc, Food fc, Stone sc);
	Cost(int wc, int fc, int sc);
	bool compare(Wood wc, Food fc, Stone sc);
	
	Wood getWood() { return WoodCost; }
	Food getFood() { return FoodCost; }
	Stone getStone() { return StoneCost; }
	
	int getWoodAmount() { return WoodCost.getAmount(); }
	int getFoodAmount() { return FoodCost.getAmount(); }
	int getStoneAmount() { return StoneCost.getAmount(); }
	
	friend bool operator==(Cost &x, Cost &y);
};

#endif

