OBJ := asciigame.o internals.o termsize.o windows.o
CC := gcc
CFLAGS := -g -Wall -ansi -O2

all: $(OBJ)
	ar cr libasciigame.a $(OBJ)
	ranlib libasciigame.a

test: all
	$(CC) $(CFLAGS) asciigame-test.c -L. -lasciigame -o asciigame-test
	asciigame-test

release: all
	rm $(OBJ)

clean:
	rm $(OBJ)