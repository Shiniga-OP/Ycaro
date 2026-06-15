#pragma once
#include "logica/mem.h"
#include "logica/controle.h"
#include "logica/graficos/tela.h"
#include "logica/graficos/yimg.h"
#include "logica/cartucho.h"

typedef struct {
    Tela* (*tela_iniciar)(int largura, int altura);
    void (*render_pixel)(Tela* t, int x, int y, unsigned short cor);
    void (*render_retangulo)(Tela* t, int x, int y, int largura, int altura, unsigned short cor);
    void (*render_limpar)(Tela* t, unsigned short cor);
    void (*render_att)(Tela* t);
    void (*render_esperar)(int ms);
    void (*render_liberar)(Tela* t);
    uint8_t (*controle_ler)(uint8_t bit);
    void (*controle_def_estado)(uint8_t estado);
    YImg* (*yimg_carregar)(const char *caminho);
    void (*yimg_render)(Tela* t, YImg* img, int x, int y);
    void (*yimg_liberar)(YImg *img);
    void (*def_evento_global)(int estado);
    int (*obter_evento_global)(int estado);
    void (*cartucho_carregar)(const char* caminho, void* ctx);
} Ycaro;