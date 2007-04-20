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
	stringstream st(text);
	string buf;
	SDLLabel *temp = new SDLLabel(" "); 
	SDLLabel *t2;
	string satir = ""; // just to init...
	lines = 0;
	
	vector<string> parcalar;
	
	int kon = 0;
	while(st >> buf)
	{
		if ( buf == "[p]")
		{
			satirlar.push_back(temp);
			satirlar.push_back(new SDLLabel(" "));
			satir = "";
			temp = t2 = 0;
			continue;
		}
		else if ( buf == "[br]" )
		{
			satirlar.push_back(temp);
			satir = "";
			temp = t2 = 0;
			continue;
		}
		
		buf = buf + " ";
		t2 = new SDLLabel(satir + buf);
		if (t2->getWidth() > width)
		{
			satirlar.push_back(temp);
			temp = new SDLLabel(buf);
			satir = buf;
		}
		else
		{
			delete temp;
			temp = t2;
			satir = satir + buf;
		}
	}
	satirlar.push_back(temp);
	lines = satirlar.size();
	uppos = 0;
	if (lines < rows)
		downpos = lines;
	else downpos = rows;
	repositionLabels();
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


