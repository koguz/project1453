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
	bool compare(int w, int f, int s);
	
	Wood getWood();
	Food getFood();
	Stone getStone();
	
	int getWoodAmount();
	int getFoodAmount();
	int getStoneAmount();
	
	void set(int w, int f, int s);
	
	friend bool operator==(Cost &x, Cost &y);
};

#endif

