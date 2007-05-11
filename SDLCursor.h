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
	static void set64();
	static void set64n();
	static void set96();
	static void set96n();
	static void set128();
	static void set128n();

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
		*oksw,
		*b64, // inşaa edilebilir, edilemez :P
		*b64n, 
		*b96,
		*b96n,
		*b128,
		*b128n;
};

#endif 

