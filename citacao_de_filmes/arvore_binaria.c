#include "arvore_binaria.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void add_offset(EntradaRepositorio *entrada, long offset) {
    for(int i = 0; i < entrada->offset_cont; i++) {
        if(entrada->offsets[i] == offset)
            return;
    }
    entrada->offsets = realloc(entrada->offsets, (entrada->offset_cont + 1)*sizeof(long));
    entrada->offsets[entrada->offset_cont++] = offset;
}

void insere_arvbus(NoArvoreBusca **raiz, char *palavra, int cont, long offset){
    NoArvoreBusca *novo_no;
    if(*raiz == NULL){
        novo_no = (NoArvoreBusca*)malloc(sizeof(NoArvoreBusca));
        strcpy(novo_no->entrada.palavra, palavra);
        novo_no->entrada.frequencia = cont;
        novo_no->entrada.offsets = (long*)malloc(sizeof(long));
        novo_no->entrada.offsets[0] = offset;
        novo_no->entrada.offset_cont = 1;
        novo_no->esq = NULL;
        novo_no->dir = NULL;
        *raiz = novo_no;
        return;
    }
    if(strcmp(palavra, (*raiz)->entrada.palavra) < 0)
        insere_arvbus(&(*raiz)->esq, palavra, cont, offset);
    else if(strcmp(palavra, (*raiz)->entrada.palavra) > 0)
        insere_arvbus(&(*raiz)->dir, palavra, cont, offset);
    else{
        (*raiz)->entrada.frequencia += cont;
        add_offset(&(*raiz)->entrada, offset);
    }
}

EntradaRepositorio *pesquisa_arvbus(NoArvoreBusca *raiz, char *palavra){
    if(raiz == NULL)
        return NULL;
    if(strcmp(palavra, raiz->entrada.palavra) < 0)
        return pesquisa_arvbus(raiz->esq, palavra);
    else if(strcmp(palavra, raiz->entrada.palavra) > 0)
        return pesquisa_arvbus(raiz->dir, palavra);
    else
        return &raiz->entrada;
}

void destroi_arvbus(NoArvoreBusca *raiz){
    if(raiz == NULL)
        return;
    destroi_arvbus(raiz->esq);
    destroi_arvbus(raiz->dir);
    free(raiz->entrada.palavra);
    free(raiz->entrada.offsets);
    free(raiz);
}
