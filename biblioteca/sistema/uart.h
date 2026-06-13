#pragma once
#include <stdio.h>
#include <stdarg.h>

#define EVENTO_PADRAO 0
#define EVENTO_SAIDA 1

static int EVENTO_GLOBAL = EVENTO_PADRAO;

void gravar(const char* formato, ...) {
    va_list args;
    va_start(args, formato);
    vprintf(formato, args);
    va_end(args);
}

char uart_ler() {
    return (char)getchar();
}

void sair(int codigo) {
    exit(codigo);
}