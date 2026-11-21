#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "raylib.h"
#include "../include/LeitorMapas.h"

void liberarMapa(DadosMapa *dados) {
    if (dados == NULL || dados->terreno == NULL) {
        return;
    }
    for (int i = 0; i < MAPA_LINHAS; i++) {
        free(dados->terreno[i]);
    }
    free(dados->terreno);
    dados->terreno = NULL;
}

int carregarMapa(const char *caminhoArquivo, DadosMapa *dados) {
    if (dados == NULL) return 0;

    FILE *arquivo = fopen(caminhoArquivo, "r");
    if (arquivo == NULL) {
        return 0;
    }

    dados->terreno = NULL;
    dados->qtdZumbis = 0;
    dados->qtdKits = 0;
    dados->jogadorInicial.linha = -1;
    dados->jogadorInicial.coluna = -1;

    if (fscanf(arquivo, "%d", &dados->tempoLimite) != 1 || dados->tempoLimite <= 0) {
        fclose(arquivo);
        return 0;
    }

    int c;
    while ((c = fgetc(arquivo)) != '\n' && c != EOF);

    dados->terreno = (char **)malloc(MAPA_LINHAS * sizeof(char *));
    if (dados->terreno == NULL) {
        fclose(arquivo);
        return 0;
    }

    for (int i = 0; i < MAPA_LINHAS; i++) {
        dados->terreno[i] = (char *)malloc((MAPA_COLUNAS + 1) * sizeof(char));
        if (dados->terreno[i] == NULL) {
            for (int k = 0; k < i; k++) free(dados->terreno[k]);
            free(dados->terreno);
            dados->terreno = NULL;
            fclose(arquivo);
            return 0;
        }
    }

    char linhaBuffer[128];
    for (int i = 0; i < MAPA_LINHAS; i++) {
        if (fgets(linhaBuffer, sizeof(linhaBuffer), arquivo) == NULL) {
            liberarMapa(dados);
            fclose(arquivo);
            return 0;
        }

        linhaBuffer[strcspn(linhaBuffer, "\r\n")] = '\0';

        if ((int)strlen(linhaBuffer) < MAPA_COLUNAS) {
            liberarMapa(dados);
            fclose(arquivo);
            return 0;
        }

        for (int j = 0; j < MAPA_COLUNAS; j++) {
            char ch = linhaBuffer[j];

            if (ch == 'P') {
                dados->jogadorInicial.linha = i;
                dados->jogadorInicial.coluna = j;
                dados->terreno[i][j] = ' ';
            } else if (ch == 'Z') {
                if (dados->qtdZumbis < MAX_ENTIDADES) {
                    dados->zumbis[dados->qtdZumbis].linha = i;
                    dados->zumbis[dados->qtdZumbis].coluna = j;
                    dados->qtdZumbis++;
                }
                dados->terreno[i][j] = ' ';
            } else if (ch == 'a' || ch == 'b' || ch == 'c') {
                if (dados->qtdKits < MAX_ENTIDADES) {
                    dados->kits[dados->qtdKits].pos.linha = i;
                    dados->kits[dados->qtdKits].pos.coluna = j;
                    dados->kits[dados->qtdKits].tipo = ch;
                    dados->kits[dados->qtdKits].coletado = 0;
                    dados->qtdKits++;
                }
                dados->terreno[i][j] = ' ';
            } else {
                dados->terreno[i][j] = ch;
            }
        }
        dados->terreno[i][MAPA_COLUNAS] = '\0';
    }

    fclose(arquivo);
    return 1;
}

void desenharMapa(const DadosMapa *dados, int offsetTopoY) {
    if (dados == NULL || dados->terreno == NULL) return;

    for (int i = 0; i < MAPA_LINHAS; i++) {
        for (int j = 0; j < MAPA_COLUNAS; j++) {
            int posX = j * TAMANHO_BLOCO;
            int posY = offsetTopoY + (i * TAMANHO_BLOCO);
            char celula = dados->terreno[i][j];

            // Fundo padrão (chão livre)
            DrawRectangle(posX, posY, TAMANHO_BLOCO, TAMANHO_BLOCO, RAYWHITE);
            DrawRectangleLines(posX, posY, TAMANHO_BLOCO, TAMANHO_BLOCO, LIGHTGRAY);

            if (celula == '#') {
                DrawRectangle(posX, posY, TAMANHO_BLOCO, TAMANHO_BLOCO, DARKGRAY);
            } else if (celula == 'A') {
                DrawRectangle(posX, posY, TAMANHO_BLOCO, TAMANHO_BLOCO, SKYBLUE);
                DrawText("A", posX + 12, posY + 10, 20, DARKBLUE);
            } else if (celula == 'B') {
                DrawRectangle(posX, posY, TAMANHO_BLOCO, TAMANHO_BLOCO, LIME);
                DrawText("B", posX + 12, posY + 10, 20, DARKGREEN);
            } else if (celula == 'C') {
                DrawRectangle(posX, posY, TAMANHO_BLOCO, TAMANHO_BLOCO, GOLD);
                DrawText("C", posX + 12, posY + 10, 20, ORANGE);
            } else if (celula == 'D') {
                DrawRectangle(posX, posY, TAMANHO_BLOCO, TAMANHO_BLOCO, BROWN);
                DrawText("D", posX + 12, posY + 10, 20, WHITE);
            } else if (celula == 'S') {
                DrawRectangle(posX, posY, TAMANHO_BLOCO, TAMANHO_BLOCO, PURPLE);
                DrawText("S", posX + 12, posY + 10, 20, WHITE);
            }
        }
    }
}
