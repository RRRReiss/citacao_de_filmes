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
    NoAVL *raiz_avl_alfabeto = NULL;
    NoAVL *raiz_avl_frequencia = NULL;

    inicializa_busbin(&vetor_busbin);

    int opcao;
    char nome_arquivo[100], palavra[100];
    
    do {
        printf("\n========= MENU =========\n");
        printf("1 - Carregar arquivo\n");
        printf("2 - Buscar palavra\n");
        printf("3 - Listar por frequencia\n");
        printf("0 - Sair\n");
        printf("========================\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                printf("Arquivo: ");
                scanf("%s", nome_arquivo);
                processa_arquivo(nome_arquivo, &vetor_busbin, &raiz_bst, &raiz_avl_alfabeto);
                printf("Dados carregados!\n");
                break;

            case 2:
                printf("Palavra: ");
                scanf("%s", palavra);
                normaliza_palavra(palavra);

                // Pesquisas
                EntradaRepositorio *vet = pesquisa_busbin(&vetor_busbin, palavra);
                EntradaRepositorio *bst = pesquisa_arvbus(raiz_bst, palavra);
                EntradaRepositorio *avl = pesquisa_avl_alfabeto(raiz_avl_alfabeto, palavra);

                // Exibir resultados
                printf("\n[VETOR] %s: %s\n", 
                    vet ? "Encontrado" : "Nao encontrado", 
                    vet ? vet->palavra : "");
                    
                printf("[BST]   %s: %s\n", 
                    bst ? "Encontrado" : "Nao encontrado", 
                    bst ? bst->palavra : "");
                    
                printf("[AVL]   %s: %s\n\n", 
                    avl ? "Encontrado" : "Nao encontrado", 
                    avl ? avl->palavra : "");
                break;

            case 3:
                // Construir AVL de frequência
                if(raiz_avl_frequencia) destroi_avl(raiz_avl_frequencia);
                raiz_avl_frequencia = NULL;
                
                for(int i = 0; i < vetor_busbin.tamanho; i++) {
                    insere_avl_frequencia(&raiz_avl_frequencia, vetor_busbin.entradas[i]);
                }
                
                printf("\nFrequencia das palavras:\n");
                em_ordem_frequencia(raiz_avl_frequencia);
                break;

            case 0:
                printf("Encerrando...\n");
                break;
        }
    } while(opcao != 0);

    // Liberar memória
    destroi_busbin(&vetor_busbin);
    destroi_arvbus(raiz_bst);
    destroi_avl(raiz_avl_alfabeto);
    destroi_avl(raiz_avl_frequencia);

    return 0;
}
