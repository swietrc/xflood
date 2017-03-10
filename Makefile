CC=gcc
FLAGS=-Wall -Wextra

all: src/main.c src/board.c src/board.h src/gameScreen.c src/gameScreen.h src/menuScreen.c src/menuScreen.h
	$(CC) src/main.c src/board.c src/gameScreen.c src/menuScreen.c -o Xflood $(FLAGS) -lSDL2

tests: test/tests.c src/board.c src/board.h
	$(CC) test/tests.c src/board.c -o tests $(FLAGS) -lcunit

.PHONY: docs
docs:
	doxygen ./Doxyfile
