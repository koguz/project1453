#ifndef SDLCHECKBOX__H_
#define SDLCHECKBOX__H_

#include <iostream>
#include <string>
#include "SDLWidget.h"
#include "SDLButton.h"
#include "SDLLabel.h"


using namespace std;

/** \brief Checkbox
  *
  * This is a simple checkbox which can be toggled 
  * and mostly used for boolean variables.
  * 
  * SDLCheckBox makes use of SDLButton, SDLWidget and
  * SDLLabel. 
  * 
  * \author Kaya Oguz
  * \date 2007.02
  */
class SDLCheckBox:public SDLWidget
{
	public:
	/** \brief Constructor
	 *
	 * This is the constructor of the SDLCheckBox.
	 * \param label is the label string of the SDLCheckBox
	 */
	SDLCheckBox(string label);
	
	/// Toggles the checkbox
	void toggle();
	
	/// \return True if it is checked, false otherwise.
	bool isChecked() { return on; }
	
	/// Draws SDLButton, SDLLabel and SDLWidget accordingly
	virtual void drawWidget(SDL_Surface* screen)
	{
		button->drawWidget(screen);
		if (on)
			check->drawWidget(screen);
		yazi->drawWidget(screen);
	}
	
	/// Positions SDLButton, SDLLabel and SDLWidget accordingly
	virtual void setPosition(int x, int y)
	{
		SDLWidget::setPosition(x, y);
		button->setPosition(x, y);
		check->setPosition(x + ((button->getWidth() - check->getWidth()) / 2), y+ ((button->getHeight() - check->getHeight()) / 2) );
		yazi->setPosition(px1 + 10 + button->getWidth(), py1 + ( (button->getHeight() - yazi->getHeight()) / 2 ));
	}
	
	/// Handles mouse events, directed to the SDLButton
	virtual void handleMouseEvent (int eventType, int button, int x, int y)
	{
		handleEvent(eventType, button, x, y);
	}
	
	protected:
	/// SDLButton for toggling
	SDLButton *button;
	
	/// This is the widget which holds an image of a "check"
	SDLWidget *check;
	
	/// Holds the label string as an SDLLabel
	SDLLabel *yazi;
	
	/// Control variable for check value
	bool on;
	
	/// Sets the control variable on
	void setOn() { on = true; }
	
	/// Sets the control variable off
	void setOff() { on = false; }
	
	/// Handles mouse event
	void handleEvent (int eventType, int button, int x, int y);
};


#endif

