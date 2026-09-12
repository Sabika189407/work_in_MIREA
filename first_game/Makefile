all: main.o game.o Pacman.o Map.o Ghost.o PauseMenu.o Registration.o StartScreen.o EndScreen.o MainMenu.o
	g++ main.o game.o Pacman.o Map.o Ghost.o PauseMenu.o Registration.o StartScreen.o MainMenu.o EndScreen.o -o game -lsfml-graphics -lsfml-system -lsfml-window

main.o: main.cpp
	g++ -c main.cpp

game.o: game.cpp
	g++ -c game.cpp

Pacman.o: Pacman.cpp
	g++ -c Pacman.cpp

Ghost.o: Ghost.cpp
	g++ -c Ghost.cpp

Map.o: Map.cpp
	g++ -c Map.cpp

PauseMenu.o: PauseMenu.cpp
	g++ -c PauseMenu.cpp

Registration.0: Registration.cpp
	g++ -c Registration.cpp

StartScreen.o: StartScreen.cpp	
	g++ -c StartScreen.cpp

MainMenu.o: MainMenu.cpp
	g++ -c MainMenu.cpp

EndScreen.o: EndScreen.cpp
	g++ -c EndScreen.cpp

clean:
	rm -rf *.o game