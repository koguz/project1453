#include "SDLButton.h"

using namespace std;

SDLButton::SDLButton(string f, string label=string(), int size)
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
		if (size == -1)
			metin = new SDLLabel(label);
		else
			metin = new SDLLabel(label, size);
	}
	else metin = 0;
	clicked = 0;
	show = true;
	over = new SDLMixer("wavs/ui/over.ogg");
	click = new SDLMixer("wavs/ui/click.ogg");
	playOnce = false;
}

SDLButton::~SDLButton()
{
	delete metin;
	delete over;
	delete click;
}

void SDLButton::setState(ButtonState s) { bState = s; }
SDLButton::ButtonState SDLButton::getState() { return bState; }


void SDLButton::handleEvent(int eventType, int button, int x, int y)
{
	switch(eventType)
	{
		case SDL_MOUSEMOTION:
			if ( isMouseOver(x, y) && getState() != PRESSED )
			{
				setState(SDLButton::OVER);
				if (!playOnce)
				{
					over->play();
					playOnce = true;
				}
			}
			else if (getState() != PRESSED)
			{
				setState(NORMAL);
				playOnce = false;
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
					if (clicked != 0)
					{
						click->play();
						clicked();
					}
				}
				setState(NORMAL);
			}
			break;
	}
}
