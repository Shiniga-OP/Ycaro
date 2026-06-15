#pragma once
#include <stdint.h>

#define CONTROLE_CIMA 7
#define CONTROLE_ESQUERDA 6
#define CONTROLE_BAIXO 5
#define CONTROLE_DIREITA 4
#define CONTROLE_ACAO1 3
#define CONTROLE_ACAO2 2
#define CONTROLE_PAUSE 1
#define CONTROLE_REINICIAR 0

// estado dos 8 botões(bit = 1 significa pressionado)
static uint8_t CONTROLE_ESTADO = 0;

uint8_t controle_ler(uint8_t bit);
void controle_def_estado(uint8_t estado);

uint8_t controle_ler(uint8_t bit) {
    return (CONTROLE_ESTADO >> bit) & 1;
}

void controle_def_estado(uint8_t estado) {
    CONTROLE_ESTADO = estado;
}