#include "SDLMusic.h"

bool SDLMusic::musicOn = true;

SDLMusic::SDLMusic(char *f)
{
	int audio_rate = 44100;
	Uint16 audio_format = AUDIO_S16;
	int audio_channels = 2;
	int audio_buffers = 4096; // 4096;
	
	
	if(Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers!=0))
	{
		cerr << "Ses sistemi açılamadı" << endl;
	}
	
	m = 0;
	loadFile(f);
	
	paused = false;
}


SDLMusic::~SDLMusic()
{
	Mix_FreeMusic(m);
	m = NULL;
}

void SDLMusic::play()
{
	Mix_PlayMusic(m, 1);
}

void SDLMusic::stop()
{
	Mix_HaltMusic();
}

bool SDLMusic::isPlaying()
{
	if (Mix_PlayingMusic() == 1)
		return true;
	else return false;
}

int SDLMusic::getVolume()
{
	return Mix_VolumeMusic(-1);
}

void SDLMusic::loadFile(char *f)
{
	if (m != 0)
		Mix_FreeMusic(m); // sismesin :)
	
	m = Mix_LoadMUS(f);
	if (!m)
	{
		cerr << "Müzik yüklenemedi: " << f << endl;
	}
	
// 	setVolume(2);
}

void SDLMusic::setVolume(int oran)
{
	Mix_VolumeMusic(MIX_MAX_VOLUME/oran);
}

void SDLMusic::pause()
{
	if (paused)
	{
		Mix_ResumeMusic();
		paused = false;
	}
	else 
	{
		Mix_PauseMusic();
		paused = true;
	}
}

