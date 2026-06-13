#pragma once
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "uart.h"

static size_t MEMORIA_BYTES_MAX = 1000 * 520; // 520 KB
static size_t MEMORIA_USADA = 0; // memória alocada durante o processo
static int debug = 1;

void* mem_alocar(size_t bytes) {
    MEMORIA_USADA += bytes;
    if(MEMORIA_USADA > MEMORIA_BYTES_MAX) {
        gravar("[LIMITE EXCEDIDO]: Memória usada maior do que disponível:\n");
        gravar("MEMORIA_USADA: %d\n", MEMORIA_USADA);
        gravar("MEMORIA_BYTES_MAX: %d\n", MEMORIA_BYTES_MAX);
        sair(1);
    }
    if(debug == 1) gravar("MEMORIA_USADA: %d/%d\n", MEMORIA_USADA, MEMORIA_BYTES_MAX);
    return (void*)malloc(bytes);
}

void mem_liberar(void* ponteiro, size_t bytes) {
    MEMORIA_USADA -= bytes;
    free(ponteiro);
}