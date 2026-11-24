#include <stdio.h>
#include "raylib.h"
#include "../include/LeitorMapas.h"

int main(void) {
    int faseAtual = 1;
    int jogoZerado = 0;
    DadosMapa mapa;

    if (!carregarFase(faseAtual, &mapa)) {
        printf("Erro critico: mapa1.txt nao encontrado ou invalido!\n");
        return 1;
    }

    InitWindow(1600, 880, "Projeto Prog2 - Teste das 3 Fases");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        // Aperte N para testar a troca automatica de fase (1 -> 2 -> 3 -> Vitoria)
        if (!jogoZerado && IsKeyPressed(KEY_N)) {
            liberarMapa(&mapa);
            faseAtual++;
            if (!carregarFase(faseAtual, &mapa)) {
                jogoZerado = 1;
            }
        }

        // Aperte P para testar abrir/fechar portoes D
        if (!jogoZerado && IsKeyPressed(KEY_P)) {
            alternarPortoes(&mapa);
        }

        BeginDrawing();
        ClearBackground(BLACK);

        if (jogoZerado) {
            DrawText("PARABENS! TODAS AS FASES FORAM CONCLUIDAS!", 340, 400, 35, GREEN);
            DrawText("Pressione ESC para sair", 620, 460, 22, LIGHTGRAY);
        } else {
            DrawText(TextFormat("Fase: %d | Tempo: %ds | Zumbis: %d | Kits: %d  [N: Prox Fase | P: Portoes]",
                                faseAtual, mapa.tempoLimite, mapa.qtdZumbis, mapa.qtdKits),
                     20, 25, 22, WHITE);

            desenharMapa(&mapa, 80);
        }

        EndDrawing();
    }

    CloseWindow();
    if (!jogoZerado) {
        liberarMapa(&mapa);
    }
    return 0;
}
