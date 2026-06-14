#include "logica/graficos/tela.h"
#include "logica/graficos/yimg.h"
#include "logica/controle.h"
#include "logica/config.h"

int main() {
    Tela* tela = tela_iniciar(240, 240);
    LOG("TESTE DE RENDERIZAÇÃO\n");
    
    YImg *palito = yimg_carregar("kit-ycaro/palito.yimg");
    
    int jogador_x = 100;
    int jogador_y = 100;
    int VELO = 2;
    int rodando = 1;
    // loop Principal
    while(rodando) {
        controle_att();
        if(EVENTO_GLOBAL == EVENTO_SAIDA) {
            rodando = 0;
        }
        // === LOGICA DO JOGO ===
        if(controle_ler(CONTROLE_DIREITA)) {
            jogador_x += VELO;
        }
        if(controle_ler(CONTROLE_ESQUERDA)) {
            jogador_x -= VELO;
        }
        if(controle_ler(CONTROLE_BAIXO)) {
            jogador_y += VELO;
        }
        if(controle_ler(CONTROLE_CIMA)) {
            jogador_y -= VELO;
        }
        // === RENDERIZAÇÃO ===
        // limpa o framebuffer com preto(0x0000)
        render_limpar(tela, 0);

        // desenha um "jogador"(retangulo vermelho, 0xF800)
        render_retangulo(tela, jogador_x, jogador_y, 50, 30, 0xF800);
        
        yimg_render(tela, palito, 10, 20);
        
        render_att(tela);
        render_esperar(16); // 60 fps
    }
    yimg_liberar(palito);
    render_liberar(tela);

    return 0;
}