CC=gcc
CFLAGS=-Wall -lpthread -lm -g
FILES=main.o map.o game.o gamecommands.o gamethreads.o
TARGET=main
SRC_DIR := src
${TARGET}: ${FILES}
	${CC} -o ${TARGET} ${FILES} ${CFLAGS} 
map.o: src/map.c src/map.h
	${CC} -o map.o -c ${SRC_DIR}/map.c ${CFLAGS}
game.o: src/game.c src/game.h
	${CC} -o game.o -c ${SRC_DIR}/game.c ${CFLAGS}
gamethreads.o : src/gamethreads.c src/gamethreads.h
	${CC} -o gamethreads.o -c ${SRC_DIR}/gamethreads.c ${CFLAGS}
gamecommands.o: src/gamecommands.c src/gamecommands.h
	${CC} -o gamecommands.o -c ${SRC_DIR}/gamecommands.c ${CFLAGS}
main.o: src/main.c src/map.h src/game.h
	${CC} -o main.o -c ${SRC_DIR}/main.c ${CFLAGS}


.PHONY: clean

clean:
	-rm -f main.o map.o main game.o gamecommands.o
