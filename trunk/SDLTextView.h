#ifndef SDLTEXTVIEW__H_
#define SDLTEXTVIEW__H_

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "SDLWidget.h"
#include "SDLButton.h"
#include "SDLLabel.h"

using namespace std;

class SDLTextView:public SDLWidget
{
	public:
	SDLTextView(string text, int width, int rows);
	~SDLTextView();
	
	string getText();
	void setText(string text);
	
	virtual void drawWidget(SDL_Surface* screen)
	{
		boxColor(screen, px1, py1, px2, py2, DARKERGRAY);
		for(int i=uppos;i<downpos;i++)
		{
			satirlar[i]->drawWidget(screen);
		}
		boxColor(screen, px2+1, py1, px2+up->getWidth() , py2, GRAY);
		up->drawWidget(screen);
		down->drawWidget(screen);
		
		if (lines > rows)
		{
			int sh1 = (((lineHeight*rows)-(up->getHeight() + down->getHeight()))/lines)*rows;
			int sh2 = (py1+up->getHeight())+(uppos*(sh1/rows));
			int sh = sh1 + sh2;
			if (downpos == lines)
			{
				sh = py2 - up->getHeight();
			}
			boxColor(screen, px2+1, sh2, px2+up->getWidth(), sh, DARKGRAY);
		}
	}
	
	virtual void setPosition(int x, int y)
	{
		px1 = x;
		py1 = y;
		w = width;
		h = rows * lineHeight;
		px2 = px1 + w;
		py2 = py1 + h;
		
		up->setPosition(px1+w+1, py1);
		down->setPosition(px1+w+1, py2-down->getHeight()+1);
		
		repositionLabels();
	}
	
	virtual void handleMouseEvent(int eventType, int button, int x, int y)
	{
		handleEvent(eventType, button, x, y);
	}
	
	protected:
	int width, rows, uppos, downpos, lines, lineHeight;
	string metin;
	SDLButton *up;
	SDLButton *down;
	vector<SDLLabel*> satirlar;
	void moveUp();
	void moveDown();
	void repositionLabels();
	void handleEvent(int eventType, int button, int x, int y);
};


#endif 

