#include "Cost.h"

Cost::Cost()
{
}

Cost::Cost(Wood wc, Food fc, Stone sc)
{
	set(wc.getAmount(), fc.getAmount(), sc.getAmount());
}

Cost::Cost(int wc, int fc, int sc)
{
	set(wc, fc, sc);
}

void Cost::set(int w, int f, int s)
{
	WoodCost.setAmount(w);
	FoodCost.setAmount(f);
	StoneCost.setAmount(s);
}

bool Cost::compare(Wood wc, Food fc, Stone sc)
{
	return ( (WoodCost.getAmount() <= wc.getAmount()) && (FoodCost.getAmount() <= fc.getAmount()) && (StoneCost.getAmount() <= sc.getAmount()) );
}

bool Cost::compare(int wc, int fc, int sc)
{
	return ( (WoodCost.getAmount() <= wc) && (FoodCost.getAmount() <= fc) && (StoneCost.getAmount() <= sc) );
}


Wood Cost::getWood() { return WoodCost; }
Food Cost::getFood() { return FoodCost; }
Stone Cost::getStone() { return StoneCost; }
int Cost::getWoodAmount() { return WoodCost.getAmount(); }
int Cost::getFoodAmount() { return FoodCost.getAmount(); }
int Cost::getStoneAmount() { return StoneCost.getAmount(); }



