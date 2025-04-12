#include "processamento.h"
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

//remove caracteres não alfanuméricos e converte para minúsculo
void normaliza_palavra(char *palavra) {
    int i = 0, j = 0;
    while (palavra[i]) {
        if (isalnum(palavra[i])) {
            if (isdigit(palavra[i]))
                palavra[j++] = palavra[i];
            else
                palavra[j++] = tolower(palavra[i]);
        }
        i++;
    }
    palavra[j] = '\0';
}

//separa a linha do arquivo em citação, filme e ano
void analisa_linha(const char *linha, InfoCitacao *info) {
    char buffer[1024], *pbuffer;
    char citacao[500], filme[500], ano[24];
    strcpy(buffer, linha);

    pbuffer = strtok(buffer, "\"");
    strcpy(citacao, pbuffer);
    info->citacao = (char*)malloc((strlen(citacao)+1) * sizeof(char));
    strcpy(info->citacao, citacao);

    pbuffer = strtok(NULL, "\"");
    strcpy(filme, pbuffer);
    info->filme = (char*)malloc((strlen(filme)+1) * sizeof(char));
    strcpy(info->filme, filme);

    pbuffer = strtok(NULL, "\n");
    strcpy(ano, pbuffer);
    info->ano = (char*)malloc((strlen(ano)+1) * sizeof(char));
    strcpy(info->ano, ano);
}

//processa cada linha do arquivo e atualiza as 3 estruturas
void processa_arquivo(const char *nome_arquivo, VetorBuscaBinaria *vet_busbin, NoArvoreBusca **raiz_arvbus, NoAVL **raiz_avl) {
    char linha[1024];
    long offset;
    FILE *arquivo = fopen(nome_arquivo, "r");
    if (!arquivo) {
        perror("Erro ao abrir o arquivo.\n");
        return;
    }

    offset = ftell(arquivo);
    while (fgets(linha, sizeof(linha), arquivo)) {
        InfoCitacao info;
        analisa_linha(linha, &info);
        char *quote = info.citacao;
        char *token = strtok(quote, " ");

        while (token) {
            normaliza_palavra(token);
            if (strlen(token) > 3) {
                //vetor com busca binária
                insere_busbin(vet_busbin, token, 1, offset);

                //arvore binária de busca
                insere_arvbus(raiz_arvbus, token, 1, offset);

                //arvore AVL alfabética
                EntradaRepositorio entrada_avl;
                entrada_avl.palavra = strdup(token);
                entrada_avl.frequencia = 1;
                entrada_avl.offsets = malloc(sizeof(long));
                entrada_avl.offsets[0] = offset;
                entrada_avl.offset_cont = 1;

                insere_avl_alfabeto(raiz_avl, entrada_avl);
            }
            token = strtok(NULL, " ");
        }

        free(info.citacao);
        free(info.filme);
        free(info.ano);

        offset = ftell(arquivo);
    }

    fclose(arquivo);
}
