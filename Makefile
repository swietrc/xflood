CC=gcc
FLAGS=-Wall -Wextra --std=c99

################# MODULES ####################

board.o: src/board.c src/board.h
	$(CC) -c src/board.c $(FLAGS)

boardTests.o: test/boardTests.c test/boardTests.h board.o
	$(CC) -c test/boardTests.c $(FLAGS)

allTests.o: test/allTests.c boardTests.o
	$(CC) -c test/allTests.c $(FLAGS)

############## REGULAR TARGETS ################

all: src/main.c src/board.c src/board.h
	$(CC) src/main.c src/board.c -o Xflood $(FLAGS) -lSDL2

allTests: allTests.o boardTests.o board.o
	$(CC) allTests.o boardTests.o board.o -o test/allTests $(FLAGS) -lcunit

################### TASKS #####################

.PHONY: docs clean
docs:
	doxygen ./Doxyfile

clean:
	rm -rf *.o ; rm -rf docs/
