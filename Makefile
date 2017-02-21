CC=gcc
FLAGS=-Wall -Wextra --std=c99

all: src/main.c src/board.c src/board.h
	$(CC) src/main.c src/board.c -o Xflood $(FLAGS) -lSDL2

tests: test/tests.c src/board.c src/board.h
	$(CC) test/tests.c src/board.c -o tests $(FLAGS) -lcunit

.PHONY: docs clean
docs:
	doxygen ./Doxyfile

clean:
	rm -rf *.o ; rm -rf docs/
