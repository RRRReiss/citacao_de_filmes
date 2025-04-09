#ifndef QUOTEREPO_H
#define QUOTEREPO_H

typedef struct {
    char *word;
    int frequency;
    long *offsets;
    int offset_count;
} WordEntry;

#endif
