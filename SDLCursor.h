#ifndef SDLCURSOR__H__
#define SDLCURSOR__H__

#include "Headers.h"
#include "SDLWidget.h"

class SDLCursor
{
	public:
	static void setCursorTarget();
	static void setCursorMain();
	static SDLWidget *cCurrent, *cMain, *cTarget;
};

#endif 

