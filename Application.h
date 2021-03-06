#ifndef APPLICATION_H_
#define APPLICATION_H_

#include <iostream>
#include <string>
#include "Headers.h"
#include "SDLScreen.h"
#include "ScreenMain.h"
#include "ScreenGameType.h"
#include "ScreenSettings.h"
#include "ScreenCredits.h"
#include "SDLMusic.h"
#include "SDLCursor.h"
#include "Game.h"
#include "callback.h"

using namespace std;

/* There is only one Application object 
 * throughout the whole game. It is also
 * responsible for initializing SDL and 
 * manages the Screens
 */
class Application
{
	private:
	string appName;
	string error;
	int width, height, bpp;  
	unsigned int flags; 
	bool done;
	SDLScreen *current;
	ScreenMain *ana;
	ScreenGameType *gt;
	ScreenSettings *ayar;
	ScreenCredits *emek;
	Game *game;
	SDLMusic *muse;
	SDLLabel *lblFps;
	bool showFps;
	
	public:
	SDL_Surface* screen;
	Application(string appName, int w, int h, int d, unsigned int f);
	~Application();
	
	bool Init();
	int Run();
	void screenMain();
	void screenGameType();
	void screenSettings();
	void screenCredits();
	void startSingleGame();
	void Quit();
};

#endif /*APPLICATION_H_*/
