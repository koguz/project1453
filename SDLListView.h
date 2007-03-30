#ifndef SDLLISTVIEW_H__
#define SDLLISTVIEW_H__

#include <iostream>
#include <string>
#include <vector>
#include "SDLWidget.h"
#include "SDLLabel.h"
#include "SDLButton.h"

using namespace std;

class SDLListView;

class SDLListViewItem:public SDLWidget
{
	public:
	SDLListViewItem(SDLListView* p, string str);
	~SDLListViewItem();
	
	enum itemState { NORMAL, OVER };
	
	virtual void drawWidget(SDL_Surface* screen)
	{
		if (selected)
			boxColor(screen, px1, py1, px2, py2, BLACK);
		else if (durum == OVER)
			boxColor(screen, px1, py1, px2, py2, 0x330000FF);
		else if (durum == NORMAL)
			boxColor(screen, px1, py1, px2, py2, DARKERGRAY);
		
		yazi->drawWidget(screen);
	}
	
	virtual void setPosition(int x, int y)
	{
		SDLWidget::setPosition(x, y);
		yazi->setPosition(px1+4, py1 + (h - yazi->getHeight())/2);
	}
	
	protected:
	friend class SDLListView;
	
	SDLListView *parent;
	SDLLabel *yazi;
	string value;
	itemState durum;
	bool selected;
	void setSelected();
	void deSelect();
	bool isSelected();
	string getValue();
	void setState(itemState it);
	itemState getState();
	void setWidth(int pw);
};


class SDLListView:public SDLWidget
{
	public:
	SDLListView(int rows);
	~SDLListView();
	
	string getValue();
	void addItem(string item);
	
	void setSelected(string val);
	
	virtual void drawWidget(SDL_Surface* screen)
	{
		rectangleColor(screen, px1, py1, px2, py2, BLUE);
		boxColor(screen, px1+1, py1+1, px2-1, py2-1, DARKERGRAY);
		for(int i=uppos;i<downpos;i++)
		{
			items[i]->drawWidget(screen);
		}
		boxColor(screen, px2+1, py1, px2+up->getWidth() , py2, GRAY);
		up->drawWidget(screen);
		down->drawWidget(screen);
		
		if (lines > rows)
		{
			int sh = (((lineHeight*rows)-(up->getHeight() + down->getHeight()))/lines)*rows;
			int sh2 = (py1+up->getHeight())+(uppos*(sh/rows));
			boxColor(screen, px2+1, sh2, px2+up->getWidth(), sh2+sh, DARKGRAY);
		}
	}
	
	virtual void setPosition(int x, int y)
	{
		px1 = x;
		py1 = y;
		// w = width;
		h = rows * lineHeight;
		px2 = px1 + w;
		py2 = py1 + h;
		
		up->setPosition(px1+w+1, py1);
		down->setPosition(px1+w+1, py2-down->getHeight()+1);
		
		repositionItems();
	}
	
	virtual void handleMouseEvent(int eventType, int button, int x, int y)
	{
		handleEvent(eventType, button, x, y);
	}
	
	protected:
	vector<SDLListViewItem*> items;
	int rows, uppos, downpos, lines, lineHeight;
	SDLButton *up;
	SDLButton *down;
	void moveUp();
	void moveDown();
	void repositionItems();
	void handleEvent(int eventType, int button, int x, int y);
};



#endif 
