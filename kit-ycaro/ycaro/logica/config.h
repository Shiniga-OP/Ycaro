#pragma once

#define DEBUG 1
#define MOTOR 1
#define EVENTO_PADRAO 0
#define EVENTO_SAIDA 1

void def_evento_global(int estado);
int obter_evento_global(int estado);

#if MOTOR
#if DEBUG
    #define LOG(...) printf(__VA_ARGS__)
#else
    #define LOG(...)
#endif

static int EVENTO_GLOBAL = EVENTO_PADRAO;

void def_evento_global(int estado) {
    EVENTO_GLOBAL = estado;
}

int obter_evento_global(int estado) {
    return EVENTO_GLOBAL;
}
#endif