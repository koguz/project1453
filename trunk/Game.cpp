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
	harita = new Map(screen, 70, 70);
	harita->setOrigin(10, 25);
	harita->setPane(630, 566);
	harita->setMiniMapPos(653, 45);
	
	human = new Player(screen, userFaction, 1000, 1000, 1000);
	human->buildStartingUnits(harita->getPx(), harita->getPy());
	
	string cpuFaction;
	if (userFaction == "Osmanlı")
		cpuFaction = "Bizans";
	else if (userFaction == "Bizans")
		cpuFaction = "Osmanlı";
		
	cpu = new Player(screen, cpuFaction, 1000, 1000, 1000);
	cpu->buildStartingUnits(harita->getCpux(), harita->getCpuy());
	
	harita->setPlayers(human, cpu);
	
	Game *me = this;
	
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
	
	menu = new SDLButton("ui/dugme100.jpg", "Menü", 12);
	menu->setPosition(680, 2);
	menu->clicked = makeFunctor((CBFunctor0*)0, *me, &Game::displayMenu);
	ui->addWidget(menu);
	
	commands = new SDLScreen(screen);
	running = true;
	
	menuArka = new SDLWidget("ui/optionPane.jpg");
	menuArka->setPosition(265, 200);
	commands->addWidget(menuArka);
	
	menuTitle = new SDLLabel("Menü", 20);
	menuTitle->setPosition( (800-menuTitle->getWidth())/2, 220);
	commands->addWidget(menuTitle);
	
	devam = new SDLButton("ui/dugme100.jpg", "Oyuna Devam", 11);
	devam->setPosition(350, 260);
	devam->clicked = makeFunctor((CBFunctor0*)0, *me, &Game::closeMenu);
	commands->addWidget(devam);
	
	btnSes = new SDLButton("ui/dugme100.jpg", "Ses Ayarları", 11);
	btnSes->setPosition(350, 285);
	btnSes->clicked = makeFunctor((CBFunctor0*)0, *me, &Game::displayVolume);
	commands->addWidget(btnSes);
	
	anamenu = new SDLButton("ui/dugme100.jpg", "Ana Menü", 11);
	anamenu->setPosition(350, 310);
	anamenu->clicked = makeFunctor((CBFunctor0*)0, *me, &Game::endGame);
	commands->addWidget(anamenu);
	
	cikis = new SDLButton("ui/dugme100.jpg", "Oyundan Çıkış", 11);
	cikis->setPosition(350, 335);
	cikis->clicked = makeFunctor((CBFunctor0*)0, *me, &Game::quitToSystem);
	commands->addWidget(cikis);
	
	sesayar = new SDLScreen(screen);
	
	SDLWidget *arka2 = new SDLWidget("ui/optionPane.jpg");
	arka2->setPosition(265, 200);
	sesayar->addWidget(arka2);
	
	sesTitle = new SDLLabel("Ses Ayarları", 20);
	sesTitle->setPosition( (800-sesTitle->getWidth())/2, 220);
	sesayar->addWidget(sesTitle);
	
	monoff = new SDLCheckBox("Müzikler Açık");
	monoff->setPosition( (800-monoff->getWidth())/2, 260);
	sesayar->addWidget(monoff);
	
	muzik = new SDLLabel("Müzik Seviyesi");
	muzik->setPosition( 300, 285);
	sesayar->addWidget(muzik);
	
	sesonceki = new SDLButton("ui/dugme100.jpg", "Menü", 11);
	sesonceki->setPosition(350, 310);
	sesonceki->clicked = makeFunctor((CBFunctor0*)0, *me, &Game::displayMenu);
	sesayar->addWidget(sesonceki);
	
	seskaydet = new SDLButton("ui/dugme100.jpg", "Uygula", 11);
	seskaydet->setPosition(350, 335);
	seskaydet->clicked = makeFunctor((CBFunctor0*)0, *me, &Game::saveVolSets);
	sesayar->addWidget(seskaydet);
	
	mvol = new SDLCombo();
	mvol->setPosition( 330 + muzik->getWidth(), 285);
	mvol->addOption("Yüksek", "1", true);
	mvol->addOption("Orta", "2");
	mvol->addOption("Kısık", "4");
	sesayar->addWidget(mvol);
	
	// emin mi diyaloglari icin
	eminmi = new SDLScreen(screen);
	
	arka3 = new SDLWidget("ui/optionPane.jpg");
	arka3->setPosition(265, 200);
	eminmi->addWidget(arka3);
	
	lblemin = new SDLLabel("Emin misiniz?");
	lblemin->setPosition(300 + ( (200-lblemin->getWidth())/2 ), 260);
	eminmi->addWidget(lblemin);
	
	evet = new SDLButton("ui/dugme100.jpg", "Evet", 11);
	evet->setPosition(300, 300);
	eminmi->addWidget(evet);
	
	hayir = new SDLButton("ui/dugme100.jpg", "Hayır", 11);
	hayir->setPosition(400, 300);
	eminmi->addWidget(hayir);
	
	current = 0;
	
	muse = new SDLMusic("wavs/music/track02.ogg");
	
	if (SDLMusic::musicOn)
		muse->play();
	
	son = 0;
}

