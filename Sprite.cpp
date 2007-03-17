#include "Sprite.h"

State::State()
{
	lastTick = 0;
	curFrameNo = 0;
}

State::State(string sName)
{
	lastTick = 0;
	curFrameNo = 0;
	setName(sName);
}

void State::setName(string sName)
{
	stateName = sName;
}

void State::addFrame(SDL_Rect s, int interval)
{
	Frame f;
	f.frame = s;
	f.frameDur = interval;
	frames.push_back(f);
}

SDL_Rect State::getCurFrame()
{
	Uint32 now = SDL_GetTicks();
	if ((now - lastTick) >= frames.at(curFrameNo).frameDur)
	{
		if ( (curFrameNo + 1) == frames.size())
			curFrameNo = 0;
		else ++curFrameNo;
		lastTick = now;
	}
	return frames.at(curFrameNo).frame;
}



/*****************************************
 * SPRITE
 * =======================================
 */


Sprite::Sprite()
{
	curState = "Not set";
}

Sprite::Sprite(char* f)
{
	SDL_Surface *t = IMG_Load(f);
	SDL_SetAlpha(t, SDL_SRCALPHA | SDL_RLEACCEL, SDL_ALPHA_OPAQUE);
	img = SDL_DisplayFormatAlpha(t);
}

Sprite::Sprite(SDL_Surface *i)
{
	img = i;
}

Sprite::~Sprite()
{
// 	SDL_FreeSurface(img);
}

void Sprite::addState(string sName)
{
	states[sName] = State(sName);
}

void Sprite::addFrameToState(string sName, SDL_Rect f, int d)
{
	states[sName].addFrame(f, d);
}

void Sprite::setState(string sName)
{
	curState = sName;
}

SDL_Surface* Sprite::getImg()
{
	return img;
}

SDL_Rect Sprite::getFrame()
{
	return states[curState].getCurFrame();
}

string Sprite::getCurState()
{
	return curState;
}

