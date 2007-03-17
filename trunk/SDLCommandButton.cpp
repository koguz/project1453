#include "SDLCommandButton.h"

SDLWidget* SDLCommandButton::ana = 0;

SDLCommandButton::SDLCommandButton(SDL_Surface *scr, SDL_Rect k, string info, BaseObject* nesne)
{
	tip = COMBUTTON;
	screen = scr;
	kare = k;
	inf = info;
	this->nesne = nesne;
	show = true;
	over = false;
	
	w = h = 48;
	
	dugme = new SDLButton("ui/commandButton.png", "");
	dugme->clicked = 0;
	if (ana == 0)
		ana = new SDLWidget("ui/commandList.png");
	
	aciklama = new SDLScreen(screen);
	
	lblCommand = new SDLLabel(inf);
	lblCommand->setPosition(648, 450);
	aciklama->addWidget(lblCommand);
	
	if (nesne != 0)
	{
		
		woodIcon = new SDLWidget("ui/wood.jpg");
		woodIcon->setPosition(648, 470);
		aciklama->addWidget(woodIcon);
		
		foodIcon = new SDLWidget("ui/food.jpg");
		foodIcon->setPosition(648, 490);
		aciklama->addWidget(foodIcon);
		
		stoneIcon = new SDLWidget("ui/stone.jpg");
		stoneIcon->setPosition(648, 510);
		aciklama->addWidget(stoneIcon);
		
		Cost nc = nesne->getCost();
		
		lblWood = new SDLLabel(nc.getWoodAmount());
		lblWood->setPosition(668, 470);
		aciklama->addWidget(lblWood);
		
		lblFood = new SDLLabel(nc.getFoodAmount());
		lblFood->setPosition(668, 490);
		aciklama->addWidget(lblFood);
		
		lblStone = new SDLLabel(nc.getStoneAmount());
		lblStone->setPosition(668, 510);
		aciklama->addWidget(lblStone);
	}
	
}

SDLCommandButton::~SDLCommandButton()
{
	delete aciklama;
// 	delete woodIcon;
// 	delete foodIcon;
// 	delete stoneIcon;
// 	delete lblWood;
// 	delete lblFood;
// 	delete lblStone;
// 	delete lblCommand;
}

void SDLCommandButton::handleEvent(int eventType, int button, int x, int y)
{
	switch(eventType)
	{
		case SDL_MOUSEMOTION:
			if (isMouseOver(x, y))
				over = true;
			else over = false;
			break;
	}
	dugme->handleMouseEvent(eventType, button, x, y);
}

