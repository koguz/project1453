#ifndef BUILDINGS__H__
#define BUILDINGS__H__

#include <iostream>
#include <string>
#include "BaseBuilding.h"
#include "Technologies.h"

using namespace std;

class Ev:public BaseBuilding
{
	public:
	Ev();
};


class SehirMerkezi:public BaseBuilding
{
	public:
	int state;
	SehirMerkezi();
};

class AskerOcagi:public BaseBuilding
{
	public:
	AskerOcagi();
};

class Demirci:public BaseBuilding
{
	public:
	Demirci();
};

#endif
