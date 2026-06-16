#pragma once
#include <SDL2/SDL.h>
#include <stdio.h>
#include "../logica/config.h"

typedef struct {
    SDL_Window* janela;
    SDL_Renderer* render;
    SDL_Texture* textura;
    SDL_Event evento;
} Contexto;

void* _iniciar_renderizacao(Tela* tela) {
    // 1. iniciar
    Contexto* ctx = (Contexto*)malloc(sizeof(Contexto));
    
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        LOG("Erro SDL: %s\n", SDL_GetError());
        exit(1);
    }
    // 2. criar a janela
    ctx->janela = SDL_CreateWindow("tela emulador", 
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, tela->largura, tela->altura, SDL_WINDOW_SHOWN);
    
    // 3. criar o renderizador
    ctx->render = SDL_CreateRenderer(ctx->janela, -1, SDL_RENDERER_ACCELERATED);

    // 4. criar a textura que vai receber os dados brutos do nosso framebuffer RAM
    ctx->textura = SDL_CreateTexture(ctx->render, 
        SDL_PIXELFORMAT_RGB565, SDL_TEXTUREACCESS_STREAMING, tela->largura, tela->altura);
    return (void*)ctx;
}

void _att_renderizacao(Tela* tela, void* dado) {
    Contexto* ctx = (Contexto*)dado;
    
    while(SDL_PollEvent(&ctx->evento)) {
        if(ctx->evento.type == SDL_QUIT) {
            def_evento_global(EVENTO_SAIDA);
        }
    }
    // --- ENVIAR PARA A TELA ---
    // copia o array da RAM direto para a textura da SDL
    SDL_UpdateTexture(ctx->textura, NULL, tela->framebuffer, tela->largura * sizeof(unsigned short));
    
    SDL_RenderClear(ctx->render);
    SDL_RenderCopy(ctx->render, ctx->textura, NULL, NULL);
    SDL_RenderPresent(ctx->render); // joga os pixels na tela do Termux-X11
}

void _esperar_renderizacao(int ms) {
    SDL_Delay(ms);
}

void _liberar_renderizacao(void* dado) {
    Contexto* ctx = (Contexto*)dado;
    // limpeza ao sair
    SDL_DestroyTexture(ctx->textura);
    SDL_DestroyRenderer(ctx->render);
    SDL_DestroyWindow(ctx->janela);
    free(ctx);
    SDL_Quit();
}