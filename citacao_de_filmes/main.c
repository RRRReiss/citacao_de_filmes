#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "processamento.h"
#include "busca_binaria.h"
#include "arvore_binaria.h"
#include "arvore_avl.h"

void mostrar_citacoes(const char *arquivo, EntradaRepositorio *entrada) {
    if (!entrada) {
        printf("Palavra não encontrada.\n");
        return;
    }

    printf("Frequência: %d\n", entrada->frequencia);

    FILE *fp = fopen(arquivo, "r");
    if (!fp) {
        perror("Erro ao abrir o arquivo para exibir citações");
        return;
    }

    char linha[1024];
    for (int i = 0; i < entrada->offset_cont; i++) {
        fseek(fp, entrada->offsets[i], SEEK_SET);
        fgets(linha, sizeof(linha), fp);
        InfoCitacao info;
        analisa_linha(linha, &info);
        printf("- \"%s\" (%s, %s)\n", info.citacao, info.filme, info.ano);
        free(info.citacao);
        free(info.filme);
        free(info.ano);
    }

    fclose(fp);
}

void buscar_palavra(const char *arquivo, const char *palavra, VetorBuscaBinaria *vet, NoArvoreBusca *raiz_bin, NoAVL *raiz_avl) {
    char normalizada[100];
    strcpy(normalizada, palavra);
    normaliza_palavra(normalizada);

    if (strlen(normalizada) <= 3) {
        printf("Palavra ignorada (menos de 4 letras).\n");
        return;
    }

    clock_t ini, fim;
    EntradaRepositorio *res;

    //vetor
    ini = clock();
    res = pesquisa_busbin(vet, normalizada);
    fim = clock();
    printf("\n🔍 Vetor (busca binária) [%.6f s]:\n", (double)(fim - ini)/CLOCKS_PER_SEC);
    mostrar_citacoes(arquivo, res);

    //arvore Binária
    ini = clock();
    res = pesquisa_arvbus(raiz_bin, normalizada);
    fim = clock();
    printf("\n🌳 Árvore Binária de Busca [%.6f s]:\n", (double)(fim - ini)/CLOCKS_PER_SEC);
    mostrar_citacoes(arquivo, res);

    //AVL
    ini = clock();
    res = pesquisa_avl_alfabeto(raiz_avl, normalizada);
    fim = clock();
    printf("\n🌲 Árvore AVL [%.6f s]:\n", (double)(fim - ini)/CLOCKS_PER_SEC);
    mostrar_citacoes(arquivo, res);
}

int main() {
    VetorBuscaBinaria vetor_bin;
    NoArvoreBusca *raiz_bin = NULL;
    NoAVL *raiz_avl = NULL;
    char arquivo[] = "movie_quotes.csv"; 

    int opcao;
    char palavra[100];
    int carregado = 0;

    do {
        printf("\n--- MENU ---\n");
        printf("1. Carregar e processar arquivo\n");
        printf("2. Buscar palavra\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar(); 

        switch(opcao) {
            case 1:
                inicializa_busbin(&vetor_bin);
                processa_arquivo(arquivo, &vetor_bin, &raiz_bin, &raiz_avl);
                printf("Arquivo carregado e estruturas preenchidas!\n");
                carregado = 1;
                break;

            case 2:
                if (!carregado) {
                    printf("⚠ Primeiro carregue o arquivo!\n");
                    break;
                }
                printf("Digite a palavra a buscar: ");
                scanf("%s", palavra);
                buscar_palavra(arquivo, palavra, &vetor_bin, raiz_bin, raiz_avl);
                break;

            case 0:
                printf("Saindo...\n");
                break;

            default:
                printf("Opção inválida.\n");
        }

    } while (opcao != 0);

    destroi_busbin(&vetor_bin);
    destroi_arvbus(raiz_bin);
    destroi_avl(raiz_avl);

    return 0;
}
