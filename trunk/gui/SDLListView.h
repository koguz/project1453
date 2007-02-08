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

/** \brief Items for SDLListView
 *
 * SDLListViewItem is the widget responsible for the displaying
 * and holding information of items in an SDLListView. It uses SDLLabel
 * for displaying items.
 *
 * \author Kaya Oguz
 * \date 2007.02.04
 */
class SDLListViewItem:public SDLWidget
{
	public:
	/** Constructor
	 * \param p is the pointer to the parent SDLListView 
	 * \param str is the string / name of the item
	 */
	SDLListViewItem(SDLListView* p, string str);
	
	/// Item States
	enum itemState { NORMAL, OVER };
	
	/// Draws the widgets to the screen
	virtual void drawWidget(SDL_Surface* screen)
	{
		if (durum == NORMAL)
			boxColor(screen, px1, py1, px2, py2, DARKERGRAY);
		else if (durum == OVER)
			boxColor(screen, px1, py1, px2, py2, BLUE);
		else if (selected)
			boxColor(screen, px1, py1, px2, py2, DARKGRAY);
		
		yazi->drawWidget(screen);
	}
	
	/// Positions widgets
	virtual void setPosition(int x, int y)
	{
		SDLWidget::setPosition(x, y);
		yazi->setPosition(px1+4, py1 + (h - yazi->getHeight())/2);
	}
	
	protected:
	/// SDLListView needs to be friend as it needs access to some of the functions
	friend class SDLListView;
	
	/// A reference is held for the parent
	SDLListView *parent;
	
	/// SDLLabel which is used for displaying string
	SDLLabel *yazi;
	
	/// Value of the item
	string value;
	
	/// State of the item
	itemState durum;
	
	/// Boolean control value for checking selected status
	bool selected;
	
	/// Selects the item
	void setSelected() { selected = true; }
	
	/// Deselects the item
	void deSelect() { selected = false; }
	
	/// \return True if the item is selected, false otherwise.
	bool isSelected() { return selected; }
	
	/// \return String value of the item
	string getValue() { return value; }
	
	/// Sets the state 
	void setState(itemState it) { durum = it; }
	
	/// \return The state of the item
	itemState getState() { return durum; }
	
	/// Resets the width of the item
	void setWidth(int pw)
	{
		w = pw; px2 = px1 + w;
	}
};


/** \brief Simple ListView Widget
 *
 * SDLListView holds a number of items for selection. These
 * items are SDLListViewItem widgets. 
 * 
 * \author Kaya Oguz
 * \date 2007.02.04
 *
 */
class SDLListView:public SDLWidget
{
	public:
	/** Constructor
	 * \param rows is the number of rows which will be used to display items
	 */
	SDLListView(int rows);
	
	/// \return The selected item's string value
	string getValue();
	
	/// Adds an item to the SDLListView
	void addItem(string item);
	
	/// Draws the widget on screen
	virtual void drawWidget(SDL_Surface* screen)
	{
		rectangleColor(screen, px1, py1, px2, py2, BLUE);
		boxColor(screen, px1+1, py1+1, px2-1, py2-1, DARKERGRAY);
		for(int i=uppos;i<downpos;i++)
		{
			items[i].drawWidget(screen);
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
	
	/// Sets the position for the widgets
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
	
	/// Handles mouse events
	virtual void handleMouseEvent(int eventType, int button, int x, int y)
	{
		handleEvent(eventType, button, x, y);
	}
	
	protected:
	/// Vector of SDLListViewItem widgets
	vector<SDLListViewItem> items;
	int // width /*! Width of widget */,
		rows /*! Number of rows of widget */,
		uppos /*! Upper position for the items */,
		downpos /*! Lower position for the items */,
		lines /*! Number of items */,
		lineHeight /*! Height for each item */;
	
	/// Button for moving up
	SDLButton *up;
	
	/// Button for moving down
	SDLButton *down;
	
	/// Moves items up
	void moveUp();
	
	/// Moves items down
	void moveDown();
	
	/// Repositions items after a move
	void repositionItems();
	
	/// Handler for events
	void handleEvent(int eventType, int button, int x, int y);
};



#endif 
