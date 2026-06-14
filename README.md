# Ycaro

## Sobre:
Ycaro é um console projetado para ser durável, de baixo consumo de energia, e de custo acessível para o consumidor final e desenvolvedores de jogos.

## Ycaro v1.0
Este modelo protótipo é um console para jogos 16-bit com cartuchos MicroSD de limite de código binário 4 MBs de Flash.

## Especificações técnicas:
1. ESP32 comum.
2. Memória RAM de 520 KBs.
3. sistema operacional/bootloader.
4. Tela 1.3 polegadas de 240x240 pixels.
5. Conector de alimentação e transferência de dados USB-C.
6. Slot de MicroSD.
7. Alimentação 5V.
8. Linguagem principal como C.
9. Saída de áudio amplificador I2S interface DaC, alta qualidade sonóra.

## Ycaro v1.1
O mesmo do anterior, mas com suporte a pilhas para se tornar um portátil.

## Recomendação:
Recomendado 3 pilhas de 1,5V. Para durabilidade, considere recarregáveis AA de Lítio (Li-ion).

## Biblioteca básica:
* Biblioteca básica de abstração para desenvolvimento acelerado via IDE/Terminal, camada SDL2 e limite de 520 KBs de RAM para simular o ambiente de desenvolvimento ESP32 padrão. Além disso, envolvendo o carregamento de imagens YIMG (.yimg) e compressão RLE em tempo de carregamento.
* Ferramenta de conversão PNG -> YIMG em biblioteca/kit-ycaro.
* Uso:
```Bash
./yimg sprite.png sprite.yimg
```