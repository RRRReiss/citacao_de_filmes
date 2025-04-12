#ifndef BS_ARRAY_H
#define BS_ARRAY_H

#include "citacoes.h"

// estrutura que representa um vetor de entradas ordenadas alfabeticamente
typedef struct VetorBuscaBinaria{
    EntradaRepositorio *entradas; // ponteiro para o vetor de entradas
    int tamanho; // quantidade de elementos no vetor
} VetorBuscaBinaria;

// realiza busca binaria em um vetor de entradas
int busca_binaria(EntradaRepositorio *entradas, int qtd_entradas, char *palavra);

// inicializa o vetor de busca binaria
void inicializa_busbin(VetorBuscaBinaria *vetor);

// libera toda a memoria usada pelo vetor
void destroi_busbin(VetorBuscaBinaria *vetor);

// insere uma entrada no vetor mantendo a ordem alfabetica
void insere_busbin(VetorBuscaBinaria *vetor, EntradaRepositorio entrada);

// busca uma palavra no vetor e retorna o ponteiro para a entrada, ou NULL se nao encontrar
EntradaRepositorio *pesquisa_busbin(VetorBuscaBinaria *vetor, char *palavra);

#endif
