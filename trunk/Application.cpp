#include "Application.h"

Application::Application(string name, int w, int h, int d, unsigned int f)
{
	appName = name; width = w; height = h; bpp = d; flags = f;
	screen = 0;
	error = "";
	done = true;
}

Application::~Application()
{
	delete ana;
	delete gt;
	SDL_FreeSurface(screen);
	delete game;
}

bool Application::Init()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		error = "SDL Başlatılamadı";
		return false;
	}
	screen = SDL_SetVideoMode(width, height, bpp, flags);
	if (screen == 0)
	{
		error = "Pencere açılamadı";
		return false;
	}
	SDL_WM_SetCaption(appName.c_str(), "SDL Simgesi");
	
	Application *me = this;
	
	ana = new ScreenMain(screen);
	ana->cikis->clicked = makeFunctor((CBFunctor0*)0, *me, &Application::Quit);
	ana->single->clicked = makeFunctor((CBFunctor0*)0, *me, &Application::screenGameType);
	
	gt = new ScreenGameType(screen);
	gt->anaEkranaDon->clicked = makeFunctor((CBFunctor0*)0, *me, &Application::screenMain);
	gt->baslat->clicked = makeFunctor((CBFunctor0*)0, *me, &Application::startSingleGame);
	
	game = 0;
	
	current = ana;
	return true;
}

void Application::startSingleGame()
{
	if (!strcmp(gt->haritalar->getValue().c_str(), "NONE"))
	{
		gt->err->setText("Lütfen bir harita seçiniz!");
		return;
	}
	gt->err->setText(" ");
	
	game = new Game(screen, gt->ulke->getValue(), atoi(gt->rakipTip->getValue().c_str()), gt->haritalar->getValue());
}

void Application::screenMain()
{
	current = ana;
}

void Application::screenGameType()
{
	current = gt;
}

void Application::Quit()
{
	done = false;
}


int Application::Run()
{
	if (!Init())
	{
		cout << error << endl;
		return -1;
	}
	SDL_Event event;
	done = true;
	while(done)
	{
		while(SDL_PollEvent(&event))
		{
			switch(event.type)
			{
				case SDL_QUIT:
					done = false;
					break;
			}
			if (game != 0)
				game->eventHandler(&event);
			else
				current->eventHandler(&event);
		}
		if (game != 0)
		{
			
			game->display();
			game->update();
		}
		else
			current->display();
		SDL_UpdateRect(screen, 0, 0, 0, 0);
		SDL_Delay(50);
	}
	
	return 0;
}

