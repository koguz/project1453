#ifndef EKRAN_H_
#define EKRAN_H_

#include <vector>
#include "SDLWidget.h"

using namespace std;

/* SDLScreen is like a Window class in a GUI application.
 * This class holds widgets; displays them and passes 
 * them the SDL_Event which is passed to it... 
 * It does not have a layout manager, so the widgets should be
 * placed manually on fixed positions
 */
class SDLScreen
{
	public:
	SDLScreen(SDL_Surface *scr);
	~SDLScreen();
	
	void addWidget(SDLWidget *w);
	virtual void display()
	{
		// SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 120, 120, 120));
		for (unsigned int i=0;i<widgets.size();i++)
		{
			if (widgets[i]->isShown())
				widgets[i]->drawWidget(screen);
		}
	}
	void eventHandler(SDL_Event *event);
	
	private:
	vector<SDLWidget*> widgets;
	SDL_Surface *screen;
};
	
#endif /*EKRAN_H_*/

