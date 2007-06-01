#include "Application.h"

using namespace std;

int main(int argc, char* argv[])
{
	/* As a result of the object oriented design, we create 
	 * an Application object and run it. When the Run function
	 * ends, the allocated space is returned. 
	 */
	Application* app = new Application("1453", 800, 600, 32, SDL_ANYFORMAT);
	
	// This function registers SDL_Quit function
	// to be called when the program exits
	atexit(SDL_Quit);
	app->Run();
	delete app;
	return 0;
}
