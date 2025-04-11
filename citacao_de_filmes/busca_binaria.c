#include "busca_binaria.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int busca_binaria(EntradaRepositorio *entradas, int qtd_entradas, char *palavra){
    int inf = 0, sup = qtd_entradas-1, meio;
    while(inf <= sup){
        meio = (inf+sup)/2;
        if(strcmp(entradas[meio].palavra, palavra) == 0)
            return meio;
        else if(strcmp(entradas[meio].palavra, palavra) > 0)
            sup = meio-1;
        else
            inf = meio+1;
    }
    return -1;
}

void inicializa_busbin(VetorBuscaBinaria *vetor){
    vetor->entradas = NULL;
    vetor->tamanho = 0;
}

void destroi_busbin(VetorBuscaBinaria *vetor){
    for(int i = 0; i < vetor->tamanho; i++){
        free(vetor->entradas[i].palavra);
        free(vetor->entradas[i].offsets);
    }
    free(vetor->entradas);
    vetor->entradas = NULL;
    vetor->tamanho = 0;
}

void insere_busbin(VetorBuscaBinaria *vetor, char *palavra, int cont, long offset){
    int pos = busca_binaria(vetor->entradas, vetor->tamanho, palavra);
    EntradaRepositorio nova_entrada;
    if(pos < vetor->tamanho && strcmp(vetor->entradas[pos].palavra, palavra) == 0){
        vetor->entradas[pos].frequencia += cont;
        for(int i = 0; i < vetor->entradas[pos].offset_cont; i++){
            if(vetor->entradas[pos].offsets[i] == offset)
                return;
        }
        vetor->entradas[pos].offsets = realloc(vetor->entradas[pos].offsets, (vetor->entradas[pos].offset_cont + 1)*sizeof(long));
        vetor->entradas[pos].offsets[vetor->entradas[pos].offset_cont++] = offset;
    }
    else {
        strcpy(nova_entrada.palavra, palavra);
        nova_entrada.frequencia = cont;
        nova_entrada.offsets = (long*)malloc(sizeof(long));
        nova_entrada.offset_cont = 1;
        nova_entrada.offsets[0] = offset;
        vetor->entradas = realloc(vetor->entradas, (vetor->tamanho+1)*sizeof(EntradaRepositorio));
        memmove(&vetor->entradas[pos+1], &vetor->entradas[pos], (vetor->tamanho - pos)*sizeof(EntradaRepositorio));
        vetor->entradas[pos] = nova_entrada;
        vetor->tamanho++;
    }
}

EntradaRepositorio *pesquisa_busbin(VetorBuscaBinaria *vetor, char *palavra){
    int pos = busca_binaria(vetor->entradas, vetor->tamanho, palavra);
    if(pos < vetor->tamanho && strcmp(vetor->entradas[pos].palavra, palavra) == 0){
        return &vetor->entradas[pos];
    }
    return NULL;
}
