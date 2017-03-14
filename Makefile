CC=gcc
FLAGS=-Wall -Wextra --std=c99

################# MODULES ####################

utils.o: src/utils.c src/utils.h
	$(CC) -c src/utils.c $(FLAGS)

board.o: src/board.c src/board.h
	$(CC) -c src/board.c $(FLAGS)

gameScreen.o: src/gameScreen.c src/gameScreen.h
	$(CC) -c src/gameScreen.c $(FLAGS)

game.o: src/game.c src/game.h
	$(CC) -c src/game.c $(FLAGS)

menuScreen.o: src/menuScreen.c src/menuScreen.h
	$(CC) -c src/menuScreen.c $(FLAGS)

boardTests.o: test/boardTests.c test/boardTests.h board.o
	$(CC) -c test/boardTests.c $(FLAGS)

allTests.o: test/allTests.c boardTests.o
	$(CC) -c test/allTests.c $(FLAGS)

############## REGULAR TARGETS ################

all: src/main.c board.o gameScreen.o game.o menuScreen.o utils.o
	$(CC) src/main.c board.o gameScreen.o game.o menuScreen.o utils.o -o Xflood $(FLAGS) -lSDL2 -lSDL2_ttf -lSDL2_image

allTests: allTests.o boardTests.o board.o
	$(CC) allTests.o boardTests.o board.o -o test/allTests $(FLAGS) -lcunit

################### TASKS #####################

.PHONY: docs clean
docs:
	doxygen ./Doxyfile

clean:
	rm -rf *.o ; rm -rf docs/
