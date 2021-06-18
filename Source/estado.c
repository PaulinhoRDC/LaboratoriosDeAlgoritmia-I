//
// Created by Paulo Costa on 17/04/2019.
//

#include <stdio.h>
#include "estado.h"
#include <stdlib.h>
#include <stdbool.h>

ESTADO grelha_inicial (ESTADO e, char peca, char modo) {      //TABULEIRO INICIAL
    e.grelha[3][4] = VALOR_X;
    e.grelha[4][3] = VALOR_X;
    e.grelha[3][3] = VALOR_O;
    e.grelha[4][4] = VALOR_O;
    e.peca = peca;
    e.modo = modo;
    return e;
}


ESTADO grelha_nova (ESTADO e) {              //PARA 'RESETAR' O TABULEIRO, PARA COMEÇAR NOVO JOGO

    for (int i=0; i<8 ; i++) {
        for (int j = 0; j < 8; j++) {
            e.grelha[i][j] = VAZIA;
        }
    }

    e.grelha[3][4] = VALOR_X;
    e.grelha[4][3] = VALOR_X;
    e.grelha[3][3] = VALOR_O;
    e.grelha[4][4] = VALOR_O;

    return e;
}

// exemplo de uma função para imprimir o estado (Tabuleiro)

void printa(ESTADO e)
{

    printf("\n");
    printf("1 2 3 4 5 6 7 8\n");
    char c = ' ';

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            switch (e.grelha[i][j]) {
                case VALOR_O: {
                    c = 'O';
                    break;
                }
                case VALOR_X: {
                    c = 'X';
                    break;
                }
                case VAZIA: {
                    c = '-';
                    break;
                }
            }
            printf("%c ", c);

        }
        printf("\n");
    }

}


//FUNÇÃO QUE VAI CHAMAR TODAS AS FUNÇÕES NECESSARIAS PARA EFETUAR VALIDAÇÃO DA JOGADA

int valida (ESTADO e, int x, int y){
    VALOR p;
    int i=0;

    p =e.peca; // Para saber se é valor X ou O;

    if (e.grelha [x] [y] != VAZIA) return 0;

    if( validale (e, x, y) || validald (e, x, y) || validacc (e, x, y) || validacb (e, x, y)
        || validad1 (e, x, y) || validad2 (e, x, y) || validad3 (e, x, y) || validad4 (e, x, y) ) return 1;

    else return 0;
}


//AGORA AS FUNÇÕES TODAS NECESSARIAS PARA A VALIDA

int validacc (ESTADO e, int x , int y){

    VALOR p,g;
    int i=0;
    p=e.peca;
    g=inverso(p);

    if(e.grelha [x-1] [y] == g){
        i= x -1;
        while (i>0 && e.grelha [i] [y] == g){
            i--;
        }
        if (e.grelha [i] [y] == p)
            return 1;
    }
    return 0;
}

int validacb (ESTADO e, int x, int y){

    VALOR p,g;
    int i=0;
    p=e.peca;
    g=inverso (p);

    if(e.grelha [x+1] [y] == g){
        i= x +1;
        while (i<7 && e.grelha [i] [y] == g){
            i++;
        }
        if (e.grelha [i] [y] == p)
            return 1;
    }
    return 0;
}

int validale (ESTADO e, int x, int y){

    VALOR p,g;
    int i=0;
    p=e.peca;
    g=inverso (p);

    if(e.grelha [x] [y-1] == g){
        i= y -1;
        while (i>0 && e.grelha [x] [i] == g){
            i--;
        }
        if (e.grelha [x] [i] == p)
            return 1;
    }
    return 0;
}

int validald (ESTADO e, int x, int y){

    VALOR p,g;
    int i=0;
    p=e.peca;
    g=inverso (p);

    if(e.grelha [x] [y+1] == g){
        i= y +1;
        while (i<7 && e.grelha [x] [i] == g){
            i++;
        }
        if (e.grelha [x] [i] == p)
            return 1;
    }
    return 0;
}

int validad1 (ESTADO e, int x, int y){
    // l-- c--

    VALOR p,g;
    int i= x-1, j=y-1;
    p=e.peca;
    g=inverso (p);

    if(e.grelha [x-1] [y-1] == g){

        while (i>0 && j>0 && e.grelha [i] [j] == g){
            i--;
            j--;
        }
        if (e.grelha [i] [j] == p)
            return 1;
    }
    return 0;
}

int validad2 (ESTADO e, int x, int y){
    //l-- c++

    VALOR p,g;
    int i= x-1, j=y+1;
    p=e.peca;
    g=inverso (p);

    if(e.grelha [x-1] [y+1] == g){

        while (i>0 && j<7 && e.grelha [i] [j] == g){
            i--;
            j++;
        }
        if (e.grelha [i] [j] == p)
            return 1;
    }
    return 0;
}

