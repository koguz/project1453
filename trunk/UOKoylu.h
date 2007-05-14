#ifndef UO__KOYLU__H__
#define UO__KOYLU__H__

#include "SDLMixer.h"
#include "BaseUnit.h"
#include "BOEv.h"
#include "BOSehirMerkezi.h"

class Koylu:public BaseUnit
{
	public:
	Koylu();
	Koylu(SDL_Surface *scr, Player *p);
	~Koylu();
	
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
		kUpdate();
	}
	
	virtual void playSelected()
	{ sndSelected->play(); }
	
	virtual void playConfirmed()
	{ sndConfirmed->play(); }
	
	static SDL_Surface* spriteImg;
	void setCommandCalis();
	void setCommandMerkezYap();
	
	void command(int x, int y);
	void defAct(int tx, int ty);
	
	void buildBina(BaseBuilding* b);
	void kUpdate(); // koyluUpdate, isim bulamiyorum artik...
	
	BaseBuilding* insa;
	
	SDLMixer *sndSelected;
	SDLMixer *sndConfirmed;
	SDLCommandButton 
		*resim, 
		*yuru, 
		*dur, 
		*calis, 
		*smerkezi, 
		*ev,
		*tarla,
		*asker,
		*demirci,
		*maden;
};

#endif
