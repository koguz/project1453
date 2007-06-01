#ifndef UO__KOYLU__H__
#define UO__KOYLU__H__

#include "SDLMixer.h"
#include "BaseUnit.h"
#include "BOEv.h"
#include "BOSehirMerkezi.h"
#include "BOAsker.h"

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
	
	virtual void cancelActions()
	{
		BaseUnit::cancelActions();
		iptal();
	}
	
	virtual void playSelected()
	{ sndSelected->play(); }
	
	virtual void playConfirmed()
	{ sndConfirmed->play(); }
	
	static SDL_Surface* spriteImg;
	void setCommandCalis();
	void setCommandMerkezYap();
	void setCommandEvYap();
	void setCommandAskerOcagiYap();
	
	void iptal();
	
	void command(int x, int y);
	void defAct(int tx, int ty);
	
	void recurseTargetTiles(int tx, int ty);
	
	void goToAndBuild(int x, int y, int s);
	void buildBina(BaseBuilding* b);
	void kUpdate(); // koyluUpdate, isim bulamiyorum artik...
	
	BaseBuilding* insa;
	int insax, insay; // insaa koordinatlari
	
	SDLMixer *sndSelected, *sndBuilding, *sndOk, *sndTamam;
	SDLMixer *sndConfirmed, *sndHata;
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
