#ifndef SDLCURSOR__H__
#define SDLCURSOR__H__

#include "Headers.h"
#include "SDLWidget.h"

class SDLCursor
{
	public:
	static void setCursorTarget();
	static void setCursorMain();
	static void setE();
	static void setS();
	static void setW();
	static void setN();
	static void setNe();
	static void setNw();
	static void setSe();
	static void setSw();
	
	static bool locked;
	
	static void updateAll(int x, int y);
	
	static SDLWidget 
		*cCurrent, // simdiki
		*temp, // gecici
		*cMain, // bildigimiz el
		*cTarget, // hedef!
		*oke, // oklar
		*oks, 
		*okw,
		*okn,
		*okne,
		*oknw,
		*okse,
		*oksw;
};

#endif 

