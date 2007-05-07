#include "Map.h"

SDL_Surface* loadimg(char* f)
{
	SDL_Surface *temp = IMG_Load(f);
	SDL_SetAlpha(temp, SDL_SRCALPHA | SDL_RLEACCEL, SDL_ALPHA_OPAQUE);
	return temp;
}

SDL_Surface* MapTile::tileList = loadimg("graphics/terrain/tiles.png");
SDL_Surface* MapTile::screen = 0;

MapTile::MapTile()
{
	tip = CIM;
	unexplored = false; // sonra true
}

void MapTile::setType(tileType t)
{
	tip = t;
}

void MapTile::draw(SDL_Rect src, SDL_Rect dest)
{
	if (unexplored)
	{
		boxColor(screen, dest.x, dest.y, dest.x + dest.w, dest.y + dest.h, 0x000000FF);
		return;
	}
	switch(tip)
	{
		case CIM:
			break;
		case SARICIM:
			src.x += 96;
			src.y += 96;
			break;
		case TOPRAK:
			src.x += 192;
			src.y += 32;
			break;
		case AGAC:
			src.x += 160;
			src.y += 96;
			break;
		case AGACKESIK:
			src.x += 128;
			src.y += 96;
			break;
		case DAGLIK:
			src.x += 32;
			src.y += 160;
			break;
		case DENIZ:
			src.x += 160;
			src.y += 32;
			break;
	}
	SDL_BlitSurface(tileList, &src, screen, &dest);
// 	rectangleColor(screen, dest.x, dest.y, dest.x+dest.w, dest.y+dest.h, 0x000000FF);
}

MapTile::tileType MapTile::getTip() { return tip; }
bool MapTile::isExplored() { return !unexplored; }
void MapTile::setExplored() { unexplored = false; }


//////////////////// MAP /////////////////////////


Map::Map(SDL_Surface* scr, int w, int h)
{
	screen = scr;
	MapTile::screen = screen;
	tx = w; ty = h;
	
	rw = tx*TILESIZE;
	rh = ty*TILESIZE;
	
	human = cpu = 0; // sonra güncellenecekler
	rsx1 = rsx2 = rsy1 = rsy2 = -1;
	multipleSelect = false;
	drawing = dragging = false;
	
	tiles = new MapTile*[w];
	for(int i=0;i<w;i++)
		tiles[i] = new MapTile[h];
	
	scroll = true; 
	
	// aslında şu kisim... bu kisim dosyadan, ya da db'den
	for(int i=0;i<w;i++)
	{
		for(int j=0;j<h;j++)
		{
			switch(rand() % 1)
			{
				case 0:
					tiles[i][j].setType(MapTile::CIM);
					break;
				case 1:
					tiles[i][j].setType(MapTile::SARICIM);
					break;
				case 2:
					tiles[i][j].setType(MapTile::TOPRAK);
					break;
				case 3:
					tiles[i][j].setType(MapTile::AGAC);
					break;
				case 4:
					tiles[i][j].setType(MapTile::AGACKESIK);
					break;
				case 5:
					tiles[i][j].setType(MapTile::DAGLIK);
					break;
				case 6:
					tiles[i][j].setType(MapTile::DENIZ);
					break;
			}
		}
	}
	startpx = 1;
	startpy = 0;
	startcx = 2000;
	startcy = 2000; 
	
	vx = vy = ax = ay = 0;
	cx = 0; cy = 0; // aslında bu da map'ten okunacak
}

int Map::getPx() { return startpx; }
int Map::getPy() { return startpy; }
int Map::getCpux() { return startcx; }
int Map::getCpuy() { return startcy; }


bool Map::isMultipleSelecting() { return (drawing && dragging); }


void Map::setPlayers(Player* h, Player* c)
{
	human = h;
	cpu = c;
}

void Map::setOrigin(int x, int y)
{
	ox=x; 
	oy=y;
}

void Map::setCurrentX(int x)
{
	if (x < 0)
		x = 0;
	if (x >= rw - pw)
		x = rw - pw - 1;
	cx = x; 
}

void Map::setCurrentY(int y)
{
	if (y < 0)
		y = 0;
	
	if (y >= rh - ph)
		y = rh - ph - 1;
	cy = y; 
}

void Map::setCurrent(int x, int y)
{	
	setCurrentX(x);
	setCurrentY(y);
}
	
int Map::getCx() 
{ 
	return cx; 
}
	
int Map::getCy() 
{ 
	return cy; 
}
	
void Map::setPane(int w, int h)
{ 
	pw=w; 
	ph=h; 
}

