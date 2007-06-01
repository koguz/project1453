#ifndef SDLCURSOR__H__
#define SDLCURSOR__H__

#include "Headers.h"
#include "SDLWidget.h"

/* In fact SDL supports only black and white 
 * mouse cursors. This is a built-in feature. 
 * So, to have a color cursor, the real mouse 
 * is disabled, and an image is drawn at the 
 * position of the mouse :) 
 * 
 * To make all of the classes access and change
 * the cursor, it's made global, it consists of 
 * static members.
 */

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

