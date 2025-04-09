#ifndef AVL_H
#define AVL_H

#include "citacoes.h"

typedef struct AVLNode {
    WordEntry entry;
    struct AVLNode *left;
    struct AVLNode *right;
    int height;
} AVLNode;

void avl_insert(AVLNode **root, const char *word, int count, long offset);
WordEntry *avl_search(AVLNode *root, const char *word);
void avl_destroy(AVLNode *root);

#endif
