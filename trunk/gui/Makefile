CC=g++
FLAGS=`sdl-config --cflags` -c -g 
LIBS=`sdl-config --libs` -lSDL_image -lSDL_gfx -lSDL_ttf

all: guitest

again: clean all

guitest: main.o Application.o SDLScreen.o SDLButton.o SDLWidget.o SDLFont.o SDLCombo.o SDLLabel.o SDLCheckBox.o SDLTextView.o SDLListView.o SDLProgressBar.o
	$(CC) $(LIBS) main.o Application.o SDLScreen.o SDLButton.o SDLFont.o SDLWidget.o SDLCombo.o SDLLabel.o SDLCheckBox.o SDLTextView.o SDLListView.o SDLProgressBar.o -o guitest
	
main.o: main.cpp
	$(CC) $(FLAGS) main.cpp
	
Application.o: Application.cpp
	$(CC) $(FLAGS) Application.cpp

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
	rm -rf *.o guitest

