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
	show = true;
}


bool SDLWidget::isMouseOver(int mx, int my)
{
	if (
		(mx > px1) &&
		(mx < px2) &&
		(my > py1) &&
		(my < py2)
		)
		return true;
	else return false;
}


SDLWidget::WidgetType SDLWidget::getType() { return tip; }
bool SDLWidget::isShown() { return show; }
void SDLWidget::setShow(bool b) { show = b; }

int SDLWidget::getWidth() { return w; }
int SDLWidget::getHeight() { return h; }
SDL_Surface* SDLWidget::getWidget() { return widget; }


