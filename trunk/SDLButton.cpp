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
		metin = new SDLLabel(label);
	}
	else metin = 0;
	clicked = 0;
}

void SDLButton::handleEvent(int eventType, int button, int x, int y)
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
// 					if (clicked != 0)
// 						clicked();
				}
			}
			break;
		case SDL_MOUSEBUTTONUP:
			if (button == SDL_BUTTON_LEFT)
			{
				if (isMouseOver(x, y) && getState() == PRESSED)
				{
					setState(NORMAL);
					if (clicked != 0)
						clicked();
				}
				else setState(NORMAL);
			}
			break;
	}
}
