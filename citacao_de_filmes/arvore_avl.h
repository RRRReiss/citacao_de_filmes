#ifndef ARVORE_AVL_H
#define ARVORE_AVL_H

#include "citacoes.h"

// estrutura de nó da arvore AVL
typedef struct NoAVL {
    EntradaRepositorio entrada; // dados da palavra
    struct NoAVL *esq; // ponteiro para o filho da esquerda
    struct NoAVL *dir; // ponteiro para o filho da direita
    int altura; // altura do no
} NoAVL;

// cria um novo nó da AVL com os dados da entrada
NoAVL* cria_no_avl(EntradaRepositorio entrada);

// retorna a altura de um nó
int altura(NoAVL *no);

// calcula o fator de balanceamento de um nó
int fator_balanceamento(NoAVL *no);

// realiza rotacao simples para a direita
NoAVL* rotacao_direita(NoAVL *y);

// realiza rotacao simples para a esquerda
NoAVL* rotacao_esquerda(NoAVL *x);

// adiciona um offset na lista se ele ainda nao estiver presente
void add_offset_avl(EntradaRepositorio *entrada, long offset);

// insere a entrada na AVL ordenada alfabeticamente
NoAVL* insere_avl(NoAVL **raiz, EntradaRepositorio entrada);

// busca uma palavra na AVL ordenada alfabeticamente
EntradaRepositorio *pesquisa_avl_alfabeto(NoAVL *raiz, char *palavra);

// libera toda memória da arvore
void destroi_avl(NoAVL *raiz);

// imprime palavras em ordem decrescente de frequencia
void em_ordem_frequencia(NoAVL *no);

// insere a entrada na AVL ordenada por frequencia
NoAVL* insere_avl_frequencia(NoAVL **raiz, EntradaRepositorio entrada);

#endif
