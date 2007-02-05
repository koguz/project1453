#ifndef SDLBUTTON_H_
#define SDLBUTTON_H_

#include <string>
#include "Headers.h"
#include "SDLWidget.h"
#include "SDLLabel.h"

using namespace std;

/** \brief Simple Button
 *
 * This is the basic simple button to use in a GUI. 
 * It uses an image file for three states, in which these
 * states are drawn from top to down. The most important member
 * of the button is the clicked member which can be bind for 
 * any action.
 *
 * The SDLButton has an SDLLabel member, if a label is
 * given at the constructor.
 *
 * The member clicked is the crucial part of the 
 * SDLButton. With this variable, and the help of 
 * the Functor classes we can bind any member function
 * of any class to this button. So, when the button is 
 * clicked the function of a specific class is executed.
 * @see callback.h 
 * 
 * Below you can see how the toggle function of SDLCheckBox
 * is binded to the button used in SDLCheckBox. me is the 
 * pointer to the class itself...
 * 
 * \code 
 * button->clicked = makeFunctor((CBFunctor0*)0, *me, &SDLCheckBox::toggle);
 * \endcode 
 * 
 * \author Kaya Oguz
 * \date 2006-2007
 */
class SDLButton:public SDLWidget
{
	public:
	/// States of a button
	enum ButtonState { NORMAL, OVER, PRESSED };
	
	/** 
	 * Basic constructor for a button. 
	 * \param f is the filename of the image file used
	 * \param label is the label on the button (can be "")
	 */
	SDLButton(string f, string label);
	
	/** \brief Binds button to any function of any class
	 *
	 * Binding can be done to any function of any class. The function
	 * makeFunctor can be used as follows:
	 * 
	 * \code 
 	 * button->clicked = makeFunctor((CBFunctor0*)0, *me, &SDLCheckBox::toggle);
 	 * \endcode 
 	 * 
	 */
	CBFunctor0 clicked; 
	
	/** \brief Draws the widget
	 *
	 * Drawing a button is done by drawing the 
	 * widget according to the ButtonState and 
	 * drawing the SDLLabel, if there is one.
	 */
	virtual void drawWidget(SDL_Surface *screen)
	{
		SDL_Rect src, dest;
		src.w = w;
		src.h = h;
		src.x = 0;
		if (bState == NORMAL)
			src.y = 0;
		else if (bState == OVER)
			src.y = h;
		else if (bState == PRESSED)
			src.y = h * 2;
		
		dest.x = px1;
		dest.y = py1;
		dest.w = w;
		dest.h = h;
		SDL_BlitSurface(widget, &src, screen, &dest);
		
		if (metin != 0)
		{
			metin->drawWidget(screen);
		}
	}
	
	/// While positioning, we also position 
	/// the SDLLabel accordingly. 
	virtual void setPosition(int x, int y)
	{
		SDLWidget::setPosition(x, y);
		if (metin != 0)
		{
			metin->setPosition(px1 + ((w - metin->getWidth()) / 2), py1 + ((h - metin->getHeight()) / 2));
		}
	}
	
	/// Handling the mouse events are done vie handleEvent 
	/// member function
	virtual void handleMouseEvent(int eventType, int button, int x, int y)
	{
		handleEvent(eventType, button, x, y);
	}
	
	protected:
	ButtonState bState;
	SDLLabel *metin;
	void setState(ButtonState s) { bState = s; }
	ButtonState getState() { return bState; }
	void handleEvent(int eventType, int button, int x, int y);
};

#endif /*SDLBUTTON_H_*/
