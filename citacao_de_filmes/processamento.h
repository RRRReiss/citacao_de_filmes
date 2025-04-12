#ifndef QUOTE_PROCESSING_H
#define QUOTE_PROCESSING_H

#include <stdio.h>
#include "arvore_avl.h"
#include "arvore_binaria.h"
#include "busca_binaria.h"
#include "citacoes.h"

// estrutura que armazena uma citacao com filme e ano
typedef struct InfoCitacao {
    char *citacao;
    char *filme;
    char *ano;
} InfoCitacao;

// remove caracteres nao alfanumericos e coloca tudo em minusculo
void normaliza_palavra(char *palavra);

// separa os campos da linha do arquivo e armazena em InfoCitacao
void analisa_linha(const char *linha, InfoCitacao *info);

// processa o arquivo e insere as palavras nas estruturas: vetor, arvore binaria e AVL
void processa_arquivo(const char *nome_arquivo, VetorBuscaBinaria *vet_busbin, NoArvoreBusca **no_arvbus, NoAVL **no_avl);

#endif
