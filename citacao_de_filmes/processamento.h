#ifndef QUOTE_PROCESSING_H
#define QUOTE_PROCESSING_H

#include <stdio.h>
#include "arvore_avl.h"
#include "arvore_binaria.h"
#include "busca_binaria.h"

typedef struct {
    char *quote;
    char *movie;
    int year;
} QuoteInfo;

void normalize_word(char *word);
int parse_line(const char *line, QuoteInfo *info);
void process_file(const char *filename, BSArray *bs_array, BSTNode **bst_root, AVLNode **avl_root);

#endif
