#include "ScreenGameType.h"

ScreenGameType::ScreenGameType(SDL_Surface *screen):SDLScreen(screen)
{
	arka = new SDLWidget("ui/ana_sayfa3.jpg");
	arka->setPosition(0, 0);
	addWidget(arka);
	
	title = new SDLLabel("Yeni Oyun", 28);
	title->setPosition(530, 170);
	addWidget(title);
	
// 	lblUlke = new SDLLabel("Ülkeniz");
// 	lblUlke->setPosition(30, 200);
// 	addWidget(lblUlke);
// 	
// 	ulke = new SDLCombo();
// 	ulke->setPosition(30, 230);
// 	ulke->addOption("Osmanlılar", "Osmanlı", true);
// 	ulke->addOption("Bizanslılar", "Bizans");
// 	addWidget(ulke);
// 	
// 	lblRakip = new SDLLabel("Rakip Zorluğu");
// 	lblRakip->setPosition(200, 200);
// 	addWidget(lblRakip);
// 	
// 	rakipTip = new SDLCombo();
// 	rakipTip->setPosition(200, 230);
// 	rakipTip->addOption("Agresif", "2");
// 	rakipTip->addOption("Normal", "1", true);
// 	rakipTip->addOption("Pasif", "0");
// 	addWidget(rakipTip);
// 	
// 	lblHarita = new SDLLabel("Haritayı Seçiniz");
// 	lblHarita->setPosition(350, 200);
// 	addWidget(lblHarita);
// 	
// 	haritalar = new SDLListView(4); // NOTE bu liste database'den gelse?
// 	haritalar->addItem("İstanbul");
// 	haritalar->addItem("İzmir");
// 	haritalar->addItem("Bursa");
// 	haritalar->addItem("Temp");
// 	haritalar->addItem("Edirne");
// 	haritalar->addItem("TekKisilik");
// 	haritalar->addItem("Son");
// 	haritalar->setPosition(350, 230);
// 	addWidget(haritalar);
/*	
	lblAciklama = new SDLLabel("Açıklama:");
	lblAciklama->setPosition(30, 350);
	addWidget(lblAciklama);*/
	
	string desc = "Tek Görev [p] Bu oyun türünde amaç rakibin bütün birimlerini ve binalarını ortadan kaldırmaktır. ";
	aciklama = new SDLTextView(desc, 200, 4);
	aciklama->setPosition(485, 280);
	addWidget(aciklama);
	
	baslat = new SDLButton("ui/button.png", "Oyunu Başlat");
	baslat->setPosition(470, 435);
	addWidget(baslat);
	
	anaEkranaDon = new SDLButton("ui/button.png", "Ana Menü");
	anaEkranaDon->setPosition(470, 485);
	addWidget(anaEkranaDon);
	
// 	err = new SDLLabel(" ");
// 	err->setPosition(350, 300+haritalar->getHeight());
// 	addWidget(err);	
}
