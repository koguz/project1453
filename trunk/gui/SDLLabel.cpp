#include "SDLLabel.h"

SDLLabel::SDLLabel()
{
	widget = 0;
}


SDLLabel::SDLLabel(string lbl)
{
	size = 14;
	setText(lbl);
}

void SDLLabel::setText(string lbl)
{
	label = lbl;
	SDL_Color c = { 255, 255, 255 };
	SDLFont t(label, size, c);
	widget = t.getString();
	w = widget->w;
	h = widget->h;
}

