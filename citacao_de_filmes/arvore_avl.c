#include "arvore_avl.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int altura(NoAVL *no) {
    return (no == NULL) ? 0 : no->altura;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

NoAVL *rotacao_direita(NoAVL *y) {
    NoAVL *x = y->esq;
    NoAVL *T2 = x->dir;
    x->dir = y;
    y->esq = T2;
    y->altura = max(altura(y->esq), altura(y->dir)) + 1;
    x->altura = max(altura(x->esq), altura(x->dir)) + 1;
    return x;
}

NoAVL *rotacao_esquerda(NoAVL *x) {
    NoAVL *y = x->dir;
    NoAVL *T2 = y->esq;
    y->esq = x;
    x->dir = T2;
    x->altura = max(altura(x->esq), altura(x->dir)) + 1;
    y->altura = max(altura(y->esq), altura(y->dir)) + 1;
    return y;
}

int balanceamento(NoAVL *no) {
    return (no == NULL) ? 0 : altura(no->esq) - altura(no->dir);
}

void insere_avl(NoAVL **raiz, EntradaRepositorio entrada) {
    if (*raiz == NULL) {
        *raiz = malloc(sizeof(NoAVL));
        (*raiz)->entrada = entrada;
        (*raiz)->esq = (*raiz)->dir = NULL;
        (*raiz)->altura = 1;
        return;
    }

    if (entrada.frequencia < (*raiz)->entrada.frequencia) {
        insere_avl(&(*raiz)->esq, entrada);
    } else {
        insere_avl(&(*raiz)->dir, entrada);
    }

    (*raiz)->altura = 1 + max(altura((*raiz)->esq), altura((*raiz)->dir));
    int fb = balanceamento(*raiz);

    if (fb > 1 && entrada.frequencia < (*raiz)->esq->entrada.frequencia)
        *raiz = rotacao_direita(*raiz);
    else if (fb < -1 && entrada.frequencia > (*raiz)->dir->entrada.frequencia)
        *raiz = rotacao_esquerda(*raiz);
    else if (fb > 1 && entrada.frequencia > (*raiz)->esq->entrada.frequencia) {
        (*raiz)->esq = rotacao_esquerda((*raiz)->esq);
        *raiz = rotacao_direita(*raiz);
    } else if (fb < -1 && entrada.frequencia < (*raiz)->dir->entrada.frequencia) {
        (*raiz)->dir = rotacao_direita((*raiz)->dir);
        *raiz = rotacao_esquerda(*raiz);
    }
}

void em_ordem_avl(NoAVL *raiz) {
    if (raiz != NULL) {
        em_ordem_avl(raiz->esq);
        printf("%s - %d ocorrencias\n", raiz->entrada.palavra, raiz->entrada.frequencia);
        em_ordem_avl(raiz->dir);
    }
}

void destroi_avl(NoAVL *raiz) {
    if (raiz != NULL) {
        destroi_avl(raiz->esq);
        destroi_avl(raiz->dir);
        free(raiz);
    }
}
