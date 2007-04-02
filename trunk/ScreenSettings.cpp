#include "ScreenSettings.h"

ScreenSettings::ScreenSettings(SDL_Surface *screen):SDLScreen(screen)
{
	ScreenSettings *me = this;

	arka = new SDLWidget("ui/arkaKirmizi.jpg");
	arka->setPosition(0, 0);
	addWidget(arka);
	
	optionPane = new SDLWidget("ui/optionPane.jpg");
	optionPane->setPosition( (800-optionPane->getWidth())/2, 250);
	addWidget(optionPane);
	
	imgYeniceri2 = new SDLWidget("ui/img_yeniceri2.jpg");
	imgYeniceri2->setPosition(12, 12);
	addWidget(imgYeniceri2);
	
	baslik = new SDLLabel("Ayarlar", 36);
	baslik->setPosition( (800-baslik->getWidth()) / 2, 200);
	addWidget(baslik);
	
	monoff = new SDLCheckBox("Müzikler Açık");
	monoff->setPosition(280, 280);
	if (SDLMusic::musicOn)
		monoff->setOn();
	else monoff->setOff();
	addWidget(monoff);
	
	muzikvol = new SDLLabel("Müzik Ses Seviyesi");
	muzikvol->setPosition(280, 320);
	addWidget(muzikvol);
	
	mvol = new SDLCombo();
	mvol->setPosition(440, 320);
	mvol->addOption("Yüksek", "1", true);
	mvol->addOption("Orta", "2");
	mvol->addOption("Kısık", "4");
	addWidget(mvol);
	
	
	tamam = new SDLButton("ui/kucukDugme.jpg", "Kaydet");
	tamam->setPosition(566, 470);
	tamam->clicked = makeFunctor((CBFunctor0*)0, *me, &ScreenSettings::accept);
	addWidget(tamam);
	
	
	iptal = new SDLButton("ui/kucukDugme.jpg", "Ana Ekran");
	iptal->setPosition(566, 510);
	addWidget(iptal);
}


void ScreenSettings::accept()
{
	if (monoff->isChecked())
		SDLMusic::musicOn = true;
	else 
		SDLMusic::musicOn = false;
	
	string t = mvol->getValue();
	if (t == "1")
		SDLMusic::setVolume(1);
	else if (t == "2")
		SDLMusic::setVolume(2);
	else if (t == "4")
		SDLMusic::setVolume(4);
}

void ScreenSettings::reset()
{
	if (SDLMusic::musicOn)
		monoff->setOn();
	else monoff->setOff();
	
	switch(SDLMusic::getVolume())
	{
		case MIX_MAX_VOLUME:
			mvol->setSelected("Yüksek");
			break;
		case MIX_MAX_VOLUME/2:
			mvol->setSelected("Orta");
			break;
		case MIX_MAX_VOLUME/4:
			mvol->setSelected("Kısık");
			break;
	}
}
