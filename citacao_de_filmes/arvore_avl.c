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

EntradaRepositorio *pesquisa_avl(NoAVL *raiz, const char *palavra) {
    if (raiz == NULL) return NULL;
    int cmp = strcmp(palavra, raiz->entrada.palavra);
    if (cmp == 0)
        return &raiz->entrada;
    else if (cmp < 0)
        return pesquisa_avl(raiz->esq, palavra);
    else
        return pesquisa_avl(raiz->dir, palavra);
}

void insere_avl(NoAVL **raiz, EntradaRepositorio entrada) {
    if (*raiz == NULL) {
        *raiz = malloc(sizeof(NoAVL));
        (*raiz)->entrada.palavra = strdup(entrada.palavra);
        (*raiz)->entrada.frequencia = entrada.frequencia;
        (*raiz)->entrada.offsets = malloc(sizeof(long));
        (*raiz)->entrada.offsets[0] = entrada.offsets[0];
        (*raiz)->entrada.offset_cont = 1;
        (*raiz)->esq = (*raiz)->dir = NULL;
        (*raiz)->altura = 1;
        return;
    }

    int cmp = strcmp(entrada.palavra, (*raiz)->entrada.palavra);

    if (cmp == 0) {
        (*raiz)->entrada.frequencia += entrada.frequencia;

        int existe = 0;
        for (int i = 0; i < (*raiz)->entrada.offset_cont; i++) {
            if ((*raiz)->entrada.offsets[i] == entrada.offsets[0]) {
                existe = 1;
                break;
            }
        }

        if (!existe) {
            (*raiz)->entrada.offsets = realloc(
                (*raiz)->entrada.offsets,
                ((*raiz)->entrada.offset_cont + 1) * sizeof(long)
            );
            (*raiz)->entrada.offsets[(*raiz)->entrada.offset_cont++] = entrada.offsets[0];
        }

        return;
    } else if (cmp < 0) {
        insere_avl(&(*raiz)->esq, entrada);
    } else {
        insere_avl(&(*raiz)->dir, entrada);
    }

    (*raiz)->altura = 1 + max(altura((*raiz)->esq), altura((*raiz)->dir));

    int fb = balanceamento(*raiz);

    if (fb > 1 && strcmp(entrada.palavra, (*raiz)->esq->entrada.palavra) < 0)
        *raiz = rotacao_direita(*raiz);

    else if (fb < -1 && strcmp(entrada.palavra, (*raiz)->dir->entrada.palavra) > 0)
        *raiz = rotacao_esquerda(*raiz);

    else if (fb > 1 && strcmp(entrada.palavra, (*raiz)->esq->entrada.palavra) > 0) {
        (*raiz)->esq = rotacao_esquerda((*raiz)->esq);
        *raiz = rotacao_direita(*raiz);
    }

    else if (fb < -1 && strcmp(entrada.palavra, (*raiz)->dir->entrada.palavra) < 0) {
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
        free(raiz->entrada.palavra);
        free(raiz->entrada.offsets);
        free(raiz);
    }
}
