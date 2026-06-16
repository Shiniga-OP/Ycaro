#pragma once

#include "mem.h"
#include "config.h"
#include "../sistema/es.h"

void cartucho_carregar(const char *caminho, void* ctx);
#if MOTOR
void cartucho_carregar(const char *caminho, void* ctx) {
    FILE* arquivo = es_abrir(caminho, "rb");
    if(arquivo == NULL) {
        LOG("[ERRO]: não foi possível abrir o cartucho: %s\n", caminho);
        exit(1);
    }
    long tam = es_tam(arquivo);

    void *destino = mem_alocar_exec((size_t)tam);
    es_ler(destino, 1, (size_t)tam, arquivo);
    es_fechar(arquivo);

    void (*entrada)(void*) = (void (*)(void*))destino;
    entrada(ctx);

    mem_liberar_exec(destino, (size_t)tam);
}
#endif