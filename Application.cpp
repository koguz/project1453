#include "Application.h"

Application::Application(string name, int w, int h, int d, unsigned int f)
{
	appName = name; width = w; height = h; bpp = d; flags = f;
	screen = 0;
	error = "";
	done = true;
	lblFps = new SDLLabel("?", 8);
	lblFps->setPosition(20, 580);
	showFps = true;
}

Application::~Application()
{
	delete ana;
	delete gt;
	SDL_FreeSurface(screen);
	delete game;
	TTF_Quit();
	
	delete muse;
	
	int numtimesopened, frequency, channels;
	Uint16 format;
	numtimesopened=Mix_QuerySpec(&frequency, &format, &channels);
	/* Turning sound off */
	if(numtimesopened) 
	{
		for (int i=0;i<numtimesopened;i++)
			Mix_CloseAudio();
	}
}

bool Application::Init()
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
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
	
	SDL_ShowCursor(SDL_DISABLE);
	
	Application *me = this;
	
	ana = new ScreenMain(screen);
	ana->cikis->clicked = makeFunctor((CBFunctor0*)0, *me, &Application::Quit);
	ana->single->clicked = makeFunctor((CBFunctor0*)0, *me, &Application::screenGameType);
	ana->ayarlar->clicked = makeFunctor((CBFunctor0*)0, *me, &Application::screenSettings);
	ana->credits->clicked = makeFunctor((CBFunctor0*)0, *me, &Application::screenCredits);
	
	gt = new ScreenGameType(screen);
	gt->anaEkranaDon->clicked = makeFunctor((CBFunctor0*)0, *me, &Application::screenMain);
	gt->baslat->clicked = makeFunctor((CBFunctor0*)0, *me, &Application::startSingleGame);
	
	ayar = new ScreenSettings(screen);
	ayar->iptal->clicked = makeFunctor((CBFunctor0*)0, *me, &Application::screenMain);
	
	emek = new ScreenCredits(screen);
	emek->anaEkranaDon->clicked = makeFunctor((CBFunctor0*)0, *me, &Application::screenMain);
	
	muse = new SDLMusic("wavs/music/track01.ogg");
	muse->play();
	
	game = 0;
	
	current = ana;
	return true;
}

void Application::startSingleGame()
{
	muse->stop();
	game = new Game(screen, "Osmanlı", 1, "dummy");
}

void Application::screenMain()
{
	current = ana;
}

void Application::screenGameType()
{
	current = gt;
}

void Application::screenCredits()
{
	current = emek;
}

void Application::screenSettings()
{
	ayar->reset();
	current = ayar;
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
	int fps = 0;
	int sonfps = SDL_GetTicks();
	while(done)
	{
		while(SDL_PollEvent(&event))
		{
			switch(event.type)
			{
				case SDL_QUIT:
					done = false;
					break;
				case SDL_MOUSEMOTION:
					SDLCursor::updateAll(event.motion.x, event.motion.y);
					break;
			}
			if (game != 0)
				game->eventHandler(&event);
			else
				current->eventHandler(&event);
		}
		if (game != 0)
		{
			switch(game->sonMu())
			{
				case 0:
					game->display();
					game->update();
					break;
				case 1:
					delete game;
					game = 0;
					current = ana;
					break;
				case 2:
					done = false;
					break;
			}
		}
		else
		{
			current->display();
			if (!muse->isPlaying() && muse->musicOn)
				muse->play();
			else if (!muse->musicOn)
				muse->stop();
		}
		SDLCursor::cCurrent->drawWidget(screen);
		if (showFps)
			lblFps->drawWidget(screen);
		SDL_Flip(screen);
		SDL_Delay(10);
		if (SDL_GetTicks() - sonfps > 1000)
		{
			if (showFps)
				lblFps->setText(fps);
			sonfps = SDL_GetTicks();
			fps = 0;
		}
		else fps++;
	}
	
	// Deleting static values
	
	delete SDLCursor::cMain;
	delete SDLCursor::cTarget;
	delete SDLCursor::oke;
	delete SDLCursor::oks;
	delete SDLCursor::okw;
	delete SDLCursor::okn;
	delete SDLCursor::okne;
	delete SDLCursor::oknw;
	delete SDLCursor::okse;
	delete SDLCursor::oksw;
	SDL_FreeSurface(Koylu::spriteImg);
	SDL_FreeSurface(AskerOcagi::spriteImg);
	SDL_FreeSurface(Ev::spriteImg);
	SDL_FreeSurface(SehirMerkezi::spriteImg);
	
	map<int, TTF_Font*>::iterator iter;
	for(iter=SDLFont::font.begin();iter != SDLFont::font.end(); iter++)
	{
		TTF_CloseFont(iter->second);
	}
	
	
	
	return 0;
}

