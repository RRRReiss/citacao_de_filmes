#include "arvore_binaria.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static void add_offset(WordEntry *entry, long offset) {
    for (int i = 0; i < entry->offset_count; i++) {
        if (entry->offsets[i] == offset) return;
    }
    entry->offsets = realloc(entry->offsets, (entry->offset_count + 1) * sizeof(long));
    entry->offsets[entry->offset_count++] = offset;
}

void bst_insert(BSTNode **root, const char *word, int count, long offset) {
    if (*root == NULL) {
        BSTNode *new_node = malloc(sizeof(BSTNode));
        new_node->entry.word = strdup(word);
        new_node->entry.frequency = count;
        new_node->entry.offsets = malloc(sizeof(long));
        new_node->entry.offsets[0] = offset;
        new_node->entry.offset_count = 1;
        new_node->left = new_node->right = NULL;
        *root = new_node;
        return;
    }
    int cmp = strcmp(word, (*root)->entry.word);
    if (cmp < 0) bst_insert(&(*root)->left, word, count, offset);
    else if (cmp > 0) bst_insert(&(*root)->right, word, count, offset);
    else {
        (*root)->entry.frequency += count;
        add_offset(&(*root)->entry, offset);
    }
}

WordEntry *bst_search(BSTNode *root, const char *word) {
    if (root == NULL) return NULL;
    int cmp = strcmp(word, root->entry.word);
    if (cmp < 0) return bst_search(root->left, word);
    else if (cmp > 0) return bst_search(root->right, word);
    else return &root->entry;
}

void bst_destroy(BSTNode *root) {
    if (root == NULL) return;
    bst_destroy(root->left);
    bst_destroy(root->right);
    free(root->entry.word);
    free(root->entry.offsets);
    free(root);
}
