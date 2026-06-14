#pragma once

#define DEBUG 1
#define EVENTO_PADRAO 0
#define EVENTO_SAIDA 1

static int EVENTO_GLOBAL = EVENTO_PADRAO;

#if DEBUG
    #define LOG(...) printf(__VA_ARGS__)
#else
    #define LOG(...)
#endif