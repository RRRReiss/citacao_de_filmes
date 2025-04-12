#include "busca_binaria.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// realiza busca binaria pela palavra e retorna a posicao ou -1 se nao encontrar
int busca_binaria(EntradaRepositorio *entradas, int qtd_entradas, char *palavra) {
    int inf = 0, sup = qtd_entradas - 1, meio;
    while (inf <= sup) {
        meio = inf + (sup - inf) / 2;
        int cmp = strcmp(entradas[meio].palavra, palavra);
        if (cmp == 0) return meio;
        else if (cmp > 0) sup = meio - 1;
        else inf = meio + 1;
    }
    return -1;
}

// inicializa o vetor de busca binaria
void inicializa_busbin(VetorBuscaBinaria *vetor){
    vetor->entradas = NULL;
    vetor->tamanho = 0;
}

// libera toda a memoria usada pelo vetor
void destroi_busbin(VetorBuscaBinaria *vetor){
    for(int i = 0; i < vetor->tamanho; i++){
        free(vetor->entradas[i].palavra);
        free(vetor->entradas[i].offsets);
    }
    free(vetor->entradas);
    vetor->entradas = NULL;
    vetor->tamanho = 0;
}

// insere palavra no vetor mantendo a ordenacao
void insere_busbin(VetorBuscaBinaria *vetor, EntradaRepositorio entrada) {
    int pos = busca_binaria(vetor->entradas, vetor->tamanho, entrada.palavra);

    if (pos >= 0) {
        vetor->entradas[pos].frequencia += entrada.frequencia;

        // evita duplicar o offset
        int offset_existe = 0;
        for (int j = 0; j < vetor->entradas[pos].offset_cont; j++) {
            if (vetor->entradas[pos].offsets[j] == entrada.offsets[0]) {
                offset_existe = 1;
                break;
            }
        }

        if (!offset_existe) {
            vetor->entradas[pos].offsets = realloc(vetor->entradas[pos].offsets,
                (vetor->entradas[pos].offset_cont + 1) * sizeof(long));
            vetor->entradas[pos].offsets[vetor->entradas[pos].offset_cont++] = entrada.offsets[0];
        }

        // libera a entrada recebida pois ja existe no vetor
        free(entrada.palavra);
        free(entrada.offsets);

    } else {
        // palavra nova, inserir ordenado
        int i = 0;
        while (i < vetor->tamanho && strcmp(vetor->entradas[i].palavra, entrada.palavra) < 0) {
            i++;
        }

        EntradaRepositorio *temp = realloc(vetor->entradas, (vetor->tamanho + 1) * sizeof(EntradaRepositorio));
        if (temp == NULL) {
            perror("erro ao realocar memoria");
            exit(1);
        }

        vetor->entradas = temp;
        memmove(&vetor->entradas[i + 1], &vetor->entradas[i], (vetor->tamanho - i) * sizeof(EntradaRepositorio));

        vetor->entradas[i].palavra = entrada.palavra;
        vetor->entradas[i].frequencia = entrada.frequencia;
        vetor->entradas[i].offsets = entrada.offsets;
        vetor->entradas[i].offset_cont = entrada.offset_cont;

        vetor->tamanho++;
    }
}

// retorna a entrada encontrada ou NULL
EntradaRepositorio *pesquisa_busbin(VetorBuscaBinaria *vetor, char *palavra){
    int pos = busca_binaria(vetor->entradas, vetor->tamanho, palavra);
    if (pos >= 0 && pos < vetor->tamanho && strcmp(vetor->entradas[pos].palavra, palavra) == 0) {
        return &vetor->entradas[pos];
    }
    return NULL;
}