int validad3 (ESTADO e, int x, int y){
    //l++ c--

    VALOR p,g;
    int i= x+1, j=y-1;
    p=e.peca;
    g=inverso (p);

    if(e.grelha [x+1] [y-1] == g){

        while (i<7 && j>0 && e.grelha [i] [j] == g){
            i++;
            j--;
        }
        if (e.grelha [i] [j] == p)
            return 1;
    }
    return 0;
}

int validad4 (ESTADO e, int x, int y){
    //l++ c++

    VALOR p,g;
    int i= x+1, j=y+1;
    p=e.peca;
    g=inverso (p);

    if(e.grelha [x+1] [y+1] == g){

        while (i<7 && j<7 && e.grelha [i] [j] == g){
            i++;
            j++;
        }
        if (e.grelha [i] [j] == p)
            return 1;
    }
    return 0;
}


//FUNÇÃO INVERSO , NECESSÁRIA PARA AS FUNÇOES VALIDA, PARA SABER SE AS PEÇAS ENTRE AS NOSSAS SAO DO ADVERSARIO
VALOR inverso (VALOR p){

    if (p==VALOR_X){
        return VALOR_O;
    }

    else if ( p== VALOR_O) return VALOR_X;
         else return VAZIA;

}


//FUNÇÃO PARA MUDAR AS PEÇAS INTERMEDIÁRIAS DA JOGADA EFETUADA DE ACORDO COM O RETURN DAS VALIDAS

ESTADO trocardepecascc (ESTADO e, int x, int y) {
    VALOR p, g;
    int i = 0;
    p = e.peca;
    g = inverso(p);

    if (validacc(e, x, y)) {
        i = x - 1;
        while (i > 0 && e.grelha[i][y] == g) {
            e.grelha[i][y] = e.peca;
            i--;
        }
    }
    return e;
}

ESTADO trocardepecascb (ESTADO e, int x, int y) {
    VALOR p, g;
    int i = 0;
    p = e.peca;
    g = inverso(p);

    if (validacb(e, x, y)) {
        i = x + 1;
        while (i < 7 && e.grelha[i][y] == g) {
            e.grelha[i][y] = e.peca;
            i++;
        }
    }
    return e;
}

ESTADO trocardepecasle (ESTADO e, int x, int y) {
    VALOR p, g;
    int i = 0;
    p = e.peca;
    g = inverso(p);
    if (validale(e, x, y)) {
        i = y - 1;
        while (i > 0 && e.grelha[x][i] == g) {
            e.grelha[x][i] = e.peca;
            i--;
        }
    }
    return e;
}

ESTADO trocardepecasld (ESTADO e, int x, int y) {
    VALOR p, g;
    int i = 0;
    p = e.peca;
    g = inverso(p);

    if (validald(e, x, y)) {
        i = y + 1;
        while (i < 7 && e.grelha[x][i] == g) {
            e.grelha[x][i] = e.peca;
            i++;
        }
    }
    return e;
}

ESTADO trocardepecasd1 (ESTADO e, int x, int y) {
    VALOR p, g;
    int i = 0;
    p = e.peca;
    g = inverso(p);

    if (validad1(e, x, y)) {        // l-- c--
        int i = x - 1, j = y - 1;
        while (i > 0 && j > 0 && e.grelha[i][j] == g) {
            e.grelha[i][j] = e.peca;
            i--;
            j--;
        }
    }
    return e;
}

ESTADO trocardepecasd2 (ESTADO e, int x, int y) {
    VALOR p, g;
    int i = 0;
    p = e.peca;
    g = inverso(p);

    if (validad2(e, x, y)) {          //l-- c++
        int i = x - 1, j = y + 1;
        while (i > 0 && j < 7 && e.grelha[i][j] == g) {
            e.grelha[i][j] = e.peca;
            i--;
            j++;
        }
    }
    return e;
}

ESTADO trocardepecasd3 (ESTADO e, int x, int y) {
    VALOR p, g;
    int i = 0;
    p = e.peca;
    g = inverso(p);
    if (validad3(e, x, y)) {          //l++ c--
        int i = x + 1, j = y - 1;
        while (i < 7 && j > 0 && e.grelha[i][j] == g) {
            e.grelha[i][j] = e.peca;
            i++;
            j--;
        }
    }
    return e;
}

