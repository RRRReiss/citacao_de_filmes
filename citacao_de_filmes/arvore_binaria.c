#include "arvore_binaria.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// adiciona um novo offset na lista de offsets, evitando duplicações
void add_offset_arvbus(EntradaRepositorio *entrada, long offset) {
    for(int i = 0; i < entrada->offset_cont; i++) {
        if(entrada->offsets[i] == offset)
            return;
    }
    entrada->offsets = realloc(entrada->offsets, (entrada->offset_cont + 1)*sizeof(long));
    entrada->offsets[entrada->offset_cont++] = offset;
}

// insere uma nova palavra na árvore binária de busca (alfabética)
// se a palavra já existir, apenas atualiza a frequência e os offsets
void insere_arvbus(NoArvoreBusca **raiz, EntradaRepositorio entrada){
    NoArvoreBusca *novo_no;
    if(*raiz == NULL){
        novo_no = (NoArvoreBusca*)malloc(sizeof(NoArvoreBusca));
        novo_no->entrada.palavra = strdup(entrada.palavra);
        novo_no->entrada.frequencia = entrada.frequencia;
        novo_no->entrada.offsets = malloc(sizeof(long));
        novo_no->entrada.offsets[0] = entrada.offsets[0];
        novo_no->entrada.offset_cont = entrada.offset_cont;
        novo_no->esq = NULL;
        novo_no->dir = NULL;
        *raiz = novo_no;
        return;
    }
    if(strcmp(entrada.palavra, (*raiz)->entrada.palavra) < 0)
        insere_arvbus(&(*raiz)->esq, entrada);
    else if(strcmp(entrada.palavra, (*raiz)->entrada.palavra) > 0)
        insere_arvbus(&(*raiz)->dir, entrada);
    else{
        (*raiz)->entrada.frequencia += entrada.frequencia;
        add_offset_arvbus(&(*raiz)->entrada, entrada.offsets[0]);
    }
}

// busca uma palavra na árvore binária de busca
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

// libera toda a memória alocada pela árvore binária
void destroi_arvbus(NoArvoreBusca *raiz){
    if(raiz == NULL)
        return;
    destroi_arvbus(raiz->esq);
    destroi_arvbus(raiz->dir);
    free(raiz->entrada.palavra);
    free(raiz->entrada.offsets);
    free(raiz);
}
