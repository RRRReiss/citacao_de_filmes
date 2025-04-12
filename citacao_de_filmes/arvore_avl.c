#include "arvore_avl.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

NoAVL* cria_no_avl(EntradaRepositorio entrada) {
    NoAVL *novo_no = (NoAVL*)malloc(sizeof(NoAVL));
    novo_no->entrada.palavra = strdup(entrada.palavra);
    novo_no->entrada.frequencia = entrada.frequencia;
    novo_no->entrada.offset_cont = entrada.offset_cont;
    novo_no->entrada.offsets = malloc(sizeof(long) * entrada.offset_cont);
    memcpy(novo_no->entrada.offsets, entrada.offsets, sizeof(long) * entrada.offset_cont);
    novo_no->altura = 1;
    novo_no->esq = NULL;
    novo_no->dir = NULL;
    return novo_no;
}

int altura(NoAVL *no) {
    return no ? no->altura : 0;
}

int fator_balanceamento(NoAVL *no) {
    return no ? altura(no->esq) - altura(no->dir) : 0;
}

NoAVL* rotacao_direita(NoAVL *y) {
    NoAVL *x = y->esq;
    NoAVL *T2 = x->dir;

    x->dir = y;
    y->esq = T2;

    y->altura = 1 + ((altura(y->esq) > altura(y->dir)) ? altura(y->esq) : altura(y->dir));
    x->altura = 1 + ((altura(x->esq) > altura(x->dir)) ? altura(x->esq) : altura(x->dir));

    return x;
}

NoAVL* rotacao_esquerda(NoAVL *x) {
    NoAVL *y = x->dir;
    NoAVL *T2 = y->esq;

    y->esq = x;
    x->dir = T2;

    x->altura = 1 + ((altura(x->esq) > altura(x->dir)) ? altura(x->esq) : altura(x->dir));
    y->altura = 1 + ((altura(y->esq) > altura(y->dir)) ? altura(y->esq) : altura(y->dir));

    return y;
}

void add_offset_avl(EntradaRepositorio *entrada, long offset) {
    for(int i = 0; i < entrada->offset_cont; i++) {
        if(entrada->offsets[i] == offset)
            return;
    }
    entrada->offsets = realloc(entrada->offsets, (entrada->offset_cont + 1)*sizeof(long));
    entrada->offsets[entrada->offset_cont++] = offset;
}

NoAVL* insere_avl(NoAVL **raiz, EntradaRepositorio entrada) {
    if (*raiz == NULL)
        return cria_no_avl(entrada);

    if (strcmp(entrada.palavra, (*raiz)->entrada.palavra) < 0)
        (*raiz)->esq = insere_avl(&(*raiz)->esq, entrada);
    else if (strcmp(entrada.palavra, (*raiz)->entrada.palavra) > 0)
        (*raiz)->dir = insere_avl(&(*raiz)->dir, entrada);
    else {
        (*raiz)->entrada.frequencia += entrada.frequencia;
        add_offset_avl(&(*raiz)->entrada, entrada.offsets[0]);
        return *raiz;
    }

    (*raiz)->altura = 1 + ((altura((*raiz)->esq) > altura((*raiz)->dir)) ? altura((*raiz)->esq) : altura((*raiz)->dir));

    int balanceamento = fator_balanceamento(*raiz);

    if (balanceamento > 1 && strcmp(entrada.palavra, (*raiz)->esq->entrada.palavra) < 0)
        return rotacao_direita(*raiz);

    if (balanceamento < -1 && strcmp(entrada.palavra, (*raiz)->dir->entrada.palavra) > 0)
        return rotacao_esquerda(*raiz);

    if (balanceamento > 1 && strcmp(entrada.palavra, (*raiz)->esq->entrada.palavra) > 0) {
        (*raiz)->esq = rotacao_esquerda((*raiz)->esq);
        return rotacao_direita(*raiz);
    }

    if (balanceamento < -1 && strcmp(entrada.palavra, (*raiz)->dir->entrada.palavra) < 0) {
        (*raiz)->dir = rotacao_direita((*raiz)->dir);
        return rotacao_esquerda(*raiz);
    }

    return *raiz;
}

EntradaRepositorio *pesquisa_avl_alfabeto(NoAVL *raiz, char *palavra) {
    if (raiz == NULL)
        return NULL;
    if (strcmp(palavra, raiz->entrada.palavra) < 0)
        return pesquisa_avl_alfabeto(raiz->esq, palavra);
    else if (strcmp(palavra, raiz->entrada.palavra) > 0)
        return pesquisa_avl_alfabeto(raiz->dir, palavra);
    else
        return &raiz->entrada;
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

void em_ordem_frequencia(NoAVL *no) {
    if (no) {
        em_ordem_frequencia(no->dir);
        printf("%s: %d\n", no->entrada.palavra, no->entrada.frequencia);
        em_ordem_frequencia(no->esq);
    }
}

NoAVL* insere_avl_frequencia(NoAVL **raiz, EntradaRepositorio entrada) {
    if (*raiz == NULL) {
        return cria_no_avl(entrada);
    }

    if (entrada.frequencia > (*raiz)->entrada.frequencia) {
        (*raiz)->esq = insere_avl_frequencia(&(*raiz)->esq, entrada);
    } else if (entrada.frequencia < (*raiz)->entrada.frequencia) {
        (*raiz)->dir = insere_avl_frequencia(&(*raiz)->dir, entrada);
    } else {
        int cmp = strcmp(entrada.palavra, (*raiz)->entrada.palavra);
        if (cmp < 0) {
            (*raiz)->esq = insere_avl_frequencia(&(*raiz)->esq, entrada);
        } else if (cmp > 0) {
            (*raiz)->dir = insere_avl_frequencia(&(*raiz)->dir, entrada);
        } else {
            free(entrada.palavra);
            free(entrada.offsets);
            return *raiz;
        }
    }

    (*raiz)->altura = 1 + ((altura((*raiz)->esq) > altura((*raiz)->dir)) ? altura((*raiz)->esq) : altura((*raiz)->dir));
    int balanceamento = fator_balanceamento(*raiz);

    if (balanceamento > 1 && fator_balanceamento((*raiz)->esq) >= 0)
        return rotacao_direita(*raiz);

    if (balanceamento > 1 && fator_balanceamento((*raiz)->esq) < 0) {
        (*raiz)->esq = rotacao_esquerda((*raiz)->esq);
        return rotacao_direita(*raiz);
    }

    if (balanceamento < -1 && fator_balanceamento((*raiz)->dir) <= 0)
        return rotacao_esquerda(*raiz);

    if (balanceamento < -1 && fator_balanceamento((*raiz)->dir) > 0) {
        (*raiz)->dir = rotacao_direita((*raiz)->dir);
        return rotacao_esquerda(*raiz);
    }

    return *raiz;
}
