#ifndef SDLWIDGET_H_
#define SDLWIDGET_H_

#define BLACK 0x000000FF
#define WHITE 0xFFFFFFFF
#define GRAY  0xCCCCCCFF
#define DARKGRAY 0xAAAAAAFF
#define DARKERGRAY 0x444444FF
#define BLUE 0x336699FF

#include <iostream>
#include "Headers.h"
#include "callback.h"

using namespace std;

/**
 * \brief Basic Widget Class
 *
 *
 * This is the basic widget class.
 * It has common functions for all widgets and virtual
 * functions for specific widgets. It can also be used for 
 * keeping an image, which can be a background or anything
 * which will only be displayed. This base widget does not
 * handle any events, it is only displayed on screen.
 *
 * \author Kaya Oguz
 * \date 2007.01 - 2007.02
 */
class SDLWidget
{
	public:
	/// Basic constructor
	SDLWidget();
	
	/** 
	 * This constructor can be used to keep an image 
	 * file within the widget.
	 * \param fileName is the filename of the image file
	 */
	SDLWidget(char *fileName);
	
	/** \brief Type of widget
	 *
	 * This enum holds the type of the widget. This enum is 
	 * mostly used internally for specific widget actions.
	 */
	enum WidgetType { WIDGET, BUTTON, COMBO, COMBOOPTION, CHECKBOX, TEXTVIEW, LISTITEM, LIST };
	
	/// Function which returns the widget type
	/// \return the type of the widget
	WidgetType getType() { return tip; }
	
	/**
	 * Function used for all widgets whether the mouse is 
	 * over the widget.
	 * \param x is the x-coordinate of the mouse
	 * \param y is the y-coordinate of the mouse
	 * \return true if the mouse is over, false if it is not
	 */
	bool isMouseOver(int x, int y);
	
	/** 
	 * Virtual function responsible for drawing the
	 * widget on the screen.
	 * \param screen is the pointer to the main screen surface
	 */
	virtual void drawWidget(SDL_Surface *screen)
	{
		SDL_Rect src, dest;
		src.x = 0;
		src.y = 0;
		src.w = w;
		src.h = h;
		
		dest.x = px1;
		dest.y = py1;
		dest.w = w;
		dest.h = h;
		
		SDL_BlitSurface(widget, &src, screen, &dest);
	}
	
	/**
	 * Virtual function responsible for positioning 
	 * the widget on the screen. Widgets are positioned in
	 * a fixed way. There are no layouts...
	 * \param x is the x coordinate
	 * \param y is the y coordinate
	 */
	virtual void setPosition(int x, int y)
	{
		px1 = x;
		py1 = y;
		px2 = px1 + w;
		py2 = py1 + h;
	}
	
	/**
	 * Virtual function for handling events... The GUI
	 * system is used only by mouse (so far) 
	 * \param eventType is SDL_Event type
	 * \param button is the mouse button
	 * \param x is the x-position of the mouse
	 * \param y is the y-position of the mouse
	 */
	virtual void handleMouseEvent (int eventType, int button, int x, int y)
	{
		/// This function does nothing for base widget
	}
	
	/// \return Returns the width of the widget
	int getWidth() { return w; }
	
	/// \return Returns the height of the widget
	int getHeight() { return h; }
	
	protected:
	/// \brief Widget surface, most likely an image
	SDL_Surface *widget; 
	
	/// Holds the type of the widget
	WidgetType tip; 
	int px1 /** \brief X-Coordinate for left corners */, 
		px2 /** \brief X-Coordinate for right corners */, 
		py1 /** \brief Y-Coordinate for upper corners */, 
		py2 /** \brief Y-Coordinate for lower corners */,
		w /** \brief Width of widget */, 
		h /** \brief Height of widget */; 
};

#endif /*SDLWIDGET_H_*/