void Map::update()
{
	if (!scroll) return;
	int top = ACC*14;
	if (vx != top && vx != -top && ax != 0)
		vx += ax;
	else if ( ((vx == top) || (vx == -top)) && ax != 0)
	{ }
	else
		vx = 0;
	
	if (vy != top && vy != -top && ay != 0)
		vy += ay;
	else if ( ((vy == top) || (vy == -top)) && ay != 0)
	{ }
	else
		vy = 0;
	
	if (vx != 0)
		setCurrentX(getCx()+vx);
	if (vy != 0)
		setCurrentY(getCy()+vy);
}



void Map::drawMiniMap()
{
	int mwx = tx*2;
	int mwy = ty*2;
	int sx = 0, sy = 0, ex = 0, ey = 0;
	rectangleColor(screen, mmx-1, mmy-1, mmx+mwx+1, mmy+mwy+1, 0xFFFFFFFF);
	for(int i=0;i<tx;i++)
	{
		for(int j=0;j<ty;j++)
		{
			sx = mmx + (i*2);
			sy = mmy + (j*2);
			ex = sx + 2;
			ey = sy + 2;
			if (!tiles[i][j].isExplored())
				boxColor(screen,sx, sy, ex, ey, 0x000000FF);
			else
			{
				switch(tiles[i][j].getTip())
				{
					case MapTile::CIM:
						boxColor(screen,sx, sy, ex, ey, 0x054D00FF);
						break;
					case MapTile::SARICIM:
						boxColor(screen,sx, sy, ex, ey, 0xCDC30DFF);
						break;
					case MapTile::TOPRAK:
						boxColor(screen,sx, sy, ex, ey, 0x5E3001FF);
						break;
					case MapTile::AGAC:
						boxColor(screen,sx, sy, ex, ey, 0x043A0BFF);
						break;
					case MapTile::AGACKESIK:
						boxColor(screen,sx, sy, ex, ey, 0x065B12FF);
						break;
					case MapTile::DAGLIK:
						boxColor(screen,sx, sy, ex, ey, 0x5B5B5BFF);
						break;
					case MapTile::DENIZ:
						boxColor(screen,sx, sy, ex, ey, 0x093284FF);
						break;
					default:
						boxColor(screen,sx, sy, ex, ey, 0x000000FF);
					break;
				}
			}
		}
	}
	
	for (int i=0;i<human->units.size();i++)
	{
		sx = mmx + (human->units[i]->getTx()*2);
		sy = mmy + (human->units[i]->getTy()*2);
		ex = sx + 2;
		ey = sy + 2;
		boxColor(screen,sx, sy, ex, ey, 0xFFFFFFFF);
	}
	
	sx = mmx + cx/16;
	sy = mmy + cy/16;
	
	ex = mmx + (cx+pw)/16 + 1;
	ey = mmy + (cy+ph)/16 + 1;
	
	rectangleColor(screen, sx, sy, ex, ey, 0xFFFFFFFF);
}
	
void Map::setMiniMapPos(int x, int y)
{
	mmx = x;
	mmy = y;
}

