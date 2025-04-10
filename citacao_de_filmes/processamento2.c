#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *arquivo = fopen("movie_quotes_subconjunto.csv", "r");
    if(arquivo == NULL){
        perror("Nao foi possivel abrir o arquivo.\n");
        exit(-1);
    }
    printf("Foi possivel abrir o arquivo.\n");
    printf("================================\n");
    return 0;
}
