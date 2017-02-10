CC=gcc

all:
	$(CC) main.c -o Xflood -Wall -Wextra -lSDL2

testBoard: testBoard.c
	$(CC) testBoard.c -o testBoard -Wall -Wextra -lcunit

tests: testBoard.c
	$(CC) testBoard.c -o tests -Wall -Wextra -lcunit

doc:
	doxygen .
