#include "SDLCheckBox.h"

SDLCheckBox::SDLCheckBox(string label)
{
	tip = SDLWidget::CHECKBOX;
	on = false;
	SDLCheckBox *me = this;
	button = new SDLButton("img/combo.png", "");
	button->clicked = makeFunctor((CBFunctor0*)0, *me, &SDLCheckBox::toggle);
	check = new SDLWidget("img/check.png");
	yazi = new SDLLabel(label);
	w = button->getWidth() + 10 + yazi->getWidth();
	h = button->getHeight();
	show = true;
}


SDLCheckBox::~SDLCheckBox()
{
	delete button;
	delete check;
	delete yazi;
}

bool SDLCheckBox::isChecked() { return on; }
void SDLCheckBox::setOn() { on = true; }
void SDLCheckBox::setOff() { on = false; }


void SDLCheckBox::toggle()
{
	if (on) setOff();
	else if (!on) setOn();
}

void SDLCheckBox::handleEvent(int eventType, int button, int x, int y)
{
	this->button->handleMouseEvent(eventType, button, x, y);
}


