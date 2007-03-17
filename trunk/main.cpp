#include "Application.h"

using namespace std;

int main(int argc, char* argv[])
{
	Application app("1453 Deneme Sürümü | Şubat / Mart 2007", 800, 600, 24, SDL_SWSURFACE|SDL_ANYFORMAT);
	atexit(SDL_Quit);
	return app.Run();
}
