#include "SDLLabel.h"

SDLLabel::SDLLabel()
{
	widget = 0;
}

SDLLabel::SDLLabel(string lbl)
{
	label = lbl;
	SDL_Color c = { 255, 255, 255 };
	SDLFont t(label, 16, c);
	widget = t.getString();
}

