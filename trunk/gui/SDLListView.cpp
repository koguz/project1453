#include "SDLListView.h"

SDLListViewItem::SDLListViewItem(SDLListView *p, string str)
{
	parent = p;
	value = str;
	durum = NORMAL;
	tip = LISTITEM;
	selected = false;
	
	yazi = new SDLLabel(str);
	w = parent->getWidth();
	h = 20; // fixed?
}

SDLListView::SDLListView(int rows)
{
	tip = LIST;
	lineHeight = 20;
	
	w = width = 200; // bu da sabit, sonra değiştir
	this->rows = rows;
	
	SDLListView *me = this;
	
	up = new SDLButton("img/up.png", "");
	down = new SDLButton("img/down.png", "");
	
	up->clicked = makeFunctor((CBFunctor0*)0, *me, &SDLListView::moveUp);
	down->clicked = makeFunctor((CBFunctor0*)0, *me, &SDLListView::moveDown);
	
	uppos = 0;
	downpos = 0;
	
}

void SDLListView::addItem(string item)
{
	SDLListViewItem temp(this, item);
	items.push_back(temp);
	lines = items.size();
	
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
		items[i].setPosition(px1, py1 + (lineHeight*j));
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
		if (items[i].isSelected())
		{
			return items[i].getValue();
		}
	}
	return "Seçili öğe yok!";
}

void SDLListView::handleEvent(int eventType, int button, int x, int y)
{
	up->handleMouseEvent(eventType, button, x, y);
	down->handleMouseEvent(eventType, button, x, y);
	for (int i=0;i<items.size();i++)
	{
		switch(eventType)
		{
			case SDL_MOUSEMOTION:
				if (items[i].isMouseOver(x, y) && !items[i].isSelected())
					items[i].setState(SDLListViewItem::OVER);
				else if(!items[i].isSelected())
					items[i].setState(SDLListViewItem::NORMAL);
				break;
			case SDL_MOUSEBUTTONDOWN:
				if (button == SDL_BUTTON_LEFT)
				{
					if(items[i].isMouseOver(x, y))
					{
						for (int j=0;j<items.size();j++)
							items[j].deSelect();
						items[i].setSelected();
						return;
					}
				}
				break;
		}
	}
}