ESTADO trocardepecasd4 (ESTADO e, int x, int y) {
    VALOR p, g;
    int i = 0;
    p = e.peca;
    g = inverso(p);


    if (validad4(e, x, y)){             //l++ c++
        int i= x+1, j=y+1;
            while (i<7 && j<7 && e.grelha [i] [j] == g){
                e.grelha [i] [j] = e.peca;
                i++;
                j++;
            }
    }
    return e;
}


//FUNÇÃO PARA NO FIM DE CADA JOGADA EFETUADA, MOSTRAR O SCORE DE CAGA JOGADOR

void resultado (ESTADO e) {
    int i;int j;int r=0;int r2=0;

    for ( i = 0; i < 8; i++) {
        for ( j = 0; j < 8; j++) {
            switch (e.grelha[i][j]) {
                case VALOR_O: {
                    r++;
                    break;
                }
                case VALOR_X: {
                    r2++;
                    break;
                }
            }
        }
    }

    printf("Resultado Jogador1 ('O'): %d                       Resultado Jogador2 ('X'): %d     \n", r,r2);
}

//FUNÇÃO QUE EM CASO DE FIM DA PARTIDA , COMPARA A QUANTIDADE DE PEÇAS DE CADA JOGADOR E DA RETURN DO VENCEDOR
void vencedor (ESTADO e) {
    int i;int j;int r=0;int r2=0;

    for ( i = 0; i < 8; i++) {
        for ( j = 0; j < 8; j++) {
            switch (e.grelha[i][j]) {
                case VALOR_O: {
                    r++;
                    break;
                }
                case VALOR_X: {
                    r2++;
                    break;
                }
            }
        }
    }
    if (r>r2) {
        printf ("VENCEDOR JOGADOR COM PECA 'O'\n");
    }
    else if (r<r2) {
        printf("VENCEDOR JOGADOR COM PECA 'X'\n");
    }
    else printf ("EMPATE\n");
}



//FUNÇOES NECESSÁRIAS PARA O CASE UNDO

//INICIAR A LISTA LIGADA

void iniciarListaLigada (ESTADO e, STACK *s){
    s -> spointer = 0;
    s -> estados [ s -> spointer] = e;
}

//PARA ATUALIZAÇÃO DA LISTA LIGADA

void atualizarListaLigada (ESTADO e, STACK *s){
    s -> spointer++;
    s -> estados [s -> spointer] = e;
}

//AGORA A FUNÇAO UNDO MESMO, PARA QUANDO FOR CHAMADA

ESTADO undo (ESTADO e, STACK *s) {
    s->spointer--;
    e = s->estados[s->spointer];
    printf("\n");
    printa(e);
    printf("\n");
    return e;
}


                                                  //---//

//FUNÇAO PARA VER SE AMBOS OS JOGADORES SAO OBRIGADOS A PASSAR JOGADA E SE SIM, TERMINAR JOGO
//RETURN 1 SE O JOGADOR ATUAL PUDER JOGAR, RETURN 2 SE AMBOS NAO PUDEREM, RETURN 3 SE O INVERSO PODE

int terminaGame (ESTADO e) {
    //jogadas possiveis
    int l, c;

    int conta = 0;
    for (l = 0; l < 8; l++) {
        for (c = 0; c < 8; c++) {
            if (valida(e, l, c) == 1) conta++;
        }
    }
    if (conta == 0) {
        e.peca = inverso(e.peca);
        int containv = 0;
        for (l = 0; l < 8; l++) {
            for (c = 0; c < 8; c++) {
                if (valida(e, l, c) == 1) containv++;
            }
        }
        if (containv == 0) return 2;             //MOSTRAR RESULTADO, APRESENTAR VENCEDOR
        else return 3;          // FAZER PASSAR A JOGADA PARA O JOGADOR ADVERSÁRIO AO ATUAL
    }
    else return 1;            // PERMITIR AO JOGADOR ATUAL, REALIZAR A SUA JOGADA
    }

    //FUNÇÃO PARA O CASE L

void cop (FILE *f,char v[20][20]){
    int i;
    for (i=0;!feof(f);i++) {
        fgets(v[i], 100, f);
    }
}


                                            //BOT//

// FUNÇÃO PARA ESCOLHA DA JOGADA QUE O BOT FARÁ, NO NÍVEL BASICO ( JOGAR NA PRIMEIRA JOGADA, QUE FOR POSSIVEL (2))
//TANTO PODERÁ SER UMA JOGADA DE BOT BÁSICO OU PROFISSIONAL , COMO OUTRA QUALQUER... O QUE FARÁ A DIFICULDADE MEDIANA

