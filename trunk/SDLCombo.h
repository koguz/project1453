#ifndef SDLCOMBO__H
#define SDLCOMBO__H

#include <iostream>
#include <string>
#include <vector>

#include "Headers.h"
#include "SDLButton.h"
#include "SDLLabel.h"

using namespace std;

class SDLCombo;

class SDLComboOption:public SDLWidget
{
	public:
	SDLComboOption(SDLCombo* pp, string po, string pv, bool pd);
	~SDLComboOption();
	
	enum optionState { NORMAL, OVER };
	
	virtual void drawWidget(SDL_Surface* screen)
	{
		rectangleColor(screen, px1, py1, px2, py2,  0x330000FF);
		if (durum == NORMAL)
			boxColor(screen, px1+1, py1+1, px2-1, py2-1, DARKERGRAY);
		else if (durum == OVER)
			boxColor(screen, px1+1, py1+1, px2-1, py2-1, DARKGRAY);
		yazi->drawWidget(screen);
	}
	
	virtual void setPosition(int x, int y)
	{
		SDLWidget::setPosition(x, y);
		yazi->setPosition(px1+4, py1 + (h-yazi->getHeight())/2);
	}

	protected:
	friend class SDLCombo;
	optionState durum;
	SDLLabel* yazi;
	SDLCombo* parent;
	string option;
	string value;
	bool selected;
	void deSelect();
	void setSelected();
	bool isSelected();
	string getOption();
	string getValue();
	optionState getState();
	void setState(optionState s);
	void setWidth(int pw);
};

class SDLCombo:public SDLWidget
{
	public:
	SDLCombo();
	~SDLCombo();
	
	enum comboState{ CLOSED, OPEN };
	string getValue();
	string getSelectedString();
	virtual void drawWidget(SDL_Surface* screen)
	{
		boxColor(screen, px1, py1, px2, py2, DARKERGRAY);
		button->drawWidget(screen);
		
		if (yazi != 0)
			yazi->drawWidget(screen);
		
		if (durum == OPEN)
		{
			for(int i=0;i<options.size();i++)
			{
				options[i]->drawWidget(screen);
			}
		}
	}
	
	virtual void handleMouseEvent(int eventType, int button, int x, int y)
	{
		handleEvent(eventType, button, x, y);
	}
	
	void addOption(string option, string value, bool def=false);
	void setSelected(string val);
	
	protected:
	SDLButton *button;
	comboState durum;
	SDLLabel *yazi;
	vector<SDLComboOption*> options;
	void showOptions();
	void hideOptions();
	void toggleOptions();
	void handleEvent(int eventType, int button, int x, int y);
};

#endif

