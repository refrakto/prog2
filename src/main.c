#include <stdio.h>
#include "raylib.h"
#include "../include/LeitorMapas.h"

int main(void) {
    int faseAtual = 1;
    char caminhoMapa[128];
    DadosMapa mapa;

    snprintf(caminhoMapa, sizeof(caminhoMapa), "include/mapas/mapa%d.txt", faseAtual);

    if (!carregarMapa(caminhoMapa, &mapa)) {
        printf("Erro ao carregar %s\n", caminhoMapa);
        return 1;
    }

    // Janela exigida: 1600x880 (80px no topo para placar + 800px para o mapa 20x40)
    InitWindow(1600, 880, "Projeto Prog2 - Teste de Mapa");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);

        // Barra superior (HUD provisória)
        DrawText(TextFormat("Fase: %d | Tempo: %ds | Zumbis: %d | Kits: %d",
                            faseAtual, mapa.tempoLimite, mapa.qtdZumbis, mapa.qtdKits),
                 20, 25, 25, WHITE);

        // Desenha o mapa começando no Y = 80
        desenharMapa(&mapa, 80);

        EndDrawing();
    }

    CloseWindow();
    liberarMapa(&mapa);
    return 0;
}
