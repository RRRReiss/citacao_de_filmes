#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "busca_binaria.h"
#include "arvore_binaria.h"
#include "arvore_avl.h"
#include "processamento.h"

void display_quote_info(FILE *file, long offset) {
    fseek(file, offset, SEEK_SET);
    char line[1024];
    if (fgets(line, sizeof(line), file)) {
        QuoteInfo info;
        if (parse_line(line, &info)) {
            printf("Quote: %s\nMovie: %s\nYear: %d\n\n", info.quote, info.movie, info.year);
            free(info.quote);
            free(info.movie);
        }
    }
}

int main() {
    BSArray bs_array;
    bs_array_init(&bs_array);
    BSTNode *bst_root = NULL;
    AVLNode *avl_root = NULL;

    char filename[256];
    printf("Enter file name: ");
    scanf("%255s", filename);

    clock_t start, end;
    double bs_time, bst_time, avl_time;

    start = clock();
    process_file(filename, &bs_array, &bst_root, &avl_root);
    end = clock();
    bs_time = ((double)(end - start)) / CLOCKS_PER_SEC;

    bs_array_destroy(&bs_array);
    bs_array_init(&bs_array);
    bst_destroy(bst_root);
    bst_root = NULL;
    avl_destroy(avl_root);
    avl_root = NULL;

    start = clock();
    process_file(filename, &bs_array, &bst_root, &avl_root);
    end = clock();
    bst_time = ((double)(end - start)) / CLOCKS_PER_SEC;

    bs_array_destroy(&bs_array);
    bs_array_init(&bs_array);
    bst_destroy(bst_root);
    bst_root = NULL;
    avl_destroy(avl_root);
    avl_root = NULL;

    start = clock();
    process_file(filename, &bs_array, &bst_root, &avl_root);
    end = clock();
    avl_time = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("Load times:\nBS Array: %f\nBST: %f\nAVL: %f\n", bs_time, bst_time, avl_time);

    char word[256];
    printf("Enter a word to search: ");
    scanf("%255s", word);
    normalize_word(word);

    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Failed to open file");
        return 1;
    }

    start = clock();
    WordEntry *entry = bs_array_search(&bs_array, word);
    end = clock();
    double bs_search_time = ((double)(end - start)) / CLOCKS_PER_SEC;

    if (entry) {
        printf("BS Array - Frequency: %d\n", entry->frequency);
        for (int i = 0; i < entry->offset_count; i++) display_quote_info(file, entry->offsets[i]);
    } else printf("Word not found in BS Array\n");

    start = clock();
    entry = bst_search(bst_root, word);
    end = clock();
    double bst_search_time = ((double)(end - start)) / CLOCKS_PER_SEC;

    if (entry) {
        printf("BST - Frequency: %d\n", entry->frequency);
        for (int i = 0; i < entry->offset_count; i++) display_quote_info(file, entry->offsets[i]);
    } else printf("Word not found in BST\n");

    start = clock();
    entry = avl_search(avl_root, word);
    end = clock();
    double avl_search_time = ((double)(end - start)) / CLOCKS_PER_SEC;

    if (entry) {
        printf("AVL - Frequency: %d\n", entry->frequency);
        for (int i = 0; i < entry->offset_count; i++) display_quote_info(file, entry->offsets[i]);
    } else printf("Word not found in AVL\n");

    printf("Search times:\nBS Array: %f\nBST: %f\nAVL: %f\n", bs_search_time, bst_search_time, avl_search_time);

    fclose(file);
    bs_array_destroy(&bs_array);
    bst_destroy(bst_root);
    avl_destroy(avl_root);

    return 0;
}
