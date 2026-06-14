#pragma once
#include <stdio.h>

FILE* es_abrir(const char* caminho, const char* modo) {
    return fopen(caminho, modo);
}

size_t es_ler(void* buf, size_t tam, size_t n, FILE* a) {
    return fread(buf, tam, n, a);
}

void es_fechar(FILE* a) {
    fclose(a);
}