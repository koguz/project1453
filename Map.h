#ifndef MAP__H__
#define MAP__H__

#include <iostream>
#include <string>
#include <vector>
#include <fstream>    // file operations
#include "Headers.h"
#include "Player.h"
#define TILESIZE 32
#define ACC 4 
#define TOL 10

using namespace std;

class Player;

class MapTile
{
	public:
	enum tileType 
	{
		CIM, // 0 
		DENIZKIYIS, // 1
		DENIZKIYIW, // 2
		DENIZKIYIN, // 3
		DENIZKIYIE, // 4
		DENIZKIYINE, // 5
		DENIZKIYISE, // 6
		DENIZKIYISW, // 7
		DENIZKIYINW, // 8
		DENIZKIYISEB, // 9
		DENIZKIYISWB, // A 
		DENIZKIYINWB, // B
		DENIZKIYINEB, // C
		DENIZ, // D
		TOPRAK, // E 
		TOPRAKKIYIS, // F 
		TOPRAKKIYIW, // G
		TOPRAKKIYIN, // H
		TOPRAKKIYIE, // I
		TOPRAKKIYINE, // J
		TOPRAKKIYISE, // K
		TOPRAKKIYISW, // L
		TOPRAKKIYINW, // M
		TOPRAKKIYISEB, // N
		TOPRAKKIYISWB, // O
		TOPRAKKIYINWB, // P
		TOPRAKKIYINEB, // R
		SARICIM, // S
		AGAC, // T
		AGACKESIK, // U 
		DAGLIK, // V 
		DAGLIKKIYIS, // W 
		DAGLIKKIYIW, // X 
		DAGLIKKIYIN, // Y 
		DAGLIKKIYIE, // Z 
		DAGLIKKIYINE, // !
		DAGLIKKIYISE, // -
		DAGLIKKIYISW, // +
		DAGLIKKIYINW, // % 
		DAGLIKKIYISEB, // &
		DAGLIKKIYISWB, // *
		DAGLIKKIYINWB, // <
		DAGLIKKIYINEB // >
	};
	
	MapTile();
	void setType(tileType t, bool obs=false);
	void draw(SDL_Rect src, SDL_Rect dest);
	tileType getTip();
	bool isExplored();
	bool tileKontrol(tileType t);
	void setExplored();
	bool isObstructed();
	SDL_Rect s, d; // nereleri cizilmis tutuyor bunlar :)
	
	static SDL_Surface* screen;
	
	private:
	bool obstruction;
	bool unexplored;
	tileType tip;
	static SDL_Surface *tileList;
};


class Map
{
	public:
	
	enum tileInfo 
	{
		BOS,
		DOLU, // deniz ya da daglik cikarsa :D
		AGACLIK,
		MADEN,
		TARLA,
		BINA,
		BIRIM,
		SALDIR // karşıdaki bir düşman birimi...
	};
	
	Map(SDL_Surface *scr, int w, int h);
	void setOrigin(int x, int y);
	void setCurrentX(int x);
	void setCurrentY(int y);
	void setCurrent(int x, int y);
	int getCx();
	int getCy();
	void setPane(int w, int h);
	void update();
	void drawMiniMap();
	void setMiniMapPos(int x, int y);
	void draw(bool running);
	void handleEvents(SDL_Event *event);
	int getPx();
	int getPy();
	int getCpux();
	int getCpuy();
	void setPlayers(Player* h, Player* c);
	
	// playerdan gelenler
	bool multipleSelect;
	int rsx1, rsx2, rsy1, rsy2;
	bool isMultipleSelecting();
	bool isValidSelection();
	
	void exploreTiles(int tx, int ty, int range);
	void startBuildSel(int size, MapTile::tileType type);
	void endBuildSel();
	bool uygun();
	bool tileEmpty(int ex, int ey);
	tileInfo getTileInfo(int ex, int ey);
	BaseBuilding* getBuilding(int x, int y);
	
	private:
	Player *human, *cpu;
	bool drawing, dragging;
	int buildsize;
	MapTile::tileType buildtype;
	MapTile** tiles;
	SDL_Surface* screen;
	
	vector<string> map;
	string line;
	int get_map(char *f);
	
	int ox, oy; // ekrandaki posizyon, sol üst
	int cx, cy; // current x & y
	int pw, ph; // ekrandaki genişlik / yükseklik
	int sx, sy; // step x - step y 
	int xb, xs; // xbaşla - xson 
	int yb, ys; // ybaşla - yson
	int tx, ty; // tile count
	int rw, rh; // real width tx*TILESIZE
	int vx, vy; // velocity 
	int ax, ay; // acceleration 
	int mtx, mty; // mouse hangi tile üzerinde :D 
	int mmx, mmy; // mini map positions
	// starting points for player and computer
	int startpx, startpy, startcx, startcy;
	bool scroll; // kare secim sirasinda scroll'u engellemek için
};





#endif


