#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "processamento.h"
#include "busca_binaria.h"
#include "arvore_binaria.h"
#include "arvore_avl.h"

NoAVL *raiz_freq_global = NULL;

//funcao para mostrar as citações associadas à palavra encontrada
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
    }

    fclose(fp);
}

//funcao para buscar uma palavra nas 3 estruturas
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

    ini = clock();
    res = pesquisa_busbin(vet, normalizada);
    fim = clock();
    printf("\n Vetor (busca binária) [%.6f s]:\n", (double)(fim - ini) / CLOCKS_PER_SEC);
    mostrar_citacoes(arquivo, res);

    ini = clock();
    res = pesquisa_arvbus(raiz_bin, normalizada);
    fim = clock();
    printf("\n Árvore Binária de Busca [%.6f s]:\n", (double)(fim - ini) / CLOCKS_PER_SEC);
    mostrar_citacoes(arquivo, res);

    ini = clock();
    res = pesquisa_avl_alfabeto(raiz_avl, normalizada);
    fim = clock();
    printf("\n Árvore AVL [%.6f s]:\n", (double)(fim - ini) / CLOCKS_PER_SEC);
    mostrar_citacoes(arquivo, res);
}

int main() {
    VetorBuscaBinaria vetor_bin;
    NoArvoreBusca *raiz_bin = NULL;
    NoAVL *raiz_avl = NULL;

    char arquivo[100];
    int opcao;
    char palavra[100];
    int carregado = 0;

    do {
        printf("\n--- MENU ---\n");
        printf("1. Carregar e processar arquivo\n");
        printf("2. Buscar palavra\n");
        printf("3. Listar palavras por frequência (AVL)\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar(); // consome o \n após o número

        switch (opcao) {
            case 1:
                printf("Digite o nome do arquivo (ex: movie_quotes.csv): ");
                fgets(arquivo, sizeof(arquivo), stdin);
                arquivo[strcspn(arquivo, "\n")] = '\0'; // remove o \n do final

                inicializa_busbin(&vetor_bin);
                processa_arquivo(arquivo, &vetor_bin, &raiz_bin, &raiz_avl);
                printf("Arquivo carregado e estruturas preenchidas!\n");

                //criar árvore AVL ordenada por frequência
                for (int i = 0; i < vetor_bin.tamanho; i++) {
                    EntradaRepositorio entrada;
                    entrada.palavra = strdup(vetor_bin.entradas[i].palavra);
                    entrada.frequencia = vetor_bin.entradas[i].frequencia;
                    entrada.offset_cont = vetor_bin.entradas[i].offset_cont;
                    entrada.offsets = malloc(sizeof(long) * entrada.offset_cont);
                    // Adicionar verificação de falha de malloc/strdup seria bom
                    memcpy(entrada.offsets, vetor_bin.entradas[i].offsets, sizeof(long) * entrada.offset_cont);

                    raiz_freq_global = insere_avl_frequencia(&raiz_freq_global, entrada); // Assumindo que insere_avl_frequencia também é NoAVL* func(NoAVL**, ...) ou ajustada

                    // Como insere_avl_frequencia faz cópias (via cria_no_avl) ou ignora
                    // a entrada em caso de duplicata, a memória alocada localmente
                    // para 'entrada' aqui pode ser liberada após a chamada.
                    free(entrada.palavra);
                    free(entrada.offsets);
                }

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

            case 3:
                if (!carregado) {
                    printf("⚠ Primeiro carregue o arquivo!\n");
                    break;
                }
                printf("Palavras em ordem decrescente de frequência:\n");
                em_ordem_frequencia(raiz_freq_global);
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
    destroi_avl(raiz_freq_global);

    return 0;
}
