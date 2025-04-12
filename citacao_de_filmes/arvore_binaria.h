#ifndef BST_H
#define BST_H

#include "citacoes.h"

typedef struct NoArvoreBusca {
    EntradaRepositorio entrada;
    struct NoArvoreBusca *esq;
    struct NoArvoreBusca *dir;
} NoArvoreBusca;

void add_offset_arvbus(EntradaRepositorio *entrada, long offset);
void insere_arvbus(NoArvoreBusca **raiz, EntradaRepositorio entrada);
EntradaRepositorio *pesquisa_arvbus(NoArvoreBusca *raiz, char *palavra);
void destroi_arvbus(NoArvoreBusca *raiz);

#endif
