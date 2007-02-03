#ifndef APPLICATION_H_
#define APPLICATION_H_

#include <iostream>
#include <string>
#include "Headers.h"
#include "SDLScreen.h"
#include "callback.h"

using namespace std;

class Application
{
	// Application is an SDL application
	private:
	string appName;
	string error;
	int width, height, bpp;  
	unsigned int flags; // for initializing
	bool done;
	SDLScreen *current;
	
	public:
	SDL_Surface* screen; // ana penceremiz
	Application(string appName, int w, int h, int d, unsigned int f);
	
	bool Init();
	int Run();
	void Quit();
};

#endif /*APPLICATION_H_*/
