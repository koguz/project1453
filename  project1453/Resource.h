#ifndef RESOURCE__H__
#define RESOURCE__H__

#include <iostream>
#include <string>

using namespace std;

class Resource
{
	protected:
	string resourceName;
	int amount;
	
	public:
	Resource(string n);
	Resource(string n, int a);
	
	void setAmount(int a) { amount = a; }
	int getAmount() { return amount; }
	string getName() { return resourceName; }
	
	friend bool operator==(Resource &x, Resource &y);
};

#endif