ESTADO jogadaBotBas (ESTADO e, int l, int c){

    int l2, c2;
    int r=0;

    for (l2 = 0; l2 < 8; l2++) {
        for (c2 = 0; c2 < 8; c2++) {
            if (valida (e,l2,c2) && r==0){
                e.grelha [l2] [c2] = e.peca;
                e= trocardepecascc (e, l2, c2);
                e= trocardepecascb (e, l2, c2);
                e= trocardepecasld (e, l2, c2);
                e= trocardepecasle (e, l2, c2);
                e= trocardepecasd1 (e, l2, c2);
                e= trocardepecasd2 (e, l2, c2);
                e= trocardepecasd3 (e, l2, c2);
                e= trocardepecasd4 (e, l2, c2);
                r++;
            }
        }
    }
    return e;
}

//FUNÇÃO PARA ESCOLHA DA JOGADA QUE O BOT FARÁ, NO NÍVEL MÉDIO (a jogada que comerá menos peças (2))

ESTADO jogadaBotMed (ESTADO e, int l, int c){
    int lb, cb;         // linha bot & coluna bot
    int minbot=65;            // guardar a jogada que come menos peças
    int lbg, cbg;    // linha e coluna  do bot que está a ser guardada   // NAO SEI SE TEM DE ESTAR INICIALIZADAS


    for (lb = 0; lb < 8; lb++) {
        for (cb = 0; cb < 8; cb++) {
            if (valida (e, lb, cb) == 1) {
                if (quantaspecas (e, lb , cb) < minbot){
                    minbot = quantaspecas (e, lb , cb);
                    lbg = lb;
                    cbg = cb;
                }
            }
        }
    }

    e.grelha [lbg] [cbg] = e.peca;
    e= trocardepecascc (e, lbg, cbg);
    e= trocardepecascb (e, lbg, cbg);
    e= trocardepecasld (e, lbg, cbg);
    e= trocardepecasle (e, lbg, cbg);
    e= trocardepecasd1 (e, lbg, cbg);
    e= trocardepecasd2 (e, lbg, cbg);
    e= trocardepecasd3 (e, lbg, cbg);
    e= trocardepecasd4 (e, lbg, cbg);

    //printa(e);
    return e;

}


//FUNÇÃO PARA ESCOLHA DA JOGADA QUE O BOT FARÁ, NO NÍVEL PROFISSIONAL ( TENTAR DEFINIR AS REGIOES DO ALGORITMO MAXSMIN )
// DEPOIS COMPARANDO AS REGIÕES ESCOLHER A JOGADA PERTENCENTE A REGIÃO MAIS PERIGOSA, E EFETUAR ESSA MESMA

ESTADO jogadaBotPro (ESTADO e, int x, int y){

    int l, c;
    int melhorjogada =0;
    int jogadacomemais =0;
    int lmj, cmj;

    for (l = 0; l < 8; l++) {
        for (c = 0; c < 8; c++) {

            if (valida(e, l, c) == 1) {
                if (regiaodajogada(l, c) > melhorjogada) {       // OPTA PELA JOGADA COM REGIÃO MAIS FAVORÁVEL
                    melhorjogada = regiaodajogada(l, c);
                    jogadacomemais = quantaspecas(e, l, c);
                    lmj = l;
                    cmj = c;
                }
                else if (regiaodajogada(l, c) == melhorjogada) {   // EM CASA DA REGIÃO IGUAL OPTA PELA QUE COME MAIS PEÇAS
                    if (quantaspecas(e, l, c) > jogadacomemais) {
                        melhorjogada = regiaodajogada(l, c);
                        jogadacomemais = quantaspecas(e, l, c);
                        lmj = l;
                        cmj = c;
                    }
                }
            }
        }
    }

    e.grelha [lmj] [cmj] = e.peca;
    e= trocardepecascc (e, lmj, cmj);
    e= trocardepecascb (e, lmj, cmj);
    e= trocardepecasld (e, lmj, cmj);
    e= trocardepecasle (e, lmj, cmj);
    e= trocardepecasd1 (e, lmj, cmj);
    e= trocardepecasd2 (e, lmj, cmj);
    e= trocardepecasd3 (e, lmj, cmj);
    e= trocardepecasd4 (e, lmj, cmj);
    //printa(e);
    return e;
}



//FUNÇÃO PARA SABER QUANTAS PEÇAS SE VÃO COMER/ALTERAR EM CADA JOGADA

