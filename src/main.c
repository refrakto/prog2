#include "LeitorMapas.c"

int main(){
    char nomeMapa[] = "../include/mapas/mapa1.txt";
    char **mapa;
    int tempo; //Iniciializa a variável tempo para armazenar o tempo lido do arquivo na função lerMapas
    int linhas = 20, colunas = 40;
    if(!lerMapas(nomeMapa, mapa, &tempo, linhas, colunas)){
        return -1;
    }
    return 0;
}