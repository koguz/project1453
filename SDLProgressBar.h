#ifndef SDLPROGBAR__H__
#define SDLPROGBAR__H__

#include <iostream>
#include <string>
#include "Headers.h"
#include "SDLWidget.h"
#include "SDLFont.h"

using namespace std;

/** \brief ProgressBar
 *
 * Simple progress bar. It does not handle any mouse events,
 * it also does not need a specific setPosition.
 * 
 * The default values for min and max values are 0 and 100 
 * respectively. 
 * 
 */
class SDLProgressBar:public SDLWidget
{
	public:
	/** \brief Constructor
	 * 
	 * \param w is the width of the progress bar
	 * \param h is the height of the progress bar
	 * \param c is the color used, some colors are defined at SDLWidget.h
	 * \param minimum is the minimum value the bar can have
	 * \param maximum is the maximum value the bar can have
	 */
	SDLProgressBar(int w, int h, Uint32 c=BLUE, int minimum=0, int maximum=100);
	
	/// The way the widget is drawn
	virtual void drawWidget(SDL_Surface *screen)
	{
		rectangleColor(screen, px1, py1, px2, py2, c);
		if (v!=min)
		{
			int val = (w * v)/max;
			boxColor(screen, px1+1, py1+1, px1+val, py2-1, c);
		}
	}
	
	/// \return The specific value between min and max
	int getValue() { return v; }
	
	/// Used for setting value between min and max.
	/// If the given value is not between these two, then
	/// it is ignored.
	void setValue(int p);
	
	protected:
	/// Color value
	Uint32 c;
	
	/// The value between min and max
	int v;
	
	/// Minimum value for bar
	int min;
	
	/// Maximum value for bar
	int max;
	
};



#endif
