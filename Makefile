CC=gcc

all:
	$(CC) main.c -o main -Wall -Wextra -lSDL2

test: test.c
	$(CC) test.c -o test -Wall -Wextra -lcunit

doc:
	doxygen .
