#include "Application.h"

using namespace std;

int main(int argc, char* argv[])
{
	Application app("1453", 800, 600, 24, SDL_HWSURFACE|SDL_DOUBLEBUF|SDL_ANYFORMAT);
	atexit(SDL_Quit);
	return app.Run();
}
