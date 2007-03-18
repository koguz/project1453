#include "SDLMixer.h"

SDLMixer::SDLMixer(char *f, bool loop)
{
	if(SetMixer())
	{
		this->loop = loop;
		loadFile(f);
	}
}

SDLMixer::~SDLMixer()
{
	Mix_FreeChunk(ses);
	ses = NULL;
}

bool SDLMixer::SetMixer()
{
	int audio_rate = 44100;
	Uint16 audio_format = AUDIO_S16;
	int audio_channels = 2;
	int audio_buffers = 4096;
	
	if(Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers!=0))
	{
		cerr << "Ses sistemi açılamadı" << endl;
		return false;
	}
	return true;
}

bool SDLMixer::loadFile(char *f)
{ 
	ses = Mix_LoadWAV(f); 
	if (ses == NULL)
	{
		cerr << "Ses yüklenemedi" << endl;
		return false;
	}
	else return true;
}

void SDLMixer::play()
{
	int l;
	if (loop)
		l = -1;
	else l = 0;
	musicChannel = Mix_PlayChannel(-1, ses, l);
}

