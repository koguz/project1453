#include "Buildings.h"

Ev::Ev():BaseBuilding("Ev")
{
	hitpoints = 400;
	buildRate = 50;
	sight = 4;
	size = 2;
	addReq("Temel Teknoloji");
	faction = "Osmanlı";
	cost = Cost(200, 0, 200);
}

SehirMerkezi::SehirMerkezi():BaseBuilding("Şehir Merkezi (I)")
{
	state = 1;
	hitpoints = 1000;
	sight = 8;
	size = 4;
	addReq("Temel Teknoloji");
	faction = "Osmanlı";
	cost = Cost(400, 0, 400);
}

AskerOcagi::AskerOcagi():BaseBuilding("Asker Ocağı")
{
	hitpoints = 800;
	sight= 6;
	size = 3;
	addReq("Temel Teknoloji");
	faction = "Osmanlı";
	cost = Cost(200, 0, 400);
}

Demirci::Demirci():BaseBuilding("Demirci")
{
	hitpoints = 600;
	sight = 4;
	size = 3;
	addReq("Temel Teknoloji");
	faction = "Osmanlı";
	cost = Cost(0, 0, 500);
}

