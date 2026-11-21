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
    Posicao zumbis[MAX_ENTIDADES];
    int qtdZumbis;
    KitMapa kits[MAX_ENTIDADES];
    int qtdKits;
} DadosMapa;

// Carrega o mapa, separa as entidades do terreno e preenche DadosMapa.
int carregarMapa(const char *caminhoArquivo, DadosMapa *dados);

// Desenha o mapa 20x40 na janela Raylib (cada bloco 40x40px).
void desenharMapa(const DadosMapa *dados, int offsetTopoY);

// Libera a memória alocada para o terreno do mapa.
void liberarMapa(DadosMapa *dados);

#endif
