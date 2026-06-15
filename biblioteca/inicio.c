#include "ycaro1.h"

__attribute__((section(".ycaro")))
Ycaro g_tabela = {
    .tela_iniciar = tela_iniciar,
    .render_pixel = render_pixel,
    .render_retangulo = render_retangulo,
    .render_limpar = render_limpar,
    .render_att = render_att,
    .render_esperar = render_esperar,
    .render_liberar = render_liberar,
    .controle_ler = controle_ler,
    .controle_def_estado = controle_def_estado,
    .yimg_carregar = yimg_carregar,
    .yimg_render = yimg_render,
    .yimg_liberar = yimg_liberar,
    .def_evento_global = def_evento_global,
    .obter_evento_global = obter_evento_global,
    .cartucho_carregar = cartucho_carregar
};

int main() {
    cartucho_carregar("teste.bin", &g_tabela);
    return 0;
}