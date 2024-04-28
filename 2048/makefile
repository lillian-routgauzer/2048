# Definitions for constants
CC=gcc
CFLAGS=-I.
LIBS=-lm

# This will create your final output using .o compiled files
make: main.o maths.o board.o score.o termios.o tiles.o
	$(CC) $(CFLAGS) -o 2048 main.o maths.o board.o score.o termios.o tiles.o $(LIBS)

# compile main.o with its dependency
main.o: main.c game.h
	$(CC) $(CFLAGS) -c main.c

maths.o: maths.c game.h
	$(CC) $(CFLAGS) -c maths.c

board.o: board.c game.h
	$(CC) $(CFLAGS) -c board.c

score.o: score.c game.h
	$(CC) $(CFLAGS) -c score.c

termios.o: termios.c game.h
	$(CC) $(CFLAGS) -c termios.c

tiles.o: tiles.c game.h
	$(CC) $(CFLAGS) -c tiles.c

# This will clean or remove compiled files so you can start fresh
clean:
	rm -f *.o
run: make
	./2048