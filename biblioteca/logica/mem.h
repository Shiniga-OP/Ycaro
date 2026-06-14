#pragma once
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "config.h"

static size_t MEMORIA_BYTES_MAX = 1000 * 520; // 520 KB
static size_t MEMORIA_USADA = 0; // memória alocada durante o processo
void* mem_alocar(size_t bytes) {
    MEMORIA_USADA += bytes;
    if(MEMORIA_USADA > MEMORIA_BYTES_MAX) {
        LOG("[LIMITE EXCEDIDO]: Memória usada maior do que disponível:\n");
        LOG("MEMÓRIA ALOCADA: %zu\n", bytes);
        LOG("MEMORIA_USADA: %zu\n", MEMORIA_USADA);
        LOG("MEMORIA_BYTES_MAX: %zu\n", MEMORIA_BYTES_MAX);
        exit(1);
    }
    LOG("MEMORIA_USADA: %zu/%zu\n", MEMORIA_USADA, MEMORIA_BYTES_MAX);
    return (void*)malloc(bytes);
}

void mem_liberar(void* ponteiro, size_t bytes) {
    MEMORIA_USADA -= bytes;
    free(ponteiro);
    LOG("MEMÓRIA LIBERADA: %zu\n", bytes);
    LOG("MEMORIA_USADA: %zu/%zu\n", MEMORIA_USADA, MEMORIA_BYTES_MAX);
}