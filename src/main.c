#include <stdio.h>
#include "../include/LeitorMapas.h"

int main(void) {
    int faseAtual = 1;
    int tempoLimite = 0;
    char caminhoMapa[128];

    snprintf(caminhoMapa, sizeof(caminhoMapa), "include/mapas/mapa%d.txt", faseAtual);

    char **mapa = carregarMapa(caminhoMapa, &tempoLimite);
    if (mapa == NULL) {
        printf("Erro ao abrir ou ler o arquivo: %s\n", caminhoMapa);
        return 1;
    }

    printf("Mapa %d carregado com sucesso! Tempo: %d segundos.\n\n", faseAtual, tempoLimite);

    for (int i = 0; i < MAPA_LINHAS; i++) {
        printf("%s\n", mapa[i]);
    }

    liberarMapa(mapa);
    return 0;
}
