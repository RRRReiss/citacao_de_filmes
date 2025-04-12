#ifndef AVL_H
#define AVL_H

#include "citacoes.h"

typedef struct NoAVL {
    EntradaRepositorio entrada;
    struct NoAVL *esq;
    struct NoAVL *dir;
    int altura;
} NoAVL;

void insere_avl(NoAVL **raiz, EntradaRepositorio entrada);
EntradaRepositorio *pesquisa_avl(NoAVL *raiz, const char *palavra);
void destroi_avl(NoAVL *raiz);

#endif
