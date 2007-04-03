#include "SDLCursor.h"

SDLWidget* SDLCursor::cMain = new SDLWidget("ui/cursorMain.png");
SDLWidget* SDLCursor::cTarget = new SDLWidget("ui/cursorTarget.png");
	
SDLWidget* SDLCursor::cCurrent = cMain;

void SDLCursor::setCursorTarget()
{
	cCurrent = cTarget;
}
void SDLCursor::setCursorMain()
{
	cCurrent = cMain;
}


