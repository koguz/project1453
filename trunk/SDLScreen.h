#ifndef EKRAN_H_
#define EKRAN_H_

#include <vector>
#include "Headers.h"
#include "SDLWidget.h"
#include "SDLButton.h"
#include "SDLCombo.h"
#include "SDLLabel.h"
#include "SDLCheckBox.h"
#include "SDLTextView.h"
#include "SDLListView.h"
#include "SDLProgressBar.h"

using namespace std;


/*! \mainpage SDLGUI Documentation
 * 
 * This is the documentation of the SDLGUI classes which are developed 
 * for the 1453 project - an Real-Time Strategy game using SDL and its sister libraries.
 * 
 * The SDLGUI system is made up of simple structures. At the base
 * of all widgets is the SDLWidget class. It has basic functions for
 * displaying and positioning widgets along with handling input. All other widgets are
 * derived from it. Most of the widgets make use of basic widgets
 * like SDLWidget, SDLLabel and SDLButton.
 * 
 * SDLFont is a temporary class which will soon be replaced by 
 * a more advanced one.
 * 
 * SDLScreen is the class which holds the widgets together.
 * 
 * To be an example, an Application class is written for testing
 * the GUI system. In any case, one can as much screens as he wants. 
 * 
 * The GUI system makes intensive use of STL libraries along with 
 * Rich Hickey's callback.h 
 * 
 */


/**
 * \file callback.h
 * This file holds the callback function classes written by
 * Rich Hickey. Using these functions the clicked member
 * of the SDLButton can be bind to any function of any class.
 */


/** \brief A Screen for holding SDLWidgets
 * 
 * SDLScreen is what a window is to a GUI application for the GUI system. 
 * It  holds the widgets together and is responsible for
 * their display and event handling. Just like an application can have many windows, 
 * a game can have many screens, like menu screen, options screen, game screen etc.
 * 
 * It's really easy to use SDLScreen. Just create a few
 * SDLWidget widgets and add them, with fixed positions. While looping for 
 * input anywhere in your game, pass the SDL_Event to 
 * the screen and it will let its children handle the event.
 * You should also use its display() function in your
 * display loop...
 * 
 * \author Kaya Oguz
 * \date 2006 - 2007
 */
class SDLScreen
{
	public:
	/**
	 * Constructor.
	 * \param scr is a pointer to the main screen surface
	 */
	SDLScreen(SDL_Surface *scr);
	
	/** \brief Adds a widget to the screen
	 *
	 * This adds a widget of any kind to the screen. Widgets
	 * are displayed / drawn with the order they are added, therefore
	 * the last one added is displayed last and is virtually on top of
	 * others. 
	 */
	void addWidget(SDLWidget *w);
	
	/** \brief Displays all widgets
	 *
	 * This function loops through the widgets and displays
	 * each one of them. 
	 * @see addWidget
	 * 
	 */
	virtual void display()
	{
		// SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 120, 120, 120));
		for (unsigned int i=0;i<widgets.size();i++)
		{
			widgets[i]->drawWidget(screen);
		}
	}
	
	/** \brief Event Handler
	 *
	 * This passes the SDL_Event to all widgets and lets each of them handle
	 * the event. 
	 * 
	 */
	void eventHandler(SDL_Event *event);
	
	private:
	/// Vector of widgets. 
	vector<SDLWidget*> widgets;
	
	/// Holding a reference to the main screen surface
	SDL_Surface *screen;
};
	
#endif /*EKRAN_H_*/

