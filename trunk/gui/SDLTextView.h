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
	SDLTextView(string text, int cols, int rows);
	string getText() { return metin; }
	void handleMouseEvent(int eventType, int button, int x, int y);
	
	virtual void drawWidget(SDL_Surface* screen)
	{
		rectangleColor(screen, px1, py1, px2, py2, BLUE);
		boxColor(screen, px1+1, py1+1, px2-1, py2-1, DARKERGRAY);
		for(int i=uppos;i<downpos;i++)
		{
			satirlar[i].drawWidget(screen);
		}
		boxColor(screen, px2+1, py1, px2+16 , py2, GRAY);
		up->drawWidget(screen);
		down->drawWidget(screen);
		
		if (lines > rows)
		{
			int sh = (((20*rows)-32)/lines)*rows;
			int sh2 = (py1+16)+(uppos*(sh/rows));
			boxColor(screen, px2+1, sh2, px2+16, sh2+sh, DARKGRAY);
		}
	}
	
	virtual void setPosition(int x, int y)
	{
		px1 = x;
		py1 = y;
		w = width;
		h = rows * 20;
		px2 = px1 + w;
		py2 = py1 + h;
		
		up->setPosition(px1+w+1, py1);
		down->setPosition(px1+w+1, py2-15);
		
		repositionLabels();
	}
	
	
	protected:
	int width, rows;
	int uppos, downpos;
	int lines;
	string metin;
	SDLButton *up;
	SDLButton *down;
	vector<SDLLabel> satirlar;
	void moveUp();
	void moveDown();
	void repositionLabels();
};


#endif 

