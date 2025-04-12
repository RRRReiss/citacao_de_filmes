#ifndef ARVORE_AVL_H
#define ARVORE_AVL_H

#include "citacoes.h"

typedef struct NoAVL {
    EntradaRepositorio entrada;
    struct NoAVL *esq;
    struct NoAVL *dir;
    int altura;
} NoAVL;

NoAVL* cria_no_avl(EntradaRepositorio entrada);
int altura(NoAVL *no);
int fator_balanceamento(NoAVL *no);
NoAVL* rotacao_direita(NoAVL *y);
NoAVL* rotacao_esquerda(NoAVL *x);
NoAVL* insere_avl(NoAVL **raiz, EntradaRepositorio entrada);
EntradaRepositorio *pesquisa_avl_alfabeto(NoAVL *raiz, char *palavra);
void destroi_avl(NoAVL *raiz);
void em_ordem_frequencia(NoAVL *no);
void insere_avl_frequencia(NoAVL **raiz, EntradaRepositorio entrada);

#endif
