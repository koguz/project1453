#include "SDLTextView.h"


SDLTextView::SDLTextView(string text, int w, int r)
{
	tip = SDLWidget::TEXTVIEW;
	lineHeight = 20; // sonra degisecek...
	
	metin = text;
	width = w;
	rows = r;
	
	show = true;
	
	satirlar.clear();
	lines = 0;
	setText(text);
	
	SDLTextView *me = this;
	
	up = new SDLButton("ui/up.png", "");
	down = new SDLButton("ui/down.png", "");
	
	up->clicked = makeFunctor((CBFunctor0*)0, *me, &SDLTextView::moveUp);
	down->clicked = makeFunctor((CBFunctor0*)0, *me, &SDLTextView::moveDown);
	
	uppos = 0;
	if (lines < r)
		downpos = lines;
	else downpos = r;
}

SDLTextView::~SDLTextView()
{
	delete up;
	delete down;
	for(int i=0;i<satirlar.size();i++)
		delete satirlar[i];
}


string SDLTextView::getText() { return metin; }

void SDLTextView::setText(string text)
{
	for(int i=0;i<satirlar.size();i++)
		delete satirlar[i];
	
	satirlar.clear();
	
	stringstream ss(text);
	string buf;
	SDLLabel *temp;
	lines = 0;
	
	while(getline(ss, buf, '\n'))
	{
		temp = new SDLLabel(buf);
		satirlar.push_back(temp);
		lines++;
	}
}

void SDLTextView::repositionLabels()
{
	int j = 0;
	for (int i=uppos;i<downpos;i++)
	{
		// sağdan 4 piksel içe- bir de satir boyuna göre ortalama...
		satirlar[i]->setPosition(px1+4, py1+(lineHeight*j)+((lineHeight-satirlar[i]->getHeight()) / 2));
		j++;
	}
}

void SDLTextView::moveUp()
{
	if (uppos > 0)
	{
		uppos--;
		downpos--;
		repositionLabels();
	}
}

void SDLTextView::moveDown()
{
	if (lines > downpos)
	{
		uppos++;
		downpos++;
		repositionLabels();
	}
}


void SDLTextView::handleEvent(int eventType, int button, int x, int y)
{
	up->handleMouseEvent(eventType, button, x, y);
	down->handleMouseEvent(eventType, button, x, y);
}


