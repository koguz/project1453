#include "SDLCheckBox.h"

SDLCheckBox::SDLCheckBox(string label)
{
	tip = SDLWidget::CHECKBOX;
	on = false;
	SDLCheckBox *me = this;
	button = new SDLButton("img/combo.png", "");
	button->clicked = makeFunctor((CBFunctor0*)0, *me, &SDLCheckBox::toggle);
	check = new SDLWidget("img/check.png");
	
	SDL_Color c = { 255, 255, 255 };
	yazi = new SDLFont(label, 16, c);
	
}

void SDLCheckBox::toggle()
{
	if (on) setOff();
	else if (!on) setOn();
}


