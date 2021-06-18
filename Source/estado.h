//
// Created by Paulo Costa on 17/04/2019.
//

#ifndef PROJETO_ESTADO_H
#define PROJETO_ESTADO_H

#define MAX_BUF 1024



// definição de valores possiveis no tabuleiro
typedef enum {VAZIA, VALOR_X, VALOR_O, COMANDO} VALOR;

/**
Estrutura que armazena o estado do jogo
*/
typedef struct estado {
    VALOR peca;                     // peça do jogador que vai jogar!
    VALOR grelha[8][8];
    char modo;              // modo em que se está a jogar! 0-> manual, 1-> contra PC
    int nivel;        // nível do bot: / 0 (SE NAO FOR) / 1(BASICO) / 2(MEDIO) / 3(PROFISSIONAL)
} ESTADO;

// ESTRUTURA PARA A LISTA LIGADA
typedef struct stack{
    int spointer;
    ESTADO estados [128];
} STACK;


ESTADO grelha_nova (ESTADO e);

ESTADO grelha_inicial (ESTADO e, char peca, char modo);
void printa(ESTADO);

//FUNÇOES PARA VERIFICAR SE A JOGADA É DE FACTO VALIDA
int validacc (ESTADO e, int x , int y);
int validacb (ESTADO e, int x, int y);
int validale (ESTADO e, int x, int y);
int validald (ESTADO e, int x, int y);
int validad1 (ESTADO e, int x, int y);
int validad2 (ESTADO e, int x, int y);
int validad3 (ESTADO e, int x, int y);
int validad4 (ESTADO e, int x, int y);


//FUNÇOES PARA TROCAR DE PEÇAS EM TODAS AS DIREÇOES QUE FOR DE FACTO 'VALIDO'
ESTADO trocardepecascc (ESTADO e, int x, int y);
ESTADO trocardepecascb (ESTADO e, int x, int y);
ESTADO trocardepecasle (ESTADO e, int x, int y);
ESTADO trocardepecasld (ESTADO e, int x, int y);
ESTADO trocardepecasd1 (ESTADO e, int x, int y);
ESTADO trocardepecasd2 (ESTADO e, int x, int y);
ESTADO trocardepecasd3 (ESTADO e, int x, int y);
ESTADO trocardepecasd4 (ESTADO e, int x, int y);

VALOR inverso (VALOR p);
int valida (ESTADO e, int x, int y);

void resultado (ESTADO e);
void vencedor (ESTADO e);

//FUNÇOES UTILIZADAS PARA A UNDO
void iniciarListaLigada (ESTADO e, STACK *s);
void atualizarListaLigada (ESTADO e, STACK *s);
ESTADO undo (ESTADO e, STACK *s);

//termina
int terminaGame (ESTADO e);

//CASE L

void cop (FILE *f,char v[20][20]);

                                                //BOT//

// FUNÇÕES NECESSÁRIAS

ESTADO jogadaBotBas (ESTADO e, int l, int c);
int quantaspecas (ESTADO e, int x, int y);

ESTADO jogadaBotMed (ESTADO e, int l, int c);

ESTADO jogadaBotPro (ESTADO e, int l, int c);
int regiaodajogada (int l, int c);

#endif //PROJETO_ESTADO_H
