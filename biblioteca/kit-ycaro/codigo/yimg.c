#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define STB_IMAGE_IMPLEMENTATION
#include "../stb_image.h"

int main(int argc, char *argv[]) {
    if(argc < 3) {
        fprintf(stderr, "Uso: conv <entrada.png> <saida.yimg>\n");
        return 1;
    }
    int l, a, canais;
    uint8_t *dados = stbi_load(argv[1], &l, &a, &canais, 3); // força RGB
    if(!dados) {
        fprintf(stderr, "Erro ao abrir: %s\n", argv[1]);
        return 1;
    }
    if(l > 255 || a > 255) {
        fprintf(stderr, "Imagem maior que 255x255!\n");
        stbi_image_free(dados);
        return 1;
    }
    FILE *saida = fopen(argv[2], "wb");
    if(!saida) {
        fprintf(stderr, "Erro ao criar: %s\n", argv[2]);
        stbi_image_free(dados);
        return 1;
    }
    uint8_t leitor[2] = { (uint8_t)l, (uint8_t)a };
    fwrite(leitor, 1, 2, saida);

    for(int i = 0; i < l * a; i++) {
        uint8_t r = dados[i * 3 + 0];
        uint8_t g = dados[i * 3 + 1];
        uint8_t b = dados[i * 3 + 2];
        uint16_t rgb565 = ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
        fwrite(&rgb565, sizeof(uint16_t), 1, saida);
    }
    fclose(saida);
    stbi_image_free(dados);
    printf("Convertido: %dx%d -> %s\n", l, a, argv[2]);
    return 0;
}