#include "SDLCombo.h"


SDLComboOption::SDLComboOption(
	SDLCombo* pp, 
	string po,
	string pv,
	bool pd)
{
	parent = pp;
	option = po;
	value = pv;
	selected = pd;
	
	durum = NORMAL;
	tip = COMBOOPTION;
	w = parent->getWidth();
	h = 20;
	
	SDL_Color c = { 0, 0, 0 };
	yazi = new SDLFont(option, 16, c);
}

bool SDLComboOption::isMouseOver(int mx, int my)
{
	if (
		(mx > px1) &&
		(mx < px2) &&
		(my > py1) &&
		(my < py2)
		)
		return true;
	else return false;
}

SDLCombo::SDLCombo()
{
	tip = SDLWidget::COMBO;
	durum = CLOSED;
	SDLCombo *me = this;
	button = new SDLButton("img/combo.png", "V");
	button->clicked = makeFunctor((CBFunctor0*)0, *me, &SDLCombo::toggleOptions);
	yazi = 0;
	w = h = 0;
}

void SDLCombo::addOption(string option, string value, bool def)
{
	options.push_back(SDLComboOption(this, option, value, def));
}

void SDLCombo::setSize(int pw, int ph)
{ 
	w = pw; 
	h = ph; 
	px2 = px1 + w;
	py2 = py1 + h;
	button->setPosition(px2-button->getWidth(), py1+1);
}

void SDLCombo::packOptions()
{
	int oy = 20;
	for(int i=0;i<options.size();i++)
	{
		options[i].setPosition(px1, (py2+1) + (oy*i));
		if (options[i].isSelected())
		{
			SDL_Color c = { 0, 0, 0 };
			yazi = new SDLFont(options[i].getOption(), 16, c);
		}
	}
}

void SDLCombo::toggleOptions()
{
	if (durum == OPEN)
		hideOptions();
	else if (durum == CLOSED)
		showOptions();
}

string SDLCombo::getSelected()
{
	for(int i=0;i<options.size();i++)
	{
		if (options[i].isSelected())
			return options[i].getValue();
	}
}

void SDLCombo::handleMouseEvent(int eventType, int button, int x, int y)
{
	if (durum == CLOSED) return;
	for (int i=0;i<options.size();i++)
	{
		switch(eventType)
		{
			case SDL_MOUSEMOTION:
				if (options[i].isMouseOver(x, y))
					options[i].setState(SDLComboOption::OVER);
				else options[i].setState(SDLComboOption::NORMAL);
				break;
			case SDL_MOUSEBUTTONDOWN:
				if (button == SDL_BUTTON_LEFT)
				{
					if(options[i].isMouseOver(x, y))
					{
						for (int j=0;j<options.size();j++)
							options[j].deSelect();
						options[i].setSelected();
						SDL_Color c = { 0, 0, 0 };
						delete(yazi);
						yazi = new SDLFont(options[i].getOption(), 16, c);
						toggleOptions();
						return;
					}
				}
				break;
		}
	}
}

