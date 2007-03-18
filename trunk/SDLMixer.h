#ifndef SDLMIXER__H__
#define SDLMIXER__H__
#include <iostream>
#include "Headers.h"

using namespace std;

class SDLMixer
{
	public:
	SDLMixer(char *f, bool loop);
	~SDLMixer();
	bool SetMixer();
	bool loadFile(char *f);
	void play();
	
	protected:
	Mix_Chunk *ses;
	int musicChannel;
	bool loop;
};

#endif
