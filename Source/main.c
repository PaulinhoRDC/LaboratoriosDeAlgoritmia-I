#include <stdio.h>
#include "estado.h"
#include "intepretador.h"

/*

typedef struct estado1{
    int linha;
    int coluna;
    char tab [500][500];
}ESTADO1;

*/

int main() {
    ESTADO e = {0};
    printf("Para comecar a jogar use o comando: N <peca> \n");
    intepretador(e);
    return 0;
}


