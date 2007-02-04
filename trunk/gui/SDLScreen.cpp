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

void SDLScreen::display()
{
	SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 120, 120, 120));
	for (unsigned int i=0;i<widgets.size();i++)
	{
		widgets[i]->drawWidget(screen);
	}
}

void SDLScreen::eventHandler(SDL_Event *event)
{
	int mx, my;
	mx = event->motion.x;
	my = event->motion.y;
	for (unsigned int i=0;i<widgets.size();i++)
	{
		widgets[i]->handleMouseEvent(event->type, event->button.button, mx, my);
// 		if (widgets[i]->getType() == SDLWidget::BUTTON)
// 		{
// 			SDLButton* t = (SDLButton*) widgets[i];
// 			t->handleMouseEvent(event->type, event->button.button, mx, my);
// 		}
// 		else if (widgets[i]->getType() == SDLWidget::COMBO)
// 		{
// 			SDLCombo *c = (SDLCombo*) widgets[i];
// 			if (c->button != 0)
// 				c->button->handleMouseEvent(event->type, event->button.button, mx, my);
// 			c->handleMouseEvent(event->type, event->button.button, mx, my);
// 			
// 		}
// 		else if (widgets[i]->getType() == SDLWidget::CHECKBOX)
// 		{
// 			SDLCheckBox* c = (SDLCheckBox*) widgets[i];
// 			c->handleMouseEvent(event->type, event->button.button, mx, my);
// 		}
// 		else if (widgets[i]->getType() == SDLWidget::TEXTVIEW)
// 		{
// 			SDLTextView *t = (SDLTextView*) widgets[i];
// 			t->handleMouseEvent(event->type, event->button.button, mx, my);
// 		}
	}
}


