#pragma once
#include <sys/mman.h>

void* mem_alocar_exec(size_t bytes) {
    MEM_USADA_IRAM += bytes;
    if(MEM_USADA_IRAM > MEM_MAX_IRAM) {
        LOG("[LIMITE EXCEDIDO]: Memória usada maior do que disponível:\n");
        LOG("MEMÓRIA ALOCADA: %zu\n", bytes);
        LOG("MEM_USADA_IRAM: %zu\n", MEM_USADA_IRAM);
        LOG("MEM_MAX_IRAM: %zu\n", MEM_MAX_IRAM);
        exit(1);
    }
    LOG("MEM_USADA_IRAM: %zu/%zu\n", MEM_USADA_IRAM, MEM_MAX_IRAM);

    void *ponteiro = mmap(NULL, bytes, PROT_READ | PROT_WRITE | PROT_EXEC,
        MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if(ponteiro == MAP_FAILED) {
        LOG("[ERRO]: mmap falhou ao alocar memória executável\n");
        exit(1);
    }
    return ponteiro;
}

void mem_liberar_exec(void* ponteiro, size_t bytes) {
    if(bytes > MEM_USADA_IRAM) {
        LOG("[ERRO]: Liberando mais bytes do que está em uso (IRAM)\n");
        exit(1);
    }
    MEM_USADA_IRAM -= bytes;
    munmap(ponteiro, bytes);
    LOG("MEMÓRIA LIBERADA: %zu\n", bytes);
    LOG("MEM_USADA_IRAM: %zu/%zu\n", MEM_USADA_IRAM, MEM_MAX_IRAM);
}