#ifndef QUOTEREPO_H
#define QUOTEREPO_H

typedef struct EntradaRepositorio{
    char *palavra;
    int frequencia;
    long *offsets;
    int offset_cont;
} EntradaRepositorio;

#endif
