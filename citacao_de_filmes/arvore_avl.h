#ifndef ARVORE_AVL_H
#define ARVORE_AVL_H

#include "citacoes.h"

typedef struct NoAVL {
    EntradaRepositorio entrada;
    struct NoAVL *esq;
    struct NoAVL *dir;
    int altura;
} NoAVL;

void insere_avl(NoAVL **raiz, EntradaRepositorio entrada);
EntradaRepositorio *pesquisa_avl(NoAVL *raiz, const char *palavra);
void em_ordem_avl(NoAVL *raiz);
void destroi_avl(NoAVL *raiz);

#endif
