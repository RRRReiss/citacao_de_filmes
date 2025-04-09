#include "busca_binaria.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static int binary_search(const WordEntry *entries, int size, const char *word) {
    int low = 0, high = size - 1;
    while (low <= high) {
        int mid = (low + high) / 2;
        int cmp = strcmp(entries[mid].word, word);
        if (cmp == 0) return mid;
        else if (cmp < 0) low = mid + 1;
        else high = mid - 1;
    }
    return low;
}

void bs_array_init(BSArray *array) {
    array->entries = NULL;
    array->size = 0;
}

void bs_array_destroy(BSArray *array) {
    for (int i = 0; i < array->size; i++) {
        free(array->entries[i].word);
        free(array->entries[i].offsets);
    }
    free(array->entries);
    array->entries = NULL;
    array->size = 0;
}

void bs_array_insert(BSArray *array, const char *word, int count, long offset) {
    int pos = binary_search(array->entries, array->size, word);
    if (pos < array->size && strcmp(array->entries[pos].word, word) == 0) {
        array->entries[pos].frequency += count;
        for (int i = 0; i < array->entries[pos].offset_count; i++) {
            if (array->entries[pos].offsets[i] == offset) return;
        }
        array->entries[pos].offsets = realloc(array->entries[pos].offsets, (array->entries[pos].offset_count + 1) * sizeof(long));
        array->entries[pos].offsets[array->entries[pos].offset_count++] = offset;
    } else {
        WordEntry new_entry = {
            .word = strdup(word),
            .frequency = count,
            .offsets = malloc(sizeof(long)),
            .offset_count = 1
        };
        new_entry.offsets[0] = offset;
        array->entries = realloc(array->entries, (array->size + 1) * sizeof(WordEntry));
        memmove(&array->entries[pos + 1], &array->entries[pos], (array->size - pos) * sizeof(WordEntry));
        array->entries[pos] = new_entry;
        array->size++;
    }
}

WordEntry *bs_array_search(BSArray *array, const char *word) {
    int pos = binary_search(array->entries, array->size, word);
    if (pos < array->size && strcmp(array->entries[pos].word, word) == 0) {
        return &array->entries[pos];
    }
    return NULL;
}
