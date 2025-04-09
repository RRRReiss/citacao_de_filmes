#ifndef BST_H
#define BST_H

#include "citacoes.h"

typedef struct BSTNode {
    WordEntry entry;
    struct BSTNode *left;
    struct BSTNode *right;
} BSTNode;

void bst_insert(BSTNode **root, const char *word, int count, long offset);
WordEntry *bst_search(BSTNode *root, const char *word);
void bst_destroy(BSTNode *root);

#endif
