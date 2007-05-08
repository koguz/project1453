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
		moveToTarget(tx, ty);
	}
	
	virtual void issueCommand(int x, int y)
	{
		if (waitingCommand == "yuru")
		{
			waiting = false;
			moveToTarget(x, y);
		}
	}
	
	virtual void playSelected()
	{ sndSelected->play(); }
	
	virtual void playConfirmed()
	{ sndConfirmed->play(); }
	
	static SDL_Surface* spriteImg;
	void setCommandCalis();
	
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
