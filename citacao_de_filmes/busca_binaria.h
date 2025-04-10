#ifndef BS_ARRAY_H
#define BS_ARRAY_H

#include "citacoes.h"

typedef struct VetorBuscaBinaria{
    EntradaRepositorio *entradas;
    int tamanho;
} VetorBuscaBinaria;

void inicializa_busbin(VetorBuscaBinaria *vetor);
void destroi_busbin(VetorBuscaBinaria *vetor);
void insere_busbin(VetorBuscaBinaria *vetor, const char *palavra, int cont, long offset);
EntradaRepositorio *pesquisa_busbin(VetorBuscaBinaria *vetor, const char *palavra);

#endif
