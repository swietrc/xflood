CC=gcc
FLAGS=-Wall -Wextra --std=c99

################# MODULES ####################

utils.o: src/utils.c src/utils.h
	$(CC) -c src/utils.c $(FLAGS)

board.o: src/board.c src/board.h
	$(CC) -c src/board.c $(FLAGS)

colorList.o: src/colorList.c src/colorList.h
	$(CC) -c src/colorList.c $(FLAGS)

gameScreen.o: src/gameScreen.c src/gameScreen.h
	$(CC) -c src/gameScreen.c $(FLAGS)

game.o: src/game.c src/game.h
	$(CC) -c src/game.c $(FLAGS)

menuScreen.o: src/menuScreen.c src/menuScreen.h
	$(CC) -c src/menuScreen.c $(FLAGS)

solver.o: src/solver.c src/solver.h src/colorList.h board.o
	$(CC) -c src/solver.c board.o $(FLAGS)

boardTests.o: test/boardTests.c test/boardTests.h board.o
	$(CC) -c test/boardTests.c $(FLAGS)

colorListTests.o: test/colorListTests.c test/colorListTests.h colorList.o
	$(CC) -c test/colorListTests.c $(FLAGS)

solverTests.o: test/solverTests.c test/solverTests.h solver.o
	$(CC) -c test/solverTests.c $(FLAGS)

allTests.o: test/allTests.c boardTests.o colorListTests.o solverTests.o
	$(CC) -c test/allTests.c $(FLAGS)

############## REGULAR TARGETS ################

all: src/main.c board.o gameScreen.o game.o menuScreen.o utils.o
	$(CC) src/main.c board.o gameScreen.o game.o menuScreen.o utils.o -o Xflood $(FLAGS) -lSDL2 -lSDL2_ttf -lSDL2_image

solver: src/solver.c board.o colorList.o
	$(CC) src/solver.c board.o colorList.o -o solver $(FLAGS)

allTests: allTests.o boardTests.o board.o colorListTests.o colorList.o solverTests.o solver.o
	$(CC) allTests.o boardTests.o board.o colorListTests.o colorList.o solverTests.o solver.o -o test/allTests $(FLAGS) -lcunit

################### TASKS #####################

.PHONY: docs clean
docs:
	doxygen ./Doxyfile

clean:
	rm -rf *.o ; rm -rf docs/
