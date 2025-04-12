#ifndef ARVORE_AVL_H
#define ARVORE_AVL_H

#include "citacoes.h"

typedef struct NoAVL {
    EntradaRepositorio entrada;
    struct NoAVL *esq;
    struct NoAVL *dir;
    int altura;
} NoAVL;

// Para árvore alfabética
void insere_avl_alfabeto(NoAVL **raiz, EntradaRepositorio entrada);
EntradaRepositorio *pesquisa_avl_alfabeto(NoAVL *raiz, const char *palavra);

// Para árvore de frequência
void insere_avl_frequencia(NoAVL **raiz, EntradaRepositorio entrada);
void em_ordem_frequencia(NoAVL *raiz);

// Funções comuns
void destroi_avl(NoAVL *raiz);

#endif
