#ifndef BS_ARRAY_H
#define BS_ARRAY_H

#include "citacoes.h"

typedef struct VetorBuscaBinaria{
    EntradaRepositorio *entradas;
    int tamanho;
} VetorBuscaBinaria;

int busca_binaria(EntradaRepositorio *entradas, int qtd_entradas, char *palavra);
void inicializa_busbin(VetorBuscaBinaria *vetor);
void destroi_busbin(VetorBuscaBinaria *vetor);
void insere_busbin(VetorBuscaBinaria *vetor, EntradaRepositorio entrada);
EntradaRepositorio *pesquisa_busbin(VetorBuscaBinaria *vetor, char *palavra);

#endif
