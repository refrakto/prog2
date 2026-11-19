#include <stdio.h>
#include <stdlib.h>

int lerMapas(char *nomeMapa, char **mapa, int *tempo) {
    // Implementação da função para ler mapas do arquivo
    FILE *arquivo = fopen(nomeMapa, "r+");
    
    int linhas=20, colunas=40;

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 0;
    }

    fscanf(arquivo, "%d", tempo);

    mapa = (char **)malloc(linhas * sizeof(char *));


    for(int i = 0; i < linhas; i++) {
        *(mapa + i) = (char *)malloc(colunas * sizeof(char));
    }
    if (mapa == NULL) {
        printf("Erro ao alocar memória para o mapa.\n");
        return 0;
    }

    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < colunas; j++) {
            mapa[i][j] = fgetc(arquivo);
        }
    }

    return 1;
}

void liberarMapa(char **mapa) {
    for (int i = 0; i < 20; i++) {
        free(mapa[i]);
    }
    free(mapa);
}
 