#include <stdio.h>

int lerMapas(char *nomeMapa, char **mapa, int *tempo, int linhas, int colunas) {
    // Implementação da função para ler mapas do arquivo
    FILE *arquivo = fopen(nomeMapa, "r+");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 0;
    }

    fscanf(arquivo, "%d", tempo);
    mapa = (char **)malloc(linhas * sizeof(char *));
    ferror(a);
    for(int i = 0; i < linhas; i++) {
        *(mapa + i) = (char *)malloc(colunas * sizeof(char));
    }

    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            fscanf(arquivo, " %c", &mapa[i][j]);
        }
    }


    return 1;
}