#ifndef RESOURCE__H__
#define RESOURCE__H__

#include <iostream>
#include <string>

using namespace std;

/* Base class for Wood, Food and Stone */
class Resource
{
	protected:
	string resourceName;
	int amount;
	
	public:
	Resource(string n);
	Resource(string n, int a);
	
	void setAmount(int a);
	int getAmount();
	string getName();
	
	friend bool operator==(Resource &x, Resource &y);
};

#endif

