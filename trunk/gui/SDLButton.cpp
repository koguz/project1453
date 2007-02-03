#include "SDLButton.h"

using namespace std;

SDLButton::SDLButton(string f, string label=string())
{
	SDL_Surface *temp = IMG_Load(f.c_str());
	SDL_SetAlpha(temp, SDL_SRCALPHA | SDL_RLEACCEL, SDL_ALPHA_OPAQUE);
	widget = temp;
	if (widget == 0)
	{
		cout << "err" << endl;
	}
	w = widget->w;
	h = widget->h / 3;
	px1 = px2 = py1 = py2 = 0;

	bState = NORMAL;
	tip = BUTTON;
	if (label.size() != 0)
	{
		SDL_Color c = { 255, 255, 255 };
		SDLFont t2(label, 16, c);
		metin = t2.getString();
	}
	else metin = 0;
}

bool SDLButton::isMouseOver(int mx, int my)
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

void SDLButton::handleMouseEvent(int eventType, int button, int x, int y)
{
	switch(eventType)
	{
		case SDL_MOUSEMOTION:
			if ( isMouseOver(x, y) && getState() != PRESSED )
			{
				setState(SDLButton::OVER);
			}
			else if (getState() != PRESSED)
			{
				setState(NORMAL);
			}
			break;
		case SDL_MOUSEBUTTONDOWN:
			if (button == SDL_BUTTON_LEFT)
			{
				if (isMouseOver(x, y))
				{
					setState(PRESSED);
					if (clicked != 0)
						clicked();
				}
			}
			break;
		case SDL_MOUSEBUTTONUP:
			if (button == SDL_BUTTON_LEFT)
			{
				if (isMouseOver(x, y))
				{
					setState(OVER);
				}
				else setState(NORMAL);
			}
			break;
	}
}
