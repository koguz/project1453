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
	void stop();
	static void setVolume(int oran);
	static int getVolume();
	void pause();
	static bool musicOn;
	static bool isPlaying();
	
	protected:
	Mix_Music *m;
	bool paused;
};

#endif
