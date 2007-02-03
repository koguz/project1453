#include "Application.h"

using namespace std;

int main(int argc, char* argv[])
{
	Application *app = new Application("SDLGui Testing", 640, 480, 16, SDL_SWSURFACE);
	return app->Run();
}
