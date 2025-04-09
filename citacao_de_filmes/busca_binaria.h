#ifndef BS_ARRAY_H
#define BS_ARRAY_H

#include "citacoes.h"

typedef struct {
    WordEntry *entries;
    int size;
} BSArray;

void bs_array_init(BSArray *array);
void bs_array_destroy(BSArray *array);
void bs_array_insert(BSArray *array, const char *word, int count, long offset);
WordEntry *bs_array_search(BSArray *array, const char *word);

#endif
