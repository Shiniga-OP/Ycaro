#include "ycaro1.h"
#include "logica/colisao/objeto.h"

void entrada(void* ponteiro) {
    Ycaro* yc = (Ycaro*)ponteiro;
    Tela* tela = yc->tela_iniciar(240, 240);
    LOG("TESTE DE RENDERIZAÇÃO\n");
    
    YImg *palito = yc->yimg_carregar("kit-ycaro/palito.yimg");
    
    Objeto jogador = { 100, 100, 30, 50 };
    
    int VELO = 2;
    int rodando = 1;
    // loop Principal
    while(rodando) {
        yc->controle_att();
        if(yc->obter_evento_global() == EVENTO_SAIDA) {
            rodando = 0;
        }
        // === LOGICA DO JOGO ===
        if(yc->controle_ler(CONTROLE_DIREITA)) {
            jogador.x += VELO;
        }
        if(yc->controle_ler(CONTROLE_ESQUERDA)) {
            jogador.x -= VELO;
        }
        if(yc->controle_ler(CONTROLE_BAIXO)) {
            jogador.y += VELO;
        }
        if(yc->controle_ler(CONTROLE_CIMA)) {
            jogador.y -= VELO;
        }
        // === RENDERIZAÇÃO ===
        // limpa o framebuffer com preto(0x0000)
        yc->render_limpar(tela, 0);

        // desenha um "jogador"(retangulo vermelho, 0xF800)
        yc->render_retangulo(tela, jogador.x, jogador.y, jogador.largura, jogador.altura, 0xF800);
        
        yc->yimg_render(tela, palito, 10, 20);
        
        yc->render_att(tela);
        yc->render_esperar(16); // 60 fps
    }
    yc->yimg_liberar(palito);
    yc->render_liberar(tela);

    return 0;
}