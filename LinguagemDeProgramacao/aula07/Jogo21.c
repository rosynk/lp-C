#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void gerarCarta(int baralho[13][4], char *naipe[4], int *soma) {
    int numero, tipoNaipe;

    do {
        numero = rand() % 13;   
        tipoNaipe = rand() % 4; 
    } while (baralho[numero][tipoNaipe] == -1);  

    if (numero == 0) {
        printf("Carta: Ás de %s\n", naipe[tipoNaipe]);
        *soma += 1;  
    } else if (numero >= 10) {
        printf("Carta: %s de %s\n", (numero == 10 ? "Valete" : (numero == 11 ? "Rainha" : "Rei")), naipe[tipoNaipe]);
        *soma += 10;  
    } else {
        printf("Carta: %d de %s\n", numero + 1, naipe[tipoNaipe]);
        *soma += numero + 1;  
    }

    baralho[numero][tipoNaipe] = -1;
}

int main() {
    int baralho[13][4];  
    int somaJogador = 0, somaMaquina = 0;

    char resposta;
    char *naipe[4] = {"♥", "♦", "♣", "♠"};  

    for (int i = 0; i < 13; i++) {
        for (int j = 0; j < 4; j++) {
            baralho[i][j] = i;  
        }
    }

    printf("Vamos começar o jogo? (S/N) >> ");
    scanf(" %c", &resposta);

    if (resposta == 'N' || resposta == 'n') {
        printf("Ok, até a próxima!\n");
        return 0;
    }

    srand(time(NULL));  

    int cartasRestantes = 52;  

    do {
        gerarCarta(baralho, naipe, &somaJogador);  
        cartasRestantes--;  

        printf("Sua soma atual: %d\n", somaJogador);

        if (somaJogador > 21) {
            printf("Seu jogo acabou!\nVocê perdeu e a máquina ganhou!\n");
            return 0;
        }

        printf("Quer jogar de novo? (S/N)\n");
        scanf(" %c", &resposta);

        if (resposta == 'N' || resposta == 'n') {
            printf("\nMáquina jogando...\n");
            do {
                gerarCarta(baralho, naipe, &somaMaquina);  
                printf("Soma da máquina: %d\n", somaMaquina);
                if (somaMaquina > 21) {
                    printf("Parabéns!\nVocê ganhou e a máquina perdeu!\n");
                    return 0;
                }
            } while (somaMaquina <= 21 && somaMaquina <= somaJogador);  
        }

    } while (resposta != 'N' && resposta != 'n');

    printf("\nAté a próxima!\n");

    if (somaJogador > somaMaquina){
        printf("Você ganhou! Sua soma foi %d e a soma da máquina foi %d\n", somaJogador, somaMaquina);
    } else if (somaMaquina > somaJogador) {
      printf("Você perdeu! Sua soma foi %d e a soma da máquina foi %d\n", somaJogador, somaMaquina);
    }

    return 0;
}
