#ifndef BST_H
#define BST_H

#include "citacoes.h"

// nó da árvore binária de busca
typedef struct NoArvoreBusca {
    EntradaRepositorio entrada;
    struct NoArvoreBusca *esq;
    struct NoArvoreBusca *dir;
} NoArvoreBusca;

// adiciona um offset a entrada (sem repetir)
void add_offset_arvbus(EntradaRepositorio *entrada, long offset);

// insere uma palavra na árvore
void insere_arvbus(NoArvoreBusca **raiz, EntradaRepositorio entrada);

// busca uma palavra na árvore
EntradaRepositorio *pesquisa_arvbus(NoArvoreBusca *raiz, char *palavra);

// libera a memória da árvore
void destroi_arvbus(NoArvoreBusca *raiz);

#endif
