#include "arvore_avl.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// Funções auxiliares
int altura(NoAVL *no) { return (no) ? no->altura : 0; }
int max(int a, int b) { return (a > b) ? a : b; }

NoAVL* rotacao_direita(NoAVL *y) {
    NoAVL *x = y->esq;
    y->esq = x->dir;
    x->dir = y;
    
    y->altura = max(altura(y->esq), altura(y->dir)) + 1;
    x->altura = max(altura(x->esq), altura(x->dir)) + 1;
    return x;
}

NoAVL* rotacao_esquerda(NoAVL *x) {
    NoAVL *y = x->dir;
    x->dir = y->esq;
    y->esq = x;
    
    x->altura = max(altura(x->esq), altura(x->dir)) + 1;
    y->altura = max(altura(y->esq), altura(y->dir)) + 1;
    return y;
}

int balanceamento(NoAVL *no) {
    return (no) ? altura(no->esq) - altura(no->dir) : 0;
}

// Árvore alfabética
void insere_avl_alfabeto(NoAVL **raiz, EntradaRepositorio entrada) {
    if (!*raiz) {
        *raiz = malloc(sizeof(NoAVL));
        (*raiz)->entrada = entrada;
        (*raiz)->esq = (*raiz)->dir = NULL;
        (*raiz)->altura = 1;
        return;
    }

    int cmp = strcmp(entrada.palavra, (*raiz)->entrada.palavra);
    
    if (cmp < 0) insere_avl_alfabeto(&(*raiz)->esq, entrada);
    else if (cmp > 0) insere_avl_alfabeto(&(*raiz)->dir, entrada);
    else {
        // Atualiza frequência se palavra já existe
        (*raiz)->entrada.frequencia += entrada.frequencia;
        return;
    }

    (*raiz)->altura = 1 + max(altura((*raiz)->esq), altura((*raiz)->dir));
    int fb = balanceamento(*raiz);

    // Balanceamentos
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

// Árvore de frequência
void insere_avl_frequencia(NoAVL **raiz, EntradaRepositorio entrada) {
    if (!*raiz) {
        *raiz = malloc(sizeof(NoAVL));
        (*raiz)->entrada = entrada;
        (*raiz)->esq = (*raiz)->dir = NULL;
        (*raiz)->altura = 1;
        return;
    }

    if (entrada.frequencia < (*raiz)->entrada.frequencia)
        insere_avl_frequencia(&(*raiz)->esq, entrada);
    else
        insere_avl_frequencia(&(*raiz)->dir, entrada);

    (*raiz)->altura = 1 + max(altura((*raiz)->esq), altura((*raiz)->dir));
    int fb = balanceamento(*raiz);

    if (fb > 1 && entrada.frequencia < (*raiz)->esq->entrada.frequencia)
        *raiz = rotacao_direita(*raiz);
    else if (fb < -1 && entrada.frequencia > (*raiz)->dir->entrada.frequencia)
        *raiz = rotacao_esquerda(*raiz);
    else if (fb > 1 && entrada.frequencia > (*raiz)->esq->entrada.frequencia) {
        (*raiz)->esq = rotacao_esquerda((*raiz)->esq);
        *raiz = rotacao_direita(*raiz);
    }
    else if (fb < -1 && entrada.frequencia < (*raiz)->dir->entrada.frequencia) {
        (*raiz)->dir = rotacao_direita((*raiz)->dir);
        *raiz = rotacao_esquerda(*raiz);
    }
}

// Funções de pesquisa
EntradaRepositorio *pesquisa_avl_alfabeto(NoAVL *raiz, const char *palavra) {
    if (!raiz) return NULL;
    
    int cmp = strcmp(palavra, raiz->entrada.palavra);
    if (cmp == 0) return &raiz->entrada;
    return pesquisa_avl_alfabeto((cmp < 0) ? raiz->esq : raiz->dir, palavra);
}

// Função de destruição
void destroi_avl(NoAVL *raiz) {
    if (raiz) {
        destroi_avl(raiz->esq);
        destroi_avl(raiz->dir);
        free(raiz->entrada.palavra);
        free(raiz->entrada.offsets);
        free(raiz);
    }
}

// Percurso para frequência
void em_ordem_frequencia(NoAVL *raiz) {
    if (raiz) {
        em_ordem_frequencia(raiz->dir); // Ordem decrescente
        printf("%-20s %d ocorrencias\n", raiz->entrada.palavra, raiz->entrada.frequencia);
        em_ordem_frequencia(raiz->esq);
    }
}
