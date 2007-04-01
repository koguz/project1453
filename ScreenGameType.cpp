#include "ScreenGameType.h"

ScreenGameType::ScreenGameType(SDL_Surface *screen):SDLScreen(screen)
{
	arka = new SDLWidget("ui/arkaKirmizi.jpg");
	arka->setPosition(0, 0);
	addWidget(arka);
	
	imgYeniceri = new SDLWidget("ui/img_yeniceri.jpg");
	imgYeniceri->setPosition(520, 30);
	addWidget(imgYeniceri);
	
	title = new SDLLabel("Yeni Oyun", 36);
	title->setPosition((520-title->getWidth())/2, 100);
	addWidget(title);
	
	lblUlke = new SDLLabel("Ülkeniz");
	lblUlke->setPosition(30, 200);
	addWidget(lblUlke);
	
	ulke = new SDLCombo();
	ulke->setPosition(30, 230);
	ulke->addOption("Osmanlılar", "Osmanlı", true);
	ulke->addOption("Bizanslılar", "Bizans");
	addWidget(ulke);
	
	lblRakip = new SDLLabel("Rakip Zorluğu");
	lblRakip->setPosition(200, 200);
	addWidget(lblRakip);
	
	rakipTip = new SDLCombo();
	rakipTip->setPosition(200, 230);
	rakipTip->addOption("Agresif", "2");
	rakipTip->addOption("Normal", "1", true);
	rakipTip->addOption("Pasif", "0");
	addWidget(rakipTip);
	
	lblHarita = new SDLLabel("Haritayı Seçiniz");
	lblHarita->setPosition(350, 200);
	addWidget(lblHarita);
	
	haritalar = new SDLListView(4); // NOTE bu liste database'den gelse?
	haritalar->addItem("İstanbul.hrt");
	haritalar->addItem("İzmir.hrt");
	haritalar->addItem("Bursa.hrt");
	haritalar->addItem("Deneme.hrt");
	haritalar->addItem("Temp.hrt");
	haritalar->addItem("Edirne.hrt");
	haritalar->addItem("TekKisilik.hrt");
	haritalar->addItem("Son.hrt");
	haritalar->setPosition(350, 230);
	addWidget(haritalar);
	
	lblAciklama = new SDLLabel("Açıklama:");
	lblAciklama->setPosition(30, 350);
	addWidget(lblAciklama);
	
	string desc = "Tek Görev [p] Bu oyun türünde amaç rakibin bütün birimlerini ve binalarını ortadan kaldırmaktır.";
	aciklama = new SDLTextView(desc, 300, 4);
	aciklama->setPosition(30, 380);
	addWidget(aciklama);
	
	baslat = new SDLButton("ui/kucukDugme.jpg", "Oyunu Başlat");
	baslat->setPosition(520 + ((imgYeniceri->getWidth() - baslat->getWidth())/2), 470);
	addWidget(baslat);
	
	anaEkranaDon = new SDLButton("ui/kucukDugme.jpg", "« Ana Ekrana Dön");
	anaEkranaDon->setPosition(520 + ((imgYeniceri->getWidth() - anaEkranaDon->getWidth())/2), 510);
	addWidget(anaEkranaDon);
	
	err = new SDLLabel(" ");
	err->setPosition(350, 300+haritalar->getHeight());
	addWidget(err);	
}
