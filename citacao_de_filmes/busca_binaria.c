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

void insere_busbin(VetorBuscaBinaria *vetor, EntradaRepositorio entrada){
    int pos = busca_binaria(vetor->entradas, vetor->tamanho, entrada.palavra);
    if(pos >= 0 && pos < vetor->tamanho && strcmp(vetor->entradas[pos].palavra, entrada.palavra) == 0){
        vetor->entradas[pos].frequencia += entrada.frequencia;
        for(int i = 0; i < entrada.offset_cont; i++){
            int j;
            for(j = 0; j < vetor->entradas[pos].offset_cont; j++){
                if(vetor->entradas[pos].offsets[j] == entrada.offsets[i])
                    break;
            }
            if(j == vetor->entradas[pos].offset_cont){
                vetor->entradas[pos].offsets = realloc(vetor->entradas[pos].offsets, (vetor->entradas[pos].offset_cont + 1)*sizeof(long));
                vetor->entradas[pos].offsets[vetor->entradas[pos].offset_cont++] = entrada.offsets[i];
            }
        }
    }
    else {
        EntradaRepositorio *temp = realloc(vetor->entradas, (vetor->tamanho + 1) * sizeof(EntradaRepositorio));
        if (temp == NULL) {
            fprintf(stderr, "Erro ao alocar memória para entradas.\n");
            exit(1);
        }
        vetor->entradas = temp;
        if(pos < 0) pos = vetor->tamanho;
        memmove(&vetor->entradas[pos+1], &vetor->entradas[pos], (vetor->tamanho - pos)*sizeof(EntradaRepositorio));
        vetor->entradas[pos] = entrada;
        vetor->tamanho++;
    }
}

EntradaRepositorio *pesquisa_busbin(VetorBuscaBinaria *vetor, char *palavra){
    int pos = busca_binaria(vetor->entradas, vetor->tamanho, palavra);
    if(pos >= 0 && pos < vetor->tamanho && strcmp(vetor->entradas[pos].palavra, palavra) == 0){
        return &vetor->entradas[pos];
    }
    return NULL;
}