void Map::draw()
{
	drawMiniMap();
	xb = cx/TILESIZE; // kaçıncı tile'dan başlıcas (0'dan say)
	xs = (cx+pw)/TILESIZE; // kaçıncı tile'a kadar  "   "
	yb = cy/TILESIZE;
	ys = (cy+ph)/TILESIZE;
	SDL_Rect s, d; // source ve dest
	int nx = -1, ny = -1;
	bool tmm = false;
	for (int i=xb;i<=xs;i++)
	{
// 		nx = -1;
		ny = -1;
		for (int j=yb;j<=ys;j++)
		{
			// önce x'leri ve w'leri
			if (i*TILESIZE <= cx)
			{
				s.x = cx - (i*TILESIZE);
				s.w = d.w = ( ((i+1) * TILESIZE) - cx );
				if (!tmm)
				{
					tmm = true;
					d.x = ox + (i-xb)*TILESIZE;
					nx = d.x + s.w;
				}
			}
			else if ( (i*TILESIZE > cx) && ((i+1)*TILESIZE < (cx+pw)) )
			{
				s.x = 0; s.w = d.w = TILESIZE;
				if (!tmm)
				{
					tmm = true;
					d.x = nx;
					nx = d.x + d.w;
				}
			}
			else 
			{
				s.x = 0;
				if (j==yb)
					s.w = d.w = (pw + ox)  - nx;
				if (!tmm)
				{
					tmm = true;
					d.x = nx;
					nx = d.x + d.w;
				}
			}
			
			
			// y
			
			if (j*TILESIZE <= cy)
			{
				s.y = cy - (j*TILESIZE);
				s.h = d.h = ( ((j+1) * TILESIZE) - cy );
				d.y = oy + (j-yb)*TILESIZE;
				ny = d.y + s.h;
			}
			else if ( (j*TILESIZE > cy) && ((j+1)*TILESIZE < (cy+ph)) )
			{
				s.y = 0; s.h = d.h = TILESIZE;
				d.y = ny;
				ny = d.y + d.h;
			}
			else 
			{
				s.y = 0;
				s.h = d.h = (ph + oy) - ny;
				d.y = ny;
				ny = d.y + d.h;
			}
			tiles[i][j].s = s; // bu s ve d asagida birim ve binalari
			tiles[i][j].d = d; // cizerken kullaniliyor :D 
			tiles[i][j].draw(s,d);
		}
		tmm = false;
	}
	rectangleColor(screen, ox-1, oy-1, ox+pw+1, oy+ph+1, 0xFFFFFFFF);
	
	
	// harita cizildi, üzerine birim ve binalari ciz
	// kopya çek :D
	for (int i=0;i<human->units.size();i++)
	{
		if (human->units[i]->onScreen(xb, xs, yb, ys))
		{
			int ux = human->units[i]->getX();
			int uy = human->units[i]->getY();
			if (ux <= cx)
			{
				s.x = cx - ux;
				s.w = d.w = ( ux + TILESIZE - cx );
				d.x = ox;
			}
			else if ( (ux > cx) && (ux + TILESIZE < (cx+pw)) )
			{
				s.x = 0; s.w = d.w = TILESIZE;
				d.x = ux - cx + ox;
			}
			else 
			{
				s.x = 0;
				s.w = d.w = pw + ox - ux;
				d.x = ux + ox;
			}
			
			// y
			if (uy <= cy)
			{
				s.y = cy - uy;
				s.h = d.h = ( uy + TILESIZE - cy );
				d.y = oy;
			}
			else if ( (uy > cy) && (uy + TILESIZE < cy+ph))
			{
				s.y = 0; s.h = d.h = TILESIZE;
				d.y = uy - cy + oy;
			}
			else 
			{
				s.y = 0;
				s.h = d.h = (ph + oy) - uy;
				d.y = uy + oy;
			}
			human->units[i]->draw(s,d);
		}
		if (!multipleSelect && human->units[i]->isSelected())
			human->units[i]->drawSubScreen();
	}
	
	for (int i=0;i<human->buildings.size();i++)
	{
		if (human->buildings[i]->onScreen(xb, xs, yb, ys))
		{
			human->buildings[i]->draw
				(
					tiles[human->buildings[i]->getX()][human->buildings[i]->getY()].s,
					tiles[human->buildings[i]->getX()][human->buildings[i]->getY()].d
				);
		}
		if (human->buildings[i]->isSelected())
			human->buildings[i]->drawSubScreen();
	}
	
	if (isMultipleSelecting())
	{
		rectangleColor(screen, rsx1, rsy1, rsx2, rsy2, 0x00FF00FF);
	}
	
	if (multipleSelect)
	{
		human->cok->display();
	}
}

bool Map::isValidSelection()
{
	if ( (rsx1 == -1) || (rsy1 == -1) || (rsx2 == -1) || (rsy2 == -1) )
	{
		return false;
	} 
	else return true;
}

