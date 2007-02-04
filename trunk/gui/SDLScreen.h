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

using namespace std;


/*! \mainpage SDLGUI 
 * 
 * This is the documentation of the SDLGUI which are written
 * for the 1453 project - an RTS game using SDL and sister libraries.
 * 
 * The GUI structure is made up of simple structures. At the base
 * of all widgets lays the SDLWidget class. It has basic functions for
 * displaying, positioning and handling input. All other widgets are
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
 * @see callback.h 
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
 * SDLScreen is what a window to a GUI application. It 
 * holds the widgets together and is responsible for
 * their display and event handling. 
 * 
 * It's really easy to use SDLScreen. Just create a few
 * SDLWidget widgets and add them. While looping for 
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
	 * Contructor.
	 * \param scr is a pointer to the main screen surface
	 */
	SDLScreen(SDL_Surface *scr);
	
	/// Adds a widget to the screen
	void addWidget(SDLWidget *w);
	
	/// Displays all widgets
	void display();
	
	/// Lets its children handle the SDL_Event
	void eventHandler(SDL_Event *event);
	
	private:
	/// Vector of widgets. 
	vector<SDLWidget*> widgets;
	
	/// Holding a reference to the main screen surface
	SDL_Surface *screen;
};
	
#endif /*EKRAN_H_*/

