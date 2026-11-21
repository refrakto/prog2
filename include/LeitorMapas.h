#ifndef LEITOR_MAPAS_H
#define LEITOR_MAPAS_H

#define MAPA_LINHAS 20
#define MAPA_COLUNAS 40

typedef struct {
    int linha;
    int coluna;
} Posicao;

// Carrega o mapa a partir de um arquivo texto e guarda o tempo limite.
// Retorna NULL se o arquivo não existir ou der erro.
char **carregarMapa(const char *caminhoArquivo, int *tempoLimite);

// Libera a memória alocada para a matriz do mapa.
void liberarMapa(char **mapa);

#endif
