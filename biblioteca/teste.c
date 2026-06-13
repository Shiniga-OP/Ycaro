#include "tela/renderizador.h"
#include "tela/tela.h"
#include "sistema/uart.h"

int main() {
    Tela* tela = tela_iniciar(240, 240);
    gravar("TESTE DE RENDERIZAÇÃO\n");

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
        // limpa o framebuffe com preto(0x0000)
        render_limpar(tela, 0);

        // desenha um "jogador"(retangulo vermelho, 0xF800)
        render_retangulo(tela, jogador_x, 100, 50, 30, 0xF800);
        
        render_att(tela);
        render_esperar(16); // 60 fps
    }
    render_liberar(tela);

    return 0;
}