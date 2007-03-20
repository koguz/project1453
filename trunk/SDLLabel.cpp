#include "SDLLabel.h"

SDLLabel::SDLLabel()
{
	widget = 0;
	show = true;
	tip = LABEL;
}


SDLLabel::SDLLabel(string lbl)
{
	size = 14;
	setText(lbl);
	show = true;
	tip = LABEL;
}

SDLLabel::SDLLabel(int lbl)
{
	size = 14;
	stringstream ss;
	string tmp;
	ss << lbl;
	ss >> tmp;
	setText(tmp);
	show = true;
	tip = LABEL;
}

SDLLabel::~SDLLabel()
{
	
}

void SDLLabel::setText(int lbl)
{
	stringstream ss;
	string tmp;
	ss << lbl;
	ss >> tmp;
	label = tmp;
	setText(label);
}

void SDLLabel::setText(string lbl)
{
	label = lbl;
	SDL_Color c = { 255, 255, 255 };
	SDLFont t(label, size, c);
	SDL_FreeSurface(widget);
	widget = t.getString();
	w = widget->w;
	h = widget->h;
}


string SDLLabel::getText() { return label; }

