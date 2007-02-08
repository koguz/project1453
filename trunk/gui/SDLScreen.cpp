#include "SDLScreen.h"

using namespace std;

SDLScreen::SDLScreen(SDL_Surface *scr)
{
	screen = scr;
}

void SDLScreen::addWidget(SDLWidget *w)
{
	widgets.push_back(w);
}

void SDLScreen::eventHandler(SDL_Event *event)
{
	int mx, my;
	mx = event->motion.x;
	my = event->motion.y;
	for (unsigned int i=0;i<widgets.size();i++)
	{
		widgets[i]->handleMouseEvent(event->type, event->button.button, mx, my);
	}
}