int quantaspecas (ESTADO e, int x, int y) {
    VALOR p, g;
    int i = 0;
    p = e.peca;
    g = inverso(p);
    int contaquantas = 0;   // variavel a acumular quantas peças se comem numa determinada jogada

    if (validacc(e, x, y)) {
        i = x - 1;
        while (i > 0 && e.grelha[i][y] == g) {
            contaquantas++;
            i--;
        }
    }

    else if (validacb(e, x, y)) {
        i = x + 1;
        while (i < 7 && e.grelha[i][y] == g) {
            contaquantas++;
            i++;
        }
    }

    else if  (validale(e, x, y)) {
        i = y - 1;
        while (i > 0 && e.grelha[x][i] == g) {
            contaquantas++;
            i--;
        }
    }

    else if (validald(e, x, y)) {
        i = y + 1;
        while (i < 7 && e.grelha[x][i] == g) {
            contaquantas++;
            i++;
        }
    }
    else if (validad1 (e, x, y)) {        // l-- c--
        int i = x - 1, j = y - 1;
        while (i > 0 && j > 0 && e.grelha[i][j] == g) {
            contaquantas++;
            i--;
            j--;
        }
    }
    else if (validad2(e, x, y)){          //l-- c++
        int i= x-1, j=y+1;
        while (i>0 && j<7 && e.grelha [i] [j] == g){
            contaquantas++;
            i--;
            j++;
        }
    }
    else if (validad3(e, x, y)){          //l++ c--
        int i= x+1, j=y-1;
        while (i<7 && j>0 && e.grelha [i] [j] == g){
            contaquantas++;
            i++;
            j--;
        }
    }
    else if (validad4(e, x, y)){             //l++ c++
        int i= x+1, j=y+1;
        while (i<7 && j<7 && e.grelha [i] [j] == g){
            contaquantas++;
            i++;
            j++;
        }
    }
    return contaquantas;
}

//FUNÇÃO QUE DEFINE AS REGIÕES UTILIZADAS NO BOT PROFISSIONAL ATRAVÉS DA LINHA E DA COLUNA DE CADA JOGADA

int regiaodajogada (int l, int c){

    //DEFINE AS JOGADAS CONFORME A SUA LINHA E COLUNA NAS REGIÕES MAIS PERIGOSAS OU MAIS VALIOSAS:

    // REGIÃO 1 É A JOGADA MAIS 'INÚTIL', CORRESPONDE Á PARTE CENTRAL DO TABULEIRO
    // REGIÃO 2 É A PRIMEIRA JOGADA MAIS 'PERIGOSA', POIS PERMITE AO ADVERSÁRIO, OBTER AS 'PONTAS' DO TABULEIRO
    // REGIÃO 3 É SEGUNDA JOGADA MAIS 'ARRISCADA', POIS PERMITE AO ADVERSÁRIO, OBTER AS LATERAIS DO TABULEIRO, MAS MAIS 'VALIOSA QUE AS ANTERIORES
    // REGIÃO 4 É A QUARTA JOGADA, ESTA JÁ MAIS 'VALIOSA', CORRESPONDE AO JOGADOR COMSEGUIR COLOCAR PEÇA NAS LATERAIS DO TABULEIRO
    // REGIÃO 5 É A QUINTA JOGADA, ESTA A MAIS 'PROCURADA' E 'VALIOSA', CORRESPONDE AO JOGADOR OBTER AS 'PONTAS' DO TABULEIRO

    if (l >= 2 && l <= 5 && c <= 5 && c >= 2){
        return 1;    // JOGADAS MAIS INÚTEIS
    }
    else if ( (l==1 && c >= 2 && c <= 5) || (l >=2 && l <= 5 && c==1) || (l==6 && c >=2 && c <= 5) || (l >= 2 && l <=5 && c==6) ){
        return 3;     // PERMITE OBTER AS LATERAIS, DO TABULEIRO
    }
    else if ( (l==0 && c >= 2 && c <= 5) || (l >= 2 && l <= 5 && c==0) || (l==7 && c >= 2 && c <= 5) || (l >= 2 && l <= 5 && c==7) ) {
        return 4;        // JOGADA NAS LATERAIS DO TABULEIRO
    }
    else if ( (l==0 && c==1) || (l==0 && c==6) || (l==1 && c >= 0 && c <= 1) || (l==1 && c >= 6 && c <= 7) || (l==6 && c >= 0 && c <= 1) || (l==6 && c >= 6 && c <= 7) || (l==7 && c==1) || (l==7 && c==6) ){
        return 2;   // PERMITE OBTER AS 'PONTAS' , JOGADA MAIS PERIOGOSA
    }
    else return 5;      // JOGADA NAS 'PONTAS' DO TABULEIRO , JOGADA MAIS PROCURADA E VALIOSA;

}



ESTADO jogada ( int L , int C , ESTADO e){
    e.peca=VALOR_O;
    e.grelha[L][C] = e.peca;
    return e;
}





