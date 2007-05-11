#include "SDLCursor.h"

bool SDLCursor::locked = false;

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
SDLWidget* SDLCursor::b64 = new SDLWidget("ui/insa64.png");
SDLWidget* SDLCursor::b64n = new SDLWidget("ui/insa64n.png");
SDLWidget* SDLCursor::b96 = new SDLWidget("ui/insa96.png");
SDLWidget* SDLCursor::b96n = new SDLWidget("ui/insa96n.png");
SDLWidget* SDLCursor::b128 = new SDLWidget("ui/insa128.png");
SDLWidget* SDLCursor::b128n = new SDLWidget("ui/insa128n.png");
	
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
	
	int tx = x / 32;
	int ty = y / 32;
	
	// uff kopya cekiyoruz burada, 10 ve 25 haritanin 
	// offset degerleri
	b64->setPosition(tx*32 + 10, ty*32 + 25);
	b64n->setPosition(tx*32 + 10, ty*32 + 25);
	b96->setPosition(tx*32 + 10, ty*32 + 25);
	b96n->setPosition(tx*32 + 10, ty*32 + 25);
	b128->setPosition(tx*32 + 10, ty*32 + 25);
	b128n->setPosition(tx*32 + 10, ty*32 + 25);
}

void SDLCursor::setCursorTarget() { cCurrent = cTarget; }
void SDLCursor::setCursorMain() { cCurrent = cMain; }

void SDLCursor::setE() { if (!locked) cCurrent = oke; }
void SDLCursor::setS() { if (!locked) cCurrent = oks; }
void SDLCursor::setW() { if (!locked) cCurrent = okw; }
void SDLCursor::setN() { if (!locked) cCurrent = okn; }
void SDLCursor::setNe() { if (!locked) cCurrent = okne; }
void SDLCursor::setNw() { if (!locked) cCurrent = oknw; }
void SDLCursor::setSe() { if (!locked) cCurrent = okse; }
void SDLCursor::setSw() { if (!locked) cCurrent = oksw; }


void SDLCursor::set64() { if (!locked) cCurrent = b64; }
void SDLCursor::set64n() { if (!locked) cCurrent = b64n; }
void SDLCursor::set96() { if (!locked) cCurrent = b96; }
void SDLCursor::set96n() { if (!locked) cCurrent = b96n; }
void SDLCursor::set128() { if (!locked) cCurrent = b128; }
void SDLCursor::set128n() { if (!locked) cCurrent = b128n; }



