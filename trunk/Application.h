#ifndef APPLICATION_H_
#define APPLICATION_H_

#include <iostream>
#include <string>
#include "Headers.h"
#include "SDLScreen.h"
#include "ScreenMain.h"
#include "ScreenGameType.h"
#include "Game.h"
#include "Player.h"
#include "callback.h"

using namespace std;

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
	SDLProgressBar *pb;
	Game *game;
	
	public:
	SDL_Surface* screen;
	Application(string appName, int w, int h, int d, unsigned int f);
	
	bool Init();
	int Run();
	void screenMain();
	void screenGameType();
	void startSingleGame();
	void Quit();
};

#endif /*APPLICATION_H_*/
