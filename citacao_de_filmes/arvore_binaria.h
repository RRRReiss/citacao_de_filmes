#ifndef BST_H
#define BST_H

#include "citacoes.h"

typedef struct NoArvoreBusca {
    EntradaRepositorio entrada;
    struct NoArvoreBusca *esq;
    struct NoArvoreBusca *dir;
} NoArvoreBusca;

void insere_arvbus(NoArvoreBusca **raiz, const char *palavra, int cont, long offset);
EntradaRepositorio *pesquisa_arvbus(NoArvoreBusca *raiz, const char *palavra);
void destroi_arvbus(NoArvoreBusca *raiz);

#endif
