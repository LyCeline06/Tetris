bin = main
folder = source
files = $(folder)/main.cpp  $(folder)/Game.cpp $(folder)/Board.cpp $(folder)/Piece.cpp $(folder)/Shape.cpp


main:   $(files)
	g++ -o $(bin)  $(files)  `sdl2-config --cflags --libs` -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -Wall -Wunused

clean:
	rm $(bin)
