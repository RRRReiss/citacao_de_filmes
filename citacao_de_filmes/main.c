#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "busca_binaria.h"
#include "arvore_binaria.h"
#include "arvore_avl.h"
#include "processamento.h"

int main() {
    VetorBuscaBinaria vetor_busbin;
    NoArvoreBusca *raiz_bst = NULL;
    NoAVL *raiz_avl = NULL;

    int opcao;
    char nome_arquivo[100];
    char palavra[100];

    inicializa_busbin(&vetor_busbin);

    do {
        printf("\n========= MENU =========\n");
        printf("1 - Carregar arquivo de citacoes\n");
        printf("2 - Buscar palavra\n");
        printf("3 - Listar palavras por frequencia (AVL)\n");
        printf("0 - Sair\n");
        printf("========================\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Digite o nome do arquivo (ex: movie_quotes_subconjunto.csv): ");
                scanf("%s", nome_arquivo);
                processa_arquivo(nome_arquivo, &vetor_busbin, &raiz_bst, &raiz_avl);
                printf("\nArquivo processado com sucesso!\n");
                break;

            case 2:
                printf("Digite a palavra que deseja buscar: ");
                scanf("%s", palavra);
                normaliza_palavra(palavra);

                EntradaRepositorio *res_vet = pesquisa_busbin(&vetor_busbin, palavra);
                EntradaRepositorio *res_bst = pesquisa_arvbus(raiz_bst, palavra);
                EntradaRepositorio *res_avl = pesquisa_avl(raiz_avl, palavra);

                printf("\n--- RESULTADOS ---\n");

                if (res_vet)
                    printf("[VETOR] '%s' - %d ocorrencias\n", palavra, res_vet->frequencia);
                else
                    printf("[VETOR] Palavra nao encontrada.\n");

                if (res_bst)
                    printf("[BST]   '%s' - %d ocorrencias\n", palavra, res_bst->frequencia);
                else
                    printf("[BST] Palavra nao encontrada.\n");

                if (res_avl)
                    printf("[AVL]   '%s' - %d ocorrencias\n", palavra, res_avl->frequencia);
                else
                    printf("[AVL] Palavra nao encontrada.\n");

                break;

            case 3:
                printf("\nPalavras ordenadas por frequencia (em ordem AVL):\n");
                em_ordem_avl(raiz_avl);
                break;

            case 0:
                printf("Saindo...\n");
                break;

            default:
                printf("Opcao invalida!\n");
        }

    } while (opcao != 0);

    destroi_busbin(&vetor_busbin);
    destroi_arvbus(raiz_bst);
    destroi_avl(raiz_avl);

    return 0;
}
