#include "Map.h"

SDL_Surface* loadimg(char* f)
{
	SDL_Surface *temp = IMG_Load(f);
	SDL_SetAlpha(temp, SDL_SRCALPHA | SDL_RLEACCEL, SDL_ALPHA_OPAQUE);
	return temp;
}

/* all tile type are on one image */
SDL_Surface* MapTile::tileList = loadimg("graphics/terrain/tiles.png");
SDL_Surface* MapTile::screen = 0;

MapTile::MapTile()
{
	tip = CIM;
	unexplored = true; 
	obstruction = false;
}

void MapTile::setType(tileType t, bool obs)
{
	tip = t;
	obstruction = obs;
}


bool MapTile::isObstructed()
{
	return obstruction;
}

bool MapTile::tileKontrol(tileType t)
{
	return (t == tip);
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
		case DENIZKIYIS:
			src.x += 32;
			break;
		case DENIZKIYIW:
			src.x += 64;
			break;
		case DENIZKIYIN:
			src.x += 96;
			break;
		case DENIZKIYIE:
			src.x += 128;
			break;
		case DENIZKIYINE:
			src.x += 160;
			break;
		case DENIZKIYISE:
			src.x += 192;
			break;
		case DENIZKIYISW:
			src.x += 224;
			break;
		case DENIZKIYINW:
			src.y += 32;
			break;
		case DENIZKIYISEB:
			src.x += 32;
			src.y += 32;
			break;
		case DENIZKIYISWB:
			src.x += 64;
			src.y += 32;
			break;
		case DENIZKIYINWB:
			src.x += 96;
			src.y += 32;
			break;
		case DENIZKIYINEB:
			src.x += 128;
			src.y += 32;
			break;
		case DENIZ:
			src.x += 160;
			src.y += 32;
			break;
		case TOPRAK:
			src.x += 192;
			src.y += 32;
			break;
		case TOPRAKKIYIS:
			src.x += 224;
			src.y += 32;
			break;
		case TOPRAKKIYIW:
			src.y += 64;
			break;
		case TOPRAKKIYIN:
			src.x += 32;
			src.y += 64;
			break;
		case TOPRAKKIYIE:
			src.x += 64;
			src.y += 64;
			break;
		case TOPRAKKIYINE:
			src.x += 96;
			src.y += 64;
			break;
		case TOPRAKKIYISE:
			src.x += 128;
			src.y += 64;
			break;
		case TOPRAKKIYISW:
			src.x += 160;
			src.y += 64;
			break;
		case TOPRAKKIYINW:
			src.x += 192;
			src.y += 64;
			break;
		case TOPRAKKIYISEB:
			src.x += 224;
			src.y += 64;
			break;
		case TOPRAKKIYISWB:
			src.y += 96;
			break;
		case TOPRAKKIYINWB:
			src.x += 32;
			src.y += 96;
			break;
		case TOPRAKKIYINEB:
			src.x += 64;
			src.y += 96;
			break;
		case SARICIM:
			src.x += 96;
			src.y += 96;
			break;
		
			break;
		case AGAC:
			src.x += 160;
			src.y += 96;
			break;
		case AGACKESIK:
			src.x += 128;
			src.y += 96;
			break;
		case DAGLIKKIYIS:
			src.x += 192;
			src.y += 96;
			break;
		case DAGLIKKIYIW:
			src.x += 224;
			src.y += 96;
			break;
		case DAGLIKKIYIN:
			src.y += 128;
			break;
		case DAGLIKKIYIE:
			src.x += 32;
			src.y += 128;
			break;
		case DAGLIKKIYISEB:
			src.x += 64;
			src.y += 128;
			break;
		case DAGLIKKIYISWB:
			src.x += 96;
			src.y += 128;
			break;
		case DAGLIKKIYINWB:
			src.x += 128;
			src.y += 128;
			break;
		case DAGLIKKIYINEB:
			src.x += 160;
			src.y += 128;
			break;
		case DAGLIKKIYISE:
			src.x += 192;
			src.y += 128;
			break;
		case DAGLIKKIYISW:
			src.x += 224;
			src.y += 128;
			break;
		case DAGLIKKIYINW:
			src.y += 160;
			break;
		case DAGLIKKIYINE:
			src.x += 32;
			src.y += 160;
			break;
		case DAGLIK:
			src.x += 64;
			src.y += 160;
			break;
		
	}
	SDL_BlitSurface(tileList, &src, screen, &dest);
	// uncomment the line below to see the borders of the tiles
 	// rectangleColor(screen, dest.x, dest.y, dest.x+dest.w, dest.y+dest.h, 0x000000FF);
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
	
	get_map("harita1.txt");
	
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
	buildsize = 0;
	
	int j = 0;
	vector<string>::iterator iter;
	for( iter = map.begin(); iter != map.end(); iter++ ) {
		for( int i=0; i < map.at(j).size(); i++ ) {
			switch(map.at(j).at(i))
			{
				case '0':
					tiles[i][j].setType(MapTile::CIM);
					break;
				case '1':
					tiles[i][j].setType(MapTile::DENIZKIYIS, true);
					break;
				case '2':
					tiles[i][j].setType(MapTile::DENIZKIYIW, true);
					break;
				case '3':
					tiles[i][j].setType(MapTile::DENIZKIYIN, true);
					break;
				case '4':
					tiles[i][j].setType(MapTile::DENIZKIYIE, true);
					break;
				case '5':
					tiles[i][j].setType(MapTile::DENIZKIYINE, true);
					break;
				case '6':
					tiles[i][j].setType(MapTile::DENIZKIYISE, true);
					break;
				case '7':
					tiles[i][j].setType(MapTile::DENIZKIYISW, true);
					break;
				case '8':
					tiles[i][j].setType(MapTile::DENIZKIYINW, true);
					break;
				case '9':
					tiles[i][j].setType(MapTile::DENIZKIYISEB, true);
					break;
				case 'A':
					tiles[i][j].setType(MapTile::DENIZKIYISWB, true);
					break;
				case 'B':
					tiles[i][j].setType(MapTile::DENIZKIYINWB, true);
					break;
				case 'C':
					tiles[i][j].setType(MapTile::DENIZKIYINEB, true);
					break;
				case 'D':
					tiles[i][j].setType(MapTile::DENIZ, true);
					break;
				case 'E':
					tiles[i][j].setType(MapTile::TOPRAK);
					break;
				case 'F':
					tiles[i][j].setType(MapTile::TOPRAKKIYIS);
					break;
				case 'G':
					tiles[i][j].setType(MapTile::TOPRAKKIYIW);
					break;
				case 'H':
					tiles[i][j].setType(MapTile::TOPRAKKIYIN);
					break;
				case 'I':
					tiles[i][j].setType(MapTile::TOPRAKKIYIE);
					break;
				case 'J':
					tiles[i][j].setType(MapTile::TOPRAKKIYINE);
					break;
				case 'K':
					tiles[i][j].setType(MapTile::TOPRAKKIYISE);
					break;
				case 'L':
					tiles[i][j].setType(MapTile::TOPRAKKIYISW);
					break;
				case 'M':
					tiles[i][j].setType(MapTile::TOPRAKKIYINW);
					break;
				case 'N':
					tiles[i][j].setType(MapTile::TOPRAKKIYISEB);
					break;
				case 'O':
					tiles[i][j].setType(MapTile::TOPRAKKIYISWB);
					break;
				case 'P':
					tiles[i][j].setType(MapTile::TOPRAKKIYINWB);
					break;
				case 'R':
					tiles[i][j].setType(MapTile::TOPRAKKIYINEB);
					break;
				case 'S':
					tiles[i][j].setType(MapTile::SARICIM);
					break;
				case 'T':
					tiles[i][j].setType(MapTile::AGAC, true);
					break;
				case 'U':
					tiles[i][j].setType(MapTile::AGACKESIK);
					break;
				case 'V':
					tiles[i][j].setType(MapTile::DAGLIK, true);
					break;
				case 'W':
					tiles[i][j].setType(MapTile::DAGLIKKIYIS, true);
					break;
				case 'X':
					tiles[i][j].setType(MapTile::DAGLIKKIYIW, true);
					break;
				case 'Y':
					tiles[i][j].setType(MapTile::DAGLIKKIYIN, true);
					break;
				case 'Z':
					tiles[i][j].setType(MapTile::DAGLIKKIYIE, true);
					break;
				case '!':
					tiles[i][j].setType(MapTile::DAGLIKKIYINE, true);
					break;
				case '-':
					tiles[i][j].setType(MapTile::DAGLIKKIYISE, true);
					break;
				case '+':
					tiles[i][j].setType(MapTile::DAGLIKKIYISW, true);
					break;
				case '%':
					tiles[i][j].setType(MapTile::DAGLIKKIYINW, true);
					break;
				case '&':
					tiles[i][j].setType(MapTile::DAGLIKKIYISEB, true);
					break;
				case '*':
					tiles[i][j].setType(MapTile::DAGLIKKIYISWB, true);
					break;
				case '<':
					tiles[i][j].setType(MapTile::DAGLIKKIYINWB, true);
					break;
				case '>':
					tiles[i][j].setType(MapTile::DAGLIKKIYINEB, true);
					break;
			}
		}
		j++;
	}
		
	startpx = 44;
	startpy = 6;
	startcx = 2000;
	startcy = 2000; 
	
	vx = vy = ax = ay = mtx = mty = 0;
	cx = 1100; cy = 0; // aslında bu da map'ten okunacak
}

