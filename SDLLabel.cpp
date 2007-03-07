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

SDLLabel::SDLLabel(int lbl)
{
	size = 14;
	stringstream ss;
	string tmp;
	ss << lbl;
	ss >> tmp;
	setText(tmp);
}

void SDLLabel::setText(int lbl)
{
	stringstream ss;
	string tmp;
	ss << lbl;
	ss >> tmp;
	label = tmp;
	SDL_Color c = { 255, 255, 255 };
	SDLFont t(label, size, c);
	widget = t.getString();
	w = widget->w;
	h = widget->h;
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

