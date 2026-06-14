#include "logica/graficos/tela.h"
#include "logica/graficos/yimg.h"

#include "logica/config.h"
#include "sistema/video.h"

int main() {
    Tela* tela = tela_iniciar(240, 240);
    LOG("TESTE DE RENDERIZAÇÃO\n");
    
    YImg *palito = yimg_carregar("kit-ycaro/palito.yimg");
    
    int jogador_x = 100;
    int rodando = 1;
    // loop Principal
    while(rodando) {
        if(EVENTO_GLOBAL == EVENTO_SAIDA) {
            rodando = 0;
        }
        // --- LOGICA DO JOGO ---
        jogador_x += 1; // move o bloco para a direita
        if(jogador_x > tela->largura) jogador_x = -50;

        // --- RENDER NO FRAMEBUFFER ---
        // limpa o framebuffer com preto(0x0000)
        render_limpar(tela, 0);

        // desenha um "jogador"(retangulo vermelho, 0xF800)
        render_retangulo(tela, jogador_x, 100, 50, 30, 0xF800);
        
        yimg_render(tela, palito, 10, 20);
        
        render_att(tela);
        render_esperar(16); // 60 fps
    }
    yimg_liberar(palito);
    render_liberar(tela);

    return 0;
}