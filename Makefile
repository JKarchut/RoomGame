CC=gcc
CFLAGS=-Wall

main: main.o map.o game.o
	${CC} -o main main.o map.o game.o
main.o: Main.c map.h game.h
	${CC} -o main.o -c Main.c ${CFLAGS}
map.o: map.c map.h
	${CC} -o map.o -c map.c ${CFLAGS}
game.o: game.c game.h map.h
	${CC} -o game.o -c game.c ${CFLAGS}


.PHONY: clean

clean:
	-rm -f main.o map.o main game.o
