#include "arvore_avl.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static int height(AVLNode *node) { return node ? node->height : 0; }
static int max(int a, int b) { return (a > b) ? a : b; }

static AVLNode *new_node(const char *word, int count, long offset) {
    AVLNode *node = malloc(sizeof(AVLNode));
    node->entry.word = strdup(word);
    node->entry.frequency = count;
    node->entry.offsets = malloc(sizeof(long));
    node->entry.offsets[0] = offset;
    node->entry.offset_count = 1;
    node->left = node->right = NULL;
    node->height = 1;
    return node;
}

static AVLNode *right_rotate(AVLNode *y) {
    AVLNode *x = y->left;
    AVLNode *T2 = x->right;
    x->right = y;
    y->left = T2;
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;
    return x;
}

static AVLNode *left_rotate(AVLNode *x) {
    AVLNode *y = x->right;
    AVLNode *T2 = y->left;
    y->left = x;
    x->right = T2;
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;
    return y;
}

static int get_balance(AVLNode *node) { return node ? height(node->left) - height(node->right) : 0; }

static void add_offset_avl(WordEntry *entry, long offset) {
    for (int i = 0; i < entry->offset_count; i++) {
        if (entry->offsets[i] == offset) return;
    }
    entry->offsets = realloc(entry->offsets, (entry->offset_count + 1) * sizeof(long));
    entry->offsets[entry->offset_count++] = offset;
}

static AVLNode *avl_insert_node(AVLNode *node, const char *word, int count, long offset) {
    if (node == NULL) return new_node(word, count, offset);
    int cmp = strcmp(word, node->entry.word);
    if (cmp < 0) node->left = avl_insert_node(node->left, word, count, offset);
    else if (cmp > 0) node->right = avl_insert_node(node->right, word, count, offset);
    else {
        node->entry.frequency += count;
        add_offset_avl(&node->entry, offset);
        return node;
    }
    node->height = 1 + max(height(node->left), height(node->right));
    int balance = get_balance(node);
    if (balance > 1 && strcmp(word, node->left->entry.word) < 0) return right_rotate(node);
    if (balance < -1 && strcmp(word, node->right->entry.word) > 0) return left_rotate(node);
    if (balance > 1 && strcmp(word, node->left->entry.word) > 0) {
        node->left = left_rotate(node->left);
        return right_rotate(node);
    }
    if (balance < -1 && strcmp(word, node->right->entry.word) < 0) {
        node->right = right_rotate(node->right);
        return left_rotate(node);
    }
    return node;
}

void avl_insert(AVLNode **root, const char *word, int count, long offset) {
    *root = avl_insert_node(*root, word, count, offset);
}

WordEntry *avl_search(AVLNode *root, const char *word) {
    if (root == NULL) return NULL;
    int cmp = strcmp(word, root->entry.word);
    if (cmp < 0) return avl_search(root->left, word);
    else if (cmp > 0) return avl_search(root->right, word);
    else return &root->entry;
}

void avl_destroy(AVLNode *root) {
    if (root == NULL) return;
    avl_destroy(root->left);
    avl_destroy(root->right);
    free(root->entry.word);
    free(root->entry.offsets);
    free(root);
}
