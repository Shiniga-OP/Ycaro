#pragma once
#include <stdio.h>
#include <stdint.h>
#include "../logica/config.h"
#include "../logica/controle.h"

FILE* es_abrir(const char* caminho, const char* modo);
size_t es_ler(void* buf, size_t tam, size_t n, FILE* a);
void es_fechar(FILE* a);
long es_tam(FILE* a);
void controle_att();

#if MOTOR
#include <SDL2/SDL.h>

// implementação:
FILE* es_abrir(const char* caminho, const char* modo) {
    FILE* a = fopen(caminho, modo);
    if(a == NULL) {
        LOG("[ERRO] ao abrir arquivo no caminho %s\n", caminho);
    }
    return a;
}

size_t es_ler(void* buf, size_t tam, size_t n, FILE* a) {
    return fread(buf, tam, n, a);
}

void es_fechar(FILE* a) {
    fclose(a);
}

long es_tam(FILE* a) {
    long pos_atual = ftell(a);
    fseek(a, 0, SEEK_END);
    long tam = ftell(a);
    fseek(a, pos_atual, SEEK_SET);
    return tam;
}

void controle_att() {
    SDL_PumpEvents();
    const Uint8* teclas = SDL_GetKeyboardState(NULL);
    
    uint8_t estado = 0;
    
    if(teclas[SDL_SCANCODE_W]) estado |= (1 << 7);
    if(teclas[SDL_SCANCODE_A]) estado |= (1 << 6);
    if(teclas[SDL_SCANCODE_S]) estado |= (1 << 5);
    if(teclas[SDL_SCANCODE_D]) estado |= (1 << 4);
    if(teclas[SDL_SCANCODE_SPACE]) estado |= (1 << 3);
    if(teclas[SDL_SCANCODE_RETURN]) estado |= (1 << 2);
    if(teclas[SDL_SCANCODE_HOME]) estado |= (1 << 1);
    if(teclas[SDL_SCANCODE_END]) estado |= (1 << 0);
    controle_def_estado(estado);
}
#endif