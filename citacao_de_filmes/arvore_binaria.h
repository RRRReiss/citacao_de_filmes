#ifndef BST_H
#define BST_H

#include "citacoes.h"

typedef struct NoArvoreBusca {
    EntradaRepositorio entrada;
    struct NoArvoreBusca *esq;
    struct NoArvoreBusca *dir;
} NoArvoreBusca;

void add_offset(EntradaRepositorio *entrada, long offset);
void insere_arvbus(NoArvoreBusca **raiz, char *palavra, int cont, long offset);
EntradaRepositorio *pesquisa_arvbus(NoArvoreBusca *raiz, char *palavra);
void destroi_arvbus(NoArvoreBusca *raiz);

#endif
