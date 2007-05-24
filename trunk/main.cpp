#include "Application.h"

using namespace std;

int main(int argc, char* argv[])
{
	Application* app = new Application("1453", 800, 600, 32, SDL_ANYFORMAT);// SDL_HWSURFACE|SDL_DOUBLEBUF|SDL_ANYFORMAT); //SDL_FULLSCREEN
	atexit(SDL_Quit);
	app->Run();
	delete app;
	return 0;
}