Game::~Game()
{
	delete ui;
	delete commands;
	delete sesayar;
	
	delete human;
	delete cpu;
	
	delete tileCim;
	delete tileSari;
	delete tileAgac;
	delete tileToprak;
	delete tileDeniz;
	delete muse;
}

int Game::sonMu()
{
	return son;
}

void Game::endGame()
{
	Game *me = this;
	evet->clicked = makeFunctor((CBFunctor0*)0, *me, &Game::quitGame);
	hayir->clicked = makeFunctor((CBFunctor0*)0, *me, &Game::closeMenu);
	current = eminmi;
}

void Game::quitGame()
{
	son = 1;
}

void Game::quitAll()
{
	son = 2;
}

void Game::quitToSystem()
{
	Game *me = this;
	evet->clicked = makeFunctor((CBFunctor0*)0, *me, &Game::quitAll);
	hayir->clicked = makeFunctor((CBFunctor0*)0, *me, &Game::closeMenu);
	current = eminmi;
}

void Game::update()
{
	checkMusic();
	if (!running)
		return;
	human->update(harita->getCx(), harita->getCy());
	lblWood->setText(human->getWoodAmount());
	lblFood->setText(human->getFoodAmount());
	lblStone->setText(human->getStoneAmount());
	harita->update();
	// TODO cpu->update() AI yazılınca
}

void Game::checkMusic()
{
	if (!SDLMusic::musicOn)
	{
		muse->stop();
		return;
	}
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

void Game::displayVolume()
{
	if(SDLMusic::musicOn)
		monoff->setOn();
	else monoff->setOff();
	
	switch(SDLMusic::getVolume())
	{
		case MIX_MAX_VOLUME:
			mvol->setSelected("Yüksek");
			break;
		case MIX_MAX_VOLUME/2:
			mvol->setSelected("Orta");
			break;
		case MIX_MAX_VOLUME/4:
			mvol->setSelected("Kısık");
			break;
	}
	
	current = sesayar;
}

void Game::displayMenu()
{
	if (current == 0 && running)
	{
		running = false;
		current = commands;
	}
	else if (current != 0 && !running)
		current = commands;
}

void Game::saveVolSets()
{
	if (monoff->isChecked())
		SDLMusic::musicOn = true;
	else 
		SDLMusic::musicOn = false;
	
	string t = mvol->getValue();
	if (t == "1")
		SDLMusic::setVolume(1);
	else if (t == "2")
		SDLMusic::setVolume(2);
	else if (t == "4")
		SDLMusic::setVolume(4);
}

void Game::closeMenu()
{
	current = 0;
	running = true;
}

void Game::display()
{
	ui->display();
	harita->draw();
	
	if (!running)
	{
		current->display();
	}
}

void Game::eventHandler(SDL_Event *event)
{
	ui->eventHandler(event);
	harita->handleEvents(event);
	if (current != 0)
		current->eventHandler(event);
	human->eventHandler(event);
}


