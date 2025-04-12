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

void analisa_linha(const char *linha, InfoCitacao *info) {
    char buffer[1024], *pbuffer;
    char citacao[500], filme[500];
    char ano[24];
    strcpy(buffer, linha);

    pbuffer = strtok(buffer, "\"");
    strcpy(citacao, pbuffer);
    info->citacao = (char*)malloc((strlen(citacao)+1)*sizeof(char));
    strcpy(info->citacao, citacao);

    pbuffer = strtok(NULL, "\"");
    strcpy(filme, pbuffer);
    info->filme = (char*)malloc((strlen(filme)+1)*sizeof(char));
    strcpy(info->filme, filme);

    pbuffer = strtok(NULL, "\n");
    strcpy(ano, pbuffer);
    info->ano = (char*)malloc((strlen(ano)+1)*sizeof(char));
    strcpy(info->ano, ano);
}

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
                EntradaRepositorio entrada;
                entrada.palavra = strdup(token);
                entrada.frequencia = 1;
                entrada.offsets = malloc(sizeof(long));
                entrada.offsets[0] = offset;
                entrada.offset_cont = 1;
                insere_busbin(vet_busbin, entrada);
                insere_arvbus(raiz_arvbus, entrada);
                *raiz_avl = insere_avl(raiz_avl, entrada);
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
