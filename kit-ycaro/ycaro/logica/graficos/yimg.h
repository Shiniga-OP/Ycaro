#pragma once
#include <stdint.h>
#include "tela.h"
#include "../config.h"
#include "../../sistema/es.h"

// formato RLE: sequência de blocos[uint16_t cor][uint8_t repeticoes]
// repeticoes = quantidade de vezes que 'cor' se repete(1..255)
typedef struct {
    uint8_t largura;
    uint8_t altura;
    uint8_t formato;
    uint16_t dados_tam; // quantidade de uint16_t/blocos em 'dados'
    uint16_t* dados;
} YImg;

YImg* yimg_carregar(const char *caminho);
void yimg_render(Tela* t, YImg* img, int x, int y);
void yimg_liberar(YImg *img);

#if MOTOR
#define YIMG_TRANSPARENTE 0xF81F // magenta

typedef enum {
    YIMG_CRU = 0,
    YIMG_RLE = 1,
} YImgFormato;

// conta quantos blocos RLE seriam necessários para os pixels dados
static uint32_t yimg__contar_blocos_rle(const uint16_t* pixels, int total) {
    uint32_t blocos = 0;
    int i = 0;
    while(i < total) {
        uint16_t cor = pixels[i];
        int rep = 1;
        while(i + rep < total && pixels[i + rep] == cor && rep < 255) rep++;
        blocos++;
        i += rep;
    }
    return blocos;
}

YImg* yimg_carregar(const char *caminho) {
    FILE* a = es_abrir(caminho, "rb");
    if(!a) return NULL;

    YImg *img = (YImg*)mem_alocar(sizeof(YImg));
    es_ler(&img->largura, 1, 1, a);
    es_ler(&img->altura,  1, 1, a);

    const int total = img->largura * img->altura;

    // le pixels crus pra um buffer temporario
    uint16_t* pixels = (uint16_t*)mem_alocar(total * sizeof(uint16_t));
    es_ler(pixels, sizeof(uint16_t), total, a);
    es_fechar(a);

    // decide se RLE compensa: cada bloco RLE ocupa 1 uint16_t(cor) + 1 byte (rep),
    // arredondado pra 2 bytes => 2 uint16_t por bloco(4 bytes)
    uint32_t blocos = yimg__contar_blocos_rle(pixels, total);
    uint32_t custo_rle = blocos * 2; // em uint16_t
    uint32_t custo_cru = total; // em uint16_t

    if(custo_rle < custo_cru) {
        img->formato = YIMG_RLE;
        img->dados_tam = (uint16_t)custo_rle;
        img->dados = (uint16_t*)mem_alocar(custo_rle * sizeof(uint16_t));

        uint16_t* l = img->dados;
        int i = 0;
        while(i < total) {
            uint16_t cor = pixels[i];
            int rep = 1;
            while(i + rep < total && pixels[i + rep] == cor && rep < 255) rep++;
            *l++ = cor;
            *l++ = (uint16_t)rep;
            i += rep;
        }
    } else {
        img->formato = YIMG_CRU;
        img->dados_tam = (uint16_t)total;
        img->dados = (uint16_t*)mem_alocar(total * sizeof(uint16_t));
        for(int i = 0; i < total; i++) {
            img->dados[i] = pixels[i];
        }
    }
    mem_liberar(pixels, total * sizeof(uint16_t));
    return img;
}

void yimg_render(Tela* t, YImg* img, int x, int y) {
    if(img->formato == YIMG_CRU) {
        for(int l = 0; l < img->altura; l++) {
            for(int c = 0; c < img->largura; c++) {
                const uint16_t cor = img->dados[l * img->largura + c];
                if(cor != YIMG_TRANSPARENTE) {
                    render_pixel(t, x + c, y + l, cor);
                }
            }
        }
    } else { // YIMG_RLE
        int l = 0, c = 0;
        for(uint16_t i = 0; i < img->dados_tam; i += 2) {
            uint16_t cor = img->dados[i];
            uint16_t rep = img->dados[i + 1];
            for(uint16_t k = 0; k < rep; k++) {
                if(cor != YIMG_TRANSPARENTE) {
                    render_pixel(t, x + c, y + l, cor);
                }
                c++;
                if(c >= img->largura) {
                    c = 0;
                    l++;
                }
            }
        }
    }
}

void yimg_liberar(YImg *img) {
    mem_liberar(img->dados, img->dados_tam * sizeof(uint16_t));
    mem_liberar(img, sizeof(YImg));
}
#endif