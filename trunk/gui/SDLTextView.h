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

/** \brief TextView Widget
 * 
 * SDLTextView displays a string of long text by splitting
 * it to lines. It has a fixed number of rows and lets the
 * user to scroll the text via two buttons. 
 * 
 * SDLTextView uses SDLLabel and SDLButton to display the text.
 * 
 * \author Kaya Oguz
 * \date 2007.02
 */
class SDLTextView:public SDLWidget
{
	public:
	/** \brief Constructor
	 *
	 * This is the contructor which sets the text, size and rows of the
	 * widget.
	 * 
	 * \param text is the text which will be displayed. It will be splitted by new lines (\\n)
	 * \param width is the width of the widget in pixels
	 * \param rows is the number of rows of the widget
	 */
	SDLTextView(string text, int width, int rows);
	
	/// \return The text of the widget
	string getText() { return metin; }
	
	/**
	 * drawWidget draws only the lines which will be displayed. It
	 * also draws the widgets...
	 */
	virtual void drawWidget(SDL_Surface* screen)
	{
		boxColor(screen, px1, py1, px2, py2, DARKERGRAY);
		for(int i=uppos;i<downpos;i++)
		{
			satirlar[i].drawWidget(screen);
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
	
	/// Positions all widgets
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
	
	/// Handles mouse events
	virtual void handleMouseEvent(int eventType, int button, int x, int y)
	{
		handleEvent(eventType, button, x, y);
	}
	
	protected:
	int width /** Width of the SDLTextArea */,
		rows /** Number of rows */,
		uppos /** Upper position of the lines */,
		downpos /** Lower position of the lines */,
		lines /** Number of lines */,
		lineHeight  /** Height of each line */;
	
	/// Text of the widget
	string metin;
	
	/// Button for scrolling up
	SDLButton *up;
	
	/// Button for scrolling down
	SDLButton *down;
	
	/// Vector for lines, which are SDLLabel widgets
	vector<SDLLabel> satirlar;
	
	/// Moves the lines up
	void moveUp();
	
	/// Moves the lines down
	void moveDown();
	
	/// After moving, the labels are repositioned
	void repositionLabels();
	
	/// Handles events
	void handleEvent(int eventType, int button, int x, int y);
};


#endif 

