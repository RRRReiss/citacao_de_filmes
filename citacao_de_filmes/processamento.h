#ifndef QUOTE_PROCESSING_H
#define QUOTE_PROCESSING_H

#include <stdio.h>
#include "arvore_avl.h"
#include "arvore_binaria.h"
#include "busca_binaria.h"
#include "citacoes.h"

typedef struct InfoCitacao{
    char *citacao;
    char *filme;
    char *ano;
} InfoCitacao;

void normaliza_palavra(char *palavra);
void analisa_linha(const char *linha, InfoCitacao *info);
void processa_arquivo(const char *nome_arquivo, VetorBuscaBinaria *vet_busbin, NoArvoreBusca **no_arvbus, NoAVL **no_avl);

#endif
