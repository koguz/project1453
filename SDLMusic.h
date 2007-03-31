#ifndef SDLMUSIC__H__
#define SDLMUSIC__H__
#include <iostream>
#include "Headers.h"

using namespace std;

class SDLMusic
{
	public:
	SDLMusic(char *f);
	~SDLMusic();
	bool SetMixer();
	void loadFile(char *f);
	void play();
	void setVolume(int oran);
	void pause();
	
	protected:
	Mix_Music *m;
	bool paused;
};

#endif
