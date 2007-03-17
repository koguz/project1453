#include "SDLProgressBar.h"


SDLProgressBar::SDLProgressBar(int pw, int ph, Uint32 color, int pmin, int pmax)
{
	c = color;
	w = pw;
	h = ph;
	v = pmin;
	min = pmin;
	max = pmax;
	show = true;
	tip = PROGRESSBAR;
}

SDLProgressBar::~SDLProgressBar()
{ }

void SDLProgressBar::setValue(int p)
{
	if (p>max || p<min)
		return;
	else 
		v = p;
}

int SDLProgressBar::getValue() { return v; }
void SDLProgressBar::setMax(int m) { max = m; }