int Map::get_map(char *f)
{
	Map::map.clear();
	ifstream infile (f, ios_base::in);
	
	while (getline(infile, line, '\n'))
	{
		map.push_back (line);
	}
}

int Map::getPx() { return startpx; }
int Map::getPy() { return startpy; }
int Map::getCpux() { return startcx; }
int Map::getCpuy() { return startcy; }
int Map::getTx() { return tx; }
int Map::getTy() { return ty; }

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
					case MapTile::TOPRAKKIYIS:
					case MapTile::TOPRAKKIYIW:
					case MapTile::TOPRAKKIYIN:
					case MapTile::TOPRAKKIYIE:
					case MapTile::TOPRAKKIYISE:
					case MapTile::TOPRAKKIYINE:
					case MapTile::TOPRAKKIYISW:
					case MapTile::TOPRAKKIYINW:
					case MapTile::TOPRAKKIYISEB:
					case MapTile::TOPRAKKIYINWB:
					case MapTile::TOPRAKKIYISWB:
					case MapTile::TOPRAKKIYINEB:
						boxColor(screen,sx, sy, ex, ey, 0x5E3001FF);
						break;
					case MapTile::AGAC:
						boxColor(screen,sx, sy, ex, ey, 0x043A0BFF);
						break;
					case MapTile::AGACKESIK:
						boxColor(screen,sx, sy, ex, ey, 0x065B12FF);
						break;
					case MapTile::DAGLIK:
					case MapTile::DAGLIKKIYIS:
					case MapTile::DAGLIKKIYIW:
					case MapTile::DAGLIKKIYIN:
					case MapTile::DAGLIKKIYIE:
					case MapTile::DAGLIKKIYISE:
					case MapTile::DAGLIKKIYINE:
					case MapTile::DAGLIKKIYISW:
					case MapTile::DAGLIKKIYINW:
					case MapTile::DAGLIKKIYISEB:
					case MapTile::DAGLIKKIYINWB:
					case MapTile::DAGLIKKIYISWB:
					case MapTile::DAGLIKKIYINEB:
						boxColor(screen,sx, sy, ex, ey, 0x5B5B5BFF);
						break;
					case MapTile::DENIZ:
					case MapTile::DENIZKIYIS:
					case MapTile::DENIZKIYIW:
					case MapTile::DENIZKIYIN:
					case MapTile::DENIZKIYIE:
					case MapTile::DENIZKIYISE:
					case MapTile::DENIZKIYINE:
					case MapTile::DENIZKIYISW:
					case MapTile::DENIZKIYINW:
					case MapTile::DENIZKIYISEB:
					case MapTile::DENIZKIYINWB:
					case MapTile::DENIZKIYISWB:
					case MapTile::DENIZKIYINEB:
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
	
	for (int i=0;i<human->buildings.size();i++)
	{
		sx = mmx + (human->buildings[i]->getTx()*2);
		sy = mmy + (human->buildings[i]->getTy()*2);
		ex = sx + (2 * human->buildings[i]->getSize());
		ey = sy + (2 * human->buildings[i]->getSize());
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

void Map::exploreTiles(int x, int y, int range)
{
	int sx = x - range;
	if (sx<0)
		sx = 0;
	int ex = x + range;
	if (ex>=tx)
		ex = tx - 1;
		
	int sy = y - range;
	if (sy<0)
		sy = 0;
	int ey = y + range;
	if (ey>=ty)
		ey = ty - 1;
		
	for (int i=sx;i<=ex;i++)
	{
		for(int j=sy;j<=ey;j++)
		{
			tiles[i][j].setExplored();
		}
	}
}

bool Map::tileEmpty(int ex, int ey)
{
	bool empty = true;
	for(int i=0;i<human->units.size();i++)
	{
		if ( (human->units[i]->getTx() == ex) && (human->units[i]->getTy() == ey) )
		{
			empty = false;
		}
		if (!empty) return empty;
	}
	
	for(int i=0;i<human->buildings.size();i++)
	{
		int tempx = human->buildings[i]->getTx();
		int tempy = human->buildings[i]->getTy();
		int temps = human->buildings[i]->getSize();
		if( (ex>=tempx) && 
			(ex<tempx+temps) && 
			(ey>=tempy) &&
			(ey<tempy+temps)
		  )
		 {
		 	empty = false;
		 }
		 if (!empty) return empty;
	}
	return true;
}

Map::tileInfo Map::getTileInfo(int ex, int ey)
{	
	/* öncelik
		- oyuncunun birimlerden biri var mi
		- bilg. birimlerden biri var mi
		- oyuncunun binalarindan biri var mi
			- maden
			- tarla
		- bilg. binalarindan biri var mi
		- agaclik bir alan mi
		- yürünebilecek bir alan mi
	
	enum tileInfo 
	{
		BOS,
		DOLU, // deniz ya da daglik cikarsa :D
		AGACLIK,
		MADEN,
		TARLA,
		BINA,
		BIRIM,
		SALDIR
	};
	
	*/
	
	
	for(int i=0;i<human->units.size();i++)
	{
		if (human->units[i]->getTx() == ex && human->units[i]->getTy() == ey)
			return Map::BIRIM;
	}
	
	for(int i=0;i<human->buildings.size();i++)
	{
		int tempx = human->buildings[i]->getTx();
		int tempy = human->buildings[i]->getTy();
		int temps = human->buildings[i]->getSize();
		if( (ex>=tempx) && 
			(ex<tempx+temps) && 
			(ey>=tempy) &&
			(ey<tempy+temps)
		  )
		 {
		 	return Map::BINA;
		 }
	}
	
	switch(tiles[ex][ey].getTip())
	{
		case MapTile::DENIZ:
		case MapTile::DENIZKIYIS:
		case MapTile::DENIZKIYIW:
		case MapTile::DENIZKIYIN:
		case MapTile::DENIZKIYIE:
		case MapTile::DENIZKIYISE:
		case MapTile::DENIZKIYINE:
		case MapTile::DENIZKIYISW:
		case MapTile::DENIZKIYINW:
		case MapTile::DENIZKIYISEB:
		case MapTile::DENIZKIYINWB:
		case MapTile::DENIZKIYISWB:
		case MapTile::DENIZKIYINEB:
		case MapTile::DAGLIK:
		case MapTile::DAGLIKKIYIS:
		case MapTile::DAGLIKKIYIW:
		case MapTile::DAGLIKKIYIN:
		case MapTile::DAGLIKKIYIE:
		case MapTile::DAGLIKKIYISE:
		case MapTile::DAGLIKKIYINE:
		case MapTile::DAGLIKKIYISW:
		case MapTile::DAGLIKKIYINW:
		case MapTile::DAGLIKKIYISEB:
		case MapTile::DAGLIKKIYINWB:
		case MapTile::DAGLIKKIYISWB:
		case MapTile::DAGLIKKIYINEB:
			return Map::DOLU;
			break;
		case MapTile::AGAC:
			return Map::AGACLIK;
			break;
	}
	
	return Map::BOS;
}

BaseBuilding* Map::getBuilding(int ex, int ey)
{
	for(int i=0;i<human->buildings.size();i++)
	{
		int tempx = human->buildings[i]->getTx();
		int tempy = human->buildings[i]->getTy();
		int temps = human->buildings[i]->getSize();
		if( (ex>=tempx) && 
			(ex<tempx+temps) && 
			(ey>=tempy) &&
			(ey<tempy+temps)
		  )
		 {
		 	return human->buildings[i];
		 }
	}
	return 0;
}


bool Map::uygun()
{
	for(int i=mtx;i<mtx+buildsize;i++)
	{
		for(int j=mty;j<mty+buildsize;j++)
		{
			if (!tiles[i][j].tileKontrol(buildtype) || 
				!tiles[i][j].isExplored() ||
				!tileEmpty(i, j)
				)
			{
				return false;
			}
		}
	}
	return true;
}

void Map::draw(bool running)
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
			if 	( 
				(buildsize > 0) && 
				(i >= mtx) && 
				(i < mtx+buildsize) &&
				(j >= mty) &&
				(j < mty+buildsize)
				)
			{
				if (tiles[i][j].tileKontrol(buildtype) &&
				 (tiles[i][j].isExplored()) &&
				 (tileEmpty(i,j))
				 )
					boxColor(screen, d.x, d.y, d.x+d.w, d.y+d.h, 0x00FF00FF);
				else 
					boxColor(screen, d.x, d.y, d.x+d.w, d.y+d.h, 0xFF0000FF);
			}
			else tiles[i][j].draw(s,d);
		}
		tmm = false;
	}
	rectangleColor(screen, ox-1, oy-1, ox+pw+1, oy+ph+1, 0xFFFFFFFF);
	
	if (!running) return;
	
	// harita cizildi, üzerine birim ve binalari ciz
	for (int i=0;i<human->units.size();i++)
	{
		exploreTiles( human->units[i]->getTx(), human->units[i]->getTy(), human->units[i]->getSight());
		
		if (human->units[i]->onScreen(cx, cx+pw, cy, cy+ph))
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
				s.w = d.w = abs(pw + cx - ux);
				d.x = ux + ox - cx;
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
				s.h = d.h = abs((ph + cy) - uy);
				d.y = uy + oy - cy;
			}
			human->units[i]->draw(s,d);
		}
		if (!multipleSelect && human->units[i]->isSelected())
			human->units[i]->drawSubScreen();
	}
	
	for (int i=0;i<human->buildings.size();i++)
	{
		for (int m=0;m<human->buildings[i]->getSize();m++)
		{
			for(int n=0;n<human->buildings[i]->getSize();n++)
			{
				exploreTiles( human->buildings[i]->getTx()+m, human->buildings[i]->getTy()+n, human->buildings[i]->getSight());
			}
		}
		
		if (human->buildings[i]->onScreen(cx, cx+pw, cy, cy+ph))
		{
			int ux = human->buildings[i]->getX();
			int uy = human->buildings[i]->getY();
			int sb = human->buildings[i]->getSize();
			
			if (ux <= cx)
			{
				s.x = cx - ux;
				s.w = d.w = ( ux + (TILESIZE*sb) - cx );
				d.x = ox;
			}
			else if ( (ux > cx) && (ux + (TILESIZE*sb) < (cx+pw)) )
			{
				s.x = 0; s.w = d.w = (TILESIZE*sb);
				d.x = ux - cx + ox;
			}
			else 
			{
				s.x = 0;
				s.w = d.w = abs(pw + cx - ux);
				d.x = ux + ox - cx;
			}
			
			// y
			if (uy <= cy)
			{
				s.y = cy - uy;
				s.h = d.h = ( uy + (TILESIZE*sb) - cy );
				d.y = oy;
			}
			else if ( (uy > cy) && (uy + (TILESIZE*sb) < cy+ph))
			{
				s.y = 0; s.h = d.h = (TILESIZE*sb);
				d.y = uy - cy + oy;
			}
			else 
			{
				s.y = 0;
				s.h = d.h = abs((ph + cy) - uy);
				d.y = uy + oy - cy;
			}
			
			human->buildings[i]->draw(s,d);
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


void Map::startBuildSel(int size, MapTile::tileType type)
{
	buildsize = size;
	buildtype = type;
}

void Map::endBuildSel()
{
	buildsize = 0;
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
				
				mtx = (mx-ox+cx)/32;
				mty = (my-oy+cy)/32;
				
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
				
				if ( (ax < 0) && (ay < 0) )
					SDLCursor::setNw();
				else if ( (ax < 0) && (ay > 0) )
					SDLCursor::setSw();
				else if ( (ax > 0) && (ay < 0) )
					SDLCursor::setNe();
				else if ( (ax > 0) && (ay > 0) )
					SDLCursor::setSe();
				else if (ax < 0)
					SDLCursor::setW();
				else if (ax > 0)
					SDLCursor::setE();
				else if (ay < 0)
					SDLCursor::setN();
				else if (ay > 0)
					SDLCursor::setS();
				else
				{
					if (!SDLCursor::locked)
						SDLCursor::setCursorMain();
				}
				
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
							human->buildings[i]->isClicked(tilex, tiley);
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
							endBuildSel();
							rsx1 = event->motion.x;
							rsy1 = event->motion.y;
						}
					}
					else if (event->button.button == SDL_BUTTON_RIGHT)
					{
						for(int i=0;i<human->units.size();i++)
						{
							if (human->units[i]->isSelected() && !human->units[i]->isWaiting())
							{
								human->units[i]->defaultAction(tilex, tiley);
							}
							else if (human->units[i]->isWaiting())
							{
								human->units[i]->cancelActions();
							}
						}
					}
				}
				
				break;
	}
}




