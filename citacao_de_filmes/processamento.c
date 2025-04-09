#include "processamento.h"
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void normalize_word(char *word) {
    int i = 0, j = 0;
    while (word[i]) {
        if (isalnum((unsigned char)word[i])) {
            word[j++] = tolower((unsigned char)word[i]);
        }
        i++;
    }
    word[j] = '\0';
}

int parse_line(const char *line, QuoteInfo *info) {
    char buffer[1024];
    strcpy(buffer, line);
    char *token = strtok(buffer, "\",");
    if (!token) return 0;
    info->quote = strdup(token);
    token = strtok(NULL, "\",");
    if (!token) {
        free(info->quote);
        return 0;
    }
    info->movie = strdup(token);
    token = strtok(NULL, ",");
    if (!token) {
        free(info->quote);
        free(info->movie);
        return 0;
    }
    info->year = atoi(token);
    return 1;
}

void process_file(const char *filename, BSArray *bs_array, BSTNode **bst_root, AVLNode **avl_root) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Failed to open file");
        return;
    }
    char line[1024];
    while (fgets(line, sizeof(line), file)) {
        long offset = ftell(file) - strlen(line) - 1;
        QuoteInfo info;
        if (!parse_line(line, &info)) continue;
        char *quote = info.quote;
        char *token = strtok(quote, " ");
        while (token) {
            normalize_word(token);
            if (strlen(token) > 3) {
                bs_array_insert(bs_array, token, 1, offset);
                bst_insert(bst_root, token, 1, offset);
                avl_insert(avl_root, token, 1, offset);
            }
            token = strtok(NULL, " ");
        }
        free(info.quote);
        free(info.movie);
    }
    fclose(file);
}
