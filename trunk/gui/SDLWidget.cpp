#include "SDLWidget.h"

SDLWidget::SDLWidget() {}

SDLWidget::SDLWidget(char *f)
{
	SDL_Surface *temp = IMG_Load(f);
	SDL_SetAlpha(temp, SDL_SRCALPHA | SDL_RLEACCEL, SDL_ALPHA_OPAQUE);
	widget = temp;
	if (widget == 0)
	{
		cout << "err" << endl;
	}
	w = widget->w;
	h = widget->h;
	px1 = px2 = py1 = py2 = 0;
	tip = WIDGET;
}



	