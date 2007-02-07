#include "Application.h"

Application::Application(string name, int w, int h, int d, unsigned int f)
{
	appName = name; width = w; height = h; bpp = d; flags = f;
	screen = 0;
	error = "";
	done = true;
}


bool Application::Init()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		error = "SDL Init was unsuccessful";
		return false;
	}
	screen = SDL_SetVideoMode(width, height, bpp, flags);
	if (screen == 0)
	{
		error = "Window could not be opened";
		return false;
	}
	SDL_WM_SetCaption(appName.c_str(), "SDL_App Icon");
	
	
	current = new SDLScreen(screen);
	
	SDLButton *buton = new SDLButton("img/button.png", "Değerleri Al");
	buton->setPosition(450,400);
	buton->clicked = 0;
	current->addWidget(buton);
	
	SDLLabel *lblZor = new SDLLabel("Oyun Zorluğu: ");
	lblZor->setPosition(40, 32);
	current->addWidget(lblZor);
	
	SDLCheckBox *cb = new SDLCheckBox("Aç kapa, aç kapa, artema :P");
	cb->setPosition(40, 80);
	current->addWidget(cb);
	
	SDLTextView *tv = new SDLTextView("Bir SDL GUI hazırlanır\nBu yazıyı gördüğünüz yer bir\ntextview alanıdır. Buraya\nyazdıklarınızı güzel güzel\ngösterir\nBu da bir başka satır\nal sana bir tane daha\nbaktıkça geliyor", 300, 4);
	tv->setPosition(200, 120);
	current->addWidget(tv);
	
	SDLCombo *combo = new SDLCombo();
	combo->setPosition(200, 30);
	combo->addOption("Çok Zor", "5");
	combo->addOption("Zor", "4");
	combo->addOption("Normal", "3", true);
	combo->addOption("Kolay", "2");
	combo->addOption("Çocuk Oyuncağı", "1");
	current->addWidget(combo);
	
	
	SDLListView *lw = new SDLListView(4);
	lw->setPosition(200, 220);
	lw->addItem("madde 1");
	lw->addItem("madde 2");
	lw->addItem("madde 3");
	lw->addItem("madde 4");
	lw->addItem("madde 5");
	lw->addItem("madde 6");
	lw->addItem("madde 7");
	lw->addItem("madde 8");
	current->addWidget(lw);
	
	pb = new SDLProgressBar(48, 6, GREEN, 2, 10);
	pb->setPosition(40, 350);
	current->addWidget(pb);
	
	return true;
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
	Uint32 lastTick = SDL_GetTicks();
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
			current->eventHandler(&event);
		}
		if ((SDL_GetTicks() - lastTick) >= 1000)
		{
			pb->setValue(pb->getValue()+1);
		}
		current->display();
		SDL_UpdateRect(screen, 0, 0, 0, 0);
		SDL_Delay(50);
	}
	
	return 0;
}

