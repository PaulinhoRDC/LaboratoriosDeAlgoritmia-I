//
// Created by Paulo Costa on 17/04/2019.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "intepretador.h"
#include "estado.h"


ESTADO intepretar (ESTADO e, char *linha) {
    char cmd[MAX_BUF];
    char ficheiro[MAX_BUF];
    char peca[MAX_BUF];
    char nivel[MAX_BUF];             //USADO PARA O NÍVEL DO BOT
    int lin, col, n;
    STACK s;
    n = sscanf(linha, "%s", cmd);
    switch (toupper(linha[0])) {
        case 'N':
            n = sscanf(linha, "%s %s", cmd, peca);
            switch (toupper(peca[0])) {
                case 'X':
                    e = grelha_inicial(e, VALOR_X, '0');
                    printf("M %s\n", peca);
                    break;
                case 'O':
                    e = grelha_inicial(e, VALOR_O, '0');
                    printf("M %s\n", peca);
                    break;
                default:
                    printf("Tem de escolher a peca com que jogar; X ou O\n");
            }

            e.nivel =0;
            iniciarListaLigada(e, &s);
            printa(e);

            break;

        case 'L':

            printf("ler em ficheiro estado do jogo \n"); //guardar estado de jogo no novo ficheiro
            sscanf(linha, " %s %s", cmd, ficheiro);

            FILE *f;

            f= fopen(ficheiro, "r");
            char (v[20][20]);

            cop(f,v);
            fclose(f);


            for (int i=1;i<9;i++) {
                for(int j=0;j<15;j=j+2){
                    if(v[i][j]=='X') e.grelha [i-1][j/2]=VALOR_X;
                    else {if(v[i][j]=='O') e.grelha [i-1][j/2]=VALOR_O;
                        else if (v[i][j]=='-') e.grelha [i-1][j/2]=VAZIA;}
                }
            }

            int i;int j;int r=0;int r2=0;

            if(v[0][0] == 'M') {

                for (i = 0; i < 8; i++) {
                    for (j = 0; j < 8; j++) {
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
                    if (r > r2) e.peca = VALOR_X;
                    else e.peca = VALOR_O;  // o jogador com menos score é sempre o primeiro a jogar, se estiver empatado pode assumir automaticamente o X
                }
            }

                 else if (v[0][0] == 'A') {

                    e.modo= '1';

                    if (v[0][2]=='X') e.peca = VALOR_O;      //PORQUE O X É A PEÇA DO BOT
                    else if (v[0][2]=='O') e.peca = VALOR_X;    // MAS O PRIMEIRO A JOGAR É A PEÇA CONTRARIA

                    if (v[0][4]=='1') e.nivel = 1;
                    else if (v[0][4]=='2') e.nivel = 2;
                    else if (v[0][4]=='3') e.nivel = 3;

                }



            printa(e);

            printf("\n");
            break;

        case 'E':
            printf("guardar em ficheiro estado do jogo \n"); //guardar estado de jogo no novo ficheiro

            sscanf(linha, "%s %s ", cmd, ficheiro);

            FILE *fp;
            fp = fopen(ficheiro, "w+");   //criar/editar o ficheiro
            //printf("%c",ficheiro);
            if (fp == NULL) printf("Erro ao guardar ficheiro");

            else {

                if (e.peca== VALOR_O && e.modo == '1') e.peca = 'X';  //MODO AUTOMATICO GUARDA PEÇA CONTRARIA
                else if (e.peca == VALOR_X && e.modo == '1') e.peca ='O';

                if (e.peca == 'O' && e.modo == '0') e.peca = VALOR_O;
                else if (e.peca == 'X' && e.modo == '0') e.peca = VALOR_X;

                if (e.modo == '1') e.modo ='A';
                else if (e.modo == '0') e.modo ='M';

                fprintf (fp,"%c %c %d\n" ,e.modo, e.peca, e.nivel);

                for (int l = 0; l <= 7; l++) { //imprimir tabuleiro no ficheiro guardado
                    for (int c = 0; c <= 7; c++) {


                        if (e.grelha[l][c] == VALOR_X) {
                            fprintf(fp, "X ");
                            printf("X ");
                        }
                        else if (e.grelha[l][c] == VALOR_O) {
                            fprintf(fp, "O ");
                            printf("O ");
                        }
                        else {
                            fprintf(fp,"- ");
                            printf("- ");
                        }

                    }
                    fprintf(fp, "\n");
                    printf("\n");
                }
            }
            fclose(fp);

            if (e.peca == 'O') e.peca = VALOR_O;
            else if (e.peca == 'X') e.peca = VALOR_X;

            if (e.modo == 'M') e.modo = '0';
            else if (e.modo == 'A') e.modo = '1';

            break;

        case 'J':
            n = sscanf(linha, "%s %d %d", cmd, &lin, &col);

            // O CANTO SUPERIOR ESQUERDO TERIA DE SER J 0 0 (COMO NOS É PEDIDO QUE SEJA J 1 1 , TEMOS:)

            col = col -1;           //FAZ COM QUE A PESSOA POSSO FAZER J 1 1 E AS FUNÇÕES ASSUMAM ' 0 0 '
            lin = lin -1;

            int jogabot=0;             //PARA QUANDO O JOGADOR EFETUAR UMA JOGADA INVALIDA, O BOT NAO EFETUAR A JOGADA

                if (terminaGame(e)==1) {
                    valida(e, lin, col);
                    if (valida(e, lin, col) == 1) {

                        jogabot=1;

                        e.grelha[lin][col] = e.peca;
                        e = trocardepecascc(e, lin, col);
                        e = trocardepecascb(e, lin, col);
                        e = trocardepecasld(e, lin, col);
                        e = trocardepecasle(e, lin, col);
                        e = trocardepecasd1(e, lin, col);
                        e = trocardepecasd2(e, lin, col);
                        e = trocardepecasd3(e, lin, col);
                        e = trocardepecasd4(e, lin, col);


                        e.peca = inverso(e.peca);                // FAZ TROCAR O JOGADOR ATUAl
                        atualizarListaLigada(e, &s);

                    } else printf("Jogada invalida\n");

                    printa(e);

                    resultado(e);
                }

                else if(terminaGame(e)==2){
                    resultado(e);
                    vencedor (e);
                }

                else {
                    e.peca = inverso (e.peca);

                    printa(e);

                    resultado(e);
                    atualizarListaLigada(e, &s);
                }


            if (e.modo == '1' && e.nivel == 1 && jogabot==1){

                int lb, cb;

                printf("Jogada efetuada pelo bot (Nivel Basico)");

                e = jogadaBotBas(e, lb, cb);              //FAZ A JOGADA DO BOT, NIVEL BASICO

                e.peca = inverso(e.peca);                 // VOLTA A TROCAR PARA O JOGADOR HUMANO

                printa (e);

                resultado(e);
            }

            else if (e.modo == '1' && e.nivel == 2 && jogabot==1){

                int lb, cb;

                printf("Jogada efetuada pelo bot (Nivel Medio)");

                e = jogadaBotMed(e, lb, cb);              //FAZ A JOGADA DO BOT, NIVEL MEDIO

                e.peca = inverso(e.peca);                 // VOLTA A TROCAR PARA O JOGADOR HUMANO

                printa (e);

                resultado(e);
            }

            else if (e.modo == '1' && e.nivel == 3 && jogabot==1){

                int lb, cb;

                printf("Jogada efetuada pelo bot (Nivel Profissional)");

                e = jogadaBotPro(e, lb, cb);              //FAZ A JOGADA DO BOT, NIVEL PROFISSIONAL

                e.peca = inverso(e.peca);                 // VOLTA A TROCAR PARA O JOGADOR HUMANO

                printa(e);

                resultado(e);
            }

            if(terminaGame(e)==2){        // PARA VER SE O JOGO TEM DE ACABAR, DEVIDO A NINGUEM TER JOGADAS POSSIVEIS

                printf ("\n");
                vencedor (e);

                e= grelha_nova(e);         //PARA REINICIAR O TABULEIRO (PARA QUE SE POSSA COMEÇAR NOVO JOGO)

                e.peca = COMANDO;

            }

            else if (terminaGame (e) == 3){          // PARA VER SE O JOGAGOR TEM DE VOLTAR A JOGAR (OPONENTE SEM JOGADAS)

                printf("Joga de novo: (OPONENTE SEM JOGADAS)\n");

                e.peca = inverso (e.peca);

                printa(e);

                resultado(e);
                atualizarListaLigada(e, &s);
            }

            break;

        case 'S':
            n = sscanf(linha, "%s", cmd);
            int l, c;

            printf ("Tabuleiro com as jogadas possiveis: \n");
            for (l = 0; l < 8; l++) {
                for (c = 0; c < 8; c++) {
                    if (e.grelha[l][c] == VALOR_X) printf("X ");
                    else if (e.grelha[l][c] == VALOR_O) printf("O ");
                    else if (valida(e, l, c) == 1) printf(". ");
                    else printf("- ");
                }
                printf("\n");
            }

            printf ("Jogadas possiveis:\n");   // 2 CICLOS PARA MOSTRAR AS COORDENADAS DAS JOGADAS POSSVEIS PARA E.PECA
            for (l = 0; l < 8; l++) {
                for (c = 0; c < 8; c++) {
                    if (valida (e, l, c) == 1) printf ("Linha: %d Coluna: %d \n", l+1 , c+1);  // +1 para assumir a posiçao corretamente
                }
            }


            break;

        case 'U':

            if (e.modo=='0') {
                if (s.spointer != 0) {               //Para caso haja um recuo que passe o estado da grela inicial
                    e = undo(e, &s);
                } else {
                    printf("Nao pode recuar mais no estado de jogo:\n");
                }
            }
            else if (e.modo == '1'){
                if (s.spointer != 0) {               //Para caso haja um recuo que passe o estado da grela inicial
                    e = undo(e, &s);
                } else {
                    printf("Nao pode recuar mais no estado de jogo:\n");
                }
                e.peca = inverso (e.peca);
            }

            break;

        case 'H':

            n = sscanf(linha, "%s", cmd);
            int l2, c2;
            int parar=0;
            int coord=0;

            printf ("Tabuleiro com a sugestao: \n");
            for (l2 = 0; l2 < 8; l2++) {
                for (c2 = 0; c2 < 8; c2++) {
                    if (valida (e,l2,c2) && parar==0){
                        printf ("? ");
                        parar++;
                    }
                    else if (e.grelha [l2] [c2] == VALOR_X ) printf ("X ");
                    else if (e.grelha [l2] [c2] == VALOR_O ) printf ("O ");
                    else printf ("- ");
                }
                printf("\n");
            }

            printf ("Coordenadas da jogada sugestao: \n");              //2 CICLOS PARA DAR AS COORDENADAS DA JOGADA SUGESTÃO
            for (l2 = 0; l2 < 8; l2++) {
                for (c2 = 0; c2 < 8; c2++) {
                    if (valida(e, l2, c2) && coord == 0) {
                        printf("Linha: %d Coluna: %d \n", l2+1 , c2+1);  // +1 para assumir a posiçao corretamente
                        coord++;
                    }
                }
            }

            break;

                case 'A':            //BOT//

                    n = sscanf(linha, "%s %s %s", cmd, peca, nivel);
                    int cb, lb;
                    int indicacao = 0;

                    switch (toupper(peca[0])) {

                case 'X':
                    e = grelha_inicial(e, VALOR_X, '1');
                            printf("A %s %s\n", peca, nivel);

                    break;

                case 'O':
                    e = grelha_inicial(e, VALOR_O, '1');
                    e.peca = inverso (e.peca);                    //para começar a jogar o X
                    indicacao = 1;
                    printf("A %s %s\n", peca, nivel);

                    break;

                default:
                    printf("Tem de escolher a peca com que jogar; X ou O\n");
            }

            iniciarListaLigada(e, &s);

            switch (toupper(nivel[0])) {               //escolha do nível a jogar
                case '1':

                    printf ("OPONENTE BASICO:\n");

                    e.nivel= 1;                   //define nivel '1'

                    break;

                    case '2':

                    printf ("OPONENTE MEDIO:\n");

                    e.nivel= 2;                               //define nivel '2'

                    break;

                    case '3':

                        printf ("OPONENTE PROFISSIONAL:\n");

                        e.nivel= 3;                      //define nivel '3'

                        break;

                default:
                    printf("Tem de escolher o nível que quer jogar ('1','2','3') \n");
            }

            /* AS PRÓXIMAS CONDIÇÕES, SERVEM PARA EM CASA DE O JOGADOR HUMANO ESCOLHER A PEÇA '0', COMO A JOGADA
            NO MODO AUTOMÁTICO TEM DE SER EFETUADA SEMPRE PELO JOGADOR DA PEÇA 'X',AQUI O BOT EFETUA LOGO
            A PRIMEIRA JOGADA  */

            if (indicacao == 1 && e.nivel == 1) {         //SE HUMANO ESCOLHER 'O' O BOT FAZ A PRIMEIRA JOGADA 'X'

                    printf("Tabuleiro com jogada efetuada pelo bot:\n");

                    e = jogadaBotBas(e, lb, cb);              //FAZ A JOGADA DO BOT, NIVEL BASICO

                    e.peca = inverso(e.peca);                 // VOLTA A TROCAR PARA O JOGADOR HUMANO

                    atualizarListaLigada(e, &s);
                }

            else if(indicacao == 1 && e.nivel ==2){     //SE HUMANO ESCOLHER 'O' O BOT FAZ A PRIMEIRA JOGADA 'X'

                printf("Tabuleiro com jogada efetuada pelo bot:\n");

                e = jogadaBotMed(e, lb, cb);              //FAZ A JOGADA DO BOT, NIVEL MEDIO

                e.peca = inverso(e.peca);                 // VOLTA A TROCAR PARA O JOGADOR HUMANO

                atualizarListaLigada(e, &s);

            }

            else if(indicacao == 1 && e.nivel ==3){     //SE HUMANO ESCOLHER 'O' O BOT FAZ A PRIMEIRA JOGADA 'X'

                printf("Tabuleiro com jogada efetuada pelo bot:\n");

                e = jogadaBotPro(e, lb, cb);              //FAZ A JOGADA DO BOT, NIVEL PROFISSIONAL

                e.peca = inverso(e.peca);                 // VOLTA A TROCAR PARA O JOGADOR HUMANO

                atualizarListaLigada(e, &s);

            }

            printa(e);

            resultado(e);

                    break;


                case 'Q':          //Para efetuar a saida do programa
                    exit(0);

                default:
                    printf("Comando Invalido!\n");

            }

            return e;

    }



    void print_prompt(ESTADO e) {
        switch (e.peca) {
            case VALOR_X:
                printf("%s X>", PROMPT);
                break;
            case VALOR_O:
                printf("%s O>", PROMPT);
                break;
            default:
                printf("%s ?>", PROMPT);

        }
    }

    void intepretador(ESTADO e) {
        char linha[MAX_BUF];
        print_prompt(e);
        while (fgets(linha, MAX_BUF, stdin)) {
            e = intepretar(e, linha);
            print_prompt(e);
        }
    }

