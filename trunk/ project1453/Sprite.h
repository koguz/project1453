#ifndef SPRITE_H_
#define SPRITE_H_

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "Headers.h"	

using namespace std;

struct Frame
{
	SDL_Rect frame;
	int frameDur;
};

class State
{
	public:
	string stateName; 
	vector<Frame> frames;
	int curFrameNo; 
	Uint32 lastTick;
	
	
	State();
	State(string sName);
	void addFrame(SDL_Rect s, int interval);
	void setName(string sName);
	SDL_Rect getCurFrame();
};

class Sprite
{
	private:
	map<string, State> states;
	string curState;
	SDL_Surface *img;
	
	public:
	Sprite();
	Sprite(char* f);
	Sprite(SDL_Surface *i);
	SDL_Rect getFrame();
	SDL_Surface* getImg();
	string getCurState();
	
	void addState(string sName);
	void setState(string sName);
	void addFrameToState(string sName, SDL_Rect f, int d); 
};

#endif /*SPRITE_H_*/
