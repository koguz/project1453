#ifndef EKRAN_H_
#define EKRAN_H_

#include <vector>
#include "Headers.h"
#include "SDLWidget.h"
#include "SDLButton.h"
#include "SDLCombo.h"
#include "SDLLabel.h"
#include "SDLCheckBox.h"
#include "SDLTextView.h"

using namespace std;

class SDLScreen
{
	public:
	SDLScreen(SDL_Surface *scr);
	void addWidget(SDLWidget *w);
	void display();
	void eventHandler(SDL_Event *event);
	
	private:
	vector<SDLWidget*> widgets;
	SDL_Surface *screen;
};
	
#endif /*EKRAN_H_*/

