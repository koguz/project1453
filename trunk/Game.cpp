#include "Game.h"

bool operator==(Resource &a, Resource &b)
{
	return (a.getAmount() == b.getAmount());
}

bool operator==(Cost &a, Cost &b)
{
	return ( (a.WoodCost==b.WoodCost) && (a.FoodCost==b.FoodCost) && (a.StoneCost==b.StoneCost) );
}

bool operator==(BaseObject &a, BaseObject &b)
{
	return (a.getName()==b.getName());
}

Game::Game(SDL_Surface *scr, string userFaction, short ai, string mapName)
{
	screen = scr;
	/*
	mapname ve ai parametreleri şimdilik yok
	userFaction'a göre ilk adamı Köylü ya da 
	Bizans'ın Köylü'ye denk birimi olarak
	başlatacağız..
	
	önce haritayı şimdilik yaratalım
	
	haritada aynı zamanda start position da olması lazım...
	
	0 - çim
	1 - sari çim
	2 - agac
	3 - toprak
	4 - daglik
	5 - deniz
	6 - kesik agac
	*/
	
	
	// öylesine harita
	{
		for(int i=0;i<20;i++)
		{
			for(int j=0;j<18;j++)
			{
				map[i][j] = 0;
			}
		}
		
		for(int i=0;i<6;i++)
		{
			for(int j=0;j<6;j++)
			{
				if ((i==5) || (j==5))
					map[i][j] = 3;
				else
					map[i][j] = 5;
			}
		}
		
		for(int i=15;i<20;i++)
		{
			for(int j=15;j<18;j++)
			{
				map[i][j] = 2;
			}
		}
		
		for(int i=0;i<4;i++)
		{
			for(int j=9;j<18;j++)
			{
				map[i][j] = 1;
			}
		}
	}
	
	
	human = new Player(screen, userFaction, 1000, 1000, 1000);
	human->buildStartingUnits(360, 450); // FIXME sabit? haritadan al
	
	string cpuFaction;
	if (userFaction == "Osmanlı")
		cpuFaction = "Bizans";
	else if (userFaction == "Bizans")
		cpuFaction = "Osmanlı";
		
	cpu = new Player(screen, cpuFaction, 1000, 1000, 1000);
	cpu->buildStartingUnits(360, 75); // FIXME sabit? haritadan al
	
	ui = new SDLScreen(screen);
	
	SDLWidget *arka = new SDLWidget("ui/arkaOyun.jpg");
	arka->setPosition(0, 0);
	ui->addWidget(arka);
	
	SDLWidget *woodIcon = new SDLWidget("ui/wood.jpg");
	woodIcon->setPosition(2, 2);
	ui->addWidget(woodIcon);
	
	SDLWidget *foodIcon = new SDLWidget("ui/food.jpg");
	foodIcon->setPosition(118, 2);
	ui->addWidget(foodIcon);
	
	SDLWidget *stoneIcon = new SDLWidget("ui/stone.jpg");
	stoneIcon->setPosition(234, 2);
	ui->addWidget(stoneIcon);
	
	SDLWidget *houseIcon = new SDLWidget("ui/house.jpg");
	houseIcon->setPosition(350, 2);
	ui->addWidget(houseIcon);
	
	lblWood = new SDLLabel(human->getWoodAmount(), 12);
	lblWood->setPosition(22, 2);
	ui->addWidget(lblWood);
	
	lblFood = new SDLLabel(human->getFoodAmount(), 12);
	lblFood->setPosition(138, 2);
	ui->addWidget(lblFood);
	
	lblStone = new SDLLabel(human->getStoneAmount(), 12);
	lblStone->setPosition(254, 2);
	ui->addWidget(lblStone);
	
	lblHouse = new SDLLabel("?/?");
	lblHouse->setPosition(370, 2);
	ui->addWidget(lblHouse);
	
	tileCim = new SDLWidget("graphics/terrain/yesil.png");
	tileSari = new SDLWidget("graphics/terrain/sariYesil.png");
	tileAgac = new SDLWidget("graphics/terrain/agac.png");
	tileToprak = new SDLWidget("graphics/terrain/toprak.png");
	tileDeniz = new SDLWidget("graphics/terrain/deniz.png");
	
	commands = new SDLScreen(screen);
	muse = new SDLMusic("wavs/music/track02.ogg");
	muse->play();
}

Game::~Game()
{
	delete ui;
	delete commands;
	
	delete human;
	delete cpu;
	
	delete tileCim;
	delete tileSari;
	delete tileAgac;
	delete tileToprak;
	delete tileDeniz;
	delete muse;
}


void Game::update()
{
	checkMusic();
	human->update();
	lblWood->setText(human->getWoodAmount());
	lblFood->setText(human->getFoodAmount());
	lblStone->setText(human->getStoneAmount());
	// TODO cpu->update() AI yazılınca
}

void Game::checkMusic()
{
	if (muse->isPlaying())
		return;
	
	// NOTE bunlar sonra müzikler gelince eklenecek
// 	int a = rand() % 4;
// 	switch(a)
// 	{
// 		case 0:
// 			muse->loadFile("wavs/music/track04.ogg");
// 			break;
// 		case 1:
// 			muse->loadFile("wavs/music/track05.ogg");
// 			break;
// 		case 2:
// 			muse->loadFile("wavs/music/track06.ogg");
// 			break;
// 		case 3:
// 			muse->loadFile("wavs/music/track07.ogg");
// 			break;
// 	}
	muse->play();
	
}

void Game::display()
{
	ui->display();
	commands->display(); // NOTE oyun içi menüsü belki?
	
	// harita
	int px, py;
	for(int i=0;i<20;i++)
	{
		for(int j=0;j<18;j++)
		{
			px = 2 + (i*32);
			py = 20 + (j*32);
			switch(map[i][j])
			{
				case 0:
					tileCim->setPosition(px, py);
					tileCim->drawWidget(screen);
					break;
				case 1:
					tileSari->setPosition(px, py);
					tileSari->drawWidget(screen);
					break;
				case 2:
					tileAgac->setPosition(px, py);
					tileAgac->drawWidget(screen);
					break;
				case 3:
					tileToprak->setPosition(px, py);
					tileToprak->drawWidget(screen);
					break;
				case 5:
					tileDeniz->setPosition(px, py);
					tileDeniz->drawWidget(screen);
					break;
			}
		}
	}	
}

void Game::eventHandler(SDL_Event *event)
{
	ui->eventHandler(event);
	commands->eventHandler(event);
	human->eventHandler(event);
}


