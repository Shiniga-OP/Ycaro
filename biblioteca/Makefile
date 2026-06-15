CC = clang
SDL_FLAGS = $(shell pkg-config --cflags --libs sdl2)

all: motor

motor: inicio.c
	$(CC) inicio.c -o motor $(SDL_FLAGS)

limpar:
	rm -f motor *.o teste.bin