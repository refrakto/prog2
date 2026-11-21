#ifndef LEITOR_MAPAS_H
#define LEITOR_MAPAS_H

#define MAPA_LINHAS 20
#define MAPA_COLUNAS 40
#define TAMANHO_BLOCO 40
#define MAX_ENTIDADES 100

typedef struct {
    int linha;
    int coluna;
} Posicao;

typedef struct {
    Posicao pos;
    char tipo; // 'a', 'b' ou 'c'
    int coletado;
} KitMapa;

typedef struct {
    char **terreno;
    int tempoLimite;
    Posicao jogadorInicial;
    Posicao saida;
    Posicao zumbis[MAX_ENTIDADES];
    int qtdZumbis;
    KitMapa kits[MAX_ENTIDADES];
    int qtdKits;
    int portoesAbertos;
} DadosMapa;

// Tenta abrir "mapaX.txt" na raiz; se não achar, tenta "include/mapas/mapaX.txt".
// Retorna 1 se carregou com sucesso, 0 se não encontrou ou deu erro.
int carregarFase(int numeroFase, DadosMapa *dados);

// Verifica se o jogador ou zumbi pode pisar naquela casa (1 = livre, 0 = bloqueado).
int ehAndavel(const DadosMapa *dados, int linha, int coluna);

// Alterna os portões 'D' entre fechados (0) e abertos (1).
void alternarPortoes(DadosMapa *dados);

// Desenha o mapa 20x40 na janela Raylib (cada bloco 40x40px).
void desenharMapa(const DadosMapa *dados, int offsetTopoY);

// Libera a memória alocada para o terreno do mapa.
void liberarMapa(DadosMapa *dados);

#endif
