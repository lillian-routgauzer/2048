# Definitions for constants
CC=gcc
CFLAGS=-I.

# This will create your final output using .o compiled files
make: main.o maths.o board.o score.o termios.o tiles.o
	$(CC) $(CFLAGS) -o 2048 main.o maths.o board.o score.o termios.o tiles.o

# compile main.o with its dependency
main.o: main.c game.h
	$(CC) $(CFLAGS) -c main.c

# This will clean or remove compiled files so you can start fresh
clean:
	rm -f *.o
run: make
	./2048