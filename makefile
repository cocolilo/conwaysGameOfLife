all:
	gcc board.c conways_game_of_life.c -lm -w -lSDL2main -lSDL2 -o vida
