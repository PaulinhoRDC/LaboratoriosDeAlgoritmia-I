//
// Created by Paulo Costa on 17/04/2019.
//

#ifndef PROJETO_INTEPRETADOR_H
#define PROJETO_INTEPRETADOR_H

#include "estado.h"
#include <stdbool.h>

#define PROMPT "Riversi"

ESTADO intepretar (ESTADO e, char *linha);
void intepretador (ESTADO e);
void print_prompt(ESTADO e);
int valida (ESTADO e, int x, int y);
int valida2 (ESTADO e, int x, int y);   //nao usada





#endif //PROJETO_INTEPRETADOR_H
