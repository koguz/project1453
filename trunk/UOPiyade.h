#ifndef UO__PIYADE__H__
#define UO__PIYADE__H__

#include "BaseUnit.h"
#include "SDLMixer.h"
#include "Player.h"

class Piyade:public BaseUnit
{
	public:
	Piyade();
	Piyade(SDL_Surface *scr, Player *p);
	~Piyade();
	
	virtual void defaultAction(int tx, int ty)
	{
		defAct(tx, ty);
	}
	
	virtual void issueCommand(int x, int y)
	{
		command(x, y);
	}
	
	virtual void update()
	{
		BaseUnit::update();
		pUpdate();
	}
	
	virtual void playSelected()
	{ sndSelected->play(); }
	
	virtual void playConfirmed()
	{ sndConfirmed->play(); }
	
	static SDL_Surface* spriteImg;
	SDLMixer *sndSelected;
	SDLMixer *sndConfirmed;
	
	void defAct(int tx, int ty);
	void command(int x, int y);
	void pUpdate();
	void recurseTargetTiles(int tx, int ty);
	
	SDLCommandButton *resim, *yuru, *dur, *saldir;
};


#endif
