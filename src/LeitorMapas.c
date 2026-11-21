#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/LeitorMapas.h"

void liberarMapa(char **mapa) {
    if (mapa == NULL) {
        return;
    }
    for (int i = 0; i < MAPA_LINHAS; i++) {
        free(mapa[i]);
    }
    free(mapa);
}

char **carregarMapa(const char *caminhoArquivo, int *tempoLimite) {
    FILE *arquivo = fopen(caminhoArquivo, "r");
    if (arquivo == NULL) {
        return NULL;
    }

    // Lê o tempo limite na primeira linha do arquivo
    if (fscanf(arquivo, "%d", tempoLimite) != 1 || *tempoLimite <= 0) {
        fclose(arquivo);
        return NULL;
    }

    // Pula o restante da primeira linha até a quebra de linha
    int c;
    while ((c = fgetc(arquivo)) != '\n' && c != EOF);

    // Aloca dinamicamente as 20 linhas da matriz
    char **mapa = (char **)malloc(MAPA_LINHAS * sizeof(char *));
    if (mapa == NULL) {
        fclose(arquivo);
        return NULL;
    }

    for (int i = 0; i < MAPA_LINHAS; i++) {
        mapa[i] = (char *)malloc((MAPA_COLUNAS + 1) * sizeof(char));
        if (mapa[i] == NULL) {
            for (int k = 0; k < i; k++) {
                free(mapa[k]);
            }
            free(mapa);
            fclose(arquivo);
            return NULL;
        }
    }

    // Lê cada uma das 20 linhas preservando os espaços em branco
    char linhaBuffer[128];
    for (int i = 0; i < MAPA_LINHAS; i++) {
        if (fgets(linhaBuffer, sizeof(linhaBuffer), arquivo) == NULL) {
            liberarMapa(mapa);
            fclose(arquivo);
            return NULL;
        }

        // Remove os caracteres de quebra de linha (\r e \n)
        linhaBuffer[strcspn(linhaBuffer, "\r\n")] = '\0';

        // Garante que a linha tem os 40 caracteres exigidos
        if ((int)strlen(linhaBuffer) < MAPA_COLUNAS) {
            liberarMapa(mapa);
            fclose(arquivo);
            return NULL;
        }

        for (int j = 0; j < MAPA_COLUNAS; j++) {
            mapa[i][j] = linhaBuffer[j];
        }
        mapa[i][MAPA_COLUNAS] = '\0';
    }

    fclose(arquivo);
    return mapa;
}
