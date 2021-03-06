#include "SDLListView.h"

SDLListViewItem::SDLListViewItem(SDLListView *p, string str)
{
	parent = p;
	value = str;
	durum = NORMAL;
	tip = LISTITEM;
	selected = false;
	
	yazi = new SDLLabel(str);
	if (yazi->getWidth() > parent->getWidth())
		w = yazi->getWidth() + 12;
	else w = parent->getWidth(); 
	h = 20; // fixed?
	show = true;
}

void SDLListViewItem::setSelected() { selected = true; }
void SDLListViewItem::deSelect() { selected = false; }
bool SDLListViewItem::isSelected() { return selected; }
string SDLListViewItem::getValue() { return value; }
void SDLListViewItem::setState(itemState it) { durum = it; }
SDLListViewItem::itemState SDLListViewItem::getState() { return durum; }
void SDLListViewItem::setWidth(int pw)
{
	w = pw; 
	px2 = px1 + w;
}


SDLListViewItem::~SDLListViewItem()
{
	delete yazi;
}


//////////////

SDLListView::SDLListView(int rows)
{
	tip = LIST;
	lineHeight = 20;
	show = true;
	w = 0; 
	this->rows = rows;
	h = lineHeight*rows;
	
	SDLListView *me = this;
	
	up = new SDLButton("ui/up.png", "");
	down = new SDLButton("ui/down.png", "");
	
	up->clicked = makeFunctor((CBFunctor0*)0, *me, &SDLListView::moveUp);
	down->clicked = makeFunctor((CBFunctor0*)0, *me, &SDLListView::moveDown);
	
	uppos = 0;
	downpos = 0;
	
}

SDLListView::~SDLListView()
{
	for(int i=0;i<items.size();i++)
	{
		SDLListViewItem *temp = items[i];
		items[i] = 0;
		delete temp;
	}
	items.clear();
	delete up;
	delete down;
}

void SDLListView::addItem(string item)
{
	SDLListViewItem *temp = new SDLListViewItem(this, item);
	
	items.push_back(temp);
	lines = items.size();
	
	if (temp->getWidth() > w)
	{
		w = temp->getWidth();
		px2 = px1 + w;
		up->setPosition(px1+w+1, py1);
		down->setPosition(px1+w+1, py2-down->getHeight()+1);
	}
	
	for (int i=0;i<items.size();i++)
		items[i]->setWidth(w);
	
	uppos = 0;
	if (lines < rows)
		downpos = lines;
	else downpos = rows;
	
	repositionItems();
}

void SDLListView::repositionItems()
{
	int j = 0;
	for (int i=uppos;i<downpos;i++)
	{
		items[i]->setPosition(px1, py1 + (lineHeight*j));
		j++;
	}
}

void SDLListView::moveUp()
{
	if (uppos > 0)
	{
		uppos--;
		downpos--;
		repositionItems();
	}
}

void SDLListView::moveDown()
{
	if (lines > downpos)
	{
		uppos++;
		downpos++;
		repositionItems();
	}
}

string SDLListView::getValue()
{
	for (int i=0;i<items.size();i++)
	{
		if (items[i]->isSelected())
		{
			return items[i]->getValue();
		}
	}
	return "NONE";
}

void SDLListView::setSelected(string val)
{
	bool changed = false;
	int d = 0;
	for(int i=0;i<items.size();i++)
	{
		if (items[i]->getValue() == val)
		{
			changed = true;
			d = i;
		}
	}
	
	if(changed)
	{
		for(int i=0;i<items.size();i++)
			items[i]->deSelect();
		items[d]->setSelected();
	}
}

void SDLListView::handleEvent(int eventType, int button, int x, int y)
{
	up->handleMouseEvent(eventType, button, x, y);
	down->handleMouseEvent(eventType, button, x, y);
// 	for (int i=0;i<items.size();i++)
	for (int i=uppos;i<downpos;i++)
	{
		switch(eventType)
		{
			case SDL_MOUSEMOTION:
				if (items[i]->isMouseOver(x, y) && !items[i]->isSelected())
					items[i]->setState(SDLListViewItem::OVER);
				else if(!items[i]->isSelected())
					items[i]->setState(SDLListViewItem::NORMAL);
				break;
			case SDL_MOUSEBUTTONDOWN:
				if (button == SDL_BUTTON_LEFT)
				{
					if(items[i]->isMouseOver(x, y))
					{
						for (int j=0;j<items.size();j++)
							items[j]->deSelect();
						items[i]->setSelected();
						return;
					}
				}
				break;
		}
	}
}


