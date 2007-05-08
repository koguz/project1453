#include "SDLCursor.h"

SDLWidget* SDLCursor::cMain = new SDLWidget("ui/cursorMain.png");
SDLWidget* SDLCursor::cTarget = new SDLWidget("ui/cursorTarget.png");
SDLWidget* SDLCursor::oke = new SDLWidget("ui/oke.png");
SDLWidget* SDLCursor::oks = new SDLWidget("ui/oks.png"); 
SDLWidget* SDLCursor::okw = new SDLWidget("ui/okw.png");
SDLWidget* SDLCursor::okn = new SDLWidget("ui/okn.png");
SDLWidget* SDLCursor::okne = new SDLWidget("ui/okne.png");
SDLWidget* SDLCursor::oknw = new SDLWidget("ui/oknw.png");
SDLWidget* SDLCursor::okse = new SDLWidget("ui/okse.png");
SDLWidget* SDLCursor::oksw = new SDLWidget("ui/oksw.png");
	
SDLWidget* SDLCursor::cCurrent = cMain;

void SDLCursor::updateAll(int x, int y)
{
	cMain->setPosition(x, y);
	cTarget->setPosition(x, y);
	
	oke->setPosition(x-32, y-16);
	oks->setPosition(x-16, y-32);
	okw->setPosition(x, y-16);
	okn->setPosition(x-16, y);
	okne->setPosition(x-32, y);
	oknw->setPosition(x, y);
	okse->setPosition(x-32, y-32);
	oksw->setPosition(x, y-32);
}

void SDLCursor::setCursorTarget() { cCurrent = cTarget; }
void SDLCursor::setCursorMain() { cCurrent = cMain; }

void SDLCursor::setE() { cCurrent = oke; }
void SDLCursor::setS() { cCurrent = oks; }
void SDLCursor::setW() { cCurrent = okw; }
void SDLCursor::setN() { cCurrent = okn; }
void SDLCursor::setNe() { cCurrent = okne; }
void SDLCursor::setNw() { cCurrent = oknw; }
void SDLCursor::setSe() { cCurrent = okse; }
void SDLCursor::setSw() { cCurrent = oksw; }



