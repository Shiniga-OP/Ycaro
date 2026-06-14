#pragma once
#include <string.h>
#include "../mem.h"
#include "../config.h"

typedef struct {
    int largura;
    int altura;
    unsigned short* framebuffer;
} Tela;

static void* ctx;

Tela* tela_iniciar(int largura, int altura);
void render_pixel(Tela* t, int x, int y, unsigned short cor);
void render_retangulo(Tela* t, int x, int y, int largura, int altura, unsigned short cor);
void render_limpar(Tela* t, unsigned short cor);
void render_att(Tela* t);
void render_esperar(int ms);
void render_liberar(Tela* t);

#include "../../sistema/video.h"

Tela* tela_iniciar(int largura, int altura) {
    Tela* t = (Tela*)mem_alocar(sizeof(Tela));
    t->largura = largura;
    t->altura = altura;
    t->framebuffer = (unsigned short*)mem_alocar(sizeof(unsigned short) * (largura * altura));
    ctx = _iniciar_renderizacao(t);
    LOG("Tela iniciada: %dx%d\n", largura, altura);
    
    return t;
}

void render_pixel(Tela* t, int x, int y, unsigned short cor) {
    if(x >= 0 && x < t->largura && y >= 0 && y < t->altura) {
        t->framebuffer[y*t->largura+x] = cor;
    }
}

void render_retangulo(Tela* t, int x, int y, int largura, int altura, unsigned short cor) {
    for(int i = 0; i < altura; i++) {
        for(int j = 0; j < largura; j++) {
            render_pixel(t, x + j, y + i, cor);
        }
    }
}

void render_limpar(Tela* t, unsigned short cor) {
    size_t total_pixels = t->largura * t->altura;
    unsigned short* fim = t->framebuffer + total_pixels;
    for(unsigned short* p = t->framebuffer; p < fim; p++) {
        *p = cor;
    }
}

void render_att(Tela* t) {
    _att_renderizacao(t, ctx);
}

void render_esperar(int ms) {
    _esperar_renderizacao(ms);
}

void render_liberar(Tela* t) {
    mem_liberar(t->framebuffer, sizeof(unsigned short) * (t->largura * t->altura));
    mem_liberar(t, sizeof(Tela));
    _liberar_renderizacao(ctx);
}