void Map::handleEvents(SDL_Event *event)
{
	if (multipleSelect)
		human->cok->eventHandler(event);
	int mx, my;
	bool empty = true;
	switch(event->type)
	{
		case SDL_KEYDOWN:
			switch(event->key.keysym.sym)
			{
				case SDLK_LEFT:
					ax = -ACC;
					break;
				case SDLK_RIGHT:
					ax = ACC;
					break;
				case SDLK_UP:
					ay = -ACC;
					break;
				case SDLK_DOWN:
					ay = ACC;
					break;
			}
			break;
			case SDL_KEYUP:
				switch(event->key.keysym.sym)
				{
					case SDLK_LEFT:
						if (ax < 0)
							ax=0;
						break;
					case SDLK_RIGHT:
						if (ax > 0)
							ax=0;
						break;
					case SDLK_UP:
						if (ay < 0)
							ay=0;
						break;
					case SDLK_DOWN:
						if (ay > 0)
							ay=0;
						break;
				}
				break;
				
			case SDL_MOUSEMOTION:
				mx = event->motion.x;
				my = event->motion.y;
				if (mx < TOL)
					ax = -ACC;
				else if (mx < screen->w && mx > screen->w-TOL)
					ax = ACC;
				else if (mx > TOL && mx < screen->w-TOL)
					ax = 0;
				
				if (my < TOL)
					ay = -ACC;
				else if (my < screen->h && my > screen->h-TOL)
					ay = ACC;
				else if (my > TOL && my < screen->h-TOL)
					ay = 0;
				
				if(drawing)
				{
					dragging = true;
					if (mx < ox)
						mx = ox;
					else if (mx > ox + pw)
						mx = ox + pw;
					
					if (my < oy)
						my = oy;
					else if (my > oy + ph)
						my = oy + ph;
					rsx2 = mx;
					rsy2 = my;
				}
					
				break;
				
				
			case SDL_MOUSEBUTTONUP:
				scroll = true;
				if (event->button.button == SDL_BUTTON_LEFT && drawing)
				{
					int sayac = 0;
					int smx, smy;
// 					rsx1 = rsx1 - ox + cx;
// 					rsx2 = rsx2 - ox + cx;
// 					rsy1 = rsy1 - oy + cy;
// 					rsy2 = rsy2 - oy + cy;
// 					mx-ox+cx
					if (isValidSelection())
					{
						rsx1 = (rsx1-ox+cx)/TILESIZE; 
						rsx2 = (rsx2-ox+cx)/TILESIZE; 
						rsy1 = (rsy1-oy+cy)/TILESIZE;
						rsy2 = (rsy2-oy+cy)/TILESIZE;
	
	
						for (int i=0;i<human->units.size();i++)
						{
							smx = human->units[i]->getTx();
							smy = human->units[i]->getTy();
							if 	(
									(
										(smx > rsx1) &&
										(smx < rsx2) &&
										(smy > rsy1) &&
										(smy < rsy2)
									) ||
									(
										(smx < rsx1) &&
										(smx > rsx2) &&
										(smy < rsy1) &&
										(smy > rsy2)
									) ||
									(
										(smx > rsx1) &&
										(smx < rsx2) &&
										(smy < rsy1) &&
										(smy > rsy2)
									) ||
									(
										(smx < rsx1) &&
										(smx > rsx2) &&
										(smy > rsy1) &&
										(smy < rsy2)
									)
								)
							{
								human->units[i]->select();
								sayac++;
							}
						}
						
						if (sayac > 1)
						{
							string a = "Liste: [br] ";
							int s2 = 0;
							for(int i=0;i<human->units.size();i++)
							{
								if (human->units[i]->isSelected())
								{
									a += human->units[i]->getName() + " ";
									if (s2 != (sayac-1))
										a += " [br] ";
									s2++;
								}
							}
							human->clist->setText(a);
							multipleSelect = true;
						}
					}
					
					drawing = dragging = false;
					rsx1 = rsx2 = rsy1 = rsy2 = -1;
				}
				
				
				break;
			
			case SDL_MOUSEBUTTONDOWN:
				mx = event->motion.x;
				my = event->motion.y;
				
				scroll = false;
				
				// mini map'e mi basilmis
				if ( 
					(mx > mmx) && 
					(mx < mmx + 2*tx) && 
					(my > mmy) && 
					(my < mmy + 2*ty) && 
					(event->button.button == SDL_BUTTON_LEFT) 
					)
				{
					setCurrentX(((mx - mmx)*16) - (pw/2));
					setCurrentY(((my - mmy)*16) - (ph/2));
				}
				// büyük map'e mi basilmis??
				else if (
						(mx > ox) &&
						(mx < ox+pw) &&
						(my > oy) &&
						(my < oy+ph)
						)
				{
					int cox = mx-ox+cx;
					int coy = my-oy+cy;
					int tilex = cox/32; // tıklanan tile x
					int tiley = coy/32; // tıklanan tile y
					if (event->button.button == SDL_BUTTON_LEFT)
					{
						bool tmm = false;
						for (int i=0;i<human->units.size();i++)
						{
							if (human->units[i]->isWaiting())
							{
								human->units[i]->issueCommand(tilex, tiley);
								human->units[i]->playConfirmed();
								tmm = true;
							}
						}
						
						if (tmm)
							break;
						
						bool single = false;
						for (int i=0;i<human->units.size();i++)
						{
							if (human->units[i]->isMouseOver(cox, coy) && !single)
							{
								human->units[i]->select();
								human->units[i]->playSelected();
								single = true;
								multipleSelect = false;
								empty = false;
							}
							else 
							{
								human->units[i]->unselect();
							}
						}
						
						for (int i=0;i<human->buildings.size();i++)
						{
							if(human->buildings[i]->isClicked(tilex, tiley) && !single)
							{
								human->buildings[i]->select();
								human->buildings[i]->playSelected();
								single = true;
								multipleSelect = false;
								empty = false;
							}
							else
							{
								human->buildings[i]->unselect();
							}
						}
						if (empty)
						{
							for(int i=0;i<human->units.size();i++)
								human->units[i]->unselect();
							for(int i=0;i<human->buildings.size();i++)
								human->buildings[i]->unselect();
							drawing = true;
							multipleSelect = false;
							rsx1 = event->motion.x;
							rsy1 = event->motion.y;
						}
					}
					else if (event->button.button == SDL_BUTTON_RIGHT)
					{
						for(int i=0;i<human->units.size();i++)
						{
							if (human->units[i]->isSelected())
							{
								human->units[i]->defaultAction(tilex, tiley);
								human->units[i]->playConfirmed();
							}
						}
					}
				}
				
				break;
	}
}




