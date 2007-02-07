#ifndef SDLLABEL__H_
#define SDLLABEL__H_

#include <iostream>
#include <string>
#include "Headers.h"
#include "SDLWidget.h"
#include "SDLFont.h"


using namespace std;
/** \brief Simple label widget
 * 
 * SDLLabel is a simple label widget which holds a 
 * string. This function will be expanded when a new
 * SDLFont class arrives.
 * @see SDLFont
 * \author Kaya Oguz
 * \date 2007.02
 */
class SDLLabel:public SDLWidget
{
	public: 
	SDLLabel(); /// Basic constructor
	
	/** \param lbl is the string to be used */
	SDLLabel(string lbl); 
	
	virtual void drawWidget(SDL_Surface *screen)
	{
		SDL_Rect dest;
		
		dest.x = px1;
		dest.y = py1;
		dest.w = widget->w;
		dest.h = widget->h;
		
		SDL_BlitSurface(widget, NULL, screen, &dest);
	}
	
	/** \brief Sets label text
	 *
	 * This function resets the text of the 
	 * label.
	 * \param lbl is the new string
	 */
	void setText(string lbl);
	
	/// \return the text of the label
	string getText() { return label; }
	
	protected:
	/// Holds the string which the SDLLabel displays
	string label;
	
	/// Size of the font of the widget. This is fixed until a new version arrives
	int size; 
};



#endif

