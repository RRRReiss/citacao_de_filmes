#include "busca_binaria.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int busca_binaria(EntradaRepositorio *entradas, int qtd_entradas, char *palavra) {
    int inf = 0, sup = qtd_entradas - 1, meio;
    while (inf <= sup) {
        meio = inf + (sup - inf) / 2; // Evita overflow para índices grandes
        int cmp = strcmp(entradas[meio].palavra, palavra);
        if (cmp == 0)
            return meio;
        else if (cmp > 0)
            sup = meio - 1;
        else // cmp < 0
            inf = meio + 1;
    }
    return -1; // Não encontrado
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

void insere_busbin(VetorBuscaBinaria *vetor, EntradaRepositorio entrada) {
    int pos = busca_binaria(vetor->entradas, vetor->tamanho, entrada.palavra);

    if (pos >= 0) { // Palavra já existe
        vetor->entradas[pos].frequencia += entrada.frequencia;
        // Lógica para adicionar offset (já existente e parece ok, mas verifica se offset já existe)
        int offset_existe = 0;
        for (int j = 0; j < vetor->entradas[pos].offset_cont; j++) {
            if (vetor->entradas[pos].offsets[j] == entrada.offsets[0]) {
                offset_existe = 1;
                break;
            }
        }
        if (!offset_existe) {
            vetor->entradas[pos].offsets = realloc(vetor->entradas[pos].offsets, (vetor->entradas[pos].offset_cont + 1) * sizeof(long));
            // Adicionar verificação de falha do realloc seria bom aqui
            vetor->entradas[pos].offsets[vetor->entradas[pos].offset_cont++] = entrada.offsets[0];
        }
        // Como a palavra já existe, podemos liberar a memória da 'entrada' que não será usada
         free(entrada.palavra);
         free(entrada.offsets);

    } else { // Palavra nova, precisa inserir em ordem
        int i = 0;
        // Encontra a posição correta para manter a ordem
        while (i < vetor->tamanho && strcmp(vetor->entradas[i].palavra, entrada.palavra) < 0) {
            i++;
        }

        EntradaRepositorio *temp = realloc(vetor->entradas, (vetor->tamanho + 1) * sizeof(EntradaRepositorio));
        if (temp == NULL) {
            perror("Erro ao realocar memoria para entradas no vetor");
            // Considerar uma forma menos drástica que exit(1) se possível
            exit(1);
        }
        vetor->entradas = temp;

        // Move os elementos para abrir espaço na posição 'i'
        memmove(&vetor->entradas[i + 1], &vetor->entradas[i], (vetor->tamanho - i) * sizeof(EntradaRepositorio));

        // Insere a nova entrada (cópia profunda)
        vetor->entradas[i].palavra = entrada.palavra; // Transfere a posse do ponteiro
        vetor->entradas[i].frequencia = entrada.frequencia;
        vetor->entradas[i].offsets = entrada.offsets; // Transfere a posse do ponteiro
        vetor->entradas[i].offset_cont = entrada.offset_cont;

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
