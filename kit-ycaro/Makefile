CC = clang
SDL_FLAGS = $(shell pkg-config --cflags --libs sdl2)

all: motor bin/teste.bin

motor: inicio.c
	$(CC) inicio.c -o motor $(SDL_FLAGS)

teste.bin: teste.c linker.ld
	$(CC) -static -fno-pic teste.c -o teste.elf -Wl,-T,linker.ld -nostdlib
	objcopy -O binary teste.elf bin/inicio.bin

limpar:
	rm -f motor teste.elf bin/teste.bin *.o