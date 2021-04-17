bin = main
folder = source
fold = include
files = $(folder)/main.cpp  $(folder)/Game.cpp $(folder)/Board.cpp $(folder)/Piece.cpp $(folder)/Shape.cpp $(folder)/Stat.cpp $(folder)/Player.cpp $(folder)/Player1.cpp $(folder)/Multi.cpp $(folder)/Client.cpp  $(folder)/IA.cpp  
include = $(fold)/Shape.h  $(fold)/Game.h $(fold)/Board.h $(fold)/Piece.h $(fold)/Stat.h $(fold)/Player.h $(fold)/Player1.h $(fold)/Multi.h $(fold)/IA.h $(fold)/Client.h

main:   $(files) $(include)
	g++ -o $(bin)  $(files)  `sdl2-config --cflags --libs` -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -Wall -Wunused -Werror

clean:
	rm $(bin)
