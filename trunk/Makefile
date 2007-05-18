CC=g++
FLAGS=`sdl-config --cflags` -c -g -O0 # bu ikisi debug icin
# FLAGS=`sdl-config --cflags` -c -march=i686 -O3 -mfpmath=sse -pipe -mmmx -msse -msse2 -fomit-frame-pointer
LIBS=`sdl-config --libs` -lSDL_image -lSDL_gfx -lSDL_ttf -lSDL_mixer -lm

all: g1453

again: clean all

g1453: main.o \
	Player.o \
	Map.o \
	Application.o \
	Game.o \
	SDLCursor.o \
	SDLMixer.o \
	SDLMusic.o \
	SDLWidget.o \
	SDLButton.o \
	SDLFont.o \
	SDLCombo.o \
	SDLLabel.o \
	SDLCheckBox.o \
	SDLTextView.o \
	SDLListView.o \
	SDLProgressBar.o \
	SDLCommandButton.o \
	SDLScreen.o \
	ScreenMain.o \
	ScreenGameType.o \
	ScreenSettings.o \
	ScreenCredits.o \
	Resource.o \
	Resources.o \
	Cost.o \
	BaseObject.o \
	BaseGraphicObject.o \
	BaseUnit.o \
	UOKoylu.o \
	UBSerf.o \
	BaseBuilding.o \
	BOEv.o \
	BOSehirMerkezi.o \
	Tech.o \
	TTemelTech.o \
	Sprite.o 
	
	$(CC) $(LIBS) main.o \
	Player.o \
	Map.o \
	Application.o \
	Game.o \
	SDLCursor.o \
	SDLMixer.o \
	SDLMusic.o \
	SDLWidget.o \
	SDLButton.o \
	SDLFont.o \
	SDLCombo.o \
	SDLLabel.o \
	SDLCheckBox.o \
	SDLTextView.o \
	SDLListView.o \
	SDLProgressBar.o \
	SDLCommandButton.o \
	SDLScreen.o \
	ScreenMain.o \
	ScreenGameType.o \
	ScreenSettings.o \
	ScreenCredits.o \
	Resource.o \
	Resources.o \
	Cost.o \
	BaseObject.o \
	BaseGraphicObject.o \
	BaseUnit.o \
	UOKoylu.o \
	UBSerf.o \
	BaseBuilding.o \
	BOEv.o \
	BOSehirMerkezi.o \
	Tech.o \
	TTemelTech.o \
	Sprite.o -o g1453
	
main.o: main.cpp
	$(CC) $(FLAGS) main.cpp
	
Application.o: Application.cpp
	$(CC) $(FLAGS) Application.cpp

ScreenMain.o: ScreenMain.cpp
	$(CC) $(FLAGS) ScreenMain.cpp

ScreenGameType.o: ScreenGameType.cpp
	$(CC) $(FLAGS) ScreenGameType.cpp
	
ScreenSettings.o: ScreenSettings.cpp
	$(CC) $(FLAGS) ScreenSettings.cpp

ScreenCredits.o: ScreenCredits.cpp
	$(CC) $(FLAGS) ScreenCredits.cpp

SDLCursor.o: SDLCursor.cpp
	$(CC) $(FLAGS) SDLCursor.cpp

# game related

Map.o: Map.cpp
	$(CC) $(FLAGS) Map.cpp

Player.o: Player.cpp
	$(CC) $(FLAGS) Player.cpp

Game.o: Game.cpp
	$(CC) $(FLAGS) Game.cpp

BaseObject.o: BaseObject.cpp
	$(CC) $(FLAGS) BaseObject.cpp

BaseGraphicObject.o: BaseGraphicObject.cpp
	$(CC) $(FLAGS) BaseGraphicObject.cpp

BaseUnit.o: BaseUnit.cpp
	$(CC) $(FLAGS) BaseUnit.cpp

SDLMixer.o: SDLMixer.cpp
	$(CC) $(FLAGS) SDLMixer.cpp
	
SDLMusic.o: SDLMusic.cpp
	$(CC) $(FLAGS) SDLMusic.cpp

# Units.o: Units.cpp
# 	$(CC) $(FLAGS) Units.cpp

BaseBuilding.o: BaseBuilding.cpp
	$(CC) $(FLAGS) BaseBuilding.cpp

# Buildings.o: Buildings.cpp
# 	$(CC) $(FLAGS) Buildings.cpp

Resource.o: Resource.cpp
	$(CC) $(FLAGS) Resource.cpp
	
Resources.o: Resources.cpp
	$(CC) $(FLAGS) Resources.cpp

Cost.o: Cost.cpp
	$(CC) $(FLAGS) Cost.cpp

Tech.o: Tech.cpp
	$(CC) $(FLAGS) Tech.cpp
	
# Technologies.o: Technologies.cpp
# 	$(CC) $(FLAGS) Technologies.cpp

# ortak

TTemelTech.o: TTemelTech.cpp
	$(CC) $(FLAGS) TTemelTech.cpp

# Osmanli birimleri

BOEv.o: BOEv.cpp
	$(CC) $(FLAGS) BOEv.cpp

BOSehirMerkezi.o: BOSehirMerkezi.cpp
	$(CC) $(FLAGS) BOSehirMerkezi.cpp
	
UOKoylu.o: UOKoylu.cpp
	$(CC) $(FLAGS) UOKoylu.cpp


# Bizans Birimleri

UBSerf.o: UBSerf.cpp
	$(CC) $(FLAGS) UBSerf.cpp

# Additional 

Sprite.o: Sprite.cpp
	$(CC) $(FLAGS) Sprite.cpp

SDLCommandButton.o: SDLCommandButton.cpp
	$(CC) $(FLAGS) SDLCommandButton.cpp

# SDLGUI base below

SDLScreen.o: SDLScreen.cpp
	$(CC) $(FLAGS) SDLScreen.cpp

SDLWidget.o: SDLWidget.cpp
	$(CC) $(FLAGS) SDLWidget.cpp
	
SDLButton.o: SDLButton.cpp
	$(CC) $(FLAGS) SDLButton.cpp

SDLFont.o: SDLFont.cpp
	$(CC) $(FLAGS) SDLFont.cpp

SDLCombo.o: SDLCombo.cpp
	$(CC) $(FLAGS) SDLCombo.cpp

SDLLabel.o: SDLLabel.cpp
	$(CC) $(FLAGS) SDLLabel.cpp
	
SDLCheckBox.o: SDLCheckBox.cpp
	$(CC) $(FLAGS) SDLCheckBox.cpp
	
SDLTextView.o: SDLTextView.cpp
	$(CC) $(FLAGS) SDLTextView.cpp

SDLListView.o: SDLListView.cpp
	$(CC) $(FLAGS) SDLListView.cpp

SDLProgressBar.o: SDLProgressBar.cpp
	$(CC) $(FLAGS) SDLProgressBar.cpp

clean:
	rm -rf *.o g1453

