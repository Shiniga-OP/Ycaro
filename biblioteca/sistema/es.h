#pragma once
#include <SDL2/SDL.h>
#include <stdio.h>
#include "../logica/controle.h"

FILE* es_abrir(const char* caminho, const char* modo);
size_t es_ler(void* buf, size_t tam, size_t n, FILE* a);
void es_fechar(FILE* a);
void controle_att();

// implementação:
FILE* es_abrir(const char* caminho, const char* modo) {
    return fopen(caminho, modo);
}

size_t es_ler(void* buf, size_t tam, size_t n, FILE* a) {
    return fread(buf, tam, n, a);
}

void es_fechar(FILE* a) {
    fclose(a);
}

void controle_att() {
    SDL_PumpEvents();
    const Uint8* teclas = SDL_GetKeyboardState(NULL);
    
    CONTROLE_ESTADO = 0;
    if(teclas[SDL_SCANCODE_W]) CONTROLE_ESTADO |= (1 << 7);
    if(teclas[SDL_SCANCODE_A]) CONTROLE_ESTADO |= (1 << 6);
    if(teclas[SDL_SCANCODE_S]) CONTROLE_ESTADO |= (1 << 5);
    if(teclas[SDL_SCANCODE_D]) CONTROLE_ESTADO |= (1 << 4);
    if(teclas[SDL_SCANCODE_SPACE]) CONTROLE_ESTADO |= (1 << 3);
    if(teclas[SDL_SCANCODE_RETURN]) CONTROLE_ESTADO |= (1 << 2);
    if(teclas[SDL_SCANCODE_HOME]) CONTROLE_ESTADO |= (1 << 1);
    if(teclas[SDL_SCANCODE_END]) CONTROLE_ESTADO |= (1 << 0);
}