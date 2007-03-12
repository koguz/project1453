#ifndef SDLCOMBO__H
#define SDLCOMBO__H

#include <iostream>
#include <string>
#include <vector>

#include "Headers.h"
#include "SDLButton.h"
#include "SDLLabel.h"

using namespace std;

class SDLCombo;

/** \brief Option Widget for SDLCombo
 * 
 * This class holds the options for the 
 * SDLCombo class. These are the options which can
 * be selected via the SDLCombo.
 * 
 * SDLComboOption has an SDLLabel for displaying the
 * option string.
 * \author Kaya Oguz
 * \date 2007.02
 */
class SDLComboOption:public SDLWidget
{
	public:
	/** \brief Basic Contructor
	 *
	 * This is the basic constructor for SDLComboOption. It 
	 * creates an instance of the class with the SDLCombo parent
	 * given.
	 * \param pp is the parent SDLCombo 
	 * \param po is the option string
	 * \param pv is the value string
	 * \param pd defines whether this option is the default (selected) one
	 */
	SDLComboOption(SDLCombo* pp, string po, string pv, bool pd);
	
	/// States of the option
	enum optionState { NORMAL, OVER };
	
	/**
	 * SDLComboOption is drawn according to its state,
	 * so this function is implemented again.
	 */
	virtual void drawWidget(SDL_Surface* screen)
	{
		rectangleColor(screen, px1, py1, px2, py2,  0x330000FF);
		if (durum == NORMAL)
			boxColor(screen, px1+1, py1+1, px2-1, py2-1, DARKERGRAY);
		else if (durum == OVER)
			boxColor(screen, px1+1, py1+1, px2-1, py2-1, DARKGRAY);
		yazi->drawWidget(screen);
	}
	
	/**
	 * Sets the position, also positions the SDLLabel
	 */
	virtual void setPosition(int x, int y)
	{
		SDLWidget::setPosition(x, y);
		yazi->setPosition(px1+4, py1 + (h-yazi->getHeight())/2);
	}

	protected:
	/// SDLCombo needs to be a friend, as it needs to access some functions
	friend class SDLCombo;
	
	/// State of the SDLComboOption
	optionState durum;
	
	/// Holds the option string as an SDLLabel
	SDLLabel* yazi;
	
	/// A pointer to the parent SDLCombo
	SDLCombo* parent;
	
	/// Option is a string which describes the value
	string option;
	
	/// Value is the target variable which will be returned
	string value;
	
	/// Control value for displaying 
	bool selected;
	
	/// Deselects the SDLComboOption
	void deSelect() { selected = false; }
	
	/// Selects the SDLComboOption
	void setSelected() { selected = true; }
	
	/// \return True if SDLComboOption is selected, otherwise returns false
	bool isSelected() { return selected; }
	
	/// \return The option string
	string getOption() { return option; }
	
	/// \return The value string
	string getValue() { return value; }
	
	/// \return SDLComboOption state
	optionState getState() { return durum; }
	
	/// Sets the state of the SDLComboOption
	void setState(optionState s) { durum = s; }
	
	/// Resets the width when a new SDLComboOption has a larger width
	void setWidth(int pw) { w = pw; px2 = px1 + w; }
};

/** \brief Combobox (Dropdown)
 *
 *	SDLCombo is a simple implementation of a ComboBox. It 
 *	has options which are made up of SDLComboOption and 
 *	lets the user select one of them.
 *	
 *	SDLCombo is made up of SDLComboOptions, an SDLButton and
 *	an SDLLabel. The SDLLabel is used for displaying the 
 *	currently selected option string.
 */
class SDLCombo:public SDLWidget
{
	public:
	/// Constructor
	SDLCombo();
	
	/// States of the combo
	enum comboState{ CLOSED, OPEN };
	
	/// \return The selected option string
	string getValue();
	
	/// \return The selected option's string
	string getSelectedString();
	
	/// Displays all widgets according to the state
	virtual void drawWidget(SDL_Surface* screen)
	{
		boxColor(screen, px1, py1, px2, py2, DARKERGRAY);
		button->drawWidget(screen);
		
		if (yazi != 0)
			yazi->drawWidget(screen);
		
		if (durum == OPEN)
		{
			for(int i=0;i<options.size();i++)
			{
				options[i].drawWidget(screen);
			}
		}
	}
	
	/// Handles mouse events, the function is redirected to handleEvent
	virtual void handleMouseEvent(int eventType, int button, int x, int y)
	{
		handleEvent(eventType, button, x, y);
	}
	
	/** Adds a new option
	 * 
	 * \param option is the string displayed
	 * \param value is the value of the option
	 * \param def is whether the option is default / selected
	 */
	void addOption(string option, string value, bool def=false);
	
	protected:
	/// SDLButton used for toggling
	SDLButton *button;
	
	/// State of the SDLCombo
	comboState durum;
	
	/// This holds the currently selected option as an SDLLabel
	SDLLabel *yazi;
	
	/// This is the vector of SDLComboOptions
	vector<SDLComboOption> options;
	
	/// Sets the state OPEN, so that the options are displayed
	void showOptions() { durum = OPEN; }
	
	/// Sets the state CLOSED, so that the options are not displayed
	void hideOptions() { durum = CLOSED; }
	
	/// Toggles showing and/or displaying options.
	/// This is connected to the button.
	void toggleOptions();
	
	/// Handles mouse events internally 
	/// @see handleMouseEvent
	void handleEvent(int eventType, int button, int x, int y);
};

#endif

