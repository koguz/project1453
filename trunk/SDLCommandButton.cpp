#include "SDLCommandButton.h"

SDLWidget* SDLCommandButton::ana = 0;

SDLCommandButton::SDLCommandButton(SDL_Surface *scr, SDL_Rect k, string info, Cost c)
{
	tip = COMBUTTON;
	screen = scr;
	kare = k;
	inf = info;
	show = true;
	over = false;
	
	w = h = 34;
	
	dugme = new SDLButton("ui/commandButton.png", "");
	dugme->clicked = 0;
	if (ana == 0)
		ana = new SDLWidget("ui/commandList.png");
	
	aciklama = new SDLScreen(screen);
	lblCommand = new SDLLabel(inf, 12);
	lblCommand->setPosition(655, 450);
	aciklama->addWidget(lblCommand);
	
	if (!c.compare(0,0,0))
	{
		woodIcon = new SDLWidget("ui/wood.jpg");
		woodIcon->setPosition(655, 470);
		aciklama->addWidget(woodIcon);
		
		foodIcon = new SDLWidget("ui/food.jpg");
		foodIcon->setPosition(655, 490);
		aciklama->addWidget(foodIcon);
		
		stoneIcon = new SDLWidget("ui/stone.jpg");
		stoneIcon->setPosition(655, 510);
		aciklama->addWidget(stoneIcon);
		
		lblWood = new SDLLabel(c.getWoodAmount(), 12);
		lblWood->setPosition(675, 470);
		aciklama->addWidget(lblWood);
		
		lblFood = new SDLLabel(c.getFoodAmount(), 12);
		lblFood->setPosition(675, 490);
		aciklama->addWidget(lblFood);
		
		lblStone = new SDLLabel(c.getStoneAmount(), 12);
		lblStone->setPosition(675, 510);
		aciklama->addWidget(lblStone);
	}
	else woodIcon = foodIcon = stoneIcon = lblWood = lblFood = lblStone = 0;
}

SDLCommandButton::~SDLCommandButton()
{
	delete aciklama;
	delete dugme; // saklanmış bu :P
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

