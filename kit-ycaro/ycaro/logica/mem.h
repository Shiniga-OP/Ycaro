#pragma once
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "config.h"

void* mem_alocar(size_t bytes);
void mem_liberar(void* ponteiro, size_t bytes);
void* mem_alocar_exec(size_t bytes);
void mem_liberar_exec(void* ponteiro, size_t bytes);

#if MOTOR
static size_t MEM_MAX_DRAM = 1000 * 328; // 328 KB
static size_t MEM_USADA_DRAM = 0; // memória alocada durante o processo
static size_t MEM_MAX_IRAM = 1000 * 192; // 192 KB executável
static size_t MEM_USADA_IRAM = 0; // memória alocada pra execução

void* mem_alocar(size_t bytes) {
    MEM_USADA_DRAM += bytes;
    if(MEM_USADA_DRAM > MEM_MAX_DRAM) {
        LOG("[LIMITE EXCEDIDO]: Memória usada maior do que disponível:\n");
        LOG("MEMÓRIA ALOCADA: %zu\n", bytes);
        LOG("MEM_USADA_DRAM: %zu\n", MEM_USADA_DRAM);
        LOG("MEM_MAX_DRAM: %zu\n", MEM_MAX_DRAM);
        exit(1);
    }
    LOG("MEM_USADA_DRAM: %zu/%zu\n", MEM_USADA_DRAM, MEM_MAX_DRAM);
    return (void*)malloc(bytes);
}

void mem_liberar(void* ponteiro, size_t bytes) {
    if(bytes > MEM_USADA_DRAM) {
        LOG("[ERRO]: Liberando mais bytes do que está em uso (DRAM)\n");
        exit(1);
    }
    MEM_USADA_DRAM -= bytes;
    free(ponteiro);
    LOG("MEMÓRIA LIBERADA: %zu\n", bytes);
    LOG("MEM_USADA_DRAM: %zu/%zu\n", MEM_USADA_DRAM, MEM_MAX_DRAM);
}

#include "../sistema/memexec.h"
#endif