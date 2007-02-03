#ifndef SDLCOMBO__H
#define SDLCOMBO__H

#include <iostream>
#include <string>
#include <vector>

#include "Headers.h"
#include "SDLButton.h"
#include "SDLFont.h"

using namespace std;

class SDLCombo;

class SDLComboOption:public SDLWidget
{
	public:
	SDLComboOption(SDLCombo* pp, string po, string pv, bool pd);
	enum optionState { NORMAL, OVER };
	void deSelect() { selected = false; }
	void setSelected() { selected = true; }
	bool isSelected() { return selected; }
	string getOption() { return option; }
	string getValue() { return value; }
	bool isMouseOver(int x, int y);
	optionState getState() { return durum; }
	void setState(optionState s) { durum = s; }
	
	virtual void drawWidget(SDL_Surface* screen)
	{
		rectangleColor(screen, px1, py1, px2, py2,  BLUE);
		if (durum == NORMAL)
			boxColor(screen, px1+1, py1+1, px2-1, py2-1, GRAY);
		else if (durum == OVER)
			boxColor(screen, px1+1, py1+1, px2-1, py2-1, DARKGRAY);
		yazi->drawMe(screen, px1+4, py1 + (h-yazi->getHeight())/2);
	}
	

	protected:
	optionState durum;
	SDLFont* yazi;
	SDLCombo* parent;
	string option;
	string value;
	bool selected;
};

class SDLCombo:public SDLWidget
{
	public:
	enum comboState{ CLOSED, OPEN };
	SDLCombo();
	
	string getSelected();
	
	virtual void drawWidget(SDL_Surface* screen)
	{
		rectangleColor(screen, px1, py1, px2, py2,  BLUE);
		boxColor(screen, px1+1, py1+1, px2-1, py2-1, GRAY);
		button->drawWidget(screen);
		
		yazi->drawMe(screen, px1+4, py1+ (h-yazi->getHeight())/2);
		
		if (durum == OPEN)
		{
			for(int i=0;i<options.size();i++)
			{
				options[i].drawWidget(screen);
			}
		}
	}
	
	void addOption(string option, string value, bool def=false);
	void packOptions();
	void setSize(int pw, int ph);
	void handleMouseEvent(int eventType, int button, int x, int y);
	SDLButton *button;
	
	protected:
	comboState durum;
	SDLFont *yazi;
	vector<SDLComboOption> options;
	void showOptions() { durum = OPEN; }
	void hideOptions() { durum = CLOSED; }
	void toggleOptions();
};

#endif

