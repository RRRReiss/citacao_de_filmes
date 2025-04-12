#ifndef QUOTEREPO_H
#define QUOTEREPO_H

// representa uma entrada no repositorio de palavras
typedef struct EntradaRepositorio {
    char *palavra;         // ponteiro p palavra armazenada
    int frequencia;        // quantidade de ocorrencias da palavra
    long *offsets;         // vetor com os offsets no arquivo onde a palavra aparece
    int offset_cont;      
} EntradaRepositorio;

#endif
