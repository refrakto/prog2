#include "leituraMapas/LeitorMapas.h"
#include <stdio.h>
#include <raylib.h>


int main(){
    char nomeMapa[] = "mapa1.txt";//Nome do arquivo de mapa a ser lido
    char **mapa;
    int tempo, numMapa = 2; //Número do mapa a ser lido e o tempo de jogo

    
    if(!lerMapas(nomeMapa, mapa, &tempo)){
        return -1;
    }

    sprintf(nomeMapa, "mapa%d.txt", numMapa);


    liberarMapa(mapa);
    return 0;
}